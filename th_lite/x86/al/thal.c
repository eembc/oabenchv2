/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

#include <stdlib.h>
/*#include <setjmp.h>*/
#include <stdarg.h>
#include <stdio.h>
#include <string.h> /* strlen */
#include <ctype.h> /* isdigit */

#if	defined(_MSC_VER) || defined(UNDER_CE)
/* SG: windows types must come before EE types for VS8 */
#define _X86_ 
#include <windef.h>
#include "dirent_msvc.h" 
#elif	HAVE_SYS_TYPES_H
#include <sys/types.h> /* DIR */
#endif

#include "eembc_dt.h"
#include "thcfg.h"


#if		HAVE_DIRENT_H
#if 	HAVE_SYS_TYPES_H
#include <sys/types.h> /* DIR */
#endif

#include <dirent.h> /* dirent */
#endif

#if		HAVE_UNISTD_H
#include <unistd.h>
#endif

#if		HAVE_STAT_H
#include <stat.h>
#elif	HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif

#if	EE_POWERTAG && HOST_EXAMPLE_CODE && !defined(_MSC_VER)
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#endif

#include "thal.h"
#include "thfl.h"
/*#include "thfli.h"*/
#include "heap.h"

#if     HAVE_CLOCK || HAVE_GETTIMEOFDAY
#if	TIME_WITH_SYS_TIME
#include <sys/time.h>
#include <time.h>
#elif	HAVE_SYS_TIME_H
#include <sys/time.h>
#elif  HAVE_TIME_H
#include <time.h>
#endif
#endif

/** Define Host specific (POSIX), or target specific global time variables. */
#if 	HAVE_CLOCK
static clock_t   start_time = 0;
static clock_t   stop_time  = 0;
#else
static e_u32   start_time = 0;
static e_u32   stop_time  = 0;
#endif

/** @addtogroup THAL Test Harness Adaptation Layer
@{ */
/** @addtogroup thal_c Adaptation Layer Routines
@{ */

/**
 * Platform Specific Header Files, Defines, Globals and Local Data
 */

/**
 * Local Defines
 */

/**
 * Local Data
 */

/*
>> Put your platform specific code here
*/
#if 	!HOST_EXAMPLE_CODE
#endif

/*------------------------------------------------------------------------------
 *                     >>> TARGET TIMER SUPPORT <<<
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
 * The following five functions must be modified if you need to support a 
 * timer on your target which will be used to measure benchmark durations.
 *
 * IMPORTANT: You do not have to modify these functions if you don't want
 *            to support target based timing!  
 */

#if 	EE_POWERTAG

#if 	HOST_EXAMPLE_CODE && !defined(_MSC_VER)
/** Hold state of pins. */
int	input;
/** Serial device for example triger. */
#define MODEMDEVICE "/dev/ttyS1"
#endif

/** Delay in milliseconds to start power measurements. */
#define	POWER_DELAY 	20

/**
When the C code hits this function, the target board asserts a latched
pin HIGH, triggers the N.I.  system to start taking samples, but there
is about a 17 millisecond or so delay.  We need a delay due to the
response time of the N.I.  on the host system itself.

We need a way to assert a pin high or low somewhere on the target
board.  That is what will trigger us to do timing, stop timing, and so
on.  Obviously, we must have power measurement points on which to
solder the power resister.

*/
void al_power_start(void)
{
	/** Set GPIO Pin */
#if HOST_EXAMPLE_CODE && !defined(_MSC_VER)
	int ser_val, errval=0;
	input =  open(MODEMDEVICE , O_RDWR);
	if (input < 0) {
		th_printf("Could not open second serial port.\n");
	} else {
  		errval = ioctl (input, TIOCMGET, &ser_val);
		if (errval == 0) {
			/** @note whether the RTS or CTS lines are used will 
			depend on whether this is a DTE or DCE port */
   			ser_val |= TIOCM_CTS;				/* Make CTS value High */
	   		errval = ioctl (input, TIOCMSET, &ser_val);
			if (errval != 0) {
				th_printf("Error attempting to set CTS. ioctl returned error %x.\n",errval);
			}
		} else {
			th_printf("Ioctl returned error %x accessing handle %d for port %s\n",errval,input,MODEMDEVICE);
		}
	}

#endif

	/** Wait POWER_DELAY milliseconds. */
#if HOST_EXAMPLE_CODE || HAVE_CLOCK
	clock_t	
	  start_delay = clock(),
	  stop_delay = start_delay + POWER_DELAY * al_ticks_per_sec()/1000;
	while (stop_delay < clock());
#else
	/** PORTING: Board specific timer code */
	unsigned long	
	  start_delay = 0,
	  stop_delay = start_delay + POWER_DELAY * al_ticks_per_sec()/1000;

	while ( /* stop_delay  your timer function here */);
#endif
}

/**
Signal the host to stop power measurement by clearing the defined
GPIO pin.
*/
void al_power_finished(void)
{
	/** PORTING: Clear GPIO Pin */
#if HOST_EXAMPLE_CODE && !defined(_MSC_VER)
	int errval, ser_val = 0;

	if (input < 0) {
		th_printf("Serial port is not open.\n");
	} else {
  		errval = ioctl (input, TIOCMGET, &ser_val);
		if (errval == 0) {
			/** @note whether the RTS or CTS lines are used will 
			depend on whther this is a DTE or DCE port */
   			ser_val &= ~TIOCM_CTS;				/* Make CTS value Low */
	   		errval = ioctl (input, TIOCMSET, &ser_val);
			if (errval != 0) {
				th_printf("Error attempting to clear CTS. ioctl returned error %x.\n",errval);
			}
		} else {
			th_printf("Ioctl returned error %x accessing handle %d for port %s\n",errval,input,MODEMDEVICE);
		}
	}
	close(input);

#endif
}
#else
void al_power_start(){}
void al_power_finished(){}
#endif

/**
 * FUNC   : al_signal_start
 *
 * DESC   : Adaptation layer implementation of th_signal_start()
 *
 *          This function is called when the benchmark starts.  It should
 *          start the target timer or record the current value of a free
 *          running timer.
 *
 * PORTING: If you want to support target based timing, you need to 
 *          fill in this function.
 */

void al_signal_start( void )
{
	al_power_start();
#if HOST_EXAMPLE_CODE || HAVE_CLOCK
	start_time      = clock();       
#else
	/** PORTING: Board specific timer code */                      
	start_time	= 0;
#endif
}

/**
 * FUNC   : al_signal_finished
 *
 * DESC   : Adaptation layer implementation of th_signal_finished()
 *
 *          This function is called when a benchmark or test finishes.  It
 *          stops the target timer or reads the value of a free running
 *          timer and calculates the number of timer ticks since
 *          al_signal_start() was called.
 *
 * RETURNS: The number of ticks since al_signal_start() was called.
 *
 * PORTING: If you want to support target based timing, you need to 
 *          fill in this function.
 */

size_t al_signal_finished( void )
{
#if HOST_EXAMPLE_CODE || HAVE_CLOCK
	stop_time	= clock();
#else
	/* Board specific timer code  */ 
	stop_time	= 0;
#endif
	al_power_finished();
	return (size_t)(stop_time-start_time);
}

/**
 * FUNC   : al_ticks_per_sec
 *
 * DESC   : Adaptation layer implementation of th_ticks_per_sec()
 *
 *          This function is used to determine the resolution of the target
 *          timer.  This value is reported to the host computer and is
 *          is used to report test results.
 *
 * RETURNS: The number of timer ticks per second.
 *
 * PORTING: If a target timer is supported, then this function must be 
 *          implemented.
 *
 *          If the target timer is NOT supported, then this function MUST
 *          return zero.
 *
 * NOTES:   ANSI C, POSIX requires that CLOCKS_PER_SEC equals 1000000
 *          independent of the actual resolution. 
 *
 *          On Linux and Solaris hosts this results in durations to be large
 *          numbers which always end with three zeros.  This is correct, 
 *          because the clock resolution is less than the POSIX required 
 *          resolution of 1000000. The resulting calculation to seconds is
 *          correct, and the actual resolution is measured to be 1000, or a
 *          millisecond timer.
 *
 *          Note that the time can wrap around.  On a 32 bit system
 *          where CLOCKS_PER_SEC equals 1000000 this function will
 *          return the same value approximately every 72 minutes.
 *          ( Excerpt from GNU man page clock )
 *
 * ---------------------------------------------------------------------------*/
   
size_t al_ticks_per_sec( void )
{
#if HOST_EXAMPLE_CODE || HAVE_CLOCK 
	return (size_t) CLOCKS_PER_SEC;
#else
	/* Board specific timer code  */ 
	return (size_t) 0;
#endif
}

/*------------------------------------------------------------------------------
 * FUNC   : al_tick_granularity
 *
 * DESC   : used to determine the granularity of timer ticks.
 *
 *          Example 1: the value returned by al_stop_timer() may be 
 *          in milliseconds. In this case, al_ticks_pers_sec() would
 *          return 1000.  However, the timer interrupt may only occur
 *          once very 10ms.  So al_tick_granularity() would return 10.
 *
 *          Example 2: on another system, th_ticks_sec() returns 10
 *          and th_tick_granularity() returns 1.  This means that each
 *          incriment of the value returned by th_stop_timer() is in 100ms
 *          intervals.
 *
 * RETURNS: the granularity of the value returned by th_stop_timer()
 *
 * PORTING: If a target timer is supported, then this function must be 
 *          implemented.
 * ---------------------------------------------------------------------------*/
   
size_t al_tick_granularity( void )
{
#if HOST_EXAMPLE_CODE || HAVE_CLOCK 
	return 10;
#else
	/** PORTING: Board specific timer code  */ 
	return 0;
#endif
}

/*------------------------------------------------------------------------------
 *                       >>> SUPPORT FUNCTIONS <<<
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
 * These support functions are part of the Adaptaion Layer but do not
 * generally need to be modified.
 * ---------------------------------------------------------------------------*/

/**
 * FUNC   : al_exit
 *                                    
 * DESC   : Exits the benchmark.
 *
 *
 * PARAMS : exit_code - the traditional exit code
 *
 *
 * PORTING: Standard C in stdlib.h
 * ---------------------------------------------------------------------------*/
void al_exit( int exit_code, const char* fmt, va_list args )   
{
	al_printf(fmt,args);
	al_hardware_reset(exit_code); /* Notify hardware reset that we came from th_exit */
	exit(exit_code);
}

/**
 * FUNC   : al_write_con
 *
 * DESC   : Sends data to the logical console
 *
 * @param tx_buf     - a pointer to a buffer containing the data to send
 * @param byte_count - the number of bytes from the buffer to send.  If this
 *                       value is zero, then no data is sent to the logical
 *                       console.
 *
 * @retval Success if all the characters were sent.
 *          Failure if all the characters could not be sent.  In this case
 *                  some of the characters MAY have been sent.
 *
 * @note PORTING: You will need to fully implement this function. 
 * Even if you are !USE_TH_PRINTF, ssubs.c calls here once.
 */
int al_write_con( const char* tx_buf, size_t byte_count )
{
   /* This logic must be preserved */
   if ( byte_count == 0 )
      return Success;

   fwrite( tx_buf, sizeof(char), byte_count, stdout );

   return Success;
}

/**
 * FUNC   : al_printf
 *                                    
 * DESC   : The traditional vprintf, control output from here.
 *
 *
 * @remark PORTING: Standard C in stdio.h, and stdargs.h
 *
 * @note To convert this to a string, use vsprintf, NOT sprintf.
 */
int		al_printf(const char *fmt, va_list	args)
{

	return	vprintf(fmt,args);
}

/*-----------------------------------------------------------------------------
 * FUNC   : al_sprintf
 *
 * DESC   : The traditional vsprintf, control output from here.
 *
 *
 * PORTING: Standard C in stdio.h, and stdargs.h
 *
 * NOTE: To convert this to a string, use vsprintf, NOT sprintf.
 * ---------------------------------------------------------------------------*/
int     al_sprintf(char *str, const char *fmt, va_list   args)
{
	return  vsprintf(str,fmt,args);
}

/*------------------------------------------------------------------------------
 * FUNC   : al_report_results
 *                                    
 * DESC   : Print additional messages below harness output.
 *
 * PORTING: Use harness th_printf.
 * ---------------------------------------------------------------------------*/
void	al_report_results( void )
{
	/* Add any debug printing here, outside the normal log */
}

FILE *restore_stdio(ee_FILE *fp);
/** Restores libc stdio files when defined as eembc stdio */
FILE *restore_stdio(ee_FILE *fp)
{
	FILE *rv;
	if      (fp == ee_stdout)	rv=stdout;
	else if (fp == ee_stderr)	rv=stderr;
	else if (fp == ee_stdin)	rv=stdin;
	else						rv=(FILE *)fp;
	return rv;
}

/** Close a stream file.*/
int	al_fclose (ee_FILE *fp) 
{
#if 	USE_TH_FILEIO
	return ee_fclose (fp);
#elif	HAVE_FILEIO
	return fclose(restore_stdio(fp));
#else
	return 0;
#endif
}
/** Open a regular file. */
int al_open(const char *pathname, int flags)
{
#if 	USE_TH_FILEIO
	return ee_open(pathname,flags);
#elif	HAVE_FILEIO
	return open(pathname,flags);
#else
	return 0;
#endif
}

/** Close a regular file.*/
int	al_close (int fildes) 
{
#if	USE_TH_FILEIO
	return ee_close (fildes);
#elif	HAVE_FILEIO
	return close(fildes);
#else
	return 0;
#endif
}
/** Read bytes from file.*/
size_t al_read(int fd, void *buf, size_t count)
{
#if	USE_TH_FILEIO
	return ee_read(fd,buf,count);
#elif	HAVE_FILEIO && HAVE_READ
	return read(fd,buf,count);
#else
	return 0;
#endif
}
/** Write bytes to file. */
size_t al_write(int fd, const void *buf, size_t count)
{
#if	USE_TH_FILEIO
	return ee_write(fd,buf,count);
#elif	HAVE_FILEIO && HAVE_WRITE
	return write(fd,buf,count);
#else
	return 0;
#endif
}
/** Seek in file. */
ee_off_t al_lseek(int fildes, ee_off_t offset, int whence)
{
#if	USE_TH_FILEIO
	return ee_lseek(fildes,offset,whence);
#elif	HAVE_FILEIO && HAVE_LSEEK
	return lseek(fildes,offset,whence);
#else
	return 0;
#endif
}
/** Return file error. */
int	al_ferror(ee_FILE *fp) 
{
#if	USE_TH_FILEIO
	return ee_ferror (fp);
#elif	HAVE_FILEIO
	return ferror(restore_stdio(fp));
#else
	return 0;
#endif
}
int	al_feof (ee_FILE *fp)
{
#if	USE_TH_FILEIO
	return ee_feof (fp);
#elif	HAVE_FILEIO
	return feof (restore_stdio(fp));
#else
	return 0;
#endif
}
void	al_clearerr (ee_FILE *fp) 
{
#if	USE_TH_FILEIO
	ee_clearerr(fp);
#elif	HAVE_FILEIO
	clearerr(restore_stdio(fp));
#else
	/* void */
#endif
}
int	al_fileno(ee_FILE *fp)
{
#if	USE_TH_FILEIO
	return ee_fileno(fp);
#elif	HAVE_FILEIO
	return fileno(restore_stdio(fp));
#else
	return 0;
#endif
}
/** flush a file */
int	al_fflush (ee_FILE *fp) 
{
#if	USE_TH_FILEIO
#if !USE_TH_PRINTF
	FILE *tmp=restore_stdio(fp);
	if (tmp != (FILE *)fp)
		return fflush (tmp);
	else
#endif
		return ee_fflush(fp);
#elif	HAVE_FILEIO
	return fflush (restore_stdio(fp));
#else
	return 0;
#endif
}
/** Sync a file.*/
int	al_fsync (int fildes) 
{
#if	USE_TH_FILEIO
	return ee_fsync (fildes);
#elif	HAVE_FILEIO
#if defined(_MSC_VER)
	return _commit(fildes);
#else
	return fsync(fildes);
#endif
#else
	return 0;
#endif
}
/** is TTY device?.*/
int	al_isatty (int fildes) 
{
#if	USE_TH_FILEIO
	return ee_isatty (fildes);
#elif	HAVE_FILEIO
	return isatty(fildes);
#else
	return 0;
#endif
}
/** vfprintf mapped from fprintf */
int	al_vfprintf(ee_FILE *fp, const char* format, va_list args)
{
#if	USE_TH_FILEIO
   return ee_vfprintf( fp, format, args );
#elif	HAVE_FILEIO
   return vfprintf( restore_stdio(fp), format, args );
#else
	return 0;
#endif
}
int	al_fseek  (ee_FILE *fp, long int offset, int whence) 
{
#if	USE_TH_FILEIO
	return ee_fseek  (fp,offset,whence);
#elif	HAVE_FILEIO
	return fseek  (restore_stdio(fp),offset,whence);
#else
	return 0;
#endif
}
long al_ftell  (ee_FILE *fp) 
{
#if	USE_TH_FILEIO
	return ee_ftell  (fp);
#elif	HAVE_FILEIO
	return ftell  (restore_stdio(fp));
#else
	return 0;
#endif
}
	/* DIRENT routines, and helpers */

char      *al_getcwd   (char *buffer, size_t size)
{
#if	USE_TH_FILEIO
	return ee_getcwd(buffer,size);
#elif	HAVE_FILEIO && !_MSC_VER
	return getcwd(buffer,size);
#else
	return NULL;
#endif
}
char      *al_getwd    (char *buffer)
{
#if	USE_TH_FILEIO
	return ee_getwd(buffer);
#elif	HAVE_FILEIO && !_MSC_VER
	return getwd(buffer);
#else
	return 0;
#endif
}
int        al_chdir    (const char *filename)
{
#if	USE_TH_FILEIO
	return ee_chdir(filename);
#elif	HAVE_FILEIO && !_MSC_VER
	return chdir(filename);
#else
	return 0;
#endif
}
ee_DIR    *al_opendir  (const char *dirname)
{
#if	USE_TH_FILEIO
	return ee_opendir(dirname);
#elif	HAVE_FILEIO && HAVE_DIRENT_H
	return (ee_DIR *)opendir(dirname);
#else
	return NULL;
#endif
}
struct ee_dirent *al_readdir  (ee_DIR *dirstream)
{
#if	USE_TH_FILEIO
	return ee_readdir  (dirstream);
#elif	HAVE_FILEIO && HAVE_DIRENT_H

#if USE_EE_DIRENT
	/* Remap entries */
	struct dirent *rv;
	static struct ee_dirent rv1;
	if ((rv=readdir((DIR *)dirstream))==NULL)
		return NULL;
	rv1.d_name = th_strdup(rv->d_name);
/*  rv1.d_namlen = rv->d_namlen; not gcc */
	rv1.d_ino = (short)rv->d_ino;
	return &rv1;
#else
	return (struct ee_dirent *)readdir  ((DIR *)dirstream);
#endif

#else
	return NULL;
#endif
}
int        al_closedir (ee_DIR *dirstream)
{
#if	USE_TH_FILEIO
	return ee_closedir(dirstream);
#elif	HAVE_FILEIO && HAVE_DIRENT_H
	return closedir((DIR *)dirstream);
#else
	return 0;
#endif
}
void       al_rewinddir(ee_DIR *dirstream)
{
#if	USE_TH_FILEIO
	ee_rewinddir(dirstream);
#elif	HAVE_FILEIO && HAVE_DIRENT_H
	rewinddir((DIR *)dirstream);
#else
	/* void return */
#endif
}

int       al_stat     (const char *path, struct th_stat *buf)
{
#if	USE_TH_FILEIO
	return ee_stat (path,buf);
#elif	HAVE_FILEIO

#if USE_TH_STAT
	struct stat st;
	int rv;
	rv = stat(path,&st);
	buf->st_size = st.st_size;
	/* MSVC doesnt support blksize or blocks */
	buf->st_blksize = 0;
	buf->st_blocks = 0;
	buf->st_mode = st.st_mode;
	buf->st_nlink = st.st_nlink;
	return rv;
#else
	return stat  (path,buf);
#endif

#else
	return 0;
#endif
}
int        al_lstat    (const char *path, struct th_stat *buf)
{
#if	USE_TH_FILEIO
	return ee_lstat (path,buf);
#elif	HAVE_FILEIO && !_MSC_VER
	return lstat (path,buf);
#else
	return 0;
#endif
}
int        al_fstat    (int fildes, struct th_stat *buf)
{
#if	USE_TH_FILEIO
	return ee_fstat(fildes,buf);
#elif	HAVE_FILEIO
	return fstat  (fildes,(struct stat *)buf);
#else
	return 0;
#endif
}

/* Fileio routines found in unistd.h */

int        al_unlink   (const char *filename)
{
#if	USE_TH_FILEIO
	return ee_unlink(filename);
#elif	HAVE_LINK
	return unlink  (filename);
#else
	return 0;
#endif
}
int        al_link     (const char *oldpath, const char *newpath)
{
#if	USE_TH_FILEIO
	return ee_link(oldpath,newpath);
#elif	HAVE_LINK
	return link  (oldpath,newpath);
#else
	return 0;
#endif
}
#if	NEED_LINK
int        link     (const char *oldpath, const char *newpath)
{
	return al_link(oldpath,newpath);
}
#endif

	/* Basic file I/O routines */

int	al_putc   (int c, ee_FILE *fp) 
{
#if	USE_TH_FILEIO
	return ee_putc(c,fp);
#elif	HAVE_FILEIO
	return putc(c,restore_stdio(fp));
#else
	return 0;
#endif
}
int	al_getc   (ee_FILE *fp) 
{
#if	USE_TH_FILEIO
	return ee_getc(fp);
#elif	HAVE_FILEIO
	return getc(restore_stdio(fp));
#else
	return 0;
#endif
}
int	al_ungetc(int ch, ee_FILE *fp)
{
#if	USE_TH_FILEIO
	return ee_ungetc(ch,fp);
#elif	HAVE_FILEIO
	return ungetc(ch,restore_stdio(fp));
#else
	return 0;
#endif
}
/** `fputs'  adaptation layer interface.
@param s character string to write
@param fp File to write to.
@retval If successful, the result is `0'; otherwise, the result is `EOF'.
*/
int al_fputs(const char *s, ee_FILE *fp)
{
#if	USE_TH_FILEIO
#if !USE_TH_PRINTF
	FILE *tmp=restore_stdio(fp);
	if (tmp != (FILE *)fp)
		return fputs(s,tmp);
	else
#endif
return ee_fputs(s,fp);
#elif	HAVE_FILEIO
	return fputs(s,restore_stdio(fp));
#else
	return 0;
#endif
}
char *al_fgets  (char *string,int count,ee_FILE *fp)
{
#if	USE_TH_FILEIO
	return ee_fgets(string,count,fp);
#elif	HAVE_FILEIO
	return fgets(string,count,restore_stdio(fp));
#else
	return 0;
#endif
}
size_t	al_fread (void *buf, size_t size, size_t count, ee_FILE *fp) 
{
#if	USE_TH_FILEIO
	return ee_fread(buf,size,count,fp);
#elif	HAVE_FILEIO
	return fread(buf,size,count,restore_stdio(fp));
#else
	return 0;
#endif
}
size_t	al_fwrite (const void *buf, size_t size, size_t count, ee_FILE *fp) 
{
#if	USE_TH_FILEIO
#if !USE_TH_PRINTF
	FILE *tmp=restore_stdio(fp);
	if (tmp != (FILE *)fp)
		return fwrite(buf,size,count,tmp);
	else
#endif
	return ee_fwrite(buf,size,count,fp);
#elif	HAVE_FILEIO
	return fwrite(buf,size,count,restore_stdio(fp));
#else
	return 0;
#endif
}
ee_FILE *al_fopen (const char *filename, const char *mode) 
{
#if	USE_TH_FILEIO
	return ee_fopen (filename,mode);
#elif	HAVE_FILEIO
	return (ee_FILE *)fopen (filename,mode);
#else
	return NULL;
#endif
}
ee_FILE *al_fdopen(int fildes, const char *mode)
{
#if	USE_TH_FILEIO
	return ee_fdopen (fildes,mode);
#elif	HAVE_FILEIO
	return (ee_FILE *)fdopen (fildes,mode);
#else
	return NULL;
#endif
}
ee_FILE *al_freopen (const char *filename, const char *mode, ee_FILE *fp) 
{
#if	USE_TH_FILEIO
	return ee_freopen (filename,mode,fp);
#elif	HAVE_FILEIO
	return (ee_FILE *)freopen (filename,mode,restore_stdio(fp));
#else
	return NULL;
#endif
}
ee_FILE *al_tmpfile (void) 
{
#if	USE_TH_FILEIO
	return ee_tmpfile();
#elif	HAVE_FILEIO
	return (ee_FILE *)tmpfile();
#else
	return NULL;
#endif
}
#if !USE_TH_FILEIO && HAVE_FILEIO 
/* Library routines not declared in a standard header */
extern char *mktemp(char *);
#endif
char *al_mktemp (char *templat) 
{
#if	USE_TH_FILEIO
	return ee_mktemp(templat);
#elif	HAVE_FILEIO
	return mktemp(templat);
#else
	return NULL;
#endif
}

/* scanf input format conversion family <stdargs.h> */

/** vscanf redirector */
int	al_vscanf(const char *format, va_list ap)
{
#if	USE_TH_FILEIO || !HAVE_VSCANF
	return ee_vscanf(format,ap);
#elif	HAVE_FILEIO
	return vscanf(format,ap);
#else
	return NULL;
#endif
}
/** vsscanf redirector */
int	al_vsscanf(const char *str, const char *format, va_list ap)
{
#if 	USE_TH_FILEIO || !HAVE_VSSCANF
	return ee_vsscanf(str,format,ap);
#elif	HAVE_FILEIO
	return vsscanf(str,format,ap);
#else
	return NULL;
#endif
}
/** vfscanf redirector */
int	al_vfscanf(ee_FILE *stream, const char *format, va_list ap)
{
#if 	USE_TH_FILEIO || !HAVE_VFSCANF
	return ee_vfscanf (stream,format,ap);
#elif	HAVE_FILEIO
	return vfscanf (restore_stdio(stream),format,ap);
#else
	return NULL;
#endif
}

/* Process I/O */

/** popen redirector, stub in harness, we will always use libc if available. */
ee_FILE	*al_popen(const char *command, const char *type)
{
#if 	USE_TH_FILEIO || !HAVE_POPEN
	return ee_popen (command,type);
#elif	HAVE_POPEN
#ifdef	_MSC_VER
	return (ee_FILE *) _popen (command,type);
#else
	return (ee_FILE *) popen (command,type);
#endif
#else
	return NULL;
#endif
}
/** pclose redirector, stub in harness, we will always use libc if available. */
int		al_pclose(ee_FILE *fd)
{
#if 	USE_TH_FILEIO || !HAVE_PCLOSE
	return ee_pclose (fd);
#elif	HAVE_PCLOSE
#ifdef	_MSC_VER
	return _pclose ((FILE *)fd);
#else
	return  pclose ((FILE *)fd);
#endif
#else
	return NULL;
#endif
}

/** Time stub routines, direct call from benchmarks. 
@todo promote these to harness if full implementation needed.
Most libc's have these so they are special cases for now.
*/
/** time  returns the time since the Epoch (00:00:00 UTC, January 1, 1970). */
ee_time_t al_time(ee_time_t *t)
{
#if		HAVE_TIME
	return (ee_time_t) time((time_t *)t);
#else
	return ee_time(t);
#endif
}
/** Convert the calendar time  timep  to  broken-down time  representation.

It is the mktime code. In our case, this is a stub routine with one default value.
We will piggyback off of the HAVE_TIME definition.
*/
struct ee_tm *al_localtime(const ee_time_t *t)
{
#if		HAVE_TIME
	return (struct ee_tm *) localtime((const time_t *)t);
#else
	return ee_localtime(t);
#endif
}
int al_gettimeofday(struct ee_timeval *tp, void *tzp)
{
#if		HAVE_GETTIMEOFDAY
	return gettimeofday ((struct timeval *) tp,tzp);
#else
	return ee_gettimeofday (tp,tzp);
#endif
}

/* NON Standard routines */

int	al_filecmp (const char *file1, const char *file2) 
{
#if	USE_TH_FILEIO
	return ee_filecmp (file1,file2);
#elif	HAVE_FILEIO
	return 1; /* not implemented */
#else
	return 0;
#endif
}
ee_FILE	*al_fcreate(const char *filename, const char *mode, char *data, ee_fsize_t size) 
{
#if	USE_TH_FILEIO
	return ee_fcreate(filename,mode,data,size);
#elif	HAVE_FILEIO
	return (ee_FILE *)1;
#else
	return 0;
#endif
}
int al_dup(int fildes)
{
#if	USE_TH_FILEIO
	return ee_dup(fildes);
#elif	HAVE_FILEIO
	return dup(fildes);
#else
	return 0;
#endif
}

/** Non Standard routine to return file size.
@note If the toolchain has the stat function, a POSIX standard
way is available to return file size.
 */
ee_fsize_t	al_fsize(const char *filename)
{
#if	USE_TH_FILEIO
	return ee_fsize(filename);
#elif	HAVE_STAT_H || HAVE_SYS_STAT_H
/** Get file size using stat function */
    ee_fsize_t	length;
    struct		th_stat st;

    if (!filename || !*filename) 
		length=0;
    else
        if ((th_stat(filename,&st))==-1)
			length=0;
        else
			length = st.st_size;
    return length;
#elif	HAVE_FILEIO
#include	<limits.h>
/* 
 * ANSI C method using fopen, fclose, fread and fseek.
 * You could find a faster method using mingw findfile, or stat
 * NOTE: filesize_t could be a 64 bit int on some hosts.
 * This will NOT be called inside of benchmark timing loop, 
 * Will handle future expansion to Petabyte files...
 * We will be old fasioned and stop at 1Gbyte.
 */
/* Extracted from MERLIN Release 2.8, under GLPL
 * WWW: http://www.noicys.cjb.net - http://run.to/noicys
 * Email: noicys@hotmail.com
 * MERLIN Library made by Ioannis Vranos
 * Copyright (C) 2001, 2002  Ioannis Vranos
 *
 * unsigned long *mfsize(const char *filename)
 * 
 * This function calculates the size of a file. It returns an unsigned long pointer to a 
 * memory space of 6 unsigned long numbers. The first number represents the size of a 
 * file in bytes, the second in Kilobytes, the third in Megabytes, the fourth in Gigabytes, 
 * the fifth in Terabytes, and the sixth in Petabytes.
 * 
 * For example a file size of 2054 bytes will be represented like this:
 * 
 * fsize[0]=6 (bytes), fsize[1]=2 (Kilobytes), fsize[2]=0 (Megabytes),
 * fsize[3]=0 (Gigabytes), fsize[4]=0 (Terabytes), fsize[5]=0 (Petabytes).
 * 
 * That is 2 Kbytes + 6 bytes. It accepts the name of the file (the path is needed if the file 
 * is not in your current directory) as an argument.
 * 
 * The returned pointer points to a dynamically allocated space in memory, so free() can 
 * be used on it. The program must have read access to the file whose size is counted.
 * 
 * In case of error it returns a NULL pointer.
 *
 * NOTE: modified to return ee_fsize_t
 */
{
	FILE *fp=fopen(filename, "rb");
    unsigned long *fsize=calloc(6, sizeof(*fsize)); /* malloc and zero the memory */
	ee_fsize_t	rv;		/* Return value for old fashioned computers that don't support petrabyte files */

    /* Optimization stuff */
    char temp[BUFSIZ];
    static const long DATALENGTH_MAX=LONG_MAX%2!=0?LONG_MAX-1:LONG_MAX;
    long datalength=DATALENGTH_MAX;

    unsigned long i, counter;

    if (fp==NULL)
    {
     free(fsize);
     return 0;
    }

    if (fsize==NULL)
    {
	fclose(fp);
	return 0;
    }

/* fseek() doesn't signal EOF so i use fread() to detect the end of file */
for (fseek(fp, datalength-1, SEEK_SET); datalength>0 && fread(temp, 1, 1, fp)==0; fseek(fp, datalength-1, SEEK_SET))
    datalength/=128;

    fseek(fp, 0, SEEK_SET);

    if (datalength==0 && fread(temp, 1, 1, fp)==0)
    {
		fclose(fp);
        return fsize[0];
    }

    else if (datalength==0)
           datalength=BUFSIZ;

    fseek(fp, datalength-1, SEEK_SET);


    /* fseek() doesn't signal EOF so i use fread() to detect the end of file */
    for(counter=0; fread(temp, 1, 1, fp)!=0; ++counter)
    	fseek(fp, datalength-1, SEEK_CUR);

    fseek(fp, 0, SEEK_SET);

    for( ; counter>0; --counter)
    {
        fseek(fp, datalength, SEEK_CUR);
        fsize[0]+=datalength;

        for (i=0; i<5 && fsize[i]/1024; ++i)
        {
            fsize[i+1]+=fsize[i]/1024;
            fsize[i]%=1024;
        }
    }

    do
    {
        fsize[0]+=datalength=fread(temp, 1, BUFSIZ, fp);

        for (i=0; i<5 && fsize[i]/1024; ++i)
        {
           fsize[i+1]+=fsize[i]/1024;
           fsize[i]%=1024;
        }

    }while(datalength!=0);

	fclose(fp);
	rv = (ee_fsize_t) fsize[0] | fsize[1]<<10 | fsize[2]<<20; /* < 1GB, 32 bits */
	free(fsize);
    return rv;
}
#else
	return 0;
#endif
}

/** Get Environment Variable (libc) 

This routine is used for host based benchmark which use
environment variables. You can set up pre-defined environment
variables here, or return NULL for not found.
@param key Environment variable name
@retval Environment variable value, or NULL if not found.
*/
char	*al_getenv( const char *key )
{
#if	HAVE_GETENV
	return getenv(key);
#else
	return NULL;
#endif
}
/** Get Process ID, usually defined in unistd.h */
ee_pid_t al_getpid( void )
{
#if	HAVE_GETPID
	return (ee_pid_t) getpid();
#else
	return 1; /* Internal benchmark process ID */
#endif
}

#if		!HAVE_VSNPRINTF && HAVE_VSPRINTF
int vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
    int ret;
    ret = vsprintf(str,format,ap);
    if (size>0)
        *str[size]=0;
    return ret;
}
#endif

/*------------------------------------------------------------------------------
 * FUNC   : al_main
 *                                    
 * DESC   : Target Specific Initialization for all Benchmarks
 *
 * PORTING: Use bmark_lite.c: main for benchmark specific init..
 * ---------------------------------------------------------------------------*/
extern	TCDef the_tcdef;

void	al_main( int argc, const char* argv[]  )
{
	int	i;
#ifdef  DO_PROFILE
        moncontrol(0);
#endif

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * AL_SECTION_0
 */

/*
 * Command line processing for all benchmarks. 
 */
	for ( i = 1; i < argc; i++ )
	{
		/* Do not change iterations if CRC_CHECK is being performed. */
#if 	!CRC_CHECK
		if ( argv[i][0] == '-' && toupper( argv[i][1] ) == 'I' )
		{
			/* set the number of tcdef->rec_iterations from the command line */
			if ( isdigit( argv[i][2] ) )
				the_tcdef.rec_iterations = (LoopCount)atol( argv[i]+2 );
			else if ( i < (argc-1) && isdigit( argv[i+1][0] ) )
				the_tcdef.rec_iterations = (LoopCount)atol( argv[i+1] );
		}
#endif
		/*
		 * Strip -autogo if mistakenly passed in, 
		 * or produce warning rather than change all const declarations in call path.
		 */
		if ((strcmp(argv[i],"-autogo"))==0)
			/*argv[i][0] = '\0';*/
			th_printf("Warning: TH Regular option -autogo passed on command line.\n");
	}

	/*
	> Perform target specific command line processing here.
	> Many systems will not need to put anything in this section. However,
	> special command line options may make porting your benchmarks easier.
	*/

#if 	!HOST_EXAMPLE_CODE
#endif
   
	/* Initialize memory management (heap) data structures */
	mem_heap_initialize();

	/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	* AL_SECTION_1
	*/

	/*
	> Perform target specific initialization here.  This should be really
	> low level code.  Many systems will not need to put anything in this
	> section.  However, your HW may require some initialization before
	> the logical console I/O channel opened.  That kind of stuff goes here.
	*/
#if 	!HOST_EXAMPLE_CODE
#endif

   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * AL_SECTION_2
    *
    * Open the logical console I/O channel. This should be done as soon
    * as possible in the initialization process.  Error messages cannot
    * be sent to the logical console until this call is made.
	*/

   /* NOTE: In TH Regular, this is done by: al_lc_open(); */
#if 	!HOST_EXAMPLE_CODE
#endif

   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * AL_SECTION_3
   */

   /*
   >> Most of the system initialization code should go here.
   */
#if 	!HOST_EXAMPLE_CODE
#endif

}

/*
 * In TH Lite, this is the last step called by main in all the benchmarks.
 * In TH Regular, this is the last step in the main defined in thal.c
 * NOTE: ev from th_exit is passed, or 0 if not from an exit.
 */

void al_hardware_reset(int ev)
{
   /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    * AL_SECTION_7
    */

   /*
   >> Here is where you can do any last cleanup that needs to happen
   >> after you close the Logical Console I/O channel.
   */
	if (ev == 0)
	{
		void ee_destroy_filelist();
		ee_destroy_filelist();
		/* Normal Termination */
#if 	!HOST_EXAMPLE_CODE
#endif
	} else
	{
		/* Terminate has occurred from th_exit */
#if 	!HOST_EXAMPLE_CODE
#endif
	}
#if VS_LEAK_DETECT
	_CrtDumpMemoryLeaks();
#endif

}
/** @} */
/** @} */
