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
OBJECTDIR=build/Tools/GNU-Linux-x86

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/tools/mk1bitlookuptable.o \
	${OBJECTDIR}/entropy.o \
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
.build-conf: ${BUILD_SUBPROJECTS} dist/Tools/GNU-Linux-x86/entropy

dist/Tools/GNU-Linux-x86/entropy: ${OBJECTFILES}
	${MKDIR} -p dist/Tools/GNU-Linux-x86
	${LINK.cc} -o dist/Tools/GNU-Linux-x86/entropy ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/tools/mk1bitlookuptable.o: tools/mk1bitlookuptable.cpp 
	${MKDIR} -p ${OBJECTDIR}/tools
	$(COMPILE.cc) -O3 -Wall -s -o ${OBJECTDIR}/tools/mk1bitlookuptable.o tools/mk1bitlookuptable.cpp

${OBJECTDIR}/entropy.o: entropy.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/entropy.o entropy.cpp

${OBJECTDIR}/benchmarks/count1bitsbenchmark.o: benchmarks/count1bitsbenchmark.cpp 
	${MKDIR} -p ${OBJECTDIR}/benchmarks
	$(COMPILE.cc) -g -o ${OBJECTDIR}/benchmarks/count1bitsbenchmark.o benchmarks/count1bitsbenchmark.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Tools
	${RM} dist/Tools/GNU-Linux-x86/entropy

# Subprojects
.clean-subprojects:
