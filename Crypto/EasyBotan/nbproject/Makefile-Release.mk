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
	${OBJECTDIR}/gui-components.o \
	${OBJECTDIR}/md.o \
	${OBJECTDIR}/gui.o \
	${OBJECTDIR}/rsa.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/ecdsa.o \
	${OBJECTDIR}/gtkmain.o \
	${OBJECTDIR}/random.o

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

${OBJECTDIR}/gui-components.o: gui-components.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/gui-components.o gui-components.cpp

${OBJECTDIR}/md.o: md.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/md.o md.cpp

${OBJECTDIR}/gui.o: gui.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/gui.o gui.cpp

${OBJECTDIR}/rsa.o: rsa.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/rsa.o rsa.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/ecdsa.o: ecdsa.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/ecdsa.o ecdsa.cpp

${OBJECTDIR}/gtkmain.o: gtkmain.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/gtkmain.o gtkmain.cpp

${OBJECTDIR}/random.o: random.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/random.o random.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/${PLATFORM}/easybotan

# Subprojects
.clean-subprojects:
