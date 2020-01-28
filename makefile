#==============================================================================
#$RCSfile: $(MAKE)file,v $
#
#   DESC : Make all app
#
# AUTHOR : Rick Foos, ECL, LLC 
#
#    CVS : $Revision: 1.56 $
#------------------------------------------------------------------------------
# Copyright (c) 1998-2005 by the EDN Embedded Microprocessor 
# Benchmark Consortium (EEMBC), Inc. All Rights Reserved.
#==============================================================================
# Available commands:
#
# all - th regular, th lite build and run
# all-vers - all for V1 and V2 Benchmarks
# all-lite - th lite build and run
# all-816 - th 816 build and run
# all-regular - th regular build and run
# rerun - run and results for lite and regular
# clean - clean lite and regular for all toolchains
# cleanlogs - clean lite and regular log files for all toolchains
# distclean - clean, and delete $(MAKE)rule dependency files.
# harness - build all $(MAKE)rule generated target files.
# count - count source code lines, and build summary log files.
# profile - Build and run with profiling (gcc gprof only from ECL)

ifndef RELEASETAG
RELEASETAG=ORC8
endif

# Override to v2 from command line ($(MAKE) VER=v2)
#vers=" " "v2"
VER=v2
ver=v2
vers="v2"
harnesses=$(THLITE)

# Automatic Override from toolchain.mak
PLATFORM=x86
TLOGTYP=_time
SLOGTYP=_size
PLOGTYP=_psnr
CLOGTYP=_count
THLITE=_lite
TH816=_816
ROOT=..
TCDIR=util/$(MAKE)
PERL:=`which perl`
AWK:=`which gawk`
SCLC="$(PERL) $(ROOT)/util/perl/sclc -ignore -recurse "
LOGTAG="`date`"  
DATESTAMP:=`date +%y_%m_%0d_%0l_%M_%S`
ETC_STAMP:=`date +%y_%j`

ifdef TOOLCHAIN
tchain=$(TOOLCHAIN)
else
tchain=`ls $(TCDIR)/*.mak | sed -e "s|.*/\([^\.]*\).*|\1|"`
endif

app=oav2

ifdef PGOINI
	EXTRA_MAKE_OPT += TRAINING=yes 
endif
ifdef PGOUSE
	FAST=1
	EXTRA_MAKE_OPT += USEPGO=yes EXTRA_TARGETS_S=cleanobjs
endif
ifdef FAST
	EXTRA_MAKE_OPT += CMDLINE_CHEADER=skip 
endif
ifndef OAFULL
	EXTRA_MAKE_OPT += OAMARKONLY=1
else
	EXTRA_MAKE_OPT += OAMARKONLY=0
endif
# Constants used in Makefile

all: all-lite

.PHONY:all-regular
all-regular:
	@echo "This target is no longer supported"

.PHONY:all-lite
all-lite: cheader
	@echo "Make ALL TH Lite by Toolchain,Application...";\
	for j in $(tchain); do \
	for i in $(app); do \
	if [ -f "$$i/dirs$(VER)$(PLATFORM).mak" ]; then \
	(cd $$i && echo EXTRA FLAGS:$(STAGE) $(EXTRA_MAKE_OPT) && $(MAKE) TCDIR=$(ROOT)/$(TCDIR) VER=$(VER) TOOLCHAIN=$$j LITE=${THLITE} $(STAGE) $(EXTRA_MAKE_OPT) );\
	tlog=$$j"$(TLOGTYP)"$(VER)${THLITE}.log;\
	slog=$$j"$(SLOGTYP)"$(VER)${THLITE}.log;\
	plog=$$j"$(PLOGTYP)"$(VER)${THLITE}.log;\
	[ ! -f "$$tlog" ] && cat util/awk/titletime.txt >$$tlog;\
	[   -f "$$i/$$tlog" ] && echo $(LOGTAG) >> $$tlog && cat $$i/$$tlog >>$$tlog;\
	[ ! -f "$$slog" ] && cat util/awk/titlesize.txt >$$slog;\
	[   -f "$$i/$$slog" ] && echo $(LOGTAG) >> $$slog && cat $$i/$$slog >>$$slog;\
	[ ! -f "$$plog" ] && cat util/awk/titlepsnr.txt >$$plog;\
	[   -f "$$i/$$plog" ] && echo $(LOGTAG) >> $$plog && cat $$i/$$plog >>$$plog;\
	fi; \
	done; \
	done;\
	echo "...$@ done."

# ETC only. Distributes common routines to Applications.
new$(MAKE)file_EXCLUDE=java
.PHONY:new$(MAKE)file
new$(MAKE)file:
	@echo "Distributing new $(MAKE)files...";\
	for i in $(app); do \
	[ "$$i" = "${new$(MAKE)file_EXCLUDE}" ] && continue;\
	[ -d "$$i" ] && echo "   $$i" && cp -f util/$(MAKE)/$(MAKE)file $$i/$(MAKE)file;\
	done;\
	echo "...$@ done."

#
# This section executes commands once per Application.
# Preambles, execution, and Post Processing
#

# Preamble: Builds Cheader executable if needed
# Removed -x check. It was missing old cheader executables with new code.
# happens to also build uudecode, and psnr
cheader ::
	@echo -n "Check cheader build...";\
	(cd util && $(MAKE));\
	[ ! -x "./util/shell/cinit.sh" ] && chmod +x "./util/shell/cinit.sh";\
	echo "done."

ifndef FAST
.PHONY:cheader count
cheader count ::
	@echo "Make $@ by Version ${ver}...";\
	for i in $(app); do \
	([ $$i == "java" ] || [ ! -f "$$i/dirs$(VER)$(PLATFORM).mak" ]) && continue;\
	(cd $$i && $(MAKE) TCDIR=$(ROOT)/$(TCDIR) VER=$(VER) $@);\
	done;\
	echo "...$@ done."
endif

# Post Processing: Count (Had to use sed to $(MAKE) the filename variable work.)
count ::
	@echo -n "Building count${VER}.log...";\
	cat util/awk/titlecount.txt >count${VER}.log;\
	cat util/awk/titlecount.txt >countsum${VER}.log;\
	for i in $(app); do \
	([ $$i == "java" ] || [ ! -f "$$i/dirs$(VER)$(PLATFORM).mak" ]) && continue;\
	clog=`echo "$$i/$$i ${CLOGTYP}${VER}.log" | sed -e "s| ||"`;\
	[ -f "$$clog" ] && cat "$$clog" >>count${VER}.log && ${AWK} -f util/awk/countsum.awk BMARK=$$i $$clog >>countsum${VER}.log;\
	done;\
	echo "done."

#
# This section passes commands to each application for each toolchain.
#
.PHONY:clean distclean harness rerun cleanlogs
clean distclean harness cleanlogs::
	@echo "Make $@ by version toolchain,application...";\
	for l in ${vers}; do \
	for j in $(tchain); do \
	for i in $(app); do \
	dirplat=`echo "$$i/dirs$$l $(PLATFORM).mak" | sed -e "s| ||g"`;\
	if [ -d "$$i" ] && [ -f "$$dirplat" ]; then \
	 (cd $$i && $(MAKE) TCDIR=$(ROOT)/$(TCDIR) VER=$$l TOOLCHAIN=$$j LITE=$(THLITE) $@);\
	fi;\
	done;\
	done;\
	done;\
	echo "...$@ done."

rerun: cleanlogs all

distclean:: clean
	@echo "Clean misc files"
	@rm -f *.log
	(cd util && $(MAKE) clean)	

.PHONY:release
release: distclean release-harness
	@for suite in $(app); do \
		if [[ -d $$suite ]] ; then \
			echo "Creating release for $${suite}_$(ETC_STAMP)" ;\
			for dname in $$suite/*; do \
				[[ -d "$$dname" ]] && [[ ! "$$dname" =~ .svn ]] &&  \
				 zip -r release/$${suite}_$(ETC_STAMP).zip $$dname -x \*.svn\* > /dev/null; \
				[[ ! -d "$$dname" ]] && \
				 zip release/$${suite}_$(ETC_STAMP).zip $$dname -x \*.svn\* > /dev/null; \
			done ;\
		fi; \
		true ;\
	done

.PHONY:release-harness
release-harness:
	@[[ -d release ]] || mkdir release
	@echo "Creating harness release harness_$(ETC_STAMP)"
	@zip -r release/harness_$(ETC_STAMP).zip th_lite util doc -x \*.svn\*  > /dev/null
	@zip release/harness_$(ETC_STAMP).zip make* *.txt > /dev/null
