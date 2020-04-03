/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#ifndef   THFL_H        /* File Sentinal */
#define   THFL_H

#include "thcfg.h"
#include "thstdint.h"
#include "thtime.h"

/** @addtogroup THLFL
@{ */
/** @addtogroup thfl_h Functional layer internal prototypes
@{ */

#ifdef __cplusplus
extern "C" {
#endif

void	*i_malloc( size_t size, const char *fn, int line );
void	*i_calloc( size_t nmemb, size_t size, const char *fn, int line );
void	*i_realloc( void *block, size_t size, const char *fn, int line );
char	*i_strdup( const char *string, const char *fn, int line );
void	i_free( void *block, const char *fn, int line );
void	i_heap_reset( void );

e_u16	t_crcbuffer(const void *inbuf,size_t size,e_u16 inputCRC);

int		t_rand( void );
void	t_srand(unsigned int seed);
void	t_exit( int exit_code, const char *fmt, ... );

char *efn( const char *fn );
char *epn( const char *fn );

/* Time Routines. */

ee_time_t ee_time(ee_time_t *t);
struct ee_tm *ee_localtime(const ee_time_t *t);
int ee_gettimeofday(struct ee_timeval *tp, void *tzp);

#define SOURCE_FILE efn( __FILE__ )

#ifdef __cplusplus
   }
#endif
#endif                /* File Sentinal */
/** @} */
/** @} */
