/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
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
