/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

/** File Sentinel. */
#if   !defined(THASSERT_H)
#define THASSERT_H

/** Get HAVE_ASSERT_H */
#include	"thconfig.h"

/** If the tool chain has assert.h, use it instead of these routines. */
#if		HAVE_ASSERT_H
#include	<assert.h>
#endif

/** @addtogroup SHFL
@{ */
/** @addtogroup thassert_h Test Harness assert functions.
@{ */
#if		!HAVE_ASSERT_H
#ifdef __cplusplus
extern "C" {
#endif

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * assert functions coded to harness
*/

#ifndef NDEBUG
extern void __assertfail( const char *msg, const char *cond, const char *file, int line );

#define assert(p)   ((p) ? ((void)0) : \
                     __assertfail( "\n** ASSERT : %s, file %s, line %d\n", \
                     #p, __FILE__, __LINE__ ))
#else
#define assert(p) ((void)0)
#endif

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * fatal error  (just like assert, but always triggers)
*/

#ifndef NDEBUG
extern void __fatal( const char* msg, const char* file, int line );

#define fatal()     (__fatal( "\n** FATAL : file %s, line %d\n",  \
                        __FILE__, __LINE__ ) )
#else
#define fatal()   ((void)0)
#endif


#ifdef __cplusplus
}
#endif
#endif /* !HAVE_ASSERT_H */
#endif /* File sentinal */
/** @} */
/** @} */
