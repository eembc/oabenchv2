#==============================================================================
# Build commands and flags for ARM RVDS 3.0
# * These flags are not optimized for performance.

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

# Tools Root Directory

TOOLS	= /c/dev/ARM/RVCT/Programs/3.0/441/win_32-pentium/
# For Solaris
#TOOLS	= /usr/local
# For Solaris
# (A shell which supports [ file1 -nt file2 ] for office, consumer)
#SHELL	= /bin/bash

# Tools Executables, Output File Flag and Output File Types

# NOTE:	Spacing between option and values can be compiler dependant.
#		The following is a trick to ensure that a space follows the -o flag. 
#		Do not remove the line continuation backslash or the following blank
#		line.
#		OBJOUT = -o \

CC		= $(TOOLS)/armcc
# Solaris: /usr/ccs/bin/as requires space after -o passed from gcc.
#OBJOUT = -o \#
OBJOUT	= -o
COBJT	= -c
CINCD	= -I
CDEFN	= -D
CUDEFN	= -U
OBJ		= .o

AS		= $(TOOLS)/armasm

LD		= $(TOOLS)/armlink
EXEOUT	= -o
EXE		= .exe

AR		= $(TOOLS)/armar
LIBTYPE	= .a
LIBOUT	= 

# Some Tool Chains require specific perl version. 
# makefile default setting can be overridden here.
#PERL=`which perl || exit 1`


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
AUTOCONF_DEFINES=  

# Solaris: Remove comments and add these definitions.
#	$(CDEFN)HAVE_INTTYPES_H=1 \
#	$(CDEFN)HAVE_STDINT_H=0


# Makefile COM=$(CCN)
COMPILER_NOOPT	= -O0 $(CDEFN)NDEBUG $(AUTOCONF_DEFINES) --cpu arm9e

# Makefile COM=$(CCD)
COMPILER_DEBUG	= -O0 -g -DDEBUG=1 $(AUTOCONF_DEFINES) --cpu arm9e

# normal compile
COMPILER_OPT = -O2 $(CDEFN)NDEBUG $(AUTOCONF_DEFINES) --cpu arm9e

# Makefile COM=$(CCC)
ifeq ($(DO_PROFILE),yes)
COMPILER_FLAGS	= $(COMPILER_NOOPT)
else
COMPILER_FLAGS	= $(COMPILER_OPT)
endif

# COMPILER OPTIONS THAT MUST BE USED WITH GCC FOR GHOSTSCRIPT EXECUTION.
AVOID_CURDIR_INC=-I-
#	The header files from the preconfig directory HAVE to be read first.
#	If your compiler does not have this option and insists on searching current dir first,
#	use the jpeg/hideincs.sh to remove the default header files.

# MSVC: HAVE_STDINT_H,SHARE_LIBPNG=1,SHARE_JPEG=1,SHARE_ZLIB=1,SHARE_JBIG2=1 
# GCC: Force gcc to -O0 due to bug when optimized code.
GSOPTS=-O0 $(CDEFN)SHARE_LIBPNG=0 $(CDEFN)SHARE_JPEG=0 $(CDEFN)SHARE_ZLIB=0 $(CDEFN)SHARE_JBIG2=0 $(CDEFN)COMPILE_INITS=1 

# -ansi          Support all ANSI standard C programs. 
#                Turns off most of the GNU extensions
# -pedantic      Issue all the warnings demanded by strict ANSI standard C;
#                reject all programs that use forbidden extensions. 
# -fno-asm       do not allow the 'asm' keyword.  Eg. no inline asembly
# -fsigned-char  use signed characters
#WARNING_OPTIONS=\
#	-ansi -pedantic -Wall \
#	-fno-asm -fsigned-char -fno-builtin -fno-common

# Special options for profiling, no inline and inline heuristics.
ifeq ($(DO_PROFILE),yes)
# Add options for GCOV, remove inlining.
WARNING_OPTIONS+=-fprofile-arcs -ftest-coverage \
	-finline-limit=0
endif

# Additional include files not in dependancies or system include.
#COMPILER_INCLUDES =
# Override harness thincs, make sure you take care of the harness paths
#THINCS=

# Optional: Passed to compiler, here or in makefile to override THCFG defines.
#COMPILER_DEFINES += 
# For Solaris, and Big Endian Targets, using 0/1 also allows support for
# files that do not have EEMBC includes. (Don't quote the string)
#COMPILER_DEFINES += -DEE_BIG_ENDIAN=1 -DEE_LITTLE_ENDIAN=0
COMPILER_DEFINES += -DHAVE_DIRENT_H=0 -DUSE_EE_DIRENT=1 -DHAVE_FCNTL_H=0 -DHAVE_SYS_TIMES_H=0 -DHAVE_UNISTD_H=0 -DHAVE_SYS_STAT_H=0 -DHAVE_SYS_TYPES_H=0 -DNEED_SYSTYPES=1 -DTIME_WITH_SYS_TIME=0 -DHAVE_SYS_TIME_H=0 -DNEED_ERRNO_DEFINES=1 -DHAVE_GETPID=0 -DHAVE_GETTIMEOFDAY=0

# ASSEMBLER SECTION

ASSEMBLER_FLAGS		= 
ASSEMBLER_INCLUDES	=

# LINKER SECTION
# -lm is optional. Some linkers (linux gcc) do not include math library by default.
LINKER_FLAGS	= --datacompressor off
#-lm
LINKER_INCLUDES	=
# Some linkers do not re-scan libraries, and require some libraries 
# to be placed last on the command line to resolve references.
LINKER_LAST 	=

# LIBRARIAN SECTION
LIBRARY_FLAGS	= -scr

# SIZE SECTION
SIZE	= size
SIZE_FLAGS		= 
AWKSZ			= $(TOOLCHAIN)
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
LINKER_LAST += -pg -lgcov
RUN_FLAGS		= $(RESULTS)
RUN				= $(TCDIR)/gprof.sh
else
ifeq ($(DO_VALGRIND),yes)
COMPILER_DEFINES += -g
RUN_FLAGS		= 
# Show Reachable blocks --show-reachable=yes
RUN				= valgrind --logfile-fd=1 --tool=memcheck -v --leak-check=yes --show-reachable=yes
else
RUN_FLAGS = -cpu arm9e -e 
RUN = armsd 
endif
endif

# Add any run output arguments (after stdout redirection)
#RUN_LASTOUT=2>&1
RUN_LASTOUT=

# Add command line arguments to the program or shell script.
# For simulators, you can reduce the iterations here.
#CMDLINE		+= -iter 1
#CMDLINE_LITE	+= -iter 1
CMDLINE			+=
CMDLINE_LITE	+=

# Describes how much to build. To compile only, "mkdir targets"
ifeq ($(OAMARKONLY),1)
ALL_TARGETS		= $(EXTRA_TARGETS_S) mkdir targets-oamark2 run-oamark2 results-oamark2 $(EXTRA_TARGETS_F)
else
ALL_TARGETS		= $(EXTRA_TARGETS_S) mkdir targets run results $(EXTRA_TARGETS_F)
endif

ifeq ($(TRAINING),yes)
 COMPILER_FLAGS	+= -DTRAINING=1 -fprofile-generate
 LINKER_FLAGS += -fprofile-generate
endif

ifeq ($(USEPGO),yes)
 COMPILER_FLAGS	+= -fprofile-use
 LINKER_FLAGS += -fprofile-use
endif

# Optional specific files for specialized run and results
PLATFORM=x86

# Optional re-use of dependency files generated by makerule.pl
TARGETS			= gcc

