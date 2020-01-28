/**
 * @file
 * @brief  Include files for Empty Benchmark
 * 
 *$RCSfile: algo.h,v $
 *
 *  EEMBC : Technical Advisory Group (TechTAG)
 *
 * @author  Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.7 $
 *          $Date: 2005/07/17 19:46:45 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/techtag/empty/algo.h,v $
 *          
 * @note   
 *
 *
 * HISTORY :
 *
 * $Log: algo.h,v $
 * Revision 1.7  2005/07/17 19:46:45  rick
 * Specification and early work on AI Real-Time
 *
 * Revision 1.6  2005/04/27 20:38:34  rick
 * Copyrite update 2005
 *
 * Revision 1.5  2004/12/09 20:41:11  rick
 * New header comments for documentation
 *
 * Revision 1.4  2004/02/06 23:32:28  alan
 * Modified release level to 2.0R1 and added authorship credits arw/ECL
 *
 * Revision 1.3  2004/01/22 01:03:14  rick
 * Release cleanup, copyright year corrections
 *
 * Revision 1.2  2003/08/15 00:30:50  rick
 * Move descriptions to common header
 *
 * Revision 1.1  2002/12/31 16:24:08  rick
 * Add DO_DIFFMEASURE, DO_UUENCODE and diffmeasure sizing
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


/** @addtogroup empty
@{ */

#ifndef ALGO_H
#define ALGO_H

/*******************************************************************************
    Includes                                                                    
*******************************************************************************/
#include "thlib.h"

/*******************************************************************************
    Defines                                                                     
*******************************************************************************/

#define	BM_ID			"ALL empty    "
#define BM_DESCRIPTION	"Void Benchmark to measure size of Harness"
#define BM_VERSION		{ 2, 0, 'R', 1 }

/* Define iterations */
#if !defined(ITERATIONS) || CRC_CHECK || ITERATIONS==DEFAULT
#undef ITERATIONS
#if CRC_CHECK
#define ITERATIONS 5000	/* required iterations for crc */
#else
#define ITERATIONS 5000	/* recommended iterations for benchmark */
#endif
#endif

#if		CRC_CHECK
#define EXPECTED_CRC 0x0000
#elif	NON_INTRUSIVE_CRC_CHECK
#define EXPECTED_CRC 0x0000
#else
#define EXPECTED_CRC 0x0000
#endif

/* Define to allow benchmark to calculate diffmeasure (after timing loop) */
/* #define	DO_DIFFMEASURE allow make environment to define for sizing */

/* Define to allow benchmark to uuencode results (after timing loop) */
/* #define DO_UUENCODE allow harness.h to control this */

#if		defined(DO_DIFFMEASURE)
#include "verify.h"		/* diffmeasure */
#endif

#endif /* ALGO_H */
/** @} */
