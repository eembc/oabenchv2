/*==============================================================================
 *$RCSfile: algo.h,v $
 *
 *   DESC : Benchmark Definitions
 *
 *  EEMBC : Consumer Subcommittee
 *
 * AUTHOR : Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.6 $
 *          $Date: 2005/04/27 20:38:03 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/office/gs8/algo.h,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: algo.h,v $
 * Revision 1.6  2005/04/27 20:38:03  rick
 * Copyrite update 2005
 *
 * Revision 1.5  2004/11/10 23:19:12  rick
 * Add automated output generation
 *
 * Revision 1.4  2004/07/02 17:56:11  rick
 * Add utilities for CRC, UUENCODE, and Ghostscript command line processing.
 *
 * Revision 1.3  2004/07/01 18:13:58  rick
 * Checkpoint after CRC4 for testing
 *
 * Revision 1.2  2004/02/04 01:05:50  rick
 * Add libresource, new cinit features
 *
 * Revision 1.1  2004/02/02 19:57:11  rick
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

#include <stdio.h>
#include <string.h> /* strlen */
#include "thlib.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Entry point of Ghostscript */
int gs_main(int argc, const char *argv[], int * exit_code);

/** Get option from command line. */
char *getOption(int *argc,char *argv[],const char *option,int remove);
/** Set do_uuencode. */
int setDouuencode(int *argc,char *argv[]);
/** Set outname. */
char *setOutname(int *argc,char *argv[]);
/** Set device. */
char *setDevice(int *argc,char *argv[]);
/** Set device parameters. */
char *setDevParams(int argc,const char *argv[]);
/** Set example postscript file. */
char *setExample(int argc,const char *argv[]);
/** Set uid based on user arguments. */
int setUID(int *argc,char *argv[]);
/** returns a pointer to the file name portion of a path. */
char *efn( const char *fn );
/** Get expected CRC based on device driver and example postscript file. */
e_u16 getExpectedcrc(char *device,char *example);
/** Initialize RAM file system */
void init_filesystem(void);
/** Create fresh argv array. */
char **loadMyargv(int *argc,const char *argv[]);
/** Free argv array. */
void freeMyargv(int argc,char *myargv[]);

/* TCDef values for benchmark. */

/** Benchmark Identifier [Subcommittee code, Name] */
#define	BM_ID			"OF2 gs8      "
/** Benchmark Description */
#define BM_DESCRIPTION	"Ghostscript 8.54 Benchmark"
/** Release where this benchmark code became final */
#define BM_VERSION		{ 2, 0, 'B', 12 }

/** Determine ITERATIONS via compiler option override, intrusive CRC, or recommended default.*/
#if !defined(ITERATIONS) || CRC_CHECK || ITERATIONS==DEFAULT
#undef ITERATIONS
#if CRC_CHECK
#define ITERATIONS 1	/* required iterations for crc */
#else
#define ITERATIONS 1	/* recommended iterations for benchmark */
#endif
#endif

/** Pre-Defined CRC values from reference system */
#if	CRC_CHECK
#define EXPECTED_CRC 0x0000
#elif NON_INTRUSIVE_CRC_CHECK
#define EXPECTED_CRC 0x0000
#else
#define EXPECTED_CRC 0x0000
#endif

#ifdef __cplusplus
}
#endif
#endif /* File Sentinel */ 
