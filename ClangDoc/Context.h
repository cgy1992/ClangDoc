/* 
 * File:   Context.h
 * Author: User
 *
 * Created on 31 lipiec 2011, 20:31
 */

#ifndef CONTEXT_H
#define	CONTEXT_H


#include "stdafx.h"
#include "ClangDoc.h"
#include "Options.h"

namespace ClangDoc {
    
    class Context {
    public:
        explicit Context(const Options &options, const std::string &mainPath);

    private:
        Options options;
        std::string logName;
        LogPtr contextLog;
        
        DiagnosticPtr diagnostic;
        TargetInfoPtr targetInfo;
        FileManagerPtr fileManager;
        HeaderSearchPtr headerSearch;
        SourceManagerPtr sourceManager;
        PreprocessorPtr preprocessor;
        
        ClangDocHTMLPtr htmlOut;        
        
        ASTContextPtr astContext;
        ASTConsumerHTMLPtr astConsumer;
    };
    
};


#endif	/* CONTEXT_H */

