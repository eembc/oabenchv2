/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
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
