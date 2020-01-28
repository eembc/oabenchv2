/* Copyright (C) 2001-2006 artofcode LLC.
   All Rights Reserved.
  
   This software is provided AS-IS with no warranty, either express or
   implied.

   This software is distributed under license and may not be copied, modified
   or distributed except as expressly authorized under the terms of that
   license.  Refer to licensing information at http://www.artifex.com/
   or contact Artifex Software, Inc.,  7 Mt. Lassen Drive - Suite A-134,
   San Rafael, CA  94903, U.S.A., +1(415)492-9861, for further information.
*/

/* $Id: gs.c 6697 2006-04-01 22:16:27Z alexcher $ */
/* 'main' program for Ghostscript */
#include "ghost.h"
#include "imain.h"
#include "imainarg.h"
#include "iapi.h"
#include "iminst.h"
#include "ierrors.h"
#include "gsmalloc.h"
/** ECL
#define fprintf th_fprintf
#define fflush th_fflush
 */

#ifdef __GNUC__
#  if (__GNUC__ == 2 && __GNUC_MINOR__ == 96)
#    define NEED_COMMIT_STACK 1
#  endif
#endif


/* Define an optional array of strings for testing. */
/*#define RUN_STRINGS */
#ifdef RUN_STRINGS
private const char *run_strings[] =
{
    "2 vmreclaim /SAVE save def 2 vmreclaim",
    "(saved\n) print flush",
    "SAVE restore (restored\n) print flush 2 vmreclaim",
    "(done\n) print flush quit",
    0
};

#endif

#ifdef NEED_COMMIT_STACK
/* 
 * It is well known that GCC 2.96 for x86 sometimes forgets to adjust $esp
 * and leaves automatic variables at small distance below the stack pointer.
 * Apparently, when the access to the automatic variable causes a page fault
 * Linux sends a SEGV signal if the access happens below the stack pointer.
 * Pre-loading the stack pages resolves the problem.
 */
private void 
commit_stack_pages( void )
{
    int exit_status = 0;
    gs_main_instance *minst = gs_main_instance_default();
    int code = gs_main_init_with_args(minst, argc, argv);
    char buf[65536]; /* In most cases GS lives in 64K stack */
    int i;
    for ( i = 0; i < sizeof(buf) - 1; i += 1024)
        buf[i] = 0;
}
#endif


/** ECL */
int gs_main(int argc, char *argv[], int *exit_code_ee);
int gs_main(int argc, char *argv[], int *exit_code_ee)
{
    int exit_status, code;
    gs_main_instance *minst;

#ifdef NEED_COMMIT_STACK   /* hack for bug in gcc 2.96 */
    commit_stack_pages();
#endif
    exit_status = 0;
    minst = gs_main_alloc_instance(gs_malloc_init(NULL));
    code = gs_main_init_with_args(minst, argc, argv);
    
#ifdef RUN_STRINGS
    {				/* Run a list of strings (for testing). */
	const char **pstr = run_strings;

	for (; *pstr; ++pstr) {
	    int exit_code;
	    ref error_object;
	    int code;

	    fprintf(stdout, "{%s} =>\n", *pstr);
	    fflush(stdout);
	    code = gs_main_run_string(minst, *pstr, 0,
				      &exit_code, &error_object);
	    zflush(osp);
	    fprintf(stdout, " => code = %d\n", code);
	    fflush(stdout);
	    if (code < 0) {
		gs_to_exit(1);
		return 1;
	    }
	}
    }
#endif

    if (code >= 0)
	code = gs_main_run_start(minst);

    exit_status = 0;
    switch (code) {
	case 0:
	case e_Info:
	case e_Quit:
	    break;
	case e_Fatal:
	    exit_status = 1;
	    break;
	default:
	    exit_status = 255;
    }

    gs_to_exit_with_code(minst->heap, exit_status, code);

    switch (exit_status) {
	case 0:
	    exit_status =  exit_OK;
	    break;
	case 1:
	    exit_status =  exit_FAILED;
	    break;
    }
	*exit_code_ee=code;
    return exit_status;
}
