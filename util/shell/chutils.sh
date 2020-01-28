#!/bin/sh
#==============================================================================
#$RCSfile: chutils.sh,v $
#
#   DESC : Cheader Utilities
#
# AUTHOR : Rick Foos, ECL, LLC 
#
#    CVS : $Revision: 1.1 $
#------------------------------------------------------------------------------
# Copyright (c) 1998-2005 by the EDN Embedded Microprocessor 
# Benchmark Consortium (EEMBC), Inc. All Rights Reserved.
#==============================================================================

CHEADERDEBUG=

#
# single file function
#
single_file()
{
# $1 - FILEDIR
# $2 - FILETYPE
# $3 - LIBDIR
# $4 - LIBNAME
# $5 - SRCDIR
# $6 - CINITNAME
# $7 - CHEADER OPTIONS (i.e. -w)
# see if we should run Cheader

echo "${MSGPREFIX}Scanning $1 for $2 files..."
RUNCHEADER=0
sfile=`echo "$6" | ${SED} -e "s|$INITC|$SINGLEC|"`

# WARNING: The sort order here generates lib_single.c. Different OS's can
# produce different results (even with sort numberic or ignore case)!
# Size was found to be accurate between OS and utility versions -- aargh.
for i in `find $1 -name "*.$2"`
do
csub=`echo "$i" | ${SED} -e "s|.*/||" | ${SED} -e "s|\.|_|g"`
cfile="$3/${csub}_init.c"
hfile="$3/${csub}.h"
if [ ! -f "${cfile}" ] || [ ! -f "${hfile}" ] 
then
#	echo "${cfile} ${hfile}"
	${CHEADER} -o $3 -d $i -m rb $7
	RUNCHEADER=`expr $RUNCHEADER + $increment`
fi
done

if [ ${RUNCHEADER} -ne 0 ] || [ ! -f "$sfile" ] 
then
	[ ${CHEADERDEBUG} ] && echo "${CINIT} -s $5 $4 >$sfile"
	${CINIT} -s $5 $4 >$sfile
	RUNCHEADER=`expr $RUNCHEADER + $increment`
fi

# Check for all library init file.
if [ ${RUNCHEADER} -ne 0 ] || [ ! -f "$6" ]
then
	${CINIT} $5 $4 >$6
	RUNCHEADER=`expr $RUNCHEADER + $increment`
fi

# If Files generated, make them re-run makerule.pl.
[ ${RUNCHEADER} = 0 ] || RANCHEADER=1

# Tell them why we are making them re-run makerule:)
echo "${MSGPREFIX}Generated ${RUNCHEADER} $2 files for $3..."
RUNCHEADER=0
}

#
# Function to drive all single file with share directory libraries
#
single_file_share()
{
# $1 = ${PSLIBDIR} 
# $2 = ${PSSRCDIR} 
# $3 = ${PSFILEDIR} 
# $4 = ${PSSHAREDIR} 
# $5 = ${PSLIBNAME} 
# $6 = ${PSCINITNAME} 
# $7 = ${lib_FILES}

echo "${MSGPREFIX}Scanning $3 for $5 files..."
RUNCHEADER=0
# see if we should run Cheader
[ -d "$1" ] || mkdir "$1" || exit 1
for i in $7
do
	csub=`echo "$i" | ${SED} -e "s|.*/||" | ${SED} -e "s|\.|_|g"`
	cfile="$2/${csub}_init.c"
	hfile="$2/${csub}.h"
	if [ ! -f "${cfile}" ]
	then
		#	echo "${cfile} ${hfile}"
		${CHEADER} -o $1 -d $i -m rb -x $3 -a $4
		RUNCHEADER=`expr $RUNCHEADER + $increment`
	fi
done

# Check for all library init file.
if [ ${RUNCHEADER} -ne 0 ] || [ ! -f "$6" ]
then
	${CINIT} $2 $5 >$6
	RUNCHEADER=`expr $RUNCHEADER + $increment`
fi

# If Files generated, make them re-run makerule.pl.
[ ${RUNCHEADER} = 0 ] || RANCHEADER=1

# Tell them why we are making them re-run makerule:)
echo "${MSGPREFIX}Generated ${RUNCHEADER} $5 files"
echo "${MSGPREFIX}  for $4 ..."
}

#
# Frame file function
#
frame_file()
{
# $1 - LIBDIR
# $2 - FNAME
# $3 - FILETYPE
# $4 - NOPT
# $5 - SOPT

echo "${MSGPREFIX}Scanning $1 for $3 files..."
RUNCHEADER=0

# Check for the init file for a frameset.
if [ ! -f "$1/$2_$3_init.c" ]
then
	rm -f $1/$2*.[ch]
	${CHEADER} -d $1/$2%.3d -n $4 -s $5 -t .$3 -m rb -f $MODULO
	RUNCHEADER=`expr $RUNCHEADER + $4`
fi

# If Files generated, make them re-run makerule.pl.
[ ${RUNCHEADER} = 0 ] || RANCHEADER=1

# Tell them why we are making them re-run makerule:)
echo "${MSGPREFIX}Generated ${RUNCHEADER} $3 files for $2..."
}
