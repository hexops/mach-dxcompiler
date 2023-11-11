#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wrl/client.h>

// #include "mingw_uuid.h"
// #define CROSS_PLATFORM_UUIDOF(type, spec) MINGW_UUIDOF(type, spec)
// CROSS_PLATFORM_UUIDOF(IDxcBlobWide, "A3F84EAB-0FAA-497E-A39C-EE6ED60B2D84")

// Avoid __declspec(dllimport) since dxcompiler is static.
#define DXC_API_IMPORT
#include <dxcapi.h>

#include "mach_dxc.h"

using Microsoft::WRL::ComPtr;

#ifdef __cplusplus
extern "C" {
#endif

MACH_EXPORT void machDxcFoo() {
    ComPtr<IDxcUtils> pUtils;
    DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(pUtils.GetAddressOf()));
    return;
}

#ifdef __cplusplus
} // extern "C"
#endif