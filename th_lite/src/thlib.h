/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
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
