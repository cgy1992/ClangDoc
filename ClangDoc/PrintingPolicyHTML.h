#pragma once
#include "stdafx.h"
#include "clang/AST/PrettyPrinter.h"


namespace ClangDoc {
    

class PrintingPolicyHTML : public PrintingPolicy {
public:

    PrintingPolicyHTML(const LangOptions &LO)
    : PrintingPolicy(LO)
    , htmlSuppressInitializers(false)
    , htmlSuppressIdentifier(false) 
    , htmlSuppressDefinition(false) 
    , htmlSuppressType(false) 
    {
    }

    PrintingPolicyHTML(const PrintingPolicy &rhs)
    : PrintingPolicy(rhs.LangOpts)
    , htmlSuppressInitializers(false)
    , htmlSuppressIdentifier(false) 
    , htmlSuppressDefinition(false) 
    , htmlSuppressType(false) 
    {
    }

    bool htmlSuppressInitializers : 1;
    bool htmlSuppressIdentifier : 1;
    bool htmlSuppressDefinition : 1;
    bool htmlSuppressType : 1;

};
};