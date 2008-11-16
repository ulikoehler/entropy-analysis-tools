#
# Gererated Makefile - do not edit!
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

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Benchmarks/GNU-Linux-x86

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/benchmarks/count1bitsbenchmark.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} dist/Benchmarks/GNU-Linux-x86/entropy

dist/Benchmarks/GNU-Linux-x86/entropy: ${OBJECTFILES}
	${MKDIR} -p dist/Benchmarks/GNU-Linux-x86
	${LINK.cc} -o dist/Benchmarks/GNU-Linux-x86/entropy ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/benchmarks/count1bitsbenchmark.o: benchmarks/count1bitsbenchmark.cpp 
	${MKDIR} -p ${OBJECTDIR}/benchmarks
	$(COMPILE.cc) -g -o ${OBJECTDIR}/benchmarks/count1bitsbenchmark.o benchmarks/count1bitsbenchmark.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Benchmarks
	${RM} dist/Benchmarks/GNU-Linux-x86/entropy

# Subprojects
.clean-subprojects:
