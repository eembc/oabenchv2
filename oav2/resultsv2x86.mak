#==============================================================================
#$RCSfile: resultsv2x86.mak,v $
#
#   DESC : Extract timing from results\*.log into alltime.log
#
# AUTHOR : Rick Foos, ECL, LLC
#
#  EEMBC : Office
#
#    CVS : $Revision: 1.31 $
#------------------------------------------------------------------------------
# Copyright (c) 1998-2005 by the EDN Embedded Microprocessor 
# Benchmark Consortium (EEMBC), Inc. All Rights Reserved.
#==============================================================================

#
# Makefile Target to build summary logs of Time and Code/Data Size Results
#
results:: alltime allsize allpsnr
results-oamark2: alltime allsize

#
# Subcommittee Unique name for Empty Benchmark.
#
EMPTYNAME="ofwempty"

#
# Program and Log files used for results generation.
#
#EXTRACTTIME=${AWK} -f $(ROOT)/util/awk/extracttime.awk
EXTRACTTIME=$(PERL) $(ROOT)/util/perl/extracttime.pl
EXTRACTSIZE=${AWK} -f $(ROOT)/util/$(AWKDIR)/size$(AWKSZ).awk
EXTRACTPSNR=${AWK} -f $(ROOT)/util/$(AWKDIR)/extractpsnr.awk
TIMELOGFILE=$(TOOLCHAIN)$(TLOGTYP)$(VER)$(LITE).log 
SIZELOGFILE=$(TOOLCHAIN)$(SLOGTYP)$(VER)$(LITE).log
PSNRLOGFILE=$(TOOLCHAIN)$(PLOGTYP)$(VER)$(LITE).log

# Special time results case for Ghostscript run by testdata-device. 
# See runv2x86.mak for definition of gs_testdata and gs_devices
GSEXE=gs8
# UU Decode program used for output verification
UUPROG=${ROOT}/util/bin/uudecode${HOSTEXE}
UUAWK=$(ROOT)/util/awk/uudecode.awk 
PSNRPROG=$(ROOT)/util/bin/psnr${HOSTEXE}


alltime:	${TIMELOGFILE}

#get prefix for all log file names that need to be scanned for time
TLOGPREFX1	= $(filter-out gs8,$(bmarks))
TLOGPREFX2	= $(filter-out empty,$(TLOGPREFX1))
TLOGPREFX3	= $(addprefix $(RESULTS)/,$(TLOGPREFX2))

TIMELOGS	= $(addsuffix .run.log,$(TLOGPREFX3))

${TIMELOGFILE}:	 $(TIMELOGS)
	@rm -f ${TIMELOGFILE}
	for i in $(bmarks); do \
		if [ "$$i" = "empty" ] || [ $$i = ${GSEXE} ] ; then continue;fi;\
		${EXTRACTTIME}  $(RESULTS)/$$i.run.log >>${TIMELOGFILE};\
		echo >> ${TIMELOGFILE};\
	done
	[ $(OAMARKONLY) == 1 ] || for j in $(RESULTS)/gs8*$(runlog); do \
		tdata=`echo "$$j" | sed -e "s/gs8\.\(.*\)$(runlog)/\1/"`;\
		${EXTRACTTIME}  $$j >>${TIMELOGFILE};\
		echo >> ${TIMELOGFILE}; \
		${UUPROG} $$j 2>/dev/null;\
	done

allsize:	${SIZELOGFILE}

#get prefix for all log file names that need to be scanned for size
SLOGPREFX	= $(addprefix $(RESULTS)/,$(bmarks))

SIZELOGS	=	$(addsuffix .size.log,$(SLOGPREFX))

${SIZELOGFILE}:	 $(SIZELOGS) $(RESULTS)/empty.size.log
	rm -f ${SIZELOGFILE};\
	for i in $(bmarks); do \
		if [ $$i = "empty" ]; then bm=${EMPTYNAME};else bm=$$i;fi;\
		${EXTRACTSIZE} -v BMARK=$$bm $(RESULTS)/$$i.size.log >> ${SIZELOGFILE};\
		echo >> ${SIZELOGFILE};\
	done

# UUDECODE completed as part of time logs.

#
# Generate PSNR Log files (Post Processing After run completes)
#
psnrlog=.psnr.csv

.PHONY:allpsnr
allpsnr: ${PSNRPROG}
	@rm -f ${PSNRLOGFILE};\
	[ ! -x "${UUPROG}" ] && (cd ${ROOT}/util && make); echo "Verify uuprog exists"
	@echo "Cleaning previous outputs" && rm -f $(TOOLCHAIN)/gs-output/*
	@for resfile in $(RESULTS)/gs8*$(runlog); do\
		if [ ! -f "$(RESULTS)/$$resfile$(psnrlog)" ] ;	then \
			echo "uuencoding $$resfile";\
			${UUPROG} "$$resfile" ;\
		fi;\
	done
	@for resfile in $(TOOLCHAIN)/gs-output/gs8* ; do\
			echo "Generating PSNR for $$resfile ..." ;\
			OUTNAME=`basename $$resfile` &&\
			echo "  ${PSNRPROG} $$resfile gs-output/$$OUTNAME" &&\
			${PSNRPROG} $$resfile gs-output/$$OUTNAME >$(RESULTS)/$$OUTNAME$(psnrlog) ;\
			${EXTRACTPSNR} -v BMARK=$$OUTNAME $(RESULTS)/$$OUTNAME$(psnrlog) >> ${PSNRLOGFILE} ;\
	done

#
# Add Clean step for PSNR logs.
#
cleanpsnr cleanlogs::
	@for i in $(gs_testdata); do \
	for j in $(gs_devices); do \
		tdata=`echo "$$i" | sed -e "s/\./\-/g"`;\
		rm -f $(RESULTS)/gs8-$$tdata-$$j$(psnrlog);\
	done;\
	done