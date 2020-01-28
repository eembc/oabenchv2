/**
 * @file
 * @brief  TH fileio to stdio Redirect Interface
 *
 * $RCSfile: thstdio.h,v $
 *
 *  EEMBC : EEMBC Technical Advisory Group (TechTAG)
 *
 * @author  Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.3 $
 *          $Date: 2006/03/09 17:34:18 $
 *          $Author: rick $
 *          $Source: /usr/local/cvs/eembc2/th_lite/src/thstdio.h,v $
 *          
 * @note   
 * @warning Do NOT include this with fileio.h.
 *
 * HISTORY :
 *
 * $Log: thstdio.h,v $
 * Revision 1.3  2006/03/09 17:34:18  rick
 * Version 2 Office Release Candidate 5
 *
 * Revision 1.17  2005/12/02 23:53:38  rick
 * Fix mixed EOL format causing ^M's to appear in Unix checkouts.
 *
 * Revision 1.16  2005/09/10 04:02:24  rick
 * eol update, add uu_send_file
 *
 * Revision 1.15  2005/04/27 20:33:15  rick
 * Copyrite update 2005
 *
 * Revision 1.14  2004/12/08 23:27:19  rick
 * New standard header for documentation generation.
 *
 * Revision 1.12  2004/08/10 17:44:51  rick
 * Add vsnprintf
 *
 * Revision 1.11  2004/08/09 20:22:39  rick
 * Add th_open, clear warnings from stdio/threent
 *
 * Revision 1.10  2004/07/03 03:13:59  rick
 * Add time, link, and exit to redirection.
 *
 * Revision 1.9  2004/06/29 19:36:23  rick
 * EE_REDIRECT, and Shared file for Regular and Lite
 *
 * Revision 1.8  2004/06/23 05:55:24  rick
 * EE_REDIRECT, and Shared Files
 *
 * Revision 1.7  2004/06/14 18:02:20  rick
 * Bug 274: Precision in log files is not large enough for reporting results on simulators.
 *
 * Revision 1.6  2004/04/15 16:45:44  rick
 * fread/fwrite rv, size, and count to size_t
 *
 * Revision 1.5  2004/02/12 23:34:37  rick
 * Add fputs, macro fixes to thstdio
 *
 * Revision 1.4  2004/02/11 22:05:22  rick
 * Add fputs to fix multiple drivers
 *
 * Revision 1.3  2004/02/11 02:56:08  rick
 * Add macro redefinitions, improve efn and fileio
 *
 * Revision 1.2  2004/02/10 08:29:58  rick
 * Waterfal bmp256 run
 *
 * Revision 1.1  2004/02/10 06:55:37  rick
 * Add fileio calls and stdio re-router
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

/** File Sentinel. */
#ifndef THSTDIO_H
#define THSTDIO_H

/** To see if we have stdarg.h. */
#include "thconfig.h"

/** Get compiler's va_list define. */
#if		HAVE_STDARG_H
#include	<stdarg.h>
#endif

/** stdio definition of FILE generally in reent.h. */
#include "threent.h"

/** @addtogroup SHFL
@{ */
/** @addtogroup THSTDIO_H EEMBC Redirection for stdio.h
@{ */

#ifdef __cplusplus
extern "C" {
#endif

/** Don't redirect unless specified explicitly. */
#if 	!defined(EE_REDIRECT)
#define	EE_REDIRECT	0
#endif

/* Display control */

/* Routines in printfe.c. */

/* Display control */

int    th_printf( const char *fmt, ... );
int    th_sprintf( char *str, const char *fmt, ... );
int    th_vsprintf( char *str, const char *fmt, va_list args );
int    th_putchar( char c );
int    th_puts( const char *s );


/* Routines in fileio.c. */

/* File I/O - Streams */

int      th_fclose  (ee_FILE *fp);
int      th_ferror  (ee_FILE *fp);
int      th_feof    (ee_FILE *fp);
void     th_clearerr(ee_FILE*);
int      th_fileno  (ee_FILE*);
int	     th_fflush  (ee_FILE *fp);
int	     th_fprintf (ee_FILE *fp, const char* format, ...);
int      th_vfprintf(ee_FILE *fp, const char *format, va_list ap);
int	     th_fseek   (ee_FILE *fp, long int offset, int whence);
long     th_ftell   (ee_FILE *fp);

/* Basic file I/O routines */

int      th_putc    (int c, ee_FILE *fp);
int      th_getc    (ee_FILE *fp);
int      th_ungetc  (int size, ee_FILE *fp);
int      th_fputs   (const char *s, ee_FILE *fp);
char    *th_fgets   (char *string,int count,ee_FILE *fp);
size_t	 th_fread   (void *buf, size_t size, size_t count, ee_FILE *fp);
size_t	 th_fwrite  (const void *buf, size_t size, size_t count, ee_FILE *fp);
ee_FILE *th_fopen   (const char *filename, const char *mode);
ee_FILE *th_fdopen  (int fildes, const char *mode);
ee_FILE *th_freopen (const char *filename, const char *mode, ee_FILE *fp);
ee_FILE *th_tmpfile (void);
char	*th_mktemp  (char *templat);

/* scanf input format conversion family (thal.c only sees vxxx functions) */

int 	th_scanf(const char *format, ...);
int		th_fscanf(ee_FILE *stream, const char *format, ...);
int		th_sscanf(const char *str, const char *format, ...);
int		th_vscanf(const char *format, va_list ap);
int		th_vsscanf(const char *str, const char *format, va_list ap);
int		th_vfscanf(ee_FILE *stream, const char *format, va_list ap);

/* Process I/O */

ee_FILE	*th_popen(const char *command, const char *type);
int		th_pclose(ee_FILE *fd);

/* Std files. */

#define ee_stdin  (&ee_stdio[0])
#define ee_stdout (&ee_stdio[1])
#define ee_stderr (&ee_stdio[2])

#if		EE_REDIRECT

/* Data Redirection */

#define	FILE	ee_FILE
#undef	stdin
#define stdin	ee_stdin
#undef	stdout
#define stdout	ee_stdout
#undef	stderr
#define stderr	ee_stderr

/* Routines in printfe.c. */

#define printf			th_printf
#define sprintf			th_sprintf
/** Requires va_list. */
#define vsprintf		th_vsprintf

#undef  ferror
#define ferror(x)  		th_ferror(x)
#undef  feof
#define feof(x)    		th_feof(x)
#undef  clearerr
#define clearerr(x)		th_clearerr(x)
#undef  fileno
#define fileno(x)  		th_fileno(x)
#undef  putc
#define putc(x,y)		th_putc(x,y)
#define fputc(x,y)		th_putc(x,y)
#define fputs(x,y)		th_fputs(x,y)
#undef	ungetc
#define ungetc(x,y) 	th_ungetc(x,y)
#undef  getc
#define getc(x) 		th_getc(x)
#define fgetc(x)		th_getc(x)
#define fgets(x,y,z)	th_fgets(x,y,z)
#define fclose(x)		th_fclose(x)
#define mktemp(x)		th_mktemp(x) 
#define tmpfile 		th_tmpfile
#define freopen(x,y,z)	th_freopen(x,y,z)
#define fdopen(x,y)		th_fdopen(x,y)
#define fopen(x,y)		th_fopen(x,y)
/** @note link and unlink are in thunistd.h. */
#define fwrite(x,y,z,w)	th_fwrite(x,y,z,w)
#define fread(x,y,z,w)	th_fread(x,y,z,w)
#define ftell(x)		th_ftell(x)
#define fseek(x,y,z)	th_fseek(x,y,z)
/** Requires va_list. */
#define vfprintf		th_vfprintf
#define fprintf 		th_fprintf
#define fflush(x)		th_fflush(x)
#define scanf			th_scanf
#define fscanf			th_fscanf
#define sscanf			th_sscanf
/** Requires va_list. */
#define vscanf(x,y)		th_vscanf(x,y)
/** Requires va_list. */
#define vsscanf(x,y,z)	th_vsscanf(x,y,z)
#define vfscanf(x,y,z)	th_vfscanf(x,y,z)
#define pclose(x)		th_pclose(x)
#define popen(x,y)		th_popen(x,y)
#endif


#ifdef __cplusplus
}
#endif
#endif /* file sentinel */
/** @} */
/** @} */
