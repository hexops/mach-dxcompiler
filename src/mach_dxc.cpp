// TODO: investigate if we can eliminate this for Windows builds
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wrl/client.h>
#endif

// Avoid __declspec(dllimport) since dxcompiler is static.
#define DXC_API_IMPORT
#include <dxcapi.h>

#include "mach_dxc.h"

#ifdef __cplusplus
extern "C" {
#endif

MACH_EXPORT void machDxcFoo() {
    CComPtr<IDxcCompiler> dxcInstance;
    HRESULT hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&dxcInstance));
    // TODO: check success
    return;
}

#ifdef __cplusplus
} // extern "C"
#endif