/*==============================================================================
 *$RCSfile: bmark_lite.c,v $
 *
 *   DESC : TH_Lite main routines for benchmark
 *
 *  EEMBC : Office Automation
 *
 * AUTHOR : Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.5 $
 *          $Date: 2005/11/02 18:14:06 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/office/textv2/bmark_lite.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: bmark_lite.c,v $
 * Revision 1.5  2005/11/02 18:14:06  rick
 * Bug #nonum: compiled with -DBMDEBUG
 *
 * Revision 1.4  2005/04/27 20:38:12  rick
 * Copyrite update 2005
 *
 * Revision 1.3  2004/09/08 05:19:10  rick
 * Add additional office datasets to complete makefile build
 *
 * Revision 1.2  2004/07/01 18:14:19  rick
 * Checkpoint after CRC4 for testing
 *
 * Revision 1.1  2004/05/03 22:27:59  rick
 * Add text, bezier, rotate base for v2
 *
 * Revision 1.19  2004/01/22 20:21:35  rick
 * Copyright update and cleanup
 *
 * Revision 1.18  2003/05/19 22:02:17  rick
 * Add al_hardware_reset to harness
 *
 * Revision 1.17  2002/08/09 17:47:18  rick
 * Add NI CRC to th regular benchmarks
 *
 * Revision 1.16  2002/07/31 22:42:26  rick
 * Fix Results iterations to report actual iterations
 *
 * Revision 1.15  2002/07/24 15:57:43  rick
 * Unique keys for all benchmarks, and generate tab delimited log files with column headers.
 *
 * Revision 1.14  2002/07/10 19:02:55  rick
 * Always initialize tcdef->CRC
 *
 * Revision 1.13  2002/05/29 22:26:41  rick
 * Set recommended iterations with make
 *
 * Revision 1.12  2002/05/10 17:20:39  rick
 * Add al_main to API
 *
 * Revision 1.11  2002/04/09 21:27:21  rick
 * Set ITERATIONS to 1000 to fix Reg/Lite differences
 *
 * Revision 1.10  2002/04/09 20:20:44  rick
 * Support 98/ME in checkout.bat
 *
 * Revision 1.9  2002/03/11 22:11:50  rick
 * ITERATIONS, CRC_CHECK, NON_INTRUSIVE TCDef Usage
 *
 * Revision 1.8  2002/03/08 00:30:39  administrator
 * Fix Endian definition, vprintf, and rotate endian crc's
 *
 * Revision 1.7  2002/02/27 00:22:13  rick
 * Add HAVE_MALLOC_H, al_printf to harness.
 *
 * Revision 1.6  2002/02/21 19:52:12  administrator
 * Build TH_Lite makefile for cygwin
 *
 * Revision 1.5  2002/02/19 20:12:09  rick
 * Add long copyright message per Alan.
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

/* ======================================================================== */
/*         F U N C T I O N   P R O T O T Y P E S                            */
/* ======================================================================== */
int main(int argc, const char* argv[] );
int t_run_test(TCDef *tcdef, int argc, const char* argv[]);

/* ====================================================================== */
/*                 Test Definition Structure */
/* ====================================================================== */
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
	/* Target Hardware Version Number (make all zeros to ignore) */
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

/*********************************************************************
    GLOBAL VARIABLES
**********************************************************************/

extern n_char   l_expLetter;
extern int		nodecnt;
#if		BMDEBUG
extern n_int    l_inputIterator;
extern const char	**g_inputLine;
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
	/*  pointer to parse tree root */
	Node *		ptree;
	size_t		total_size;
	/* --------------- Test Harness specific variables */
	int    l_rule_count = 0;       /*  number of lines to parse */
	char * l_rule;                 /*  pointer to text "rule" table */
#if BMDEBUG
	int            l_dorunrun,iterations;
#endif

 	init_files();
	check_data_params(argc,argv);
	load_rules();
	initFreeNodes();
	initOperatorTree();
	initCharacterTypes();

	/* ======================================================= */
	/*         start up main loop                              */
	/* ======================================================= */

	th_signal_start();

#if BMDEBUG
    iterations = 0;
    l_dorunrun = True;
    while( l_dorunrun && loop_cnt-- )  /*  allow stop if compiled for debug */
#else
    while(             loop_cnt-- )  /*  no stopping! */
#endif
    {
        while (input() != NULL)
        {
            initVariables();
            ptree = parseRule();
            release(ptree);            /*  free memory allocated in parser */
#if		BMDEBUG
			if (nodecnt)
			{
				th_printf("Failure: Invalid parse tree data\nUnreleased nodes: %d\nLine %d : %s\n",
					nodecnt,l_inputIterator,g_inputLine[l_inputIterator-1]);
				th_exit(THE_FAILURE,"Data file error, aborted run.\n");
			}
#endif
        }
        resetInput();

#if BMDEBUG
        iterations++;
        if ( !th_harness_poll() ) { break; }
#endif
    }

	tcdef->duration		= th_signal_finished() ;
    tcdef->iterations	= tcdef->rec_iterations-(loop_cnt+1);

    /* ======================================================= */
    /*         One more time to print validation data          */
    /* ======================================================= */

#if NON_INTRUSIVE_CRC_CHECK
	tcdef->CRC = 0;
    total_size = 0;
    while ((l_rule = input()) != NULL)
    {
        total_size += strlen(l_rule);

        initVariables();

        ptree = parseRule();
        if (ptree != (Node *)NULL)
        {
            l_expLetter = 'A';
            CRCNodes(ptree,&tcdef->CRC);
            release(ptree);            /*  free memory allocated in parser */
        }
        ++l_rule_count;
    }
    resetInput();

#elif	CRC_CHECK
	tcdef->CRC = 0;
    total_size = 0;
#else
	tcdef->CRC = 0;
    total_size = 0;
    while ((l_rule = input()) != NULL)
    {
        total_size += strlen(l_rule);

        initVariables();

        ptree = parseRule();
        if (ptree != (Node *)NULL)
        {
#ifdef PRINTOUTTEXT
            /*  -------- print truth table header -------- */
            th_printf("----------------\n" );
            th_printf( "rule: %s\n", l_rule );
#endif /*  PRINTOUTTEXT */
            l_expLetter = 'A';
            printNodes(ptree);
            release(ptree);            /*  free memory allocated in parser */
        }
        ++l_rule_count;
    }
    resetInput();
#endif

    tcdef->v1 = l_rule_count;
    tcdef->v2 = total_size;
    tcdef->v3 = nodecnt;
    tcdef->v4 = 0;

	/* check for release errors, and fail. */
	if (nodecnt)
		th_printf("Failure: Invalid parse tree data: %d\n",nodecnt);

	free_rules();

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
