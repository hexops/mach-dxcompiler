const c = @cImport(
    @cInclude("mach_dxc.h"),
);

pub const Compiler = struct {
    handle: c.MachDxcCompiler,

    pub fn init() Compiler {
        const handle = c.machDxcInit();
        return .{ .handle = handle };
    }

    pub fn deinit(compiler: Compiler) void {
        c.machDxcDeinit(compiler.handle);
    }

    pub fn compile(compiler: Compiler, code: []const u8, args: []const [*:0]const u8) Result {
        const result = c.machDxcCompile(compiler.handle, code.ptr, code.len, args.ptr, args.len, null);
        return .{ .handle = result };
    }

    pub const Result = struct {
        handle: c.MachDxcCompileResult,

        pub fn deinit(result: Result) void {
            c.machDxcCompileResultDeinit(result.handle);
        }

        pub fn getError(result: Result) ?Error {
            if (c.machDxcCompileResultGetError(result.handle)) |err| return .{ .handle = err };
            return null;
        }

        pub fn getObject(result: Result) Object {
            return .{ .handle = c.machDxcCompileResultGetObject(result.handle) };
        }

        pub const Error = struct {
            handle: c.MachDxcCompileError,

            pub fn deinit(err: Error) void {
                c.machDxcCompileErrorDeinit(err.handle);
            }

            pub fn getString(err: Error) []const u8 {
                return c.machDxcCompileErrorGetString(err.handle)[0..c.machDxcCompileErrorGetStringLength(err.handle)];
            }
        };

        pub const Object = struct {
            handle: c.MachDxcCompileObject,

            pub fn deinit(obj: Object) void {
                c.machDxcCompileObjectDeinit(obj.handle);
            }

            pub fn getBytes(obj: Object) []const u8 {
                return c.machDxcCompileObjectGetBytes(obj.handle)[0..c.machDxcCompileObjectGetBytesLength(obj.handle)];
            }
        };
    };
};

test {
    const std = @import("std");

    const code =
        \\ Texture1D<float4> tex[5] : register(t3);
        \\ SamplerState SS[3] : register(s2);
        \\
        \\ [RootSignature("DescriptorTable(SRV(t3, numDescriptors=5)), DescriptorTable(Sampler(s2, numDescriptors=3))")]
        \\ float4 main(int i : A, float j : B) : SV_TARGET
        \\ {
        \\   float4 r = tex[NonUniformResourceIndex(i)].Sample(SS[NonUniformResourceIndex(i)], i);
        \\   r += tex[NonUniformResourceIndex(j)].Sample(SS[i], j+2);
        \\   return r;
        \\ };
    ;
    const args = &[_][*:0]const u8{ "-E", "main", "-T", "ps_6_0", "-D", "MYDEFINE=1", "-Qstrip_debug", "-Qstrip_reflect" };

    const compiler = Compiler.init();
    defer compiler.deinit();

    const result = compiler.compile(code, args);
    if (result.getError()) |err| {
        defer err.deinit();
        std.debug.print("compiler error: {s}\n", .{err.getString()});
        return error.ShaderCompilationFailed;
    }

    const object = result.getObject();
    defer object.deinit();

    try std.testing.expectEqual(@as(usize, 2392), object.getBytes().len);
}
