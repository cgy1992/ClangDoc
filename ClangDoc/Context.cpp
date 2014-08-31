
#include "stdafx.h"

#include "Context.h"
#include "ClangDocHTML.h"
#include "ASTConsumerHTML.h"
#include "ContextManager.h"

using namespace ClangDoc;

Context::Context(const Options& _options, const std::string &mainPath)
: options(_options)
, logName(ContextManager::logNameFromPath(mainPath))
, contextLog(ContextManager::newLogFile(logName + "_CTX.log"))
, diagnostic(ContextManager::newDiagnostic(options))
, targetInfo(ContextManager::newTargetInfo(options, *diagnostic))
, fileManager(ContextManager::newFileManager(options))
, headerSearch(ContextManager::newHeaderSearch(options, *fileManager, *targetInfo))
, sourceManager(ContextManager::newSourceManager(mainPath, *diagnostic, *fileManager))
, preprocessor(ContextManager::newPreprocessor(options, *diagnostic, *targetInfo, *headerSearch, *sourceManager))
, htmlOut(new ClangDocHTML(*preprocessor))
, astContext(ContextManager::newASTContext(*preprocessor))
, astConsumer(new ASTConsumerHTML(htmlOut.get(), *preprocessor, *contextLog))
{    
    preprocessor->addPPCallbacks(htmlOut.get());
    preprocessor->AddCommentHandler(htmlOut.get());
    
    ParseAST(*preprocessor, astConsumer.get(), *astContext);
    *contextLog << "\n" << "success" << "\n";
}
