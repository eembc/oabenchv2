# ============================================================================
#
# Copyright (C) EEMBC(R) All Rights Reserved
#
# This software is licensed with an Acceptable Use Agreement under Apache 2.0.
# Please refer to the license file (LICENSE.md) included with this code.
#
# ============================================================================


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
