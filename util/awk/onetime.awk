# ============================================================================
#
# Copyright (C) EEMBC(R) All Rights Reserved
#
# This software is licensed with an Acceptable Use Agreement under Apache 2.0.
# Please refer to the license file (LICENSE.md) included with this code.
#
# ============================================================================

# This is for those who capture all benchmarks to one file...

# NF -1 strips th regular ^Z or ^M character after algorithm.

#cat "/util/titletime.txt"

BEGIN{error=0;CRC="";ECRC="";FirstLine=0}
(1==1) {

  if (FirstLine==0) {
	FirstLine = 1;
	printf("Subcommittee	Benchmark	Dataset	Error?	Description	Expected CRC	Actual CRC	Iterations	Duration	Iterations/Sec	Run Time	Time/Iter\n\n");
  }
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
  if (($2=="Iterations") && ($3=="=")) { IT = $4;  }
  if (($2=="Target") && ($3=="Duration")) { DU = $5; }
  if (($3=="CRC") && ($4=="=")) { CRC = $5; }
  if (($2=="Time") && ($3=="/") && ($4=="Iter")) { SECIT = $6; }

  if (($2=="Iterations/Sec") && ($3=="=")) { ITSEC = $4; }
  if (($2=="Total") && ($3=="Run") && ($4=="Time")) { RUNTIME = $6; }
  if (($2=="Failure:") && ($4=="CRC") && ($6=="Expected")) { ECRC = $8; }
# DONE replaced by Failure
  if ($2=="Failure:") { error++; }
  if ($1=="ERROR")    { error++; }

# Need Check for Data Set
  if (($2 == "Data") && ($3 == "Set")) { DATASET = $5; }
  if (($1 == "WARNING:") && ($3 == "output")) { DATASET = $6; }
  if (($2 == "Datagram") && ($3 == "buffer") && ($4 == "size")) {
	if ($6 == "0x0080000") { DATASET = "512K"; }
	if ($6 == "0x0100000") { DATASET = "1MEG"; }
	if ($6 == "0x0200000") { DATASET = "2MEG"; }
	if ($6 == "0x0400000") { DATASET = "4MEG"; }
  }
  if ((DATASET != "") && (substr(DATASET,1,4) != "DATA")) {
# This will be a big long series of if/elseif's
	if (DATASET == "xpulseiOutput.dat" ) DATASET = "DATA1";
		else if (DATASET == "xsineiOutput.dat" ) DATASET = "DATA2";
		else if (DATASET == "xspeechiOutput.dat" ) DATASET = "DATA3";
		else if (DATASET == "xk5r2diOutput.dat" ) DATASET = "DATA1";
		else if (DATASET == "xk4r2diOutput.dat" ) DATASET = "DATA2";
		else if (DATASET == "xk3r2diOutput.dat" ) DATASET = "DATA3";
		else if (DATASET == "xtypsnriOut.dat" ) DATASET = "DATA2";
		else if (DATASET == "xstepsnriOut.dat" ) DATASET = "DATA3";
		else if (DATASET == "xpentsnriOut.dat" ) DATASET = "DATA6";
		else if (DATASET == "xtpulse256iOutput.dat" ) DATASET = "DATA1";
		else if (DATASET == "xspn256iOutput.dat" ) DATASET = "DATA2";
		else if (DATASET == "xsine256iOutput.dat" ) DATASET = "DATA3";
		else if (DATASET == "gettiOutput.dat" ) DATASET = "DATA1";
		else if (DATASET == "toggleiOutput.dat" ) DATASET = "DATA2";
		else if (DATASET == "onesiOutput.dat" ) DATASET = "DATA3";
		else if (DATASET == "zerosiOutput.dat" ) DATASET = "DATA4";
		else if (substr(DATASET,1,7) == "Rose256" ) DATASET = "DATA1";
		else if (substr(DATASET,1,5) == "goose" ) DATASET = "DATA2";
		else if (substr(DATASET,1,5) == "Goose" ) DATASET = "DATA2";
		else if (substr(DATASET,1,19) == "EEMBCGroupShotMiami" ) DATASET = "DATA3";
		else if (substr(DATASET,1,12) == "DavidAndDogs" ) DATASET = "DATA4";
		else if (substr(DATASET,1,9) == "DragonFly" ) DATASET = "DATA5";
		else if (substr(DATASET,1,15) == "MarsFormerLakes" ) DATASET = "DATA6";
		else if (substr(DATASET,1,7) == "Galileo" ) DATASET = "DATA7";
		else if (substr(DATASET,1,8) == "Mandrake" ) DATASET = "DATA1";
		else if (substr(DATASET,1,7) == "graphic" ) DATASET = "DATA1";
		else if (substr(DATASET,1,8) == "marsface" ) DATASET = "DATA2";
		else if (substr(DATASET,1,9) == "railgrind" ) DATASET = "DATA3";
		else if (substr(DATASET,1,4) == "sign" ) DATASET = "DATA4";
		else if (substr(DATASET,1,4) == "zoom" ) DATASET = "DATA5";
		else if (DATASET == "libmpeg/graphic.mpeg" ) DATASET = "DATA1";
		else if (DATASET  == "libmpeg/marsface.mpeg" ) DATASET = "DATA2";
		else if (DATASET  == "libmpeg/railgrind.mpeg" ) DATASET = "DATA3";
		else if (DATASET == "libmpeg/sign.mpeg" ) DATASET = "DATA4";
		else if (DATASET  == "libmpeg/zoom.mpeg" ) DATASET = "DATA5";
		else if (DATASET == "libmp3/jupiter.mp3" ) DATASET = "DATA1";
		else if (DATASET  == "libmp3/music128stereo.mp3" ) DATASET = "DATA2";
		else if (DATASET  == "libmp3/music48mono.mp3" ) DATASET = "DATA3";
		else if (DATASET == "libmp3/music48_128stereo.mp3" ) DATASET = "DATA4";
		else if (DATASET  == "libmp3/music64stereo.mp3" ) DATASET = "DATA5";
  }

  if ($2=="ID:") { 
	# Print out the benchmark
	if (CRC != "")
	  {
	    CRC = "0x" CRC;
	    if (ECRC == ""){ECRC=CRC;}
	    else {ECRC = "0x" ECRC;error++;}
		if (IT==0) {error++;}
		if ( error != 0 || BM=="") {TERROR = "ERROR"}
#	} 
#		getline;
		  numbenchmarks++;
	  printf ("%s\t%-12s\t%-11s\t%s\t%-30s\t%-6s\t%-6s\t%d\t%d\t%f\t%f\t%f\n", 
	  IDSUB, IDBM, DATASET, TERROR, BM, ECRC, CRC, IT, DU, ITSEC, RUNTIME, SECIT);
#	} else {
#		printf ("\n");
	}
		error=0;CRC="";ECRC="";ITSEC=0;IT=0;TERROR="";DATASET="";BM="";IDSUB="";IDBM="";DU=0;RUNTIME=0;SECIT=0;
#	  }
#	  DU=DU+0;
	  fflush();
  }
next;
}
  
END {
print "*** Number of benchmarks processed:" numbenchmarks > "/dev/stderr";
}
    
