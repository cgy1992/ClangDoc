/* 
 * File:   HTMLDocFrame.cpp
 * Author: User
 * 
 * Created on May 9, 2011, 12:07 PM
 */

#include "HTMLDocFrame.h"
#include <sstream>
#include <string>

using namespace ClangDoc;


HTMLDocFrame::HTMLDocFrame(HTMLFStream::Ptr out)
: HTMLDoc(out, HTMLFStream::newIFStream(std::string("./resources/index.html")))
{
}

HTMLDocFrame::~HTMLDocFrame()
{
}

void HTMLDocFrame::Write()
{
    html::ReplaceAllIn(Doc, "%DOC_TITLE%", "title");
    HTMLDoc::Write();
}


