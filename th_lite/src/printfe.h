/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#ifndef   PRINTFE_H
#define   PRINTFE_H

#include "thcfg.h"
#if		HAVE_STDARG_H
#include <stdarg.h>
#endif

/** @addtogroup SHFL
@{ */
/** @addtogroup printfe_c Functional Layer Printf Engine
@{ */

/** Compile out if not being used. */
#if USE_TH_PRINTF

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*sender) ( char c, void *ptr );

int printfe( sender sf, void *ptr, const char *fmt, va_list args );

int sprintf( char *s, const char *fmt, ... );
int vsprintf( char *s, const char *fmt, va_list args );
int thpf_sender( char c, void *ptr );

#ifdef __cplusplus
   }
#endif
#endif /* USE_TH_PRINTF */
#endif /* file sentinal */
/** @} */
/** @} */
