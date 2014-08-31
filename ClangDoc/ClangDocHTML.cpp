#include "stdafx.h"
#include "ClangDocHTML.h"
#include "DeclPrinterHTML.h"
#include "ASTConsumerHTML.h"
#include "HTMLDocFrame.h"
#include "HTMLDocIndex.h"
#include "HTMLDocPage.h"
#include "clang/Basic/FileManager.h"
#include "ContextManager.h"

using namespace ClangDoc;

ClangDocHTML::ClangDocHTML(Preprocessor &preprocessor)
: preprocessor(preprocessor) {
    
}

ClangDocHTML::~ClangDocHTML(void) {
}

void ClangDocHTML::InclusionDirective(
        SourceLocation HashLoc,
        const Token &IncludeTok,
        llvm::StringRef FileName,
        bool IsAngled,
        const FileEntry *File,
        SourceLocation EndLoc) {
    if (preprocessor.getSourceManager().isFromMainFile(HashLoc)) {
        std::string str;
        llvm::raw_string_ostream os(str);
        os.SetUnbuffered();
        //os << "#include ";
        os << (IsAngled ? "&lt;" : "\"");
        os << FileName;
        os << (IsAngled ? "&gt;" : "\"");
        includes.push_back(str);
    }
}

void ClangDocHTML::MacroDefined(const Token &MacroNameTok, const MacroInfo *MI) {
    //@fixme: ugly
    if (preprocessor.isInPrimaryFile()) {
        std::string define;
        llvm::raw_string_ostream OS(define);
        OS.SetUnbuffered();

        IdentifierInfo *II = MacroNameTok.getIdentifierInfo();

        OS << II->getName();

        if (MI->isFunctionLike()) {
            OS << '(';
            if (!MI->arg_empty()) {
                MacroInfo::arg_iterator AI = MI->arg_begin(), E = MI->arg_end();
                for (; AI + 1 != E; ++AI) {
                    OS << (*AI)->getName();
                    OS << ',';
                }

                // Last argument.
                if ((*AI)->getName() == "__VA_ARGS__")
                    OS << "...";
                else
                    OS << (*AI)->getName();
            }

            if (MI->isGNUVarargs())
                OS << "..."; // #define foo(x...)

            OS << ')';
        }

        // GCC always emits a space, even if the macro body is empty.  However, do not
        // want to emit two spaces if the first token has a leading space.
        if (MI->tokens_empty() || !MI->tokens_begin()->hasLeadingSpace())
            OS << ' ';

        llvm::SmallString < 128 > SpellingBuffer;
        for (MacroInfo::tokens_iterator I = MI->tokens_begin(), E = MI->tokens_end();
                I != E; ++I) {
            if (I->hasLeadingSpace())
                OS << ' ';

            OS << preprocessor.getSpelling(*I, SpellingBuffer);
        }

        objList.push_back(HTMLObject::newDefine(define));
    }
}

bool ClangDocHTML::HandleComment(Preprocessor &PP, SourceRange Comment) {
    if (Comment.isValid()) {
        if (preprocessor.isInPrimaryFile()) {
            commentsList.push_back(Comment);
        }
    }
    return false;
}

void ClangDocHTML::LinkCommentsToDecls() {
    for (CommentsList::iterator c = commentsList.begin(); c != commentsList.end(); ++c) {
        //@fixme: ugly
        const char *cbegin = preprocessor.getSourceManager().getCharacterData((*c).getBegin());
        const char *cend = preprocessor.getSourceManager().getCharacterData((*c).getEnd());
        llvm::StringRef string = llvm::StringRef(cbegin, cend - cbegin);
        

        if (string.startswith("///< ")) {
            std::string htmlString = html::PrintableString(string.substr(5));
            DeclsByLocIt lb = declsByLoc.lower_bound((*c).getBegin());
            DeclsByLocItPair d = declsByLoc.equal_range(lb->first);
            for (DeclsByLocIt it = d.first; it != d.second; ++it) {
                commentsByDecl.insert(CommentsByDeclPair(it->second, htmlString));
            }
        } else if (string.startswith("/// ")) {
            std::string htmlString = html::PrintableString(string.substr(4));
            DeclsByLocIt ub = declsByLoc.upper_bound((*c).getEnd());
            DeclsByLocItPair d = declsByLoc.equal_range(ub->first);
            for (DeclsByLocIt it = d.first; it != d.second; ++it) {
                //Out << "\n" << it->second->getDeclKindName() << " " << string << "\n";
                commentsByDecl.insert(CommentsByDeclPair(it->second, htmlString));
            }
        }
    }
}

ClangDocHTML::RecordDeclsType ClangDocHTML::GetDeclsOfRecord(CXXRecordDecl *decl) {
    // Grouped by Access Specifier
    RecordDeclsType recordDecls(4);

    // skip invalid
    if (!decl || !decl->isDefinition() || !decl->getIdentifier()) {
        return recordDecls;
    }

    DeclContext *DC = decl;
    for (DeclContext::decl_iterator
        dc = DC->decls_begin(), dce = DC->decls_end(); dc != dce; ++dc) {

        // Skip invalid
        if (isa<AccessSpecDecl > (*dc) || (*dc)->isImplicit()) {
            continue;
        }

        DeclsByType &dbt = recordDecls.at((*dc)->getAccess());
        dbt.insert(DeclsByTypePair((*dc)->getKind(), (*dc)));
    }

    return recordDecls;
}

std::string ClangDocHTML::AccessSpecifierAsString(int as) {
    switch (as) {
        case AS_none: return ""; //assert(0 && "No access specifier!");
        case AS_public: return "public";
        case AS_protected: return "protected";
        case AS_private: return "private";
    }
}

ClangDocHTML::DeclsByType ClangDocHTML::GetTopLevelDeclsWithTypes(std::vector<int> types) {
    // Get all decl types, in given order
    DeclsByType allDecls;
    for (int i = 0; i < types.size(); ++i) {
        DeclsByTypeItPair result = declsByType.equal_range(types.at(i));
        allDecls.insert(result.first, result.second);
    }
    return allDecls;
}

ClangDocHTML::RecordDeclsType ClangDocHTML::GetDeclsFromContextWithTypes(
        DeclContext *decl, std::vector<int> types) {
    // Get all decl types, in given order
    RecordDeclsType recordDecls(4);
    for (int i = 0; i < types.size(); ++i) {
        RecordDeclsType decls = GetDeclsFromContextWithType(decl, types.at(i));
        for (int d = 0; d < recordDecls.size(); ++d) {
            recordDecls.at(d).insert(decls.at(d).begin(), decls.at(d).end());
        }
    }
    return recordDecls;
}

ClangDocHTML::RecordDeclsType ClangDocHTML::GetDeclsFromContextWithType(
        DeclContext *decl, int type) {
    // Grouped by Access Specifier
    RecordDeclsType recordDecls(4);

    // skip invalid
    if (!decl) {
        return recordDecls;
    } else if (TagDecl * TD = dyn_cast_or_null<TagDecl > (decl)) {
        if (!TD->isDefinition() || !TD->getIdentifier()) {
            return recordDecls;
        }
    }

    DeclContext *DC = decl;
    for (DeclContext::decl_iterator
        dc = DC->decls_begin(), dce = DC->decls_end(); dc != dce; ++dc) {

        // Skip invalid
        if (isa<AccessSpecDecl > (*dc) || (*dc)->isImplicit()) {
            continue;
        }
        if (TagDecl * TD = dyn_cast_or_null<TagDecl > (*dc)) {
            if (!TD->isDefinition() || !TD->getIdentifier()) {
                continue;
            }
        }

        if ((*dc)->getKind() == type) {
            DeclsByType &dbt = recordDecls.at((*dc)->getAccess());
            dbt.insert(DeclsByTypePair((*dc)->getKind(), (*dc)));
        }
    }

    return recordDecls;
}

HTMLDocPage *ClangDocHTML::newDocPage(const std::string& title, const std::string& indexName) {
    std::string pagePath = html::PagePathFromTitleAndIndexName(title, indexName);
    std::string filePath = std::string(docDir).append(pagePath);
    HTMLDocPage *itemPage = new HTMLDocPage(HTMLFStream::newOFStream(filePath));
    itemPage->PagePath = pagePath;
    itemPage->IndexName = indexName;
    return itemPage;
}

std::string ClangDocHTML::indexNameForDecl(Decl *decl) {
    std::string str;
    llvm::raw_string_ostream htmlOut(str);
    htmlOut.SetUnbuffered();
    PrintingPolicyHTML printingPolicy = PrintingPolicyHTML(decl->getASTContext().PrintingPolicy);
    printingPolicy.SuppressSpecifiers = 1;
    //printingPolicy.SuppressScope = 1;
    printingPolicy.htmlSuppressType = 1;
    DeclPrinterHTML Printer(htmlOut, decl->getASTContext(), printingPolicy, 0);
    Printer.Visit(decl);
    return str;
}

std::string ClangDocHTML::TypeColumnStringForDecl(Decl *decl) {
    std::string str;
    llvm::raw_string_ostream htmlOut(str);
    htmlOut.SetUnbuffered();
    PrintingPolicyHTML printingPolicy = PrintingPolicyHTML(decl->getASTContext().PrintingPolicy);
    printingPolicy.htmlSuppressIdentifier = 1;
    printingPolicy.htmlSuppressInitializers = 1;
    printingPolicy.htmlSuppressDefinition = 1;
    DeclPrinterHTML Printer(htmlOut, decl->getASTContext(), printingPolicy, 0);
    Printer.Visit(decl);
    return str;
}

std::string ClangDocHTML::IdColumnStringForDecl(Decl *decl) {
    std::string str;
    llvm::raw_string_ostream htmlOut(str);
    htmlOut.SetUnbuffered();
    PrintingPolicyHTML printingPolicy = PrintingPolicyHTML(decl->getASTContext().PrintingPolicy);
    printingPolicy.SuppressSpecifiers = 1;
    printingPolicy.SuppressScope = 1;
    printingPolicy.htmlSuppressInitializers = 1;
    printingPolicy.htmlSuppressType = 1;
    DeclPrinterHTML Printer(htmlOut, decl->getASTContext(), printingPolicy, 0);
    Printer.Visit(decl);
    return str;
}

void ClangDocHTML::HandleTranslationUnit(TranslationUnitDecl * D) {
    LinkCommentsToDecls();

    docDir = "./cdoc/";

    // Frame
    {
        HTMLDocFrame docFrame(HTMLFStream::newOFStream("./cdoc/index.html"));
        docFrame.Write();
    }

    // Index and pages
    {
        HTMLDocIndex docIndex(HTMLFStream::newOFStream("./cdoc/docIndex.html"));
        //std::string &doc = docIndex.Doc;

        // Files
        {
            std::string title = "Files";
            HTMLDocIndex::IndexItems items;

            //@fixme: ugly
            FileID fileID = preprocessor.getSourceManager().getMainFileID();
            const char *fileName = preprocessor.getSourceManager().getFileEntryForID(fileID)->getName();

            HTMLDocPage *itemPage = newDocPage(title, fileName);
            itemPage->AddTopLevel(declsByType, this);
            itemPage->Write();

            items.insert(itemPage);
            docIndex.AddIndex(title, items);
        }

        // Namespaces
        {
            std::string title = "Namespaces";
            HTMLDocIndex::IndexItems items;

            DeclsByTypeItPair result = declsByType.equal_range(Decl::Namespace);
            for (DeclsByTypeIt it = result.first; it != result.second; ++it) {
                NamespaceDecl *namespaceDecl = cast<NamespaceDecl > (it->second);

                HTMLDocPage *itemPage = newDocPage(title, indexNameForDecl(namespaceDecl));
                itemPage->AddNamespace(namespaceDecl, this);
                itemPage->Write();

                items.insert(itemPage);
            }

            docIndex.AddIndex(title, items);
        }

        // Records
        {
            std::string title = "Classes";
            HTMLDocIndex::IndexItems items;

            DeclsByTypeItPair result = declsByType.equal_range(Decl::CXXRecord);
            for (DeclsByTypeIt it = result.first; it != result.second; ++it) {
                CXXRecordDecl *recordDecl = cast<CXXRecordDecl > (it->second);

                HTMLDocPage *itemPage = newDocPage(title, indexNameForDecl(recordDecl));
                itemPage->AddRecord(recordDecl, this);
                itemPage->Write();

                items.insert(itemPage);
            }

            docIndex.AddIndex(title, items);
        }

        docIndex.Write();
    }

}

std::string ClangDocHTML::GetCommentsForDecl(Decl *decl) {
    std::stringstream str;
    CommentsByDeclItPair comments = commentsByDecl.equal_range(decl);
    for (CommentsByDeclIt c = comments.first; c != comments.second; ++c) {
        str << c->second << " ";
    }
    return str.str();
}

void ClangDocHTML::HandleTagDeclDefinition(TagDecl * D) {
    DeclContext *DC = D;
    for (DeclContext::decl_iterator
        dc = DC->decls_begin(), dce = DC->decls_end(); dc != dce; ++dc) {
        Decl *decl = (*dc);//->getCanonicalDecl();
        if(ShouldSkipDecl(decl)) {
            continue;
        }
        declsByLoc.insert(DeclsByLocPair(decl->getLocation(), decl));
    }

    HandleTopLevelDecl(D);
}

void ClangDocHTML::HandleTopLevelDecl(Decl * D) {
    declsByType.insert(DeclsByTypePair(D->getKind(), D));
    Decl *decl = D;//->getCanonicalDecl();
        if(ShouldSkipDecl(decl)) {
            return;
        }
    declsByLoc.insert(DeclsByLocPair(decl->getLocation(), decl));
}

bool ClangDocHTML::ShouldSkipDecl(Decl *decl) {
    if (!decl) {
        return true;
    }

    if (FunctionDecl * D = dyn_cast_or_null<FunctionDecl > (decl)) {
        // Template function specializations
        if (D->getTemplateSpecializationInfo()) {
            return true;
        }
    }

    if (TagDecl * D = dyn_cast_or_null<TagDecl > (decl)) {
        // TagDecl without Identifier
        if (!D->getIdentifier()) {
            return true;
        }
        // TagDecl without definition
        if (!D->isDefinition()) {
            return true;
        }
    }

    // Access Specifier
    if (AccessSpecDecl * D = dyn_cast_or_null<AccessSpecDecl > (decl)) {
        return true;
    }

    // Generated by the implementation, not in source code
    if (decl->isImplicit()) {
        return true;
    }

    return false;
}