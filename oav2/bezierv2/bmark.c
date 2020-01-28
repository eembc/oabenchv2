/*==============================================================================
 *$RCSfile: bmark.c,v $
 *
 *   DESC : This file contains the Test Main and other TH support functions
 *
 * AUTHOR : Rick Foos, ECL, LLC
 *
 *  EEMBC : Office Automation Subcommittee 
 *
 *    CVS : $Revision: 1.6 $
 *          $Date: 2005/04/27 20:37:51 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/office/bezierv2/bmark.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: bmark.c,v $
 * Revision 1.6  2005/04/27 20:37:51  rick
 * Copyrite update 2005
 *
 * Revision 1.5  2004/09/20 16:50:35  rick
 * Add strongoptimization save to results V4
 *
 * Revision 1.4  2004/09/08 21:03:14  rick
 * Modify CRC algorithms for toolchain differences
 *
 * Revision 1.3  2004/09/08 05:18:53  rick
 * Add additional office datasets to complete makefile build
 *
 * Revision 1.2  2004/07/01 18:13:49  rick
 * Checkpoint after CRC4 for testing
 *
 * Revision 1.1  2004/05/03 22:27:46  rick
 * Add text, bezier, rotate base for v2
 *
 * Revision 1.14  2002/08/16 19:13:20  rick
 * Add Float NICRC in Big Endian
 *
 * Revision 1.13  2002/08/16 19:10:29  rick
 * Add Float NICRC in Big Endian
 *
 * Revision 1.12  2002/08/12 22:12:31  rick
 * INCRC regression fixes
 *
 * Revision 1.11  2002/08/12 19:24:11  rick
 * Rename cygwin toolchain to gcc
 *
 * Revision 1.10  2002/08/09 17:47:06  rick
 * Add NI CRC to th regular benchmarks
 *
 * Revision 1.9  2002/07/31 22:42:20  rick
 * Fix Results iterations to report actual iterations
 *
 * Revision 1.8  2002/07/22 21:56:54  rick
 * Add Bezier float to automated run
 *
 * Revision 1.7  2002/07/10 19:02:42  rick
 * Always initialize results.CRC
 *
 * Revision 1.6  2002/05/29 22:26:21  rick
 * Set recommended iterations with make
 *
 * Revision 1.5  2002/04/19 19:56:33  rick
 * Bug 137: Compiler Optimization Problem
 *
 * Revision 1.4  2002/04/09 21:27:20  rick
 * Set ITERATIONS to 1000 to fix Reg/Lite differences
 *
 * Revision 1.3  2002/03/11 22:11:50  rick
 * ITERATIONS, CRC_CHECK, NON_INTRUSIVE TCDef Usage
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
    Run the calculations to interpolate a set of points defined by
    the four points of a Bezier curve.

    The curve is defined by two endpoints and two control points.
    The points are in 2D space, and are defined using floating point
    (double precision) variables.

    The actual formula was pulled from a web page created by Paul Thomson:
    http://www.dcs.ed.ac.uk/~pat/dfi/effect_pics/bezier_line.html

    The algorithm makes use of configuration constants in the header
    file "bez.h".  This includes the number of points to interpolate
    for each curve as well as the overall loop count.

    If the points are to be read in from a data file (as opposed to
    being compiled in), then the main function makes use of a call
    to the test harness malloc to create an array of Curve structures.
    This allows for different sizes of input files when the data
    points are read from file.  The first line in the file is the
    number of points following in the rest of the file

***************************************************************************/

/**************************************************************************
    Includes
***************************************************************************/

#include "algo.h"
#if		USE_FPU
#include <math.h>
#endif

/***************************************************************************
    Defines
***************************************************************************/

/* ====================================================================== */
/*                 F U N C T I O N   P R O T O T Y P E S                  */
/* ====================================================================== */
int t_run_test( LoopCount iterations, int argc, const char* argv[] );
n_int   test_main( struct TCDef** tcdef, int argc, const char* argv[] );

/*
 *       Test Definition Structure
 */

static TCDef the_tcdef =
{
	BM_ID,
	EEMBC_MEMBER_COMPANY,
	EEMBC_PROCESSOR,
	EEMBC_TARGET,
	BM_DESCRIPTION,
	TCDEF_REVISION,
	NULL,               /* pointer to the next TCDef */
	/* TH Version Number Required */
	{ EEMBC_TH_MAJOR, EEMBC_TH_MINOR, EEMBC_TH_STEP, EEMBC_TH_REVISION },
	/* Target Hardware Version Number Required (make all zeros to ignore)*/
	{ 0, 0, 0, 0 },
	/* The Version number of this Benchmark */
	BM_VERSION,
    ITERATIONS,
    &t_run_test,
    &test_main,
    NULL,               /* no main funciton in this implementation */
    NULL                /* no entry function in this implementation */
};

/*
 * Local Data
 */


/****************************************************************************
    GLOBAL VARIABLES
****************************************************************************/

extern	volatile Scalar	strongoptimization;

/* ======================================================================== */
/*                                                                          */
/*                  S T A R T   H E R E !                                   */
/*                                                                          */
/* ======================================================================== */

/*****************************************************************************
FUNCTION NAME: test_main

DESCRIPTION:
    Test entry point - initialization

RETURN:
    int success/failure
*****************************************************************************/

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

int t_run_test( LoopCount iterations, int argc, const char* argv[] )
{
	LoopCount		loop_cnt = iterations;
	THTestResults	results;

	Curve			*l_curve;		/*  Master list of Bezier definitions */
	n_int			l_curveCount;	/*  number of Bezier curves in array */
	Point			*test_points,*golden_points;
	n_int			test_idx;
	Scalar			dummy_sum=0,max_error;

	/* ======================================================= */
	/*         Where is the image coming from?                 */
	/* ======================================================= */

	init_files();
	l_curve = readDataPoints( &l_curveCount,&test_idx,&golden_points );
	test_points = (Point *)th_malloc(l_curveCount * sizeof(Point));

	th_signal_start();

	while(loop_cnt--)
	{
		/* create read dependency by reading a random value */
		interpolatePoints( l_curve, l_curveCount, test_points, test_idx);
		/* make sure that even a compiler that can track individual item arrays has to keep all items */
		dummy_sum+=test_points[test_idx].X + test_points[test_idx].Y;
#if BMDEBUG
        if ( !th_harness_poll() ) {break;}
#endif
    }

    results.duration = th_signal_finished();
    results.iterations   = iterations-(loop_cnt+1);
    results.v1           = l_curveCount;
    results.v2           = PARM_STEPS;
    results.v3           = FIXED_SHIFT;
	results.v4           = (e_u32)dummy_sum;
    results.info         = NULL;

#if		NON_INTRUSIVE_CRC_CHECK
	/* 32 bytes in a curve * number of curves */
	results.CRC = 0;
 #if USE_FPU
	max_error = 0.0;
	for (loop_cnt=0;loop_cnt<(LoopCount)l_curveCount;loop_cnt++)
	{
		/* SG: When floating point is used, allow an error of EPSILON 
		   to account for different IEEE standards. */
		if ((dummy_sum=fabs(test_points[loop_cnt].X - golden_points[loop_cnt].X)) 
					 > max_error ) {
			   max_error=dummy_sum;
		}
		if ((dummy_sum=fabs(test_points[loop_cnt].Y - golden_points[loop_cnt].Y)) 
					 > max_error ) {
			   max_error=dummy_sum;
		}
	}
	/* if max_error too big, fail the test */
	if (max_error > ERROR_EPSILON) {
		results.CRC = -1;
		th_printf(">> ERROR: Self test failed! Error of %f detected.\n",max_error); 
	}
	else /* otherwise pass */ {
		results.CRC = EXPECTED_CRC;
	}
 #else
	for (loop_cnt=0;loop_cnt<(LoopCount)l_curveCount;loop_cnt++)
	{
		results.CRC = Calc_crc32((e_u32)test_points[loop_cnt].X, results.CRC );
		results.CRC = Calc_crc32((e_u32)test_points[loop_cnt].Y, results.CRC );
	}
 #endif


#elif	CRC_CHECK
	results.CRC = 0;
#else
	results.CRC = 0;
#endif

	th_free(test_points);
	th_free(golden_points);

    return th_report_results( &results, expected_crc );
}

