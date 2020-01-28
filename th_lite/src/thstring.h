/**
 * @file
 * @brief  EEMBC Redirect for string.h
 *
 * $RCSfile: thstring.h,v $
 *
 *  EEMBC : EEMBC Technical Advisory Group (TechTAG)
 *
 * @author  Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.1 $
 *          $Date: 2006/03/09 17:34:18 $
 *          $Author: rick $
 *          $Source: /usr/local/cvs/eembc2/th_lite/src/thstring.h,v $
 *          
 * @note   
 *          This header file contains the interface fuctions and
 *          structures for the Test Harness Library, which implements
 *          the API.
 *
 *
 * HISTORY :
 *
 * $Log: thstring.h,v $
 * Revision 1.1  2006/03/09 17:34:18  rick
 * Version 2 Office Release Candidate 5
 *
 * Revision 1.10  2005/12/02 23:53:39  rick
 * Fix mixed EOL format causing ^M's to appear in Unix checkouts.
 *
 * Revision 1.9  2005/09/10 04:02:24  rick
 * eol update, add uu_send_file
 *
 * Revision 1.8  2005/04/27 20:33:15  rick
 * Copyrite update 2005
 *
 * Revision 1.7  2005/04/27 16:05:07  rick
 * Add HAVE_CTYPE_H, re-order headers in doscan.c, and correct type sign in fileio.c to remove warnings.
 *
 * Revision 1.3  2004/12/08 23:27:47  rick
 * New standard header for documentation generation.
 *
 * Revision 1.2  2004/06/29 19:36:23  rick
 * EE_REDIRECT, and Shared file for Regular and Lite
 *
 * Revision 1.1  2004/06/23 05:55:24  rick
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

/** File Sentinal */
#ifndef   THSTRING_H
#define   THSTRING_H

/** @addtogroup SHFL
@{ */
/** @addtogroup thstring_h EEMBC Redirect for string.h
@{ */

#ifdef __cplusplus
extern "C" {
#endif

/** Don't redirect unless specified explicitly. */
#if 	!defined(EE_REDIRECT)
#define	EE_REDIRECT	0
#endif

/* Memory Management from string.h */

/** Most compilers have strdup, but do not define it or define it in a variety of 
locations. This avoids extern returning int warnings in thal.c, but 
in some cases causes problems. Use HAVE_DECL_STRDUP flag to control things.
*/
#if		!HAVE_DECL_STRDUP
char	*strdup(const char *);
#endif

/** @note Re-direction may need to occur first to pick up th_strdup_x redirection. Redirection failure
will occur in link on symbol _th_strdup. */
#if		EE_REDIRECT
/** strdup re-direction can conflict between string.h, and stdlib.h */
#define	strdup(x)		th_strdup(x)
#endif

/** We use bcopy if available. */
#if		HAVE_BCOPY
#define	memcpy(dest,src,len)	bcopy(src,dest,len)
#endif

/** strdup defined with __FILE__ and __LINE__ for Harness out of memory reporting. */
char *th_strdup_x( const char *string, const char *file, int line );
/** Always redirect th_strdup to harness routine adding FILE and LINE. */
#define th_strdup( string ) th_strdup_x( string, __FILE__, __LINE__ )

#ifdef __cplusplus
}
#endif
#endif /* THSTRING_H */ 
/** @} */
/** @} */
