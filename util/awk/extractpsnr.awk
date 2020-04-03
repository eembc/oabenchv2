# ============================================================================
#
# Copyright (C) EEMBC(R) All Rights Reserved
#
# This software is licensed with an Acceptable Use Agreement under Apache 2.0.
# Please refer to the license file (LICENSE.md) included with this code.
#
# ============================================================================

BEGIN{error=0;rv=0;
GEOMEAN=-1.0;
ARITHMEAN=-1.0;
VARIANCE=-1.0;
MINIMUM=-1.0;
FRAMES=-1;
ZEROFRAMES=-1;
MATCHFRAMES=-1;
}
(1==1) {
# debug
# 	print $0
	if (($1 == "ERROR") || ($1 == "ERROR:") || ($2 == "Failure:"))
	{
# debug
#	print "errs: " $1 $2
		error++;
	}
	if ($0 ~ /^Geometric Mean.*/)  
	{
		rv=split($0,a,",");
		GEOMEAN=a[2];
	}
	if ($0 ~ /^Arithmetic Mean.*/)  
	{
		rv=split($0,a,",");
		ARITHMEAN=a[2];
	}
	if ($0 ~ /^Variance.*/)  
	{
		rv=split($0,a,",");
		VARIANCE=a[2];
	}
	if ($0 ~ /^Minimum.*/)  
	{
		rv=split($0,a,",");
		MINIMUM=a[2];
	}
	if ($0 ~ /^(Frame|Page).*/)  
	{
		rv=split($0,a,",");
		FRAMES=a[2];
	}
	if ($0 ~ /^All Zero.*/)  
	{
		rv=split($0,a,",");
		ZEROFRAMES=a[2];
	}
	if ($0 ~ /^Exact Match.*/)  
	{
		rv=split($0,a,",");
		MATCHFRAMES=a[2];
	}
}

END {
	# Print out the benchmark
	if ( BMARK == "" ) {BMARK = "Benchmark"}
	if (ARITHMEAN == -1.0){error++;}
	if (VARIANCE == -1.0){error++;}
	if (MINIMUM == -1.0){error++;}
	if (FRAMES == -1){error++;}
	if (ZEROFRAMES == -1){error++;}
	if (MATCHFRAMES == -1){error++;}

	if ( error != 0 ) {
	printf ("%-20s\t%d ERROR(s) encountered in psnr processing\n",
	BMARK,error);
	}
	printf ("%-20s\t%f\t%f\t%f\t%d\t%d\t%d\n",
		BMARK, ARITHMEAN, VARIANCE, MINIMUM,
		FRAMES, ZEROFRAMES,MATCHFRAMES);
}
