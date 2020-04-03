/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#ifndef THTYPES_H
#define THTYPES_H

/** Get tool chain capabilities. */
#include "thconfig.h"

#if HAVE_STDDEF_H
	#include <stddef.h>
#else
	/* basic types missing, must define these */
	typedef unsigned long size_t;
	#ifndef NULL
	#define NULL    ((void *)0)
	#endif
#endif

/** Build a sentinel for these includes and definitions, 
libc's may not have them.

@note Porting: there may be several files involved with
internal defines to only produce data types. Review your
tool chain for these differences.
*/
#ifndef	EE_SYSTYPES_TYPES_DEFINED
	#if		HAVE_SYS_TYPES_H
	#include <sys/types.h>
	#elif	HAVE_TYPES_H
	#include <types.h>
	#elif	HAVE_UNISTD_H
	#include <unistd.h>
	#endif
	/** The standard types come in through this file on Visual C. */
	#if		HAVE_IO_H
	#include	<io.h>
	#endif
	#if 	__TASKING__
	/** time_t only here (no sys/types)...*/
	#include	<time.h>
	#endif

	/* Set of Old Compatibility Types, __USE_MISC. */
	/** Define to 1 if you have ulong defined in sys/types.h. 
	Old compatibility names for C types, see __USE_MISC in sys/types.h.
	@note Define to 0 for gcc 4.0.2x and above versions.
	*/
	#if 	NEED_ULONG && !defined(ULONG_DEFINED) && !defined(__USE_MISC)
	#define ULONG_DEFINED
	typedef unsigned long ulong;
	#endif

	/** Define to 1 if you have ushort defined in sys/types.h. 
	Old compatibility names for C types, see __USE_MISC in sys/types.h.
	@note Define to 0 for gcc 4.0.2x and above versions.
	*/
	#if     NEED_USHORT && !defined(USHORT_DEFINED) && !defined(__USE_MISC)
	#define USHORT_DEFINED
	typedef unsigned short ushort;
	#endif

	/** Define to 1 if you have uint defined in sys/types.h. 
	Old compatibility names for C types, see __USE_MISC in sys/types.h.
	@note Define to 0 for gcc 4.0.2x and above versions.
	*/
	#if     NEED_UINT && !defined(UINT_DEFINED) && !defined(__USE_MISC)
	#define UINT_DEFINED
	typedef unsigned int uint;
	#endif

	/** Define to 1 if you have uchar defined in sys/types.h. 
	This is NOT an Old compatibility name for C types, see __USE_MISC in sys/types.h.
	@note Define to 1 .
	*/
	#if     NEED_UCHAR && !defined(UCHAR_DEFINED)
	#define UCHAR_DEFINED
	typedef unsigned char uchar;
	#endif

	/** Only define this if sys/types does nothing */
	#if 	!NEED_SYSTYPES

		#if 	!defined(_MSC_VER)
			/** GCC/glibc implementations might use off_t for fsize_t. */
			#if 	!HAVE_STRUCT_STAT_FSIZE_T
			typedef off_t	fsize_t;
			#endif

			/** GCC/newlib implementations don't have blksize_t, or blkcnt_t. */
			#if 	!HAVE_STRUCT_STAT_ST_BLKSIZE
			typedef	off_t	blksize_t;
			#endif
			#if 	!HAVE_STRUCT_STAT_ST_BLKCNT
			typedef off_t	blkcnt_t;
			#endif

		#define	EE_SYSTYPES_TYPES_DEFINED	1
		#endif
	#endif

/* #else block is within C++ area, and partial definitions. */
#endif

/** If we are going to define more elements, we need to make
sure that thstdint.h is brought in. It must be included outside
the C++ area.
*/
#ifndef	EE_SYSTYPES_TYPES_DEFINED
#include "thstdint.h"
#endif

/** @addtogroup SHAL
@{ */
/** @addtogroup THTYPES_H Harness types used in POSIX struct definitions
@{ */

#ifdef __cplusplus
extern "C" {
#endif

/** A good example of PARTIAL type definitions, and how to 
handle this for your compiler.
*/
#if		defined(_MSC_VER) && !defined(UNDER_CE)
/** The partial definitions contributed by sys/types.h. */
#define	off_t	_off_t
#define EE_OFF_T_DEFINED	1
#define ino_t	_ino_t
#define EE_INO_T_DEFINED	1
/** In a partial case, also define the ones that are spelled correctly. */
#define EE_TIME_T_DEFINED	1
/** The partial definitions contributed by io.h. */
#define	fsize_t		_fsize_t
#define EE_FSIZE_T_DEFINED	1
#endif


/** @warning including stdint causes conflicts. Must wrap all typedefs with sentinels.
	Since there is only one point of definition, we will only wrap the first one. 

    Inidividual control of the type definitions is given for compilers that do not
	define all of these. If a partial case occurs, we will enter this section
	defining only those that remain undefined.
*/
#ifndef	EE_SYSTYPES_TYPES_DEFINED
/** file size type. */
#ifndef	EE_FSIZE_T_DEFINED
typedef e_u32	fsize_t;
#endif
/** pid_t - Unix is usually 32 bit process ID's, and -1 is used, so it must be a signed type */
#ifndef	EE_PID_T_DEFINED
typedef e_s32	pid_t;
#endif
/** EEMBC file mode type */
#ifndef	EE_MODE_T_DEFINED
typedef	e_u16	mode_t;
#endif
/** EEMBC number of file links type */
#ifndef	EE_NLINK_T_DEFINED
typedef e_s16	nlink_t;
#endif
/** EEMBC block count type */
#ifndef	EE_BLKCNT_T_DEFINED
typedef e_u32	blkcnt_t;
#endif
/** EEMBC File size type. Keep in sync with ee_fsize_t used in ee_FILE. */
#ifndef	EE_OFF_T_DEFINED
typedef e_u32	off_t;
#endif
/** EEMBC inode type */
#ifndef	EE_INO_T_DEFINED
typedef e_u32	ino_t;
#endif
/** EEMBC time type. */
#ifndef	EE_TIME_T_DEFINED
typedef e_u32	time_t;
#define _TIME_T
#endif

#define	EE_SYSTYPES_TYPES_DEFINED	1
#endif

/**@remark former fileio.h definitions */

/**
 * @remark EEMBC Standard Data Types
 * @note These definitions are benign, do not edit.
 */
#ifndef	EE_SYSTYPES_EEMBC_DEFINED
typedef fsize_t		ee_fsize_t;
typedef pid_t		ee_pid_t;
typedef	mode_t		ee_mode_t;
typedef nlink_t		ee_nlink_t;
typedef blkcnt_t	ee_blkcnt_t;
typedef off_t		ee_off_t;
typedef ino_t		ee_ino_t;
typedef time_t		ee_time_t;
#define _TIME_T
#define	EE_SYSTYPES_EEMBC_DEFINED	1
#endif

#ifdef __cplusplus
}
#endif
#endif /* file sentinel */
/** @} */
/** @} */
