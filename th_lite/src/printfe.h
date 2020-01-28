/**
 * @file
 * @brief  Test Harness routines for benchmarks
 *
 * $RCSfile: printfe.h,v $
 *
 * @author  ECL, LLC
 *
 *  EEMBC : Technical Advisory Group (TechTAG)
 *
 *    CVS : $Revision: 1.3 $
 *          $Date: 2006/03/09 17:34:18 $
 *          $Author: rick $
 *          $Source: /usr/local/cvs/eembc2/th_lite/src/printfe.h,v $
 *          
 * @note   
 *
 *
 * HISTORY :
 *
 * $Log: printfe.h,v $
 * Revision 1.3  2006/03/09 17:34:18  rick
 * Version 2 Office Release Candidate 5
 *
 * Revision 1.12  2005/12/02 23:53:35  rick
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
 * Revision 1.6  2004/06/23 05:55:23  rick
 * EE_REDIRECT, and Shared Files
 *
 * Revision 1.5  2004/01/22 00:56:52  rick
 * Release cleanup, copyright year corrections
 *
 * Revision 1.4  2002/12/07 00:46:01  rick
 * MPEG 4 data files
 *
 * Revision 1.3  2002/10/31 21:34:15  rick
 * Move thpf_sender to printfe
 *
 * Revision 1.2  2002/03/21 22:31:09  rick
 * Network Harness, and empty benchmark fixes
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

#ifndef   PRINTFE_H
#define   PRINTFE_H

#include "thcfg.h"
#if		HAVE_STDARG_H
#include <stdarg.h>
#endif

/** @addtogroup SHFL
@{ */
/** @addtogroup printfe_c Functional Layer Printf Engine
@{ */

/** Compile out if not being used. */
#if USE_TH_PRINTF

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*sender) ( char c, void *ptr );

int printfe( sender sf, void *ptr, const char *fmt, va_list args );

int sprintf( char *s, const char *fmt, ... );
int vsprintf( char *s, const char *fmt, va_list args );
int thpf_sender( char c, void *ptr );

#ifdef __cplusplus
   }
#endif
#endif /* USE_TH_PRINTF */
#endif /* file sentinal */
/** @} */
/** @} */
