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
    source_revision: []const u8 = "42a21aa811937b58d3e40836aa5f3f4ef9c890f1", // main branch
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
    machdxc.addCSourceFile(.{
        .file = .{ .path = "src/mach_dxc.cpp" },
        .flags = &.{
            "-fms-extensions", // __uuidof and friends (on non-windows targets)
        },
    });
    if (machdxc.target.getOsTag() != .windows) machdxc.defineCMacro("HAVE_DLFCN_H", "1");

    const debug_symbols = false; // TODO: build option
    var cflags = std.ArrayList([]const u8).init(b.allocator);
    var cppflags = std.ArrayList([]const u8).init(b.allocator);
    if (!debug_symbols) {
        try cflags.append("-g0");
        try cppflags.append("-g0");
    }
    try cppflags.append("-std=c++14");
    const base_flags = &.{
        "-Wno-unused-command-line-argument",
        "-Wno-unused-variable",
        "-Wno-missing-exception-spec",
        "-Wno-macro-redefined",
        "-Wno-unknown-attributes",
        "-Wno-implicit-fallthrough",
        "-fms-extensions", // __uuidof and friends (on non-windows targets)
    };
    try cflags.appendSlice(base_flags);
    try cppflags.appendSlice(base_flags);

    addConfigHeaders(b, machdxc);
    addIncludes(machdxc);
    try appendLangScannedSources(b, machdxc, .{
        .cflags = cflags.items,
        .cppflags = cppflags.items,
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
            prefix ++ "/tools/clang/lib/Format",
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
    machdxc.defineCMacro("NDEBUG", ""); // disable assertions
    if (machdxc.target.getOsTag() == .windows) {
        machdxc.defineCMacro("LLVM_ON_WIN32", "1");
        try appendLangScannedSources(b, machdxc, .{
            .cflags = cflags.items,
            .cppflags = cppflags.items,
            .rel_dirs = &.{prefix ++ "/lib/Support/Windows"},
            .excluding_contains = &.{".inc.cpp"},
        });
        machdxc.linkSystemLibrary("ole32");
        machdxc.linkSystemLibrary("oleaut32");
        machdxc.linkSystemLibrary("version");
    } else {
        machdxc.defineCMacro("LLVM_ON_UNIX", "1");
        try appendLangScannedSources(b, machdxc, .{
            .cflags = cflags.items,
            .cppflags = cppflags.items,
            .rel_dirs = &.{prefix ++ "/lib/Support/Unix"},
            .excluding_contains = &.{".inc.cpp"},
        });
    }

    if (options.install_libs) b.installArtifact(machdxc);

    machdxc.linkLibCpp();
    machdxc.addIncludePath(.{ .path = "src" });

    // TODO: investigate SSE2 #define / cmake option for CPU target
    //
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
        dxc_exe.defineCMacro("NDEBUG", ""); // disable assertions
        if (dxc_exe.target.getOsTag() != .windows) dxc_exe.defineCMacro("HAVE_DLFCN_H", "1");
        dxc_exe.addIncludePath(.{ .path = prefix ++ "/tools/clang/tools" });
        dxc_exe.addIncludePath(.{ .path = prefix ++ "/include" });
        addConfigHeaders(b, dxc_exe);
        addIncludes(dxc_exe);
        try appendLangScannedSources(b, dxc_exe, .{
            .cflags = cflags.items,
            .cppflags = cppflags.items,
            .rel_dirs = &.{prefix ++ "/tools/clang/tools/dxclib"},
            .excluding_contains = &.{},
        });
        b.installArtifact(dxc_exe);
        dxc_exe.linkLibrary(machdxc);
    }

    step.linkLibrary(machdxc);
    step.addIncludePath(.{ .path = "src" });
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

    step.addConfigHeader(addConfigHeaderLLVMConfig(b, step.target, .llvm_config_h));
    step.addConfigHeader(addConfigHeaderLLVMConfig(b, step.target, .config_h));

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
    step.addIncludePath(.{ .path = prefix ++ "/include/dxc" });
    step.addIncludePath(.{ .path = prefix ++ "/external/DirectX-Headers/include/directx" });
    if (step.target.getOsTag() != .windows) step.addIncludePath(.{ .path = prefix ++ "/external/DirectX-Headers/include/wsl/stubs" });
}

// /include/llvm/Config/llvm-config.h.cmake
// /include/llvm/Config/config.h.cmake (derives llvm-config.h.cmake)
pub fn addConfigHeaderLLVMConfig(b: *Build, target: std.zig.CrossTarget, which: anytype) *std.Build.Step.ConfigHeader {
    // Note: LLVM_HOST_TRIPLEs can be found by running $ llc --version | grep Default
    // Note: arm64 is an alias for aarch64, we always use aarch64 over arm64.
    const cross_platform = .{
        .LLVM_PREFIX = "/usr/local",
        .LLVM_DEFAULT_TARGET_TRIPLE = "dxil-ms-dx",
        .LLVM_ENABLE_THREADS = 1,
        .LLVM_HAS_ATOMICS = 1,
        .LLVM_VERSION_MAJOR = 3,
        .LLVM_VERSION_MINOR = 7,
        .LLVM_VERSION_PATCH = 0,
        .LLVM_VERSION_STRING = "3.7-v1.4.0.2274-1812-machdxc",
    };

    const LLVMConfigH = struct {
        LLVM_HOST_TRIPLE: []const u8,
        LLVM_ON_WIN32: ?i64 = null,
        LLVM_ON_UNIX: ?i64 = null,
        HAVE_SYS_MMAN_H: ?i64 = null,
    };
    const llvm_config_h = blk: {
        if (target.getOsTag() == .windows) {
            if (target.getAbi() == .msvc) @panic("TODO: support *-windows-msvc targets");
            break :blk switch (target.getCpuArch()) {
                .x86_64 => merge(cross_platform, LLVMConfigH{
                    .LLVM_HOST_TRIPLE = "x86_64-w64-mingw32",
                    .LLVM_ON_WIN32 = 1,
                }),
                .aarch64 => @panic("TODO: support aarch64-windows-gnu targets"),
                else => @panic("target architecture not supported"),
            };
        } else if (target.getOsTag().isDarwin()) {
            break :blk switch (target.getCpuArch()) {
                .aarch64 => merge(cross_platform, LLVMConfigH{
                    .LLVM_HOST_TRIPLE = "aarch64-apple-darwin",
                    .LLVM_ON_UNIX = 1,
                    .HAVE_SYS_MMAN_H = 1,
                }),
                .x86_64 => @panic("TODO: support Intel macOS"),
                else => @panic("target architecture not supported"),
            };
        } else {
            // Assume linux-like
            break :blk switch (target.getCpuArch()) {
                .aarch64 => @panic("TODO: support aarch64-linux targets"),
                .x86_64 => @panic("TODO: support x86_64-linux targets"),
                else => @panic("target architecture not supported"),
            };
        }
    };

    const if_windows: ?i64 = if (target.getOsTag() == .windows) 1 else null;
    const if_not_windows: ?i64 = if (target.getOsTag() == .windows) null else 1;
    const config_h = merge(llvm_config_h, .{
        .HAVE_STRERROR = if_windows,
        .HAVE_STRERROR_R = if_not_windows,
        .HAVE_MALLOC_H = if_windows,
        .HAVE_MALLOC_MALLOC_H = if_not_windows,
        .HAVE_MALLOC_ZONE_STATISTICS = if_not_windows,
        .HAVE_GETPAGESIZE = if_not_windows,
        .HAVE_PTHREAD_H = if_not_windows,
        .HAVE_PTHREAD_GETSPECIFIC = if_not_windows,
        .HAVE_PTHREAD_MUTEX_LOCK = if_not_windows,
        .HAVE_PTHREAD_RWLOCK_INIT = if_not_windows,
        .HAVE_DLOPEN = if_not_windows,
        .HAVE_DLFCN_H = if_not_windows, //

        .BUG_REPORT_URL = "http://llvm.org/bugs/",
        .ENABLE_BACKTRACES = "",
        .ENABLE_CRASH_OVERRIDES = "",
        .DISABLE_LLVM_DYLIB_ATEXIT = "",
        .ENABLE_PIC = "",
        .ENABLE_TIMESTAMPS = 1,
        .HAVE_CLOSEDIR = 1,
        .HAVE_CXXABI_H = 1,
        .HAVE_DECL_STRERROR_S = 1,
        .HAVE_DIRENT_H = 1,
        .HAVE_ERRNO_H = 1,
        .HAVE_FCNTL_H = 1,
        .HAVE_FENV_H = 1,
        .HAVE_GETCWD = 1,
        .HAVE_GETTIMEOFDAY = 1,
        .HAVE_INT64_T = 1,
        .HAVE_INTTYPES_H = 1,
        .HAVE_ISATTY = 1,
        .HAVE_LIBPSAPI = 1,
        .HAVE_LIBSHELL32 = 1,
        .HAVE_LIMITS_H = 1,
        .HAVE_LINK_EXPORT_DYNAMIC = 1,
        .HAVE_MKSTEMP = 1,
        .HAVE_MKTEMP = 1,
        .HAVE_OPENDIR = 1,
        .HAVE_READDIR = 1,
        .HAVE_SIGNAL_H = 1,
        .HAVE_STDINT_H = 1,
        .HAVE_STRTOLL = 1,
        .HAVE_SYS_PARAM_H = 1,
        .HAVE_SYS_STAT_H = 1,
        .HAVE_SYS_TIME_H = 1,
        .HAVE_UINT64_T = 1,
        .HAVE_UNISTD_H = 1,
        .HAVE_UTIME_H = 1,
        .HAVE__ALLOCA = 1,
        .HAVE___ASHLDI3 = 1,
        .HAVE___ASHRDI3 = 1,
        .HAVE___CMPDI2 = 1,
        .HAVE___DIVDI3 = 1,
        .HAVE___FIXDFDI = 1,
        .HAVE___FIXSFDI = 1,
        .HAVE___FLOATDIDF = 1,
        .HAVE___LSHRDI3 = 1,
        .HAVE___MAIN = 1,
        .HAVE___MODDI3 = 1,
        .HAVE___UDIVDI3 = 1,
        .HAVE___UMODDI3 = 1,
        .HAVE____CHKSTK_MS = 1,
        .LLVM_ENABLE_ZLIB = 0,
        .PACKAGE_BUGREPORT = "http://llvm.org/bugs/",
        .PACKAGE_NAME = "LLVM",
        .PACKAGE_STRING = "LLVM 3.7-v1.4.0.2274-1812-g84da60c6c-dirty",
        .PACKAGE_VERSION = "3.7-v1.4.0.2274-1812-g84da60c6c-dirty",
        .RETSIGTYPE = "void",
        .WIN32_ELMCB_PCSTR = "PCSTR",
        .HAVE__CHSIZE_S = 1,
    });

    return switch (which) {
        .llvm_config_h => b.addConfigHeader(.{
            .style = .{ .cmake = .{ .path = prefix ++ "/include/llvm/Config/llvm-config.h.cmake" } },
            .include_path = "llvm/Config/llvm-config.h",
        }, llvm_config_h),
        .config_h => b.addConfigHeader(.{
            .style = .{ .cmake = .{ .path = prefix ++ "/include/llvm/Config/config.h.cmake" } },
            .include_path = "llvm/Config/config.h",
        }, config_h),
        else => unreachable,
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

fn appendLangScannedSources(
    b: *Build,
    step: *std.build.CompileStep,
    args: struct {
        cflags: []const []const u8,
        cppflags: []const []const u8,
        rel_dirs: []const []const u8 = &.{},
        objc: bool = false,
        excluding: []const []const u8 = &.{},
        excluding_contains: []const []const u8 = &.{},
    },
) !void {
    var cpp_flags = std.ArrayList([]const u8).init(b.allocator);
    try cpp_flags.appendSlice(args.cppflags);
    const cpp_extensions: []const []const u8 = if (args.objc) &.{".mm"} else &.{ ".cpp", ".cc" };
    try appendScannedSources(b, step, .{
        .flags = cpp_flags.items,
        .rel_dirs = args.rel_dirs,
        .extensions = cpp_extensions,
        .excluding = args.excluding,
        .excluding_contains = args.excluding_contains,
    });

    var flags = std.ArrayList([]const u8).init(b.allocator);
    try flags.appendSlice(args.cflags);
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

// Merge struct types A and B
pub fn Merge(comptime a: type, comptime b: type) type {
    const a_fields = @typeInfo(a).Struct.fields;
    const b_fields = @typeInfo(b).Struct.fields;

    return @Type(std.builtin.Type{
        .Struct = .{
            .layout = .Auto,
            .fields = a_fields ++ b_fields,
            .decls = &.{},
            .is_tuple = false,
        },
    });
}

// Merge struct values A and B
pub fn merge(a: anytype, b: anytype) Merge(@TypeOf(a), @TypeOf(b)) {
    var merged: Merge(@TypeOf(a), @TypeOf(b)) = undefined;
    inline for (@typeInfo(@TypeOf(merged)).Struct.fields) |f| {
        if (@hasField(@TypeOf(a), f.name)) @field(merged, f.name) = @field(a, f.name);
        if (@hasField(@TypeOf(b), f.name)) @field(merged, f.name) = @field(b, f.name);
    }
    return merged;
}

fn sdkPath(comptime suffix: []const u8) []const u8 {
    if (suffix[0] != '/') @compileError("suffix must be an absolute path");
    return comptime blk: {
        const root_dir = std.fs.path.dirname(@src().file) orelse ".";
        break :blk root_dir ++ suffix;
    };
}
