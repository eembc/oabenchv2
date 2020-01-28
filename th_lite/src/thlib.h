/**
 * @file
 * @brief  Test Harness Library Interface
 * 
 *$RCSfile: thlib.h,v $
 *
 *  EEMBC : EEMBC Technical Advisory Group (TechTAG)
 *
 * @author  Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.49 $
 *          $Date: 2005/12/02 23:53:37 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/techtag/th_lite/src/thlib.h,v $
 *          
 * @note   
 *          This header file contains the interface fuctions and
 *          structures for the Test Harness Library, which implements
 *          the API.
 *
 *
 * HISTORY :
 *
 * $Log: thlib.h,v $
 * Revision 1.49  2005/12/02 23:53:37  rick
 * Fix mixed EOL format causing ^M's to appear in Unix checkouts.
 *
 * Revision 1.48  2005/09/10 04:02:24  rick
 * eol update, add uu_send_file
 *
 * Revision 1.47  2005/04/27 20:33:15  rick
 * Copyrite update 2005
 *
 * Revision 1.46  2004/12/08 23:27:19  rick
 * New standard header for documentation generation.
 *
 * Revision 1.45  2004/10/26 22:51:47  rick
 * Add stdio.h for off_t, NULL and EOF defines in some tool chains.
 *
 * Revision 1.44  2004/09/11 01:53:12  administrator
 * Modifications for armrv
 *
 * Revision 1.43  2004/07/01 17:37:27  rick
 * Add th_crcbuffer, and place all redirection includes inside file sentinel.
 *
 * Revision 1.42  2004/06/29 19:36:46  rick
 * EE_REDIRECT, and Shared file for Regular and Lite
 *
 * Revision 1.41  2004/06/23 05:55:05  rick
 * EE_REDIRECT, and Shared Files
 *
 * Revision 1.40  2004/04/15 16:46:07  rick
 * fread/fwrite rv, size, and count to size_t
 *
 * Revision 1.39  2004/03/10 23:57:30  rick
 * fix dirent calls
 *
 * Revision 1.38  2004/03/10 00:18:29  rick
 * Add scanf family, vfprintf, and new doscan
 *
 * Revision 1.37  2004/02/20 00:24:43  rick
 * change ee_dirent from typedef to struct
 *
 * Revision 1.36  2004/02/12 23:35:03  rick
 * Add fputs, macro fixes to thstdio
 *
 * Revision 1.35  2004/02/10 06:55:37  rick
 * Add fileio calls and stdio re-router
 *
 * Revision 1.34  2004/02/05 23:03:50  rick
 * Harness update with portable dirent
 *
 * Revision 1.33  2004/01/28 23:08:31  rick
 * Add th_strdup, fileio cwd
 *
 * Revision 1.32  2004/01/22 00:57:49  rick
 * Release cleanup, copyright year corrections
 *
 * Revision 1.31  2003/07/26 18:29:38  rick
 * Fix include paths
 *
 * Revision 1.30  2003/06/03 18:57:07  rick
 * Add th_srand, and initialization
 *
 * Revision 1.29  2003/05/28 23:08:49  rick
 * Move GRAND to th_rand
 *
 * Revision 1.28  2003/04/18 15:05:49  rick
 * Add ftell, vfscanf, vsscanf
 *
 * Revision 1.27  2003/04/11 22:13:10  rick
 * Add th_vsprintf, remove Go define
 *
 * Revision 1.26  2003/04/04 18:47:32  rick
 * Fix file sentinel
 *
 * Revision 1.25  2003/03/26 00:18:12  rick
 * Add scanf functions
 *
 * Revision 1.24  2003/03/06 00:34:53  rick
 * Add th_fgets, and %g to printf
 *
 * Revision 1.23  2003/03/05 00:28:58  rick
 * Change th_fcreate size to ee_fsize_t
 *
 * Revision 1.22  2003/01/22 00:01:12  rick
 * Add File I/O to Regular
 *
 * Revision 1.21  2003/01/17 22:44:37  rick
 * Add File I/O to harness
 *
 * Revision 1.20  2002/12/31 16:21:02  rick
 * Add harness stubs for memmgr
 *
 * Revision 1.19  2002/07/19 19:29:24  rick
 * Replace eembc_id string with Benchmark ID
 *
 * Revision 1.18  2002/06/28 17:00:11  rick
 * Beta 2 Documentation
 *
 * Revision 1.17  2002/05/14 19:12:22  rick
 * Add th_sprintf for bmdebug calls
 *
 * Revision 1.16  2002/05/10 17:09:08  rick
 * Add al_main to API
 *
 * Revision 1.15  2002/04/23 18:34:06  rick
 * Match eembc_dt with Lite, remove stdinc.h
 *
 * Revision 1.14  2002/04/04 17:03:22  rick
 * thvinfo 4.0B1
 *
 * Revision 1.13  2002/04/03 23:18:46  rick
 * Clear warnings from gcc
 *
 * Revision 1.12  2002/03/18 21:15:09  rick
 * Add al_report, cyclecount, crc fix in iirflt, and pktflow.
 *
 * Revision 1.7  2002/03/12 21:45:54  rick
 * TH Lite harness updates, and Build changes from directory changes
 *
 * Revision 1.13  2002/03/11 22:11:49  rick
 * ITERATIONS, CRC_CHECK, NON_INTRUSIVE TCDef Usage
 *
 * Revision 1.12  2002/03/08 00:30:37  administrator
 * Fix Endian definition, vprintf, and rotate endian crc's
 *
 * Revision 1.10  2002/02/27 17:40:49  rick
 * Update Documentation and API comments for 0.3
 *
 * Revision 1.9  2002/02/25 17:15:35  rick
 * Add comment blocks, fix atime th_report call.
 *
 * Revision 1.8  2002/02/21 19:52:11  administrator
 * Build TH_Lite makefile for cygwin
 *
 * Revision 1.7  2002/02/19 20:12:09  rick
 * Add long copyright message per Alan.
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
#if VS_LEAK_DETECT
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif
/** Some tool chains define off_t, NULL, EOF here. */
#include <stdio.h>
#include "eembc_dt.h"
#include "thvinfo.h"
#include "therror.h"
/** Get al_main for bmark_lite. */
#include "thal.h"

/** Memory management, and rand routines */
#include "thstdlib.h"
/** String routine(s). */
#include "thstring.h"
/** Unix Standard routines. */
#include "thunistd.h"
/** File control definitions */
#include "thfcntl.h"
/** Display Control, File I/O - Streams, scanf, and Basic file I/O routines */
#include "thstdio.h"
/** DIRENT routines, and helpers */
#include "thdirent.h"
/** STAT routines. */
#include "thstat.h"

/** @addtogroup THLFL
@{ */
/** @addtogroup thlib_h Test Harness Library Interface
@{ */

/** File Sentinal */
#ifndef THLIB_H
#define	THLIB_H
#ifdef __cplusplus
extern "C" {
#endif

#define		VN_BAD_PTR          0x0001
#define		VN_BAD_MAJOR        0x0002
#define		VN_BAD_MINOR        0x0004
#define		VN_BAD_STEP         0x0008
#define		VN_BAD_REVISION     0x0010
#define		VN_EMPTY_STR        0x0020
#define		VN_BAD_VER_IND      0x0040
#define		VN_MAJOR_TOO_BIG    0x0080
#define		VN_MINOR_TOO_BIG    0x0100
#define		VN_REVISION_TOO_BIG 0x0200
#define		VN_BAD_PERIOD       0x0400

/*------------------------------------------------------------------------------
 * Typedefs and Structs
 */

typedef struct
{
   unsigned char  major;
   unsigned char  minor;
   unsigned char  step;
   unsigned char  revision;
}  version_number;

/*------------------------------------------------------------------------------
 * Test Component Defintion
 *
 * A const pointer to this sturcture is returned from test component's
 * entry point to the test harness.  It is used by the test harness to
 * control the test or benchmark.
 *----------------------------------------------------------------------------*/

/* TCDef.revsion == 1  { this is revision 1 of this structure } */

#define TCDEF_REVISION (2)

typedef struct TCDef{
   /*------------------------------------
    * This section is the same 
    * for all versions of this structure
    */
   char				eembc_bm_id[ 16 ];/* id flag */
   char				member[ 16 ];     /* the member id */
   char				processor[ 16 ];  /* the processor id */
   char				platform[ 16 ];   /* the platform id */
   char				desc[ 64 ];       /* benchmark description */
   e_u16			revision;         /* The revision of this structure. */

   /*------------------------------------*/

   version_number	th_vnum_required;  /* TH Version Required        */
   version_number	target_vnum_required;  /* Target Hardware Version Required */
   version_number	bm_vnum;  /* the version of this bench mark */
   e_u32  			rec_iterations;

   /*
    * Test Harness Results
    */
   e_u32			iterations;
   e_u32            duration;
   e_u16            CRC;
   size_t			v1;		/* Verification Data, can be double via union */
   size_t			v2;
   size_t			v3;
   size_t			v4;
} TCDef;


/*----------------------------------------------------------------------------*/

/** DEPRECATED */
#define FILE_NAME_SIZE (128)
/** DEPRECATED */
typedef size_t BlockSize;
/** DEPRECATED */
typedef struct FileDef
   {
   char          name[ FILE_NAME_SIZE ];  /* the file name */
   BlockSize     size;                    /* the file size */
   char         *buf;                     /* the buffer that holds the file */
   Dword         crc;                     /* the file's CRC */
   BlockSize     buf_size;                /* the size of the buffer */
   }
FileDef;

/** Keep FD_SIZE and even multiple of 4 */
#define FD_SIZE ((size_t)ROUNDUP4(sizeof(FileDef)*2))

/*------------------------------------------------------------------------------
 * The Test Harness API
 *----------------------------------------------------------------------------*/

/* Display Control - Also see thstdio.h */

int    th_putb( const char *b, size_t buf_size );
int    th_sends( const char *s );

/* Console routines */
size_t	th_read_con( char *buf, size_t buf_size );
size_t	th_con_chars_avail( void );

/** Internal to harness. */
void	mem_heap_initialize(void);

/* Test Harness Timer Routines */

int		th_timer_available( void );
int		th_timer_is_intrusive( void );
int 	th_is_timer_running( void );
size_t	th_ticks_per_sec( void );
size_t	th_tick_granularity( void );
void	th_signal_start( void );
size_t	th_signal_finished( void );

/* Test Harness System Routines */

void	th_exit( int exit_code, const char *fmt, ... );
int		th_report_results(TCDef *tcdef, e_u16 Expected_CRC );
int		th_harness_poll( void );

/** DEPRECATED, use Harness File System in fileio.c */
const FileDef *th_get_file_def( const char *fn );
/** DEPRECATED, use Harness File System in fileio.c */
const FileDef *th_get_file_num( int n );

/** UUencode buffer to stdout which can be uudecoded to filename on host. */
int th_send_buf_as_file( const char* buf, BlockSize length, const char* fn );

/*  CRC and Utilities */

e_u16 Calc_crc8(e_u8 data, e_u16 crc );
e_u16 Calc_crc16( e_u16 data, e_u16 crc );
e_u16 Calc_crc32( e_u32 data, e_u16 crc );
e_u16 th_crcbuffer(const void *inbuf,size_t size,e_u16 inputCRC);
int change_data(int argc, const char* argv[], char **data_name );

/* NON Standard File I/O Routines */

int      th_filecmp (const char *file1, const char *file2);
ee_FILE *th_fcreate (const char *filename, const char *mode, char *data, ee_fsize_t size);
ee_fsize_t th_fsize (const char *filename);
int th_dup(int fildes);

/*----------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif /* THLIB_H */ 
/** @} */
/** @} */
