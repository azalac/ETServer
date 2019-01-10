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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/4b0a011a/data.o \
	${OBJECTDIR}/_ext/4b0a011a/linux_app_io.o \
	${OBJECTDIR}/_ext/4b0a011a/posix_driver_io.o \
	${OBJECTDIR}/_ext/4b0a011a/xml_parse.o \
	${OBJECTDIR}/EntryPoint.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/etserver

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/etserver: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/etserver ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/4b0a011a/data.o: /home/austin-z/NetBeansProjects/ETServer/data.c
	${MKDIR} -p ${OBJECTDIR}/_ext/4b0a011a
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4b0a011a/data.o /home/austin-z/NetBeansProjects/ETServer/data.c

${OBJECTDIR}/_ext/4b0a011a/linux_app_io.o: /home/austin-z/NetBeansProjects/ETServer/linux_app_io.c
	${MKDIR} -p ${OBJECTDIR}/_ext/4b0a011a
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4b0a011a/linux_app_io.o /home/austin-z/NetBeansProjects/ETServer/linux_app_io.c

${OBJECTDIR}/_ext/4b0a011a/posix_driver_io.o: /home/austin-z/NetBeansProjects/ETServer/posix_driver_io.c
	${MKDIR} -p ${OBJECTDIR}/_ext/4b0a011a
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4b0a011a/posix_driver_io.o /home/austin-z/NetBeansProjects/ETServer/posix_driver_io.c

${OBJECTDIR}/_ext/4b0a011a/xml_parse.o: /home/austin-z/NetBeansProjects/ETServer/xml_parse.c
	${MKDIR} -p ${OBJECTDIR}/_ext/4b0a011a
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4b0a011a/xml_parse.o /home/austin-z/NetBeansProjects/ETServer/xml_parse.c

${OBJECTDIR}/EntryPoint.o: EntryPoint.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EntryPoint.o EntryPoint.c

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
