# ============================================================================
#
# Copyright (C) EEMBC(R) All Rights Reserved
#
# This software is licensed with an Acceptable Use Agreement under Apache 2.0.
# Please refer to the license file (LICENSE.md) included with this code.
#
# ============================================================================

# NF -1 strips th regular ^Z or ^M character after algorithm.

BEGIN{error=0;CRC="";ECRC="";}
(1==1) {

  if (($2=="Bench") && ($3=="Mark") && ($4==":")) {
    BM = "";
    for (i=5; i<=NF; i++) BM = BM $i " ";
    # Have to strip NL off the last field.
    BM=substr(BM,1,length(BM)-1);
# TH Regular put's a carriage return in here.
    THCR=match(BM,/\r/);
    if (THCR != 0 ) {BM=substr(BM,1,THCR-1);}
  }

  if ($2=="BM:") {
    BM = "";
    for (i=3; i<=NF; i++) BM = BM $i " ";
    BM=substr(BM,1,length(BM)-1);
# TH Regular put's a carriage return in here.
    THCR=match(BM,/\r/);
    if (THCR != 0 ) {BM=substr(BM,1,THCR-1);}
  }
  
  if ($2=="ID:") {
    IDSUB = substr($3,1,16);
    IDBM  = $4;
    if (IDSUB=="!!!!EEMBC-BM!!!!") {
    IDSUB = "EEMBC";
    IDBM  = "EEMBC";
    }
  }
  if (($2=="Target") && ($3=="Timer") && ($4=="Rate")) { RATE = $6;  }
  if (($2=="Iterations") && ($3=="=")) { IT = $4;  }
  if (($2=="Target") && ($3=="Duration")) { DU = $5; }
  if (($3=="CRC") && ($4=="=")) { CRC = $5;  }
  if (($2=="Time") && ($3=="/") && ($4=="Iter")) { SECIT = $6; }

  if (($2=="Iterations/Sec") && ($3=="=")) { ITSEC = $4; }
  if (($2=="Total") && ($3=="Run") && ($4=="Time")) { RUNTIME = $6; }

# --  Failure: Actual CRC 28a8, Expected CRC 0
  if (($2=="Failure:") && ($4=="CRC") )
  {
    ECRC = $8;
    ECOMMA=match(ECRC,/,/);
    if (ECOMMA != 0 ) 
    {
      ECRC=substr(ECRC,1,ECOMMA-1);
    }
    error++;
  }

# DONE replaced by Failure
  if (($1=="Failure:") || ($2=="Failure:")) { error++; }
  if (($1=="ERROR") || ($2=="ERROR:")) { error++; }
}
  
END {
# Print out the benchmark
if (CRC != "")
  {
    CRC = "0x" CRC;
    if (ECRC == ""){ECRC=CRC;}
    else {ECRC = "0x" ECRC;}
  }
if (IT==0) {error++;}
if ( error != 0 || IDBM == "") {TERROR = "ERROR"}

  DU=DU+0;
  printf ("%s\t%-12s\t%-11s\t%s\t%-30s\t%-6s\t%-6s\t%d\t%d\t%d\t%18.9f\t%18.9f\t%18.9f", 
  IDSUB, IDBM, DATASET, TERROR, BM, ECRC, CRC, IT, DU, RATE, ITSEC, RUNTIME, SECIT);
  fflush();
}
    
