#!/bin/sh
#==============================================================================
#$RCSfile: cheaderv2.sh,v $
#
#   DESC : Build C files for RAM file system.
#
# AUTHOR : Rick Foos, ECL, LLC 
#
#    CVS : $Revision: 1.25 $
#------------------------------------------------------------------------------
# Copyright (c) 1998-2005 by the EDN Embedded Microprocessor 
# Benchmark Consortium (EEMBC), Inc. All Rights Reserved.
#==============================================================================

# NOTE: The -e option to CHEADER removes Test Harness header file dependencies
#       from the build. If you need these to compile, 
#		edit the CHEADER variable.

# Arguments
# skip - do not process.
# clean - delete all cheader generated files and directories.
# rebuild - Rebuild dependant cheader files, do not delete targets.mak

#
# Programs
#
SED=`which sed`
CHEADER='../util/bin/cheader.exe -e'
CINIT=../util/shell/cinit.sh
CHUTILS=../util/shell/chutils.sh

# Find options to exclude CVS directories
# Older versions of find, in particular BusyBox
# do not support this option within find.
# If there is no CVS directory, then the option
# that doesn't work correctly will be remove.
if [ -d CVS ]; then
	find_NOCVS="-not -path '*CVS*'"
else
	find_NOCVS=
fi

# User Message Prefix
MSGPREFIX="$0 : "

# Setup shell independant method for echo -n
# Usage: echo $ECHO_N "... $ECHO_C"

case `echo "testing\c"; echo 1,2,3`,`echo -n testing; echo 1,2,3` in
  *c*,-n*) ECHO_N= ECHO_C='
' ECHO_T='	' ;;
  *c*,*  ) ECHO_N=-n ECHO_C= ECHO_T= ;;
  *)       ECHO_N= ECHO_C='\c' ECHO_T= ;;
esac

#
# Display any arguments we are acting upon.
#
if [ "$1" = "skip" ]
then
	echo "${MSGPREFIX}Skip CHEADER scan..."
	exit
fi
[ "$1" = "clean" ] && echo "${MSGPREFIX}CHEADER is performing clean ..."
[ "$1" = "rebuild" ] && echo "${MSGPREFIX}CHEADER is performing rebuild ..."

echo "${MSGPREFIX}BEGIN"

#
# Global Variables
#
RANCHEADER=0
RUNCHEADER=0
INITC="_init.c"
SINGLEC="_single.c"
srcdir=.
increment=1

# Ghostscript Version Information.
GSRCDIR=${srcdir}/gs8
GSVER=8.30

#
# Clean command
#
clean_DIRS="\
	${GSRCDIR}/libps \
	${GSRCDIR}/libexamples \
	${GSRCDIR}/libfonts \
	${GSRCDIR}/libresource "

clean_FILES="\
	libpgm/*.[ch] \
	libtxt/*.[ch] \
	libbez/*.[ch] \
	gs8/*_init.c "

if [ "$1" = "clean" ]
then
	echo $ECHO_N "${MSGPREFIX}Cleaning library files... $ECHO_C"
	for i in ${clean_FILES}
	do
		rm -f $i
	done
	echo "done."
	echo $ECHO_N "${MSGPREFIX}Cleaning library directories... $ECHO_C"
	for i in ${clean_DIRS}
	do
		rm -rf $i
	done
	echo "done."
	echo "${MSGPREFIX}END" 
	exit
fi

#
# Common functions for library generation.
#
. ${CHUTILS}

# Shared File Libraries

#
# libps Postscript source file library
#
#PSLIBNAME=libps
#PSFILEDIR=${GSRCDIR}/lib
#PSSRCDIR=${GSRCDIR}/${PSLIBNAME}
#PSLIBDIR=${GSRCDIR}/${PSLIBNAME}
#PSSHAREDIR=/usr/local/share/ghostscript/${GSVER}/lib
#PSCINITDIR=${GSRCDIR}
#PSCINITNAME=${PSCINITDIR}/${PSLIBNAME}${INITC}
#PSINITNAME=libps

# Warning: Sort order used in lib_single.c (we don't use it in this case).
#libps_FILES=`find ${PSFILEDIR} -type f ${find_NOCVS}`

#single_file_share "${PSLIBDIR}" "${PSSRCDIR}" "${PSFILEDIR}" \
#"${PSSHAREDIR}" "${PSLIBNAME}" "${PSCINITNAME}" "${libps_FILES}"

#
# libpgm File Library 
#
FILETYPE=pgm
LIBNAME=libpgm
FILEDIR=${srcdir}/${LIBNAME}
SRCDIR=${srcdir}/${LIBNAME}
LIBDIR=${srcdir}/${LIBNAME}
CINITDIR=${srcdir}/${LIBNAME}
CINITNAME=${CINITDIR}/${LIBNAME}${INITC}

single_file ${FILEDIR} ${FILETYPE} ${LIBDIR} ${LIBNAME} ${SRCDIR} ${CINITNAME}

#
# libtxt File Library 
#
FILETYPE=txt
LIBNAME=libtxt
FILEDIR=${srcdir}/${LIBNAME}
SRCDIR=${srcdir}/${LIBNAME}
LIBDIR=${srcdir}/${LIBNAME}
CINITDIR=${srcdir}/${LIBNAME}
CINITNAME=${CINITDIR}/${LIBNAME}${INITC}

single_file ${FILEDIR} ${FILETYPE} ${LIBDIR} ${LIBNAME} ${SRCDIR} ${CINITNAME}

#
# libbez File Library 
#
FILETYPE=txt
LIBNAME=libbez
FILEDIR=${srcdir}/${LIBNAME}
SRCDIR=${srcdir}/${LIBNAME}
LIBDIR=${srcdir}/${LIBNAME}
CINITDIR=${srcdir}/${LIBNAME}
CINITNAME=${CINITDIR}/${LIBNAME}${INITC}

single_file ${FILEDIR} ${FILETYPE} ${LIBDIR} ${LIBNAME} ${SRCDIR} ${CINITNAME}

#
# libexamples File Library - Input Datasets for Ghostscript
#
#EXLIBNAME=libexamples
#EXFILEDIR=${GSRCDIR}/examples
#EXSRCDIR=${GSRCDIR}/${EXLIBNAME}
#EXLIBDIR=${GSRCDIR}/${EXLIBNAME}
#EXSHAREDIR=/usr/local/share/ghostscript/${GSVER}/examples
#EXCINITDIR=${GSRCDIR}
#EXCINITNAME=${EXCINITDIR}/${EXLIBNAME}${INITC}
#
#libexamples_FILES=`find ${EXFILEDIR} -type f ${find_NOCVS}`
#
#single_file_share "${EXLIBDIR}" "${EXSRCDIR}" "${EXFILEDIR}" \
#"${EXSHAREDIR}" "${EXLIBNAME}" "${EXCINITNAME}" "${libexamples_FILES}"

#
# libfonts File Library
#
#FTLIBNAME=libfonts
#FTFILEDIR=${GSRCDIR}/fonts
#FTSRCDIR=${GSRCDIR}/${FTLIBNAME}
#FTLIBDIR=${GSRCDIR}/${FTLIBNAME}
#FTSHAREDIR=/usr/local/share/ghostscript/fonts
#FTCINITDIR=${GSRCDIR}
#FTCINITNAME=${FTCINITDIR}/${FTLIBNAME}${INITC}
#
#libfonts_FILES=`find ${FTFILEDIR} -type f ${find_NOCVS}`
#
#single_file_share "${FTLIBDIR}" "${FTSRCDIR}" "${FTFILEDIR}" \
#"${FTSHAREDIR}" "${FTLIBNAME}" "${FTCINITNAME}" "${libfonts_FILES}"

#
# libresource File Library for Ghostscript
#
#RSLIBNAME=libresource
#RSFILEDIR=${GSRCDIR}/Resource
#RSSRCDIR=${GSRCDIR}/${RSLIBNAME}
#RSLIBDIR=${GSRCDIR}/${RSLIBNAME}
#RSSHAREDIR=/usr/local/share/ghostscript/${GSVER}/Resource
#RSCINITDIR=${GSRCDIR}
#RSCINITNAME=${RSCINITDIR}/${RSLIBNAME}${INITC}
#
#libresource_FILES=`find ${RSFILEDIR} -type f ${find_NOCVS}`
#
#single_file_share "${RSLIBDIR}" "${RSSRCDIR}" "${RSFILEDIR}" \
#"${RSSHAREDIR}" "${RSLIBNAME}" "${RSCINITNAME}" "${libresource_FILES}"

# Done with library file generation

# Create initialization file for gs filesystem.
GSINITFILE=filesystem
GSCINITDIR=${GSRCDIR}
GSCINITNAME=${GSCINITDIR}/${GSINITFILE}${INITC}
# TODO, add further dependency check if needed.
[ -f "${GSCINITNAME}" ] || ${CINIT} ${GSCINITDIR} ${GSINITFILE} >${GSCINITNAME}

#
# If Cheader was run, force makerule rebuild across all toolchains
#
if [ $RANCHEADER -ne 0 ] && [ "$1" != "rebuild" ]
then
 rm -f targetsv2*.mak
 echo "${MSGPREFIX}Forced makerule rebuild" 
fi

echo "${MSGPREFIX}END" 
