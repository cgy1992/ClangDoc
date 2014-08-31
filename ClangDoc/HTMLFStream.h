/* 
 * File:   HTMLFStream.h
 * Author: User
 *
 * Created on May 9, 2011, 12:48 PM
 */

#ifndef HTMLFSTREAM_H
#define	HTMLFSTREAM_H

#include "stdafx.h"
#include "llvm/ADT/IntrusiveRefCntPtr.h"
#include <fstream>
#include <string>


namespace ClangDoc {
    

class HTMLFStream;

using std::ios_base;

class HTMLFStream : public std::fstream, public llvm::RefCountedBase<HTMLFStream> {
public:
    typedef llvm::IntrusiveRefCntPtr<HTMLFStream> Ptr;

public:
    static HTMLFStream::Ptr newFStream(const std::string &filename,
            ios_base::openmode mode = ios_base::in | ios_base::out);

    static HTMLFStream::Ptr newIFStream(const std::string &filename,
            ios_base::openmode mode = ios_base::in);

    static HTMLFStream::Ptr newOFStream(const std::string &filename,
            ios_base::openmode mode = ios_base::out | ios_base::trunc);
    
private:
    HTMLFStream(const std::string &filename,
            ios_base::openmode mode = ios_base::in | ios_base::out);
};

};
#endif	/* HTMLFSTREAM_H */

