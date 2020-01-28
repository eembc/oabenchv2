/**
 * @file
 * @brief  EEMBC Redirect for malloc.h, a subset of stdlib.h
 *
 * $RCSfile: thmalloc.h,v $
 *
 *  EEMBC : EEMBC Technical Advisory Group (TechTAG)
 *
 * @author  Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.1 $
 *          $Date: 2006/03/09 17:34:18 $
 *          $Author: rick $
 *          $Source: /usr/local/cvs/eembc2/th_lite/src/thmalloc.h,v $
 *          
 * @note   
 *
 *
 * HISTORY :
 *
 * $Log: thmalloc.h,v $
 * Revision 1.1  2006/03/09 17:34:18  rick
 * Version 2 Office Release Candidate 5
 *
 * Revision 1.10  2005/12/02 23:53:38  rick
 * Fix mixed EOL format causing ^M's to appear in Unix checkouts.
 *
 * Revision 1.9  2005/09/10 04:02:24  rick
 * eol update, add uu_send_file
 *
 * Revision 1.8  2005/04/27 20:33:15  rick
 * Copyrite update 2005
 *
 * Revision 1.7  2004/12/08 23:27:19  rick
 * New standard header for documentation generation.
 *
 * Revision 1.5  2004/07/03 03:13:59  rick
 * Add time, link, and exit to redirection.
 *
 * Revision 1.4  2004/07/02 18:00:05  rick
 * Return without th_exec if user requests Null buffer of size 0.
 *
 * Revision 1.3  2004/06/29 19:36:23  rick
 * EE_REDIRECT, and Shared file for Regular and Lite
 *
 * Revision 1.2  2004/06/23 05:55:24  rick
 * EE_REDIRECT, and Shared Files
 *
 * Revision 1.1  2004/06/14 18:02:20  rick
 * Bug 274: Precision in log files is not large enough for reporting results on simulators.
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

/** @addtogroup SHFL
@{ */
/** @addtogroup thmalloc_h EEMBC Redirect for malloc.h, a subset of stdlib.h.
@{ */

/** File Sentinal */
#ifndef   THMALLOC_H
#define   THMALLOC_H

/** @note You may need to bring in size_t definition manually. */

#ifdef __cplusplus
extern "C" {
#endif

/** Don't redirect unless specified explicitly. */
#if 	!defined(EE_REDIRECT)
#define	EE_REDIRECT	0
#endif

/* Memory Management, must have size_t defined. */

#define th_malloc( size ) th_malloc_x( size, __FILE__, __LINE__ )
void *th_malloc_x( size_t size, const char *file, int line );
#define th_calloc( nmemb, size ) th_calloc_x( nmemb, size, __FILE__, __LINE__ )
void *th_calloc_x( size_t nmemb, size_t size, const char *file, int line );
#define th_realloc( blk, size ) th_realloc_x( blk, size, __FILE__, __LINE__ )
void *th_realloc_x( void *blk, size_t size, const char *file, int line );
#define th_free( blk ) th_free_x( blk, __FILE__, __LINE__ )
void    th_free_x( void *blk, const char *file, int line );
void    th_heap_reset( void );

#if		defined(EE_REDIRECT) && EE_REDIRECT
#define	malloc(x)   	th_malloc(x)
#define	calloc(x,y) 	th_calloc(x,y)
#define realloc(x,y)	th_realloc(x,y)
#define free(x)			th_free(x)
/** @warning strdup re-direction conflicts with string.h, and stdlib.h. 
             See thstring.h for strdup.
*/
#endif /* EE_REDIRECT */

#ifdef __cplusplus
}
#endif
#endif /* File Sentinel */ 
/** @} */
/** @} */
