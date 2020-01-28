/*==============================================================================
 *$RCSfile: bmark_lite.c,v $
 *
 *   DESC : TH_Lite main routines for benchmark
 *
 *  EEMBC : Office Automation
 *
 * AUTHOR : ARM Ltd., Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.6 $
 *          $Date: 2005/04/27 20:37:51 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/office/bezierv2/bmark_lite.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: bmark_lite.c,v $
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
 * Revision 1.19  2003/05/19 22:02:10  rick
 * Add al_hardware_reset to harness
 *
 * Revision 1.18  2002/08/16 19:24:12  rick
 * Add Float NICRC in Big Endian
 *
 * Revision 1.17  2002/08/12 22:12:31  rick
 * INCRC regression fixes
 *
 * Revision 1.16  2002/08/12 19:24:11  rick
 * Rename cygwin toolchain to gcc
 *
 * Revision 1.15  2002/08/09 17:47:06  rick
 * Add NI CRC to th regular benchmarks
 *
 * Revision 1.14  2002/07/31 22:42:20  rick
 * Fix Results iterations to report actual iterations
 *
 * Revision 1.13  2002/07/22 21:56:54  rick
 * Add Bezier float to automated run
 *
 * Revision 1.12  2002/07/10 19:02:42  rick
 * Always initialize tcdef->CRC
 *
 * Revision 1.11  2002/05/29 22:26:21  rick
 * Set recommended iterations with make
 *
 * Revision 1.10  2002/05/10 17:20:39  rick
 * Add al_main to API
 *
 * Revision 1.9  2002/04/19 19:56:33  rick
 * Bug 137: Compiler Optimization Problem
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

/**************************************************************************
    Includes
***************************************************************************/

#include "algo.h"

#if	USE_FPU && NON_INTRUSIVE_CRC_CHECK
d_union	dunion;
#endif

#if		USE_FPU
#include <math.h>
#endif

/***************************************************************************
    Defines
***************************************************************************/

/* ====================================================================== */
/*                 F U N C T I O N   P R O T O T Y P E S                  */
/* ====================================================================== */
int t_run_test(struct TCDef *tcdef, int argc, const char* argv[]);
int main(int argc, const char* argv[] );

/*
 *       Test Definition Structure
 */

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
};

/*
 * Local Data
 */

/****************************************************************************
    GLOBAL VARIABLES
****************************************************************************/

extern	volatile Scalar	strongoptimization;

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

int t_run_test(struct TCDef *tcdef, int argc, const char* argv[]) 
{
	LoopCount	loop_cnt = tcdef->rec_iterations;
	Curve			*l_curve;		/*  Master list of Bezier definitions */
	n_int			l_curveCount;	/*  number of Bezier curves in array */
	Point			*test_points,*golden_points;
	n_int			test_idx,dummy_test=0;
	Scalar			dummy_sum=0;

    /* ======================================================= */
    /*         Where is the image coming from?                 */
    /* ======================================================= */

	init_files();
	check_data_params(argc,argv);
	l_curve = readDataPoints( &l_curveCount,&test_idx,&golden_points );
	test_points = (Point *)th_malloc(l_curveCount * sizeof(Point));
#if CREATE_DATASET
	loop_cnt=1;
#endif
    th_signal_start();

	while(loop_cnt--)
	{
		/* create read dependency by reading a random value */
		interpolatePoints( l_curve, l_curveCount, test_points, test_idx);
		/* make sure that even a compiler that can track individual item arrays */
		/* in individual invocations has to keep all interpolated points */
		for (dummy_test=0; dummy_test<l_curveCount; dummy_test++)
			dummy_sum+=test_points[dummy_test].X - test_points[dummy_test].Y;
#if BMDEBUG
        if ( !th_harness_poll() ) {break;}
#endif
    }

	tcdef->duration		= th_signal_finished() ;
    tcdef->iterations	= tcdef->rec_iterations-(loop_cnt+1); 
    tcdef->v1           = l_curveCount;
    tcdef->v2           = PARM_STEPS;
    tcdef->v3           = FIXED_SHIFT;
    tcdef->v4           = (e_u32)dummy_sum;

#if CREATE_DATASET
{
	FILE *f=fopen("c:\\tmp\\out.txt","wt");
	for (loop_cnt=0;loop_cnt<(LoopCount)l_curveCount;loop_cnt++)
	{
		fprintf(f,"%f,%f\n",test_points[loop_cnt].X,test_points[loop_cnt].Y);
	}		
	fclose(f);
}
#endif

#if		NON_INTRUSIVE_CRC_CHECK
	/* 32 bytes in a curve * number of curves */
	tcdef->CRC = 0;
 #if USE_FPU
	{
		double signal_x,signal_y,noise_x,noise_y,snr_x,snr_y,max_snr=-1e10,min_snr=1e10;
		double max_error = 0.0;
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
			/* and calculate SNR for X and Y */
			signal_x= golden_points[loop_cnt].X*golden_points[loop_cnt].X;
			signal_y= golden_points[loop_cnt].Y*golden_points[loop_cnt].Y;
			noise_x=test_points[loop_cnt].X - golden_points[loop_cnt].X; noise_x*=noise_x;
			noise_y=test_points[loop_cnt].Y - golden_points[loop_cnt].Y; noise_y*=noise_y;
			if (noise_x>0.0) {
				snr_x=10.0*log10(signal_x/noise_x);
				if (snr_x > max_snr)
					max_snr=snr_x;
				if (snr_x < min_snr)
					min_snr=snr_x;
			}
			if (noise_y>0.0) {
				snr_y=10.0*log10(signal_y/noise_y);
				if (snr_y > max_snr)
					max_snr=snr_y;
				if (snr_y < min_snr)
					min_snr=snr_y;
			}
		}
		/* if SNR lower then 50dB, fail the test */
		th_printf(">> SNR values: min=%f , max=%f .\n",min_snr,max_snr); 
		if (min_snr < 50)  {
			tcdef->CRC = -1;
			th_printf(">> ERROR: Self test failed! Error of %f detected.\n",max_error); 
		}
		else /* otherwise pass */ {
			tcdef->CRC = EXPECTED_CRC;
		}
	}
 #else
	for (loop_cnt=0;loop_cnt<(LoopCount)l_curveCount;loop_cnt++)
	{
		tcdef->CRC = Calc_crc32((e_u32)test_points[loop_cnt].X, tcdef->CRC );
		tcdef->CRC = Calc_crc32((e_u32)test_points[loop_cnt].Y, tcdef->CRC );
	}
 #endif

#elif	CRC_CHECK
	tcdef->CRC = 0;
#else
	tcdef->CRC = 0;
#endif

	th_free(test_points);
	th_free(golden_points);
	th_free(l_curve);
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

