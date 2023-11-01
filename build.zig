const std = @import("std");
const Build = std.Build;

pub fn build(b: *Build) !void {
    const optimize = b.standardOptimizeOption(.{});
    const target = b.standardTargetOptions(.{});
    const from_source = b.option(bool, "from_source", "Build DXC from source (large C++ codebase)");

    const options = Options{
        .install_libs = true,
        .from_source = from_source,
        .debug = true,
    };
    _ = options;

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
};

pub fn link(b: *Build, step: *std.build.CompileStep, options: Options) !void {
    const opt = options;

    if (options.from_source)
        try linkFromSource(b, step, opt)
    else
        try linkFromBinary(b, step, opt);
}

fn linkFromSource(b: *Build, step: *std.build.CompileStep, options: Options) !void {
    _ = b;
    _ = options;
    _ = step;

    // TODO
}

pub fn linkFromBinary(b: *Build, step: *std.build.CompileStep, options: Options) !void {
    _ = options;
    _ = step;
    _ = b;
    // TODO
}
