#!/bin/sh
#==============================================================================
#$RCSfile: gdb.sh,v $
#
#   DESC : GCC compatible gdb run generator (simulator)
#
# AUTHOR : Rick Foos, ECL, LLC
#
#  EEMBC : Technical Advisory Group (TechTAG)
#
#    CVS : $Revision: 1.2 $
#------------------------------------------------------------------------------
# Copyright (c) 1998-2005 by the EDN Embedded Microprocessor 
# Benchmark Consortium (EEMBC), Inc. All Rights Reserved.
#==============================================================================
TGDB=$1
TRES=$2
TRUN=$3
echo "TGDB : $TGDB"

if [ ! -x "$TGDB" ]; then
	echo "*** GDB: $TGDB Not found or not executable." >stderr
	exit 1
fi

# Extract the filename without filetype
#TFILE=`basename $2 | sed -e 's/\(.*\)\..*/\1/g'`
#echo "tfile: $TFILE"

# Clear the GDB program, and pass the --args.
shift
# Build gdb.in for simulator
echo "target sim" >gdb.in
echo "load" >>gdb.in
echo "run" >>gdb.in

echo "$TGDB --args $* <gdb.in"
$TGDB --args $* <gdb.in 2>&1
rm -f gdb.in

