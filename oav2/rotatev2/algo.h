/*==============================================================================
 *$RCSfile: algo.h,v $
 *
 *   DESC : Benchmark Definitions
 *
 *  EEMBC : Office Automation
 *
 * AUTHOR : Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.1.1.1 $
 *          $Date: 2006/03/07 19:54:45 $
 *          $Author: Owner $
 *          $Source: /usr/local/cvs/oa2/office/rotatev2/algo.h,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: algo.h,v $
 * Revision 1.1.1.1  2006/03/07 19:54:45  Owner
 * Initial sources for OAv2, created from RC5
 *
 * Revision 1.8  2005/04/27 20:38:08  rick
 * Copyrite update 2005
 *
 * Revision 1.7  2004/09/08 21:03:22  rick
 * Modify CRC algorithms for toolchain differences
 *
 * Revision 1.6  2004/09/08 05:19:05  rick
 * Add additional office datasets to complete makefile build
 *
 * Revision 1.5  2004/09/03 22:32:00  rick
 * New Office Textv2 functions
 *
 * Revision 1.4  2004/07/01 18:14:14  rick
 * Checkpoint after CRC4 for testing
 *
 * Revision 1.3  2004/06/25 23:36:14  rick
 * 8.30 Merge Autoconf/MSVC compilation
 *
 * Revision 1.2  2004/05/13 19:33:29  rick
 * Release cleanup
 *
 * Revision 1.1  2004/05/03 22:27:54  rick
 * Add text, bezier, rotate base for v2
 *
 * Revision 1.1  2004/02/02 19:57:05  rick
 * Clear Root directory problems
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
#include "rot.h"
#include "masks.h"
#include "rimageio.h"

/*********************************************************************
    Defines
**********************************************************************/

/** Data set identifier default. */
#if		!defined(DATA_1) && !defined(DATA_2) && !defined(DATA_3) && !defined(DATA_4) && !defined(DATA_5) && !defined(DATA_6) && !defined(DATA_7) && !defined(DATA_8) && !defined(DATA_9) && !defined(DATA_10) && !defined(DATA_11)
#define	DATA_1
#endif

/** Benchmark Identifier [Subcommittee code, Name] */
#define	BM_ID			"OF2 rotatev2"
/** Benchmark Description */
#define BM_DESCRIPTION	"Bitmap Rotation Algorithm"
/** Release where this benchmark code became final */
#define BM_VERSION		{ 2, 0, 'B', 13 }

/* Define iterations */
#if !defined(ITERATIONS) || CRC_CHECK || ITERATIONS==DEFAULT
#undef ITERATIONS
#if CRC_CHECK
#define ITERATIONS 2	/* required iterations for crc */
#else
#define ITERATIONS 50	/* recommended iterations for benchmark */
#endif
#endif

#if CRC_CHECK
#define EXPECTED_CRC 0x0000
#elif NON_INTRUSIVE_CRC_CHECK

#if BITS >= 32

#if		(TRAINING==1)
#define EE_UID 181
#define EXPECTED_CRC 0x65cb
#elif	defined(DATA_2)
#define EE_UID 182
#define EXPECTED_CRC 0x4b1a
#elif	defined(DATA_3)
#define EE_UID 183
#define EXPECTED_CRC 0x4ea6
#elif	defined(DATA_4)
#define EE_UID 184
#define EXPECTED_CRC 0xc9c4
#elif	defined(DATA_5)
#define EE_UID 185
#define EXPECTED_CRC 0xaa3f
#elif	defined(DATA_6)
#define EE_UID 186
#define EXPECTED_CRC 0xC0F2
#elif	defined(DATA_7)
#define EE_UID 187
#define EXPECTED_CRC 0xADF0
#elif	defined(DATA_8)
#define EE_UID 188
#define EXPECTED_CRC 0x5E82
#elif	defined(DATA_9)
#define EE_UID 189
#define EXPECTED_CRC 0x1965
#elif	defined(DATA_10)
#define EE_UID 190
#define EXPECTED_CRC 0x05E2
#elif	defined(DATA_11)
#define EE_UID 191
#define EXPECTED_CRC 0x78BA
#else
#define EXPECTED_CRC 0
#endif

#define EXPECTED_CRC_1  0x65cb
#define EXPECTED_CRC_2  0x4b1a
#define EXPECTED_CRC_3  0x4ea6
#define EXPECTED_CRC_4  0xc9c4
#define EXPECTED_CRC_5  0xaa3f
#define EXPECTED_CRC_6  0xC0F2
#define EXPECTED_CRC_7  0xADF0
#define EXPECTED_CRC_8  0x5E82
#define EXPECTED_CRC_9  0x1965
#define EXPECTED_CRC_10 0x05E2
#define EXPECTED_CRC_11 0x78BA
#define EE_UID_1  181
#define EE_UID_2  182
#define EE_UID_3  183
#define EE_UID_4  184
#define EE_UID_5  185
#define EE_UID_6  186
#define EE_UID_7  187
#define EE_UID_8  188
#define EE_UID_9  189
#define EE_UID_10 190
#define EE_UID_11 191
#define NUM_DATAS 11

#elif BITS >= 16
#define EXPECTED_CRC 0
#elif BITS >= 8
#define EXPECTED_CRC 0
#else
#define EXPECTED_CRC 0
#endif

#else
#define EXPECTED_CRC 0x0000
#endif

extern unsigned long ee_uid;
extern e_u16 expected_crc;
extern unsigned long ee_uid_all[NUM_DATAS];
extern e_u16 expected_crc_all[NUM_DATAS];
extern char *dataname_all[NUM_DATAS];

/* ------------------------------------------------- */
/*     Check BIG/small endian */
/* ------------------------------------------------- */
#if EE_BIG_ENDIAN

#if BITS >= 32
#define SHIFT1    (CHAR_BITS * 3)
#define SHIFT2    (CHAR_BITS * 2)
#define SHIFT3    (CHAR_BITS * 1)
#define SHIFT4    (CHAR_BITS * 0)
#elif BITS >= 16
#define SHIFT1    (CHAR_BITS * 1)
#define SHIFT2    (CHAR_BITS * 0)
#elif BITS >= 8
#define SHIFT1    (CHAR_BITS * 0)
#endif

#elif EE_LITTLE_ENDIAN

/** @note: LE Bit shifts are the same for 8, 16, and 32 bit cases. */
#define SHIFT1    (CHAR_BITS * 0)
#define SHIFT2    (CHAR_BITS * 1)
#define SHIFT3    (CHAR_BITS * 2)
#define SHIFT4    (CHAR_BITS * 3)

#endif

/* ------------------------------------------------- */
/*     Define 8/16/32 bit masks */
/* ------------------------------------------------- */
#define MASK01    (MASKBYTE01<<SHIFT1)
#define MASK02    (MASKBYTE02<<SHIFT1)
#define MASK03    (MASKBYTE03<<SHIFT1)
#define MASK04    (MASKBYTE04<<SHIFT1)
#define MASK05    (MASKBYTE05<<SHIFT1)
#define MASK06    (MASKBYTE06<<SHIFT1)
#define MASK07    (MASKBYTE07<<SHIFT1)
#define MASK08    (MASKBYTE08<<SHIFT1)
#if BITS >= 16
#define MASK09    (MASKBYTE01<<SHIFT2)
#define MASK10    (MASKBYTE02<<SHIFT2)
#define MASK11    (MASKBYTE03<<SHIFT2)
#define MASK12    (MASKBYTE04<<SHIFT2)
#define MASK13    (MASKBYTE05<<SHIFT2)
#define MASK14    (MASKBYTE06<<SHIFT2)
#define MASK15    (MASKBYTE07<<SHIFT2)
#define MASK16    (MASKBYTE08<<SHIFT2)
#if BITS >= 32
#define MASK17    (MASKBYTE01<<SHIFT3)
#define MASK18    (MASKBYTE02<<SHIFT3)
#define MASK19    (MASKBYTE03<<SHIFT3)
#define MASK20    (MASKBYTE04<<SHIFT3)
#define MASK21    (MASKBYTE05<<SHIFT3)
#define MASK22    (MASKBYTE06<<SHIFT3)
#define MASK23    (MASKBYTE07<<SHIFT3)
#define MASK24    (MASKBYTE08<<SHIFT3)
#define MASK25    (MASKBYTE01<<SHIFT4)
#define MASK26    (MASKBYTE02<<SHIFT4)
#define MASK27    (MASKBYTE03<<SHIFT4)
#define MASK28    (MASKBYTE04<<SHIFT4)
#define MASK29    (MASKBYTE05<<SHIFT4)
#define MASK30    (MASKBYTE06<<SHIFT4)
#define MASK31    (MASKBYTE07<<SHIFT4)
#define MASK32    (MASKBYTE08<<SHIFT4)
#endif
#endif


/*
 *  Define an array of bitmasks for SETTING the output image bits.
 *     Using the defines above, this list should cover all Endian cases
 *  Note: this is a zero-based list, which assumes the "first" row is
 *     row number zero...
 */
static UNIT setmask[] =
{
    MASK01, MASK02, MASK03, MASK04, MASK05, MASK06, MASK07, MASK08,
#if BITS >= 16
    MASK09, MASK10, MASK11, MASK12, MASK13, MASK14, MASK15, MASK16,
#if BITS >= 32
    MASK17, MASK18, MASK19, MASK20, MASK21, MASK22, MASK23, MASK24,
    MASK25, MASK26, MASK27, MASK28, MASK29, MASK30, MASK31, MASK32,
#endif
#endif
};

/*********************************************************************
    M A C R O S
**********************************************************************/
/* image_buffsz always rounds down, image_bitwidth always rounds up. */
#define IMAGE_BITWIDTH(w)	(w*CHAR_BITS-1)
#define IMAGE_WIDTH(w)		((w-1)/CHAR_BITS+1)
#define IMAGE_BUFFSZ(h,w)	(h * w)

/*********************************************************************
    Function Prototypes
**********************************************************************/

n_void rotateImage(e_u8 *input,n_int input_height,n_int input_width,e_u8 *output);

#endif /* ALGO_H */
