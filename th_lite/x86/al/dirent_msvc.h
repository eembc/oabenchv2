/**
 * @file
 * @brief  MSVC Dirent types and structures.
 *
 * $RCSfile: dirent_msvc.h,v $
 *
 * @author  Rick Foos, ECL, LLC
 *
 *  EEMBC : Technical Advisory Group (TechTAG)
 *
 *    CVS : $Revision: 1.3 $
 *          $Date: 2006/03/09 17:34:19 $
 *          $Author: rick $
 *          $Source: /usr/local/cvs/eembc2/th_lite/x86/al/dirent_msvc.h,v $
 *          
 *   @note  
 *
 *
 * HISTORY :
 *
 * $Log: dirent_msvc.h,v $
 * Revision 1.3  2006/03/09 17:34:19  rick
 * Version 2 Office Release Candidate 5
 *
 * Revision 1.10  2005/07/16 03:08:31  rick
 * Merge updates for DSP environments
 *
 * Revision 1.9  2005/04/27 20:33:16  rick
 * Copyrite update 2005
 *
 * Revision 1.8  2004/12/08 23:27:26  rick
 * New standard header for documentation generation.
 *
 * Revision 1.4  2004/06/29 19:36:26  rick
 * EE_REDIRECT, and Shared file for Regular and Lite
 *
 * Revision 1.3  2004/06/23 05:55:27  rick
 * EE_REDIRECT, and Shared Files
 *
 * Revision 1.2  2004/03/10 23:57:19  rick
 * fix dirent calls
 *
 *
 * @verbatim
 *------------------------------------------------------------------------------
 * Copyright (c) 1998-2005 by the EDN Embedded Microprocessor 
 * Benchmark Consortium (EEMBC), Inc. 
 * 
 * All Rights Reserved. This is licensed program product and 
 * is owned by EEMBC. The Licensee understands and agrees that the 
 * Benchmarks licensed by EEMBC hereunder (including methods or concepts 
 * utilized therein) contain certain information that is confidential 
 * and proprietary which the Licensee expressly agrees to retain in the 
 * strictest confidence and to use only in conjunction with the Benchmarks 
 * pursuant to the terms of this Agreement. The Licensee further agrees 
 * to keep the source code and all related documentation confidential and 
 * not to disclose such source code and/or related documentation to any 
 * third party. The Licensee and any READER of this code is subject to 
 * either the EEMBC Member License Agreement and/or the EEMBC Licensee 
 * Agreement. 
 * TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, EEMBC DISCLAIMS ALL 
 * WARRANTIES, EITHER EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, 
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR 
 * PURPOSE, WITH REGARD TO THE BENCHMARKS AND THE ACCOMPANYING 
 * DOCUMENTATION. LICENSEE ACKNOWLEDGES AND AGREES THAT THERE ARE NO 
 * WARRANTIES, GUARANTIES, CONDITIONS, COVENANTS, OR REPRESENTATIONS BY 
 * EEMBC AS TO MARKETABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR OTHER 
 * ATTRIBUTES, WHETHER EXPRESS OR IMPLIED (IN LAW OR IN FACT), ORAL OR 
 * WRITTEN. 
 * 
 * Licensee hereby agrees by accessing this source code that all benchmark 
 * scores related to this code must be certified by ECL prior to publication 
 * in any media, form, distribution, or other means of conveyance of 
 * information subject to the terms of the EEMBC Member License Agreement 
 * and/or EEMBC Licensee Agreement. 
 * 
 * Other Copyright Notice (if any): 
 *
 * by M. J. Weinstein   Released to public domain 1-Jan-89
 *
 * Because I have heard that this feature (opendir, readdir, closedir)
 * is so useful for programmers coming from UNIX or attempting to port
 * UNIX code, and because it is reasonably light weight, I have included
 * it in the Mingw32 package. I have also added an implementation of
 * rewinddir, seekdir and telldir.
 *   - Colin Peters <colin@bird.fu.is.saga-u.ac.jp>
 *
 * Modified for EEMBC usage in host runs. NOT part of benchmark code. (Public Domain)
 *
 *  This code is distributed in the hope that is will be useful but
 *  WITHOUT ANY WARRANTY. ALL WARRANTIES, EXPRESS OR IMPLIED ARE HEREBY
 *  DISCLAIMED. This includeds but is not limited to warranties of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $Revision: 1.3 $
 * $Author: rick $
 * $Date: 2006/03/09 17:34:19 $
 *
 * For conditions of distribution and use, see the accompanying README file.
 *------------------------------------------------------------------------------
 * @endverbatim
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
