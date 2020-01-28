/*==============================================================================
 *$RCSfile: bmark.c,v $
 *
 *   DESC : TH_Lite Test Harness interface routines
 *
 *  EEMBC : Office Automation
 *
 * AUTHOR : Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.8 $
 *          $Date: 2005/09/12 05:42:18 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/office/rotatev2/bmark.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: bmark.c,v $
 * Revision 1.8  2005/09/12 05:42:18  rick
 * Pre-release updates.
 *
 * Revision 1.7  2005/09/04 20:24:26  rick
 * Add reference files, and uuencode to rotate.
 *
 * Revision 1.6  2005/04/27 20:38:08  rick
 * Copyrite update 2005
 *
 * Revision 1.5  2004/09/08 05:19:05  rick
 * Add additional office datasets to complete makefile build
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

/****************************************************************************

FILE DESCRIPTION
    Rotate a binary image of arbitrary size by 90 degrees.

    At this point, the algorithm makes use of a series of timer
    functions in the timer.c module.  This may change in the future
    as the EEMBC Test Harness API is solidified.

    If the image is to be read in from a data file (as opposed to
    being compiled in), then the main function makes use of a call
    to the test harness malloc to create a buffer of sufficient size
    to hold the image.  This allows for different sizes of input files
***************************************************************************/


/*********************************************************************
    Includes
**********************************************************************/
#include <math.h>
#include "algo.h"
int uu_send_file(const char *fn);

/* ======================================================================= */
/*         F U N C T I O N   P R O T O T Y P E S                           */
/* ======================================================================= */
int    t_run_test( LoopCount iterations, int argc, const char* argv[] );
int    test_main( struct TCDef** tcdef, int argc, const char* argv[] );

/* ======================================================================= */
/*         Test Definition Structure                                       */
/* ======================================================================= */

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
	NULL,        /* there is no main funciton in this implimentation */
	NULL         /* there is no entry function in this implimentation */
};

/*********************************************************************
    GLOBAL VARIABLES
**********************************************************************/

/* ===================================================================== */
/*                                                                       */
/*         S T A R T   H E R E !                                         */
/*                                                                       */
/* ===================================================================== */

/************************************************************
FUNCTION NAME: test_main

DESCRIPTION:
    Test entry point - initialization

RETURN:
    int success/failure
*************************************************************/

int test_main( struct TCDef **tcdef, int argc, const char *argv[] )
{
    /*  Point the test harness at our test defintion struction */

    *tcdef = &the_tcdef;

    return Success;
}



/************************************************************
FUNCTION NAME: t_run_test

DESCRIPTION:
    called to start the test

    This function is called to start the test.  It does not return
    until after the test is completed (finished).  Note, th_finished()
    and th_report_results() MUST be called before this function
    returns if results are to be report.  If these are not called
    then no results will be reported for the test.

RETURN:
    Success of the test
**************************************************************/

int t_run_test( LoopCount iterations, int argc, const char *argv[] )
{
	LoopCount		loop_cnt = iterations;
	THTestResults	results;

#if BMDEBUG
	int 		l_dorunrun;
#endif
	int 		do_uuencode,i;
	size_t  	image_size;
	e_u8		*g_outputImage = NULL;
	e_u8		*g_inputImage;
	int			g_inputHeight;
	int			g_inputWidth,bitWidth;

	/* Look for -do_uuencode */
#	if		defined(DO_UUENCODE)
	do_uuencode=1;
#	else
	do_uuencode=0;
#	endif
	for (i=1;i<argc;i++)
	{
		if ((strcmp(argv[i],"-do_uuencode")) == 0)
		{
			do_uuencode=1;
			/* Remove from any other command line processing. */
			strcpy((char *)argv[i],"");
		}
	}

    /* ======================================================= */
    /*     Where is the image coming from?                     */
    /* ======================================================= */

	init_files();
    g_inputImage = readImage( &g_inputHeight, &g_inputWidth );

    /* ======================================================= */
    /*  All points have been read in - allocate output buffer  */
    /*     and start up main loop                              */
    /* ======================================================= */
#if BMDEBUG
    th_printf("\nInput Image:\n");
    outputBinaryImage( g_inputImage, g_inputHeight, g_inputWidth,NULL );
    th_printf("height: %4d (%3d)\n", g_inputHeight,
                    (g_inputHeight)/CHAR_BITS+1);
    th_printf("width:  %4d (%3d)\n", g_inputWidth,
                    (g_inputWidth)/CHAR_BITS+1);
    th_printf("allocated OUTPUT size: %d\n\n",
                    IMAGE_BUFFSZ( g_inputWidth,g_inputHeight ));
#endif
    
    if (sizeof(UNIT)*CHAR_BITS != BITS)
        th_exit( 1, "%s:%d - word size does not equal BITS definition.",
                __FILE__, __LINE__ );


	bitWidth = IMAGE_BITWIDTH( g_inputWidth );
	image_size = IMAGE_BUFFSZ( bitWidth,g_inputHeight );
    g_outputImage = th_malloc(image_size);
    if ( g_outputImage == NULL)
        th_exit( 1, "%s:%d - cannot allocate output image buffer!",
                __FILE__, __LINE__ );
 
    th_signal_start();

#if BMDEBUG
    l_dorunrun = True;
    iterations = 0;
    while( l_dorunrun && loop_cnt-- )  /*  allow stop if compiled for debug */
#else
    while(             loop_cnt-- )  /*  no stopping! */
#endif
    {
        rotateImage( g_inputImage, g_inputHeight, bitWidth,
                        g_outputImage );

#if BMDEBUG
        iterations++;
        if ( !th_harness_poll() ) { break; }
#endif
    }

    results.duration = th_signal_finished();
    results.iterations = iterations-(loop_cnt+1);
    results.v1 = g_inputHeight;
    results.v2 = g_inputWidth;
    results.v3 = IMAGE_BUFFSZ( g_inputHeight,g_inputWidth );
    results.v4 = BITS;
    results.info = NULL;

#if NON_INTRUSIVE_CRC_CHECK
	results.CRC = th_crcbuffer(g_outputImage,(size_t)g_inputHeight*bitWidth/CHAR_BITS,0);
#elif	CRC_CHECK
	results.CRC = 0;
#else
	results.CRC = 0;
#endif
	/* Output image is padded with 0's */

    outputBinaryImage( g_outputImage,g_inputWidth,g_inputHeight,extendFilename());

	/* send the output image buffer back to the host */
	if (do_uuencode)
	{
		char *outname=extendFilename();
		if (uu_send_file(outname))
			th_exit(THE_FAILURE,"Failure: Output file: %s not readable\n",outname);
	}
    th_free( g_outputImage );
#if !BENCHMARK
    th_free( g_inputImage );
#endif

    return th_report_results( &results, EXPECTED_CRC );
}
