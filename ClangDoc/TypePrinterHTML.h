#pragma once
#include "stdafx.h"
#include "clang/AST/Type.h"

#include "PrintingPolicyHTML.h"


namespace ClangDoc {
    

class TypePrinterHTML {
    PrintingPolicyHTML Policy;

public:

    explicit TypePrinterHTML(const PrintingPolicyHTML &Policy) : Policy(Policy) {
    }

    void print(const Type *ty, Qualifiers qs, std::string &buffer);
    void print(QualType T, std::string &S);
    void AppendScope(DeclContext *DC, std::string &S);
    void printTag(TagDecl *T, std::string &S);

    static std::string
    PrintTemplateArgumentList(
            const TemplateArgumentListInfo &Args,
            const PrintingPolicyHTML &Policy);


    static std::string
    PrintTemplateArgumentList(
            const TemplateArgument *Args,
            unsigned NumArgs,
            const PrintingPolicyHTML &Policy,
            bool SkipBrackets = false);

    static std::string
    PrintTemplateArgumentList(const TemplateArgumentLoc *Args, unsigned NumArgs,
            const PrintingPolicyHTML &Policy);



#define ABSTRACT_TYPE(CLASS, PARENT)
#define TYPE(CLASS, PARENT) \
    void print##CLASS(const CLASS##Type *T, std::string &S);
#include "clang/AST/TypeNodes.def"
};
};