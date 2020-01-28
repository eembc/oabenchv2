#==============================================================================
#$RCSfile: makerule.mak,v $
#
#   DESC : Makerule build script
#
# AUTHOR : Rick Foos, ECL, LLC
#
#  EEMBC : Technical Advisory Group (TechTAG)
#
#    CVS : $Revision: 1.8 $
#------------------------------------------------------------------------------
# Copyright (c) 1998-2005 by the EDN Embedded Microprocessor 
# Benchmark Consortium (EEMBC), Inc. All Rights Reserved.
#==============================================================================

# This makefile handles all rules which use the makerule utility.
# harness rules cover the test harnesses.
# host rules cover optional host executables.

MAKERULE=$(PERL) $(ROOT)/util/perl/makerule.pl -cmd 
HARNESSDIRS=th_lite
ROOT?=..

cleanrule :
	@rm -f targets_*.mak;\
	for i in ${HARNESSDIRS}; do \
	echo "... Removing build dependencies from $(ROOT)/$$i";\
	find $(ROOT)/$$i -name harness.mak -exec rm -f {} \; ;\
	done

harness: targets$(VER)_$(TARGETS).mak $(TH)/$(TARGETS)/harness.mak

targets$(VER)_$(TARGETS).mak:	depgen$(VER)_$(TARGETS).cml $(ROOT)/util/perl/makerule.pl
	$(MAKERULE) depgen$(VER)_$(TARGETS).cml 

$(TH)/$(TARGETS)/harness.mak:	$(TH)/$(TARGETS)/depgen.cml $(ROOT)/util/perl/makerule.pl
	$(MAKERULE) $(TH)/$(TARGETS)/depgen.cml 

cleanhost:
	rm -f ${HOSTFILE}

host: ${HOSTFILE}


# note: we use two if statements so that we do nothing if !dependency check
# note: -nt test does not work on all shells, but it is the only test available
#       for scripted dependency checks.
.PHONY:${HOSTFILE}
${HOSTFILE}: $(ROOT)/util/perl/makerule.pl
	@if [ -f depgen${VER}_host.cml ]; then \
	echo "Checking ${HOSTFILE}...";\
	if [ depgen${VER}_host.cml -nt ${HOSTFILE} -o ! -f ${HOSTFILE} ]; then \
	echo "Building ${HOSTFILE}...";\
	${MAKERULE} depgen${VER}_host.cml ;\
	fi;\
	else \
	echo "# No Host utilities for this run." >${HOSTFILE};\
	fi

	