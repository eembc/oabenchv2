/*==============================================================================
 *$RCSfile: algo.h,v $
 *
 *   DESC : Benchmark Definitions
 *
 *  EEMBC : Office Automation
 *
 * AUTHOR : Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.7 $
 *          $Date: 2005/10/29 02:09:32 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/office/bezierv2/algo.h,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: algo.h,v $
 * Revision 1.7  2005/10/29 02:09:32  rick
 * Bug #287: Fixed Big Endian checksums were not updated, should match the Little Endian CRC's. V2 is CRC endian neutral.
 *
 * Revision 1.6  2005/07/16 13:26:08  rick
 * Fix checksums for final modifications
 *
 * Revision 1.5  2005/04/27 20:37:51  rick
 * Copyrite update 2005
 *
 * Revision 1.4  2004/09/09 16:01:12  rick
 * Add BE CRC's - they now match LE with new CRC algorithm
 *
 * Revision 1.3  2004/09/08 21:03:14  rick
 * Modify CRC algorithms for toolchain differences
 *
 * Revision 1.2  2004/09/08 05:18:53  rick
 * Add additional office datasets to complete makefile build
 *
 * Revision 1.1  2004/07/01 18:13:49  rick
 * Checkpoint after CRC4 for testing
 *
 *
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
 * ===========================================================================*/

#ifndef	ALGO_H
#define	ALGO_H


/* ==== Project Wide Headers ==== */
#include "kernel.h"

/* ==== Algorithm specific headers ==== */
#include "bez.h"
#include "pointio.h"

/** Data set identifier default. */
#if		!defined(DATA_1) && !defined(DATA_2) && !defined(DATA_3) && !defined(DATA_4)
#define	DATA_1
#endif

/** Benchmark Identifier [Subcommittee code, Name] */
#define	BM_ID			"OF2 bezierv2   "
/** Benchmark Description */
#if USE_FPU
#define BM_DESCRIPTION	"Bezier Curve Interpolation (Float) Algorithm"
#else
#define BM_DESCRIPTION	"Bezier Curve Interpolation (Fixed) Algorithm"
#endif
/** Release where this benchmark code became final */
#define BM_VERSION		{ 2, 0, 'B', 13 }

/* Define iterations */
#if !defined(ITERATIONS) || CRC_CHECK || ITERATIONS==DEFAULT
#undef ITERATIONS
#if CRC_CHECK
#define ITERATIONS 10	/* required iterations for crc */
#else
#define ITERATIONS 1000	/* recommended iterations for benchmark */
#endif
#endif

#if CRC_CHECK
#define EXPECTED_CRC 0x0000
#elif NON_INTRUSIVE_CRC_CHECK

#define NUM_DATAS 4
/** \note V2 Bezier CRC is Endian neutral. */
#if USE_FPU /* Float */

/* Word Swapping in calculation */
#if		(TRAINING==1)
#define EE_UID 162
#define EXPECTED_CRC 0x40db
#elif	defined(DATA_2)
#define EE_UID 163
#define EXPECTED_CRC 0x40db
#elif	defined(DATA_3)
#define EE_UID 164
#define EXPECTED_CRC 0x40db
#elif	defined(DATA_4)
#define EE_UID 165
#define EXPECTED_CRC 0x40db
#else
#define EE_UID 0
#define EXPECTED_CRC 0
#endif
#define EE_UID_1 162
#define EE_UID_2 163
#define EE_UID_3 164
#define EE_UID_4 165
#define EXPECTED_CRC_1 0x40db
#define EXPECTED_CRC_2 0x40db
#define EXPECTED_CRC_3 0x40db
#define EXPECTED_CRC_4 0x40db

#else /* !USE_FPU Fixed */

/* Word Swapping in calculation */
#if		(TRAINING==1)
#define EE_UID 166
#define EXPECTED_CRC 0x871e
#elif	defined(DATA_2)
#define EE_UID 167
#define EXPECTED_CRC 0xe765
#elif	defined(DATA_3)
#define EE_UID 168
#define EXPECTED_CRC 0x4bdc
#elif	defined(DATA_4)
#define EE_UID 169
#define EXPECTED_CRC 0xce83
#else
#define EE_UID 0
#define EXPECTED_CRC 0
#endif

#define EE_UID_1 166
#define EE_UID_2 167
#define EE_UID_3 168
#define EE_UID_4 169
#define EXPECTED_CRC_1 0x871e
#define EXPECTED_CRC_2 0xe765
#define EXPECTED_CRC_3 0x4bdc
#define EXPECTED_CRC_4 0xce83

#endif /* USE_FPU end. */

#else /* NON_INTRUSIVE_CRC end. */
#define EXPECTED_CRC 0x0000
#endif

extern unsigned long ee_uid;
extern e_u16 expected_crc;
extern unsigned long ee_uid_all[NUM_DATAS];
extern e_u16 expected_crc_all[NUM_DATAS];
extern char *dataname_all[NUM_DATAS];

#if	USE_FPU && NON_INTRUSIVE_CRC_CHECK
	typedef union {
		double	d;
		size_t	v[2];
	} d_union;
extern d_union	dunion;
#define ERROR_EPSILON 0.000001
#endif

#endif /* ALGO_H */
