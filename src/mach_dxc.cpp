// TODO: investigate if we can eliminate this for Windows builds
#ifdef _WIN32
    #ifdef _MSC_VER
        #define __C89_NAMELESS
        #define __C89_NAMELESSUNIONNAME
        #define WIN32_LEAN_AND_MEAN
        #include <windows.h>
        #include <wrl/client.h>
        #define CComPtr Microsoft::WRL::ComPtr
    #else // _MSC_VER
        #include <windows.h>
        #include <wrl/client.h>
    #endif // _MSC_VER
#endif // _WIN32

// Avoid __declspec(dllimport) since dxcompiler is static.
#define DXC_API_IMPORT
#include <dxcapi.h>
#include <cassert>
#include <stddef.h>

#include "mach_dxc.h"

#ifdef __cplusplus
extern "C" {
#endif

// Mach change start: static dxcompiler/dxil
BOOL MachDxcompilerInvokeDllMain();
void MachDxcompilerInvokeDllShutdown();

//----------------
// MachDxcCompiler
//----------------
MACH_EXPORT MachDxcCompiler machDxcInit() {
    MachDxcompilerInvokeDllMain();
    CComPtr<IDxcCompiler3> dxcInstance;
    HRESULT hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&dxcInstance));
    assert(SUCCEEDED(hr));
    return reinterpret_cast<MachDxcCompiler>(dxcInstance.Detach());
}

MACH_EXPORT void machDxcDeinit(MachDxcCompiler compiler) {
    CComPtr<IDxcCompiler3> dxcInstance = CComPtr(reinterpret_cast<IDxcCompiler3*>(compiler));
    dxcInstance.Release();
    MachDxcompilerInvokeDllShutdown();
}

//---------------------
// MachDxcCompileResult
//---------------------
MACH_EXPORT MachDxcCompileResult machDxcCompile(
    MachDxcCompiler compiler,
    char const* code,
    size_t code_len,
    char const* const* args,
    size_t args_len
) {
    CComPtr<IDxcCompiler3> dxcInstance = CComPtr(reinterpret_cast<IDxcCompiler3*>(compiler));

    CComPtr<IDxcUtils> pUtils;
    DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&pUtils));
    CComPtr<IDxcBlobEncoding> pSource;
    pUtils->CreateBlob(code, code_len, CP_UTF8, &pSource);

    DxcBuffer sourceBuffer;
    sourceBuffer.Ptr = pSource->GetBufferPointer();
    sourceBuffer.Size = pSource->GetBufferSize();
    sourceBuffer.Encoding = 0;

    // We have args in char form, but dxcInstance->Compile expects wchar_t form.
    std::vector<std::wstring> arguments;
    for (int i=0; i < args_len; i++) {
        wchar_t wtext_buf[200];
        std::mbstowcs(wtext_buf, args[i], strlen(args[i])+1);
        arguments.push_back(std::wstring(wtext_buf));
    }
    std::vector<LPCWSTR> w_arguments_list;
    for (int i=0; i < args_len; i++) {
        w_arguments_list.push_back(arguments[i].data());
    }

    CComPtr<IDxcResult> pCompileResult;
    HRESULT hr = dxcInstance->Compile(
        &sourceBuffer,
        w_arguments_list.data(),
        (uint32_t)w_arguments_list.size(),
        nullptr,
        IID_PPV_ARGS(&pCompileResult)
    );
    assert(SUCCEEDED(hr));
    return reinterpret_cast<MachDxcCompileResult>(pCompileResult.Detach());
}

MACH_EXPORT MachDxcCompileError machDxcCompileResultGetError(MachDxcCompileResult err) {
    CComPtr<IDxcResult> pCompileResult = CComPtr(reinterpret_cast<IDxcResult*>(err));
    CComPtr<IDxcBlobUtf8> pErrors;
    pCompileResult->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&pErrors), nullptr);
    if (pErrors && pErrors->GetStringLength() > 0) {
        return reinterpret_cast<MachDxcCompileError>(pErrors.Detach());
    }
    return nullptr;
}

MACH_EXPORT MachDxcCompileObject machDxcCompileResultGetObject(MachDxcCompileResult err) {
    CComPtr<IDxcResult> pCompileResult = CComPtr(reinterpret_cast<IDxcResult*>(err));
    CComPtr<IDxcBlob> pObject;
    pCompileResult->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&pObject), nullptr);
    if (pObject && pObject->GetBufferSize() > 0) {
        return reinterpret_cast<MachDxcCompileObject>(pObject.Detach());
    }
    return nullptr;
}

MACH_EXPORT void machDxcCompileResultDeinit(MachDxcCompileResult err) {
    CComPtr<IDxcResult> pCompileResult = CComPtr(reinterpret_cast<IDxcResult*>(err));
    pCompileResult.Release();
}

//---------------------
// MachDxcCompileObject
//---------------------
MACH_EXPORT char const* machDxcCompileObjectGetBytes(MachDxcCompileObject err) {
    CComPtr<IDxcBlob> pObject = CComPtr(reinterpret_cast<IDxcBlob*>(err));
    return (char const*)(pObject->GetBufferPointer());
}

MACH_EXPORT size_t machDxcCompileObjectGetBytesLength(MachDxcCompileObject err) {
    CComPtr<IDxcBlob> pObject = CComPtr(reinterpret_cast<IDxcBlob*>(err));
    return pObject->GetBufferSize();
}

MACH_EXPORT void machDxcCompileObjectDeinit(MachDxcCompileObject err) {
    CComPtr<IDxcBlob> pObject = CComPtr(reinterpret_cast<IDxcBlob*>(err));
    pObject.Release();
}

//--------------------
// MachDxcCompileError
//--------------------
MACH_EXPORT char const* machDxcCompileErrorGetString(MachDxcCompileError err) {
    CComPtr<IDxcBlobUtf8> pErrors = CComPtr(reinterpret_cast<IDxcBlobUtf8*>(err));
    return (char const*)(pErrors->GetBufferPointer());
}

MACH_EXPORT size_t machDxcCompileErrorGetStringLength(MachDxcCompileError err) {
    CComPtr<IDxcBlobUtf8> pErrors = CComPtr(reinterpret_cast<IDxcBlobUtf8*>(err));
    return pErrors->GetStringLength();
}

MACH_EXPORT void machDxcCompileErrorDeinit(MachDxcCompileError err) {
    CComPtr<IDxcBlobUtf8> pErrors = CComPtr(reinterpret_cast<IDxcBlobUtf8*>(err));
    pErrors.Release();
}

#ifdef __cplusplus
} // extern "C"
#endif