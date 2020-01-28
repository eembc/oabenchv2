/**
 * @file
 * @brief  EEMBC Redirect for sys/time.h
 *
 * $RCSfile: thtime.h,v $
 *
 *  EEMBC : EEMBC Technical Advisory Group (TechTAG)
 *
 * @author  Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.1 $
 *          $Date: 2006/03/09 17:34:18 $
 *          $Author: rick $
 *          $Source: /usr/local/cvs/eembc2/th_lite/src/thtime.h,v $
 *          
 * @note   
 *
 *
 * HISTORY :
 *
 * $Log: thtime.h,v $
 * Revision 1.1  2006/03/09 17:34:18  rick
 * Version 2 Office Release Candidate 5
 *
 * Revision 1.9  2005/12/02 23:53:39  rick
 * Fix mixed EOL format causing ^M's to appear in Unix checkouts.
 *
 * Revision 1.8  2005/09/10 04:02:24  rick
 * eol update, add uu_send_file
 *
 * Revision 1.7  2005/04/27 20:33:15  rick
 * Copyrite update 2005
 *
 * Revision 1.6  2004/12/08 23:27:19  rick
 * New standard header for documentation generation.
 *
 * Revision 1.4  2004/11/29 23:00:09  rick
 * Add dependency generation, and deprecated to documentation
 *
 * Revision 1.3  2004/07/09 05:11:07  rick
 * Add gettimeofday
 *
 * Revision 1.2  2004/07/06 20:38:40  rick
 * Convert errno to ee_errno to resolve libc errno function conflict. Add prototypes for internal time functions.
 *
 * Revision 1.1  2004/07/03 03:13:59  rick
 * Add time, link, and exit to redirection.
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
