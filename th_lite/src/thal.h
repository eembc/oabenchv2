/**
 * @file
 * @brief  Test Harness Adaptation Layer Interface
 *
 * $RCSfile: thal.h,v $
 *
 *  EEMBC : EEMBC Technical Advisory Group (TechTAG)
 *
 * @author  Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.42 $
 *          $Date: 2005/12/02 23:53:36 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/techtag/th_lite/src/thal.h,v $
 *          
 *   @note  IMPORTANT! Do not include any host specific include files here
 *          like WINDOWS.H or SOLARIS.H.  This file is intended to be a host
 *          independent interface to the Test Harness Adaptation Layer used by
 *          the Test Harness Functional Layer.
 *
 *
 * HISTORY :
 *
 * $Log: thal.h,v $
 * Revision 1.42  2005/12/02 23:53:36  rick
 * Fix mixed EOL format causing ^M's to appear in Unix checkouts.
 *
 * Revision 1.41  2005/09/10 04:02:24  rick
 * eol update, add uu_send_file
 *
 * Revision 1.29  2005/04/27 20:32:49  rick
 * Copyrite update 2005
 *
 * Revision 1.28  2004/12/08 23:27:44  rick
 * New standard header for documentation generation.
 *
 * Revision 1.27  2004/09/13 19:29:51  rick
 * Add th_read, th_write, and th_lseek
 *
 * Revision 1.26  2004/08/09 20:22:38  rick
 * Add th_open, clear warnings from stdio/threent
 *
 * Revision 1.25  2004/07/09 05:11:07  rick
 * Add gettimeofday
 *
 * Revision 1.24  2004/07/07 18:04:11  rick
 * Resolve type definition recursion on Linux GCC
 *
 * Revision 1.23  2004/07/03 03:13:58  rick
 * Add time, link, and exit to redirection.
 *
 * Revision 1.22  2004/06/29 19:36:22  rick
 * EE_REDIRECT, and Shared file for Regular and Lite
 *
 * Revision 1.21  2004/06/23 05:55:23  rick
 * EE_REDIRECT, and Shared Files
 *
 * Revision 1.20  2004/04/15 16:45:43  rick
 * fread/fwrite rv, size, and count to size_t
 *
 * Revision 1.19  2004/03/10 00:18:00  rick
 * Add scanf family, vfprintf, and new doscan
 *
 * Revision 1.18  2004/02/20 00:24:31  rick
 * change ee_dirent from typedef to struct
 *
 * Revision 1.17  2004/02/12 23:34:36  rick
 * Add fputs, macro fixes to thstdio
 *
 * Revision 1.16  2004/02/10 06:55:10  rick
 * Add fileio calls and stdio re-router
 *
 * Revision 1.15  2004/02/05 23:03:24  rick
 * Harness update with portable dirent
 *
 * Revision 1.14  2004/02/02 19:58:30  rick
 * Add ability to link thlib with original applications
 *
 * Revision 1.13  2004/01/22 00:56:52  rick
 * Release cleanup, copyright year corrections
 *
 * Revision 1.12  2003/05/20 19:16:16  rick
 * Add al_hardware_reset
 *
 * Revision 1.11  2003/04/18 15:05:30  rick
 * Add ftell, vfscanf, vsscanf
 *
 * Revision 1.10  2003/03/14 00:24:29  rick
 * Add feof and text file support to fileio
 *
 * Revision 1.9  2003/03/06 00:34:26  rick
 * Add th_fgets, and %g to printf
 *
 * Revision 1.8  2003/03/05 00:29:10  rick
 * Change th_fcreate size to ee_fsize_t
 *
 * Revision 1.7  2003/01/22 00:00:57  rick
 * Add File I/O to Regular
 *
 * Revision 1.6  2003/01/04 00:06:37  rick
 * fix al prototypes
 *
 * Revision 1.5  2002/12/31 16:22:39  rick
 * fix comments
 *
 * Revision 1.4  2002/08/06 21:57:16  rick
 * Add NI CRC to TH Regular
 *
 * Revision 1.3  2002/04/23 18:33:56  rick
 * Match eembc_dt with Lite, remove stdinc.h
 *
 * Revision 1.2  2002/03/21 22:31:09  rick
 * Network Harness, and empty benchmark fixes
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
 * For conditions of distribution and use, see the accompanying README file.
 *------------------------------------------------------------------------------
 * @endverbatim
 */

#ifndef   THAL_H       /* File Sentinal */
#define   THAL_H

#include "thconfig.h"
/** Define size_t, va_list. */
#if 	HAVE_STDARG_H
#include <stdarg.h> /* size_t */
#endif
/** Define direct call to time, localtime stubs from benchmark. */
#include "thtime.h"
#include "thcfg.h"
/** Define all ee_routines. */
#include "fileio.h"
/** Define mem_size. */
#include "heapport.h"

/** @addtogroup SHFL
@{ */
/** @addtogroup thal_h Test Harness Adaptation Layer Interface
@{ */

#ifdef __cplusplus
extern "C" {
#endif

   /*------------------------------------------------------------------------------
    * Global Defines
    */

#define FATAL_EXIT (-32766)
#define PF_BUF_SIZE (1024)

   /*------------------------------------------------------------------------------
    * Global data
    */

   /*------------------------------------------------------------------------------
    * The Test Harness Application Layer API
    */

	/* Display Routines */
	int    al_sprintf  (char *str, const char *fmt, va_list   args);
	int    al_printf   (const char *fmt, va_list	args);
	int    al_write_con(const char* tx_buf, size_t byte_count);
	/* TH Regular only. */
	int    al_lc_open ( void );
	void   al_lc_close( void );
	size_t al_read_con( char *buf, size_t buf_size );
	size_t al_con_chars_avail( void );

	/* Timer Routines */
	size_t   al_ticks           (void);
	size_t   al_ticks_per_sec   (void);
	size_t   al_tick_granularity(void);
	void     al_signal_start    (void);
	size_t   al_signal_finished (void);

	/* PowerTAG Routines. */
	void	al_power_start      (void);
	void	al_power_finished   (void);

	/* System Routines */
	void	 al_exit  ( int exit_code, const char *fmt, va_list args );
	void	 al_report_results	(void);
	void	 al_hardware_reset	(int ev);

	/* TH Lite only. */
	void	 al_main		(int argc, const char* argv[]);

	/* LIBC Routines */
	char	*al_getenv	( const char *key );
	ee_pid_t al_getpid	( void );

	/* File I/O Routines */
	int 	 al_fclose  (ee_FILE *fp);
	int 	 al_open	(const char *pathname, int flags);
	int 	 al_close   (int fildes);
	size_t	 al_read    (int fd, void *buf, size_t count);
	size_t	 al_write   (int fd, const void *buf, size_t count);
	ee_off_t al_lseek   (int fildes, ee_off_t offset, int whence);
	int 	 al_ferror  (ee_FILE *fp);
	int 	 al_feof    (ee_FILE *fp);
	void	 al_clearerr(ee_FILE *fp);
	int 	 al_fileno  (ee_FILE *fp);
	int 	 al_fflush  (ee_FILE *fp);
	int 	 al_fsync   (int fildes);
	int 	 al_isatty  (int fildes);
	int 	 al_vfprintf(ee_FILE *fp, const char* format, va_list arg);
	int 	 al_fseek   (ee_FILE *fp, long int offset, int whence);
	long	 al_ftell   (ee_FILE *fp);

	/* DIRENT routines, and helpers */

	char      *al_getcwd   (char *buffer, size_t size);
	char      *al_getwd    (char *buffer);
	int        al_chdir    (const char *filename);
	ee_DIR    *al_opendir  (const char *dirname);
	struct ee_dirent *al_readdir  (ee_DIR *dirstream);
	int        al_closedir (ee_DIR *dirstream);
	void       al_rewinddir(ee_DIR *dirstream);
	int        al_stat     (const char *path, struct th_stat *buf);
	int        al_lstat    (const char *path, struct th_stat *buf);
	int        al_fstat    (int fildes, struct th_stat *buf);
	int        al_unlink   (const char *filename);
	int        al_link     (const char *oldpath, const char *newpath);

	/* Basic file I/O routines */

	int 	 al_putc    (int c, ee_FILE *fp);
	int 	 al_getc    (ee_FILE *fp);
	int 	 al_ungetc  (int size, ee_FILE *fp);
	int 	 al_fputs   (const char *s, ee_FILE *fp);
	char	*al_fgets   (char *string,int count,ee_FILE *fp);
	size_t 	 al_fread   (void *buf, size_t size, size_t count, ee_FILE *fp);
	size_t 	 al_fwrite  (const void *buf, size_t size, size_t count, ee_FILE *fp);
	ee_FILE *al_fopen   (const char *filename, const char *mode);
	ee_FILE *al_fdopen  (int fildes, const char *mode);
	ee_FILE *al_freopen (const char *filename, const char *mode, ee_FILE *fp);
	ee_FILE *al_tmpfile (void);
	char    *al_mktemp  (char *templat);

	/* scanf input format conversion family (thal.c only sees vxxx functions) */

	int		al_vscanf(const char *format, va_list ap);
	int		al_vsscanf(const char *str, const char *format, va_list ap);
	int		al_vfscanf(ee_FILE *stream, const char *format, va_list ap);

	/* Process I/O */

	ee_FILE	*al_popen(const char *command, const char *type);
	int		al_pclose(ee_FILE *fd);

	/** @remark Time Routines are direct calls to harness defined in thtime.h */

	/* NON Standard routines */

	int 	 al_filecmp (const char *file1, const char *file2);
	ee_FILE *al_fcreate (const char *filename, const char *mode, char *data, ee_fsize_t size);
	ee_fsize_t al_fsize (const char *filename);
	int al_dup(int fildes);

   /*----------------------------------------------------------------------------*/

#ifdef __cplusplus
   }
#endif
#endif                /*  File Sentinal */
/** @} */
/** @} */
