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
OBJECTDIR=build/PentiumM/${PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/randgen.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m32 -O3 -march=pentium4m -fexpensive-optimizations -fomit-frame-pointer -march=p -ftree-vectorize -ffunction-sections -ffast-math -fno-strict-aliasing -mfpmath=sse
CXXFLAGS=-m32 -O3 -march=pentium4m -fexpensive-optimizations -fomit-frame-pointer -march=p -ftree-vectorize -ffunction-sections -ffast-math -fno-strict-aliasing -mfpmath=sse

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-PentiumM.mk dist/Release/${PLATFORM}/randgen

dist/Release/${PLATFORM}/randgen: ${OBJECTFILES}
	${MKDIR} -p dist/Release/${PLATFORM}
	${LINK.cc} -lboost_program_options-gcc43-mt -o dist/Release/${PLATFORM}/randgen -s ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/randgen.o: src/randgen.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O3 -s -o ${OBJECTDIR}/src/randgen.o src/randgen.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/PentiumM
	${RM} dist/Release/${PLATFORM}/randgen

# Subprojects
.clean-subprojects:
