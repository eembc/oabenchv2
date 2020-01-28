/**
 * @file
 * @brief  Test Harness Version Information
 *
 * $RCSfile: thvinfo.h,v $
 *
 * @author  ECL, LLC
 *
 *  EEMBC : Technical Advisory Group (TechTAG)
 *
 *    CVS : $Revision: 1.21 $
 *          $Date: 2005/10/24 14:55:35 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/techtag/th_lite/src/thvinfo.h,v $
 *          
 * @note   
 *
 *
 * HISTORY :
 *
 * Revision 1.3  2002/04/04 17:03:30  rick
 * thvinfo 4.0B1
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
/** @addtogroup THVINFO_H Test Harness Version Information
@{ */

/** File Sentinel */
#ifndef THVINFO_H
#define THVINFO_H

#ifdef __cplusplus
extern "C" {
#endif

/** Version Text displayed to the user.

This is a human readable form of the version number. It is manually kept
in sync with major, minor, step, and revision numbers.
The revision minor, step, and revision are related to CVS tags.
*/
#define EEMBC_TH_ID "EEMBC Portable Test Harness V4.3B16"

/** Major Release of Test Harness. */
#define EEMBC_TH_MAJOR         4
/** Minor Release of Test Harness. */
#define EEMBC_TH_MINOR         3
/** Step Version in Release. Describes Beta and Release. */
#define EEMBC_TH_STEP          'B'
/** Sub version within Step. */
#define EEMBC_TH_REVISION      16

#ifdef __cplusplus
}
#endif
#endif /* THVINFO_H */
/** @} */
/** @} */
