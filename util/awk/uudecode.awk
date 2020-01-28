#!/usr/local/bin/gawk -f
#==============================================================================
#$RCSfile: uudecode.awk,v $
#
#   DESC : Extract Multiple Uuencoded for uudecode.
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

# @todo: unprocessed lines are being flushed to stdout, next doesn't clear.

# @note SHORT FILE ERROR: It means that uudecode was expecting more
# data, but it wasn't there.  The two biggest reasons for this are: 1. 
# The uuencoded file was sent in several pieces and you only decoded
# the first part.  You'll need to combine the parts first before
# decoding.  2.  The message passed through a BITNET site, which is
# notorious for corrupting uuencoded files.  (because BITNET transports
# tend to delete any trailing spaces in a file, which the uuencoding
# format depends on).


BEGIN{
  numfiles=0;
  shellout="uudecode.sh";
  UUPROG="../util/bin/uudecode.exe";
#  UUPROG="../util/c/win32/uudecode_Debug/uudecode.exe";
#  UUPROG="uudecode";
  print "#!/bin/sh" >shellout;
}
(1==1) {
  if ($0 ~ /^begin .*/)  {
    if ($3 != "") {uuname=$3 ".uue";}
    else          {uuname="xxx.uue";}
    print UUPROG " " uuname >> shellout;
    print "rm -f " uuname >> shellout;
    print $0 > uuname;
    getline;
    numfiles++;
    while ($0 !~ /^end.*/ ) {
      print $0 >> uuname;
      getline;
    }
    # Make caller Avoid short file error.
#    print " " >> uuname;
    print $0 >> uuname;
    getline;
    close(uuname);
  }
  else
    next
}  

END {
close(shellout);
print "*** Number of files processed:" numfiles;
printf ("*** Executing uudecode...");
system("chmod +x "shellout);
system("./"shellout);
print "done";
}
