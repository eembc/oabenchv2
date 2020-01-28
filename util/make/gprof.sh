#==============================================================================
#$RCSfile: gprof.sh,v $
#
#   DESC : GCC compatible gprof run generator (profiling)
#
# AUTHOR : Rick Foos, ECL, LLC
#
#  EEMBC : Technical Advisory Group (TechTAG)
#
#    CVS : $Revision: 1.3 $
#------------------------------------------------------------------------------
# Copyright (c) 1998-2005 by the EDN Embedded Microprocessor 
# Benchmark Consortium (EEMBC), Inc. All Rights Reserved.
#==============================================================================
TRES=$1
TRUN=$2
# Extract the filename without filetype
TFILE=`basename $2 | sed -e 's/\(.*\)\..*/\1/g'`
shift
$*
cp gmon.out $TRES/$TFILE.gmon.out
gprof $TRUN $TRES/$TFILE.gmon.out >$TRES/$TFILE.gprof

