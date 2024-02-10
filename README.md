# mach-dxcompiler

The DirectX shader compiler, built better.

See ['Building the DirectX shader compiler better than Microsoft?'](https://devlog.hexops.com/2024/building-the-directx-shader-compiler-better-than-microsoft/) for details/background information.
## Experimental

This is an **experimental** project according to [our stability guarantees](https://machengine.org/about/stability):

> When a project has an experimental warning, it means all bets are off. You should carefully read the warning to understand why the project is experimental, and assume the worst.

**Tracking issue:** https://github.com/hexops/mach/issues/1094

## Features

* Statically linked `dxcompiler` library and `dxc` executables.
* Zero dependency on proprietary `dxil.dll` code-signing blob (see: [Mach Siegbert Vogt DXCSA](https://github.com/hexops/DirectXShaderCompiler/blob/4190bb0c90d374c6b4d0b0f2c7b45b604eda24b6/tools/clang/tools/dxcompiler/MachSiegbertVogtDXCSA.cpp#L178))
* Built using `build.zig` instead of 10k+ LOC CMake build system.
* [Prebuilt binaries](https://github.com/hexops/mach-dxcompiler/releases) provided for many OS/arch.
* Binaries for macOS and aarch64 Linux (first ever in history), among others.
* [Simple C API](https://github.com/hexops/mach-dxcompiler/blob/main/src/mach_dxc.h) bundled into library as an alternative to the traditional COM API.

## Documentation

[machengine.org/pkg/mach-dxcompiler](https://machengine.org/pkg/mach-dxcompiler)

## Join the community

Join the [Mach community on Discord](https://discord.gg/XNG3NZgCqp) to discuss this project, ask questions, get help, etc.

## Issues

Issues are tracked in the [main Mach repository](https://github.com/hexops/mach/issues?q=is%3Aissue+is%3Aopen+label%3Adxcompiler).
