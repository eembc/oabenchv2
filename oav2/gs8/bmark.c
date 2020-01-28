/*==============================================================================
 *$RCSfile: bmark.c,v $
 *
 *   DESC : Test Harness regular benchmark routines
 *
 *  EEMBC : Office Automation
 *
 * AUTHOR : Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.12 $
 *          $Date: 2005/04/27 20:38:03 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/office/gs8/bmark.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: bmark.c,v $
 * Revision 1.12  2005/04/27 20:38:03  rick
 * Copyrite update 2005
 *
 * Revision 1.11  2004/11/10 23:19:12  rick
 * Add automated output generation
 *
 * Revision 1.10  2004/07/07 01:05:13  rick
 * Fix handling of null devices bbox and devicen
 *
 * Revision 1.9  2004/07/06 18:25:21  rick
 * Correct string.h include causing makerule warning
 *
 * Revision 1.8  2004/07/03 03:29:47  rick
 * Add thtime.h, and link/time harness interfaces.
 *
 * Revision 1.7  2004/07/02 17:56:11  rick
 * Add utilities for CRC, UUENCODE, and Ghostscript command line processing.
 *
 * Revision 1.6  2004/07/01 18:13:58  rick
 * Checkpoint after CRC4 for testing
 *
 * Revision 1.5  2004/02/12 23:36:00  rick
 * Add fputs, pdfwrite fix
 *
 * Revision 1.4  2004/02/11 22:12:42  rick
 * Add fputs to fix multiple drivers
 *
 * Revision 1.3  2004/02/04 01:05:50  rick
 * Add libresource, new cinit features
 *
 * Revision 1.2  2004/02/02 19:57:11  rick
 * Clear Root directory problems
 *
 * Revision 1.1  2004/01/22 20:21:11  rick
 * Copyright update and cleanup
 *
 * Revision 1.7  2002/05/29 22:25:49  rick
 * Set recommended iterations with make
 *
 * Revision 1.6  2002/04/23 14:45:07  rick
 * Bug 51: ifdef BMDEBUG always true
 *
 * Revision 1.5  2002/04/19 22:17:02  rick
 * Code cleanup for Linux build
 *
 * Revision 1.4  2002/03/22 22:57:54  rick
 * Change project files for lowercase, and techtag empty, th, and th_lite
 *
 * Revision 1.3  2002/03/11 22:11:49  rick
 * ITERATIONS, CRC_CHECK, NON_INTRUSIVE TCDef Usage
 *
 * Revision 1.2  2002/02/27 00:22:10  rick
 * Add HAVE_MALLOC_H, al_printf to harness.
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

#include "algo.h"

/*
 * Test Component Defintion Structure
 */
int    t_run_test( LoopCount iterations, int argc, const char* argv[] );
int    test_main( struct TCDef** tcdef, int argc, const char* argv[] );

TCDef the_tcdef = 
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
	ITERATIONS,    /* recomended iterations */
	&t_run_test, 
	&test_main,
	NULL,        /* there is no main funciton in this implementation */
	NULL         /* there is no entry function in this implementation */
};

/** 
 * Called to run the test
 *
 *          This function is called to start the test.  It does not return
 *          until after the test is completed (finished).  Note, th_finished()
 *          and th_report_results() MUST be called before this function
 *          returns if results are to be report.  If these are not called
 *          then no results will be reported for the test.
 *         
 * @NOTE    after this function returns, no other functions in the test
 *          will be called.  EG, returning from this function is equivelent
 *          to returning from a main() or calling th_exit()
 *
 * RETURNS: Success if the test ran fine.  If th_finished() and
 *          th_report_results() were not called, then the test finished
 *          successfully, but there were no results and the host will
 *          not be able to measure the test's duration.
 */
int t_run_test( LoopCount iterations, int argc, const char* argv[] )
{
	LoopCount		loop_cnt;
	THTestResults	results;
	int				temp_code=0;
	int				myargc=argc;
	char			**myargv=loadMyargv(argc,argv);
	int				do_uuencode=setDouuencode(&myargc,myargv);
	char			*outname=setOutname(&myargc,myargv);
	char			*device=setDevice(&myargc,myargv);
	char			*example=setExample(myargc,myargv);
	e_u16			expected_crc=getExpectedcrc(device,example);
	ee_FILE			*outfile=NULL;
	char			*outbuf=NULL;
	ee_fsize_t		outsize=0;
	
	/* Load RAM file system, if needed */
	init_filesystem();

    /* This is the actual benchmark */

	th_signal_start();   /* Tell the host that the test has begun */

	for ( loop_cnt = 0; ((loop_cnt < iterations) && !temp_code); loop_cnt++ )
	{
		temp_code = gs_main( argc, argv );
#if BMDEBUG
		if (!th_harness_poll())	break;
#endif
	}

	/* signal that we are finished */
	results.duration   = th_signal_finished();   
	results.iterations = loop_cnt;
	results.v1         = temp_code;
	results.v2         = 0;
	results.v3         = 0;
	results.v4         = 0;
	results.info       = NULL;

	/* Set error in log file */
	if (temp_code)
		th_printf("Failure: Ghostscript return code: %d\n",temp_code);

	/* some drivers (bbox, devicen) do not produce output files. */
	if ((outfile=th_fopen(outname,"rb"))==NULL)
	{
		/*if ((strcmp(device,"bbox"))!=0)
			th_printf("Failure: Output file: %s not found\n",outname);*/

		th_free(outname);
		outname=NULL;
	}
	else
	{
		/* 
		 * Load the output file into memory for CRC, 
		 * and uuencode.
		 */
		outsize=th_fsize(outname);
		outbuf=NULL;
		if (outsize)
		{
			outbuf=th_malloc(outsize);
			if ((th_fread(outbuf,outsize,1,outfile))!=1)
				th_exit(THE_FAILURE,"Failure: Output file: %s not readable\n",outname);
		}
	}

	/* send the output image buffer back to the host */
	if (do_uuencode && outname && outbuf && outsize)
		th_send_buf_as_file(outbuf, outsize, outname);

#if		NON_INTRUSIVE_CRC_CHECK
	results.CRC=expected_crc=th_crcbuffer(outbuf,outsize,0);
#elif	CRC_CHECK
	results.CRC=0;
#else
	results.CRC=0;
#endif

	if (outbuf)
		th_free(outbuf);
	freeMyargv(myargc,myargv);

	return th_report_results( &results, expected_crc );
}

/**
 * FUNC   : test_main
 *
 * DESC   : the test (or bench mark) main entry point
 *
 * RETURNS: Any error value defined in th_error.h
 */
int test_main( struct TCDef** tcdef, int argc, const char* argv[] )
{
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

