/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Attribute classes' definitions                                             *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifndef LLVM_CLANG_ATTR_CLASSES_INC
#define LLVM_CLANG_ATTR_CLASSES_INC

class AMDGPUNumSGPRAttr : public InheritableAttr {
unsigned numSGPR;


public:
  static AMDGPUNumSGPRAttr *CreateImplicit(ASTContext &Ctx, unsigned NumSGPR, SourceRange Loc = SourceRange()) {
    AMDGPUNumSGPRAttr *A = new (Ctx) AMDGPUNumSGPRAttr(Loc, Ctx, NumSGPR, 0);
    A->setImplicit(true);
    return A;
  }

  AMDGPUNumSGPRAttr(SourceRange R, ASTContext &Ctx
              , unsigned NumSGPR
              , unsigned SI
             )
    : InheritableAttr(attr::AMDGPUNumSGPR, R, SI, 0, 0)
              , numSGPR(NumSGPR)
  {

  }

  AMDGPUNumSGPRAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  unsigned getNumSGPR() const {
    return numSGPR;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::AMDGPUNumSGPR; }
};

class AMDGPUNumVGPRAttr : public InheritableAttr {
unsigned numVGPR;


public:
  static AMDGPUNumVGPRAttr *CreateImplicit(ASTContext &Ctx, unsigned NumVGPR, SourceRange Loc = SourceRange()) {
    AMDGPUNumVGPRAttr *A = new (Ctx) AMDGPUNumVGPRAttr(Loc, Ctx, NumVGPR, 0);
    A->setImplicit(true);
    return A;
  }

  AMDGPUNumVGPRAttr(SourceRange R, ASTContext &Ctx
              , unsigned NumVGPR
              , unsigned SI
             )
    : InheritableAttr(attr::AMDGPUNumVGPR, R, SI, 0, 0)
              , numVGPR(NumVGPR)
  {

  }

  AMDGPUNumVGPRAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  unsigned getNumVGPR() const {
    return numVGPR;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::AMDGPUNumVGPR; }
};

class ARMInterruptAttr : public InheritableAttr {
public:
  enum InterruptType {
    IRQ,
    FIQ,
    SWI,
    ABORT,
    UNDEF,
    Generic
  };
private:
  InterruptType interrupt;


public:
  static ARMInterruptAttr *CreateImplicit(ASTContext &Ctx, InterruptType Interrupt, SourceRange Loc = SourceRange()) {
    ARMInterruptAttr *A = new (Ctx) ARMInterruptAttr(Loc, Ctx, Interrupt, 0);
    A->setImplicit(true);
    return A;
  }

  ARMInterruptAttr(SourceRange R, ASTContext &Ctx
              , InterruptType Interrupt
              , unsigned SI
             )
    : InheritableAttr(attr::ARMInterrupt, R, SI, 0, 0)
              , interrupt(Interrupt)
  {

  }

  ARMInterruptAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::ARMInterrupt, R, SI, 0, 0)
              , interrupt(InterruptType(0))
  {
  }

  ARMInterruptAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  InterruptType getInterrupt() const {
    return interrupt;
  }

  static bool ConvertStrToInterruptType(StringRef Val, InterruptType &Out) {
    Optional<InterruptType> R = llvm::StringSwitch<Optional<InterruptType>>(Val)
      .Case("IRQ", ARMInterruptAttr::IRQ)
      .Case("FIQ", ARMInterruptAttr::FIQ)
      .Case("SWI", ARMInterruptAttr::SWI)
      .Case("ABORT", ARMInterruptAttr::ABORT)
      .Case("UNDEF", ARMInterruptAttr::UNDEF)
      .Case("", ARMInterruptAttr::Generic)
      .Default(Optional<InterruptType>());
    if (R) {
      Out = *R;
      return true;
    }
    return false;
  }

  static const char *ConvertInterruptTypeToStr(InterruptType Val) {
    switch(Val) {
    case ARMInterruptAttr::IRQ: return "IRQ";
    case ARMInterruptAttr::FIQ: return "FIQ";
    case ARMInterruptAttr::SWI: return "SWI";
    case ARMInterruptAttr::ABORT: return "ABORT";
    case ARMInterruptAttr::UNDEF: return "UNDEF";
    case ARMInterruptAttr::Generic: return "";
    }
    llvm_unreachable("No enumerator with that value");
  }


  static bool classof(const Attr *A) { return A->getKind() == attr::ARMInterrupt; }
};

class AcquireCapabilityAttr : public InheritableAttr {
  unsigned args_Size;
  Expr * *args_;


public:
  enum Spelling {
    GNU_acquire_capability = 0,
    CXX11_clang_acquire_capability = 1,
    GNU_acquire_shared_capability = 2,
    CXX11_clang_acquire_shared_capability = 3,
    GNU_exclusive_lock_function = 4,
    GNU_shared_lock_function = 5
  };

  static AcquireCapabilityAttr *CreateImplicit(ASTContext &Ctx, Spelling S, Expr * *Args, unsigned ArgsSize, SourceRange Loc = SourceRange()) {
    AcquireCapabilityAttr *A = new (Ctx) AcquireCapabilityAttr(Loc, Ctx, Args, ArgsSize, S);
    A->setImplicit(true);
    return A;
  }

  AcquireCapabilityAttr(SourceRange R, ASTContext &Ctx
              , Expr * *Args, unsigned ArgsSize
              , unsigned SI
             )
    : InheritableAttr(attr::AcquireCapability, R, SI, 1, 1)
              , args_Size(ArgsSize), args_(new (Ctx, 16) Expr *[args_Size])
  {
    std::copy(Args, Args + args_Size, args_);
  }

  AcquireCapabilityAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::AcquireCapability, R, SI, 1, 1)
              , args_Size(0), args_(nullptr)
  {
  }

  AcquireCapabilityAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  Spelling getSemanticSpelling() const {
  switch (SpellingListIndex) {
    default: llvm_unreachable("Unknown spelling list index");
    case 0: return GNU_acquire_capability;
    case 1: return CXX11_clang_acquire_capability;
    case 2: return GNU_acquire_shared_capability;
    case 3: return CXX11_clang_acquire_shared_capability;
    case 4: return GNU_exclusive_lock_function;
    case 5: return GNU_shared_lock_function;
  }
  }
  bool isShared() const { return SpellingListIndex == 2 ||
    SpellingListIndex == 3 ||
    SpellingListIndex == 5; }
  typedef Expr ** args_iterator;
  args_iterator args_begin() const { return args_; }
  args_iterator args_end() const { return args_ + args_Size; }
  unsigned args_size() const { return args_Size; }
  llvm::iterator_range<args_iterator> args() const { return llvm::make_range(args_begin(), args_end()); }




  static bool classof(const Attr *A) { return A->getKind() == attr::AcquireCapability; }
};

class AcquiredAfterAttr : public InheritableAttr {
  unsigned args_Size;
  Expr * *args_;


public:
  static AcquiredAfterAttr *CreateImplicit(ASTContext &Ctx, Expr * *Args, unsigned ArgsSize, SourceRange Loc = SourceRange()) {
    AcquiredAfterAttr *A = new (Ctx) AcquiredAfterAttr(Loc, Ctx, Args, ArgsSize, 0);
    A->setImplicit(true);
    return A;
  }

  AcquiredAfterAttr(SourceRange R, ASTContext &Ctx
              , Expr * *Args, unsigned ArgsSize
              , unsigned SI
             )
    : InheritableAttr(attr::AcquiredAfter, R, SI, 1, 1)
              , args_Size(ArgsSize), args_(new (Ctx, 16) Expr *[args_Size])
  {
    std::copy(Args, Args + args_Size, args_);
  }

  AcquiredAfterAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::AcquiredAfter, R, SI, 1, 1)
              , args_Size(0), args_(nullptr)
  {
  }

  AcquiredAfterAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  typedef Expr ** args_iterator;
  args_iterator args_begin() const { return args_; }
  args_iterator args_end() const { return args_ + args_Size; }
  unsigned args_size() const { return args_Size; }
  llvm::iterator_range<args_iterator> args() const { return llvm::make_range(args_begin(), args_end()); }




  static bool classof(const Attr *A) { return A->getKind() == attr::AcquiredAfter; }
};

class AcquiredBeforeAttr : public InheritableAttr {
  unsigned args_Size;
  Expr * *args_;


public:
  static AcquiredBeforeAttr *CreateImplicit(ASTContext &Ctx, Expr * *Args, unsigned ArgsSize, SourceRange Loc = SourceRange()) {
    AcquiredBeforeAttr *A = new (Ctx) AcquiredBeforeAttr(Loc, Ctx, Args, ArgsSize, 0);
    A->setImplicit(true);
    return A;
  }

  AcquiredBeforeAttr(SourceRange R, ASTContext &Ctx
              , Expr * *Args, unsigned ArgsSize
              , unsigned SI
             )
    : InheritableAttr(attr::AcquiredBefore, R, SI, 1, 1)
              , args_Size(ArgsSize), args_(new (Ctx, 16) Expr *[args_Size])
  {
    std::copy(Args, Args + args_Size, args_);
  }

  AcquiredBeforeAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::AcquiredBefore, R, SI, 1, 1)
              , args_Size(0), args_(nullptr)
  {
  }

  AcquiredBeforeAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  typedef Expr ** args_iterator;
  args_iterator args_begin() const { return args_; }
  args_iterator args_end() const { return args_ + args_Size; }
  unsigned args_size() const { return args_Size; }
  llvm::iterator_range<args_iterator> args() const { return llvm::make_range(args_begin(), args_end()); }




  static bool classof(const Attr *A) { return A->getKind() == attr::AcquiredBefore; }
};

class AliasAttr : public Attr {
unsigned aliaseeLength;
char *aliasee;


public:
  static AliasAttr *CreateImplicit(ASTContext &Ctx, llvm::StringRef Aliasee, SourceRange Loc = SourceRange()) {
    AliasAttr *A = new (Ctx) AliasAttr(Loc, Ctx, Aliasee, 0);
    A->setImplicit(true);
    return A;
  }

  AliasAttr(SourceRange R, ASTContext &Ctx
              , llvm::StringRef Aliasee
              , unsigned SI
             )
    : Attr(attr::Alias, R, SI, 0, 0)
              , aliaseeLength(Aliasee.size()),aliasee(new (Ctx, 1) char[aliaseeLength])
  {
      if (!Aliasee.empty())
        std::memcpy(aliasee, Aliasee.data(), aliaseeLength);
  }

  AliasAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  llvm::StringRef getAliasee() const {
    return llvm::StringRef(aliasee, aliaseeLength);
  }
  unsigned getAliaseeLength() const {
    return aliaseeLength;
  }
  void setAliasee(ASTContext &C, llvm::StringRef S) {
    aliaseeLength = S.size();
    this->aliasee = new (C, 1) char [aliaseeLength];
    if (!S.empty())
      std::memcpy(this->aliasee, S.data(), aliaseeLength);
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::Alias; }
};

class AlignMac68kAttr : public InheritableAttr {

public:
  static AlignMac68kAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    AlignMac68kAttr *A = new (Ctx) AlignMac68kAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  AlignMac68kAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::AlignMac68k, R, SI, 0, 0)
  {
  }

  AlignMac68kAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::AlignMac68k; }
};

class AlignValueAttr : public Attr {
Expr * alignment;


public:
  static AlignValueAttr *CreateImplicit(ASTContext &Ctx, Expr * Alignment, SourceRange Loc = SourceRange()) {
    AlignValueAttr *A = new (Ctx) AlignValueAttr(Loc, Ctx, Alignment, 0);
    A->setImplicit(true);
    return A;
  }

  AlignValueAttr(SourceRange R, ASTContext &Ctx
              , Expr * Alignment
              , unsigned SI
             )
    : Attr(attr::AlignValue, R, SI, 0, 0)
              , alignment(Alignment)
  {

  }

  AlignValueAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  Expr * getAlignment() const {
    return alignment;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::AlignValue; }
};

class AlignedAttr : public InheritableAttr {
bool isalignmentExpr;
union {
Expr *alignmentExpr;
TypeSourceInfo *alignmentType;
};


public:
  enum Spelling {
    GNU_aligned = 0,
    CXX11_gnu_aligned = 1,
    Declspec_align = 2,
    Keyword_alignas = 3,
    Keyword_Alignas = 4
  };

  static AlignedAttr *CreateImplicit(ASTContext &Ctx, Spelling S, bool IsAlignmentExpr, void *Alignment, SourceRange Loc = SourceRange()) {
    AlignedAttr *A = new (Ctx) AlignedAttr(Loc, Ctx, IsAlignmentExpr, Alignment, S);
    A->setImplicit(true);
    return A;
  }

  AlignedAttr(SourceRange R, ASTContext &Ctx
              , bool IsAlignmentExpr, void *Alignment
              , unsigned SI
             )
    : InheritableAttr(attr::Aligned, R, SI, 0, 0)
              , isalignmentExpr(IsAlignmentExpr)
  {
    if (isalignmentExpr)
       alignmentExpr = reinterpret_cast<Expr *>(Alignment);
    else
       alignmentType = reinterpret_cast<TypeSourceInfo *>(Alignment);
  }

  AlignedAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::Aligned, R, SI, 0, 0)
              , isalignmentExpr(false)
  {
  }

  AlignedAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  Spelling getSemanticSpelling() const {
  switch (SpellingListIndex) {
    default: llvm_unreachable("Unknown spelling list index");
    case 0: return GNU_aligned;
    case 1: return CXX11_gnu_aligned;
    case 2: return Declspec_align;
    case 3: return Keyword_alignas;
    case 4: return Keyword_Alignas;
  }
  }
  bool isGNU() const { return SpellingListIndex == 0 ||
    SpellingListIndex == 1; }
  bool isC11() const { return SpellingListIndex == 4; }
  bool isAlignas() const { return SpellingListIndex == 3 ||
    SpellingListIndex == 4; }
  bool isDeclspec() const { return SpellingListIndex == 2; }
  bool isAlignmentDependent() const;
  unsigned getAlignment(ASTContext &Ctx) const;
  bool isAlignmentExpr() const {
    return isalignmentExpr;
  }
  Expr *getAlignmentExpr() const {
    assert(isalignmentExpr);
    return alignmentExpr;
  }
  TypeSourceInfo *getAlignmentType() const {
    assert(!isalignmentExpr);
    return alignmentType;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::Aligned; }
};

class AlwaysInlineAttr : public InheritableAttr {

public:
  enum Spelling {
    GNU_always_inline = 0,
    CXX11_gnu_always_inline = 1,
    Keyword_forceinline = 2
  };

  static AlwaysInlineAttr *CreateImplicit(ASTContext &Ctx, Spelling S, SourceRange Loc = SourceRange()) {
    AlwaysInlineAttr *A = new (Ctx) AlwaysInlineAttr(Loc, Ctx, S);
    A->setImplicit(true);
    return A;
  }

  AlwaysInlineAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::AlwaysInline, R, SI, 0, 0)
  {
  }

  AlwaysInlineAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  Spelling getSemanticSpelling() const {
  switch (SpellingListIndex) {
    default: llvm_unreachable("Unknown spelling list index");
    case 0: return GNU_always_inline;
    case 1: return CXX11_gnu_always_inline;
    case 2: return Keyword_forceinline;
  }
  }


  static bool classof(const Attr *A) { return A->getKind() == attr::AlwaysInline; }
};

class AnalyzerNoReturnAttr : public InheritableAttr {

public:
  static AnalyzerNoReturnAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    AnalyzerNoReturnAttr *A = new (Ctx) AnalyzerNoReturnAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  AnalyzerNoReturnAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::AnalyzerNoReturn, R, SI, 0, 0)
  {
  }

  AnalyzerNoReturnAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::AnalyzerNoReturn; }
};

class AnnotateAttr : public InheritableParamAttr {
unsigned annotationLength;
char *annotation;


public:
  static AnnotateAttr *CreateImplicit(ASTContext &Ctx, llvm::StringRef Annotation, SourceRange Loc = SourceRange()) {
    AnnotateAttr *A = new (Ctx) AnnotateAttr(Loc, Ctx, Annotation, 0);
    A->setImplicit(true);
    return A;
  }

  AnnotateAttr(SourceRange R, ASTContext &Ctx
              , llvm::StringRef Annotation
              , unsigned SI
             )
    : InheritableParamAttr(attr::Annotate, R, SI, 0, 0)
              , annotationLength(Annotation.size()),annotation(new (Ctx, 1) char[annotationLength])
  {
      if (!Annotation.empty())
        std::memcpy(annotation, Annotation.data(), annotationLength);
  }

  AnnotateAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  llvm::StringRef getAnnotation() const {
    return llvm::StringRef(annotation, annotationLength);
  }
  unsigned getAnnotationLength() const {
    return annotationLength;
  }
  void setAnnotation(ASTContext &C, llvm::StringRef S) {
    annotationLength = S.size();
    this->annotation = new (C, 1) char [annotationLength];
    if (!S.empty())
      std::memcpy(this->annotation, S.data(), annotationLength);
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::Annotate; }
};

class ArcWeakrefUnavailableAttr : public InheritableAttr {

public:
  static ArcWeakrefUnavailableAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    ArcWeakrefUnavailableAttr *A = new (Ctx) ArcWeakrefUnavailableAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  ArcWeakrefUnavailableAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::ArcWeakrefUnavailable, R, SI, 0, 0)
  {
  }

  ArcWeakrefUnavailableAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::ArcWeakrefUnavailable; }
};

class ArgumentWithTypeTagAttr : public InheritableAttr {
IdentifierInfo * argumentKind;

unsigned argumentIdx;

unsigned typeTagIdx;

bool isPointer;


public:
  enum Spelling {
    GNU_argument_with_type_tag = 0,
    GNU_pointer_with_type_tag = 1
  };

  static ArgumentWithTypeTagAttr *CreateImplicit(ASTContext &Ctx, Spelling S, IdentifierInfo * ArgumentKind, unsigned ArgumentIdx, unsigned TypeTagIdx, bool IsPointer, SourceRange Loc = SourceRange()) {
    ArgumentWithTypeTagAttr *A = new (Ctx) ArgumentWithTypeTagAttr(Loc, Ctx, ArgumentKind, ArgumentIdx, TypeTagIdx, IsPointer, S);
    A->setImplicit(true);
    return A;
  }

  ArgumentWithTypeTagAttr(SourceRange R, ASTContext &Ctx
              , IdentifierInfo * ArgumentKind
              , unsigned ArgumentIdx
              , unsigned TypeTagIdx
              , bool IsPointer
              , unsigned SI
             )
    : InheritableAttr(attr::ArgumentWithTypeTag, R, SI, 0, 0)
              , argumentKind(ArgumentKind)
              , argumentIdx(ArgumentIdx)
              , typeTagIdx(TypeTagIdx)
              , isPointer(IsPointer)
  {




  }

  ArgumentWithTypeTagAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  Spelling getSemanticSpelling() const {
  switch (SpellingListIndex) {
    default: llvm_unreachable("Unknown spelling list index");
    case 0: return GNU_argument_with_type_tag;
    case 1: return GNU_pointer_with_type_tag;
  }
  }
  IdentifierInfo * getArgumentKind() const {
    return argumentKind;
  }

  unsigned getArgumentIdx() const {
    return argumentIdx;
  }

  unsigned getTypeTagIdx() const {
    return typeTagIdx;
  }

  bool getIsPointer() const {
    return isPointer;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::ArgumentWithTypeTag; }
};

class AsmLabelAttr : public InheritableAttr {
unsigned labelLength;
char *label;


public:
  static AsmLabelAttr *CreateImplicit(ASTContext &Ctx, llvm::StringRef Label, SourceRange Loc = SourceRange()) {
    AsmLabelAttr *A = new (Ctx) AsmLabelAttr(Loc, Ctx, Label, 0);
    A->setImplicit(true);
    return A;
  }

  AsmLabelAttr(SourceRange R, ASTContext &Ctx
              , llvm::StringRef Label
              , unsigned SI
             )
    : InheritableAttr(attr::AsmLabel, R, SI, 0, 0)
              , labelLength(Label.size()),label(new (Ctx, 1) char[labelLength])
  {
      if (!Label.empty())
        std::memcpy(label, Label.data(), labelLength);
  }

  AsmLabelAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  llvm::StringRef getLabel() const {
    return llvm::StringRef(label, labelLength);
  }
  unsigned getLabelLength() const {
    return labelLength;
  }
  void setLabel(ASTContext &C, llvm::StringRef S) {
    labelLength = S.size();
    this->label = new (C, 1) char [labelLength];
    if (!S.empty())
      std::memcpy(this->label, S.data(), labelLength);
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::AsmLabel; }
};

class AssertCapabilityAttr : public InheritableAttr {
Expr * expr;


public:
  enum Spelling {
    GNU_assert_capability = 0,
    CXX11_clang_assert_capability = 1,
    GNU_assert_shared_capability = 2,
    CXX11_clang_assert_shared_capability = 3
  };

  static AssertCapabilityAttr *CreateImplicit(ASTContext &Ctx, Spelling S, Expr * Expr, SourceRange Loc = SourceRange()) {
    AssertCapabilityAttr *A = new (Ctx) AssertCapabilityAttr(Loc, Ctx, Expr, S);
    A->setImplicit(true);
    return A;
  }

  AssertCapabilityAttr(SourceRange R, ASTContext &Ctx
              , Expr * Expr
              , unsigned SI
             )
    : InheritableAttr(attr::AssertCapability, R, SI, 1, 1)
              , expr(Expr)
  {

  }

  AssertCapabilityAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  Spelling getSemanticSpelling() const {
  switch (SpellingListIndex) {
    default: llvm_unreachable("Unknown spelling list index");
    case 0: return GNU_assert_capability;
    case 1: return CXX11_clang_assert_capability;
    case 2: return GNU_assert_shared_capability;
    case 3: return CXX11_clang_assert_shared_capability;
  }
  }
  bool isShared() const { return SpellingListIndex == 2 ||
    SpellingListIndex == 3; }
  Expr * getExpr() const {
    return expr;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::AssertCapability; }
};

class AssertExclusiveLockAttr : public InheritableAttr {
  unsigned args_Size;
  Expr * *args_;


public:
  static AssertExclusiveLockAttr *CreateImplicit(ASTContext &Ctx, Expr * *Args, unsigned ArgsSize, SourceRange Loc = SourceRange()) {
    AssertExclusiveLockAttr *A = new (Ctx) AssertExclusiveLockAttr(Loc, Ctx, Args, ArgsSize, 0);
    A->setImplicit(true);
    return A;
  }

  AssertExclusiveLockAttr(SourceRange R, ASTContext &Ctx
              , Expr * *Args, unsigned ArgsSize
              , unsigned SI
             )
    : InheritableAttr(attr::AssertExclusiveLock, R, SI, 1, 1)
              , args_Size(ArgsSize), args_(new (Ctx, 16) Expr *[args_Size])
  {
    std::copy(Args, Args + args_Size, args_);
  }

  AssertExclusiveLockAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::AssertExclusiveLock, R, SI, 1, 1)
              , args_Size(0), args_(nullptr)
  {
  }

  AssertExclusiveLockAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  typedef Expr ** args_iterator;
  args_iterator args_begin() const { return args_; }
  args_iterator args_end() const { return args_ + args_Size; }
  unsigned args_size() const { return args_Size; }
  llvm::iterator_range<args_iterator> args() const { return llvm::make_range(args_begin(), args_end()); }




  static bool classof(const Attr *A) { return A->getKind() == attr::AssertExclusiveLock; }
};

class AssertSharedLockAttr : public InheritableAttr {
  unsigned args_Size;
  Expr * *args_;


public:
  static AssertSharedLockAttr *CreateImplicit(ASTContext &Ctx, Expr * *Args, unsigned ArgsSize, SourceRange Loc = SourceRange()) {
    AssertSharedLockAttr *A = new (Ctx) AssertSharedLockAttr(Loc, Ctx, Args, ArgsSize, 0);
    A->setImplicit(true);
    return A;
  }

  AssertSharedLockAttr(SourceRange R, ASTContext &Ctx
              , Expr * *Args, unsigned ArgsSize
              , unsigned SI
             )
    : InheritableAttr(attr::AssertSharedLock, R, SI, 1, 1)
              , args_Size(ArgsSize), args_(new (Ctx, 16) Expr *[args_Size])
  {
    std::copy(Args, Args + args_Size, args_);
  }

  AssertSharedLockAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::AssertSharedLock, R, SI, 1, 1)
              , args_Size(0), args_(nullptr)
  {
  }

  AssertSharedLockAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  typedef Expr ** args_iterator;
  args_iterator args_begin() const { return args_; }
  args_iterator args_end() const { return args_ + args_Size; }
  unsigned args_size() const { return args_Size; }
  llvm::iterator_range<args_iterator> args() const { return llvm::make_range(args_begin(), args_end()); }




  static bool classof(const Attr *A) { return A->getKind() == attr::AssertSharedLock; }
};

class AssumeAlignedAttr : public InheritableAttr {
Expr * alignment;

Expr * offset;


public:
  static AssumeAlignedAttr *CreateImplicit(ASTContext &Ctx, Expr * Alignment, Expr * Offset, SourceRange Loc = SourceRange()) {
    AssumeAlignedAttr *A = new (Ctx) AssumeAlignedAttr(Loc, Ctx, Alignment, Offset, 0);
    A->setImplicit(true);
    return A;
  }

  AssumeAlignedAttr(SourceRange R, ASTContext &Ctx
              , Expr * Alignment
              , Expr * Offset
              , unsigned SI
             )
    : InheritableAttr(attr::AssumeAligned, R, SI, 0, 0)
              , alignment(Alignment)
              , offset(Offset)
  {


  }

  AssumeAlignedAttr(SourceRange R, ASTContext &Ctx
              , Expr * Alignment
              , unsigned SI
             )
    : InheritableAttr(attr::AssumeAligned, R, SI, 0, 0)
              , alignment()
              , offset()
  {

  }

  AssumeAlignedAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  Expr * getAlignment() const {
    return alignment;
  }

  Expr * getOffset() const {
    return offset;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::AssumeAligned; }
};

class AvailabilityAttr : public InheritableAttr {
IdentifierInfo * platform;

VersionTuple introduced;


VersionTuple deprecated;


VersionTuple obsoleted;


bool unavailable;

unsigned messageLength;
char *message;


public:
  static AvailabilityAttr *CreateImplicit(ASTContext &Ctx, IdentifierInfo * Platform, VersionTuple Introduced, VersionTuple Deprecated, VersionTuple Obsoleted, bool Unavailable, llvm::StringRef Message, SourceRange Loc = SourceRange()) {
    AvailabilityAttr *A = new (Ctx) AvailabilityAttr(Loc, Ctx, Platform, Introduced, Deprecated, Obsoleted, Unavailable, Message, 0);
    A->setImplicit(true);
    return A;
  }

  AvailabilityAttr(SourceRange R, ASTContext &Ctx
              , IdentifierInfo * Platform
              , VersionTuple Introduced
              , VersionTuple Deprecated
              , VersionTuple Obsoleted
              , bool Unavailable
              , llvm::StringRef Message
              , unsigned SI
             )
    : InheritableAttr(attr::Availability, R, SI, 0, 1)
              , platform(Platform)
              , introduced(Introduced)
              , deprecated(Deprecated)
              , obsoleted(Obsoleted)
              , unavailable(Unavailable)
              , messageLength(Message.size()),message(new (Ctx, 1) char[messageLength])
  {





      if (!Message.empty())
        std::memcpy(message, Message.data(), messageLength);
  }

  AvailabilityAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  IdentifierInfo * getPlatform() const {
    return platform;
  }

  VersionTuple getIntroduced() const {
    return introduced;
  }
  void setIntroduced(ASTContext &C, VersionTuple V) {
    introduced = V;
  }

  VersionTuple getDeprecated() const {
    return deprecated;
  }
  void setDeprecated(ASTContext &C, VersionTuple V) {
    deprecated = V;
  }

  VersionTuple getObsoleted() const {
    return obsoleted;
  }
  void setObsoleted(ASTContext &C, VersionTuple V) {
    obsoleted = V;
  }

  bool getUnavailable() const {
    return unavailable;
  }

  llvm::StringRef getMessage() const {
    return llvm::StringRef(message, messageLength);
  }
  unsigned getMessageLength() const {
    return messageLength;
  }
  void setMessage(ASTContext &C, llvm::StringRef S) {
    messageLength = S.size();
    this->message = new (C, 1) char [messageLength];
    if (!S.empty())
      std::memcpy(this->message, S.data(), messageLength);
  }

static llvm::StringRef getPrettyPlatformName(llvm::StringRef Platform) {
    return llvm::StringSwitch<llvm::StringRef>(Platform)
             .Case("android", "Android")
             .Case("ios", "iOS")
             .Case("macosx", "OS X")
             .Case("ios_app_extension", "iOS (App Extension)")
             .Case("macosx_app_extension", "OS X (App Extension)")
             .Default(llvm::StringRef());
} 

  static bool classof(const Attr *A) { return A->getKind() == attr::Availability; }
};

class BlocksAttr : public InheritableAttr {
public:
  enum BlockType {
    ByRef
  };
private:
  BlockType type;


public:
  static BlocksAttr *CreateImplicit(ASTContext &Ctx, BlockType Type, SourceRange Loc = SourceRange()) {
    BlocksAttr *A = new (Ctx) BlocksAttr(Loc, Ctx, Type, 0);
    A->setImplicit(true);
    return A;
  }

  BlocksAttr(SourceRange R, ASTContext &Ctx
              , BlockType Type
              , unsigned SI
             )
    : InheritableAttr(attr::Blocks, R, SI, 0, 0)
              , type(Type)
  {

  }

  BlocksAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  BlockType getType() const {
    return type;
  }

  static bool ConvertStrToBlockType(StringRef Val, BlockType &Out) {
    Optional<BlockType> R = llvm::StringSwitch<Optional<BlockType>>(Val)
      .Case("byref", BlocksAttr::ByRef)
      .Default(Optional<BlockType>());
    if (R) {
      Out = *R;
      return true;
    }
    return false;
  }

  static const char *ConvertBlockTypeToStr(BlockType Val) {
    switch(Val) {
    case BlocksAttr::ByRef: return "byref";
    }
    llvm_unreachable("No enumerator with that value");
  }


  static bool classof(const Attr *A) { return A->getKind() == attr::Blocks; }
};

class C11NoReturnAttr : public InheritableAttr {

public:
  static C11NoReturnAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    C11NoReturnAttr *A = new (Ctx) C11NoReturnAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  C11NoReturnAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::C11NoReturn, R, SI, 0, 0)
  {
  }

  C11NoReturnAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::C11NoReturn; }
};

class CDeclAttr : public InheritableAttr {

public:
  static CDeclAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    CDeclAttr *A = new (Ctx) CDeclAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  CDeclAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::CDecl, R, SI, 0, 0)
  {
  }

  CDeclAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::CDecl; }
};

class CFAuditedTransferAttr : public InheritableAttr {

public:
  static CFAuditedTransferAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    CFAuditedTransferAttr *A = new (Ctx) CFAuditedTransferAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  CFAuditedTransferAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::CFAuditedTransfer, R, SI, 0, 0)
  {
  }

  CFAuditedTransferAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::CFAuditedTransfer; }
};

class CFConsumedAttr : public InheritableParamAttr {

public:
  static CFConsumedAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    CFConsumedAttr *A = new (Ctx) CFConsumedAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  CFConsumedAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableParamAttr(attr::CFConsumed, R, SI, 0, 0)
  {
  }

  CFConsumedAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::CFConsumed; }
};

class CFReturnsNotRetainedAttr : public InheritableAttr {

public:
  static CFReturnsNotRetainedAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    CFReturnsNotRetainedAttr *A = new (Ctx) CFReturnsNotRetainedAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  CFReturnsNotRetainedAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::CFReturnsNotRetained, R, SI, 0, 0)
  {
  }

  CFReturnsNotRetainedAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::CFReturnsNotRetained; }
};

class CFReturnsRetainedAttr : public InheritableAttr {

public:
  static CFReturnsRetainedAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    CFReturnsRetainedAttr *A = new (Ctx) CFReturnsRetainedAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  CFReturnsRetainedAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::CFReturnsRetained, R, SI, 0, 0)
  {
  }

  CFReturnsRetainedAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::CFReturnsRetained; }
};

class CFUnknownTransferAttr : public InheritableAttr {

public:
  static CFUnknownTransferAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    CFUnknownTransferAttr *A = new (Ctx) CFUnknownTransferAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  CFUnknownTransferAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::CFUnknownTransfer, R, SI, 0, 0)
  {
  }

  CFUnknownTransferAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::CFUnknownTransfer; }
};

class CUDAConstantAttr : public InheritableAttr {

public:
  static CUDAConstantAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    CUDAConstantAttr *A = new (Ctx) CUDAConstantAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  CUDAConstantAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::CUDAConstant, R, SI, 0, 0)
  {
  }

  CUDAConstantAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::CUDAConstant; }
};

class CUDADeviceAttr : public InheritableAttr {

public:
  static CUDADeviceAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    CUDADeviceAttr *A = new (Ctx) CUDADeviceAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  CUDADeviceAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::CUDADevice, R, SI, 0, 0)
  {
  }

  CUDADeviceAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::CUDADevice; }
};

class CUDAGlobalAttr : public InheritableAttr {

public:
  static CUDAGlobalAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    CUDAGlobalAttr *A = new (Ctx) CUDAGlobalAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  CUDAGlobalAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::CUDAGlobal, R, SI, 0, 0)
  {
  }

  CUDAGlobalAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::CUDAGlobal; }
};

class CUDAHostAttr : public InheritableAttr {

public:
  static CUDAHostAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    CUDAHostAttr *A = new (Ctx) CUDAHostAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  CUDAHostAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::CUDAHost, R, SI, 0, 0)
  {
  }

  CUDAHostAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::CUDAHost; }
};

class CUDAInvalidTargetAttr : public InheritableAttr {

public:
  static CUDAInvalidTargetAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    CUDAInvalidTargetAttr *A = new (Ctx) CUDAInvalidTargetAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  CUDAInvalidTargetAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::CUDAInvalidTarget, R, SI, 0, 0)
  {
  }

  CUDAInvalidTargetAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::CUDAInvalidTarget; }
};

class CUDALaunchBoundsAttr : public InheritableAttr {
Expr * maxThreads;

Expr * minBlocks;


public:
  static CUDALaunchBoundsAttr *CreateImplicit(ASTContext &Ctx, Expr * MaxThreads, Expr * MinBlocks, SourceRange Loc = SourceRange()) {
    CUDALaunchBoundsAttr *A = new (Ctx) CUDALaunchBoundsAttr(Loc, Ctx, MaxThreads, MinBlocks, 0);
    A->setImplicit(true);
    return A;
  }

  CUDALaunchBoundsAttr(SourceRange R, ASTContext &Ctx
              , Expr * MaxThreads
              , Expr * MinBlocks
              , unsigned SI
             )
    : InheritableAttr(attr::CUDALaunchBounds, R, SI, 0, 0)
              , maxThreads(MaxThreads)
              , minBlocks(MinBlocks)
  {


  }

  CUDALaunchBoundsAttr(SourceRange R, ASTContext &Ctx
              , Expr * MaxThreads
              , unsigned SI
             )
    : InheritableAttr(attr::CUDALaunchBounds, R, SI, 0, 0)
              , maxThreads()
              , minBlocks()
  {

  }

  CUDALaunchBoundsAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  Expr * getMaxThreads() const {
    return maxThreads;
  }

  Expr * getMinBlocks() const {
    return minBlocks;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::CUDALaunchBounds; }
};

class CUDASharedAttr : public InheritableAttr {

public:
  static CUDASharedAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    CUDASharedAttr *A = new (Ctx) CUDASharedAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  CUDASharedAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::CUDAShared, R, SI, 0, 0)
  {
  }

  CUDASharedAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::CUDAShared; }
};

class CXX11NoReturnAttr : public InheritableAttr {

public:
  static CXX11NoReturnAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    CXX11NoReturnAttr *A = new (Ctx) CXX11NoReturnAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  CXX11NoReturnAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::CXX11NoReturn, R, SI, 0, 0)
  {
  }

  CXX11NoReturnAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::CXX11NoReturn; }
};

class CallableWhenAttr : public InheritableAttr {
public:
  enum ConsumedState {
    Unknown,
    Consumed,
    Unconsumed
  };
private:
  unsigned callableStates_Size;
  ConsumedState *callableStates_;


public:
  static CallableWhenAttr *CreateImplicit(ASTContext &Ctx, ConsumedState *CallableStates, unsigned CallableStatesSize, SourceRange Loc = SourceRange()) {
    CallableWhenAttr *A = new (Ctx) CallableWhenAttr(Loc, Ctx, CallableStates, CallableStatesSize, 0);
    A->setImplicit(true);
    return A;
  }

  CallableWhenAttr(SourceRange R, ASTContext &Ctx
              , ConsumedState *CallableStates, unsigned CallableStatesSize
              , unsigned SI
             )
    : InheritableAttr(attr::CallableWhen, R, SI, 0, 0)
              , callableStates_Size(CallableStatesSize), callableStates_(new (Ctx, 16) ConsumedState[callableStates_Size])
  {
    std::copy(CallableStates, CallableStates + callableStates_Size, callableStates_);
  }

  CallableWhenAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::CallableWhen, R, SI, 0, 0)
              , callableStates_Size(0), callableStates_(nullptr)
  {
  }

  CallableWhenAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  typedef ConsumedState* callableStates_iterator;
  callableStates_iterator callableStates_begin() const { return callableStates_; }
  callableStates_iterator callableStates_end() const { return callableStates_ + callableStates_Size; }
  unsigned callableStates_size() const { return callableStates_Size; }
  llvm::iterator_range<callableStates_iterator> callableStates() const { return llvm::make_range(callableStates_begin(), callableStates_end()); }


  static bool ConvertStrToConsumedState(StringRef Val, ConsumedState &Out) {
    Optional<ConsumedState> R = llvm::StringSwitch<Optional<ConsumedState>>(Val)
      .Case("unknown", CallableWhenAttr::Unknown)
      .Case("consumed", CallableWhenAttr::Consumed)
      .Case("unconsumed", CallableWhenAttr::Unconsumed)
      .Default(Optional<ConsumedState>());
    if (R) {
      Out = *R;
      return true;
    }
    return false;
  }

  static const char *ConvertConsumedStateToStr(ConsumedState Val) {
    switch(Val) {
    case CallableWhenAttr::Unknown: return "unknown";
    case CallableWhenAttr::Consumed: return "consumed";
    case CallableWhenAttr::Unconsumed: return "unconsumed";
    }
    llvm_unreachable("No enumerator with that value");
  }


  static bool classof(const Attr *A) { return A->getKind() == attr::CallableWhen; }
};

class CapabilityAttr : public InheritableAttr {
unsigned nameLength;
char *name;


public:
  enum Spelling {
    GNU_capability = 0,
    CXX11_clang_capability = 1,
    GNU_shared_capability = 2,
    CXX11_clang_shared_capability = 3
  };

  static CapabilityAttr *CreateImplicit(ASTContext &Ctx, Spelling S, llvm::StringRef Name, SourceRange Loc = SourceRange()) {
    CapabilityAttr *A = new (Ctx) CapabilityAttr(Loc, Ctx, Name, S);
    A->setImplicit(true);
    return A;
  }

  CapabilityAttr(SourceRange R, ASTContext &Ctx
              , llvm::StringRef Name
              , unsigned SI
             )
    : InheritableAttr(attr::Capability, R, SI, 0, 0)
              , nameLength(Name.size()),name(new (Ctx, 1) char[nameLength])
  {
      if (!Name.empty())
        std::memcpy(name, Name.data(), nameLength);
  }

  CapabilityAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  Spelling getSemanticSpelling() const {
  switch (SpellingListIndex) {
    default: llvm_unreachable("Unknown spelling list index");
    case 0: return GNU_capability;
    case 1: return CXX11_clang_capability;
    case 2: return GNU_shared_capability;
    case 3: return CXX11_clang_shared_capability;
  }
  }
  bool isShared() const { return SpellingListIndex == 2 ||
    SpellingListIndex == 3; }
  llvm::StringRef getName() const {
    return llvm::StringRef(name, nameLength);
  }
  unsigned getNameLength() const {
    return nameLength;
  }
  void setName(ASTContext &C, llvm::StringRef S) {
    nameLength = S.size();
    this->name = new (C, 1) char [nameLength];
    if (!S.empty())
      std::memcpy(this->name, S.data(), nameLength);
  }


    bool isMutex() const { return getName().equals_lower("mutex"); }
    bool isRole() const { return getName().equals_lower("role"); }
  

  static bool classof(const Attr *A) { return A->getKind() == attr::Capability; }
};

class CapturedRecordAttr : public InheritableAttr {

public:
  static CapturedRecordAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    CapturedRecordAttr *A = new (Ctx) CapturedRecordAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  CapturedRecordAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::CapturedRecord, R, SI, 0, 0)
  {
  }

  CapturedRecordAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::CapturedRecord; }
};

class CarriesDependencyAttr : public InheritableParamAttr {

public:
  static CarriesDependencyAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    CarriesDependencyAttr *A = new (Ctx) CarriesDependencyAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  CarriesDependencyAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableParamAttr(attr::CarriesDependency, R, SI, 0, 0)
  {
  }

  CarriesDependencyAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::CarriesDependency; }
};

class CleanupAttr : public InheritableAttr {
FunctionDecl * functionDecl;


public:
  static CleanupAttr *CreateImplicit(ASTContext &Ctx, FunctionDecl * FunctionDecl, SourceRange Loc = SourceRange()) {
    CleanupAttr *A = new (Ctx) CleanupAttr(Loc, Ctx, FunctionDecl, 0);
    A->setImplicit(true);
    return A;
  }

  CleanupAttr(SourceRange R, ASTContext &Ctx
              , FunctionDecl * FunctionDecl
              , unsigned SI
             )
    : InheritableAttr(attr::Cleanup, R, SI, 0, 0)
              , functionDecl(FunctionDecl)
  {

  }

  CleanupAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  FunctionDecl * getFunctionDecl() const {
    return functionDecl;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::Cleanup; }
};

class ColdAttr : public InheritableAttr {

public:
  static ColdAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    ColdAttr *A = new (Ctx) ColdAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  ColdAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::Cold, R, SI, 0, 0)
  {
  }

  ColdAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::Cold; }
};

class CommonAttr : public InheritableAttr {

public:
  static CommonAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    CommonAttr *A = new (Ctx) CommonAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  CommonAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::Common, R, SI, 0, 0)
  {
  }

  CommonAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::Common; }
};

class ConstAttr : public InheritableAttr {

public:
  static ConstAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    ConstAttr *A = new (Ctx) ConstAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  ConstAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::Const, R, SI, 0, 0)
  {
  }

  ConstAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::Const; }
};

class ConstructorAttr : public InheritableAttr {
int priority;


public:
  static ConstructorAttr *CreateImplicit(ASTContext &Ctx, int Priority, SourceRange Loc = SourceRange()) {
    ConstructorAttr *A = new (Ctx) ConstructorAttr(Loc, Ctx, Priority, 0);
    A->setImplicit(true);
    return A;
  }

  ConstructorAttr(SourceRange R, ASTContext &Ctx
              , int Priority
              , unsigned SI
             )
    : InheritableAttr(attr::Constructor, R, SI, 0, 0)
              , priority(Priority)
  {

  }

  ConstructorAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::Constructor, R, SI, 0, 0)
              , priority()
  {
  }

  ConstructorAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  int getPriority() const {
    return priority;
  }

  static const int DefaultPriority = 65535;



  static bool classof(const Attr *A) { return A->getKind() == attr::Constructor; }
};

class ConsumableAttr : public InheritableAttr {
public:
  enum ConsumedState {
    Unknown,
    Consumed,
    Unconsumed
  };
private:
  ConsumedState defaultState;


public:
  static ConsumableAttr *CreateImplicit(ASTContext &Ctx, ConsumedState DefaultState, SourceRange Loc = SourceRange()) {
    ConsumableAttr *A = new (Ctx) ConsumableAttr(Loc, Ctx, DefaultState, 0);
    A->setImplicit(true);
    return A;
  }

  ConsumableAttr(SourceRange R, ASTContext &Ctx
              , ConsumedState DefaultState
              , unsigned SI
             )
    : InheritableAttr(attr::Consumable, R, SI, 0, 0)
              , defaultState(DefaultState)
  {

  }

  ConsumableAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  ConsumedState getDefaultState() const {
    return defaultState;
  }

  static bool ConvertStrToConsumedState(StringRef Val, ConsumedState &Out) {
    Optional<ConsumedState> R = llvm::StringSwitch<Optional<ConsumedState>>(Val)
      .Case("unknown", ConsumableAttr::Unknown)
      .Case("consumed", ConsumableAttr::Consumed)
      .Case("unconsumed", ConsumableAttr::Unconsumed)
      .Default(Optional<ConsumedState>());
    if (R) {
      Out = *R;
      return true;
    }
    return false;
  }

  static const char *ConvertConsumedStateToStr(ConsumedState Val) {
    switch(Val) {
    case ConsumableAttr::Unknown: return "unknown";
    case ConsumableAttr::Consumed: return "consumed";
    case ConsumableAttr::Unconsumed: return "unconsumed";
    }
    llvm_unreachable("No enumerator with that value");
  }


  static bool classof(const Attr *A) { return A->getKind() == attr::Consumable; }
};

class ConsumableAutoCastAttr : public InheritableAttr {

public:
  static ConsumableAutoCastAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    ConsumableAutoCastAttr *A = new (Ctx) ConsumableAutoCastAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  ConsumableAutoCastAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::ConsumableAutoCast, R, SI, 0, 0)
  {
  }

  ConsumableAutoCastAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::ConsumableAutoCast; }
};

class ConsumableSetOnReadAttr : public InheritableAttr {

public:
  static ConsumableSetOnReadAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    ConsumableSetOnReadAttr *A = new (Ctx) ConsumableSetOnReadAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  ConsumableSetOnReadAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::ConsumableSetOnRead, R, SI, 0, 0)
  {
  }

  ConsumableSetOnReadAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::ConsumableSetOnRead; }
};

class DLLExportAttr : public InheritableAttr {

public:
  static DLLExportAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    DLLExportAttr *A = new (Ctx) DLLExportAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  DLLExportAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::DLLExport, R, SI, 0, 0)
  {
  }

  DLLExportAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::DLLExport; }
};

class DLLImportAttr : public InheritableAttr {

public:
  static DLLImportAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    DLLImportAttr *A = new (Ctx) DLLImportAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  DLLImportAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::DLLImport, R, SI, 0, 0)
  {
  }

  DLLImportAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::DLLImport; }
};

class DeprecatedAttr : public InheritableAttr {
unsigned messageLength;
char *message;


public:
  static DeprecatedAttr *CreateImplicit(ASTContext &Ctx, llvm::StringRef Message, SourceRange Loc = SourceRange()) {
    DeprecatedAttr *A = new (Ctx) DeprecatedAttr(Loc, Ctx, Message, 0);
    A->setImplicit(true);
    return A;
  }

  DeprecatedAttr(SourceRange R, ASTContext &Ctx
              , llvm::StringRef Message
              , unsigned SI
             )
    : InheritableAttr(attr::Deprecated, R, SI, 0, 0)
              , messageLength(Message.size()),message(new (Ctx, 1) char[messageLength])
  {
      if (!Message.empty())
        std::memcpy(message, Message.data(), messageLength);
  }

  DeprecatedAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::Deprecated, R, SI, 0, 0)
              , messageLength(0),message(0)
  {
  }

  DeprecatedAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  llvm::StringRef getMessage() const {
    return llvm::StringRef(message, messageLength);
  }
  unsigned getMessageLength() const {
    return messageLength;
  }
  void setMessage(ASTContext &C, llvm::StringRef S) {
    messageLength = S.size();
    this->message = new (C, 1) char [messageLength];
    if (!S.empty())
      std::memcpy(this->message, S.data(), messageLength);
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::Deprecated; }
};

class DestructorAttr : public InheritableAttr {
int priority;


public:
  static DestructorAttr *CreateImplicit(ASTContext &Ctx, int Priority, SourceRange Loc = SourceRange()) {
    DestructorAttr *A = new (Ctx) DestructorAttr(Loc, Ctx, Priority, 0);
    A->setImplicit(true);
    return A;
  }

  DestructorAttr(SourceRange R, ASTContext &Ctx
              , int Priority
              , unsigned SI
             )
    : InheritableAttr(attr::Destructor, R, SI, 0, 0)
              , priority(Priority)
  {

  }

  DestructorAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::Destructor, R, SI, 0, 0)
              , priority()
  {
  }

  DestructorAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  int getPriority() const {
    return priority;
  }

  static const int DefaultPriority = 65535;



  static bool classof(const Attr *A) { return A->getKind() == attr::Destructor; }
};

class EnableIfAttr : public InheritableAttr {
Expr * cond;

unsigned messageLength;
char *message;


public:
  static EnableIfAttr *CreateImplicit(ASTContext &Ctx, Expr * Cond, llvm::StringRef Message, SourceRange Loc = SourceRange()) {
    EnableIfAttr *A = new (Ctx) EnableIfAttr(Loc, Ctx, Cond, Message, 0);
    A->setImplicit(true);
    return A;
  }

  EnableIfAttr(SourceRange R, ASTContext &Ctx
              , Expr * Cond
              , llvm::StringRef Message
              , unsigned SI
             )
    : InheritableAttr(attr::EnableIf, R, SI, 0, 0)
              , cond(Cond)
              , messageLength(Message.size()),message(new (Ctx, 1) char[messageLength])
  {

      if (!Message.empty())
        std::memcpy(message, Message.data(), messageLength);
  }

  EnableIfAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  Expr * getCond() const {
    return cond;
  }

  llvm::StringRef getMessage() const {
    return llvm::StringRef(message, messageLength);
  }
  unsigned getMessageLength() const {
    return messageLength;
  }
  void setMessage(ASTContext &C, llvm::StringRef S) {
    messageLength = S.size();
    this->message = new (C, 1) char [messageLength];
    if (!S.empty())
      std::memcpy(this->message, S.data(), messageLength);
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::EnableIf; }
};

class ExclusiveTrylockFunctionAttr : public InheritableAttr {
Expr * successValue;

  unsigned args_Size;
  Expr * *args_;


public:
  static ExclusiveTrylockFunctionAttr *CreateImplicit(ASTContext &Ctx, Expr * SuccessValue, Expr * *Args, unsigned ArgsSize, SourceRange Loc = SourceRange()) {
    ExclusiveTrylockFunctionAttr *A = new (Ctx) ExclusiveTrylockFunctionAttr(Loc, Ctx, SuccessValue, Args, ArgsSize, 0);
    A->setImplicit(true);
    return A;
  }

  ExclusiveTrylockFunctionAttr(SourceRange R, ASTContext &Ctx
              , Expr * SuccessValue
              , Expr * *Args, unsigned ArgsSize
              , unsigned SI
             )
    : InheritableAttr(attr::ExclusiveTrylockFunction, R, SI, 1, 1)
              , successValue(SuccessValue)
              , args_Size(ArgsSize), args_(new (Ctx, 16) Expr *[args_Size])
  {

    std::copy(Args, Args + args_Size, args_);
  }

  ExclusiveTrylockFunctionAttr(SourceRange R, ASTContext &Ctx
              , Expr * SuccessValue
              , unsigned SI
             )
    : InheritableAttr(attr::ExclusiveTrylockFunction, R, SI, 1, 1)
              , successValue()
              , args_Size(0), args_(nullptr)
  {

  }

  ExclusiveTrylockFunctionAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  Expr * getSuccessValue() const {
    return successValue;
  }

  typedef Expr ** args_iterator;
  args_iterator args_begin() const { return args_; }
  args_iterator args_end() const { return args_ + args_Size; }
  unsigned args_size() const { return args_Size; }
  llvm::iterator_range<args_iterator> args() const { return llvm::make_range(args_begin(), args_end()); }




  static bool classof(const Attr *A) { return A->getKind() == attr::ExclusiveTrylockFunction; }
};

class FallThroughAttr : public Attr {

public:
  static FallThroughAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    FallThroughAttr *A = new (Ctx) FallThroughAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  FallThroughAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : Attr(attr::FallThrough, R, SI, 0, 0)
  {
  }

  FallThroughAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::FallThrough; }
};

class FastCallAttr : public InheritableAttr {

public:
  static FastCallAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    FastCallAttr *A = new (Ctx) FastCallAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  FastCallAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::FastCall, R, SI, 0, 0)
  {
  }

  FastCallAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::FastCall; }
};

class FinalAttr : public InheritableAttr {

public:
  enum Spelling {
    Keyword_final = 0,
    Keyword_sealed = 1
  };

  static FinalAttr *CreateImplicit(ASTContext &Ctx, Spelling S, SourceRange Loc = SourceRange()) {
    FinalAttr *A = new (Ctx) FinalAttr(Loc, Ctx, S);
    A->setImplicit(true);
    return A;
  }

  FinalAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::Final, R, SI, 0, 0)
  {
  }

  FinalAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  Spelling getSemanticSpelling() const {
  switch (SpellingListIndex) {
    default: llvm_unreachable("Unknown spelling list index");
    case 0: return Keyword_final;
    case 1: return Keyword_sealed;
  }
  }
  bool isSpelledAsSealed() const { return SpellingListIndex == 1; }


  static bool classof(const Attr *A) { return A->getKind() == attr::Final; }
};

class FlagEnumAttr : public InheritableAttr {

public:
  static FlagEnumAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    FlagEnumAttr *A = new (Ctx) FlagEnumAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  FlagEnumAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::FlagEnum, R, SI, 0, 0)
  {
  }

  FlagEnumAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;

private:
    llvm::APInt FlagBits;
public:
    llvm::APInt &getFlagBits() {
      return FlagBits;
    }

    const llvm::APInt &getFlagBits() const {
      return FlagBits;
    }


  static bool classof(const Attr *A) { return A->getKind() == attr::FlagEnum; }
};

class FlattenAttr : public InheritableAttr {

public:
  static FlattenAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    FlattenAttr *A = new (Ctx) FlattenAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  FlattenAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::Flatten, R, SI, 0, 0)
  {
  }

  FlattenAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::Flatten; }
};

class FormatAttr : public InheritableAttr {
IdentifierInfo * type;

int formatIdx;

int firstArg;


public:
  static FormatAttr *CreateImplicit(ASTContext &Ctx, IdentifierInfo * Type, int FormatIdx, int FirstArg, SourceRange Loc = SourceRange()) {
    FormatAttr *A = new (Ctx) FormatAttr(Loc, Ctx, Type, FormatIdx, FirstArg, 0);
    A->setImplicit(true);
    return A;
  }

  FormatAttr(SourceRange R, ASTContext &Ctx
              , IdentifierInfo * Type
              , int FormatIdx
              , int FirstArg
              , unsigned SI
             )
    : InheritableAttr(attr::Format, R, SI, 0, 0)
              , type(Type)
              , formatIdx(FormatIdx)
              , firstArg(FirstArg)
  {



  }

  FormatAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  IdentifierInfo * getType() const {
    return type;
  }

  int getFormatIdx() const {
    return formatIdx;
  }

  int getFirstArg() const {
    return firstArg;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::Format; }
};

class FormatArgAttr : public InheritableAttr {
int formatIdx;


public:
  static FormatArgAttr *CreateImplicit(ASTContext &Ctx, int FormatIdx, SourceRange Loc = SourceRange()) {
    FormatArgAttr *A = new (Ctx) FormatArgAttr(Loc, Ctx, FormatIdx, 0);
    A->setImplicit(true);
    return A;
  }

  FormatArgAttr(SourceRange R, ASTContext &Ctx
              , int FormatIdx
              , unsigned SI
             )
    : InheritableAttr(attr::FormatArg, R, SI, 0, 0)
              , formatIdx(FormatIdx)
  {

  }

  FormatArgAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  int getFormatIdx() const {
    return formatIdx;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::FormatArg; }
};

class GNUInlineAttr : public InheritableAttr {

public:
  static GNUInlineAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    GNUInlineAttr *A = new (Ctx) GNUInlineAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  GNUInlineAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::GNUInline, R, SI, 0, 0)
  {
  }

  GNUInlineAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::GNUInline; }
};

class GuardedByAttr : public InheritableAttr {
Expr * arg;


public:
  static GuardedByAttr *CreateImplicit(ASTContext &Ctx, Expr * Arg, SourceRange Loc = SourceRange()) {
    GuardedByAttr *A = new (Ctx) GuardedByAttr(Loc, Ctx, Arg, 0);
    A->setImplicit(true);
    return A;
  }

  GuardedByAttr(SourceRange R, ASTContext &Ctx
              , Expr * Arg
              , unsigned SI
             )
    : InheritableAttr(attr::GuardedBy, R, SI, 1, 1)
              , arg(Arg)
  {

  }

  GuardedByAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  Expr * getArg() const {
    return arg;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::GuardedBy; }
};

class GuardedVarAttr : public InheritableAttr {

public:
  static GuardedVarAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    GuardedVarAttr *A = new (Ctx) GuardedVarAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  GuardedVarAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::GuardedVar, R, SI, 0, 0)
  {
  }

  GuardedVarAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::GuardedVar; }
};

class HLSLAllowUAVConditionAttr : public Attr {

public:
  static HLSLAllowUAVConditionAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLAllowUAVConditionAttr *A = new (Ctx) HLSLAllowUAVConditionAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLAllowUAVConditionAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : Attr(attr::HLSLAllowUAVCondition, R, SI, 0, 0)
  {
  }

  HLSLAllowUAVConditionAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLAllowUAVCondition; }
};

class HLSLBranchAttr : public Attr {

public:
  static HLSLBranchAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLBranchAttr *A = new (Ctx) HLSLBranchAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLBranchAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : Attr(attr::HLSLBranch, R, SI, 0, 0)
  {
  }

  HLSLBranchAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLBranch; }
};

class HLSLCXXOverloadAttr : public InheritableAttr {

public:
  static HLSLCXXOverloadAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLCXXOverloadAttr *A = new (Ctx) HLSLCXXOverloadAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLCXXOverloadAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLCXXOverload, R, SI, 0, 0)
  {
  }

  HLSLCXXOverloadAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLCXXOverload; }
};

class HLSLCallAttr : public Attr {

public:
  static HLSLCallAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLCallAttr *A = new (Ctx) HLSLCallAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLCallAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : Attr(attr::HLSLCall, R, SI, 0, 0)
  {
  }

  HLSLCallAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLCall; }
};

class HLSLCenterAttr : public InheritableAttr {

public:
  static HLSLCenterAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLCenterAttr *A = new (Ctx) HLSLCenterAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLCenterAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLCenter, R, SI, 0, 0)
  {
  }

  HLSLCenterAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLCenter; }
};

class HLSLCentroidAttr : public InheritableAttr {

public:
  static HLSLCentroidAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLCentroidAttr *A = new (Ctx) HLSLCentroidAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLCentroidAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLCentroid, R, SI, 0, 0)
  {
  }

  HLSLCentroidAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLCentroid; }
};

class HLSLClipPlanesAttr : public InheritableAttr {
Expr * clipPlane1;

Expr * clipPlane2;

Expr * clipPlane3;

Expr * clipPlane4;

Expr * clipPlane5;

Expr * clipPlane6;


public:
  static HLSLClipPlanesAttr *CreateImplicit(ASTContext &Ctx, Expr * ClipPlane1, Expr * ClipPlane2, Expr * ClipPlane3, Expr * ClipPlane4, Expr * ClipPlane5, Expr * ClipPlane6, SourceRange Loc = SourceRange()) {
    HLSLClipPlanesAttr *A = new (Ctx) HLSLClipPlanesAttr(Loc, Ctx, ClipPlane1, ClipPlane2, ClipPlane3, ClipPlane4, ClipPlane5, ClipPlane6, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLClipPlanesAttr(SourceRange R, ASTContext &Ctx
              , Expr * ClipPlane1
              , Expr * ClipPlane2
              , Expr * ClipPlane3
              , Expr * ClipPlane4
              , Expr * ClipPlane5
              , Expr * ClipPlane6
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLClipPlanes, R, SI, 0, 0)
              , clipPlane1(ClipPlane1)
              , clipPlane2(ClipPlane2)
              , clipPlane3(ClipPlane3)
              , clipPlane4(ClipPlane4)
              , clipPlane5(ClipPlane5)
              , clipPlane6(ClipPlane6)
  {






  }

  HLSLClipPlanesAttr(SourceRange R, ASTContext &Ctx
              , Expr * ClipPlane1
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLClipPlanes, R, SI, 0, 0)
              , clipPlane1()
              , clipPlane2()
              , clipPlane3()
              , clipPlane4()
              , clipPlane5()
              , clipPlane6()
  {

  }

  HLSLClipPlanesAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  Expr * getClipPlane1() const {
    return clipPlane1;
  }

  Expr * getClipPlane2() const {
    return clipPlane2;
  }

  Expr * getClipPlane3() const {
    return clipPlane3;
  }

  Expr * getClipPlane4() const {
    return clipPlane4;
  }

  Expr * getClipPlane5() const {
    return clipPlane5;
  }

  Expr * getClipPlane6() const {
    return clipPlane6;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLClipPlanes; }
};

class HLSLDomainAttr : public InheritableAttr {
unsigned domainTypeLength;
char *domainType;


public:
  static HLSLDomainAttr *CreateImplicit(ASTContext &Ctx, llvm::StringRef DomainType, SourceRange Loc = SourceRange()) {
    HLSLDomainAttr *A = new (Ctx) HLSLDomainAttr(Loc, Ctx, DomainType, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLDomainAttr(SourceRange R, ASTContext &Ctx
              , llvm::StringRef DomainType
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLDomain, R, SI, 0, 0)
              , domainTypeLength(DomainType.size()),domainType(new (Ctx, 1) char[domainTypeLength])
  {
      if (!DomainType.empty())
        std::memcpy(domainType, DomainType.data(), domainTypeLength);
  }

  HLSLDomainAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  llvm::StringRef getDomainType() const {
    return llvm::StringRef(domainType, domainTypeLength);
  }
  unsigned getDomainTypeLength() const {
    return domainTypeLength;
  }
  void setDomainType(ASTContext &C, llvm::StringRef S) {
    domainTypeLength = S.size();
    this->domainType = new (C, 1) char [domainTypeLength];
    if (!S.empty())
      std::memcpy(this->domainType, S.data(), domainTypeLength);
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLDomain; }
};

class HLSLEarlyDepthStencilAttr : public InheritableAttr {

public:
  static HLSLEarlyDepthStencilAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLEarlyDepthStencilAttr *A = new (Ctx) HLSLEarlyDepthStencilAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLEarlyDepthStencilAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLEarlyDepthStencil, R, SI, 0, 0)
  {
  }

  HLSLEarlyDepthStencilAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLEarlyDepthStencil; }
};

class HLSLExperimentalAttr : public InheritableAttr {
unsigned nameLength;
char *name;

unsigned valueLength;
char *value;


public:
  static HLSLExperimentalAttr *CreateImplicit(ASTContext &Ctx, llvm::StringRef Name, llvm::StringRef Value, SourceRange Loc = SourceRange()) {
    HLSLExperimentalAttr *A = new (Ctx) HLSLExperimentalAttr(Loc, Ctx, Name, Value, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLExperimentalAttr(SourceRange R, ASTContext &Ctx
              , llvm::StringRef Name
              , llvm::StringRef Value
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLExperimental, R, SI, 0, 0)
              , nameLength(Name.size()),name(new (Ctx, 1) char[nameLength])
              , valueLength(Value.size()),value(new (Ctx, 1) char[valueLength])
  {
      if (!Name.empty())
        std::memcpy(name, Name.data(), nameLength);
      if (!Value.empty())
        std::memcpy(value, Value.data(), valueLength);
  }

  HLSLExperimentalAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  llvm::StringRef getName() const {
    return llvm::StringRef(name, nameLength);
  }
  unsigned getNameLength() const {
    return nameLength;
  }
  void setName(ASTContext &C, llvm::StringRef S) {
    nameLength = S.size();
    this->name = new (C, 1) char [nameLength];
    if (!S.empty())
      std::memcpy(this->name, S.data(), nameLength);
  }

  llvm::StringRef getValue() const {
    return llvm::StringRef(value, valueLength);
  }
  unsigned getValueLength() const {
    return valueLength;
  }
  void setValue(ASTContext &C, llvm::StringRef S) {
    valueLength = S.size();
    this->value = new (C, 1) char [valueLength];
    if (!S.empty())
      std::memcpy(this->value, S.data(), valueLength);
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLExperimental; }
};

class HLSLExportAttr : public InheritableAttr {

public:
  static HLSLExportAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLExportAttr *A = new (Ctx) HLSLExportAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLExportAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLExport, R, SI, 0, 0)
  {
  }

  HLSLExportAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLExport; }
};

class HLSLFastOptAttr : public Attr {

public:
  static HLSLFastOptAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLFastOptAttr *A = new (Ctx) HLSLFastOptAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLFastOptAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : Attr(attr::HLSLFastOpt, R, SI, 0, 0)
  {
  }

  HLSLFastOptAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLFastOpt; }
};

class HLSLFlattenAttr : public Attr {

public:
  static HLSLFlattenAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLFlattenAttr *A = new (Ctx) HLSLFlattenAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLFlattenAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : Attr(attr::HLSLFlatten, R, SI, 0, 0)
  {
  }

  HLSLFlattenAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLFlatten; }
};

class HLSLForceCaseAttr : public Attr {

public:
  static HLSLForceCaseAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLForceCaseAttr *A = new (Ctx) HLSLForceCaseAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLForceCaseAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : Attr(attr::HLSLForceCase, R, SI, 0, 0)
  {
  }

  HLSLForceCaseAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLForceCase; }
};

class HLSLGloballyCoherentAttr : public InheritableAttr {

public:
  static HLSLGloballyCoherentAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLGloballyCoherentAttr *A = new (Ctx) HLSLGloballyCoherentAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLGloballyCoherentAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLGloballyCoherent, R, SI, 0, 0)
  {
  }

  HLSLGloballyCoherentAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLGloballyCoherent; }
};

class HLSLGroupSharedAttr : public InheritableAttr {

public:
  static HLSLGroupSharedAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLGroupSharedAttr *A = new (Ctx) HLSLGroupSharedAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLGroupSharedAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLGroupShared, R, SI, 0, 0)
  {
  }

  HLSLGroupSharedAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLGroupShared; }
};

class HLSLInAttr : public InheritableAttr {

public:
  static HLSLInAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLInAttr *A = new (Ctx) HLSLInAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLInAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLIn, R, SI, 0, 0)
  {
  }

  HLSLInAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLIn; }
};

class HLSLInOutAttr : public InheritableAttr {

public:
  static HLSLInOutAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLInOutAttr *A = new (Ctx) HLSLInOutAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLInOutAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLInOut, R, SI, 0, 0)
  {
  }

  HLSLInOutAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLInOut; }
};

class HLSLIndicesAttr : public InheritableAttr {

public:
  static HLSLIndicesAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLIndicesAttr *A = new (Ctx) HLSLIndicesAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLIndicesAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLIndices, R, SI, 0, 0)
  {
  }

  HLSLIndicesAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLIndices; }
};

class HLSLInstanceAttr : public InheritableAttr {
int count;


public:
  static HLSLInstanceAttr *CreateImplicit(ASTContext &Ctx, int Count, SourceRange Loc = SourceRange()) {
    HLSLInstanceAttr *A = new (Ctx) HLSLInstanceAttr(Loc, Ctx, Count, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLInstanceAttr(SourceRange R, ASTContext &Ctx
              , int Count
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLInstance, R, SI, 0, 0)
              , count(Count)
  {

  }

  HLSLInstanceAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  int getCount() const {
    return count;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLInstance; }
};

class HLSLIntrinsicAttr : public InheritableAttr {
unsigned groupLength;
char *group;

unsigned loweringLength;
char *lowering;

int opcode;


public:
  static HLSLIntrinsicAttr *CreateImplicit(ASTContext &Ctx, llvm::StringRef Group, llvm::StringRef Lowering, int Opcode, SourceRange Loc = SourceRange()) {
    HLSLIntrinsicAttr *A = new (Ctx) HLSLIntrinsicAttr(Loc, Ctx, Group, Lowering, Opcode, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLIntrinsicAttr(SourceRange R, ASTContext &Ctx
              , llvm::StringRef Group
              , llvm::StringRef Lowering
              , int Opcode
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLIntrinsic, R, SI, 0, 0)
              , groupLength(Group.size()),group(new (Ctx, 1) char[groupLength])
              , loweringLength(Lowering.size()),lowering(new (Ctx, 1) char[loweringLength])
              , opcode(Opcode)
  {
      if (!Group.empty())
        std::memcpy(group, Group.data(), groupLength);
      if (!Lowering.empty())
        std::memcpy(lowering, Lowering.data(), loweringLength);

  }

  HLSLIntrinsicAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  llvm::StringRef getGroup() const {
    return llvm::StringRef(group, groupLength);
  }
  unsigned getGroupLength() const {
    return groupLength;
  }
  void setGroup(ASTContext &C, llvm::StringRef S) {
    groupLength = S.size();
    this->group = new (C, 1) char [groupLength];
    if (!S.empty())
      std::memcpy(this->group, S.data(), groupLength);
  }

  llvm::StringRef getLowering() const {
    return llvm::StringRef(lowering, loweringLength);
  }
  unsigned getLoweringLength() const {
    return loweringLength;
  }
  void setLowering(ASTContext &C, llvm::StringRef S) {
    loweringLength = S.size();
    this->lowering = new (C, 1) char [loweringLength];
    if (!S.empty())
      std::memcpy(this->lowering, S.data(), loweringLength);
  }

  int getOpcode() const {
    return opcode;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLIntrinsic; }
};

class HLSLLineAttr : public InheritableAttr {

public:
  static HLSLLineAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLLineAttr *A = new (Ctx) HLSLLineAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLLineAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLLine, R, SI, 0, 0)
  {
  }

  HLSLLineAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLLine; }
};

class HLSLLineAdjAttr : public InheritableAttr {

public:
  static HLSLLineAdjAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLLineAdjAttr *A = new (Ctx) HLSLLineAdjAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLLineAdjAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLLineAdj, R, SI, 0, 0)
  {
  }

  HLSLLineAdjAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLLineAdj; }
};

class HLSLLinearAttr : public InheritableAttr {

public:
  static HLSLLinearAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLLinearAttr *A = new (Ctx) HLSLLinearAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLLinearAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLLinear, R, SI, 0, 0)
  {
  }

  HLSLLinearAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLLinear; }
};

class HLSLLoopAttr : public Attr {

public:
  static HLSLLoopAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLLoopAttr *A = new (Ctx) HLSLLoopAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLLoopAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : Attr(attr::HLSLLoop, R, SI, 0, 0)
  {
  }

  HLSLLoopAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLLoop; }
};

class HLSLMaxTessFactorAttr : public InheritableAttr {
int factor;


public:
  static HLSLMaxTessFactorAttr *CreateImplicit(ASTContext &Ctx, int Factor, SourceRange Loc = SourceRange()) {
    HLSLMaxTessFactorAttr *A = new (Ctx) HLSLMaxTessFactorAttr(Loc, Ctx, Factor, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLMaxTessFactorAttr(SourceRange R, ASTContext &Ctx
              , int Factor
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLMaxTessFactor, R, SI, 0, 0)
              , factor(Factor)
  {

  }

  HLSLMaxTessFactorAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  int getFactor() const {
    return factor;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLMaxTessFactor; }
};

class HLSLMaxVertexCountAttr : public InheritableAttr {
int count;


public:
  static HLSLMaxVertexCountAttr *CreateImplicit(ASTContext &Ctx, int Count, SourceRange Loc = SourceRange()) {
    HLSLMaxVertexCountAttr *A = new (Ctx) HLSLMaxVertexCountAttr(Loc, Ctx, Count, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLMaxVertexCountAttr(SourceRange R, ASTContext &Ctx
              , int Count
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLMaxVertexCount, R, SI, 0, 0)
              , count(Count)
  {

  }

  HLSLMaxVertexCountAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  int getCount() const {
    return count;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLMaxVertexCount; }
};

class HLSLMaybeUnusedAttr : public InheritableAttr {

public:
  static HLSLMaybeUnusedAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLMaybeUnusedAttr *A = new (Ctx) HLSLMaybeUnusedAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLMaybeUnusedAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLMaybeUnused, R, SI, 0, 0)
  {
  }

  HLSLMaybeUnusedAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLMaybeUnused; }
};

class HLSLNoInterpolationAttr : public InheritableAttr {

public:
  static HLSLNoInterpolationAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLNoInterpolationAttr *A = new (Ctx) HLSLNoInterpolationAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLNoInterpolationAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLNoInterpolation, R, SI, 0, 0)
  {
  }

  HLSLNoInterpolationAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLNoInterpolation; }
};

class HLSLNoPerspectiveAttr : public InheritableAttr {

public:
  static HLSLNoPerspectiveAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLNoPerspectiveAttr *A = new (Ctx) HLSLNoPerspectiveAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLNoPerspectiveAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLNoPerspective, R, SI, 0, 0)
  {
  }

  HLSLNoPerspectiveAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLNoPerspective; }
};

class HLSLNumThreadsAttr : public InheritableAttr {
int x;

int y;

int z;


public:
  static HLSLNumThreadsAttr *CreateImplicit(ASTContext &Ctx, int X, int Y, int Z, SourceRange Loc = SourceRange()) {
    HLSLNumThreadsAttr *A = new (Ctx) HLSLNumThreadsAttr(Loc, Ctx, X, Y, Z, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLNumThreadsAttr(SourceRange R, ASTContext &Ctx
              , int X
              , int Y
              , int Z
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLNumThreads, R, SI, 0, 0)
              , x(X)
              , y(Y)
              , z(Z)
  {



  }

  HLSLNumThreadsAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  int getX() const {
    return x;
  }

  int getY() const {
    return y;
  }

  int getZ() const {
    return z;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLNumThreads; }
};

class HLSLOutAttr : public InheritableAttr {

public:
  static HLSLOutAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLOutAttr *A = new (Ctx) HLSLOutAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLOutAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLOut, R, SI, 0, 0)
  {
  }

  HLSLOutAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLOut; }
};

class HLSLOutputControlPointsAttr : public InheritableAttr {
int count;


public:
  static HLSLOutputControlPointsAttr *CreateImplicit(ASTContext &Ctx, int Count, SourceRange Loc = SourceRange()) {
    HLSLOutputControlPointsAttr *A = new (Ctx) HLSLOutputControlPointsAttr(Loc, Ctx, Count, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLOutputControlPointsAttr(SourceRange R, ASTContext &Ctx
              , int Count
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLOutputControlPoints, R, SI, 0, 0)
              , count(Count)
  {

  }

  HLSLOutputControlPointsAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  int getCount() const {
    return count;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLOutputControlPoints; }
};

class HLSLOutputTopologyAttr : public InheritableAttr {
unsigned topologyLength;
char *topology;


public:
  static HLSLOutputTopologyAttr *CreateImplicit(ASTContext &Ctx, llvm::StringRef Topology, SourceRange Loc = SourceRange()) {
    HLSLOutputTopologyAttr *A = new (Ctx) HLSLOutputTopologyAttr(Loc, Ctx, Topology, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLOutputTopologyAttr(SourceRange R, ASTContext &Ctx
              , llvm::StringRef Topology
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLOutputTopology, R, SI, 0, 0)
              , topologyLength(Topology.size()),topology(new (Ctx, 1) char[topologyLength])
  {
      if (!Topology.empty())
        std::memcpy(topology, Topology.data(), topologyLength);
  }

  HLSLOutputTopologyAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  llvm::StringRef getTopology() const {
    return llvm::StringRef(topology, topologyLength);
  }
  unsigned getTopologyLength() const {
    return topologyLength;
  }
  void setTopology(ASTContext &C, llvm::StringRef S) {
    topologyLength = S.size();
    this->topology = new (C, 1) char [topologyLength];
    if (!S.empty())
      std::memcpy(this->topology, S.data(), topologyLength);
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLOutputTopology; }
};

class HLSLPartitioningAttr : public InheritableAttr {
unsigned schemeLength;
char *scheme;


public:
  static HLSLPartitioningAttr *CreateImplicit(ASTContext &Ctx, llvm::StringRef Scheme, SourceRange Loc = SourceRange()) {
    HLSLPartitioningAttr *A = new (Ctx) HLSLPartitioningAttr(Loc, Ctx, Scheme, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLPartitioningAttr(SourceRange R, ASTContext &Ctx
              , llvm::StringRef Scheme
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLPartitioning, R, SI, 0, 0)
              , schemeLength(Scheme.size()),scheme(new (Ctx, 1) char[schemeLength])
  {
      if (!Scheme.empty())
        std::memcpy(scheme, Scheme.data(), schemeLength);
  }

  HLSLPartitioningAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  llvm::StringRef getScheme() const {
    return llvm::StringRef(scheme, schemeLength);
  }
  unsigned getSchemeLength() const {
    return schemeLength;
  }
  void setScheme(ASTContext &C, llvm::StringRef S) {
    schemeLength = S.size();
    this->scheme = new (C, 1) char [schemeLength];
    if (!S.empty())
      std::memcpy(this->scheme, S.data(), schemeLength);
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLPartitioning; }
};

class HLSLPatchConstantFuncAttr : public InheritableAttr {
unsigned functionNameLength;
char *functionName;


public:
  static HLSLPatchConstantFuncAttr *CreateImplicit(ASTContext &Ctx, llvm::StringRef FunctionName, SourceRange Loc = SourceRange()) {
    HLSLPatchConstantFuncAttr *A = new (Ctx) HLSLPatchConstantFuncAttr(Loc, Ctx, FunctionName, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLPatchConstantFuncAttr(SourceRange R, ASTContext &Ctx
              , llvm::StringRef FunctionName
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLPatchConstantFunc, R, SI, 0, 0)
              , functionNameLength(FunctionName.size()),functionName(new (Ctx, 1) char[functionNameLength])
  {
      if (!FunctionName.empty())
        std::memcpy(functionName, FunctionName.data(), functionNameLength);
  }

  HLSLPatchConstantFuncAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  llvm::StringRef getFunctionName() const {
    return llvm::StringRef(functionName, functionNameLength);
  }
  unsigned getFunctionNameLength() const {
    return functionNameLength;
  }
  void setFunctionName(ASTContext &C, llvm::StringRef S) {
    functionNameLength = S.size();
    this->functionName = new (C, 1) char [functionNameLength];
    if (!S.empty())
      std::memcpy(this->functionName, S.data(), functionNameLength);
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLPatchConstantFunc; }
};

class HLSLPayloadAttr : public InheritableAttr {

public:
  static HLSLPayloadAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLPayloadAttr *A = new (Ctx) HLSLPayloadAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLPayloadAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLPayload, R, SI, 0, 0)
  {
  }

  HLSLPayloadAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLPayload; }
};

class HLSLPointAttr : public InheritableAttr {

public:
  static HLSLPointAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLPointAttr *A = new (Ctx) HLSLPointAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLPointAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLPoint, R, SI, 0, 0)
  {
  }

  HLSLPointAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLPoint; }
};

class HLSLPreciseAttr : public InheritableAttr {

public:
  static HLSLPreciseAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLPreciseAttr *A = new (Ctx) HLSLPreciseAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLPreciseAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLPrecise, R, SI, 0, 0)
  {
  }

  HLSLPreciseAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLPrecise; }
};

class HLSLPrimitivesAttr : public InheritableAttr {

public:
  static HLSLPrimitivesAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLPrimitivesAttr *A = new (Ctx) HLSLPrimitivesAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLPrimitivesAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLPrimitives, R, SI, 0, 0)
  {
  }

  HLSLPrimitivesAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLPrimitives; }
};

class HLSLRayPayloadAttr : public InheritableAttr {

public:
  static HLSLRayPayloadAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLRayPayloadAttr *A = new (Ctx) HLSLRayPayloadAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLRayPayloadAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLRayPayload, R, SI, 0, 0)
  {
  }

  HLSLRayPayloadAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLRayPayload; }
};

class HLSLRootSignatureAttr : public InheritableAttr {
unsigned signatureNameLength;
char *signatureName;


public:
  static HLSLRootSignatureAttr *CreateImplicit(ASTContext &Ctx, llvm::StringRef SignatureName, SourceRange Loc = SourceRange()) {
    HLSLRootSignatureAttr *A = new (Ctx) HLSLRootSignatureAttr(Loc, Ctx, SignatureName, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLRootSignatureAttr(SourceRange R, ASTContext &Ctx
              , llvm::StringRef SignatureName
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLRootSignature, R, SI, 0, 0)
              , signatureNameLength(SignatureName.size()),signatureName(new (Ctx, 1) char[signatureNameLength])
  {
      if (!SignatureName.empty())
        std::memcpy(signatureName, SignatureName.data(), signatureNameLength);
  }

  HLSLRootSignatureAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  llvm::StringRef getSignatureName() const {
    return llvm::StringRef(signatureName, signatureNameLength);
  }
  unsigned getSignatureNameLength() const {
    return signatureNameLength;
  }
  void setSignatureName(ASTContext &C, llvm::StringRef S) {
    signatureNameLength = S.size();
    this->signatureName = new (C, 1) char [signatureNameLength];
    if (!S.empty())
      std::memcpy(this->signatureName, S.data(), signatureNameLength);
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLRootSignature; }
};

class HLSLSampleAttr : public InheritableAttr {

public:
  static HLSLSampleAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLSampleAttr *A = new (Ctx) HLSLSampleAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLSampleAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLSample, R, SI, 0, 0)
  {
  }

  HLSLSampleAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLSample; }
};

class HLSLSemanticAttr : public InheritableAttr {
unsigned nameLength;
char *name;


public:
  static HLSLSemanticAttr *CreateImplicit(ASTContext &Ctx, llvm::StringRef Name, SourceRange Loc = SourceRange()) {
    HLSLSemanticAttr *A = new (Ctx) HLSLSemanticAttr(Loc, Ctx, Name, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLSemanticAttr(SourceRange R, ASTContext &Ctx
              , llvm::StringRef Name
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLSemantic, R, SI, 0, 0)
              , nameLength(Name.size()),name(new (Ctx, 1) char[nameLength])
  {
      if (!Name.empty())
        std::memcpy(name, Name.data(), nameLength);
  }

  HLSLSemanticAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  llvm::StringRef getName() const {
    return llvm::StringRef(name, nameLength);
  }
  unsigned getNameLength() const {
    return nameLength;
  }
  void setName(ASTContext &C, llvm::StringRef S) {
    nameLength = S.size();
    this->name = new (C, 1) char [nameLength];
    if (!S.empty())
      std::memcpy(this->name, S.data(), nameLength);
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLSemantic; }
};

class HLSLShaderAttr : public InheritableAttr {
unsigned stageLength;
char *stage;


public:
  static HLSLShaderAttr *CreateImplicit(ASTContext &Ctx, llvm::StringRef Stage, SourceRange Loc = SourceRange()) {
    HLSLShaderAttr *A = new (Ctx) HLSLShaderAttr(Loc, Ctx, Stage, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLShaderAttr(SourceRange R, ASTContext &Ctx
              , llvm::StringRef Stage
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLShader, R, SI, 0, 0)
              , stageLength(Stage.size()),stage(new (Ctx, 1) char[stageLength])
  {
      if (!Stage.empty())
        std::memcpy(stage, Stage.data(), stageLength);
  }

  HLSLShaderAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  llvm::StringRef getStage() const {
    return llvm::StringRef(stage, stageLength);
  }
  unsigned getStageLength() const {
    return stageLength;
  }
  void setStage(ASTContext &C, llvm::StringRef S) {
    stageLength = S.size();
    this->stage = new (C, 1) char [stageLength];
    if (!S.empty())
      std::memcpy(this->stage, S.data(), stageLength);
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLShader; }
};

class HLSLSharedAttr : public InheritableAttr {

public:
  static HLSLSharedAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLSharedAttr *A = new (Ctx) HLSLSharedAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLSharedAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLShared, R, SI, 0, 0)
  {
  }

  HLSLSharedAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLShared; }
};

class HLSLSnormAttr : public InheritableAttr {

public:
  static HLSLSnormAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLSnormAttr *A = new (Ctx) HLSLSnormAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLSnormAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLSnorm, R, SI, 0, 0)
  {
  }

  HLSLSnormAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLSnorm; }
};

class HLSLTriangleAttr : public InheritableAttr {

public:
  static HLSLTriangleAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLTriangleAttr *A = new (Ctx) HLSLTriangleAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLTriangleAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLTriangle, R, SI, 0, 0)
  {
  }

  HLSLTriangleAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLTriangle; }
};

class HLSLTriangleAdjAttr : public InheritableAttr {

public:
  static HLSLTriangleAdjAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLTriangleAdjAttr *A = new (Ctx) HLSLTriangleAdjAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLTriangleAdjAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLTriangleAdj, R, SI, 0, 0)
  {
  }

  HLSLTriangleAdjAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLTriangleAdj; }
};

class HLSLUniformAttr : public InheritableAttr {

public:
  static HLSLUniformAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLUniformAttr *A = new (Ctx) HLSLUniformAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLUniformAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLUniform, R, SI, 0, 0)
  {
  }

  HLSLUniformAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLUniform; }
};

class HLSLUnormAttr : public InheritableAttr {

public:
  static HLSLUnormAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLUnormAttr *A = new (Ctx) HLSLUnormAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLUnormAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLUnorm, R, SI, 0, 0)
  {
  }

  HLSLUnormAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLUnorm; }
};

class HLSLUnrollAttr : public Attr {
int count;


public:
  static HLSLUnrollAttr *CreateImplicit(ASTContext &Ctx, int Count, SourceRange Loc = SourceRange()) {
    HLSLUnrollAttr *A = new (Ctx) HLSLUnrollAttr(Loc, Ctx, Count, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLUnrollAttr(SourceRange R, ASTContext &Ctx
              , int Count
              , unsigned SI
             )
    : Attr(attr::HLSLUnroll, R, SI, 0, 0)
              , count(Count)
  {

  }

  HLSLUnrollAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : Attr(attr::HLSLUnroll, R, SI, 0, 0)
              , count()
  {
  }

  HLSLUnrollAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  int getCount() const {
    return count;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLUnroll; }
};

class HLSLVerticesAttr : public InheritableAttr {

public:
  static HLSLVerticesAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLVerticesAttr *A = new (Ctx) HLSLVerticesAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLVerticesAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLVertices, R, SI, 0, 0)
  {
  }

  HLSLVerticesAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLVertices; }
};

class HLSLWaveOpsIncludeHelperLanesAttr : public InheritableAttr {

public:
  static HLSLWaveOpsIncludeHelperLanesAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLWaveOpsIncludeHelperLanesAttr *A = new (Ctx) HLSLWaveOpsIncludeHelperLanesAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLWaveOpsIncludeHelperLanesAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLWaveOpsIncludeHelperLanes, R, SI, 0, 0)
  {
  }

  HLSLWaveOpsIncludeHelperLanesAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLWaveOpsIncludeHelperLanes; }
};

class HLSLWaveSensitiveAttr : public InheritableAttr {

public:
  static HLSLWaveSensitiveAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HLSLWaveSensitiveAttr *A = new (Ctx) HLSLWaveSensitiveAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLWaveSensitiveAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLWaveSensitive, R, SI, 0, 0)
  {
  }

  HLSLWaveSensitiveAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLWaveSensitive; }
};

class HLSLWaveSizeAttr : public InheritableAttr {
int size;


public:
  static HLSLWaveSizeAttr *CreateImplicit(ASTContext &Ctx, int Size, SourceRange Loc = SourceRange()) {
    HLSLWaveSizeAttr *A = new (Ctx) HLSLWaveSizeAttr(Loc, Ctx, Size, 0);
    A->setImplicit(true);
    return A;
  }

  HLSLWaveSizeAttr(SourceRange R, ASTContext &Ctx
              , int Size
              , unsigned SI
             )
    : InheritableAttr(attr::HLSLWaveSize, R, SI, 0, 0)
              , size(Size)
  {

  }

  HLSLWaveSizeAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  int getSize() const {
    return size;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::HLSLWaveSize; }
};

class HotAttr : public InheritableAttr {

public:
  static HotAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    HotAttr *A = new (Ctx) HotAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  HotAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::Hot, R, SI, 0, 0)
  {
  }

  HotAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::Hot; }
};

class IBActionAttr : public InheritableAttr {

public:
  static IBActionAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    IBActionAttr *A = new (Ctx) IBActionAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  IBActionAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::IBAction, R, SI, 0, 0)
  {
  }

  IBActionAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::IBAction; }
};

class IBOutletAttr : public InheritableAttr {

public:
  static IBOutletAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    IBOutletAttr *A = new (Ctx) IBOutletAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  IBOutletAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::IBOutlet, R, SI, 0, 0)
  {
  }

  IBOutletAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::IBOutlet; }
};

class IBOutletCollectionAttr : public InheritableAttr {
TypeSourceInfo * interface;


public:
  static IBOutletCollectionAttr *CreateImplicit(ASTContext &Ctx, TypeSourceInfo * Interface, SourceRange Loc = SourceRange()) {
    IBOutletCollectionAttr *A = new (Ctx) IBOutletCollectionAttr(Loc, Ctx, Interface, 0);
    A->setImplicit(true);
    return A;
  }

  IBOutletCollectionAttr(SourceRange R, ASTContext &Ctx
              , TypeSourceInfo * Interface
              , unsigned SI
             )
    : InheritableAttr(attr::IBOutletCollection, R, SI, 0, 0)
              , interface(Interface)
  {

  }

  IBOutletCollectionAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::IBOutletCollection, R, SI, 0, 0)
              , interface()
  {
  }

  IBOutletCollectionAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  QualType getInterface() const {
    return interface->getType();
  }  TypeSourceInfo * getInterfaceLoc() const {
    return interface;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::IBOutletCollection; }
};

class InitPriorityAttr : public InheritableAttr {
unsigned priority;


public:
  static InitPriorityAttr *CreateImplicit(ASTContext &Ctx, unsigned Priority, SourceRange Loc = SourceRange()) {
    InitPriorityAttr *A = new (Ctx) InitPriorityAttr(Loc, Ctx, Priority, 0);
    A->setImplicit(true);
    return A;
  }

  InitPriorityAttr(SourceRange R, ASTContext &Ctx
              , unsigned Priority
              , unsigned SI
             )
    : InheritableAttr(attr::InitPriority, R, SI, 0, 0)
              , priority(Priority)
  {

  }

  InitPriorityAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  unsigned getPriority() const {
    return priority;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::InitPriority; }
};

class InitSegAttr : public Attr {
unsigned sectionLength;
char *section;


public:
  static InitSegAttr *CreateImplicit(ASTContext &Ctx, llvm::StringRef Section, SourceRange Loc = SourceRange()) {
    InitSegAttr *A = new (Ctx) InitSegAttr(Loc, Ctx, Section, 0);
    A->setImplicit(true);
    return A;
  }

  InitSegAttr(SourceRange R, ASTContext &Ctx
              , llvm::StringRef Section
              , unsigned SI
             )
    : Attr(attr::InitSeg, R, SI, 0, 0)
              , sectionLength(Section.size()),section(new (Ctx, 1) char[sectionLength])
  {
      if (!Section.empty())
        std::memcpy(section, Section.data(), sectionLength);
  }

  InitSegAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  llvm::StringRef getSection() const {
    return llvm::StringRef(section, sectionLength);
  }
  unsigned getSectionLength() const {
    return sectionLength;
  }
  void setSection(ASTContext &C, llvm::StringRef S) {
    sectionLength = S.size();
    this->section = new (C, 1) char [sectionLength];
    if (!S.empty())
      std::memcpy(this->section, S.data(), sectionLength);
  }


  void printPrettyPragma(raw_ostream &OS, const PrintingPolicy &Policy) const {
    OS << '(' << getSection() << ')';
  }
  

  static bool classof(const Attr *A) { return A->getKind() == attr::InitSeg; }
};

class IntelOclBiccAttr : public InheritableAttr {

public:
  static IntelOclBiccAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    IntelOclBiccAttr *A = new (Ctx) IntelOclBiccAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  IntelOclBiccAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::IntelOclBicc, R, SI, 0, 0)
  {
  }

  IntelOclBiccAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::IntelOclBicc; }
};

class LockReturnedAttr : public InheritableAttr {
Expr * arg;


public:
  static LockReturnedAttr *CreateImplicit(ASTContext &Ctx, Expr * Arg, SourceRange Loc = SourceRange()) {
    LockReturnedAttr *A = new (Ctx) LockReturnedAttr(Loc, Ctx, Arg, 0);
    A->setImplicit(true);
    return A;
  }

  LockReturnedAttr(SourceRange R, ASTContext &Ctx
              , Expr * Arg
              , unsigned SI
             )
    : InheritableAttr(attr::LockReturned, R, SI, 1, 0)
              , arg(Arg)
  {

  }

  LockReturnedAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  Expr * getArg() const {
    return arg;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::LockReturned; }
};

class LocksExcludedAttr : public InheritableAttr {
  unsigned args_Size;
  Expr * *args_;


public:
  static LocksExcludedAttr *CreateImplicit(ASTContext &Ctx, Expr * *Args, unsigned ArgsSize, SourceRange Loc = SourceRange()) {
    LocksExcludedAttr *A = new (Ctx) LocksExcludedAttr(Loc, Ctx, Args, ArgsSize, 0);
    A->setImplicit(true);
    return A;
  }

  LocksExcludedAttr(SourceRange R, ASTContext &Ctx
              , Expr * *Args, unsigned ArgsSize
              , unsigned SI
             )
    : InheritableAttr(attr::LocksExcluded, R, SI, 1, 1)
              , args_Size(ArgsSize), args_(new (Ctx, 16) Expr *[args_Size])
  {
    std::copy(Args, Args + args_Size, args_);
  }

  LocksExcludedAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::LocksExcluded, R, SI, 1, 1)
              , args_Size(0), args_(nullptr)
  {
  }

  LocksExcludedAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  typedef Expr ** args_iterator;
  args_iterator args_begin() const { return args_; }
  args_iterator args_end() const { return args_ + args_Size; }
  unsigned args_size() const { return args_Size; }
  llvm::iterator_range<args_iterator> args() const { return llvm::make_range(args_begin(), args_end()); }




  static bool classof(const Attr *A) { return A->getKind() == attr::LocksExcluded; }
};

class LoopHintAttr : public Attr {
public:
  enum OptionType {
    Vectorize,
    VectorizeWidth,
    Interleave,
    InterleaveCount,
    Unroll,
    UnrollCount
  };
private:
  OptionType option;

public:
  enum LoopHintState {
    Default,
    Enable,
    Disable,
    AssumeSafety
  };
private:
  LoopHintState state;

Expr * value;


public:
  enum Spelling {
    Pragma_clang_loop = 0,
    Pragma_unroll = 1,
    Pragma_nounroll = 2
  };

  static LoopHintAttr *CreateImplicit(ASTContext &Ctx, Spelling S, OptionType Option, LoopHintState State, Expr * Value, SourceRange Loc = SourceRange()) {
    LoopHintAttr *A = new (Ctx) LoopHintAttr(Loc, Ctx, Option, State, Value, S);
    A->setImplicit(true);
    return A;
  }

  LoopHintAttr(SourceRange R, ASTContext &Ctx
              , OptionType Option
              , LoopHintState State
              , Expr * Value
              , unsigned SI
             )
    : Attr(attr::LoopHint, R, SI, 0, 0)
              , option(Option)
              , state(State)
              , value(Value)
  {



  }

  LoopHintAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  Spelling getSemanticSpelling() const {
  switch (SpellingListIndex) {
    default: llvm_unreachable("Unknown spelling list index");
    case 0: return Pragma_clang_loop;
    case 1: return Pragma_unroll;
    case 2: return Pragma_nounroll;
  }
  }
  OptionType getOption() const {
    return option;
  }

  static bool ConvertStrToOptionType(StringRef Val, OptionType &Out) {
    Optional<OptionType> R = llvm::StringSwitch<Optional<OptionType>>(Val)
      .Case("vectorize", LoopHintAttr::Vectorize)
      .Case("vectorize_width", LoopHintAttr::VectorizeWidth)
      .Case("interleave", LoopHintAttr::Interleave)
      .Case("interleave_count", LoopHintAttr::InterleaveCount)
      .Case("unroll", LoopHintAttr::Unroll)
      .Case("unroll_count", LoopHintAttr::UnrollCount)
      .Default(Optional<OptionType>());
    if (R) {
      Out = *R;
      return true;
    }
    return false;
  }

  static const char *ConvertOptionTypeToStr(OptionType Val) {
    switch(Val) {
    case LoopHintAttr::Vectorize: return "vectorize";
    case LoopHintAttr::VectorizeWidth: return "vectorize_width";
    case LoopHintAttr::Interleave: return "interleave";
    case LoopHintAttr::InterleaveCount: return "interleave_count";
    case LoopHintAttr::Unroll: return "unroll";
    case LoopHintAttr::UnrollCount: return "unroll_count";
    }
    llvm_unreachable("No enumerator with that value");
  }
  LoopHintState getState() const {
    return state;
  }

  static bool ConvertStrToLoopHintState(StringRef Val, LoopHintState &Out) {
    Optional<LoopHintState> R = llvm::StringSwitch<Optional<LoopHintState>>(Val)
      .Case("default", LoopHintAttr::Default)
      .Case("enable", LoopHintAttr::Enable)
      .Case("disable", LoopHintAttr::Disable)
      .Case("assume_safety", LoopHintAttr::AssumeSafety)
      .Default(Optional<LoopHintState>());
    if (R) {
      Out = *R;
      return true;
    }
    return false;
  }

  static const char *ConvertLoopHintStateToStr(LoopHintState Val) {
    switch(Val) {
    case LoopHintAttr::Default: return "default";
    case LoopHintAttr::Enable: return "enable";
    case LoopHintAttr::Disable: return "disable";
    case LoopHintAttr::AssumeSafety: return "assume_safety";
    }
    llvm_unreachable("No enumerator with that value");
  }
  Expr * getValue() const {
    return value;
  }


  static const char *getOptionName(int Option) {
    switch(Option) {
    case Vectorize: return "vectorize";
    case VectorizeWidth: return "vectorize_width";
    case Interleave: return "interleave";
    case InterleaveCount: return "interleave_count";
    case Unroll: return "unroll";
    case UnrollCount: return "unroll_count";
    }
    llvm_unreachable("Unhandled LoopHint option.");
  }

  void printPrettyPragma(raw_ostream &OS, const PrintingPolicy &Policy) const {
    unsigned SpellingIndex = getSpellingListIndex();
    // For "#pragma unroll" and "#pragma nounroll" the string "unroll" or
    // "nounroll" is already emitted as the pragma name.
    if (SpellingIndex == Pragma_nounroll) {
      OS << "\n";
      return;
    }
    else if (SpellingIndex == Pragma_unroll) {
      OS << getValueString(Policy) << "\n";
      return;
    }

    assert(SpellingIndex == Pragma_clang_loop && "Unexpected spelling");
    OS << getOptionName(option) << getValueString(Policy) << "\n";
  }

  // Return a string containing the loop hint argument including the
  // enclosing parentheses.
  std::string getValueString(const PrintingPolicy &Policy) const {
    std::string ValueName;
    llvm::raw_string_ostream OS(ValueName);
    OS << "(";
    if (option == VectorizeWidth || option == InterleaveCount ||
        option == UnrollCount)
      value->printPretty(OS, nullptr, Policy);
    else if (state == Default)
      return "";
    else if (state == Enable)
      OS << (option == Unroll ? "full" : "enable");
    else if (state == AssumeSafety)
      OS << "assume_safety";
    else
      OS << "disable";
    OS << ")";
    return OS.str();
  }

  // Return a string suitable for identifying this attribute in diagnostics.
  std::string getDiagnosticName(const PrintingPolicy &Policy) const {
    unsigned SpellingIndex = getSpellingListIndex();
    if (SpellingIndex == Pragma_nounroll)
      return "#pragma nounroll";
    else if (SpellingIndex == Pragma_unroll)
      return "#pragma unroll" + getValueString(Policy);

    assert(SpellingIndex == Pragma_clang_loop && "Unexpected spelling");
    return getOptionName(option) + getValueString(Policy);
  }
  

  static bool classof(const Attr *A) { return A->getKind() == attr::LoopHint; }
};

class MSABIAttr : public InheritableAttr {

public:
  static MSABIAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    MSABIAttr *A = new (Ctx) MSABIAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  MSABIAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::MSABI, R, SI, 0, 0)
  {
  }

  MSABIAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::MSABI; }
};

class MSInheritanceAttr : public InheritableAttr {
bool bestCase;


public:
  enum Spelling {
    Keyword_single_inheritance = 0,
    Keyword_multiple_inheritance = 1,
    Keyword_virtual_inheritance = 2,
    Keyword_unspecified_inheritance = 3
  };

  static MSInheritanceAttr *CreateImplicit(ASTContext &Ctx, Spelling S, bool BestCase, SourceRange Loc = SourceRange()) {
    MSInheritanceAttr *A = new (Ctx) MSInheritanceAttr(Loc, Ctx, BestCase, S);
    A->setImplicit(true);
    return A;
  }

  MSInheritanceAttr(SourceRange R, ASTContext &Ctx
              , bool BestCase
              , unsigned SI
             )
    : InheritableAttr(attr::MSInheritance, R, SI, 0, 0)
              , bestCase(BestCase)
  {

  }

  MSInheritanceAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::MSInheritance, R, SI, 0, 0)
              , bestCase()
  {
  }

  MSInheritanceAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  Spelling getSemanticSpelling() const {
  switch (SpellingListIndex) {
    default: llvm_unreachable("Unknown spelling list index");
    case 0: return Keyword_single_inheritance;
    case 1: return Keyword_multiple_inheritance;
    case 2: return Keyword_virtual_inheritance;
    case 3: return Keyword_unspecified_inheritance;
  }
  }
  bool getBestCase() const {
    return bestCase;
  }

  static const bool DefaultBestCase = 1;


  static bool hasVBPtrOffsetField(Spelling Inheritance) {
    return Inheritance == Keyword_unspecified_inheritance;
  }

  // Only member pointers to functions need a this adjustment, since it can be
  // combined with the field offset for data pointers.
  static bool hasNVOffsetField(bool IsMemberFunction, Spelling Inheritance) {
    return IsMemberFunction && Inheritance >= Keyword_multiple_inheritance;
  }

  static bool hasVBTableOffsetField(Spelling Inheritance) {
    return Inheritance >= Keyword_virtual_inheritance;
  }

  static bool hasOnlyOneField(bool IsMemberFunction,
                              Spelling Inheritance) {
    if (IsMemberFunction)
      return Inheritance <= Keyword_single_inheritance;
    return Inheritance <= Keyword_multiple_inheritance;
  }
  

  static bool classof(const Attr *A) { return A->getKind() == attr::MSInheritance; }
};

class MSNoVTableAttr : public InheritableAttr {

public:
  static MSNoVTableAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    MSNoVTableAttr *A = new (Ctx) MSNoVTableAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  MSNoVTableAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::MSNoVTable, R, SI, 0, 0)
  {
  }

  MSNoVTableAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::MSNoVTable; }
};

class MSP430InterruptAttr : public InheritableAttr {
unsigned number;


public:
  static MSP430InterruptAttr *CreateImplicit(ASTContext &Ctx, unsigned Number, SourceRange Loc = SourceRange()) {
    MSP430InterruptAttr *A = new (Ctx) MSP430InterruptAttr(Loc, Ctx, Number, 0);
    A->setImplicit(true);
    return A;
  }

  MSP430InterruptAttr(SourceRange R, ASTContext &Ctx
              , unsigned Number
              , unsigned SI
             )
    : InheritableAttr(attr::MSP430Interrupt, R, SI, 0, 0)
              , number(Number)
  {

  }

  MSP430InterruptAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  unsigned getNumber() const {
    return number;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::MSP430Interrupt; }
};

class MSStructAttr : public InheritableAttr {

public:
  static MSStructAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    MSStructAttr *A = new (Ctx) MSStructAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  MSStructAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::MSStruct, R, SI, 0, 0)
  {
  }

  MSStructAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::MSStruct; }
};

class MSVtorDispAttr : public InheritableAttr {
unsigned vdm;


public:
  static MSVtorDispAttr *CreateImplicit(ASTContext &Ctx, unsigned Vdm, SourceRange Loc = SourceRange()) {
    MSVtorDispAttr *A = new (Ctx) MSVtorDispAttr(Loc, Ctx, Vdm, 0);
    A->setImplicit(true);
    return A;
  }

  MSVtorDispAttr(SourceRange R, ASTContext &Ctx
              , unsigned Vdm
              , unsigned SI
             )
    : InheritableAttr(attr::MSVtorDisp, R, SI, 0, 0)
              , vdm(Vdm)
  {

  }

  MSVtorDispAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  unsigned getVdm() const {
    return vdm;
  }


  enum Mode {
    Never,
    ForVBaseOverride,
    ForVFTable
  };

  Mode getVtorDispMode() const { return Mode(vdm); }
  

  static bool classof(const Attr *A) { return A->getKind() == attr::MSVtorDisp; }
};

class MaxFieldAlignmentAttr : public InheritableAttr {
unsigned alignment;


public:
  static MaxFieldAlignmentAttr *CreateImplicit(ASTContext &Ctx, unsigned Alignment, SourceRange Loc = SourceRange()) {
    MaxFieldAlignmentAttr *A = new (Ctx) MaxFieldAlignmentAttr(Loc, Ctx, Alignment, 0);
    A->setImplicit(true);
    return A;
  }

  MaxFieldAlignmentAttr(SourceRange R, ASTContext &Ctx
              , unsigned Alignment
              , unsigned SI
             )
    : InheritableAttr(attr::MaxFieldAlignment, R, SI, 0, 0)
              , alignment(Alignment)
  {

  }

  MaxFieldAlignmentAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  unsigned getAlignment() const {
    return alignment;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::MaxFieldAlignment; }
};

class MayAliasAttr : public InheritableAttr {

public:
  static MayAliasAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    MayAliasAttr *A = new (Ctx) MayAliasAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  MayAliasAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::MayAlias, R, SI, 0, 0)
  {
  }

  MayAliasAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::MayAlias; }
};

class MinSizeAttr : public InheritableAttr {

public:
  static MinSizeAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    MinSizeAttr *A = new (Ctx) MinSizeAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  MinSizeAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::MinSize, R, SI, 0, 0)
  {
  }

  MinSizeAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::MinSize; }
};

class Mips16Attr : public InheritableAttr {

public:
  static Mips16Attr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    Mips16Attr *A = new (Ctx) Mips16Attr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  Mips16Attr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::Mips16, R, SI, 0, 0)
  {
  }

  Mips16Attr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::Mips16; }
};

class ModeAttr : public Attr {
IdentifierInfo * mode;


public:
  static ModeAttr *CreateImplicit(ASTContext &Ctx, IdentifierInfo * Mode, SourceRange Loc = SourceRange()) {
    ModeAttr *A = new (Ctx) ModeAttr(Loc, Ctx, Mode, 0);
    A->setImplicit(true);
    return A;
  }

  ModeAttr(SourceRange R, ASTContext &Ctx
              , IdentifierInfo * Mode
              , unsigned SI
             )
    : Attr(attr::Mode, R, SI, 0, 0)
              , mode(Mode)
  {

  }

  ModeAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  IdentifierInfo * getMode() const {
    return mode;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::Mode; }
};

class NSConsumedAttr : public InheritableParamAttr {

public:
  static NSConsumedAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    NSConsumedAttr *A = new (Ctx) NSConsumedAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  NSConsumedAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableParamAttr(attr::NSConsumed, R, SI, 0, 0)
  {
  }

  NSConsumedAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::NSConsumed; }
};

class NSConsumesSelfAttr : public InheritableAttr {

public:
  static NSConsumesSelfAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    NSConsumesSelfAttr *A = new (Ctx) NSConsumesSelfAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  NSConsumesSelfAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::NSConsumesSelf, R, SI, 0, 0)
  {
  }

  NSConsumesSelfAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::NSConsumesSelf; }
};

class NSReturnsAutoreleasedAttr : public InheritableAttr {

public:
  static NSReturnsAutoreleasedAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    NSReturnsAutoreleasedAttr *A = new (Ctx) NSReturnsAutoreleasedAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  NSReturnsAutoreleasedAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::NSReturnsAutoreleased, R, SI, 0, 0)
  {
  }

  NSReturnsAutoreleasedAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::NSReturnsAutoreleased; }
};

class NSReturnsNotRetainedAttr : public InheritableAttr {

public:
  static NSReturnsNotRetainedAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    NSReturnsNotRetainedAttr *A = new (Ctx) NSReturnsNotRetainedAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  NSReturnsNotRetainedAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::NSReturnsNotRetained, R, SI, 0, 0)
  {
  }

  NSReturnsNotRetainedAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::NSReturnsNotRetained; }
};

class NSReturnsRetainedAttr : public InheritableAttr {

public:
  static NSReturnsRetainedAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    NSReturnsRetainedAttr *A = new (Ctx) NSReturnsRetainedAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  NSReturnsRetainedAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::NSReturnsRetained, R, SI, 0, 0)
  {
  }

  NSReturnsRetainedAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::NSReturnsRetained; }
};

class NakedAttr : public InheritableAttr {

public:
  static NakedAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    NakedAttr *A = new (Ctx) NakedAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  NakedAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::Naked, R, SI, 0, 0)
  {
  }

  NakedAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::Naked; }
};

class NoCommonAttr : public InheritableAttr {

public:
  static NoCommonAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    NoCommonAttr *A = new (Ctx) NoCommonAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  NoCommonAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::NoCommon, R, SI, 0, 0)
  {
  }

  NoCommonAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::NoCommon; }
};

class NoDebugAttr : public InheritableAttr {

public:
  static NoDebugAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    NoDebugAttr *A = new (Ctx) NoDebugAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  NoDebugAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::NoDebug, R, SI, 0, 0)
  {
  }

  NoDebugAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::NoDebug; }
};

class NoDuplicateAttr : public InheritableAttr {

public:
  static NoDuplicateAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    NoDuplicateAttr *A = new (Ctx) NoDuplicateAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  NoDuplicateAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::NoDuplicate, R, SI, 0, 0)
  {
  }

  NoDuplicateAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::NoDuplicate; }
};

class NoInlineAttr : public InheritableAttr {

public:
  static NoInlineAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    NoInlineAttr *A = new (Ctx) NoInlineAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  NoInlineAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::NoInline, R, SI, 0, 0)
  {
  }

  NoInlineAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::NoInline; }
};

class NoInstrumentFunctionAttr : public InheritableAttr {

public:
  static NoInstrumentFunctionAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    NoInstrumentFunctionAttr *A = new (Ctx) NoInstrumentFunctionAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  NoInstrumentFunctionAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::NoInstrumentFunction, R, SI, 0, 0)
  {
  }

  NoInstrumentFunctionAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::NoInstrumentFunction; }
};

class NoMips16Attr : public InheritableAttr {

public:
  static NoMips16Attr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    NoMips16Attr *A = new (Ctx) NoMips16Attr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  NoMips16Attr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::NoMips16, R, SI, 0, 0)
  {
  }

  NoMips16Attr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::NoMips16; }
};

class NoReturnAttr : public InheritableAttr {

public:
  static NoReturnAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    NoReturnAttr *A = new (Ctx) NoReturnAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  NoReturnAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::NoReturn, R, SI, 0, 0)
  {
  }

  NoReturnAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::NoReturn; }
};

class NoSanitizeAttr : public InheritableAttr {
  unsigned sanitizers_Size;
  std::string *sanitizers_;


public:
  static NoSanitizeAttr *CreateImplicit(ASTContext &Ctx, std::string *Sanitizers, unsigned SanitizersSize, SourceRange Loc = SourceRange()) {
    NoSanitizeAttr *A = new (Ctx) NoSanitizeAttr(Loc, Ctx, Sanitizers, SanitizersSize, 0);
    A->setImplicit(true);
    return A;
  }

  NoSanitizeAttr(SourceRange R, ASTContext &Ctx
              , std::string *Sanitizers, unsigned SanitizersSize
              , unsigned SI
             )
    : InheritableAttr(attr::NoSanitize, R, SI, 0, 0)
              , sanitizers_Size(SanitizersSize), sanitizers_(new (Ctx, 16) std::string[sanitizers_Size])
  {
    std::copy(Sanitizers, Sanitizers + sanitizers_Size, sanitizers_);
  }

  NoSanitizeAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::NoSanitize, R, SI, 0, 0)
              , sanitizers_Size(0), sanitizers_(nullptr)
  {
  }

  NoSanitizeAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  typedef std::string* sanitizers_iterator;
  sanitizers_iterator sanitizers_begin() const { return sanitizers_; }
  sanitizers_iterator sanitizers_end() const { return sanitizers_ + sanitizers_Size; }
  unsigned sanitizers_size() const { return sanitizers_Size; }
  llvm::iterator_range<sanitizers_iterator> sanitizers() const { return llvm::make_range(sanitizers_begin(), sanitizers_end()); }



    SanitizerMask getMask() const {
      SanitizerMask Mask = 0;
      for (auto SanitizerName : sanitizers()) {
        SanitizerMask ParsedMask =
            parseSanitizerValue(SanitizerName, /*AllowGroups=*/true);
        Mask |= expandSanitizerGroups(ParsedMask);
      }
      return Mask;
    }
  

  static bool classof(const Attr *A) { return A->getKind() == attr::NoSanitize; }
};

class NoSplitStackAttr : public InheritableAttr {

public:
  static NoSplitStackAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    NoSplitStackAttr *A = new (Ctx) NoSplitStackAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  NoSplitStackAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::NoSplitStack, R, SI, 0, 0)
  {
  }

  NoSplitStackAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::NoSplitStack; }
};

class NoThreadSafetyAnalysisAttr : public InheritableAttr {

public:
  static NoThreadSafetyAnalysisAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    NoThreadSafetyAnalysisAttr *A = new (Ctx) NoThreadSafetyAnalysisAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  NoThreadSafetyAnalysisAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::NoThreadSafetyAnalysis, R, SI, 0, 0)
  {
  }

  NoThreadSafetyAnalysisAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::NoThreadSafetyAnalysis; }
};

class NoThrowAttr : public InheritableAttr {

public:
  static NoThrowAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    NoThrowAttr *A = new (Ctx) NoThrowAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  NoThrowAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::NoThrow, R, SI, 0, 0)
  {
  }

  NoThrowAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::NoThrow; }
};

class NonNullAttr : public InheritableAttr {
  unsigned args_Size;
  unsigned *args_;


public:
  static NonNullAttr *CreateImplicit(ASTContext &Ctx, unsigned *Args, unsigned ArgsSize, SourceRange Loc = SourceRange()) {
    NonNullAttr *A = new (Ctx) NonNullAttr(Loc, Ctx, Args, ArgsSize, 0);
    A->setImplicit(true);
    return A;
  }

  NonNullAttr(SourceRange R, ASTContext &Ctx
              , unsigned *Args, unsigned ArgsSize
              , unsigned SI
             )
    : InheritableAttr(attr::NonNull, R, SI, 0, 1)
              , args_Size(ArgsSize), args_(new (Ctx, 16) unsigned[args_Size])
  {
    std::copy(Args, Args + args_Size, args_);
  }

  NonNullAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::NonNull, R, SI, 0, 1)
              , args_Size(0), args_(nullptr)
  {
  }

  NonNullAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  typedef unsigned* args_iterator;
  args_iterator args_begin() const { return args_; }
  args_iterator args_end() const { return args_ + args_Size; }
  unsigned args_size() const { return args_Size; }
  llvm::iterator_range<args_iterator> args() const { return llvm::make_range(args_begin(), args_end()); }


bool isNonNull(unsigned idx) const {
    if (!args_size())
      return true;
    for (const auto &V : args())
      if (V == idx)
        return true;
    return false;
  } 

  static bool classof(const Attr *A) { return A->getKind() == attr::NonNull; }
};

class OMPThreadPrivateDeclAttr : public InheritableAttr {

public:
  static OMPThreadPrivateDeclAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    OMPThreadPrivateDeclAttr *A = new (Ctx) OMPThreadPrivateDeclAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  OMPThreadPrivateDeclAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::OMPThreadPrivateDecl, R, SI, 0, 0)
  {
  }

  OMPThreadPrivateDeclAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::OMPThreadPrivateDecl; }
};

class ObjCBoxableAttr : public Attr {

public:
  static ObjCBoxableAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    ObjCBoxableAttr *A = new (Ctx) ObjCBoxableAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  ObjCBoxableAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : Attr(attr::ObjCBoxable, R, SI, 0, 0)
  {
  }

  ObjCBoxableAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::ObjCBoxable; }
};

class ObjCBridgeAttr : public InheritableAttr {
IdentifierInfo * bridgedType;


public:
  static ObjCBridgeAttr *CreateImplicit(ASTContext &Ctx, IdentifierInfo * BridgedType, SourceRange Loc = SourceRange()) {
    ObjCBridgeAttr *A = new (Ctx) ObjCBridgeAttr(Loc, Ctx, BridgedType, 0);
    A->setImplicit(true);
    return A;
  }

  ObjCBridgeAttr(SourceRange R, ASTContext &Ctx
              , IdentifierInfo * BridgedType
              , unsigned SI
             )
    : InheritableAttr(attr::ObjCBridge, R, SI, 0, 0)
              , bridgedType(BridgedType)
  {

  }

  ObjCBridgeAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  IdentifierInfo * getBridgedType() const {
    return bridgedType;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::ObjCBridge; }
};

class ObjCBridgeMutableAttr : public InheritableAttr {
IdentifierInfo * bridgedType;


public:
  static ObjCBridgeMutableAttr *CreateImplicit(ASTContext &Ctx, IdentifierInfo * BridgedType, SourceRange Loc = SourceRange()) {
    ObjCBridgeMutableAttr *A = new (Ctx) ObjCBridgeMutableAttr(Loc, Ctx, BridgedType, 0);
    A->setImplicit(true);
    return A;
  }

  ObjCBridgeMutableAttr(SourceRange R, ASTContext &Ctx
              , IdentifierInfo * BridgedType
              , unsigned SI
             )
    : InheritableAttr(attr::ObjCBridgeMutable, R, SI, 0, 0)
              , bridgedType(BridgedType)
  {

  }

  ObjCBridgeMutableAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  IdentifierInfo * getBridgedType() const {
    return bridgedType;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::ObjCBridgeMutable; }
};

class ObjCBridgeRelatedAttr : public InheritableAttr {
IdentifierInfo * relatedClass;

IdentifierInfo * classMethod;

IdentifierInfo * instanceMethod;


public:
  static ObjCBridgeRelatedAttr *CreateImplicit(ASTContext &Ctx, IdentifierInfo * RelatedClass, IdentifierInfo * ClassMethod, IdentifierInfo * InstanceMethod, SourceRange Loc = SourceRange()) {
    ObjCBridgeRelatedAttr *A = new (Ctx) ObjCBridgeRelatedAttr(Loc, Ctx, RelatedClass, ClassMethod, InstanceMethod, 0);
    A->setImplicit(true);
    return A;
  }

  ObjCBridgeRelatedAttr(SourceRange R, ASTContext &Ctx
              , IdentifierInfo * RelatedClass
              , IdentifierInfo * ClassMethod
              , IdentifierInfo * InstanceMethod
              , unsigned SI
             )
    : InheritableAttr(attr::ObjCBridgeRelated, R, SI, 0, 0)
              , relatedClass(RelatedClass)
              , classMethod(ClassMethod)
              , instanceMethod(InstanceMethod)
  {



  }

  ObjCBridgeRelatedAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  IdentifierInfo * getRelatedClass() const {
    return relatedClass;
  }

  IdentifierInfo * getClassMethod() const {
    return classMethod;
  }

  IdentifierInfo * getInstanceMethod() const {
    return instanceMethod;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::ObjCBridgeRelated; }
};

class ObjCDesignatedInitializerAttr : public Attr {

public:
  static ObjCDesignatedInitializerAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    ObjCDesignatedInitializerAttr *A = new (Ctx) ObjCDesignatedInitializerAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  ObjCDesignatedInitializerAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : Attr(attr::ObjCDesignatedInitializer, R, SI, 0, 0)
  {
  }

  ObjCDesignatedInitializerAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::ObjCDesignatedInitializer; }
};

class ObjCExceptionAttr : public InheritableAttr {

public:
  static ObjCExceptionAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    ObjCExceptionAttr *A = new (Ctx) ObjCExceptionAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  ObjCExceptionAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::ObjCException, R, SI, 0, 0)
  {
  }

  ObjCExceptionAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::ObjCException; }
};

class ObjCExplicitProtocolImplAttr : public InheritableAttr {

public:
  static ObjCExplicitProtocolImplAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    ObjCExplicitProtocolImplAttr *A = new (Ctx) ObjCExplicitProtocolImplAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  ObjCExplicitProtocolImplAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::ObjCExplicitProtocolImpl, R, SI, 0, 0)
  {
  }

  ObjCExplicitProtocolImplAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::ObjCExplicitProtocolImpl; }
};

class ObjCIndependentClassAttr : public InheritableAttr {

public:
  static ObjCIndependentClassAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    ObjCIndependentClassAttr *A = new (Ctx) ObjCIndependentClassAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  ObjCIndependentClassAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::ObjCIndependentClass, R, SI, 0, 0)
  {
  }

  ObjCIndependentClassAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::ObjCIndependentClass; }
};

class ObjCMethodFamilyAttr : public InheritableAttr {
public:
  enum FamilyKind {
    OMF_None,
    OMF_alloc,
    OMF_copy,
    OMF_init,
    OMF_mutableCopy,
    OMF_new
  };
private:
  FamilyKind family;


public:
  static ObjCMethodFamilyAttr *CreateImplicit(ASTContext &Ctx, FamilyKind Family, SourceRange Loc = SourceRange()) {
    ObjCMethodFamilyAttr *A = new (Ctx) ObjCMethodFamilyAttr(Loc, Ctx, Family, 0);
    A->setImplicit(true);
    return A;
  }

  ObjCMethodFamilyAttr(SourceRange R, ASTContext &Ctx
              , FamilyKind Family
              , unsigned SI
             )
    : InheritableAttr(attr::ObjCMethodFamily, R, SI, 0, 0)
              , family(Family)
  {

  }

  ObjCMethodFamilyAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  FamilyKind getFamily() const {
    return family;
  }

  static bool ConvertStrToFamilyKind(StringRef Val, FamilyKind &Out) {
    Optional<FamilyKind> R = llvm::StringSwitch<Optional<FamilyKind>>(Val)
      .Case("none", ObjCMethodFamilyAttr::OMF_None)
      .Case("alloc", ObjCMethodFamilyAttr::OMF_alloc)
      .Case("copy", ObjCMethodFamilyAttr::OMF_copy)
      .Case("init", ObjCMethodFamilyAttr::OMF_init)
      .Case("mutableCopy", ObjCMethodFamilyAttr::OMF_mutableCopy)
      .Case("new", ObjCMethodFamilyAttr::OMF_new)
      .Default(Optional<FamilyKind>());
    if (R) {
      Out = *R;
      return true;
    }
    return false;
  }

  static const char *ConvertFamilyKindToStr(FamilyKind Val) {
    switch(Val) {
    case ObjCMethodFamilyAttr::OMF_None: return "none";
    case ObjCMethodFamilyAttr::OMF_alloc: return "alloc";
    case ObjCMethodFamilyAttr::OMF_copy: return "copy";
    case ObjCMethodFamilyAttr::OMF_init: return "init";
    case ObjCMethodFamilyAttr::OMF_mutableCopy: return "mutableCopy";
    case ObjCMethodFamilyAttr::OMF_new: return "new";
    }
    llvm_unreachable("No enumerator with that value");
  }


  static bool classof(const Attr *A) { return A->getKind() == attr::ObjCMethodFamily; }
};

class ObjCNSObjectAttr : public InheritableAttr {

public:
  static ObjCNSObjectAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    ObjCNSObjectAttr *A = new (Ctx) ObjCNSObjectAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  ObjCNSObjectAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::ObjCNSObject, R, SI, 0, 0)
  {
  }

  ObjCNSObjectAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::ObjCNSObject; }
};

class ObjCPreciseLifetimeAttr : public InheritableAttr {

public:
  static ObjCPreciseLifetimeAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    ObjCPreciseLifetimeAttr *A = new (Ctx) ObjCPreciseLifetimeAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  ObjCPreciseLifetimeAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::ObjCPreciseLifetime, R, SI, 0, 0)
  {
  }

  ObjCPreciseLifetimeAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::ObjCPreciseLifetime; }
};

class ObjCRequiresPropertyDefsAttr : public InheritableAttr {

public:
  static ObjCRequiresPropertyDefsAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    ObjCRequiresPropertyDefsAttr *A = new (Ctx) ObjCRequiresPropertyDefsAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  ObjCRequiresPropertyDefsAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::ObjCRequiresPropertyDefs, R, SI, 0, 0)
  {
  }

  ObjCRequiresPropertyDefsAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::ObjCRequiresPropertyDefs; }
};

class ObjCRequiresSuperAttr : public InheritableAttr {

public:
  static ObjCRequiresSuperAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    ObjCRequiresSuperAttr *A = new (Ctx) ObjCRequiresSuperAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  ObjCRequiresSuperAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::ObjCRequiresSuper, R, SI, 0, 0)
  {
  }

  ObjCRequiresSuperAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::ObjCRequiresSuper; }
};

class ObjCReturnsInnerPointerAttr : public InheritableAttr {

public:
  static ObjCReturnsInnerPointerAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    ObjCReturnsInnerPointerAttr *A = new (Ctx) ObjCReturnsInnerPointerAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  ObjCReturnsInnerPointerAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::ObjCReturnsInnerPointer, R, SI, 0, 0)
  {
  }

  ObjCReturnsInnerPointerAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::ObjCReturnsInnerPointer; }
};

class ObjCRootClassAttr : public InheritableAttr {

public:
  static ObjCRootClassAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    ObjCRootClassAttr *A = new (Ctx) ObjCRootClassAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  ObjCRootClassAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::ObjCRootClass, R, SI, 0, 0)
  {
  }

  ObjCRootClassAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::ObjCRootClass; }
};

class ObjCRuntimeNameAttr : public Attr {
unsigned metadataNameLength;
char *metadataName;


public:
  static ObjCRuntimeNameAttr *CreateImplicit(ASTContext &Ctx, llvm::StringRef MetadataName, SourceRange Loc = SourceRange()) {
    ObjCRuntimeNameAttr *A = new (Ctx) ObjCRuntimeNameAttr(Loc, Ctx, MetadataName, 0);
    A->setImplicit(true);
    return A;
  }

  ObjCRuntimeNameAttr(SourceRange R, ASTContext &Ctx
              , llvm::StringRef MetadataName
              , unsigned SI
             )
    : Attr(attr::ObjCRuntimeName, R, SI, 0, 0)
              , metadataNameLength(MetadataName.size()),metadataName(new (Ctx, 1) char[metadataNameLength])
  {
      if (!MetadataName.empty())
        std::memcpy(metadataName, MetadataName.data(), metadataNameLength);
  }

  ObjCRuntimeNameAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  llvm::StringRef getMetadataName() const {
    return llvm::StringRef(metadataName, metadataNameLength);
  }
  unsigned getMetadataNameLength() const {
    return metadataNameLength;
  }
  void setMetadataName(ASTContext &C, llvm::StringRef S) {
    metadataNameLength = S.size();
    this->metadataName = new (C, 1) char [metadataNameLength];
    if (!S.empty())
      std::memcpy(this->metadataName, S.data(), metadataNameLength);
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::ObjCRuntimeName; }
};

class OpenCLImageAccessAttr : public Attr {

public:
  enum Spelling {
    Keyword_read_only = 0,
    Keyword_write_only = 2,
    Keyword_read_write = 4
  };

  static OpenCLImageAccessAttr *CreateImplicit(ASTContext &Ctx, Spelling S, SourceRange Loc = SourceRange()) {
    OpenCLImageAccessAttr *A = new (Ctx) OpenCLImageAccessAttr(Loc, Ctx, S);
    A->setImplicit(true);
    return A;
  }

  OpenCLImageAccessAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : Attr(attr::OpenCLImageAccess, R, SI, 0, 0)
  {
  }

  OpenCLImageAccessAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  Spelling getSemanticSpelling() const {
  switch (SpellingListIndex) {
    default: llvm_unreachable("Unknown spelling list index");
    case 0: return Keyword_read_only;
    case 1: return Keyword_read_only;
    case 2: return Keyword_write_only;
    case 3: return Keyword_write_only;
    case 4: return Keyword_read_write;
    case 5: return Keyword_read_write;
  }
  }
  bool isReadOnly() const { return SpellingListIndex == 0 ||
    SpellingListIndex == 1; }
  bool isReadWrite() const { return SpellingListIndex == 4 ||
    SpellingListIndex == 5; }
  bool isWriteOnly() const { return SpellingListIndex == 2 ||
    SpellingListIndex == 3; }


  static bool classof(const Attr *A) { return A->getKind() == attr::OpenCLImageAccess; }
};

class OpenCLKernelAttr : public InheritableAttr {

public:
  static OpenCLKernelAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    OpenCLKernelAttr *A = new (Ctx) OpenCLKernelAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  OpenCLKernelAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::OpenCLKernel, R, SI, 0, 0)
  {
  }

  OpenCLKernelAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::OpenCLKernel; }
};

class OptimizeNoneAttr : public InheritableAttr {

public:
  static OptimizeNoneAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    OptimizeNoneAttr *A = new (Ctx) OptimizeNoneAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  OptimizeNoneAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::OptimizeNone, R, SI, 0, 0)
  {
  }

  OptimizeNoneAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::OptimizeNone; }
};

class OverloadableAttr : public Attr {

public:
  static OverloadableAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    OverloadableAttr *A = new (Ctx) OverloadableAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  OverloadableAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : Attr(attr::Overloadable, R, SI, 0, 0)
  {
  }

  OverloadableAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::Overloadable; }
};

class OverrideAttr : public InheritableAttr {

public:
  static OverrideAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    OverrideAttr *A = new (Ctx) OverrideAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  OverrideAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::Override, R, SI, 0, 0)
  {
  }

  OverrideAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::Override; }
};

class OwnershipAttr : public InheritableAttr {
IdentifierInfo * module;

  unsigned args_Size;
  unsigned *args_;


public:
  enum Spelling {
    GNU_ownership_holds = 0,
    GNU_ownership_returns = 1,
    GNU_ownership_takes = 2
  };

  static OwnershipAttr *CreateImplicit(ASTContext &Ctx, Spelling S, IdentifierInfo * Module, unsigned *Args, unsigned ArgsSize, SourceRange Loc = SourceRange()) {
    OwnershipAttr *A = new (Ctx) OwnershipAttr(Loc, Ctx, Module, Args, ArgsSize, S);
    A->setImplicit(true);
    return A;
  }

  OwnershipAttr(SourceRange R, ASTContext &Ctx
              , IdentifierInfo * Module
              , unsigned *Args, unsigned ArgsSize
              , unsigned SI
             )
    : InheritableAttr(attr::Ownership, R, SI, 0, 0)
              , module(Module)
              , args_Size(ArgsSize), args_(new (Ctx, 16) unsigned[args_Size])
  {

    std::copy(Args, Args + args_Size, args_);
  }

  OwnershipAttr(SourceRange R, ASTContext &Ctx
              , IdentifierInfo * Module
              , unsigned SI
             )
    : InheritableAttr(attr::Ownership, R, SI, 0, 0)
              , module()
              , args_Size(0), args_(nullptr)
  {

  }

  OwnershipAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  Spelling getSemanticSpelling() const {
  switch (SpellingListIndex) {
    default: llvm_unreachable("Unknown spelling list index");
    case 0: return GNU_ownership_holds;
    case 1: return GNU_ownership_returns;
    case 2: return GNU_ownership_takes;
  }
  }
  bool isHolds() const { return SpellingListIndex == 0; }
  bool isReturns() const { return SpellingListIndex == 1; }
  bool isTakes() const { return SpellingListIndex == 2; }
  IdentifierInfo * getModule() const {
    return module;
  }

  typedef unsigned* args_iterator;
  args_iterator args_begin() const { return args_; }
  args_iterator args_end() const { return args_ + args_Size; }
  unsigned args_size() const { return args_Size; }
  llvm::iterator_range<args_iterator> args() const { return llvm::make_range(args_begin(), args_end()); }



    enum OwnershipKind { Holds, Returns, Takes };
    OwnershipKind getOwnKind() const {
      return isHolds() ? Holds :
             isTakes() ? Takes :
             Returns;
    }
  

  static bool classof(const Attr *A) { return A->getKind() == attr::Ownership; }
};

class PackedAttr : public InheritableAttr {

public:
  static PackedAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    PackedAttr *A = new (Ctx) PackedAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  PackedAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::Packed, R, SI, 0, 0)
  {
  }

  PackedAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::Packed; }
};

class ParamTypestateAttr : public InheritableAttr {
public:
  enum ConsumedState {
    Unknown,
    Consumed,
    Unconsumed
  };
private:
  ConsumedState paramState;


public:
  static ParamTypestateAttr *CreateImplicit(ASTContext &Ctx, ConsumedState ParamState, SourceRange Loc = SourceRange()) {
    ParamTypestateAttr *A = new (Ctx) ParamTypestateAttr(Loc, Ctx, ParamState, 0);
    A->setImplicit(true);
    return A;
  }

  ParamTypestateAttr(SourceRange R, ASTContext &Ctx
              , ConsumedState ParamState
              , unsigned SI
             )
    : InheritableAttr(attr::ParamTypestate, R, SI, 0, 0)
              , paramState(ParamState)
  {

  }

  ParamTypestateAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  ConsumedState getParamState() const {
    return paramState;
  }

  static bool ConvertStrToConsumedState(StringRef Val, ConsumedState &Out) {
    Optional<ConsumedState> R = llvm::StringSwitch<Optional<ConsumedState>>(Val)
      .Case("unknown", ParamTypestateAttr::Unknown)
      .Case("consumed", ParamTypestateAttr::Consumed)
      .Case("unconsumed", ParamTypestateAttr::Unconsumed)
      .Default(Optional<ConsumedState>());
    if (R) {
      Out = *R;
      return true;
    }
    return false;
  }

  static const char *ConvertConsumedStateToStr(ConsumedState Val) {
    switch(Val) {
    case ParamTypestateAttr::Unknown: return "unknown";
    case ParamTypestateAttr::Consumed: return "consumed";
    case ParamTypestateAttr::Unconsumed: return "unconsumed";
    }
    llvm_unreachable("No enumerator with that value");
  }


  static bool classof(const Attr *A) { return A->getKind() == attr::ParamTypestate; }
};

class PascalAttr : public InheritableAttr {

public:
  static PascalAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    PascalAttr *A = new (Ctx) PascalAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  PascalAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::Pascal, R, SI, 0, 0)
  {
  }

  PascalAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::Pascal; }
};

class PcsAttr : public InheritableAttr {
public:
  enum PCSType {
    AAPCS,
    AAPCS_VFP
  };
private:
  PCSType pCS;


public:
  static PcsAttr *CreateImplicit(ASTContext &Ctx, PCSType PCS, SourceRange Loc = SourceRange()) {
    PcsAttr *A = new (Ctx) PcsAttr(Loc, Ctx, PCS, 0);
    A->setImplicit(true);
    return A;
  }

  PcsAttr(SourceRange R, ASTContext &Ctx
              , PCSType PCS
              , unsigned SI
             )
    : InheritableAttr(attr::Pcs, R, SI, 0, 0)
              , pCS(PCS)
  {

  }

  PcsAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  PCSType getPCS() const {
    return pCS;
  }

  static bool ConvertStrToPCSType(StringRef Val, PCSType &Out) {
    Optional<PCSType> R = llvm::StringSwitch<Optional<PCSType>>(Val)
      .Case("aapcs", PcsAttr::AAPCS)
      .Case("aapcs-vfp", PcsAttr::AAPCS_VFP)
      .Default(Optional<PCSType>());
    if (R) {
      Out = *R;
      return true;
    }
    return false;
  }

  static const char *ConvertPCSTypeToStr(PCSType Val) {
    switch(Val) {
    case PcsAttr::AAPCS: return "aapcs";
    case PcsAttr::AAPCS_VFP: return "aapcs-vfp";
    }
    llvm_unreachable("No enumerator with that value");
  }


  static bool classof(const Attr *A) { return A->getKind() == attr::Pcs; }
};

class PtGuardedByAttr : public InheritableAttr {
Expr * arg;


public:
  static PtGuardedByAttr *CreateImplicit(ASTContext &Ctx, Expr * Arg, SourceRange Loc = SourceRange()) {
    PtGuardedByAttr *A = new (Ctx) PtGuardedByAttr(Loc, Ctx, Arg, 0);
    A->setImplicit(true);
    return A;
  }

  PtGuardedByAttr(SourceRange R, ASTContext &Ctx
              , Expr * Arg
              , unsigned SI
             )
    : InheritableAttr(attr::PtGuardedBy, R, SI, 1, 1)
              , arg(Arg)
  {

  }

  PtGuardedByAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  Expr * getArg() const {
    return arg;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::PtGuardedBy; }
};

class PtGuardedVarAttr : public InheritableAttr {

public:
  static PtGuardedVarAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    PtGuardedVarAttr *A = new (Ctx) PtGuardedVarAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  PtGuardedVarAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::PtGuardedVar, R, SI, 0, 0)
  {
  }

  PtGuardedVarAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::PtGuardedVar; }
};

class PureAttr : public InheritableAttr {

public:
  static PureAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    PureAttr *A = new (Ctx) PureAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  PureAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::Pure, R, SI, 0, 0)
  {
  }

  PureAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::Pure; }
};

class ReleaseCapabilityAttr : public InheritableAttr {
  unsigned args_Size;
  Expr * *args_;


public:
  enum Spelling {
    GNU_release_capability = 0,
    CXX11_clang_release_capability = 1,
    GNU_release_shared_capability = 2,
    CXX11_clang_release_shared_capability = 3,
    GNU_release_generic_capability = 4,
    CXX11_clang_release_generic_capability = 5,
    GNU_unlock_function = 6
  };

  static ReleaseCapabilityAttr *CreateImplicit(ASTContext &Ctx, Spelling S, Expr * *Args, unsigned ArgsSize, SourceRange Loc = SourceRange()) {
    ReleaseCapabilityAttr *A = new (Ctx) ReleaseCapabilityAttr(Loc, Ctx, Args, ArgsSize, S);
    A->setImplicit(true);
    return A;
  }

  ReleaseCapabilityAttr(SourceRange R, ASTContext &Ctx
              , Expr * *Args, unsigned ArgsSize
              , unsigned SI
             )
    : InheritableAttr(attr::ReleaseCapability, R, SI, 1, 1)
              , args_Size(ArgsSize), args_(new (Ctx, 16) Expr *[args_Size])
  {
    std::copy(Args, Args + args_Size, args_);
  }

  ReleaseCapabilityAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::ReleaseCapability, R, SI, 1, 1)
              , args_Size(0), args_(nullptr)
  {
  }

  ReleaseCapabilityAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  Spelling getSemanticSpelling() const {
  switch (SpellingListIndex) {
    default: llvm_unreachable("Unknown spelling list index");
    case 0: return GNU_release_capability;
    case 1: return CXX11_clang_release_capability;
    case 2: return GNU_release_shared_capability;
    case 3: return CXX11_clang_release_shared_capability;
    case 4: return GNU_release_generic_capability;
    case 5: return CXX11_clang_release_generic_capability;
    case 6: return GNU_unlock_function;
  }
  }
  bool isShared() const { return SpellingListIndex == 2 ||
    SpellingListIndex == 3; }
  bool isGeneric() const { return SpellingListIndex == 4 ||
    SpellingListIndex == 5 ||
    SpellingListIndex == 6; }
  typedef Expr ** args_iterator;
  args_iterator args_begin() const { return args_; }
  args_iterator args_end() const { return args_ + args_Size; }
  unsigned args_size() const { return args_Size; }
  llvm::iterator_range<args_iterator> args() const { return llvm::make_range(args_begin(), args_end()); }




  static bool classof(const Attr *A) { return A->getKind() == attr::ReleaseCapability; }
};

class ReqdWorkGroupSizeAttr : public InheritableAttr {
unsigned xDim;

unsigned yDim;

unsigned zDim;


public:
  static ReqdWorkGroupSizeAttr *CreateImplicit(ASTContext &Ctx, unsigned XDim, unsigned YDim, unsigned ZDim, SourceRange Loc = SourceRange()) {
    ReqdWorkGroupSizeAttr *A = new (Ctx) ReqdWorkGroupSizeAttr(Loc, Ctx, XDim, YDim, ZDim, 0);
    A->setImplicit(true);
    return A;
  }

  ReqdWorkGroupSizeAttr(SourceRange R, ASTContext &Ctx
              , unsigned XDim
              , unsigned YDim
              , unsigned ZDim
              , unsigned SI
             )
    : InheritableAttr(attr::ReqdWorkGroupSize, R, SI, 0, 0)
              , xDim(XDim)
              , yDim(YDim)
              , zDim(ZDim)
  {



  }

  ReqdWorkGroupSizeAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  unsigned getXDim() const {
    return xDim;
  }

  unsigned getYDim() const {
    return yDim;
  }

  unsigned getZDim() const {
    return zDim;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::ReqdWorkGroupSize; }
};

class RequiresCapabilityAttr : public InheritableAttr {
  unsigned args_Size;
  Expr * *args_;


public:
  enum Spelling {
    GNU_requires_capability = 0,
    CXX11_clang_requires_capability = 1,
    GNU_exclusive_locks_required = 2,
    GNU_requires_shared_capability = 3,
    CXX11_clang_requires_shared_capability = 4,
    GNU_shared_locks_required = 5
  };

  static RequiresCapabilityAttr *CreateImplicit(ASTContext &Ctx, Spelling S, Expr * *Args, unsigned ArgsSize, SourceRange Loc = SourceRange()) {
    RequiresCapabilityAttr *A = new (Ctx) RequiresCapabilityAttr(Loc, Ctx, Args, ArgsSize, S);
    A->setImplicit(true);
    return A;
  }

  RequiresCapabilityAttr(SourceRange R, ASTContext &Ctx
              , Expr * *Args, unsigned ArgsSize
              , unsigned SI
             )
    : InheritableAttr(attr::RequiresCapability, R, SI, 1, 1)
              , args_Size(ArgsSize), args_(new (Ctx, 16) Expr *[args_Size])
  {
    std::copy(Args, Args + args_Size, args_);
  }

  RequiresCapabilityAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::RequiresCapability, R, SI, 1, 1)
              , args_Size(0), args_(nullptr)
  {
  }

  RequiresCapabilityAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  Spelling getSemanticSpelling() const {
  switch (SpellingListIndex) {
    default: llvm_unreachable("Unknown spelling list index");
    case 0: return GNU_requires_capability;
    case 1: return CXX11_clang_requires_capability;
    case 2: return GNU_exclusive_locks_required;
    case 3: return GNU_requires_shared_capability;
    case 4: return CXX11_clang_requires_shared_capability;
    case 5: return GNU_shared_locks_required;
  }
  }
  bool isShared() const { return SpellingListIndex == 3 ||
    SpellingListIndex == 5 ||
    SpellingListIndex == 4; }
  typedef Expr ** args_iterator;
  args_iterator args_begin() const { return args_; }
  args_iterator args_end() const { return args_ + args_Size; }
  unsigned args_size() const { return args_Size; }
  llvm::iterator_range<args_iterator> args() const { return llvm::make_range(args_begin(), args_end()); }




  static bool classof(const Attr *A) { return A->getKind() == attr::RequiresCapability; }
};

class RestrictAttr : public InheritableAttr {

public:
  enum Spelling {
    Declspec_restrict = 0,
    GNU_malloc = 1,
    CXX11_gnu_malloc = 2
  };

  static RestrictAttr *CreateImplicit(ASTContext &Ctx, Spelling S, SourceRange Loc = SourceRange()) {
    RestrictAttr *A = new (Ctx) RestrictAttr(Loc, Ctx, S);
    A->setImplicit(true);
    return A;
  }

  RestrictAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::Restrict, R, SI, 0, 0)
  {
  }

  RestrictAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  Spelling getSemanticSpelling() const {
  switch (SpellingListIndex) {
    default: llvm_unreachable("Unknown spelling list index");
    case 0: return Declspec_restrict;
    case 1: return GNU_malloc;
    case 2: return CXX11_gnu_malloc;
  }
  }


  static bool classof(const Attr *A) { return A->getKind() == attr::Restrict; }
};

class ReturnTypestateAttr : public InheritableAttr {
public:
  enum ConsumedState {
    Unknown,
    Consumed,
    Unconsumed
  };
private:
  ConsumedState state;


public:
  static ReturnTypestateAttr *CreateImplicit(ASTContext &Ctx, ConsumedState State, SourceRange Loc = SourceRange()) {
    ReturnTypestateAttr *A = new (Ctx) ReturnTypestateAttr(Loc, Ctx, State, 0);
    A->setImplicit(true);
    return A;
  }

  ReturnTypestateAttr(SourceRange R, ASTContext &Ctx
              , ConsumedState State
              , unsigned SI
             )
    : InheritableAttr(attr::ReturnTypestate, R, SI, 0, 0)
              , state(State)
  {

  }

  ReturnTypestateAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  ConsumedState getState() const {
    return state;
  }

  static bool ConvertStrToConsumedState(StringRef Val, ConsumedState &Out) {
    Optional<ConsumedState> R = llvm::StringSwitch<Optional<ConsumedState>>(Val)
      .Case("unknown", ReturnTypestateAttr::Unknown)
      .Case("consumed", ReturnTypestateAttr::Consumed)
      .Case("unconsumed", ReturnTypestateAttr::Unconsumed)
      .Default(Optional<ConsumedState>());
    if (R) {
      Out = *R;
      return true;
    }
    return false;
  }

  static const char *ConvertConsumedStateToStr(ConsumedState Val) {
    switch(Val) {
    case ReturnTypestateAttr::Unknown: return "unknown";
    case ReturnTypestateAttr::Consumed: return "consumed";
    case ReturnTypestateAttr::Unconsumed: return "unconsumed";
    }
    llvm_unreachable("No enumerator with that value");
  }


  static bool classof(const Attr *A) { return A->getKind() == attr::ReturnTypestate; }
};

class ReturnsNonNullAttr : public InheritableAttr {

public:
  static ReturnsNonNullAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    ReturnsNonNullAttr *A = new (Ctx) ReturnsNonNullAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  ReturnsNonNullAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::ReturnsNonNull, R, SI, 0, 0)
  {
  }

  ReturnsNonNullAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::ReturnsNonNull; }
};

class ReturnsTwiceAttr : public InheritableAttr {

public:
  static ReturnsTwiceAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    ReturnsTwiceAttr *A = new (Ctx) ReturnsTwiceAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  ReturnsTwiceAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::ReturnsTwice, R, SI, 0, 0)
  {
  }

  ReturnsTwiceAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::ReturnsTwice; }
};

class ScopedLockableAttr : public InheritableAttr {

public:
  static ScopedLockableAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    ScopedLockableAttr *A = new (Ctx) ScopedLockableAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  ScopedLockableAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::ScopedLockable, R, SI, 0, 0)
  {
  }

  ScopedLockableAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::ScopedLockable; }
};

class SectionAttr : public InheritableAttr {
unsigned nameLength;
char *name;


public:
  enum Spelling {
    GNU_section = 0,
    CXX11_gnu_section = 1,
    Declspec_allocate = 2
  };

  static SectionAttr *CreateImplicit(ASTContext &Ctx, Spelling S, llvm::StringRef Name, SourceRange Loc = SourceRange()) {
    SectionAttr *A = new (Ctx) SectionAttr(Loc, Ctx, Name, S);
    A->setImplicit(true);
    return A;
  }

  SectionAttr(SourceRange R, ASTContext &Ctx
              , llvm::StringRef Name
              , unsigned SI
             )
    : InheritableAttr(attr::Section, R, SI, 0, 0)
              , nameLength(Name.size()),name(new (Ctx, 1) char[nameLength])
  {
      if (!Name.empty())
        std::memcpy(name, Name.data(), nameLength);
  }

  SectionAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  Spelling getSemanticSpelling() const {
  switch (SpellingListIndex) {
    default: llvm_unreachable("Unknown spelling list index");
    case 0: return GNU_section;
    case 1: return CXX11_gnu_section;
    case 2: return Declspec_allocate;
  }
  }
  llvm::StringRef getName() const {
    return llvm::StringRef(name, nameLength);
  }
  unsigned getNameLength() const {
    return nameLength;
  }
  void setName(ASTContext &C, llvm::StringRef S) {
    nameLength = S.size();
    this->name = new (C, 1) char [nameLength];
    if (!S.empty())
      std::memcpy(this->name, S.data(), nameLength);
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::Section; }
};

class SelectAnyAttr : public InheritableAttr {

public:
  static SelectAnyAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    SelectAnyAttr *A = new (Ctx) SelectAnyAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  SelectAnyAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::SelectAny, R, SI, 0, 0)
  {
  }

  SelectAnyAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::SelectAny; }
};

class SentinelAttr : public InheritableAttr {
int sentinel;

int nullPos;


public:
  static SentinelAttr *CreateImplicit(ASTContext &Ctx, int Sentinel, int NullPos, SourceRange Loc = SourceRange()) {
    SentinelAttr *A = new (Ctx) SentinelAttr(Loc, Ctx, Sentinel, NullPos, 0);
    A->setImplicit(true);
    return A;
  }

  SentinelAttr(SourceRange R, ASTContext &Ctx
              , int Sentinel
              , int NullPos
              , unsigned SI
             )
    : InheritableAttr(attr::Sentinel, R, SI, 0, 0)
              , sentinel(Sentinel)
              , nullPos(NullPos)
  {


  }

  SentinelAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::Sentinel, R, SI, 0, 0)
              , sentinel()
              , nullPos()
  {
  }

  SentinelAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  int getSentinel() const {
    return sentinel;
  }

  static const int DefaultSentinel = 0;

  int getNullPos() const {
    return nullPos;
  }

  static const int DefaultNullPos = 0;



  static bool classof(const Attr *A) { return A->getKind() == attr::Sentinel; }
};

class SetTypestateAttr : public InheritableAttr {
public:
  enum ConsumedState {
    Unknown,
    Consumed,
    Unconsumed
  };
private:
  ConsumedState newState;


public:
  static SetTypestateAttr *CreateImplicit(ASTContext &Ctx, ConsumedState NewState, SourceRange Loc = SourceRange()) {
    SetTypestateAttr *A = new (Ctx) SetTypestateAttr(Loc, Ctx, NewState, 0);
    A->setImplicit(true);
    return A;
  }

  SetTypestateAttr(SourceRange R, ASTContext &Ctx
              , ConsumedState NewState
              , unsigned SI
             )
    : InheritableAttr(attr::SetTypestate, R, SI, 0, 0)
              , newState(NewState)
  {

  }

  SetTypestateAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  ConsumedState getNewState() const {
    return newState;
  }

  static bool ConvertStrToConsumedState(StringRef Val, ConsumedState &Out) {
    Optional<ConsumedState> R = llvm::StringSwitch<Optional<ConsumedState>>(Val)
      .Case("unknown", SetTypestateAttr::Unknown)
      .Case("consumed", SetTypestateAttr::Consumed)
      .Case("unconsumed", SetTypestateAttr::Unconsumed)
      .Default(Optional<ConsumedState>());
    if (R) {
      Out = *R;
      return true;
    }
    return false;
  }

  static const char *ConvertConsumedStateToStr(ConsumedState Val) {
    switch(Val) {
    case SetTypestateAttr::Unknown: return "unknown";
    case SetTypestateAttr::Consumed: return "consumed";
    case SetTypestateAttr::Unconsumed: return "unconsumed";
    }
    llvm_unreachable("No enumerator with that value");
  }


  static bool classof(const Attr *A) { return A->getKind() == attr::SetTypestate; }
};

class SharedTrylockFunctionAttr : public InheritableAttr {
Expr * successValue;

  unsigned args_Size;
  Expr * *args_;


public:
  static SharedTrylockFunctionAttr *CreateImplicit(ASTContext &Ctx, Expr * SuccessValue, Expr * *Args, unsigned ArgsSize, SourceRange Loc = SourceRange()) {
    SharedTrylockFunctionAttr *A = new (Ctx) SharedTrylockFunctionAttr(Loc, Ctx, SuccessValue, Args, ArgsSize, 0);
    A->setImplicit(true);
    return A;
  }

  SharedTrylockFunctionAttr(SourceRange R, ASTContext &Ctx
              , Expr * SuccessValue
              , Expr * *Args, unsigned ArgsSize
              , unsigned SI
             )
    : InheritableAttr(attr::SharedTrylockFunction, R, SI, 1, 1)
              , successValue(SuccessValue)
              , args_Size(ArgsSize), args_(new (Ctx, 16) Expr *[args_Size])
  {

    std::copy(Args, Args + args_Size, args_);
  }

  SharedTrylockFunctionAttr(SourceRange R, ASTContext &Ctx
              , Expr * SuccessValue
              , unsigned SI
             )
    : InheritableAttr(attr::SharedTrylockFunction, R, SI, 1, 1)
              , successValue()
              , args_Size(0), args_(nullptr)
  {

  }

  SharedTrylockFunctionAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  Expr * getSuccessValue() const {
    return successValue;
  }

  typedef Expr ** args_iterator;
  args_iterator args_begin() const { return args_; }
  args_iterator args_end() const { return args_ + args_Size; }
  unsigned args_size() const { return args_Size; }
  llvm::iterator_range<args_iterator> args() const { return llvm::make_range(args_begin(), args_end()); }




  static bool classof(const Attr *A) { return A->getKind() == attr::SharedTrylockFunction; }
};

class StdCallAttr : public InheritableAttr {

public:
  static StdCallAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    StdCallAttr *A = new (Ctx) StdCallAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  StdCallAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::StdCall, R, SI, 0, 0)
  {
  }

  StdCallAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::StdCall; }
};

class SysVABIAttr : public InheritableAttr {

public:
  static SysVABIAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    SysVABIAttr *A = new (Ctx) SysVABIAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  SysVABIAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::SysVABI, R, SI, 0, 0)
  {
  }

  SysVABIAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::SysVABI; }
};

class TLSModelAttr : public InheritableAttr {
unsigned modelLength;
char *model;


public:
  static TLSModelAttr *CreateImplicit(ASTContext &Ctx, llvm::StringRef Model, SourceRange Loc = SourceRange()) {
    TLSModelAttr *A = new (Ctx) TLSModelAttr(Loc, Ctx, Model, 0);
    A->setImplicit(true);
    return A;
  }

  TLSModelAttr(SourceRange R, ASTContext &Ctx
              , llvm::StringRef Model
              , unsigned SI
             )
    : InheritableAttr(attr::TLSModel, R, SI, 0, 0)
              , modelLength(Model.size()),model(new (Ctx, 1) char[modelLength])
  {
      if (!Model.empty())
        std::memcpy(model, Model.data(), modelLength);
  }

  TLSModelAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  llvm::StringRef getModel() const {
    return llvm::StringRef(model, modelLength);
  }
  unsigned getModelLength() const {
    return modelLength;
  }
  void setModel(ASTContext &C, llvm::StringRef S) {
    modelLength = S.size();
    this->model = new (C, 1) char [modelLength];
    if (!S.empty())
      std::memcpy(this->model, S.data(), modelLength);
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::TLSModel; }
};

class TargetAttr : public InheritableAttr {
unsigned featuresLength;
char *features;


public:
  static TargetAttr *CreateImplicit(ASTContext &Ctx, llvm::StringRef Features, SourceRange Loc = SourceRange()) {
    TargetAttr *A = new (Ctx) TargetAttr(Loc, Ctx, Features, 0);
    A->setImplicit(true);
    return A;
  }

  TargetAttr(SourceRange R, ASTContext &Ctx
              , llvm::StringRef Features
              , unsigned SI
             )
    : InheritableAttr(attr::Target, R, SI, 0, 0)
              , featuresLength(Features.size()),features(new (Ctx, 1) char[featuresLength])
  {
      if (!Features.empty())
        std::memcpy(features, Features.data(), featuresLength);
  }

  TargetAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  llvm::StringRef getFeatures() const {
    return llvm::StringRef(features, featuresLength);
  }
  unsigned getFeaturesLength() const {
    return featuresLength;
  }
  void setFeatures(ASTContext &C, llvm::StringRef S) {
    featuresLength = S.size();
    this->features = new (C, 1) char [featuresLength];
    if (!S.empty())
      std::memcpy(this->features, S.data(), featuresLength);
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::Target; }
};

class TestTypestateAttr : public InheritableAttr {
public:
  enum ConsumedState {
    Consumed,
    Unconsumed
  };
private:
  ConsumedState testState;


public:
  static TestTypestateAttr *CreateImplicit(ASTContext &Ctx, ConsumedState TestState, SourceRange Loc = SourceRange()) {
    TestTypestateAttr *A = new (Ctx) TestTypestateAttr(Loc, Ctx, TestState, 0);
    A->setImplicit(true);
    return A;
  }

  TestTypestateAttr(SourceRange R, ASTContext &Ctx
              , ConsumedState TestState
              , unsigned SI
             )
    : InheritableAttr(attr::TestTypestate, R, SI, 0, 0)
              , testState(TestState)
  {

  }

  TestTypestateAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  ConsumedState getTestState() const {
    return testState;
  }

  static bool ConvertStrToConsumedState(StringRef Val, ConsumedState &Out) {
    Optional<ConsumedState> R = llvm::StringSwitch<Optional<ConsumedState>>(Val)
      .Case("consumed", TestTypestateAttr::Consumed)
      .Case("unconsumed", TestTypestateAttr::Unconsumed)
      .Default(Optional<ConsumedState>());
    if (R) {
      Out = *R;
      return true;
    }
    return false;
  }

  static const char *ConvertConsumedStateToStr(ConsumedState Val) {
    switch(Val) {
    case TestTypestateAttr::Consumed: return "consumed";
    case TestTypestateAttr::Unconsumed: return "unconsumed";
    }
    llvm_unreachable("No enumerator with that value");
  }


  static bool classof(const Attr *A) { return A->getKind() == attr::TestTypestate; }
};

class ThisCallAttr : public InheritableAttr {

public:
  static ThisCallAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    ThisCallAttr *A = new (Ctx) ThisCallAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  ThisCallAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::ThisCall, R, SI, 0, 0)
  {
  }

  ThisCallAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::ThisCall; }
};

class ThreadAttr : public Attr {

public:
  static ThreadAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    ThreadAttr *A = new (Ctx) ThreadAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  ThreadAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : Attr(attr::Thread, R, SI, 0, 0)
  {
  }

  ThreadAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::Thread; }
};

class TransparentUnionAttr : public InheritableAttr {

public:
  static TransparentUnionAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    TransparentUnionAttr *A = new (Ctx) TransparentUnionAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  TransparentUnionAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::TransparentUnion, R, SI, 0, 0)
  {
  }

  TransparentUnionAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::TransparentUnion; }
};

class TryAcquireCapabilityAttr : public InheritableAttr {
Expr * successValue;

  unsigned args_Size;
  Expr * *args_;


public:
  enum Spelling {
    GNU_try_acquire_capability = 0,
    CXX11_clang_try_acquire_capability = 1,
    GNU_try_acquire_shared_capability = 2,
    CXX11_clang_try_acquire_shared_capability = 3
  };

  static TryAcquireCapabilityAttr *CreateImplicit(ASTContext &Ctx, Spelling S, Expr * SuccessValue, Expr * *Args, unsigned ArgsSize, SourceRange Loc = SourceRange()) {
    TryAcquireCapabilityAttr *A = new (Ctx) TryAcquireCapabilityAttr(Loc, Ctx, SuccessValue, Args, ArgsSize, S);
    A->setImplicit(true);
    return A;
  }

  TryAcquireCapabilityAttr(SourceRange R, ASTContext &Ctx
              , Expr * SuccessValue
              , Expr * *Args, unsigned ArgsSize
              , unsigned SI
             )
    : InheritableAttr(attr::TryAcquireCapability, R, SI, 1, 1)
              , successValue(SuccessValue)
              , args_Size(ArgsSize), args_(new (Ctx, 16) Expr *[args_Size])
  {

    std::copy(Args, Args + args_Size, args_);
  }

  TryAcquireCapabilityAttr(SourceRange R, ASTContext &Ctx
              , Expr * SuccessValue
              , unsigned SI
             )
    : InheritableAttr(attr::TryAcquireCapability, R, SI, 1, 1)
              , successValue()
              , args_Size(0), args_(nullptr)
  {

  }

  TryAcquireCapabilityAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  Spelling getSemanticSpelling() const {
  switch (SpellingListIndex) {
    default: llvm_unreachable("Unknown spelling list index");
    case 0: return GNU_try_acquire_capability;
    case 1: return CXX11_clang_try_acquire_capability;
    case 2: return GNU_try_acquire_shared_capability;
    case 3: return CXX11_clang_try_acquire_shared_capability;
  }
  }
  bool isShared() const { return SpellingListIndex == 2 ||
    SpellingListIndex == 3; }
  Expr * getSuccessValue() const {
    return successValue;
  }

  typedef Expr ** args_iterator;
  args_iterator args_begin() const { return args_; }
  args_iterator args_end() const { return args_ + args_Size; }
  unsigned args_size() const { return args_Size; }
  llvm::iterator_range<args_iterator> args() const { return llvm::make_range(args_begin(), args_end()); }




  static bool classof(const Attr *A) { return A->getKind() == attr::TryAcquireCapability; }
};

class TypeTagForDatatypeAttr : public InheritableAttr {
IdentifierInfo * argumentKind;

TypeSourceInfo * matchingCType;

bool layoutCompatible;

bool mustBeNull;


public:
  static TypeTagForDatatypeAttr *CreateImplicit(ASTContext &Ctx, IdentifierInfo * ArgumentKind, TypeSourceInfo * MatchingCType, bool LayoutCompatible, bool MustBeNull, SourceRange Loc = SourceRange()) {
    TypeTagForDatatypeAttr *A = new (Ctx) TypeTagForDatatypeAttr(Loc, Ctx, ArgumentKind, MatchingCType, LayoutCompatible, MustBeNull, 0);
    A->setImplicit(true);
    return A;
  }

  TypeTagForDatatypeAttr(SourceRange R, ASTContext &Ctx
              , IdentifierInfo * ArgumentKind
              , TypeSourceInfo * MatchingCType
              , bool LayoutCompatible
              , bool MustBeNull
              , unsigned SI
             )
    : InheritableAttr(attr::TypeTagForDatatype, R, SI, 0, 0)
              , argumentKind(ArgumentKind)
              , matchingCType(MatchingCType)
              , layoutCompatible(LayoutCompatible)
              , mustBeNull(MustBeNull)
  {




  }

  TypeTagForDatatypeAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  IdentifierInfo * getArgumentKind() const {
    return argumentKind;
  }

  QualType getMatchingCType() const {
    return matchingCType->getType();
  }  TypeSourceInfo * getMatchingCTypeLoc() const {
    return matchingCType;
  }

  bool getLayoutCompatible() const {
    return layoutCompatible;
  }

  bool getMustBeNull() const {
    return mustBeNull;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::TypeTagForDatatype; }
};

class TypeVisibilityAttr : public InheritableAttr {
public:
  enum VisibilityType {
    Default,
    Hidden,
    Protected
  };
private:
  VisibilityType visibility;


public:
  static TypeVisibilityAttr *CreateImplicit(ASTContext &Ctx, VisibilityType Visibility, SourceRange Loc = SourceRange()) {
    TypeVisibilityAttr *A = new (Ctx) TypeVisibilityAttr(Loc, Ctx, Visibility, 0);
    A->setImplicit(true);
    return A;
  }

  TypeVisibilityAttr(SourceRange R, ASTContext &Ctx
              , VisibilityType Visibility
              , unsigned SI
             )
    : InheritableAttr(attr::TypeVisibility, R, SI, 0, 0)
              , visibility(Visibility)
  {

  }

  TypeVisibilityAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  VisibilityType getVisibility() const {
    return visibility;
  }

  static bool ConvertStrToVisibilityType(StringRef Val, VisibilityType &Out) {
    Optional<VisibilityType> R = llvm::StringSwitch<Optional<VisibilityType>>(Val)
      .Case("default", TypeVisibilityAttr::Default)
      .Case("hidden", TypeVisibilityAttr::Hidden)
      .Case("internal", TypeVisibilityAttr::Hidden)
      .Case("protected", TypeVisibilityAttr::Protected)
      .Default(Optional<VisibilityType>());
    if (R) {
      Out = *R;
      return true;
    }
    return false;
  }

  static const char *ConvertVisibilityTypeToStr(VisibilityType Val) {
    switch(Val) {
    case TypeVisibilityAttr::Default: return "default";
    case TypeVisibilityAttr::Hidden: return "hidden";
    case TypeVisibilityAttr::Protected: return "protected";
    }
    llvm_unreachable("No enumerator with that value");
  }


  static bool classof(const Attr *A) { return A->getKind() == attr::TypeVisibility; }
};

class UnavailableAttr : public InheritableAttr {
unsigned messageLength;
char *message;


public:
  static UnavailableAttr *CreateImplicit(ASTContext &Ctx, llvm::StringRef Message, SourceRange Loc = SourceRange()) {
    UnavailableAttr *A = new (Ctx) UnavailableAttr(Loc, Ctx, Message, 0);
    A->setImplicit(true);
    return A;
  }

  UnavailableAttr(SourceRange R, ASTContext &Ctx
              , llvm::StringRef Message
              , unsigned SI
             )
    : InheritableAttr(attr::Unavailable, R, SI, 0, 0)
              , messageLength(Message.size()),message(new (Ctx, 1) char[messageLength])
  {
      if (!Message.empty())
        std::memcpy(message, Message.data(), messageLength);
  }

  UnavailableAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::Unavailable, R, SI, 0, 0)
              , messageLength(0),message(0)
  {
  }

  UnavailableAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  llvm::StringRef getMessage() const {
    return llvm::StringRef(message, messageLength);
  }
  unsigned getMessageLength() const {
    return messageLength;
  }
  void setMessage(ASTContext &C, llvm::StringRef S) {
    messageLength = S.size();
    this->message = new (C, 1) char [messageLength];
    if (!S.empty())
      std::memcpy(this->message, S.data(), messageLength);
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::Unavailable; }
};

class UnusedAttr : public InheritableAttr {

public:
  static UnusedAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    UnusedAttr *A = new (Ctx) UnusedAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  UnusedAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::Unused, R, SI, 0, 0)
  {
  }

  UnusedAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::Unused; }
};

class UsedAttr : public InheritableAttr {

public:
  static UsedAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    UsedAttr *A = new (Ctx) UsedAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  UsedAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::Used, R, SI, 0, 0)
  {
  }

  UsedAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::Used; }
};

class UuidAttr : public InheritableAttr {
unsigned guidLength;
char *guid;


public:
  static UuidAttr *CreateImplicit(ASTContext &Ctx, llvm::StringRef Guid, SourceRange Loc = SourceRange()) {
    UuidAttr *A = new (Ctx) UuidAttr(Loc, Ctx, Guid, 0);
    A->setImplicit(true);
    return A;
  }

  UuidAttr(SourceRange R, ASTContext &Ctx
              , llvm::StringRef Guid
              , unsigned SI
             )
    : InheritableAttr(attr::Uuid, R, SI, 0, 0)
              , guidLength(Guid.size()),guid(new (Ctx, 1) char[guidLength])
  {
      if (!Guid.empty())
        std::memcpy(guid, Guid.data(), guidLength);
  }

  UuidAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  llvm::StringRef getGuid() const {
    return llvm::StringRef(guid, guidLength);
  }
  unsigned getGuidLength() const {
    return guidLength;
  }
  void setGuid(ASTContext &C, llvm::StringRef S) {
    guidLength = S.size();
    this->guid = new (C, 1) char [guidLength];
    if (!S.empty())
      std::memcpy(this->guid, S.data(), guidLength);
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::Uuid; }
};

class VKBindingAttr : public InheritableAttr {
int binding;

int set;


public:
  static VKBindingAttr *CreateImplicit(ASTContext &Ctx, int Binding, int Set, SourceRange Loc = SourceRange()) {
    VKBindingAttr *A = new (Ctx) VKBindingAttr(Loc, Ctx, Binding, Set, 0);
    A->setImplicit(true);
    return A;
  }

  VKBindingAttr(SourceRange R, ASTContext &Ctx
              , int Binding
              , int Set
              , unsigned SI
             )
    : InheritableAttr(attr::VKBinding, R, SI, 0, 0)
              , binding(Binding)
              , set(Set)
  {


  }

  VKBindingAttr(SourceRange R, ASTContext &Ctx
              , int Binding
              , unsigned SI
             )
    : InheritableAttr(attr::VKBinding, R, SI, 0, 0)
              , binding()
              , set()
  {

  }

  VKBindingAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  int getBinding() const {
    return binding;
  }

  int getSet() const {
    return set;
  }

  static const int DefaultSet = 0;



  static bool classof(const Attr *A) { return A->getKind() == attr::VKBinding; }
};

class VKBuiltInAttr : public InheritableAttr {
unsigned builtInLength;
char *builtIn;


public:
  static VKBuiltInAttr *CreateImplicit(ASTContext &Ctx, llvm::StringRef BuiltIn, SourceRange Loc = SourceRange()) {
    VKBuiltInAttr *A = new (Ctx) VKBuiltInAttr(Loc, Ctx, BuiltIn, 0);
    A->setImplicit(true);
    return A;
  }

  VKBuiltInAttr(SourceRange R, ASTContext &Ctx
              , llvm::StringRef BuiltIn
              , unsigned SI
             )
    : InheritableAttr(attr::VKBuiltIn, R, SI, 0, 0)
              , builtInLength(BuiltIn.size()),builtIn(new (Ctx, 1) char[builtInLength])
  {
      if (!BuiltIn.empty())
        std::memcpy(builtIn, BuiltIn.data(), builtInLength);
  }

  VKBuiltInAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  llvm::StringRef getBuiltIn() const {
    return llvm::StringRef(builtIn, builtInLength);
  }
  unsigned getBuiltInLength() const {
    return builtInLength;
  }
  void setBuiltIn(ASTContext &C, llvm::StringRef S) {
    builtInLength = S.size();
    this->builtIn = new (C, 1) char [builtInLength];
    if (!S.empty())
      std::memcpy(this->builtIn, S.data(), builtInLength);
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::VKBuiltIn; }
};

class VKCapabilityExtAttr : public InheritableAttr {
int capability;


public:
  static VKCapabilityExtAttr *CreateImplicit(ASTContext &Ctx, int Capability, SourceRange Loc = SourceRange()) {
    VKCapabilityExtAttr *A = new (Ctx) VKCapabilityExtAttr(Loc, Ctx, Capability, 0);
    A->setImplicit(true);
    return A;
  }

  VKCapabilityExtAttr(SourceRange R, ASTContext &Ctx
              , int Capability
              , unsigned SI
             )
    : InheritableAttr(attr::VKCapabilityExt, R, SI, 0, 0)
              , capability(Capability)
  {

  }

  VKCapabilityExtAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  int getCapability() const {
    return capability;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::VKCapabilityExt; }
};

class VKCombinedImageSamplerAttr : public InheritableAttr {

public:
  static VKCombinedImageSamplerAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    VKCombinedImageSamplerAttr *A = new (Ctx) VKCombinedImageSamplerAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  VKCombinedImageSamplerAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::VKCombinedImageSampler, R, SI, 0, 0)
  {
  }

  VKCombinedImageSamplerAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::VKCombinedImageSampler; }
};

class VKConstantIdAttr : public InheritableAttr {
int specConstId;


public:
  static VKConstantIdAttr *CreateImplicit(ASTContext &Ctx, int SpecConstId, SourceRange Loc = SourceRange()) {
    VKConstantIdAttr *A = new (Ctx) VKConstantIdAttr(Loc, Ctx, SpecConstId, 0);
    A->setImplicit(true);
    return A;
  }

  VKConstantIdAttr(SourceRange R, ASTContext &Ctx
              , int SpecConstId
              , unsigned SI
             )
    : InheritableAttr(attr::VKConstantId, R, SI, 0, 0)
              , specConstId(SpecConstId)
  {

  }

  VKConstantIdAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  int getSpecConstId() const {
    return specConstId;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::VKConstantId; }
};

class VKCounterBindingAttr : public InheritableAttr {
int binding;


public:
  static VKCounterBindingAttr *CreateImplicit(ASTContext &Ctx, int Binding, SourceRange Loc = SourceRange()) {
    VKCounterBindingAttr *A = new (Ctx) VKCounterBindingAttr(Loc, Ctx, Binding, 0);
    A->setImplicit(true);
    return A;
  }

  VKCounterBindingAttr(SourceRange R, ASTContext &Ctx
              , int Binding
              , unsigned SI
             )
    : InheritableAttr(attr::VKCounterBinding, R, SI, 0, 0)
              , binding(Binding)
  {

  }

  VKCounterBindingAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  int getBinding() const {
    return binding;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::VKCounterBinding; }
};

class VKDecorateExtAttr : public InheritableAttr {
unsigned decorate;

  unsigned literals_Size;
  unsigned *literals_;


public:
  static VKDecorateExtAttr *CreateImplicit(ASTContext &Ctx, unsigned Decorate, unsigned *Literals, unsigned LiteralsSize, SourceRange Loc = SourceRange()) {
    VKDecorateExtAttr *A = new (Ctx) VKDecorateExtAttr(Loc, Ctx, Decorate, Literals, LiteralsSize, 0);
    A->setImplicit(true);
    return A;
  }

  VKDecorateExtAttr(SourceRange R, ASTContext &Ctx
              , unsigned Decorate
              , unsigned *Literals, unsigned LiteralsSize
              , unsigned SI
             )
    : InheritableAttr(attr::VKDecorateExt, R, SI, 0, 0)
              , decorate(Decorate)
              , literals_Size(LiteralsSize), literals_(new (Ctx, 16) unsigned[literals_Size])
  {

    std::copy(Literals, Literals + literals_Size, literals_);
  }

  VKDecorateExtAttr(SourceRange R, ASTContext &Ctx
              , unsigned Decorate
              , unsigned SI
             )
    : InheritableAttr(attr::VKDecorateExt, R, SI, 0, 0)
              , decorate()
              , literals_Size(0), literals_(nullptr)
  {

  }

  VKDecorateExtAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  unsigned getDecorate() const {
    return decorate;
  }

  typedef unsigned* literals_iterator;
  literals_iterator literals_begin() const { return literals_; }
  literals_iterator literals_end() const { return literals_ + literals_Size; }
  unsigned literals_size() const { return literals_Size; }
  llvm::iterator_range<literals_iterator> literals() const { return llvm::make_range(literals_begin(), literals_end()); }




  static bool classof(const Attr *A) { return A->getKind() == attr::VKDecorateExt; }
};

class VKDecorateIdExtAttr : public InheritableAttr {
unsigned decorate;

  unsigned arguments_Size;
  Expr * *arguments_;


public:
  static VKDecorateIdExtAttr *CreateImplicit(ASTContext &Ctx, unsigned Decorate, Expr * *Arguments, unsigned ArgumentsSize, SourceRange Loc = SourceRange()) {
    VKDecorateIdExtAttr *A = new (Ctx) VKDecorateIdExtAttr(Loc, Ctx, Decorate, Arguments, ArgumentsSize, 0);
    A->setImplicit(true);
    return A;
  }

  VKDecorateIdExtAttr(SourceRange R, ASTContext &Ctx
              , unsigned Decorate
              , Expr * *Arguments, unsigned ArgumentsSize
              , unsigned SI
             )
    : InheritableAttr(attr::VKDecorateIdExt, R, SI, 0, 0)
              , decorate(Decorate)
              , arguments_Size(ArgumentsSize), arguments_(new (Ctx, 16) Expr *[arguments_Size])
  {

    std::copy(Arguments, Arguments + arguments_Size, arguments_);
  }

  VKDecorateIdExtAttr(SourceRange R, ASTContext &Ctx
              , unsigned Decorate
              , unsigned SI
             )
    : InheritableAttr(attr::VKDecorateIdExt, R, SI, 0, 0)
              , decorate()
              , arguments_Size(0), arguments_(nullptr)
  {

  }

  VKDecorateIdExtAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  unsigned getDecorate() const {
    return decorate;
  }

  typedef Expr ** arguments_iterator;
  arguments_iterator arguments_begin() const { return arguments_; }
  arguments_iterator arguments_end() const { return arguments_ + arguments_Size; }
  unsigned arguments_size() const { return arguments_Size; }
  llvm::iterator_range<arguments_iterator> arguments() const { return llvm::make_range(arguments_begin(), arguments_end()); }




  static bool classof(const Attr *A) { return A->getKind() == attr::VKDecorateIdExt; }
};

class VKDecorateStringExtAttr : public InheritableAttr {
unsigned decorate;

  unsigned arguments_Size;
  std::string *arguments_;


public:
  static VKDecorateStringExtAttr *CreateImplicit(ASTContext &Ctx, unsigned Decorate, std::string *Arguments, unsigned ArgumentsSize, SourceRange Loc = SourceRange()) {
    VKDecorateStringExtAttr *A = new (Ctx) VKDecorateStringExtAttr(Loc, Ctx, Decorate, Arguments, ArgumentsSize, 0);
    A->setImplicit(true);
    return A;
  }

  VKDecorateStringExtAttr(SourceRange R, ASTContext &Ctx
              , unsigned Decorate
              , std::string *Arguments, unsigned ArgumentsSize
              , unsigned SI
             )
    : InheritableAttr(attr::VKDecorateStringExt, R, SI, 0, 0)
              , decorate(Decorate)
              , arguments_Size(ArgumentsSize), arguments_(new (Ctx, 16) std::string[arguments_Size])
  {

    std::copy(Arguments, Arguments + arguments_Size, arguments_);
  }

  VKDecorateStringExtAttr(SourceRange R, ASTContext &Ctx
              , unsigned Decorate
              , unsigned SI
             )
    : InheritableAttr(attr::VKDecorateStringExt, R, SI, 0, 0)
              , decorate()
              , arguments_Size(0), arguments_(nullptr)
  {

  }

  VKDecorateStringExtAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  unsigned getDecorate() const {
    return decorate;
  }

  typedef std::string* arguments_iterator;
  arguments_iterator arguments_begin() const { return arguments_; }
  arguments_iterator arguments_end() const { return arguments_ + arguments_Size; }
  unsigned arguments_size() const { return arguments_Size; }
  llvm::iterator_range<arguments_iterator> arguments() const { return llvm::make_range(arguments_begin(), arguments_end()); }




  static bool classof(const Attr *A) { return A->getKind() == attr::VKDecorateStringExt; }
};

class VKDepthUnchangedAttr : public InheritableAttr {

public:
  static VKDepthUnchangedAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    VKDepthUnchangedAttr *A = new (Ctx) VKDepthUnchangedAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  VKDepthUnchangedAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::VKDepthUnchanged, R, SI, 0, 0)
  {
  }

  VKDepthUnchangedAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::VKDepthUnchanged; }
};

class VKEarlyAndLateTestsAttr : public InheritableAttr {

public:
  static VKEarlyAndLateTestsAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    VKEarlyAndLateTestsAttr *A = new (Ctx) VKEarlyAndLateTestsAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  VKEarlyAndLateTestsAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::VKEarlyAndLateTests, R, SI, 0, 0)
  {
  }

  VKEarlyAndLateTestsAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::VKEarlyAndLateTests; }
};

class VKExtensionExtAttr : public InheritableAttr {
unsigned nameLength;
char *name;


public:
  static VKExtensionExtAttr *CreateImplicit(ASTContext &Ctx, llvm::StringRef Name, SourceRange Loc = SourceRange()) {
    VKExtensionExtAttr *A = new (Ctx) VKExtensionExtAttr(Loc, Ctx, Name, 0);
    A->setImplicit(true);
    return A;
  }

  VKExtensionExtAttr(SourceRange R, ASTContext &Ctx
              , llvm::StringRef Name
              , unsigned SI
             )
    : InheritableAttr(attr::VKExtensionExt, R, SI, 0, 0)
              , nameLength(Name.size()),name(new (Ctx, 1) char[nameLength])
  {
      if (!Name.empty())
        std::memcpy(name, Name.data(), nameLength);
  }

  VKExtensionExtAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  llvm::StringRef getName() const {
    return llvm::StringRef(name, nameLength);
  }
  unsigned getNameLength() const {
    return nameLength;
  }
  void setName(ASTContext &C, llvm::StringRef S) {
    nameLength = S.size();
    this->name = new (C, 1) char [nameLength];
    if (!S.empty())
      std::memcpy(this->name, S.data(), nameLength);
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::VKExtensionExt; }
};

class VKImageFormatAttr : public InheritableAttr {
public:
  enum ImageFormatType {
    unknown,
    rgba32f,
    rgba16f,
    r32f,
    rgba8,
    rgba8snorm,
    rg32f,
    rg16f,
    r11g11b10f,
    r16f,
    rgba16,
    rgb10a2,
    rg16,
    rg8,
    r16,
    r8,
    rgba16snorm,
    rg16snorm,
    rg8snorm,
    r16snorm,
    r8snorm,
    rgba32i,
    rgba16i,
    rgba8i,
    r32i,
    rg32i,
    rg16i,
    rg8i,
    r16i,
    r8i,
    rgba32ui,
    rgba16ui,
    rgba8ui,
    r32ui,
    rgb10a2ui,
    rg32ui,
    rg16ui,
    rg8ui,
    r16ui,
    r8ui,
    r64ui,
    r64i
  };
private:
  ImageFormatType imageFormat;


public:
  static VKImageFormatAttr *CreateImplicit(ASTContext &Ctx, ImageFormatType ImageFormat, SourceRange Loc = SourceRange()) {
    VKImageFormatAttr *A = new (Ctx) VKImageFormatAttr(Loc, Ctx, ImageFormat, 0);
    A->setImplicit(true);
    return A;
  }

  VKImageFormatAttr(SourceRange R, ASTContext &Ctx
              , ImageFormatType ImageFormat
              , unsigned SI
             )
    : InheritableAttr(attr::VKImageFormat, R, SI, 0, 0)
              , imageFormat(ImageFormat)
  {

  }

  VKImageFormatAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  ImageFormatType getImageFormat() const {
    return imageFormat;
  }

  static bool ConvertStrToImageFormatType(StringRef Val, ImageFormatType &Out) {
    Optional<ImageFormatType> R = llvm::StringSwitch<Optional<ImageFormatType>>(Val)
      .Case("unknown", VKImageFormatAttr::unknown)
      .Case("rgba32f", VKImageFormatAttr::rgba32f)
      .Case("rgba16f", VKImageFormatAttr::rgba16f)
      .Case("r32f", VKImageFormatAttr::r32f)
      .Case("rgba8", VKImageFormatAttr::rgba8)
      .Case("rgba8snorm", VKImageFormatAttr::rgba8snorm)
      .Case("rg32f", VKImageFormatAttr::rg32f)
      .Case("rg16f", VKImageFormatAttr::rg16f)
      .Case("r11g11b10f", VKImageFormatAttr::r11g11b10f)
      .Case("r16f", VKImageFormatAttr::r16f)
      .Case("rgba16", VKImageFormatAttr::rgba16)
      .Case("rgb10a2", VKImageFormatAttr::rgb10a2)
      .Case("rg16", VKImageFormatAttr::rg16)
      .Case("rg8", VKImageFormatAttr::rg8)
      .Case("r16", VKImageFormatAttr::r16)
      .Case("r8", VKImageFormatAttr::r8)
      .Case("rgba16snorm", VKImageFormatAttr::rgba16snorm)
      .Case("rg16snorm", VKImageFormatAttr::rg16snorm)
      .Case("rg8snorm", VKImageFormatAttr::rg8snorm)
      .Case("r16snorm", VKImageFormatAttr::r16snorm)
      .Case("r8snorm", VKImageFormatAttr::r8snorm)
      .Case("rgba32i", VKImageFormatAttr::rgba32i)
      .Case("rgba16i", VKImageFormatAttr::rgba16i)
      .Case("rgba8i", VKImageFormatAttr::rgba8i)
      .Case("r32i", VKImageFormatAttr::r32i)
      .Case("rg32i", VKImageFormatAttr::rg32i)
      .Case("rg16i", VKImageFormatAttr::rg16i)
      .Case("rg8i", VKImageFormatAttr::rg8i)
      .Case("r16i", VKImageFormatAttr::r16i)
      .Case("r8i", VKImageFormatAttr::r8i)
      .Case("rgba32ui", VKImageFormatAttr::rgba32ui)
      .Case("rgba16ui", VKImageFormatAttr::rgba16ui)
      .Case("rgba8ui", VKImageFormatAttr::rgba8ui)
      .Case("r32ui", VKImageFormatAttr::r32ui)
      .Case("rgb10a2ui", VKImageFormatAttr::rgb10a2ui)
      .Case("rg32ui", VKImageFormatAttr::rg32ui)
      .Case("rg16ui", VKImageFormatAttr::rg16ui)
      .Case("rg8ui", VKImageFormatAttr::rg8ui)
      .Case("r16ui", VKImageFormatAttr::r16ui)
      .Case("r8ui", VKImageFormatAttr::r8ui)
      .Case("r64ui", VKImageFormatAttr::r64ui)
      .Case("r64i", VKImageFormatAttr::r64i)
      .Default(Optional<ImageFormatType>());
    if (R) {
      Out = *R;
      return true;
    }
    return false;
  }

  static const char *ConvertImageFormatTypeToStr(ImageFormatType Val) {
    switch(Val) {
    case VKImageFormatAttr::unknown: return "unknown";
    case VKImageFormatAttr::rgba32f: return "rgba32f";
    case VKImageFormatAttr::rgba16f: return "rgba16f";
    case VKImageFormatAttr::r32f: return "r32f";
    case VKImageFormatAttr::rgba8: return "rgba8";
    case VKImageFormatAttr::rgba8snorm: return "rgba8snorm";
    case VKImageFormatAttr::rg32f: return "rg32f";
    case VKImageFormatAttr::rg16f: return "rg16f";
    case VKImageFormatAttr::r11g11b10f: return "r11g11b10f";
    case VKImageFormatAttr::r16f: return "r16f";
    case VKImageFormatAttr::rgba16: return "rgba16";
    case VKImageFormatAttr::rgb10a2: return "rgb10a2";
    case VKImageFormatAttr::rg16: return "rg16";
    case VKImageFormatAttr::rg8: return "rg8";
    case VKImageFormatAttr::r16: return "r16";
    case VKImageFormatAttr::r8: return "r8";
    case VKImageFormatAttr::rgba16snorm: return "rgba16snorm";
    case VKImageFormatAttr::rg16snorm: return "rg16snorm";
    case VKImageFormatAttr::rg8snorm: return "rg8snorm";
    case VKImageFormatAttr::r16snorm: return "r16snorm";
    case VKImageFormatAttr::r8snorm: return "r8snorm";
    case VKImageFormatAttr::rgba32i: return "rgba32i";
    case VKImageFormatAttr::rgba16i: return "rgba16i";
    case VKImageFormatAttr::rgba8i: return "rgba8i";
    case VKImageFormatAttr::r32i: return "r32i";
    case VKImageFormatAttr::rg32i: return "rg32i";
    case VKImageFormatAttr::rg16i: return "rg16i";
    case VKImageFormatAttr::rg8i: return "rg8i";
    case VKImageFormatAttr::r16i: return "r16i";
    case VKImageFormatAttr::r8i: return "r8i";
    case VKImageFormatAttr::rgba32ui: return "rgba32ui";
    case VKImageFormatAttr::rgba16ui: return "rgba16ui";
    case VKImageFormatAttr::rgba8ui: return "rgba8ui";
    case VKImageFormatAttr::r32ui: return "r32ui";
    case VKImageFormatAttr::rgb10a2ui: return "rgb10a2ui";
    case VKImageFormatAttr::rg32ui: return "rg32ui";
    case VKImageFormatAttr::rg16ui: return "rg16ui";
    case VKImageFormatAttr::rg8ui: return "rg8ui";
    case VKImageFormatAttr::r16ui: return "r16ui";
    case VKImageFormatAttr::r8ui: return "r8ui";
    case VKImageFormatAttr::r64ui: return "r64ui";
    case VKImageFormatAttr::r64i: return "r64i";
    }
    llvm_unreachable("No enumerator with that value");
  }


  static bool classof(const Attr *A) { return A->getKind() == attr::VKImageFormat; }
};

class VKIndexAttr : public InheritableAttr {
int number;


public:
  static VKIndexAttr *CreateImplicit(ASTContext &Ctx, int Number, SourceRange Loc = SourceRange()) {
    VKIndexAttr *A = new (Ctx) VKIndexAttr(Loc, Ctx, Number, 0);
    A->setImplicit(true);
    return A;
  }

  VKIndexAttr(SourceRange R, ASTContext &Ctx
              , int Number
              , unsigned SI
             )
    : InheritableAttr(attr::VKIndex, R, SI, 0, 0)
              , number(Number)
  {

  }

  VKIndexAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  int getNumber() const {
    return number;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::VKIndex; }
};

class VKInputAttachmentIndexAttr : public InheritableAttr {
int index;


public:
  static VKInputAttachmentIndexAttr *CreateImplicit(ASTContext &Ctx, int Index, SourceRange Loc = SourceRange()) {
    VKInputAttachmentIndexAttr *A = new (Ctx) VKInputAttachmentIndexAttr(Loc, Ctx, Index, 0);
    A->setImplicit(true);
    return A;
  }

  VKInputAttachmentIndexAttr(SourceRange R, ASTContext &Ctx
              , int Index
              , unsigned SI
             )
    : InheritableAttr(attr::VKInputAttachmentIndex, R, SI, 0, 0)
              , index(Index)
  {

  }

  VKInputAttachmentIndexAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  int getIndex() const {
    return index;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::VKInputAttachmentIndex; }
};

class VKInstructionExtAttr : public InheritableAttr {
int opcode;

unsigned instruction_setLength;
char *instruction_set;


public:
  static VKInstructionExtAttr *CreateImplicit(ASTContext &Ctx, int Opcode, llvm::StringRef Instruction_set, SourceRange Loc = SourceRange()) {
    VKInstructionExtAttr *A = new (Ctx) VKInstructionExtAttr(Loc, Ctx, Opcode, Instruction_set, 0);
    A->setImplicit(true);
    return A;
  }

  VKInstructionExtAttr(SourceRange R, ASTContext &Ctx
              , int Opcode
              , llvm::StringRef Instruction_set
              , unsigned SI
             )
    : InheritableAttr(attr::VKInstructionExt, R, SI, 0, 0)
              , opcode(Opcode)
              , instruction_setLength(Instruction_set.size()),instruction_set(new (Ctx, 1) char[instruction_setLength])
  {

      if (!Instruction_set.empty())
        std::memcpy(instruction_set, Instruction_set.data(), instruction_setLength);
  }

  VKInstructionExtAttr(SourceRange R, ASTContext &Ctx
              , int Opcode
              , unsigned SI
             )
    : InheritableAttr(attr::VKInstructionExt, R, SI, 0, 0)
              , opcode()
              , instruction_setLength(0),instruction_set(0)
  {

  }

  VKInstructionExtAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  int getOpcode() const {
    return opcode;
  }

  llvm::StringRef getInstruction_set() const {
    return llvm::StringRef(instruction_set, instruction_setLength);
  }
  unsigned getInstruction_setLength() const {
    return instruction_setLength;
  }
  void setInstruction_set(ASTContext &C, llvm::StringRef S) {
    instruction_setLength = S.size();
    this->instruction_set = new (C, 1) char [instruction_setLength];
    if (!S.empty())
      std::memcpy(this->instruction_set, S.data(), instruction_setLength);
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::VKInstructionExt; }
};

class VKLiteralExtAttr : public InheritableAttr {

public:
  static VKLiteralExtAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    VKLiteralExtAttr *A = new (Ctx) VKLiteralExtAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  VKLiteralExtAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::VKLiteralExt, R, SI, 0, 0)
  {
  }

  VKLiteralExtAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::VKLiteralExt; }
};

class VKLocationAttr : public InheritableAttr {
int number;


public:
  static VKLocationAttr *CreateImplicit(ASTContext &Ctx, int Number, SourceRange Loc = SourceRange()) {
    VKLocationAttr *A = new (Ctx) VKLocationAttr(Loc, Ctx, Number, 0);
    A->setImplicit(true);
    return A;
  }

  VKLocationAttr(SourceRange R, ASTContext &Ctx
              , int Number
              , unsigned SI
             )
    : InheritableAttr(attr::VKLocation, R, SI, 0, 0)
              , number(Number)
  {

  }

  VKLocationAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  int getNumber() const {
    return number;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::VKLocation; }
};

class VKOffsetAttr : public InheritableAttr {
int offset;


public:
  static VKOffsetAttr *CreateImplicit(ASTContext &Ctx, int Offset, SourceRange Loc = SourceRange()) {
    VKOffsetAttr *A = new (Ctx) VKOffsetAttr(Loc, Ctx, Offset, 0);
    A->setImplicit(true);
    return A;
  }

  VKOffsetAttr(SourceRange R, ASTContext &Ctx
              , int Offset
              , unsigned SI
             )
    : InheritableAttr(attr::VKOffset, R, SI, 0, 0)
              , offset(Offset)
  {

  }

  VKOffsetAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  int getOffset() const {
    return offset;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::VKOffset; }
};

class VKPostDepthCoverageAttr : public InheritableAttr {

public:
  static VKPostDepthCoverageAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    VKPostDepthCoverageAttr *A = new (Ctx) VKPostDepthCoverageAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  VKPostDepthCoverageAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::VKPostDepthCoverage, R, SI, 0, 0)
  {
  }

  VKPostDepthCoverageAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::VKPostDepthCoverage; }
};

class VKPushConstantAttr : public InheritableAttr {

public:
  static VKPushConstantAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    VKPushConstantAttr *A = new (Ctx) VKPushConstantAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  VKPushConstantAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::VKPushConstant, R, SI, 0, 0)
  {
  }

  VKPushConstantAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::VKPushConstant; }
};

class VKReferenceExtAttr : public InheritableAttr {

public:
  static VKReferenceExtAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    VKReferenceExtAttr *A = new (Ctx) VKReferenceExtAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  VKReferenceExtAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::VKReferenceExt, R, SI, 0, 0)
  {
  }

  VKReferenceExtAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::VKReferenceExt; }
};

class VKShaderRecordEXTAttr : public InheritableAttr {

public:
  static VKShaderRecordEXTAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    VKShaderRecordEXTAttr *A = new (Ctx) VKShaderRecordEXTAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  VKShaderRecordEXTAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::VKShaderRecordEXT, R, SI, 0, 0)
  {
  }

  VKShaderRecordEXTAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::VKShaderRecordEXT; }
};

class VKShaderRecordNVAttr : public InheritableAttr {

public:
  static VKShaderRecordNVAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    VKShaderRecordNVAttr *A = new (Ctx) VKShaderRecordNVAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  VKShaderRecordNVAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::VKShaderRecordNV, R, SI, 0, 0)
  {
  }

  VKShaderRecordNVAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::VKShaderRecordNV; }
};

class VKSpvExecutionModeAttr : public InheritableAttr {
unsigned executionMode;


public:
  static VKSpvExecutionModeAttr *CreateImplicit(ASTContext &Ctx, unsigned ExecutionMode, SourceRange Loc = SourceRange()) {
    VKSpvExecutionModeAttr *A = new (Ctx) VKSpvExecutionModeAttr(Loc, Ctx, ExecutionMode, 0);
    A->setImplicit(true);
    return A;
  }

  VKSpvExecutionModeAttr(SourceRange R, ASTContext &Ctx
              , unsigned ExecutionMode
              , unsigned SI
             )
    : InheritableAttr(attr::VKSpvExecutionMode, R, SI, 0, 0)
              , executionMode(ExecutionMode)
  {

  }

  VKSpvExecutionModeAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  unsigned getExecutionMode() const {
    return executionMode;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::VKSpvExecutionMode; }
};

class VKStencilRefGreaterEqualBackAttr : public InheritableAttr {

public:
  static VKStencilRefGreaterEqualBackAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    VKStencilRefGreaterEqualBackAttr *A = new (Ctx) VKStencilRefGreaterEqualBackAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  VKStencilRefGreaterEqualBackAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::VKStencilRefGreaterEqualBack, R, SI, 0, 0)
  {
  }

  VKStencilRefGreaterEqualBackAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::VKStencilRefGreaterEqualBack; }
};

class VKStencilRefGreaterEqualFrontAttr : public InheritableAttr {

public:
  static VKStencilRefGreaterEqualFrontAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    VKStencilRefGreaterEqualFrontAttr *A = new (Ctx) VKStencilRefGreaterEqualFrontAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  VKStencilRefGreaterEqualFrontAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::VKStencilRefGreaterEqualFront, R, SI, 0, 0)
  {
  }

  VKStencilRefGreaterEqualFrontAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::VKStencilRefGreaterEqualFront; }
};

class VKStencilRefLessEqualBackAttr : public InheritableAttr {

public:
  static VKStencilRefLessEqualBackAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    VKStencilRefLessEqualBackAttr *A = new (Ctx) VKStencilRefLessEqualBackAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  VKStencilRefLessEqualBackAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::VKStencilRefLessEqualBack, R, SI, 0, 0)
  {
  }

  VKStencilRefLessEqualBackAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::VKStencilRefLessEqualBack; }
};

class VKStencilRefLessEqualFrontAttr : public InheritableAttr {

public:
  static VKStencilRefLessEqualFrontAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    VKStencilRefLessEqualFrontAttr *A = new (Ctx) VKStencilRefLessEqualFrontAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  VKStencilRefLessEqualFrontAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::VKStencilRefLessEqualFront, R, SI, 0, 0)
  {
  }

  VKStencilRefLessEqualFrontAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::VKStencilRefLessEqualFront; }
};

class VKStencilRefUnchangedBackAttr : public InheritableAttr {

public:
  static VKStencilRefUnchangedBackAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    VKStencilRefUnchangedBackAttr *A = new (Ctx) VKStencilRefUnchangedBackAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  VKStencilRefUnchangedBackAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::VKStencilRefUnchangedBack, R, SI, 0, 0)
  {
  }

  VKStencilRefUnchangedBackAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::VKStencilRefUnchangedBack; }
};

class VKStencilRefUnchangedFrontAttr : public InheritableAttr {

public:
  static VKStencilRefUnchangedFrontAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    VKStencilRefUnchangedFrontAttr *A = new (Ctx) VKStencilRefUnchangedFrontAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  VKStencilRefUnchangedFrontAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::VKStencilRefUnchangedFront, R, SI, 0, 0)
  {
  }

  VKStencilRefUnchangedFrontAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::VKStencilRefUnchangedFront; }
};

class VKStorageClassExtAttr : public InheritableAttr {
unsigned stclass;


public:
  static VKStorageClassExtAttr *CreateImplicit(ASTContext &Ctx, unsigned Stclass, SourceRange Loc = SourceRange()) {
    VKStorageClassExtAttr *A = new (Ctx) VKStorageClassExtAttr(Loc, Ctx, Stclass, 0);
    A->setImplicit(true);
    return A;
  }

  VKStorageClassExtAttr(SourceRange R, ASTContext &Ctx
              , unsigned Stclass
              , unsigned SI
             )
    : InheritableAttr(attr::VKStorageClassExt, R, SI, 0, 0)
              , stclass(Stclass)
  {

  }

  VKStorageClassExtAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  unsigned getStclass() const {
    return stclass;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::VKStorageClassExt; }
};

class VKTypeDefExtAttr : public InheritableAttr {
unsigned id;

unsigned opcode;


public:
  static VKTypeDefExtAttr *CreateImplicit(ASTContext &Ctx, unsigned Id, unsigned Opcode, SourceRange Loc = SourceRange()) {
    VKTypeDefExtAttr *A = new (Ctx) VKTypeDefExtAttr(Loc, Ctx, Id, Opcode, 0);
    A->setImplicit(true);
    return A;
  }

  VKTypeDefExtAttr(SourceRange R, ASTContext &Ctx
              , unsigned Id
              , unsigned Opcode
              , unsigned SI
             )
    : InheritableAttr(attr::VKTypeDefExt, R, SI, 0, 0)
              , id(Id)
              , opcode(Opcode)
  {


  }

  VKTypeDefExtAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  unsigned getId() const {
    return id;
  }

  unsigned getOpcode() const {
    return opcode;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::VKTypeDefExt; }
};

class VecReturnAttr : public InheritableAttr {

public:
  static VecReturnAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    VecReturnAttr *A = new (Ctx) VecReturnAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  VecReturnAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::VecReturn, R, SI, 0, 0)
  {
  }

  VecReturnAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::VecReturn; }
};

class VecTypeHintAttr : public InheritableAttr {
TypeSourceInfo * typeHint;


public:
  static VecTypeHintAttr *CreateImplicit(ASTContext &Ctx, TypeSourceInfo * TypeHint, SourceRange Loc = SourceRange()) {
    VecTypeHintAttr *A = new (Ctx) VecTypeHintAttr(Loc, Ctx, TypeHint, 0);
    A->setImplicit(true);
    return A;
  }

  VecTypeHintAttr(SourceRange R, ASTContext &Ctx
              , TypeSourceInfo * TypeHint
              , unsigned SI
             )
    : InheritableAttr(attr::VecTypeHint, R, SI, 0, 0)
              , typeHint(TypeHint)
  {

  }

  VecTypeHintAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  QualType getTypeHint() const {
    return typeHint->getType();
  }  TypeSourceInfo * getTypeHintLoc() const {
    return typeHint;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::VecTypeHint; }
};

class VectorCallAttr : public InheritableAttr {

public:
  static VectorCallAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    VectorCallAttr *A = new (Ctx) VectorCallAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  VectorCallAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::VectorCall, R, SI, 0, 0)
  {
  }

  VectorCallAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::VectorCall; }
};

class VisibilityAttr : public InheritableAttr {
public:
  enum VisibilityType {
    Default,
    Hidden,
    Protected
  };
private:
  VisibilityType visibility;


public:
  static VisibilityAttr *CreateImplicit(ASTContext &Ctx, VisibilityType Visibility, SourceRange Loc = SourceRange()) {
    VisibilityAttr *A = new (Ctx) VisibilityAttr(Loc, Ctx, Visibility, 0);
    A->setImplicit(true);
    return A;
  }

  VisibilityAttr(SourceRange R, ASTContext &Ctx
              , VisibilityType Visibility
              , unsigned SI
             )
    : InheritableAttr(attr::Visibility, R, SI, 0, 0)
              , visibility(Visibility)
  {

  }

  VisibilityAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  VisibilityType getVisibility() const {
    return visibility;
  }

  static bool ConvertStrToVisibilityType(StringRef Val, VisibilityType &Out) {
    Optional<VisibilityType> R = llvm::StringSwitch<Optional<VisibilityType>>(Val)
      .Case("default", VisibilityAttr::Default)
      .Case("hidden", VisibilityAttr::Hidden)
      .Case("internal", VisibilityAttr::Hidden)
      .Case("protected", VisibilityAttr::Protected)
      .Default(Optional<VisibilityType>());
    if (R) {
      Out = *R;
      return true;
    }
    return false;
  }

  static const char *ConvertVisibilityTypeToStr(VisibilityType Val) {
    switch(Val) {
    case VisibilityAttr::Default: return "default";
    case VisibilityAttr::Hidden: return "hidden";
    case VisibilityAttr::Protected: return "protected";
    }
    llvm_unreachable("No enumerator with that value");
  }


  static bool classof(const Attr *A) { return A->getKind() == attr::Visibility; }
};

class WarnUnusedAttr : public InheritableAttr {

public:
  static WarnUnusedAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    WarnUnusedAttr *A = new (Ctx) WarnUnusedAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  WarnUnusedAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::WarnUnused, R, SI, 0, 0)
  {
  }

  WarnUnusedAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::WarnUnused; }
};

class WarnUnusedResultAttr : public InheritableAttr {

public:
  static WarnUnusedResultAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    WarnUnusedResultAttr *A = new (Ctx) WarnUnusedResultAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  WarnUnusedResultAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::WarnUnusedResult, R, SI, 0, 0)
  {
  }

  WarnUnusedResultAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::WarnUnusedResult; }
};

class WeakAttr : public InheritableAttr {

public:
  static WeakAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    WeakAttr *A = new (Ctx) WeakAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  WeakAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::Weak, R, SI, 0, 0)
  {
  }

  WeakAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::Weak; }
};

class WeakImportAttr : public InheritableAttr {

public:
  static WeakImportAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    WeakImportAttr *A = new (Ctx) WeakImportAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  WeakImportAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::WeakImport, R, SI, 0, 0)
  {
  }

  WeakImportAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::WeakImport; }
};

class WeakRefAttr : public InheritableAttr {
unsigned aliaseeLength;
char *aliasee;


public:
  static WeakRefAttr *CreateImplicit(ASTContext &Ctx, llvm::StringRef Aliasee, SourceRange Loc = SourceRange()) {
    WeakRefAttr *A = new (Ctx) WeakRefAttr(Loc, Ctx, Aliasee, 0);
    A->setImplicit(true);
    return A;
  }

  WeakRefAttr(SourceRange R, ASTContext &Ctx
              , llvm::StringRef Aliasee
              , unsigned SI
             )
    : InheritableAttr(attr::WeakRef, R, SI, 0, 0)
              , aliaseeLength(Aliasee.size()),aliasee(new (Ctx, 1) char[aliaseeLength])
  {
      if (!Aliasee.empty())
        std::memcpy(aliasee, Aliasee.data(), aliaseeLength);
  }

  WeakRefAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::WeakRef, R, SI, 0, 0)
              , aliaseeLength(0),aliasee(0)
  {
  }

  WeakRefAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  llvm::StringRef getAliasee() const {
    return llvm::StringRef(aliasee, aliaseeLength);
  }
  unsigned getAliaseeLength() const {
    return aliaseeLength;
  }
  void setAliasee(ASTContext &C, llvm::StringRef S) {
    aliaseeLength = S.size();
    this->aliasee = new (C, 1) char [aliaseeLength];
    if (!S.empty())
      std::memcpy(this->aliasee, S.data(), aliaseeLength);
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::WeakRef; }
};

class WorkGroupSizeHintAttr : public InheritableAttr {
unsigned xDim;

unsigned yDim;

unsigned zDim;


public:
  static WorkGroupSizeHintAttr *CreateImplicit(ASTContext &Ctx, unsigned XDim, unsigned YDim, unsigned ZDim, SourceRange Loc = SourceRange()) {
    WorkGroupSizeHintAttr *A = new (Ctx) WorkGroupSizeHintAttr(Loc, Ctx, XDim, YDim, ZDim, 0);
    A->setImplicit(true);
    return A;
  }

  WorkGroupSizeHintAttr(SourceRange R, ASTContext &Ctx
              , unsigned XDim
              , unsigned YDim
              , unsigned ZDim
              , unsigned SI
             )
    : InheritableAttr(attr::WorkGroupSizeHint, R, SI, 0, 0)
              , xDim(XDim)
              , yDim(YDim)
              , zDim(ZDim)
  {



  }

  WorkGroupSizeHintAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;
  unsigned getXDim() const {
    return xDim;
  }

  unsigned getYDim() const {
    return yDim;
  }

  unsigned getZDim() const {
    return zDim;
  }



  static bool classof(const Attr *A) { return A->getKind() == attr::WorkGroupSizeHint; }
};

class X86ForceAlignArgPointerAttr : public InheritableAttr {

public:
  static X86ForceAlignArgPointerAttr *CreateImplicit(ASTContext &Ctx, SourceRange Loc = SourceRange()) {
    X86ForceAlignArgPointerAttr *A = new (Ctx) X86ForceAlignArgPointerAttr(Loc, Ctx, 0);
    A->setImplicit(true);
    return A;
  }

  X86ForceAlignArgPointerAttr(SourceRange R, ASTContext &Ctx
              , unsigned SI
             )
    : InheritableAttr(attr::X86ForceAlignArgPointer, R, SI, 0, 0)
  {
  }

  X86ForceAlignArgPointerAttr *clone(ASTContext &C) const;
  void printPretty(raw_ostream &OS,
                   const PrintingPolicy &Policy) const;
  const char *getSpelling() const;


  static bool classof(const Attr *A) { return A->getKind() == attr::X86ForceAlignArgPointer; }
};

#endif
