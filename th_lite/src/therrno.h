/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#ifndef THERRNO_H
#define THERRNO_H

/** Get autoconf definitions */
#include "thconfig.h"

/** Use Toolchain defines if possible. */
#if		HAVE_ERRNO_H
#include <errno.h>
#elif	HAVE_SYS_ERRNO_H
#include <sys/errno.h>
#endif

/** @addtogroup SHFL
@{ */
/** @addtogroup therrno_h EEMBC Redirect for errno.h
@{ */

#ifdef __cplusplus
extern "C" {
#endif

/** Definitions inside of local c++ extern. Keep in sync with ERRNO definitions above. */
#if		(!HAVE_ERRNO_H && !HAVE_SYS_ERRNO_H) || NEED_ERRNO_DEFINES
/** End of file, this is almost always -1.
@warning EOF can be defined by errno.h OR stdio.h */
#ifndef	EOF
#define EOF             -1
#endif

/* Need all definitions. */

#undef	NEED_ERANGE
#define NEED_ERANGE 	1
#undef	NEED_ENOTDIR
#define NEED_ENOTDIR 	1
#undef	NEED_EACCES
#define NEED_EACCES 	1
#undef	NEED_EBADF
#define NEED_EBADF  	1
#undef	NEED_EINVAL
#define NEED_EINVAL 	1
#undef	NEED_ENOENT
#define NEED_ENOENT 	1
#undef	NEED_EEXIST
#define NEED_EEXIST 	1
#undef	NEED_EFAULT
#define NEED_EFAULT 	1
#undef	NEED_ENOMEM
#define NEED_ENOMEM 	1
#undef	NEED_EPERM
#define NEED_EPERM  	1
#undef	NEED_ESRCH
#define NEED_ESRCH  	1

#endif /* HAVE_ERRNO. */

/* Select errno definitions to define. */

#if 	NEED_ERANGE && !defined(ERANGE)
#define ERANGE	define_ERANGE
#endif
#if 	NEED_ENOTDIR && !defined(ENOTDIR)
#define ENOTDIR	define_ENOTDIR
#endif
#if 	NEED_EACCES && !defined(EACCES)
#define EACCES	define_EACCES
#endif
#if 	NEED_EBADF && !defined(EBADF)
#define EBADF	define_EBADF
#endif
#if 	NEED_EINVAL && !defined(EINVAL)
#define EINVAL	define_EINVAL
#endif
#if 	NEED_ENOENT && !defined(ENOENT)
#define ENOENT	define_ENOENT
#endif
#if 	NEED_EEXIST && !defined(EEXIST)
#define EEXIST	define_EEXIST
#endif
#if 	NEED_EFAULT && !defined(EFAULT)
#define EFAULT	define_EFAULT
#endif
#if 	NEED_ENOMEM && !defined(ENOMEM)
#define ENOMEM	define_ENOMEM
#endif
#if 	NEED_EPERM && !defined(EPERM)
#define EPERM	define_EPERM
#endif
#if 	NEED_ESRCH && !defined(ESRCH)
#define ESRCH	define_ESRCH
#endif


#ifdef __cplusplus
}
#endif
#endif /* file sentinel */
/** @} */
/** @} */
