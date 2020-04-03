/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#ifndef	DIRENT_MSVC_H
#define	DIRENT_MSVC_H

/** get autoconf variables from thconfig, and harness fileio configuration from thcfg.*/
#include "thcfg.h"

/** If we are not using harness fileio, and compiler is flagged to have fileio use this code */ 
#if		!USE_TH_FILEIO && HAVE_FILEIO

/** MSVC ONLY, calls MSVC specific libc routines. */
#if 	defined(_MSC_VER)

/** Get Malloc and Free. */
#include "thmalloc.h"

#ifndef UNDER_CE
#   include <io.h>
#   include <direct.h>
#endif

#include <windows.h> /* for GetFileAttributes */

/** @addtogroup SHAL
@{ */
/** @addtogroup DIRENT_MSVC_H MSVC Dirent Declarations
@{ */

#ifdef __cplusplus
extern "C" {
#endif

/** A dirent structure for MSVC. */
struct dirent
{
	long		d_ino;		/* Always zero. */
	unsigned short	d_reclen;	/* Always zero. */
	unsigned short	d_namlen;	/* Length of name in d_name. */
	char*		d_name;		/* File name. */
	/* NOTE: The name in the dirent structure points to the name in the
	 *       finddata_t structure in the DIR. */
};

/**
 * This is an internal data structure. Good programmers will not use it
 * except as an argument to one of the functions below.
 */
typedef struct msvc_DIR
{
	/* disk transfer area for this dir */
	WIN32_FIND_DATA		dd_dta;

	/* dirent struct to return from dir (NOTE: this makes this thread
	 * safe as long as only one thread uses a particular DIR struct at
	 * a time) */
	struct dirent		dd_dir;

	/* _findnext handle */
	long			dd_handle;

	/*
         * Status of search:
	 *   0 = not started yet (next entry to read is first entry)
	 *  -1 = off the end
	 *   positive = 0 based index of next entry
	 */
	short			dd_stat;

	/* given path for dir with search pattern (struct is extended) */
	char			dd_name[1];
} DIR;



DIR*		opendir (const char*);
struct dirent*	readdir (DIR*);
int		closedir (DIR*);
void		rewinddir (DIR*);
long		telldir (DIR*);
void		seekdir (DIR*, long);


/* wide char versions */

struct _wdirent
{
	long		d_ino;		/* Always zero. */
	unsigned short	d_reclen;	/* Always zero. */
	unsigned short	d_namlen;	/* Length of name in d_name. */
	wchar_t*	d_name;		/* File name. */
	/* NOTE: The name in the dirent structure points to the name in the
	 *       wfinddata_t structure in the _WDIR. */
};

/*
 * This is an internal data structure. Good programmers will not use it
 * except as an argument to one of the functions below.
 */
typedef struct
{
	/* disk transfer area for this dir */
	WIN32_FIND_DATA		dd_dta;

	/* dirent struct to return from dir (NOTE: this makes this thread
	 * safe as long as only one thread uses a particular DIR struct at
	 * a time) */
	struct _wdirent		dd_dir;

	/* _findnext handle */
	long			dd_handle;

	/*
         * Status of search:
	 *   0 = not started yet (next entry to read is first entry)
	 *  -1 = off the end
	 *   positive = 0 based index of next entry
	 */
	short			dd_stat;

	/* given path for dir with search pattern (struct is extended) */
	wchar_t			dd_name[1];
} _WDIR;


_WDIR*		_wopendir (const wchar_t*);
struct _wdirent* _wreaddir (_WDIR*);
int		_wclosedir (_WDIR*);
void		_wrewinddir (_WDIR*);
long		_wtelldir (_WDIR*);
void		_wseekdir (_WDIR*, long);


#ifdef	__cplusplus
}
#endif
/** @} */
/** @} */
#endif /* Not _MSC_VER */

#endif /* Not !USE_TH_FILEIO && HAVE_FILEIO */

#endif /* File Sentinal 	DIRENT_MSVC_H */
