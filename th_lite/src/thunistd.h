/**
 * @file
 * @brief  Redirect for unistd.h or io.h
 *
 * $RCSfile: thunistd.h,v $
 *
 *  EEMBC : EEMBC Technical Advisory Group (TechTAG)
 *
 * @author  Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.1 $
 *          $Date: 2006/03/09 17:34:18 $
 *          $Author: rick $
 *          $Source: /usr/local/cvs/eembc2/th_lite/src/thunistd.h,v $
 *          
 * @note   
 *
 *
 * HISTORY :
 *
 * $Log: thunistd.h,v $
 * Revision 1.1  2006/03/09 17:34:18  rick
 * Version 2 Office Release Candidate 5
 *
 * Revision 1.12  2005/12/02 23:53:39  rick
 * Fix mixed EOL format causing ^M's to appear in Unix checkouts.
 *
 * Revision 1.11  2005/09/10 04:02:24  rick
 * eol update, add uu_send_file
 *
 * Revision 1.10  2005/04/27 20:33:15  rick
 * Copyrite update 2005
 *
 * Revision 1.9  2005/04/26 22:38:03  rick
 * Add HAVE_DECL_SETMODE, HAVE_SETMODE
 *
 * Revision 1.8  2004/12/08 23:27:48  rick
 * New standard header for documentation generation.
 *
 * Revision 1.7  2004/09/13 19:29:53  rick
 * Add th_read, th_write, and th_lseek
 *
 * Revision 1.6  2004/09/11 01:45:20  administrator
 * Enhancements for no fcntl.h, and limited errno.h
 *
 * Revision 1.5  2004/08/10 17:44:51  rick
 * Add vsnprintf
 *
 * Revision 1.4  2004/07/03 03:13:59  rick
 * Add time, link, and exit to redirection.
 *
 * Revision 1.3  2004/06/29 19:36:23  rick
 * EE_REDIRECT, and Shared file for Regular and Lite
 *
 * Revision 1.2  2004/06/23 05:55:24  rick
 * EE_REDIRECT, and Shared Files
 *
 * Revision 1.1  2004/06/14 18:02:20  rick
 * Bug 274: Precision in log files is not large enough for reporting results on simulators.
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

#ifndef THUNISTD_H
#define THUNISTD_H

/** Type for ee_pid_t. */
#include "thtypes.h"
#if		HAVE_UNISTD_H
#include <unistd.h>
#else
#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2
#endif

/** @addtogroup SHFL
@{ */
/** @addtogroup thunistd_h EEMBC Redirect for unistd.h
@{ */

#ifdef __cplusplus
extern "C" {
#endif

/** Don't redirect unless specified explicitly. */
#if 	!defined(EE_REDIRECT)
#define	EE_REDIRECT	0
#endif

/** libc getenv */
char	*th_getenv(const char *key);
/** libc getpid Get Process ID */
ee_pid_t th_getpid(void);

int		 th_open	(const char *pathname, int flags);
int 	 th_close	(int fildes);
size_t	 th_read	(int fd, void *buf, size_t count);
size_t	 th_write	(int fd, const void *buf, size_t count);
ee_off_t th_lseek	(int fildes, ee_off_t offset, int whence);

int		th_fsync(int fildes);
int		th_isatty(int fildes);
int 	th_dup(int oldfd);
int 	th_dup2(int oldfd, int newfd);
int		th_unlink(const char *filename);
int 	th_link(const char *oldpath, const char *newpath);

/** This is from io.h windows only. 
@note This declaration can conflict with some gcc unistd.h files, use this
flag to remove the local declaration.
*/
#if 	!HAVE_DECL_SETMODE
int 	setmode(int fd, int mode);
#endif

#if 	EE_REDIRECT
#define open(x,y,z)		th_open(x,y)
#define read(x,y,z)		th_read(x,y,z)
#define write(x,y,z)	th_write(x,y,z)
#define close(x)		th_close(x)
#define lseek(x,y,z)	th_lseek(x,y,z)
#define getenv(x)		th_getenv(x)
#define pid_t			ee_pid_t
#define getpid			th_getpid
#define fsync(x)		th_fsync(x)
#define isatty(x)		th_isatty(x)
#define dup(x)			th_dup(x)
#define dup2(x,y)		th_dup2(x,y)
#define unlink(x)		th_unlink(x)
#define link(x,y)		th_link(x,y)
#define setmode(x,y)	/* */
#endif

#ifdef __cplusplus
}
#endif
#endif /* file sentinel */
/** @} */
/** @} */
