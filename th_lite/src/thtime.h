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
/** @addtogroup THTIME_H EEMBC Redirect for sys/time.h
@{ */

/** File Sentinal */
#ifndef   THTIME_H
#define   THTIME_H

/** Need ee_time_t */
#include "thtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Don't redirect unless specified explicitly. */
#if 	!defined(EE_REDIRECT)
#define	EE_REDIRECT	0
#endif

#ifndef EE_TM_DEFINED
struct ee_tm {
        int tm_sec;     /* seconds after the minute - [0,59] */
        int tm_min;     /* minutes after the hour - [0,59] */
        int tm_hour;    /* hours since midnight - [0,23] */
        int tm_mday;    /* day of the month - [1,31] */
        int tm_mon;     /* months since January - [0,11] */
        int tm_year;    /* years since 1900 */
        int tm_wday;    /* days since Sunday - [0,6] */
        int tm_yday;    /* days since January 1 - [0,365] */
        int tm_isdst;   /* daylight savings time flag */
        };

struct ee_timeval {
	long tv_sec;        /* seconds */
	long tv_usec;  /* microseconds */
};
/** @deprecated The tinezone struct is DEPRECATED. */
#define EE_TM_DEFINED
#endif

/** time  returns the time since the Epoch (00:00:00 UTC, January 1, 1970). */
ee_time_t al_time(ee_time_t *t);

/** The localtime() function converts the calendar time to  broken-time. */
struct ee_tm *al_localtime(const ee_time_t *t);

/** Returns the Epoch time in Seconds and Milliseconds. */
int al_gettimeofday(struct ee_timeval *tp, void *tzp);


#if		EE_REDIRECT

#define	time_t	ee_time_t
#define time(x)	al_time(x)
/** maybe a typedef, but those can be problems as well. */
#define tm		ee_tm
#define localtime(x)		al_localtime(x)
#define timeval		ee_timeval
#define gettimeofday(x,y)	al_gettimeofday(x,y)

#endif

#ifdef __cplusplus
}
#endif
#endif /* File Sentinel */
/** @} */
/** @} */
