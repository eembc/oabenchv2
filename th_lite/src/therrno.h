/**
 * @file
 * @brief  EEMBC Redirect for errno.h
 *
 * $RCSfile: therrno.h,v $
 *
 *  EEMBC : EEMBC Technical Advisory Group (TechTAG)
 *
 * @author  Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.1 $
 *          $Date: 2006/03/09 17:34:18 $
 *          $Author: rick $
 *          $Source: /usr/local/cvs/eembc2/th_lite/src/therrno.h,v $
 *          
 * @note   
 *
 *
 * HISTORY :
 *
 * $Log: therrno.h,v $
 * Revision 1.1  2006/03/09 17:34:18  rick
 * Version 2 Office Release Candidate 5
 *
 * Revision 1.10  2005/12/02 23:53:36  rick
 * Fix mixed EOL format causing ^M's to appear in Unix checkouts.
 *
 * Revision 1.9  2005/09/10 04:02:24  rick
 * eol update, add uu_send_file
 *
 * Revision 1.8  2005/04/27 20:33:14  rick
 * Copyrite update 2005
 *
 * Revision 1.7  2004/12/08 23:27:18  rick
 * New standard header for documentation generation.
 *
 * Revision 1.3  2004/09/11 01:45:20  administrator
 * Enhancements for no fcntl.h, and limited errno.h
 *
 * Revision 1.2  2004/06/29 19:36:22  rick
 * EE_REDIRECT, and Shared file for Regular and Lite
 *
 * Revision 1.1  2004/06/23 05:55:24  rick
 * EE_REDIRECT, and Shared Files
 *
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

#ifndef THERRNO_H
#define THERRNO_H

/** Get autoconf definitions */
#include "thconfig.h"

/** Use Toolchain defines if possible. */
#if		HAVE_ERRNO_H
#include <errno.h>
#elif	HAVE_SYS_ERRNO_H
#include <sys/errno.h>
#endif

/** @addtogroup SHFL
@{ */
/** @addtogroup therrno_h EEMBC Redirect for errno.h
@{ */

#ifdef __cplusplus
extern "C" {
#endif

/** Definitions inside of local c++ extern. Keep in sync with ERRNO definitions above. */
#if		(!HAVE_ERRNO_H && !HAVE_SYS_ERRNO_H) || NEED_ERRNO_DEFINES
/** End of file, this is almost always -1.
@warning EOF can be defined by errno.h OR stdio.h */
#ifndef	EOF
#define EOF             -1
#endif

/* Need all definitions. */

#undef	NEED_ERANGE
#define NEED_ERANGE 	1
#undef	NEED_ENOTDIR
#define NEED_ENOTDIR 	1
#undef	NEED_EACCES
#define NEED_EACCES 	1
#undef	NEED_EBADF
#define NEED_EBADF  	1
#undef	NEED_EINVAL
#define NEED_EINVAL 	1
#undef	NEED_ENOENT
#define NEED_ENOENT 	1
#undef	NEED_EEXIST
#define NEED_EEXIST 	1
#undef	NEED_EFAULT
#define NEED_EFAULT 	1
#undef	NEED_ENOMEM
#define NEED_ENOMEM 	1
#undef	NEED_EPERM
#define NEED_EPERM  	1
#undef	NEED_ESRCH
#define NEED_ESRCH  	1

#endif /* HAVE_ERRNO. */

/* Select errno definitions to define. */

#if 	NEED_ERANGE && !defined(ERANGE)
#define ERANGE	define_ERANGE
#endif
#if 	NEED_ENOTDIR && !defined(ENOTDIR)
#define ENOTDIR	define_ENOTDIR
#endif
#if 	NEED_EACCES && !defined(EACCES)
#define EACCES	define_EACCES
#endif
#if 	NEED_EBADF && !defined(EBADF)
#define EBADF	define_EBADF
#endif
#if 	NEED_EINVAL && !defined(EINVAL)
#define EINVAL	define_EINVAL
#endif
#if 	NEED_ENOENT && !defined(ENOENT)
#define ENOENT	define_ENOENT
#endif
#if 	NEED_EEXIST && !defined(EEXIST)
#define EEXIST	define_EEXIST
#endif
#if 	NEED_EFAULT && !defined(EFAULT)
#define EFAULT	define_EFAULT
#endif
#if 	NEED_ENOMEM && !defined(ENOMEM)
#define ENOMEM	define_ENOMEM
#endif
#if 	NEED_EPERM && !defined(EPERM)
#define EPERM	define_EPERM
#endif
#if 	NEED_ESRCH && !defined(ESRCH)
#define ESRCH	define_ESRCH
#endif


#ifdef __cplusplus
}
#endif
#endif /* file sentinel */
/** @} */
/** @} */
