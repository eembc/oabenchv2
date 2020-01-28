#==============================================================================
#$RCSfile: makefile,v $
#
#   DESC : Utility Level Makefile
#
# AUTHOR : Rick Foos, ECL, LLC
#
#  EEMBC : Technical Advisory Group (TechTAG)
#
#    CVS : $Revision: 1.3 $
#------------------------------------------------------------------------------
# Copyright (c) 1998-2005 by the EDN Embedded Microprocessor 
# Benchmark Consortium (EEMBC), Inc. All Rights Reserved.
#==============================================================================

CC		= gcc
CINCS	= 
# You need to remove this for unix.
EXE		= .exe
# WARNING: we build straight to EXE. 
# Compile for Normal Run
CFLAGS	= -Wall -O3
CCC		= $(CC) $(CFLAGS) $(CINCS)  

# Compile for Debugger
CFLAGSD	= -g -Wall -O0
CCD		= $(CC) $(CFLAGSD) $(CINCS) 

# Select Compile for Normal Run, or Compile for Debug
COM		= $(CCC)

PROGRAMS=\
	bin/cheader$(EXE) \
	bin/uudecode$(EXE) \
	bin/uuencode$(EXE) \
	bin/swap$(EXE) \
	bin/psnr$(EXE)

all: bin psnr/Makefile ${PROGRAMS}

clean:
	rm -f $(PROGRAMS)
	rm -f  c/*.o
	make -C psnr clean

bin/psnr$(EXE):
	make -C psnr install

bin:
	mkdir bin

psnr/Makefile: psnr/autoconf.sh
	[ -x psnr/autoconf.sh ] || chmod +x psnr/autoconf.sh;\
	(cd psnr;./autoconf.sh)

getopt_SOURCES=\
	c/win32/getopt.c \
	c/win32/getopt1.c

getopt_INC=\
	-Ic -Ic/win32

bin/cheader$(EXE):	c/cheader.c
	$(COM) -obin/cheader$(EXE) c/cheader.c

bin/swap$(EXE):	c/swap.c
	$(COM) -obin/swap$(EXE) c/swap.c

bin/uudecode$(EXE):	c/uudecode.c ${getopt_SOURCES}
	$(COM) -obin/uudecode$(EXE) ${getopt_INC} -DHAVE_CONFIG_H c/uudecode.c ${getopt_SOURCES}

bin/uuencode$(EXE):	c/uuencode.c ${getopt_SOURCES}
	$(COM) -obin/uuencode$(EXE) ${getopt_INC} -DHAVE_CONFIG_H c/uuencode.c ${getopt_SOURCES}


