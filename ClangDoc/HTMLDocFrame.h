/* 
 * File:   HTMLDocFrame.h
 * Author: User
 *
 * Created on May 9, 2011, 12:07 PM
 */

#ifndef HTMLDOCFRAME_H
#define	HTMLDOCFRAME_H

#include "HTMLDoc.h"


namespace ClangDoc {
    

class HTMLDocFrame : public HTMLDoc {
public:
    HTMLDocFrame(HTMLFStream::Ptr out);
    virtual ~HTMLDocFrame();
    
    virtual void Write();
};
};
#endif	/* HTMLDOCFRAME_H */

