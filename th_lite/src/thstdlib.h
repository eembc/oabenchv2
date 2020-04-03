/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

/** Malloc is a subset of stdlib.h, must have size_t defined to use this. */
#include "thmalloc.h"

/** @addtogroup SHFL
@{ */
/** @addtogroup thstdlib_h EEMBC Redirect for stdlib.h
@{ */

/** File Sentinal */
#ifndef   THSTDLIB_H
#define   THSTDLIB_H
#ifdef __cplusplus
extern "C" {
#endif

/** Don't redirect unless specified explicitly. */
#if 	!defined(EE_REDIRECT)
#define	EE_REDIRECT	0
#endif

void	th_exit( int exit_code, const char *fmt, ... );

/** Use TH_RAND_MAX instead of stdlib.h RAND_MAX.
Test Harness Random Numbers (Uniform Distribution [0-128].
*/
#define TH_RAND_MAX	128
/** Internal harness random number generator. */
int 	th_rand( void );
/** Seed internal harness random number generator. */
void	th_srand(unsigned int seed);

#if		EE_REDIRECT

#define  exit(x)	th_exit(x,"Failure: %s : %d\n",__FILE__,__LINE__)

#undef	RAND_MAX
#define RAND_MAX	TH_RAND_MAX
#define rand(x)		th_rand(x)
#define srand(x)	th_srand(x)

#endif

#ifdef __cplusplus
}
#endif
#endif /* File Sentinel */
/** @} */
/** @} */
