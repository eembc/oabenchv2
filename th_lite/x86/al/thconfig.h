/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#ifndef THCONFIG_H
#define THCONFIG_H

/** Get overrides to configuration. */
#include "harness.h"

/** @addtogroup SHAL
@{ */
/** @addtogroup THCONFIG_H Test Harness Toolchain Header File and Function Configuration
@{ */

#ifdef __cplusplus
extern "C" {
#endif

/* EEMBC related flags for tool chain capabilities. */

/**
 * @remark A list of compiler capabilities. Intended usage is
 * to identify POSIX compliant functions and headers, so all tool chains will be
 * able to take advantage of this, and the harness code remains portable.
 *
 * @note This is slightly different in that the TRUE/FALSE are used rather than
 * #define 1/#undef. The #ifndef wrapper can then be activated allowing the variable 
 * to be set to true or false externally. Autoheader does not support this.
 * @warning You cannot use #ifdef/#ifndef with these structures. But most professional
 * Autoheader people use #if's anyway which resolve to false on undefined symbols:). It's
 * a necessary tradeoff.
 * @note While strdup is a malloc/free variant, it may be possible for a libc to have malloc,
 * and not have implemented strdup in string.h.
 */

/** Define to 1 if your libc has the `isdigit' function. */
#if !defined (HAVE_ISDIGIT)
#define HAVE_ISDIGIT 1
#endif

/** Define to 1 if your libc has the `memcpy' function (uses malloc/free). */
#if !defined (HAVE_MEMCPY)
#define HAVE_MEMCPY 1
#endif

/** Define to 1 if your libc has the `bcopy' function (uses malloc/free). */
#if !defined (HAVE_BCOPY)
#define HAVE_BCOPY 0
#endif

/** Define to 1 if your libc has the `setmode' function. 
@warning The setmode function is not used, and redirected to null.
*/
#if !defined (HAVE_SETMODE)
#define HAVE_SETMODE 1
#endif

/** Define to 1 if your libc has the `setmode' function declared (unistd.h). 
@warning The setmode function is not used, and redirected to null.
*/
#if !defined (HAVE_DECL_SETMODE)
#define HAVE_DECL_SETMODE 1
#endif

/** Define to 1 if your libc has the `strdup' function (uses malloc/free). */
#if !defined (HAVE_STRDUP)
#if  defined(_MSC_VER)
#define HAVE_DECL_STRDUP 0
#else
#define HAVE_DECL_STRDUP 1
#endif
#endif

/** Define to 1 if your libc has the `strdup' function declaration. */
#if !defined (HAVE_DECL_STRDUP)
#define HAVE_DECL_STRDUP 1
#if	defined(UNDER_CE)
#define	strdup(x)	_strdup(x)
#endif
#endif
/** Define to 1 if your libc has the `strtoll' function.
@note Harness uses this in doscan.c
*/
#if		!defined(HAVE_STRTOLL)
#ifdef _MSC_VER
#define HAVE_STRTOLL 0
#else
#define HAVE_STRTOLL 1
#endif
#endif

/** Define to 1 if your libc has the `strtod' function.
@note Harness uses this in doscan.c only on long double path.
*/
#if !defined(HAVE_STRTOD)
#define	HAVE_STRTOD	1
#endif

/** Define to 1 if your libc has the `popen' function. */
#if !defined (HAVE_POPEN)
#define HAVE_POPEN 1
#endif

/** Define to 1 if your libc has the `pclose' function. */
#if !defined (HAVE_PCLOSE)
#define HAVE_PCLOSE 1
#endif

/** Define to 1 if your libc has the `clock' function. */
#if !defined (HAVE_CLOCK)
#define HAVE_CLOCK 1
#endif

/** Define to 1 if your libc has the `getenv' function. */
#if !defined (HAVE_GETENV)
#if defined(UNDER_CE)
#define HAVE_GETENV 0
#else
#define HAVE_GETENV 1
#endif
#endif

/** Set this define to 1 if your compiler has stdarg.h. */
#if !defined (HAVE_STDARG_H)
#define HAVE_STDARG_H 1
#endif

/** Set this define to 1 if your compiler has ctype.h. */
#if !defined (HAVE_CTYPE_H)
#define HAVE_CTYPE_H 1
#endif

/** Set this define to 1 if your compiler has assert.h. */
#if !defined (HAVE_ASSERT_H)
#define HAVE_ASSERT_H 1
#endif

/** Set this define to 1 if your compiler has errno.h. */
#if !defined (HAVE_ERRNO_H)
#define HAVE_ERRNO_H 1
#endif

/** Set this define to 1 if your compiler has sys/errno.h. */
#if !defined (HAVE_SYS_ERRNO_H)
#define HAVE_SYS_ERRNO_H 0
#endif

/** 
\note If your toolchain has Incomplete Errno definitions, 
define just the ones you need here.

\note If you need a definition, define NEED_<definition> 1.

\note If you need to set errno.h defines to a non-conflicting value,
define define_<definition> <non-conflicting value>.

*/

/** Set this to 1 if your compiler does NOT have this errno.h define. */
#if 	!defined(NEED_ERANGE)
/** Common POSIX value for errno.h define. */
#define	NEED_ERANGE	0
#endif
/** Set this to 1 if your compiler does NOT have this errno.h define. */
#if 	!defined(define_ERANGE)
/** Common POSIX value for errno.h define. */
#define define_ERANGE	34
#endif
/** Set this to 1 if your compiler does NOT have this errno.h define. */
#if 	!defined(NEED_ENOTDIR)
/** Common POSIX value for errno.h define. */
#define	NEED_ENOTDIR	0
#endif
/** Set this to 1 if your compiler does NOT have this errno.h define. */
#if 	!defined(define_ENOTDIR)
/** Common POSIX value for errno.h define. */
#define define_ENOTDIR	12
#endif
/** Set this to 1 if your compiler does NOT have this errno.h define. */
#if 	!defined(NEED_EACCES)
/** Common POSIX value for errno.h define. */
#define	NEED_EACCES	0
#endif
/** Set this to 1 if your compiler does NOT have this errno.h define. */
#if 	!defined(define_EACCES)
/** Common POSIX value for errno.h define. */
#define define_EACCES	13
#endif
/** Set this to 1 if your compiler does NOT have this errno.h define. */
#if 	!defined(NEED_EBADF)
/** Common POSIX value for errno.h define. */
#define	NEED_EBADF	0
#endif
/** Set this to 1 if your compiler does NOT have this errno.h define. */
#if 	!defined(define_EBADF)
/** Common POSIX value for errno.h define. */
#define define_EBADF	9
#endif
/** Set this to 1 if your compiler does NOT have this errno.h define. */
#if 	!defined(NEED_EINVAL)
/** Common POSIX value for errno.h define. */
#define	NEED_EINVAL	0
#endif
/** Set this to 1 if your compiler does NOT have this errno.h define. */
#if 	!defined(define_EINVAL)
/** Common POSIX value for errno.h define. */
#define define_EINVAL	22
#endif
/** Set this to 1 if your compiler does NOT have this errno.h define. */
#if 	!defined(NEED_ENOENT)
/** Common POSIX value for errno.h define. */
#define	NEED_ENOENT	0
#endif
/** Set this to 1 if your compiler does NOT have this errno.h define. */
#if 	!defined(define_ENOENT)
/** Common POSIX value for errno.h define. */
#define define_ENOENT	2
#endif
/** Set this to 1 if your compiler does NOT have this errno.h define. */
#if 	!defined(NEED_EEXIST)
/** Common POSIX value for errno.h define. */
#define	NEED_EEXIST	0
#endif
/** Set this to 1 if your compiler does NOT have this errno.h define. */
#if 	!defined(define_EEXIST)
/** Common POSIX value for errno.h define. */
#define define_EEXIST	17
#endif
/** Set this to 1 if your compiler does NOT have this errno.h define. */
#if 	!defined(NEED_EFAULT)
/** Common POSIX value for errno.h define. */
#define	NEED_EFAULT	0
#endif
/** Set this to 1 if your compiler does NOT have this errno.h define. */
#if 	!defined(define_EFAULT)
/** Common POSIX value for errno.h define. */
#define define_EFAULT	1
#endif
/** Set this to 1 if your compiler does NOT have this errno.h define. */
#if 	!defined(NEED_ENOMEM)
/** Common POSIX value for errno.h define. */
#define	NEED_ENOMEM	0
#endif
/** Set this to 1 if your compiler does NOT have this errno.h define. */
#if 	!defined(define_ENOMEM)
/** Common POSIX value for errno.h define. */
#define define_ENOMEM	5
#endif
/** Set this to 1 if your compiler does NOT have this errno.h define. */
#if 	!defined(NEED_EPERM)
/** Common POSIX value for errno.h define. */
#define	NEED_EPERM	0
#endif
/** Set this to 1 if your compiler does NOT have this errno.h define. */
#if 	!defined(define_EPERM)
/** Common POSIX value for errno.h define. */
#define define_EPERM	7
#endif
/** Set this to 1 if your compiler does NOT have this errno.h define. */
#if 	!defined(NEED_ESRCH)
/** Common POSIX value for errno.h define. */
#define	NEED_ESRCH	0
#endif
/** Set this to 1 if your compiler does NOT have this errno.h define. */
#if 	!defined(define_ESRCH)
/** Common POSIX value for errno.h define. */
#define define_ESRCH	8
#endif


/** Set this define to 1 if your compiler has getpid.
@note used only in HOST_EXAMPLE_CODE. */
#if !defined (HAVE_GETPID)
#if  defined(_MSC_VER)
#define HAVE_GETPID 0
#else
#define HAVE_GETPID 1
#endif
#endif

/** Set this define to 1 if your compiler has dirent.h*/
#if !defined (HAVE_DIRENT_H)
#if  defined(_MSC_VER) || defined(UNDER_CE)
#define HAVE_DIRENT_H 0
#else
#define HAVE_DIRENT_H 1
#endif
#endif

/** Define to 1 if you have the <sys/dir.h> header file, and it defines `DIR'.*/
#if 	!defined(HAVE_SYS_DIR_H)
#define HAVE_SYS_DIR_H 0
#endif

/** Define to 1 if you have the <sys/ndir.h> header file, and it defines `DIR'.*/
#if 	!defined(HAVE_SYS_NDIR_H)
#define HAVE_SYS_NDIR_H 0
#endif

/** Define to 1 if you have the <ndir.h> header file, and it defines `DIR'.*/
#if 	!defined(HAVE_NDIR_H)
#define HAVE_NDIR_H 0
#endif

/** Define to 1 if you have dirent functions. You may or may not have dirent.h */
#ifndef HAVE_DIRENT	
#define HAVE_DIRENT	1
#endif

/** Set this define to 1 if your compiler has unistd.h (chdir) */
#if !defined (HAVE_UNISTD_H)
#if  defined(_MSC_VER)
#define HAVE_UNISTD_H 0
#else
#define HAVE_UNISTD_H 1
#endif
#endif

/** Set this 1 if your compiler has stat.h, specific to Metrowerks not POSIX */
#if !defined(HAVE_STAT_H)
#define	HAVE_STAT_H	0
#endif

/** Set this 1 if your compiler has sys/stat.h */
#if !defined(HAVE_SYS_STAT_H)
#ifdef	UNDER_CE
#define	HAVE_SYS_STAT_H	0
#else
#define	HAVE_SYS_STAT_H	1
#endif
#endif

/** Define to 1 if `st_blksize' is member of `struct stat'. */
#if 	!defined(HAVE_STRUCT_STAT_ST_BLKSIZE)
#define HAVE_STRUCT_STAT_ST_BLKSIZE 1
#endif

/** Define to 1 if `st_blocks' is member of `struct stat'. */
#if 	!defined(HAVE_STRUCT_STAT_ST_BLOCKS)
#define HAVE_STRUCT_STAT_ST_BLOCKS 1
#endif

/** Define to 1 if `fsize_t' is used to define `st_size' in `struct stat'. */
#if 	!defined(HAVE_STRUCT_STAT_FSIZE_T)
#if 	_MSC_VER
#define HAVE_STRUCT_STAT_FSIZE_T	1
#else
#define HAVE_STRUCT_STAT_FSIZE_T	0
#endif
#endif

/** Define to 1 if you have the `vfscanf' function. */
#if  defined(_MSC_VER)
#define HAVE_VFSCANF 0
#else
#define HAVE_VFSCANF 1
#endif

/** Define to 1 if you have the `vprintf' function. */
#ifndef HAVE_VPRINTF 
#define HAVE_VPRINTF 1
#endif

/** Define to 1 if you have the `vprintf' function. */
#ifndef HAVE_VSPRINTF 
#define HAVE_VSPRINTF 1
#endif

/** Define to 1 if you have the `vprintf' function. */
#ifndef HAVE_VSNPRINTF 
#define HAVE_VSNPRINTF 1
#endif

/** Define to 1 if you don't have `vprintf' but do have `_doprnt.' */
/* #undef HAVE_DOPRNT */

/** Define to 1 if you have the `vscanf' function. */
#if  defined(_MSC_VER)
#define HAVE_VSCANF 0
#else
#define HAVE_VSCANF 1
#endif

/** Define to 1 if you have the `vsscanf' function. */
#if  defined(_MSC_VER)
#define HAVE_VSSCANF 0
#else
#define HAVE_VSSCANF 1
#endif

/** Define to 1 if you have the <limits.h> header file. */
#ifndef	HAVE_LIMITS_H
#define HAVE_LIMITS_H 1
#endif

/** If tool chain does not have limits.h, define number of bits per character. */
#if 	!HAVE_LIMITS_H
/** This is used in several benchmarks. */
#ifndef	CHAR_BIT
#define	CHAR_BIT	8
#endif
/** This is used in the harness doscan.c file. */
#ifndef	LONG_MAX
#define	LONG_MAX	0xFFFFFFFF
#endif
#endif

/** Define to 1 if you have the <sys/types.h> header file. */
#ifndef	HAVE_SYS_TYPES_H
#define HAVE_SYS_TYPES_H 1
#endif

/** Define to 1 if you have the <types.h> header file. */
#ifndef	HAVE_TYPES_H
#define HAVE_TYPES_H 0
#endif

/** Define to 1 if you have the <fcntl.h> header file. */
#ifndef	HAVE_FCNTL_H
#define HAVE_FCNTL_H 1
#endif

/** Define to 1 if sys/time.h should be included with time.h.  */
#ifndef	TIME_WITH_SYS_TIME
#ifdef	_MSC_VER
#define TIME_WITH_SYS_TIME 0
#else
#define TIME_WITH_SYS_TIME 1
#endif
#endif
/** Define to 1 if you have the <time.h> header file. */
#ifndef	HAVE_TIME_H
#define HAVE_TIME_H 1
#endif

/** Define to 1 if you have the <sys/time.h> header file. */
#ifndef	HAVE_SYS_TIME_H
#ifdef	_MSC_VER
#define HAVE_SYS_TIME_H 0
#else
#define HAVE_SYS_TIME_H 1
#endif
#endif

/** Define to 1 if you have the <sys/times.h> header file. */
#ifndef	HAVE_SYS_TIMES_H
#ifdef	_MSC_VER
#define HAVE_SYS_TIMES_H 0
#else
#define HAVE_SYS_TIMES_H 1
#endif
#endif

/** Define to 1 if you have the <dlfcn.h> header file. */
#ifndef HAVE_DLFCN_H 
#define HAVE_DLFCN_H 1
#endif

/** Define to 1 if you have the <stdint.h> header file. */
#ifndef HAVE_STDINT_H
#ifdef	_MSC_VER
#define HAVE_STDINT_H 0
#else
#define HAVE_STDINT_H 1
#endif
#endif

/** Define to 1 if you have the <inttypes.h> header file.
@note Generally this is found on Solaris.
*/
#ifndef HAVE_INTTYPES_H
#define HAVE_INTTYPES_H 0
#endif

/** Define to 1 if you have the <stdbool.h> header file. */
#ifndef HAVE_STDBOOL_H
#ifdef	_MSC_VER
#define HAVE_STDBOOL_H 0
#else
#define HAVE_STDBOOL_H 1
#endif
#endif

/** Define to 1 if you have the <io.h> header file.
@note This is Windows specific, cygwin gcc also supports it,
but most do not so we will disable it in general. */
#ifndef HAVE_IO_H
#ifdef _MSC_VER
#define HAVE_IO_H 1
#else
#define HAVE_IO_H 0
#endif
#endif

/** Define to 1 if you have the `m' math library (-lm). */
#ifndef HAVE_LIBM
#define HAVE_LIBM 1
#endif

/** Define to 1 if you have the <memory.h> header file. */
#ifndef HAVE_MEMORY_H
#define HAVE_MEMORY_H 1
#endif


/** Define to 1 if you have the <stddef.h> header file.
@note SEE EE_NEED_SIZE_T.
*/
#ifndef HAVE_STDDEF_H
#define HAVE_STDDEF_H 1
#endif

/** Define to 1 if you have the <stdlib.h> header file. */
#ifndef HAVE_STDLIB_H
#define HAVE_STDLIB_H 1
#endif

/** Define to 1 if you have the <strings.h> header file. */
#ifndef HAVE_STRINGS_H
#define HAVE_STRINGS_H 1
#endif

/** Define to 1 if you have the <string.h> header file. */
#ifndef HAVE_STRING_H
#define HAVE_STRING_H 1
#endif

/** Have variable length arrays */
#ifndef HAVE_VLA
#ifdef	_MSC_VER
#define HAVE_VLA 0
#else
#define HAVE_VLA 1
#endif
#endif

/** Define to 1 if you have the <windows.h> header file. */
#ifndef HAVE_WINDOWS_H
#define HAVE_WINDOWS_H 1
#endif

/** Define to 1 if you have the hypot function in math.h.
@code
#  define hypot(x,y) sqrt((double)(x)*(x)+(double)(y)*(y))
@endcode
*/
#ifndef HAVE_HYPOT
#define HAVE_HYPOT 1
#endif

/** Define to 1 if you have the time function in time.h.
@note Deprecated, but called in Ghostscript. Usually found in compilers without
sys/time.h.
See NEED_TIME for newlib link problems.
*/
#ifndef HAVE_TIME
#define HAVE_TIME 1
#endif

/** Define to 1 if you have the gettimeofday function in time.h. */
#ifndef HAVE_GETTIMEOFDAY
#ifdef	_MSC_VER
#define HAVE_GETTIMEOFDAY 0
#else
#define HAVE_GETTIMEOFDAY 1
#endif
#endif

/** Define to 1 if you have the link function in unistd.h.
@note See NEED_LINK for newlib link problems, ASSUMES UNLINK AS WELL.
*/
#ifndef HAVE_LINK
#ifdef	_MSC_VER
#define HAVE_LINK	0
#else
#define HAVE_LINK	1
#endif
#endif

/** Define to 1 if you have the read function. */
#ifndef HAVE_READ
#define HAVE_READ	1
#endif

/** Define to 1 if you have the write function. */
#ifndef HAVE_WRITE
#define HAVE_WRITE	1
#endif

/** Define to 1 if you have the lseek function. */
#ifndef HAVE_LSEEK
#define HAVE_LSEEK	1
#endif

/** Define to 1 if you have the clock function in sys/time.h.
@note See NEED_CLOCK for eVC link problems.
*/
#ifndef HAVE_CLOCK
#define HAVE_CLOCK	1
#endif

/** Define to 1 if you have the wchar_t defined in stdio.h.
@note See doscan.c if you are having compilation problems related to wchar_t.
*/
#ifndef NEED_WCHAR_T
#define NEED_WCHAR_T	0
#endif

/** Define to 1 if you have ulong defined in sys/types.h. 
Old compatibility names for C types, see __USE_MISC in sys/types.h.
@note Define to 0 for gcc 4.0.2x and above versions.
*/
#ifndef NEED_ULONG
#define	NEED_ULONG	1
#endif

/** Define to 1 if you have ushort defined in sys/types.h. 
Old compatibility names for C types, see __USE_MISC in sys/types.h.
@note Define to 0 for gcc 4.0.2x and above versions.
*/
#ifndef NEED_USHORT
#define	NEED_USHORT	1
#endif

/** Define to 1 if you have uint defined in sys/types.h. 
Old compatibility names for C types, see __USE_MISC in sys/types.h.
@note Define to 0 for gcc 4.0.2x and above versions.
*/
#ifndef NEED_UINT
#define	NEED_UINT	1
#endif

/** Define to 1 if you have uchar defined in sys/types.h. 
Old compatibility names for C types, see __USE_MISC in sys/types.h.
@note Define to 0 for gcc 4.0.2x and above versions.
*/
#ifndef NEED_UCHAR
#define	NEED_UCHAR	1
#endif

#ifdef __cplusplus
}
#endif
#endif /* THCONFIG_H file sentinel */
/** @} */
/** @} */
