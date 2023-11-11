#ifndef MACH_DXC_H_
#define MACH_DXC_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(MACH_DXC_C_SHARED_LIBRARY)
#    if defined(_WIN32)
#        if defined(MACH_DXC_C_IMPLEMENTATION)
#            define MACH_EXPORT __declspec(dllexport)
#        else
#            define MACH_EXPORT __declspec(dllimport)
#        endif
#    else  // defined(_WIN32)
#        if defined(MACH_DXC_C_IMPLEMENTATION)
#            define MACH_EXPORT __attribute__((visibility("default")))
#        else
#            define MACH_EXPORT
#        endif
#    endif  // defined(_WIN32)
#else       // defined(MACH_DXC_C_SHARED_LIBRARY)
#    define MACH_EXPORT
#endif  // defined(MACH_DXC_C_SHARED_LIBRARY)

MACH_EXPORT void machDxcFoo();

#ifdef __cplusplus
} // extern "C"
#endif

#endif  // MACH_DXC_H_
