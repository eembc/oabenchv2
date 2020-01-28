/**
 * @file
 * @brief  Test Harness Stub for Development Testing
 * 
 *$RCSfile: stubth.cpp,v $
 *
 * @author  Rick Foos, ECL, LLC
 *
 *  EEMBC : Technical Advisory Group (TechTAG)
 *
 *    CVS : $Revision: 1.2 $
 *          $Date: 2006/03/09 17:34:19 $
 *          $Author: rick $
 *          $Source: /usr/local/cvs/eembc2/th_lite/x86/al/stubth.cpp,v $
 *          
 * @note    For Development and Porting.  NOT part of normal build.  This
 *          file is used to allow developers to link the thlib library with a
 *          package that is not a benchmark.  This allows application porting to
 *          test TH library calls in the initial source code and build environment
 *          without requring a benchmark routine.
 *
 *          To use this build mode:
 *          -# rename the main routine in the target
 *          application, and define that name here in TH_BYPASS.
 *          -#  Add this routine as
 *          an OBJECT file outside the library in your build. 
 *          -# Link with a
 *          flag allowing multiple symbol definitions, The main routine will be defined in
 *          thlib.a, as well as in your application.
 *          
 *          Stubth will supply the
 *          test_main symbol required by thlib, and a main which will pass through
 *          to the entry point of the application.
 *          
 *          Header files, and prototype definitions are excluded on purpose so
 *          that Test Harness definitions like TCDef are not included here which
 *          could cause conflicts in other parts of a link external to the normal
 *          test harness link.
 *          
 *          @note tmain.c contains ONLY the test harness main routine.  This allows
 *          the TH Regular routines to link with a different main program, which
 *          bypasses the harness wrapper.  Useful for development and porting
 *          compatibility checks.  This is NOT used for final benchmarking and
 *          certification.
 *          
 *          @warning This file is NOT part of normal benchmark build.  Uses cpp
 *          file type so that depgen ignores this file when building dependencies.
 *
 *
 * HISTORY :
 *
 * $Log: stubth.cpp,v $
 * Revision 1.2  2006/03/09 17:34:19  rick
 * Version 2 Office Release Candidate 5
 *
 * Revision 1.4  2005/07/16 03:08:31  rick
 * Merge updates for DSP environments
 *
 * Revision 1.3  2005/04/27 20:33:21  rick
 * Copyrite update 2005
 *
 * Revision 1.2  2004/12/08 23:27:26  rick
 * New standard header for documentation generation.
 *
 * Revision 1.1  2004/03/15 21:29:22  rick
 * Add documentation tags, and cleanup comments
 *
 * Revision 1.3  2004/03/10 23:57:19  rick
 * fix dirent calls
 *
 * Revision 1.2  2004/02/05 23:03:30  rick
 * Harness update with portable dirent
 *
 * Revision 1.1  2004/02/02 19:58:35  rick
 * Add ability to link thlib with original applications
 *
 *
 * @verbatim
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
 *------------------------------------------------------------------------------
 * @endverbatim
 */

/** @addtogroup THLAL
@{ */
/** @addtogroup stubth_cpp TH Stub for Development Testing.
@{ */

/** Define this to const, or not depending on how argv is handled in
the target application.*/
#define STUBTH_CONST /* const */

/** Define application_main to the alternate main routine of the external
application. */
#define TH_BYPASS(argc,argv) application_main(argc,argv)

/* Prototypes, cpp file type requires extern C namespace. */
#ifdef __cplusplus
extern "C" {
#endif

int TH_BYPASS(int argc, STUBTH_CONST char *argv[]);
int main(int argc, STUBTH_CONST char *argv[]);
int test_main( char **tcdef, int argc, const char* argv[] );

/** Extract pointer to thal.c defined th_def. */
//extern void *the_thdef;
/** Extract pointer to thdef */
//extern void *thdef;
/** Unused definition of space for TCDef */
char the_tcdef[1024];

#ifdef __cplusplus
   }
#endif

/* Stub Routines */

/** Stub for autoconf build, allows test harness link. */
int    test_main( char **tcdef, int argc, const char* argv[] )
{
	return 0;
}

/** Stub for autoconf build. 

This is used to bypass the test harness for library linking. The
linker must use an option to allow multiple definitions of symbools. 
For example, in GCC use --allow-multiple-definition.
*/
int main(int argc, STUBTH_CONST char *argv[])
{
	/* allow th calls by stitching together. */
//	thdef = &the_thdef;
	return TH_BYPASS(argc,argv);
}

/** @} */
/** @} */
