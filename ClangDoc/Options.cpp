
#include "stdafx.h"

#include "Options.h"
#include "ClangDoc.h"

using namespace ClangDoc;

Options::Options() 
: diagnosticOptions(Options::getDiagnosticOptions())
, fileSystemOptions(Options::getFileSystemOptions())
, langOptions(Options::getLangOptions())
, headerSearchOptions(Options::getHeaderSearchOptions())
, targetOptions(Options::getTargetOptions())
, preprocessorOptions(Options::getPreprocessorOptions())
, frontendOptions(Options::getFrontendOptions())
{
    
}

Options &Options::instance() {
    static Options staticInstance;
    return staticInstance;
}

DiagnosticOptions Options::getDiagnosticOptions() {
    DiagnosticOptions diagnosticOptions;
    //diagnosticOptions.DumpBuildInformation = logFileName;
    return diagnosticOptions;
}

FileSystemOptions Options::getFileSystemOptions() {
    FileSystemOptions fileSystemOptions;
    //fileSystemOptions.WorkingDir = "";
    return fileSystemOptions;
}

LangOptions Options::getLangOptions() {
    LangOptions langOptions;

    /*
    -cc1
    -triple i386-pc-mingw32
    -S
    -disable-free
    -disable-llvm-verifier
    -main-file-name test.cpp
    -mrelocation-model static
    -mdisable-fp-elim
    -mconstructor-aliases
    -target-cpu pentium4
    -target-linker-version 97.14
    -momit-leaf-frame-pointer
    -v
    -resource-dir C:/sdk/clang/bin\..\lib\clang\2.9
    -ferror-limit 19
    -fmessage-length 80
    -fcxx-exceptions
    -fexceptions
    -fno-use-cxa-atexit
    -fgnu-runtime
    -fdiagnostics-show-option
    -fcolor-diagnostics
    -o C:/DOCUME~1/User/LOCALS~1/Temp/cc-594073.s
    -x c++ test.cpp
     */

    // LANGSTANDARD gnu++0x
    langOptions.BCPLComment = 1;
    langOptions.CPlusPlus = 1;
    langOptions.CPlusPlus0x = 0;
    langOptions.Digraphs = 1;
    langOptions.GNUMode = 1;

    langOptions.GNUKeywords = 1; // OPT_fgnu_keywords
    langOptions.CXXOperatorNames = 1; // OPT_fno_operator_names
    langOptions.AltiVec = 0; // OPT_faltivec
    langOptions.POSIXThreads = 0; // OPT_pthread
    langOptions.NoBuiltin = 0;
    langOptions.Bool = 1;
    langOptions.Exceptions = 1;
    langOptions.CXXExceptions = 1;
    langOptions.RTTI = 0;
    langOptions.ImplicitInt = 0;
    langOptions.C99 = 1;

    //langOptions.HeinousExtensions = 1;
    //langOptions.Microsoft = 1;
    langOptions.EmitAllDecls = 1;

    /* langOptions.Microsoft = 1;
     langOptions.Exceptions = 1;
     langOptions.CXXExceptions = 1;
     langOptions.C99 = 1;
     langOptions.HeinousExtensions = 1;
     langOptions.HexFloats = 1;
     langOptions.ImplicitInt = 0;
     langOptions.DollarIdents = 1;
     langOptions.RTTI = 0;
     langOptions.MathErrno = 0;
     langOptions.PICLevel = 1;
     langOptions.NoInline = 1;
     langOptions.GNUInline = 0;*/

    return langOptions;
}

HeaderSearchOptions Options::getHeaderSearchOptions() {
    // HeaderSearchOptions
    HeaderSearchOptions headerSearchOptions;
    //headerSearchOptions.Sysroot = "/";
    headerSearchOptions.Verbose = true;
    headerSearchOptions.UseBuiltinIncludes = true;
    headerSearchOptions.UseStandardIncludes = true;
    headerSearchOptions.UseStandardCXXIncludes = true;
    headerSearchOptions.ResourceDir = "C:\\sdk\\clang\\lib\\clang\\2.9\\";

    headerSearchOptions.AddPath("C:\\sdk\\clang\\include\\",
            frontend::Quoted, true, false, false);

    headerSearchOptions.AddPath("C:\\sdk\\llvm\\include\\",
            frontend::Quoted, true, false, false);
    return headerSearchOptions;
}

TargetOptions Options::getTargetOptions() {
    TargetOptions targetOptions;
    targetOptions.Triple = llvm::sys::getHostTriple();
    return targetOptions;
}

PreprocessorOptions Options::getPreprocessorOptions() {
    PreprocessorOptions preprocessorOptions;
    preprocessorOptions.UsePredefines = 1;
    preprocessorOptions.addMacroDef("__STDC_LIMIT_MACROS");
    preprocessorOptions.addMacroDef("__STDC_CONSTANT_MACROS");
    return preprocessorOptions;
}

FrontendOptions Options::getFrontendOptions() {
    FrontendOptions frontendOptions;
    return frontendOptions;
}
