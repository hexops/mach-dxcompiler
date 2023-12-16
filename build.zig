const std = @import("std");
const builtin = @import("builtin");
const Build = std.Build;

/// The latest binary release available at https://github.com/hexops/mach-dxcompiler/releases
const latest_binary_release = "2023.12.15+d9e236d.1";

const log = std.log.scoped(.mach_dxcompiler);
const prefix = "libs/DirectXShaderCompiler";

pub fn build(b: *Build) !void {
    const optimize = b.standardOptimizeOption(.{});
    const target = b.standardTargetOptions(.{});
    const from_source = b.option(bool, "from-source", "Build dxcompiler from source (large C++ codebase)") orelse false;

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

    /// When building from source, which optimize mode to build.
    /// When using a prebuilt binary, which optimize mode to download.
    optimize: std.builtin.OptimizeMode = .ReleaseFast,

    /// When building from source, whether to produce detailed debug symbols
    /// or not (g0 level). These can increase the binary size considerably
    debug_symbols: bool = false,

    /// Whether to build and install dxc.exe
    build_binary_tools: bool = false,

    /// When building from source, which repository and revision to clone.
    source_repository: []const u8 = "https://github.com/hexops/DirectXShaderCompiler",
    source_revision: []const u8 = "4190bb0c90d374c6b4d0b0f2c7b45b604eda24b6", // main branch
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

    const lib = b.addStaticLibrary(.{
        .name = "machdxcompiler",
        .root_source_file = b.addWriteFiles().add("empty.c", ""),
        .optimize = options.optimize,
        .target = step.target,
    });
    b.installArtifact(lib);
    if (options.install_libs) b.installArtifact(lib);
    lib.addCSourceFile(.{
        .file = .{ .path = "src/mach_dxc.cpp" },
        .flags = &.{
            "-fms-extensions", // __uuidof and friends (on non-windows targets)
        },
    });
    if (lib.target.getOsTag() != .windows) lib.defineCMacro("HAVE_DLFCN_H", "1");

    // The Windows 10 SDK winrt/wrl/client.h is incompatible with clang due to #pragma pack usages
    // (unclear why), so instead we use the wrl/client.h headers from https://github.com/ziglang/zig/tree/225fe6ddbfae016395762850e0cd5c51f9e7751c/lib/libc/include/any-windows-any
    // which seem to work fine.
    if (lib.target.getOsTag() == .windows and lib.target.getAbi() == .msvc) lib.addIncludePath(.{ .path = "msvc/" });

    // Microsoft does some shit.
    lib.disable_sanitize_c = true;
    lib.sanitize_thread = false; // sometimes in parallel, too.

    var cflags = std.ArrayList([]const u8).init(b.allocator);
    var cppflags = std.ArrayList([]const u8).init(b.allocator);
    if (!options.debug_symbols) {
        try cflags.append("-g0");
        try cppflags.append("-g0");
    }
    try cppflags.append("-std=c++17");
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

    addConfigHeaders(b, lib);
    addIncludes(lib);
    try appendLangScannedSources(b, lib, .{
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

            // lib/Transforms/Vectorize/CMakeLists.txt
            "BBVectorize.cpp",
            "LoopVectorize.cpp",
            "LPVectorizer.cpp",

            // lib/Support/CMakeLists.txt
            "DynamicLibrary.cpp",
            "PluginLoader.cpp",
        },
    });
    if (lib.target.getAbi() != .msvc) lib.defineCMacro("NDEBUG", ""); // disable assertions
    if (lib.target.getOsTag() == .windows) {
        lib.defineCMacro("LLVM_ON_WIN32", "1");
        if (lib.target.getAbi() == .msvc) lib.defineCMacro("CINDEX_LINKAGE", "");
        try appendLangScannedSources(b, lib, .{
            .cflags = cflags.items,
            .cppflags = cppflags.items,
            .rel_dirs = &.{prefix ++ "/lib/Support/Windows"},
            .excluding_contains = &.{".inc.cpp"},
        });
        lib.linkSystemLibrary("version");
    } else {
        lib.defineCMacro("LLVM_ON_UNIX", "1");
        try appendLangScannedSources(b, lib, .{
            .cflags = cflags.items,
            .cppflags = cppflags.items,
            .rel_dirs = &.{prefix ++ "/lib/Support/Unix"},
            .excluding_contains = &.{".inc.cpp"},
        });
    }

    if (options.install_libs) b.installArtifact(lib);

    linkMachDxcDependencies(lib);
    lib.addIncludePath(.{ .path = "src" });

    // TODO: investigate SSE2 #define / cmake option for CPU target
    //
    // TODO: investigate how projects/dxilconv/lib/DxbcConverter/DxbcConverterImpl.h is getting pulled
    // in, we can get rid of dxbc conversion presumably

    if (options.build_binary_tools) {
        const dxc_exe = b.addExecutable(.{
            .name = "dxc",
            .root_source_file = b.addWriteFiles().add("empty.c", ""),
            .optimize = options.optimize,
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
        dxc_exe.linkLibrary(lib);

        if (dxc_exe.target.getOsTag() == .windows) {
            // windows must be built with LTO disabled due to:
            // https://github.com/ziglang/zig/issues/15958
            dxc_exe.want_lto = false;
            if (builtin.os.tag == .windows and dxc_exe.target.getAbi() == .msvc) {
                const msvc_lib_dir: ?[]const u8 = try @import("msvc.zig").MsvcLibDir.find(b.allocator);

                // The MSVC lib dir looks like this:
                // C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.38.33130\Lib\x64
                // But we need the atlmfc lib dir:
                // C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.38.33130\atlmfc\lib\x64
                const msvc_dir = try std.fs.path.resolve(b.allocator, &.{ msvc_lib_dir.?, "..\\.." });

                const lib_dir_path = try std.mem.concat(b.allocator, u8, &.{
                    msvc_dir,
                    "\\atlmfc\\lib\\",
                    if (dxc_exe.target.getCpuArch() == .aarch64) "arm64" else "x64",
                });

                const lib_path = try std.mem.concat(b.allocator, u8, &.{ lib_dir_path, "\\atls.lib" });
                const pdb_name = if (dxc_exe.target.getCpuArch() == .aarch64)
                    "atls.arm64.pdb"
                else
                    "atls.amd64.pdb";
                const pdb_path = try std.mem.concat(b.allocator, u8, &.{ lib_dir_path, "\\", pdb_name });

                // For some reason, msvc target needs atls.lib to be in the 'zig build' working directory.
                // Addomg tp the library path like this has no effect:
                dxc_exe.addLibraryPath(.{ .path = lib_dir_path });
                // So instead we must copy the lib into this directory:
                try std.fs.cwd().copyFile(lib_path, std.fs.cwd(), "atls.lib", .{});
                try std.fs.cwd().copyFile(pdb_path, std.fs.cwd(), pdb_name, .{});
                // This is probably a bug in the Zig linker.
            }
        }
    }

    step.linkLibrary(lib);
    step.addIncludePath(.{ .path = "src" });
}

fn linkMachDxcDependencies(step: *std.build.Step.Compile) void {
    if (step.target.getAbi() == .msvc) {
        // https://github.com/ziglang/zig/issues/5312
        step.linkLibC();
    } else step.linkLibCpp();
    if (step.target.getOsTag() == .windows) {
        step.linkSystemLibrary("ole32");
        step.linkSystemLibrary("oleaut32");
    }
}

fn linkFromBinary(b: *Build, step: *std.build.CompileStep, options: Options) !void {
    // Add a build step to download binaries. This being a custom build step ensures it only
    // downloads if needed, and that and that e.g. if you are running a different
    // `zig build <step>` it doesn't always just download the binaries.
    var download_step = DownloadBinaryStep.init(b, step, options);
    step.step.dependOn(&download_step.step);

    const cache_dir = try binaryCacheDirPath(b, options, step);
    step.addLibraryPath(.{ .path = cache_dir });
    step.linkSystemLibrary("machdxcompiler");
    linkMachDxcDependencies(step);

    step.addIncludePath(.{ .path = "src" });
}

fn addConfigHeaders(b: *Build, step: *std.build.CompileStep) void {
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

fn addIncludes(step: *std.build.CompileStep) void {
    // TODO: replace unofficial external/DIA submodule with something else (or eliminate dep on it)
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
fn addConfigHeaderLLVMConfig(b: *Build, target: std.zig.CrossTarget, which: anytype) *std.Build.Step.ConfigHeader {
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
        .LLVM_VERSION_STRING = "3.7-v1.4.0.2274-1812-machdxcompiler",
    };

    const LLVMConfigH = struct {
        LLVM_HOST_TRIPLE: []const u8,
        LLVM_ON_WIN32: ?i64 = null,
        LLVM_ON_UNIX: ?i64 = null,
        HAVE_SYS_MMAN_H: ?i64 = null,
    };
    const llvm_config_h = blk: {
        if (target.getOsTag() == .windows) {
            break :blk switch (target.getAbi()) {
                .msvc => switch (target.getCpuArch()) {
                    .x86_64 => merge(cross_platform, LLVMConfigH{
                        .LLVM_HOST_TRIPLE = "x86_64-w64-msvc",
                        .LLVM_ON_WIN32 = 1,
                    }),
                    .aarch64 => merge(cross_platform, LLVMConfigH{
                        .LLVM_HOST_TRIPLE = "aarch64-w64-msvc",
                        .LLVM_ON_WIN32 = 1,
                    }),
                    else => @panic("target architecture not supported"),
                },
                .gnu => switch (target.getCpuArch()) {
                    .x86_64 => merge(cross_platform, LLVMConfigH{
                        .LLVM_HOST_TRIPLE = "x86_64-w64-mingw32",
                        .LLVM_ON_WIN32 = 1,
                    }),
                    .aarch64 => merge(cross_platform, LLVMConfigH{
                        .LLVM_HOST_TRIPLE = "aarch64-w64-mingw32",
                        .LLVM_ON_WIN32 = 1,
                    }),
                    else => @panic("target architecture not supported"),
                },
                else => @panic("target ABI not supported"),
            };
        } else if (target.getOsTag().isDarwin()) {
            break :blk switch (target.getCpuArch()) {
                .aarch64 => merge(cross_platform, LLVMConfigH{
                    .LLVM_HOST_TRIPLE = "aarch64-apple-darwin",
                    .LLVM_ON_UNIX = 1,
                    .HAVE_SYS_MMAN_H = 1,
                }),
                .x86_64 => merge(cross_platform, LLVMConfigH{
                    .LLVM_HOST_TRIPLE = "x86_64-apple-darwin",
                    .LLVM_ON_UNIX = 1,
                    .HAVE_SYS_MMAN_H = 1,
                }),
                else => @panic("target architecture not supported"),
            };
        } else {
            // Assume linux-like
            // TODO: musl support?
            break :blk switch (target.getCpuArch()) {
                .aarch64 => merge(cross_platform, LLVMConfigH{
                    .LLVM_HOST_TRIPLE = "aarch64-linux-gnu",
                    .LLVM_ON_UNIX = 1,
                    .HAVE_SYS_MMAN_H = 1,
                }),
                .x86_64 => merge(cross_platform, LLVMConfigH{
                    .LLVM_HOST_TRIPLE = "x86_64-linux-gnu",
                    .LLVM_ON_UNIX = 1,
                    .HAVE_SYS_MMAN_H = 1,
                }),
                else => @panic("target architecture not supported"),
            };
        }
    };

    const tag = target.getOsTag();
    const if_windows: ?i64 = if (tag == .windows) 1 else null;
    const if_not_windows: ?i64 = if (tag == .windows) null else 1;
    const if_windows_or_linux: ?i64 = if (tag == .windows and !tag.isDarwin()) 1 else null;
    const if_darwin: ?i64 = if (tag.isDarwin()) 1 else null;
    const if_not_msvc: ?i64 = if (target.getAbi() != .msvc) 1 else null;
    const config_h = merge(llvm_config_h, .{
        .HAVE_STRERROR = if_windows,
        .HAVE_STRERROR_R = if_not_windows,
        .HAVE_MALLOC_H = if_windows_or_linux,
        .HAVE_MALLOC_MALLOC_H = if_darwin,
        .HAVE_MALLOC_ZONE_STATISTICS = if_not_windows,
        .HAVE_GETPAGESIZE = if_not_windows,
        .HAVE_PTHREAD_H = if_not_windows,
        .HAVE_PTHREAD_GETSPECIFIC = if_not_windows,
        .HAVE_PTHREAD_MUTEX_LOCK = if_not_windows,
        .HAVE_PTHREAD_RWLOCK_INIT = if_not_windows,
        .HAVE_DLOPEN = if_not_windows,
        .HAVE_DLFCN_H = if_not_windows, //
        .HAVE_UNISTD_H = if_not_msvc,

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
    const result = try std.ChildProcess.run(.{ .allocator = allocator, .argv = &.{ "git", "rev-parse", "HEAD" }, .cwd = cwd });
    allocator.free(result.stderr);
    if (result.stdout.len > 0) return result.stdout[0 .. result.stdout.len - 1]; // trim newline
    return result.stdout;
}

fn ensureGit(allocator: std.mem.Allocator) void {
    const argv = &[_][]const u8{ "git", "--version" };
    const result = std.ChildProcess.run(.{
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
    var dir = std.fs.cwd().openDir(abs_dir, .{ .iterate = true }) catch |err| {
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
fn Merge(comptime a: type, comptime b: type) type {
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
fn merge(a: anytype, b: anytype) Merge(@TypeOf(a), @TypeOf(b)) {
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

// ------------------------------------------
// Binary download logic
// ------------------------------------------
const project_name = "dxcompiler";

var download_mutex = std.Thread.Mutex{};

fn binaryZigTriple(arena: std.mem.Allocator, step: *std.build.Step.Compile) ![]const u8 {
    // Craft a zig_triple string that we will use to create the binary download URL. Remove OS
    // version range / glibc version from triple, as we don't include that in our download URL.
    var binary_target = std.zig.CrossTarget.fromTarget(step.target_info.target);
    binary_target.os_version_min = .{ .none = undefined };
    binary_target.os_version_max = .{ .none = undefined };
    binary_target.glibc_version = null;
    return try binary_target.zigTriple(arena);
}

fn binaryOptimizeMode(options: Options) []const u8 {
    return switch (options.optimize) {
        .Debug => "Debug",
        // All Release* are mapped to ReleaseFast, as we only provide ReleaseFast and Debug binaries.
        .ReleaseSafe => "ReleaseFast",
        .ReleaseFast => "ReleaseFast",
        .ReleaseSmall => "ReleaseFast",
    };
}

fn binaryCacheDirPath(b: *std.build.Builder, options: Options, step: *std.build.Step.Compile) ![]const u8 {
    // Global Mach project cache directory, e.g. $HOME/.cache/zig/mach/<project_name>
    const project_cache_dir_rel = try b.global_cache_root.join(b.allocator, &.{ "mach", project_name });

    // Release-specific cache directory, e.g. $HOME/.cache/zig/mach/<project_name>/<latest_binary_release>/<zig_triple>/<optimize>
    // where we will download the binary release to.
    return try std.fs.path.join(b.allocator, &.{
        project_cache_dir_rel,
        latest_binary_release,
        try binaryZigTriple(b.allocator, step),
        binaryOptimizeMode(options),
    });
}

const DownloadBinaryStep = struct {
    target_step: *std.build.Step.Compile,
    options: Options,
    step: std.build.Step,
    b: *std.build.Builder,

    fn init(b: *std.build.Builder, target_step: *std.build.Step.Compile, options: Options) *DownloadBinaryStep {
        const download_step = b.allocator.create(DownloadBinaryStep) catch unreachable;
        download_step.* = .{
            .target_step = target_step,
            .options = options,
            .step = std.build.Step.init(.{
                .id = .custom,
                .name = "download",
                .owner = b,
                .makeFn = &make,
            }),
            .b = b,
        };
        return download_step;
    }

    fn make(step_ptr: *std.build.Step, prog_node: *std.Progress.Node) anyerror!void {
        _ = prog_node;
        const download_step = @fieldParentPtr(DownloadBinaryStep, "step", step_ptr);
        const b = download_step.b;
        const step = download_step.target_step;
        const options = download_step.options;

        // Zig will run build steps in parallel if possible, so if there were two invocations of
        // link() then this function would be called in parallel. We're manipulating the FS here
        // and so need to prevent that.
        download_mutex.lock();
        defer download_mutex.unlock();

        // Check if we've already downloaded binaries to the cache dir
        const cache_dir = try binaryCacheDirPath(b, options, step);
        if (dirExists(cache_dir)) {
            // Nothing to do.
            return;
        }
        std.fs.cwd().makePath(cache_dir) catch |err| {
            log.err("unable to create cache dir '{s}': {s}", .{ cache_dir, @errorName(err) });
            return error.DownloadFailed;
        };

        // Compose the download URL, e.g.
        // https://github.com/hexops/mach-dxcompiler/releases/download/2023.11.30%2Ba451866.3/aarch64-linux-gnu_Debug_bin.tar.gz
        const download_url = try std.mem.concat(b.allocator, u8, &.{
            "https://github.com",
            "/hexops/mach-" ++ project_name ++ "/releases/download/",
            latest_binary_release,
            "/",
            try binaryZigTriple(b.allocator, step),
            "_",
            binaryOptimizeMode(options),
            "_lib",
            ".tar.zst",
        });

        try downloadExtractTarball(
            b.allocator,
            "", // tmp_dir_root
            try std.fs.openDirAbsolute(cache_dir, .{}),
            download_url,
            ZstdWrapper,
        );
    }
};

// due to slight differences in the API of std.compress.(gzip|xz) and std.compress.zstd, zstd is
// wrapped for generic use in unpackTarballCompressed: see github.com/ziglang/zig/issues/14739
const ZstdWrapper = struct {
    fn DecompressType(comptime T: type) type {
        return error{}!std.compress.zstd.DecompressStream(T, .{});
    }

    fn decompress(allocator: std.mem.Allocator, reader: anytype) DecompressType(@TypeOf(reader)) {
        return std.compress.zstd.decompressStream(allocator, reader);
    }
};

fn downloadExtractTarball(
    arena: std.mem.Allocator,
    tmp_dir_root: []const u8,
    out_dir: std.fs.Dir,
    url: []const u8,
    comptime Compression: type,
) !void {
    log.info("downloading {s}..\n", .{url});
    const gpa = arena;

    // Create a tmp directory
    const rand_int = std.crypto.random.int(u64);
    const tmp_dir_sub_path = "tmp" ++ std.fs.path.sep_str ++ hex64(rand_int);
    const tmp_dir_path = try std.fs.path.join(arena, &.{ tmp_dir_root, tmp_dir_sub_path });
    var tmp_dir = blk: {
        const dir = std.fs.cwd().makeOpenPath(tmp_dir_path, .{ .iterate = true }) catch |err| {
            log.err("unable to create temporary directory '{s}': {s}", .{ tmp_dir_path, @errorName(err) });
            return error.FetchFailed;
        };
        break :blk dir;
    };
    defer tmp_dir.close();

    // Download the file into the tmp directory.
    const download_path = try std.fs.path.join(arena, &.{ tmp_dir_path, "download" });
    const download_file = try std.fs.cwd().createFile(download_path, .{});
    defer download_file.close();
    var client: std.http.Client = .{ .allocator = gpa };
    defer client.deinit();
    var fetch_res = try client.fetch(arena, .{
        .location = .{ .url = url },
        .response_strategy = .{ .file = download_file },
    });
    if (fetch_res.status.class() != .success) {
        log.err("unable to fetch: HTTP {}", .{fetch_res.status});
        fetch_res.deinit();
        return error.FetchFailed;
    }
    fetch_res.deinit();
    const downloaded_file = try std.fs.cwd().openFile(download_path, .{});
    defer downloaded_file.close();

    // Decompress tarball
    var br = std.io.bufferedReaderSize(std.crypto.tls.max_ciphertext_record_len, downloaded_file.reader());
    var decompress = Compression.decompress(gpa, br.reader()) catch |err| {
        log.err("unable to decompress downloaded tarball: {s}", .{@errorName(err)});
        return error.DecompressFailed;
    };
    defer decompress.deinit();

    // Unpack tarball
    var diagnostics: std.tar.Options.Diagnostics = .{ .allocator = gpa };
    defer diagnostics.deinit();
    std.tar.pipeToFileSystem(out_dir, decompress.reader(), .{
        .diagnostics = &diagnostics,
        .strip_components = 1,
        // TODO: we would like to set this to executable_bit_only, but two
        // things need to happen before that:
        // 1. the tar implementation needs to support it
        // 2. the hashing algorithm here needs to support detecting the is_executable
        //    bit on Windows from the ACLs (see the isExecutable function).
        .mode_mode = .ignore,
        .exclude_empty_directories = true,
    }) catch |err| {
        log.err("unable to unpack tarball: {s}", .{@errorName(err)});
        return error.UnpackFailed;
    };
    if (diagnostics.errors.items.len > 0) {
        const notes_len: u32 = @intCast(diagnostics.errors.items.len);
        log.err("unable to unpack tarball(2)", .{});
        for (diagnostics.errors.items, notes_len..) |item, note_i| {
            _ = note_i;

            switch (item) {
                .unable_to_create_sym_link => |info| {
                    log.err("unable to create symlink from '{s}' to '{s}': {s}", .{ info.file_name, info.link_name, @errorName(info.code) });
                },
                .unable_to_create_file => |info| {
                    log.err("unable to create file '{s}': {s}", .{ info.file_name, @errorName(info.code) });
                },
                .unsupported_file_type => |info| {
                    log.err("file '{s}' has unsupported type '{c}'", .{ info.file_name, @intFromEnum(info.file_type) });
                },
            }
        }
        return error.UnpackFailed;
    }
}

fn dirExists(path: []const u8) bool {
    var dir = std.fs.openDirAbsolute(path, .{}) catch return false;
    dir.close();
    return true;
}

const hex_charset = "0123456789abcdef";

fn hex64(x: u64) [16]u8 {
    var result: [16]u8 = undefined;
    var i: usize = 0;
    while (i < 8) : (i += 1) {
        const byte = @as(u8, @truncate(x >> @as(u6, @intCast(8 * i))));
        result[i * 2 + 0] = hex_charset[byte >> 4];
        result[i * 2 + 1] = hex_charset[byte & 15];
    }
    return result;
}

test hex64 {
    const s = "[" ++ hex64(0x12345678_abcdef00) ++ "]";
    try std.testing.expectEqualStrings("[00efcdab78563412]", s);
}
