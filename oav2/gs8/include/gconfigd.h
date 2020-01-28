/**
@file
@brief Ghostscript configuration directories
*/

/** ECL We can't bring in thcfg.h, so we will default using Harness file system */
#ifndef	GCONFIGD_H
#define	GCONFIGD_H

#include "thconfig.h"

/** Default to Harness File System. */
#ifndef	USE_TH_FILEIO
#define	USE_TH_FILEIO	0
#endif

#define GS_LIB_DEFAULT "/usr/local/share/ghostscript/8.30/lib;/usr/local/share/ghostscript/8.30/Resource;/usr/local/share/ghostscript/fonts"
/** ECL - Use this for testing under Windows.
#define GS_LIB_DEFAULT "c:/cygwin/usr/local/share/ghostscript/8.30/lib;/usr/local/share/ghostscript/8.30/lib;c:/cygwin/usr/local/share/ghostscript/8.30/Resource;/usr/local/share/ghostscript/8.30/Resource;c:/cygwin/usr/local/share/ghostscript/fonts;/usr/local/share/ghostscript/fonts"
*/

#define GS_CACHE_DIR "~/.ghostscript/cache/"
#define SEARCH_HERE_FIRST 1

#define GS_DOCDIR "/usr/local/share/ghostscript/8.30/doc"
/** ECL - Use this for testing under Windows.
#define GS_DOCDIR "/usr/local/share/ghostscript/8.30/doc;c:/cygwin/usr/local/share/ghostscript/8.30/doc"
*/

#define GS_INIT "gs_init.ps"
#define GS_REVISION 830
#define GS_REVISIONDATE 20040529

#endif /* File Sentinel */
