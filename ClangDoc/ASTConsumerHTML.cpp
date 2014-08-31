#include "stdafx.h"

#include "ASTConsumerHTML.h"

using namespace ClangDoc;

ASTConsumerHTML::ASTConsumerHTML(
        ClangDocHTML *html, 
        Preprocessor &preprocessor, 
        llvm::raw_ostream& os)
: ASTConsumer()
, ASTMutationListener()
, html(html)
, preprocessor(preprocessor)
, log(os) 
{

}

ASTConsumerHTML::~ASTConsumerHTML() {
}

/// Initialize - This is called to initialize the consumer, providing the
/// ASTContext.

void ASTConsumerHTML::Initialize(ASTContext &Context) {

}

/// HandleTopLevelDecl - Handle the specified top-level declaration.  This is
/// called by the parser to process every top-level Decl*. Note that D can be
/// the head of a chain of Decls (e.g. for `int a, b` the chain will have two
/// elements). Use Decl::getNextDeclarator() to walk the chain.

void ASTConsumerHTML::HandleTopLevelDecl(DeclGroupRef D) {

    static int count = 0;
    for (DeclGroupRef::iterator it = D.begin(); it != D.end(); ++it) {
        Decl *decl = *it;
        if (decl) {
            if (!preprocessor.getSourceManager().isFromMainFile(decl->getLocation())) {
                continue;
            }
            log << "\n" << decl << " HandleTopLevelDecl" << "\n";
            decl->print(log);
            log << "\n";
            decl->dumpXML(log);
            log << "\n";
            html->HandleTopLevelDecl(decl);
        }
    }
}

/// HandleInterestingDecl - Handle the specified interesting declaration. This
/// is called by the AST reader when deserializing things that might interest
/// the consumer. The default implementation forwards to HandleTopLevelDecl.

void ASTConsumerHTML::HandleInterestingDecl(DeclGroupRef D) {

    for (DeclGroupRef::iterator it = D.begin(); it != D.end(); ++it) {
        Decl *decl = *it;
        if (decl) {
            log << "\n" << decl << " HandleInterestingDecl" << "\n";
            decl->print(log);
            log << "\n";
        }
    }
}

/// HandleTranslationUnit - This method is called when the ASTs for entire
/// translation unit have been parsed.

void ASTConsumerHTML::HandleTranslationUnit(ASTContext &Ctx) {
    TranslationUnitDecl *decl = Ctx.getTranslationUnitDecl();
    if (decl) {
        /*if(decl->getLocation().isInvalid() || !sourceManager->isFromMainFile(decl->getLocation())) {
                        return;
                }*/
        log << "\n" << static_cast<Decl *> (decl) << " HandleTranslationUnit" << "\n";
        //decl->print(log);
        log << "\n";
        html->HandleTranslationUnit(decl);
    }
}

/// HandleTagDeclDefinition - This callback is invoked each time a TagDecl
/// (e.g. struct, union, enum, class) is completed.  This allows the client to
/// hack on the type, which can occur at any point in the file (because these
/// can be defined in declspecs).

void ASTConsumerHTML::HandleTagDeclDefinition(TagDecl *D) {
    TagDecl *decl = D;
    if (decl) {
        if (/*decl->getLocation().isInvalid() ||*/ 
                !preprocessor.getSourceManager().isFromMainFile(decl->getLocation())) {
            return;
        }
        log << "\n" << static_cast<Decl *> (decl) << " HandleTagDeclDefinition" << "\n";
        decl->print(log);
        log << "\n";
        decl->dumpXML(log);
        log << "\n";
        html->HandleTagDeclDefinition(decl);
    }
}

/// CompleteTentativeDefinition - Callback invoked at the end of a translation
/// unit to notify the consumer that the given tentative definition should be
/// completed.
///
/// The variable declaration itself will be a tentative
/// definition. If it had an incomplete array type, its type will
/// have already been changed to an array of size 1. However, the
/// declaration remains a tentative definition and has not been
/// modified by the introduction of an implicit zero initializer.

void ASTConsumerHTML::CompleteTentativeDefinition(VarDecl *D) {
    VarDecl *decl = D;
    if (decl) {
        log << "\n" << static_cast<Decl *> (decl) << " CompleteTentativeDefinition" << "\n";
        decl->print(log);
        log << "\n";
    }

}

/// \brief Callback involved at the end of a translation unit to
/// notify the consumer that a vtable for the given C++ class is
/// required.
///
/// \param RD The class whose vtable was used.
///
/// \param DefinitionRequired Whether a definition of this vtable is
/// required in this translation unit; otherwise, it is only needed if
/// it was actually used.

void ASTConsumerHTML::HandleVTable(CXXRecordDecl *RD, bool DefinitionRequired) {
    CXXRecordDecl *decl = RD;
    if (decl) {
        log << "\n" << static_cast<Decl *> (decl) << " HandleVTable" << "\n";
        decl->print(log);
        log << "\n";
    }

}

/// \brief If the consumer is interested in entities getting modified after
/// their initial creation, it should return a pointer to
/// an ASTMutationListener here.

ASTMutationListener *ASTConsumerHTML::GetASTMutationListener() {
    return this;
}

/// \brief If the consumer is interested in entities being deserialized from
/// AST files, it should return a pointer to a ASTDeserializationListener here

ASTDeserializationListener *ASTConsumerHTML::GetASTDeserializationListener() {
    return 0;
}

/// PrintStats - If desired, print any statistics.

void ASTConsumerHTML::PrintStats() {

}


/// \brief A new TagDecl definition was completed.

void ASTConsumerHTML::CompletedTagDefinition(const TagDecl *D) {
    const TagDecl *decl = D;
    if (decl) {
        log << "\n" << "CompletedTagDefinition" << "\n";
        decl->print(log);
        log << "\n" << decl << "\n";
    }
}

/// \brief A new declaration with name has been added to a DeclContext.

void ASTConsumerHTML::AddedVisibleDecl(const DeclContext *DC, const Decl *D) {
    log << "\n" << "AddedVisibleDecl" << "\n";
    if (DC) {
        DC->dumpDeclContext();
        log << "\n";
    }

    const Decl *decl = D;
    if (decl) {
        decl->print(log);
        log << "\n" << decl << "\n";
    }
}

/// \brief An implicit member was added after the definition was completed.

void ASTConsumerHTML::AddedCXXImplicitMember(const CXXRecordDecl *RD, const Decl *D) {
    log << "\n" << "AddedCXXImplicitMember" << "\n";
    if (RD) {
        RD->print(log);
        log << "\n";
    }

    const Decl *decl = D;
    if (decl) {
        decl->print(log);
        log << "\n" << decl << "\n";
    }
}

/// \brief A template specialization (or partial one) was added to the
/// template declaration.

void ASTConsumerHTML::AddedCXXTemplateSpecialization(const ClassTemplateDecl *TD,
        const ClassTemplateSpecializationDecl *D) {
    log << "\n" << "AddedCXXTemplateSpecialization2" << "\n";
    if (TD) {
        TD->print(log);
        log << "\n";
    }

    const Decl *decl = D;
    if (decl) {
        decl->print(log);
        log << "\n" << decl << "\n";
    }
}


