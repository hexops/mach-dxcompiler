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

#if !defined(MACH_OBJECT_ATTRIBUTE)
#define MACH_OBJECT_ATTRIBUTE
#endif

#include <stddef.h>

typedef struct MachDxcCompilerImpl* MachDxcCompiler MACH_OBJECT_ATTRIBUTE;
typedef struct MachDxcCompileResultImpl* MachDxcCompileResult MACH_OBJECT_ATTRIBUTE;
typedef struct MachDxcCompileErrorImpl* MachDxcCompileError MACH_OBJECT_ATTRIBUTE;
typedef struct MachDxcCompileObjectImpl* MachDxcCompileObject MACH_OBJECT_ATTRIBUTE;

//----------------
// MachDxcCompiler
//----------------

/// Initializes a DXC compiler
///
/// Invoke machDxcDeinit when done with the compiler.
MACH_EXPORT MachDxcCompiler machDxcInit();

/// Deinitializes the DXC compiler.
MACH_EXPORT void machDxcDeinit(MachDxcCompiler compiler);

//---------------------
// MachDxcCompileResult
//---------------------

/// Compiles the given code with the given dxc.exe CLI arguments
///
/// Invoke machDxcCompileResultDeinit when done with the result.
MACH_EXPORT MachDxcCompileResult machDxcCompile(
    MachDxcCompiler compiler,
    char const* code,
    size_t code_len,
    char const* const* args,
    size_t args_len
);

/// Returns an error object, or null in the case of success.
///
/// Invoke machDxcCompileErrorDeinit when done with the error, iff it was non-null.
MACH_EXPORT MachDxcCompileError machDxcCompileResultGetError(MachDxcCompileResult err);

/// Returns the compiled object code, or null if an error occurred.
MACH_EXPORT MachDxcCompileObject machDxcCompileResultGetObject(MachDxcCompileResult err);

/// Deinitializes the DXC compiler.
MACH_EXPORT void machDxcCompileResultDeinit(MachDxcCompileResult err);

//---------------------
// MachDxcCompileObject
//---------------------

/// Returns a pointer to the raw bytes of the compiled object file.
MACH_EXPORT char const* machDxcCompileObjectGetBytes(MachDxcCompileObject err);

/// Returns the length of the compiled object file.
MACH_EXPORT size_t machDxcCompileObjectGetBytesLength(MachDxcCompileObject err);

/// Deinitializes the compiled object, calling Get methods after this is illegal.
MACH_EXPORT void machDxcCompileObjectDeinit(MachDxcCompileObject err);

//--------------------
// MachDxcCompileError
//--------------------

/// Returns a pointer to the null-terminated UTF-8 encoded error string. This includes
/// compiler warnings, unless they were disabled in the compile arguments.
MACH_EXPORT char const* machDxcCompileErrorGetString(MachDxcCompileError err);

/// Returns the length of the error string.
MACH_EXPORT size_t machDxcCompileErrorGetStringLength(MachDxcCompileError err);

/// Deinitializes the error, calling Get methods after this is illegal.
MACH_EXPORT void machDxcCompileErrorDeinit(MachDxcCompileError err);

#ifdef __cplusplus
} // extern "C"
#endif

#endif  // MACH_DXC_H_
