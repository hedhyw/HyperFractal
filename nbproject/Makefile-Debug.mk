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
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Fractal.o \
	${OBJECTDIR}/bitmapCore.o \
	${OBJECTDIR}/box.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/triplexNumber.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-lpthread
CXXFLAGS=-lpthread

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lglut -lGL -lGLU -lpthread

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hyperfractal

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hyperfractal: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/hyperfractal ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Fractal.o: Fractal.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/GL -include /usr/include/GL/glut.h -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Fractal.o Fractal.cpp

${OBJECTDIR}/bitmapCore.o: bitmapCore.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/GL -include /usr/include/GL/glut.h -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/bitmapCore.o bitmapCore.cpp

${OBJECTDIR}/box.o: box.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/GL -include /usr/include/GL/glut.h -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/box.o box.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/GL -include /usr/include/GL/glut.h -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/triplexNumber.o: triplexNumber.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/GL -include /usr/include/GL/glut.h -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/triplexNumber.o triplexNumber.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
