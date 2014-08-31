/* 
 * File:   HTMLDocIndex.h
 * Author: User
 *
 * Created on May 9, 2011, 12:09 PM
 */

#ifndef HTMLDOCINDEX_H
#define	HTMLDOCINDEX_H

#include "HTMLDoc.h"
#include "HTMLDocPage.h"
#include <set>


namespace ClangDoc {
    

struct HTMLDocPageComp {

    bool operator() (const HTMLDocPage *lhs, const HTMLDocPage * rhs) const {
        return lhs->IndexName < rhs->IndexName;
    }
};

class HTMLDocIndex : public HTMLDoc {
public:
    typedef std::set<HTMLDocPage *, HTMLDocPageComp> IndexItems;
    typedef IndexItems::iterator IndexItemsIt;

    HTMLDocIndex(HTMLFStream::Ptr out);
    virtual ~HTMLDocIndex();

    virtual void Write();
    virtual void AddIndex(const std::string &title, const IndexItems &items);

protected:
    std::stringstream Indexes;
    std::string IndexGroupLayout;
    std::string IndexItemLayout;
};
};
#endif	/* HTMLDOCINDEX_H */

