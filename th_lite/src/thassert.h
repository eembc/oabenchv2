/**
 * @file
 * @brief  Test Harness assert functions
 *
 * $RCSfile: thassert.h,v $
 *
 *  EEMBC : EEMBC Technical Advisory Group (TechTAG)
 *
 * @author  ECL, LLC
 *
 *    CVS : $Revision: 1.12 $
 *          $Date: 2005/12/02 23:53:36 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/techtag/th_lite/src/thassert.h,v $
 *          
 * @note   
 *
 *
 * HISTORY :
 *
 * $Log: thassert.h,v $
 * Revision 1.12  2005/12/02 23:53:36  rick
 * Fix mixed EOL format causing ^M's to appear in Unix checkouts.
 *
 * Revision 1.11  2005/09/10 04:02:24  rick
 * eol update, add uu_send_file
 *
 * Revision 1.10  2005/04/27 20:33:14  rick
 * Copyrite update 2005
 *
 * Revision 1.9  2004/12/08 23:27:18  rick
 * New standard header for documentation generation.
 *
 * Revision 1.8  2004/06/29 19:36:22  rick
 * EE_REDIRECT, and Shared file for Regular and Lite
 *
 * Revision 1.7  2004/06/23 05:55:24  rick
 * EE_REDIRECT, and Shared Files
 *
 * Revision 1.6  2004/01/22 00:56:52  rick
 * Release cleanup, copyright year corrections
 *
 * Revision 1.5  2003/12/18 20:14:19  rick
 * Bug #242: The assert function uses different parameters in debug and non-debug modes
 *
 * Revision 1.4  2003/02/03 19:18:22  rick
 * Fix eol characters
 *
 * Revision 1.3  2002/10/28 22:33:53  rick
 * Unix2dos
 *
 * Revision 1.2  2002/05/23 16:31:52  rick
 * Bug #169, #170, #172, #173: Char/assert fixes
 *
 * Revision 1.1  2002/05/22 17:55:20  rick
 * Replace assert.h with thassert.h, add assert functions to th lite.
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
#if   !defined(THASSERT_H)
#define THASSERT_H

/** Get HAVE_ASSERT_H */
#include	"thconfig.h"

/** If the tool chain has assert.h, use it instead of these routines. */
#if		HAVE_ASSERT_H
#include	<assert.h>
#endif

/** @addtogroup SHFL
@{ */
/** @addtogroup thassert_h Test Harness assert functions.
@{ */
#if		!HAVE_ASSERT_H
#ifdef __cplusplus
extern "C" {
#endif

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * assert functions coded to harness
*/

#ifndef NDEBUG
extern void __assertfail( const char *msg, const char *cond, const char *file, int line );

#define assert(p)   ((p) ? ((void)0) : \
                     __assertfail( "\n** ASSERT : %s, file %s, line %d\n", \
                     #p, __FILE__, __LINE__ ))
#else
#define assert(p) ((void)0)
#endif

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * fatal error  (just like assert, but always triggers)
*/

#ifndef NDEBUG
extern void __fatal( const char* msg, const char* file, int line );

#define fatal()     (__fatal( "\n** FATAL : file %s, line %d\n",  \
                        __FILE__, __LINE__ ) )
#else
#define fatal()   ((void)0)
#endif


#ifdef __cplusplus
}
#endif
#endif /* !HAVE_ASSERT_H */
#endif /* File sentinal */
/** @} */
/** @} */
