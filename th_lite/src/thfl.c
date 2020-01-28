/**
 * @file
 * @brief  Test Harness functional layer
 * 
 *$RCSfile: thfl.c,v $
 *
 * @author  ECL, LLC
 *
 *  EEMBC : Technical Advisory Group (TechTAG)
 *
 *    CVS : $Revision: 1.3 $
 *          $Date: 2006/03/09 17:34:18 $
 *          $Author: rick $
 *          $Source: /usr/local/cvs/eembc2/th_lite/src/thfl.c,v $
 *          
 * @note   
 *
 *
 * HISTORY :
 *
 * $Log: thfl.c,v $
 * Revision 1.3  2006/03/09 17:34:18  rick
 * Version 2 Office Release Candidate 5
 *
 * Revision 1.17  2005/12/02 23:53:37  rick
 * Fix mixed EOL format causing ^M's to appear in Unix checkouts.
 *
 * Revision 1.16  2005/09/10 04:02:24  rick
 * eol update, add uu_send_file
 *
 * Revision 1.15  2005/04/27 20:33:15  rick
 * Copyrite update 2005
 *
 * Revision 1.14  2004/12/08 23:27:18  rick
 * New standard header for documentation generation.
 *
 * Revision 1.13  2004/11/09 15:42:20  rick
 * Generalize Valgrind fix to integer size for all compiler cases.
 *
 * Revision 1.12  2004/11/04 22:15:12  rick
 * Fix valgrind calloc(1,1)
 *
 * Revision 1.11  2004/07/09 05:11:21  rick
 * Add gettimeofday
 *
 * Revision 1.10  2004/07/03 03:13:40  rick
 * Add time, link, and exit to redirection.
 *
 * Revision 1.9  2004/07/01 17:37:27  rick
 * Add th_crcbuffer, and place all redirection includes inside file sentinel.
 *
 * Revision 1.8  2004/06/23 05:55:05  rick
 * EE_REDIRECT, and Shared Files
 *
 * Revision 1.7  2004/06/22 14:31:49  rick
 * Move add_version from thlib to thfl.
 *
 * Revision 1.6  2004/06/14 18:03:32  rick
 * Bug 274: Precision in log files is not large enough for reporting results on simulators.
 *
 * Revision 1.5  2004/05/20 18:41:24  rick
 * Fix definition when HEAP_BASE is defined
 *
 * Revision 1.4  2004/05/07 22:45:56  rick
 * Match Heap manager in harnesses, move internal routines to thfl.c
 *
 * Revision 1.3  2004/05/06 21:15:48  rick
 * Fix th_strdup for heap, and epn NULL return to 0 string
 *
 * Revision 1.2  2004/02/11 02:56:08  rick
 * Add macro redefinitions, improve efn and fileio
 *
 * Revision 1.1  2004/01/28 23:08:31  rick
 * Add th_strdup, fileio cwd
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

#include "thcfg.h"

#include <string.h> /* strdup */
#include <ctype.h>
#if HAVE_MALLOC || !USE_TH_PRINTF
/** atol, malloc, calloc */
#include <stdlib.h>
#endif
#if !USE_TH_PRINTF
#include <stdio.h>
#endif

#include "thfl.h"
#include "heap.h"

/** @addtogroup THLFL
@{ */
/** @addtogroup thfl Functional layer routines and utilities
@{ */

void  *i_calloc( size_t nmemb, size_t size, const char *fn, int line );

/*
 * Heap routines with th_regular i_xxx form
 */

/* Globals defined in heap.c */

extern void 	*th_heap;
#ifdef HEAP_BASE
extern char	*mem_base;
#else
extern char	mem_base[];
#endif
extern size_t	mem_size;

void mem_heap_initialize(void)
{
#if HAVE_MALLOC
/* do nothing */
#elif COMPILE_OUT_HEAP
/* do nothing */
#else
	th_heap = heap_initialize( mem_base, mem_size );
#endif
}

/**
 * FUNC   : i_malloc
 *
 * DESC   : functional layer implementation of th_malloc()
 */
void *i_malloc( size_t size, const char *file, int line )

   {
#if HAVE_MALLOC
   void *block = malloc( size );

   if (block == NULL)
      {
         th_printf( "** ERROR:  Out Of memory! size=%ld %s:%d\n", size, file, line );
         t_exit( 1, "--      :  Detected in %s:%d\n", file, line );
      }

   return block;
#elif COMPILE_OUT_HEAP
	size=size;
	th_printf( "** ERROR: Heap Routines are compiled out! %s:%d\n", file, line );
	t_exit( 1, "\n" );
	/**
	 *@note : If this code executes, then the heap routines have been compiled
	 *        out by setting the COMPILE_OUT_HEAP define in THCFG.H.
	 *        This means you CANNOT run benchmarks that need the heap!
	 */
	return NULL;
#else
   void *block = heap_alloc( th_heap, size );

   if (block == NULL)
      {
         th_printf( "** ERROR:  Out Of memory! size=%ld %s:%d\n", size, file, line );
         t_exit( 1, "--      :  Detected in %s:%d\n", file, line );
      }

   return block;
#endif
   }

/**
 * FUNC   : i_calloc
 *
 * DESC   : functional layer implementation of th_calloc()
 */
void *i_calloc( size_t nmemb, size_t size, const char *file, int line )

   {
#if HAVE_MALLOC
   void *block = calloc( nmemb, size );

   if (block == NULL)
      {
         th_printf( "** ERROR:  Out Of memory! size=%ld %s:%d\n", size, file, line );
         t_exit( 1, "--      :  Detected in %s:%d\n", file, line );
      }

   return block;
#elif COMPILE_OUT_HEAP
    nmemb=nmemb;
	size=size;
	th_printf( "** ERROR: Heap Routines are compiled out! %s:%d\n", file, line );
	t_exit( 1, "\n" );
	/* 
	 * NOTE : If this code executes, then the heap routines have been compiled
	 *        out by setting the COMPILE_OUT_HEAP define in THCFG.H.
	 *        This means you CANNOT run benchmarks that need the heap!
	 */
	return NULL;
#else
   void *block = heap_calloc( th_heap, nmemb, size );

   if (block == NULL)
      {
         th_printf( "** ERROR:  Out Of memory! size=%ld %s:%d\n", size, file, line );
         t_exit( 1, "--      :  Detected in %s:%d\n", file, line );
      }

   return block;
#endif
   }

/** functional layer implementation of th_realloc() */
void *i_realloc( void *block, size_t size, const char *file, int line )
{
#if HAVE_MALLOC
   void *newblock = realloc( block, size );

   if (newblock == NULL)
      {
         th_printf( "** ERROR:  Out Of memory! size=%ld %s:%d\n", size, file, line );
         t_exit( 1, "--      :  Detected in %s:%d\n", file, line );
      }

   return newblock;
#elif COMPILE_OUT_HEAP
	size=size;
	th_printf( "** ERROR: Heap Routines are compiled out! %s:%d\n", file, line );
	t_exit( 1, "\n" );
	/* 
	 * NOTE : If this code executes, then the heap routines have been compiled
	 *        out by setting the COMPILE_OUT_HEAP define in THCFG.H.
	 *        This means you CANNOT run benchmarks that need the heap!
	 */
	return NULL;
#else
   void *newblock = heap_realloc( th_heap, block, size );

   if (newblock == NULL)
      {
         th_printf( "** ERROR:  Out Of memory! size=%ld %s:%d\n", size, file, line );
         t_exit( 1, "--      :  Detected in %s:%d\n", file, line );
      }

   return newblock;
#endif
}
/** functional layer implementation of th_strdup() */
char *i_strdup( const char *string, const char *file, int line )
{
	/* Must do internal heap manager case first */
#if !HAVE_MALLOC && !COMPILE_OUT_HEAP
	char *newblock = heap_alloc( th_heap, strlen(string)+1 );

	if (newblock == NULL)
	{
		th_printf( "** ERROR:  Out Of memory! size=%ld %s:%d\n", strlen(string), file, line );
		t_exit( 1, "--      :  Detected in %s:%d\n", file, line );
	}
	/* can also return memcpy(newblock,string,strlen(string)+1) (calloc) */
	newblock = strcpy(newblock,string);
	return newblock;
#elif HAVE_STRDUP
   char *newblock = strdup( string );

   if (newblock == NULL)
      {
         th_printf( "** ERROR:  Out Of memory! size=%ld %s:%d\n", strlen(string), file, line );
         t_exit( 1, "--      :  Detected in %s:%d\n", file, line );
      }

   return newblock;
#elif HAVE_MALLOC
	char *newblock = malloc( strlen(string)+1 );

	if (newblock == NULL)
	{
		th_printf( "** ERROR:  Out Of memory! size=%ld %s:%d\n", strlen(string), file, line );
		t_exit( 1, "--      :  Detected in %s:%d\n", file, line );
	}
	/* can also return memcpy(newblock,string,strlen(string)+1) (calloc) */
	newblock = strcpy(newblock,string);
	return newblock;
#elif COMPILE_OUT_HEAP
	string=string;
	th_printf( "** ERROR: Heap Routines are compiled out! %s:%d\n", file, line );
	t_exit( 1, "\n" );
	/* 
	 * @note  If this code executes, then the heap routines have been compiled
	 *        out by setting the COMPILE_OUT_HEAP define in THCFG.H.
	 *        This means you CANNOT run benchmarks that need the heap!
	 */
	return NULL;
#else
#error "Invalid COMPILE_OUT_HEAP, HAVE_MALLOC, HAVE_STRDUP setting"
#endif
}

/** functional layer implementation of i_free(). */
void i_free( void *block, const char *file, int line ){
#if HAVE_MALLOC
	file=file;
	line=line;
	free(block);
#elif COMPILE_OUT_HEAP
/* do nothing */
	file=file;
	line=line;
	block=block;
#else
	file=file;
	line=line;
   heap_free( th_heap, block );
#endif
}

/** functional layer implementation of th_heap_reset(). */
void i_heap_reset( void )
{
#if !COMPILE_OUT_HEAP
   heap_reset( th_heap );
#endif
}

/* File system utilities, originally bundled with string. */

/** returns a pointer to the file name portion of a path
 *
 *          Used to trim off drive letters and directory paths from file
 *          specs.
 *
 * @note     This function assumes that both the '\' and '/' characters
 *           are directory path separators.  E.g. we handle both Microsoft
 *           and Unix style paths.
 * @param fn Path name to extract file name.
 * @retval A pointer to the file name within fn (not malloc'ed)
 */
char *efn( const char *fn )
{
	char *s=(char *)fn;
	char *end;
	if (!fn || !*fn) return NULL;

	/* Find the right most ':' or '/' or '\' in the string */

	for (end = s; *s; s++)
      if (*s == '/' || *s == '\\' || *s == ':')
         end = s + 1;
   return end;
}
/** Return the path name portion of a string.
@param fn - file name with path
@retval A new string with path name, or NULL Malloc'ed, caller may free.
*/
char *epn( const char *fn )
{
	const char *filename = efn(fn);
	char *pathname;
	int len;

	if (fn == filename)
	{
		/** Must return an element that can be free'ed
		@note Calling calloc(1,1) caused valgrind error from character
		comparisons that assume an int sized character.
		*/
		pathname=i_calloc(sizeof(int),1,__FILE__,__LINE__);
	}
	else
	{
		/* Create a fresh string with pathname */
		len = (int)(filename-fn);
		pathname = i_calloc(len+1,1,__FILE__,__LINE__);
		strncpy(pathname,fn,len);
	}
	return pathname;
}

/** time  returns the time since the Epoch, measured in seconds.

If t is non-NULL, the return value is also stored in the memory pointed to by t.

@param t Storage location for time, or NULL.
@retval On  success,  the value of time in seconds since the Epoch is returned.
       On error, ((time_t)-1) is returned, and errno is set appropriately.
*/
ee_time_t ee_time(ee_time_t *t)
{
	const ee_time_t epoch=12345;
	if (t) *t=epoch;
	return epoch;
}
/** Returns broken-down time given time t. 
Stub for now. This is the mktime code if needed.
*/
struct ee_tm *ee_localtime(const ee_time_t *t)
{
	static struct ee_tm brokentime = {0,0,0,0,0,0,0,0,0};
	return &brokentime;
}
/** Stub routine for gettimeofday. MUST RETURN SUCCESS. */
int ee_gettimeofday (struct ee_timeval *tp, void *tzp)
{
	tp->tv_sec=0;
	tp->tv_usec=0;
	return 0;
}

/** used to avoid warning: returning address of local variable or temporary */
static	char	avbuf[80];
/** Append Version number to description string.  */
static char *add_version(char *desc,version_number vnum)
{
	/* desc char[64] + ver char[4] + " V.\0" */
	th_sprintf(avbuf,"%s V%1u.%1u%c%1u",desc,vnum.major,vnum.minor,vnum.step,vnum.revision);
	return avbuf;
}

/**
 * FUNC   : report_info
 *
 * DESC   : Reports the system info to the use or HCP
 */
static void report_info( TCDef *tcdef )
{
th_printf( ">>------------------------------------------------------------\n" );
th_printf( ">> EEMBC Component          : %s\n",EEMBC_TH_ID);
th_printf( ">> EEMBC Member Company     : %s\n",tcdef->member);
th_printf( ">> Target Processor         : %s\n",tcdef->processor);
th_printf( ">> Target Platform          : %s\n",tcdef->platform);
th_printf( ">> Target Timer Available   : %s\n",th_timer_available() ? "YES"   : "NO" );
th_printf( ">> Target Timer Intrusive   : %s\n",th_timer_is_intrusive() ? "YES" : "NO" );
th_printf( ">> Target Timer Rate        : %d\n",th_ticks_per_sec());
th_printf( ">> Target Timer Granularity : %d\n",th_tick_granularity());
#if		CRC_CHECK
th_printf( ">> Required Iterations      : %d\n",tcdef->rec_iterations);
#else
th_printf( ">> Recommended Iterations   : %d\n",tcdef->rec_iterations);
#endif
if (tcdef->iterations != tcdef->rec_iterations)
th_printf( ">> Programmed Iterations    : %d\n",tcdef->iterations );
th_printf( ">> Bench Mark               : %s\n",add_version(tcdef->desc,tcdef->bm_vnum));
}

/**
 * FUNC   : th_report_results
 *
 * DESC   : Used to report a test's results after it is finished
 *
 *          This function is used to report the results of a test after
 *          it has run.  It differs from TH in that Expected CRC is reported, 
 *          and passed instead of a character string.
 */
int th_report_results(TCDef *tcdef, e_u16 Expected_CRC )
{
int	exit_code = Success;

/* Used to unload double from two vx results variables */ 
#if	VERIFY_FLOAT && FLOAT_SUPPORT
	typedef union {
		double	d;
		size_t	v[2];
	} d_union;
	d_union	dunion;
#endif

/* Standard Log file Print Section */
	report_info(tcdef);

/* Standard Results Section */

#if		CRC_CHECK
th_printf(  "--  Intrusive CRC     = %4x\n",tcdef->CRC);
#elif	NON_INTRUSIVE_CRC_CHECK
th_printf(  "--  Non-Intrusive CRC = %4x\n",tcdef->CRC);
#else
th_printf(  "--  No CRC check      = 0000\n"); 
#endif
th_printf(  "--  Iterations        = %u\n", tcdef->iterations );
th_printf(  "--  Target Duration   = %u\n", tcdef->duration );
th_printf(  "--  Target Timer Rate = %d\n", th_ticks_per_sec());
#if		VERIFY_INT
th_printf(  "--  v1                = %d\n", tcdef->v1);
th_printf(  "--  v2                = %d\n", tcdef->v2);
th_printf(  "--  v3                = %d\n", tcdef->v3);
th_printf(  "--  v4                = %d\n", tcdef->v4);
#endif
#if		VERIFY_FLOAT && FLOAT_SUPPORT
dunion.v[0]	= tcdef->v1;
dunion.v[1] = tcdef->v2;
th_printf(  "--  v1v2              = %f\n", dunion.d);
dunion.v[0]	= tcdef->v3;
dunion.v[1] = tcdef->v4;
th_printf(  "--  v3v4              = %f\n", dunion.d);
#endif

#if		FLOAT_SUPPORT
   if (tcdef -> duration > 0)
      {
      double fduration;
      double fiterations;
      double ticks_per_sec;
      double its_per_sec;

      /* Ok, lets do this in floating point.... */

      fduration = tcdef -> duration;
	  fiterations = tcdef->iterations;
      ticks_per_sec = th_ticks_per_sec();

      its_per_sec = fiterations / ( fduration / ticks_per_sec );

      th_printf( "--  Iterations/Sec    = %18.9f\n", its_per_sec );
      th_printf( "--  Total Run Time    = %18.9fsec\n", fduration / ticks_per_sec );
      th_printf( "--  Time / Iter       = %18.9fsec\n", 1.0 / its_per_sec );
      }
#endif

   /* Failure Section */
#if		CRC_CHECK || NON_INTRUSIVE_CRC_CHECK
	if( tcdef->CRC != Expected_CRC ){
		th_printf("--  Failure: Actual CRC %x, Expected CRC %x\n",tcdef->CRC,Expected_CRC);
		exit_code = Failure;
	} 
#endif

	if (tcdef->iterations != tcdef->rec_iterations) {
		th_printf("--  Failure: Actual iterations %x, Expected iterations %x\n",tcdef->iterations,tcdef->rec_iterations);
		exit_code = Failure;
	}

if	(exit_code == SUCCESS )	th_printf( ">> DONE!\n" );
else						th_printf( ">> Failure: %d\n", exit_code );

	/* 
	 * user defined print information
	 * outside fixed standard log so automated scripts still work
	 */
	al_report_results();

/* Match TH Regular output */
	th_printf( ">> BM: %s\n", add_version(tcdef->desc,tcdef->bm_vnum));
	th_printf( ">> ID: %s\n\n", tcdef->eembc_bm_id );

	return	exit_code;
}

/**
 * FUNC   : t_exit
 *
 * DESC   : The benchmark code failed internally.
 *
 * RETURNS: Any error value supplied by the caller.
 * NOTE: differs from th_exit in that it returns exit code, and does
 *       not print unless windows example code.
 *       Add any signal code to aid debugging.
 * @note Keep in sync with thlib.c:th_exit. Exit cannot go through layers.
 */
void t_exit( int exit_code, const char *fmt, ... )
{
	va_list args;
	va_start( args, fmt );
	al_exit( exit_code, fmt, args );
	va_end( args );
}

/** @} */
/** @} */
