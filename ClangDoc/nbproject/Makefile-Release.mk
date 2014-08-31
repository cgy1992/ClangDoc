#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=gfortran
AS=as.exe

# Macros
CND_PLATFORM=MinGW-Windows
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Context.o \
	${OBJECTDIR}/HTMLFStream.o \
	${OBJECTDIR}/ASTConsumerHTML.o \
	${OBJECTDIR}/HTMLDocFrame.o \
	${OBJECTDIR}/DeclPrinterHTML.o \
	${OBJECTDIR}/test.o \
	${OBJECTDIR}/HTMLDocIndex.o \
	${OBJECTDIR}/ContextManager.o \
	${OBJECTDIR}/TypePrinterHTML.o \
	${OBJECTDIR}/Options.o \
	${OBJECTDIR}/ClangDocHTML.o \
	${OBJECTDIR}/HTMLDoc.o \
	${OBJECTDIR}/ClangDoc.o \
	${OBJECTDIR}/PrintingPolicyHTML.o \
	${OBJECTDIR}/HTMLDocPage.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f2

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangdoc.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangdoc.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangdoc ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/Context.o: Context.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Context.o Context.cpp

${OBJECTDIR}/HTMLFStream.o: HTMLFStream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/HTMLFStream.o HTMLFStream.cpp

${OBJECTDIR}/ASTConsumerHTML.o: ASTConsumerHTML.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ASTConsumerHTML.o ASTConsumerHTML.cpp

${OBJECTDIR}/HTMLDocFrame.o: HTMLDocFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/HTMLDocFrame.o HTMLDocFrame.cpp

${OBJECTDIR}/DeclPrinterHTML.o: DeclPrinterHTML.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/DeclPrinterHTML.o DeclPrinterHTML.cpp

${OBJECTDIR}/test.o: test.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/test.o test.cpp

${OBJECTDIR}/HTMLDocIndex.o: HTMLDocIndex.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/HTMLDocIndex.o HTMLDocIndex.cpp

${OBJECTDIR}/ContextManager.o: ContextManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ContextManager.o ContextManager.cpp

${OBJECTDIR}/TypePrinterHTML.o: TypePrinterHTML.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/TypePrinterHTML.o TypePrinterHTML.cpp

${OBJECTDIR}/Options.o: Options.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Options.o Options.cpp

${OBJECTDIR}/ClangDocHTML.o: ClangDocHTML.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ClangDocHTML.o ClangDocHTML.cpp

${OBJECTDIR}/HTMLDoc.o: HTMLDoc.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/HTMLDoc.o HTMLDoc.cpp

${OBJECTDIR}/ClangDoc.o: ClangDoc.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ClangDoc.o ClangDoc.cpp

${OBJECTDIR}/PrintingPolicyHTML.o: PrintingPolicyHTML.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/PrintingPolicyHTML.o PrintingPolicyHTML.cpp

${OBJECTDIR}/HTMLDocPage.o: HTMLDocPage.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/HTMLDocPage.o HTMLDocPage.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/newsimpletest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/newtestclass.o ${TESTDIR}/tests/newtestrunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} 


${TESTDIR}/tests/newsimpletest.o: tests/newsimpletest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/newsimpletest.o tests/newsimpletest.cpp


${TESTDIR}/tests/newtestclass.o: tests/newtestclass.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/newtestclass.o tests/newtestclass.cpp


${TESTDIR}/tests/newtestrunner.o: tests/newtestrunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -O2 -I. -I. -I. -MMD -MP -MF $@.d -o ${TESTDIR}/tests/newtestrunner.o tests/newtestrunner.cpp


${OBJECTDIR}/Context_nomain.o: ${OBJECTDIR}/Context.o Context.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Context.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Context_nomain.o Context.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Context.o ${OBJECTDIR}/Context_nomain.o;\
	fi

${OBJECTDIR}/HTMLFStream_nomain.o: ${OBJECTDIR}/HTMLFStream.o HTMLFStream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/HTMLFStream.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/HTMLFStream_nomain.o HTMLFStream.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/HTMLFStream.o ${OBJECTDIR}/HTMLFStream_nomain.o;\
	fi

${OBJECTDIR}/ASTConsumerHTML_nomain.o: ${OBJECTDIR}/ASTConsumerHTML.o ASTConsumerHTML.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ASTConsumerHTML.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/ASTConsumerHTML_nomain.o ASTConsumerHTML.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ASTConsumerHTML.o ${OBJECTDIR}/ASTConsumerHTML_nomain.o;\
	fi

${OBJECTDIR}/HTMLDocFrame_nomain.o: ${OBJECTDIR}/HTMLDocFrame.o HTMLDocFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/HTMLDocFrame.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/HTMLDocFrame_nomain.o HTMLDocFrame.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/HTMLDocFrame.o ${OBJECTDIR}/HTMLDocFrame_nomain.o;\
	fi

${OBJECTDIR}/DeclPrinterHTML_nomain.o: ${OBJECTDIR}/DeclPrinterHTML.o DeclPrinterHTML.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/DeclPrinterHTML.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/DeclPrinterHTML_nomain.o DeclPrinterHTML.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/DeclPrinterHTML.o ${OBJECTDIR}/DeclPrinterHTML_nomain.o;\
	fi

${OBJECTDIR}/test_nomain.o: ${OBJECTDIR}/test.o test.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/test.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/test_nomain.o test.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/test.o ${OBJECTDIR}/test_nomain.o;\
	fi

${OBJECTDIR}/HTMLDocIndex_nomain.o: ${OBJECTDIR}/HTMLDocIndex.o HTMLDocIndex.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/HTMLDocIndex.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/HTMLDocIndex_nomain.o HTMLDocIndex.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/HTMLDocIndex.o ${OBJECTDIR}/HTMLDocIndex_nomain.o;\
	fi

${OBJECTDIR}/ContextManager_nomain.o: ${OBJECTDIR}/ContextManager.o ContextManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ContextManager.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/ContextManager_nomain.o ContextManager.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ContextManager.o ${OBJECTDIR}/ContextManager_nomain.o;\
	fi

${OBJECTDIR}/TypePrinterHTML_nomain.o: ${OBJECTDIR}/TypePrinterHTML.o TypePrinterHTML.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/TypePrinterHTML.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/TypePrinterHTML_nomain.o TypePrinterHTML.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/TypePrinterHTML.o ${OBJECTDIR}/TypePrinterHTML_nomain.o;\
	fi

${OBJECTDIR}/Options_nomain.o: ${OBJECTDIR}/Options.o Options.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Options.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Options_nomain.o Options.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Options.o ${OBJECTDIR}/Options_nomain.o;\
	fi

${OBJECTDIR}/ClangDocHTML_nomain.o: ${OBJECTDIR}/ClangDocHTML.o ClangDocHTML.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ClangDocHTML.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/ClangDocHTML_nomain.o ClangDocHTML.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ClangDocHTML.o ${OBJECTDIR}/ClangDocHTML_nomain.o;\
	fi

${OBJECTDIR}/HTMLDoc_nomain.o: ${OBJECTDIR}/HTMLDoc.o HTMLDoc.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/HTMLDoc.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/HTMLDoc_nomain.o HTMLDoc.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/HTMLDoc.o ${OBJECTDIR}/HTMLDoc_nomain.o;\
	fi

${OBJECTDIR}/ClangDoc_nomain.o: ${OBJECTDIR}/ClangDoc.o ClangDoc.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ClangDoc.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/ClangDoc_nomain.o ClangDoc.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ClangDoc.o ${OBJECTDIR}/ClangDoc_nomain.o;\
	fi

${OBJECTDIR}/PrintingPolicyHTML_nomain.o: ${OBJECTDIR}/PrintingPolicyHTML.o PrintingPolicyHTML.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/PrintingPolicyHTML.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/PrintingPolicyHTML_nomain.o PrintingPolicyHTML.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/PrintingPolicyHTML.o ${OBJECTDIR}/PrintingPolicyHTML_nomain.o;\
	fi

${OBJECTDIR}/HTMLDocPage_nomain.o: ${OBJECTDIR}/HTMLDocPage.o HTMLDocPage.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/HTMLDocPage.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -O2 -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/HTMLDocPage_nomain.o HTMLDocPage.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/HTMLDocPage.o ${OBJECTDIR}/HTMLDocPage_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/clangdoc.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
