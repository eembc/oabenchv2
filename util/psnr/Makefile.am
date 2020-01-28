# $Id: Makefile.am,v 1.6 2005/11/29 22:18:09 rick Exp $
# Copyright (C) 2005 EEMBC Certification Labs, LLC

DESTDIR=..
EXEEXT=.exe

AUTOMAKE_OPTIONS = no-installman foreign 
#SUBDIRS = dox libtiff
SUBDIRS = libtiff

# Must preceed by / and hope that DESTDIR works:)
myexecbindir = /bin
myexecbin_PROGRAMS = tiffcmp psnr

LIBTIFF_LDADDS = $(top_builddir)/libtiff/libtiff.a
AM_CPPFLAGS = -I$(top_srcdir)/libtiff

psnr_SOURCES = psnr.c proto.h
tiffcmp_SOURCES = tiffcmp.c
LDADD = -lm $(LIBTIFF_LDADDS)

# Circular dependency, we want proto.h to update based on psnr.c changes
# we want proto.h created from the dependency in psnr.c
proto.h: mkproto.awk
	$(AWK) -f mkproto.awk psnr.c >proto.h

psnr.c: proto.h

EXTRA_DIST = autoconf.sh 
