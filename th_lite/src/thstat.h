/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
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
