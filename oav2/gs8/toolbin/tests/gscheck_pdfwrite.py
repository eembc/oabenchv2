#!/usr/bin/env python

#    Copyright (C) 2001-2004 Artifex Software Inc.
# 
# This file is part of AFPL Ghostscript.
# 
# AFPL Ghostscript is distributed with NO WARRANTY OF ANY KIND.  No author or
# distributor accepts any responsibility for the consequences of using it, or
# for whether it serves any particular purpose or works at all, unless he or
# she says so in writing.  Refer to the Aladdin Free Public License (the
# "License") for full details.
# 
# Every copy of AFPL Ghostscript must include a copy of the License, normally
# in a plain ASCII text file named PUBLIC.  The License grants you the right
# to copy, modify and redistribute AFPL Ghostscript, but only under certain
# conditions described in the License.  Among other things, the License
# requires that the copyright notice and this notice be preserved on all
# copies.

# $Id: gscheck_pdfwrite.py 6300 2005-12-28 19:56:24Z giles $

#
# gscheck_pdfwrite.py
#
# compares Ghostscript against a baseline made from file->pdf->raster->md5sum.
# this test tries to detect Ghostscript changes that affect the pdfwrite driver.

import os, stat
import calendar, string, time
import gstestutils
import gsconf, gstestgs, gsparamsets, gssum, gsutil


class GSPDFWriteCompareTestCase(gstestgs.GhostscriptTestCase):
    def shortDescription(self):
        file = "%s.pdf.%s.%d.%d" % (self.file[string.rindex(self.file, '/') + 1:], self.device, self.dpi, self.band)
	rasterfilename = gsconf.rasterdbdir + file + ".gz"
	if not os.access(rasterfilename, os.F_OK):
		os.system(gsconf.codedir + "update_pdfbaseline '%s'" %
                          (os.path.basename(self.file),))
        try:
            ct = time.localtime(os.stat(rasterfilename)[stat.ST_MTIME])
            baseline_date = "%s %d, %4d %02d:%02d" % (
                calendar.month_abbr[ct[1]], ct[2], ct[0], ct[3], ct[4])
        except:
            if self.band: banded = "banded"
            else: banded = "noband"
            self.skip = 1

      	    return "Skipping pdfwrite %s (%s/%ddpi/%s) [no previous raster data found]" % (os.path.basename(self.file), self.device, self.dpi, banded)

	if self.band:
	    return "Checking pdfwrite of %s (%s/%ddpi/banded) against baseline set on %s" % (os.path.basename(self.file), self.device, self.dpi, baseline_date)
        else:
	    return "Checking pdfwrite of %s (%s/%ddpi/noband) against baseline set on %s" % (os.path.basename(self.file), self.device, self.dpi, baseline_date)

	
    def runTest(self):
        if hasattr(self, "skip") and self.skip:
	    self.assert_(True)
	    return

        file1 = '%s.%s.%d.%d.pdf' % (self.file[string.rindex(self.file, '/') + 1:], 'pdf', self.dpi, self.band)
	file2 = '%s.pdf.%s.%d.%d' % (self.file[string.rindex(self.file, '/') + 1:], self.device, self.dpi, self.band)

	gs = gstestgs.Ghostscript()
	gs.command = self.gs
	gs.dpi = self.dpi
	gs.band = self.band
	gs.infile = self.file
	if self.log_stdout:
	    gs.log_stdout = self.log_stdout
	if self.log_stderr:
	    gs.log_stderr = self.log_stderr

	# do file->PDF conversion

	gs.device = 'pdfwrite'
        gs.dpi = None
	gs.outfile = file1
	if not gs.process():
	    self.fail("non-zero exit code trying to create pdf file from " + self.file)

	# do PDF->device (pbmraw, pgmraw, ppmraw, pkmraw)
		
	gs.device = self.device
        gs.dpi = self.dpi
	gs.infile = file1
	gs.outfile = file2
	if not gs.process():
	    self.fail("non-zero exit code trying to"\
		      " rasterize " + file1)

	# compare baseline
		
	sum = gssum.make_sum(file2)
	os.unlink(file1)
	os.unlink(file2)
	
	# add test result to daily database
	if self.track_daily:
	    gssum.add_file(file2, dbname=gsconf.get_dailydb_name(), sum=sum)

	self.assertEqual(sum, gssum.get_sum(file2), "md5sum did not match baseline (" + file2 + ") for file: " + self.file)

# Add the tests defined in this file to a suite

def add_compare_test(suite, f, device, dpi, band, track):
    suite.addTest(GSPDFWriteCompareTestCase(gs=gsconf.comparegs,
					    file=gsconf.comparefiledir + f,
					    device=device, dpi=dpi,
					    band=band, track_daily=track,
					    log_stdout=gsconf.log_stdout,
					    log_stderr=gsconf.log_stderr))

def addTests(suite, gsroot, **args):
    if args.has_key('track'):
        track = args['track']
    else:
        track = 0
    
    # get a list of test files
    comparefiles = os.listdir(gsconf.comparefiledir)

    for f in comparefiles:
        if gsutil.check_extension(f):
	    for params in gsparamsets.pdftestparamsets:
	        add_compare_test(suite, f, params.device,
				 params.resolution,
				 params.banding, track)

if __name__ == "__main__":
    gstestutils.gsRunTestsMain(addTests)
