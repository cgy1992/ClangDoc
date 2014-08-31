
#include "stdafx.h"

#include "ContextManager.h"
#include "ASTConsumerHTML.h"

using namespace ClangDoc;


DiagnosticPtr ContextManager::newDiagnostic(
        Options &options
        ) {

    // Diagnostic
    llvm::IntrusiveRefCntPtr<DiagnosticIDs> DiagID(new DiagnosticIDs());
    DiagnosticPtr diagnostic = DiagnosticPtr(new Diagnostic(DiagID));

    // TextDiagnosticPrinter
    diagnostic->setClient(new TextDiagnosticPrinter(
            llvm::errs(),
            options.diagnosticOptions,
            false));

    // Apply DiagnosticOptions
    ProcessWarningOptions(*diagnostic, options.diagnosticOptions);

    return diagnostic;
}

TargetInfoPtr ContextManager::newTargetInfo(
        Options &options,
        Diagnostic &diagnostic) {

    TargetInfoPtr targetInfo = TargetInfoPtr(
            TargetInfo::CreateTargetInfo(
            diagnostic,
            options.targetOptions));

    return targetInfo;
}

FileManagerPtr ContextManager::newFileManager(Options &options) {
    FileManagerPtr fileManager = FileManagerPtr(new FileManager(options.fileSystemOptions));
    return fileManager;
}

HeaderSearchPtr ContextManager::newHeaderSearch(
        Options &options,
        FileManager &fileManager,
        TargetInfo &targetInfo) {

    HeaderSearchPtr headerSearch = HeaderSearchPtr(new HeaderSearch(fileManager));

    // Apply HeaderSearchOptions
    ApplyHeaderSearchOptions(
            *headerSearch,
            options.headerSearchOptions,
            options.langOptions,
            targetInfo.getTriple());

    return headerSearch;
}

SourceManagerPtr ContextManager::newSourceManager(
        llvm::StringRef fileName,
        Diagnostic &diagnostic,
        FileManager &fileManager) {

    SourceManagerPtr sourceManager = SourceManagerPtr(new SourceManager(diagnostic, fileManager));

    // Load main file
    const FileEntry *mainFile = fileManager.getFile(fileName);
    sourceManager->createMainFileID(mainFile);

    return sourceManager;
}

std::string ContextManager::logNameFromPath(std::string path) {
    std::replace(path.begin(), path.end(), '.', '_');
    std::replace(path.begin(), path.end(), '/', '_');
    std::replace(path.begin(), path.end(), '\\', '_');
    return path;
}

PreprocessorPtr ContextManager::newPreprocessor(
        Options &options
        , Diagnostic &diagnostic
        , TargetInfo &targetInfo
        , HeaderSearch &headerSearch
        , SourceManager &sourceManager
        ) {
    PreprocessorPtr preprocessor = PreprocessorPtr(new Preprocessor(
            diagnostic,
            options.langOptions,
            targetInfo,
            sourceManager,
            headerSearch));

    // DetailedRecord
    //if (preprocessorOptions.DetailedRecord) {
    //    preprocessor.createPreprocessingRecord();
    //}

    // InitializePreprocessor
    InitializePreprocessor(
            *preprocessor,
            options.preprocessorOptions,
            options.headerSearchOptions,
            options.frontendOptions);

    Builtin::Context &builtinInfo = preprocessor->getBuiltinInfo();

    // InitializeBuiltins
    builtinInfo.InitializeBuiltins(
            preprocessor->getIdentifierTable(),
            preprocessor->getLangOptions());

    // Log BuiltinNames
    /*if (false) {
     *logFile << "\nInitializeBuiltins\n";
        llvm::SmallVector<const char *, 32 > BuiltinNames;
        builtinInfo.GetBuiltinNames(BuiltinNames, langOptions.NoBuiltin);
        for (int i = 0; i < BuiltinNames.size(); i++) {
     *logFile << BuiltinNames[i] << "\n";
        }
    }*/

    return preprocessor;
}

ASTContextPtr ContextManager::newASTContext(Preprocessor &preprocessor) {

    ASTContextPtr astContext = ASTContextPtr(new ASTContext(
            preprocessor.getLangOptions(),
            preprocessor.getSourceManager(),
            preprocessor.getTargetInfo(),
            preprocessor.getIdentifierTable(),
            preprocessor.getSelectorTable(),
            preprocessor.getBuiltinInfo(),
            0));
    return astContext;
}

LogPtr ContextManager::newLogFile(std::string fileName) {
    std::string logFileName = fileName;
    std::string errorInfo;
    LogPtr logFile = LogPtr(new llvm::raw_fd_ostream(logFileName.c_str(), errorInfo));
    logFile->SetUnbuffered();
    logFile->SetUseAtomicWrites(true);
    return logFile;
}

SemaPtr ContextManager::newSema(
        Preprocessor &preprocessor,
        ASTContext &astContext,
        ASTConsumer &astConsumer) {

    SemaPtr sema = SemaPtr(new Sema(
            preprocessor,
            astContext,
            astConsumer));

    // Initialize
    sema->Initialize();

    return sema;
}
