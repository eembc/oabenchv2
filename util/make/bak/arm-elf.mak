#==============================================================================
#$RCSfile: arm-elf.mak,v $
#
#   DESC : GCC Tool Definition, Cross Compile and Run
#
# AUTHOR : Rick Foos, ECL, LLC
#
#  EEMBC : Technical Advisory Group (TechTAG)
#
#    CVS : $Revision: 1.1 $
#------------------------------------------------------------------------------
# Copyright (c) 1998-2005 by the EDN Embedded Microprocessor 
# Benchmark Consortium (EEMBC), Inc. All Rights Reserved.
#==============================================================================
# For information on the GNU Win32 project (Cygwin), and gcc
#
# http://www.cygwin.com, http://gcc.gnu.org

# RUN OPTIONS SECTION
# Build or run options (i.e. profiling, simulation)

# Enable profiling with 'yes'. All other strings disable profiling.
ifndef (DO_PROFILE)
DO_PROFILE=no
endif
ifndef (DO_VALGRIND)
DO_VALGRIND=no
endif

# ARCHITECTURE SECTION
# Any specific options (i.e. cpu, fpu)

# SYSTEM ENVIRONMENT SECTION
# CROSS COMPILER
program_transform_name = s,^,arm-elf-,;

# Tools Root Directory
#TOOLS	= /usr/local
# Location for Linux gnuarm tools (gcc -print-search-dirs)
TOOLS	= /srv/shared/gnuarm/gnuarm-3.4.3
# For Solaris
#TOOLS	= /usr/local
# (A shell which supports [ file1 -nt file2 ] for office/gs01)
SHELL	= /bin/bash

# Tools Executables, Output File Flag and Output File Types

# NOTE:	Spacing between option and values can be compiler dependant.
#		The following is a trick to ensure that a space follows the -o flag. 
#		Do not remove the line continuation backslash or the following blank
#		line.
#		OBJOUT = -o \

CC		= $(TOOLS)/bin/arm-elf-gcc
OBJOUT	= -o
COBJT	= -c
CINCD	= -I
CDEFN	= -D
CUDEFN	= -U
OBJ		= .o

AS		= $(TOOLS)/bin/arm-elf-as

LD		= $(TOOLS)/bin/arm-elf-gcc
EXEOUT	= -o
EXE		= .exe

AR		= $(TOOLS)/bin/arm-elf-ar
LIBTYPE	= .a
LIBOUT	= 

# COMPILER SECTION

# You may need to override the Environment variable INCLUDE.
# INCLUDE is used by most compilers, and should not 
# be passed to the compiler in the makefile.
INCLUDE = $(TOOLS)/include

# -c             compile but do not link
# -o             specify the output file name
# -march=i486    generate code for the intel 486
# -O0			 Do not optimize
# -O2			 Optimize for speed

# Define your non-default compiler capabilities here for thconfig.h
# arm-elf 4.01 removes these restrictions:
#	$(CDEFN)HAVE_TIME=0 \
#
AUTOCONF_DEFINES = \
	$(CDEFN)HAVE_DIRENT_H=0 \
	$(CDEFN)HAVE_STDINT_H=0 \
	$(CDEFN)HAVE_INTTYPES_H=0 \
	$(CDEFN)NEED_LINK=1 \
	$(CDEFN)HAVE_STRUCT_STAT_ST_BLKSIZE=0

COMPILER_FLAGS	= -O2     $(CDEFN)NDEBUG $(AUTOCONF_DEFINES)
COMPILER_NOOPT	= -O0     $(CDEFN)NDEBUG $(AUTOCONF_DEFINES)
COMPILER_DEBUG	= -O0 -g  $(AUTOCONF_DEFINES)

# -ansi          Support all ANSI standard C programs. 
#                Turns off most of the GNU extensions
# -pedantic      Issue all the warnings demanded by strict ANSI standard C;
#                reject all programs that use forbidden extensions. 
# -fno-asm       do not allow the 'asm' keyword.  Eg. no inline asembly
# -fsigned-char  use signed characters

WARNING_OPTIONS	=	\
	-ansi -pedantic -Wcomment -Wparentheses -Wreturn-type -Wswitch \
	-Wunused -Wsign-compare -Wimplicit -Wreturn-type	\
	-Wshadow -Wpointer-arith -Wwrite-strings \
	-Wsign-compare -Wstrict-prototypes -Wmissing-prototypes	\
	-Wmissing-declarations -Wno-long-long \
	-fno-asm -fsigned-char -fno-builtin -fno-common

# Additional include files not in dependancies or system include.
COMPILER_INCLUDES =
# Override harness thincs, make sure you take care of the harness paths
#THINCS=

# Optional: Passed to compiler, here or in makefile to override THCFG defines.
#COMPILER_DEFINES = 
# For Solaris, and Big Endian Targets, using 0/1 also allows support for
# files that do not have EEMBC includes. (Don't quote the string)
#COMPILER_DEFINES = -DEE_BIG_ENDIAN=1 -DEE_LITTLE_ENDIAN=0 

# ASSEMBLER SECTION

ASSEMBLER_FLAGS		= 
ASSEMBLER_INCLUDES	=

# LINKER SECTION
# -lm is optional. Some linkers do not include math library by default.
LINKER_FLAGS	= -lm -msim
LINKER_INCLUDES	=
# Some linkers do not re-scan libraries, and require some libraries 
# to be placed last on the command line to resolve references.
LINKER_LAST 	= -lm

# LIBRARIAN SECTION
LIBRARY_FLAGS	= scr

# SIZE SECTION
SIZE	= $(TOOLS)/bin/arm-elf-size
SIZE_FLAGS		= 
AWKSZ			= gcc
AWKDIR			= awk

# IMAGE SECTION
IMAGE			= 
IM_FLAGS		= 
IMG				= 

# CONTROL SECTION

ifeq ($(DO_PROFILE),yes)
# Make PG overrides
OBJBUILD	= $(TOOLCHAIN)/pgobj$(LITE)
BINBUILD	= $(OBJBUILD)
RESULTS		= $(TOOLCHAIN)/pgresults$(LITE)

COMPILER_DEFINES += -pg -DDO_PROFILE=yes
LINKER_FLAGS += -pg
RUN_FLAGS		= $(RESULTS)
RUN				= $(TCDIR)/gprof.sh
else
ifeq ($(DO_VALGRIND),yes)
COMPILER_DEFINES += -g
RUN_FLAGS		= 
RUN				= valgrind --logfile-fd=1 --tool=memcheck -v --leak-check=yes
else
RUN_FLAGS		=

RUN				= $(TCDIR)/gdb.sh $(TOOLS)/bin/arm-elf-gdb
endif
endif

# Add any run output arguments (after stdout redirection)
#RUN_LASTOUT=2>&1
RUN_LASTOUT=

# Add command line arguments to the program or shell script.
# For simulators, you can reduce the iterations here.
CMDLINE			+= -iter 1
CMDLINE_LITE	+= -iter 1


# Describes how much to build. To compile only, "mkdir targets"
#ALL_TARGETS		= mkdir targets 
ALL_TARGETS		= mkdir targets run results

# Optional specific files for specialized run and results
PLATFORM=x86

# Optional re-use of dependency files generated by makerule.pl
TARGETS			= gcc
