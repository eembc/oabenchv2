/**
 * @file
 * @brief  Redirect for stat.h
 *
 * $RCSfile: thstat.h,v $
 *
 *  EEMBC : EEMBC Technical Advisory Group (TechTAG)
 *
 * @author  Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.1 $
 *          $Date: 2006/03/09 17:34:18 $
 *          $Author: rick $
 *          $Source: /usr/local/cvs/eembc2/th_lite/src/thstat.h,v $
 *          
 * @note   
 *
 *
 * HISTORY :
 *
 * $Log: thstat.h,v $
 * Revision 1.1  2006/03/09 17:34:18  rick
 * Version 2 Office Release Candidate 5
 *
 * Revision 1.8  2005/12/02 23:53:38  rick
 * Fix mixed EOL format causing ^M's to appear in Unix checkouts.
 *
 * Revision 1.7  2005/09/10 04:02:24  rick
 * eol update, add uu_send_file
 *
 * Revision 1.6  2005/04/27 20:33:15  rick
 * Copyrite update 2005
 *
 * Revision 1.5  2004/12/08 23:27:19  rick
 * New standard header for documentation generation.
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


#ifndef THSTAT_H
#define THSTAT_H

/** Type definitions for struct members. */
#include "thtypes.h"

/** @addtogroup SHFL
@{ */
/** @addtogroup thstat_h EEMBC Redirect for stat.h
@{ */

#ifdef __cplusplus
extern "C" {
#endif

/** Don't redirect unless specified explicitly. */
#if 	!defined(EE_REDIRECT)
#define	EE_REDIRECT	0
#endif

/** EEMBC stat structure. File status information returned to user.
Since ee_stat is also a function, we can't typedef this one. As POSIX as possible. 
@warning Cygwin redefines timestamps (i.e. #define st_atime st_atim.tv_sec)
*/
struct th_stat
{
	ee_mode_t	st_mode;	/* File mode (see mknod(2)), not in MSVC */
	/*ee_ino_t    st_ino;*/      /* Inode number */
	/*ee_dev_t    st_dev;*/      /* ID of device containing a directory entry for this file */
	/*ee_dev_t    st_rdev;*/     /* ID of device defined only for char special or block special files */
	ee_nlink_t	st_nlink;    /* Number of links */
	/*ee_uid_t    st_uid;*/      /* User ID of the file's owner */
	/*ee_gid_t    st_gid;*/      /* Group ID of the file's group */
	ee_off_t    st_size;	/* File size in bytes */
	ee_time_t	ee_st_atime;	/* Time of last access */
	ee_time_t   ee_st_mtime;	/* Time of last data modification */
	ee_time_t   ee_st_ctime;	/* Time of last file status change */
	long		st_blksize;  /* Preferred I/O block size */
	ee_blkcnt_t	st_blocks;   /* Number of 512 byte blocks allocated */
};

/* Harness Stat functions */

int        th_stat     (const char *path, struct th_stat *buf);
int        th_lstat    (const char *path, struct th_stat *buf);
int        th_fstat    (int fildes, struct th_stat *buf);

/* Stat Macro in Harness */

#define 	ee__IFMT	0170000	/* type of file */
#define 	ee__IFDIR	0040000	/* directory */
#define 	ee__IFCHR	0020000	/* character special */
#define 	ee__IFBLK	0060000	/* block special */
#define 	ee__IFREG	0100000	/* regular */
#define 	ee__IFLNK	0120000	/* symbolic link */
#define 	ee__IFSOCK	0140000	/* socket */
#define 	ee__IFIFO	0010000	/* fifo */

#define 	ee_S_BLKSIZE  1024 /* size of a block */

#define 	ee_S_ISUID		0004000	/* set user id on execution */
#define 	ee_S_ISGID		0002000	/* set group id on execution */
/* Begin Not POSIX */
#define 	ee_S_ISVTX		0001000	/* save swapped text even after use */
#define 	ee_S_IREAD		0000400	/* read permission, owner */
#define 	ee_S_IWRITE		0000200	/* write permission, owner */
#define 	ee_S_IEXEC		0000100	/* execute/search permission, owner */
#define 	ee_S_ENFMT		0002000	/* enforcement-mode locking */

#define 	ee_S_IFMT		ee__IFMT
#define 	ee_S_IFDIR		ee__IFDIR
#define 	ee_S_IFCHR		ee__IFCHR
#define 	ee_S_IFBLK		ee__IFBLK
#define 	ee_S_IFREG		ee__IFREG
#define 	ee_S_IFLNK		ee__IFLNK
#define 	ee_S_IFSOCK		ee__IFSOCK
#define 	ee_S_IFIFO		ee__IFIFO
/* End Not POSIX */

#define 	ee_S_IRWXU (ee_S_IRUSR | ee_S_IWUSR | ee_S_IXUSR)
#define 	ee_S_IRUSR	0000400	/* read permission, owner */
#define 	ee_S_IWUSR	0000200	/* write permission, owner */
#define 	ee_S_IXUSR	0000100/* execute/search permission, owner */
#define 	ee_S_IRWXG	(ee_S_IRGRP | ee_S_IWGRP | ee_S_IXGRP)
#define 	ee_S_IRGRP	0000040	/* read permission, group */
#define 	ee_S_IWGRP	0000020	/* write permission, grougroup */
#define 	ee_S_IXGRP	0000010/* execute/search permission, group */
#define 	ee_S_IRWXO	(ee_S_IROTH | ee_S_IWOTH | ee_S_IXOTH)
#define 	ee_S_IROTH	0000004	/* read permission, other */
#define 	ee_S_IWOTH	0000002	/* write permission, other */
#define 	ee_S_IXOTH	0000001/* execute/search permission, other */

#define 	ee_S_ISBLK(m)	(((m)&ee__IFMT) == ee__IFBLK)
#define 	ee_S_ISCHR(m)	(((m)&ee__IFMT) == ee__IFCHR)
#define 	ee_S_ISDIR(m)	(((m)&ee__IFMT) == ee__IFDIR)
#define 	ee_S_ISFIFO(m)	(((m)&ee__IFMT) == ee__IFIFO)
#define 	ee_S_ISREG(m)	(((m)&ee__IFMT) == ee__IFREG)
#define 	ee_S_ISLNK(m)	(((m)&ee__IFMT) == ee__IFLNK)
#define 	ee_S_ISSOCK(m)	(((m)&ee__IFMT) == ee__IFSOCK)

/** Redirection Section */

#if 	EE_REDIRECT

/* Stat Structure Definition. Cygwin problem only at this time. */
#undef	st_atime
#define	st_atime	ee_st_atime
#undef	st_mtime
#define	st_mtime	ee_st_mtime
#undef	st_ctime
#define	st_ctime	ee_st_ctime

/* Stat Macro Redirection */

#define 	_IFMT   	ee__IFMT	/* type of file */
#define 	_IFDIR		ee__IFDIR	/* directory */
#define 	_IFCHR		ee__IFCHR	/* character special */
#define 	_IFBLK		ee__IFBLK	/* block special */
#define 	_IFREG		ee__IFREG	/* regular */
#define 	_IFLNK  	ee__IFLNK	/* symbolic link */
#define 	_IFSOCK		ee__IFSOCK	/* socket */
#define 	_IFIFO  	ee__IFIFO	/* fifo */

#define 	S_BLKSIZE	ee_S_BLKSIZE	/* size of a block */

#define 	S_ISUID		ee_S_ISUID	/* set user id on execution */
#define 	S_ISGID		ee_S_ISGID	/* set group id on execution */
/* Begin Not POSIX */
#define 	S_ISVTX 	ee_S_ISVTX	/* save swapped text even after use */
#define 	S_IREAD 	ee_S_IREAD	/* read permission, owner */
#define 	S_IWRITE 	ee_S_IWRITE	/* write permission, owner */
#define 	S_IEXEC 	ee_S_IEXEC	/* execute/search permission, owner */
#define 	S_ENFMT 	ee_S_ENFMT	/* enforcement-mode locking */

#define 	S_IFMT		ee__IFMT
#define 	S_IFDIR		ee__IFDIR
#define 	S_IFCHR		ee__IFCHR
#define 	S_IFBLK		ee__IFBLK
#define 	S_IFREG		ee__IFREG
#define 	S_IFLNK		ee__IFLNK
#define 	S_IFSOCK	ee__IFSOCK
#define 	S_IFIFO		ee__IFIFO
/* End Not POSIX */

#define 	S_IRWXU	ee_S_IRWXU	

#define 	S_IRWXU	ee_S_IRWXU	
#define 	S_IRUSR	ee_S_IRUSR	/* read permission, owner */
#define 	S_IWUSR	ee_S_IWUSR	/* write permission, owner */
#define 	S_IXUSR	ee_S_IXUSR	/* execute/search permission, owner */
#define 	S_IRWXG	ee_S_IRWXG	
#define 	S_IRGRP	ee_S_IRGRP	/* read permission, group */
#define 	S_IWGRP	ee_S_IWGRP	/* write permission, grougroup */
#define 	S_IXGRP	ee_S_IXGRP	/* execute/search permission, group */
#define 	S_IRWXO	ee_S_IRWXO
#define 	S_IROTH	ee_S_IROTH	/* read permission, other */
#define 	S_IWOTH	ee_S_IWOTH	/* write permission, other */
#define 	S_IXOTH	ee_S_IXOTH	/* execute/search permission, other */

#define 	S_ISBLK 	ee_S_ISBLK
#define 	S_ISCHR 	ee_S_ISCHR
#define 	S_ISDIR 	ee_S_ISDIR
#define 	S_ISFIFO 	ee_S_ISFIFO
#define 	S_ISREG 	ee_S_ISREG
#define 	S_ISLNK 	ee_S_ISLNK
#define 	S_ISSOCK	ee_S_ISSOCK

/* Function re-direction */

/** lstat re-direction */
#define lstat(x,y)	th_lstat(x,y)
/** Stat redirection involves both function stat, and struct stat. */
#define stat	th_stat
/** fstat re-direction */
#define fstat(x,y)	th_fstat(x,y)
#endif

#ifdef __cplusplus
}
#endif
#endif /* file sentinel */
/** @} */
/** @} */
