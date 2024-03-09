const std = @import("std");
const builtin = @import("builtin");
const Build = std.Build;

/// The latest binary release available at https://github.com/hexops/mach-dxcompiler/releases
const latest_binary_release = "2024.03.09+d19dd6d.1";

/// When building from source, which repository and revision to clone.
const source_repository = "https://github.com/hexops/DirectXShaderCompiler";
const source_revision = "4190bb0c90d374c6b4d0b0f2c7b45b604eda24b6"; // main branch

const log = std.log.scoped(.mach_dxcompiler);
const prefix = "libs/DirectXShaderCompiler";

pub fn build(b: *Build) !void {
    const optimize = b.standardOptimizeOption(.{});
    const target = b.standardTargetOptions(.{});
    const from_source = b.option(bool, "from_source", "Build dxcompiler from source (large C++ codebase)") orelse false;
    const debug_symbols = b.option(bool, "debug_symbols", "Whether to produce detailed debug symbols (g0) or not. These increase binary size considerably.") orelse false;

    const machdxcompiler: struct { lib: *std.Build.Step.Compile, lib_path: ?[]const u8 } = blk: {
        if (!from_source) {
            // We can't express that an std.Build.Module should depend on our DownloadBinaryStep.
            // But we can express that an std.Build.Module should link a library, which depends on
            // our DownloadBinaryStep.
            const linkage = b.addStaticLibrary(.{
                .name = "machdxcompiler-linkage",
                .root_source_file = b.addWriteFiles().add("empty.zig", ""),
                .optimize = optimize,
                .target = target,
            });
            var download_step = DownloadBinaryStep.init(b, target.result, optimize);
            linkage.step.dependOn(&download_step.step);

            const cache_dir = binaryCacheDirPath(b, target.result, optimize) catch |err| std.debug.panic("unable to construct binary cache dir path: {}", .{err});
            linkage.addLibraryPath(.{ .path = cache_dir });
            linkage.linkSystemLibrary("machdxcompiler");
            linkMachDxcDependenciesModule(&linkage.root_module);
            break :blk .{ .lib = linkage, .lib_path = cache_dir };
        } else {
            const lib = b.addStaticLibrary(.{
                .name = "machdxcompiler",
                .root_source_file = b.addWriteFiles().add("empty.zig", ""),
                .optimize = optimize,
                .target = target,
            });
            b.installArtifact(lib);
            // Microsoft does some shit.
            lib.root_module.sanitize_c = false;
            lib.root_module.sanitize_thread = false; // sometimes in parallel, too.

            var download_step = DownloadSourceStep.init(b);
            lib.step.dependOn(&download_step.step);

            lib.addCSourceFile(.{
                .file = .{ .path = "src/mach_dxc.cpp" },
                .flags = &.{
                    "-fms-extensions", // __uuidof and friends (on non-windows targets)
                },
            });
            if (target.result.os.tag != .windows) lib.defineCMacro("HAVE_DLFCN_H", "1");

            // The Windows 10 SDK winrt/wrl/client.h is incompatible with clang due to #pragma pack usages
            // (unclear why), so instead we use the wrl/client.h headers from https://github.com/ziglang/zig/tree/225fe6ddbfae016395762850e0cd5c51f9e7751c/lib/libc/include/any-windows-any
            // which seem to work fine.
            if (target.result.os.tag == .windows and target.result.abi == .msvc) lib.addIncludePath(.{ .path = "msvc/" });

            var cflags = std.ArrayList([]const u8).init(b.allocator);
            var cppflags = std.ArrayList([]const u8).init(b.allocator);
            if (!debug_symbols) {
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

            const cpp_sources =
                tools_clang_lib_lex_sources ++
                tools_clang_lib_basic_sources ++
                tools_clang_lib_driver_sources ++
                tools_clang_lib_analysis_sources ++
                tools_clang_lib_index_sources ++
                tools_clang_lib_parse_sources ++
                tools_clang_lib_ast_sources ++
                tools_clang_lib_edit_sources ++
                tools_clang_lib_sema_sources ++
                tools_clang_lib_codegen_sources ++
                tools_clang_lib_astmatchers_sources ++
                tools_clang_lib_tooling_core_sources ++
                tools_clang_lib_tooling_sources ++
                tools_clang_lib_format_sources ++
                tools_clang_lib_rewrite_sources ++
                tools_clang_lib_frontend_sources ++
                tools_clang_tools_libclang_sources ++
                tools_clang_tools_dxcompiler_sources ++
                lib_bitcode_reader_sources ++
                lib_bitcode_writer_sources ++
                lib_ir_sources ++
                lib_irreader_sources ++
                lib_linker_sources ++
                lib_asmparser_sources ++
                lib_analysis_sources ++
                lib_mssupport_sources ++
                lib_transforms_utils_sources ++
                lib_transforms_instcombine_sources ++
                lib_transforms_ipo_sources ++
                lib_transforms_scalar_sources ++
                lib_transforms_vectorize_sources ++
                lib_target_sources ++
                lib_profiledata_sources ++
                lib_option_sources ++
                lib_passprinters_sources ++
                lib_passes_sources ++
                lib_hlsl_sources ++
                lib_support_cpp_sources ++
                lib_dxcsupport_sources ++
                lib_dxcbindingtable_sources ++
                lib_dxil_sources ++
                lib_dxilcontainer_sources ++
                lib_dxilpixpasses_sources ++
                lib_dxilcompression_cpp_sources ++
                lib_dxilrootsignature_sources;

            const c_sources =
                lib_support_c_sources ++
                lib_dxilcompression_c_sources;

            lib.addCSourceFiles(.{
                .files = &cpp_sources,
                .flags = cppflags.items,
            });
            lib.addCSourceFiles(.{
                .files = &c_sources,
                .flags = cflags.items,
            });

            if (target.result.abi != .msvc) lib.defineCMacro("NDEBUG", ""); // disable assertions
            if (target.result.os.tag == .windows) {
                lib.defineCMacro("LLVM_ON_WIN32", "1");
                if (target.result.abi == .msvc) lib.defineCMacro("CINDEX_LINKAGE", "");
                lib.linkSystemLibrary("version");
            } else {
                lib.defineCMacro("LLVM_ON_UNIX", "1");
            }

            linkMachDxcDependencies(lib);
            lib.addIncludePath(.{ .path = "src" });

            // TODO: investigate SSE2 #define / cmake option for CPU target
            //
            // TODO: investigate how projects/dxilconv/lib/DxbcConverter/DxbcConverterImpl.h is getting pulled
            // in, we can get rid of dxbc conversion presumably

            // dxc.exe builds
            const dxc_exe = b.addExecutable(.{
                .name = "dxc",
                .optimize = optimize,
                .target = target,
            });
            const install_dxc_step = b.step("dxc", "Build and install dxc.exe");
            install_dxc_step.dependOn(&b.addInstallArtifact(dxc_exe, .{}).step);
            dxc_exe.addCSourceFile(.{
                .file = .{ .path = prefix ++ "/tools/clang/tools/dxc/dxcmain.cpp" },
                .flags = &.{"-std=c++17"},
            });
            dxc_exe.defineCMacro("NDEBUG", ""); // disable assertions

            if (target.result.os.tag != .windows) dxc_exe.defineCMacro("HAVE_DLFCN_H", "1");
            dxc_exe.addIncludePath(.{ .path = prefix ++ "/tools/clang/tools" });
            dxc_exe.addIncludePath(.{ .path = prefix ++ "/include" });
            addConfigHeaders(b, dxc_exe);
            addIncludes(dxc_exe);
            dxc_exe.addCSourceFile(.{
                .file = .{ .path = prefix ++ "/tools/clang/tools/dxclib/dxc.cpp" },
                .flags = cppflags.items,
            });
            b.installArtifact(dxc_exe);
            dxc_exe.linkLibrary(lib);

            if (target.result.os.tag == .windows) {
                // windows must be built with LTO disabled due to:
                // https://github.com/ziglang/zig/issues/15958
                dxc_exe.want_lto = false;
                if (builtin.os.tag == .windows and target.result.abi == .msvc) {
                    const msvc_lib_dir: ?[]const u8 = try @import("msvc.zig").MsvcLibDir.find(b.allocator);

                    // The MSVC lib dir looks like this:
                    // C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.38.33130\Lib\x64
                    // But we need the atlmfc lib dir:
                    // C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.38.33130\atlmfc\lib\x64
                    const msvc_dir = try std.fs.path.resolve(b.allocator, &.{ msvc_lib_dir.?, "..\\.." });

                    const lib_dir_path = try std.mem.concat(b.allocator, u8, &.{
                        msvc_dir,
                        "\\atlmfc\\lib\\",
                        if (target.result.cpu.arch == .aarch64) "arm64" else "x64",
                    });

                    const lib_path = try std.mem.concat(b.allocator, u8, &.{ lib_dir_path, "\\atls.lib" });
                    const pdb_name = if (target.result.cpu.arch == .aarch64)
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

            break :blk .{ .lib = lib, .lib_path = null };
        }
    };

    // Zig bindings
    const mach_dxcompiler = b.addModule("mach-dxcompiler", .{
        .root_source_file = .{ .path = "src/main.zig" },
        .target = target,
        .optimize = optimize,
    });
    mach_dxcompiler.addIncludePath(.{ .path = "src" });

    mach_dxcompiler.linkLibrary(machdxcompiler.lib);
    if (machdxcompiler.lib_path) |p| mach_dxcompiler.addLibraryPath(.{ .path = p });

    const main_tests = b.addTest(.{
        .name = "dxcompiler-tests",
        .root_source_file = .{ .path = "src/main.zig" },
        .target = target,
        .optimize = optimize,
    });
    main_tests.addIncludePath(.{ .path = "src" });
    main_tests.linkLibrary(machdxcompiler.lib);
    if (machdxcompiler.lib_path) |p| main_tests.addLibraryPath(.{ .path = p });

    b.installArtifact(main_tests);
    const test_step = b.step("test", "Run library tests");
    test_step.dependOn(&b.addRunArtifact(main_tests).step);
}

fn linkMachDxcDependencies(step: *std.Build.Step.Compile) void {
    const target = step.rootModuleTarget();
    if (target.abi == .msvc) {
        // https://github.com/ziglang/zig/issues/5312
        step.linkLibC();
    } else step.linkLibCpp();
    if (target.os.tag == .windows) {
        step.linkSystemLibrary("ole32");
        step.linkSystemLibrary("oleaut32");
    }
}

fn linkMachDxcDependenciesModule(mod: *std.Build.Module) void {
    const target = mod.resolved_target.?.result;
    if (target.abi == .msvc) {
        // https://github.com/ziglang/zig/issues/5312
        mod.link_libc = true;
    } else {
        mod.link_libcpp = true;
    }
    if (target.os.tag == .windows) {
        mod.linkSystemLibrary("ole32", .{});
        mod.linkSystemLibrary("oleaut32", .{});
    }
}

fn addConfigHeaders(b: *Build, step: *std.Build.Step.Compile) void {
    // /tools/clang/include/clang/Config/config.h.cmake
    step.addConfigHeader(b.addConfigHeader(
        .{
            .style = .{ .cmake = .{ .path = "config-headers/tools/clang/include/clang/Config/config.h.cmake" } },
            .include_path = "clang/Config/config.h",
        },
        .{},
    ));

    // /include/llvm/Config/AsmParsers.def.in
    step.addConfigHeader(b.addConfigHeader(
        .{
            .style = .{ .cmake = .{ .path = "config-headers/include/llvm/Config/AsmParsers.def.in" } },
            .include_path = "llvm/Config/AsmParsers.def",
        },
        .{},
    ));

    // /include/llvm/Config/Disassemblers.def.in
    step.addConfigHeader(b.addConfigHeader(
        .{
            .style = .{ .cmake = .{ .path = "config-headers/include/llvm/Config/Disassemblers.def.in" } },
            .include_path = "llvm/Config/Disassemblers.def",
        },
        .{},
    ));

    // /include/llvm/Config/Targets.def.in
    step.addConfigHeader(b.addConfigHeader(
        .{
            .style = .{ .cmake = .{ .path = "config-headers/include/llvm/Config/Targets.def.in" } },
            .include_path = "llvm/Config/Targets.def",
        },
        .{},
    ));

    // /include/llvm/Config/AsmPrinters.def.in
    step.addConfigHeader(b.addConfigHeader(
        .{
            .style = .{ .cmake = .{ .path = "config-headers/include/llvm/Config/AsmPrinters.def.in" } },
            .include_path = "llvm/Config/AsmPrinters.def",
        },
        .{},
    ));

    // /include/llvm/Support/DataTypes.h.cmake
    step.addConfigHeader(b.addConfigHeader(
        .{
            .style = .{ .cmake = .{ .path = "config-headers/include/llvm/Support/DataTypes.h.cmake" } },
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
            .style = .{ .cmake = .{ .path = "config-headers/include/llvm/Config/abi-breaking.h.cmake" } },
            .include_path = "llvm/Config/abi-breaking.h",
        },
        .{},
    ));

    const target = step.rootModuleTarget();
    step.addConfigHeader(addConfigHeaderLLVMConfig(b, target, .llvm_config_h));
    step.addConfigHeader(addConfigHeaderLLVMConfig(b, target, .config_h));

    // /include/dxc/config.h.cmake
    step.addConfigHeader(b.addConfigHeader(
        .{
            .style = .{ .cmake = .{ .path = "config-headers/include/dxc/config.h.cmake" } },
            .include_path = "dxc/config.h",
        },
        .{
            .DXC_DISABLE_ALLOCATOR_OVERRIDES = false,
        },
    ));
}

fn addIncludes(step: *std.Build.Step.Compile) void {
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
    const target = step.rootModuleTarget();
    if (target.os.tag != .windows) step.addIncludePath(.{ .path = prefix ++ "/external/DirectX-Headers/include/wsl/stubs" });
}

// /include/llvm/Config/llvm-config.h.cmake
// /include/llvm/Config/config.h.cmake (derives llvm-config.h.cmake)
fn addConfigHeaderLLVMConfig(b: *Build, target: std.Target, which: anytype) *std.Build.Step.ConfigHeader {
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
        if (target.os.tag == .windows) {
            break :blk switch (target.abi) {
                .msvc => switch (target.cpu.arch) {
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
                .gnu => switch (target.cpu.arch) {
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
        } else if (target.os.tag.isDarwin()) {
            break :blk switch (target.cpu.arch) {
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
            break :blk switch (target.cpu.arch) {
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

    const tag = target.os.tag;
    const if_windows: ?i64 = if (tag == .windows) 1 else null;
    const if_not_windows: ?i64 = if (tag == .windows) null else 1;
    const if_windows_or_linux: ?i64 = if (tag == .windows and !tag.isDarwin()) 1 else null;
    const if_darwin: ?i64 = if (tag.isDarwin()) 1 else null;
    const if_not_msvc: ?i64 = if (target.abi != .msvc) 1 else null;
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
            .style = .{ .cmake = .{ .path = "config-headers/include/llvm/Config/llvm-config.h.cmake" } },
            .include_path = "llvm/Config/llvm-config.h",
        }, llvm_config_h),
        .config_h => b.addConfigHeader(.{
            .style = .{ .cmake = .{ .path = "config-headers/include/llvm/Config/config.h.cmake" } },
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

const DownloadSourceStep = struct {
    step: std.Build.Step,
    b: *std.Build,

    fn init(b: *std.Build) *DownloadSourceStep {
        const download_step = b.allocator.create(DownloadSourceStep) catch unreachable;
        download_step.* = .{
            .step = std.Build.Step.init(.{
                .id = .custom,
                .name = "download",
                .owner = b,
                .makeFn = &make,
            }),
            .b = b,
        };
        return download_step;
    }

    fn make(step_ptr: *std.Build.Step, prog_node: *std.Progress.Node) anyerror!void {
        _ = prog_node;
        const download_step = @fieldParentPtr(DownloadSourceStep, "step", step_ptr);
        const b = download_step.b;

        // Zig will run build steps in parallel if possible, so if there were two invocations of
        // then this function would be called in parallel. We're manipulating the FS here
        // and so need to prevent that.
        download_mutex.lock();
        defer download_mutex.unlock();

        try ensureGitRepoCloned(b.allocator, source_repository, source_revision, sdkPath("/libs/DirectXShaderCompiler"));
    }
};

// ------------------------------------------
// Binary download logic
// ------------------------------------------
const project_name = "dxcompiler";

var download_mutex = std.Thread.Mutex{};

fn binaryZigTriple(arena: std.mem.Allocator, target: std.Target) ![]const u8 {
    // Craft a zig_triple string that we will use to create the binary download URL. Remove OS
    // version range / glibc version from triple, as we don't include that in our download URL.
    var binary_target = std.zig.CrossTarget.fromTarget(target);
    binary_target.os_version_min = .{ .none = undefined };
    binary_target.os_version_max = .{ .none = undefined };
    binary_target.glibc_version = null;
    return try binary_target.zigTriple(arena);
}

fn binaryOptimizeMode(optimize: std.builtin.OptimizeMode) []const u8 {
    return switch (optimize) {
        .Debug => "Debug",
        // All Release* are mapped to ReleaseFast, as we only provide ReleaseFast and Debug binaries.
        .ReleaseSafe => "ReleaseFast",
        .ReleaseFast => "ReleaseFast",
        .ReleaseSmall => "ReleaseFast",
    };
}

fn binaryCacheDirPath(b: *std.Build, target: std.Target, optimize: std.builtin.OptimizeMode) ![]const u8 {
    // Global Mach project cache directory, e.g. $HOME/.cache/zig/mach/<project_name>
    // TODO: remove this once https://github.com/ziglang/zig/issues/16149 is fixed.
    const global_cache_root = if (@hasField(std.Build, "graph")) b.graph.global_cache_root else b.global_cache_root;
    const project_cache_dir_rel = try global_cache_root.join(b.allocator, &.{ "mach", project_name });

    // Release-specific cache directory, e.g. $HOME/.cache/zig/mach/<project_name>/<latest_binary_release>/<zig_triple>/<optimize>
    // where we will download the binary release to.
    return try std.fs.path.join(b.allocator, &.{
        project_cache_dir_rel,
        latest_binary_release,
        try binaryZigTriple(b.allocator, target),
        binaryOptimizeMode(optimize),
    });
}

const DownloadBinaryStep = struct {
    target: std.Target,
    optimize: std.builtin.OptimizeMode,
    step: std.Build.Step,
    b: *std.Build,

    fn init(b: *std.Build, target: std.Target, optimize: std.builtin.OptimizeMode) *DownloadBinaryStep {
        const download_step = b.allocator.create(DownloadBinaryStep) catch unreachable;
        download_step.* = .{
            .target = target,
            .optimize = optimize,
            .step = std.Build.Step.init(.{
                .id = .custom,
                .name = "download",
                .owner = b,
                .makeFn = &make,
            }),
            .b = b,
        };
        return download_step;
    }

    fn make(step_ptr: *std.Build.Step, prog_node: *std.Progress.Node) anyerror!void {
        _ = prog_node;
        const download_step = @fieldParentPtr(DownloadBinaryStep, "step", step_ptr);
        const b = download_step.b;
        const target = download_step.target;
        const optimize = download_step.optimize;

        // Zig will run build steps in parallel if possible, so if there were two invocations of
        // then this function would be called in parallel. We're manipulating the FS here
        // and so need to prevent that.
        download_mutex.lock();
        defer download_mutex.unlock();

        // Check if we've already downloaded binaries to the cache dir
        const cache_dir = try binaryCacheDirPath(b, target, optimize);
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
            try binaryZigTriple(b.allocator, target),
            "_",
            binaryOptimizeMode(optimize),
            "_lib",
            ".tar.zst",
        });

        try downloadExtractTarball(
            b.allocator,
            cache_dir,
            try std.fs.openDirAbsolute(cache_dir, .{}),
            download_url,
        );
    }
};

fn downloadExtractTarball(
    arena: std.mem.Allocator,
    out_dir_path: []const u8,
    out_dir: std.fs.Dir,
    url: []const u8,
) !void {
    log.info("downloading {s}\n", .{url});
    const gpa = arena;

    // Fetch the file into memory.
    var resp = std.ArrayList(u8).init(arena);
    defer resp.deinit();
    var client: std.http.Client = .{ .allocator = gpa };
    defer client.deinit();
    var fetch_res = client.fetch(.{
        .location = .{ .url = url },
        .response_storage = .{ .dynamic = &resp },
        .max_append_size = 50 * 1024 * 1024,
    }) catch |err| {
        log.err("unable to fetch: error: {s}", .{@errorName(err)});
        return error.FetchFailed;
    };
    if (fetch_res.status.class() != .success) {
        log.err("unable to fetch: HTTP {}", .{fetch_res.status});
        return error.FetchFailed;
    }
    log.info("extracting {} bytes to {s}\n", .{ resp.items.len, out_dir_path });

    // Decompress tarball
    const window_buffer = try gpa.alloc(u8, 1 << 23);
    defer gpa.free(window_buffer);

    var fbs = std.io.fixedBufferStream(resp.items);
    var decompressor = std.compress.zstd.decompressor(fbs.reader(), .{
        .window_buffer = window_buffer,
    });

    // Unpack tarball
    var diagnostics: std.tar.Options.Diagnostics = .{ .allocator = gpa };
    defer diagnostics.deinit();
    std.tar.pipeToFileSystem(out_dir, decompressor.reader(), .{
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
    log.info("finished\n", .{});
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

// find libs/DirectXShaderCompiler/tools/clang/lib/Lex | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_lex_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/tools/clang/lib/Lex/MacroInfo.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Lex/Preprocessor.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Lex/PPExpressions.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Lex/PreprocessorLexer.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Lex/HeaderSearch.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Lex/PPDirectives.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Lex/ScratchBuffer.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Lex/ModuleMap.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Lex/TokenLexer.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Lex/Lexer.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Lex/HLSLMacroExpander.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Lex/PTHLexer.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Lex/PPCallbacks.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Lex/Pragma.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Lex/PPCaching.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Lex/PreprocessingRecord.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Lex/PPMacroExpansion.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Lex/HeaderMap.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Lex/LiteralSupport.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Lex/PPLexerChange.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Lex/TokenConcatenation.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Lex/PPConditionalDirectiveRecord.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Lex/MacroArgs.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/Basic | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_basic_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/tools/clang/lib/Basic/OpenMPKinds.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Basic/TargetInfo.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Basic/LangOptions.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Basic/Warnings.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Basic/Builtins.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Basic/DiagnosticOptions.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Basic/Module.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Basic/Version.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Basic/IdentifierTable.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Basic/TokenKinds.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Basic/ObjCRuntime.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Basic/SourceManager.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Basic/VersionTuple.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Basic/FileSystemStatCache.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Basic/FileManager.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Basic/CharInfo.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Basic/OperatorPrecedence.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Basic/SanitizerBlacklist.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Basic/VirtualFileSystem.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Basic/DiagnosticIDs.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Basic/Diagnostic.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Basic/Targets.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Basic/Attributes.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Basic/SourceLocation.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Basic/Sanitizers.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/Driver | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_driver_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/tools/clang/lib/Driver/Job.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Driver/ToolChains.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Driver/DriverOptions.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Driver/Types.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Driver/MinGWToolChain.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Driver/Phases.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Driver/MSVCToolChain.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Driver/Compilation.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Driver/Driver.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Driver/Multilib.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Driver/Tools.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Driver/SanitizerArgs.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Driver/Tool.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Driver/Action.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Driver/CrossWindowsToolChain.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Driver/ToolChain.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/Analysis | grep -v 'CocoaConventions.cpp' | grep -v 'FormatString.cpp' | grep -v 'PrintfFormatString.cpp' | grep -v 'ScanfFormatString.cpp' | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_analysis_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/tools/clang/lib/Analysis/ReachableCode.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Analysis/ThreadSafetyLogical.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Analysis/ThreadSafetyCommon.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Analysis/CFG.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Analysis/BodyFarm.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Analysis/ThreadSafety.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Analysis/UninitializedValues.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Analysis/CFGReachabilityAnalysis.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Analysis/Dominators.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Analysis/PseudoConstantAnalysis.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Analysis/AnalysisDeclContext.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Analysis/LiveVariables.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Analysis/CallGraph.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Analysis/PostOrderCFGView.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Analysis/ProgramPoint.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Analysis/ObjCNoReturn.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Analysis/ThreadSafetyTIL.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Analysis/CFGStmtMap.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Analysis/Consumed.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Analysis/CodeInjector.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/Index | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_index_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/tools/clang/lib/Index/CommentToXML.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Index/USRGeneration.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/Parse | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_parse_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/tools/clang/lib/Parse/ParseExprCXX.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Parse/ParseTemplate.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Parse/ParseDeclCXX.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Parse/ParseInit.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Parse/ParseOpenMP.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Parse/HLSLRootSignature.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Parse/ParseObjc.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Parse/ParseDecl.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Parse/ParseExpr.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Parse/ParseHLSL.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Parse/ParseCXXInlineMethods.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Parse/ParseStmtAsm.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Parse/ParseStmt.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Parse/ParsePragma.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Parse/Parser.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Parse/ParseAST.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Parse/ParseTentative.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/AST | grep -v 'NSAPI.cpp' | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_ast_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/ExprConstant.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/ExprCXX.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/CommentCommandTraits.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/Mangle.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/ASTDiagnostic.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/CommentParser.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/AttrImpl.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/ASTDumper.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/DeclOpenMP.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/ASTTypeTraits.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/ASTImporter.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/StmtPrinter.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/CommentBriefParser.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/APValue.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/ASTConsumer.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/DeclCXX.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/Stmt.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/CommentSema.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/HlslTypes.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/ASTContextHLSL.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/InheritViz.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/Expr.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/RecordLayout.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/StmtIterator.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/ExprClassification.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/DeclPrinter.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/DeclBase.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/StmtProfile.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/Comment.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/VTTBuilder.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/Decl.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/SelectorLocationsKind.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/TypeLoc.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/DeclarationName.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/DeclObjC.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/VTableBuilder.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/CommentLexer.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/StmtViz.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/DeclTemplate.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/CXXInheritance.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/RecordLayoutBuilder.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/RawCommentList.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/TemplateBase.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/HlslBuiltinTypeDeclBuilder.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/DeclFriend.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/ItaniumMangle.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/ASTContext.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/TemplateName.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/ParentMap.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/ItaniumCXXABI.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/NestedNameSpecifier.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/MicrosoftMangle.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/DeclGroup.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/Type.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/ExternalASTSource.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/TypePrinter.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/AST/MicrosoftCXXABI.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/Edit | grep -v 'RewriteObjCFoundationAPI.cpp' | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_edit_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/tools/clang/lib/Edit/EditedSource.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Edit/Commit.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/Sema | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_sema_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaDXR.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/CodeCompleteConsumer.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaOverload.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaLambda.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaTemplateDeduction.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/MultiplexExternalSemaSource.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/IdentifierResolver.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/TypeLocBuilder.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaCUDA.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaTemplateInstantiate.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaTemplate.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/DelayedDiagnostic.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaTemplateInstantiateDecl.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaDeclCXX.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/ScopeInfo.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaStmtAttr.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaChecking.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaCast.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaInit.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaType.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaDeclAttr.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaOpenMP.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaFixItUtils.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaTemplateVariadic.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaExprCXX.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/Scope.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/DeclSpec.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaLookup.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaPseudoObject.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/AttributeList.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaDeclObjC.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaCXXScopeSpec.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaExprMember.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaAccess.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaStmt.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaCodeComplete.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaExprObjC.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaAttr.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaStmtAsm.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaExpr.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/JumpDiagnostics.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaHLSL.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaObjCProperty.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaConsumer.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaDecl.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/SemaExceptionSpec.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/Sema.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Sema/AnalysisBasedWarnings.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/CodeGen | grep -v 'CGObjCGNU.cpp' | grep -v 'CGObjCMac.cpp' | grep -v 'CGObjCRuntime.cpp' | grep -v 'CGOpenCLRuntime.cpp' | grep -v 'CGOpenMPRuntime.cpp' | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_codegen_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/ObjectFilePCHContainerOperations.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGHLSLMSFinishCodeGen.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGDeclCXX.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/SanitizerMetadata.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGDecl.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/TargetInfo.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGCall.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGVTables.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGExprScalar.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGBlocks.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGExpr.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CodeGenPGO.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGStmtOpenMP.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGExprCXX.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/BackendUtil.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGAtomic.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGCUDARuntime.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGHLSLRootSignature.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CodeGenAction.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGStmt.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CodeGenABITypes.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGClass.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGException.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGHLSLRuntime.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGExprComplex.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGExprConstant.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/ModuleBuilder.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CodeGenTypes.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGCUDANV.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGRecordLayoutBuilder.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CoverageMappingGen.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGExprAgg.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGVTT.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGCXX.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGCleanup.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGHLSLMS.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CodeGenFunction.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/ItaniumCXXABI.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGDebugInfo.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGCXXABI.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGObjC.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CodeGenModule.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGBuiltin.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CodeGenTBAA.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/CGLoopInfo.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/CodeGen/MicrosoftCXXABI.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/ASTMatchers | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_astmatchers_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/tools/clang/lib/ASTMatchers/Dynamic/Diagnostics.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/ASTMatchers/Dynamic/Registry.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/ASTMatchers/Dynamic/VariantValue.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/ASTMatchers/Dynamic/Parser.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/ASTMatchers/ASTMatchersInternal.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/ASTMatchers/ASTMatchFinder.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/Tooling/Core | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_tooling_core_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/tools/clang/lib/Tooling/Core/Replacement.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/Tooling | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_tooling_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/tools/clang/lib/Tooling/JSONCompilationDatabase.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Tooling/FileMatchTrie.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Tooling/Core/Replacement.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Tooling/RefactoringCallbacks.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Tooling/CommonOptionsParser.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Tooling/CompilationDatabase.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Tooling/ArgumentsAdjusters.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Tooling/Refactoring.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Tooling/Tooling.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/Format | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_format_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/tools/clang/lib/Format/FormatToken.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Format/ContinuationIndenter.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Format/Format.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Format/UnwrappedLineFormatter.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Format/WhitespaceManager.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Format/BreakableToken.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Format/TokenAnnotator.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Format/UnwrappedLineParser.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/Rewrite | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_rewrite_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/tools/clang/lib/Rewrite/HTMLRewrite.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Rewrite/RewriteRope.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Rewrite/DeltaTree.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Rewrite/TokenRewriter.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Rewrite/Rewriter.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/Frontend | grep -v 'RewriteModernObjC.cpp' | grep -v 'ChainedIncludesSource.cpp' | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_frontend_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/ASTConsumers.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/InitPreprocessor.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/FrontendActions.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/InitHeaderSearch.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/ASTMerge.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/Rewrite/RewriteMacros.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/Rewrite/FixItRewriter.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/Rewrite/InclusionRewriter.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/Rewrite/RewriteTest.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/Rewrite/FrontendActions_rewrite.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/Rewrite/RewriteObjC.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/Rewrite/HTMLPrint.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/DependencyGraph.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/FrontendAction.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/MultiplexConsumer.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/TextDiagnostic.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/ModuleDependencyCollector.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/DiagnosticRenderer.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/CompilerInvocation.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/CreateInvocationFromCommandLine.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/PCHContainerOperations.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/TextDiagnosticPrinter.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/CodeGenOptions.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/HeaderIncludeGen.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/ASTUnit.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/ChainedDiagnosticConsumer.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/SerializedDiagnosticPrinter.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/LayoutOverrideSource.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/CacheTokens.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/FrontendOptions.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/LangStandards.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/TextDiagnosticBuffer.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/PrintPreprocessedOutput.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/DependencyFile.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/SerializedDiagnosticReader.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/VerifyDiagnosticConsumer.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/CompilerInstance.cpp",
    "libs/DirectXShaderCompiler/tools/clang/lib/Frontend/LogDiagnosticPrinter.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/tools/libclang | grep -v 'ARCMigrate.cpp' | grep -v 'BuildSystem.cpp' | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_tools_libclang_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/tools/clang/tools/libclang/dxcisenseimpl.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/libclang/IndexBody.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/libclang/CIndexCXX.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/libclang/CIndexer.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/libclang/IndexingContext.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/libclang/CXLoadedDiagnostic.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/libclang/Indexing.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/libclang/CXCursor.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/libclang/dxcrewriteunused.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/libclang/CXCompilationDatabase.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/libclang/CIndexInclusionStack.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/libclang/CXStoredDiagnostic.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/libclang/CIndexHigh.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/libclang/CXType.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/libclang/CIndex.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/libclang/CIndexCodeCompletion.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/libclang/IndexTypeSourceInfo.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/libclang/CIndexDiagnostic.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/libclang/CXString.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/libclang/IndexDecl.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/libclang/CXComment.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/libclang/CXSourceLocation.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/libclang/CIndexUSRs.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/tools/dxcompiler | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_tools_dxcompiler_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/tools/clang/tools/dxcompiler/MachSiegbertVogtDXCSA.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/dxcompiler/dxcdisassembler.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/dxcompiler/dxcvalidator.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/dxcompiler/dxillib.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/dxcompiler/dxcfilesystem.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/dxcompiler/DXCompiler.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/dxcompiler/dxcutil.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/dxcompiler/dxclinker.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/dxcompiler/dxcshadersourceinfo.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/dxcompiler/dxcassembler.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/dxcompiler/dxcapi.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/dxcompiler/dxclibrary.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/dxcompiler/dxcpdbutils.cpp",
    "libs/DirectXShaderCompiler/tools/clang/tools/dxcompiler/dxcompilerobj.cpp",
};

// find libs/DirectXShaderCompiler/lib/Bitcode/Reader | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_bitcode_reader_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/Bitcode/Reader/BitReader.cpp",
    "libs/DirectXShaderCompiler/lib/Bitcode/Reader/BitstreamReader.cpp",
    "libs/DirectXShaderCompiler/lib/Bitcode/Reader/BitcodeReader.cpp",
};

// find libs/DirectXShaderCompiler/lib/Bitcode/Writer | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_bitcode_writer_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/Bitcode/Writer/BitcodeWriterPass.cpp",
    "libs/DirectXShaderCompiler/lib/Bitcode/Writer/BitWriter.cpp",
    "libs/DirectXShaderCompiler/lib/Bitcode/Writer/ValueEnumerator.cpp",
    "libs/DirectXShaderCompiler/lib/Bitcode/Writer/BitcodeWriter.cpp",
};

// find libs/DirectXShaderCompiler/lib/IR | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_ir_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/IR/DebugInfoMetadata.cpp",
    "libs/DirectXShaderCompiler/lib/IR/GCOV.cpp",
    "libs/DirectXShaderCompiler/lib/IR/IRBuilder.cpp",
    "libs/DirectXShaderCompiler/lib/IR/Pass.cpp",
    "libs/DirectXShaderCompiler/lib/IR/AutoUpgrade.cpp",
    "libs/DirectXShaderCompiler/lib/IR/Core.cpp",
    "libs/DirectXShaderCompiler/lib/IR/InlineAsm.cpp",
    "libs/DirectXShaderCompiler/lib/IR/Module.cpp",
    "libs/DirectXShaderCompiler/lib/IR/GVMaterializer.cpp",
    "libs/DirectXShaderCompiler/lib/IR/Operator.cpp",
    "libs/DirectXShaderCompiler/lib/IR/DataLayout.cpp",
    "libs/DirectXShaderCompiler/lib/IR/IntrinsicInst.cpp",
    "libs/DirectXShaderCompiler/lib/IR/DebugLoc.cpp",
    "libs/DirectXShaderCompiler/lib/IR/Dominators.cpp",
    "libs/DirectXShaderCompiler/lib/IR/Constants.cpp",
    "libs/DirectXShaderCompiler/lib/IR/PassRegistry.cpp",
    "libs/DirectXShaderCompiler/lib/IR/DiagnosticPrinter.cpp",
    "libs/DirectXShaderCompiler/lib/IR/ValueSymbolTable.cpp",
    "libs/DirectXShaderCompiler/lib/IR/Globals.cpp",
    "libs/DirectXShaderCompiler/lib/IR/ConstantRange.cpp",
    "libs/DirectXShaderCompiler/lib/IR/LegacyPassManager.cpp",
    "libs/DirectXShaderCompiler/lib/IR/Function.cpp",
    "libs/DirectXShaderCompiler/lib/IR/TypeFinder.cpp",
    "libs/DirectXShaderCompiler/lib/IR/DebugInfo.cpp",
    "libs/DirectXShaderCompiler/lib/IR/LLVMContextImpl.cpp",
    "libs/DirectXShaderCompiler/lib/IR/Verifier.cpp",
    "libs/DirectXShaderCompiler/lib/IR/Comdat.cpp",
    "libs/DirectXShaderCompiler/lib/IR/Value.cpp",
    "libs/DirectXShaderCompiler/lib/IR/Use.cpp",
    "libs/DirectXShaderCompiler/lib/IR/MetadataTracking.cpp",
    "libs/DirectXShaderCompiler/lib/IR/Mangler.cpp",
    "libs/DirectXShaderCompiler/lib/IR/DiagnosticInfo.cpp",
    "libs/DirectXShaderCompiler/lib/IR/ValueTypes.cpp",
    "libs/DirectXShaderCompiler/lib/IR/DIBuilder.cpp",
    "libs/DirectXShaderCompiler/lib/IR/User.cpp",
    "libs/DirectXShaderCompiler/lib/IR/MDBuilder.cpp",
    "libs/DirectXShaderCompiler/lib/IR/Metadata.cpp",
    "libs/DirectXShaderCompiler/lib/IR/BasicBlock.cpp",
    "libs/DirectXShaderCompiler/lib/IR/Instruction.cpp",
    "libs/DirectXShaderCompiler/lib/IR/AsmWriter.cpp",
    "libs/DirectXShaderCompiler/lib/IR/Statepoint.cpp",
    "libs/DirectXShaderCompiler/lib/IR/LLVMContext.cpp",
    "libs/DirectXShaderCompiler/lib/IR/Instructions.cpp",
    "libs/DirectXShaderCompiler/lib/IR/PassManager.cpp",
    "libs/DirectXShaderCompiler/lib/IR/ConstantFold.cpp",
    "libs/DirectXShaderCompiler/lib/IR/IRPrintingPasses.cpp",
    "libs/DirectXShaderCompiler/lib/IR/Attributes.cpp",
    "libs/DirectXShaderCompiler/lib/IR/Type.cpp",
};

// find libs/DirectXShaderCompiler/lib/IRReader | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_irreader_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/IRReader/IRReader.cpp",
};

// find libs/DirectXShaderCompiler/lib/Linker | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_linker_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/Linker/LinkModules.cpp",
};

// find libs/DirectXShaderCompiler/lib/AsmParser | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_asmparser_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/AsmParser/LLParser.cpp",
    "libs/DirectXShaderCompiler/lib/AsmParser/LLLexer.cpp",
    "libs/DirectXShaderCompiler/lib/AsmParser/Parser.cpp",
};

// find libs/DirectXShaderCompiler/lib/Analysis | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_analysis_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/Analysis/regioninfo.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/DxilConstantFolding.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/CGSCCPassManager.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/DxilValueCache.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/AliasSetTracker.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/LoopPass.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/MemDerefPrinter.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/regionprinter.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/DominanceFrontier.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/Loads.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/BlockFrequencyInfoImpl.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/Analysis.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/ReducibilityAnalysis.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/CodeMetrics.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/TargetTransformInfo.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/CFG.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/SparsePropagation.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/IntervalPartition.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/ScalarEvolutionNormalization.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/CFGPrinter.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/IPA/IPA.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/IPA/GlobalsModRef.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/IPA/InlineCost.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/IPA/CallGraph.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/IPA/CallGraphSCCPass.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/IPA/CallPrinter.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/Lint.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/ScalarEvolution.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/MemoryDependenceAnalysis.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/PostDominators.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/TypeBasedAliasAnalysis.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/DxilSimplify.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/DivergenceAnalysis.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/BlockFrequencyInfo.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/VectorUtils.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/Delinearization.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/AssumptionCache.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/AliasAnalysisEvaluator.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/IVUsers.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/ValueTracking.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/PHITransAddr.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/NoAliasAnalysis.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/AliasDebugger.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/DependenceAnalysis.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/LibCallSemantics.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/DomPrinter.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/Trace.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/LazyValueInfo.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/ConstantFolding.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/LoopAccessAnalysis.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/BranchProbabilityInfo.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/TargetLibraryInfo.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/CaptureTracking.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/IteratedDominanceFrontier.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/MemoryLocation.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/InstructionSimplify.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/VectorUtils2.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/MemDepPrinter.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/InstCount.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/CostModel.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/DxilConstantFoldingExt.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/ScopedNoAliasAA.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/ModuleDebugInfoPrinter.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/LibCallAliasAnalysis.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/MemoryBuiltins.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/PtrUseVisitor.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/AliasAnalysisCounter.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/ScalarEvolutionAliasAnalysis.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/BasicAliasAnalysis.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/ScalarEvolutionExpander.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/LoopInfo.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/CFLAliasAnalysis.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/Interval.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/RegionPass.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/LazyCallGraph.cpp",
    "libs/DirectXShaderCompiler/lib/Analysis/AliasAnalysis.cpp",
};

// find libs/DirectXShaderCompiler/lib/MSSupport | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_mssupport_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/MSSupport/MSFileSystemImpl.cpp",
};

// find libs/DirectXShaderCompiler/lib/Transforms/Utils | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_transforms_utils_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/LoopUtils.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/DemoteRegToStack.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/Utils.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/SimplifyCFG.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/LoopSimplifyId.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/UnifyFunctionExitNodes.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/SSAUpdater.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/SimplifyIndVar.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/BasicBlockUtils.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/ASanStackFrameLayout.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/FlattenCFG.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/CmpInstAnalysis.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/ModuleUtils.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/LoopUnroll.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/LowerSwitch.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/LoopVersioning.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/AddDiscriminators.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/Local.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/PromoteMemoryToRegister.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/LCSSA.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/BypassSlowDivision.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/Mem2Reg.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/CodeExtractor.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/InlineFunction.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/LoopSimplify.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/SimplifyLibCalls.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/MetaRenamer.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/CloneModule.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/IntegerDivision.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/LoopUnrollRuntime.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/ValueMapper.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/InstructionNamer.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/CtorUtils.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/GlobalStatus.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/LowerInvoke.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/SimplifyInstructions.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/BuildLibCalls.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/SymbolRewriter.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/BreakCriticalEdges.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Utils/CloneFunction.cpp",
};

// find libs/DirectXShaderCompiler/lib/Transforms/InstCombine | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_transforms_instcombine_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/Transforms/InstCombine/InstCombineCasts.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/InstCombine/InstCombineCompares.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/InstCombine/InstCombineSelect.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/InstCombine/InstCombineCalls.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/InstCombine/InstCombineSimplifyDemanded.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/InstCombine/InstCombineAddSub.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/InstCombine/InstructionCombining.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/InstCombine/InstCombineMulDivRem.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/InstCombine/InstCombineLoadStoreAlloca.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/InstCombine/InstCombineShifts.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/InstCombine/InstCombineVectorOps.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/InstCombine/InstCombineAndOrXor.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/InstCombine/InstCombinePHI.cpp",
};

// find libs/DirectXShaderCompiler/lib/Transforms/IPO | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_transforms_ipo_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/Transforms/IPO/ExtractGV.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/IPO/GlobalDCE.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/IPO/PruneEH.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/IPO/MergeFunctions.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/IPO/IPConstantPropagation.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/IPO/ConstantMerge.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/IPO/FunctionAttrs.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/IPO/BarrierNoopPass.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/IPO/StripSymbols.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/IPO/Internalize.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/IPO/StripDeadPrototypes.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/IPO/DeadArgumentElimination.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/IPO/ArgumentPromotion.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/IPO/PassManagerBuilder.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/IPO/LoopExtractor.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/IPO/Inliner.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/IPO/InlineAlways.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/IPO/LowerBitSets.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/IPO/InlineSimple.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/IPO/PartialInlining.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/IPO/ElimAvailExtern.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/IPO/IPO.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/IPO/GlobalOpt.cpp",
};

// find libs/DirectXShaderCompiler/lib/Transforms/Scalar | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_transforms_scalar_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/LoopRotation.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/LoopInstSimplify.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/ConstantProp.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/StructurizeCFG.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/IndVarSimplify.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/FlattenCFGPass.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/PartiallyInlineLibCalls.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/Scalarizer.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/ADCE.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/SCCP.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/InductiveRangeCheckElimination.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/LoopDistribute.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/Sink.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/DxilEliminateVector.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/CorrelatedValuePropagation.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/EarlyCSE.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/LoopUnrollPass.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/DxilLoopUnroll.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/GVN.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/ConstantHoisting.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/DxilEraseDeadRegion.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/Scalar.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/LoopInterchange.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/JumpThreading.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/Reg2MemHLSL.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/Reg2Mem.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/HoistConstantArray.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/ScalarReplAggregates.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/LoadCombine.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/SeparateConstOffsetFromGEP.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/Reassociate.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/LoopIdiomRecognize.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/SampleProfile.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/DeadStoreElimination.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/SimplifyCFGPass.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/LoopStrengthReduce.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/DxilRemoveDeadBlocks.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/LoopRerollPass.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/LowerAtomic.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/MemCpyOptimizer.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/BDCE.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/LowerExpectIntrinsic.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/DxilFixConstArrayInitializer.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/ScalarReplAggregatesHLSL.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/Float2Int.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/LoopDeletion.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/SROA.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/MergedLoadStoreMotion.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/DCE.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/AlignmentFromAssumptions.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/DxilRemoveUnstructuredLoopExits.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/SpeculativeExecution.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/NaryReassociate.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/LoopUnswitch.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/RewriteStatepointsForGC.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/LICM.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/DxilConditionalMem2Reg.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/PlaceSafepoints.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/LowerTypePasses.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/TailRecursionElimination.cpp",
    "libs/DirectXShaderCompiler/lib/Transforms/Scalar/StraightLineStrengthReduce.cpp",
};

// find libs/DirectXShaderCompiler/lib/Transforms/Vectorize | grep -v 'BBVectorize.cpp' | grep -v 'LoopVectorize.cpp' | grep -v 'LPVectorizer.cpp' | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_transforms_vectorize_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/Transforms/Vectorize/Vectorize.cpp",
};

// find libs/DirectXShaderCompiler/lib/Target | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_target_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/Target/TargetSubtargetInfo.cpp",
    "libs/DirectXShaderCompiler/lib/Target/TargetLoweringObjectFile.cpp",
    "libs/DirectXShaderCompiler/lib/Target/Target.cpp",
    "libs/DirectXShaderCompiler/lib/Target/TargetRecip.cpp",
    "libs/DirectXShaderCompiler/lib/Target/TargetMachine.cpp",
    "libs/DirectXShaderCompiler/lib/Target/TargetIntrinsicInfo.cpp",
    "libs/DirectXShaderCompiler/lib/Target/TargetMachineC.cpp",
};

// find libs/DirectXShaderCompiler/lib/ProfileData | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_profiledata_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/ProfileData/InstrProfReader.cpp",
    "libs/DirectXShaderCompiler/lib/ProfileData/CoverageMappingWriter.cpp",
    "libs/DirectXShaderCompiler/lib/ProfileData/CoverageMapping.cpp",
    "libs/DirectXShaderCompiler/lib/ProfileData/InstrProfWriter.cpp",
    "libs/DirectXShaderCompiler/lib/ProfileData/CoverageMappingReader.cpp",
    "libs/DirectXShaderCompiler/lib/ProfileData/SampleProfWriter.cpp",
    "libs/DirectXShaderCompiler/lib/ProfileData/SampleProf.cpp",
    "libs/DirectXShaderCompiler/lib/ProfileData/InstrProf.cpp",
    "libs/DirectXShaderCompiler/lib/ProfileData/SampleProfReader.cpp",
};

// find libs/DirectXShaderCompiler/lib/Option | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_option_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/Option/Arg.cpp",
    "libs/DirectXShaderCompiler/lib/Option/OptTable.cpp",
    "libs/DirectXShaderCompiler/lib/Option/Option.cpp",
    "libs/DirectXShaderCompiler/lib/Option/ArgList.cpp",
};

// find libs/DirectXShaderCompiler/lib/PassPrinters | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_passprinters_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/PassPrinters/PassPrinters.cpp",
};

// find libs/DirectXShaderCompiler/lib/Passes | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_passes_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/Passes/PassBuilder.cpp",
};

// find libs/DirectXShaderCompiler/lib/HLSL | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_hlsl_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/HLSL/HLLegalizeParameter.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/HLOperations.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilExportMap.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilPrecisePropagatePass.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilPatchShaderRecordBindings.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/HLUtil.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilCondenseResources.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilValidation.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilDeleteRedundantDebugValues.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilNoops.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/ComputeViewIdState.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/HLMatrixType.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilPackSignatureElement.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilLegalizeSampleOffsetPass.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/HLModule.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilContainerReflection.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilLegalizeEvalOperations.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/ControlDependence.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilTargetTransformInfo.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/HLOperationLower.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilSignatureValidation.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilRenameResourcesPass.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilPromoteResourcePasses.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/PauseResumePasses.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/HLDeadFunctionElimination.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilExpandTrigIntrinsics.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilPoisonValues.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilGenerationPass.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilTranslateRawBuffer.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/ComputeViewIdStateBuilder.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilTargetLowering.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilNoOptLegalize.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/HLExpandStoreIntrinsics.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/HLMetadataPasses.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilPreparePasses.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/HLMatrixBitcastLowerPass.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/HLPreprocess.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/HLSignatureLower.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/HLMatrixLowerPass.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/HLResource.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/HLLowerUDT.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/HLOperationLowerExtension.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilEliminateOutputDynamicIndexing.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilSimpleGVNHoist.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxcOptimizer.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilLinker.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilConvergent.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilLoopDeletion.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/WaveSensitivityAnalysis.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/DxilPreserveAllOutputs.cpp",
    "libs/DirectXShaderCompiler/lib/HLSL/HLMatrixSubscriptUseReplacer.cpp",
};

// find libs/DirectXShaderCompiler/lib/Support | grep -v 'DynamicLibrary.cpp' | grep -v 'PluginLoader.cpp' | grep -v '\.inc\.cpp' | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_support_cpp_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/Support/BranchProbability.cpp",
    "libs/DirectXShaderCompiler/lib/Support/Memory.cpp",
    "libs/DirectXShaderCompiler/lib/Support/ToolOutputFile.cpp",
    "libs/DirectXShaderCompiler/lib/Support/YAMLTraits.cpp",
    "libs/DirectXShaderCompiler/lib/Support/MD5.cpp",
    "libs/DirectXShaderCompiler/lib/Support/Mutex.cpp",
    "libs/DirectXShaderCompiler/lib/Support/Program.cpp",
    "libs/DirectXShaderCompiler/lib/Support/APFloat.cpp",
    "libs/DirectXShaderCompiler/lib/Support/SpecialCaseList.cpp",
    "libs/DirectXShaderCompiler/lib/Support/LEB128.cpp",
    "libs/DirectXShaderCompiler/lib/Support/FileOutputBuffer.cpp",
    "libs/DirectXShaderCompiler/lib/Support/Process.cpp",
    "libs/DirectXShaderCompiler/lib/Support/regmalloc.cpp",
    "libs/DirectXShaderCompiler/lib/Support/ScaledNumber.cpp",
    "libs/DirectXShaderCompiler/lib/Support/Locale.cpp",
    "libs/DirectXShaderCompiler/lib/Support/TimeProfiler.cpp",
    "libs/DirectXShaderCompiler/lib/Support/FileUtilities.cpp",
    "libs/DirectXShaderCompiler/lib/Support/TimeValue.cpp",
    "libs/DirectXShaderCompiler/lib/Support/TargetRegistry.cpp",
    "libs/DirectXShaderCompiler/lib/Support/Statistic.cpp",
    "libs/DirectXShaderCompiler/lib/Support/Twine.cpp",
    "libs/DirectXShaderCompiler/lib/Support/DAGDeltaAlgorithm.cpp",
    "libs/DirectXShaderCompiler/lib/Support/APSInt.cpp",
    "libs/DirectXShaderCompiler/lib/Support/SearchForAddressOfSpecialSymbol.cpp",
    "libs/DirectXShaderCompiler/lib/Support/LineIterator.cpp",
    "libs/DirectXShaderCompiler/lib/Support/PrettyStackTrace.cpp",
    "libs/DirectXShaderCompiler/lib/Support/Timer.cpp",
    "libs/DirectXShaderCompiler/lib/Support/ConvertUTFWrapper.cpp",
    "libs/DirectXShaderCompiler/lib/Support/LockFileManager.cpp",
    "libs/DirectXShaderCompiler/lib/Support/assert.cpp",
    "libs/DirectXShaderCompiler/lib/Support/ARMBuildAttrs.cpp",
    "libs/DirectXShaderCompiler/lib/Support/CrashRecoveryContext.cpp",
    "libs/DirectXShaderCompiler/lib/Support/Options.cpp",
    "libs/DirectXShaderCompiler/lib/Support/DeltaAlgorithm.cpp",
    "libs/DirectXShaderCompiler/lib/Support/SystemUtils.cpp",
    "libs/DirectXShaderCompiler/lib/Support/ThreadLocal.cpp",
    "libs/DirectXShaderCompiler/lib/Support/YAMLParser.cpp",
    "libs/DirectXShaderCompiler/lib/Support/StringPool.cpp",
    "libs/DirectXShaderCompiler/lib/Support/IntrusiveRefCntPtr.cpp",
    "libs/DirectXShaderCompiler/lib/Support/Watchdog.cpp",
    "libs/DirectXShaderCompiler/lib/Support/StringRef.cpp",
    "libs/DirectXShaderCompiler/lib/Support/Compression.cpp",
    "libs/DirectXShaderCompiler/lib/Support/COM.cpp",
    "libs/DirectXShaderCompiler/lib/Support/FoldingSet.cpp",
    "libs/DirectXShaderCompiler/lib/Support/FormattedStream.cpp",
    "libs/DirectXShaderCompiler/lib/Support/BlockFrequency.cpp",
    "libs/DirectXShaderCompiler/lib/Support/IntervalMap.cpp",
    "libs/DirectXShaderCompiler/lib/Support/MemoryObject.cpp",
    "libs/DirectXShaderCompiler/lib/Support/TargetParser.cpp",
    "libs/DirectXShaderCompiler/lib/Support/raw_os_ostream.cpp",
    "libs/DirectXShaderCompiler/lib/Support/Allocator.cpp",
    "libs/DirectXShaderCompiler/lib/Support/DataExtractor.cpp",
    "libs/DirectXShaderCompiler/lib/Support/APInt.cpp",
    "libs/DirectXShaderCompiler/lib/Support/StreamingMemoryObject.cpp",
    "libs/DirectXShaderCompiler/lib/Support/circular_raw_ostream.cpp",
    "libs/DirectXShaderCompiler/lib/Support/DataStream.cpp",
    "libs/DirectXShaderCompiler/lib/Support/Debug.cpp",
    "libs/DirectXShaderCompiler/lib/Support/Errno.cpp",
    "libs/DirectXShaderCompiler/lib/Support/Path.cpp",
    "libs/DirectXShaderCompiler/lib/Support/raw_ostream.cpp",
    "libs/DirectXShaderCompiler/lib/Support/Atomic.cpp",
    "libs/DirectXShaderCompiler/lib/Support/SmallVector.cpp",
    "libs/DirectXShaderCompiler/lib/Support/MathExtras.cpp",
    "libs/DirectXShaderCompiler/lib/Support/MemoryBuffer.cpp",
    "libs/DirectXShaderCompiler/lib/Support/ErrorHandling.cpp",
    "libs/DirectXShaderCompiler/lib/Support/StringExtras.cpp",
    "libs/DirectXShaderCompiler/lib/Support/Triple.cpp",
    "libs/DirectXShaderCompiler/lib/Support/Hashing.cpp",
    "libs/DirectXShaderCompiler/lib/Support/GraphWriter.cpp",
    "libs/DirectXShaderCompiler/lib/Support/RandomNumberGenerator.cpp",
    "libs/DirectXShaderCompiler/lib/Support/SourceMgr.cpp",
    "libs/DirectXShaderCompiler/lib/Support/Signals.cpp",
    "libs/DirectXShaderCompiler/lib/Support/Dwarf.cpp",
    "libs/DirectXShaderCompiler/lib/Support/StringMap.cpp",
    "libs/DirectXShaderCompiler/lib/Support/MSFileSystemBasic.cpp",
    "libs/DirectXShaderCompiler/lib/Support/IntEqClasses.cpp",
    "libs/DirectXShaderCompiler/lib/Support/Threading.cpp",
    "libs/DirectXShaderCompiler/lib/Support/RWMutex.cpp",
    "libs/DirectXShaderCompiler/lib/Support/StringSaver.cpp",
    "libs/DirectXShaderCompiler/lib/Support/CommandLine.cpp",
    "libs/DirectXShaderCompiler/lib/Support/ManagedStatic.cpp",
    "libs/DirectXShaderCompiler/lib/Support/Host.cpp",
    "libs/DirectXShaderCompiler/lib/Support/Unicode.cpp",
    "libs/DirectXShaderCompiler/lib/Support/SmallPtrSet.cpp",
    "libs/DirectXShaderCompiler/lib/Support/Valgrind.cpp",
    "libs/DirectXShaderCompiler/lib/Support/Regex.cpp",
    "libs/DirectXShaderCompiler/lib/Support/ARMWinEH.cpp",
};

// find libs/DirectXShaderCompiler/lib/Support | grep '\.c$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_support_c_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/Support/ConvertUTF.c",
    "libs/DirectXShaderCompiler/lib/Support/regexec.c",
    "libs/DirectXShaderCompiler/lib/Support/regcomp.c",
    "libs/DirectXShaderCompiler/lib/Support/regerror.c",
    "libs/DirectXShaderCompiler/lib/Support/regstrlcpy.c",
    "libs/DirectXShaderCompiler/lib/Support/regfree.c",
};

// find libs/DirectXShaderCompiler/lib/DxcSupport | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_dxcsupport_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/DxcSupport/WinIncludes.cpp",
    "libs/DirectXShaderCompiler/lib/DxcSupport/HLSLOptions.cpp",
    "libs/DirectXShaderCompiler/lib/DxcSupport/dxcmem.cpp",
    "libs/DirectXShaderCompiler/lib/DxcSupport/WinFunctions.cpp",
    "libs/DirectXShaderCompiler/lib/DxcSupport/Global.cpp",
    "libs/DirectXShaderCompiler/lib/DxcSupport/Unicode.cpp",
    "libs/DirectXShaderCompiler/lib/DxcSupport/FileIOHelper.cpp",
    "libs/DirectXShaderCompiler/lib/DxcSupport/dxcapi.use.cpp",
    "libs/DirectXShaderCompiler/lib/DxcSupport/WinAdapter.cpp",
};

// find libs/DirectXShaderCompiler/lib/DxcBindingTable | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_dxcbindingtable_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/DxcBindingTable/DxcBindingTable.cpp",
};

// find libs/DirectXShaderCompiler/lib/DXIL | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_dxil_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/DXIL/DxilInterpolationMode.cpp",
    "libs/DirectXShaderCompiler/lib/DXIL/DxilCompType.cpp",
    "libs/DirectXShaderCompiler/lib/DXIL/DxilShaderFlags.cpp",
    "libs/DirectXShaderCompiler/lib/DXIL/DxilResourceBase.cpp",
    "libs/DirectXShaderCompiler/lib/DXIL/DxilResource.cpp",
    "libs/DirectXShaderCompiler/lib/DXIL/DxilOperations.cpp",
    "libs/DirectXShaderCompiler/lib/DXIL/DxilSignature.cpp",
    "libs/DirectXShaderCompiler/lib/DXIL/DxilResourceProperties.cpp",
    "libs/DirectXShaderCompiler/lib/DXIL/DxilPDB.cpp",
    "libs/DirectXShaderCompiler/lib/DXIL/DxilUtilDbgInfoAndMisc.cpp",
    "libs/DirectXShaderCompiler/lib/DXIL/DxilSignatureElement.cpp",
    "libs/DirectXShaderCompiler/lib/DXIL/DxilSemantic.cpp",
    "libs/DirectXShaderCompiler/lib/DXIL/DxilSampler.cpp",
    "libs/DirectXShaderCompiler/lib/DXIL/DxilModuleHelper.cpp",
    "libs/DirectXShaderCompiler/lib/DXIL/DxilResourceBinding.cpp",
    "libs/DirectXShaderCompiler/lib/DXIL/DxilTypeSystem.cpp",
    "libs/DirectXShaderCompiler/lib/DXIL/DxilCounters.cpp",
    "libs/DirectXShaderCompiler/lib/DXIL/DxilCBuffer.cpp",
    "libs/DirectXShaderCompiler/lib/DXIL/DxilUtil.cpp",
    "libs/DirectXShaderCompiler/lib/DXIL/DxilSubobject.cpp",
    "libs/DirectXShaderCompiler/lib/DXIL/DxilShaderModel.cpp",
    "libs/DirectXShaderCompiler/lib/DXIL/DxilMetadataHelper.cpp",
    "libs/DirectXShaderCompiler/lib/DXIL/DxilModule.cpp",
};

// find libs/DirectXShaderCompiler/lib/DxilContainer | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_dxilcontainer_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/DxilContainer/DxilRuntimeReflection.cpp",
    "libs/DirectXShaderCompiler/lib/DxilContainer/DxilRDATBuilder.cpp",
    "libs/DirectXShaderCompiler/lib/DxilContainer/RDATDumper.cpp",
    "libs/DirectXShaderCompiler/lib/DxilContainer/DxilContainerReader.cpp",
    "libs/DirectXShaderCompiler/lib/DxilContainer/D3DReflectionStrings.cpp",
    "libs/DirectXShaderCompiler/lib/DxilContainer/DxilContainer.cpp",
    "libs/DirectXShaderCompiler/lib/DxilContainer/RDATDxilSubobjects.cpp",
    "libs/DirectXShaderCompiler/lib/DxilContainer/D3DReflectionDumper.cpp",
    "libs/DirectXShaderCompiler/lib/DxilContainer/DxcContainerBuilder.cpp",
    "libs/DirectXShaderCompiler/lib/DxilContainer/DxilContainerAssembler.cpp",
};

// find libs/DirectXShaderCompiler/lib/DxilPIXPasses | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_dxilpixpasses_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/DxilPIXPasses/DxilDbgValueToDbgDeclare.cpp",
    "libs/DirectXShaderCompiler/lib/DxilPIXPasses/DxilRemoveDiscards.cpp",
    "libs/DirectXShaderCompiler/lib/DxilPIXPasses/DxilPIXDXRInvocationsLog.cpp",
    "libs/DirectXShaderCompiler/lib/DxilPIXPasses/DxilForceEarlyZ.cpp",
    "libs/DirectXShaderCompiler/lib/DxilPIXPasses/DxilAnnotateWithVirtualRegister.cpp",
    "libs/DirectXShaderCompiler/lib/DxilPIXPasses/DxilPIXAddTidToAmplificationShaderPayload.cpp",
    "libs/DirectXShaderCompiler/lib/DxilPIXPasses/DxilDebugInstrumentation.cpp",
    "libs/DirectXShaderCompiler/lib/DxilPIXPasses/DxilPIXPasses.cpp",
    "libs/DirectXShaderCompiler/lib/DxilPIXPasses/PixPassHelpers.cpp",
    "libs/DirectXShaderCompiler/lib/DxilPIXPasses/DxilPIXVirtualRegisters.cpp",
    "libs/DirectXShaderCompiler/lib/DxilPIXPasses/DxilShaderAccessTracking.cpp",
    "libs/DirectXShaderCompiler/lib/DxilPIXPasses/DxilOutputColorBecomesConstant.cpp",
    "libs/DirectXShaderCompiler/lib/DxilPIXPasses/DxilReduceMSAAToSingleSample.cpp",
    "libs/DirectXShaderCompiler/lib/DxilPIXPasses/DxilAddPixelHitInstrumentation.cpp",
    "libs/DirectXShaderCompiler/lib/DxilPIXPasses/DxilPIXMeshShaderOutputInstrumentation.cpp",
};

// find libs/DirectXShaderCompiler/lib/DxilCompression | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_dxilcompression_cpp_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/DxilCompression/DxilCompression.cpp",
};

// find libs/DirectXShaderCompiler/lib/DxilCompression | grep '\.c$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_dxilcompression_c_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/DxilCompression/miniz.c",
};

// find libs/DirectXShaderCompiler/lib/DxilRootSignature | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_dxilrootsignature_sources = [_][]const u8{
    "libs/DirectXShaderCompiler/lib/DxilRootSignature/DxilRootSignature.cpp",
    "libs/DirectXShaderCompiler/lib/DxilRootSignature/DxilRootSignatureSerializer.cpp",
    "libs/DirectXShaderCompiler/lib/DxilRootSignature/DxilRootSignatureConvert.cpp",
    "libs/DirectXShaderCompiler/lib/DxilRootSignature/DxilRootSignatureValidator.cpp",
};
