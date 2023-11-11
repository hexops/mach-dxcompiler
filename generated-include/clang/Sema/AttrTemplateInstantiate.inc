/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Template instantiation code for attributes                                 *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace clang {
namespace sema {

Attr *instantiateTemplateAttribute(const Attr *At, ASTContext &C, Sema &S,
        const MultiLevelTemplateArgumentList &TemplateArgs) {
  switch (At->getKind()) {
    default:
      break;
    case attr::AMDGPUNumSGPR: {
      const AMDGPUNumSGPRAttr *A = cast<AMDGPUNumSGPRAttr>(At);
      return A->clone(C);
    }
    case attr::AMDGPUNumVGPR: {
      const AMDGPUNumVGPRAttr *A = cast<AMDGPUNumVGPRAttr>(At);
      return A->clone(C);
    }
    case attr::ARMInterrupt: {
      const ARMInterruptAttr *A = cast<ARMInterruptAttr>(At);
      return A->clone(C);
    }
    case attr::AcquireCapability: {
      const AcquireCapabilityAttr *A = cast<AcquireCapabilityAttr>(At);
      Expr * *tempInstArgs = new (C, 16) Expr *[A->args_size()];
      {
        EnterExpressionEvaluationContext Unevaluated(S, Sema::Unevaluated);
        Expr * *TI = tempInstArgs;
        Expr * *I = A->args_begin();
        Expr * *E = A->args_end();
        for (; I != E; ++I, ++TI) {
          ExprResult Result = S.SubstExpr(*I, TemplateArgs);
          *TI = Result.getAs<Expr>();
        }
      }
      return new (C) AcquireCapabilityAttr(A->getLocation(), C, tempInstArgs, A->args_size(), A->getSpellingListIndex());
    }
    case attr::AcquiredAfter: {
      const AcquiredAfterAttr *A = cast<AcquiredAfterAttr>(At);
      Expr * *tempInstArgs = new (C, 16) Expr *[A->args_size()];
      {
        EnterExpressionEvaluationContext Unevaluated(S, Sema::Unevaluated);
        Expr * *TI = tempInstArgs;
        Expr * *I = A->args_begin();
        Expr * *E = A->args_end();
        for (; I != E; ++I, ++TI) {
          ExprResult Result = S.SubstExpr(*I, TemplateArgs);
          *TI = Result.getAs<Expr>();
        }
      }
      return new (C) AcquiredAfterAttr(A->getLocation(), C, tempInstArgs, A->args_size(), A->getSpellingListIndex());
    }
    case attr::AcquiredBefore: {
      const AcquiredBeforeAttr *A = cast<AcquiredBeforeAttr>(At);
      Expr * *tempInstArgs = new (C, 16) Expr *[A->args_size()];
      {
        EnterExpressionEvaluationContext Unevaluated(S, Sema::Unevaluated);
        Expr * *TI = tempInstArgs;
        Expr * *I = A->args_begin();
        Expr * *E = A->args_end();
        for (; I != E; ++I, ++TI) {
          ExprResult Result = S.SubstExpr(*I, TemplateArgs);
          *TI = Result.getAs<Expr>();
        }
      }
      return new (C) AcquiredBeforeAttr(A->getLocation(), C, tempInstArgs, A->args_size(), A->getSpellingListIndex());
    }
    case attr::Alias: {
      const AliasAttr *A = cast<AliasAttr>(At);
      return A->clone(C);
    }
    case attr::AlignMac68k: {
      const AlignMac68kAttr *A = cast<AlignMac68kAttr>(At);
      return A->clone(C);
    }
    case attr::AlignValue: {
      const AlignValueAttr *A = cast<AlignValueAttr>(At);
      return A->clone(C);
    }
    case attr::Aligned: {
      const AlignedAttr *A = cast<AlignedAttr>(At);
      return A->clone(C);
    }
    case attr::AlwaysInline: {
      const AlwaysInlineAttr *A = cast<AlwaysInlineAttr>(At);
      return A->clone(C);
    }
    case attr::AnalyzerNoReturn: {
      const AnalyzerNoReturnAttr *A = cast<AnalyzerNoReturnAttr>(At);
      return A->clone(C);
    }
    case attr::Annotate: {
      const AnnotateAttr *A = cast<AnnotateAttr>(At);
      return A->clone(C);
    }
    case attr::ArcWeakrefUnavailable: {
      const ArcWeakrefUnavailableAttr *A = cast<ArcWeakrefUnavailableAttr>(At);
      return A->clone(C);
    }
    case attr::ArgumentWithTypeTag: {
      const ArgumentWithTypeTagAttr *A = cast<ArgumentWithTypeTagAttr>(At);
      return A->clone(C);
    }
    case attr::AsmLabel: {
      const AsmLabelAttr *A = cast<AsmLabelAttr>(At);
      return A->clone(C);
    }
    case attr::AssertCapability: {
      const AssertCapabilityAttr *A = cast<AssertCapabilityAttr>(At);
      Expr * tempInstExpr;
      {
        EnterExpressionEvaluationContext Unevaluated(S, Sema::Unevaluated);
        ExprResult Result = S.SubstExpr(A->getExpr(), TemplateArgs);
        tempInstExpr = Result.getAs<Expr>();
      }
      return new (C) AssertCapabilityAttr(A->getLocation(), C, tempInstExpr, A->getSpellingListIndex());
    }
    case attr::AssertExclusiveLock: {
      const AssertExclusiveLockAttr *A = cast<AssertExclusiveLockAttr>(At);
      Expr * *tempInstArgs = new (C, 16) Expr *[A->args_size()];
      {
        EnterExpressionEvaluationContext Unevaluated(S, Sema::Unevaluated);
        Expr * *TI = tempInstArgs;
        Expr * *I = A->args_begin();
        Expr * *E = A->args_end();
        for (; I != E; ++I, ++TI) {
          ExprResult Result = S.SubstExpr(*I, TemplateArgs);
          *TI = Result.getAs<Expr>();
        }
      }
      return new (C) AssertExclusiveLockAttr(A->getLocation(), C, tempInstArgs, A->args_size(), A->getSpellingListIndex());
    }
    case attr::AssertSharedLock: {
      const AssertSharedLockAttr *A = cast<AssertSharedLockAttr>(At);
      Expr * *tempInstArgs = new (C, 16) Expr *[A->args_size()];
      {
        EnterExpressionEvaluationContext Unevaluated(S, Sema::Unevaluated);
        Expr * *TI = tempInstArgs;
        Expr * *I = A->args_begin();
        Expr * *E = A->args_end();
        for (; I != E; ++I, ++TI) {
          ExprResult Result = S.SubstExpr(*I, TemplateArgs);
          *TI = Result.getAs<Expr>();
        }
      }
      return new (C) AssertSharedLockAttr(A->getLocation(), C, tempInstArgs, A->args_size(), A->getSpellingListIndex());
    }
    case attr::AssumeAligned: {
      const AssumeAlignedAttr *A = cast<AssumeAlignedAttr>(At);
      return A->clone(C);
    }
    case attr::Availability: {
      const AvailabilityAttr *A = cast<AvailabilityAttr>(At);
      return A->clone(C);
    }
    case attr::Blocks: {
      const BlocksAttr *A = cast<BlocksAttr>(At);
      return A->clone(C);
    }
    case attr::C11NoReturn: {
      const C11NoReturnAttr *A = cast<C11NoReturnAttr>(At);
      return A->clone(C);
    }
    case attr::CDecl: {
      const CDeclAttr *A = cast<CDeclAttr>(At);
      return A->clone(C);
    }
    case attr::CFAuditedTransfer: {
      const CFAuditedTransferAttr *A = cast<CFAuditedTransferAttr>(At);
      return A->clone(C);
    }
    case attr::CFConsumed: {
      const CFConsumedAttr *A = cast<CFConsumedAttr>(At);
      return A->clone(C);
    }
    case attr::CFReturnsNotRetained: {
      const CFReturnsNotRetainedAttr *A = cast<CFReturnsNotRetainedAttr>(At);
      return A->clone(C);
    }
    case attr::CFReturnsRetained: {
      const CFReturnsRetainedAttr *A = cast<CFReturnsRetainedAttr>(At);
      return A->clone(C);
    }
    case attr::CFUnknownTransfer: {
      const CFUnknownTransferAttr *A = cast<CFUnknownTransferAttr>(At);
      return A->clone(C);
    }
    case attr::CUDAConstant: {
      const CUDAConstantAttr *A = cast<CUDAConstantAttr>(At);
      return A->clone(C);
    }
    case attr::CUDADevice: {
      const CUDADeviceAttr *A = cast<CUDADeviceAttr>(At);
      return A->clone(C);
    }
    case attr::CUDAGlobal: {
      const CUDAGlobalAttr *A = cast<CUDAGlobalAttr>(At);
      return A->clone(C);
    }
    case attr::CUDAHost: {
      const CUDAHostAttr *A = cast<CUDAHostAttr>(At);
      return A->clone(C);
    }
    case attr::CUDAInvalidTarget: {
      const CUDAInvalidTargetAttr *A = cast<CUDAInvalidTargetAttr>(At);
      return A->clone(C);
    }
    case attr::CUDALaunchBounds: {
      const CUDALaunchBoundsAttr *A = cast<CUDALaunchBoundsAttr>(At);
      return A->clone(C);
    }
    case attr::CUDAShared: {
      const CUDASharedAttr *A = cast<CUDASharedAttr>(At);
      return A->clone(C);
    }
    case attr::CXX11NoReturn: {
      const CXX11NoReturnAttr *A = cast<CXX11NoReturnAttr>(At);
      return A->clone(C);
    }
    case attr::CallableWhen: {
      const CallableWhenAttr *A = cast<CallableWhenAttr>(At);
      return A->clone(C);
    }
    case attr::Capability: {
      const CapabilityAttr *A = cast<CapabilityAttr>(At);
      return A->clone(C);
    }
    case attr::CapturedRecord: {
      const CapturedRecordAttr *A = cast<CapturedRecordAttr>(At);
      return A->clone(C);
    }
    case attr::CarriesDependency: {
      const CarriesDependencyAttr *A = cast<CarriesDependencyAttr>(At);
      return A->clone(C);
    }
    case attr::Cleanup: {
      const CleanupAttr *A = cast<CleanupAttr>(At);
      return A->clone(C);
    }
    case attr::Cold: {
      const ColdAttr *A = cast<ColdAttr>(At);
      return A->clone(C);
    }
    case attr::Common: {
      const CommonAttr *A = cast<CommonAttr>(At);
      return A->clone(C);
    }
    case attr::Const: {
      const ConstAttr *A = cast<ConstAttr>(At);
      return A->clone(C);
    }
    case attr::Constructor: {
      const ConstructorAttr *A = cast<ConstructorAttr>(At);
      return A->clone(C);
    }
    case attr::Consumable: {
      const ConsumableAttr *A = cast<ConsumableAttr>(At);
      return A->clone(C);
    }
    case attr::ConsumableAutoCast: {
      const ConsumableAutoCastAttr *A = cast<ConsumableAutoCastAttr>(At);
      return A->clone(C);
    }
    case attr::ConsumableSetOnRead: {
      const ConsumableSetOnReadAttr *A = cast<ConsumableSetOnReadAttr>(At);
      return A->clone(C);
    }
    case attr::DLLExport: {
      const DLLExportAttr *A = cast<DLLExportAttr>(At);
      return A->clone(C);
    }
    case attr::DLLImport: {
      const DLLImportAttr *A = cast<DLLImportAttr>(At);
      return A->clone(C);
    }
    case attr::Deprecated: {
      const DeprecatedAttr *A = cast<DeprecatedAttr>(At);
      return A->clone(C);
    }
    case attr::Destructor: {
      const DestructorAttr *A = cast<DestructorAttr>(At);
      return A->clone(C);
    }
    case attr::EnableIf: {
      const EnableIfAttr *A = cast<EnableIfAttr>(At);
      Expr * tempInstCond;
      {
        EnterExpressionEvaluationContext Unevaluated(S, Sema::Unevaluated);
        ExprResult Result = S.SubstExpr(A->getCond(), TemplateArgs);
        tempInstCond = Result.getAs<Expr>();
      }
      return new (C) EnableIfAttr(A->getLocation(), C, tempInstCond, A->getMessage(), A->getSpellingListIndex());
    }
    case attr::ExclusiveTrylockFunction: {
      const ExclusiveTrylockFunctionAttr *A = cast<ExclusiveTrylockFunctionAttr>(At);
      Expr * tempInstSuccessValue;
      {
        EnterExpressionEvaluationContext Unevaluated(S, Sema::Unevaluated);
        ExprResult Result = S.SubstExpr(A->getSuccessValue(), TemplateArgs);
        tempInstSuccessValue = Result.getAs<Expr>();
      }
      Expr * *tempInstArgs = new (C, 16) Expr *[A->args_size()];
      {
        EnterExpressionEvaluationContext Unevaluated(S, Sema::Unevaluated);
        Expr * *TI = tempInstArgs;
        Expr * *I = A->args_begin();
        Expr * *E = A->args_end();
        for (; I != E; ++I, ++TI) {
          ExprResult Result = S.SubstExpr(*I, TemplateArgs);
          *TI = Result.getAs<Expr>();
        }
      }
      return new (C) ExclusiveTrylockFunctionAttr(A->getLocation(), C, tempInstSuccessValue, tempInstArgs, A->args_size(), A->getSpellingListIndex());
    }
    case attr::FallThrough: {
      const FallThroughAttr *A = cast<FallThroughAttr>(At);
      return A->clone(C);
    }
    case attr::FastCall: {
      const FastCallAttr *A = cast<FastCallAttr>(At);
      return A->clone(C);
    }
    case attr::Final: {
      const FinalAttr *A = cast<FinalAttr>(At);
      return A->clone(C);
    }
    case attr::FlagEnum: {
      const FlagEnumAttr *A = cast<FlagEnumAttr>(At);
      return A->clone(C);
    }
    case attr::Flatten: {
      const FlattenAttr *A = cast<FlattenAttr>(At);
      return A->clone(C);
    }
    case attr::Format: {
      const FormatAttr *A = cast<FormatAttr>(At);
      return A->clone(C);
    }
    case attr::FormatArg: {
      const FormatArgAttr *A = cast<FormatArgAttr>(At);
      return A->clone(C);
    }
    case attr::GNUInline: {
      const GNUInlineAttr *A = cast<GNUInlineAttr>(At);
      return A->clone(C);
    }
    case attr::GuardedBy: {
      const GuardedByAttr *A = cast<GuardedByAttr>(At);
      Expr * tempInstArg;
      {
        EnterExpressionEvaluationContext Unevaluated(S, Sema::Unevaluated);
        ExprResult Result = S.SubstExpr(A->getArg(), TemplateArgs);
        tempInstArg = Result.getAs<Expr>();
      }
      return new (C) GuardedByAttr(A->getLocation(), C, tempInstArg, A->getSpellingListIndex());
    }
    case attr::GuardedVar: {
      const GuardedVarAttr *A = cast<GuardedVarAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLAllowUAVCondition: {
      const HLSLAllowUAVConditionAttr *A = cast<HLSLAllowUAVConditionAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLBranch: {
      const HLSLBranchAttr *A = cast<HLSLBranchAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLCXXOverload: {
      const HLSLCXXOverloadAttr *A = cast<HLSLCXXOverloadAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLCall: {
      const HLSLCallAttr *A = cast<HLSLCallAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLCenter: {
      const HLSLCenterAttr *A = cast<HLSLCenterAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLCentroid: {
      const HLSLCentroidAttr *A = cast<HLSLCentroidAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLClipPlanes: {
      const HLSLClipPlanesAttr *A = cast<HLSLClipPlanesAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLDomain: {
      const HLSLDomainAttr *A = cast<HLSLDomainAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLEarlyDepthStencil: {
      const HLSLEarlyDepthStencilAttr *A = cast<HLSLEarlyDepthStencilAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLExperimental: {
      const HLSLExperimentalAttr *A = cast<HLSLExperimentalAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLExport: {
      const HLSLExportAttr *A = cast<HLSLExportAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLFastOpt: {
      const HLSLFastOptAttr *A = cast<HLSLFastOptAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLFlatten: {
      const HLSLFlattenAttr *A = cast<HLSLFlattenAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLForceCase: {
      const HLSLForceCaseAttr *A = cast<HLSLForceCaseAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLGloballyCoherent: {
      const HLSLGloballyCoherentAttr *A = cast<HLSLGloballyCoherentAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLGroupShared: {
      const HLSLGroupSharedAttr *A = cast<HLSLGroupSharedAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLIn: {
      const HLSLInAttr *A = cast<HLSLInAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLInOut: {
      const HLSLInOutAttr *A = cast<HLSLInOutAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLIndices: {
      const HLSLIndicesAttr *A = cast<HLSLIndicesAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLInstance: {
      const HLSLInstanceAttr *A = cast<HLSLInstanceAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLIntrinsic: {
      const HLSLIntrinsicAttr *A = cast<HLSLIntrinsicAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLLine: {
      const HLSLLineAttr *A = cast<HLSLLineAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLLineAdj: {
      const HLSLLineAdjAttr *A = cast<HLSLLineAdjAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLLinear: {
      const HLSLLinearAttr *A = cast<HLSLLinearAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLLoop: {
      const HLSLLoopAttr *A = cast<HLSLLoopAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLMaxTessFactor: {
      const HLSLMaxTessFactorAttr *A = cast<HLSLMaxTessFactorAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLMaxVertexCount: {
      const HLSLMaxVertexCountAttr *A = cast<HLSLMaxVertexCountAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLMaybeUnused: {
      const HLSLMaybeUnusedAttr *A = cast<HLSLMaybeUnusedAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLNoInterpolation: {
      const HLSLNoInterpolationAttr *A = cast<HLSLNoInterpolationAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLNoPerspective: {
      const HLSLNoPerspectiveAttr *A = cast<HLSLNoPerspectiveAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLNumThreads: {
      const HLSLNumThreadsAttr *A = cast<HLSLNumThreadsAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLOut: {
      const HLSLOutAttr *A = cast<HLSLOutAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLOutputControlPoints: {
      const HLSLOutputControlPointsAttr *A = cast<HLSLOutputControlPointsAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLOutputTopology: {
      const HLSLOutputTopologyAttr *A = cast<HLSLOutputTopologyAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLPartitioning: {
      const HLSLPartitioningAttr *A = cast<HLSLPartitioningAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLPatchConstantFunc: {
      const HLSLPatchConstantFuncAttr *A = cast<HLSLPatchConstantFuncAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLPayload: {
      const HLSLPayloadAttr *A = cast<HLSLPayloadAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLPoint: {
      const HLSLPointAttr *A = cast<HLSLPointAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLPrecise: {
      const HLSLPreciseAttr *A = cast<HLSLPreciseAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLPrimitives: {
      const HLSLPrimitivesAttr *A = cast<HLSLPrimitivesAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLRayPayload: {
      const HLSLRayPayloadAttr *A = cast<HLSLRayPayloadAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLRootSignature: {
      const HLSLRootSignatureAttr *A = cast<HLSLRootSignatureAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLSample: {
      const HLSLSampleAttr *A = cast<HLSLSampleAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLSemantic: {
      const HLSLSemanticAttr *A = cast<HLSLSemanticAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLShader: {
      const HLSLShaderAttr *A = cast<HLSLShaderAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLShared: {
      const HLSLSharedAttr *A = cast<HLSLSharedAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLSnorm: {
      const HLSLSnormAttr *A = cast<HLSLSnormAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLTriangle: {
      const HLSLTriangleAttr *A = cast<HLSLTriangleAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLTriangleAdj: {
      const HLSLTriangleAdjAttr *A = cast<HLSLTriangleAdjAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLUniform: {
      const HLSLUniformAttr *A = cast<HLSLUniformAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLUnorm: {
      const HLSLUnormAttr *A = cast<HLSLUnormAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLUnroll: {
      const HLSLUnrollAttr *A = cast<HLSLUnrollAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLVertices: {
      const HLSLVerticesAttr *A = cast<HLSLVerticesAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLWaveOpsIncludeHelperLanes: {
      const HLSLWaveOpsIncludeHelperLanesAttr *A = cast<HLSLWaveOpsIncludeHelperLanesAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLWaveSensitive: {
      const HLSLWaveSensitiveAttr *A = cast<HLSLWaveSensitiveAttr>(At);
      return A->clone(C);
    }
    case attr::HLSLWaveSize: {
      const HLSLWaveSizeAttr *A = cast<HLSLWaveSizeAttr>(At);
      return A->clone(C);
    }
    case attr::Hot: {
      const HotAttr *A = cast<HotAttr>(At);
      return A->clone(C);
    }
    case attr::IBAction: {
      const IBActionAttr *A = cast<IBActionAttr>(At);
      return A->clone(C);
    }
    case attr::IBOutlet: {
      const IBOutletAttr *A = cast<IBOutletAttr>(At);
      return A->clone(C);
    }
    case attr::IBOutletCollection: {
      const IBOutletCollectionAttr *A = cast<IBOutletCollectionAttr>(At);
      return A->clone(C);
    }
    case attr::InitPriority: {
      const InitPriorityAttr *A = cast<InitPriorityAttr>(At);
      return A->clone(C);
    }
    case attr::InitSeg: {
      const InitSegAttr *A = cast<InitSegAttr>(At);
      return A->clone(C);
    }
    case attr::IntelOclBicc: {
      const IntelOclBiccAttr *A = cast<IntelOclBiccAttr>(At);
      return A->clone(C);
    }
    case attr::LockReturned: {
      const LockReturnedAttr *A = cast<LockReturnedAttr>(At);
      Expr * tempInstArg;
      {
        EnterExpressionEvaluationContext Unevaluated(S, Sema::Unevaluated);
        ExprResult Result = S.SubstExpr(A->getArg(), TemplateArgs);
        tempInstArg = Result.getAs<Expr>();
      }
      return new (C) LockReturnedAttr(A->getLocation(), C, tempInstArg, A->getSpellingListIndex());
    }
    case attr::LocksExcluded: {
      const LocksExcludedAttr *A = cast<LocksExcludedAttr>(At);
      Expr * *tempInstArgs = new (C, 16) Expr *[A->args_size()];
      {
        EnterExpressionEvaluationContext Unevaluated(S, Sema::Unevaluated);
        Expr * *TI = tempInstArgs;
        Expr * *I = A->args_begin();
        Expr * *E = A->args_end();
        for (; I != E; ++I, ++TI) {
          ExprResult Result = S.SubstExpr(*I, TemplateArgs);
          *TI = Result.getAs<Expr>();
        }
      }
      return new (C) LocksExcludedAttr(A->getLocation(), C, tempInstArgs, A->args_size(), A->getSpellingListIndex());
    }
    case attr::LoopHint: {
      const LoopHintAttr *A = cast<LoopHintAttr>(At);
      return A->clone(C);
    }
    case attr::MSABI: {
      const MSABIAttr *A = cast<MSABIAttr>(At);
      return A->clone(C);
    }
    case attr::MSInheritance: {
      const MSInheritanceAttr *A = cast<MSInheritanceAttr>(At);
      return A->clone(C);
    }
    case attr::MSNoVTable: {
      const MSNoVTableAttr *A = cast<MSNoVTableAttr>(At);
      return A->clone(C);
    }
    case attr::MSP430Interrupt: {
      const MSP430InterruptAttr *A = cast<MSP430InterruptAttr>(At);
      return A->clone(C);
    }
    case attr::MSStruct: {
      const MSStructAttr *A = cast<MSStructAttr>(At);
      return A->clone(C);
    }
    case attr::MSVtorDisp: {
      const MSVtorDispAttr *A = cast<MSVtorDispAttr>(At);
      return A->clone(C);
    }
    case attr::MaxFieldAlignment: {
      const MaxFieldAlignmentAttr *A = cast<MaxFieldAlignmentAttr>(At);
      return A->clone(C);
    }
    case attr::MayAlias: {
      const MayAliasAttr *A = cast<MayAliasAttr>(At);
      return A->clone(C);
    }
    case attr::MinSize: {
      const MinSizeAttr *A = cast<MinSizeAttr>(At);
      return A->clone(C);
    }
    case attr::Mips16: {
      const Mips16Attr *A = cast<Mips16Attr>(At);
      return A->clone(C);
    }
    case attr::Mode: {
      const ModeAttr *A = cast<ModeAttr>(At);
      return A->clone(C);
    }
    case attr::NSConsumed: {
      const NSConsumedAttr *A = cast<NSConsumedAttr>(At);
      return A->clone(C);
    }
    case attr::NSConsumesSelf: {
      const NSConsumesSelfAttr *A = cast<NSConsumesSelfAttr>(At);
      return A->clone(C);
    }
    case attr::NSReturnsAutoreleased: {
      const NSReturnsAutoreleasedAttr *A = cast<NSReturnsAutoreleasedAttr>(At);
      return A->clone(C);
    }
    case attr::NSReturnsNotRetained: {
      const NSReturnsNotRetainedAttr *A = cast<NSReturnsNotRetainedAttr>(At);
      return A->clone(C);
    }
    case attr::NSReturnsRetained: {
      const NSReturnsRetainedAttr *A = cast<NSReturnsRetainedAttr>(At);
      return A->clone(C);
    }
    case attr::Naked: {
      const NakedAttr *A = cast<NakedAttr>(At);
      return A->clone(C);
    }
    case attr::NoCommon: {
      const NoCommonAttr *A = cast<NoCommonAttr>(At);
      return A->clone(C);
    }
    case attr::NoDebug: {
      const NoDebugAttr *A = cast<NoDebugAttr>(At);
      return A->clone(C);
    }
    case attr::NoDuplicate: {
      const NoDuplicateAttr *A = cast<NoDuplicateAttr>(At);
      return A->clone(C);
    }
    case attr::NoInline: {
      const NoInlineAttr *A = cast<NoInlineAttr>(At);
      return A->clone(C);
    }
    case attr::NoInstrumentFunction: {
      const NoInstrumentFunctionAttr *A = cast<NoInstrumentFunctionAttr>(At);
      return A->clone(C);
    }
    case attr::NoMips16: {
      const NoMips16Attr *A = cast<NoMips16Attr>(At);
      return A->clone(C);
    }
    case attr::NoReturn: {
      const NoReturnAttr *A = cast<NoReturnAttr>(At);
      return A->clone(C);
    }
    case attr::NoSanitize: {
      const NoSanitizeAttr *A = cast<NoSanitizeAttr>(At);
      return A->clone(C);
    }
    case attr::NoSplitStack: {
      const NoSplitStackAttr *A = cast<NoSplitStackAttr>(At);
      return A->clone(C);
    }
    case attr::NoThreadSafetyAnalysis: {
      const NoThreadSafetyAnalysisAttr *A = cast<NoThreadSafetyAnalysisAttr>(At);
      return A->clone(C);
    }
    case attr::NoThrow: {
      const NoThrowAttr *A = cast<NoThrowAttr>(At);
      return A->clone(C);
    }
    case attr::NonNull: {
      const NonNullAttr *A = cast<NonNullAttr>(At);
      return A->clone(C);
    }
    case attr::OMPThreadPrivateDecl: {
      const OMPThreadPrivateDeclAttr *A = cast<OMPThreadPrivateDeclAttr>(At);
      return A->clone(C);
    }
    case attr::ObjCBoxable: {
      const ObjCBoxableAttr *A = cast<ObjCBoxableAttr>(At);
      return A->clone(C);
    }
    case attr::ObjCBridge: {
      const ObjCBridgeAttr *A = cast<ObjCBridgeAttr>(At);
      return A->clone(C);
    }
    case attr::ObjCBridgeMutable: {
      const ObjCBridgeMutableAttr *A = cast<ObjCBridgeMutableAttr>(At);
      return A->clone(C);
    }
    case attr::ObjCBridgeRelated: {
      const ObjCBridgeRelatedAttr *A = cast<ObjCBridgeRelatedAttr>(At);
      return A->clone(C);
    }
    case attr::ObjCDesignatedInitializer: {
      const ObjCDesignatedInitializerAttr *A = cast<ObjCDesignatedInitializerAttr>(At);
      return A->clone(C);
    }
    case attr::ObjCException: {
      const ObjCExceptionAttr *A = cast<ObjCExceptionAttr>(At);
      return A->clone(C);
    }
    case attr::ObjCExplicitProtocolImpl: {
      const ObjCExplicitProtocolImplAttr *A = cast<ObjCExplicitProtocolImplAttr>(At);
      return A->clone(C);
    }
    case attr::ObjCIndependentClass: {
      const ObjCIndependentClassAttr *A = cast<ObjCIndependentClassAttr>(At);
      return A->clone(C);
    }
    case attr::ObjCMethodFamily: {
      const ObjCMethodFamilyAttr *A = cast<ObjCMethodFamilyAttr>(At);
      return A->clone(C);
    }
    case attr::ObjCNSObject: {
      const ObjCNSObjectAttr *A = cast<ObjCNSObjectAttr>(At);
      return A->clone(C);
    }
    case attr::ObjCPreciseLifetime: {
      const ObjCPreciseLifetimeAttr *A = cast<ObjCPreciseLifetimeAttr>(At);
      return A->clone(C);
    }
    case attr::ObjCRequiresPropertyDefs: {
      const ObjCRequiresPropertyDefsAttr *A = cast<ObjCRequiresPropertyDefsAttr>(At);
      return A->clone(C);
    }
    case attr::ObjCRequiresSuper: {
      const ObjCRequiresSuperAttr *A = cast<ObjCRequiresSuperAttr>(At);
      return A->clone(C);
    }
    case attr::ObjCReturnsInnerPointer: {
      const ObjCReturnsInnerPointerAttr *A = cast<ObjCReturnsInnerPointerAttr>(At);
      return A->clone(C);
    }
    case attr::ObjCRootClass: {
      const ObjCRootClassAttr *A = cast<ObjCRootClassAttr>(At);
      return A->clone(C);
    }
    case attr::ObjCRuntimeName: {
      const ObjCRuntimeNameAttr *A = cast<ObjCRuntimeNameAttr>(At);
      return A->clone(C);
    }
    case attr::OpenCLImageAccess: {
      const OpenCLImageAccessAttr *A = cast<OpenCLImageAccessAttr>(At);
      return A->clone(C);
    }
    case attr::OpenCLKernel: {
      const OpenCLKernelAttr *A = cast<OpenCLKernelAttr>(At);
      return A->clone(C);
    }
    case attr::OptimizeNone: {
      const OptimizeNoneAttr *A = cast<OptimizeNoneAttr>(At);
      return A->clone(C);
    }
    case attr::Overloadable: {
      const OverloadableAttr *A = cast<OverloadableAttr>(At);
      return A->clone(C);
    }
    case attr::Override: {
      const OverrideAttr *A = cast<OverrideAttr>(At);
      return A->clone(C);
    }
    case attr::Ownership: {
      const OwnershipAttr *A = cast<OwnershipAttr>(At);
      return A->clone(C);
    }
    case attr::Packed: {
      const PackedAttr *A = cast<PackedAttr>(At);
      return A->clone(C);
    }
    case attr::ParamTypestate: {
      const ParamTypestateAttr *A = cast<ParamTypestateAttr>(At);
      return A->clone(C);
    }
    case attr::Pascal: {
      const PascalAttr *A = cast<PascalAttr>(At);
      return A->clone(C);
    }
    case attr::Pcs: {
      const PcsAttr *A = cast<PcsAttr>(At);
      return A->clone(C);
    }
    case attr::PtGuardedBy: {
      const PtGuardedByAttr *A = cast<PtGuardedByAttr>(At);
      Expr * tempInstArg;
      {
        EnterExpressionEvaluationContext Unevaluated(S, Sema::Unevaluated);
        ExprResult Result = S.SubstExpr(A->getArg(), TemplateArgs);
        tempInstArg = Result.getAs<Expr>();
      }
      return new (C) PtGuardedByAttr(A->getLocation(), C, tempInstArg, A->getSpellingListIndex());
    }
    case attr::PtGuardedVar: {
      const PtGuardedVarAttr *A = cast<PtGuardedVarAttr>(At);
      return A->clone(C);
    }
    case attr::Pure: {
      const PureAttr *A = cast<PureAttr>(At);
      return A->clone(C);
    }
    case attr::ReleaseCapability: {
      const ReleaseCapabilityAttr *A = cast<ReleaseCapabilityAttr>(At);
      Expr * *tempInstArgs = new (C, 16) Expr *[A->args_size()];
      {
        EnterExpressionEvaluationContext Unevaluated(S, Sema::Unevaluated);
        Expr * *TI = tempInstArgs;
        Expr * *I = A->args_begin();
        Expr * *E = A->args_end();
        for (; I != E; ++I, ++TI) {
          ExprResult Result = S.SubstExpr(*I, TemplateArgs);
          *TI = Result.getAs<Expr>();
        }
      }
      return new (C) ReleaseCapabilityAttr(A->getLocation(), C, tempInstArgs, A->args_size(), A->getSpellingListIndex());
    }
    case attr::ReqdWorkGroupSize: {
      const ReqdWorkGroupSizeAttr *A = cast<ReqdWorkGroupSizeAttr>(At);
      return A->clone(C);
    }
    case attr::RequiresCapability: {
      const RequiresCapabilityAttr *A = cast<RequiresCapabilityAttr>(At);
      Expr * *tempInstArgs = new (C, 16) Expr *[A->args_size()];
      {
        EnterExpressionEvaluationContext Unevaluated(S, Sema::Unevaluated);
        Expr * *TI = tempInstArgs;
        Expr * *I = A->args_begin();
        Expr * *E = A->args_end();
        for (; I != E; ++I, ++TI) {
          ExprResult Result = S.SubstExpr(*I, TemplateArgs);
          *TI = Result.getAs<Expr>();
        }
      }
      return new (C) RequiresCapabilityAttr(A->getLocation(), C, tempInstArgs, A->args_size(), A->getSpellingListIndex());
    }
    case attr::Restrict: {
      const RestrictAttr *A = cast<RestrictAttr>(At);
      return A->clone(C);
    }
    case attr::ReturnTypestate: {
      const ReturnTypestateAttr *A = cast<ReturnTypestateAttr>(At);
      return A->clone(C);
    }
    case attr::ReturnsNonNull: {
      const ReturnsNonNullAttr *A = cast<ReturnsNonNullAttr>(At);
      return A->clone(C);
    }
    case attr::ReturnsTwice: {
      const ReturnsTwiceAttr *A = cast<ReturnsTwiceAttr>(At);
      return A->clone(C);
    }
    case attr::ScopedLockable: {
      const ScopedLockableAttr *A = cast<ScopedLockableAttr>(At);
      return A->clone(C);
    }
    case attr::Section: {
      const SectionAttr *A = cast<SectionAttr>(At);
      return A->clone(C);
    }
    case attr::SelectAny: {
      const SelectAnyAttr *A = cast<SelectAnyAttr>(At);
      return A->clone(C);
    }
    case attr::Sentinel: {
      const SentinelAttr *A = cast<SentinelAttr>(At);
      return A->clone(C);
    }
    case attr::SetTypestate: {
      const SetTypestateAttr *A = cast<SetTypestateAttr>(At);
      return A->clone(C);
    }
    case attr::SharedTrylockFunction: {
      const SharedTrylockFunctionAttr *A = cast<SharedTrylockFunctionAttr>(At);
      Expr * tempInstSuccessValue;
      {
        EnterExpressionEvaluationContext Unevaluated(S, Sema::Unevaluated);
        ExprResult Result = S.SubstExpr(A->getSuccessValue(), TemplateArgs);
        tempInstSuccessValue = Result.getAs<Expr>();
      }
      Expr * *tempInstArgs = new (C, 16) Expr *[A->args_size()];
      {
        EnterExpressionEvaluationContext Unevaluated(S, Sema::Unevaluated);
        Expr * *TI = tempInstArgs;
        Expr * *I = A->args_begin();
        Expr * *E = A->args_end();
        for (; I != E; ++I, ++TI) {
          ExprResult Result = S.SubstExpr(*I, TemplateArgs);
          *TI = Result.getAs<Expr>();
        }
      }
      return new (C) SharedTrylockFunctionAttr(A->getLocation(), C, tempInstSuccessValue, tempInstArgs, A->args_size(), A->getSpellingListIndex());
    }
    case attr::StdCall: {
      const StdCallAttr *A = cast<StdCallAttr>(At);
      return A->clone(C);
    }
    case attr::SysVABI: {
      const SysVABIAttr *A = cast<SysVABIAttr>(At);
      return A->clone(C);
    }
    case attr::TLSModel: {
      const TLSModelAttr *A = cast<TLSModelAttr>(At);
      return A->clone(C);
    }
    case attr::Target: {
      const TargetAttr *A = cast<TargetAttr>(At);
      return A->clone(C);
    }
    case attr::TestTypestate: {
      const TestTypestateAttr *A = cast<TestTypestateAttr>(At);
      return A->clone(C);
    }
    case attr::ThisCall: {
      const ThisCallAttr *A = cast<ThisCallAttr>(At);
      return A->clone(C);
    }
    case attr::Thread: {
      const ThreadAttr *A = cast<ThreadAttr>(At);
      return A->clone(C);
    }
    case attr::TransparentUnion: {
      const TransparentUnionAttr *A = cast<TransparentUnionAttr>(At);
      return A->clone(C);
    }
    case attr::TryAcquireCapability: {
      const TryAcquireCapabilityAttr *A = cast<TryAcquireCapabilityAttr>(At);
      Expr * tempInstSuccessValue;
      {
        EnterExpressionEvaluationContext Unevaluated(S, Sema::Unevaluated);
        ExprResult Result = S.SubstExpr(A->getSuccessValue(), TemplateArgs);
        tempInstSuccessValue = Result.getAs<Expr>();
      }
      Expr * *tempInstArgs = new (C, 16) Expr *[A->args_size()];
      {
        EnterExpressionEvaluationContext Unevaluated(S, Sema::Unevaluated);
        Expr * *TI = tempInstArgs;
        Expr * *I = A->args_begin();
        Expr * *E = A->args_end();
        for (; I != E; ++I, ++TI) {
          ExprResult Result = S.SubstExpr(*I, TemplateArgs);
          *TI = Result.getAs<Expr>();
        }
      }
      return new (C) TryAcquireCapabilityAttr(A->getLocation(), C, tempInstSuccessValue, tempInstArgs, A->args_size(), A->getSpellingListIndex());
    }
    case attr::TypeTagForDatatype: {
      const TypeTagForDatatypeAttr *A = cast<TypeTagForDatatypeAttr>(At);
      return A->clone(C);
    }
    case attr::TypeVisibility: {
      return NULL;
    }
    case attr::Unavailable: {
      const UnavailableAttr *A = cast<UnavailableAttr>(At);
      return A->clone(C);
    }
    case attr::Unused: {
      const UnusedAttr *A = cast<UnusedAttr>(At);
      return A->clone(C);
    }
    case attr::Used: {
      const UsedAttr *A = cast<UsedAttr>(At);
      return A->clone(C);
    }
    case attr::Uuid: {
      const UuidAttr *A = cast<UuidAttr>(At);
      return A->clone(C);
    }
    case attr::VKBinding: {
      const VKBindingAttr *A = cast<VKBindingAttr>(At);
      return A->clone(C);
    }
    case attr::VKBuiltIn: {
      const VKBuiltInAttr *A = cast<VKBuiltInAttr>(At);
      return A->clone(C);
    }
    case attr::VKCapabilityExt: {
      const VKCapabilityExtAttr *A = cast<VKCapabilityExtAttr>(At);
      return A->clone(C);
    }
    case attr::VKCombinedImageSampler: {
      const VKCombinedImageSamplerAttr *A = cast<VKCombinedImageSamplerAttr>(At);
      return A->clone(C);
    }
    case attr::VKConstantId: {
      const VKConstantIdAttr *A = cast<VKConstantIdAttr>(At);
      return A->clone(C);
    }
    case attr::VKCounterBinding: {
      const VKCounterBindingAttr *A = cast<VKCounterBindingAttr>(At);
      return A->clone(C);
    }
    case attr::VKDecorateExt: {
      const VKDecorateExtAttr *A = cast<VKDecorateExtAttr>(At);
      return A->clone(C);
    }
    case attr::VKDecorateIdExt: {
      const VKDecorateIdExtAttr *A = cast<VKDecorateIdExtAttr>(At);
      return A->clone(C);
    }
    case attr::VKDecorateStringExt: {
      const VKDecorateStringExtAttr *A = cast<VKDecorateStringExtAttr>(At);
      return A->clone(C);
    }
    case attr::VKDepthUnchanged: {
      const VKDepthUnchangedAttr *A = cast<VKDepthUnchangedAttr>(At);
      return A->clone(C);
    }
    case attr::VKEarlyAndLateTests: {
      const VKEarlyAndLateTestsAttr *A = cast<VKEarlyAndLateTestsAttr>(At);
      return A->clone(C);
    }
    case attr::VKExtensionExt: {
      const VKExtensionExtAttr *A = cast<VKExtensionExtAttr>(At);
      return A->clone(C);
    }
    case attr::VKImageFormat: {
      const VKImageFormatAttr *A = cast<VKImageFormatAttr>(At);
      return A->clone(C);
    }
    case attr::VKIndex: {
      const VKIndexAttr *A = cast<VKIndexAttr>(At);
      return A->clone(C);
    }
    case attr::VKInputAttachmentIndex: {
      const VKInputAttachmentIndexAttr *A = cast<VKInputAttachmentIndexAttr>(At);
      return A->clone(C);
    }
    case attr::VKInstructionExt: {
      const VKInstructionExtAttr *A = cast<VKInstructionExtAttr>(At);
      return A->clone(C);
    }
    case attr::VKLiteralExt: {
      const VKLiteralExtAttr *A = cast<VKLiteralExtAttr>(At);
      return A->clone(C);
    }
    case attr::VKLocation: {
      const VKLocationAttr *A = cast<VKLocationAttr>(At);
      return A->clone(C);
    }
    case attr::VKOffset: {
      const VKOffsetAttr *A = cast<VKOffsetAttr>(At);
      return A->clone(C);
    }
    case attr::VKPostDepthCoverage: {
      const VKPostDepthCoverageAttr *A = cast<VKPostDepthCoverageAttr>(At);
      return A->clone(C);
    }
    case attr::VKPushConstant: {
      const VKPushConstantAttr *A = cast<VKPushConstantAttr>(At);
      return A->clone(C);
    }
    case attr::VKReferenceExt: {
      const VKReferenceExtAttr *A = cast<VKReferenceExtAttr>(At);
      return A->clone(C);
    }
    case attr::VKShaderRecordEXT: {
      const VKShaderRecordEXTAttr *A = cast<VKShaderRecordEXTAttr>(At);
      return A->clone(C);
    }
    case attr::VKShaderRecordNV: {
      const VKShaderRecordNVAttr *A = cast<VKShaderRecordNVAttr>(At);
      return A->clone(C);
    }
    case attr::VKSpvExecutionMode: {
      const VKSpvExecutionModeAttr *A = cast<VKSpvExecutionModeAttr>(At);
      return A->clone(C);
    }
    case attr::VKStencilRefGreaterEqualBack: {
      const VKStencilRefGreaterEqualBackAttr *A = cast<VKStencilRefGreaterEqualBackAttr>(At);
      return A->clone(C);
    }
    case attr::VKStencilRefGreaterEqualFront: {
      const VKStencilRefGreaterEqualFrontAttr *A = cast<VKStencilRefGreaterEqualFrontAttr>(At);
      return A->clone(C);
    }
    case attr::VKStencilRefLessEqualBack: {
      const VKStencilRefLessEqualBackAttr *A = cast<VKStencilRefLessEqualBackAttr>(At);
      return A->clone(C);
    }
    case attr::VKStencilRefLessEqualFront: {
      const VKStencilRefLessEqualFrontAttr *A = cast<VKStencilRefLessEqualFrontAttr>(At);
      return A->clone(C);
    }
    case attr::VKStencilRefUnchangedBack: {
      const VKStencilRefUnchangedBackAttr *A = cast<VKStencilRefUnchangedBackAttr>(At);
      return A->clone(C);
    }
    case attr::VKStencilRefUnchangedFront: {
      const VKStencilRefUnchangedFrontAttr *A = cast<VKStencilRefUnchangedFrontAttr>(At);
      return A->clone(C);
    }
    case attr::VKStorageClassExt: {
      const VKStorageClassExtAttr *A = cast<VKStorageClassExtAttr>(At);
      return A->clone(C);
    }
    case attr::VKTypeDefExt: {
      const VKTypeDefExtAttr *A = cast<VKTypeDefExtAttr>(At);
      return A->clone(C);
    }
    case attr::VecReturn: {
      const VecReturnAttr *A = cast<VecReturnAttr>(At);
      return A->clone(C);
    }
    case attr::VecTypeHint: {
      const VecTypeHintAttr *A = cast<VecTypeHintAttr>(At);
      return A->clone(C);
    }
    case attr::VectorCall: {
      const VectorCallAttr *A = cast<VectorCallAttr>(At);
      return A->clone(C);
    }
    case attr::Visibility: {
      return NULL;
    }
    case attr::WarnUnused: {
      const WarnUnusedAttr *A = cast<WarnUnusedAttr>(At);
      return A->clone(C);
    }
    case attr::WarnUnusedResult: {
      const WarnUnusedResultAttr *A = cast<WarnUnusedResultAttr>(At);
      return A->clone(C);
    }
    case attr::Weak: {
      const WeakAttr *A = cast<WeakAttr>(At);
      return A->clone(C);
    }
    case attr::WeakImport: {
      const WeakImportAttr *A = cast<WeakImportAttr>(At);
      return A->clone(C);
    }
    case attr::WeakRef: {
      const WeakRefAttr *A = cast<WeakRefAttr>(At);
      return A->clone(C);
    }
    case attr::WorkGroupSizeHint: {
      const WorkGroupSizeHintAttr *A = cast<WorkGroupSizeHintAttr>(At);
      return A->clone(C);
    }
    case attr::X86ForceAlignArgPointer: {
      const X86ForceAlignArgPointerAttr *A = cast<X86ForceAlignArgPointerAttr>(At);
      return A->clone(C);
    }
  } // end switch
  llvm_unreachable("Unknown attribute!");
  return 0;
}

} // end namespace sema
} // end namespace clang
