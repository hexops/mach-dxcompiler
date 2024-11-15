const std = @import("std");
const builtin = @import("builtin");
const Build = std.Build;

/// The latest binary release available at https://github.com/hexops/mach-dxcompiler/releases
const latest_binary_release = "2024.10.16+da605cf.1";

/// When building from source, which repository and revision to clone.
const source_repository = "https://github.com/hexops/DirectXShaderCompiler";
const source_revision = "4190bb0c90d374c6b4d0b0f2c7b45b604eda24b6"; // main branch

const log = std.log.scoped(.mach_dxcompiler);

pub fn build(b: *Build) !void {
    const optimize = b.standardOptimizeOption(.{});
    const target = b.standardTargetOptions(.{});
    const from_source = b.option(bool, "from_source", "Build dxcompiler from source (large C++ codebase)") orelse false;
    const debug_symbols = b.option(bool, "debug_symbols", "Whether to produce detailed debug symbols (g0) or not. These increase binary size considerably.") orelse false;
    const build_shared = b.option(bool, "shared", "Build dxcompiler shared libraries") orelse false;
    const build_spirv = b.option(bool, "spirv", "Build spir-v compilation support") orelse false;
    const skip_executables = b.option(bool, "skip_executables", "Skip building executables") orelse false;
    const skip_tests = b.option(bool, "skip_tests", "Skip building tests") orelse false;

    const machdxcompiler: struct { lib: *std.Build.Step.Compile, lib_path: ?[]const u8 } = blk: {
        if (!from_source) {
            // We can't express that an std.Build.Module should depend on our DownloadBinaryStep.
            // But we can express that an std.Build.Module should link a library, which depends on
            // our DownloadBinaryStep.
            const linkage = b.addStaticLibrary(.{
                .name = "machdxcompiler-linkage",
                .optimize = optimize,
                .target = target,
            });
            var download_step = DownloadBinaryStep.init(b, target.result, optimize);
            linkage.step.dependOn(&download_step.step);

            const cache_dir = binaryCacheDirPath(b, target.result, optimize) catch |err| std.debug.panic("unable to construct binary cache dir path: {}", .{err});
            linkage.addLibraryPath(.{ .cwd_relative = cache_dir });
            linkage.linkSystemLibrary("machdxcompiler");
            linkMachDxcDependenciesModule(&linkage.root_module);

            // not entirely sure this will work
            if (build_shared) {
                buildShared(b, linkage, optimize, target);
            }

            break :blk .{ .lib = linkage, .lib_path = cache_dir };
        } else {
            const lib = b.addStaticLibrary(.{
                .name = "machdxcompiler",
                .optimize = optimize,
                .target = target,
            });

            b.installArtifact(lib);

            // Microsoft does some shit.
            lib.root_module.sanitize_c = false;
            lib.root_module.sanitize_thread = false; // sometimes in parallel, too.

            lib.addCSourceFile(.{
                .file = b.path("src/mach_dxc.cpp"),
                .flags = &.{
                    "-fms-extensions", // __uuidof and friends (on non-windows targets)
                },
            });
            if (target.result.os.tag != .windows) lib.defineCMacro("HAVE_DLFCN_H", "1");

            // The Windows 10 SDK winrt/wrl/client.h is incompatible with clang due to #pragma pack usages
            // (unclear why), so instead we use the wrl/client.h headers from https://github.com/ziglang/zig/tree/225fe6ddbfae016395762850e0cd5c51f9e7751c/lib/libc/include/any-windows-any
            // which seem to work fine.
            if (target.result.os.tag == .windows and target.result.abi == .msvc) lib.addIncludePath(b.path("msvc/"));

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

            const dxh_sources = b.lazyDependency("directx-headers", .{}) orelse break :blk .{ .lib = lib, .lib_path = null };
            const dxc_sources = b.lazyDependency("DirectXShaderCompiler", .{}) orelse break :blk .{ .lib = lib, .lib_path = null };

            addConfigHeaders(b, lib);
            addIncludes(b, dxc_sources, dxh_sources, lib);

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

            // Link lazy-loaded SPIRV-Tools
            if (build_spirv) {
                lib.defineCMacro("ENABLE_SPIRV_CODEGEN", "");

                // Add clang SPIRV tooling sources
                lib.addCSourceFiles(.{
                    .files = &lib_spirv,
                    .flags = cppflags.items,
                    .root = dxc_sources.path("."),
                });

                if (b.lazyDependency("spirv-tools", .{
                    .target = target,
                    .optimize = optimize,
                })) |spirv_tools| {
                    if (b.lazyDependency("SPIRV-Headers", .{})) |spirv_headers|
                        addSPIRVIncludes(spirv_tools, spirv_headers, lib);

                    lib.linkLibrary(spirv_tools.artifact("spirv-opt"));
                }
            }

            lib.addCSourceFiles(.{
                .files = &cpp_sources,
                .flags = cppflags.items,
                .root = dxc_sources.path("."),
            });
            lib.addCSourceFiles(.{
                .files = &c_sources,
                .flags = cflags.items,
                .root = dxc_sources.path("."),
            });

            if (target.result.abi != .msvc) lib.defineCMacro("NDEBUG", ""); // disable assertions
            if (target.result.os.tag == .windows) {
                lib.defineCMacro("LLVM_ON_WIN32", "1");
                if (target.result.abi == .msvc) lib.defineCMacro("CINDEX_LINKAGE", "");
                lib.linkSystemLibrary("version");
            } else {
                lib.defineCMacro("LLVM_ON_UNIX", "1");
            }

            if (build_shared) {
                lib.defineCMacro("MACH_DXC_C_SHARED_LIBRARY", "");
                lib.defineCMacro("MACH_DXC_C_IMPLEMENTATION", "");
            }

            linkMachDxcDependencies(lib);
            lib.addIncludePath(b.path("src"));

            // TODO: investigate SSE2 #define / cmake option for CPU target
            //
            // TODO: investigate how projects/dxilconv/lib/DxbcConverter/DxbcConverterImpl.h is getting pulled
            // in, we can get rid of dxbc conversion presumably

            if (!skip_executables) {
                // dxc.exe builds
                const dxc_exe = b.addExecutable(.{
                    .name = "dxc",
                    .optimize = optimize,
                    .target = target,
                });
                const install_dxc_step = b.step("dxc", "Build and install dxc.exe");
                install_dxc_step.dependOn(&b.addInstallArtifact(dxc_exe, .{}).step);
                dxc_exe.addCSourceFile(.{
                    .file = dxc_sources.path("tools/clang/tools/dxc/dxcmain.cpp"),
                    .flags = &.{"-std=c++17"},
                });
                dxc_exe.defineCMacro("NDEBUG", ""); // disable assertions

                if (target.result.os.tag != .windows) dxc_exe.defineCMacro("HAVE_DLFCN_H", "1");
                dxc_exe.addIncludePath(dxc_sources.path("tools/clang/tools"));
                dxc_exe.addIncludePath(dxc_sources.path("include"));
                addConfigHeaders(b, dxc_exe);
                addIncludes(b, dxc_sources, dxh_sources, dxc_exe);
                dxc_exe.addCSourceFile(.{
                    .file = dxc_sources.path("tools/clang/tools/dxclib/dxc.cpp"),
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
                        dxc_exe.addLibraryPath(b.path(lib_dir_path));
                        // So instead we must copy the lib into this directory:
                        try std.fs.cwd().copyFile(lib_path, std.fs.cwd(), "atls.lib", .{});
                        try std.fs.cwd().copyFile(pdb_path, std.fs.cwd(), pdb_name, .{});
                        // This is probably a bug in the Zig linker.
                    }
                }
            }

            if (build_shared) buildShared(b, lib, optimize, target);

            break :blk .{ .lib = lib, .lib_path = null };
        }
    };

    if (skip_executables)
        return;

    // Zig bindings
    const mach_dxcompiler = b.addModule("mach-dxcompiler", .{
        .root_source_file = b.path("src/main.zig"),
        .target = target,
        .optimize = optimize,
    });
    mach_dxcompiler.addIncludePath(b.path("src"));

    mach_dxcompiler.linkLibrary(machdxcompiler.lib);

    if (machdxcompiler.lib_path) |p| mach_dxcompiler.addLibraryPath(.{ .cwd_relative = p });

    if (skip_tests)
        return;

    const main_tests = b.addTest(.{
        .name = "dxcompiler-tests",
        .root_source_file = b.path("src/main.zig"),
        .target = target,
        .optimize = optimize,
    });
    main_tests.addIncludePath(b.path("src"));
    main_tests.linkLibrary(machdxcompiler.lib);
    if (machdxcompiler.lib_path) |p| main_tests.addLibraryPath(.{ .cwd_relative = p });

    b.installArtifact(main_tests);
    const test_step = b.step("test", "Run library tests");
    test_step.dependOn(&b.addRunArtifact(main_tests).step);
}

fn buildShared(b: *Build, lib: *Build.Step.Compile, optimize: std.builtin.OptimizeMode, target: std.Build.ResolvedTarget) void {
    const sharedlib = b.addSharedLibrary(.{
        .name = "machdxcompiler-shared",
        .optimize = optimize,
        .target = target,
    });

    sharedlib.addCSourceFile(.{
        .file = b.path("src/shared_main.cpp"),
        .flags = &.{"-std=c++17"},
    });

    const shared_install_step = b.step("machdxcompiler", "Build and install the machdxcompiler shared library");
    shared_install_step.dependOn(&b.addInstallArtifact(sharedlib, .{}).step);

    b.installArtifact(sharedlib);
    sharedlib.linkLibrary(lib);
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
            .style = .{ .cmake = b.path("config-headers/tools/clang/include/clang/Config/config.h.cmake") },
            .include_path = "clang/Config/config.h",
        },
        .{
            .BUG_REPORT_URL = null,
            .CLANG_DEFAULT_OPENMP_RUNTIME = null,
            .CLANG_LIBDIR_SUFFIX = null,
            .CLANG_RESOURCE_DIR = null,
            .C_INCLUDE_DIRS = null,
            .DEFAULT_SYSROOT = null,
            .GCC_INSTALL_PREFIX = null,
            .CLANG_HAVE_LIBXML = 0,
            .BACKEND_PACKAGE_STRING = null,
            .HOST_LINK_VERSION = null,
        },
    ));

    // /include/llvm/Config/AsmParsers.def.in
    step.addConfigHeader(b.addConfigHeader(
        .{
            .style = .{ .cmake = b.path("config-headers/include/llvm/Config/AsmParsers.def.in") },
            .include_path = "llvm/Config/AsmParsers.def",
        },
        .{ .LLVM_ENUM_ASM_PARSERS = null },
    ));

    // /include/llvm/Config/Disassemblers.def.in
    step.addConfigHeader(b.addConfigHeader(
        .{
            .style = .{ .cmake = b.path("config-headers/include/llvm/Config/Disassemblers.def.in") },
            .include_path = "llvm/Config/Disassemblers.def",
        },
        .{ .LLVM_ENUM_DISASSEMBLERS = null },
    ));

    // /include/llvm/Config/Targets.def.in
    step.addConfigHeader(b.addConfigHeader(
        .{
            .style = .{ .cmake = b.path("config-headers/include/llvm/Config/Targets.def.in") },
            .include_path = "llvm/Config/Targets.def",
        },
        .{ .LLVM_ENUM_TARGETS = null },
    ));

    // /include/llvm/Config/AsmPrinters.def.in
    step.addConfigHeader(b.addConfigHeader(
        .{
            .style = .{ .cmake = b.path("config-headers/include/llvm/Config/AsmPrinters.def.in") },
            .include_path = "llvm/Config/AsmPrinters.def",
        },
        .{ .LLVM_ENUM_ASM_PRINTERS = null },
    ));

    // /include/llvm/Support/DataTypes.h.cmake
    step.addConfigHeader(b.addConfigHeader(
        .{
            .style = .{ .cmake = b.path("config-headers/include/llvm/Support/DataTypes.h.cmake") },
            .include_path = "llvm/Support/DataTypes.h",
        },
        .{
            .HAVE_INTTYPES_H = 1,
            .HAVE_STDINT_H = 1,
            .HAVE_U_INT64_T = 0,
            .HAVE_UINT64_T = 1,
        },
    ));

    // /include/llvm/Config/abi-breaking.h.cmake
    step.addConfigHeader(b.addConfigHeader(
        .{
            .style = .{ .cmake = b.path("config-headers/include/llvm/Config/abi-breaking.h.cmake") },
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
            .style = .{ .cmake = b.path("config-headers/include/dxc/config.h.cmake") },
            .include_path = "dxc/config.h",
        },
        .{
            .DXC_DISABLE_ALLOCATOR_OVERRIDES = false,
        },
    ));
}

fn addIncludes(b: *Build, dxc_sources: *std.Build.Dependency, dxh_sources: *std.Build.Dependency, step: *std.Build.Step.Compile) void {
    // TODO: replace unofficial external/DIA submodule with something else (or eliminate dep on it)
    if (b.lazyDependency("DIA", .{})) |dia| step.addIncludePath(dia.path("include"));
    // TODO: replace generated-include with logic to actually generate this code
    step.addIncludePath(b.path("generated-include/"));
    step.addIncludePath(dxc_sources.path("tools/clang/include"));
    step.addIncludePath(dxc_sources.path("include"));
    step.addIncludePath(dxc_sources.path("include/llvm"));
    step.addIncludePath(dxc_sources.path("include/llvm/llvm_assert"));
    step.addIncludePath(dxc_sources.path("include/llvm/Bitcode"));
    step.addIncludePath(dxc_sources.path("include/llvm/IR"));
    step.addIncludePath(dxc_sources.path("include/llvm/IRReader"));
    step.addIncludePath(dxc_sources.path("include/llvm/Linker"));
    step.addIncludePath(dxc_sources.path("include/llvm/Analysis"));
    step.addIncludePath(dxc_sources.path("include/llvm/Transforms"));
    step.addIncludePath(dxc_sources.path("include/llvm/Transforms/Utils"));
    step.addIncludePath(dxc_sources.path("include/llvm/Transforms/InstCombine"));
    step.addIncludePath(dxc_sources.path("include/llvm/Transforms/IPO"));
    step.addIncludePath(dxc_sources.path("include/llvm/Transforms/Scalar"));
    step.addIncludePath(dxc_sources.path("include/llvm/Transforms/Vectorize"));
    step.addIncludePath(dxc_sources.path("include/llvm/Target"));
    step.addIncludePath(dxc_sources.path("include/llvm/ProfileData"));
    step.addIncludePath(dxc_sources.path("include/llvm/Option"));
    step.addIncludePath(dxc_sources.path("include/llvm/PassPrinters"));
    step.addIncludePath(dxc_sources.path("include/llvm/Passes"));
    step.addIncludePath(dxc_sources.path("include/dxc"));
    step.addIncludePath(dxh_sources.path("include/directx"));

    const target = step.rootModuleTarget();
    if (target.os.tag != .windows) step.addIncludePath(dxh_sources.path("include/wsl/stubs"));
}

fn addSPIRVIncludes(
    spirv_tools: *std.Build.Dependency,
    spirv_headers: *std.Build.Dependency,
    step: *std.Build.Step.Compile,
) void {
    step.addIncludePath(spirv_tools.path("source"));
    step.addIncludePath(spirv_tools.path("include"));

    step.addIncludePath(spirv_headers.path("include"));
}

// /include/llvm/Config/llvm-config.h.cmake
// /include/llvm/Config/config.h.cmake (derives llvm-config.h.cmake)
fn addConfigHeaderLLVMConfig(b: *Build, target: std.Target, which: anytype) *std.Build.Step.ConfigHeader {
    // Note: LLVM_HOST_TRIPLEs can be found by running $ llc --version | grep Default
    // Note: arm64 is an alias for aarch64, we always use aarch64 over arm64.

    const LLVMConfigH = struct {
        LLVM_BINDIR: ?[]const u8 = null,
        LLVM_CONFIGTIME: ?[]const u8 = null,
        LLVM_DATADIR: ?[]const u8 = null,
        LLVM_DEFAULT_TARGET_TRIPLE: []const u8,
        LLVM_DOCSDIR: ?[]const u8 = null,
        LLVM_ENABLE_THREADS: ?i64 = null,
        LLVM_ETCDIR: ?[]const u8 = null,
        LLVM_HAS_ATOMICS: ?i64 = null,
        LLVM_HOST_TRIPLE: []const u8 = "",
        LLVM_INCLUDEDIR: ?[]const u8 = null,
        LLVM_INFODIR: ?[]const u8 = null,
        LLVM_MANDIR: ?[]const u8 = null,
        LLVM_NATIVE_ARCH: []const u8 = "",
        LLVM_ON_UNIX: ?i64 = null,
        LLVM_ON_WIN32: ?i64 = null,
        LLVM_PREFIX: []const u8,
        LLVM_VERSION_MAJOR: u8,
        LLVM_VERSION_MINOR: u8,
        LLVM_VERSION_PATCH: u8,
        PACKAGE_VERSION: []const u8,
    };

    var llvm_config_h: LLVMConfigH = .{
        .LLVM_PREFIX = "/usr/local",
        .LLVM_DEFAULT_TARGET_TRIPLE = "dxil-ms-dx",
        .LLVM_ENABLE_THREADS = 1,
        .LLVM_HAS_ATOMICS = 1,
        .LLVM_HOST_TRIPLE = "",
        .LLVM_VERSION_MAJOR = 3,
        .LLVM_VERSION_MINOR = 7,
        .LLVM_VERSION_PATCH = 0,
        .PACKAGE_VERSION = "3.7-v1.4.0.2274-1812-g84da60c6c-dirty",
    };

    if (target.os.tag == .windows) {
        llvm_config_h.LLVM_ON_WIN32 = 1;
        switch (target.abi) {
            .msvc => switch (target.cpu.arch) {
                .x86_64 => llvm_config_h.LLVM_HOST_TRIPLE = "x86_64-w64-msvc",
                .aarch64 => llvm_config_h.LLVM_HOST_TRIPLE = "aarch64-w64-msvc",
                else => @panic("target architecture not supported"),
            },
            .gnu => switch (target.cpu.arch) {
                .x86_64 => llvm_config_h.LLVM_HOST_TRIPLE = "x86_64-w64-mingw32",
                .aarch64 => llvm_config_h.LLVM_HOST_TRIPLE = "aarch64-w64-mingw32",
                else => @panic("target architecture not supported"),
            },
            else => @panic("target ABI not supported"),
        }
    } else if (target.os.tag.isDarwin()) {
        llvm_config_h.LLVM_ON_UNIX = 1;
        switch (target.cpu.arch) {
            .aarch64 => llvm_config_h.LLVM_HOST_TRIPLE = "aarch64-apple-darwin",
            .x86_64 => llvm_config_h.LLVM_HOST_TRIPLE = "x86_64-apple-darwin",
            else => @panic("target architecture not supported"),
        }
    } else {
        // Assume linux-like
        // TODO: musl support?
        llvm_config_h.LLVM_ON_UNIX = 1;
        switch (target.cpu.arch) {
            .aarch64 => llvm_config_h.LLVM_HOST_TRIPLE = "aarch64-linux-gnu",
            .x86_64 => llvm_config_h.LLVM_HOST_TRIPLE = "x86_64-linux-gnu",
            else => @panic("target architecture not supported"),
        }
    }

    const CONFIG_H = struct {
        BUG_REPORT_URL: []const u8 = "http://llvm.org/bugs/",
        ENABLE_BACKTRACES: []const u8 = "",
        ENABLE_CRASH_OVERRIDES: []const u8 = "",
        DISABLE_LLVM_DYLIB_ATEXIT: []const u8 = "",
        ENABLE_PIC: []const u8 = "",
        ENABLE_TIMESTAMPS: ?i64 = null,
        HAVE_DECL_ARC4RANDOM: ?i64 = null,
        HAVE_BACKTRACE: ?i64 = null,
        HAVE_CLOSEDIR: ?i64 = null,
        HAVE_CXXABI_H: ?i64 = null,
        HAVE_DECL_STRERROR_S: ?i64 = null,
        HAVE_DIRENT_H: ?i64 = null,
        HAVE_DIA_SDK: ?i64 = null,
        HAVE_DLERROR: ?i64 = null,
        HAVE_DLFCN_H: ?i64 = null,
        HAVE_DLOPEN: ?i64 = null,
        HAVE_ERRNO_H: ?i64 = null,
        HAVE_EXECINFO_H: ?i64 = null,
        HAVE_FCNTL_H: ?i64 = null,
        HAVE_FENV_H: ?i64 = null,
        HAVE_FFI_CALL: ?i64 = null,
        HAVE_FFI_FFI_H: ?i64 = null,
        HAVE_FFI_H: ?i64 = null,
        HAVE_FUTIMENS: ?i64 = null,
        HAVE_FUTIMES: ?i64 = null,
        HAVE_GETCWD: ?i64 = null,
        HAVE_GETPAGESIZE: ?i64 = null,
        HAVE_GETRLIMIT: ?i64 = null,
        HAVE_GETRUSAGE: ?i64 = null,
        HAVE_GETTIMEOFDAY: ?i64 = null,
        HAVE_INT64_T: ?i64 = null,
        HAVE_INTTYPES_H: ?i64 = null,
        HAVE_ISATTY: ?i64 = null,
        HAVE_LIBDL: ?i64 = null,
        HAVE_LIBEDIT: ?i64 = null,
        HAVE_LIBPSAPI: ?i64 = null,
        HAVE_LIBPTHREAD: ?i64 = null,
        HAVE_LIBSHELL32: ?i64 = null,
        HAVE_LIBZ: ?i64 = null,
        HAVE_LIMITS_H: ?i64 = null,
        HAVE_LINK_EXPORT_DYNAMIC: ?i64 = null,
        HAVE_LINK_H: ?i64 = null,
        HAVE_LONGJMP: ?i64 = null,
        HAVE_MACH_MACH_H: ?i64 = null,
        HAVE_MACH_O_DYLD_H: ?i64 = null,
        HAVE_MALLCTL: ?i64 = null,
        HAVE_MALLINFO: ?i64 = null,
        HAVE_MALLINFO2: ?i64 = null,
        HAVE_MALLOC_H: ?i64 = null,
        HAVE_MALLOC_MALLOC_H: ?i64 = null,
        HAVE_MALLOC_ZONE_STATISTICS: ?i64 = null,
        HAVE_MKDTEMP: ?i64 = null,
        HAVE_MKSTEMP: ?i64 = null,
        HAVE_MKTEMP: ?i64 = null,
        HAVE_NDIR_H: ?i64 = null,
        HAVE_OPENDIR: ?i64 = null,
        HAVE_POSIX_SPAWN: ?i64 = null,
        HAVE_PREAD: ?i64 = null,
        HAVE_PTHREAD_GETSPECIFIC: ?i64 = null,
        HAVE_PTHREAD_H: ?i64 = null,
        HAVE_PTHREAD_MUTEX_LOCK: ?i64 = null,
        HAVE_PTHREAD_RWLOCK_INIT: ?i64 = null,
        HAVE_RAND48: ?i64 = null,
        HAVE_READDIR: ?i64 = null,
        HAVE_REALPATH: ?i64 = null,
        HAVE_SBRK: ?i64 = null,
        HAVE_SETENV: ?i64 = null,
        HAVE_SETJMP: ?i64 = null,
        HAVE_SETRLIMIT: ?i64 = null,
        HAVE_SIGLONGJMP: ?i64 = null,
        HAVE_SIGNAL_H: ?i64 = null,
        HAVE_SIGSETJMP: ?i64 = null,
        HAVE_STDINT_H: ?i64 = null,
        HAVE_STRDUP: ?i64 = null,
        HAVE_STRERROR_R: ?i64 = null,
        HAVE_STRERROR: ?i64 = null,
        HAVE_STRTOLL: ?i64 = null,
        HAVE_STRTOQ: ?i64 = null,
        HAVE_SYS_DIR_H: ?i64 = null,
        HAVE_SYS_IOCTL_H: ?i64 = null,
        HAVE_SYS_MMAN_H: ?i64 = null,
        HAVE_SYS_NDIR_H: ?i64 = null,
        HAVE_SYS_PARAM_H: ?i64 = null,
        HAVE_SYS_RESOURCE_H: ?i64 = null,
        HAVE_SYS_STAT_H: ?i64 = null,
        HAVE_SYS_TIME_H: ?i64 = null,
        HAVE_SYS_TYPES_H: ?i64 = null,
        HAVE_SYS_UIO_H: ?i64 = null,
        HAVE_SYS_WAIT_H: ?i64 = null,
        HAVE_TERMINFO: ?i64 = null,
        HAVE_TERMIOS_H: ?i64 = null,
        HAVE_UINT64_T: ?i64 = null,
        HAVE_UNISTD_H: ?i64 = null,
        HAVE_UTIME_H: ?i64 = null,
        HAVE_U_INT64_T: ?i64 = null,
        HAVE_VALGRIND_VALGRIND_H: ?i64 = null,
        HAVE_WRITEV: ?i64 = null,
        HAVE_ZLIB_H: ?i64 = null,
        HAVE__ALLOCA: ?i64 = null,
        HAVE___ALLOCA: ?i64 = null,
        HAVE___ASHLDI3: ?i64 = null,
        HAVE___ASHRDI3: ?i64 = null,
        HAVE___CHKSTK: ?i64 = null,
        HAVE___CHKSTK_MS: ?i64 = null,
        HAVE___CMPDI2: ?i64 = null,
        HAVE___DIVDI3: ?i64 = null,
        HAVE___FIXDFDI: ?i64 = null,
        HAVE___FIXSFDI: ?i64 = null,
        HAVE___FLOATDIDF: ?i64 = null,
        HAVE___LSHRDI3: ?i64 = null,
        HAVE___MAIN: ?i64 = null,
        HAVE___MODDI3: ?i64 = null,
        HAVE___UDIVDI3: ?i64 = null,
        HAVE___UMODDI3: ?i64 = null,
        HAVE____CHKSTK: ?i64 = null,
        HAVE____CHKSTK_MS: ?i64 = null,
        LLVM_BINDIR: ?[]const u8 = null,
        LLVM_CONFIGTIME: ?[]const u8 = null,
        LLVM_DATADIR: ?[]const u8 = null,
        LLVM_DEFAULT_TARGET_TRIPLE: []const u8,
        LLVM_DOCSDIR: ?[]const u8 = null,
        LLVM_ENABLE_THREADS: ?i64 = null,
        LLVM_ENABLE_ZLIB: ?i64 = null,
        LLVM_ETCDIR: ?[]const u8 = null,
        LLVM_HAS_ATOMICS: ?i64 = null,
        LLVM_HOST_TRIPLE: []const u8 = "",
        LLVM_INCLUDEDIR: ?[]const u8 = null,
        LLVM_INFODIR: ?[]const u8 = null,
        LLVM_MANDIR: ?[]const u8 = null,
        LLVM_NATIVE_ARCH: []const u8 = "",
        LLVM_ON_UNIX: ?i64 = null,
        LLVM_ON_WIN32: ?i64 = null,
        LLVM_PREFIX: []const u8,
        LLVM_VERSION_MAJOR: u8,
        LLVM_VERSION_MINOR: u8,
        LLVM_VERSION_PATCH: u8,

        // LTDL_... isn't an i64, but we don't use them and I am unsure
        // what type is more appropriate.
        LTDL_DLOPEN_DEPLIBS: ?i64 = null,
        LTDL_SHLIB_EXT: ?i64 = null,
        LTDL_SYSSEARCHPATH: ?i64 = null,

        PACKAGE_BUGREPORT: []const u8 = "http://llvm.org/bugs/",
        PACKAGE_NAME: []const u8 = "LLVM",
        PACKAGE_STRING: []const u8 = "LLVM 3.7-v1.4.0.2274-1812-g84da60c6c-dirty",
        PACKAGE_VERSION: []const u8,
        RETSIGTYPE: []const u8 = "void",
        WIN32_ELMCB_PCSTR: []const u8 = "PCSTR",

        // str... isn't an i64, but we don't use them and I am unsure
        // what type is more appropriate. Perhaps a function pointer?
        strtoll: ?i64 = null,
        strtoull: ?i64 = null,
        stricmp: ?i64 = null,
        strdup: ?i64 = null,

        HAVE__CHSIZE_S: ?i64 = null,
    };

    const tag = target.os.tag;
    const if_windows: ?i64 = if (tag == .windows) 1 else null;
    const if_not_windows: ?i64 = if (tag == .windows) null else 1;
    const if_windows_or_linux: ?i64 = if (tag == .windows and !tag.isDarwin()) 1 else null;
    const if_darwin: ?i64 = if (tag.isDarwin()) 1 else null;
    const if_not_msvc: ?i64 = if (target.abi != .msvc) 1 else null;
    const config_h = CONFIG_H{
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
        .HAVE_SYS_MMAN_H = if_not_windows,

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

        .LLVM_DEFAULT_TARGET_TRIPLE = llvm_config_h.LLVM_DEFAULT_TARGET_TRIPLE,
        .LLVM_ENABLE_THREADS = llvm_config_h.LLVM_ENABLE_THREADS,
        .LLVM_ENABLE_ZLIB = 0,
        .LLVM_HAS_ATOMICS = llvm_config_h.LLVM_HAS_ATOMICS,
        .LLVM_HOST_TRIPLE = llvm_config_h.LLVM_HOST_TRIPLE,
        .LLVM_ON_UNIX = llvm_config_h.LLVM_ON_UNIX,
        .LLVM_ON_WIN32 = llvm_config_h.LLVM_ON_WIN32,
        .LLVM_PREFIX = llvm_config_h.LLVM_PREFIX,
        .LLVM_VERSION_MAJOR = llvm_config_h.LLVM_VERSION_MAJOR,
        .LLVM_VERSION_MINOR = llvm_config_h.LLVM_VERSION_MINOR,
        .LLVM_VERSION_PATCH = llvm_config_h.LLVM_VERSION_PATCH,
        .PACKAGE_VERSION = llvm_config_h.PACKAGE_VERSION,

        .HAVE__CHSIZE_S = 1,
    };

    return switch (which) {
        .llvm_config_h => b.addConfigHeader(.{
            .style = .{ .cmake = b.path("config-headers/include/llvm/Config/llvm-config.h.cmake") },
            .include_path = "llvm/Config/llvm-config.h",
        }, llvm_config_h),
        .config_h => b.addConfigHeader(.{
            .style = .{ .cmake = b.path("config-headers/include/llvm/Config/config.h.cmake") },
            .include_path = "llvm/Config/config.h",
        }, config_h),
        else => unreachable,
    };
}

fn ensureCommandExists(allocator: std.mem.Allocator, name: []const u8, exist_check: []const u8) bool {
    const result = std.process.Child.run(.{
        .allocator = allocator,
        .argv = &[_][]const u8{ name, exist_check },
        .cwd = ".",
    }) catch // e.g. FileNotFound
        {
        return false;
    };

    defer {
        allocator.free(result.stderr);
        allocator.free(result.stdout);
    }

    if (result.term.Exited != 0)
        return false;

    return true;
}

// ------------------------------------------
// Source cloning logic
// ------------------------------------------

fn ensureGitRepoCloned(allocator: std.mem.Allocator, clone_url: []const u8, revision: []const u8, dir: []const u8) !void {
    if (isEnvVarTruthy(allocator, "NO_ENSURE_SUBMODULES") or isEnvVarTruthy(allocator, "NO_ENSURE_GIT")) {
        return;
    }

    ensureGit(allocator);

    if (std.fs.cwd().openDir(dir, .{})) |_| {
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
    const result = try std.process.Child.run(.{ .allocator = allocator, .argv = &.{ "git", "rev-parse", "HEAD" }, .cwd = cwd });
    allocator.free(result.stderr);
    if (result.stdout.len > 0) return result.stdout[0 .. result.stdout.len - 1]; // trim newline
    return result.stdout;
}

// Command validation logic moved to ensureCommandExists()
fn ensureGit(allocator: std.mem.Allocator) void {
    if (!ensureCommandExists(allocator, "git", "--version")) {
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

    var child = std.process.Child.init(argv, allocator);
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
    const a_fields = @typeInfo(a).@"struct".fields;
    const b_fields = @typeInfo(b).@"struct".fields;

    return @Type(std.builtin.Type{
        .@"struct" = .{
            .layout = .auto,
            .fields = a_fields ++ b_fields,
            .decls = &.{},
            .is_tuple = false,
        },
    });
}

// Merge struct values A and B
fn merge(a: anytype, b: anytype) Merge(@TypeOf(a), @TypeOf(b)) {
    var merged: Merge(@TypeOf(a), @TypeOf(b)) = undefined;
    inline for (@typeInfo(@TypeOf(merged)).@"struct".fields) |f| {
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

fn binaryZigTriple(arena: std.mem.Allocator, target: std.Target) ![]const u8 {
    // Craft a zig_triple string that we will use to create the binary download URL. Remove OS
    // version range / glibc version from triple, as we don't include that in our download URL.
    var binary_target = std.Target.Query.fromTarget(target);
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
                .name = "download mach-dxcompiler prebuilt binary",
                .owner = b,
                .makeFn = &make,
            }),
            .b = b,
        };
        return download_step;
    }

    fn make(step_ptr: *std.Build.Step, make_options: Build.Step.MakeOptions) anyerror!void {
        _ = make_options;
        const download_step: *DownloadBinaryStep = @fieldParentPtr("step", step_ptr);
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
    var diagnostics: std.tar.Diagnostics = .{ .allocator = gpa };
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
                .components_outside_stripped_prefix => |info| {
                    log.err("file '{s}' contains components outside of stripped prefix", .{info.file_name});
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
    "tools/clang/lib/Lex/MacroInfo.cpp",
    "tools/clang/lib/Lex/Preprocessor.cpp",
    "tools/clang/lib/Lex/PPExpressions.cpp",
    "tools/clang/lib/Lex/PreprocessorLexer.cpp",
    "tools/clang/lib/Lex/HeaderSearch.cpp",
    "tools/clang/lib/Lex/PPDirectives.cpp",
    "tools/clang/lib/Lex/ScratchBuffer.cpp",
    "tools/clang/lib/Lex/ModuleMap.cpp",
    "tools/clang/lib/Lex/TokenLexer.cpp",
    "tools/clang/lib/Lex/Lexer.cpp",
    "tools/clang/lib/Lex/HLSLMacroExpander.cpp",
    "tools/clang/lib/Lex/PTHLexer.cpp",
    "tools/clang/lib/Lex/PPCallbacks.cpp",
    "tools/clang/lib/Lex/Pragma.cpp",
    "tools/clang/lib/Lex/PPCaching.cpp",
    "tools/clang/lib/Lex/PreprocessingRecord.cpp",
    "tools/clang/lib/Lex/PPMacroExpansion.cpp",
    "tools/clang/lib/Lex/HeaderMap.cpp",
    "tools/clang/lib/Lex/LiteralSupport.cpp",
    "tools/clang/lib/Lex/PPLexerChange.cpp",
    "tools/clang/lib/Lex/TokenConcatenation.cpp",
    "tools/clang/lib/Lex/PPConditionalDirectiveRecord.cpp",
    "tools/clang/lib/Lex/MacroArgs.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/Basic | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_basic_sources = [_][]const u8{
    "tools/clang/lib/Basic/OpenMPKinds.cpp",
    "tools/clang/lib/Basic/TargetInfo.cpp",
    "tools/clang/lib/Basic/LangOptions.cpp",
    "tools/clang/lib/Basic/Warnings.cpp",
    "tools/clang/lib/Basic/Builtins.cpp",
    "tools/clang/lib/Basic/DiagnosticOptions.cpp",
    "tools/clang/lib/Basic/Module.cpp",
    "tools/clang/lib/Basic/Version.cpp",
    "tools/clang/lib/Basic/IdentifierTable.cpp",
    "tools/clang/lib/Basic/TokenKinds.cpp",
    "tools/clang/lib/Basic/ObjCRuntime.cpp",
    "tools/clang/lib/Basic/SourceManager.cpp",
    "tools/clang/lib/Basic/VersionTuple.cpp",
    "tools/clang/lib/Basic/FileSystemStatCache.cpp",
    "tools/clang/lib/Basic/FileManager.cpp",
    "tools/clang/lib/Basic/CharInfo.cpp",
    "tools/clang/lib/Basic/OperatorPrecedence.cpp",
    "tools/clang/lib/Basic/SanitizerBlacklist.cpp",
    "tools/clang/lib/Basic/VirtualFileSystem.cpp",
    "tools/clang/lib/Basic/DiagnosticIDs.cpp",
    "tools/clang/lib/Basic/Diagnostic.cpp",
    "tools/clang/lib/Basic/Targets.cpp",
    "tools/clang/lib/Basic/Attributes.cpp",
    "tools/clang/lib/Basic/SourceLocation.cpp",
    "tools/clang/lib/Basic/Sanitizers.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/Driver | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_driver_sources = [_][]const u8{
    "tools/clang/lib/Driver/Job.cpp",
    "tools/clang/lib/Driver/ToolChains.cpp",
    "tools/clang/lib/Driver/DriverOptions.cpp",
    "tools/clang/lib/Driver/Types.cpp",
    "tools/clang/lib/Driver/MinGWToolChain.cpp",
    "tools/clang/lib/Driver/Phases.cpp",
    "tools/clang/lib/Driver/MSVCToolChain.cpp",
    "tools/clang/lib/Driver/Compilation.cpp",
    "tools/clang/lib/Driver/Driver.cpp",
    "tools/clang/lib/Driver/Multilib.cpp",
    "tools/clang/lib/Driver/Tools.cpp",
    "tools/clang/lib/Driver/SanitizerArgs.cpp",
    "tools/clang/lib/Driver/Tool.cpp",
    "tools/clang/lib/Driver/Action.cpp",
    "tools/clang/lib/Driver/CrossWindowsToolChain.cpp",
    "tools/clang/lib/Driver/ToolChain.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/Analysis | grep -v 'CocoaConventions.cpp' | grep -v 'FormatString.cpp' | grep -v 'PrintfFormatString.cpp' | grep -v 'ScanfFormatString.cpp' | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_analysis_sources = [_][]const u8{
    "tools/clang/lib/Analysis/ReachableCode.cpp",
    "tools/clang/lib/Analysis/ThreadSafetyLogical.cpp",
    "tools/clang/lib/Analysis/ThreadSafetyCommon.cpp",
    "tools/clang/lib/Analysis/CFG.cpp",
    "tools/clang/lib/Analysis/BodyFarm.cpp",
    "tools/clang/lib/Analysis/ThreadSafety.cpp",
    "tools/clang/lib/Analysis/UninitializedValues.cpp",
    "tools/clang/lib/Analysis/CFGReachabilityAnalysis.cpp",
    "tools/clang/lib/Analysis/Dominators.cpp",
    "tools/clang/lib/Analysis/PseudoConstantAnalysis.cpp",
    "tools/clang/lib/Analysis/AnalysisDeclContext.cpp",
    "tools/clang/lib/Analysis/LiveVariables.cpp",
    "tools/clang/lib/Analysis/CallGraph.cpp",
    "tools/clang/lib/Analysis/PostOrderCFGView.cpp",
    "tools/clang/lib/Analysis/ProgramPoint.cpp",
    "tools/clang/lib/Analysis/ObjCNoReturn.cpp",
    "tools/clang/lib/Analysis/ThreadSafetyTIL.cpp",
    "tools/clang/lib/Analysis/CFGStmtMap.cpp",
    "tools/clang/lib/Analysis/Consumed.cpp",
    "tools/clang/lib/Analysis/CodeInjector.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/Index | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_index_sources = [_][]const u8{
    "tools/clang/lib/Index/CommentToXML.cpp",
    "tools/clang/lib/Index/USRGeneration.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/Parse | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_parse_sources = [_][]const u8{
    "tools/clang/lib/Parse/ParseExprCXX.cpp",
    "tools/clang/lib/Parse/ParseTemplate.cpp",
    "tools/clang/lib/Parse/ParseDeclCXX.cpp",
    "tools/clang/lib/Parse/ParseInit.cpp",
    "tools/clang/lib/Parse/ParseOpenMP.cpp",
    "tools/clang/lib/Parse/HLSLRootSignature.cpp",
    "tools/clang/lib/Parse/ParseObjc.cpp",
    "tools/clang/lib/Parse/ParseDecl.cpp",
    "tools/clang/lib/Parse/ParseExpr.cpp",
    "tools/clang/lib/Parse/ParseHLSL.cpp",
    "tools/clang/lib/Parse/ParseCXXInlineMethods.cpp",
    "tools/clang/lib/Parse/ParseStmtAsm.cpp",
    "tools/clang/lib/Parse/ParseStmt.cpp",
    "tools/clang/lib/Parse/ParsePragma.cpp",
    "tools/clang/lib/Parse/Parser.cpp",
    "tools/clang/lib/Parse/ParseAST.cpp",
    "tools/clang/lib/Parse/ParseTentative.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/AST | grep -v 'NSAPI.cpp' | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_ast_sources = [_][]const u8{
    "tools/clang/lib/AST/ExprConstant.cpp",
    "tools/clang/lib/AST/ExprCXX.cpp",
    "tools/clang/lib/AST/CommentCommandTraits.cpp",
    "tools/clang/lib/AST/Mangle.cpp",
    "tools/clang/lib/AST/ASTDiagnostic.cpp",
    "tools/clang/lib/AST/CommentParser.cpp",
    "tools/clang/lib/AST/AttrImpl.cpp",
    "tools/clang/lib/AST/ASTDumper.cpp",
    "tools/clang/lib/AST/DeclOpenMP.cpp",
    "tools/clang/lib/AST/ASTTypeTraits.cpp",
    "tools/clang/lib/AST/ASTImporter.cpp",
    "tools/clang/lib/AST/StmtPrinter.cpp",
    "tools/clang/lib/AST/CommentBriefParser.cpp",
    "tools/clang/lib/AST/APValue.cpp",
    "tools/clang/lib/AST/ASTConsumer.cpp",
    "tools/clang/lib/AST/DeclCXX.cpp",
    "tools/clang/lib/AST/Stmt.cpp",
    "tools/clang/lib/AST/CommentSema.cpp",
    "tools/clang/lib/AST/HlslTypes.cpp",
    "tools/clang/lib/AST/ASTContextHLSL.cpp",
    "tools/clang/lib/AST/InheritViz.cpp",
    "tools/clang/lib/AST/Expr.cpp",
    "tools/clang/lib/AST/RecordLayout.cpp",
    "tools/clang/lib/AST/StmtIterator.cpp",
    "tools/clang/lib/AST/ExprClassification.cpp",
    "tools/clang/lib/AST/DeclPrinter.cpp",
    "tools/clang/lib/AST/DeclBase.cpp",
    "tools/clang/lib/AST/StmtProfile.cpp",
    "tools/clang/lib/AST/Comment.cpp",
    "tools/clang/lib/AST/VTTBuilder.cpp",
    "tools/clang/lib/AST/Decl.cpp",
    "tools/clang/lib/AST/SelectorLocationsKind.cpp",
    "tools/clang/lib/AST/TypeLoc.cpp",
    "tools/clang/lib/AST/DeclarationName.cpp",
    "tools/clang/lib/AST/DeclObjC.cpp",
    "tools/clang/lib/AST/VTableBuilder.cpp",
    "tools/clang/lib/AST/CommentLexer.cpp",
    "tools/clang/lib/AST/StmtViz.cpp",
    "tools/clang/lib/AST/DeclTemplate.cpp",
    "tools/clang/lib/AST/CXXInheritance.cpp",
    "tools/clang/lib/AST/RecordLayoutBuilder.cpp",
    "tools/clang/lib/AST/RawCommentList.cpp",
    "tools/clang/lib/AST/TemplateBase.cpp",
    "tools/clang/lib/AST/HlslBuiltinTypeDeclBuilder.cpp",
    "tools/clang/lib/AST/DeclFriend.cpp",
    "tools/clang/lib/AST/ItaniumMangle.cpp",
    "tools/clang/lib/AST/ASTContext.cpp",
    "tools/clang/lib/AST/TemplateName.cpp",
    "tools/clang/lib/AST/ParentMap.cpp",
    "tools/clang/lib/AST/ItaniumCXXABI.cpp",
    "tools/clang/lib/AST/NestedNameSpecifier.cpp",
    "tools/clang/lib/AST/MicrosoftMangle.cpp",
    "tools/clang/lib/AST/DeclGroup.cpp",
    "tools/clang/lib/AST/Type.cpp",
    "tools/clang/lib/AST/ExternalASTSource.cpp",
    "tools/clang/lib/AST/TypePrinter.cpp",
    "tools/clang/lib/AST/MicrosoftCXXABI.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/Edit | grep -v 'RewriteObjCFoundationAPI.cpp' | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_edit_sources = [_][]const u8{
    "tools/clang/lib/Edit/EditedSource.cpp",
    "tools/clang/lib/Edit/Commit.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/Sema | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_sema_sources = [_][]const u8{
    "tools/clang/lib/Sema/SemaDXR.cpp",
    "tools/clang/lib/Sema/CodeCompleteConsumer.cpp",
    "tools/clang/lib/Sema/SemaOverload.cpp",
    "tools/clang/lib/Sema/SemaLambda.cpp",
    "tools/clang/lib/Sema/SemaTemplateDeduction.cpp",
    "tools/clang/lib/Sema/MultiplexExternalSemaSource.cpp",
    "tools/clang/lib/Sema/IdentifierResolver.cpp",
    "tools/clang/lib/Sema/TypeLocBuilder.cpp",
    "tools/clang/lib/Sema/SemaCUDA.cpp",
    "tools/clang/lib/Sema/SemaTemplateInstantiate.cpp",
    "tools/clang/lib/Sema/SemaTemplate.cpp",
    "tools/clang/lib/Sema/DelayedDiagnostic.cpp",
    "tools/clang/lib/Sema/SemaTemplateInstantiateDecl.cpp",
    "tools/clang/lib/Sema/SemaDeclCXX.cpp",
    "tools/clang/lib/Sema/ScopeInfo.cpp",
    "tools/clang/lib/Sema/SemaStmtAttr.cpp",
    "tools/clang/lib/Sema/SemaChecking.cpp",
    "tools/clang/lib/Sema/SemaCast.cpp",
    "tools/clang/lib/Sema/SemaInit.cpp",
    "tools/clang/lib/Sema/SemaType.cpp",
    "tools/clang/lib/Sema/SemaDeclAttr.cpp",
    "tools/clang/lib/Sema/SemaOpenMP.cpp",
    "tools/clang/lib/Sema/SemaFixItUtils.cpp",
    "tools/clang/lib/Sema/SemaTemplateVariadic.cpp",
    "tools/clang/lib/Sema/SemaExprCXX.cpp",
    "tools/clang/lib/Sema/Scope.cpp",
    "tools/clang/lib/Sema/DeclSpec.cpp",
    "tools/clang/lib/Sema/SemaLookup.cpp",
    "tools/clang/lib/Sema/SemaPseudoObject.cpp",
    "tools/clang/lib/Sema/AttributeList.cpp",
    "tools/clang/lib/Sema/SemaDeclObjC.cpp",
    "tools/clang/lib/Sema/SemaCXXScopeSpec.cpp",
    "tools/clang/lib/Sema/SemaExprMember.cpp",
    "tools/clang/lib/Sema/SemaAccess.cpp",
    "tools/clang/lib/Sema/SemaStmt.cpp",
    "tools/clang/lib/Sema/SemaCodeComplete.cpp",
    "tools/clang/lib/Sema/SemaExprObjC.cpp",
    "tools/clang/lib/Sema/SemaAttr.cpp",
    "tools/clang/lib/Sema/SemaStmtAsm.cpp",
    "tools/clang/lib/Sema/SemaExpr.cpp",
    "tools/clang/lib/Sema/JumpDiagnostics.cpp",
    "tools/clang/lib/Sema/SemaHLSL.cpp",
    "tools/clang/lib/Sema/SemaObjCProperty.cpp",
    "tools/clang/lib/Sema/SemaConsumer.cpp",
    "tools/clang/lib/Sema/SemaDecl.cpp",
    "tools/clang/lib/Sema/SemaExceptionSpec.cpp",
    "tools/clang/lib/Sema/Sema.cpp",
    "tools/clang/lib/Sema/AnalysisBasedWarnings.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/CodeGen | grep -v 'CGObjCGNU.cpp' | grep -v 'CGObjCMac.cpp' | grep -v 'CGObjCRuntime.cpp' | grep -v 'CGOpenCLRuntime.cpp' | grep -v 'CGOpenMPRuntime.cpp' | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_codegen_sources = [_][]const u8{
    "tools/clang/lib/CodeGen/ObjectFilePCHContainerOperations.cpp",
    "tools/clang/lib/CodeGen/CGHLSLMSFinishCodeGen.cpp",
    "tools/clang/lib/CodeGen/CGDeclCXX.cpp",
    "tools/clang/lib/CodeGen/SanitizerMetadata.cpp",
    "tools/clang/lib/CodeGen/CGDecl.cpp",
    "tools/clang/lib/CodeGen/TargetInfo.cpp",
    "tools/clang/lib/CodeGen/CGCall.cpp",
    "tools/clang/lib/CodeGen/CGVTables.cpp",
    "tools/clang/lib/CodeGen/CGExprScalar.cpp",
    "tools/clang/lib/CodeGen/CGBlocks.cpp",
    "tools/clang/lib/CodeGen/CGExpr.cpp",
    "tools/clang/lib/CodeGen/CodeGenPGO.cpp",
    "tools/clang/lib/CodeGen/CGStmtOpenMP.cpp",
    "tools/clang/lib/CodeGen/CGExprCXX.cpp",
    "tools/clang/lib/CodeGen/BackendUtil.cpp",
    "tools/clang/lib/CodeGen/CGAtomic.cpp",
    "tools/clang/lib/CodeGen/CGCUDARuntime.cpp",
    "tools/clang/lib/CodeGen/CGHLSLRootSignature.cpp",
    "tools/clang/lib/CodeGen/CodeGenAction.cpp",
    "tools/clang/lib/CodeGen/CGStmt.cpp",
    "tools/clang/lib/CodeGen/CodeGenABITypes.cpp",
    "tools/clang/lib/CodeGen/CGClass.cpp",
    "tools/clang/lib/CodeGen/CGException.cpp",
    "tools/clang/lib/CodeGen/CGHLSLRuntime.cpp",
    "tools/clang/lib/CodeGen/CGExprComplex.cpp",
    "tools/clang/lib/CodeGen/CGExprConstant.cpp",
    "tools/clang/lib/CodeGen/ModuleBuilder.cpp",
    "tools/clang/lib/CodeGen/CodeGenTypes.cpp",
    "tools/clang/lib/CodeGen/CGCUDANV.cpp",
    "tools/clang/lib/CodeGen/CGRecordLayoutBuilder.cpp",
    "tools/clang/lib/CodeGen/CoverageMappingGen.cpp",
    "tools/clang/lib/CodeGen/CGExprAgg.cpp",
    "tools/clang/lib/CodeGen/CGVTT.cpp",
    "tools/clang/lib/CodeGen/CGCXX.cpp",
    "tools/clang/lib/CodeGen/CGCleanup.cpp",
    "tools/clang/lib/CodeGen/CGHLSLMS.cpp",
    "tools/clang/lib/CodeGen/CodeGenFunction.cpp",
    "tools/clang/lib/CodeGen/ItaniumCXXABI.cpp",
    "tools/clang/lib/CodeGen/CGDebugInfo.cpp",
    "tools/clang/lib/CodeGen/CGCXXABI.cpp",
    "tools/clang/lib/CodeGen/CGObjC.cpp",
    "tools/clang/lib/CodeGen/CodeGenModule.cpp",
    "tools/clang/lib/CodeGen/CGBuiltin.cpp",
    "tools/clang/lib/CodeGen/CodeGenTBAA.cpp",
    "tools/clang/lib/CodeGen/CGLoopInfo.cpp",
    "tools/clang/lib/CodeGen/MicrosoftCXXABI.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/ASTMatchers | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_astmatchers_sources = [_][]const u8{
    "tools/clang/lib/ASTMatchers/Dynamic/Diagnostics.cpp",
    "tools/clang/lib/ASTMatchers/Dynamic/Registry.cpp",
    "tools/clang/lib/ASTMatchers/Dynamic/VariantValue.cpp",
    "tools/clang/lib/ASTMatchers/Dynamic/Parser.cpp",
    "tools/clang/lib/ASTMatchers/ASTMatchersInternal.cpp",
    "tools/clang/lib/ASTMatchers/ASTMatchFinder.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/Tooling/Core | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_tooling_core_sources = [_][]const u8{
    "tools/clang/lib/Tooling/Core/Replacement.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/Tooling | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_tooling_sources = [_][]const u8{
    "tools/clang/lib/Tooling/JSONCompilationDatabase.cpp",
    "tools/clang/lib/Tooling/FileMatchTrie.cpp",
    "tools/clang/lib/Tooling/Core/Replacement.cpp",
    "tools/clang/lib/Tooling/RefactoringCallbacks.cpp",
    "tools/clang/lib/Tooling/CommonOptionsParser.cpp",
    "tools/clang/lib/Tooling/CompilationDatabase.cpp",
    "tools/clang/lib/Tooling/ArgumentsAdjusters.cpp",
    "tools/clang/lib/Tooling/Refactoring.cpp",
    "tools/clang/lib/Tooling/Tooling.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/Format | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_format_sources = [_][]const u8{
    "tools/clang/lib/Format/FormatToken.cpp",
    "tools/clang/lib/Format/ContinuationIndenter.cpp",
    "tools/clang/lib/Format/Format.cpp",
    "tools/clang/lib/Format/UnwrappedLineFormatter.cpp",
    "tools/clang/lib/Format/WhitespaceManager.cpp",
    "tools/clang/lib/Format/BreakableToken.cpp",
    "tools/clang/lib/Format/TokenAnnotator.cpp",
    "tools/clang/lib/Format/UnwrappedLineParser.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/Rewrite | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_rewrite_sources = [_][]const u8{
    "tools/clang/lib/Rewrite/HTMLRewrite.cpp",
    "tools/clang/lib/Rewrite/RewriteRope.cpp",
    "tools/clang/lib/Rewrite/DeltaTree.cpp",
    "tools/clang/lib/Rewrite/TokenRewriter.cpp",
    "tools/clang/lib/Rewrite/Rewriter.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/lib/Frontend | grep -v 'RewriteModernObjC.cpp' | grep -v 'ChainedIncludesSource.cpp' | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_lib_frontend_sources = [_][]const u8{
    "tools/clang/lib/Frontend/ASTConsumers.cpp",
    "tools/clang/lib/Frontend/InitPreprocessor.cpp",
    "tools/clang/lib/Frontend/FrontendActions.cpp",
    "tools/clang/lib/Frontend/InitHeaderSearch.cpp",
    "tools/clang/lib/Frontend/ASTMerge.cpp",
    "tools/clang/lib/Frontend/Rewrite/RewriteMacros.cpp",
    "tools/clang/lib/Frontend/Rewrite/FixItRewriter.cpp",
    "tools/clang/lib/Frontend/Rewrite/InclusionRewriter.cpp",
    "tools/clang/lib/Frontend/Rewrite/RewriteTest.cpp",
    "tools/clang/lib/Frontend/Rewrite/FrontendActions_rewrite.cpp",
    "tools/clang/lib/Frontend/Rewrite/RewriteObjC.cpp",
    "tools/clang/lib/Frontend/Rewrite/HTMLPrint.cpp",
    "tools/clang/lib/Frontend/DependencyGraph.cpp",
    "tools/clang/lib/Frontend/FrontendAction.cpp",
    "tools/clang/lib/Frontend/MultiplexConsumer.cpp",
    "tools/clang/lib/Frontend/TextDiagnostic.cpp",
    "tools/clang/lib/Frontend/ModuleDependencyCollector.cpp",
    "tools/clang/lib/Frontend/DiagnosticRenderer.cpp",
    "tools/clang/lib/Frontend/CompilerInvocation.cpp",
    "tools/clang/lib/Frontend/CreateInvocationFromCommandLine.cpp",
    "tools/clang/lib/Frontend/PCHContainerOperations.cpp",
    "tools/clang/lib/Frontend/TextDiagnosticPrinter.cpp",
    "tools/clang/lib/Frontend/CodeGenOptions.cpp",
    "tools/clang/lib/Frontend/HeaderIncludeGen.cpp",
    "tools/clang/lib/Frontend/ASTUnit.cpp",
    "tools/clang/lib/Frontend/ChainedDiagnosticConsumer.cpp",
    "tools/clang/lib/Frontend/SerializedDiagnosticPrinter.cpp",
    "tools/clang/lib/Frontend/LayoutOverrideSource.cpp",
    "tools/clang/lib/Frontend/CacheTokens.cpp",
    "tools/clang/lib/Frontend/FrontendOptions.cpp",
    "tools/clang/lib/Frontend/LangStandards.cpp",
    "tools/clang/lib/Frontend/TextDiagnosticBuffer.cpp",
    "tools/clang/lib/Frontend/PrintPreprocessedOutput.cpp",
    "tools/clang/lib/Frontend/DependencyFile.cpp",
    "tools/clang/lib/Frontend/SerializedDiagnosticReader.cpp",
    "tools/clang/lib/Frontend/VerifyDiagnosticConsumer.cpp",
    "tools/clang/lib/Frontend/CompilerInstance.cpp",
    "tools/clang/lib/Frontend/LogDiagnosticPrinter.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/tools/libclang | grep -v 'ARCMigrate.cpp' | grep -v 'BuildSystem.cpp' | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_tools_libclang_sources = [_][]const u8{
    "tools/clang/tools/libclang/dxcisenseimpl.cpp",
    "tools/clang/tools/libclang/IndexBody.cpp",
    "tools/clang/tools/libclang/CIndexCXX.cpp",
    "tools/clang/tools/libclang/CIndexer.cpp",
    "tools/clang/tools/libclang/IndexingContext.cpp",
    "tools/clang/tools/libclang/CXLoadedDiagnostic.cpp",
    "tools/clang/tools/libclang/Indexing.cpp",
    "tools/clang/tools/libclang/CXCursor.cpp",
    "tools/clang/tools/libclang/dxcrewriteunused.cpp",
    "tools/clang/tools/libclang/CXCompilationDatabase.cpp",
    "tools/clang/tools/libclang/CIndexInclusionStack.cpp",
    "tools/clang/tools/libclang/CXStoredDiagnostic.cpp",
    "tools/clang/tools/libclang/CIndexHigh.cpp",
    "tools/clang/tools/libclang/CXType.cpp",
    "tools/clang/tools/libclang/CIndex.cpp",
    "tools/clang/tools/libclang/CIndexCodeCompletion.cpp",
    "tools/clang/tools/libclang/IndexTypeSourceInfo.cpp",
    "tools/clang/tools/libclang/CIndexDiagnostic.cpp",
    "tools/clang/tools/libclang/CXString.cpp",
    "tools/clang/tools/libclang/IndexDecl.cpp",
    "tools/clang/tools/libclang/CXComment.cpp",
    "tools/clang/tools/libclang/CXSourceLocation.cpp",
    "tools/clang/tools/libclang/CIndexUSRs.cpp",
};

// find libs/DirectXShaderCompiler/tools/clang/tools/dxcompiler | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const tools_clang_tools_dxcompiler_sources = [_][]const u8{
    "tools/clang/tools/dxcompiler/MachSiegbertVogtDXCSA.cpp",
    "tools/clang/tools/dxcompiler/dxcdisassembler.cpp",
    "tools/clang/tools/dxcompiler/dxcvalidator.cpp",
    "tools/clang/tools/dxcompiler/dxillib.cpp",
    "tools/clang/tools/dxcompiler/dxcfilesystem.cpp",
    "tools/clang/tools/dxcompiler/DXCompiler.cpp",
    "tools/clang/tools/dxcompiler/dxcutil.cpp",
    "tools/clang/tools/dxcompiler/dxclinker.cpp",
    "tools/clang/tools/dxcompiler/dxcshadersourceinfo.cpp",
    "tools/clang/tools/dxcompiler/dxcassembler.cpp",
    "tools/clang/tools/dxcompiler/dxcapi.cpp",
    "tools/clang/tools/dxcompiler/dxclibrary.cpp",
    "tools/clang/tools/dxcompiler/dxcpdbutils.cpp",
    "tools/clang/tools/dxcompiler/dxcompilerobj.cpp",
};

// find libs/DirectXShaderCompiler/lib/Bitcode/Reader | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_bitcode_reader_sources = [_][]const u8{
    "lib/Bitcode/Reader/BitReader.cpp",
    "lib/Bitcode/Reader/BitstreamReader.cpp",
    "lib/Bitcode/Reader/BitcodeReader.cpp",
};

// find libs/DirectXShaderCompiler/lib/Bitcode/Writer | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_bitcode_writer_sources = [_][]const u8{
    "lib/Bitcode/Writer/BitcodeWriterPass.cpp",
    "lib/Bitcode/Writer/BitWriter.cpp",
    "lib/Bitcode/Writer/ValueEnumerator.cpp",
    "lib/Bitcode/Writer/BitcodeWriter.cpp",
};

// find libs/DirectXShaderCompiler/lib/IR | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_ir_sources = [_][]const u8{
    "lib/IR/DebugInfoMetadata.cpp",
    "lib/IR/GCOV.cpp",
    "lib/IR/IRBuilder.cpp",
    "lib/IR/Pass.cpp",
    "lib/IR/AutoUpgrade.cpp",
    "lib/IR/Core.cpp",
    "lib/IR/InlineAsm.cpp",
    "lib/IR/Module.cpp",
    "lib/IR/GVMaterializer.cpp",
    "lib/IR/Operator.cpp",
    "lib/IR/DataLayout.cpp",
    "lib/IR/IntrinsicInst.cpp",
    "lib/IR/DebugLoc.cpp",
    "lib/IR/Dominators.cpp",
    "lib/IR/Constants.cpp",
    "lib/IR/PassRegistry.cpp",
    "lib/IR/DiagnosticPrinter.cpp",
    "lib/IR/ValueSymbolTable.cpp",
    "lib/IR/Globals.cpp",
    "lib/IR/ConstantRange.cpp",
    "lib/IR/LegacyPassManager.cpp",
    "lib/IR/Function.cpp",
    "lib/IR/TypeFinder.cpp",
    "lib/IR/DebugInfo.cpp",
    "lib/IR/LLVMContextImpl.cpp",
    "lib/IR/Verifier.cpp",
    "lib/IR/Comdat.cpp",
    "lib/IR/Value.cpp",
    "lib/IR/Use.cpp",
    "lib/IR/MetadataTracking.cpp",
    "lib/IR/Mangler.cpp",
    "lib/IR/DiagnosticInfo.cpp",
    "lib/IR/ValueTypes.cpp",
    "lib/IR/DIBuilder.cpp",
    "lib/IR/User.cpp",
    "lib/IR/MDBuilder.cpp",
    "lib/IR/Metadata.cpp",
    "lib/IR/BasicBlock.cpp",
    "lib/IR/Instruction.cpp",
    "lib/IR/AsmWriter.cpp",
    "lib/IR/Statepoint.cpp",
    "lib/IR/LLVMContext.cpp",
    "lib/IR/Instructions.cpp",
    "lib/IR/PassManager.cpp",
    "lib/IR/ConstantFold.cpp",
    "lib/IR/IRPrintingPasses.cpp",
    "lib/IR/Attributes.cpp",
    "lib/IR/Type.cpp",
};

// find libs/DirectXShaderCompiler/lib/IRReader | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_irreader_sources = [_][]const u8{
    "lib/IRReader/IRReader.cpp",
};

// find libs/DirectXShaderCompiler/lib/Linker | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_linker_sources = [_][]const u8{
    "lib/Linker/LinkModules.cpp",
};

// find libs/DirectXShaderCompiler/lib/AsmParser | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_asmparser_sources = [_][]const u8{
    "lib/AsmParser/LLParser.cpp",
    "lib/AsmParser/LLLexer.cpp",
    "lib/AsmParser/Parser.cpp",
};

// find libs/DirectXShaderCompiler/lib/Analysis | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_analysis_sources = [_][]const u8{
    "lib/Analysis/regioninfo.cpp",
    "lib/Analysis/DxilConstantFolding.cpp",
    "lib/Analysis/CGSCCPassManager.cpp",
    "lib/Analysis/DxilValueCache.cpp",
    "lib/Analysis/AliasSetTracker.cpp",
    "lib/Analysis/LoopPass.cpp",
    "lib/Analysis/MemDerefPrinter.cpp",
    "lib/Analysis/regionprinter.cpp",
    "lib/Analysis/DominanceFrontier.cpp",
    "lib/Analysis/Loads.cpp",
    "lib/Analysis/BlockFrequencyInfoImpl.cpp",
    "lib/Analysis/Analysis.cpp",
    "lib/Analysis/ReducibilityAnalysis.cpp",
    "lib/Analysis/CodeMetrics.cpp",
    "lib/Analysis/TargetTransformInfo.cpp",
    "lib/Analysis/CFG.cpp",
    "lib/Analysis/SparsePropagation.cpp",
    "lib/Analysis/IntervalPartition.cpp",
    "lib/Analysis/ScalarEvolutionNormalization.cpp",
    "lib/Analysis/CFGPrinter.cpp",
    "lib/Analysis/IPA/IPA.cpp",
    "lib/Analysis/IPA/GlobalsModRef.cpp",
    "lib/Analysis/IPA/InlineCost.cpp",
    "lib/Analysis/IPA/CallGraph.cpp",
    "lib/Analysis/IPA/CallGraphSCCPass.cpp",
    "lib/Analysis/IPA/CallPrinter.cpp",
    "lib/Analysis/Lint.cpp",
    "lib/Analysis/ScalarEvolution.cpp",
    "lib/Analysis/MemoryDependenceAnalysis.cpp",
    "lib/Analysis/PostDominators.cpp",
    "lib/Analysis/TypeBasedAliasAnalysis.cpp",
    "lib/Analysis/DxilSimplify.cpp",
    "lib/Analysis/DivergenceAnalysis.cpp",
    "lib/Analysis/BlockFrequencyInfo.cpp",
    "lib/Analysis/VectorUtils.cpp",
    "lib/Analysis/Delinearization.cpp",
    "lib/Analysis/AssumptionCache.cpp",
    "lib/Analysis/AliasAnalysisEvaluator.cpp",
    "lib/Analysis/IVUsers.cpp",
    "lib/Analysis/ValueTracking.cpp",
    "lib/Analysis/PHITransAddr.cpp",
    "lib/Analysis/NoAliasAnalysis.cpp",
    "lib/Analysis/AliasDebugger.cpp",
    "lib/Analysis/DependenceAnalysis.cpp",
    "lib/Analysis/LibCallSemantics.cpp",
    "lib/Analysis/DomPrinter.cpp",
    "lib/Analysis/Trace.cpp",
    "lib/Analysis/LazyValueInfo.cpp",
    "lib/Analysis/ConstantFolding.cpp",
    "lib/Analysis/LoopAccessAnalysis.cpp",
    "lib/Analysis/BranchProbabilityInfo.cpp",
    "lib/Analysis/TargetLibraryInfo.cpp",
    "lib/Analysis/CaptureTracking.cpp",
    "lib/Analysis/IteratedDominanceFrontier.cpp",
    "lib/Analysis/MemoryLocation.cpp",
    "lib/Analysis/InstructionSimplify.cpp",
    "lib/Analysis/VectorUtils2.cpp",
    "lib/Analysis/MemDepPrinter.cpp",
    "lib/Analysis/InstCount.cpp",
    "lib/Analysis/CostModel.cpp",
    "lib/Analysis/DxilConstantFoldingExt.cpp",
    "lib/Analysis/ScopedNoAliasAA.cpp",
    "lib/Analysis/ModuleDebugInfoPrinter.cpp",
    "lib/Analysis/LibCallAliasAnalysis.cpp",
    "lib/Analysis/MemoryBuiltins.cpp",
    "lib/Analysis/PtrUseVisitor.cpp",
    "lib/Analysis/AliasAnalysisCounter.cpp",
    "lib/Analysis/ScalarEvolutionAliasAnalysis.cpp",
    "lib/Analysis/BasicAliasAnalysis.cpp",
    "lib/Analysis/ScalarEvolutionExpander.cpp",
    "lib/Analysis/LoopInfo.cpp",
    "lib/Analysis/CFLAliasAnalysis.cpp",
    "lib/Analysis/Interval.cpp",
    "lib/Analysis/RegionPass.cpp",
    "lib/Analysis/LazyCallGraph.cpp",
    "lib/Analysis/AliasAnalysis.cpp",
};

// find libs/DirectXShaderCompiler/lib/MSSupport | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_mssupport_sources = [_][]const u8{
    "lib/MSSupport/MSFileSystemImpl.cpp",
};

// find libs/DirectXShaderCompiler/lib/Transforms/Utils | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_transforms_utils_sources = [_][]const u8{
    "lib/Transforms/Utils/LoopUtils.cpp",
    "lib/Transforms/Utils/DemoteRegToStack.cpp",
    "lib/Transforms/Utils/Utils.cpp",
    "lib/Transforms/Utils/SimplifyCFG.cpp",
    "lib/Transforms/Utils/LoopSimplifyId.cpp",
    "lib/Transforms/Utils/UnifyFunctionExitNodes.cpp",
    "lib/Transforms/Utils/SSAUpdater.cpp",
    "lib/Transforms/Utils/SimplifyIndVar.cpp",
    "lib/Transforms/Utils/BasicBlockUtils.cpp",
    "lib/Transforms/Utils/ASanStackFrameLayout.cpp",
    "lib/Transforms/Utils/FlattenCFG.cpp",
    "lib/Transforms/Utils/CmpInstAnalysis.cpp",
    "lib/Transforms/Utils/ModuleUtils.cpp",
    "lib/Transforms/Utils/LoopUnroll.cpp",
    "lib/Transforms/Utils/LowerSwitch.cpp",
    "lib/Transforms/Utils/LoopVersioning.cpp",
    "lib/Transforms/Utils/AddDiscriminators.cpp",
    "lib/Transforms/Utils/Local.cpp",
    "lib/Transforms/Utils/PromoteMemoryToRegister.cpp",
    "lib/Transforms/Utils/LCSSA.cpp",
    "lib/Transforms/Utils/BypassSlowDivision.cpp",
    "lib/Transforms/Utils/Mem2Reg.cpp",
    "lib/Transforms/Utils/CodeExtractor.cpp",
    "lib/Transforms/Utils/InlineFunction.cpp",
    "lib/Transforms/Utils/LoopSimplify.cpp",
    "lib/Transforms/Utils/SimplifyLibCalls.cpp",
    "lib/Transforms/Utils/MetaRenamer.cpp",
    "lib/Transforms/Utils/CloneModule.cpp",
    "lib/Transforms/Utils/IntegerDivision.cpp",
    "lib/Transforms/Utils/LoopUnrollRuntime.cpp",
    "lib/Transforms/Utils/ValueMapper.cpp",
    "lib/Transforms/Utils/InstructionNamer.cpp",
    "lib/Transforms/Utils/CtorUtils.cpp",
    "lib/Transforms/Utils/GlobalStatus.cpp",
    "lib/Transforms/Utils/LowerInvoke.cpp",
    "lib/Transforms/Utils/SimplifyInstructions.cpp",
    "lib/Transforms/Utils/BuildLibCalls.cpp",
    "lib/Transforms/Utils/SymbolRewriter.cpp",
    "lib/Transforms/Utils/BreakCriticalEdges.cpp",
    "lib/Transforms/Utils/CloneFunction.cpp",
};

// find libs/DirectXShaderCompiler/lib/Transforms/InstCombine | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_transforms_instcombine_sources = [_][]const u8{
    "lib/Transforms/InstCombine/InstCombineCasts.cpp",
    "lib/Transforms/InstCombine/InstCombineCompares.cpp",
    "lib/Transforms/InstCombine/InstCombineSelect.cpp",
    "lib/Transforms/InstCombine/InstCombineCalls.cpp",
    "lib/Transforms/InstCombine/InstCombineSimplifyDemanded.cpp",
    "lib/Transforms/InstCombine/InstCombineAddSub.cpp",
    "lib/Transforms/InstCombine/InstructionCombining.cpp",
    "lib/Transforms/InstCombine/InstCombineMulDivRem.cpp",
    "lib/Transforms/InstCombine/InstCombineLoadStoreAlloca.cpp",
    "lib/Transforms/InstCombine/InstCombineShifts.cpp",
    "lib/Transforms/InstCombine/InstCombineVectorOps.cpp",
    "lib/Transforms/InstCombine/InstCombineAndOrXor.cpp",
    "lib/Transforms/InstCombine/InstCombinePHI.cpp",
};

// find libs/DirectXShaderCompiler/lib/Transforms/IPO | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_transforms_ipo_sources = [_][]const u8{
    "lib/Transforms/IPO/ExtractGV.cpp",
    "lib/Transforms/IPO/GlobalDCE.cpp",
    "lib/Transforms/IPO/PruneEH.cpp",
    "lib/Transforms/IPO/MergeFunctions.cpp",
    "lib/Transforms/IPO/IPConstantPropagation.cpp",
    "lib/Transforms/IPO/ConstantMerge.cpp",
    "lib/Transforms/IPO/FunctionAttrs.cpp",
    "lib/Transforms/IPO/BarrierNoopPass.cpp",
    "lib/Transforms/IPO/StripSymbols.cpp",
    "lib/Transforms/IPO/Internalize.cpp",
    "lib/Transforms/IPO/StripDeadPrototypes.cpp",
    "lib/Transforms/IPO/DeadArgumentElimination.cpp",
    "lib/Transforms/IPO/ArgumentPromotion.cpp",
    "lib/Transforms/IPO/PassManagerBuilder.cpp",
    "lib/Transforms/IPO/LoopExtractor.cpp",
    "lib/Transforms/IPO/Inliner.cpp",
    "lib/Transforms/IPO/InlineAlways.cpp",
    "lib/Transforms/IPO/LowerBitSets.cpp",
    "lib/Transforms/IPO/InlineSimple.cpp",
    "lib/Transforms/IPO/PartialInlining.cpp",
    "lib/Transforms/IPO/ElimAvailExtern.cpp",
    "lib/Transforms/IPO/IPO.cpp",
    "lib/Transforms/IPO/GlobalOpt.cpp",
};

// find libs/DirectXShaderCompiler/lib/Transforms/Scalar | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_transforms_scalar_sources = [_][]const u8{
    "lib/Transforms/Scalar/LoopRotation.cpp",
    "lib/Transforms/Scalar/LoopInstSimplify.cpp",
    "lib/Transforms/Scalar/ConstantProp.cpp",
    "lib/Transforms/Scalar/StructurizeCFG.cpp",
    "lib/Transforms/Scalar/IndVarSimplify.cpp",
    "lib/Transforms/Scalar/FlattenCFGPass.cpp",
    "lib/Transforms/Scalar/PartiallyInlineLibCalls.cpp",
    "lib/Transforms/Scalar/Scalarizer.cpp",
    "lib/Transforms/Scalar/ADCE.cpp",
    "lib/Transforms/Scalar/SCCP.cpp",
    "lib/Transforms/Scalar/InductiveRangeCheckElimination.cpp",
    "lib/Transforms/Scalar/LoopDistribute.cpp",
    "lib/Transforms/Scalar/Sink.cpp",
    "lib/Transforms/Scalar/DxilEliminateVector.cpp",
    "lib/Transforms/Scalar/CorrelatedValuePropagation.cpp",
    "lib/Transforms/Scalar/EarlyCSE.cpp",
    "lib/Transforms/Scalar/LoopUnrollPass.cpp",
    "lib/Transforms/Scalar/DxilLoopUnroll.cpp",
    "lib/Transforms/Scalar/GVN.cpp",
    "lib/Transforms/Scalar/ConstantHoisting.cpp",
    "lib/Transforms/Scalar/DxilEraseDeadRegion.cpp",
    "lib/Transforms/Scalar/Scalar.cpp",
    "lib/Transforms/Scalar/LoopInterchange.cpp",
    "lib/Transforms/Scalar/JumpThreading.cpp",
    "lib/Transforms/Scalar/Reg2MemHLSL.cpp",
    "lib/Transforms/Scalar/Reg2Mem.cpp",
    "lib/Transforms/Scalar/HoistConstantArray.cpp",
    "lib/Transforms/Scalar/ScalarReplAggregates.cpp",
    "lib/Transforms/Scalar/LoadCombine.cpp",
    "lib/Transforms/Scalar/SeparateConstOffsetFromGEP.cpp",
    "lib/Transforms/Scalar/Reassociate.cpp",
    "lib/Transforms/Scalar/LoopIdiomRecognize.cpp",
    "lib/Transforms/Scalar/SampleProfile.cpp",
    "lib/Transforms/Scalar/DeadStoreElimination.cpp",
    "lib/Transforms/Scalar/SimplifyCFGPass.cpp",
    "lib/Transforms/Scalar/LoopStrengthReduce.cpp",
    "lib/Transforms/Scalar/DxilRemoveDeadBlocks.cpp",
    "lib/Transforms/Scalar/LoopRerollPass.cpp",
    "lib/Transforms/Scalar/LowerAtomic.cpp",
    "lib/Transforms/Scalar/MemCpyOptimizer.cpp",
    "lib/Transforms/Scalar/BDCE.cpp",
    "lib/Transforms/Scalar/LowerExpectIntrinsic.cpp",
    "lib/Transforms/Scalar/DxilFixConstArrayInitializer.cpp",
    "lib/Transforms/Scalar/ScalarReplAggregatesHLSL.cpp",
    "lib/Transforms/Scalar/Float2Int.cpp",
    "lib/Transforms/Scalar/LoopDeletion.cpp",
    "lib/Transforms/Scalar/SROA.cpp",
    "lib/Transforms/Scalar/MergedLoadStoreMotion.cpp",
    "lib/Transforms/Scalar/DCE.cpp",
    "lib/Transforms/Scalar/AlignmentFromAssumptions.cpp",
    "lib/Transforms/Scalar/DxilRemoveUnstructuredLoopExits.cpp",
    "lib/Transforms/Scalar/SpeculativeExecution.cpp",
    "lib/Transforms/Scalar/NaryReassociate.cpp",
    "lib/Transforms/Scalar/LoopUnswitch.cpp",
    "lib/Transforms/Scalar/RewriteStatepointsForGC.cpp",
    "lib/Transforms/Scalar/LICM.cpp",
    "lib/Transforms/Scalar/DxilConditionalMem2Reg.cpp",
    "lib/Transforms/Scalar/PlaceSafepoints.cpp",
    "lib/Transforms/Scalar/LowerTypePasses.cpp",
    "lib/Transforms/Scalar/TailRecursionElimination.cpp",
    "lib/Transforms/Scalar/StraightLineStrengthReduce.cpp",
};

// find libs/DirectXShaderCompiler/lib/Transforms/Vectorize | grep -v 'BBVectorize.cpp' | grep -v 'LoopVectorize.cpp' | grep -v 'LPVectorizer.cpp' | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_transforms_vectorize_sources = [_][]const u8{
    "lib/Transforms/Vectorize/Vectorize.cpp",
};

// find libs/DirectXShaderCompiler/lib/Target | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_target_sources = [_][]const u8{
    "lib/Target/TargetSubtargetInfo.cpp",
    "lib/Target/TargetLoweringObjectFile.cpp",
    "lib/Target/Target.cpp",
    "lib/Target/TargetRecip.cpp",
    "lib/Target/TargetMachine.cpp",
    "lib/Target/TargetIntrinsicInfo.cpp",
    "lib/Target/TargetMachineC.cpp",
};

// find libs/DirectXShaderCompiler/lib/ProfileData | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_profiledata_sources = [_][]const u8{
    "lib/ProfileData/InstrProfReader.cpp",
    "lib/ProfileData/CoverageMappingWriter.cpp",
    "lib/ProfileData/CoverageMapping.cpp",
    "lib/ProfileData/InstrProfWriter.cpp",
    "lib/ProfileData/CoverageMappingReader.cpp",
    "lib/ProfileData/SampleProfWriter.cpp",
    "lib/ProfileData/SampleProf.cpp",
    "lib/ProfileData/InstrProf.cpp",
    "lib/ProfileData/SampleProfReader.cpp",
};

// find libs/DirectXShaderCompiler/lib/Option | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_option_sources = [_][]const u8{
    "lib/Option/Arg.cpp",
    "lib/Option/OptTable.cpp",
    "lib/Option/Option.cpp",
    "lib/Option/ArgList.cpp",
};

// find libs/DirectXShaderCompiler/lib/PassPrinters | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_passprinters_sources = [_][]const u8{
    "lib/PassPrinters/PassPrinters.cpp",
};

// find libs/DirectXShaderCompiler/lib/Passes | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_passes_sources = [_][]const u8{
    "lib/Passes/PassBuilder.cpp",
};

// find libs/DirectXShaderCompiler/lib/HLSL | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_hlsl_sources = [_][]const u8{
    "lib/HLSL/HLLegalizeParameter.cpp",
    "lib/HLSL/HLOperations.cpp",
    "lib/HLSL/DxilExportMap.cpp",
    "lib/HLSL/DxilPrecisePropagatePass.cpp",
    "lib/HLSL/DxilPatchShaderRecordBindings.cpp",
    "lib/HLSL/HLUtil.cpp",
    "lib/HLSL/DxilCondenseResources.cpp",
    "lib/HLSL/DxilValidation.cpp",
    "lib/HLSL/DxilDeleteRedundantDebugValues.cpp",
    "lib/HLSL/DxilNoops.cpp",
    "lib/HLSL/ComputeViewIdState.cpp",
    "lib/HLSL/HLMatrixType.cpp",
    "lib/HLSL/DxilPackSignatureElement.cpp",
    "lib/HLSL/DxilLegalizeSampleOffsetPass.cpp",
    "lib/HLSL/HLModule.cpp",
    "lib/HLSL/DxilContainerReflection.cpp",
    "lib/HLSL/DxilLegalizeEvalOperations.cpp",
    "lib/HLSL/ControlDependence.cpp",
    "lib/HLSL/DxilTargetTransformInfo.cpp",
    "lib/HLSL/HLOperationLower.cpp",
    "lib/HLSL/DxilSignatureValidation.cpp",
    "lib/HLSL/DxilRenameResourcesPass.cpp",
    "lib/HLSL/DxilPromoteResourcePasses.cpp",
    "lib/HLSL/PauseResumePasses.cpp",
    "lib/HLSL/HLDeadFunctionElimination.cpp",
    "lib/HLSL/DxilExpandTrigIntrinsics.cpp",
    "lib/HLSL/DxilPoisonValues.cpp",
    "lib/HLSL/DxilGenerationPass.cpp",
    "lib/HLSL/DxilTranslateRawBuffer.cpp",
    "lib/HLSL/ComputeViewIdStateBuilder.cpp",
    "lib/HLSL/DxilTargetLowering.cpp",
    "lib/HLSL/DxilNoOptLegalize.cpp",
    "lib/HLSL/HLExpandStoreIntrinsics.cpp",
    "lib/HLSL/HLMetadataPasses.cpp",
    "lib/HLSL/DxilPreparePasses.cpp",
    "lib/HLSL/HLMatrixBitcastLowerPass.cpp",
    "lib/HLSL/HLPreprocess.cpp",
    "lib/HLSL/HLSignatureLower.cpp",
    "lib/HLSL/HLMatrixLowerPass.cpp",
    "lib/HLSL/HLResource.cpp",
    "lib/HLSL/HLLowerUDT.cpp",
    "lib/HLSL/HLOperationLowerExtension.cpp",
    "lib/HLSL/DxilEliminateOutputDynamicIndexing.cpp",
    "lib/HLSL/DxilSimpleGVNHoist.cpp",
    "lib/HLSL/DxcOptimizer.cpp",
    "lib/HLSL/DxilLinker.cpp",
    "lib/HLSL/DxilConvergent.cpp",
    "lib/HLSL/DxilLoopDeletion.cpp",
    "lib/HLSL/WaveSensitivityAnalysis.cpp",
    "lib/HLSL/DxilPreserveAllOutputs.cpp",
    "lib/HLSL/HLMatrixSubscriptUseReplacer.cpp",
};

// find libs/DirectXShaderCompiler/lib/Support | grep -v 'DynamicLibrary.cpp' | grep -v 'PluginLoader.cpp' | grep -v '\.inc\.cpp' | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_support_cpp_sources = [_][]const u8{
    "lib/Support/BranchProbability.cpp",
    "lib/Support/Memory.cpp",
    "lib/Support/ToolOutputFile.cpp",
    "lib/Support/YAMLTraits.cpp",
    "lib/Support/MD5.cpp",
    "lib/Support/Mutex.cpp",
    "lib/Support/Program.cpp",
    "lib/Support/APFloat.cpp",
    "lib/Support/SpecialCaseList.cpp",
    "lib/Support/LEB128.cpp",
    "lib/Support/FileOutputBuffer.cpp",
    "lib/Support/Process.cpp",
    "lib/Support/regmalloc.cpp",
    "lib/Support/ScaledNumber.cpp",
    "lib/Support/Locale.cpp",
    "lib/Support/TimeProfiler.cpp",
    "lib/Support/FileUtilities.cpp",
    "lib/Support/TimeValue.cpp",
    "lib/Support/TargetRegistry.cpp",
    "lib/Support/Statistic.cpp",
    "lib/Support/Twine.cpp",
    "lib/Support/DAGDeltaAlgorithm.cpp",
    "lib/Support/APSInt.cpp",
    "lib/Support/SearchForAddressOfSpecialSymbol.cpp",
    "lib/Support/LineIterator.cpp",
    "lib/Support/PrettyStackTrace.cpp",
    "lib/Support/Timer.cpp",
    "lib/Support/ConvertUTFWrapper.cpp",
    "lib/Support/LockFileManager.cpp",
    "lib/Support/assert.cpp",
    "lib/Support/ARMBuildAttrs.cpp",
    "lib/Support/CrashRecoveryContext.cpp",
    "lib/Support/Options.cpp",
    "lib/Support/DeltaAlgorithm.cpp",
    "lib/Support/SystemUtils.cpp",
    "lib/Support/ThreadLocal.cpp",
    "lib/Support/YAMLParser.cpp",
    "lib/Support/StringPool.cpp",
    "lib/Support/IntrusiveRefCntPtr.cpp",
    "lib/Support/Watchdog.cpp",
    "lib/Support/StringRef.cpp",
    "lib/Support/Compression.cpp",
    "lib/Support/COM.cpp",
    "lib/Support/FoldingSet.cpp",
    "lib/Support/FormattedStream.cpp",
    "lib/Support/BlockFrequency.cpp",
    "lib/Support/IntervalMap.cpp",
    "lib/Support/MemoryObject.cpp",
    "lib/Support/TargetParser.cpp",
    "lib/Support/raw_os_ostream.cpp",
    "lib/Support/Allocator.cpp",
    "lib/Support/DataExtractor.cpp",
    "lib/Support/APInt.cpp",
    "lib/Support/StreamingMemoryObject.cpp",
    "lib/Support/circular_raw_ostream.cpp",
    "lib/Support/DataStream.cpp",
    "lib/Support/Debug.cpp",
    "lib/Support/Errno.cpp",
    "lib/Support/Path.cpp",
    "lib/Support/raw_ostream.cpp",
    "lib/Support/Atomic.cpp",
    "lib/Support/SmallVector.cpp",
    "lib/Support/MathExtras.cpp",
    "lib/Support/MemoryBuffer.cpp",
    "lib/Support/ErrorHandling.cpp",
    "lib/Support/StringExtras.cpp",
    "lib/Support/Triple.cpp",
    "lib/Support/Hashing.cpp",
    "lib/Support/GraphWriter.cpp",
    "lib/Support/RandomNumberGenerator.cpp",
    "lib/Support/SourceMgr.cpp",
    "lib/Support/Signals.cpp",
    "lib/Support/Dwarf.cpp",
    "lib/Support/StringMap.cpp",
    "lib/Support/MSFileSystemBasic.cpp",
    "lib/Support/IntEqClasses.cpp",
    "lib/Support/Threading.cpp",
    "lib/Support/RWMutex.cpp",
    "lib/Support/StringSaver.cpp",
    "lib/Support/CommandLine.cpp",
    "lib/Support/ManagedStatic.cpp",
    "lib/Support/Host.cpp",
    "lib/Support/Unicode.cpp",
    "lib/Support/SmallPtrSet.cpp",
    "lib/Support/Valgrind.cpp",
    "lib/Support/Regex.cpp",
    "lib/Support/ARMWinEH.cpp",
};

// find libs/DirectXShaderCompiler/lib/Support | grep '\.c$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_support_c_sources = [_][]const u8{
    "lib/Support/ConvertUTF.c",
    "lib/Support/regexec.c",
    "lib/Support/regcomp.c",
    "lib/Support/regerror.c",
    "lib/Support/regstrlcpy.c",
    "lib/Support/regfree.c",
};

// find libs/DirectXShaderCompiler/lib/DxcSupport | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_dxcsupport_sources = [_][]const u8{
    "lib/DxcSupport/WinIncludes.cpp",
    "lib/DxcSupport/HLSLOptions.cpp",
    "lib/DxcSupport/dxcmem.cpp",
    "lib/DxcSupport/WinFunctions.cpp",
    "lib/DxcSupport/Global.cpp",
    "lib/DxcSupport/Unicode.cpp",
    "lib/DxcSupport/FileIOHelper.cpp",
    "lib/DxcSupport/dxcapi.use.cpp",
    "lib/DxcSupport/WinAdapter.cpp",
};

// find libs/DirectXShaderCompiler/lib/DxcBindingTable | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_dxcbindingtable_sources = [_][]const u8{
    "lib/DxcBindingTable/DxcBindingTable.cpp",
};

// find libs/DirectXShaderCompiler/lib/DXIL | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_dxil_sources = [_][]const u8{
    "lib/DXIL/DxilInterpolationMode.cpp",
    "lib/DXIL/DxilCompType.cpp",
    "lib/DXIL/DxilShaderFlags.cpp",
    "lib/DXIL/DxilResourceBase.cpp",
    "lib/DXIL/DxilResource.cpp",
    "lib/DXIL/DxilOperations.cpp",
    "lib/DXIL/DxilSignature.cpp",
    "lib/DXIL/DxilResourceProperties.cpp",
    "lib/DXIL/DxilPDB.cpp",
    "lib/DXIL/DxilUtilDbgInfoAndMisc.cpp",
    "lib/DXIL/DxilSignatureElement.cpp",
    "lib/DXIL/DxilSemantic.cpp",
    "lib/DXIL/DxilSampler.cpp",
    "lib/DXIL/DxilModuleHelper.cpp",
    "lib/DXIL/DxilResourceBinding.cpp",
    "lib/DXIL/DxilTypeSystem.cpp",
    "lib/DXIL/DxilCounters.cpp",
    "lib/DXIL/DxilCBuffer.cpp",
    "lib/DXIL/DxilUtil.cpp",
    "lib/DXIL/DxilSubobject.cpp",
    "lib/DXIL/DxilShaderModel.cpp",
    "lib/DXIL/DxilMetadataHelper.cpp",
    "lib/DXIL/DxilModule.cpp",
};

// find libs/DirectXShaderCompiler/lib/DxilContainer | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_dxilcontainer_sources = [_][]const u8{
    "lib/DxilContainer/DxilRuntimeReflection.cpp",
    "lib/DxilContainer/DxilRDATBuilder.cpp",
    "lib/DxilContainer/RDATDumper.cpp",
    "lib/DxilContainer/DxilContainerReader.cpp",
    "lib/DxilContainer/D3DReflectionStrings.cpp",
    "lib/DxilContainer/DxilContainer.cpp",
    "lib/DxilContainer/RDATDxilSubobjects.cpp",
    "lib/DxilContainer/D3DReflectionDumper.cpp",
    "lib/DxilContainer/DxcContainerBuilder.cpp",
    "lib/DxilContainer/DxilContainerAssembler.cpp",
};

// find libs/DirectXShaderCompiler/lib/DxilPIXPasses | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_dxilpixpasses_sources = [_][]const u8{
    "lib/DxilPIXPasses/DxilDbgValueToDbgDeclare.cpp",
    "lib/DxilPIXPasses/DxilRemoveDiscards.cpp",
    "lib/DxilPIXPasses/DxilPIXDXRInvocationsLog.cpp",
    "lib/DxilPIXPasses/DxilForceEarlyZ.cpp",
    "lib/DxilPIXPasses/DxilAnnotateWithVirtualRegister.cpp",
    "lib/DxilPIXPasses/DxilPIXAddTidToAmplificationShaderPayload.cpp",
    "lib/DxilPIXPasses/DxilDebugInstrumentation.cpp",
    "lib/DxilPIXPasses/DxilPIXPasses.cpp",
    "lib/DxilPIXPasses/PixPassHelpers.cpp",
    "lib/DxilPIXPasses/DxilPIXVirtualRegisters.cpp",
    "lib/DxilPIXPasses/DxilShaderAccessTracking.cpp",
    "lib/DxilPIXPasses/DxilOutputColorBecomesConstant.cpp",
    "lib/DxilPIXPasses/DxilReduceMSAAToSingleSample.cpp",
    "lib/DxilPIXPasses/DxilAddPixelHitInstrumentation.cpp",
    "lib/DxilPIXPasses/DxilPIXMeshShaderOutputInstrumentation.cpp",
};

// find libs/DirectXShaderCompiler/lib/DxilCompression | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_dxilcompression_cpp_sources = [_][]const u8{
    "lib/DxilCompression/DxilCompression.cpp",
};

// find libs/DirectXShaderCompiler/lib/DxilCompression | grep '\.c$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_dxilcompression_c_sources = [_][]const u8{
    "lib/DxilCompression/miniz.c",
};

// find libs/DirectXShaderCompiler/lib/DxilRootSignature | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy
const lib_dxilrootsignature_sources = [_][]const u8{
    "lib/DxilRootSignature/DxilRootSignature.cpp",
    "lib/DxilRootSignature/DxilRootSignatureSerializer.cpp",
    "lib/DxilRootSignature/DxilRootSignatureConvert.cpp",
    "lib/DxilRootSignature/DxilRootSignatureValidator.cpp",
};

// SPIRV-Tools stuff
// find libs/DirectXShaderCompiler/external/SPIRV-Tools/source | grep '\.cpp$' | xargs -I {} -n1 echo '"{}",' | pbcopy

const lib_spirv = [_][]const u8{
    "tools/clang/lib/SPIRV/RemoveBufferBlockVisitor.cpp",
    "tools/clang/lib/SPIRV/LiteralTypeVisitor.cpp",
    "tools/clang/lib/SPIRV/AlignmentSizeCalculator.cpp",
    "tools/clang/lib/SPIRV/RawBufferMethods.cpp",
    "tools/clang/lib/SPIRV/GlPerVertex.cpp",
    "tools/clang/lib/SPIRV/SpirvFunction.cpp",
    "tools/clang/lib/SPIRV/LowerTypeVisitor.cpp",
    "tools/clang/lib/SPIRV/SpirvInstruction.cpp",
    "tools/clang/lib/SPIRV/DeclResultIdMapper.cpp",
    "tools/clang/lib/SPIRV/SpirvEmitter.cpp",
    "tools/clang/lib/SPIRV/SpirvBuilder.cpp",
    "tools/clang/lib/SPIRV/FeatureManager.cpp",
    "tools/clang/lib/SPIRV/SpirvModule.cpp",
    "tools/clang/lib/SPIRV/BlockReadableOrder.cpp",
    "tools/clang/lib/SPIRV/SignaturePackingUtil.cpp",
    "tools/clang/lib/SPIRV/CapabilityVisitor.cpp",
    "tools/clang/lib/SPIRV/SpirvBasicBlock.cpp",
    "tools/clang/lib/SPIRV/NonUniformVisitor.cpp",
    "tools/clang/lib/SPIRV/RelaxedPrecisionVisitor.cpp",
    "tools/clang/lib/SPIRV/SpirvType.cpp",
    "tools/clang/lib/SPIRV/SortDebugInfoVisitor.cpp",
    "tools/clang/lib/SPIRV/SpirvContext.cpp",
    "tools/clang/lib/SPIRV/PreciseVisitor.cpp",
    "tools/clang/lib/SPIRV/EmitSpirvAction.cpp",
    "tools/clang/lib/SPIRV/PervertexInputVisitor.cpp",
    "tools/clang/lib/SPIRV/EmitVisitor.cpp",
    "tools/clang/lib/SPIRV/String.cpp",
    "tools/clang/lib/SPIRV/AstTypeProbe.cpp",
    "tools/clang/lib/SPIRV/DebugTypeVisitor.cpp",
    "tools/clang/lib/SPIRV/InitListHandler.cpp",
};
