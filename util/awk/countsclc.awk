#!/usr/local/bin/gawk -f
#==============================================================================
#$RCSfile: countsclc.awk,v $
#
#   DESC : Application Level Make
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


BEGIN{AESL=0.0;error=1;}
(1==1) {

#
# Total appears if multiple languages. 
# Total is last so it will overrite single language cases.
# Reference my @Languages in util/perl/sclc.
#
  if (($7=="TOTAL") ||
      ($7=="Ada") ||
      ($7=="Assembly") ||
      ($7=="Awk") ||
      ($7=="C") ||
      ($7=="C++") ||
      ($7=="Eiffel") ||
      ($7=="Java") ||
      ($7=="Lisp") ||
      ($7=="Pascal") ||
      ($7=="Perl") ||
      ($7=="Tcl") ||
      ($7=="shell") ||
      ($7=="make"))
  {
	LINES=$1;
	BLANK=$2;
	CMMTS=$3;
	NCSL=$4;
	AESL=$5;
	error = 0;
  }
}
  
END {
# Print out the benchmark
if ( BMARK == "" ) {BMARK = "Benchmark"}

if ( error == 0 ) 
  {
  printf ("%-20s\t%d\t%d\t%d\t%d\t%.2f", 
  BMARK, LINES, BLANK, CMMTS, NCSL, AESL);
  fflush();
  }
else
  {
  printf ("%-20s\tERROR", BMARK);
  fflush();
  }
}
