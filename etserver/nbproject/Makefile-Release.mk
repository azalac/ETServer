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
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/App/posix_app_io.o \
	${OBJECTDIR}/src/App/win_app_io.o \
	${OBJECTDIR}/src/Driver/posix_driver_io.o \
	${OBJECTDIR}/src/EntryPoint.o \
	${OBJECTDIR}/src/data.o \
	${OBJECTDIR}/src/xml_parse.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/etserver.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/etserver.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/etserver ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/App/posix_app_io.o: src/App/posix_app_io.c
	${MKDIR} -p ${OBJECTDIR}/src/App
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/App/posix_app_io.o src/App/posix_app_io.c

${OBJECTDIR}/src/App/win_app_io.o: src/App/win_app_io.c
	${MKDIR} -p ${OBJECTDIR}/src/App
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/App/win_app_io.o src/App/win_app_io.c

${OBJECTDIR}/src/Driver/posix_driver_io.o: src/Driver/posix_driver_io.c
	${MKDIR} -p ${OBJECTDIR}/src/Driver
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Driver/posix_driver_io.o src/Driver/posix_driver_io.c

${OBJECTDIR}/src/EntryPoint.o: src/EntryPoint.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/EntryPoint.o src/EntryPoint.c

${OBJECTDIR}/src/data.o: src/data.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/data.o src/data.c

${OBJECTDIR}/src/xml_parse.o: src/xml_parse.c
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/xml_parse.o src/xml_parse.c

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
