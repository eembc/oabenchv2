/*==============================================================================
 *$RCSfile: algo.h,v $
 *
 *   DESC : Benchmark Definitions
 *
 *  EEMBC : Office Automation
 *
 * AUTHOR : Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.4 $
 *          $Date: 2005/04/27 20:38:12 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/office/textv2/algo.h,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: algo.h,v $
 * Revision 1.4  2005/04/27 20:38:12  rick
 * Copyrite update 2005
 *
 * Revision 1.3  2004/09/08 05:19:10  rick
 * Add additional office datasets to complete makefile build
 *
 * Revision 1.2  2004/09/03 22:32:02  rick
 * New Office Textv2 functions
 *
 * Revision 1.1  2004/07/01 18:14:19  rick
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

/* ==== strlen */
#include <string.h>
/* ==== Project Wide Headers */
#include "thlib.h"
#include "kernel.h"

/* ==== Algorithm specific headers */
#include "text.h"


/**************************************************************************
      Defines
***************************************************************************/

/** Data set identifier default. */
#if		!defined(DATA_1) && !defined(DATA_2) && !defined(DATA_3) && !defined(DATA_4)
#define	DATA_1
#endif

/** Benchmark Identifier [Subcommittee code, Name] */
#define	BM_ID			"OF2 textv2     "
/** Benchmark Description */
#define BM_DESCRIPTION	"Text Parsing Algorithm"
/** Release where this benchmark code became final */
#define BM_VERSION		{ 2, 0, 'B', 13 }

/* Define iterations */
#if !defined(ITERATIONS) || CRC_CHECK || ITERATIONS==DEFAULT
#undef ITERATIONS
#if CRC_CHECK
#define ITERATIONS 1000	/* required iterations for crc */
#else
#define ITERATIONS 1000	/* recommended iterations for benchmark */
#endif
#endif

#if CRC_CHECK
#define EXPECTED_CRC	0x0000
#elif NON_INTRUSIVE_CRC_CHECK

#if		(TRAINING==1)
#define EE_UID 192
#define EXPECTED_CRC	0xb056
#elif	defined(DATA_2)
#define EE_UID 193
#define EXPECTED_CRC	0x0d63
#elif	defined(DATA_3)
#define EE_UID 194
#define EXPECTED_CRC	0xaef0
#elif	defined(DATA_4)
#define EE_UID 195
#define EXPECTED_CRC	0x04bd
#else
#define EXPECTED_CRC	0x0000
#endif

#else
#define EXPECTED_CRC	0x0000
#endif

#define EXPECTED_CRC_1	0xb056
#define EXPECTED_CRC_2	0x0d63
#define EXPECTED_CRC_3	0xaef0
#define EXPECTED_CRC_4	0x04bd
#define EE_UID_1 192
#define EE_UID_2 193
#define EE_UID_3 194
#define EE_UID_4 195
#define NUM_DATAS 4

extern unsigned long ee_uid;
extern e_u16 expected_crc;
extern unsigned long ee_uid_all[NUM_DATAS];
extern e_u16 expected_crc_all[NUM_DATAS];
extern char *dataname_all[NUM_DATAS];

/****************************************************************************
      Function Prototypes
***************************************************************************/
/* ---------- Initialization functions */
n_void           initFreeNodes(n_void);
n_void           initCharacterTypes(n_void);
n_void           initVariables(n_void);
n_void           initOperatorTree(n_void);

n_char *         input(n_void);
#if BENCHMARK
n_void             resetInput(n_void);
#endif

Node *           parseRule(n_void);

n_void           release( Node *p );

n_char           printNodes( Node *p );

#if	NON_INTRUSIVE_CRC_CHECK
n_char        CRCNodes( Node *p, e_u16 *crc );
#endif

void	init_files(void);
void	load_rules(void);
void	free_rules(void);



#endif /* ALGO_H */
