// ClangDoc.cpp : Defines the entry point for the console application.
//

/*
 To identify globals over several translation units: Combination filename/global name should be unique (global name alone is unique for non-static vars). If static vars in functions should be handled, function name becomes important, too.
Do it like a compiler: For each file, output an .o file, and build the complete file during “link time”. The .o file could be
A copy of the input file
A serialized AST of the input file
A serialized form of the extracted data
Problem with 1.: Need to remember compile flags, paths, etc
Problem with 3.: Likely need manual (de)serializing code, not really flexible
Second options seems to hit the sweet spot: Shows some more clang, keeps parsing paralellizable, but keeps .o files general.
Sadly, serializing is still incomplete, so we can’t do that. So, go with 3 for now. We need to serialize for each file:
(List of declared globals)
List of defined globals (with information if they are static to that file)
List of global uses, perhaps along with a few lines of context
The linker then can for each global list all uses.
Need to ignore globals in system headers. Tricky: Where to put -I files? Need them as users for some dirs (., proto), as system for others (python). For now keep them as system and whitelist .. This drops proto, but that’s ok for now.
Careful: Need to collect globals on the rhs of toplevel inits, too (XXX).
What about multiple declarations (e.g. gui)?
 */

/*
 Macro expansion?
 */

#include "stdafx.h"

#include "ClangDoc.h"
#include "Options.h"
#include "Context.h"

using namespace ClangDoc;



int main(int argc, const char **argv, char * const *envp) {
    try {

        Options options = Options::instance();
        Context testContext(options, "test.cpp");

        // --
    } catch (std::exception &e) {
        llvm::errs() << e.what() << "\n";
    } catch (...) {
        llvm::errs() << "unknown error" << "\n";
    }
    return 0;
}