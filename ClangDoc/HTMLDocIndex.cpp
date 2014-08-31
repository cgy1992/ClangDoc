/* 
 * File:   HTMLDocIndex.cpp
 * Author: User
 * 
 * Created on May 9, 2011, 12:09 PM
 */

#include <set>

#include "HTMLDocIndex.h"


using namespace ClangDoc;

HTMLDocIndex::HTMLDocIndex(HTMLFStream::Ptr out)
: HTMLDoc(out, HTMLFStream::newIFStream(std::string("./resources/docIndex.html")))
{
    IndexGroupLayout = html::popItemLayout(Doc, "INDEX_GROUP");
    IndexItemLayout = html::popItemLayout(IndexGroupLayout, "INDEX_ITEM");
}

HTMLDocIndex::~HTMLDocIndex()
{
}

void HTMLDocIndex::AddIndex(const std::string &title, const IndexItems &items)
{
    if (items.empty()) {
        return;
    }

    // Title
    std::string indexGroup = IndexGroupLayout;
    html::ReplaceAllIn(indexGroup, "%INDEX_GROUP_TITLE%", title);

    // Rows
    std::stringstream rows;
    for (IndexItemsIt it = items.begin(); it != items.end(); ++it) {
        // Index row
        std::string indexRow = IndexItemLayout;
        html::ReplaceAllIn(indexRow, "%INDEX_ITEM_HREF%", (*it)->PagePath);
        html::ReplaceAllIn(indexRow, "%INDEX_ITEM_TITLE%", (*it)->IndexName);
        rows << indexRow;
    }
    html::ReplaceAllIn(indexGroup, "<!-- INDEX_ROWS -->", rows.str());

    // Write
    Indexes << indexGroup;
}

void HTMLDocIndex::Write()
{
    html::ReplaceAllIn(Doc, "%DOC_TITLE%", "title");
    html::ReplaceAllIn(Doc, "<!-- INDEX_GROUPS -->", Indexes.str());
    HTMLDoc::Write();
}
