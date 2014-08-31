/* 
 * File:   HTMLDocPage.cpp
 * Author: User
 * 
 * Created on May 9, 2011, 12:09 PM
 */

#include <stdexcept>

#include "HTMLDocPage.h"
#include "ClangDocHTML.h"
#include "PrintingPolicyHTML.h"
#include "DeclPrinterHTML.h"


using namespace ClangDoc;

HTMLDocPage::HTMLDocPage(HTMLFStream::Ptr out)
: HTMLDoc(out, HTMLFStream::newIFStream(std::string("./resources/docOverview.html")))
{
    if (Doc.empty()) {
        throw std::runtime_error("Doc empty");
    }
    TypeSummaryLayout = html::popItemLayout(Doc, "TYPE_SUMMARY");
    AccessSpecifierLayout = html::popItemLayout(Doc, "ACCESS_SPECIFIER");
    DeclLayout = html::popItemLayout(Doc, "DECL");
}

HTMLDocPage::~HTMLDocPage()
{
}

void HTMLDocPage::AddDeclRows(
        ClangDocHTML::DeclsByType &dbt,
        ClangDocHTML *clang
        )
{
    for (ClangDocHTML::DeclsByTypeIt it = dbt.begin(); it != dbt.end(); ++it) {
        Decl *decl = it->second;
        std::string declRow = DeclLayout;

        // Type column
        html::ReplaceAllIn(declRow, "%DECL_TYPE%", clang->TypeColumnStringForDecl(decl));

        // id column
        html::ReplaceAllIn(declRow, "%DECL_ID%", clang->IdColumnStringForDecl(decl));

        // Comment
        std::string comment = clang->GetCommentsForDecl(decl);
        if (!comment.empty()) {
            comment = std::string("<br/><br/>").append(comment);
        }
        html::ReplaceAllIn(declRow, "%DECL_COMMENT%", comment);

        // Write decl row
        Str << declRow;
    }
}

void HTMLDocPage::AddDeclContextGroup(DeclContext *recordDecl, int type,
        ClangDocHTML *clang, std::string title)
{
    std::vector<int> types;
    types.push_back(type);
    AddDeclContextGroup(recordDecl, types, clang, title);
}

void HTMLDocPage::AddDeclContextGroup(DeclContext *recordDecl, std::vector<int> types,
        ClangDocHTML *clang, std::string title)
{
    ClangDocHTML::RecordDeclsType decls =
            clang->GetDeclsFromContextWithTypes(recordDecl, types);

    // skip if empty
    size_t totalCount = 0;
    for (int ai = 0; ai < decls.size(); ++ai) {
        totalCount += !decls.at(ai).empty() ? 1 : 0;
    }
    if (totalCount == 0) {
        return;
    }

    // Write type summary
    Str << html::ReplaceAll(TypeSummaryLayout, "%TYPE_SUMMARY%", title);

    for (int ai = 0; ai < decls.size(); ++ai) {

        ClangDocHTML::DeclsByType &dbt = decls.at(ai);
        if (dbt.empty()) {
            continue;
        }

        // Write Access Specifier
        std::string accessSpecifier = clang->AccessSpecifierAsString(ai);
        if (!accessSpecifier.empty()) {
            Str << html::ReplaceAll(AccessSpecifierLayout,
                    "%ACCESS_SPECIFIER%", accessSpecifier);
        }

        // Decls rows
        AddDeclRows(dbt, clang);
    }
}

void HTMLDocPage::AddDeclGroup(ClangDocHTML::DeclsByType decls, int type,
        ClangDocHTML *clang, std::string title)
{
    std::vector<int> types;
    types.push_back(type);
    AddDeclGroup(decls, types, clang, title);
}

void HTMLDocPage::AddDeclGroup(ClangDocHTML::DeclsByType decls, std::vector<int> types,
        ClangDocHTML *clang, std::string title)
{
    ClangDocHTML::DeclsByType dbt = clang->GetTopLevelDeclsWithTypes(types);

    // skip if empty
    if (dbt.empty()) {
        return;
    }

    // Write type summary
    Str << html::ReplaceAll(TypeSummaryLayout, "%TYPE_SUMMARY%", title);

    // Decls rows
    AddDeclRows(dbt, clang);
}

void HTMLDocPage::AddDefines(ClangDocHTML::ObjectList defines,
        ClangDocHTML *clang, std::string title)
{
    // skip if empty
    if (defines.empty()) {
        return;
    }

    // Write type summary
    Str << html::ReplaceAll(TypeSummaryLayout, "%TYPE_SUMMARY%", title);

    // Decls rows
    for (ClangDocHTML::ObjectListIt it = defines.begin(); it != defines.end(); ++it) {
        HTMLObject *obj = *it;
        std::string declRow = DeclLayout;

        // Type column
        html::ReplaceAllIn(declRow, "%DECL_TYPE%", "#define");

        // id column
        html::ReplaceAllIn(declRow, "%DECL_ID%", *(obj->define));

        // Comment
        //@fixme: comment support
        std::string comment = "" ;//clang->GetCommentsForDecl(decl);
        if (!comment.empty()) {
            comment = std::string("<br/><br/>").append(comment);
        }
        html::ReplaceAllIn(declRow, "%DECL_COMMENT%", comment);

        // Write decl row
        Str << declRow;
    }
}

void HTMLDocPage::AddRecord(CXXRecordDecl *recordDecl, ClangDocHTML *clang)
{
    // Write page title
    html::ReplaceAllIn(Doc, "%INDEX_NAME%", IndexName);

    // Write main comment
    std::string comments = clang->GetCommentsForDecl(recordDecl);
    html::ReplaceAllIn(Doc, "%INDEX_COMMENT%", comments);

    DeclContext *DC = recordDecl;
    for (DeclContext::decl_iterator
        dc = DC->decls_begin(), dce = DC->decls_end(); dc != dce; ++dc) {

      //  Str << "<tr><td>" << (*dc)->getDeclKindName() << "</td></tr>";
    }

    
    std::vector<int> fields;
    fields.push_back(Decl::Field);
    fields.push_back(Decl::Enum);
    fields.push_back(Decl::Typedef);

    std::vector<int> specialFunctions;
    specialFunctions.push_back(Decl::CXXConstructor);
    specialFunctions.push_back(Decl::CXXDestructor);
    specialFunctions.push_back(Decl::CXXConversion);

    std::vector<int> methods;
    methods.push_back(Decl::CXXMethod);

    AddDeclContextGroup(recordDecl, fields, clang, "Field");
    AddDeclContextGroup(recordDecl, specialFunctions, clang, "Special Function");
    AddDeclContextGroup(recordDecl, methods, clang, "Method");
}

void HTMLDocPage::AddNamespace(NamespaceDecl *namespaceDecl, ClangDocHTML *clang)
{
    // Write page title
    html::ReplaceAllIn(Doc, "%INDEX_NAME%", IndexName);

    // Write main comment
    std::string comments = clang->GetCommentsForDecl(namespaceDecl);
    html::ReplaceAllIn(Doc, "%INDEX_COMMENT%", comments);

    DeclContext *DC = namespaceDecl;
    /*for (DeclContext::decl_iterator
        dc = DC->decls_begin(), dce = DC->decls_end(); dc != dce; ++dc) {

    //for (ClangDocHTML::DeclsByTypeIt it = (*dc)->begin(); it != (*dc)->end(); ++it) {
        Decl *decl = *dc;
        decl = decl->getCanonicalDecl();
        Str << "<tr><td>" << decl->getDeclKindName() << "</td><td>"
                << clang->GetCommentsForDecl(decl)
                 << "</td></tr>";
        
    //}
      //  Str << "<tr><td>" << (*dc)->getDeclKindName() << "</td></tr>";
    }*/

    std::vector<int> functions;
    //functions.push_back(Decl::CXXMethod);
    functions.push_back(Decl::Function);
    functions.push_back(Decl::FunctionTemplate);
    
    std::vector<int> classes;
    classes.push_back(Decl::CXXRecord);
    classes.push_back(Decl::ClassTemplateSpecialization);
    //classes.push_back(Decl::ClassTemplate);
    //classes.push_back(Decl::ClassTemplatePartialSpecialization);
    
    /* potentially:
     * Decl::Friend
     * Decl::Using
     * 
     */
    
    
    
    AddDeclContextGroup(namespaceDecl, Decl::Var, clang, "Var");
    AddDeclContextGroup(namespaceDecl, Decl::Enum, clang, "Enum");
    AddDeclContextGroup(namespaceDecl, Decl::Typedef, clang, "Typedef");
    AddDeclContextGroup(namespaceDecl, classes, clang, "Classes");
    AddDeclContextGroup(namespaceDecl, functions, clang, "Function");
}

std::vector<int> GetClassTypes() {
    std::vector<int> types;
    types.push_back(Decl::CXXRecord);
    types.push_back(Decl::ClassTemplateSpecialization);
    //types.push_back(Decl::ClassTemplate);
    //types.push_back(Decl::ClassTemplatePartialSpecialization);
    return types;
}

std::vector<int> GetFunctionTypes() {
    std::vector<int> types;
    //types.push_back(Decl::CXXMethod);
    types.push_back(Decl::Function);
    types.push_back(Decl::FunctionTemplate);
    return types;
}

void HTMLDocPage::AddTopLevel(ClangDocHTML::DeclsByType decls, ClangDocHTML *clang)
{

    // Write page title
    html::ReplaceAllIn(Doc, "%INDEX_NAME%", IndexName);

    // Write main comment
    std::string comments = "";
    html::ReplaceAllIn(Doc, "%INDEX_COMMENT%", comments);

    // Includes
    ClangDocHTML::Includes includes = clang->includes;
    std::stringstream incStr;
    for (ClangDocHTML::IncludesIt it = includes.begin(); it != includes.end(); ++it) {
        incStr << "#include " << *it << "<br/>";
    }
    html::ReplaceAllIn(Doc, "<!-- INCLUDES -->", incStr.str());

    // Defines
    AddDefines(clang->objList, clang, "Defines");


    for (ClangDocHTML::DeclsByTypeIt it = decls.begin(); it != decls.end(); ++it) {
       // Str << "<tr><td>" << it->second->getDeclKindName() << "</td></tr>";
    }

    std::vector<int> functions;
    //functions.push_back(Decl::CXXMethod);
    functions.push_back(Decl::Function);
    functions.push_back(Decl::FunctionTemplate);

    AddDeclGroup(decls, Decl::Enum, clang, "Enum");
    AddDeclGroup(decls, Decl::Typedef, clang, "Typedef");
    AddDeclGroup(decls, Decl::CXXRecord, clang, "Classes");
    AddDeclGroup(decls, functions, clang, "Function");
}

void HTMLDocPage::Write()
{
    html::ReplaceAllIn(Doc, "%DOC_TITLE%", "title");
    html::ReplaceAllIn(Doc, "<!-- TABLE_ROWS -->", Str.str());
    HTMLDoc::Write();
}

