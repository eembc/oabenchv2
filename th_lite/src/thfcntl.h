/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#ifndef THFCNTL_H
#define THFCNTL_H

/** See if we have fcntl.h. */
#include "thconfig.h"

/** @addtogroup SHFL
@{ */
/** @addtogroup thfcntl_h EEMBC Redirect for fcntl.h
@{ */

#ifdef __cplusplus
extern "C" {
#endif

/** Don't redirect unless specified explicitly. */
#if 	!defined(EE_REDIRECT)
#define	EE_REDIRECT	0
#endif

int 	 th_open	(const char *pathname, int flags);

#if 	!HAVE_FCNTL_H
/*
 * Flag values for open(2) and fcntl(2)
 * The kernel adds 1 to the open modes to turn it into some
 * combination of FREAD and FWRITE.
 */
#define O_RDONLY    0       /* +1 == FREAD */
#define O_WRONLY    1       /* +1 == FWRITE */
#define O_RDWR      2       /* +1 == FREAD|FWRITE */
#define O_APPEND    3
#define O_CREAT     4
#define O_TRUNC     5
#define O_EXCL      6
#endif

#if 	EE_REDIRECT
#define open(x,y,z)  		th_open(x,y)
#define creat(x,y)		th_open(x,0)
#endif

#ifdef __cplusplus
}
#endif
#endif /* file sentinel */
/** @} */
/** @} */
