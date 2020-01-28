#==============================================================================
#$RCSfile: runv2x86.mak,v $
#
#   DESC : Run Each Benchmark
#
# AUTHOR : Rick Foos, ECL, LLC
#
#  EEMBC : Office
#
#    CVS : $Revision: 1.44 $
#------------------------------------------------------------------------------
# Copyright (c) 1998-2005 by the EDN Embedded Microprocessor 
# Benchmark Consortium (EEMBC), Inc. All Rights Reserved.
#==============================================================================

# Flag for Benchmark generation of uuencoded data. (See GS_RUNOPTS)
UUFLAG=-do_uuencode

#
# make target to run benchmarks, and run size utility on each benchmark.
#
run:: run_gs8 run_ditherv2 run_bezierv2 run_rotatev2 run_textv2

run-oamark2: run_ditherv2 run_bezierv2 run_rotatev2 run_textv2

# Ghostscript Device List can be found in the rungs.pl script file.

# Don't quote these variable strings, problem in makefile environment.
# NOTE: Add -dDEBUG -Z# to command line if you are having problems to get extra debug output.
GSRUNOPTS=${UUFLAG} -dNOPAUSE -dBATCH
ifeq (${COM},${CCD})
GSRUNOPTS+=-dDEBUG
else
GSRUNOPTS+=-q
endif

runlog=.run.log

define copy-gprof
	-testname=`basename $< $(EXE)` && \
	if [ -f "$(RESULTS)/$$testname.gprof" ]; then				\
		echo "copy gprof results for $<" &&				\
		mv $(RESULTS)/$$testname.gprof $(RESULTS)/$$testname.$*.gprof ;	\
	fi		
endef

#rules to create run/size logs for all benchmarks except GS
$(RESULTS)/bezierv2fixed%.run.log: $(BINBUILD)/bezierv2fixed$(LITE)$(EXE)
	-$(RUN) $(RUN_FLAGS) $< $(CMDLINE$(LITE)) -$* ${UUFLAG} > $@ ${RUN_LASTOUT}
	$(copy-gprof)

$(RESULTS)/bezierv2fixed%.size.log: $(BINBUILD)/bezierv2fixed$(LITE)$(EXE)
	$(SIZE) $(SIZE_FLAGS) $< > $@

$(RESULTS)/bezierv2float%.run.log: $(BINBUILD)/bezierv2float$(LITE)$(EXE)
	-$(RUN) $(RUN_FLAGS) $< $(CMDLINE$(LITE)) -$* ${UUFLAG} > $@ ${RUN_LASTOUT}
	$(copy-gprof)

$(RESULTS)/bezierv2float%.size.log: $(BINBUILD)/bezierv2float$(LITE)$(EXE)
	$(SIZE) $(SIZE_FLAGS) $< > $@

$(RESULTS)/ditherv2%.run.log: $(BINBUILD)/ditherv2$(LITE)$(EXE)
	-$(RUN) $(RUN_FLAGS) $< $(CMDLINE$(LITE)) -$* ${UUFLAG} > $@ ${RUN_LASTOUT}
	$(copy-gprof)

$(RESULTS)/ditherv2%.size.log: $(BINBUILD)/ditherv2$(LITE)$(EXE)
	$(SIZE) $(SIZE_FLAGS) $< > $@

$(RESULTS)/rotatev2%.run.log: $(BINBUILD)/rotatev2$(LITE)$(EXE)
	-$(RUN) $(RUN_FLAGS) $< $(CMDLINE$(LITE)) -$* ${UUFLAG} > $@ ${RUN_LASTOUT}
	$(copy-gprof)

$(RESULTS)/rotatev2%.size.log: $(BINBUILD)/rotatev2$(LITE)$(EXE)
	$(SIZE) $(SIZE_FLAGS) $< > $@

$(RESULTS)/textv2%.run.log: $(BINBUILD)/textv2$(LITE)$(EXE)
	-$(RUN) $(RUN_FLAGS) $< $(CMDLINE$(LITE)) -$* ${UUFLAG} > $@ ${RUN_LASTOUT}
	$(copy-gprof)

$(RESULTS)/textv2%.size.log: $(BINBUILD)/textv2$(LITE)$(EXE)
	$(SIZE) $(SIZE_FLAGS) $< > $@

$(RESULTS)/%.run.log: $(BINBUILD)/%$(LITE)$(EXE)
	-$(RUN) $(RUN_FLAGS) $< $(CMDLINE$(LITE)) ${UUFLAG} > $@ ${RUN_LASTOUT}
	$(copy-gprof)

$(RESULTS)/%.size.log: $(BINBUILD)/%$(LITE)$(EXE)
	$(SIZE) $(SIZE_FLAGS) $< > $@

BEZBENCH1 = $(filter bezierv2%,$(bmarks))
BEZBENCH2 = $(addprefix $(RESULTS)/,$(BEZBENCH1))
BEZRUNLOGS= $(addsuffix .run.log,$(BEZBENCH2))

#need to be created
run_bezierv2: $(THLIB) $(BEZRUNLOGS)

TEXTBENCH1 = $(filter textv2%,$(bmarks))
TEXTBENCH2 = $(addprefix $(RESULTS)/,$(TEXTBENCH1))
TEXTRUNLOGS= $(addsuffix .run.log,$(TEXTBENCH2))

run_textv2: $(THLIB) $(TEXTRUNLOGS)

DITHBENCH1 = $(filter ditherv2%,$(bmarks))
DITHBENCH2 = $(addprefix $(RESULTS)/,$(DITHBENCH1))
DITHRUNLOGS= $(addsuffix .run.log,$(DITHBENCH2))

run_ditherv2: $(THLIB) $(DITHRUNLOGS) 

ROTBENCH1 = $(filter rotatev2%,$(bmarks))
ROTBENCH2 = $(addprefix $(RESULTS)/,$(ROTBENCH1))
ROTRUNLOGS= $(addsuffix .run.log,$(ROTBENCH2))

run_rotatev2: $(THLIB) $(ROTRUNLOGS)

run_gs8: $(THLIB) gs8_all $(RESULTS)/gs8.size.log

ifeq ($(TRAINING),yes)
 GS_TRAIN=-train
endif

#
# Special Run Step for Ghostscript. 
# Run by data and devices.
# see rungs.pl for a list of devices, data files, and specific options.

.PHONY:gs8_all
gs8_all: 
	perl rungs.pl -gsname="$(RUN) $(RUN_FLAGS) $(BINBUILD)/gs8$(LITE)$(EXE)" \
	 -gsparam="$(CMDLINE$(LITE)) ${GSRUNOPTS}" \
	 -outpath="$(TOOLCHAIN)/gs-output" -logpath=$(RESULTS) -logext=$(runlog) $(GS_TRAIN)
