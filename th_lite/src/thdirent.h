/**
 * @file
 * @brief  Redirect for dirent.h
 *
 * $RCSfile: thdirent.h,v $
 *
 *  EEMBC : EEMBC Technical Advisory Group (TechTAG)
 *
 * @author  Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.1 $
 *          $Date: 2006/03/09 17:34:18 $
 *          $Author: rick $
 *          $Source: /usr/local/cvs/eembc2/th_lite/src/thdirent.h,v $
 *          
 * @note   This file provides a stub interface for files that cannot include
 *         eembc data types.
 *
 * HISTORY :
 *
 * $Log: thdirent.h,v $
 * Revision 1.1  2006/03/09 17:34:18  rick
 * Version 2 Office Release Candidate 5
 *
 * Revision 1.9  2005/12/02 23:53:36  rick
 * Fix mixed EOL format causing ^M's to appear in Unix checkouts.
 *
 * Revision 1.8  2005/09/10 04:02:24  rick
 * eol update, add uu_send_file
 *
 * Revision 1.7  2005/04/27 20:33:14  rick
 * Copyrite update 2005
 *
 * Revision 1.6  2004/12/08 23:27:18  rick
 * New standard header for documentation generation.
 *
 * Revision 1.2  2004/06/29 19:36:22  rick
 * EE_REDIRECT, and Shared file for Regular and Lite
 *
 * Revision 1.1  2004/06/23 05:55:24  rick
 * EE_REDIRECT, and Shared Files
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
