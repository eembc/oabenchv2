/**
 * @file
 * @brief  Test Harness File System using Stream I/O calls.
 *
 * $RCSfile: fileio.c,v $
 *
 *  EEMBC : TechTag
 *
 * @author  Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.3 $
 *          $Date: 2006/03/09 17:34:18 $
 *          $Author: rick $
 *          $Source: /usr/local/cvs/eembc2/th_lite/src/fileio.c,v $
 *          
 * @note   
 *
 *
 * HISTORY :
 *
 * $Log: fileio.c,v $
 * Revision 1.3  2006/03/09 17:34:18  rick
 * Version 2 Office Release Candidate 5
 *
 * Revision 1.50  2005/12/02 23:53:34  rick
 * Fix mixed EOL format causing ^M's to appear in Unix checkouts.
 *
 * Revision 1.49  2005/09/10 04:02:23  rick
 * eol update, add uu_send_file
 *
 * Revision 1.48  2005/04/27 20:33:13  rick
 * Copyrite update 2005
 *
 * Revision 1.47  2005/04/27 16:05:06  rick
 * Add HAVE_CTYPE_H, re-order headers in doscan.c, and correct type sign in fileio.c to remove warnings.
 *
 * Revision 1.46  2004/12/08 23:27:43  rick
 * New standard header for documentation generation.
 *
 * Revision 1.45  2004/11/19 19:53:32  rick
 * Fix empty path case in ee_fname_resolver
 *
 * Revision 1.44  2004/11/10 17:32:33  rick
 * Fix ee_vfprintf with static buf and th_vsprintf
 *
 * Revision 1.43  2004/09/14 17:41:48  rick
 * Bug 280: ee_fwrite calls th_printf w/o EOL, fix by Ron Olson
 *
 * Revision 1.42  2004/09/13 19:29:51  rick
 * Add th_read, th_write, and th_lseek
 *
 * Revision 1.41  2004/09/03 22:29:24  rick
 * New Office Textv2 functions
 *
 * Revision 1.40  2004/08/09 20:22:38  rick
 * Add th_open, clear warnings from stdio/threent
 *
 * Revision 1.39  2004/08/09 18:29:50  rick
 * Porting enhancements for wchar_t, FILE typedefs, and missing stdio definitions.
 *
 * Revision 1.38  2004/07/06 20:38:40  rick
 * Convert errno to ee_errno to resolve libc errno function conflict. Add prototypes for internal time functions.
 *
 * Revision 1.37  2004/07/03 03:13:58  rick
 * Add time, link, and exit to redirection.
 *
 * Revision 1.36  2004/06/29 19:36:22  rick
 * EE_REDIRECT, and Shared file for Regular and Lite
 *
 * Revision 1.35  2004/06/23 05:55:23  rick
 * EE_REDIRECT, and Shared Files
 *
 * Revision 1.34  2004/05/07 22:35:30  rick
 * Fix internal rv type in ee_fread.
 *
 * Revision 1.31  2004/05/06 21:15:48  rick
 * Fix th_strdup for heap, and epn NULL return to 0 string
 *
 * Revision 1.30  2004/04/29 17:30:36  rick
 * Fix warnings.
 *
 * Revision 1.31  2004/04/15 16:45:43  rick
 * fread/fwrite rv, size, and count to size_t
 *
 * Revision 1.30  2004/04/08 23:08:50  rick
 * Bug 128: rollback and fix ee_extend
 *
 * Revision 1.28  2004/04/05 15:43:50  rick
 * Convert ee_fread/ee_fwrite to memcpy/bcopy.
 *
 * Revision 1.25  2004/04/01 22:38:46  rick
 * Add ee_exec_ls, add config flags for doscan, fix msvc dirent flags
 *
 * Revision 1.26  2004/03/24 02:01:15  rick
 * Fix ee_fcreate for expanded files
 *
 * Revision 1.25  2004/03/23 21:03:24  rick
 * Add file size extender for fwrite
 *
 * Revision 1.24  2004/03/15 21:29:05  rick
 * Add documentation tags, and cleanup comments
 *
 * Revision 1.23  2004/03/10 23:57:17  rick
 * fix dirent calls
 *
 * Revision 1.22  2004/03/10 00:18:00  rick
 * Add scanf family, vfprintf, and new doscan
 *
 * Revision 1.21  2004/02/20 00:24:31  rick
 * change ee_dirent from typedef to struct
 *
 * Revision 1.20  2004/02/12 23:34:36  rick
 * Add fputs, macro fixes to thstdio
 *
 * Revision 1.19  2004/02/11 02:55:45  rick
 * Add macro redefinitions, improve efn and fileio
 *
 * Revision 1.16  2004/02/10 08:29:58  rick
 * Waterfal bmp256 run
 *
 * Revision 1.15  2004/02/10 06:55:37  rick
 * Add fileio calls and stdio re-router
 *
 * Revision 1.14  2004/02/06 18:18:38  rick
 * Fix errno conflicts
 *
 * Revision 1.15  2004/02/05 23:03:24  rick
 * Harness update with portable dirent
 *
 * Revision 1.14  2004/01/28 23:07:29  rick
 * Add th_strdup, fileio cwd
 *
 * Revision 1.13  2004/01/22 00:56:52  rick
 * Release cleanup, copyright year corrections
 *
 * Revision 1.12  2003/07/24 22:01:36  mdvesper
 * Protect fseek types
 *
 * Revision 1.11  2003/04/30 21:53:31  rick
 * if !float_support, remove atof
 *
 * Revision 1.10  2003/04/18 15:05:29  rick
 * Add ftell, vfscanf, vsscanf
 *
 * Revision 1.9  2003/04/10 22:54:37  rick
 * add reopen support to th_fcreate
 *
 * Revision 1.8  2003/03/26 00:17:56  rick
 * Add scanf functions
 *
 * Revision 1.7  2003/03/14 00:24:28  rick
 * Add feof and text file support to fileio
 *
 * Revision 1.6  2003/03/06 00:34:25  rick
 * Add th_fgets, and %g to printf
 *
 * Revision 1.5  2003/03/05 00:29:10  rick
 * Change th_fcreate size to ee_fsize_t
 *
 * Revision 1.4  2003/02/08 21:24:04  rick
 * Add newline
 *
 * Revision 1.3  2003/01/22 00:00:56  rick
 * Add File I/O to Regular
 *
 * Revision 1.4  2003/01/17 22:44:37  rick
 * Add File I/O to harness
 *
 * Revision 1.3  2003/01/03 22:22:37  rick
 * fix eol format and remove unreachable statements
 *
 * Revision 1.1  2003/01/03 18:08:58  rick
 * Add ee fileio to harness
 *
 * Revision 1.1  2003/01/03 00:26:03  rick
 * Initial file I/O routines
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

#include <string.h>	/* memcmp */
#include <stdarg.h>
#include <stdio.h>

#include "thlib.h"
#include "fileio.h"
#include "thfl.h" /* efn, epn */
#include "ssubs.h"

/** eVC doesn't provide this define. */
#ifndef		FILENAME_MAX
#define		FILENAME_MAX	1024
#endif

/** @addtogroup SHFL
@{ */
/** @addtogroup fileio_c Test Harness File System 
@{ */

/** Internal variable used for stream file error reporting when !ee_errno.h. 
@note fileio.h includes an actual libc ee_errno.h, with ee_errno defined. If you
are just including fileio.h, you will need to handle ee_errno like this in
your C source. If you want to use libc ee_errno, see fileio.h and thcfg.h for
the autoconf definitions.
@todo We now use ee_errno internnaly defined. Some compilers implement errno
as a function, not a variable. We do NOT use
internal ee_errno in fileio.h for external callers when we force
HAVE_ERRNO_H false, as it will conflict with libc when the user forces
us to define ee_errno.h variables when they also have ee_errno.h in thier
tool chain.  If this becomes important, like we implement strerror,
then come up with a 100% resolution for all cases.
@warning You cannot set libc errno in all cases. Some tool chains
define errno as a function, not a variable. This is a porting problem 
to be resolved in thal.c.
*/
static int ee_errno;

/** Default value for writeable file when not specified by user */
#define MAX_FILESIZE     (0x40000)

/** Default value to reallocate writeable file when not specified in thcfg.
@note This causes a realloc during benchmark runs. Since we are embedded,
this number should be larger than normally the case in a file system.
*/
#ifndef TH_FILE_ALLOCATION_BLOCKSZ
#define	TH_FILE_ALLOCATION_BLOCKSZ	0x40000
#endif

/** Linked list of files in filesystem. */
ee_FILE	*ee_filelist = NULL;

/** Reqired file definitions for standard I/O, outside of ee_filelist. 
@todo We are not supporting writes to stdin. Technically you can do this
but it isn't really used unless you are executing inside a daemon, like 
a web server. If this become important, then open this up and handle the
differences between host and embedded operation.
*/
ee_FILE	ee_stdio[3]	= {
	{NULL,"stdin",0,0,0,0,0,F_OPEN,F_READABLE,0,0},
	{NULL,"stdout",0,0,0,0,0,F_OPEN,F_WRITEABLE,0,1},
	{NULL,"stderr",0,0,0,0,0,F_OPEN,F_WRITEABLE,0,2}
};

/** Internal storage for current working directory */
static char ee_cwd[FILENAME_MAX] = "/";
/** Internal storage for current home directory when '~' in user path.
Stitch together with $HOME,$LOGNAME if environment variable link needed. */
static char ee_hmd[FILENAME_MAX] = "/home/eembc";

/* Static, or internal use only */

static ee_FILE	*ee_find_file (const char *filename);
static ee_FILE	*ee_last_file (void);
static char		*ee_fname_resolver (const char *fname);
static ee_FILE	*ee_find_fildes (int fildes);
static ee_FILE	*ee_find_fp (ee_FILE *fp);
static ee_FILE	*ee_createstrfile(const char *str);
static int		 ee_destroystrfile(ee_FILE *fp);
static int		 ee_wasCRLF(ee_FILE *fp);
static size_t	 ee_extend(ee_FILE *fp);

/* Internal use, see doscan.c */
int  ee_svfscanf (register ee_FILE *fp,const char *fmt0,va_list ap);

/* Flag Definitions */

#define __eeRD   0x0001      /* OK to read */
#define __eeWR   0x0002      /* OK to write */
/** RD and WR are not set together by standard, RW is update or '+' */
#define __eeRW   0x0004      /* + mode not supported here (open for reading & writing) */
/* These have standard values from ATT daze */
#define __eeEOF  0x0020      /* found EOF */
#define __eeERR  0x0040      /* found error */
/** Append mode not supported in this release*/
#define __eeAPP  0x0008      /* fopen()ed in append mode - so writes go to end of file */
#define __eeALLOC  0x0800      /* data malloced and needs to be cleaned */
#define __eeSTICKYMASK  0x0F00      /* mask for sticky flags */

#define __eefeof(p)      (((p)->_flags & __eeEOF) != 0)
#define __eeseof(p)      ((void)((p)->_flags |= __eeEOF))
#define __eeferror(p)    (((p)->_flags & __eeERR) != 0)
#define __eeserr(p)      ((void)((p)->_flags |= __eeERR))
#define __eeclearerr(p)  ((void)((p)->_flags &= ~(__eeERR|__eeEOF)))

#if (EE_DEBUG_FIO)
int ee_fio_numcall=0;
int ee_fio_from[256]={0,};
int ee_fio_fidx=0;
int ee_fio_once=1;
int ee_fio_dbg(char * f, int l, char *fn) {
	int i;
	ee_fio_numcall++;
	for (i=0; i<256; i++) {
		if (ee_fio_once && ee_fio_from[i]==l)
			return 1;
	}
	if (ee_fio_once)
		ee_fio_from[ee_fio_fidx++]=l;
	th_printf("THFIO[%d]:%s\n",ee_fio_numcall,fn);
	return 0;
}
#endif

/** Internal routine to check mode, and return _flags.

The mode argument is a character string having  one  of  the
following values:

- r or rb               Open a file for reading.
- w or wb               Open a file for writing.
- a or ab               Open a file for writing  at  end  of
                      file.
- r+ or rb+ or r+b      Open a file for update (reading  and
                      writing).
- w+ or wb+ or w+b      Open a file for update (reading  and
                      writing).
- a+ or ab+ or a+b      Open a file for update (reading  and
                      writing) at end of file.
@param filename pathname of file.
@mode proposed mode
@retval _flags based on mode, or 0 for failure.
*/
static int ee_checkmode(const char *filename,const char *mode)
{
	int flags=0;
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif
	if (!filename || !*filename || !mode || !*mode || (strlen(filename) > FILENAME_MAX))
		return 0;
	/* We don't have append support now */
	if (strchr(mode,'a')) return 0;
	if      (strchr(mode,'+'))
		flags |= __eeAPP;
	else if (strchr(mode,'r'))
		flags |= __eeRD;
	else if (strchr(mode,'w'))
		flags |= __eeWR;
	return flags;
}

/** NON-STANDARD ROUTINE TO CREATE A FILE.

Rather than create files when opened for writing, we need to allow a read/only file system to be
defined. This routine allows read and write only files to be created as needed by the benchmark.

@param filename File name, can contain path information as well.
@param mode Default stream mode enforced by filesystem. For simplicity we do not require the
usual POSIX file permissions (i.e. chmod).
@param data - Optional data to be loaded into file. Write mode files are malloced.
@param size - maximum size of file. We do NOT grow files, fragment, etc. All files are contigious.
*/
ee_FILE *ee_fcreate(const char *filename, const char *mode, char *data, ee_fsize_t size)
{
	ee_FILE	*file;
	char *fname;
	int flags;
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif

	/* bm debug
	if (strstr(filename,"waterfal.ps"))
		th_printf("*** %s\n",filename);
	 */

    /* Verify mode, get flags */
	if ((flags=ee_checkmode(filename,mode))==0)
    {
        ee_errno = EINVAL;
        return NULL;
    }

	fname = ee_fname_resolver(filename);
    /* file should not be in the filesystem */
    file = ee_find_file(fname);
    if (file != (ee_FILE *)0)
    {
		/* 
		 * Reuse file if it the same girth 
		 * Now that we can grow writeable files, remove this restriction.
		 * and just reset the girth.
		 * if (file->girth == size)
		 * file is already open, set ee_errno
         * ee_errno = EEXIST;
		 * __eeserr(file);
         * return (ee_FILE *)0;
		 * if (file->status != F_CLOSED) ee_fclose(file);
		 * return ee_fopen(file->name,mode);
		 */
		/* The only case at this point is multiple runs under th regular */
		if ((data == NULL) && (file->start!=NULL))
			th_free(file->start);	
    }
	if (size == 0) size = MAX_FILESIZE;
	if (data == NULL) { 
		data = th_malloc(size); 
		flags |= __eeALLOC; 
	}
	if (data == NULL)
		th_exit(THE_OUT_OF_MEMORY,"ee_fcreate: Not enough memory to create data for file %s\n",filename);
	/*
	 * Get the address of the pointer we need to fill in,
	 */
	if (!file)
	{
		file = ee_last_file();
		file->next = NULL;				/* next file */
	}
	strcpy(file->name,fname);    /* ascii filename */
    file->girth = size;           /* physical storage allocated for file */
    file->start = data;            /* pointer to first byte in file */
    file->pos = data;              /* current position in file */
    file->end = data;              /* end of file pointer */
    file->size=size;              /* actual file size (in bytes) */
    file->status = F_CLOSED;        /* file status (open, closed, etc...), assume open */
    file->mode = F_READABLE;      /* mode, such as readable, writeable, etc.. */
	file->_flags = flags;
	if (strchr(mode, 'w'))
	{
		file->mode |= F_WRITEABLE;
		file->size = 0;
	}
	th_free(fname);
	return(file);
}

/* ee_dup, to create a duplicate FD */

int ee_dup(int fildes)
{
	ee_FILE *dupfile;
	ee_FILE *file=ee_find_fildes(fildes);
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif
	dupfile = ee_last_file();
	dupfile->next = NULL;				/* next file */
	strcpy(dupfile->name,file->name);    /* ascii filename */
    dupfile->girth  = file->girth ;           /* physical storage allocated for file */
    dupfile->start  = file->start ;            /* pointer to first byte in file */
    dupfile->pos  = file->pos ;              /* current position in file */
    dupfile->end  = file->end ;              /* end of file pointer */
    dupfile->size = file->size;              /* actual file size (in bytes) */
    dupfile->status  = file->status ;        /* file status (open, closed, etc...), assume open */
    dupfile->mode  = file->mode ;      /* mode, such as readable, writeable, etc.. */
	dupfile->_flags  = file->_flags ;

	return dupfile->fileno;
}

/** FCLOSE() Close a file. */
int    ee_fclose (ee_FILE *file)
{
    int retval = 0;
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif

    /* If ee_FILE pointer unset or file not open, error */
    if ( (!ee_find_fp(file)) || ( file->status != F_OPEN ) )
    {
        ee_errno  = EBADF;
		if (file) __eeserr(file);
        retval = EOF;
    }

    /* No need to flush, this is a ramdisk, just update status */
	/* No need to check numlinks, yet */
    file->status = F_CLOSED;
	__eeclearerr(file);
    return (retval);
}
/** CLOSE() Close a file. 
@param fildes fileno
@retval success 0 is returned. Otherwise, -1  is
returned and ee_errno is set to indicate the error.
*/
int ee_close(int fildes)
{
	return ee_fclose(ee_find_fildes(fildes));
}

/** CLEARERR() - clear file or stream error indicator.

The  `stdio'  functions  maintain  an  error  indicator  with each file
pointer FP, to record whether any read or write errors have occurred on
the  associated file or stream.  Similarly, it maintains an end-of-file
indicator to record whether there is no more data in the file.

   Use `clearerr' to reset both of these indicators.

   See `ferror' and `feof' to query the two indicators.
*/
void ee_clearerr(ee_FILE *fp)
{
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif
	if (!fp) return;
	__eeclearerr(fp);
	ee_errno = 0;
}
/** FILENO() - Get integer file number from stream */
int ee_fileno(ee_FILE *fp)
{
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif
	if (!fp) th_exit(THE_FAILURE,"Null pointer passed to fileno");
	return fp->fileno;
}

/** FERROR() - Return ee_errno associated with file.

The  `stdio'  functions  maintain  an  error  indicator  with each file
pointer FP, to record whether any read or write errors have occurred on
the associated file or stream.  Use `ferror' to query this indicator.
@param file to be checked for errors.
@retval `0' if no errors have occurred; a nonzero value otherwise.
 */
int    ee_ferror (ee_FILE *file)
{
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif
    /* If ee_FILE pointer unset or file not open, error */
    if ( ( !file ) || ( file->status != F_OPEN ) )
    {
        return(0);
    }
    else
    {
        return __eeferror(file);
    }
}

/** FEOF() - Find end of file. 

The feof() function returns a non-zero value  when  EOF  has
previously been detected reading the named input stream.  It
returns 0 otherwise.
*/
int    ee_feof (ee_FILE *fp)
{
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif
    /* If ee_FILE pointer unset or file not open, error */
    if ((!fp) || (__eefeof(fp)))
    {
        return(EOF);
    }
    else
    {
        return (0);
    }
}
/** FFLUSH() - Flush buffered output to file. 

If stream points to an output stream or an update stream  in
which  the  most  recent  operation  was not input, fflush()
causes any unwritten data for that stream to be  written  to
the file, and the st_ctime and st_mtime fields of the under-
lying file are marked for update.

If stream is a null pointer, fflush() performs this flushing
action  on  all  streams  for  which the behavior is defined
above.

Upon successful completion, fflush() returns  0.  Otherwise,
it returns EOF and sets ee_errno to indicate the error.

*/
int    ee_fflush (ee_FILE *file)
{
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif
   /* No buffer support, so only check for valid parameter */
	if (!file)
		return 0;
	else if ((ee_find_fp(file)) == NULL)
		return EOF;
    return (0);
}
/** synchronize a file's in-memory state with the physical medium.

<unistd.h>: The fsync() function forces all outstanding  data
operations  to  synchronized  file integrity completion (see
fcntl(3HEAD) definition of O_SYNC.)
@param fildes fileno
@retval success 0. Otherwise, -1  is returned and ee_errno is set.
*/
int ee_fsync(int fildes)
{
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif
    /* No buffer support, so just check for valid fildes */
	if ((ee_find_fildes(fildes))==NULL)
	{
		ee_errno=EBADF;
		return -1;
	}
	else
		return 0;
}
/** test for a terminal device.

  The isatty() function tests whether  fildes,  an  open  file
descriptor, is associated with a terminal device.

@param fildes fileno
@retval Returns 1 if fildes is associated with
a  terminal;  otherwise  it  returns  0 and sets ee_errno.
*/
int ee_isatty(int fildes)
{
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif
	/* Not supporting device drivers for consoles */
	if ((fildes==1) || (fildes==2))
		return 1;
	else
		return 0;
}

/* Routines added to support dirent */

/** Get current working directory */
char *ee_getcwd (char *buffer, size_t size)
{
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif
	if (!buffer)
		return th_strdup(ee_cwd);

	if (strlen(ee_cwd) < size)
	{
		strcpy(buffer,ee_cwd);
		return(buffer);
	}
	else
	{
		ee_errno = EINVAL;
		return NULL;
	}
}

/** Get current working directory (BSD Deprecated) */
char *ee_getwd (char *buffer)
{
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif
	return ee_getcwd(buffer,FILENAME_MAX);
}
/** Change current working directory
@param filename File Name
@retval The normal, successful return value from chdir is 0. 
A value of -1 is returned to indicate an error. 
The ee_errno error conditions defined for this function are 
the usual file name syntax errors, plus ENOTDIR if the file filename is not a directory. 
*/
int ee_chdir (const char *filename)
{
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif
	return -1;
}
/** Convert user path name into unix path name with only relocations (../) present */
static char *ee_unixify(char *pathname)
{
	char *buf=pathname;
	/* Convert all \ to / */
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif
	while (*buf)
	{
		if (*buf=='\\') *buf='/';
		buf++;
	}
	/* Convert Drive Letters to / (/cygdrive/<drive letter> not supported) */
	/* Convert all // to / */
	return pathname;
}
/** Get path N levels up.

In this version, if the number of upward levels exceeds /, we
will return /. Input path must be absolute (start with /).
@param path Path to check levels.
@param levels Number of levels to go up.
@retval Error NULL, Success up leveled path, or /. 
Malloc'ed, caller may use free.
*/
static char *ee_uppath(const char *path,int levels)
{
	char *buf;
	char *tmpbuf;
	int	  i;
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif

	/* input path must be absolute (/xxx), less code to return empty string. */
	if (!path || (*path != '/'))
		return th_calloc(1,1);

	buf=th_strdup(path);
	if (levels==0) return buf;

	tmpbuf=buf;
	for (i=0;i<levels;i++)
	{
		tmpbuf = strrchr(buf,'/');
		if (tmpbuf == buf)
		{
			buf[1] = '\0';
			break;
		}
		else if (tmpbuf)
			*tmpbuf = '\0';
		else
			strcpy(buf,"/");
	}
	/* The result path will ALWAYS be shorter than the input path */
	if (buf[strlen(buf)-1] != '/')
		strcat(buf,"/");
	return buf;
}

/** Perform File Nmme Resolution.

Convert a user defined path to an absolute path. */
static char *ee_fname_resolver(const char *fname)
{
	char *pathname;
	char *buf;
	char *tmpbuf;
	const char *filename;
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif

	if (!fname || !*fname)
		return NULL;
	pathname=epn(fname);
	filename=efn(fname);
	/* Use current working directory as default */
	if (!pathname)
		pathname=th_strdup(ee_cwd);
	else
		pathname=ee_unixify(pathname);

	/* Very trivial cases at front of string are converted to absolute names */

	/* Use pointer arithmetic in case 16 bit char */
	tmpbuf = pathname;
	/* Don't increment past the end of string. */
	if (*tmpbuf)
		tmpbuf++; /* pathname[1] */
	/* Current directory (./) */
	if ((*pathname == '.') && (*tmpbuf == '/'))
	{
		tmpbuf++;	/* pathname[2] */
		buf = th_malloc( strlen(tmpbuf) + strlen(ee_cwd) + 2);
		strcpy(buf,ee_cwd);
		strcat(buf,tmpbuf);
		th_free(pathname);
		pathname=buf;
	}
	/* Relative path upward (../) */
	else if ((*pathname == '.') && (*tmpbuf == '.'))
	{
		int   i=0;
		char *prefix;
		/* Count how many ../ levels to go up. */
		tmpbuf=pathname;
		while ((strncmp(tmpbuf,"../",3))==0)
		{
			tmpbuf += 3;
			i++;
		}
		/* tmpbuf has the start position */
		prefix=ee_uppath(ee_cwd,i);
		buf=th_malloc(strlen(prefix)+strlen(tmpbuf)+2);
		strcpy(buf,prefix);
		strcat(buf,tmpbuf);
		th_free(prefix);
		th_free(pathname);
		pathname=buf;
	}
	/* Home Directory (~)*/
	else if (*pathname == '~')
	{
		buf = th_malloc( strlen(pathname) + strlen(ee_hmd) + 2);
		strcpy(buf,ee_hmd);
		strcat(buf,pathname);
		th_free(pathname);
		pathname=buf;
	}
	/* Drive Letter ([a-z]:) */
	else if (*tmpbuf == ':')
	{
		if ((buf=strstr(tmpbuf,"cygwin"))==NULL)
			tmpbuf++; /* root directory on first slash */
		else
			tmpbuf=buf+6; /* root directory on first slash after cygwin */
		buf = th_strdup(tmpbuf);
		th_free(pathname);
		pathname=buf;
	}
	/* empty, assumes current working directory */
	else if (*pathname != '/')
	{
		buf = th_malloc( strlen(pathname) + strlen(ee_cwd) + 2);
		strcpy(buf,ee_cwd);
		strcat(buf,pathname);
		th_free(pathname);
		pathname=buf;
	}

	buf = th_malloc(strlen(pathname) + strlen(filename) + 2);
	strcpy(buf,pathname);
	strcat(buf,filename);
	th_free(pathname);
	return buf;
}

/** The opendir function opens and returns a directory stream for reading the directory whose file name is dirname.*/
ee_DIR *ee_opendir(const char *dirname)
{
	char *buf;
	char *pathname;
	int   pathlen;
	char *pattern;
	char *d_name;
	ee_FILE *file = ee_filelist;
	ee_DIR  *dir=NULL;
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif

	if (!dirname || !*dirname) return NULL;

	buf=ee_fname_resolver(dirname);
	pathname=epn(buf);
	pathlen=strlen(pathname);
	/* We will assume '*' for Ghostscript. Use regex for general case */
	pattern=efn(buf);
	d_name=efn(pathname);
	/* root directory, no pattern supplied */
	if (pathlen==1 || !*d_name) 
	{
		if (pathname) th_free(pathname);
		pathname=buf;
		pathlen=strlen(pathname);
		d_name=(pattern?th_strdup(pattern):NULL);
		pattern=NULL;
	}

    while (file != NULL)
    {
        if (strncmp(pathname,file->name,pathlen) == 0)
		{
			dir=th_malloc(sizeof(ee_DIR));
			dir->start=file;
			dir->pos=file;
			dir->pathname=pathname;
			dir->pattern=pattern;
			dir->d_name=d_name;
            return (dir);
		}
		file = file->next;
    }
	return NULL;
}
/** This function reads the next entry from the directory. 

The ee_readdir() function returns a pointer to a dirent structure repre-
senting the next directory entry in the directory stream pointed to  by
dir.   It  returns  NULL  on  reaching  the  end-of-file or if an error
occurred.

@param dirstream The directory being read.
@retval A freshly populated dirent structure, dirstream is also updated with current information.
*/
struct ee_dirent *ee_readdir (ee_DIR *dirstream)
{
	ee_FILE *file;
	static struct ee_dirent ent={NULL,0,0};
	static struct ee_dirent *ent_ptr;
	int pathlen;
	char *buf;
	char *fname;
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif

	/* 
	 * opendir leaves us at the first file.
	 * return this file, and set DIR to next file or NULL.
	 */
	if (!dirstream || (dirstream->pos==NULL)) return NULL;

	/* Return current file */
	file=dirstream->pos;
	buf=efn(file->name);
	if (ent.d_name) th_free(ent.d_name);
	ent.d_name=th_strdup(buf);
	ent.d_ino=file->fileno;
	ent.d_namlen=strlen(buf);
	/* return this to caller */
	ent_ptr = &ent;

	/* Search for next file. */
	pathlen=strlen(dirstream->pathname);
	while (file->next)
	{
		file=file->next;
		if (strncmp(dirstream->pathname,file->name,pathlen)==0)
		{
			buf=file->name;
			buf+=pathlen+1;
			fname=efn(buf);
			/** @todo Add support for directories as files. */
			if (buf==fname)
			{
				dirstream->pos=file;
				return ent_ptr;
			}
		}
	}
	dirstream->pos=NULL;
	return ent_ptr;
}
/** Close directory.

This function closes the directory stream dirstream. 
@param dirstream An open directory stream.
@retval Returns 0 on success and -1 on failure.
*/
int ee_closedir(ee_DIR *dirstream)
{
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif
	if (!dirstream) return -1;
	th_free(dirstream);
	return 0;
}

/** Rewind Directory.

The rewinddir function is used to reinitialize the directory stream dirstream, 
so that if you call readdir it returns information about the first entry in the directory again.

@param dirstream An open directory stream.
@return The caller dirstream points to the start entry.
*/
void ee_rewinddir (ee_DIR *dirstream)
{
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif
	if (!dirstream) return;
	dirstream->pos=dirstream->start;
}

/** Returns file information about file described by path.
@param filename File name to stat
@param buf Caller stat structure, data returned here.
@retval 0 success, -1 fail. Caller suplied stat structure. */
int ee_stat(const char *filename, struct th_stat *buf)
{
	ee_FILE *file=ee_find_file(filename);
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif

	if (!file || !buf)
	{
		ee_errno=EINVAL;
		return -1;
	}
	buf->st_size=file->size;
	buf->st_blksize=512;
	buf->st_blocks=file->size % 512;
	buf->st_mode=(unsigned short)file->mode;

	return 0;
}

/** Like stat, except if file is link, lstat returns information about link instead.
@note Test Harness is not supporting links, so this is equivalent to ee_stat.
*/
int ee_lstat(const char *filename, struct th_stat *buf)
{
	return ee_stat(filename,buf);
}
/** Returns info on file opened by open, see fdopen */
int ee_fstat(int fildes, struct th_stat *buf)
{
	ee_FILE *file=ee_find_fildes(fildes);
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif
	if (!file || !buf)
	{
		ee_errno=EINVAL;
		return -1;
	}
	buf->st_size=file->size;
	buf->st_blksize=512;
	buf->st_blocks=file->size % 512;
	buf->st_mode=(unsigned short)file->mode;

	return 0;
}
/** Unlink a file, delete after all callers have closed the file.

The unlink() function removes a link  to  a  file.  If  path
names  a  symbolic  link, unlink() removes the symbolic link
named by path and does not  affect  any  file  or  directory
named  by  the  contents  of  the symbolic link.  Otherwise,
unlink() removes the link named by the pathname  pointed  to
by path and decrements the link count of the file referenced
by the link.

@note We are supporting multiple opens, but not symlinks/hardlink.
@note This is included from thunistd.h

@param filename path name of file.
@retval 0 success.  Otherwise, -1 is returned,  ee_errno  is set.
*/
int ee_unlink(const char *filename)
{
	return ee_fclose(ee_find_file(filename));
}
/** link  creates  a  new  link  (also known as a hard link) to an existing file.

If newpath exists it will not be overwritten.

This new name may be used exactly as the old  one  for  any  operation;
both names refer to the same file (and so have the same permissions and
ownership) and it is impossible to tell which name was the original.

@param oldpath The existing file.
@param newpath The new link
@retval On  success,  zero is returned.  On error, -1 is returned, and ee_errno is
set appropriately.
*/
int ee_link(const char *oldpath, const char *newpath)
{
	return -1;
}

/** FOPEN() - Open a file. */
ee_FILE *ee_fopen (const char *filename, const char *mode)
{
    ee_FILE *file;
	int      flags;
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif

    /* Verify mode */
	if ((flags=ee_checkmode(filename,mode))==0)
    {
        ee_errno = EINVAL;
        return NULL;
    }
	
    /* Find the file in the filesystem, find file will resolve */
    
    if ((file = ee_find_file(filename)) == NULL)
    {
		if ((strchr(mode,'r')) || ((file=ee_fcreate(filename,mode,NULL,MAX_FILESIZE))==NULL))
		{
			ee_errno = ENOENT;
			/*	__eeserr(file);*/
			return NULL;
		}

    }

    /* Init ee_FILE stream */
    file->status   = F_OPEN;
    file->pos      = file->start;
    file->end      = file->start + file->size;
	file->_flags= (flags | (file->_flags & __eeSTICKYMASK));
	if ((strchr(mode,'w')) != NULL)
	{
		file->size = 0;
	}
	__eeclearerr(file);
    return (file);
}
/** OPEN() - Open a file. 
@param pathname Name of file.
@param flags flags  is  one  of  O_RDONLY,  O_WRONLY or O_RDWR with 
the following qualifiers:
- O_CREAT If the file does not exist it will be created.  The owner
(user ID) of the file is set to the effective user ID of the process. 
- O_EXCL When used with O_CREAT, if the file already exists it is an
error and the open will fail.  In this context, a symbolic link exists,
regardless of where its points to.  
- O_TRUNC If the file already exists and is a regular file and the open
mode allows writing (i.e., is O_RDWR or O_WRONLY) it will be truncated
to length 0.  
- O_APPEND The file is opened in append mode.  Before each write, the
file pointer is positioned at the end of the file, as if with lseek. 

There are several more, but they are not relevant.
@retval New file descriptor or -1 on error.
*/
int ee_open(const char *pathname, int flags)
{
	ee_FILE *file;
	char 	*mode="rb";
	
	if (!pathname || !*pathname)
		return -1;
	
	/** @todo Set mode based on flags. */

	if ((file=ee_fopen(pathname,mode))==NULL)
		return -1;
	else
		return file->fileno;
}


	

/** FDOPEN() - Associate a stream with a given file descriptor */
ee_FILE *ee_fdopen(int fildes, const char *mode)
{
	ee_FILE *file;

	if ((file=ee_find_fildes(fildes))==NULL)
		return NULL;
	else
		return ee_fopen(file->name,mode);
}
/** Close passed file, and open new file per filename. 
The freopen function opens the file whose name is the string pointed to
by path and associates the stream pointed to by stream  with  it.   The
original  stream  (if  it exists) is closed.  The mode argument is used
just as in the fopen function.  The primary use of the freopen function
is  to  change the file associated with a standard text stream (stderr,
 stdin, or stdout).
*/
ee_FILE *ee_freopen (const char *filename, const char *mode, ee_FILE *fp)
{
	ee_fclose(fp);
	fp=ee_fopen(filename,mode);
	return fp;
}
/** SCANF() input format conversion. 
This is here for compatibility, it doesn't make much sense for
embedded without input buffering.
*/
int ee_scanf(const char *fmt, ...)
{
	int rv;
	va_list args;
	ee_FILE *fp = ee_stdin;
 
	va_start( args, fmt );
	rv = ee_svfscanf(fp, fmt, args); 
	va_end( args );
	return rv;
}
/** FSCANF() input format conversion. */
int ee_fscanf(ee_FILE *fp,const char *fmt, ...)
{
   int rv;
   va_list args;
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif
 
   va_start( args, fmt );
   rv = ee_svfscanf(fp, fmt, args); 
   va_end( args );
   return rv;
}
/* VSCANF() input format conversion.
This is here for compatibility, it doesn't make much sense for
embedded without input buffering.
@note This is not standard in all libc's, glibc yes.
*/
int ee_vscanf(const char *fmt, va_list args)
{
	ee_FILE *fp = ee_stdin;
	return ee_svfscanf(fp, fmt, args);
}

/** If internal scanf file created, force I/O to harness in doscan ee_svfscanf. */
int ee_use_internal_fileio = 0;
/** Internal scanf file mode. */
static const char *ee_strfilemode = "rb";
/** Internal scanf file name, used as key for destructor. */
static const char *ee_strfilename = "sscanf";

/** Create scanf string file. 
@param str String to load into a file.
@retval malloc'ed internal file (caller may use free)
*/
static ee_FILE *ee_createstrfile(const char *str)
{
	ee_FILE *fp;
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif
	if (!str) return NULL;
	fp = th_malloc(sizeof(*fp));
	fp->next=NULL;
	fp->start=th_strdup(str);
	fp->pos=fp->start;
	fp->size=strlen(str);
	fp->end = fp->start + fp->size;
	fp->girth = fp->size;
	strcpy(fp->name,ee_strfilename);
	fp->mode = F_READABLE;
	fp->status = F_OPEN;
	fp->_flags = ee_checkmode(fp->name,ee_strfilemode);
	fp->fileno=(ee_ino_t)~0;
	ee_use_internal_fileio = 1;
	return fp;
}
/** Destroy scanf string file. 
@param fp 
@retval 0 Success, 1 EINVAL, 2 File key mismatch.
*/
static int ee_destroystrfile(ee_FILE *fp)
{
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif
	if (!fp)
		return 1;
	if (strcmp(fp->name,ee_strfilename))
		return 2;
	th_free(fp->start);
	th_free(fp);
	ee_use_internal_fileio = 0;
	return 0;
}
/** SSCANF() input format conversion. */
int ee_sscanf(const char *str,const char *fmt, ...)
{
	va_list	args;
	int	rv;
	ee_FILE *fp = ee_createstrfile(str);

	va_start( args, fmt );
    rv = ee_svfscanf(fp, fmt, args); 
    va_end( args );
	ee_destroystrfile(fp);
    return rv;

}
/** Scan file for matching string.
@note This is not standard in all libc's, glibc yes 
*/
int ee_vfscanf (ee_FILE *fp, const char* fmt, va_list args)
{
	return ee_svfscanf(fp,fmt,args);
}
/** Scan string for formatted input. */
int ee_vsscanf(const char *str, const char *fmt, va_list args)
{
	ee_FILE *fp = ee_createstrfile(str);
	int rv=ee_svfscanf(fp, fmt, args);
	ee_destroystrfile(fp);
	return rv;
}

/* Process I/O */

/** Create a process, invoke shell with -c option, and execute command.
Stub routine in this release (return NULL). 
@todo Next level is to combine with an
execl function for required commands. Integrate with mode bits and filesystem.
@param command Command line to process.
@param type Read or Write (r|w)
@retval FILE or NULL failure.
*/
ee_FILE	*ee_popen(const char *command, const char *type)
{
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif
	command=command;
	type=type;
	return NULL;
}
/** Wait for created process to terminate (wait4).
Stub routine in this release.
@param fd File created with popen.
@retval -1 for failure
*/
int		ee_pclose(ee_FILE *fd)
{
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif
	fd=fd;
	return -1;
}

/** Set file position. */
ee_off_t ee_lseek(int fildes, ee_off_t offset, int whence)
{
	return ee_fseek(ee_find_fildes(fildes),offset,whence);
}

/** Set file position.
-# SEEK_SET---<[offset]> is the absolute file position (an offset
from the beginning of the file) desired.  <[offset]> must be positive.

-# SEEK_CUR---<[offset]> is relative to the current file position.
<[offset]> can meaningfully be either positive or negative.

-# SEEK_END---<[offset]> is relative to the current end of file.
<[offset]> can meaningfully be either positive (to increase the size
of the file) or negative.
*/
int ee_fseek (ee_FILE *file, long offset, int whence)
{
    char   *new_pos;
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif

    /* If ee_FILE pointer unset or file not open, error */
    if ( ( !file ) || ( file->status != F_OPEN ) )
    {
        ee_errno  = EBADF;
		__eeserr(file);
        return (-1);
    }

    switch (whence)
    {
        case SEEK_SET:
            /* SEEK_SET - from beginning of file */
            /* Make sure we stay in bounds */
            if ( (offset < 0 ) || ( offset >= (long)file->girth ) )
            {
                ee_errno  = ERANGE;
				__eeserr(file);
                return (-1);
            }
            else
            {
                file->pos = file->start + offset;

                if (file->pos > file->end)
                {
                    file->end = file->pos;
                }
                file->size = file->end - file->start;
				__eeclearerr(file);
                return(0);
            }
            /* break; returns from here */

        case SEEK_CUR:
            /* SEEK_CUR - from current file position */
            /* Make sure we stay in bounds */
            new_pos = file->pos + offset;

            if ( ( new_pos < file->start ) ||
                 ( new_pos >= (file->start + file->girth) ) )
            {
                ee_errno  = ERANGE;
				__eeserr(file);
                return(-1);
            }
            else
            {
                file->pos = new_pos;

                if (file->pos > file->end)
                {
                    file->end = file->pos;
                }
                file->size = file->end - file->start;

				__eeclearerr(file);
                return(0);
            }
            /* break; returns from here */
    
        case SEEK_END:
            /* SEEK_END - from end of file */
             new_pos = file->end + offset;

             if ( (new_pos < file->start) ||
                  (new_pos >= file->start + file->girth) )
            {
                ee_errno  = ERANGE;
				__eeserr(file);
                return(-1);
            }
            else
            {
                file->pos = new_pos;
                if (file->pos > file->end)
                {
                    file->end = file->pos;
                }
                file->size = file->end - file->start;

				__eeclearerr(file);
                return(0);
            }
            /* break; returns from here */

        default:
            /* Bad mode */
            ee_errno  = EINVAL;
			__eeserr(file);
            return (-1);
            /* break; returns from here */
    }
}
/** Return position in stream or file.*/
long ee_ftell (ee_FILE *file)
{
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif
	/* If ee_FILE pointer unset or file not open, error */
    if ( ( !file ) || ( file->status != F_OPEN ) )
    {
        ee_errno  = EBADF;
		__eeserr(file);
        return (-1);
    }
	return (file->pos-file->start);
}

/** Read count bytes from file. 
@param fd File to read.
@param buf data buffer
@param count number of bytes to read.
@retval number of bytes read, or 0 for error.
*/
size_t ee_read(int fd, void *buf, size_t count)
{
	return ee_fread(buf,count,1,ee_find_fildes(fd));
}

/** Read nelem elements of size from file.
@param ptr Data buffer read.
@param size Size of element.
@param nelem Number of elements to read
@param file File to read from.
@retval number of items successfully read (i.e.,  not the number of characters).
If an error occurs, or the end-of-file is reached, the return value is a short
item  count  (or zero).
@remark fread  does  not distinguish between end-of-file and error, and callers
must use feof(3) and ferror(3) to determine which occurred.
*/
size_t ee_fread (void *ptr, size_t size, size_t nelem, ee_FILE *file)
{
    size_t bytes_to_read;
    size_t num_readable;
    size_t num_desired;
    size_t retval;
#if		!HAVE_MEMCPY && !HAVE_BCOPY
    char *buff;
#endif
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif

    /*
     *  Assert error if:
     *    - ee_FILE ptr not valid
     *    - ee_FILE not open
     *    - ee_FILE not readable
     */
    if ((!file) || (file->status != F_OPEN))
    {
        ee_errno = EBADF;
		__eeserr(file);
        return (0);
    }

    if (!(file->mode & F_READABLE))
    {
        ee_errno = EACCES;
		__eeserr(file);
        return (0);
    }


    /* Determine how many bytes can be read, and how many are requested */
    num_readable = (file->end - file->pos);
    num_desired  = (nelem * size);

    /* Have they asked for more than we can read? */
    if ( num_desired > num_readable )
    {
        /* Determine how many elements we CAN read */
        retval        = ( num_readable / size );
        bytes_to_read = ( retval * size );
    }
    else
    {
        bytes_to_read = num_desired;
        retval        = nelem;
    }

    /* If there is something to read, do it */
    if ( retval > 0 )
    {
#if		HAVE_MEMCPY || HAVE_BCOPY
		/* convert memcpy to bcopy if available. */
		memcpy(ptr,file->pos,bytes_to_read);
		file->pos += bytes_to_read;
#else
        buff = (char *)ptr;
        while (bytes_to_read--)
			*buff++ = *(file->pos++);
#endif
    }
	if (file->pos == file->end) __eeseof(file);
    return (retval); 
}

/** Put one character to file.*/
int ee_putc ( int c, ee_FILE *file )
{
    char ch;

    ch = (char)c;

    if (!(ee_fwrite(&ch, sizeof(ch), 1, file)))
    {
		__eeseof(file);
        return (EOF);
    }
    else
    {
        return (c);
    }
   
}

/** Get character from file.*/
int ee_getc( ee_FILE *file )
{
    char ch;

    if (!(ee_fread(&ch, sizeof(ch), 1, file)))
    {
		__eeseof(file);
        return (EOF);
    }
    else
    {
        return ((int)(ch & 0xff));
    }
}

/** Push character back into the file.*/
int	ee_ungetc(int ch, ee_FILE *file)
{
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif

    /*
     *  Assert error if:
     *    - ee_FILE ptr not valid
     *    - ee_FILE not open
     *    - ee_FILE not readable
	 *
	 * NOTE: This is supposed to push a character back into the file.
	 *       This fails on read/only files, and since we are ROM based
	 *       it could significantly increase the RAM requirements.
	 *       If the file is "rb", just decrement the file position.
     */

    if ((!file) || (file->status != F_OPEN))
    {
        ee_errno = EBADF;
		__eeserr(file);
        return (0);
    }

    if (!(file->mode & F_READABLE))
    {
        ee_errno = EACCES;
		__eeserr(file);
        return (0);
    }

	/* Push character back onto stream, IF FILE IS WRITEABLE, OTHERWISE DON'T WRITE */
	if (file->pos == file->start) return (0);
	if ((file->mode & F_WRITEABLE)) *(--file->pos) = (char)ch;
	else --file->pos;

	return (1);
}

/** `fputs'  writes  the string at S (but without the trailing null) to fp.
@param s character string to write
@param fp File to write to.
@retval If successful, the result is `0'; otherwise, the result is `EOF'.
*/
int ee_fputs(const char *s, ee_FILE *fp)
{
	return (ee_fwrite(s,strlen(s),1,fp) ? 0 : EOF);
}
/** Test if getc just read the start of a CRLF sequence. */
static int ee_wasCRLF(ee_FILE *fp)
{
	char	*prevpos=fp->pos;
	int		 rv=0;

	prevpos--;
	if ((*prevpos == '\r') && (*(fp->pos) == '\n'))
		rv=1;
	return rv;
}

/** Get string of length count from file.
Old routine, but still used. Only difference for us is that it strips eol 
characters, and unfortunately several benchmarks rely upon this.

  `fgets' should replace all uses of `gets'. Note  however  that  `fgets'
returns  all  of  the  data,  while `gets' removes the trailing newline
(with no indication that it has done so.)
*/
char *ee_gets(char *string,int count,ee_FILE *fp)
{
	char *pointer=string;
	if (ee_fgets(pointer,count,fp))
		strip_t_crlf(pointer);
	return pointer;
}

/** Get string of length count from file.
`fgets'  returns  the  buffer passed to it, with the data filled in. If
end of file occurs with some data  already  accumulated,  the  data  is
returned  with  no  other  indication.  If  no  data  are read, NULL is
returned instead.

@note Returns are compatible with VC and Unix V7
@note We need to convert CRLF to LF in this routine. The determination
of a text file is more sophisticated than file mode, and so we will assume
binary in other external routines. LIBC's usually do this conversion during
buffer reading.
*/
char *ee_fgets(char *string,int count,ee_FILE *fp)
{
	ee_FILE *stream;
	char *pointer = string;
	char *rv = string;
	int ch;
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif

	if ((count <= 0) ||
		(string == NULL) ||
		(fp == NULL))
		return(NULL);

	stream = fp;

	while (--count)
	{
		if ((ch = ee_getc(stream)) == EOF)
		{
			if (pointer == string)
			{
				rv=NULL;
				goto done;
			}

			break;
		}
		/* skip CRLF's, by dropping CR, now Unix EOL format. */
		else if (!ee_wasCRLF(stream))
		{
			if ((*pointer++ = (char)ch) == (char)('\n'))
				break;
		}
	}

	*pointer = (char)('\0');
done:
	return(rv);
}

/** Extend file by allocation block size.
@param fp File to extend
@retval Number of writeable bytes after extension applied.
*/
static size_t ee_extend(ee_FILE *fp)
{
	size_t	tmpgirth;
	size_t	posoffset,endoffset;
	char	*buf;
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif

    if (!(fp->mode & F_WRITEABLE))
    {
        ee_errno = EACCES;
		__eeserr(fp);
        return (0);
    }

	tmpgirth=fp->girth + TH_FILE_ALLOCATION_BLOCKSZ;
	/* harness traps out of memory */
	buf=th_realloc(fp->start,tmpgirth);

	/* To debug CRC errors on file->size, initialize realloc area to non-zero
	memset(buf + fp->girth,0xA5,TH_FILE_ALLOCATION_BLOCKSZ);
	*/

	posoffset = fp->pos - fp->start;
	endoffset = fp->end - fp->start;

	/* Reset file positions based on new start in buf */
	fp->girth = tmpgirth;
	fp->start = buf;
	fp->pos = buf + posoffset;
	fp->end = buf + endoffset;
	return fp->girth - (fp->pos - fp->start);
}

/** Write count bytes to file.
@param fd File to write
@param buf Data to write
@param count Number of bytes to write
@retval Number of bytes written, or 0
*/
size_t ee_write(int fd, const void *buf, size_t count)
{
	return ee_fwrite(buf,count,1,ee_find_fildes(fd));
}

/** Write elements of size to file.
@param ptr Data to write.
@param size Size of element.
@param nmemb Number of elements
@param file File to write.
@retval Number of elements written or 0.
*/
size_t ee_fwrite (const void *ptr, size_t size, size_t nmemb, ee_FILE *file)
{
    size_t    bytes_to_write;
    size_t    num_writeable;
    size_t    num_desired;
    size_t    retval;
#if		!HAVE_MEMCPY && !HAVE_BCOPY
    char *buff;
#endif
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif

    /** @remark
     *  Assert error if:
     *    - ee_FILE ptr not valid
     *    - ee_FILE not open
     *    - ee_FILE not writeable
     */

    num_desired   = ( nmemb * size );
	/** Ghostscript tiffg4 driver calls with void, size 0. */
	if (!ptr)
	{
		if (num_desired)
		{
			ee_errno = EINVAL;
			__eeserr(file);
		}
		return (0);
	}

    if ((!file) || (file->status != F_OPEN))
    {
        ee_errno = EBADF;
		__eeserr(file);
        return (0);
    }

    if (!(file->mode & F_WRITEABLE))
    {
        ee_errno = EACCES;
		__eeserr(file);
        return (0);
    }

	/* 
	 * Check for stdio files, re-route to th_printf 
	 * Not sure what to do with stdin in embedded environment,
	 * fall through return 0 until we have a defined need for this.
	 */
	if ((file==ee_stdout) || (file==ee_stderr))
	{
		size_t len;
		char *strbuf=th_malloc(num_desired+1);
		if(!strbuf) {
			ee_errno = ENOMEM;
			__eeserr(file);
			return 0;
		}
		strncpy(strbuf,ptr,num_desired);
		strbuf[num_desired]='\0';
		/* don't use puts, it appends a newline. */
		th_printf("%s",strbuf);
		len=strlen(strbuf);
		th_free(strbuf);
		return len;
	}

	/** 
	 * Calculate writeable size.
	 * @todo realloc file based on allocation block size when
	 * we overfill it.
	 */
	num_writeable = file->girth - (file->pos - file->start);

	/* retval result is the number of complete elements that `fwrite' copied to the file.*/
    if ( num_desired > num_writeable )
    {
		num_writeable = ee_extend(file);
		if ( num_desired > num_writeable )
		{
			/* Determine how many elements we can write */
			bytes_to_write  = num_writeable / size;
			retval          = bytes_to_write;
			bytes_to_write *= size;
		}
		else
		{
        bytes_to_write = num_desired;
        retval         = nmemb;
		}
    }
    else
    {
        bytes_to_write = num_desired;
        retval         = nmemb;
    }
 
    /* If there is something to write, do it */
    if ( retval > 0 )
    {
#if		HAVE_MEMCPY || HAVE_BCOPY
		/* convert memcpy to bcopy if available. */
		memcpy(file->pos,ptr,bytes_to_write);
		file->pos += bytes_to_write;
#else
		buff = (char *)ptr;
		while (bytes_to_write--)
			*(file->pos++) = *buff++;
#endif

		if (file->pos > file->end)
			file->end = file->pos;
		file->size = file->end - file->start;
    }

  return (retval);

}

/** Write formatted argument list to file */
int ee_vfprintf (ee_FILE *fp, const char* format, va_list args)
{
	static char	buf[1024];
	th_vsprintf(buf,format,args);
	return ee_fwrite(buf,strlen(buf),1,fp);
}

/** Write printf format string to file.*/
int ee_fprintf (ee_FILE* fp, const char* format, ...)
{
   int rv;
   va_list args;
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif
   va_start( args, format );
   rv = ee_vfprintf( fp, format, args );
   va_end( args );
   return rv;
}

/** Create a writeable temporary file. */
ee_FILE *ee_tmpfile (void)
{
    ee_FILE *fp;
	char	buf[10];
	int		i;
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif

	/* Always create a new file up to 10 */
	for (i=0;i<10;i++)
	{
		th_sprintf(buf,"%d",i);
		if ((fp = ee_find_file(buf)) != NULL )
		{
			/* Reuse tmp file if it has been closed */
			if (fp->status == F_CLOSED) return ee_fopen(buf,"wb");
		} else break;
	}
	/* Create a new tmp file */
	if (i == 9) 
	{
		th_printf("ERROR ee_tmpfile: too many tmp files open\n");
		return (ee_FILE *) NULL; /* too many tmp files */
	}
	ee_fcreate(buf,"wb",NULL,MAX_FILESIZE);
	return ee_fopen(buf,"wb+");
}
/** Unique ID for ee_mktemp.
Most OS's return as a function of getpid, and deal with collisions. 
In our case, we can more simply return a
number that is incremented each time. */
static e_s32 ee_mktempID = 0;

/** Return a unique temporary file name based on 6 X's in user template */
char    *ee_mktemp  (char *templat)
{
	char *s = templat;
	int  countX = 0;
	int  mktempID;
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif
	
	if (!templat || !*templat) return NULL;

	mktempID = ee_mktempID++;
	
	/* find end of string */
	while (*s) s++;
	/* Replace 6 X's, we aren't minimizing collisions */
	while ((--s >= templat) && (*s == 'X'))
	{
		countX++;
		*s = (char)((mktempID % 10) + '0');
		mktempID /= 10;
	}
	/* File should not exist */
	if ((countX < 6) || ((ee_find_file(templat))!=NULL))
		return(NULL);
	else
		return templat;
}

/*
 * Utilities used by API calls
 */

/** find a file given an unresolved or resolved filename */
static ee_FILE *ee_find_file (const char *filename)
{   
    ee_FILE   *file;
	char      *fname;
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif

	/* Trap stdio files */
	if (strcmp(filename,"stdin") == 0) return ee_stdin;
	if (strcmp(filename,"stdout") == 0) return ee_stdout;
	if (strcmp(filename,"stderr") == 0) return ee_stderr;

	file = ee_filelist;
	fname = ee_fname_resolver(filename);
    while (file != NULL)
    {
        if (strcmp(fname, file->name) == 0)
		{
			th_free(fname);
            return (file);
		}
		file = file->next;
    }

	th_free(fname);
    /* If we get here, we didn't find the file in the filesystem */
    return (ee_FILE *)0;
}
/** find a file given an unresolved or resolved filename */
static ee_FILE *ee_find_fildes (int fildes)
{   
    ee_FILE   *file;
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif

	/* Trap stdio files */
	if (fildes == 0) return ee_stdin;
	if (fildes == 1) return ee_stdout;
	if (fildes == 2) return ee_stderr;

	file = ee_filelist;
    while (file != NULL)
    {
        if (file->fileno == (ee_ino_t)fildes)
            return (file);
		file = file->next;
    }

    /* If we get here, we didn't find the file in the filesystem */
    return NULL;
}
/** find a file given an unresolved or resolved filename */
static ee_FILE *ee_find_fp (ee_FILE *fp)
{   
    ee_FILE   *file = ee_filelist;
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif

	if (!fp) return NULL;

	/* Trap stdio files */
	if (fp == ee_stdin) return fp;
	if (fp == ee_stdout) return fp;
	if (fp == ee_stderr) return fp;

    while (file != NULL)
    {
        if (file == fp)
            return (fp);
		file = file->next;
    }

    /* If we get here, we didn't find the file in the filesystem */
    return NULL;
}

/** find the last file in filesystem, and set fileno. */
static ee_FILE *ee_last_file (void)
{
	ee_FILE	*file;
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif
	if (ee_filelist == NULL)
	{
		ee_filelist = th_malloc(sizeof(ee_FILE));
		if (ee_filelist == NULL)
			th_exit(THE_OUT_OF_MEMORY,"fileio ee_last_file: could not create new filelist\n");
		/* The first fileno */
		ee_filelist->fileno = 3;
		return ee_filelist;
	}
	file = ee_filelist;
	while (file->next != NULL) file=file->next;
	if ((file->next = th_malloc(sizeof(ee_FILE))) == NULL)
			th_exit(THE_OUT_OF_MEMORY,"fileio ee_last_file: could not create new filelist\n");
	/* Set the fileno */
	((ee_FILE *)file->next)->fileno = (ee_ino_t)file->fileno+1;
	return file->next;
}

void ee_destroy_filelist (void)
{
	ee_FILE	*file,*dfile;
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif
	if (ee_filelist == NULL)
		return;

	file = ee_filelist;
	while (file != NULL) {
		dfile=file;
		file=file->next;
		if (((dfile->_flags & __eeALLOC) != 0) &&
			dfile->start)
			th_free(dfile->start);
		th_free(dfile);
	}
	ee_filelist=NULL;
}

/** non-standard: compares 2 files (are they identical?)
 *@param file1 - First input file
 *@param file2 - Second input file
 *@retval Returns 0  if they are exactly the same, Returns -1 if they are different in any way.
 */
int ee_filecmp(const char *file1, const char *file2)
{

    int    i;
    ee_FILE   *f1;
    ee_FILE   *f2;
#if (EE_DEBUG_FIO)
	ee_fio_dbg(__FILE__,__LINE__,__FUNCTION__);
#endif

    /* Get the files' entries in the filesystem */
    f1 = ee_find_file(file1);
    f2 = ee_find_file(file2);

    /* If we didn't find the files, error out */
    if ( ( f1 == NULL ) || ( f2 == NULL ) )
    {
        return(-1);
    }

    /*
     * Ideally we'd use an API to look at the file size
     * and file contents, but cheat here and dip directly
     * into the file structure's internals.
     */

    /* Make sure files are the same size */
    if ( ee_fsize(file1) != ee_fsize(file2) )
    {
        return(-1);
    }

    /* See if the contents are identical */
    i = memcmp((const void *)f1->start,
               (const void *)f2->start,
               f1->size);

    /* Any non-match becomes retval of -1 */
    if (i)
    {
        i = -1;
    }

    return (i);

}

/** Non-Standard C routine to get file size */
ee_fsize_t	ee_fsize(const char *filename)
{
	ee_FILE *fp;
	if ((fp = ee_find_file(filename)) == NULL) return 0;
	return fp->size;
}

/* exec commands related to harness file system */

/** Get list of files for directory. */
#define MAX_DIR 100

static char **loadDirlist(const char *name)
{
	char **dirlist;
	int i=0;
	ee_DIR *dir;
	struct ee_dirent *d;
	char fullname[FILENAME_MAX];
	char *needslash="";

	if ((dirlist = (char **)th_malloc(MAX_DIR*sizeof(dirlist[0])))==NULL)
		return NULL;

	if ((dir = th_opendir(name))==NULL)
	{
		th_free(dirlist);
		return NULL;
	}
	needslash = ((name[strlen(name)-1] == '/') ? "" : "/");
	while ((d=th_readdir(dir))!=0) 
	{
		char *dname = d->d_name;
		if (dname[0] == '.')
			continue;
		th_sprintf(fullname,"%s%s%s",name,needslash,dname);
		dirlist[i] = th_strdup(dname);
		if (!dirlist[i])
		{
			th_printf("Out of memory loading directory list %s\n",name);
			return NULL;
		}
		i++;
		if (i == MAX_DIR-1)
			break;
	}
	dirlist[i] = NULL;

	th_closedir(dir);

	return dirlist;
}
static void freeDirlist(char **list)
{
	int i;
	if (!list) return;
	/* 
	 * Null terminated list of entries. 
	 * The values after first null cannot be free'ed.
	 */
	for (i=0;i<MAX_DIR && list[i];i++)
		th_free(list[i]);
	th_free(list);
}

/** exec ls processor. */
void ee_exec_ls(const char *args)
{
	char **dirlist;
	int 	i=0;
	int		nofree;
	/* Initial single function. process args later. */
	char *slash="/";
	char *dname;

	if ((nofree=is_all_white_space(args))!=0)
		dname=slash;
	else
	{
		dname=th_strdup(args);
		strip_l_spaces(dname);
	}

	dirlist=loadDirlist(dname);
	if (!dirlist || !*dirlist) 
	{
		th_printf("No such file or directory\n");
		return;
	}
	while (dirlist[i])
	{
		th_printf("%s/%s ",dname,dirlist[i]);
		i++;
	}
	th_printf("\n");
	if (!nofree)
		th_free(dname);
	freeDirlist(dirlist);
}

/** @} */
/** @} */
