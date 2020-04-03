/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

/** File Sentinal */
#ifndef   THSTRING_H
#define   THSTRING_H

/** @addtogroup SHFL
@{ */
/** @addtogroup thstring_h EEMBC Redirect for string.h
@{ */

#ifdef __cplusplus
extern "C" {
#endif

/** Don't redirect unless specified explicitly. */
#if 	!defined(EE_REDIRECT)
#define	EE_REDIRECT	0
#endif

/* Memory Management from string.h */

/** Most compilers have strdup, but do not define it or define it in a variety of 
locations. This avoids extern returning int warnings in thal.c, but 
in some cases causes problems. Use HAVE_DECL_STRDUP flag to control things.
*/
#if		!HAVE_DECL_STRDUP
char	*strdup(const char *);
#endif

/** @note Re-direction may need to occur first to pick up th_strdup_x redirection. Redirection failure
will occur in link on symbol _th_strdup. */
#if		EE_REDIRECT
/** strdup re-direction can conflict between string.h, and stdlib.h */
#define	strdup(x)		th_strdup(x)
#endif

/** We use bcopy if available. */
#if		HAVE_BCOPY
#define	memcpy(dest,src,len)	bcopy(src,dest,len)
#endif

/** strdup defined with __FILE__ and __LINE__ for Harness out of memory reporting. */
char *th_strdup_x( const char *string, const char *file, int line );
/** Always redirect th_strdup to harness routine adding FILE and LINE. */
#define th_strdup( string ) th_strdup_x( string, __FILE__, __LINE__ )

#ifdef __cplusplus
}
#endif
#endif /* THSTRING_H */ 
/** @} */
/** @} */
