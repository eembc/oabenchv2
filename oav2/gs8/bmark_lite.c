/*==============================================================================
 *$RCSfile: bmark_lite.c,v $
 *
 *   DESC : TH Lite Test Harness routines for benchmarks
 *
 *  EEMBC : Office Automation
 *
 * AUTHOR : Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.10 $
 *          $Date: 2005/04/27 20:38:04 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/office/gs8/bmark_lite.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 * $Log: bmark_lite.c,v $
 * Revision 1.10  2005/04/27 20:38:04  rick
 * Copyrite update 2005
 *
 * Revision 1.9  2004/11/10 23:19:13  rick
 * Add automated output generation
 *
 * Revision 1.8  2004/07/07 01:05:13  rick
 * Fix handling of null devices bbox and devicen
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

/*******************************************************************************
    Includes                                                                    
*******************************************************************************/

#include "algo.h"

/*
 * Test Component Defintion Structure
 */
int t_run_test(struct TCDef *tcdef, int argc, const char* argv[]);
int main(int argc, const char* argv[] );

TCDef the_tcdef = 
{
	BM_ID,
	EEMBC_MEMBER_COMPANY, 
	EEMBC_PROCESSOR, 
	EEMBC_TARGET, 
	BM_DESCRIPTION,
	TCDEF_REVISION, 
	{ EEMBC_TH_MAJOR, EEMBC_TH_MINOR, EEMBC_TH_STEP, EEMBC_TH_REVISION },
	/* Target Hardware Version Number Required( make all zeros to ignore )*/
	{ 0, 0, 0, 0 },
	/* The Version number of this Benchmark */
	BM_VERSION,
	ITERATIONS,
	0,
	0,
	0,
	/* results */
	0,
	0,
	0,
	0
} ; 

/*
 * Local Declarations
 */
/* Print some dataset specific information */
print_dataset_info(const char *example,const char *device,const char *outname,int uid, char *devparam) {
	th_printf(">> Data   Name: %s\n",example);
	th_printf(">> Device Name: %s%s\n",device,devparam);
	th_printf(">> Output Name: %s\n",outname);
	if (uid>0)
		th_printf(">> UID: %d\n",uid);
}


/**
 * FUNC	: int t_run_test( struct TCDef *tcdef,int argc, const char *argv[] )
 * DESC  : This is the functions that carries out the algorithm. This function
 *         is called from the main.  Same algorithm is called three times. Input
 *         data for the algorithm is stored in 'algotst'c'.  All variables declared
 *         and initialized in 'init.c'.  When 'BMDEBUG' and 'HOST_EXAMPLE_CODE' 
 *         defined in 'thcfg.h' it will write bunch of debug message in the RAM.  
 *         All debug routines are in 'debug.c'. It calculates CRC using intermediate
 *         values from the algorithms.  CRC is used to check if algorithm carried out
 *         correctly.
 * ARGUMENT:	arc - command line arguments
 *				argv - parameters for gs8 calls
 *				tcdef - structure defined in 'thlib.h'.  Following members of tcdef
 *     			rec_iterations- recommend number of times algorithm should be carried out
 *   			iterations  - actual number of times algorithm was carried
 *                             most cases same as 'rec_iterations'
 *              duration	- Total time to carry out the algorithm
 *              CRC			- calculated CRC
 *
 * RETURNS : Success if the the CRC matches. 
 */
int t_run_test( struct TCDef *tcdef,int argc, const char *argv[] )
{    
	LoopCount		loop_cnt;

	int				temp_code=0;
	int				myargc=argc;
	char			**myargv=loadMyargv(&myargc,argv);
	int				do_uuencode=setDouuencode(&myargc,myargv);
	char			*outname=setOutname(&myargc,myargv);
	char			*device=setDevice(&myargc,myargv);
	char			*devparam=setDevParams(myargc,myargv);
	char			*example=setExample(myargc,myargv);
	int				uid=setUID(&myargc,myargv);
	e_u16			expected_crc=getExpectedcrc(device,example);
	ee_FILE			*outfile=NULL;
	char			*outbuf=NULL;
	ee_fsize_t		outsize=0;
	int exit_code;

	/* Load RAM file system, if needed */
	/*init_filesystem();*/
	print_dataset_info(example,device,outname,uid,devparam);

	/* This is the actual benchmark*/
    
	th_signal_start();   /* Tell the host that the test has begun*/

	for ( loop_cnt = 0; loop_cnt < (size_t) tcdef->rec_iterations; loop_cnt++ )   /* no stopping!*/
	{
		temp_code = gs_main( myargc, myargv, &exit_code );
#if BMDEBUG
		if ( !th_harness_poll() )	break;
#endif
   }

	tcdef->duration   = th_signal_finished() ;
	tcdef->iterations = loop_cnt ;
	tcdef->v1         = temp_code;
	tcdef->v2         = 0;
	tcdef->v3         = 0;
	tcdef->v4         = 0;

	/* Set error in log file */
	if (temp_code)
		th_printf("Failure: Ghostscript return code: %d [errcode=%d]\n",temp_code,exit_code);

	/* some drivers (bbox, devicen) do not produce output files. */
	if ((outfile=th_fopen(outname,"rb"))==NULL)
	{
		th_printf("ERROR: Output file: %s not found\n",outname);
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
	/** @todo If we use CRC, implement getExpectedcrc and remove override. */
 	tcdef->CRC=expected_crc=th_crcbuffer(outbuf,outsize,0);
#elif	CRC_CHECK
	tcdef->CRC=0;
#else
	tcdef->CRC=0;
#endif

	if (outbuf)
		th_free(outbuf);
	freeMyargv(myargc,myargv);
	th_free(device);
	th_free(outname);
	th_free(devparam);

	return	th_report_results(tcdef,expected_crc);
} 

/***************************************************************************/
int main(int argc, const char* argv[] )
{
	 /* target specific inititialization */
	al_main(argc, argv);
	/* Benchmark Execution */
	return	t_run_test(&the_tcdef,argc,argv); 
} 

