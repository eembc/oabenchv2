#!/bin/sh
# $Id: eembc.sh,v 1.3 2004/07/09 18:25:10 rick Exp $
# Rick Foos, ECL, LLC.
#
# Develoment testing only. 
# This runs the Ghostscript supplied autogen.sh with EEMBC options.
#
# A seperate makefile is created. type make, and the binary will be
# in the bin directory. The autoconf generated configuration files are
# in the obj directory. For EEMBC builds, the include directory has a 
# similar set of files manually modified. 
#
# NOTE: The base configuration of jaspter must be done from the source base
# to eliminate undefined ulong errors in the build. The release has a
# pre-defined configuration for this. 
# cd jasper-1.701.0;sh configure --without-x
#
# NOTE: the build process has been modified to link in the test harness library.
# for testing. You will need to build this with the EEMBC makefile before
# linking. 
# The main program entry point is in src/stub_autoconf.c
# the main-> gs_main program is in src/gs.c
#
# NOTE: Cross compilation won't be supported (very well) until Autoconf 3.0.
# To build this cross, you must set both host and CFLAGS to reflect the target
# and the options to bring in the startup files.
# Example: ./configure --host=powerpc-eabi CFLAGS='-msim -mbig -mcpu=440'
# At this point, note that thconfig options must also be included for
# data types defined in the harness.
#AUTOCONF_DEFINES = \
#	-DHAVE_DIRENT_H=0 \
#	-DHAVE_STDINT_H=0 \
#	-DHAVE_INTTYPES_H=0 \
#	-DHAVE_TIME=0 \
#	-DNEED_LINK=1 \
#	-DHAVE_STRUCT_STAT_ST_BLKSIZE=0
#
# This is for COMPILE, link requires more work on library path overrides.
# Cross compiler example for autogen
#./autogen.sh --with-toolchain=gccppc --without-x --without-ijs --with-jasper --with-jbig2dec --disable-compile-inits --host=powerpc-eabi CFLAGS='-msim -mbig -mcpu=440 -DHAVE_DIRENT_H=0 -DHAVE_STDINT_H=0 -DHAVE_INTTYPES_H=0 -DHAVE_TIME=0 -DNEED_LINK=1 -DHAVE_STRUCT_STAT_ST_BLKSIZE=0'
# Cross compiler example for configure
#./configure --with-toolchain=gccppc --without-x --without-ijs --with-jasper --with-jbig2dec --disable-compile-inits --host=powerpc-eabi CFLAGS='-msim -mbig -mcpu=440 -DHAVE_DIRENT_H=0 -DHAVE_STDINT_H=0 -DHAVE_INTTYPES_H=0 -DHAVE_TIME=0 -DNEED_LINK=1 -DHAVE_STRUCT_STAT_ST_BLKSIZE=0'

./autogen.sh --without-x --without-ijs --without-jasper --without-jbig2dec --enable-compile-inits

