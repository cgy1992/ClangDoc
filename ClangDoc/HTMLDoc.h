/* 
 * File:   HTMLDoc.h
 * Author: User
 *
 * Created on May 9, 2011, 12:15 PM
 */

#ifndef HTMLDOC_H
#define	HTMLDOC_H

#include "stdafx.h"
#include "HTMLFStream.h"
#include <sstream>


namespace ClangDoc {
    

class HTMLDoc : public llvm::RefCountedBaseVPTR<HTMLDoc> {
public:
    HTMLDoc(HTMLFStream::Ptr out, HTMLFStream::Ptr layout);
    virtual ~HTMLDoc();

    virtual void Write();

protected:
    HTMLFStream::Ptr Out;
    HTMLFStream::Ptr Layout;
    std::string Doc;
    std::stringstream Str;
};

namespace html {

    inline void ReplaceAllIn(std::string &str, const std::string &of,
            const std::string &with) {
        for (int at = str.find(of); at != std::string::npos; at = str.find(of, at)) {
            str.replace(at, of.length(), with);
        }
    }

    inline std::string ReplaceAll(const std::string &str, const std::string &of,
            const std::string &with) {
        std::string s = str;
        html::ReplaceAllIn(s, of, with);
        return s;
    }

    inline std::string PrintableString(const std::string& str) {
        std::string htmlString = str;
        html::ReplaceAllIn(htmlString, "<", "&lt;");
        html::ReplaceAllIn(htmlString, ">", "&gt;");
        return htmlString;
    }

    //@fixme: main filename too?

    inline std::string PagePathFromTitleAndIndexName(const std::string &title,
            const std::string &indexName) {
        std::stringstream path;
        path << title << "/" << indexName << ".html";
        std::string str = path.str();
        html::ReplaceAllIn(str, "::", "_");
        //html::ReplaceAllIn(str, ".", "_");
        return str;
    }

    class string_make : public std::ostringstream {
    public:

        operator std::string() const {
            return str();
        };

        template<typename AA>
        string_make &operator <<(const AA &str) {
            *static_cast<std::ostringstream *> (this) << str;
            return *this;
        }
    };

    inline std::string popItemLayout(std::string& layout, const std::string& tag) {

        std::string tagBegin = html::string_make() << "<!-- " << tag << "_BEGIN -->";
        std::string tagEnd = html::string_make() << "<!-- " << tag << "_END -->";

        size_t begin = layout.find(tagBegin);
        if (begin != std::string::npos) {
            size_t end = layout.find(tagEnd);
            if (end != std::string::npos) {
                size_t beginContent = begin + tagBegin.length();
                size_t endContent = end;
                std::string itemLayout = layout.substr(beginContent, endContent - beginContent);

                end += tagEnd.length();
                layout.erase(begin, end - begin);
                return itemLayout;
            }
        }
        return std::string();
    }

}
};

#endif	/* HTMLDOC_H */

