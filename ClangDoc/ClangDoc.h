/* 
 * File:   ClangDoc.h
 * Author: User
 *
 * Created on 30 lipiec 2011, 18:52
 */

#ifndef CLANGDOC_H
#define	CLANGDOC_H

#include "stdafx.h"

#include "clang/Basic/FileSystemOptions.h"
#include "clang/Basic/FileManager.h"
#include "clang/Basic/TargetOptions.h"
#include "clang/Basic/TargetInfo.h"

#include "clang/Frontend/DiagnosticOptions.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"
#include "clang/Frontend/HeaderSearchOptions.h"
#include "clang/Frontend/Utils.h"
#include "clang/Frontend/PreprocessorOptions.h"
#include "clang/Frontend/FrontendOptions.h"
#include "clang/Frontend/DiagnosticOptions.h"
#include "clang/Frontend/FrontendDiagnostic.h"

#include "clang/Lex/HeaderSearch.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Lex/PreprocessingRecord.h"

#include "clang/Parse/ParseAST.h"

#include "clang/Sema/Sema.h"

#include "clang/Basic/SourceManager.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/AST/ASTMutationListener.h"
#include "clang/AST/ASTConsumer.h"

#include "clang/Lex/PPCallbacks.h"
#include "clang/AST/DeclVisitor.h"

#include <memory>

namespace ClangDoc {
    
    class ASTConsumerHTML;
    class ClangDocHTML;
    
    typedef std::auto_ptr<Diagnostic> DiagnosticPtr;
    typedef std::auto_ptr<TargetInfo> TargetInfoPtr;
    typedef std::auto_ptr<FileManager> FileManagerPtr;
    typedef std::auto_ptr<HeaderSearch> HeaderSearchPtr;
    typedef std::auto_ptr<SourceManager> SourceManagerPtr;
    typedef std::auto_ptr<Preprocessor> PreprocessorPtr;
    typedef std::auto_ptr<ASTContext> ASTContextPtr;
    typedef std::auto_ptr<llvm::raw_fd_ostream> LogPtr;
    typedef std::auto_ptr<Sema> SemaPtr;
    typedef std::auto_ptr<ASTConsumerHTML> ASTConsumerHTMLPtr;
    typedef std::auto_ptr<ClangDocHTML> ClangDocHTMLPtr;

    struct DocElement {
        std::string path;
        int visibility;
        int group;
        std::string declType;
        std::string declID;
        std::string comment;
    };
};
#endif	/* CLANGDOC_H */

