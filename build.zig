const std = @import("std");
const Build = std.Build;

const log = std.log.scoped(.mach_dxcompiler);

pub fn build(b: *Build) !void {
    const optimize = b.standardOptimizeOption(.{});
    const target = b.standardTargetOptions(.{});
    const from_source = b.option(bool, "from-source", "Build DXC from source (large C++ codebase)") orelse false;

    const mach_dxcompiler = b.addModule("mach-dxcompiler", .{
        .source_file = .{ .path = "src/main.zig" },
    });
    _ = mach_dxcompiler;

    const main_tests = b.addTest(.{
        .name = "dxcompiler-tests",
        .root_source_file = .{ .path = "src/main.zig" },
        .target = target,
        .optimize = optimize,
    });
    try link(b, main_tests, .{
        .install_libs = true,
        .from_source = from_source,
    });
    b.installArtifact(main_tests);
    const test_step = b.step("test", "Run library tests");
    test_step.dependOn(&b.addRunArtifact(main_tests).step);
}

pub const Options = struct {
    /// Whether libraries and headers should be installed to e.g. zig-out/
    install_libs: bool = false,

    /// Whether to build dxcompiler from source or not.
    from_source: bool = false,

    /// The binary release version to use from https://github.com/hexops/mach-dxcompiler/releases
    binary_version: []const u8 = "release-d7b308b",

    /// When building from source, which repository and revision to clone.
    source_repository: []const u8 = "https://github.com/hexops/DirectXShaderCompiler",
    source_revision: []const u8 = "84da60c6cda610b8068bd0d25eb51ac40fbf99c4", // main branch
};

pub fn link(b: *Build, step: *std.build.CompileStep, options: Options) !void {
    const opt = options;

    if (options.from_source)
        try linkFromSource(b, step, opt)
    else
        try linkFromBinary(b, step, opt);
}

fn linkFromSource(b: *Build, step: *std.build.CompileStep, options: Options) !void {
    _ = step;
    try ensureGitRepoCloned(b.allocator, options.source_repository, options.source_revision, sdkPath("/libs/DirectXShaderCompiler"));

    // TODO: investigate SSE2 #define / cmake option for CPU target
    // TODO: investigate option to disable SPIRV to make binary smaller
    // TODO: add toolchain/ for other targets
    // TODO: do not hard-code these:
    const machZigTarget = "x86_64-windows-gnu";
    const cmakeBuildType = "Release";
    ensureCMake(b.allocator);

    const buildDir = sdkPath("/libs/DirectXShaderCompiler/build-" ++ machZigTarget);
    log.info("cd {s}", .{buildDir});
    if (std.fs.openDirAbsolute(buildDir, .{})) |_| {
        // Already configured
        log.info("Already configured with cmake, skipping.", .{});
    } else |err| return switch (err) {
        error.FileNotFound => {
            log.info("Configuring with cmake", .{});
            try exec(b.allocator, &[_][]const u8{
                "cmake",
                "-B",
                "build-" ++ machZigTarget,
                "-G",
                "Ninja",
                "-C",
                "./cmake/caches/PredefinedParams.cmake",
                "-DCMAKE_TOOLCHAIN_FILE=../../toolchain/zig-toolchain-" ++ machZigTarget ++ ".cmake",
                "-DCMAKE_BUILD_TYPE=" ++ cmakeBuildType,
                "-DSPIRV_BUILD_TESTS=OFF",
                "-DLLVM_LIT_ARGS=--xunit-xml-output=testresults.xunit.xml",
                "-DLLVM_BUILD_TESTS=OFF",
                "-DLLVM_INCLUDE_TESTS=OFF",
                "-DCLANG_INCLUDE_TESTS=OFF",
                "-DHLSL_INCLUDE_TESTS=OFF",
                "-DHLSL_INCLUDE_TESTS=OFF",
                "-DHLSL_BUILD_DXILCONV=OFF",
                "-DLLVM_ENABLE_WERROR=On",
                "-DLLVM_ENABLE_EH:BOOL=ON",
                // TODO: we shouldn't need this anymore
                // "-DLLVM_TOOLS_BINARY_DIR="$(dirname $(which llvm-tblgen))" \
                "-DDIASDK_GUIDS_LIBRARY=./external/DIA/lib/x64/diaguids.lib",
                "-DDIASDK_INCLUDE_DIR=./external/DIA/include",
                ".",
            }, sdkPath("/libs/DirectXShaderCompiler"));
        },
        else => err,
    };

    ensureNinja(b.allocator);
    try exec(b.allocator, &[_][]const u8{
        "ninja",
        "-C",
        "build-" ++ machZigTarget,
    }, sdkPath("/libs/DirectXShaderCompiler"));
}

pub fn linkFromBinary(b: *Build, step: *std.build.CompileStep, options: Options) !void {
    _ = options;
    _ = step;
    _ = b;
    // TODO
}

fn ensureGitRepoCloned(allocator: std.mem.Allocator, clone_url: []const u8, revision: []const u8, dir: []const u8) !void {
    if (isEnvVarTruthy(allocator, "NO_ENSURE_SUBMODULES") or isEnvVarTruthy(allocator, "NO_ENSURE_GIT")) {
        return;
    }

    ensureGit(allocator);

    if (std.fs.openDirAbsolute(dir, .{})) |_| {
        const current_revision = try getCurrentGitRevision(allocator, dir);
        if (!std.mem.eql(u8, current_revision, revision)) {
            // Reset to the desired revision
            exec(allocator, &[_][]const u8{ "git", "fetch" }, dir) catch |err| log.warn("failed to 'git fetch' in {s}: {s}\n", .{ dir, @errorName(err) });
            try exec(allocator, &[_][]const u8{ "git", "checkout", "--quiet", "--force", revision }, dir);
            try exec(allocator, &[_][]const u8{ "git", "submodule", "update", "--init", "--recursive" }, dir);
        }
        return;
    } else |err| return switch (err) {
        error.FileNotFound => {
            log.info("cloning required dependency..\ngit clone {s} {s}..\n", .{ clone_url, dir });

            try exec(allocator, &[_][]const u8{ "git", "clone", "-c", "core.longpaths=true", clone_url, dir }, sdkPath("/"));
            try exec(allocator, &[_][]const u8{ "git", "checkout", "--quiet", "--force", revision }, dir);
            try exec(allocator, &[_][]const u8{ "git", "submodule", "update", "--init", "--recursive" }, dir);
            return;
        },
        else => err,
    };
}

fn getCurrentGitRevision(allocator: std.mem.Allocator, cwd: []const u8) ![]const u8 {
    const result = try std.ChildProcess.exec(.{ .allocator = allocator, .argv = &.{ "git", "rev-parse", "HEAD" }, .cwd = cwd });
    allocator.free(result.stderr);
    if (result.stdout.len > 0) return result.stdout[0 .. result.stdout.len - 1]; // trim newline
    return result.stdout;
}

fn ensureGit(allocator: std.mem.Allocator) void {
    const argv = &[_][]const u8{ "git", "--version" };
    const result = std.ChildProcess.exec(.{
        .allocator = allocator,
        .argv = argv,
        .cwd = ".",
    }) catch { // e.g. FileNotFound
        log.err("'git --version' failed. Is git not installed?", .{});
        std.process.exit(1);
    };
    defer {
        allocator.free(result.stderr);
        allocator.free(result.stdout);
    }
    if (result.term.Exited != 0) {
        log.err("'git --version' failed. Is git not installed?", .{});
        std.process.exit(1);
    }
}

fn ensureCMake(allocator: std.mem.Allocator) void {
    const argv = &[_][]const u8{ "cmake", "--version" };
    const result = std.ChildProcess.exec(.{
        .allocator = allocator,
        .argv = argv,
        .cwd = ".",
    }) catch { // e.g. FileNotFound
        log.err("'cmake --version' failed. Is cmake not installed?", .{});
        std.process.exit(1);
    };
    defer {
        allocator.free(result.stderr);
        allocator.free(result.stdout);
    }
    if (result.term.Exited != 0) {
        log.err("'cmake --version' failed. Is cmake not installed?", .{});
        std.process.exit(1);
    }
}

fn ensureNinja(allocator: std.mem.Allocator) void {
    const argv = &[_][]const u8{ "ninja", "--version" };
    const result = std.ChildProcess.exec(.{
        .allocator = allocator,
        .argv = argv,
        .cwd = ".",
    }) catch { // e.g. FileNotFound
        log.err("'ninja --version' failed. Is ninja not installed?", .{});
        std.process.exit(1);
    };
    defer {
        allocator.free(result.stderr);
        allocator.free(result.stdout);
    }
    if (result.term.Exited != 0) {
        log.err("'ninja --version' failed. Is ninja not installed?", .{});
        std.process.exit(1);
    }
}

fn exec(allocator: std.mem.Allocator, argv: []const []const u8, cwd: []const u8) !void {
    log.info("cd {s}", .{cwd});
    var buf = std.ArrayList(u8).init(allocator);
    for (argv) |arg| {
        try std.fmt.format(buf.writer(), "{s} ", .{arg});
    }
    log.info("{s}", .{buf.items});

    var child = std.ChildProcess.init(argv, allocator);
    child.cwd = cwd;
    _ = try child.spawnAndWait();
}

fn isEnvVarTruthy(allocator: std.mem.Allocator, name: []const u8) bool {
    if (std.process.getEnvVarOwned(allocator, name)) |truthy| {
        defer allocator.free(truthy);
        if (std.mem.eql(u8, truthy, "true")) return true;
        return false;
    } else |_| {
        return false;
    }
}

fn sdkPath(comptime suffix: []const u8) []const u8 {
    if (suffix[0] != '/') @compileError("suffix must be an absolute path");
    return comptime blk: {
        const root_dir = std.fs.path.dirname(@src().file) orelse ".";
        break :blk root_dir ++ suffix;
    };
}
