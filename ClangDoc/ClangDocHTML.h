#pragma once
#include "stdafx.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/AST/DeclVisitor.h"

namespace ClangDoc {
class ASTConsumerHTML;
class HTMLDocPage;

//@fixme: unified commentable object for Decls/includes/defines/etc?

class HTMLObject {
public:
    typedef std::string DefineType;
    Decl *decl;
    DefineType *define;

private:

    HTMLObject(Decl *_decl = NULL, DefineType *_define = NULL)
    : decl(_decl)
    , define(_define) {
    }

public:

    static HTMLObject* newDefine(const std::string _define) {
        return new HTMLObject(NULL, new std::string(_define));
    }

    static HTMLObject* newDecl(Decl *_decl) {
        return new HTMLObject(_decl, NULL);
    }
};

class ClangDocHTML :
public PPCallbacks,
public CommentHandler {
public:

    typedef std::pair<SourceLocation, Decl*> DeclsByLocPair;
    typedef std::multimap<DeclsByLocPair::first_type, DeclsByLocPair::second_type> DeclsByLoc;
    typedef DeclsByLoc::iterator DeclsByLocIt;
    typedef std::pair<DeclsByLocIt, DeclsByLocIt> DeclsByLocItPair;
    DeclsByLoc declsByLoc;

    typedef std::vector<SourceRange> CommentsList;
    CommentsList commentsList;

    typedef std::pair<Decl *, std::string> CommentsByDeclPair;
    typedef std::multimap<CommentsByDeclPair::first_type, CommentsByDeclPair::second_type> CommentsByDecl;
    typedef CommentsByDecl::iterator CommentsByDeclIt;
    typedef std::pair<CommentsByDeclIt, CommentsByDeclIt> CommentsByDeclItPair;
    CommentsByDecl commentsByDecl;


    typedef std::pair<int, Decl*> DeclsByTypePair;
    typedef std::multimap<DeclsByTypePair::first_type, DeclsByTypePair::second_type> DeclsByType;
    typedef DeclsByType::iterator DeclsByTypeIt;
    typedef std::pair<DeclsByTypeIt, DeclsByTypeIt> DeclsByTypeItPair;
    DeclsByType declsByType;


    typedef std::vector<std::string> Includes;
    typedef Includes::iterator IncludesIt;
    typedef std::pair<IncludesIt, IncludesIt> IncludesItPair;
    Includes includes;

    typedef std::vector<ClangDocHTML::DeclsByType> RecordDeclsType;
    typedef RecordDeclsType::iterator RecordDeclsIt;

    typedef std::vector<HTMLObject *> ObjectList;
    typedef ObjectList::iterator ObjectListIt;
    ObjectList objList;

    std::string docDir;
    Preprocessor &preprocessor;

public:
    ClangDocHTML(Preprocessor &preprocessor);
    virtual ~ClangDocHTML(void);

public:
    void HandleTranslationUnit(TranslationUnitDecl *D);
    void HandleTopLevelDecl(Decl *D);
    void HandleTagDeclDefinition(TagDecl *D);

public:
    void LinkCommentsToDecls();

    HTMLDocPage *newDocPage(const std::string& title, const std::string& indexName);
    std::string indexNameForDecl(Decl *decl);
    ClangDocHTML::RecordDeclsType GetDeclsOfRecord(CXXRecordDecl *decl);
    ClangDocHTML::RecordDeclsType GetDeclsFromContextWithType(
            DeclContext *decl, int type);
    ClangDocHTML::RecordDeclsType GetDeclsFromContextWithTypes(
            DeclContext *decl, std::vector<int> types);
    std::string GetCommentsForDecl(Decl *decl);

    ClangDocHTML::DeclsByType GetTopLevelDeclsWithTypes(std::vector<int> types);

    std::string TypeColumnStringForDecl(Decl *decl);
    std::string IdColumnStringForDecl(Decl *decl);

    std::string AccessSpecifierAsString(int as);

    bool ShouldSkipDecl(Decl *decl);

public:
    /// InclusionDirective -- PPCallbacks Interface
    virtual void InclusionDirective(SourceLocation HashLoc,
            const Token &IncludeTok,
            llvm::StringRef FileName,
            bool IsAngled,
            const FileEntry *File,
            SourceLocation EndLoc);


    /// MacroDefined -- PPCallbacks Interface
    virtual void MacroDefined(const Token &MacroNameTok, const MacroInfo *MI);

public:
    /// HandleComment -- CommentHandler Interface
    virtual bool HandleComment(Preprocessor &PP, SourceRange Comment);
};

};