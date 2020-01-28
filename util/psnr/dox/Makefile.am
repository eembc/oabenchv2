# $Id: Makefile.am,v 1.5 2005/11/29 20:21:09 rick Exp $
# Copyright (c) 2005 EEMBC. All rights reserved.

# NOTE: Document is ONLY built when install rule is executed.

# Target is root directory in eembc tree.
DESTDIR = ../../../doc

EXTRA_DIST = \
	index.dox \
	README

# We don't all ways want to rebuild this without dependencies.
DOX_OUTPUT_DIR = ${srcdir}

${DOX_OUTPUT_DIR}/latex/refman.pdf dox : Doxyfile
	@DOXYGEN@
	make -C ${DOX_OUTPUT_DIR}/latex
	[ -f "${DOX_OUTPUT_DIR}/latex/refman.pdf" ] || make -C ${DOX_OUTPUT_DIR}/latex pdf

# Avoid build break if PDF file didn't generate.
install-exec-local: ${DOX_OUTPUT_DIR}/latex/refman.pdf
	[ -f "${DOX_OUTPUT_DIR}/latex/refman.pdf" ] && $(INSTALL) ${DOX_OUTPUT_DIR}/latex/refman.pdf $(DESTDIR)/psnr.pdf

uninstall-local:
	[ -f "$(DESTDIR)/psnr.pdf" ] && rm -f $(DESTDIR)/psnr.pdf
	rm -rf ${DOX_OUTPUT_DIR}/latex ${DOX_OUTPUT_DIR}/html
