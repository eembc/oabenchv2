#!/usr/local/bin/gawk -f
#==============================================================================
#$RCSfile: sizeghs.awk,v $
#
#   DESC : Parse GHS gsize output
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

# NF -1 strips th regular ^Z or ^M character after algorithm.

BEGIN{error=0;DATA=0;TEXT=0;BSS=0}
(1==1) {

  if (($1==".data") || ($1==".rodata") || ($1==".romdata") ||
      ($1 == ".fixaddr") || ($1 == ".fixtype") || ($1 == ".zdata")) 
  {DATA+=$2;}
  if (($1==".text") || ($1==".syscall") || ($1==".secinfo")) 
  {TEXT+=$2;}
  if (($1==".bss") || ($1==".sbss") || ($1==".zbss")) 
  {BSS+=$2;}
}
  
END {
# Print out the benchmark
if ( error != 0 ) {TERROR = "ERROR"}
if ( BMARK == "" ) {BMARK = "Benchmark"}
TOTAL=DATA+BSS+TEXT;

  printf ("%-12s\t%d\t%d\t%d\t%d", 
  BMARK, TEXT, DATA, BSS, TOTAL);
  fflush();
}
    
    
