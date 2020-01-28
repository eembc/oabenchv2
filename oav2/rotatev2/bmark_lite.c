/*==============================================================================
 *$RCSfile: bmark_lite.c,v $
 *
 *   DESC : TH_Lite main routines for benchmark
 *
 *  EEMBC : Office Automation
 *
 * AUTHOR : Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.7 $
 *          $Date: 2005/09/12 05:42:18 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/office/rotatev2/bmark_lite.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: bmark_lite.c,v $
 * Revision 1.7  2005/09/12 05:42:18  rick
 * Pre-release updates.
 *
 * Revision 1.6  2005/09/04 20:24:27  rick
 * Add reference files, and uuencode to rotate.
 *
 * Revision 1.5  2005/04/27 20:38:09  rick
 * Copyrite update 2005
 *
 * Revision 1.4  2004/09/08 05:19:05  rick
 * Add additional office datasets to complete makefile build
 *
 * Revision 1.3  2004/07/01 18:14:14  rick
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
#include "uuencode.h"
/* ======================================================================= */
/*         F U N C T I O N   P R O T O T Y P E S                           */
/* ======================================================================= */

int t_run_test(TCDef *tcdef, int argc, const char* argv[]);
int main(int argc,const char *argv[]);

/* ======================================================================= */
/*         Test Definition Structure                                       */
/* ======================================================================= */

TCDef the_tcdef = 
{
	BM_ID,
	EEMBC_MEMBER_COMPANY,
	EEMBC_PROCESSOR,
	EEMBC_TARGET,
	BM_DESCRIPTION,
	TCDEF_REVISION,
	/* TH Version Number Required */
	{ EEMBC_TH_MAJOR, EEMBC_TH_MINOR, EEMBC_TH_STEP, EEMBC_TH_REVISION },
	/* Target Hardware Version Number Required (make all zeros to ignore)*/
	{ 0, 0, 0, 0 },
	/* The Version number of this Benchmark */
	BM_VERSION,
	ITERATIONS,
	0,
	0,
	0,
	0,
	0,
	0,
	0
} ; 

/************************************************************************
    GLOBAL (ugh!) VARIABLES
************************************************************************/
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

/* ===================================================================== */
/*                                                                       */
/*         S T A R T   H E R E !                                         */
/*                                                                       */
/* ===================================================================== */

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

	/* target specific termination */
	al_hardware_reset(0);

	return rv;
} 

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
	LoopCount	iterations = tcdef->rec_iterations;

#if BMDEBUG
	int 		l_dorunrun;
#endif
	int 		do_uuencode,i;
	size_t  	image_size;
	e_u8		*g_outputImage = NULL;
	e_u8		*g_inputImage;
	int			g_inputHeight;
	int			g_inputWidth,bitWidth;
	char *outname;

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
		}
	}

    /* ======================================================= */
    /*     Where is the image coming from?                     */
    /* ======================================================= */

	init_files();
	check_data_params(argc,argv);
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
    g_outputImage = th_calloc(1,image_size);
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

    tcdef->duration = th_signal_finished();
    tcdef->iterations = iterations-(loop_cnt+1);
    tcdef->v1 = g_inputHeight;
    tcdef->v2 = g_inputWidth;
    tcdef->v3 = IMAGE_BUFFSZ( g_inputHeight,g_inputWidth );
    tcdef->v4 = BITS;

#if NON_INTRUSIVE_CRC_CHECK
	tcdef->CRC = th_crcbuffer(g_outputImage,(size_t)g_inputHeight*bitWidth/CHAR_BITS,0);
#elif	CRC_CHECK
	tcdef->CRC = 0;
#else
	tcdef->CRC = 0;
#endif

	/* Output image is padded with 0's */
	outname=extendFilename();
    outputBinaryImage( g_outputImage,g_inputWidth,g_inputHeight,outname);

	/* send the output image buffer back to the host */
	if (do_uuencode)
	{
		if (uu_send_file(outname))
			th_exit(THE_FAILURE,"Failure: Output file: %s not readable\n",outname);
	}
	th_free(outname);
    th_free( g_outputImage );
    th_free( g_inputImage );

	return	th_report_results(tcdef,expected_crc);
}
