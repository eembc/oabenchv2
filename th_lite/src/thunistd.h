/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#ifndef THUNISTD_H
#define THUNISTD_H

/** Type for ee_pid_t. */
#include "thtypes.h"
#if		HAVE_UNISTD_H
#include <unistd.h>
#else
#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2
#endif

/** @addtogroup SHFL
@{ */
/** @addtogroup thunistd_h EEMBC Redirect for unistd.h
@{ */

#ifdef __cplusplus
extern "C" {
#endif

/** Don't redirect unless specified explicitly. */
#if 	!defined(EE_REDIRECT)
#define	EE_REDIRECT	0
#endif

/** libc getenv */
char	*th_getenv(const char *key);
/** libc getpid Get Process ID */
ee_pid_t th_getpid(void);

int		 th_open	(const char *pathname, int flags);
int 	 th_close	(int fildes);
size_t	 th_read	(int fd, void *buf, size_t count);
size_t	 th_write	(int fd, const void *buf, size_t count);
ee_off_t th_lseek	(int fildes, ee_off_t offset, int whence);

int		th_fsync(int fildes);
int		th_isatty(int fildes);
int 	th_dup(int oldfd);
int 	th_dup2(int oldfd, int newfd);
int		th_unlink(const char *filename);
int 	th_link(const char *oldpath, const char *newpath);

/** This is from io.h windows only. 
@note This declaration can conflict with some gcc unistd.h files, use this
flag to remove the local declaration.
*/
#if 	!HAVE_DECL_SETMODE
int 	setmode(int fd, int mode);
#endif

#if 	EE_REDIRECT
#define open(x,y,z)		th_open(x,y)
#define read(x,y,z)		th_read(x,y,z)
#define write(x,y,z)	th_write(x,y,z)
#define close(x)		th_close(x)
#define lseek(x,y,z)	th_lseek(x,y,z)
#define getenv(x)		th_getenv(x)
#define pid_t			ee_pid_t
#define getpid			th_getpid
#define fsync(x)		th_fsync(x)
#define isatty(x)		th_isatty(x)
#define dup(x)			th_dup(x)
#define dup2(x,y)		th_dup2(x,y)
#define unlink(x)		th_unlink(x)
#define link(x,y)		th_link(x,y)
#define setmode(x,y)	/* */
#endif

#ifdef __cplusplus
}
#endif
#endif /* file sentinel */
/** @} */
/** @} */
