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
	${OBJECTDIR}/crypto/random.o \
	${OBJECTDIR}/gui/gui.o \
	${OBJECTDIR}/crypto/rsa.o \
	${OBJECTDIR}/gui/gui-components.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/crypto/ecdsa.o \
	${OBJECTDIR}/gtkmain.o \
	${OBJECTDIR}/crypto/md.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=`pkg-config gtkmm-2.4 --cflags` 
CXXFLAGS=`pkg-config gtkmm-2.4 --cflags` 

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/${PLATFORM}/easybotan

dist/Release/${PLATFORM}/easybotan: ${OBJECTFILES}
	${MKDIR} -p dist/Release/${PLATFORM}
	${LINK.cc} -lbotan `pkg-config gtkmm-2.4 --libs` `pkg-config --libs gthread-2.0` -o dist/Release/${PLATFORM}/easybotan  ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/crypto/random.o: crypto/random.cpp 
	${MKDIR} -p ${OBJECTDIR}/crypto
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/crypto/random.o crypto/random.cpp

${OBJECTDIR}/gui/gui.o: gui/gui.cpp 
	${MKDIR} -p ${OBJECTDIR}/gui
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/gui/gui.o gui/gui.cpp

${OBJECTDIR}/crypto/rsa.o: crypto/rsa.cpp 
	${MKDIR} -p ${OBJECTDIR}/crypto
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/crypto/rsa.o crypto/rsa.cpp

${OBJECTDIR}/gui/gui-components.o: gui/gui-components.cpp 
	${MKDIR} -p ${OBJECTDIR}/gui
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/gui/gui-components.o gui/gui-components.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/crypto/ecdsa.o: crypto/ecdsa.cpp 
	${MKDIR} -p ${OBJECTDIR}/crypto
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/crypto/ecdsa.o crypto/ecdsa.cpp

${OBJECTDIR}/gtkmain.o: gtkmain.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/gtkmain.o gtkmain.cpp

${OBJECTDIR}/crypto/md.o: crypto/md.cpp 
	${MKDIR} -p ${OBJECTDIR}/crypto
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/crypto/md.o crypto/md.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/${PLATFORM}/easybotan

# Subprojects
.clean-subprojects:
