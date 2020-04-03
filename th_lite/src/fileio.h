/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
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
