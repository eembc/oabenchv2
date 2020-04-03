/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#ifndef THSTDINT_H
#define THSTDINT_H

/** Get tool chain capabilities. */
#include "thconfig.h"

/** Build a sentinel for these definitions, libc's don't have them generally. */
#ifndef	EE_STDINT_TYPES_DEFINED
#if		HAVE_STDINT_H
#include <stdint.h>
#define	EE_STDINT_TYPES_DEFINED	1
#elif	HAVE_INTTYPES_H
#include <inttypes.h>

/** @note Solaris GCC has 64 bit integers, 
     but in 3.3.x these types are not enabled:( 
     in 3.4 these types are enabled:)
     the -pedantic option removes the compiler version flags,
     so you have to define this manually here for now.
     this is a compiler specific bug fix, so it won't
     be promoted to thconfig.h.
*/
#if 	0
typedef	long		int64_t;
typedef unsigned long	uint64_t;
#endif

#define	EE_STDINT_TYPES_DEFINED	1
#endif
/* #else block is within C++ area. */
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup SHAL
@{ */
/** @addtogroup THSTDINT_H Harness redirection for stdint.h
@{ */

/** @remark Porting: Define these for your architecture. 
Only used if tool chain doesn't have standard types.
*/
#ifndef	EE_STDINT_TYPES_DEFINED
typedef signed char             int8_t;
typedef short int               int16_t;
typedef int                     int32_t;
#ifdef	_MSC_VER
typedef __int64                 int64_t;
#else
typedef	long long               int64_t;
#endif
typedef unsigned char           uint8_t;
typedef unsigned short int      uint16_t;
typedef unsigned int            uint32_t;
#ifdef	_MSC_VER
typedef unsigned __int64        uint64_t;
#else
typedef	unsigned long long      uint64_t;
#endif
#define	EE_STDINT_TYPES_DEFINED	1
#endif

/**@remark former eembc_dt.h definitions */

/** Integral data types at least 64 bits in size. If your libc doesn't support this,
you can define this False, and use a smaller size data type.  */
#ifndef	HAVE_64
#define HAVE_64    (1)
#endif

/**
 * @remark EEMBC Standard Data Types
 * @note These definitions are benign, do not edit.
 */
#ifndef	EE_STDINT_EEMBC_DEFINED
typedef int8_t		e_s8;
typedef int16_t		e_s16;
typedef int32_t		e_s32;
typedef int64_t		e_s64;
typedef uint8_t		e_u8;
typedef uint16_t	e_u16;
typedef uint32_t	e_u32;
typedef uint64_t	e_u64;
#define	EE_STDINT_EEMBC_DEFINED	1
#endif


#ifdef __cplusplus
}
#endif
#endif /* file sentinel */

/** @} */
/** @} */
