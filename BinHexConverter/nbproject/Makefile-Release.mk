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
	${OBJECTDIR}/binhexconverter.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64 -fexpensive-optimizations -fomit-frame-pointer -march=core2 -ftree-vectorize -msse2 -msse3 -msse4 -ffunction-sections -fno-strict-aliasing
CXXFLAGS=-m64 -fexpensive-optimizations -fomit-frame-pointer -march=core2 -ftree-vectorize -msse2 -msse3 -msse4 -ffunction-sections -fno-strict-aliasing

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/${PLATFORM}/binhexconverter

dist/Release/${PLATFORM}/binhexconverter: ${OBJECTFILES}
	${MKDIR} -p dist/Release/${PLATFORM}
	${LINK.cc} -o dist/Release/${PLATFORM}/binhexconverter ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/binhexconverter.o: binhexconverter.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O3 -s -o ${OBJECTDIR}/binhexconverter.o binhexconverter.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/${PLATFORM}/binhexconverter

# Subprojects
.clean-subprojects:
