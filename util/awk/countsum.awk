#!/usr/local/bin/gawk -f
#==============================================================================
#$RCSfile: countsum.awk,v $
#
#   DESC : Sum fields in countsclc.awk generated file.
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


BEGIN{LINES=0;BLANK=0;CMMTS=0;NCSL=0;AESL=0;error=1;}
(1==1) {

LINES+=$2;
BLANK+=$3;
CMMTS+=$4;
NCSL+=$5;
AESL+=$6;
error = 0;
}
  
END {
# Print out the benchmark
if ( BMARK == "" ) {BMARK = "Subcommittee"}

if ( error == 0 ) 
  {
  printf ("%-12s\t%d\t%d\t%d\t%d\t%.2f\n", 
  BMARK, LINES, BLANK, CMMTS, NCSL, AESL);
  }
else
  {
  printf ("%-12s\tERROR\n", BMARK);
  }
  fflush();
}
