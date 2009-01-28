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
OBJECTDIR=build/Debug/${PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/gtkmain.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/crypto/rsa.o \
	${OBJECTDIR}/src/gui/gui.o \
	${OBJECTDIR}/src/crypto/ecdsa.o \
	${OBJECTDIR}/src/crypto/random.o \
	${OBJECTDIR}/src/crypto/md.o \
	${OBJECTDIR}/src/gui/gui-components.o

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
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/${PLATFORM}/easybotan

dist/Debug/${PLATFORM}/easybotan: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/${PLATFORM}
	${LINK.cc} -lbotan `pkg-config gtkmm-2.4 --libs` `pkg-config --libs gthread-2.0` -o dist/Debug/${PLATFORM}/easybotan  ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/gtkmain.o: src/gtkmain.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/src/gtkmain.o src/gtkmain.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/crypto/rsa.o: src/crypto/rsa.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/crypto
	$(COMPILE.cc) -g -o ${OBJECTDIR}/src/crypto/rsa.o src/crypto/rsa.cpp

${OBJECTDIR}/src/gui/gui.o: src/gui/gui.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	$(COMPILE.cc) -g -o ${OBJECTDIR}/src/gui/gui.o src/gui/gui.cpp

${OBJECTDIR}/src/crypto/ecdsa.o: src/crypto/ecdsa.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/crypto
	$(COMPILE.cc) -g -o ${OBJECTDIR}/src/crypto/ecdsa.o src/crypto/ecdsa.cpp

${OBJECTDIR}/src/crypto/random.o: src/crypto/random.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/crypto
	$(COMPILE.cc) -g -o ${OBJECTDIR}/src/crypto/random.o src/crypto/random.cpp

${OBJECTDIR}/src/crypto/md.o: src/crypto/md.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/crypto
	$(COMPILE.cc) -g -o ${OBJECTDIR}/src/crypto/md.o src/crypto/md.cpp

${OBJECTDIR}/src/gui/gui-components.o: src/gui/gui-components.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/gui
	$(COMPILE.cc) -g -o ${OBJECTDIR}/src/gui/gui-components.o src/gui/gui-components.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Debug
	${RM} dist/Debug/${PLATFORM}/easybotan

# Subprojects
.clean-subprojects:
