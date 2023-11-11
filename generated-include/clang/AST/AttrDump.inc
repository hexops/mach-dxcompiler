/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Attribute dumper                                                           *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

  switch (A->getKind()) {
  default:
    llvm_unreachable("Unknown attribute kind!");
    break;
  case attr::AMDGPUNumSGPR: {
    const AMDGPUNumSGPRAttr *SA = cast<AMDGPUNumSGPRAttr>(A);
    OS << " " << SA->getNumSGPR();
    break;
  }
  case attr::AMDGPUNumVGPR: {
    const AMDGPUNumVGPRAttr *SA = cast<AMDGPUNumVGPRAttr>(A);
    OS << " " << SA->getNumVGPR();
    break;
  }
  case attr::ARMInterrupt: {
    const ARMInterruptAttr *SA = cast<ARMInterruptAttr>(A);
    switch(SA->getInterrupt()) {
    case ARMInterruptAttr::IRQ:
      OS << " IRQ";
      break;
    case ARMInterruptAttr::FIQ:
      OS << " FIQ";
      break;
    case ARMInterruptAttr::SWI:
      OS << " SWI";
      break;
    case ARMInterruptAttr::ABORT:
      OS << " ABORT";
      break;
    case ARMInterruptAttr::UNDEF:
      OS << " UNDEF";
      break;
    case ARMInterruptAttr::Generic:
      OS << " Generic";
      break;
    }
    break;
  }
  case attr::AcquireCapability: {
    OS << " " << A->getSpelling();
    const AcquireCapabilityAttr *SA = cast<AcquireCapabilityAttr>(A);
    for (AcquireCapabilityAttr::args_iterator I = SA->args_begin(), E = SA->args_end(); I != E; ++I)
      dumpStmt(*I);
    break;
  }
  case attr::AcquiredAfter: {
    const AcquiredAfterAttr *SA = cast<AcquiredAfterAttr>(A);
    for (AcquiredAfterAttr::args_iterator I = SA->args_begin(), E = SA->args_end(); I != E; ++I)
      dumpStmt(*I);
    break;
  }
  case attr::AcquiredBefore: {
    const AcquiredBeforeAttr *SA = cast<AcquiredBeforeAttr>(A);
    for (AcquiredBeforeAttr::args_iterator I = SA->args_begin(), E = SA->args_end(); I != E; ++I)
      dumpStmt(*I);
    break;
  }
  case attr::Alias: {
    const AliasAttr *SA = cast<AliasAttr>(A);
    OS << " \"" << SA->getAliasee() << "\"";
    break;
  }
  case attr::AlignMac68k: {
    break;
  }
  case attr::AlignValue: {
    const AlignValueAttr *SA = cast<AlignValueAttr>(A);
    dumpStmt(SA->getAlignment());
    break;
  }
  case attr::Aligned: {
    OS << " " << A->getSpelling();
    const AlignedAttr *SA = cast<AlignedAttr>(A);
    if (SA->isAlignmentExpr())
      dumpStmt(SA->getAlignmentExpr());
    else
      dumpType(SA->getAlignmentType()->getType());
    break;
  }
  case attr::AlwaysInline: {
    OS << " " << A->getSpelling();
    break;
  }
  case attr::AnalyzerNoReturn: {
    break;
  }
  case attr::Annotate: {
    const AnnotateAttr *SA = cast<AnnotateAttr>(A);
    OS << " \"" << SA->getAnnotation() << "\"";
    break;
  }
  case attr::ArcWeakrefUnavailable: {
    break;
  }
  case attr::ArgumentWithTypeTag: {
    OS << " " << A->getSpelling();
    const ArgumentWithTypeTagAttr *SA = cast<ArgumentWithTypeTagAttr>(A);
    OS << " " << SA->getArgumentKind()->getName();
    OS << " " << SA->getArgumentIdx();
    OS << " " << SA->getTypeTagIdx();
    if (SA->getIsPointer()) OS << " IsPointer";
    break;
  }
  case attr::AsmLabel: {
    const AsmLabelAttr *SA = cast<AsmLabelAttr>(A);
    OS << " \"" << SA->getLabel() << "\"";
    break;
  }
  case attr::AssertCapability: {
    OS << " " << A->getSpelling();
    const AssertCapabilityAttr *SA = cast<AssertCapabilityAttr>(A);
    dumpStmt(SA->getExpr());
    break;
  }
  case attr::AssertExclusiveLock: {
    const AssertExclusiveLockAttr *SA = cast<AssertExclusiveLockAttr>(A);
    for (AssertExclusiveLockAttr::args_iterator I = SA->args_begin(), E = SA->args_end(); I != E; ++I)
      dumpStmt(*I);
    break;
  }
  case attr::AssertSharedLock: {
    const AssertSharedLockAttr *SA = cast<AssertSharedLockAttr>(A);
    for (AssertSharedLockAttr::args_iterator I = SA->args_begin(), E = SA->args_end(); I != E; ++I)
      dumpStmt(*I);
    break;
  }
  case attr::AssumeAligned: {
    const AssumeAlignedAttr *SA = cast<AssumeAlignedAttr>(A);
    dumpStmt(SA->getAlignment());
    dumpStmt(SA->getOffset());
    break;
  }
  case attr::Availability: {
    const AvailabilityAttr *SA = cast<AvailabilityAttr>(A);
    OS << " " << SA->getPlatform()->getName();
    OS << " " << SA->getIntroduced();
    OS << " " << SA->getDeprecated();
    OS << " " << SA->getObsoleted();
    if (SA->getUnavailable()) OS << " Unavailable";
    OS << " \"" << SA->getMessage() << "\"";
    break;
  }
  case attr::Blocks: {
    const BlocksAttr *SA = cast<BlocksAttr>(A);
    switch(SA->getType()) {
    case BlocksAttr::ByRef:
      OS << " ByRef";
      break;
    }
    break;
  }
  case attr::C11NoReturn: {
    break;
  }
  case attr::CDecl: {
    break;
  }
  case attr::CFAuditedTransfer: {
    break;
  }
  case attr::CFConsumed: {
    break;
  }
  case attr::CFReturnsNotRetained: {
    break;
  }
  case attr::CFReturnsRetained: {
    break;
  }
  case attr::CFUnknownTransfer: {
    break;
  }
  case attr::CUDAConstant: {
    break;
  }
  case attr::CUDADevice: {
    break;
  }
  case attr::CUDAGlobal: {
    break;
  }
  case attr::CUDAHost: {
    break;
  }
  case attr::CUDAInvalidTarget: {
    break;
  }
  case attr::CUDALaunchBounds: {
    const CUDALaunchBoundsAttr *SA = cast<CUDALaunchBoundsAttr>(A);
    dumpStmt(SA->getMaxThreads());
    dumpStmt(SA->getMinBlocks());
    break;
  }
  case attr::CUDAShared: {
    break;
  }
  case attr::CXX11NoReturn: {
    break;
  }
  case attr::CallableWhen: {
    const CallableWhenAttr *SA = cast<CallableWhenAttr>(A);
    for (CallableWhenAttr::callableStates_iterator I = SA->callableStates_begin(), E = SA->callableStates_end(); I != E; ++I) {
      switch(*I) {
    case CallableWhenAttr::Unknown:
      OS << " Unknown";
      break;
    case CallableWhenAttr::Consumed:
      OS << " Consumed";
      break;
    case CallableWhenAttr::Unconsumed:
      OS << " Unconsumed";
      break;
      }
    }
    break;
  }
  case attr::Capability: {
    OS << " " << A->getSpelling();
    const CapabilityAttr *SA = cast<CapabilityAttr>(A);
    OS << " \"" << SA->getName() << "\"";
    break;
  }
  case attr::CapturedRecord: {
    break;
  }
  case attr::CarriesDependency: {
    break;
  }
  case attr::Cleanup: {
    const CleanupAttr *SA = cast<CleanupAttr>(A);
    OS << " ";
    dumpBareDeclRef(SA->getFunctionDecl());
    break;
  }
  case attr::Cold: {
    break;
  }
  case attr::Common: {
    break;
  }
  case attr::Const: {
    break;
  }
  case attr::Constructor: {
    const ConstructorAttr *SA = cast<ConstructorAttr>(A);
    OS << " " << SA->getPriority();
    break;
  }
  case attr::Consumable: {
    const ConsumableAttr *SA = cast<ConsumableAttr>(A);
    switch(SA->getDefaultState()) {
    case ConsumableAttr::Unknown:
      OS << " Unknown";
      break;
    case ConsumableAttr::Consumed:
      OS << " Consumed";
      break;
    case ConsumableAttr::Unconsumed:
      OS << " Unconsumed";
      break;
    }
    break;
  }
  case attr::ConsumableAutoCast: {
    break;
  }
  case attr::ConsumableSetOnRead: {
    break;
  }
  case attr::DLLExport: {
    break;
  }
  case attr::DLLImport: {
    break;
  }
  case attr::Deprecated: {
    const DeprecatedAttr *SA = cast<DeprecatedAttr>(A);
    OS << " \"" << SA->getMessage() << "\"";
    break;
  }
  case attr::Destructor: {
    const DestructorAttr *SA = cast<DestructorAttr>(A);
    OS << " " << SA->getPriority();
    break;
  }
  case attr::EnableIf: {
    const EnableIfAttr *SA = cast<EnableIfAttr>(A);
    OS << " \"" << SA->getMessage() << "\"";
    dumpStmt(SA->getCond());
    break;
  }
  case attr::ExclusiveTrylockFunction: {
    const ExclusiveTrylockFunctionAttr *SA = cast<ExclusiveTrylockFunctionAttr>(A);
    dumpStmt(SA->getSuccessValue());
    for (ExclusiveTrylockFunctionAttr::args_iterator I = SA->args_begin(), E = SA->args_end(); I != E; ++I)
      dumpStmt(*I);
    break;
  }
  case attr::FallThrough: {
    break;
  }
  case attr::FastCall: {
    break;
  }
  case attr::Final: {
    OS << " " << A->getSpelling();
    break;
  }
  case attr::FlagEnum: {
    break;
  }
  case attr::Flatten: {
    break;
  }
  case attr::Format: {
    const FormatAttr *SA = cast<FormatAttr>(A);
    OS << " " << SA->getType()->getName();
    OS << " " << SA->getFormatIdx();
    OS << " " << SA->getFirstArg();
    break;
  }
  case attr::FormatArg: {
    const FormatArgAttr *SA = cast<FormatArgAttr>(A);
    OS << " " << SA->getFormatIdx();
    break;
  }
  case attr::GNUInline: {
    break;
  }
  case attr::GuardedBy: {
    const GuardedByAttr *SA = cast<GuardedByAttr>(A);
    dumpStmt(SA->getArg());
    break;
  }
  case attr::GuardedVar: {
    break;
  }
  case attr::HLSLAllowUAVCondition: {
    break;
  }
  case attr::HLSLBranch: {
    break;
  }
  case attr::HLSLCXXOverload: {
    break;
  }
  case attr::HLSLCall: {
    break;
  }
  case attr::HLSLCenter: {
    break;
  }
  case attr::HLSLCentroid: {
    break;
  }
  case attr::HLSLClipPlanes: {
    const HLSLClipPlanesAttr *SA = cast<HLSLClipPlanesAttr>(A);
    dumpStmt(SA->getClipPlane1());
    dumpStmt(SA->getClipPlane2());
    dumpStmt(SA->getClipPlane3());
    dumpStmt(SA->getClipPlane4());
    dumpStmt(SA->getClipPlane5());
    dumpStmt(SA->getClipPlane6());
    break;
  }
  case attr::HLSLDomain: {
    const HLSLDomainAttr *SA = cast<HLSLDomainAttr>(A);
    OS << " \"" << SA->getDomainType() << "\"";
    break;
  }
  case attr::HLSLEarlyDepthStencil: {
    break;
  }
  case attr::HLSLExperimental: {
    const HLSLExperimentalAttr *SA = cast<HLSLExperimentalAttr>(A);
    OS << " \"" << SA->getName() << "\"";
    OS << " \"" << SA->getValue() << "\"";
    break;
  }
  case attr::HLSLExport: {
    break;
  }
  case attr::HLSLFastOpt: {
    break;
  }
  case attr::HLSLFlatten: {
    break;
  }
  case attr::HLSLForceCase: {
    break;
  }
  case attr::HLSLGloballyCoherent: {
    break;
  }
  case attr::HLSLGroupShared: {
    break;
  }
  case attr::HLSLIn: {
    break;
  }
  case attr::HLSLInOut: {
    break;
  }
  case attr::HLSLIndices: {
    break;
  }
  case attr::HLSLInstance: {
    const HLSLInstanceAttr *SA = cast<HLSLInstanceAttr>(A);
    OS << " " << SA->getCount();
    break;
  }
  case attr::HLSLIntrinsic: {
    const HLSLIntrinsicAttr *SA = cast<HLSLIntrinsicAttr>(A);
    OS << " \"" << SA->getGroup() << "\"";
    OS << " \"" << SA->getLowering() << "\"";
    OS << " " << SA->getOpcode();
    break;
  }
  case attr::HLSLLine: {
    break;
  }
  case attr::HLSLLineAdj: {
    break;
  }
  case attr::HLSLLinear: {
    break;
  }
  case attr::HLSLLoop: {
    break;
  }
  case attr::HLSLMaxTessFactor: {
    const HLSLMaxTessFactorAttr *SA = cast<HLSLMaxTessFactorAttr>(A);
    OS << " " << SA->getFactor();
    break;
  }
  case attr::HLSLMaxVertexCount: {
    const HLSLMaxVertexCountAttr *SA = cast<HLSLMaxVertexCountAttr>(A);
    OS << " " << SA->getCount();
    break;
  }
  case attr::HLSLMaybeUnused: {
    break;
  }
  case attr::HLSLNoInterpolation: {
    break;
  }
  case attr::HLSLNoPerspective: {
    break;
  }
  case attr::HLSLNumThreads: {
    const HLSLNumThreadsAttr *SA = cast<HLSLNumThreadsAttr>(A);
    OS << " " << SA->getX();
    OS << " " << SA->getY();
    OS << " " << SA->getZ();
    break;
  }
  case attr::HLSLOut: {
    break;
  }
  case attr::HLSLOutputControlPoints: {
    const HLSLOutputControlPointsAttr *SA = cast<HLSLOutputControlPointsAttr>(A);
    OS << " " << SA->getCount();
    break;
  }
  case attr::HLSLOutputTopology: {
    const HLSLOutputTopologyAttr *SA = cast<HLSLOutputTopologyAttr>(A);
    OS << " \"" << SA->getTopology() << "\"";
    break;
  }
  case attr::HLSLPartitioning: {
    const HLSLPartitioningAttr *SA = cast<HLSLPartitioningAttr>(A);
    OS << " \"" << SA->getScheme() << "\"";
    break;
  }
  case attr::HLSLPatchConstantFunc: {
    const HLSLPatchConstantFuncAttr *SA = cast<HLSLPatchConstantFuncAttr>(A);
    OS << " \"" << SA->getFunctionName() << "\"";
    break;
  }
  case attr::HLSLPayload: {
    break;
  }
  case attr::HLSLPoint: {
    break;
  }
  case attr::HLSLPrecise: {
    break;
  }
  case attr::HLSLPrimitives: {
    break;
  }
  case attr::HLSLRayPayload: {
    break;
  }
  case attr::HLSLRootSignature: {
    const HLSLRootSignatureAttr *SA = cast<HLSLRootSignatureAttr>(A);
    OS << " \"" << SA->getSignatureName() << "\"";
    break;
  }
  case attr::HLSLSample: {
    break;
  }
  case attr::HLSLSemantic: {
    const HLSLSemanticAttr *SA = cast<HLSLSemanticAttr>(A);
    OS << " \"" << SA->getName() << "\"";
    break;
  }
  case attr::HLSLShader: {
    const HLSLShaderAttr *SA = cast<HLSLShaderAttr>(A);
    OS << " \"" << SA->getStage() << "\"";
    break;
  }
  case attr::HLSLShared: {
    break;
  }
  case attr::HLSLSnorm: {
    break;
  }
  case attr::HLSLTriangle: {
    break;
  }
  case attr::HLSLTriangleAdj: {
    break;
  }
  case attr::HLSLUniform: {
    break;
  }
  case attr::HLSLUnorm: {
    break;
  }
  case attr::HLSLUnroll: {
    const HLSLUnrollAttr *SA = cast<HLSLUnrollAttr>(A);
    OS << " " << SA->getCount();
    break;
  }
  case attr::HLSLVertices: {
    break;
  }
  case attr::HLSLWaveOpsIncludeHelperLanes: {
    break;
  }
  case attr::HLSLWaveSensitive: {
    break;
  }
  case attr::HLSLWaveSize: {
    const HLSLWaveSizeAttr *SA = cast<HLSLWaveSizeAttr>(A);
    OS << " " << SA->getSize();
    break;
  }
  case attr::Hot: {
    break;
  }
  case attr::IBAction: {
    break;
  }
  case attr::IBOutlet: {
    break;
  }
  case attr::IBOutletCollection: {
    const IBOutletCollectionAttr *SA = cast<IBOutletCollectionAttr>(A);
    OS << " " << SA->getInterface().getAsString();
    break;
  }
  case attr::InitPriority: {
    const InitPriorityAttr *SA = cast<InitPriorityAttr>(A);
    OS << " " << SA->getPriority();
    break;
  }
  case attr::InitSeg: {
    const InitSegAttr *SA = cast<InitSegAttr>(A);
    OS << " \"" << SA->getSection() << "\"";
    break;
  }
  case attr::IntelOclBicc: {
    break;
  }
  case attr::LockReturned: {
    const LockReturnedAttr *SA = cast<LockReturnedAttr>(A);
    dumpStmt(SA->getArg());
    break;
  }
  case attr::LocksExcluded: {
    const LocksExcludedAttr *SA = cast<LocksExcludedAttr>(A);
    for (LocksExcludedAttr::args_iterator I = SA->args_begin(), E = SA->args_end(); I != E; ++I)
      dumpStmt(*I);
    break;
  }
  case attr::LoopHint: {
    OS << " " << A->getSpelling();
    const LoopHintAttr *SA = cast<LoopHintAttr>(A);
    switch(SA->getOption()) {
    case LoopHintAttr::Vectorize:
      OS << " Vectorize";
      break;
    case LoopHintAttr::VectorizeWidth:
      OS << " VectorizeWidth";
      break;
    case LoopHintAttr::Interleave:
      OS << " Interleave";
      break;
    case LoopHintAttr::InterleaveCount:
      OS << " InterleaveCount";
      break;
    case LoopHintAttr::Unroll:
      OS << " Unroll";
      break;
    case LoopHintAttr::UnrollCount:
      OS << " UnrollCount";
      break;
    }
    switch(SA->getState()) {
    case LoopHintAttr::Default:
      OS << " Default";
      break;
    case LoopHintAttr::Enable:
      OS << " Enable";
      break;
    case LoopHintAttr::Disable:
      OS << " Disable";
      break;
    case LoopHintAttr::AssumeSafety:
      OS << " AssumeSafety";
      break;
    }
    dumpStmt(SA->getValue());
    break;
  }
  case attr::MSABI: {
    break;
  }
  case attr::MSInheritance: {
    OS << " " << A->getSpelling();
    const MSInheritanceAttr *SA = cast<MSInheritanceAttr>(A);
    if (SA->getBestCase()) OS << " BestCase";
    break;
  }
  case attr::MSNoVTable: {
    break;
  }
  case attr::MSP430Interrupt: {
    const MSP430InterruptAttr *SA = cast<MSP430InterruptAttr>(A);
    OS << " " << SA->getNumber();
    break;
  }
  case attr::MSStruct: {
    break;
  }
  case attr::MSVtorDisp: {
    const MSVtorDispAttr *SA = cast<MSVtorDispAttr>(A);
    OS << " " << SA->getVdm();
    break;
  }
  case attr::MaxFieldAlignment: {
    const MaxFieldAlignmentAttr *SA = cast<MaxFieldAlignmentAttr>(A);
    OS << " " << SA->getAlignment();
    break;
  }
  case attr::MayAlias: {
    break;
  }
  case attr::MinSize: {
    break;
  }
  case attr::Mips16: {
    break;
  }
  case attr::Mode: {
    const ModeAttr *SA = cast<ModeAttr>(A);
    OS << " " << SA->getMode()->getName();
    break;
  }
  case attr::NSConsumed: {
    break;
  }
  case attr::NSConsumesSelf: {
    break;
  }
  case attr::NSReturnsAutoreleased: {
    break;
  }
  case attr::NSReturnsNotRetained: {
    break;
  }
  case attr::NSReturnsRetained: {
    break;
  }
  case attr::Naked: {
    break;
  }
  case attr::NoCommon: {
    break;
  }
  case attr::NoDebug: {
    break;
  }
  case attr::NoDuplicate: {
    break;
  }
  case attr::NoInline: {
    break;
  }
  case attr::NoInstrumentFunction: {
    break;
  }
  case attr::NoMips16: {
    break;
  }
  case attr::NoReturn: {
    break;
  }
  case attr::NoSanitize: {
    const NoSanitizeAttr *SA = cast<NoSanitizeAttr>(A);
    for (const auto &Val : SA->sanitizers())
      OS << " " << Val;
    break;
  }
  case attr::NoSplitStack: {
    break;
  }
  case attr::NoThreadSafetyAnalysis: {
    break;
  }
  case attr::NoThrow: {
    break;
  }
  case attr::NonNull: {
    const NonNullAttr *SA = cast<NonNullAttr>(A);
    for (const auto &Val : SA->args())
      OS << " " << Val;
    break;
  }
  case attr::OMPThreadPrivateDecl: {
    break;
  }
  case attr::ObjCBoxable: {
    break;
  }
  case attr::ObjCBridge: {
    const ObjCBridgeAttr *SA = cast<ObjCBridgeAttr>(A);
    OS << " " << SA->getBridgedType()->getName();
    break;
  }
  case attr::ObjCBridgeMutable: {
    const ObjCBridgeMutableAttr *SA = cast<ObjCBridgeMutableAttr>(A);
    OS << " " << SA->getBridgedType()->getName();
    break;
  }
  case attr::ObjCBridgeRelated: {
    const ObjCBridgeRelatedAttr *SA = cast<ObjCBridgeRelatedAttr>(A);
    OS << " " << SA->getRelatedClass()->getName();
    OS << " " << SA->getClassMethod()->getName();
    OS << " " << SA->getInstanceMethod()->getName();
    break;
  }
  case attr::ObjCDesignatedInitializer: {
    break;
  }
  case attr::ObjCException: {
    break;
  }
  case attr::ObjCExplicitProtocolImpl: {
    break;
  }
  case attr::ObjCIndependentClass: {
    break;
  }
  case attr::ObjCMethodFamily: {
    const ObjCMethodFamilyAttr *SA = cast<ObjCMethodFamilyAttr>(A);
    switch(SA->getFamily()) {
    case ObjCMethodFamilyAttr::OMF_None:
      OS << " OMF_None";
      break;
    case ObjCMethodFamilyAttr::OMF_alloc:
      OS << " OMF_alloc";
      break;
    case ObjCMethodFamilyAttr::OMF_copy:
      OS << " OMF_copy";
      break;
    case ObjCMethodFamilyAttr::OMF_init:
      OS << " OMF_init";
      break;
    case ObjCMethodFamilyAttr::OMF_mutableCopy:
      OS << " OMF_mutableCopy";
      break;
    case ObjCMethodFamilyAttr::OMF_new:
      OS << " OMF_new";
      break;
    }
    break;
  }
  case attr::ObjCNSObject: {
    break;
  }
  case attr::ObjCPreciseLifetime: {
    break;
  }
  case attr::ObjCRequiresPropertyDefs: {
    break;
  }
  case attr::ObjCRequiresSuper: {
    break;
  }
  case attr::ObjCReturnsInnerPointer: {
    break;
  }
  case attr::ObjCRootClass: {
    break;
  }
  case attr::ObjCRuntimeName: {
    const ObjCRuntimeNameAttr *SA = cast<ObjCRuntimeNameAttr>(A);
    OS << " \"" << SA->getMetadataName() << "\"";
    break;
  }
  case attr::OpenCLImageAccess: {
    OS << " " << A->getSpelling();
    break;
  }
  case attr::OpenCLKernel: {
    break;
  }
  case attr::OptimizeNone: {
    break;
  }
  case attr::Overloadable: {
    break;
  }
  case attr::Override: {
    break;
  }
  case attr::Ownership: {
    OS << " " << A->getSpelling();
    const OwnershipAttr *SA = cast<OwnershipAttr>(A);
    OS << " " << SA->getModule()->getName();
    for (const auto &Val : SA->args())
      OS << " " << Val;
    break;
  }
  case attr::Packed: {
    break;
  }
  case attr::ParamTypestate: {
    const ParamTypestateAttr *SA = cast<ParamTypestateAttr>(A);
    switch(SA->getParamState()) {
    case ParamTypestateAttr::Unknown:
      OS << " Unknown";
      break;
    case ParamTypestateAttr::Consumed:
      OS << " Consumed";
      break;
    case ParamTypestateAttr::Unconsumed:
      OS << " Unconsumed";
      break;
    }
    break;
  }
  case attr::Pascal: {
    break;
  }
  case attr::Pcs: {
    const PcsAttr *SA = cast<PcsAttr>(A);
    switch(SA->getPCS()) {
    case PcsAttr::AAPCS:
      OS << " AAPCS";
      break;
    case PcsAttr::AAPCS_VFP:
      OS << " AAPCS_VFP";
      break;
    }
    break;
  }
  case attr::PtGuardedBy: {
    const PtGuardedByAttr *SA = cast<PtGuardedByAttr>(A);
    dumpStmt(SA->getArg());
    break;
  }
  case attr::PtGuardedVar: {
    break;
  }
  case attr::Pure: {
    break;
  }
  case attr::ReleaseCapability: {
    OS << " " << A->getSpelling();
    const ReleaseCapabilityAttr *SA = cast<ReleaseCapabilityAttr>(A);
    for (ReleaseCapabilityAttr::args_iterator I = SA->args_begin(), E = SA->args_end(); I != E; ++I)
      dumpStmt(*I);
    break;
  }
  case attr::ReqdWorkGroupSize: {
    const ReqdWorkGroupSizeAttr *SA = cast<ReqdWorkGroupSizeAttr>(A);
    OS << " " << SA->getXDim();
    OS << " " << SA->getYDim();
    OS << " " << SA->getZDim();
    break;
  }
  case attr::RequiresCapability: {
    OS << " " << A->getSpelling();
    const RequiresCapabilityAttr *SA = cast<RequiresCapabilityAttr>(A);
    for (RequiresCapabilityAttr::args_iterator I = SA->args_begin(), E = SA->args_end(); I != E; ++I)
      dumpStmt(*I);
    break;
  }
  case attr::Restrict: {
    OS << " " << A->getSpelling();
    break;
  }
  case attr::ReturnTypestate: {
    const ReturnTypestateAttr *SA = cast<ReturnTypestateAttr>(A);
    switch(SA->getState()) {
    case ReturnTypestateAttr::Unknown:
      OS << " Unknown";
      break;
    case ReturnTypestateAttr::Consumed:
      OS << " Consumed";
      break;
    case ReturnTypestateAttr::Unconsumed:
      OS << " Unconsumed";
      break;
    }
    break;
  }
  case attr::ReturnsNonNull: {
    break;
  }
  case attr::ReturnsTwice: {
    break;
  }
  case attr::ScopedLockable: {
    break;
  }
  case attr::Section: {
    OS << " " << A->getSpelling();
    const SectionAttr *SA = cast<SectionAttr>(A);
    OS << " \"" << SA->getName() << "\"";
    break;
  }
  case attr::SelectAny: {
    break;
  }
  case attr::Sentinel: {
    const SentinelAttr *SA = cast<SentinelAttr>(A);
    OS << " " << SA->getSentinel();
    OS << " " << SA->getNullPos();
    break;
  }
  case attr::SetTypestate: {
    const SetTypestateAttr *SA = cast<SetTypestateAttr>(A);
    switch(SA->getNewState()) {
    case SetTypestateAttr::Unknown:
      OS << " Unknown";
      break;
    case SetTypestateAttr::Consumed:
      OS << " Consumed";
      break;
    case SetTypestateAttr::Unconsumed:
      OS << " Unconsumed";
      break;
    }
    break;
  }
  case attr::SharedTrylockFunction: {
    const SharedTrylockFunctionAttr *SA = cast<SharedTrylockFunctionAttr>(A);
    dumpStmt(SA->getSuccessValue());
    for (SharedTrylockFunctionAttr::args_iterator I = SA->args_begin(), E = SA->args_end(); I != E; ++I)
      dumpStmt(*I);
    break;
  }
  case attr::StdCall: {
    break;
  }
  case attr::SysVABI: {
    break;
  }
  case attr::TLSModel: {
    const TLSModelAttr *SA = cast<TLSModelAttr>(A);
    OS << " \"" << SA->getModel() << "\"";
    break;
  }
  case attr::Target: {
    const TargetAttr *SA = cast<TargetAttr>(A);
    OS << " \"" << SA->getFeatures() << "\"";
    break;
  }
  case attr::TestTypestate: {
    const TestTypestateAttr *SA = cast<TestTypestateAttr>(A);
    switch(SA->getTestState()) {
    case TestTypestateAttr::Consumed:
      OS << " Consumed";
      break;
    case TestTypestateAttr::Unconsumed:
      OS << " Unconsumed";
      break;
    }
    break;
  }
  case attr::ThisCall: {
    break;
  }
  case attr::Thread: {
    break;
  }
  case attr::TransparentUnion: {
    break;
  }
  case attr::TryAcquireCapability: {
    OS << " " << A->getSpelling();
    const TryAcquireCapabilityAttr *SA = cast<TryAcquireCapabilityAttr>(A);
    dumpStmt(SA->getSuccessValue());
    for (TryAcquireCapabilityAttr::args_iterator I = SA->args_begin(), E = SA->args_end(); I != E; ++I)
      dumpStmt(*I);
    break;
  }
  case attr::TypeTagForDatatype: {
    const TypeTagForDatatypeAttr *SA = cast<TypeTagForDatatypeAttr>(A);
    OS << " " << SA->getArgumentKind()->getName();
    OS << " " << SA->getMatchingCType().getAsString();
    if (SA->getLayoutCompatible()) OS << " LayoutCompatible";
    if (SA->getMustBeNull()) OS << " MustBeNull";
    break;
  }
  case attr::TypeVisibility: {
    const TypeVisibilityAttr *SA = cast<TypeVisibilityAttr>(A);
    switch(SA->getVisibility()) {
    case TypeVisibilityAttr::Default:
      OS << " Default";
      break;
    case TypeVisibilityAttr::Hidden:
      OS << " Hidden";
      break;
    case TypeVisibilityAttr::Protected:
      OS << " Protected";
      break;
    }
    break;
  }
  case attr::Unavailable: {
    const UnavailableAttr *SA = cast<UnavailableAttr>(A);
    OS << " \"" << SA->getMessage() << "\"";
    break;
  }
  case attr::Unused: {
    break;
  }
  case attr::Used: {
    break;
  }
  case attr::Uuid: {
    const UuidAttr *SA = cast<UuidAttr>(A);
    OS << " \"" << SA->getGuid() << "\"";
    break;
  }
  case attr::VKBinding: {
    const VKBindingAttr *SA = cast<VKBindingAttr>(A);
    OS << " " << SA->getBinding();
    OS << " " << SA->getSet();
    break;
  }
  case attr::VKBuiltIn: {
    const VKBuiltInAttr *SA = cast<VKBuiltInAttr>(A);
    OS << " \"" << SA->getBuiltIn() << "\"";
    break;
  }
  case attr::VKCapabilityExt: {
    const VKCapabilityExtAttr *SA = cast<VKCapabilityExtAttr>(A);
    OS << " " << SA->getCapability();
    break;
  }
  case attr::VKCombinedImageSampler: {
    break;
  }
  case attr::VKConstantId: {
    const VKConstantIdAttr *SA = cast<VKConstantIdAttr>(A);
    OS << " " << SA->getSpecConstId();
    break;
  }
  case attr::VKCounterBinding: {
    const VKCounterBindingAttr *SA = cast<VKCounterBindingAttr>(A);
    OS << " " << SA->getBinding();
    break;
  }
  case attr::VKDecorateExt: {
    const VKDecorateExtAttr *SA = cast<VKDecorateExtAttr>(A);
    OS << " " << SA->getDecorate();
    for (const auto &Val : SA->literals())
      OS << " " << Val;
    break;
  }
  case attr::VKDecorateIdExt: {
    const VKDecorateIdExtAttr *SA = cast<VKDecorateIdExtAttr>(A);
    OS << " " << SA->getDecorate();
    for (VKDecorateIdExtAttr::arguments_iterator I = SA->arguments_begin(), E = SA->arguments_end(); I != E; ++I)
      dumpStmt(*I);
    break;
  }
  case attr::VKDecorateStringExt: {
    const VKDecorateStringExtAttr *SA = cast<VKDecorateStringExtAttr>(A);
    OS << " " << SA->getDecorate();
    for (const auto &Val : SA->arguments())
      OS << " " << Val;
    break;
  }
  case attr::VKDepthUnchanged: {
    break;
  }
  case attr::VKEarlyAndLateTests: {
    break;
  }
  case attr::VKExtensionExt: {
    const VKExtensionExtAttr *SA = cast<VKExtensionExtAttr>(A);
    OS << " \"" << SA->getName() << "\"";
    break;
  }
  case attr::VKImageFormat: {
    const VKImageFormatAttr *SA = cast<VKImageFormatAttr>(A);
    switch(SA->getImageFormat()) {
    case VKImageFormatAttr::unknown:
      OS << " unknown";
      break;
    case VKImageFormatAttr::rgba32f:
      OS << " rgba32f";
      break;
    case VKImageFormatAttr::rgba16f:
      OS << " rgba16f";
      break;
    case VKImageFormatAttr::r32f:
      OS << " r32f";
      break;
    case VKImageFormatAttr::rgba8:
      OS << " rgba8";
      break;
    case VKImageFormatAttr::rgba8snorm:
      OS << " rgba8snorm";
      break;
    case VKImageFormatAttr::rg32f:
      OS << " rg32f";
      break;
    case VKImageFormatAttr::rg16f:
      OS << " rg16f";
      break;
    case VKImageFormatAttr::r11g11b10f:
      OS << " r11g11b10f";
      break;
    case VKImageFormatAttr::r16f:
      OS << " r16f";
      break;
    case VKImageFormatAttr::rgba16:
      OS << " rgba16";
      break;
    case VKImageFormatAttr::rgb10a2:
      OS << " rgb10a2";
      break;
    case VKImageFormatAttr::rg16:
      OS << " rg16";
      break;
    case VKImageFormatAttr::rg8:
      OS << " rg8";
      break;
    case VKImageFormatAttr::r16:
      OS << " r16";
      break;
    case VKImageFormatAttr::r8:
      OS << " r8";
      break;
    case VKImageFormatAttr::rgba16snorm:
      OS << " rgba16snorm";
      break;
    case VKImageFormatAttr::rg16snorm:
      OS << " rg16snorm";
      break;
    case VKImageFormatAttr::rg8snorm:
      OS << " rg8snorm";
      break;
    case VKImageFormatAttr::r16snorm:
      OS << " r16snorm";
      break;
    case VKImageFormatAttr::r8snorm:
      OS << " r8snorm";
      break;
    case VKImageFormatAttr::rgba32i:
      OS << " rgba32i";
      break;
    case VKImageFormatAttr::rgba16i:
      OS << " rgba16i";
      break;
    case VKImageFormatAttr::rgba8i:
      OS << " rgba8i";
      break;
    case VKImageFormatAttr::r32i:
      OS << " r32i";
      break;
    case VKImageFormatAttr::rg32i:
      OS << " rg32i";
      break;
    case VKImageFormatAttr::rg16i:
      OS << " rg16i";
      break;
    case VKImageFormatAttr::rg8i:
      OS << " rg8i";
      break;
    case VKImageFormatAttr::r16i:
      OS << " r16i";
      break;
    case VKImageFormatAttr::r8i:
      OS << " r8i";
      break;
    case VKImageFormatAttr::rgba32ui:
      OS << " rgba32ui";
      break;
    case VKImageFormatAttr::rgba16ui:
      OS << " rgba16ui";
      break;
    case VKImageFormatAttr::rgba8ui:
      OS << " rgba8ui";
      break;
    case VKImageFormatAttr::r32ui:
      OS << " r32ui";
      break;
    case VKImageFormatAttr::rgb10a2ui:
      OS << " rgb10a2ui";
      break;
    case VKImageFormatAttr::rg32ui:
      OS << " rg32ui";
      break;
    case VKImageFormatAttr::rg16ui:
      OS << " rg16ui";
      break;
    case VKImageFormatAttr::rg8ui:
      OS << " rg8ui";
      break;
    case VKImageFormatAttr::r16ui:
      OS << " r16ui";
      break;
    case VKImageFormatAttr::r8ui:
      OS << " r8ui";
      break;
    case VKImageFormatAttr::r64ui:
      OS << " r64ui";
      break;
    case VKImageFormatAttr::r64i:
      OS << " r64i";
      break;
    }
    break;
  }
  case attr::VKIndex: {
    const VKIndexAttr *SA = cast<VKIndexAttr>(A);
    OS << " " << SA->getNumber();
    break;
  }
  case attr::VKInputAttachmentIndex: {
    const VKInputAttachmentIndexAttr *SA = cast<VKInputAttachmentIndexAttr>(A);
    OS << " " << SA->getIndex();
    break;
  }
  case attr::VKInstructionExt: {
    const VKInstructionExtAttr *SA = cast<VKInstructionExtAttr>(A);
    OS << " " << SA->getOpcode();
    OS << " \"" << SA->getInstruction_set() << "\"";
    break;
  }
  case attr::VKLiteralExt: {
    break;
  }
  case attr::VKLocation: {
    const VKLocationAttr *SA = cast<VKLocationAttr>(A);
    OS << " " << SA->getNumber();
    break;
  }
  case attr::VKOffset: {
    const VKOffsetAttr *SA = cast<VKOffsetAttr>(A);
    OS << " " << SA->getOffset();
    break;
  }
  case attr::VKPostDepthCoverage: {
    break;
  }
  case attr::VKPushConstant: {
    break;
  }
  case attr::VKReferenceExt: {
    break;
  }
  case attr::VKShaderRecordEXT: {
    break;
  }
  case attr::VKShaderRecordNV: {
    break;
  }
  case attr::VKSpvExecutionMode: {
    const VKSpvExecutionModeAttr *SA = cast<VKSpvExecutionModeAttr>(A);
    OS << " " << SA->getExecutionMode();
    break;
  }
  case attr::VKStencilRefGreaterEqualBack: {
    break;
  }
  case attr::VKStencilRefGreaterEqualFront: {
    break;
  }
  case attr::VKStencilRefLessEqualBack: {
    break;
  }
  case attr::VKStencilRefLessEqualFront: {
    break;
  }
  case attr::VKStencilRefUnchangedBack: {
    break;
  }
  case attr::VKStencilRefUnchangedFront: {
    break;
  }
  case attr::VKStorageClassExt: {
    const VKStorageClassExtAttr *SA = cast<VKStorageClassExtAttr>(A);
    OS << " " << SA->getStclass();
    break;
  }
  case attr::VKTypeDefExt: {
    const VKTypeDefExtAttr *SA = cast<VKTypeDefExtAttr>(A);
    OS << " " << SA->getId();
    OS << " " << SA->getOpcode();
    break;
  }
  case attr::VecReturn: {
    break;
  }
  case attr::VecTypeHint: {
    const VecTypeHintAttr *SA = cast<VecTypeHintAttr>(A);
    OS << " " << SA->getTypeHint().getAsString();
    break;
  }
  case attr::VectorCall: {
    break;
  }
  case attr::Visibility: {
    const VisibilityAttr *SA = cast<VisibilityAttr>(A);
    switch(SA->getVisibility()) {
    case VisibilityAttr::Default:
      OS << " Default";
      break;
    case VisibilityAttr::Hidden:
      OS << " Hidden";
      break;
    case VisibilityAttr::Protected:
      OS << " Protected";
      break;
    }
    break;
  }
  case attr::WarnUnused: {
    break;
  }
  case attr::WarnUnusedResult: {
    break;
  }
  case attr::Weak: {
    break;
  }
  case attr::WeakImport: {
    break;
  }
  case attr::WeakRef: {
    const WeakRefAttr *SA = cast<WeakRefAttr>(A);
    OS << " \"" << SA->getAliasee() << "\"";
    break;
  }
  case attr::WorkGroupSizeHint: {
    const WorkGroupSizeHintAttr *SA = cast<WorkGroupSizeHintAttr>(A);
    OS << " " << SA->getXDim();
    OS << " " << SA->getYDim();
    OS << " " << SA->getZDim();
    break;
  }
  case attr::X86ForceAlignArgPointer: {
    break;
  }
  }
