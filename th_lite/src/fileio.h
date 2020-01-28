/**
 * @file
 * @brief  Test Harness File System using Stream I/O calls.
 *
 * $RCSfile: fileio.h,v $
 *
 *  EEMBC : Techtag
 *
 * @author  Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.3 $
 *          $Date: 2006/03/09 17:34:18 $
 *          $Author: rick $
 *          $Source: /usr/local/cvs/eembc2/th_lite/src/fileio.h,v $
 *          
 * @note   
 *
 *
 * HISTORY :
 *
 * $Log: fileio.h,v $
 * Revision 1.3  2006/03/09 17:34:18  rick
 * Version 2 Office Release Candidate 5
 *
 * Revision 1.38  2005/12/02 23:53:34  rick
 * Fix mixed EOL format causing ^M's to appear in Unix checkouts.
 *
 * Revision 1.37  2005/09/10 04:02:23  rick
 * eol update, add uu_send_file
 *
 * Revision 1.36  2005/04/27 20:33:14  rick
 * Copyrite update 2005
 *
 * Revision 1.35  2004/12/08 23:27:17  rick
 * New standard header for documentation generation.
 *
 * Revision 1.31  2004/09/13 19:29:51  rick
 * Add th_read, th_write, and th_lseek
 *
 * Revision 1.30  2004/09/03 22:29:24  rick
 * New Office Textv2 functions
 *
 * Revision 1.29  2004/08/09 20:22:38  rick
 * Add th_open, clear warnings from stdio/threent
 *
 * Revision 1.28  2004/07/07 18:04:11  rick
 * Resolve type definition recursion on Linux GCC
 *
 * Revision 1.27  2004/07/03 03:13:58  rick
 * Add time, link, and exit to redirection.
 *
 * Revision 1.26  2004/06/23 05:55:23  rick
 * EE_REDIRECT, and Shared Files
 *
 * Revision 1.25  2004/04/15 17:34:44  rick
 * svfscanf prototype for doscan
 *
 * Revision 1.24  2004/04/15 16:45:43  rick
 * fread/fwrite rv, size, and count to size_t
 *
 * Revision 1.23  2004/04/01 22:38:29  rick
 * Add ee_exec_ls, add config flags for doscan, fix msvc dirent flags
 *
 * Revision 1.22  2004/03/15 21:29:05  rick
 * Add documentation tags, and cleanup comments
 *
 * Revision 1.21  2004/03/10 00:18:00  rick
 * Add scanf family, vfprintf, and new doscan
 *
 * Revision 1.20  2004/02/20 00:24:31  rick
 * change ee_dirent from typedef to struct
 *
 * Revision 1.19  2004/02/12 23:34:36  rick
 * Add fputs, macro fixes to thstdio
 *
 * Revision 1.18  2004/02/11 02:55:45  rick
 * Add macro redefinitions, improve efn and fileio
 *
 * Revision 1.17  2004/02/10 06:55:10  rick
 * Add fileio calls and stdio re-router
 *
 * Revision 1.16  2004/02/06 18:18:26  rick
 * Fix errno conflicts
 *
 * Revision 1.15  2004/02/05 23:03:24  rick
 * Harness update with portable dirent
 *
 * Revision 1.14  2004/01/22 00:56:52  rick
 * Release cleanup, copyright year corrections
 *
 * Revision 1.13  2003/07/26 18:29:15  rick
 * Fix include paths
 *
 * Revision 1.12  2003/07/24 22:01:36  mdvesper
 * Protect fseek types
 *
 * Revision 1.11  2003/06/23 16:23:50  rick
 * Fix FIONREAD
 *
 * Revision 1.10  2003/05/05 21:20:40  mike
 * Add errno's for NAT benchmark
 *
 * Revision 1.9  2003/04/18 15:05:30  rick
 * Add ftell, vfscanf, vsscanf
 *
 * Revision 1.8  2003/03/26 00:17:57  rick
 * Add scanf functions
 *
 * Revision 1.7  2003/03/14 00:24:29  rick
 * Add feof and text file support to fileio
 *
 * Revision 1.6  2003/03/06 00:34:26  rick
 * Add th_fgets, and %g to printf
 *
 * Revision 1.5  2003/03/05 00:29:10  rick
 * Change th_fcreate size to ee_fsize_t
 *
 * Revision 1.4  2003/02/12 16:45:45  rick
 * GreenHills36 needs #if !defined on filename_max
 *
 * Revision 1.4  2003/02/03 18:31:50  rick
 * Make MAX_FILESIZE local to resolve stdio.h conflicts
 *
 * Revision 1.3  2003/01/17 22:44:37  rick
 * Add File I/O to harness
 *
 * Revision 1.2  2003/01/03 18:09:13  rick
 * Add ee fileio to harness
 *
 * Revision 1.1  2003/01/03 00:26:03  rick
 * Initial file I/O routines
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
 * For conditions of distribution and use, see the accompanying README file.
 *------------------------------------------------------------------------------
 * @endverbatim
 */

/** for autoconf ERRNO definitions needed for header file. */
#include "thconfig.h"
/** va_list for scanf functions. */
#if		HAVE_STDARG_H
#include <stdarg.h>
#endif
/** for EOF, and SEEK defines. */
#include <stdio.h>
/** errno definitions, split as NAT benchmark needs pre-defines from header */
#include "therrno.h"
/** FILE definition. */
#include "threent.h"
/** types definitions for dirent structure. */
#include "thtypes.h"
/** Data declarations for dirent routines. */
#include "thdirent.h"
/** Data declarations for stat routines. */
#include "thstat.h"

/** @addtogroup SHFL
@{ */
/** @addtogroup fileio_c Test Harness File System 
@{ */

/** File Sentinel */
#ifndef FILEIO_H
#define FILEIO_H
#ifdef  __cplusplus
extern "C" {
#endif

#if	USE_TH_FILEIO
/* Just in case someone uses a supplied stdio.h */
#ifndef	SEEK_SET
#undef  SEEK_SET
#define SEEK_SET 0
#endif
#ifndef	SEEK_CUR
#undef  SEEK_CUR
#define SEEK_CUR 1
#endif
#ifndef	SEEK_END
#undef  SEEK_END
#define SEEK_END 2
#endif
#endif

/*
 *  File status
 */
#define F_CLOSED      0
#define F_OPEN        1

/*
 *  File modes
 */
#define   F_READABLE    (1<<0)
#define   F_WRITEABLE   (1<<1)

/** Declare external stdio array */
extern	ee_FILE     ee_stdio[];
#define ee_stdin  (&ee_stdio[0])
#define ee_stdout (&ee_stdio[1])
#define ee_stderr (&ee_stdio[2])

/*
 *  Prototypes for API functions
 */
int        ee_fclose  (ee_FILE*);
int        ee_ferror  (ee_FILE*);
int        ee_feof    (ee_FILE*);
void       ee_clearerr(ee_FILE*);
int        ee_fileno  (ee_FILE*);
int        ee_fflush  (ee_FILE*);
int        ee_fsync   (int fildes);
int        ee_isatty  (int fildes);

int        ee_fprintf (ee_FILE*, const char* format, ...);
int        ee_vfprintf(ee_FILE *fp, const char* format, va_list arg);
int        ee_fseek   (ee_FILE* fp, long int offset, int whence);
long       ee_ftell   (ee_FILE *fp);

/* DIRENT routines, and helpers */

char      *ee_getcwd   (char *buffer, size_t size);
char      *ee_getwd    (char *buffer);
int        ee_chdir    (const char *filename);
ee_DIR    *ee_opendir  (const char *dirname);
struct ee_dirent *ee_readdir  (ee_DIR *dirstream);
int        ee_closedir (ee_DIR *dirstream);
void       ee_rewinddir(ee_DIR *dirstream);
int        ee_stat     (const char *filename, struct th_stat *buf);
int        ee_lstat    (const char *filename, struct th_stat *buf);
int        ee_fstat    (int fildes, struct th_stat *buf);

/* unistd.h routines. */

int        ee_open		(const char *pathname, int flags);
int        ee_close 	(int fildes);
size_t     ee_read		(int fd, void *buf, size_t count);
size_t     ee_write		(int fd, const void *buf, size_t count);
ee_off_t   ee_lseek		(int fildes, ee_off_t offset, int whence);
int        ee_unlink	(const char *filename);
int        ee_link		(const char *oldpath, const char *newpath);


/* Basic file I/O routines */

int      ee_putc    (int c, ee_FILE *fp);
int      ee_getc    (ee_FILE *fp);
int      ee_ungetc  (int size,ee_FILE *fp);
int      ee_fputs   (const char *s, ee_FILE *fp);
char	*ee_gets	(char *string,int count,ee_FILE *fp);
char    *ee_fgets   (char *string,int count,ee_FILE *fp);
size_t   ee_fread   (void*, size_t, size_t, ee_FILE*);
size_t   ee_fwrite  (const void*, size_t, size_t, ee_FILE *);
ee_FILE *ee_fopen   (const char*, const char*);
ee_FILE *ee_fdopen  (int fildes, const char *mode);
ee_FILE *ee_freopen (const char*, const char*, ee_FILE *);
ee_FILE *ee_tmpfile (void);
char    *ee_mktemp  (char *templat);

/* scanf input format conversion family (thal.c only sees vxxx functions) */

int 	 ee_scanf   (const char *fmt, ...);
int		 ee_fscanf  (ee_FILE *fp,const char *fmt, ...);
int		 ee_sscanf  (const char *str, const char *fmt, ...);
int 	 ee_vscanf  (const char *fmt, va_list args);
int      ee_vfscanf (ee_FILE *fp, const char* fmt, va_list args);
int      ee_vsscanf (const char *str, const char *fmt, va_list args);
int      ee_svfscanf(register ee_FILE *fp,const char *fmt0,va_list ap);

/* Process I/O */

ee_FILE	*ee_popen(const char *command, const char *type);
int		ee_pclose(ee_FILE *fd);

/* NON Standard routines */

int         ee_filecmp(const char *file1, const char *file2);
ee_FILE    *ee_fcreate(const char *filename, const char *mode, char *data, ee_fsize_t size);
ee_fsize_t	ee_fsize  (const char *filename);
int ee_dup(int fildes);

/* exec commands related to file system */

void		ee_exec_ls(const char *args);

#ifdef  __cplusplus
}
#endif
#endif /* File Sentinel */
/** @} */
/** @} */
