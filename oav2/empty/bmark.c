/**
 * @file
 * @brief  TH Regular Test Harness routines for benchmarks
 * 
 *$RCSfile: bmark.c,v $
 *
 * @author  Rick Foos, ECL, LLC
 *
 *  EEMBC : Technical Advisory Group (TechTAG)
 *
 *    CVS : $Revision: 1.19 $
 *          $Date: 2005/07/17 19:46:45 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/techtag/empty/bmark.c,v $
 *          
 * @note    Since benchmarks can be entered (run) multiple times, the benchmark
 *          MUST NOT depend on global data being initialized.  E.g. it must
 *          complelty initialize itself EVERY TIME its t_run_test() function
 *          is called.
 *
 *
 * HISTORY :
 *
 * $Log: bmark.c,v $
 * Revision 1.19  2005/07/17 19:46:45  rick
 * Specification and early work on AI Real-Time
 *
 * Revision 1.18  2005/04/27 20:38:34  rick
 * Copyrite update 2005
 *
 * Revision 1.17  2004/12/09 20:41:11  rick
 * New header comments for documentation
 *
 * Revision 1.16  2004/01/22 01:03:14  rick
 * Release cleanup, copyright year corrections
 *
 * Revision 1.15  2003/08/15 00:30:50  rick
 * Move descriptions to common header
 *
 * Revision 1.14  2002/12/31 16:24:08  rick
 * Add DO_DIFFMEASURE, DO_UUENCODE and diffmeasure sizing
 *
 * Revision 1.13  2002/08/12 20:23:06  rick
 * Fix have_malloc compile_out_heap conflict
 *
 * Revision 1.12  2002/08/09 00:01:55  rick
 * Add NI CRC to TH Regular
 *
 * Revision 1.11  2002/08/07 22:21:09  rick
 * Add NI CRC to TH Regular
 *
 * Revision 1.10  2002/08/06 21:59:04  rick
 * Add NI CRC to TH Regular
 *
 * Revision 1.9  2002/07/26 22:21:33  rick
 * If no heap, Compile out th_malloc call.
 *
 * Revision 1.8  2002/07/22 16:10:12  rick
 * Fix iteration dependant NI CRC
 *
 * Revision 1.7  2002/05/29 22:12:37  rick
 * Set recommended iterations with make
 *
 * Revision 1.6  2002/05/23 20:22:36  rick
 * Clear ansi warnings
 *
 * Revision 1.5  2002/04/25 23:20:30  rick
 * Cleanup after bug database scrub
 *
 * Revision 1.4  2002/04/12 21:30:47  rick
 * Make Lite more consistent with Regular
 *
 * Revision 1.3  2002/03/20 23:19:26  rick
 * Empty Benchmarks
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

/*******************************************************************************
    Includes                                                                    
*******************************************************************************/

#include "algo.h"

/*
 * Test Component Defintion Structure
 */

int    t_run_test( size_t iterations, int argc, const char* argv[] );
int    test_main( struct TCDef** tcdef, int argc, const char* argv[] );

static TCDef the_tcdef = 
   {
   BM_ID,
   EEMBC_MEMBER_COMPANY,
   EEMBC_PROCESSOR,
   EEMBC_TARGET,
   BM_DESCRIPTION,
   TCDEF_REVISION,       
   NULL, /* pointer to the next TCDef */
   /* TH Version Number Required */
   { EEMBC_TH_MAJOR, EEMBC_TH_MINOR, EEMBC_TH_STEP, EEMBC_TH_REVISION },  
   /* Target Hardware Version Number Required (make all zeros to ignore)*/
   { 0, 0, 0, 0 },  
   /* The Version number of this Benchmark */
   BM_VERSION,
   ITERATIONS,    
   &t_run_test, 
   &test_main,
   NULL,        /* there is no main funciton in this implementation */
   NULL         /* there is no entry function in this implementation */
   };

/*
 * Local Declarations
 */

#if	defined(DO_UUENCODE)
#define T_BSIZE 1024
char* t_buf;
#endif

#if		defined(DO_DIFFMEASURE) && VERIFY_FLOAT && FLOAT_SUPPORT
static e_f64 test_buf[] = { 1.0,0.0 }; 
#endif

/*------------------------------------------------------------------------------
 * FUNC   : t_run_test
 *
 * DESC   : called to run the test
 *
 *          This function is called to start the test.  It does not return
 *          until after the test is completed (finished).  Note, th_finished()
 *          and th_report_results() MUST be called before this function
 *          returns if results are to be report.  If these are not called
 *          then no results will be reported for the test.
 *         
 * NOTE   : after this function returns, no other functions in the test
 *          will be called.  EG, returning from this function is equivelent
 *          to returning from a main() or calling th_exit()
 *
 * RETURNS: Success if the test ran fine.  If th_finished() and
 *          th_report_results() were not called, then the test finished
 *          successfully, but there were no results and the host will
 *          not be able to measure the test's duration.
 * ---------------------------------------------------------------------------*/

int t_run_test( size_t iterations, int argc, const char* argv[] )
{
	size_t         loop_cnt; /* Actual Iterations */
	THTestResults  results;
	static char    info[64]; /* must be static */

#if	defined(DO_UUENCODE)
	int				bsize;
	int				c,i;
	const			FileDef* fd; 
#endif

#if		defined(DO_DIFFMEASURE) && VERIFY_FLOAT && FLOAT_SUPPORT
	e_f64			*golden_result; 
	d_union			dunion;
	e_s16			DummyData[2]={1,0};
	e_s16			NumberOfLags=1;
#endif
   
	/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
	 * First, initialize the data structures we need for the test
	 */

#if		defined(DO_DIFFMEASURE) && VERIFY_FLOAT && FLOAT_SUPPORT
   	golden_result= (e_f64 *)&test_buf; 
#endif

#if	defined(DO_UUENCODE)
	if ( argc == 2 )
	{
		fd = th_get_file_def( argv[1] );

		if ( fd == NULL )
		{
		th_printf( "\nBM Error! Cannot find file '%s'\n", argv[1] );
		return Failure;
         }
      
      th_printf( "\nBM: Using '%s' as data\n", argv[1] );
      
      t_buf = fd->buf;
      bsize = (int)fd->size;
      }
   else
      {
      fd = NULL;
      
      bsize = T_BSIZE;

      t_buf = (char*)th_malloc( T_BSIZE );
   
      if ( t_buf == NULL )
         {
         th_exit( THE_OUT_OF_MEMORY, "Cannot Allocate Memory %s:%d", __FILE__, __LINE__ );
         }

	/*
	 * Initialize the test buffer
	 */   
		for ( c = 'A', i = 0; i < T_BSIZE; i++, (c == '~' ? c = 'A' : c++) )
		{
			t_buf[i] = c;
		}
	}
#else
	/* Unused */
	argc=argc;
	argv=argv;
#endif

	/*
	 * This is the actual benchmark
	 */
	th_signal_start();  /* Tell the host that the test has begun */

	/*
	 * Void - there is no benchmark.  
	 * Just get the size of the Test Harness
	 */
	loop_cnt = iterations;

	results.duration   = th_signal_finished();  /* signal that we are finished */

	results.iterations = loop_cnt;
#if		defined(DO_DIFFMEASURE) && VERIFY_FLOAT && FLOAT_SUPPORT
	dunion.d           = diffmeasure (golden_result, NumberOfLags, COMPLEX, DummyData, NumberOfLags, COMPLEX);
	results.v1         = dunion.v[0];
	results.v2         = dunion.v[1];
#else
	results.v1         = 0;
	results.v2         = 0;
#endif
	results.v3         = 0;
	results.v4         = 0;
	results.info       = info;

	th_sprintf( info, "Just at test to see how big the TH is." );

#if		NON_INTRUSIVE_CRC_CHECK
	results.CRC=0;
	results.CRC = Calc_crc8((e_u8)0, results.CRC);
#elif	CRC_CHECK
	results.CRC=0;
	results.CRC = Calc_crc8((e_u8)0, results.CRC);
#else
	results.CRC=0;
#endif

#if	defined(DO_UUENCODE)
	if ( fd != NULL )
	{
		/* send the input buffer back to the host */
		th_send_buf_as_file( fd->buf, fd->size, fd->name );
	}
#endif

	return th_report_results( &results, EXPECTED_CRC );
}

/*------------------------------------------------------------------------------
 * FUNC   : test_main
 *
 * DESC   : the test (or bench mark) main entry point
 *
 * RETURNS: Any error value defined in th_error.h
 * ---------------------------------------------------------------------------*/

int test_main( struct TCDef** tcdef, int argc, const char* argv[] )

{
	argc=argc;
	argv=argv;
   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -    
    *                  >>> GOTTA DO THIS FIRST <<<
    * Point the test harness at our test defintion struction
    */
   *tcdef = &the_tcdef;
   
   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
    * Now do any other low level, or basic initialization here   
    */   
   return Success;
}

/** @} */
