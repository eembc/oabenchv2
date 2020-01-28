/**
 * @file
 * @brief  Definition of FILE for thstdio.h and fileio.h
 *
 * $RCSfile: threent.h,v $
 *
 *  EEMBC : EEMBC Technical Advisory Group (TechTAG)
 *
 * @author  Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.1 $
 *          $Date: 2006/03/09 17:34:18 $
 *          $Author: rick $
 *          $Source: /usr/local/cvs/eembc2/th_lite/src/threent.h,v $
 *          
 * @note   
 *
 *
 * HISTORY :
 *
 * $Log: threent.h,v $
 * Revision 1.1  2006/03/09 17:34:18  rick
 * Version 2 Office Release Candidate 5
 *
 * Revision 1.14  2005/12/02 23:53:38  rick
 * Fix mixed EOL format causing ^M's to appear in Unix checkouts.
 *
 * Revision 1.13  2005/09/10 04:02:24  rick
 * eol update, add uu_send_file
 *
 * Revision 1.12  2005/04/27 20:33:15  rick
 * Copyrite update 2005
 *
 * Revision 1.11  2004/12/08 23:27:19  rick
 * New standard header for documentation generation.
 *
 * Revision 1.8  2004/09/03 22:29:25  rick
 * New Office Textv2 functions
 *
 * Revision 1.7  2004/08/10 17:44:51  rick
 * Add vsnprintf
 *
 * Revision 1.6  2004/08/09 20:22:39  rick
 * Add th_open, clear warnings from stdio/threent
 *
 * Revision 1.5  2004/08/09 18:29:50  rick
 * Porting enhancements for wchar_t, FILE typedefs, and missing stdio definitions.
 *
 * Revision 1.4  2004/07/07 18:04:11  rick
 * Resolve type definition recursion on Linux GCC
 *
 * Revision 1.3  2004/07/07 05:14:01  rick
 * Seperate thstdint.h from thtypes.h, conflicts on Unix
 *
 * Revision 1.2  2004/06/29 19:36:23  rick
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


/** File Sentinel */
#ifndef THREENT_H
#define THREENT_H

/** Get FILENAME_MAX */
#include <stdio.h>

#ifndef	TH_TYPES_H
#include "thtypes.h"
#endif

/** @addtogroup SHFL
@{ */
/** @addtogroup threent_h Harness definition of FILE
@{ */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	PATH_MAX
#define	PATH_MAX	160
#endif

/** compiler may define this one in stdio.h, we don't care, but do need to pick one. */
#if		defined(FILENAME_MAX)
#define	FILENAME_MAX_defined
#else
/*#undef	FILENAME_MAX*/
#define FILENAME_MAX	1024
#endif

/** Generally part of stdio.h. eVC does not support this, and has trouble nesting ifdef's. */
#if		!defined(L_tmpnam)

#if		defined(FILENAME_MAX)
#define L_tmpnam    FILENAME_MAX
#else
#define L_tmpnam    1024
#endif

#endif

/** Definition  of  FILE
 *
 *  Non-portable, specific definition of FILE.
 *  @warning Do *NOT* use your own compiler's definition of FILE or
 *  any of the file-related I/O definitions.
 *
 */
typedef struct ee_file_t
{
	void *next;		/* a-void a seperate typedef for linked list */
	char name[FILENAME_MAX]; /* ascii filename */
	size_t  girth;      /* physical storage allocated for file (block allocation) */
	char *start;            /* pointer to first byte in file */
	char *pos;              /* current position in file */
	char *end;              /* end of file pointer */
	size_t  size;       /* actual file size (in bytes) */
	int  status;            /* file status (open, closed, etc...) */
	int  mode;              /* mode, such as readable, writeable, etc.. */
	int  _flags;            /* flags for ferror,feof,clearerr compatibility */
	ee_ino_t  fileno;      /* fileno, inode, filedes, all together. */
} ee_FILE;
/** Remove FILENAME_MAX so future stdio.h won't fail. */
#ifndef	FILENAME_MAX_defined
#undef	FILENAME_MAX
#else
#undef	FILENAME_MAX_defined
#endif

/** Declare external stdio array */
extern	ee_FILE     ee_stdio[];


#ifdef __cplusplus
}
#endif
#endif /* file sentinel */
/** @} */
/** @} */
