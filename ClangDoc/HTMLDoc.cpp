/* 
 * File:   HTMLDoc.cpp
 * Author: User
 * 
 * Created on May 9, 2011, 12:15 PM
 */

#include "HTMLDoc.h"

using namespace ClangDoc;

HTMLDoc::HTMLDoc(HTMLFStream::Ptr out, HTMLFStream::Ptr layout)
: Out(out), Layout(layout) {
    // Read layout file into Doc string
    size_t fileSize = Layout->seekg(0, ios_base::end).tellg();
    Doc.resize(fileSize);
    Layout->seekg(0, ios_base::beg).read(&Doc.at(0), fileSize);
}

HTMLDoc::~HTMLDoc() {
    Out->close();
}

void HTMLDoc::Write() {
    *Out << Doc;
}

