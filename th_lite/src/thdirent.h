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
/** @addtogroup thdirent_h EEMBC Redirect for dirent.h
@{ */

/** File Sentinel. */
#ifndef THDIRENT_H
#define THDIRENT_H
#ifdef __cplusplus
extern "C" {
#endif

/** Don't redirect unless specified explicitly. */
#if 	!defined(EE_REDIRECT)
#define	EE_REDIRECT	0
#endif

/** EEMBC dirent structure.
According to POSIX, the dirent structure contains a field char d_name[]
of  unspecified  size,  with  at most NAME_MAX characters preceding the
terminating null character. Use of other fields will harm  the  porta-
bility  of  your  programs. POSIX-2001 also documents the field ino_t
d_ino as an XSI extension.
*/
struct ee_dirent
{
	/** This is the null-terminated file name component. 
	This is the only field you can count on in all POSIX systems.
	You need to make this the FIRST field, callers downstream may map thier own dirent with
	this assumption.*/
	char *d_name;

	/** This is the file serial number. For BSD compatibility, you can also refer to this member as d_ino.
	(ino_t -> uint in this implementation).*/
	ee_ino_t d_ino;

	/** This is the length of the file name, not including the terminating null character. */
	size_t d_namlen;
};

/** EEMBC DIR structure.
The DIR type is typically implemented using a file descriptor, and the opendir function in terms of the open function.
*/
typedef struct __ee_DIR
{
	ee_FILE *start;
	ee_FILE	*pos;
	char    *pathname;
	char    *pattern;
	char    *d_name;
} ee_DIR;


/* DIRENT routines, and helpers from harness */

char      *th_getcwd   (char *buffer, size_t size);
char      *th_getwd    (char *buffer);
int        th_chdir    (const char *filename);
ee_DIR    *th_opendir  (const char *dirname);
struct ee_dirent *th_readdir  (ee_DIR *dirstream);
int        th_closedir (ee_DIR *dirstream);
void       th_rewinddir(ee_DIR *dirstream);

#if 	EE_REDIRECT
#define DIR		ee_DIR
#define dirent	ee_dirent
#define getcwd  		th_getcwd   
#define getwd(b)    	th_getwd(b)
#define chdir(f)    	th_chdir(f)
#define opendir(d)  	th_opendir(d)
#define readdir(d)  	th_readdir(d)  
#define closedir(d) 	th_closedir(d)
#define rewinddir(d)	th_rewinddir(d)
#endif

#ifdef __cplusplus
}
#endif
#endif /* file sentinel */
/** @} */
/** @} */
