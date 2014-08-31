#pragma once
#include "stdafx.h"

#include "PrintingPolicyHTML.h"
#include "clang/AST/DeclVisitor.h"

namespace ClangDoc {

class DeclPrinterHTML : public DeclVisitor<DeclPrinterHTML> {
    llvm::raw_ostream &Out;
    ASTContext &Context;
    PrintingPolicyHTML Policy;
    unsigned Indentation;

    llvm::raw_ostream& Indent() {
        return Indent(Indentation);
    }
    llvm::raw_ostream& Indent(unsigned Indentation);
    void ProcessDeclGroup(llvm::SmallVectorImpl<Decl*>& Decls);

    void Print(AccessSpecifier AS);

public:

    DeclPrinterHTML(llvm::raw_ostream &Out, ASTContext &Context,
            const PrintingPolicyHTML &Policy,
            unsigned Indentation = 0)
    : Out(Out), Context(Context), Policy(Policy), Indentation(Indentation) {
    }

    void VisitDeclContext(DeclContext *DC, bool Indent = true);

    void VisitTranslationUnitDecl(TranslationUnitDecl *D);
    void VisitTypedefDecl(TypedefDecl *D);
    void VisitEnumDecl(EnumDecl *D);
    void VisitRecordDecl(RecordDecl *D);
    void VisitEnumConstantDecl(EnumConstantDecl *D);
    void VisitFunctionDecl(FunctionDecl *D);
    void VisitFieldDecl(FieldDecl *D);
    void VisitVarDecl(VarDecl *D);
    void VisitLabelDecl(LabelDecl *D);
    void VisitParmVarDecl(ParmVarDecl *D);
    void VisitFileScopeAsmDecl(FileScopeAsmDecl *D);
    void VisitNamespaceDecl(NamespaceDecl *D);
    void VisitUsingDirectiveDecl(UsingDirectiveDecl *D);
    void VisitNamespaceAliasDecl(NamespaceAliasDecl *D);
    void VisitCXXRecordDecl(CXXRecordDecl *D);
    void VisitLinkageSpecDecl(LinkageSpecDecl *D);
    void VisitTemplateDecl(TemplateDecl *D);
    void VisitUnresolvedUsingTypenameDecl(UnresolvedUsingTypenameDecl *D);
    void VisitUnresolvedUsingValueDecl(UnresolvedUsingValueDecl *D);
    void VisitUsingDecl(UsingDecl *D);
    void VisitUsingShadowDecl(UsingShadowDecl *D);

    void VisitFriendDecl(FriendDecl *D);
};

};