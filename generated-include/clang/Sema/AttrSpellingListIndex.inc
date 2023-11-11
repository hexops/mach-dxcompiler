/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Code to translate different attribute spellings into internal identifiers  *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

  switch (AttrKind) {
  default:
    llvm_unreachable("Unknown attribute kind!");
    break;
  case AT_AMDGPUNumSGPR: {
    if (Name == "amdgpu_num_sgpr" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_AMDGPUNumVGPR: {
    if (Name == "amdgpu_num_vgpr" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_Interrupt: {
    if (Name == "interrupt" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_AcquireCapability: {
    if (Name == "acquire_capability" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "acquire_capability" && SyntaxUsed == 1 && Scope == "clang")
        return 1;
    if (Name == "acquire_shared_capability" && SyntaxUsed == 0 && Scope == "")
        return 2;
    if (Name == "acquire_shared_capability" && SyntaxUsed == 1 && Scope == "clang")
        return 3;
    if (Name == "exclusive_lock_function" && SyntaxUsed == 0 && Scope == "")
        return 4;
    if (Name == "shared_lock_function" && SyntaxUsed == 0 && Scope == "")
        return 5;
    break;
  }
  case AT_AcquiredAfter: {
    if (Name == "acquired_after" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_AcquiredBefore: {
    if (Name == "acquired_before" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_AddressSpace: {
    if (Name == "address_space" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_Alias: {
    if (Name == "alias" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "alias" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_AlignValue: {
    if (Name == "align_value" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_Aligned: {
    if (Name == "aligned" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "aligned" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    if (Name == "align" && SyntaxUsed == 2 && Scope == "")
        return 2;
    if (Name == "alignas" && SyntaxUsed == 3 && Scope == "")
        return 3;
    if (Name == "_Alignas" && SyntaxUsed == 3 && Scope == "")
        return 4;
    break;
  }
  case AT_AlwaysInline: {
    if (Name == "always_inline" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "always_inline" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    if (Name == "__forceinline" && SyntaxUsed == 3 && Scope == "")
        return 2;
    break;
  }
  case AT_AnalyzerNoReturn: {
    if (Name == "analyzer_noreturn" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_Annotate: {
    if (Name == "annotate" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_ArcWeakrefUnavailable: {
    if (Name == "objc_arc_weak_reference_unavailable" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_ArgumentWithTypeTag: {
    if (Name == "argument_with_type_tag" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "pointer_with_type_tag" && SyntaxUsed == 0 && Scope == "")
        return 1;
    break;
  }
  case AT_AssertCapability: {
    if (Name == "assert_capability" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "assert_capability" && SyntaxUsed == 1 && Scope == "clang")
        return 1;
    if (Name == "assert_shared_capability" && SyntaxUsed == 0 && Scope == "")
        return 2;
    if (Name == "assert_shared_capability" && SyntaxUsed == 1 && Scope == "clang")
        return 3;
    break;
  }
  case AT_AssertExclusiveLock: {
    if (Name == "assert_exclusive_lock" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_AssertSharedLock: {
    if (Name == "assert_shared_lock" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_AssumeAligned: {
    if (Name == "assume_aligned" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "assume_aligned" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_Availability: {
    if (Name == "availability" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_Blocks: {
    if (Name == "blocks" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_CDecl: {
    if (Name == "cdecl" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "cdecl" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    if (Name == "__cdecl" && SyntaxUsed == 3 && Scope == "")
        return 2;
    if (Name == "_cdecl" && SyntaxUsed == 3 && Scope == "")
        return 3;
    break;
  }
  case AT_CFAuditedTransfer: {
    if (Name == "cf_audited_transfer" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_CFConsumed: {
    if (Name == "cf_consumed" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_CFReturnsNotRetained: {
    if (Name == "cf_returns_not_retained" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_CFReturnsRetained: {
    if (Name == "cf_returns_retained" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_CFUnknownTransfer: {
    if (Name == "cf_unknown_transfer" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_CUDAConstant: {
    if (Name == "constant" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_CUDADevice: {
    if (Name == "device" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_CUDAGlobal: {
    if (Name == "global" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_CUDAHost: {
    if (Name == "host" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_CUDAInvalidTarget: {
    break;
  }
  case AT_CUDALaunchBounds: {
    if (Name == "launch_bounds" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_CUDAShared: {
    if (Name == "shared" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_CXX11NoReturn: {
    if (Name == "noreturn" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_CallableWhen: {
    if (Name == "callable_when" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_Capability: {
    if (Name == "capability" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "capability" && SyntaxUsed == 1 && Scope == "clang")
        return 1;
    if (Name == "shared_capability" && SyntaxUsed == 0 && Scope == "")
        return 2;
    if (Name == "shared_capability" && SyntaxUsed == 1 && Scope == "clang")
        return 3;
    break;
  }
  case AT_CarriesDependency: {
    if (Name == "carries_dependency" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "carries_dependency" && SyntaxUsed == 1 && Scope == "")
        return 1;
    break;
  }
  case AT_Cleanup: {
    if (Name == "cleanup" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "cleanup" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_Cold: {
    if (Name == "cold" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "cold" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_Common: {
    if (Name == "common" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "common" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_Const: {
    if (Name == "const" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "const" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    if (Name == "__const" && SyntaxUsed == 0 && Scope == "")
        return 2;
    if (Name == "__const" && SyntaxUsed == 1 && Scope == "gnu")
        return 3;
    break;
  }
  case AT_Constructor: {
    if (Name == "constructor" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "constructor" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_Consumable: {
    if (Name == "consumable" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_ConsumableAutoCast: {
    if (Name == "consumable_auto_cast_state" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_ConsumableSetOnRead: {
    if (Name == "consumable_set_state_on_read" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_DLLExport: {
    if (Name == "dllexport" && SyntaxUsed == 2 && Scope == "")
        return 0;
    if (Name == "dllexport" && SyntaxUsed == 0 && Scope == "")
        return 1;
    if (Name == "dllexport" && SyntaxUsed == 1 && Scope == "gnu")
        return 2;
    break;
  }
  case AT_DLLImport: {
    if (Name == "dllimport" && SyntaxUsed == 2 && Scope == "")
        return 0;
    if (Name == "dllimport" && SyntaxUsed == 0 && Scope == "")
        return 1;
    if (Name == "dllimport" && SyntaxUsed == 1 && Scope == "gnu")
        return 2;
    break;
  }
  case AT_Deprecated: {
    if (Name == "deprecated" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "deprecated" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    if (Name == "deprecated" && SyntaxUsed == 2 && Scope == "")
        return 2;
    if (Name == "deprecated" && SyntaxUsed == 1 && Scope == "")
        return 3;
    break;
  }
  case AT_Destructor: {
    if (Name == "destructor" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "destructor" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_EnableIf: {
    if (Name == "enable_if" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_ExclusiveTrylockFunction: {
    if (Name == "exclusive_trylock_function" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_ExtVectorType: {
    if (Name == "ext_vector_type" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_FallThrough: {
    if (Name == "fallthrough" && SyntaxUsed == 1 && Scope == "clang")
        return 0;
    break;
  }
  case AT_FastCall: {
    if (Name == "fastcall" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "fastcall" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    if (Name == "__fastcall" && SyntaxUsed == 3 && Scope == "")
        return 2;
    if (Name == "_fastcall" && SyntaxUsed == 3 && Scope == "")
        return 3;
    break;
  }
  case AT_FlagEnum: {
    if (Name == "flag_enum" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_Flatten: {
    if (Name == "flatten" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "flatten" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_Format: {
    if (Name == "format" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "format" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_FormatArg: {
    if (Name == "format_arg" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "format_arg" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_GNUInline: {
    if (Name == "gnu_inline" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "gnu_inline" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_GuardedBy: {
    if (Name == "guarded_by" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_GuardedVar: {
    if (Name == "guarded_var" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLAllowUAVCondition: {
    if (Name == "allow_uav_condition" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLBranch: {
    if (Name == "branch" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLCXXOverload: {
    break;
  }
  case AT_HLSLCall: {
    if (Name == "call" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLCenter: {
    if (Name == "center" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLCentroid: {
    if (Name == "centroid" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLClipPlanes: {
    if (Name == "clipplanes" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLColumnMajor: {
    if (Name == "column_major" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLDomain: {
    if (Name == "domain" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLEarlyDepthStencil: {
    if (Name == "earlydepthstencil" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLExperimental: {
    if (Name == "experimental" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLExport: {
    if (Name == "export" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLFastOpt: {
    if (Name == "fastopt" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLFlatten: {
    if (Name == "flatten" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLForceCase: {
    if (Name == "forcecase" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLGloballyCoherent: {
    if (Name == "globallycoherent" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLGroupShared: {
    if (Name == "groupshared" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLIn: {
    if (Name == "in" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLInOut: {
    if (Name == "inout" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLIndices: {
    if (Name == "indices" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLInstance: {
    if (Name == "instance" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLIntrinsic: {
    if (Name == "intrinsic" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLLine: {
    if (Name == "line" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLLineAdj: {
    if (Name == "lineadj" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLLinear: {
    if (Name == "linear" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLLoop: {
    if (Name == "loop" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLMaxTessFactor: {
    if (Name == "maxtessfactor" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLMaxVertexCount: {
    if (Name == "maxvertexcount" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLMaybeUnused: {
    if (Name == "maybe_unused" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLNoInterpolation: {
    if (Name == "nointerpolation" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLNoPerspective: {
    if (Name == "noperspective" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLNumThreads: {
    if (Name == "numthreads" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLOut: {
    if (Name == "out" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLOutputControlPoints: {
    if (Name == "outputcontrolpoints" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLOutputTopology: {
    if (Name == "outputtopology" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLPartitioning: {
    if (Name == "partitioning" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLPatchConstantFunc: {
    if (Name == "patchconstantfunc" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLPayload: {
    if (Name == "payload" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLPoint: {
    if (Name == "point" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLPrecise: {
    if (Name == "precise" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLPrimitives: {
    if (Name == "primitives" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLRayPayload: {
    if (Name == "raypayload" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLRootSignature: {
    if (Name == "RootSignature" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLRowMajor: {
    if (Name == "row_major" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLSample: {
    if (Name == "sample" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLSemantic: {
    break;
  }
  case AT_HLSLShader: {
    if (Name == "shader" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLShared: {
    if (Name == "shared" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLSnorm: {
    if (Name == "snorm" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLTriangle: {
    if (Name == "triangle" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLTriangleAdj: {
    if (Name == "triangleadj" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLUniform: {
    if (Name == "uniform" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLUnorm: {
    if (Name == "unorm" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLUnroll: {
    if (Name == "unroll" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLVertices: {
    if (Name == "vertices" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLWaveOpsIncludeHelperLanes: {
    if (Name == "waveopsincludehelperlanes" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLWaveSensitive: {
    if (Name == "wavesensitive" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_HLSLWaveSize: {
    if (Name == "wavesize" && SyntaxUsed == 1 && Scope == "")
        return 0;
    break;
  }
  case AT_Hot: {
    if (Name == "hot" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "hot" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_IBAction: {
    if (Name == "ibaction" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_IBOutlet: {
    if (Name == "iboutlet" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_IBOutletCollection: {
    if (Name == "iboutletcollection" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_InitPriority: {
    if (Name == "init_priority" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_IntelOclBicc: {
    if (Name == "intel_ocl_bicc" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_LockReturned: {
    if (Name == "lock_returned" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_Lockable: {
    if (Name == "lockable" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_LocksExcluded: {
    if (Name == "locks_excluded" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_LoopHint: {
    if (Name == "loop" && SyntaxUsed == 4 && Scope == "clang")
        return 0;
    if (Name == "unroll" && SyntaxUsed == 4 && Scope == "")
        return 1;
    if (Name == "nounroll" && SyntaxUsed == 4 && Scope == "")
        return 2;
    break;
  }
  case AT_MSABI: {
    if (Name == "ms_abi" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "ms_abi" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_MSInheritance: {
    if (Name == "__single_inheritance" && SyntaxUsed == 3 && Scope == "")
        return 0;
    if (Name == "__multiple_inheritance" && SyntaxUsed == 3 && Scope == "")
        return 1;
    if (Name == "__virtual_inheritance" && SyntaxUsed == 3 && Scope == "")
        return 2;
    if (Name == "__unspecified_inheritance" && SyntaxUsed == 3 && Scope == "")
        return 3;
    break;
  }
  case AT_MSNoVTable: {
    if (Name == "novtable" && SyntaxUsed == 2 && Scope == "")
        return 0;
    break;
  }
  case AT_MSStruct: {
    if (Name == "ms_struct" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "ms_struct" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_MayAlias: {
    if (Name == "may_alias" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "may_alias" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_MinSize: {
    if (Name == "minsize" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_Mips16: {
    if (Name == "mips16" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "mips16" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_Mode: {
    if (Name == "mode" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "mode" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_NSConsumed: {
    if (Name == "ns_consumed" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_NSConsumesSelf: {
    if (Name == "ns_consumes_self" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_NSReturnsAutoreleased: {
    if (Name == "ns_returns_autoreleased" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_NSReturnsNotRetained: {
    if (Name == "ns_returns_not_retained" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_NSReturnsRetained: {
    if (Name == "ns_returns_retained" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_Naked: {
    if (Name == "naked" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "naked" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    if (Name == "naked" && SyntaxUsed == 2 && Scope == "")
        return 2;
    break;
  }
  case AT_NeonPolyVectorType: {
    if (Name == "neon_polyvector_type" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_NeonVectorType: {
    if (Name == "neon_vector_type" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_NoCommon: {
    if (Name == "nocommon" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "nocommon" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_NoDebug: {
    if (Name == "nodebug" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "nodebug" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_NoDuplicate: {
    if (Name == "noduplicate" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "noduplicate" && SyntaxUsed == 1 && Scope == "clang")
        return 1;
    break;
  }
  case AT_NoInline: {
    if (Name == "noinline" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "noinline" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    if (Name == "noinline" && SyntaxUsed == 2 && Scope == "")
        return 2;
    if (Name == "noinline" && SyntaxUsed == 1 && Scope == "")
        return 3;
    break;
  }
  case AT_NoInstrumentFunction: {
    if (Name == "no_instrument_function" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "no_instrument_function" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_NoMips16: {
    if (Name == "nomips16" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "nomips16" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_NoReturn: {
    if (Name == "noreturn" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "noreturn" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    if (Name == "noreturn" && SyntaxUsed == 2 && Scope == "")
        return 2;
    break;
  }
  case AT_NoSanitize: {
    if (Name == "no_sanitize" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "no_sanitize" && SyntaxUsed == 1 && Scope == "clang")
        return 1;
    break;
  }
  case AT_NoSanitizeSpecific: {
    if (Name == "no_address_safety_analysis" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "no_address_safety_analysis" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    if (Name == "no_sanitize_address" && SyntaxUsed == 0 && Scope == "")
        return 2;
    if (Name == "no_sanitize_address" && SyntaxUsed == 1 && Scope == "gnu")
        return 3;
    if (Name == "no_sanitize_thread" && SyntaxUsed == 0 && Scope == "")
        return 4;
    if (Name == "no_sanitize_thread" && SyntaxUsed == 1 && Scope == "gnu")
        return 5;
    if (Name == "no_sanitize_memory" && SyntaxUsed == 0 && Scope == "")
        return 6;
    break;
  }
  case AT_NoSplitStack: {
    if (Name == "no_split_stack" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "no_split_stack" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_NoThreadSafetyAnalysis: {
    if (Name == "no_thread_safety_analysis" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_NoThrow: {
    if (Name == "nothrow" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "nothrow" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    if (Name == "nothrow" && SyntaxUsed == 2 && Scope == "")
        return 2;
    break;
  }
  case AT_NonNull: {
    if (Name == "nonnull" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "nonnull" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_ObjCBoxable: {
    if (Name == "objc_boxable" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_ObjCBridge: {
    if (Name == "objc_bridge" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_ObjCBridgeMutable: {
    if (Name == "objc_bridge_mutable" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_ObjCBridgeRelated: {
    if (Name == "objc_bridge_related" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_ObjCDesignatedInitializer: {
    if (Name == "objc_designated_initializer" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_ObjCException: {
    if (Name == "objc_exception" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_ObjCExplicitProtocolImpl: {
    if (Name == "objc_protocol_requires_explicit_implementation" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_ObjCGC: {
    if (Name == "objc_gc" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_ObjCIndependentClass: {
    if (Name == "objc_independent_class" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_ObjCKindOf: {
    if (Name == "__kindof" && SyntaxUsed == 3 && Scope == "")
        return 0;
    break;
  }
  case AT_ObjCMethodFamily: {
    if (Name == "objc_method_family" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_ObjCNSObject: {
    if (Name == "NSObject" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_ObjCOwnership: {
    if (Name == "objc_ownership" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_ObjCPreciseLifetime: {
    if (Name == "objc_precise_lifetime" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_ObjCRequiresPropertyDefs: {
    if (Name == "objc_requires_property_definitions" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_ObjCRequiresSuper: {
    if (Name == "objc_requires_super" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_ObjCReturnsInnerPointer: {
    if (Name == "objc_returns_inner_pointer" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_ObjCRootClass: {
    if (Name == "objc_root_class" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_ObjCRuntimeName: {
    if (Name == "objc_runtime_name" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_OpenCLConstantAddressSpace: {
    if (Name == "__constant" && SyntaxUsed == 3 && Scope == "")
        return 0;
    if (Name == "constant" && SyntaxUsed == 3 && Scope == "")
        return 1;
    break;
  }
  case AT_OpenCLGenericAddressSpace: {
    if (Name == "__generic" && SyntaxUsed == 3 && Scope == "")
        return 0;
    if (Name == "generic" && SyntaxUsed == 3 && Scope == "")
        return 1;
    break;
  }
  case AT_OpenCLGlobalAddressSpace: {
    if (Name == "__global" && SyntaxUsed == 3 && Scope == "")
        return 0;
    if (Name == "global" && SyntaxUsed == 3 && Scope == "")
        return 1;
    break;
  }
  case AT_OpenCLImageAccess: {
    if (Name == "__read_only" && SyntaxUsed == 3 && Scope == "")
        return 0;
    if (Name == "read_only" && SyntaxUsed == 3 && Scope == "")
        return 1;
    if (Name == "__write_only" && SyntaxUsed == 3 && Scope == "")
        return 2;
    if (Name == "write_only" && SyntaxUsed == 3 && Scope == "")
        return 3;
    if (Name == "__read_write" && SyntaxUsed == 3 && Scope == "")
        return 4;
    if (Name == "read_write" && SyntaxUsed == 3 && Scope == "")
        return 5;
    break;
  }
  case AT_OpenCLKernel: {
    if (Name == "__kernel" && SyntaxUsed == 3 && Scope == "")
        return 0;
    if (Name == "kernel" && SyntaxUsed == 3 && Scope == "")
        return 1;
    break;
  }
  case AT_OpenCLLocalAddressSpace: {
    if (Name == "__local" && SyntaxUsed == 3 && Scope == "")
        return 0;
    if (Name == "local" && SyntaxUsed == 3 && Scope == "")
        return 1;
    break;
  }
  case AT_OpenCLPrivateAddressSpace: {
    if (Name == "__private" && SyntaxUsed == 3 && Scope == "")
        return 0;
    if (Name == "private" && SyntaxUsed == 3 && Scope == "")
        return 1;
    break;
  }
  case AT_OptimizeNone: {
    if (Name == "optnone" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "optnone" && SyntaxUsed == 1 && Scope == "clang")
        return 1;
    break;
  }
  case AT_Overloadable: {
    if (Name == "overloadable" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_Ownership: {
    if (Name == "ownership_holds" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "ownership_returns" && SyntaxUsed == 0 && Scope == "")
        return 1;
    if (Name == "ownership_takes" && SyntaxUsed == 0 && Scope == "")
        return 2;
    break;
  }
  case AT_Packed: {
    if (Name == "packed" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "packed" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_ParamTypestate: {
    if (Name == "param_typestate" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_Pascal: {
    if (Name == "pascal" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "__pascal" && SyntaxUsed == 3 && Scope == "")
        return 1;
    if (Name == "_pascal" && SyntaxUsed == 3 && Scope == "")
        return 2;
    break;
  }
  case AT_Pcs: {
    if (Name == "pcs" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "pcs" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_PtGuardedBy: {
    if (Name == "pt_guarded_by" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_PtGuardedVar: {
    if (Name == "pt_guarded_var" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_Ptr32: {
    if (Name == "__ptr32" && SyntaxUsed == 3 && Scope == "")
        return 0;
    break;
  }
  case AT_Ptr64: {
    if (Name == "__ptr64" && SyntaxUsed == 3 && Scope == "")
        return 0;
    break;
  }
  case AT_Pure: {
    if (Name == "pure" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "pure" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_Regparm: {
    if (Name == "regparm" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "regparm" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_ReleaseCapability: {
    if (Name == "release_capability" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "release_capability" && SyntaxUsed == 1 && Scope == "clang")
        return 1;
    if (Name == "release_shared_capability" && SyntaxUsed == 0 && Scope == "")
        return 2;
    if (Name == "release_shared_capability" && SyntaxUsed == 1 && Scope == "clang")
        return 3;
    if (Name == "release_generic_capability" && SyntaxUsed == 0 && Scope == "")
        return 4;
    if (Name == "release_generic_capability" && SyntaxUsed == 1 && Scope == "clang")
        return 5;
    if (Name == "unlock_function" && SyntaxUsed == 0 && Scope == "")
        return 6;
    break;
  }
  case AT_ReqdWorkGroupSize: {
    if (Name == "reqd_work_group_size" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_RequiresCapability: {
    if (Name == "requires_capability" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "requires_capability" && SyntaxUsed == 1 && Scope == "clang")
        return 1;
    if (Name == "exclusive_locks_required" && SyntaxUsed == 0 && Scope == "")
        return 2;
    if (Name == "requires_shared_capability" && SyntaxUsed == 0 && Scope == "")
        return 3;
    if (Name == "requires_shared_capability" && SyntaxUsed == 1 && Scope == "clang")
        return 4;
    if (Name == "shared_locks_required" && SyntaxUsed == 0 && Scope == "")
        return 5;
    break;
  }
  case AT_Restrict: {
    if (Name == "restrict" && SyntaxUsed == 2 && Scope == "")
        return 0;
    if (Name == "malloc" && SyntaxUsed == 0 && Scope == "")
        return 1;
    if (Name == "malloc" && SyntaxUsed == 1 && Scope == "gnu")
        return 2;
    break;
  }
  case AT_ReturnTypestate: {
    if (Name == "return_typestate" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_ReturnsNonNull: {
    if (Name == "returns_nonnull" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "returns_nonnull" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_ReturnsTwice: {
    if (Name == "returns_twice" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "returns_twice" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_SPtr: {
    if (Name == "__sptr" && SyntaxUsed == 3 && Scope == "")
        return 0;
    break;
  }
  case AT_ScopedLockable: {
    if (Name == "scoped_lockable" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_Section: {
    if (Name == "section" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "section" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    if (Name == "allocate" && SyntaxUsed == 2 && Scope == "")
        return 2;
    break;
  }
  case AT_SelectAny: {
    if (Name == "selectany" && SyntaxUsed == 2 && Scope == "")
        return 0;
    break;
  }
  case AT_Sentinel: {
    if (Name == "sentinel" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "sentinel" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_SetTypestate: {
    if (Name == "set_typestate" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_SharedTrylockFunction: {
    if (Name == "shared_trylock_function" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_StdCall: {
    if (Name == "stdcall" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "stdcall" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    if (Name == "__stdcall" && SyntaxUsed == 3 && Scope == "")
        return 2;
    if (Name == "_stdcall" && SyntaxUsed == 3 && Scope == "")
        return 3;
    break;
  }
  case AT_SysVABI: {
    if (Name == "sysv_abi" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "sysv_abi" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_TLSModel: {
    if (Name == "tls_model" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "tls_model" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_Target: {
    if (Name == "target" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "target" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_TestTypestate: {
    if (Name == "test_typestate" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_ThisCall: {
    if (Name == "thiscall" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "thiscall" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    if (Name == "__thiscall" && SyntaxUsed == 3 && Scope == "")
        return 2;
    if (Name == "_thiscall" && SyntaxUsed == 3 && Scope == "")
        return 3;
    break;
  }
  case AT_Thread: {
    if (Name == "thread" && SyntaxUsed == 2 && Scope == "")
        return 0;
    break;
  }
  case AT_TransparentUnion: {
    if (Name == "transparent_union" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "transparent_union" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_TryAcquireCapability: {
    if (Name == "try_acquire_capability" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "try_acquire_capability" && SyntaxUsed == 1 && Scope == "clang")
        return 1;
    if (Name == "try_acquire_shared_capability" && SyntaxUsed == 0 && Scope == "")
        return 2;
    if (Name == "try_acquire_shared_capability" && SyntaxUsed == 1 && Scope == "clang")
        return 3;
    break;
  }
  case AT_TypeNonNull: {
    if (Name == "_Nonnull" && SyntaxUsed == 3 && Scope == "")
        return 0;
    break;
  }
  case AT_TypeNullUnspecified: {
    if (Name == "_Null_unspecified" && SyntaxUsed == 3 && Scope == "")
        return 0;
    break;
  }
  case AT_TypeNullable: {
    if (Name == "_Nullable" && SyntaxUsed == 3 && Scope == "")
        return 0;
    break;
  }
  case AT_TypeTagForDatatype: {
    if (Name == "type_tag_for_datatype" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_TypeVisibility: {
    if (Name == "type_visibility" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "type_visibility" && SyntaxUsed == 1 && Scope == "clang")
        return 1;
    break;
  }
  case AT_UPtr: {
    if (Name == "__uptr" && SyntaxUsed == 3 && Scope == "")
        return 0;
    break;
  }
  case AT_Unavailable: {
    if (Name == "unavailable" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_Unused: {
    if (Name == "unused" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "unused" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_Used: {
    if (Name == "used" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "used" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_Uuid: {
    if (Name == "uuid" && SyntaxUsed == 2 && Scope == "")
        return 0;
    break;
  }
  case AT_VKBinding: {
    if (Name == "binding" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKBuiltIn: {
    if (Name == "builtin" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKCapabilityExt: {
    if (Name == "ext_capability" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKCombinedImageSampler: {
    if (Name == "combinedImageSampler" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKConstantId: {
    if (Name == "constant_id" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKCounterBinding: {
    if (Name == "counter_binding" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKDecorateExt: {
    if (Name == "ext_decorate" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKDecorateIdExt: {
    if (Name == "ext_decorate_id" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKDecorateStringExt: {
    if (Name == "ext_decorate_string" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKDepthUnchanged: {
    if (Name == "depth_unchanged" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKEarlyAndLateTests: {
    if (Name == "early_and_late_tests" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKExtensionExt: {
    if (Name == "ext_extension" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKImageFormat: {
    if (Name == "image_format" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKIndex: {
    if (Name == "index" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKInputAttachmentIndex: {
    if (Name == "input_attachment_index" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKInstructionExt: {
    if (Name == "ext_instruction" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKLiteralExt: {
    if (Name == "ext_literal" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKLocation: {
    if (Name == "location" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKOffset: {
    if (Name == "offset" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKPostDepthCoverage: {
    if (Name == "post_depth_coverage" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKPushConstant: {
    if (Name == "push_constant" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKReferenceExt: {
    if (Name == "ext_reference" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKShaderRecordEXT: {
    if (Name == "shader_record_ext" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKShaderRecordNV: {
    if (Name == "shader_record_nv" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKSpvExecutionMode: {
    if (Name == "spvexecutionmode" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKStencilRefGreaterEqualBack: {
    if (Name == "stencil_ref_greater_equal_back" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKStencilRefGreaterEqualFront: {
    if (Name == "stencil_ref_greater_equal_front" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKStencilRefLessEqualBack: {
    if (Name == "stencil_ref_less_equal_back" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKStencilRefLessEqualFront: {
    if (Name == "stencil_ref_less_equal_front" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKStencilRefUnchangedBack: {
    if (Name == "stencil_ref_unchanged_back" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKStencilRefUnchangedFront: {
    if (Name == "stencil_ref_unchanged_front" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKStorageClassExt: {
    if (Name == "ext_storage_class" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VKTypeDefExt: {
    if (Name == "ext_type_def" && SyntaxUsed == 1 && Scope == "vk")
        return 0;
    break;
  }
  case AT_VecReturn: {
    if (Name == "vecreturn" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_VecTypeHint: {
    if (Name == "vec_type_hint" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_VectorCall: {
    if (Name == "vectorcall" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "__vectorcall" && SyntaxUsed == 3 && Scope == "")
        return 1;
    if (Name == "_vectorcall" && SyntaxUsed == 3 && Scope == "")
        return 2;
    break;
  }
  case AT_VectorSize: {
    if (Name == "vector_size" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "vector_size" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_Visibility: {
    if (Name == "visibility" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "visibility" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_WarnUnused: {
    if (Name == "warn_unused" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_WarnUnusedResult: {
    if (Name == "warn_unused_result" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "warn_unused_result" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    if (Name == "warn_unused_result" && SyntaxUsed == 1 && Scope == "clang")
        return 2;
    break;
  }
  case AT_Weak: {
    if (Name == "weak" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "weak" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_WeakImport: {
    if (Name == "weak_import" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_WeakRef: {
    if (Name == "weakref" && SyntaxUsed == 0 && Scope == "")
        return 0;
    if (Name == "weakref" && SyntaxUsed == 1 && Scope == "gnu")
        return 1;
    break;
  }
  case AT_WorkGroupSizeHint: {
    if (Name == "work_group_size_hint" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  case AT_X86ForceAlignArgPointer: {
    if (Name == "force_align_arg_pointer" && SyntaxUsed == 0 && Scope == "")
        return 0;
    break;
  }
  }
  return 0;
