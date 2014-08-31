/* 
 * File:   HTMLFStream.cpp
 * Author: User
 * 
 * Created on May 9, 2011, 12:48 PM
 */

#include "HTMLFStream.h"
#include <stdexcept>


using namespace ClangDoc;

HTMLFStream::HTMLFStream(const std::string &filename, ios_base::openmode mode)
: std::fstream(filename.c_str(), mode)
{
}

HTMLFStream::Ptr HTMLFStream::newFStream(const std::string &filename, ios_base::openmode mode)
{
    HTMLFStream::Ptr os(new HTMLFStream(filename, mode));
    if (!os->is_open()) {
        throw std::runtime_error(filename);
    }
    return os;
}

HTMLFStream::Ptr HTMLFStream::newIFStream(const std::string &filename,
        ios_base::openmode mode)
{
    return HTMLFStream::newFStream(filename, mode | ios_base::in);
}

HTMLFStream::Ptr HTMLFStream::newOFStream(const std::string &filename,
        ios_base::openmode mode)
{
    return HTMLFStream::newFStream(filename, mode | ios_base::out);
}
