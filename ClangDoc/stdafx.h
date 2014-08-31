// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


//#include "targetver.h"

//#include <stdio.h>
//#include <tchar.h>


// - STL -----------------------------------------------------------------------

#include <iostream>
#include <exception>
#include <map>


// - LLVM ----------------------------------------------------------------------

#include "llvm/ADT/StringExtras.h"

#include "llvm/Support/Host.h"
#include "llvm/Support/raw_ostream.h"


// - Clang ---------------------------------------------------------------------

#include "clang/Basic/SourceManager.h"

using namespace clang;
//using namespace clang::driver;

// TODO: reference additional headers your program requires here
