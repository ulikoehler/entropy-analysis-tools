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
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran

# Macros
PLATFORM=GNU-Linux-x86

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Release/${PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/TextAnalyzer.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64 -O3 -fexpensive-optimizations -fomit-frame-pointer -march=core2 -ftree-vectorize -msse2 -msse3 -msse4 -ffunction-sections -ffast-math -fno-strict-aliasing
CXXFLAGS=-m64 -O3 -fexpensive-optimizations -fomit-frame-pointer -march=core2 -ftree-vectorize -msse2 -msse3 -msse4 -ffunction-sections -ffast-math -fno-strict-aliasing

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/${PLATFORM}/textanalyzer

dist/Release/${PLATFORM}/textanalyzer: ${OBJECTFILES}
	${MKDIR} -p dist/Release/${PLATFORM}
	${LINK.cc} -lboost_program_options-gcc43-mt -o dist/Release/${PLATFORM}/textanalyzer ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/TextAnalyzer.o: TextAnalyzer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O3 -s -o ${OBJECTDIR}/TextAnalyzer.o TextAnalyzer.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/${PLATFORM}/textanalyzer

# Subprojects
.clean-subprojects:
