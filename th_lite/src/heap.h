/**
 * @file
 * @brief  Test Harness routines for benchmarks
 *
 * $RCSfile: heap.h,v $
 *
 * @author  ECL, LLC
 *
 *  EEMBC : Technical Advisory Group (TechTAG)
 *
 *    CVS : $Revision: 1.24 $
 *          $Date: 2005/12/02 23:53:34 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/techtag/th_lite/src/heap.h,v $
 *          
 * @note   
 *
 *
 * HISTORY :
 *
 * $Log: heap.h,v $
 * Revision 1.24  2005/12/02 23:53:34  rick
 * Fix mixed EOL format causing ^M's to appear in Unix checkouts.
 *
 * Revision 1.23  2005/09/10 04:02:23  rick
 * eol update, add uu_send_file
 *
 * Revision 1.22  2005/04/27 20:33:14  rick
 * Copyrite update 2005
 *
 * Revision 1.21  2004/12/08 23:27:17  rick
 * New standard header for documentation generation.
 *
 * Revision 1.7  2004/06/23 05:55:23  rick
 * EE_REDIRECT, and Shared Files
 *
 * Revision 1.6  2004/05/07 22:45:47  rick
 * Match Heap manager in harnesses, move internal routines to thfl.c
 *
 * Revision 1.5  2004/01/22 00:56:52  rick
 * Release cleanup, copyright year corrections
 *
 * Revision 1.4  2003/07/26 18:29:15  rick
 * Fix include paths
 *
 * Revision 1.3  2002/04/23 18:33:56  rick
 * Match eembc_dt with Lite, remove stdinc.h
 *
 * Revision 1.2  2002/03/21 22:31:08  rick
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

#ifndef   HEAP_H
#define   HEAP_H

#ifndef   HEAPPORT_H
#include "heapport.h"
#endif

/** @addtogroup SHFL
@{ */
/** @addtogroup heap_c Functional Layer Heap Manager
@{ */

#ifdef __cplusplus
extern "C" {
#endif

/** Heap statistics structures used by heap_stats. */
typedef struct
{
	/** total size of the heap                 */
	BlockSize size;
	/** free (useable) space in the heap       */
	BlockSize free;
	/** number of free blocks                  */
	BlockSize num_free;
	/** number of allocated blocks             */
	BlockSize num_alloced;
}
   HeapStats;

/* Initialization routines. */

void *heap_initialize( char *start, BlockSize size );

/* Runtime API routines. */

void *heap_alloc  ( void *heap, BlockSize size );
void *heap_calloc ( void *heap, BlockSize nmemb, BlockSize size );
void *heap_realloc( void *heap, void *buf, BlockSize size );
void  heap_free   ( void *heap, void *buf );
void  heap_reset  ( void *heap );

/* Runtime Internal routines. */

BlockSize heap_free_space        ( void *heap );
BlockSize heap_biggest_free_block( void *heap );

/* Debug Routines */

long  heap_check( void *heap );
void  heap_dump ( void *heap );
void  heap_stats( void *heap, HeapStats * stats );

/* Error values returned by heap_check() */

#define HEAP_OK              (0x00000000)
#define HERR_BAD_HEAP_STRUCT (0x00000001)
#define HERR_FIRST_BLOCK_BAD (0x00000002)
#define HERR_BLOCK_BAD       (0x00000004)
#define HERR_TOTAL_SIZE_BAD  (0x00000008)
#define HERR_FREE_SIZE_BAD   (0x00000010)
#define HERR_NUM_FREE_BAD    (0x00000020)
#define HERR_NUM_ALLOCED_BAD (0x00000040)
#define HERR_PSIZE_BAD       (0x00000080)
#define HERR_BLOCK_TOO_SMALL (0x00000100)
#define HERR_BLOCK_SIZE_MOD  (0x00000200)
#define HERR_FREE_ADJACENT   (0x00000400)
#define HERR_BAD_FREELPTR    (0x00000800)
/** free list pointer not null */
#define HERR_FREELPTR_NN     (0x00001000)
/** bad free list previous ptr */
#define HERR_BAD_FL_PREV     (0x00002000)
/** bad free list previous ptr */
#define HERR_BAD_FL_NEXT     (0x00004000)
/** too many items in the free list */
#define HERR_BAD_FL_TOO_MANY (0x00008000)
/** not enough items in the free list */
#define HERR_BAD_FL_NOT_NUFF (0x00010000)
/** bad previous link */
#define HERR_BAD_PREV_LINK   (0x00020000)
/** a block in the free list is bad */
#define HERR_FL_BLOCK_BAD    (0x00040000)

#ifdef __cplusplus
   }
#endif
#endif /* HEAP_H */
/** @} */
/** @} */
