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
 *          $Date: 2005/11/03 23:57:41 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/office/ditherv2/algo.h,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: algo.h,v $
 * Revision 1.7  2005/11/03 23:57:41  rick
 * Bug #141: CRC update
 *
 * Revision 1.6  2005/04/27 20:37:57  rick
 * Copyrite update 2005
 *
 * Revision 1.5  2004/09/08 21:03:20  rick
 * Modify CRC algorithms for toolchain differences
 *
 * Revision 1.4  2004/09/08 05:18:56  rick
 * Add additional office datasets to complete makefile build
 *
 * Revision 1.3  2004/09/03 22:31:52  rick
 * New Office Textv2 functions
 *
 * Revision 1.2  2004/07/01 18:13:54  rick
 * Checkpoint after CRC4 for testing
 *
 * Revision 1.1  2004/02/02 19:57:05  rick
 * Clear Root directory problems
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

/* ==== Project Wide Headers */
#include <string.h>
#include "thlib.h"
#include "kernel.h"

/* ==== Algorithm specific headers */
#include "dither.h"
#include "masks.h"
#include "imageio.h"

/** Data set identifier default. */
#if		!defined(DATA_1) && !defined(DATA_2) && !defined(DATA_3) && !defined(DATA_4) && !defined(DATA_5) && !defined(DATA_6) && !defined(DATA_7) && !defined(DATA_8) && !defined(DATA_9) && !defined(DATA_10) && !defined(DATA_11)
#define	DATA_2
#endif

/** Benchmark Identifier [Subcommittee code, Name] */
#define	BM_ID			"OF2 ditherv2   "
/** Benchmark Description */
#if FILTER == FLOYD_STEIN
#define BM_DESCRIPTION	"Floyd-Stein Grayscale Dithering Algorithm"
#else
#define BM_DESCRIPTION	"Jarvis Grayscale Dithering Algorithm"
#endif
/** Release where this benchmark code became final */
#define BM_VERSION		{ 2, 0, 'B', 16 }

/** Determine ITERATIONS via compiler option override, intrusive CRC, or recommended default.*/
#if !defined(ITERATIONS) || CRC_CHECK || ITERATIONS==DEFAULT
#undef ITERATIONS
#if CRC_CHECK
#define ITERATIONS      2		/* required iterations for crc */
#else
#define ITERATIONS      200		/* recommended iterations for benchmark */
#endif
#endif

#if CRC_CHECK

#define EXPECTED_CRC 0x0000

#elif NON_INTRUSIVE_CRC_CHECK

#if FILTER == FLOYD_STEIN

#if		(TRAINING==1)
#define EE_UID 170
#define EXPECTED_CRC 0x1810
#elif	defined(DATA_2)
#define EE_UID 171
#define EXPECTED_CRC 0x9fa4
#elif	defined(DATA_3)
#define EE_UID 172
#define EXPECTED_CRC 0x7571
#elif	defined(DATA_4)
#define EE_UID 173
#define EXPECTED_CRC 0xdff7
#elif	defined(DATA_5)
#define EE_UID 174
#define EXPECTED_CRC 0x0303 
#elif	defined(DATA_6)
#define EE_UID 175
#define EXPECTED_CRC 0xc043
#elif	defined(DATA_7)
#define EE_UID 176
#define EXPECTED_CRC 0x6e39
#elif	defined(DATA_8)
#define EE_UID 177
#define EXPECTED_CRC 0x569b
#elif	defined(DATA_9)
#define EE_UID 178
#define EXPECTED_CRC 0x1bb8
#elif	defined(DATA_10)
#define EE_UID 179
#define EXPECTED_CRC 0xfe85
#elif	defined(DATA_11)
#define EE_UID 180
#define EXPECTED_CRC 0xc982
#else
#define EXPECTED_CRC 0
#endif

#else	/* JARVIS */

#if		(TRAINING==1)
#define EXPECTED_CRC 0x3aa8
#elif	defined(DATA_2)
#define EXPECTED_CRC 0x3aa8
#elif	defined(DATA_3)
#define EXPECTED_CRC 0x3aa8
#elif	defined(DATA_4)
#define EXPECTED_CRC 0x3aa8
#elif	defined(DATA_5)
#define EXPECTED_CRC 0x3aa8
#elif	defined(DATA_6)
#define EXPECTED_CRC 0x3aa8
#elif	defined(DATA_7)
#define EXPECTED_CRC 0x3aa8
#elif	defined(DATA_8)
#define EXPECTED_CRC 0x3aa8
#elif	defined(DATA_9)
#define EXPECTED_CRC 0x3aa8
#elif	defined(DATA_10)
#define EXPECTED_CRC 0x3aa8
#elif	defined(DATA_11)
#define EXPECTED_CRC 0x3aa8
#else
#define EXPECTED_CRC 0
#endif

#endif

#else
#define EXPECTED_CRC 0x0000
#endif

#define EXPECTED_CRC_1  0x1810
#define EXPECTED_CRC_2  0x9fa4
#define EXPECTED_CRC_3  0x7571
#define EXPECTED_CRC_4  0xdff7
#define EXPECTED_CRC_5  0x0303 
#define EXPECTED_CRC_6  0xc043
#define EXPECTED_CRC_7  0x6e39
#define EXPECTED_CRC_8  0x569b
#define EXPECTED_CRC_9  0x1bb8
#define EXPECTED_CRC_10 0xfe85
#define EXPECTED_CRC_11 0xc982
#define EE_UID_1  170
#define EE_UID_2  171
#define EE_UID_3  172
#define EE_UID_4  173
#define EE_UID_5  174
#define EE_UID_6  175
#define EE_UID_7  176
#define EE_UID_8  177
#define EE_UID_9  178
#define EE_UID_10 179
#define EE_UID_11 180
#define NUM_DATAS 11

extern unsigned long ee_uid;
extern e_u16 expected_crc;
extern unsigned long ee_uid_all[NUM_DATAS];
extern e_u16 expected_crc_all[NUM_DATAS];
extern char *dataname_all[NUM_DATAS];

/** Prototype */
n_void ditherImage( e_u8 *input, int input_height, int input_width,
                         e_u8 *output );

/** Define output image buffer size in bytes */
#define IMAGE_BUFFSZ(h,w)       (h * ((w-1)/CHAR_BITS+1))

#endif /* ALGO_H */
