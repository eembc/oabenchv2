/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
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
