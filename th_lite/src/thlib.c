/**
 * @file
 * @brief  TH_Lite Library Routines
 * 
 *$RCSfile: thlib.c,v $
 *
 *  EEMBC : EEMBC Technical Advisory Group (TechTAG)
 *
 * @author  Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.70 $
 *          $Date: 2005/12/02 23:53:37 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/techtag/th_lite/src/thlib.c,v $
 *          
 * @note   
 *
 *
 * HISTORY :
 *
 * $Log: thlib.c,v $
 * Revision 1.70  2005/12/02 23:53:37  rick
 * Fix mixed EOL format causing ^M's to appear in Unix checkouts.
 *
 * Revision 1.69  2005/09/10 04:02:24  rick
 * eol update, add uu_send_file
 *
 * Revision 1.68  2005/07/16 19:52:16  rick
 * Add monstart/stop profiling
 *
 * Revision 1.67  2005/04/27 20:33:15  rick
 * Copyrite update 2005
 *
 * Revision 1.66  2004/12/08 23:27:19  rick
 * New standard header for documentation generation.
 *
 * Revision 1.65  2004/11/19 22:27:13  rick
 * Return *va_list from createvalist for compiler portability.
 *
 * Revision 1.64  2004/10/26 22:01:16  administrator
 * Fix write->th_write redirection, add portable va_list creation
 *
 * Revision 1.63  2004/09/23 00:57:05  rick
 * Add trap for printf inside timing loop.
 *
 * Revision 1.62  2004/09/13 19:30:15  rick
 * Add th_read, th_write, and th_lseek
 *
 * Revision 1.61  2004/08/09 21:38:01  rick
 * Bug 277: al_exit called with too few parameters.
 *
 * Revision 1.60  2004/08/09 20:23:06  rick
 * Add th_open, clear warnings from stdio/threent
 *
 * Revision 1.59  2004/07/08 03:42:53  rick
 * Add th_close call.
 *
 * Revision 1.58  2004/07/03 03:13:40  rick
 * Add time, link, and exit to redirection.
 *
 * Revision 1.57  2004/07/01 17:37:27  rick
 * Add th_crcbuffer, and place all redirection includes inside file sentinel.
 *
 * Revision 1.56  2004/06/29 19:36:46  rick
 * EE_REDIRECT, and Shared file for Regular and Lite
 *
 * Revision 1.55  2004/06/23 05:55:05  rick
 * EE_REDIRECT, and Shared Files
 *
 * Revision 1.54  2004/06/22 14:31:49  rick
 * Move add_version from thlib to thfl.
 *
 * Revision 1.53  2004/06/14 18:03:32  rick
 * Bug 274: Precision in log files is not large enough for reporting results on simulators.
 *
 * Revision 1.52  2004/05/07 22:45:56  rick
 * Match Heap manager in harnesses, move internal routines to thfl.c
 *
 * Revision 1.51  2004/05/06 21:15:48  rick
 * Fix th_strdup for heap, and epn NULL return to 0 string
 *
 * Revision 1.50  2004/04/15 16:46:06  rick
 * fread/fwrite rv, size, and count to size_t
 *
 * Revision 1.49  2004/03/19 21:15:44  rick
 * Fix uuencode table, move th_send_buf_as_file to thlib.c
 *
 * Revision 1.48  2004/03/10 00:18:29  rick
 * Add scanf family, vfprintf, and new doscan
 *
 * Revision 1.47  2004/02/20 00:24:43  rick
 * change ee_dirent from typedef to struct
 *
 * Revision 1.46  2004/02/13 18:31:33  rick
 * Bug 243: Test harness lite doesn't compile if HAVE_ASSERT_H is FALSE.
 *
 * Revision 1.45  2004/02/12 23:35:03  rick
 * Add fputs, macro fixes to thstdio
 *
 * Revision 1.44  2004/02/11 02:56:08  rick
 * Add macro redefinitions, improve efn and fileio
 *
 * Revision 1.43  2004/02/10 06:55:37  rick
 * Add fileio calls and stdio re-router
 *
 * Revision 1.42  2004/02/05 23:15:56  rick
 * HAVE_MALLOC_H -> HAVE_MALLOC
 *
 * Revision 1.41  2004/02/05 23:03:49  rick
 * Harness update with portable dirent
 *
 * Revision 1.40  2004/01/28 23:08:31  rick
 * Add th_strdup, fileio cwd
 *
 * Revision 1.39  2004/01/22 00:57:49  rick
 * Release cleanup, copyright year corrections
 *
 * Revision 1.38  2004/01/19 22:55:50  rick
 * Remove 5 digit limitation to Iteration/Duration display
 *
 * Revision 1.37  2003/08/13 23:10:52  rick
 * Append TCDef BM version string after description
 *
 * Revision 1.36  2003/04/18 15:05:49  rick
 * Add ftell, vfscanf, vsscanf
 *
 * Revision 1.35  2003/04/11 22:13:10  rick
 * Add th_vsprintf, remove Go define
 *
 * Revision 1.34  2003/03/26 00:18:12  rick
 * Add scanf functions
 *
 * Revision 1.33  2003/03/06 00:34:53  rick
 * Add th_fgets, and %g to printf
 *
 * Revision 1.32  2003/03/05 00:28:58  rick
 * Change th_fcreate size to ee_fsize_t
 *
 * Revision 1.31  2003/02/03 21:54:27  rick
 * Bug #209: Fix MAP_MALLOC_TO_TH symbol
 *
 * Revision 1.30  2003/01/22 00:01:12  rick
 * Add File I/O to Regular
 *
 * Revision 1.29  2003/01/17 22:44:37  rick
 * Add File I/O to harness
 *
 * Revision 1.28  2003/01/03 18:09:13  rick
 * Add ee fileio to harness
 *
 * Revision 1.27  2002/12/31 16:21:01  rick
 * Add harness stubs for memmgr
 *
 * Revision 1.26  2002/08/12 19:07:17  rick
 * Rename cygwin toolchain to gcc
 *
 * Revision 1.25  2002/08/08 20:50:42  rick
 * Compile out command line -i (iterations) when CRC_CHECK enabled.
 *
 * Revision 1.24  2002/08/06 21:58:20  rick
 * Add NI CRC to TH Regular
 *
 * Revision 1.23  2002/07/26 20:53:16  rick
 * Add harness.h for Application overrides
 *
 * Revision 1.22  2002/07/19 19:29:24  rick
 * Replace eembc_id string with Benchmark ID
 *
 * Revision 1.21  2002/05/24 23:28:58  rick
 * Remove verify_float code if no float_support available
 *
 * Revision 1.20  2002/05/23 16:31:53  rick
 * Bug #169, #170, #172, #173: Char/assert fixes
 *
 * Revision 1.19  2002/05/22 17:55:26  rick
 * Replace assert.h with thassert.h, add assert functions to th lite.
 *
 * Revision 1.18  2002/05/21 19:18:33  rick
 * Abstract al_sprintf for compilers w/o vsprintf
 *
 * Revision 1.17  2002/05/15 15:04:17  rick
 * include stdio.h for vsprintf
 *
 * Revision 1.16  2002/05/14 19:12:22  rick
 * Add th_sprintf for bmdebug calls
 *
 * Revision 1.15  2002/04/23 21:37:42  rick
 * Bug #124: printf format
 *
 * Revision 1.14  2002/04/19 20:56:28  rick
 * Fix clock inconsistency with th regular vs. lite
 *
 * Revision 1.13  2002/04/12 21:31:25  rick
 * Remove cyclecount from th_report_results
 *
 * Revision 1.12  2002/04/03 23:18:46  rick
 * Clear warnings from gcc
 *
 * Revision 1.11  2002/03/18 21:15:09  rick
 * Add al_report, cyclecount, crc fix in iirflt, and pktflow.
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

/** @todo Drop these includes when thfl.c move is complete. */
#include <string.h>
#include <stdio.h>
#include "thlib.h"
#include "thal.h"
#include "thfl.h"
#include "uuencode.h"
#include "thassert.h"

/** @addtogroup THLFL
@{ */
/** @addtogroup thlib_c Test Harness Library Interface
@{ */

/** Portable method of creating the va_list we need without recursion. 
@note Must return pointer, some compilers cannot return arrays.
@param format Format string, and varaiable argument list.
@retval Pointer to static va_list.
*/
static va_list	*createvalist(const char *format,...)
{
	static va_list	args;
	va_start(args,format);
	return &args;
	va_end(args);
}
/** Number of calls to th_signal_start - calls to th_signal_finish. */
int		inside_timing_loop=0;
/** Flag to ignore th_printf's inside timing loop. */
int		ignore_inside_timing_loop=0;

/**
 * FUNC   : th_printf
 *
 * DESC   : The basic printf function. Does not need to be used in TH_Lite
 *
 * PARAMS : fmt - the classic printf format string, va's in stdarg.h
 */
int th_printf( const char *fmt, ... )
{
	int rv;
	va_list args;
	const char *err_inside_timing_loop = "Failure: Printf inside timing loop\n";

	if (inside_timing_loop && !ignore_inside_timing_loop)
	{
		/* Once is enough (i.e. uuencoding). */
		ignore_inside_timing_loop++;
		rv = al_printf(err_inside_timing_loop,
				*createvalist(err_inside_timing_loop));
	}
	va_start( args, fmt );
	rv = al_printf( fmt, args );
	va_end( args );
	return rv;
}

/**
 * FUNC   : th_sprintf
 *
 * DESC   : The basic sprintf function.
 *
 * PARAMS : fmt - the classic printf format string
 */
int th_sprintf( char *str, const char *fmt, ... )
{
   int rv;
   va_list args;
   va_start( args, fmt );
   rv = al_sprintf( str, fmt, args );
   va_end( args );
   return rv;
}
/**
 * FUNC   : th_vsprintf
 *
 * DESC   : The basic vsprintf function.
 *
 * PARAMS : fmt - the classic vprintf format string
 */
int    th_vsprintf( char *str, const char *fmt, va_list args )
{
	return al_sprintf( str, fmt, args );
}

/**
 * FUNC   : th_timer_available
 *
 * DESC   : used to determine if the duration timer is available.
 *
 * RETURNS: TRUE if the target supports the duration timer.
 *          FALSE if not
 */
int th_timer_available( void ) {return TARGET_TIMER_AVAIL;}

/**
 * FUNC   : th_timer_is_intrusive
 *
 * DESC   : used to determine if the timer function is intrusive.
 *
 *          Intrusive usually means that operating and maintaining the timer
 *          has a run time overhead.  For example, using a 10ms interrupt
 *          to incriment a timer value is intrusive because the interrupt
 *          service routine takes CPU time.
 *
 *          If an intrusive target timer is used to measure benchmarks, then
 *          its effect must be measured and taken into account.
 *
 *          Some target timers may not be intrusive.  For example, a target
 *          with a built in real time clock can measure time without an
 *          interrupt service routine.
 *
 *          Another way to build a non-intrusive timer is to cascade
 *          counter/timer circuits to get very large divisors.  For example,
 *          with a 20mhz system clock two 16bit timers could be cascaded to
 *          measure durations up to 3 minutes and 34 seconds before rolling
 *          over.
 *
 *    NOTE: If the timer is not avaialable, then this function returns
 *          FALSE.
 *
 *
 * RETURNS: TRUE if the target's duration timer is intrusive
 *          FALSE if it is not
 */
int th_timer_is_intrusive( void ) {return TARGET_TIMER_INTRUSIVE;}

/**
 * FUNC   : th_ticks_per_sec
 *
 * DESC   : used to determine the number of timer ticks per second.
 *
 * RETURNS: The number of timer ticks per second returned by th_stop_timer()
 */
size_t th_ticks_per_sec( void ) {return al_ticks_per_sec();}

/**
 * FUNC   : th_tick_granularity
 *
 * DESC   : used to determine the granularity of timer ticks.
 *
 *          For example, the value returned by th_stop_timer() may be
 *          in milliseconds. In this case, th_ticks_pers_sec() would
 *          return 1000.  However, the timer interrupt may only occur
 *          once very 10ms.  So th_tick_granularity() would return 10.
 *
 *          However, on another system, th_ticks_sec() might return 10
 *          and th_tick_granularity() could return 1.  This means that each
 *          incriment of the value returned by th_stop_timer() is in 100ms
 *          intervals.
 *
 * RETURNS: the granularity of the value returned by th_stop_timer()
 */
size_t th_tick_granularity( void ) {return al_tick_granularity();}

/**
 * FUNC   : th_signal_start()
 *
 * DESC   : Signals the host system the test has started
 *
 *          Calling this function signals the host system that the test
 *          has actually started.  The host uses this signal to begin
 *          measuring the duration of the test (bench mark).
 *
 *          If a target based timer is avaialable, this this function will
 *          also start the target's timer.
 */
void th_signal_start( void )
{
#ifdef  DO_PROFILE
        moncontrol(1);
#endif
	inside_timing_loop++;
	al_signal_start();
}

/**
 * FUNC   : th_signal_finished
 *
 * DESC   : Signals the host that the test is finished
 *
 *          This function is called to signal the host system that the
 *          currently executing test or benchmark is finished.  The host
 *          uses this signal to mark the stop time of the test and to
 *          measure the duration of the test.
 *
 * RETURNS: The duration of the test in 'ticks' as measured by the target's
 *          timer (if one is available).  If the target does not have a timer,
 *          or it is not supported by the TH, then this function returns
 *          TH_UNDEF_VALUE.
 *
 * NOTE   : There are intentionally no parameters for this function.  It is
 *          designed to have very low overhead. It causes a short message to
 *          be sent to the host indicating.  The results of the test are
 *          reported using another function.
 */
size_t th_signal_finished( void )
{
#ifdef  DO_PROFILE
        moncontrol(0);
#endif
	inside_timing_loop--;
	return al_signal_finished();
}

/**
 * FUNC   : th_exit
 *
 * DESC   : The benchmark code failed internally.
 *
 * RETURNS: Any error value supplied by the caller.
 * NOTE: differs from th_exit in that it returns exit code, and does
 *       not print unless windows example code.
 *       Add any signal code to aid debugging.
 * @note Keep in sync with thfl.c:t_exit. Exit cannot go through layers.
 */
void th_exit( int exit_code, const char *fmt, ... )
{
	va_list args;
	inside_timing_loop--;
	va_start( args, fmt );
	al_exit( exit_code, fmt, args );
	va_end( args );
}

/** 
 * Random Numbers (Uniform Distribution [0-128], 
 * use TH_RAND_MAX instead of stdlib.h RAND_MAX
 * @note Modified to promote thrand.c to shared file.
 */
int 	th_rand( void ) {return t_rand();}
/** Set random seed for th_rand. */
void	th_srand(unsigned int seed) {t_srand(seed);}

/** libc getenv Get Environment Variables */
char	*th_getenv(const char *key) {return al_getenv(key);}
/** libc getpid Get Process ID */
ee_pid_t th_getpid(void) {return al_getpid();}

/** @attention
 * File I/O section, standard C parameters, but fileio.h is used instead of stdio
 *
 * @note These could be done with #defines, but I chose to have symbols to be picked up
 * by the linker in case fileio.h conflicts with stdio.h
 */
int      th_fclose  (ee_FILE *fp) {return al_fclose (fp);}
int 	 th_open	(const char *pathname, int flags) {return al_open(pathname,flags);}
int      th_close   (int fildes)  {return al_close (fildes);}
size_t   th_read (int fd, void *buf, size_t count){return al_read(fd,buf,count);}
size_t	 th_write(int fd, const void *buf, size_t count){return al_write(fd,buf,count);}
ee_off_t th_lseek(int fildes, ee_off_t offset, int whence){return al_lseek(fildes,offset,whence);}
int      th_ferror  (ee_FILE *fp) {return al_ferror (fp);}
int      th_feof    (ee_FILE *fp) {return al_feof   (fp);}
void     th_clearerr(ee_FILE *fp) {al_clearerr (fp);}
int      th_fileno  (ee_FILE *fp) {return al_fileno   (fp);}
int      th_fflush  (ee_FILE *fp) {return al_fflush (fp);}
int      th_fprintf (ee_FILE *fp, const char* format, ...) 
{
   int rv;
   va_list args;
   va_start( args, format );
   rv = al_vfprintf( fp, format, args );
   va_end( args );
   return rv;
}
int      th_vfprintf(ee_FILE *fp, const char *format, va_list ap){return al_vfprintf( fp, format, ap );}
int      th_fseek  (ee_FILE *fp, long int offset, int whence) {return al_fseek   (fp,offset,whence);}
long     th_ftell  (ee_FILE *fp) {return al_ftell(fp);}


/* DIRENT routines, and helpers */

char      *th_getcwd   (char *buffer, size_t size){return al_getcwd(buffer,size);}
char      *th_getwd    (char *buffer){return al_getwd(buffer);}
int        th_chdir    (const char *filename){return al_chdir(filename);}
ee_DIR    *th_opendir  (const char *dirname){return al_opendir(dirname);}
struct ee_dirent *th_readdir  (ee_DIR *dirstream){return al_readdir(dirstream);}
int        th_closedir (ee_DIR *dirstream){return al_closedir(dirstream);}
void       th_rewinddir(ee_DIR *dirstream){al_rewinddir(dirstream);}
int        th_stat     (const char *path, struct th_stat *buf){return al_stat(path,buf);}
int        th_lstat    (const char *path, struct th_stat *buf){return al_lstat(path,buf);}
int        th_fstat    (int fildes, struct th_stat *buf){return al_fstat(fildes,buf);}
int        th_unlink   (const char *filename){return al_unlink(filename);}
int        th_link     (const char *oldpath, const char *newpath){return al_link(oldpath,newpath);}

/* Basic file I/O routines */

int      th_putc   (int c, ee_FILE *fp) {return al_putc(c,fp);}
int	     th_getc   (ee_FILE *fp) {return al_getc(fp);}
int      th_ungetc (int ch, ee_FILE *file){return al_ungetc(ch,file);}
int      th_fputs  (const char *s, ee_FILE *fp){return al_fputs(s,fp);}
char    *th_fgets  (char *string,int count,ee_FILE *file){return al_fgets(string,count,file);}
size_t   th_fread  (void *buf, size_t size, size_t count, ee_FILE *fp) {return al_fread   (buf,size,count,fp);}
size_t   th_fwrite (const void *buf, size_t size, size_t count, ee_FILE *fp) {return al_fwrite  (buf,size,count,fp);}
ee_FILE *th_fopen  (const char *filename, const char *mode) {return al_fopen   (filename,mode);}
ee_FILE *th_fdopen (int fildes, const char *mode) {return al_fdopen(fildes,mode);}
ee_FILE *th_freopen(const char *filename, const char *mode, ee_FILE *fp) {return al_freopen(filename,mode,fp);}
ee_FILE *th_tmpfile(void) {return al_tmpfile();}
char    *th_mktemp (char *templat) {return al_mktemp(templat);}

/* scanf input format conversion family (thal.c only sees vxxx functions) */

int 	th_scanf(const char *format, ...)
{
   int rv;
   va_list args;
   va_start( args, format );
   rv = al_vscanf( format, args );
   va_end( args );
   return rv;
}
int		th_fscanf(ee_FILE *stream, const char *format, ...)
{
   int rv;
   va_list args;
   va_start( args, format );
   rv = al_vfscanf( stream, format, args );
   va_end( args );
   return rv;
}
int		th_sscanf(const char *str, const char *format, ...)
{
   int rv;
   va_list args;
   va_start( args, format );
   rv = al_vsscanf( str, format, args );
   va_end( args );
   return rv;
}
int		th_vscanf(const char *format, va_list ap){return al_vscanf( format, ap );}
int		th_vsscanf(const char *str, const char *format, va_list ap){return al_vsscanf( str,format, ap );}
int		th_vfscanf(ee_FILE *stream, const char *format, va_list ap){return al_vfscanf( stream, format, ap );}

/* Process I/O */

ee_FILE	*th_popen(const char *command, const char *type){return al_popen(command,type);}
int		th_pclose(ee_FILE *fd){return al_pclose(fd);}

/* NON Standard routines */

int          th_filecmp(const char *file1, const char *file2) 
	{return al_filecmp (file1,file2);}
ee_FILE	    *th_fcreate(const char *filename, const char *mode, char *data, ee_fsize_t size) 
	{return al_fcreate (filename,mode,data,size);}
ee_fsize_t   th_fsize  (const char *filename) {return al_fsize(filename);}
int th_dup(int fildes) {return al_dup(fildes);}

/**
 * FUNC   : th_harness_poll  .(stub routine in Lite)
 *
 * DESC   : Gives the test harness some CPU time.(stub routine in Lite)
 *
 *          This function can be called during the execution of a test
 *          or benchmark to give the test harness some execution time so it
 *          can respond to commands from a host.
 *
 * CAVEAT : Only debug or test versions of true bench marks should call this
 *          function as it uses CPU time.
 *
 * RETURNS: TRUE if the test should keep running.
 *          FALSE if the stop message has been received form the host
 *          and the benchmark or test should stop.
 * NOTE:    Added to TH_Lite for application compatibility.
 */

int th_harness_poll( void ) {return (TRUE);}

/*------------------------------------------------------------------------------
 * FUNC   : th_get_file_def  .(stub routine in Lite)
 *
 * DESC   : Gets the file defintion (FileDef*) for a specific file.
 *
 *          Give a file name, this function returns a pointer to the file
 *          defintion structure for the file. If the file does not exist
 *          then NULL is returned. The FileDef structure is documented in the
 *          THLIB.H file.
 *
 * PARAMS : fn - The index of the file to find.
 *               The most recent file downloaded has an index number of zero.
 *               The previouly downloaded file has index 1. etc. etc.
 *
 * RETURNS: A pointer to the FileDef struct or NULL if the file has not yet
 *          been downloaded
 * ---------------------------------------------------------------------------*/

const FileDef *th_get_file_def( const char *fn )
{
	/* memargs.c NOT implemented in Lite */
	fn = fn;
	return NULL;
}
/*------------------------------------------------------------------------------
 * FUNC   : th_get_file_num  .(stub routine in Lite)
 *
 * DESC   : Gets the file defintion (FileDef*) for a file by index number.
 *
 *          Give a file number index, this function returns a pointer to the
 *          file defintion structure for the file. If the file does not
 *          exist then NULL is returned. The FileDef structure is documented
 *          in the THLIB.H file.
 *
 * PARAMS : n - The index of the file to find. The most recent file
 *              downloaded has an index number of zero. The previous file
 *              has index 1. etc. etc.
 *
 * RETURNS: A pointer to the FileDef struct or NULL if the file has not yet
 *          been downloaded.
 * ---------------------------------------------------------------------------*/

const FileDef *th_get_file_num( int n )
{
	/* unused */
	n = n;
	return NULL;
}

/**
 * FUNC   : th_send_buf_as_file
 *
 * DESC   : Sends a buffer (as a file) to the host using uuencode over the console
 *
 * PARAMS : buf    - a pointer to the buffer to send
 *          length - the length of the buffer
 *          fn     - the name to use on the host system.
 *
 * RETRUNS: Success of the file was succesfully sent.
 *          Failure otherwise.
 *
 * CAVEAT : Note that if a file exists on the remote system it will
 *          be overwritten.
 */
int th_send_buf_as_file( const char* buf, BlockSize length, const char* fn )
	{return uu_send_buf ( buf, length, fn );}

/** CRC a buffer. */
e_u16	th_crcbuffer(const void *inbuf,size_t size,e_u16 inputCRC)
	{return t_crcbuffer(inbuf,size,inputCRC);}


/*==============================================================================
 *                  -- Funcational Layer Implemenation --
 * ===========================================================================*/

#if	!HAVE_ASSERT_H
/*------------------------------------------------------------------------------
 * FUNC   : __assertfail
 *
 * DESC   : Called by the assert() macro when a condition fails
 *
 * NOTE   : Does not return!
 * ---------------------------------------------------------------------------*/

void __assertfail( const char *msg, const char *cond, const char *file, int line )
{
	th_exit( THE_FAILURE,"message: %s\nCondition: %s\nFile: %s at %d\n",msg,cond,efn(file),line );
}

/*------------------------------------------------------------------------------
 * FUNC   : __fatal
 *
 * DESC   : called when a fatal error is encountered
 * ---------------------------------------------------------------------------*/

void __fatal( const char *msg, const char *file, int line )
{
	th_exit( THE_FAILURE,"message: %s\nFile: %s at %d\n",msg,efn(file),line );
}
#endif

/*------------------------------------------------------------------------------
 * Malloc and Free Mapping
 *----------------------------------------------------------------------------*/

#if MAP_MALLOC_TO_TH
/*
 * If malloc or free are called by OS or crt0 th_heap will not be initialized, and
 * we need to give up. Attempt to return Error 8.
 * This traps the case when duplicate heap managers are being compiled
 * into the benchmark code. To minimize size, use compiler malloc in thcfg.h:
 * HAVE_MALLOC=TRUE, COMPILE_OUT_HEAP=TRUE
 */
#if		!HAVE_MALLOC && !COMPILE_OUT_HEAP
extern	void	*th_heap; 
#else
/* heap is compiled out */
#error "MAP_MALLOC_TO_TH only valid if using internal heap manager"
#endif

/** malloc entry point to catch CRT0 calls when internal heap manager is used. */
void * malloc( size_t foo )
{
	if (th_heap)
		return th_malloc( foo );
	else
		exit(THE_OUT_OF_MEMORY);
}

void free( void* ptr )
{
	if (th_heap)
		th_free( ptr );
}
#endif

/**
 * FUNC    : th_malloc_x
 *
 * DESC    : Test Harness malloc()
 *
 *           This works just like malloc() from the standard library.
 *
 * PARAMS  : size - is the size of the memory block neded
 *           file - the __FILE__ macro from where the call was made
 *           line - the __LINE__ macro from where the call was made
 *
 * NOTE    : This function is usually invoked by using th th_malloc()
 *           macro.
 *
 * RETURNS : A void pointer to the allocated block.  Use a cast to asssign
 *           it to the proper poitner type.
 *           The NULL value is returned if a block ofthe specified size cannot
 *           be allocated.
 */

void *th_malloc_x( size_t size, const char *file, int line )
{
	return i_malloc( size, file, line );
}

/**
 * FUNC    : th_calloc_x
 *
 * DESC    : Test Harness calloc()
 *
 *           This works just like calloc() from the standard library.
 *
 * PARAMS  : size - is the size of the memory block neded
 *           file - the __FILE__ macro from where the call was made
 *           line - the __LINE__ macro from where the call was made
 *
 * NOTE    : This function is usually invoked by using th_calloc()
 *           macro.
 *
 * RETURNS : A void pointer to the allocated block.  Use a cast to asssign
 *           it to the proper poitner type.
 *           The NULL value is returned if a block ofthe specified size cannot
 *           be allocated.
 */

void *th_calloc_x( size_t nmemb, size_t size, const char *file, int line )
{
	return i_calloc( nmemb, size, file, line );
}

/** Test Harness realloc()
 *
 * This works just like realloc() from the standard library.
 *
 *@param  ptr  - pointer to the original malloc
 *@param  size - is the size of the memory block neded
 *@param  file - the __FILE__ macro from where the call was made
 *@param  line - the __LINE__ macro from where the call was made
 *
 *@note   This function is usually invoked by using th th_realloc() macro.
 *@retval A void pointer to the allocated block.  Use a cast to asssign
 *        it to the proper poitner type.
 *        The NULL value is returned if a block ofthe specified size cannot
 *        be allocated.
 */
void *th_realloc_x( void *ptr, size_t size, const char *file, int line )
{
	return i_realloc( ptr, size, file, line );
}
/** Test Harness strdup()
 *
 * This works just like strdup() from the standard library.
 *
 *@param  string  - pointer to the original character string
 *@param  file    - the __FILE__ macro from where the call was made
 *@param  line    - the __LINE__ macro from where the call was made
 *
 *@note   This function is usually invoked by using th th_strdup() macro.
 *@retval A char pointer to the allocated block.
 *        The NULL value is returned if a block of the strlen size cannot
 *        be allocated.
 */
char *th_strdup_x( const char *string, const char *file, int line )
	{return i_strdup( string, file, line );}

/** Test Harness free()
 *
 *           This works just like free() from the standard library.
 *
 * PARAMS  : ptr - points to the block pointer returned by th_malloc().
 *           file - the __FILE__ macro from where the call was made
 *           line - the __LINE__ macro from where the call was made
 *
 * NOTE    : This function is usually invoked by using th th_free()
 *           macro.
 *
 * NOTE    : It is valid to pass the null pointer to this function.
 */
void th_free_x( void *block, const char *file, int line )
	{i_free ( block, file, line );}

/**
 * FUNC   : th_heap_reset()
 *
 * DESC   : Resets the heap to its initialized state
 *
 *          Calling this function implicitly free's all the memory which
 *          has been allocated with th_malloc()
 */
void th_heap_reset( void ){i_heap_reset();}

/* helper for parsing command line for input filename */
int change_data(int argc, const char* argv[], char **data_name )
{
	int i;
	for (i=0; i<argc; i++) {
		if (strstr(argv[i],"-data=")!=NULL) {
			*data_name=th_strdup(argv[i]+strlen("-data="));
			return -1;
		}
		if (strstr(argv[i],"-data")!=NULL) {
			const char *pidx=argv[i]+strlen("-data");
			int idx=0;
			while ((*pidx>='0') & (*pidx<='9')) {
				idx*=10;
				idx+=*pidx-'0';
				pidx++;
			}
			idx--;
			return idx;
		}
	}
	return -1;
}



/** @} */
/** @} */

