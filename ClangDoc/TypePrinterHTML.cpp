#include "stdafx.h"
#include "TypePrinterHTML.h"
#include "DeclPrinterHTML.h"


using namespace ClangDoc;

static void AppendTypeQualList(std::string &S, unsigned TypeQuals)
{
    if (TypeQuals & Qualifiers::Const) {
        if (!S.empty()) S += ' ';
        S += "const";
    }
    if (TypeQuals & Qualifiers::Volatile) {
        if (!S.empty()) S += ' ';
        S += "volatile";
    }
    if (TypeQuals & Qualifiers::Restrict) {
        if (!S.empty()) S += ' ';
        S += "restrict";
    }
}

void TypePrinterHTML::print(QualType t, std::string &buffer)
{
    SplitQualType split = t.split();
    print(split.first, split.second, buffer);
}

void TypePrinterHTML::print(const Type *T, Qualifiers Quals, std::string &buffer)
{
    if (!T) {
        buffer += "NULL TYPE";
        return;
    }

    if (Policy.SuppressSpecifiers && T->isSpecifierType())
        return;

    // Print qualifiers as appropriate.

    // CanPrefixQualifiers - We prefer to print type qualifiers before the type,
    // so that we get "const int" instead of "int const", but we can't do this if
    // the type is complex.  For example if the type is "int*", we *must* print
    // "int * const", printing "const int *" is different.  Only do this when the
    // type expands to a simple string.
    bool CanPrefixQualifiers = false;

    Type::TypeClass TC = T->getTypeClass();
    if (const AutoType * AT = dyn_cast<AutoType > (T))
        TC = AT->desugar()->getTypeClass();
    if (const SubstTemplateTypeParmType * Subst
            = dyn_cast<SubstTemplateTypeParmType > (T))
        TC = Subst->getReplacementType()->getTypeClass();

    switch (TC) {
    case Type::Builtin:
    case Type::Complex:
    case Type::UnresolvedUsing:
    case Type::Typedef:
    case Type::TypeOfExpr:
    case Type::TypeOf:
    case Type::Decltype:
    case Type::Record:
    case Type::Enum:
    case Type::Elaborated:
    case Type::TemplateTypeParm:
    case Type::SubstTemplateTypeParmPack:
    case Type::TemplateSpecialization:
    case Type::InjectedClassName:
    case Type::DependentName:
    case Type::DependentTemplateSpecialization:
    case Type::ObjCObject:
    case Type::ObjCInterface:
        CanPrefixQualifiers = true;
        break;

    case Type::ObjCObjectPointer:
        CanPrefixQualifiers = T->isObjCIdType() || T->isObjCClassType() ||
                T->isObjCQualifiedIdType() || T->isObjCQualifiedClassType();
        break;

    case Type::Pointer:
    case Type::BlockPointer:
    case Type::LValueReference:
    case Type::RValueReference:
    case Type::MemberPointer:
    case Type::ConstantArray:
    case Type::IncompleteArray:
    case Type::VariableArray:
    case Type::DependentSizedArray:
    case Type::DependentSizedExtVector:
    case Type::Vector:
    case Type::ExtVector:
    case Type::FunctionProto:
    case Type::FunctionNoProto:
    case Type::Paren:
    case Type::Attributed:
    case Type::PackExpansion:
    case Type::SubstTemplateTypeParm:
    case Type::Auto:
        CanPrefixQualifiers = false;
        break;
    }

    if (!CanPrefixQualifiers && !Quals.empty()) {
        std::string qualsBuffer;
        Quals.getAsStringInternal(qualsBuffer, Policy);

        if (!buffer.empty()) {
            qualsBuffer += ' ';
            qualsBuffer += buffer;
        }
        std::swap(buffer, qualsBuffer);
    }

    switch (T->getTypeClass()) {
#define ABSTRACT_TYPE(CLASS, PARENT)
#define TYPE(CLASS, PARENT) case Type::CLASS: \
    print##CLASS(cast<CLASS##Type>(T), buffer); \
    break;
#include "clang/AST/TypeNodes.def"
    }

    // If we're adding the qualifiers as a prefix, do it now.
    if (CanPrefixQualifiers && !Quals.empty()) {
        std::string qualsBuffer;
        Quals.getAsStringInternal(qualsBuffer, Policy);

        if (!buffer.empty()) {
            qualsBuffer += ' ';
            qualsBuffer += buffer;
        }
        std::swap(buffer, qualsBuffer);
    }
}

void TypePrinterHTML::printBuiltin(const BuiltinType *T, std::string &S)
{
    if (S.empty()) {
        S = T->getName(Policy.LangOpts);
    } else {
        // Prefix the basic type, e.g. 'int X'.
        S = ' ' + S;
        S = T->getName(Policy.LangOpts) + S;
    }
}

void TypePrinterHTML::printComplex(const ComplexType *T, std::string &S)
{
    print(T->getElementType(), S);
    S = "_Complex " + S;
}

void TypePrinterHTML::printPointer(const PointerType *T, std::string &S)
{
    S = '*' + S;

    // Handle things like 'int (*A)[4];' correctly.
    // FIXME: this should include vectors, but vectors use attributes I guess.
    if (isa<ArrayType > (T->getPointeeType()))
        S = '(' + S + ')';

    print(T->getPointeeType(), S);
}

void TypePrinterHTML::printBlockPointer(const BlockPointerType *T, std::string &S)
{
    S = '^' + S;
    print(T->getPointeeType(), S);
}

void TypePrinterHTML::printLValueReference(const LValueReferenceType *T,
        std::string &S)
{
    S = '&' + S;

    // Handle things like 'int (&A)[4];' correctly.
    // FIXME: this should include vectors, but vectors use attributes I guess.
    if (isa<ArrayType > (T->getPointeeTypeAsWritten()))
        S = '(' + S + ')';

    print(T->getPointeeTypeAsWritten(), S);
}

void TypePrinterHTML::printRValueReference(const RValueReferenceType *T,
        std::string &S)
{
    S = "&&" + S;

    // Handle things like 'int (&&A)[4];' correctly.
    // FIXME: this should include vectors, but vectors use attributes I guess.
    if (isa<ArrayType > (T->getPointeeTypeAsWritten()))
        S = '(' + S + ')';

    print(T->getPointeeTypeAsWritten(), S);
}

void TypePrinterHTML::printMemberPointer(const MemberPointerType *T,
        std::string &S)
{
    std::string C;
    print(QualType(T->getClass(), 0), C);
    C += "::*";
    S = C + S;

    // Handle things like 'int (Cls::*A)[4];' correctly.
    // FIXME: this should include vectors, but vectors use attributes I guess.
    if (isa<ArrayType > (T->getPointeeType()))
        S = '(' + S + ')';

    print(T->getPointeeType(), S);
}

void TypePrinterHTML::printConstantArray(const ConstantArrayType *T,
        std::string &S)
{
    S += '[';
    S += llvm::utostr(T->getSize().getZExtValue());
    S += ']';

    print(T->getElementType(), S);
}

void TypePrinterHTML::printIncompleteArray(const IncompleteArrayType *T,
        std::string &S)
{
    S += "[]";
    print(T->getElementType(), S);
}

void TypePrinterHTML::printVariableArray(const VariableArrayType *T,
        std::string &S)
{
    S += '[';

    if (T->getIndexTypeQualifiers().hasQualifiers()) {
        AppendTypeQualList(S, T->getIndexTypeCVRQualifiers());
        S += ' ';
    }

    if (T->getSizeModifier() == VariableArrayType::Static)
        S += "static";
    else if (T->getSizeModifier() == VariableArrayType::Star)
        S += '*';

    if (T->getSizeExpr()) {
        std::string SStr;
        llvm::raw_string_ostream s(SStr);
        T->getSizeExpr()->printPretty(s, 0, Policy);
        S += s.str();
    }
    S += ']';

    print(T->getElementType(), S);
}

void TypePrinterHTML::printDependentSizedArray(const DependentSizedArrayType *T,
        std::string &S)
{
    S += '[';

    if (T->getSizeExpr()) {
        std::string SStr;
        llvm::raw_string_ostream s(SStr);
        T->getSizeExpr()->printPretty(s, 0, Policy);
        S += s.str();
    }
    S += ']';

    print(T->getElementType(), S);
}

void TypePrinterHTML::printDependentSizedExtVector(
        const DependentSizedExtVectorType *T,
        std::string &S)
{
    print(T->getElementType(), S);

    S += " __attribute__((ext_vector_type(";
    if (T->getSizeExpr()) {
        std::string SStr;
        llvm::raw_string_ostream s(SStr);
        T->getSizeExpr()->printPretty(s, 0, Policy);
        S += s.str();
    }
    S += ")))";
}

void TypePrinterHTML::printVector(const VectorType *T, std::string &S)
{
    switch (T->getVectorKind()) {
    case VectorType::AltiVecPixel:
        S = "__vector __pixel " + S;
        break;
    case VectorType::AltiVecBool:
        print(T->getElementType(), S);
        S = "__vector __bool " + S;
        break;
    case VectorType::AltiVecVector:
        print(T->getElementType(), S);
        S = "__vector " + S;
        break;
    case VectorType::NeonVector:
        print(T->getElementType(), S);
        S = ("__attribute__((neon_vector_type(" +
                llvm::utostr_32(T->getNumElements()) + "))) " + S);
        break;
    case VectorType::NeonPolyVector:
        print(T->getElementType(), S);
        S = ("__attribute__((neon_polyvector_type(" +
                llvm::utostr_32(T->getNumElements()) + "))) " + S);
        break;
    case VectorType::GenericVector:
    {
        // FIXME: We prefer to print the size directly here, but have no way
        // to get the size of the type.
        print(T->getElementType(), S);
        std::string V = "__attribute__((__vector_size__(";
        V += llvm::utostr_32(T->getNumElements()); // convert back to bytes.
        std::string ET;
        print(T->getElementType(), ET);
        V += " * sizeof(" + ET + ")))) ";
        S = V + S;
        break;
    }
    }
}

void TypePrinterHTML::printExtVector(const ExtVectorType *T, std::string &S)
{
    S += " __attribute__((ext_vector_type(";
    S += llvm::utostr_32(T->getNumElements());
    S += ")))";
    print(T->getElementType(), S);
}

void TypePrinterHTML::printFunctionProto(const FunctionProtoType *T,
        std::string &S)
{
    // If needed for precedence reasons, wrap the inner part in grouping parens.
    if (!S.empty())
        S = "(" + S + ")";

    S += "(";
    std::string Tmp;
    PrintingPolicyHTML ParamPolicy(Policy);
    ParamPolicy.SuppressSpecifiers = false;
    for (unsigned i = 0, e = T->getNumArgs(); i != e; ++i) {
        if (i) S += ", ";
        print(T->getArgType(i), Tmp);
        S += Tmp;
        Tmp.clear();
    }

    if (T->isVariadic()) {
        if (T->getNumArgs())
            S += ", ";
        S += "...";
    } else if (T->getNumArgs() == 0 && !Policy.LangOpts.CPlusPlus) {
        // Do not emit int() if we have a proto, emit 'int(void)'.
        S += "void";
    }

    S += ")";

    FunctionType::ExtInfo Info = T->getExtInfo();
    switch (Info.getCC()) {
    case CC_Default:
    default: break;
    case CC_C:
        S += " __attribute__((cdecl))";
        break;
    case CC_X86StdCall:
        S += " __attribute__((stdcall))";
        break;
    case CC_X86FastCall:
        S += " __attribute__((fastcall))";
        break;
    case CC_X86ThisCall:
        S += " __attribute__((thiscall))";
        break;
    case CC_X86Pascal:
        S += " __attribute__((pascal))";
        break;
    }
    if (Info.getNoReturn())
        S += " __attribute__((noreturn))";
    if (Info.getRegParm())
        S += " __attribute__((regparm (" +
            llvm::utostr_32(Info.getRegParm()) + ")))";

    AppendTypeQualList(S, T->getTypeQuals());

    switch (T->getRefQualifier()) {
    case RQ_None:
        break;

    case RQ_LValue:
        S += " &";
        break;

    case RQ_RValue:
        S += " &&";
        break;
    }

    if (T->hasExceptionSpec()) {
        S += " throw(";
        if (T->hasAnyExceptionSpec())
            S += "...";
        else
            for (unsigned I = 0, N = T->getNumExceptions(); I != N; ++I) {
                if (I)
                    S += ", ";

                std::string ExceptionType;
                print(T->getExceptionType(I), ExceptionType);
                S += ExceptionType;
            }
        S += ")";
    }

    print(T->getResultType(), S);
}

void TypePrinterHTML::printFunctionNoProto(const FunctionNoProtoType *T,
        std::string &S)
{
    // If needed for precedence reasons, wrap the inner part in grouping parens.
    if (!S.empty())
        S = "(" + S + ")";

    S += "()";
    if (T->getNoReturnAttr())
        S += " __attribute__((noreturn))";
    print(T->getResultType(), S);
}

static void printTypeSpec(const NamedDecl *D, std::string &S)
{
    IdentifierInfo *II = D->getIdentifier();
    if (S.empty())
        S = II->getName().str();
    else
        S = II->getName().str() + ' ' + S;
}

void TypePrinterHTML::printUnresolvedUsing(const UnresolvedUsingType *T,
        std::string &S)
{
    printTypeSpec(T->getDecl(), S);
}

void TypePrinterHTML::printTypedef(const TypedefType *T, std::string &S)
{
    TypedefDecl *decl = T->getDecl();
    
    std::string type;
    printTypeSpec(decl, type);
    
    std::string scope;
    AppendScope(decl->getDeclContext(), scope);
    S = S + ' ' + scope + type;
}

void TypePrinterHTML::printTypeOfExpr(const TypeOfExprType *T, std::string &S)
{
    if (!S.empty()) // Prefix the basic type, e.g. 'typeof(e) X'.
        S = ' ' + S;
    std::string Str;
    llvm::raw_string_ostream s(Str);
    T->getUnderlyingExpr()->printPretty(s, 0, Policy);
    S = "typeof " + s.str() + S;
}

void TypePrinterHTML::printTypeOf(const TypeOfType *T, std::string &S)
{
    if (!S.empty()) // Prefix the basic type, e.g. 'typeof(t) X'.
        S = ' ' + S;
    std::string Tmp;
    print(T->getUnderlyingType(), Tmp);
    S = "typeof(" + Tmp + ")" + S;
}

void TypePrinterHTML::printDecltype(const DecltypeType *T, std::string &S)
{
    if (!S.empty()) // Prefix the basic type, e.g. 'decltype(t) X'.
        S = ' ' + S;
    std::string Str;
    llvm::raw_string_ostream s(Str);
    T->getUnderlyingExpr()->printPretty(s, 0, Policy);
    S = "decltype(" + s.str() + ")" + S;
}

void TypePrinterHTML::printAuto(const AutoType *T, std::string &S)
{
    // If the type has been deduced, do not print 'auto'.
    if (T->isDeduced()) {
        print(T->getDeducedType(), S);
    } else {
        if (!S.empty()) // Prefix the basic type, e.g. 'auto X'.
            S = ' ' + S;
        S = "auto" + S;
    }
}

/// Appends the given scope to the end of a string.

void TypePrinterHTML::AppendScope(DeclContext *DC, std::string &Buffer)
{
    if (DC->isTranslationUnit()) return;
    AppendScope(DC->getParent(), Buffer);

    unsigned OldSize = Buffer.size();

    if (NamespaceDecl * NS = dyn_cast<NamespaceDecl > (DC)) {
        if (NS->getIdentifier())
            Buffer += NS->getNameAsString();
        else
            Buffer += "<anonymous>";
    } else if (ClassTemplateSpecializationDecl * Spec
            = dyn_cast<ClassTemplateSpecializationDecl > (DC)) {
        const TemplateArgumentList &TemplateArgs = Spec->getTemplateArgs();
        std::string TemplateArgsStr
                = TypePrinterHTML::PrintTemplateArgumentList(
                TemplateArgs.data(),
                TemplateArgs.size(),
                Policy);
        Buffer += Spec->getIdentifier()->getName();
        Buffer += TemplateArgsStr;
    } else if (TagDecl * Tag = dyn_cast<TagDecl > (DC)) {
        if (TypedefDecl * Typedef = Tag->getTypedefForAnonDecl())
            Buffer += Typedef->getIdentifier()->getName();
        else if (Tag->getIdentifier())
            Buffer += Tag->getIdentifier()->getName();
    }

    if (Buffer.size() != OldSize)
        Buffer += "::";
}

void TypePrinterHTML::printTag(TagDecl *D, std::string &InnerString)
{
    //if (Policy.SuppressTag)
    //    return;

    std::string Buffer;
    bool HasKindDecoration = false;

    // We don't print tags unless this is an elaborated type.
    // In C, we just assume every RecordType is an elaborated type.
    if (!Policy.LangOpts.CPlusPlus && !D->getTypedefForAnonDecl()) {
        HasKindDecoration = true;
        Buffer += D->getKindName();
        Buffer += ' ';
    }

    // Compute the full nested-name-specifier for this type.
    // In C, this will always be empty except when the type
    // being printed is anonymous within other Record.
    //if (!Policy.SuppressScope)
    AppendScope(D->getDeclContext(), Buffer);

    if (const IdentifierInfo * II = D->getIdentifier())
        Buffer += II->getNameStart();
    else if (TypedefDecl * Typedef = D->getTypedefForAnonDecl()) {
        assert(Typedef->getIdentifier() && "Typedef without identifier?");
        Buffer += Typedef->getIdentifier()->getNameStart();
    } else {
        // Print
        llvm::raw_string_ostream OS(Buffer);

        OS << D->getKindName();
        if (D->getIdentifier())
            OS << ' ' << D;

        if (D->isDefinition()) {
            OS << " {\n";
            PrintingPolicyHTML policy = PrintingPolicyHTML(Policy);
            DeclPrinterHTML Printer(OS, D->getASTContext(), policy, 0);
            Printer.VisitDeclContext(D);
            OS << "}";
        }
    }


    // If this is a class template specialization, print the template
    // arguments.
    if (ClassTemplateSpecializationDecl * Spec
            = dyn_cast<ClassTemplateSpecializationDecl > (D)) {
        const TemplateArgument *Args;
        unsigned NumArgs;
        if (TypeSourceInfo * TAW = Spec->getTypeAsWritten()) {
            const TemplateSpecializationType *TST =
                    cast<TemplateSpecializationType > (TAW->getType());
            Args = TST->getArgs();
            NumArgs = TST->getNumArgs();
        } else {
            const TemplateArgumentList &TemplateArgs = Spec->getTemplateArgs();
            Args = TemplateArgs.data();
            NumArgs = TemplateArgs.size();
        }
        Buffer += TypePrinterHTML::PrintTemplateArgumentList(Args,
                NumArgs,
                Policy);
    }

    if (!InnerString.empty()) {
        Buffer += ' ';
        Buffer += InnerString;
    }

    std::swap(Buffer, InnerString);
}

void TypePrinterHTML::printRecord(const RecordType *T, std::string &S)
{
    printTag(T->getDecl(), S);
}

void TypePrinterHTML::printEnum(const EnumType *T, std::string &S)
{
    printTag(T->getDecl(), S);
}

void TypePrinterHTML::printTemplateTypeParm(const TemplateTypeParmType *T,
        std::string &S)
{
    if (!S.empty()) // Prefix the basic type, e.g. 'parmname X'.
        S = ' ' + S;

    if (!T->getName())
        S = "type-parameter-" + llvm::utostr_32(T->getDepth()) + '-' +
        llvm::utostr_32(T->getIndex()) + S;
    else
        S = T->getName()->getName().str() + S;
}

void TypePrinterHTML::printSubstTemplateTypeParm(const SubstTemplateTypeParmType *T,
        std::string &S)
{
    print(T->getReplacementType(), S);
}

void TypePrinterHTML::printSubstTemplateTypeParmPack(
        const SubstTemplateTypeParmPackType *T,
        std::string &S)
{
    printTemplateTypeParm(T->getReplacedParameter(), S);
}

std::string TypePrinterHTML::
PrintTemplateArgumentList(const TemplateArgumentListInfo &Args,
        const PrintingPolicyHTML &Policy)
{
    return PrintTemplateArgumentList(Args.getArgumentArray(),
            Args.size(),
            Policy);
}

std::string
TypePrinterHTML::PrintTemplateArgumentList(
        const TemplateArgument *Args,
        unsigned NumArgs,
        const PrintingPolicyHTML &Policy,
        bool SkipBrackets)
{
    std::string SpecString;
    if (!SkipBrackets)
        SpecString += "&lt;";

    for (unsigned Arg = 0; Arg < NumArgs; ++Arg) {
        if (Arg > 0)
            SpecString += ", ";

        // Print the argument into a string.
        std::string ArgString;
        if (Args[Arg].getKind() == TemplateArgument::Pack) {
            ArgString = PrintTemplateArgumentList(Args[Arg].pack_begin(),
                    Args[Arg].pack_size(),
                    Policy, true);
        } else {
            llvm::raw_string_ostream ArgOut(ArgString);
            Args[Arg].print(Policy, ArgOut);
        }

        // If this is the first argument and its string representation
        // begins with the global scope specifier ('::foo'), add a space
        // to avoid printing the diagraph '<:'.
        if (!Arg && !ArgString.empty() && ArgString[0] == ':')
            SpecString += ' ';

        SpecString += ArgString;
    }

    // If the last character of our string is '>', add another space to
    // keep the two '>''s separate tokens. We don't *have* to do this in
    // C++0x, but it's still good hygiene.
    //if (!SpecString.empty() && SpecString[SpecString.size() - 1] == '>')
    //    SpecString += ' ';

    if (!SkipBrackets)
        SpecString += "&gt;";

    return SpecString;
}

// Sadly, repeat all that with TemplateArgLoc.

std::string TypePrinterHTML::
PrintTemplateArgumentList(const TemplateArgumentLoc *Args, unsigned NumArgs,
        const PrintingPolicyHTML &Policy)
{
    std::string SpecString;
    SpecString += "&lt;";
    for (unsigned Arg = 0; Arg < NumArgs; ++Arg) {
        if (Arg > 0)
            SpecString += ", ";

        // Print the argument into a string.
        std::string ArgString;
        if (Args[Arg].getArgument().getKind() == TemplateArgument::Pack) {
            ArgString = PrintTemplateArgumentList(
                    Args[Arg].getArgument().pack_begin(),
                    Args[Arg].getArgument().pack_size(),
                    Policy, true);
        } else {
            llvm::raw_string_ostream ArgOut(ArgString);
            Args[Arg].getArgument().print(Policy, ArgOut);
        }

        // If this is the first argument and its string representation
        // begins with the global scope specifier ('::foo'), add a space
        // to avoid printing the diagraph '<:'.
        if (!Arg && !ArgString.empty() && ArgString[0] == ':')
            SpecString += ' ';

        SpecString += ArgString;
    }

    // If the last character of our string is '>', add another space to
    // keep the two '>''s separate tokens. We don't *have* to do this in
    // C++0x, but it's still good hygiene.
    //if (SpecString[SpecString.size() - 1] == '>')
    //    SpecString += ' ';

    SpecString += "&gt;";

    return SpecString;
}

void TypePrinterHTML::printTemplateSpecialization(
        const TemplateSpecializationType *T,
        std::string &S)
{
    std::string SpecString;
    llvm::raw_string_ostream OS(SpecString);
    OS.SetUnbuffered();

    //OS << " tname: ";
    {
        T->getTemplateName().print(OS, Policy);
    }

    //OS << " targs: [" << T->getNumArgs() << "] ";

    SpecString += TypePrinterHTML::PrintTemplateArgumentList(
            T->getArgs(),
            T->getNumArgs(),
            Policy,
            false);
    if (S.empty())
        S.swap(SpecString);
    else
        S = SpecString + ' ' + S;
}

void TypePrinterHTML::printInjectedClassName(const InjectedClassNameType *T,
        std::string &S)
{
    printTemplateSpecialization(T->getInjectedTST(), S);
}

void TypePrinterHTML::printElaborated(const ElaboratedType *T, std::string &S)
{

    // Type name
    std::string typeWithQualifier;
    llvm::raw_string_ostream OS(typeWithQualifier);
    OS << TypeWithKeyword::getKeywordName(T->getKeyword());
    if (T->getKeyword() != ETK_None)
        OS << " ";

    // Qualifier
    NestedNameSpecifier* Qualifier = T->getQualifier();
    if (Qualifier)
        Qualifier->print(OS, Policy);

    // Full Type
    std::string fullType;
    PrintingPolicyHTML InnerPolicy(Policy);
    InnerPolicy.SuppressScope = true;
    TypePrinterHTML(InnerPolicy).print(T->getNamedType(), fullType);

    // Result
    typeWithQualifier += fullType;
    if (S.empty())
        S.swap(typeWithQualifier);
    else
        S = typeWithQualifier + ' ' + S;
}

void TypePrinterHTML::printParen(const ParenType *T, std::string &S)
{
    if (!S.empty() && !isa<FunctionType > (T->getInnerType()))
        S = '(' + S + ')';
    print(T->getInnerType(), S);
}

void TypePrinterHTML::printDependentName(const DependentNameType *T, std::string &S)
{
    std::string MyString;

    {
        llvm::raw_string_ostream OS(MyString);
        OS << TypeWithKeyword::getKeywordName(T->getKeyword());
        if (T->getKeyword() != ETK_None)
            OS << " ";

        T->getQualifier()->print(OS, Policy);

        OS << T->getIdentifier()->getName();
    }

    if (S.empty())
        S.swap(MyString);
    else
        S = MyString + ' ' + S;
}

void TypePrinterHTML::printDependentTemplateSpecialization(
        const DependentTemplateSpecializationType *T, std::string &S)
{
    std::string MyString;
    {
        llvm::raw_string_ostream OS(MyString);

        OS << TypeWithKeyword::getKeywordName(T->getKeyword());
        if (T->getKeyword() != ETK_None)
            OS << " ";

        if (T->getQualifier())
            T->getQualifier()->print(OS, Policy);
        OS << T->getIdentifier()->getName();
        OS << TypePrinterHTML::PrintTemplateArgumentList(
                T->getArgs(),
                T->getNumArgs(),
                Policy);
    }

    if (S.empty())
        S.swap(MyString);
    else
        S = MyString + ' ' + S;
}

void TypePrinterHTML::printPackExpansion(const PackExpansionType *T,
        std::string &S)
{
    print(T->getPattern(), S);
    S += "...";
}

void TypePrinterHTML::printAttributed(const AttributedType *T,
        std::string &S)
{
    // Prefer the macro forms of the GC qualifiers.
    if (T->getAttrKind() == AttributedType::attr_objc_gc)
        return print(T->getEquivalentType(), S);

    print(T->getModifiedType(), S);

    // TODO: not all attributes are GCC-style attributes.
    S += " __attribute__((";
    switch (T->getAttrKind()) {
    case AttributedType::attr_address_space:
        S += "address_space(";
        S += T->getEquivalentType().getAddressSpace();
        S += ")";
        break;

    case AttributedType::attr_vector_size:
    {
        S += "__vector_size__(";
        if (const VectorType * vector = T->getEquivalentType()->getAs<VectorType > ()) {
            S += vector->getNumElements();
            S += " * sizeof(";

            std::string tmp;
            print(vector->getElementType(), tmp);
            S += tmp;
            S += ")";
        }
        S += ")";
        break;
    }

    case AttributedType::attr_neon_vector_type:
    case AttributedType::attr_neon_polyvector_type:
    {
        if (T->getAttrKind() == AttributedType::attr_neon_vector_type)
            S += "neon_vector_type(";
        else
            S += "neon_polyvector_type(";
        const VectorType *vector = T->getEquivalentType()->getAs<VectorType > ();
        S += llvm::utostr_32(vector->getNumElements());
        S += ")";
        break;
    }

    case AttributedType::attr_regparm:
    {
        S += "regparm(";
        QualType t = T->getEquivalentType();
        while (!t->isFunctionType())
            t = t->getPointeeType();
        S += t->getAs<FunctionType > ()->getRegParmType();
        S += ")";
        break;
    }

    case AttributedType::attr_objc_gc:
    {
        S += "objc_gc(";

        QualType tmp = T->getEquivalentType();
        while (tmp.getObjCGCAttr() == Qualifiers::GCNone) {
            QualType next = tmp->getPointeeType();
            if (next == tmp) break;
            tmp = next;
        }

        if (tmp.isObjCGCWeak())
            S += "weak";
        else
            S += "strong";
        S += ")";
        break;
    }

    case AttributedType::attr_noreturn: S += "noreturn";
        break;
    case AttributedType::attr_cdecl: S += "cdecl";
        break;
    case AttributedType::attr_fastcall: S += "fastcall";
        break;
    case AttributedType::attr_stdcall: S += "stdcall";
        break;
    case AttributedType::attr_thiscall: S += "thiscall";
        break;
    case AttributedType::attr_pascal: S += "pascal";
        break;
    }
    S += "))";
}

void TypePrinterHTML::printObjCInterface(const ObjCInterfaceType *T,
        std::string &S)
{
    assert("Obj-C unsupported" == false);
}

void TypePrinterHTML::printObjCObject(const ObjCObjectType *T,
        std::string &S)
{
    assert("Obj-C unsupported" == false);
}

void TypePrinterHTML::printObjCObjectPointer(const ObjCObjectPointerType *T,
        std::string &S)
{
    assert("Obj-C unsupported" == false);
}