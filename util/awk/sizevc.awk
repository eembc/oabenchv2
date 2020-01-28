#!/usr/local/bin/gawk -f
#==============================================================================
#$RCSfile: sizevc.awk,v $
#
#   DESC : Application Level Make
#
# AUTHOR : Rick Foos, ECL, LLC
#
#  EEMBC : Technical Advisory Group (TechTAG)
#
#    CVS : $Revision: 1.5 $
#------------------------------------------------------------------------------
# Copyright (c) 1998-2005 by the EDN Embedded Microprocessor 
# Benchmark Consortium (EEMBC), Inc. All Rights Reserved.
#==============================================================================

## Convert hexadecimal string x to decimal n
# @note Parameters h,n,l are required to create local variables.
function hex2dec(x,    h, n, l, i) {
    h = "0123456789ABCDEF..........abcdef"
    for (i = l = length(x); i > 0; i--)
        n += (index(h, substr(x, i, 1)) - 1) % 16 * 16 ^ (l - i)
    return n
}


BEGIN{error=0;}
(1==1) {

  if ($2==".data") {
  DATA=hex2dec($1);
  }
  if ($2==".text") {
  TEXT=hex2dec($1);
  }
  if ($2==".rdata") {
  BSS=hex2dec($1);
  }
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
    
    
