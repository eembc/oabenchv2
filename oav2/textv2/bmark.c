/*==============================================================================
 *$RCSfile: bmark.c,v $
 *
 *   DESC : TH Regular main routines for benchmark
 *
 *  EEMBC : Office Automation
 *
 * AUTHOR : ECL, LLC
 *
 *    CVS : $Revision: 1.5 $
 *          $Date: 2005/04/27 20:38:12 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/office/textv2/bmark.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: bmark.c,v $
 * Revision 1.5  2005/04/27 20:38:12  rick
 * Copyrite update 2005
 *
 * Revision 1.4  2004/09/08 05:19:10  rick
 * Add additional office datasets to complete makefile build
 *
 * Revision 1.3  2004/09/03 22:32:02  rick
 * New Office Textv2 functions
 *
 * Revision 1.2  2004/07/01 18:14:19  rick
 * Checkpoint after CRC4 for testing
 *
 * Revision 1.1  2004/05/03 22:27:59  rick
 * Add text, bezier, rotate base for v2
 *
 * Revision 1.10  2004/01/22 20:21:35  rick
 * Copyright update and cleanup
 *
 * Revision 1.9  2002/08/09 17:47:18  rick
 * Add NI CRC to th regular benchmarks
 *
 * Revision 1.8  2002/07/31 22:42:26  rick
 * Fix Results iterations to report actual iterations
 *
 * Revision 1.7  2002/07/24 15:57:43  rick
 * Unique keys for all benchmarks, and generate tab delimited log files with column headers.
 *
 * Revision 1.6  2002/05/29 22:26:41  rick
 * Set recommended iterations with make
 *
 * Revision 1.5  2002/04/23 21:15:14  rick
 * Clear printouttext warnings
 *
 * Revision 1.4  2002/04/09 21:27:21  rick
 * Set ITERATIONS to 1000 to fix Reg/Lite differences
 *
 * Revision 1.3  2002/04/09 20:20:43  rick
 * Support 98/ME in checkout.bat
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
    Parse Boolean expressions

    For each line, break the expression into a binary tree structure,
    where each node contains a binary expression with two opperands
    (each with a possible unary operator) and a binary operator.  The
    operands may be variables, constants, or pointers to further nodes
    which themselves represent binary operations, etc...

    NOTE:  Use the BENCHMARK define to activate the main timed loop,
    controled by the test harness.    If this is NOT defined, then
    the program goes into an interactive mode where each "rule"
    (boolean expression) is entered by the user, parsed, and then
    printed out as a truth table

    If in debug mode (i.e., not in benchmark mode), then actually
    evaluate the expression for all possible values of the variable
    list.  This is done with a recursive function to set the
    variables, and then evaluate the expression stored in the binary
    tree.

      NOTE:  Not much error checking is done for valid expressions.  It
      should be hard to crash the program, but ill-formed expressions
      may give bogus results.
***************************************************************************/

#include "algo.h"

/* ======================================================================== */
/*         F U N C T I O N   P R O T O T Y P E S                            */
/* ======================================================================== */
int    t_run_test( LoopCount iterations, int argc, const char* argv[] );
int    test_main( struct TCDef** tcdef, int argc, const char* argv[] );


/* ======================================================================== */
/*         Test Definition Structure                                        */
/* ======================================================================== */

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
	/* Target Hardware Version Number (make all zeros to ignore) */
    { 0, 0, 0, 0 },
	/* The Version number of this Benchmark */
	BM_VERSION,
	ITERATIONS,
	&t_run_test,
	&test_main,
	NULL,           /* no main funciton in this implimentation */
	NULL            /* no entry function in this implimentation */
};

/*********************************************************************
    GLOBAL (ugh!) VARIABLES
**********************************************************************/

extern n_char   l_expLetter;
extern int		nodecnt;
#if		BMDEBUG
extern n_int    l_inputIterator;
extern const char	**g_inputLine;
#endif

/* ====================================================================== */
/*                                                                        */
/*             S T A R T   H E R E                                        */
/*                                                                        */
/* ====================================================================== */

/************************************************************
FUNCTION NAME: test_main

DESCRIPTION:
    Test entry point - initialization

RETURN:
    int success/failure
*************************************************************/

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

    MAIN LOOP:  loop through list of input lines, parsing each rule.
    After going through the main timed loop, go through once more
    to print validation output.

RETURN:
    Success of the test
**************************************************************/

int t_run_test( size_t iterations, int argc, const char *argv[] )
{
	LoopCount	loop_cnt = iterations;
	THTestResults   l_results;
	/*  pointer to parse tree root */
	Node *		ptree;
	size_t		total_size;
	/* --------------- Test Harness specific variables */
	int    l_rule_count = 0;       /*  number of lines to parse */
	char * l_rule;                 /*  pointer to text "rule" table */
#if BMDEBUG
	int            l_dorunrun;
#endif

	init_files();
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
        if ( !th_harness_poll() )
			break;
#endif
    }

    l_results.duration = th_signal_finished();
    l_results.iterations = iterations-(loop_cnt+1);

	/** Check for memory leak in release. */

    /* ======================================================= */
    /*         One more time to print validation data          */
    /* ======================================================= */

#if NON_INTRUSIVE_CRC_CHECK
	l_results.CRC = 0;
    total_size = 0;
    while ((l_rule = input()) != NULL)
    {
        total_size += strlen(l_rule);

        initVariables();

        ptree = parseRule();
        if (ptree != (Node *)NULL)
        {
            l_expLetter = 'A';
            CRCNodes(ptree,&l_results.CRC);
            release(ptree);            /*  free memory allocated in parser */
        }
        ++l_rule_count;
    }
    resetInput();

#elif	CRC_CHECK
	l_results.CRC = 0;
    total_size = 0;
#else
	l_results.CRC = 0;
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
	l_results.v1 = l_rule_count;
	l_results.v2 = total_size;
	l_results.v3 = nodecnt;
	l_results.v4 = 0;
	l_results.info = NULL;

	/* check for release errors, and fail. */
	if (nodecnt)
		th_printf("Failure: Invalid parse tree data: %d\n",nodecnt);

	return th_report_results( &l_results, EXPECTED_CRC );
}
