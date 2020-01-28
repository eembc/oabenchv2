/*==============================================================================
 *$RCSfile: bmark.c,v $
 *
 *   DESC : This file contains the Test Main and other TH support functions
 *
 * AUTHOR : Rick Foos, ECL, LLC
 *
 *  EEMBC : Office Automation Subcommittee 
 *
 *    CVS : $Revision: 1.4 $
 *          $Date: 2005/04/27 20:37:58 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/office/ditherv2/bmark.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: bmark.c,v $
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

/***************************************************************************

FILE DESCRIPTION
    Change a grayscale, 8bpp image to a binary image, using a
    Floyd-Steinberg Error Diffusion dithering algorithm

REFERENCES:
    Robert Ulichney (1987); "Digital Halftoning",
        The MIT Press, Cambridge, Massachusetts; pp. 239-242
***************************************************************************/

/*********************************************************************
    Includes
**********************************************************************/

#include "algo.h"

/* ======================================================================= */
/*         F U N C T I O N   P R O T O T Y P E S                           */
/* ======================================================================= */
int	t_run_test( LoopCount iterations, int argc, const char* argv[] );
int	test_main( struct TCDef **tcdef, int argc, const char **argv );

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
	ITERATIONS,         /*  recomended iterations */
	&t_run_test,
	&test_main,
	NULL,               /* no main function in this implimentation */
	NULL                /* no entry function in this implimentation */
};


/************************************************************************
    Data Buffers
************************************************************************/

/************************************************************************
    GLOBAL (ugh!) VARIABLES
************************************************************************/

e_u8 *                  g_inputImage;
n_int                   g_inputHeight;
n_int                   g_inputWidth;
e_u8 *                  g_outputImage;

#if BMDEBUG
static n_int            l_dorunrun;
#endif

/* ----- So, what happened??? */
static THTestResults    l_results;


/* ===================================================================== */
/*                                                                       */
/*         S T A R T   H E R E !                                         */
/*                                                                       */
/* ===================================================================== */

/*************************************************************************
FUNCTION NAME: test_main

DESCRIPTION:
    Test entry point - initialization

RETURN:
    int success/failure
**************************************************************************/

int test_main( struct TCDef **tcdef, int argc, const char **argv )
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
    LoopCount   loop_cnt = iterations;
    size_t		image_buf_size;
	n_int		g_outputWidth;

	init_files();   /* Create input and output RAM files */
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

    l_results.duration = th_signal_finished();
    l_results.iterations = iterations-(loop_cnt+1);
    l_results.v1 = g_inputHeight;
    l_results.v2 = g_inputWidth;
    l_results.v3 = IMAGE_BUFFSZ( g_inputHeight,g_inputWidth );
    l_results.v4 = 0;
    l_results.info = NULL;

#if NON_INTRUSIVE_CRC_CHECK || HOST_EXAMPLE_CODE
    /* ========================================================= */
    /* Run through loop once more, 16 bit CRC  calculated points */
    /* validation validation                                     */
    /* ========================================================= */

	ditherImage( g_inputImage, g_inputHeight,
                  g_inputWidth, g_outputImage );
#endif

#if NON_INTRUSIVE_CRC_CHECK
	l_results.CRC = 0;
	for (loop_cnt=0; loop_cnt < (LoopCount)IMAGE_BUFFSZ( g_inputHeight,g_inputWidth ); ++loop_cnt)
    {
		/* Read bytes to avoid ENDIAN problems */
		l_results.CRC = Calc_crc8( (e_u8)g_outputImage[loop_cnt], l_results.CRC );
    }
#elif	CRC_CHECK
	l_results.CRC = 0;
#else
	l_results.CRC = 0;
#endif

#if		HOST_EXAMPLE_CODE
	g_outputWidth = ((g_inputWidth-1)/CHAR_BITS+1);
	outputBinaryImage( g_outputImage, g_inputHeight, g_outputWidth );
#endif

    th_free( g_outputImage );
	th_free( g_inputImage );

    return th_report_results( &l_results, EXPECTED_CRC );
}

