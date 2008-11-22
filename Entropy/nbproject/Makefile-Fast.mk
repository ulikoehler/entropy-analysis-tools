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
OBJECTDIR=build/Fast/${PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/entropy.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64
CXXFLAGS=-m64

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Fast.mk dist/Release/GNU-Linux-x86/entropy

dist/Release/GNU-Linux-x86/entropy: ${OBJECTFILES}
	${MKDIR} -p dist/Release/GNU-Linux-x86
	${LINK.cc} -lboost_program_options-gcc43-mt -o dist/Release/GNU-Linux-x86/entropy ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/entropy.o: entropy.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -s -o ${OBJECTDIR}/entropy.o entropy.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Fast
	${RM} dist/Release/GNU-Linux-x86/entropy

# Subprojects
.clean-subprojects:
