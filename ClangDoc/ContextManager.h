/* 
 * File:   ContextManager.h
 * Author: User
 *
 * Created on 31 lipiec 2011, 20:31
 */

#ifndef CONTEXTMANAGER_H
#define	CONTEXTMANAGER_H


#include "stdafx.h"
#include "ClangDoc.h"
#include "Options.h"

namespace ClangDoc {
    
    class ContextManager {
    public:

    public:
        static std::string logNameFromPath(std::string path);

        static DiagnosticPtr newDiagnostic(
                Options &options);

        static TargetInfoPtr newTargetInfo(
                Options &options,
                Diagnostic &diagnostic);

        static FileManagerPtr newFileManager(
                Options &options);

        static HeaderSearchPtr newHeaderSearch(
                Options &options,
                FileManager &fileManager,
                TargetInfo &targetInfo);

        static SourceManagerPtr newSourceManager(
                llvm::StringRef fileName,
                Diagnostic &diagnostic,
                FileManager &fileManager);

        static PreprocessorPtr newPreprocessor(
                Options &options
                , Diagnostic &diagnostic
                , TargetInfo &targetInfo
                , HeaderSearch &headerSearch
                , SourceManager &sourceManager);

        static ASTContextPtr newASTContext(
                Preprocessor &preprocessor);

        static LogPtr newLogFile(std::string fileName);

        static SemaPtr newSema(
                Preprocessor &preprocessor,
                ASTContext &astContext,
                ASTConsumer &astConsumer);
    };
    
};


#endif	/* CONTEXTMANAGER_H */

