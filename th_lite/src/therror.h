/**
 * @file
 * @brief  Test Harness error routines
 *
 * $RCSfile: therror.h,v $
 *
 * @author  ECL, LLC
 *
 *  EEMBC : Technical Advisory Group (TechTAG)
 *
 *    CVS : $Revision: 1.21 $
 *          $Date: 2005/12/02 23:53:36 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/techtag/th_lite/src/therror.h,v $
 *          
 * @note   
 *
 *
 * HISTORY :
 *
 * $Log: therror.h,v $
 * Revision 1.21  2005/12/02 23:53:36  rick
 * Fix mixed EOL format causing ^M's to appear in Unix checkouts.
 *
 * Revision 1.20  2005/09/10 04:02:24  rick
 * eol update, add uu_send_file
 *
 * Revision 1.19  2005/04/27 20:33:14  rick
 * Copyrite update 2005
 *
 * Revision 1.18  2004/12/08 23:27:18  rick
 * New standard header for documentation generation.
 *
 * Revision 1.5  2004/06/23 05:55:24  rick
 * EE_REDIRECT, and Shared Files
 *
 * Revision 1.4  2004/01/22 00:56:52  rick
 * Release cleanup, copyright year corrections
 *
 * Revision 1.3  2002/03/23 00:41:19  rick
 * Fix misspelling THE_FAILURE
 *
 * Revision 1.2  2002/03/21 22:31:10  rick
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

/** @addtogroup SHFL
@{ */
/** @addtogroup therror_h Test Harness error routines
@{ */

#ifndef   TH_ERROR_H     /* File Sentinal */
#define   TH_ERROR_H

#ifdef __cplusplus
extern "C" {
#endif

   /*------------------------------------------------------------------------------
    * Error return values
   */
   enum TH_ERRORS
      {
      THE_SUCCESS,            /* Success! */
      THE_FAILURE,             /* Generic Falure... :( */

      THE_BAD_PTR,            /* a pointer parameter was NULL */
      THE_BAD_THDEF_VERSION,  /* the THDef pointer did not point to a valid structure */
      THE_BAD_TCDEF_VERSION,  /* the THDef pointer did not point to a valid structure */
      THE_TC_INIT_FAILED,     /* The test component intialization failed */
      THE_BAD_BASE_PTR,       /* Bad base pointer for Malloc init */
      THE_BAD_SIZE,           /* The size parameter is bad */
      THE_OUT_OF_MEMORY       /* The test ran out of memory */
      };

   const char *th_error_str( int error );

   /*----------------------------------------------------------------------------*/

#ifdef __cplusplus
   }
#endif
#endif                /* File Sentinal */
/** @} */
/** @} */
