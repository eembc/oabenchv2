/*==============================================================================
 *$RCSfile: bmark_lite.c,v $
 *
 *   DESC : TH_Lite main routines for benchmark
 *
 * AUTHOR : ARM Ltd., Rick Foos, ECL, LLC
 *
 *  EEMBC : Office Automation
 *
 *    CVS : $Revision: 1.5 $
 *          $Date: 2005/11/02 18:27:08 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/office/ditherv2/bmark_lite.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: bmark_lite.c,v $
 * Revision 1.5  2005/11/02 18:27:08  rick
 * Bug #nonum: compiled with -DBMDEBUG iterations is undefined.
 *
 * Revision 1.4  2005/04/27 20:37:58  rick
 * Copyrite update 2005
 *
 * Revision 1.3  2004/02/02 19:57:06  rick
 * Clear Root directory problems
 *
 * Revision 1.2  2004/01/29 00:34:12  rick
 * Resolve header file cycles
 *
 * Revision 1.1  2004/01/23 00:29:39  rick
 * Initial dither V2
 *
 * Revision 1.15  2003/05/19 22:02:12  rick
 * Add al_hardware_reset to harness
 *
 * Revision 1.14  2002/08/09 17:47:13  rick
 * Add NI CRC to th regular benchmarks
 *
 * Revision 1.13  2002/07/31 22:42:22  rick
 * Fix Results iterations to report actual iterations
 *
 * Revision 1.12  2002/07/24 15:57:41  rick
 * Unique keys for all benchmarks, and generate tab delimited log files with column headers.
 *
 * Revision 1.11  2002/07/10 19:02:49  rick
 * Always initialize tcdef->CRC
 *
 * Revision 1.10  2002/05/29 22:26:38  rick
 * Set recommended iterations with make
 *
 * Revision 1.9  2002/05/10 17:09:52  rick
 * Rollback Floyd Stein Checksum
 *
 * Revision 1.8  2002/04/23 19:01:21  rick
 * Correct Floyd-Stein checksum
 *
 * Revision 1.7  2002/04/09 21:27:20  rick
 * Set ITERATIONS to 1000 to fix Reg/Lite differences
 *
 * Revision 1.6  2002/03/11 22:11:50  rick
 * ITERATIONS, CRC_CHECK, NON_INTRUSIVE TCDef Usage
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

/* ====================================================================== */
/*                 Test Definition Structure */
/* ====================================================================== */
int t_run_test(TCDef *tcdef, int argc, const char* argv[]);

TCDef the_tcdef = 
{
	BM_ID,
	EEMBC_MEMBER_COMPANY, 
	EEMBC_PROCESSOR, 
	EEMBC_TARGET, 
	BM_DESCRIPTION,
	TCDEF_REVISION, 
	{ EEMBC_TH_MAJOR, EEMBC_TH_MINOR, EEMBC_TH_STEP, EEMBC_TH_REVISION }, 
	{ 0, 0, 0, 0 },   /* Target Hardware Version Number Required( make all zeros to ignore )*/
	BM_VERSION, /* The Version number of this Benchmark */
	ITERATIONS,
	0,
	0,
	0,
	0,
	0,
	0,
	0
};

/*
 * Local Data
 */


/************************************************************************
    GLOBAL VARIABLES
************************************************************************/

e_u8 *                  g_inputImage;
n_int                   g_inputHeight;
n_int                   g_inputWidth;
e_u8 *                  g_outputImage;

#if BMDEBUG
static int            l_dorunrun,iterations;
#endif

void check_data_params(int argc, const char* argv[]) {
	int data_index;
	extern char *DATANAME;
	data_index=change_data(argc,argv,&DATANAME);
	if ((data_index>=0) && (data_index<NUM_DATAS)) {
		expected_crc=expected_crc_all[data_index];
		DATANAME=dataname_all[data_index];
		ee_uid=ee_uid_all[data_index];
	}
}

/* Benchmark MUST NOT depend on initialized global data. */

/*------------------------------------------------------------------------------
 * FUNC   : t_run_test
 *
 * DESC   : Called to run the test
 *
 *			This function is called to start the test.	It does not return
 *			until after the test is completed (finished).  Note, th_finished()
 *			and th_report_results() MUST be called before this function
 *			returns if results are to be report.  If these are not called
 *			then no results will be reported for the test.
 *		   
 * NOTE   : After this function returns, no other functions in the test
 *			will be called.  EG, returning from this function is equivelent
 *			to returning from a main() or calling th_exit()
 *
 * RETURNS: SUCCESS if the test ran fine.  If th_finished() and
 *			th_report_results() were not called, then the test finished
 *			successfully, but there were no results and the host will
 *			not be able to measure the test's duration.
 * ---------------------------------------------------------------------------*/

int t_run_test(TCDef *tcdef, int argc, const char* argv[])
{
    LoopCount	loop_cnt = tcdef->rec_iterations;
    size_t		image_buf_size;
#if		HOST_EXAMPLE_CODE
	n_int		g_outputWidth;
#endif

	init_files();   /* Create input and output RAM files */
	check_data_params(argc,argv);
    g_inputImage = readImage( &g_inputHeight, &g_inputWidth );

    /* ======================================================= */
    /*  All points have been read in - allocate output buffer  */
    /*     and start up main loop                              */
    /* ======================================================= */
#if BMDEBUG
    th_printf( "height: %4d (%3d)\n", g_inputHeight,
                    (g_inputHeight)/CHAR_BITS+1 );
    th_printf( "width:  %4d (%3d)\n", g_inputWidth,
                    (g_inputWidth)/CHAR_BITS+1 );
    th_printf( "allocated OUTPUT size: %d\n\n",
                    IMAGE_BUFFSZ( g_inputHeight, g_inputWidth) );
#endif

	image_buf_size = IMAGE_BUFFSZ(g_inputHeight,g_inputWidth); 
	g_outputImage = (e_u8*)th_malloc(image_buf_size);

    if ( g_outputImage == NULL)
    {
        th_exit( 1, "%s:%d - cannot allocate output image buffer!",
                __FILE__, __LINE__ );
    }

    th_signal_start();

#if BMDEBUG
    l_dorunrun = True;
    iterations = 0;
    while( l_dorunrun && loop_cnt-- )  /* allow stop if compiled for debug */
#else
    while(             loop_cnt-- )  /*  no stopping! */
#endif
    {
        ditherImage( g_inputImage, g_inputHeight, g_inputWidth,
                        g_outputImage );
#if BMDEBUG
        iterations++;
        if ( !th_harness_poll() ) { break; }
#endif
    }

	tcdef->duration		= th_signal_finished() ;
    tcdef->iterations	= tcdef->rec_iterations-(loop_cnt+1);
    tcdef->v1 = g_inputHeight;
    tcdef->v2 = g_inputWidth;
    tcdef->v3 = IMAGE_BUFFSZ( g_inputHeight,g_inputWidth );
    tcdef->v4 = 0;


#if NON_INTRUSIVE_CRC_CHECK || HOST_EXAMPLE_CODE
    /* ========================================================= */
    /* Run through loop once more, 16 bit CRC  calculated points */
    /* validation validation                                     */
    /* ========================================================= */

	ditherImage( g_inputImage, g_inputHeight,
                  g_inputWidth, g_outputImage );
#endif

#if NON_INTRUSIVE_CRC_CHECK
	tcdef->CRC = 0;
    for (loop_cnt=0; loop_cnt < (LoopCount)IMAGE_BUFFSZ( g_inputHeight,g_inputWidth ); ++loop_cnt)
    {
		/* Read bytes to avoid ENDIAN problems */
		tcdef->CRC = Calc_crc8( (e_u8)g_outputImage[loop_cnt], tcdef->CRC );
    }
#elif	CRC_CHECK
	tcdef->CRC = 0;
#else
	tcdef->CRC = 0;
#endif

#if		HOST_EXAMPLE_CODE
	g_outputWidth = ((g_inputWidth-1)/CHAR_BITS+1);
	outputBinaryImage( g_outputImage, g_inputHeight, g_outputWidth );
#endif

    th_free( g_outputImage );
	th_free( g_inputImage );

	return	th_report_results(tcdef,expected_crc);

}

/*------------------------------------------------------------------------------
 * FUNC   : test_main
 *
 * DESC   : The test (or bench mark) main entry point
 *
 * RETURNS: Any error value defined in th_error.h
 * ---------------------------------------------------------------------------*/

int main(int argc, const char* argv[] )
{
	int rv;
	/* target specific inititialization */
	al_main(argc, argv);

	/* Benchmark Execution */
	rv = t_run_test(&the_tcdef,argc,argv); 
	al_hardware_reset(0);
	return rv;
} 
