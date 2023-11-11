const std = @import("std");
const Build = std.Build;

const log = std.log.scoped(.mach_dxcompiler);
const prefix = "libs/DirectXShaderCompiler";

pub fn build(b: *Build) !void {
    const optimize = b.standardOptimizeOption(.{});
    const target = b.standardTargetOptions(.{});
    const from_source = b.option(bool, "from-source", "Build DXC from source (large C++ codebase)") orelse false;

    // Zig bindings
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
        .build_binary_tools = true,
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

    /// Whether to build and install dxc.exe
    build_binary_tools: bool = false,

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
    try ensureGitRepoCloned(b.allocator, options.source_repository, options.source_revision, sdkPath("/libs/DirectXShaderCompiler"));

    const machdxc = b.addStaticLibrary(.{
        .name = "machdxc",
        .root_source_file = b.addWriteFiles().add("empty.c", ""),
        .optimize = step.optimize,
        .target = step.target,
    });
    b.installArtifact(machdxc);
    if (options.install_libs) b.installArtifact(machdxc);
    machdxc.addCSourceFile(.{ .file = .{ .path = "src/mach_dxc.cpp" }, .flags = &.{} });

    addConfigHeaders(b, machdxc);
    addIncludes(machdxc);
    try appendLangScannedSources(b, machdxc, .{
        .rel_dirs = &.{
            prefix ++ "/tools/clang/lib/Lex",
            prefix ++ "/tools/clang/lib/Basic",
            prefix ++ "/tools/clang/lib/Driver",
            prefix ++ "/tools/clang/lib/Analysis",
            prefix ++ "/tools/clang/lib/Index",
            prefix ++ "/tools/clang/lib/Parse",
            prefix ++ "/tools/clang/lib/AST",
            prefix ++ "/tools/clang/lib/Edit",
            prefix ++ "/tools/clang/lib/Sema",
            prefix ++ "/tools/clang/lib/CodeGen",
            prefix ++ "/tools/clang/lib/ASTMatchers",
            prefix ++ "/tools/clang/lib/Tooling/Core",
            prefix ++ "/tools/clang/lib/Tooling",
            prefix ++ "/tools/clang/lib/Format", // TODO: try build without it
            prefix ++ "/tools/clang/lib/Rewrite",
            prefix ++ "/tools/clang/lib/Frontend/Rewrite",
            prefix ++ "/tools/clang/lib/Frontend",
            prefix ++ "/tools/clang/tools/libclang",
            prefix ++ "/tools/clang/tools/dxcompiler",

            prefix ++ "/lib/Bitcode/Reader",
            prefix ++ "/lib/Bitcode/Writer",
            prefix ++ "/lib/IR",
            prefix ++ "/lib/IRReader",
            prefix ++ "/lib/Linker",
            prefix ++ "/lib/AsmParser",
            prefix ++ "/lib/Analysis",
            prefix ++ "/lib/Analysis/IPA",
            prefix ++ "/lib/MSSupport",
            prefix ++ "/lib/Transforms/Utils",
            prefix ++ "/lib/Transforms/InstCombine",
            prefix ++ "/lib/Transforms/IPO",
            prefix ++ "/lib/Transforms/Scalar",
            prefix ++ "/lib/Transforms/Vectorize",
            prefix ++ "/lib/Target",
            prefix ++ "/lib/ProfileData",
            prefix ++ "/lib/Option",
            prefix ++ "/lib/PassPrinters",
            prefix ++ "/lib/Passes",
            prefix ++ "/lib/HLSL",
            prefix ++ "/lib/Support",
            prefix ++ "/lib/DxcSupport",
            prefix ++ "/lib/DxcBindingTable",
            prefix ++ "/lib/DXIL",
            prefix ++ "/lib/DxilContainer",
            prefix ++ "/lib/DxilPIXPasses",
            prefix ++ "/lib/DxilCompression",
            prefix ++ "/lib/DxilRootSignature",
        },
        .flags = &.{},
        .excluding_contains = &.{
            // tools/clang/lib/Analysis/CMakeLists.txt
            "CocoaConventions.cpp",
            "FormatString.cpp",
            "PrintfFormatString.cpp",
            "ScanfFormatString.cpp",

            // tools/clang/lib/AST/CMakeLists.txt
            "NSAPI.cpp",

            // tools/clang/lib/Edit/CMakeLists.txt
            "RewriteObjCFoundationAPI.cpp",

            // tools/clang/lib/CodeGen/CMakeLists.txt
            "CGObjCGNU.cpp",
            "CGObjCMac.cpp",
            "CGObjCRuntime.cpp",
            "CGOpenCLRuntime.cpp",
            "CGOpenMPRuntime.cpp",

            // tools/clang/lib/Frontend/Rewrite/CMakeLists.txt
            "RewriteModernObjC.cpp",

            // tools/clang/lib/Frontend/CMakeLists.txt
            "ChainedIncludesSource.cpp",

            // tools/clang/tools/libclang/CMakeLists.txt
            "ARCMigrate.cpp",
            "BuildSystem.cpp",

            // tools/clang/tools/dxcompiler/CMakeLists.txt
            "dxillib.cpp",

            // lib/Transforms/Vectorize/CMakeLists.txt
            "BBVectorize.cpp",
            "LoopVectorize.cpp",
            "LPVectorizer.cpp",

            // lib/Support/CMakeLists.txt
            "DynamicLibrary.cpp",
            "PluginLoader.cpp",
        },
    });

    // Windows
    try appendLangScannedSources(b, machdxc, .{
        .rel_dirs = &.{prefix ++ "/lib/Support/Windows"},
        .flags = &.{},
        .excluding_contains = &.{".inc.cpp"},
    });

    machdxc.linkSystemLibrary("ole32");
    machdxc.linkSystemLibrary("oleaut32");
    machdxc.linkSystemLibrary("version");

    // TODO: ability to use MSVC dxcapi.h via this path:
    // machdxc.addIncludePath(.{ .path = prefix++"/include/dxc" });
    // TODO: install the resulting direct3d_headers / dxcapi.h?
    // TODO: install MSVC header?:
    // machdxc.installHeader(prefix++"/include/dxc/dxcapi.h", "dxc");
    if (options.install_libs) b.installArtifact(machdxc);

    machdxc.linkLibCpp();
    machdxc.addIncludePath(.{ .path = "src" });
    machdxc.linkLibrary(b.dependency("direct3d_headers", .{
        .target = step.target,
        .optimize = step.optimize,
    }).artifact("direct3d-headers"));
    @import("direct3d_headers").addLibraryPath(machdxc);

    // TODO: investigate SSE2 #define / cmake option for CPU target
    // TODO: investigate option to disable SPIRV to make binary smaller (ENABLE_SPIRV_CODEGEN)

    // TODO: investigate how projects/dxilconv/lib/DxbcConverter/DxbcConverterImpl.h is getting pulled
    // in, we can get rid of dxbc conversion presumably

    if (options.build_binary_tools) {
        const dxc_exe = b.addExecutable(.{
            .name = "dxc",
            .root_source_file = b.addWriteFiles().add("empty.c", ""),
            .optimize = step.optimize,
            .target = step.target,
        });
        dxc_exe.addCSourceFile(.{
            .file = .{ .path = prefix ++ "/tools/clang/tools/dxc/dxcmain.cpp" },
            .flags = &.{"-std=c++17"},
        });
        dxc_exe.addIncludePath(.{ .path = prefix ++ "/tools/clang/tools" });
        dxc_exe.addIncludePath(.{ .path = prefix ++ "/include" });
        addConfigHeaders(b, dxc_exe);
        addIncludes(dxc_exe);
        try appendLangScannedSources(b, dxc_exe, .{
            .rel_dirs = &.{prefix ++ "/tools/clang/tools/dxclib"},
            .flags = &.{},
            .excluding_contains = &.{},
        });
        b.installArtifact(dxc_exe);
        dxc_exe.linkLibrary(machdxc);
        dxc_exe.linkLibrary(b.dependency("direct3d_headers", .{
            .target = dxc_exe.target,
            .optimize = dxc_exe.optimize,
        }).artifact("direct3d-headers"));
        @import("direct3d_headers").addLibraryPath(dxc_exe);
    }

    step.linkLibrary(machdxc);
    step.addIncludePath(.{ .path = "src" });
    step.linkLibrary(b.dependency("direct3d_headers", .{
        .target = step.target,
        .optimize = step.optimize,
    }).artifact("direct3d-headers"));
    @import("direct3d_headers").addLibraryPath(step);
}

pub fn linkFromBinary(b: *Build, step: *std.build.CompileStep, options: Options) !void {
    _ = options;
    _ = step;
    _ = b;
    // TODO
}

pub fn addConfigHeaders(b: *Build, step: *std.build.CompileStep) void {
    // /tools/clang/include/clang/Config/config.h.cmake
    step.addConfigHeader(b.addConfigHeader(
        .{
            .style = .{ .cmake = .{ .path = prefix ++ "/tools/clang/include/clang/Config/config.h.cmake" } },
            .include_path = "clang/Config/config.h",
        },
        .{},
    ));

    // /include/llvm/Config/AsmParsers.def.in
    step.addConfigHeader(b.addConfigHeader(
        .{
            .style = .{ .cmake = .{ .path = prefix ++ "/include/llvm/Config/AsmParsers.def.in" } },
            .include_path = "llvm/Config/AsmParsers.def",
        },
        .{},
    ));

    // /include/llvm/Config/Disassemblers.def.in
    step.addConfigHeader(b.addConfigHeader(
        .{
            .style = .{ .cmake = .{ .path = prefix ++ "/include/llvm/Config/Disassemblers.def.in" } },
            .include_path = "llvm/Config/Disassemblers.def",
        },
        .{},
    ));

    // /include/llvm/Config/Targets.def.in
    step.addConfigHeader(b.addConfigHeader(
        .{
            .style = .{ .cmake = .{ .path = prefix ++ "/include/llvm/Config/Targets.def.in" } },
            .include_path = "llvm/Config/Targets.def",
        },
        .{},
    ));

    // /include/llvm/Config/AsmPrinters.def.in
    step.addConfigHeader(b.addConfigHeader(
        .{
            .style = .{ .cmake = .{ .path = prefix ++ "/include/llvm/Config/AsmPrinters.def.in" } },
            .include_path = "llvm/Config/AsmPrinters.def",
        },
        .{},
    ));

    // /include/llvm/Support/DataTypes.h.cmake
    step.addConfigHeader(b.addConfigHeader(
        .{
            .style = .{ .cmake = .{ .path = prefix ++ "/include/llvm/Support/DataTypes.h.cmake" } },
            .include_path = "llvm/Support/DataTypes.h",
        },
        .{
            .HAVE_INTTYPES_H = 1,
            .HAVE_STDINT_H = 1,
            .HAVE_UINT64_T = 1,
            // /* #undef HAVE_U_INT64_T */
        },
    ));

    // /include/llvm/Config/abi-breaking.h.cmake
    step.addConfigHeader(b.addConfigHeader(
        .{
            .style = .{ .cmake = .{ .path = prefix ++ "/include/llvm/Config/abi-breaking.h.cmake" } },
            .include_path = "llvm/Config/abi-breaking.h",
        },
        .{},
    ));

    // /include/llvm/Config/llvm-config.h.cmake
    step.addConfigHeader(b.addConfigHeader(
        .{
            .style = .{ .cmake = .{ .path = prefix ++ "/include/llvm/Config/llvm-config.h.cmake" } },
            .include_path = "llvm/Config/llvm-config.h",
        },
        getLLVMConfig(),
    ));

    // TODO
    // // /include/llvm/Config/config.h.cmake
    // machdxc.addConfigHeader(b.addConfigHeader(
    //     .{
    //         .style = .{ .cmake = .{ .path = prefix ++ "/include/llvm/Config/config.h.cmake" } },
    //         .include_path = "llvm/Config/config.h",
    //     },
    //     getLLVMConfig(),
    // ));

    // /include/dxc/config.h.cmake
    step.addConfigHeader(b.addConfigHeader(
        .{
            .style = .{ .cmake = .{ .path = prefix ++ "/include/dxc/config.h.cmake" } },
            .include_path = "dxc/config.h",
        },
        .{
            .DXC_DISABLE_ALLOCATOR_OVERRIDES = false,
        },
    ));
}

pub fn addIncludes(step: *std.build.CompileStep) void {
    step.addIncludePath(.{ .path = prefix ++ "/external/DIA/include" });
    // TODO: replace generated-include with logic to actually generate this code
    step.addIncludePath(.{ .path = "generated-include/" });
    step.addIncludePath(.{ .path = prefix ++ "/tools/clang/include" });
    step.addIncludePath(.{ .path = prefix ++ "/include" });
    step.addIncludePath(.{ .path = prefix ++ "/include/llvm" });
    step.addIncludePath(.{ .path = prefix ++ "/include/llvm/llvm_assert" });
    step.addIncludePath(.{ .path = prefix ++ "/include/llvm/Bitcode" });
    step.addIncludePath(.{ .path = prefix ++ "/include/llvm/IR" });
    step.addIncludePath(.{ .path = prefix ++ "/include/llvm/IRReader" });
    step.addIncludePath(.{ .path = prefix ++ "/include/llvm/Linker" });
    step.addIncludePath(.{ .path = prefix ++ "/include/llvm/Analysis" });
    step.addIncludePath(.{ .path = prefix ++ "/include/llvm/Transforms" });
    step.addIncludePath(.{ .path = prefix ++ "/include/llvm/Transforms/Utils" });
    step.addIncludePath(.{ .path = prefix ++ "/include/llvm/Transforms/InstCombine" });
    step.addIncludePath(.{ .path = prefix ++ "/include/llvm/Transforms/IPO" });
    step.addIncludePath(.{ .path = prefix ++ "/include/llvm/Transforms/Scalar" });
    step.addIncludePath(.{ .path = prefix ++ "/include/llvm/Transforms/Vectorize" });
    step.addIncludePath(.{ .path = prefix ++ "/include/llvm/Target" });
    step.addIncludePath(.{ .path = prefix ++ "/include/llvm/ProfileData" });
    step.addIncludePath(.{ .path = prefix ++ "/include/llvm/Option" });
    step.addIncludePath(.{ .path = prefix ++ "/include/llvm/PassPrinters" });
    step.addIncludePath(.{ .path = prefix ++ "/include/llvm/Passes" });
}

const LLVMConfig = struct {
    // /* Installation directory for binary executables */
    // /* #undef LLVM_BINDIR */

    // /* Time at which LLVM was configured */
    // /* #undef LLVM_CONFIGTIME */

    // /* Installation directory for data files */
    // /* #undef LLVM_DATADIR */

    // /* Target triple LLVM will generate code for by default */
    LLVM_DEFAULT_TARGET_TRIPLE: []const u8 = "dxil-ms-dx",

    // /* Installation directory for documentation */
    // /* #undef LLVM_DOCSDIR */

    // /* Define if threads enabled */
    LLVM_ENABLE_THREADS: i64 = 1,

    // /* Installation directory for config files */
    // /* #undef LLVM_ETCDIR */

    // /* Has gcc/MSVC atomic intrinsics */
    LLVM_HAS_ATOMICS: i64 = 1,

    // /* Host triple LLVM will be executed on */
    LLVM_HOST_TRIPLE: []const u8,

    // /* Installation directory for include files */
    // /* #undef LLVM_INCLUDEDIR */

    // /* Installation directory for .info files */
    // /* #undef LLVM_INFODIR */

    // /* Installation directory for man pages */
    // /* #undef LLVM_MANDIR */

    // /* LLVM architecture name for the native architecture, if available */
    LLVM_NATIVE_ARCH: []const u8,

    // /* LLVM name for the native AsmParser init function, if available */
    // /* #undef LLVM_NATIVE_ASMPARSER */

    // /* LLVM name for the native AsmPrinter init function, if available */
    // /* #undef LLVM_NATIVE_ASMPRINTER */

    // /* LLVM name for the native Disassembler init function, if available */
    // /* #undef LLVM_NATIVE_DISASSEMBLER */

    // /* LLVM name for the native Target init function, if available */
    // /* #undef LLVM_NATIVE_TARGET */

    // /* LLVM name for the native TargetInfo init function, if available */
    // /* #undef LLVM_NATIVE_TARGETINFO */

    // /* LLVM name for the native target MC init function, if available */
    // /* #undef LLVM_NATIVE_TARGETMC */

    // /* Define if this is Unixish platform */
    LLVM_ON_UNIX: ?i64 = null,

    // /* Define if this is Win32ish platform */
    LLVM_ON_WIN32: ?i64 = null,

    // /* Installation prefix directory */
    LLVM_PREFIX: []const u8,

    // /* Define if we have the Intel JIT API runtime support library */
    // /* #undef LLVM_USE_INTEL_JITEVENTS */

    // /* Define if we have the oprofile JIT-support library */
    // /* #undef LLVM_USE_OPROFILE */

    LLVM_VERSION_MAJOR: i64 = 3,
    LLVM_VERSION_MINOR: i64 = 7,
    LLVM_VERSION_PATCH: i64 = 0,
    LLVM_VERSION_STRING: []const u8 = "3.7-v1.4.0.2274-1812-machdxc",

    // /* Define if we link Polly to the tools */
    // /* #undef LINK_POLLY_INTO_TOOLS */
};

fn getLLVMConfig() LLVMConfig {
    // TODO: non-windows architectures
    return .{
        .LLVM_HOST_TRIPLE = "x86_64-w64-mingw32",
        .LLVM_NATIVE_ARCH = "X86",
        .LLVM_ON_WIN32 = 1,
        .LLVM_PREFIX = "/usr/local",
    };
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

pub fn appendFlags(flags: *std.ArrayList([]const u8), debug_symbols: bool, is_cpp: bool) !void {
    if (debug_symbols) try flags.append("-g1") else try flags.append("-g0");
    if (is_cpp) try flags.append("-std=c++14");
    try flags.appendSlice(&.{
        "-Wno-unused-command-line-argument",
        "-Wno-unused-variable",
        "-Wno-missing-exception-spec",
        "-Wno-macro-redefined",
        "-Wno-unknown-attributes",
        "-Wno-implicit-fallthrough",
        "-DLLVM_ON_WIN32",
        "-DNDEBUG", // disable debug
    });
}

fn appendLangScannedSources(
    b: *Build,
    step: *std.build.CompileStep,
    args: struct {
        debug_symbols: bool = false,
        flags: []const []const u8,
        rel_dirs: []const []const u8 = &.{},
        objc: bool = false,
        excluding: []const []const u8 = &.{},
        excluding_contains: []const []const u8 = &.{},
    },
) !void {
    var cpp_flags = std.ArrayList([]const u8).init(b.allocator);
    try cpp_flags.appendSlice(args.flags);
    try appendFlags(&cpp_flags, args.debug_symbols, true);
    const cpp_extensions: []const []const u8 = if (args.objc) &.{".mm"} else &.{ ".cpp", ".cc" };
    try appendScannedSources(b, step, .{
        .flags = cpp_flags.items,
        .rel_dirs = args.rel_dirs,
        .extensions = cpp_extensions,
        .excluding = args.excluding,
        .excluding_contains = args.excluding_contains,
    });

    var flags = std.ArrayList([]const u8).init(b.allocator);
    try flags.appendSlice(args.flags);
    try appendFlags(&flags, args.debug_symbols, false);
    const c_extensions: []const []const u8 = if (args.objc) &.{".m"} else &.{".c"};
    try appendScannedSources(b, step, .{
        .flags = flags.items,
        .rel_dirs = args.rel_dirs,
        .extensions = c_extensions,
        .excluding = args.excluding,
        .excluding_contains = args.excluding_contains,
    });
}

fn appendScannedSources(b: *Build, step: *std.build.CompileStep, args: struct {
    flags: []const []const u8,
    rel_dirs: []const []const u8 = &.{},
    extensions: []const []const u8,
    excluding: []const []const u8 = &.{},
    excluding_contains: []const []const u8 = &.{},
}) !void {
    var sources = std.ArrayList([]const u8).init(b.allocator);
    for (args.rel_dirs) |rel_dir| {
        try scanSources(b, &sources, rel_dir, args.extensions, args.excluding, args.excluding_contains);
    }
    step.addCSourceFiles(.{ .files = sources.items, .flags = args.flags });
}

/// Scans rel_dir for sources ending with one of the provided extensions, excluding relative paths
/// listed in the excluded list.
/// Results are appended to the dst ArrayList.
fn scanSources(
    b: *Build,
    dst: *std.ArrayList([]const u8),
    rel_dir: []const u8,
    extensions: []const []const u8,
    excluding: []const []const u8,
    excluding_contains: []const []const u8,
) !void {
    const abs_dir = try std.fs.path.join(b.allocator, &.{ sdkPath("/"), rel_dir });
    var dir = std.fs.openIterableDirAbsolute(abs_dir, .{}) catch |err| {
        std.log.err("mach: error: failed to open: {s}", .{abs_dir});
        return err;
    };
    defer dir.close();
    var dir_it = dir.iterate();
    while (try dir_it.next()) |entry| {
        if (entry.kind != .file) continue;
        var abs_path = try std.fs.path.join(b.allocator, &.{ abs_dir, entry.name });
        abs_path = try std.fs.realpathAlloc(b.allocator, abs_path);

        const allowed_extension = blk: {
            const ours = std.fs.path.extension(entry.name);
            for (extensions) |ext| {
                if (std.mem.eql(u8, ours, ext)) break :blk true;
            }
            break :blk false;
        };
        if (!allowed_extension) continue;

        const excluded = blk: {
            for (excluding) |excluded| {
                if (std.mem.eql(u8, entry.name, excluded)) break :blk true;
            }
            break :blk false;
        };
        if (excluded) continue;

        const excluded_contains = blk: {
            for (excluding_contains) |contains| {
                if (std.mem.containsAtLeast(u8, entry.name, 1, contains)) break :blk true;
            }
            break :blk false;
        };
        if (excluded_contains) continue;

        try dst.append(abs_path);
    }
}

fn sdkPath(comptime suffix: []const u8) []const u8 {
    if (suffix[0] != '/') @compileError("suffix must be an absolute path");
    return comptime blk: {
        const root_dir = std.fs.path.dirname(@src().file) orelse ".";
        break :blk root_dir ++ suffix;
    };
}
