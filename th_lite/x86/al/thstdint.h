/**
 * @file
 * @brief  Test Harness Toolchain Header file configuration
 *
 * $RCSfile: thstdint.h,v $
 *
 * @author  Rick Foos, ECL, LLC
 *
 *  EEMBC : Technical Advisory Group (TechTAG)
 *
 *    CVS : $Revision: 1.1 $
 *          $Date: 2006/03/09 17:34:19 $
 *          $Author: rick $
 *          $Source: /usr/local/cvs/eembc2/th_lite/x86/al/thstdint.h,v $
 *          
 * @note   
 * This is the replacement of eembc_dt.h for benchmark programs. Originally it was
 * designed for redirection of stdint.h types to eembc types. This causes a number
 * of recursions on some tool chains. The current approach is to completely use the
 * tool chain supplied types if available, and define them only if the tool chain's are
 * not available.
 *
 * HISTORY :
 *
 * $Log: thstdint.h,v $
 * Revision 1.1  2006/03/09 17:34:19  rick
 * Version 2 Office Release Candidate 5
 *
 * Revision 1.11  2005/07/16 03:08:31  rick
 * Merge updates for DSP environments
 *
 * Revision 1.10  2005/04/27 20:33:21  rick
 * Copyrite update 2005
 *
 * Revision 1.9  2004/12/08 23:27:27  rick
 * New standard header for documentation generation.
 *
 * Revision 1.7  2004/07/09 18:16:12  rick
 * Set sparc definition for gcc 3.4, and document usage.
 *
 * Revision 1.6  2004/07/08 03:41:19  rick
 * Add int64 definitions for Solaris
 *
 * Revision 1.5  2004/07/07 22:56:55  rick
 * Move thtypes to AL, add definitions to support sys/types
 *
 * Revision 1.4  2004/07/07 17:07:14  rick
 * Replace EEMBC type redirection with stdint definitions
 *
 * Revision 1.3  2004/07/03 04:43:01  rick
 * Trap int8_t definitions (e_s32 problem)
 *
 * Revision 1.2  2004/06/29 19:36:26  rick
 * EE_REDIRECT, and Shared file for Regular and Lite
 *
 * Revision 1.1  2004/06/23 05:55:27  rick
 * EE_REDIRECT, and Shared Files
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
