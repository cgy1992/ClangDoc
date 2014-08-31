/* 
 * File:   Options.h
 * Author: User
 *
 * Created on 31 lipiec 2011, 20:30
 */

#ifndef OPTIONS_H
#define	OPTIONS_H

#include "stdafx.h"
#include "ClangDoc.h"

namespace ClangDoc {
    
    class Options {
    public:
        Options();
        static Options &instance();

    public:
        static DiagnosticOptions getDiagnosticOptions();
        static FileSystemOptions getFileSystemOptions();
        static LangOptions getLangOptions();
        static HeaderSearchOptions getHeaderSearchOptions();
        static TargetOptions getTargetOptions();
        static PreprocessorOptions getPreprocessorOptions();
        static FrontendOptions getFrontendOptions();

    public:
        DiagnosticOptions diagnosticOptions;
        FileSystemOptions fileSystemOptions;
        LangOptions langOptions;
        HeaderSearchOptions headerSearchOptions;
        TargetOptions targetOptions;
        PreprocessorOptions preprocessorOptions;
        FrontendOptions frontendOptions;
    };
    
};


#endif	/* OPTIONS_H */

