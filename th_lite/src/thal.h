/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
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
