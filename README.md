# mach-dxcompiler: DXC built using Zig

This project builds/cross-compiles static binaries of Microsoft/DirectXShaderCompiler (`dxcompiler` / DXC, the official HLSL compiler for DirectX) for many OS/Arch.

## Experimental

This is an **experimental** project according to [our stability guarantees](https://machengine.org/about/stability):

> When a project has an experimental warning, it means all bets are off. You should carefully read the warning to understand why the project is experimental, and assume the worst.

**Tracking issue:** https://github.com/hexops/mach/issues/1094

## Why?

The HLSL compiler shipped with Windows by default is called FXC, it does not support SM6.0 (DirectX 12+ features), is slow, has very poor codegen, and is officially deprected by Microsoft.

[Microsoft/DirectXShaderCompiler](https://github.com/microsoft/DirectXShaderCompiler) (DXC) is a fork of LLVM/Clang, and the successor to FXC with new Microsoft eccentricities such as using their own C++ testing framework (TAEF), Tracing library (ETW), and various dependencies on the Windows SDK and MSVC compiler. The fork is based on LLVM/Clang 3.7, which is over 7 years old and Microsoft is not able to update it because DirectX drivers directly expect DXIL, which is just _specifically_ LLVM v3.7's IR format. They are now bound to this old/outdated IR format, and are [making an effort to add DXIL/LLVM IR v3.7 as a backend to modern Clang versions](https://discourse.llvm.org/t/rfc-adding-hlsl-and-directx-support-to-clang-llvm/60783) upstream so that modern LLVM/Clang can be used without requiring all GPU drivers having to support a newer LLVM IR version.

The [Microsoft/DirectXShaderCompiler](https://github.com/microsoft/DirectXShaderCompiler) fork may be compiled on Windows using MSVC, and on macOS/Linux using clang. However, the codebase is not setup to support [static library compilation](https://github.com/microsoft/DirectXShaderCompiler/issues/4766) and building on Windows is rather involved: it requires using a special HLSL Console, `hctbuild` wrapper, Visual Studio 2019, has dependencies on the Windows SDK, Windows Driver development kits, MSVC, etc.

`zig cc` and `zig c++` are clang-compatible C/C++ compilers, but use MinGW windows headers which are not 100% compatible with Microsoft's own [proprietary](https://github.com/microsoft/win32metadata/issues/766#issuecomment-1103518587) Windows SDK headers. We would like to use these MinGW headers and the `-gnu` clang ABI target so that game binaries can be cross-compiled from Linux/macOS -> Windows effortlessly.

## How?

We maintain a fork of [DirectXCompiler](https://github.com/hexops/DirectXShaderCompiler) with various modifications to CMake build configurations and headers to support building only the `dxcompiler` library with `zig cc` and the MinGW headers on Windows.

Subsequently, _this project_ provides CMake toolchains which use `zig cc`, and provides a `zig build` script to invoke `cmake` with these toolchains and the right configuration options for the given target.

This repository _also_ provides lightweight Zig bindings to use DXC as a Zig API.

## Usage

By default, `zig build` will build the Zig bindings to DXC and will link against prebuilt binaries of DXC fetched from our CI build system. This is so that Zig developers do not need to wait the ~5 minutes or so that compiling DXC/LLVM takes, as it is a large C++ codebase.

To build a static `dxcompiler` and headers from source, use:

```
zig build install -Dfrom-source=true
```

You may wish to use the following options when building:

| Option                         | Description                                                                                     |
| ------------------------------ | ----------------------------------------------------------------------------------------------- |
| `-from-source=true`            | Build from source                                                                               |
| `-Dcpu=x86_64_v2`              | e.g. do not emit AVX2 instructions, see [this issue](https://github.com/hexops/mach/issues/989) |
| `-Doptimize=ReleaseFast`       | Release mode / perform release optimizations                                                    |
| `-Dtarget=x86_64-linux-gnu`    | Cross-compile for 64-bit Linux GNU libc                                                         |
| `-Dtarget=x86_64-linux-musl`   | Cross-compile for 64-bit Linux musl libc                                                        |
| `-Dtarget=aarch64-linux-gnu`   | Cross-compile for ARM Linux GNU libc                                                            |
| `-Dtarget=aarch64-linux-musl`  | Cross-compile for ARM Linux musl libc                                                           |
| `-Dtarget=x86_64-windows-gnu`  | Cross-compile for Windows GNU/MinGW ABI                                                         |
| `-Dtarget=x86_64-windows-msvc` | Cross-compile for Windows MSVC ABI                                                              |
| `-Dtarget=aarch64-macos`       | Cross-compile for macOS Apple Silicon                                                           |
| `-Dtarget=x86_64-macos`        | Cross-compile for macOS Intel                                                                   |

**Note:**

* Building from source requires `cmake` and `ninja`.
* Linux->Windows cross-compilation _from source_ is only supported with a case-insensitive filesystem.
  * MacOS and Windows both use case-insensitive filesystems, but most Linux distributions do not by default.
  * Microsoft uses mixed case `#include`s throughout their headers and relies on this behavior.
* `-Dtarget=x86_64-windows-msvc` requires the Windows SDK and may only be used on a Windows host machine.

## Issues

Issues are tracked in the [main Mach repository](https://github.com/hexops/mach/issues?q=is%3Aissue+is%3Aopen+label%3Adxcompiler).

## Community

Join the Mach engine community [on Discord](https://discord.gg/XNG3NZgCqp) to discuss this project, ask questions, get help, etc.
