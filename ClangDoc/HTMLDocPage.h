/* 
 * File:   HTMLDocPage.h
 * Author: User
 *
 * Created on May 9, 2011, 12:09 PM
 */

#ifndef HTMLDOCPAGE_H
#define	HTMLDOCPAGE_H

#include "HTMLDoc.h"
#include "clang/AST/DeclVisitor.h"
#include "ClangDocHTML.h"

namespace ClangDoc {

class HTMLDocPage : public HTMLDoc {
public:
    HTMLDocPage(HTMLFStream::Ptr out);
    virtual ~HTMLDocPage();

    virtual void Write();
    virtual void AddRecord(CXXRecordDecl *recordDecl, ClangDocHTML *clang);
    virtual void AddDeclContextGroup(DeclContext *recordDecl, int type,
            ClangDocHTML *clang, std::string title);
    virtual void AddDeclContextGroup(DeclContext *recordDecl, std::vector<int> types,
            ClangDocHTML *clang, std::string title);

    virtual void AddDeclGroup(ClangDocHTML::DeclsByType decls, std::vector<int> types,
            ClangDocHTML *clang, std::string title);

    virtual void AddDeclGroup(ClangDocHTML::DeclsByType decls, int type,
            ClangDocHTML *clang, std::string title);

    virtual void AddDeclRows(
            ClangDocHTML::DeclsByType &dbt,
            ClangDocHTML *clang
            );

    virtual void AddDefines(ClangDocHTML::ObjectList defines,
            ClangDocHTML *clang, std::string title);

    virtual void AddNamespace(NamespaceDecl *namespaceDecl, ClangDocHTML *clang);
    virtual void AddTopLevel(ClangDocHTML::DeclsByType decls, ClangDocHTML *clang);

public:
    std::string IndexName;
    std::string PagePath;

    std::string TypeSummaryLayout;
    std::string AccessSpecifierLayout;
    std::string DeclLayout;

};
};

#endif	/* HTMLDOCPAGE_H */

