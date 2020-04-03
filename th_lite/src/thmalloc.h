/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

/** @addtogroup SHFL
@{ */
/** @addtogroup thmalloc_h EEMBC Redirect for malloc.h, a subset of stdlib.h.
@{ */

/** File Sentinal */
#ifndef   THMALLOC_H
#define   THMALLOC_H

/** @note You may need to bring in size_t definition manually. */

#ifdef __cplusplus
extern "C" {
#endif

/** Don't redirect unless specified explicitly. */
#if 	!defined(EE_REDIRECT)
#define	EE_REDIRECT	0
#endif

/* Memory Management, must have size_t defined. */

#define th_malloc( size ) th_malloc_x( size, __FILE__, __LINE__ )
void *th_malloc_x( size_t size, const char *file, int line );
#define th_calloc( nmemb, size ) th_calloc_x( nmemb, size, __FILE__, __LINE__ )
void *th_calloc_x( size_t nmemb, size_t size, const char *file, int line );
#define th_realloc( blk, size ) th_realloc_x( blk, size, __FILE__, __LINE__ )
void *th_realloc_x( void *blk, size_t size, const char *file, int line );
#define th_free( blk ) th_free_x( blk, __FILE__, __LINE__ )
void    th_free_x( void *blk, const char *file, int line );
void    th_heap_reset( void );

#if		defined(EE_REDIRECT) && EE_REDIRECT
#define	malloc(x)   	th_malloc(x)
#define	calloc(x,y) 	th_calloc(x,y)
#define realloc(x,y)	th_realloc(x,y)
#define free(x)			th_free(x)
/** @warning strdup re-direction conflicts with string.h, and stdlib.h. 
             See thstring.h for strdup.
*/
#endif /* EE_REDIRECT */

#ifdef __cplusplus
}
#endif
#endif /* File Sentinel */ 
/** @} */
/** @} */
