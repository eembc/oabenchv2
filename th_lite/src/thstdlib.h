/**
 * @file
 * @brief  EEMBC Redirect for stdlib.h
 *
 * $RCSfile: thstdlib.h,v $
 *
 *  EEMBC : EEMBC Technical Advisory Group (TechTAG)
 *
 * @author  Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.1 $
 *          $Date: 2006/03/09 17:34:18 $
 *          $Author: rick $
 *          $Source: /usr/local/cvs/eembc2/th_lite/src/thstdlib.h,v $
 *          
 * @note   
 *
 *
 * HISTORY :
 *
 * $Log: thstdlib.h,v $
 * Revision 1.1  2006/03/09 17:34:18  rick
 * Version 2 Office Release Candidate 5
 *
 * Revision 1.8  2005/12/02 23:53:38  rick
 * Fix mixed EOL format causing ^M's to appear in Unix checkouts.
 *
 * Revision 1.7  2005/09/10 04:02:24  rick
 * eol update, add uu_send_file
 *
 * Revision 1.6  2005/04/27 20:33:15  rick
 * Copyrite update 2005
 *
 * Revision 1.5  2004/12/08 23:27:19  rick
 * New standard header for documentation generation.
 *
 * Revision 1.2  2004/07/03 03:13:59  rick
 * Add time, link, and exit to redirection.
 *
 * Revision 1.1  2004/06/29 19:36:23  rick
 * EE_REDIRECT, and Shared file for Regular and Lite
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

/** Malloc is a subset of stdlib.h, must have size_t defined to use this. */
#include "thmalloc.h"

/** @addtogroup SHFL
@{ */
/** @addtogroup thstdlib_h EEMBC Redirect for stdlib.h
@{ */

/** File Sentinal */
#ifndef   THSTDLIB_H
#define   THSTDLIB_H
#ifdef __cplusplus
extern "C" {
#endif

/** Don't redirect unless specified explicitly. */
#if 	!defined(EE_REDIRECT)
#define	EE_REDIRECT	0
#endif

void	th_exit( int exit_code, const char *fmt, ... );

/** Use TH_RAND_MAX instead of stdlib.h RAND_MAX.
Test Harness Random Numbers (Uniform Distribution [0-128].
*/
#define TH_RAND_MAX	128
/** Internal harness random number generator. */
int 	th_rand( void );
/** Seed internal harness random number generator. */
void	th_srand(unsigned int seed);

#if		EE_REDIRECT

#define  exit(x)	th_exit(x,"Failure: %s : %d\n",__FILE__,__LINE__)

#undef	RAND_MAX
#define RAND_MAX	TH_RAND_MAX
#define rand(x)		th_rand(x)
#define srand(x)	th_srand(x)

#endif

#ifdef __cplusplus
}
#endif
#endif /* File Sentinel */
/** @} */
/** @} */
