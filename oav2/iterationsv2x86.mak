#==============================================================================
#$RCSfile: iterationsv2x86.mak,v $
#
#   DESC : Set iterations for each benchmark
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

DEFAULT	=	DEFAULT
# For initial debugging, you can lower the iterations.
#DEFAULT    = 2

empty			=	$(DEFAULT)
bezierv2fixeddata1	=	$(DEFAULT)
bezierv2floatdata1	=	$(DEFAULT)
bezierv2fixeddata2	=	$(DEFAULT)
bezierv2floatdata2	=	$(DEFAULT)
bezierv2fixeddata3	=	$(DEFAULT)
bezierv2floatdata3	=	$(DEFAULT)
bezierv2fixeddata4	=	$(DEFAULT)
bezierv2floatdata4	=	$(DEFAULT)
ditherv2data1	=	$(DEFAULT)
ditherv2data2	=	$(DEFAULT)
ditherv2data3	=	$(DEFAULT)
ditherv2data4	=	$(DEFAULT)
ditherv2data5	=	$(DEFAULT)
ditherv2data6	=	$(DEFAULT)
ditherv2data7	=	$(DEFAULT)
ditherv2data8	=	$(DEFAULT)
ditherv2data9	=	$(DEFAULT)
ditherv2data10	=	$(DEFAULT)
ditherv2data11	=	$(DEFAULT)
rotatev2data1	=	$(DEFAULT)
rotatev2data2	=	$(DEFAULT)
rotatev2data3	=	$(DEFAULT)
rotatev2data4	=	$(DEFAULT)
rotatev2data5	=	$(DEFAULT)
rotatev2data6	=	$(DEFAULT)
rotatev2data7	=	$(DEFAULT)
rotatev2data8	=	$(DEFAULT)
rotatev2data9	=	$(DEFAULT)
rotatev2data10	=	$(DEFAULT)
rotatev2data11	=	$(DEFAULT)
textv2data1		=	$(DEFAULT)
textv2data2		=	$(DEFAULT)
textv2data3		=	$(DEFAULT)
textv2data4		=	$(DEFAULT)
gs8 			=	$(DEFAULT)
ghostpcl 		=	$(DEFAULT)

#
# Benchmark specific defines used in depgen files are placed below.
#

# Set the libjasper source directory.
JASPERSRCDIR=jasper
JASSRC=$(JASPERSRCDIR)/src/libjasper
# jpeglib.h from gs8/include
JASINCS= \
	$(CINCD)gs8/${JASSRC}/include \
	$(CINCD)gs8/${JASSRC}/jpc \
	$(CINCD)gs8/${JASSRC}/jp2 \
	$(CINCD)gs8/include

JASOPTS= \
	$(CDEFN)EXCLUDE_BMP_SUPPORT=1 \
	$(CDEFN)EXCLUDE_JPG_SUPPORT=1 \
	$(CDEFN)EXCLUDE_MIF_SUPPORT=1 \
	$(CDEFN)EXCLUDE_PGX_SUPPORT=1 \
	$(CDEFN)EXCLUDE_PNM_SUPPORT=1 \
	$(CDEFN)EXCLUDE_RAS_SUPPORT=1 \
	$(CDEFN)EXCLUDE_PNG_SUPPORT=1

# MSVC, eVC
ifeq ($(TOOLCHAIN),vc)
JASOPTS += $(CDEFN)JAS_WIN_MSVC_BUILD
endif

# MSVC: ..\include,..\icclib,..\ijs,..\jpeg,..\jbig2dec,..\lib,..\libpng,..\src,..\zlib
GSINCS	= \
	$(CINCD)gs8/preconfig \
	$(CINCD)gs8/include \
	$(CINCD)gs8/icclib \
	$(CINCD)gs8/ijs \
	$(CINCD)gs8/jpeg \
	$(CINCD)gs8/jbig2dec \
	$(CINCD)gs8/lib \
	$(CINCD)gs8/libpng \
	$(CINCD)gs8/src \
	$(CINCD)gs8/zlib \
	$(CINCD)gs8 \
	$(CINCD).


