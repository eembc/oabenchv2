/**
 * @file
 * @brief  Functional Layer Heap Manager
 * 
 *$RCSfile: heap.c,v $
 *
 *  EEMBC : EEMBC Technical Advisory Group (TechTAG)
 *
 *    CVS : $Revision: 1.34 $
 *          $Date: 2005/12/02 23:53:34 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/techtag/th_lite/src/heap.c,v $
 *          
 * @note   
 *    define TURN_ON_VERIFY_HEAP as 1 to turn on all the heap checking stuff
 *    define TURN_ON_DEBUG_HEAP  as 1 to turn on debug printf output
 *
 *    Note, this is usually done from a make file, IDE or HEAPPORT.H
 *	  This file is not 64b safe.
 *
 * HISTORY :
 *
 * $Log: heap.c,v $
 * Revision 1.34  2005/12/02 23:53:34  rick
 * Fix mixed EOL format causing ^M's to appear in Unix checkouts.
 *
 * Revision 1.33  2005/09/10 04:02:23  rick
 * eol update, add uu_send_file
 *
 * Revision 1.32  2005/04/27 20:33:14  rick
 * Copyrite update 2005
 *
 * Revision 1.31  2004/12/08 23:27:17  rick
 * New standard header for documentation generation.
 *
 * Revision 1.30  2004/05/07 22:45:56  rick
 * Match Heap manager in harnesses, move internal routines to thfl.c
 *
 * Revision 1.20  2004/05/06 21:15:42  rick
 * Fix th_strdup for heap, and epn NULL return to 0 string
 *
 * Revision 1.19  2004/03/15 21:29:05  rick
 * Add documentation tags, and cleanup comments
 *
 * Revision 1.18  2004/02/05 23:03:24  rick
 * Harness update with portable dirent
 *
 * Revision 1.17  2004/01/22 00:56:52  rick
 * Release cleanup, copyright year corrections
 *
 * Revision 1.16  2003/07/26 18:29:15  rick
 * Fix include paths
 *
 * Revision 1.15  2003/03/14 00:24:29  rick
 * Add feof and text file support to fileio
 *
 * Revision 1.14  2003/02/03 19:18:22  rick
 * Fix eol characters
 *
 * Revision 1.13  2002/10/29 23:27:27  rick
 * implimentation?
 *
 * Revision 1.12  2002/10/29 16:08:14  rick
 * Bug #203: ANSI C compliant
 *
 * Revision 1.11  2002/10/15 15:07:53  rick
 * Bug #202: Remove dbpf comment
 *
 * Revision 1.10  2002/09/12 19:02:25  rick
 * Fix dbpf and | definitions
 *
 * Revision 1.9  2002/08/06 22:52:03  rick
 * Integrate HAVE_MALLOC
 *
 * Revision 1.8  2002/07/17 17:47:10  rick
 * Fix Heap warnings
 *
 * Revision 1.7  2002/07/11 22:50:27  rick
 * Fix lite Heap init, tcdef results init, and stig's suggestions
 *
 * Revision 1.6  2002/05/22 17:55:20  rick
 * Replace assert.h with thassert.h, add assert functions to th lite.
 *
 * Revision 1.5  2002/04/10 19:37:00  rick
 * Fixes to reduce Lite vs. Regular variances in timing
 *
 * Revision 1.4  2002/04/02 17:06:27  administrator
 * Remove whitespace before # directives
 *
 * Revision 1.3  2002/03/22 22:57:54  rick
 * Change project files for lowercase, and techtag empty, th, and th_lite
 *
 * Revision 1.2  2002/03/21 22:31:08  rick
 * Network Harness, and empty benchmark fixes
 *
 * Revision 1.1  2002/02/15 19:26:39  rick
 * Networking converstion to TH_Lite
 *
 * Revision 1.3  2001/11/01 00:26:46  administrator
 * Beta 1.1 of encdec
 *
 * Revision 1.2  2001/10/20 06:07:48  rick
 * Add DES, RC5, RC4, RC2 Encryption Benchmarks.
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

#include "eembc_dt.h"
#if	HAVE_MALLOC
#include <stdlib.h>
#endif

#if TURN_ON_VERIFY_HEAP
#include <stdlib.h>
#include <ctype.h>
#endif
#include <string.h> /* memset */
#include "heap.h"


#ifndef HEAP_ALIGN_V
#error HEAP_ALIGN_V not defined! (must be an even power of 2)
#endif

#include "thassert.h"

/** @addtogroup THLFL
@{ */
/** @addtogroup heap_c Functional Layer Heap Manager
@{ */

/** @todo move th_heap from memmgr, and harness ifdef for mem_base. */
/* Lite=1 Regular=0 */
#if		1
#if		HAVE_MALLOC
/* heap is compiled out */
#elif		COMPILE_OUT_HEAP
/* heap is compiled out */
#else
#ifdef HEAP_BASE
char    *mem_base = (char *)(HEAP_BASE);
#else
char    mem_base[HEAP_SIZE];
#endif
size_t	mem_size = HEAP_SIZE;
void	*th_heap	= NULL; 
#endif
#endif

/*----------------------------------------------------------------------------*/

typedef struct Blok
   {
   BlockSize tsize;       /* size of this block      */
   BlockSize psize;       /* size of previous block  */
   BlockSize flags;       /* flags for this block    */
#if       TURN_ON_VERIFY_HEAP
   char      magic[ 8 ];
#endif
   }
Blok;

typedef struct FreeBlok
   {
   BlockSize tsize;       /* size of this block      */
   BlockSize psize;       /* size of previous block  */
   BlockSize flags;       /* flags for this block    */
#if       TURN_ON_VERIFY_HEAP
   char      magic[ 8 ];
#endif
   struct FreeBlok *prev;
   struct FreeBlok *next;
   }
FreeBlok;

typedef struct Heap
   {
   BlockSize size;         /* total size of the heap                 */
   BlockSize free;         /* free (useable) space in the heap       */
   BlockSize num_free;     /* number of free blocks                  */
   BlockSize num_alloced;  /* number of allocated blocks             */
   Blok *first;            /* pointer to the first block in the heap */
   FreeBlok *freel;        /* the free list                          */
   Blok *llastb;           /* the logical last block in the heap     */

#if      TURN_ON_VERIFY_HEAP
   char     magic[ 8 ];
#endif
   }
Heap;


#if TURN_ON_DEBUG_HEAP
#define LO_MALLOC 1
#define LO_FREE   2
int last_op = 0;
#define REC_MALLOC (last_op = LO_MALLOC)
#define REC_FREE   (last_op = LO_FREE)
char *ops[] = { "INIT", "MALLOC", "FREE" };
#else
#define REC_MALLOC ((void)0)
#define REC_FREE   ((void)0)
#endif

/**
 * Calculate the size of the Blok strucure, rounding up to the
 * nearest multiple of the heap alignment boundary
 */
#define BSIZE ((BlockSize)(HEAP_ALIGN(sizeof( Blok ))))

/**
 * Calculate the size of the Heap strucure, rounding up to the
 * nearest multiple of the heap alignment boundary 
 */
#define HSIZE ((BlockSize)(HEAP_ALIGN(sizeof( Heap ))))

#if TURN_ON_DEBUG_HEAP
#define DECLARE_XHEAP Heap* xheap = (Heap*)theap
#define HEAP xheap
#else
#define DECLARE_XHEAP  /*empty define*/
#define HEAP ((Heap*)theap)
#endif

/** Return a pointer to the next block */
#define NEXT_BLOK( blk ) ((Blok*)( PTR_ADD( blk, ((blk)->tsize))))

/** Return a pointer to the previous block */
#define PREV_BLOK( blk ) ((Blok*)( PTR_SUB( blk, ((blk)->psize))))

#define NEXT_PTR( blk ) ((FreeBlok*)blk)->next
#define PREV_PTR( blk ) ((FreeBlok*)blk)->prev

#define ALLOCED_BIT (1)
#define LAST_BIT    (2)
#define FIRST_BIT   (4)

#define IS_FREE( blk )      (!(blk->flags & ALLOCED_BIT))
#define IS_ALLOCTED( blk )    (blk->flags & ALLOCED_BIT)
#define IS_FIRST( blk )       (blk->flags & FIRST_BIT)
#define IS_LAST( blk )        (blk->flags & LAST_BIT)

#define MAGIC_SIZE 8
#define HEAP_MAGIC  "!!HEAP!!"
#define BLOCK_MAGIC "!!BLOK!!"
#define DEAD_BEAF   "\xDE\xAD\xBE\xAF\xDE\xAD\xBE\xAF"

#define HEAP_PTR_INVALID  0
#define BLOCK_PTR_INVALID 0

/*----------------------------------------------------------------------------*/
/* Lint Stuff */

#if TURN_ON_VERIFY_HEAP
static int cm( const char *magic, const char *value );
#endif

/*lint -e740*/

/*----------------------------------------------------------------------------*/

#if TURN_ON_VERIFY_HEAP
#define VERIFY_HEAP(h)  { assert( theap != NULL );                         \
                          assert( !cm(((Heap*)h)->magic,  HEAP_MAGIC  )); }

#define VERIFY_BLOK(b) { assert( b != NULL );                          \
                         assert( !cm(((Blok*)b)->magic, BLOCK_MAGIC )); }

#define INIT_MAGIC( b, m ) { int i; for(i=0;i<MAGIC_SIZE;i++) \
                             b->magic[i]=m[i]; }
#define ZAP_MAGIC( b     ) { int i; for(i=0;i<MAGIC_SIZE;i++) \
                             b->magic[i]=DEAD_BEAF[i]; }
#else
#define VERIFY_HEAP(h)   {((void)0);}
#define VERIFY_BLOK(b)   {((void)0);}
#define INIT_MAGIC(b,m)  {((void)0);}
#define ZAP_MAGIC(b)     {((void)0);}
#endif


#if TURN_ON_DEBUG_HEAP
#define dpf0( f ) th_printf( f )
#define dpf1( f, a1) th_printf( f, a1 )
#define dpf2( f, a1, a2 ) th_printf( f, a1, a2 )
#define dpf3( f, a1, a2, a3 ) th_printf( f, a1, a2, a3 )
#define dpf4( f, a1, a2, a3, a4 ) th_printf( f, a1, a2, a3, a4 )
#else
#define dpf0( f ) {((void)0);}
#define dpf1( f, a1) {((void)0);}
#define dpf2( f, a1, a2 ) {((void)0);}
#define dpf3( f, a1, a2, a3 ) {((void)0);}
#define dpf4( f, a1, a2, a3, a4 ) {((void)0);}
#endif

/**
 * FUNC   : heap_initialize
 *
 * DESC   : Initializes the heap from scratch
 */

void *heap_initialize( char *start, BlockSize size )

   {
#if	HAVE_MALLOC
  /* force alignment of start & size */
   start = (char *)HEAP_ALIGN((long)start);
   size = HEAP_ALIGN(size)-BSIZE;
	return NULL;
#elif COMPILE_OUT_HEAP
  /* force alignment of start & size */
   start = (char *)HEAP_ALIGN((long)start);
   size = HEAP_ALIGN(size)-BSIZE;
   return NULL;
#else

   Heap *xheap;

   dpf1( "BSIZE = %lu\n", BSIZE );
   dpf1( "HSIZE = %lu\n", HSIZE );

   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * Initialize the heap structure */

   xheap = ( Heap * ) start;
   xheap -> size = size;
   xheap -> first = ( Blok * ) PTR_ADD( start, HSIZE );
   xheap -> free = xheap -> size - HSIZE - BSIZE;
   xheap -> num_free = 1;
   xheap -> num_alloced = 0;
   xheap -> freel = ( FreeBlok * ) xheap -> first;
   xheap -> llastb = ( Blok * ) PTR_ADD( xheap->first, (size - HSIZE - ( BSIZE * 2 )));

   INIT_MAGIC( xheap, HEAP_MAGIC );/* init the magic number */

   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * Initialize the first block in the heap */

   xheap -> first -> psize = 0;
   xheap -> first -> tsize = xheap -> free + BSIZE;

   xheap -> first -> flags = FIRST_BIT | LAST_BIT; /* mark as both first and last block */

   NEXT_PTR( xheap -> first ) = NULL; /* terminate the free list */
   PREV_PTR( xheap -> first ) = NULL; /* terminate the free list */

   INIT_MAGIC( xheap -> first, BLOCK_MAGIC );  /* init the first block's magic number */

   dpf0( "\n" );
   dpf1( "Heap Ptr         = %p\n", xheap );
   dpf1( "Heap First       = %p\n", xheap -> first );
   dpf1( "Heap Free List   = %p\n", xheap -> freel );
   dpf1( "Heap End         = %p\n", PTR_ADD( xheap, xheap -> size - 1 ));
   dpf2( "Heap Size        = %ld (%08lX)\n", xheap -> size, xheap -> size );
   dpf2( "Heap Free        = %ld (%08lX)\n", xheap -> free, xheap -> free );
   dpf1( "Heap Num Free    = %ld\n", xheap -> num_free );
   dpf1( "Heap Num Alloced = %ld\n", xheap -> num_alloced );

   return (void *) xheap;

#endif
   }

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

#if COMPILE_OUT_HEAP
/* heap stuff is compiled out! */
#else

/**
 * FUNC   : cm
 *
 * DESC   : check magic
 *
 * RETURNS: TRUE if the magic value checks
 *          FALSE if not
 */

#if TURN_ON_VERIFY_HEAP
static int cm( const char *magic, const char *value )

   {
   int i;

   for (i = 0; i < MAGIC_SIZE; i++)
      if (magic[ i ] != value[ i ])
         return 1;

   return 0;
   }
#endif

/**
 * FUNC   : heap_reset
 *
 * DESC   : Reset the heap so that it is empty!
 *
 *          After this function returns, the heap will be in the same state
 *          as it was after heap_initialize returned
 */

void heap_reset( void *theap )

   {
   DECLARE_XHEAP;

   VERIFY_HEAP( HEAP );

   /* Reset the heap structure */
   HEAP -> first = ( Blok * ) PTR_ADD( theap, HSIZE );
   HEAP -> llastb = ( Blok * ) PTR_ADD( HEAP -> first, (HEAP -> size - HSIZE - ( BSIZE * 2 )));
   HEAP -> free = HEAP -> size - HSIZE - BSIZE;
   HEAP -> num_free = 1;
   HEAP -> num_alloced = 0;
   HEAP -> freel = ( FreeBlok * ) HEAP -> first;

   /* Initialize the first block in the heap */
   HEAP -> first -> psize = 0;
   HEAP -> first -> tsize = HEAP -> free;

   HEAP -> first -> flags = FIRST_BIT | LAST_BIT; /* mark as both first and last block */
   NEXT_PTR( HEAP -> first ) = NULL; /* terminate the free list */
   PREV_PTR( HEAP -> first ) = NULL; /* terminate the free list */

   /* init the first block's magic number */
   INIT_MAGIC( HEAP -> first, BLOCK_MAGIC );
   }

/**
 * FUNC   : heap_alloc
 *
 * DESC   : Allocates a block of memory from the heap
 *
 *          This function implements a first fit algoritem.
 *
 * RETURNS: A pointer to the allocated buffer.  If there is not a free
 *          block big enough, then NULL is returned
 */

void *heap_alloc( void *theap, BlockSize size )

   {
   FreeBlok *blk;  /* the current block */

   DECLARE_XHEAP;

   VERIFY_HEAP( HEAP );

   if (HEAP -> num_free == 0)
      return 0;

   REC_MALLOC; /* record that a malloc happend */

   for (blk = HEAP -> freel; blk != NULL; blk = NEXT_PTR( blk ))
      {
      VERIFY_BLOK( blk );

      /* Is the block free and large enough for the required size? */
      if (size <= blk -> tsize - BSIZE)
         {
         /*       split( theap, blk, size );  * Now in-line here  SEE FN#1 */
         Blok *nblk;       /* the next block in memory */
         BlockSize asize;  /* requested size rounded up to an even multple of 4 */
         BlockSize xsize;  /* the actual size of the allocated block */

         /* Keep block sizes an even multiple of BSIZE
          * note, BSIZE is an even multiple of 4! */
         {
         BlockSize x = size % BSIZE;
         asize = (x!=0) ? size+(BSIZE-x) : size;
         }

         assert( (asize % 4)     == 0 ); /* better be an even multiple of 4 */
         assert( (asize % BSIZE) == 0 ); /* ... and BSIZE */

         xsize = asize + BSIZE;

         /* Do we have an exact fit?? OR
          * Or will the resultant fragmented block be
          * less than (BSIZE*2) in size */
         if (size == ( blk -> tsize - BSIZE ) || ( blk -> tsize - xsize ) <= ( BSIZE * 2 ))
            {
            /* It doesn't make sense to split the block */
            HEAP -> num_free--;
            HEAP -> num_alloced++;
            HEAP -> free -= ( blk -> tsize - BSIZE );

            blk -> flags |= ALLOCED_BIT; /* Its allocated! */

            /* if this is the first block in the free list then we
             * gotta move the free list pointer in the heap structure.
             * Note, since we keep the linked list null terminated,
             * this works even when we remove the last block form the list. */
            if (HEAP -> freel == ( FreeBlok * ) blk)
               HEAP -> freel = NEXT_PTR( blk );

            /* Unlink this pointer from the free list */
            if (PREV_PTR( blk ) != NULL)
               NEXT_PTR( PREV_PTR( blk )) = NEXT_PTR( blk );
            if (NEXT_PTR( blk ) != NULL)
               PREV_PTR( NEXT_PTR( blk )) = PREV_PTR( blk );

            return (void *) PTR_ADD( blk, BSIZE );
            }

         blk -> tsize -= xsize;   /* Shrink the current block */

         nblk = NEXT_BLOK( blk ); /* Get a pointer to the new split block */

         nblk -> tsize = xsize;
         nblk -> psize = blk -> tsize;
         nblk -> flags = ALLOCED_BIT;      /* also set all other flag bits to zero */

         if (blk -> flags & LAST_BIT)      /* are we splitting the last one? */
            {
            nblk -> flags |= LAST_BIT;    /* new one is last */
            blk -> flags &= ~LAST_BIT;    /* previous one isn't */
            }

         /* Link the next block to the recently split block */
         if (!IS_LAST( nblk ))
            NEXT_BLOK( nblk ) -> psize = nblk -> tsize;

         INIT_MAGIC( nblk, BLOCK_MAGIC ); /* init the magic number */

         HEAP -> num_alloced++;
         HEAP -> free -= nblk -> tsize;

#if TURN_ON_VERIFY_HEAP
         if (!IS_FIRST( nblk ) && PREV_BLOK( nblk ) -> tsize != nblk -> psize)
            th_printf( "\nHEAP.C! Big Problem %d\n", __LINE__ );
#endif

         /* Note, since we are splitting the block, we don't have to
          * do any maintenance on the free list :) */

         /*----------------------------*/

         return (void *) PTR_ADD( nblk, BSIZE );
         }
      }

   /* Gee, we looked through the entire free list and couldn't find a block
    * Large enough for the requested size!  So, just return NULL
   */
   return NULL; /*lint !e527 : Unreachable code
                 * We'll never get here, but this keeps the compiler
                 * from griping. about no return value */
   }

/**
 * FUNC   : heap_calloc
 *
 * DESC   : Allocates a block of memory from the heap, and sets it to zero
 *
 * RETURNS: A pointer to the allocated buffer.  If there is not a free
 *          block big enough, then NULL is returned
 */

void *heap_calloc( void *theap, BlockSize nmemb, BlockSize size )
{
	void	*block;
	BlockSize	mulsize = nmemb*size;
	if ((block = heap_alloc( theap, mulsize )) != NULL)
		memset(block,0,(size_t)mulsize);
	return block;
}

/**
 * FUNC   : heap_realloc
 *
 * DESC   : reAllocates a block of memory from the heap
 *
 * RETURNS: A pointer to the allocated buffer.  If there is not a free
 *          block big enough, then NULL is returned. If the input buffer
 *          is null, just do a malloc.
 */

void *heap_realloc( void *theap, void *buff, BlockSize size )
{
	void	*tbuff;
	Blok	*blk;

	/* read programmers mind and do a malloc or free */
	if (buff == NULL)
		return heap_alloc(theap, size);
/*
the normal way to handle this is to malloc(0)
  if (size == 0)
		return heap_free( 
*/
	tbuff = heap_alloc(theap, size);
	if (tbuff) {
		blk = (Blok *) PTR_SUB (buff, BSIZE);
        if((blk->tsize - BSIZE) > size)
			memcpy(tbuff,buff,size);
        else
			memcpy(tbuff,buff,(blk->tsize - BSIZE));
	}
	heap_free( theap, buff );
	return tbuff;
}

/**
 * FUNC   : heap_free
 *
 * DESC   : frees a block
 *
 *          Markes a block as free and coaleses it with adjacent blocks
 *          as necessary
 *
 * PARAMS : heap - a pointer to the heap structure that defines the heap
 *          buf  - the buffer to free
 */

void heap_free( void *theap, void *buff )

   {
   Blok *blk;      /* The block to be freed  */
   Blok *nblk;     /* The next block         */
   Blok *pblk;     /* the previous block     */
   int   combined; /* set if the block is combined */

   DECLARE_XHEAP;

   REC_FREE;       /* record that a free happend */

   VERIFY_HEAP( HEAP );

   if (buff == 0)
      return;

   combined = 0;   /* assume its not combined */

   blk = ( Blok * ) PTR_SUB( buff, BSIZE );

   VERIFY_BLOK( blk );

   blk -> flags &= ~ALLOCED_BIT;       /* Flag this block as free */

   HEAP -> num_free++;
   HEAP -> num_alloced--;

   HEAP -> free += ( blk -> tsize - BSIZE );

   /* If this is not the first block in the heap, then lets see if we
    * can combine it with the previous block */
   if (!IS_FIRST( blk ))
      {
      pblk = PREV_BLOK( blk );

      if (IS_FREE( pblk ))
         {
         ZAP_MAGIC( blk ); /* un-mark the block as being valid */

         /* Combine the block with the previous block */
         HEAP -> num_free--;

         pblk -> tsize += blk -> tsize;
         pblk -> flags |= blk -> flags & LAST_BIT;
         HEAP -> free += BSIZE;
         blk = pblk;

         /* Note, we are combining the block with one alread on the free
          * list so we don't have to do any free list maintenance here */
         combined = 1;
         }
      }

   /* If this is not the last block in the heap, then lets see if we
    * can combine it with the next block */
   if (!IS_LAST( blk ))
      {
      nblk = NEXT_BLOK( blk );

      if (IS_FREE( nblk ))
         {
         HEAP -> num_free--;

         blk -> tsize += nblk -> tsize;
         blk -> flags |= nblk -> flags & LAST_BIT;
         HEAP -> free += BSIZE;

         ZAP_MAGIC( nblk ); /* un-mark the block as being valid */

         /* gotta remove the next block from the free list because
          * it is getting combined with the one that was just freed */

         /* if this is the first block in the free list then we
          * gotta move the free list pointer in the heap structure.
          * Note, since we keep the linked list null terminated,
          * this works even when we remove the last block form the list. */
         if (HEAP -> freel == ( FreeBlok * ) nblk)
            HEAP -> freel = NEXT_PTR( nblk );

         /* Unlink this pointer from the free list */
         if (PREV_PTR( nblk ) != NULL)
            NEXT_PTR( PREV_PTR( nblk )) = NEXT_PTR( nblk );
         if (NEXT_PTR( nblk ) != NULL)
            PREV_PTR( NEXT_PTR( nblk )) = PREV_PTR( nblk );
         }
      }

   if (!combined)
      {
      /* The newly free'd block was not combined with the previous
       * block so we need to add it to the front of the free list */

      if (HEAP -> freel != NULL)
         {
         /* we have a list, so just add it to the front of the list */
         PREV_PTR( HEAP -> freel ) = ( FreeBlok * ) blk;
         NEXT_PTR( blk ) = HEAP -> freel;
         PREV_PTR( blk ) = NULL;
         }
      else
         {
         /* the list is empty, so make this block the only one in the list */
         NEXT_PTR( blk ) = NULL;
         PREV_PTR( blk ) = NULL;
         }

      HEAP -> freel = ( FreeBlok * ) blk; /* in any case, the free list
                                           * starts with this block */
      }
   /* else,
        * the recently free'd block was combined with the previous
        * block which (since it is free) is already a member of the free
        * list. So, we don't need to do any free list maintenance here */

   if (!IS_LAST( blk ))
      {
      NEXT_BLOK( blk ) -> psize = blk -> tsize;
      }
   }

#if TURN_ON_DEBUG_HEAP
/**
 * FUNC   : dump_blok
 *
 * DESC   : Prints out the info about a blok
 */
static void dump_blok( const Blok *blk, long bnum )

   {
   dpf2( "Block %ld  addr = %p\n", bnum, blk );
#if TURN_ON_VERIFY_HEAP
   dpf1( "   %s  ", ( cm( blk -> magic, BLOCK_MAGIC ) ? "VALID" : "INVALID" ));
#endif
   dpf1( "   %s  ", IS_FREE( blk ) ? "FREE" : "ALLOCED" );
   dpf1( "   %s  ", IS_FIRST( blk ) ? "FIRST" : "" );
   dpf1( "   %s\n", IS_LAST( blk ) ? "LAST" : "" );
   dpf2( "   tsize = %08lx  psize = %08lx\n", blk -> tsize, blk -> psize );
   }
#endif

#if !defined(NDEBUG)
/**
 * FUNC   : ptr_check
 *
 * DESC   : check a pointer to see if it is inside the heap
 *
 * RETURNS: FALSE  if the pointer is ok
 *          TRUE   if the pointer is bad
 *
 * PARAMS : heap - a pointer to the heap structure that defines the heap
 *
 * NOTE   : This funciton could probably be implemented as a macro, but we
 *          may need to make it more sophisticated in the future so I made
 *          it a function.
 */

static int ptr_check( Heap *xheap, FreeBlok *ptr )

   {
   return !( ptr >= ( FreeBlok * ) xheap -> first && ptr <= ( FreeBlok * ) xheap -> llastb );
   }

/**
 * FUNC   : heap_check
 *
 * DESC   : check the heap to see if it is ok.
 *
 *          This function scans throught the heap looking for errors.
 *
 * RETURNS: 0 if the heap is ok
 *          If the heap is not ok, then a bit mask value is returned.
 *          indicating the problem(s) found.
 *
 * PARAMS : heap - a pointer to the heap structure that defines the heap
 */


long heap_check( void *theap )

   {
   long      rv            = 0;
   Blok *blk;
   FreeBlok *fblk;
   BlockSize heap_size = 0;
   BlockSize free_size = 0;
   BlockSize alloced_size = 0;
   BlockSize num_free = 0;
   BlockSize num_alloced = 0;
#if TURN_ON_DEBUG_HEAP
   long      bnum          = 0;  /* signed on purpose */
#endif

   Heap *xheap             = ( Heap * ) theap;

   /* If the TURN_ON_VERIFY_HEAP stuff is turned on, then check pointers
    * pointers as we can */
#if TURN_ON_VERIFY_HEAP
   assert( xheap != NULL );

   if (cm( xheap -> magic, HEAP_MAGIC ))
      {
      dpf0( "$$ Bad Heap Structure\n" );
      return HERR_BAD_HEAP_STRUCT;
      }

   if (cm( xheap -> first -> magic, BLOCK_MAGIC ))
      {
      dpf0( "$$ Bad First Block\n" );
      return HERR_FIRST_BLOCK_BAD;
      }
#endif

   for (blk = xheap -> first;;)
      {
#if TURN_ON_VERIFY_HEAP
      if (cm( blk -> magic, BLOCK_MAGIC ))
         {
         dpf0( "$$ Bad Block\n" );
         return HERR_BLOCK_BAD;
         }
#endif

      if (blk -> tsize < ( BSIZE * 2 ))
         {
         dpf1( "$$ Block Too Small (size==%lu)\n", blk -> tsize );
         rv |= HERR_BLOCK_TOO_SMALL;
         }

      if (( blk -> tsize % 4 ) != 0)
         {
         dpf1( "$$ Block Not a multiple of 4 (size==%lu)\n", blk -> tsize );
         rv |= HERR_BLOCK_SIZE_MOD;
         }

      if (!IS_FIRST( blk ))
         {
         if (blk -> psize != PREV_BLOK( blk ) -> tsize)
            {
            rv |= HERR_PSIZE_BAD;
            dpf2( "$$ blk->psize{%lu} != prev_blk->tsize{%lu}\n", blk -> psize, PREV_BLOK( blk ) -> tsize );
            }
         }

      if (IS_FREE( blk ))
         {
         num_free++;
         free_size += blk -> tsize - BSIZE;

         /* Look for adjacent free blocks (there had better
          * not be any) */
         if (!IS_LAST( blk ))
            {
            if (IS_FREE( NEXT_BLOK( blk )))
               {
               rv |= HERR_FREE_ADJACENT;
               dpf0( "$$ Free Blocks are Adjacent\n" );
               }
            }
         }
      else
         {
         /* its allocated; */
         num_alloced++;
         alloced_size += blk -> tsize - BSIZE;
         }

      if (rv)
         break;

      if (!IS_LAST( blk ))
         {
         blk = NEXT_BLOK( blk );
#if TURN_ON_DEBUG_HEAP
         bnum++;
#endif
         }
      else
         break;
      }

   if (rv == 0)
      {
      heap_size = (( num_free + num_alloced ) * BSIZE ) +
         free_size + alloced_size + HSIZE;

      if (heap_size != xheap -> size)
         {
         dpf2( "$$ heap_size{%lu} != xheap->size{%lu}\n", heap_size, xheap -> size );
         rv |= HERR_TOTAL_SIZE_BAD;
         }

      if (free_size != xheap -> free)
         {
         dpf2( "$$ free_size{%lu} != xheap->free{%lu}\n", free_size, xheap -> free );
         rv |= HERR_FREE_SIZE_BAD;
         }

      if (num_free != xheap -> num_free)
         {
         dpf2( "$$ num_free{%lu} != xheap->num_free{%lu}\n", num_free, xheap -> num_free );
         rv |= HERR_NUM_FREE_BAD;
         }

      if (num_alloced != xheap -> num_alloced)
         {
         dpf2( "$$ num_alloced{%lu} != xheap->num_alloced{%lu}\n", num_alloced, xheap -> num_alloced );
         rv |= HERR_NUM_ALLOCED_BAD;
         }

      if (rv == 0)
         {
         /* Now, we gotta check the free list */
         if (xheap -> num_free == 0)
            {
            /* the list is empty, so the free list pointer had better be NULL */
            if (xheap -> freel != NULL)
               rv |= HERR_FREELPTR_NN;  /* free list pointe not null */
            }
         else
            if (xheap -> num_free == 1)
               {
               /* the list should have only 1 element. so
                * -- the free list pointer had better be valid
                * -- the free block the list pointer points to should
                *    have  null next and prev pointers
               */
               if (ptr_check( xheap, xheap -> freel ))
                  {
                  rv |= HERR_BAD_FREELPTR;  /* bad free list pointer */
                  }
               else
                  {
                  fblk = xheap -> freel;

                  if (fblk -> prev != NULL)
                     rv |= HERR_BAD_FL_NEXT;

                  if (fblk -> next != NULL)
                     rv |= HERR_BAD_FL_NEXT;
                  }
               }
            else
               {
               BlockSize free_count = 1; /* starting at one on purpose! */

               if (ptr_check( xheap, xheap -> freel ))
                  {
                  rv |= HERR_BAD_FREELPTR;  /* bad free list pointer */
                  }
               else
                  {
                  /* first, check the first block */
                  fblk = xheap -> freel;

                  if (fblk -> prev != NULL)
                     rv |= HERR_BAD_FL_NEXT;

                  /* note, if we are here we KNOW that that there are two or
                   * more free blocks in the free list so the next pointer of
                   * the first block must not be null */
                  if (fblk -> next == NULL || ptr_check( xheap, fblk -> next ))
                     rv |= HERR_BAD_FL_NEXT;

                  if (rv == 0)
                     {
                     FreeBlok *previous;

                     while (rv == 0)  /* traverse the list */
                        {
                        previous = fblk;
                        fblk = fblk -> next;

                        if (fblk == NULL)
                           break;

                        free_count++;

#if TURN_ON_VERIFY_HEAP
                        if (cm( fblk -> magic, BLOCK_MAGIC ))
                           {
                           dpf0( "$$ Bad Block\n" );
                           return HERR_FL_BLOCK_BAD;
                           }
#endif

                        /* check the consistency of the next pointer */
                        if (free_count == xheap -> num_free)
                           {
                           if (fblk -> next != NULL)
                              rv |= HERR_BAD_FL_TOO_MANY;
                           }
                        else
                           {
                           if (fblk -> next == NULL)
                              rv |= HERR_BAD_FL_NOT_NUFF;
                           else
                              if (ptr_check( xheap, fblk -> next ))
                                 rv |= HERR_BAD_FL_NEXT;
                           }

                        /* check the consitency of the prev pointer */
                        if (fblk -> prev == NULL || ptr_check( xheap, fblk -> prev ))
                           rv |= HERR_BAD_FL_PREV;

                        if (fblk -> prev != previous)
                           rv |= HERR_BAD_PREV_LINK;
                        }
                     }
                  }
               }
         }
      }

#if TURN_ON_DEBUG_HEAP
   else
      {
      if (rv != 0)
         {
         dpf1( "\nLast Op %s\n", ops[ last_op ] );

         dpf1( "Heap Ptr         = %p\n", xheap );
         dpf1( "Heap First       = %p\n", xheap -> first );
         dpf1( "Heap Last Block  = %p\n", xheap -> llastb );
         dpf1( "Heap Free List   = %p\n", xheap -> freel );
         dpf1( "Heap End         = %p\n", PTR_ADD( xheap, xheap -> size - 1 ));
         dpf2( "Heap Size        = %lu (%08lX)\n", xheap -> size, xheap -> size );
         dpf2( "Heap Free        = %lu (%08lX)\n", xheap -> free, xheap -> free );
         dpf1( "Heap Num Free    = %ld\n", xheap -> num_free );
         dpf1( "Heap Num Alloced = %ld\n", xheap -> num_alloced );
         dpf0( "\n" );

         if (!IS_FIRST( blk ))
            dump_blok( PREV_BLOK( blk ), bnum - 1 );

         dump_blok( blk, bnum );

         if (!IS_LAST( blk ))
            dump_blok( NEXT_BLOK( blk ), bnum + 1 );
         }
      }
#endif

   return rv;
   }

#endif

/**
 * FUNC   : heap_free_space
 *
 * DESC   : Returns the total free space in the heap
 */

BlockSize heap_free_space( void *theap )

   {
   DECLARE_XHEAP;

   return HEAP -> free;
   }

/**
 * FUNC   : heap_biggest_free_block
 *
 * RETURNS: The size of the biggest free block
 */

BlockSize heap_biggest_free_block( void *theap )

   {
   Blok *blk;
   BlockSize biggest_blok = 0;

   DECLARE_XHEAP;

#if TURN_ON_VERIFY_HEAP
   assert( theap != NULL );
#endif

   VERIFY_HEAP( HEAP );

   for (blk = HEAP -> first;;)
      {
      VERIFY_BLOK( blk );

      if (IS_FREE( blk ))
         {
         if (blk -> tsize > biggest_blok)
            biggest_blok = blk -> tsize;
         }

      if (!IS_LAST( blk ))
         blk = NEXT_BLOK( blk );
      else
         break;
      }

   return biggest_blok - BSIZE;
   }

/**
 * FUNC   : heap_stats
 *
 * DESC   : Gets the heap statistics
 *
 * PARAMS : heap - a pointer to the heap
 *          stats - a pointer to a heap statistics structure to fill out
 */

void heap_stats( void *theap, HeapStats *stats )

   {
   DECLARE_XHEAP;

   VERIFY_HEAP( HEAP );

   stats -> size = HEAP -> size;            /* total size of the heap          */
   stats -> free = HEAP -> free;            /* free (useable) space in the heap*/
   stats -> num_free = HEAP -> num_free;    /* number of free blocks           */
   stats -> num_alloced = HEAP -> num_alloced; /* number of allocated blocks      */
   }

/**
 * FUNC   : heap_dump
 *
 * DESC   : Dumps the heap
 */

#if !defined(NDEBUG)

void heap_dump( void *theap )

   {
   Blok *blk;
   int       i;

   DECLARE_XHEAP;

#if TURN_ON_VERIFY_HEAP
   assert( theap != NULL );
#endif

   VERIFY_HEAP( HEAP );

   dpf0( "\n" );
   dpf1( "Heap Ptr         = %p\n", HEAP );
   dpf1( "Heap First       = %p\n", HEAP -> first );
   dpf1( "Heap End         = %p\n", PTR_ADD( theap, HEAP -> size - 1 ));
   dpf2( "Heap Size        = %ld (%08lX)\n", HEAP -> size, HEAP -> size );
   dpf2( "Heap Free        = %ld (%08lX)\n", HEAP -> free, HEAP -> free );
   dpf1( "Heap Num Free    = %ld\n", HEAP -> num_free );
   dpf1( "Heap Num Alloced = %ld\n", HEAP -> num_alloced );

   for (i = 0, blk = HEAP -> first;; i++)
      {
      VERIFY_BLOK( blk );

      dpf4( "%04d, BLK=%p tsize=%8ld psize=%8ld ", i, blk, blk -> tsize, blk -> psize );

      dpf1( " %s ", IS_FREE( blk ) ? "F" : "A" );
      dpf1( " %s ", IS_FIRST( blk ) ? "F" : " " );
      dpf1( " %s ", IS_LAST( blk ) ? "L" : " " );

#if TURN_ON_VERIFY_HEAP
      dpf1( " %8.8s", blk -> magic );
#endif

      dpf0( "\n" );

      if (!IS_LAST( blk ))
         blk = NEXT_BLOK( blk );
      else
         break;
      }
   }
#endif


#endif /* COMPILE_OUT_HEAP */
/** @} */
/** @} */
