#==============================================================================
#$RCSfile: dirsv2x86.mak,v $
#
#   DESC : Make Directories for benchmarks
#
# AUTHOR : Rick Foos, ECL, LLC
#
#  EEMBC : Office
#
#    CVS : $Revision: 1.27 $
#------------------------------------------------------------------------------
# Copyright (c) 1998-2005 by the EDN Embedded Microprocessor 
# Benchmark Consortium (EEMBC), Inc. All Rights Reserved.
#==============================================================================

#
# Benchmark names. Each is a unique object file directory, and executable name.
#
bmarksoamark=\
	empty \
	ditherv2data2 ditherv2data3 ditherv2data4 \
	ditherv2data5 ditherv2data6 ditherv2data7 ditherv2data8 \
	ditherv2data9 ditherv2data10 ditherv2data11 \
	rotatev2data2 rotatev2data3 rotatev2data4 \
	rotatev2data5 rotatev2data6 rotatev2data7 rotatev2data8 \
	rotatev2data9 rotatev2data10 rotatev2data11 \
	bezierv2fixeddata2 bezierv2floatdata2 \
	bezierv2fixeddata3 bezierv2floatdata3 \
	bezierv2fixeddata4 bezierv2floatdata4 \
	textv2data2 textv2data3 textv2data4 

bmarkspgo=\
	ditherv2data1 rotatev2data1 bezierv2fixeddata1 bezierv2floatdata1 textv2data1

ifdef TRAINING
 bmarks = $(bmarkspgo)
else
 bmarks = $(bmarksoamark)
endif

ifndef OAMARKONLY
 bmarks += gs8
endif

#
# Benchmark Extra Directories.
# Define object file directories for libraries and utilities.
#
bmextradirs=\
	gs8/libjpeg gs8/libjasper gs8/libps gs8/libfonts gs8/libresource gs8/libjbig2 gs8/libz \
	gs8/libpng gs8/libicc gs8/libexamples gs8/libijs libpgm libtxt libbez psnr bezierv2fixed \
	rotatev2 ditherv2 textv2 bezierv2float

#
# Results Extra Directories. Used for special run and results processing.
#
rsextradirs=\
	gs-output 

#
# Count section. These are the only variables, the rest is constant.
# Needs a Physical source file for the dependencies to work.
# NOTE: Keep COUNTLOGS in sync with dirsXX.mak bmarksrc
#
bmarksrc=\
	gs8/src gs8/jpeg gs8/libps gs8/libfonts gs8/libresource gs8/jbig2dec gs8/zlib \
	gs8/libpng gs8/icclib gs8/libexamples ditherv2 libpgm libtxt libbez

COUNTLOGS = \
	gs8-src.count.log \
	gs8-jpeg.count.log \
	gs8-libps.count.log \
	gs8-libfonts.count.log \
	gs8-libresource.count.log \
	gs8-jbig2dec.count.log \
	gs8-zlib.count.log \
	gs8-libpng.count.log \
	gs8-icclib.count.log \
	libpgm.count.log \
	libtxt.count.log \
	libbez.count.log \
	bezierv2.count.log	\
	rotatev2.count.log	\
	textv2.count.log

