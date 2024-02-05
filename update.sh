rm -rf config-headers/

mkdir -p config-headers/tools/clang/include/clang/Config/
cp libs/DirectXShaderCompiler/tools/clang/include/clang/Config/config.h.cmake config-headers/tools/clang/include/clang/Config/

mkdir -p config-headers/include/llvm/Config/
cp libs/DirectXShaderCompiler/include/llvm/Config/AsmParsers.def.in config-headers/include/llvm/Config/
cp libs/DirectXShaderCompiler/include/llvm/Config/Disassemblers.def.in config-headers/include/llvm/Config/
cp libs/DirectXShaderCompiler/include/llvm/Config/Targets.def.in config-headers/include/llvm/Config/
cp libs/DirectXShaderCompiler/include/llvm/Config/AsmPrinters.def.in config-headers/include/llvm/Config/
cp libs/DirectXShaderCompiler/include/llvm/Config/abi-breaking.h.cmake config-headers/include/llvm/Config/
cp libs/DirectXShaderCompiler/include/llvm/Config/config.h.cmake config-headers/include/llvm/Config/
cp libs/DirectXShaderCompiler/include/llvm/Config/llvm-config.h.cmake config-headers/include/llvm/Config/

mkdir -p config-headers/include/llvm/Support/
cp libs/DirectXShaderCompiler/include/llvm/Support/DataTypes.h.cmake config-headers/include/llvm/Support/

mkdir -p config-headers/include/dxc/
cp libs/DirectXShaderCompiler/include/dxc/config.h.cmake config-headers/include/dxc/
