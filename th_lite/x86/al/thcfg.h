/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

/** @addtogroup THLAL
@{ */
/** @addtogroup THCFG_H Test Harness Configuration
@{ */

#ifndef THCFG_H
#define THCFG_H

/**
 * Enable Host specific code for host based execution using an OS.
 * HOST_EXAMPLE_CODE can also be used to mark porting changes
 */
#if		!defined(HOST_EXAMPLE_CODE)
#define	HOST_EXAMPLE_CODE	(0)
#endif

/** Porting section to add Target specific include files. */
#if 	!HOST_EXAMPLE_CODE
/* Target specific includes go here */
#endif

/** Set FALSE definition.
 *
 * @note Also defined in eembc_dt.h, and some target compilers.
 * we need these to be correct here.
 */
#ifndef	FALSE
#undef	FALSE
#define FALSE   (0)
#endif
/** Set TRUE definition.
 *
 * @note Also defined in eembc_dt.h, and some target compilers.
 * we need these to be correct here.
 */
#ifndef TRUE
#undef	TRUE
#define TRUE    (!FALSE)
#endif

/** Subcommittee Specific Overrides to TH config are in this file. */
#include "harness.h"

/** Company, Processor and Target specific information
 *
 * @remark This data is displayed by th_report_results.
 */
#include "thvinfo.h"

/** Toolchain Header file and function configuration. */
#include "thconfig.h"

#if 	HOST_EXAMPLE_CODE
/** EEMBC member company name */
#define EEMBC_MEMBER_COMPANY   "EEMBC"
/** Processor or DSP name. */
#define EEMBC_PROCESSOR        "HOST PROCESSOR"
/** Name of Target System/Processor description. */
#define EEMBC_TARGET           "32 Bit"
#else
/** EEMBC member company name */
#define EEMBC_MEMBER_COMPANY   "EEMBC"
/** Processor or DSP name (16 chars=15 + 1 reserved for a 0.). */
#define EEMBC_PROCESSOR        "TargetProcessor"
/** Name of Target System/Processor description. */
#define EEMBC_TARGET           "32 Bit"
#endif

/** Target System/Processor Major Revision. */
#define TARGET_MAJOR           0
/** Target System/Processor Minor Revision. */
#define TARGET_MINOR           0
/** Target System/Processor Stepping. */
#define TARGET_STEP            'R'
/** Target System/Processor sub-revision. */
#define TARGET_REVISION        0

/** Target Timer Available */
#define TARGET_TIMER_AVAIL     (TRUE)
/** Target Timer Intrusive (can effect performance score) */
#define TARGET_TIMER_INTRUSIVE (TRUE)

/**
 * Set BMDEBUG to a (TRUE) to enable debugging printf's etc etc.
 * Set it to a (FALSE) for the released version of the BM
 */
#if !defined( BMDEBUG )
#define BMDEBUG (FALSE)
#endif

/**
 * Set EE_POWERTAG to a (TRUE) to enable Power Measurement.
 * Set it to a (FALSE) for normal operation.
 */
#if !defined( EE_POWERTAG )
#define EE_POWERTAG (FALSE)
#endif

/**
 * Define BIG or LITTLE Endian here.  Note, do not define both to a (TRUE) or
 * both to a (0), one (and only one) of these must be set to a (TRUE)
 * @note If not defined from COMPILER_DEFINES in toolchain file, Set it here. 
 * Default is Little Endian.
 */
#if !defined( EE_BIG_ENDIAN ) && !defined( EE_LITTLE_ENDIAN)
#define EE_BIG_ENDIAN    (FALSE)
#define EE_LITTLE_ENDIAN (TRUE)
#endif

#if !defined( EE_LITTLE_ENDIAN ) 
#if EE_BIG_ENDIAN
#define EE_LITTLE_ENDIAN (FALSE)
#else
#define EE_LITTLE_ENDIAN (TRUE)
#endif
#endif

#if !defined( EE_BIG_ENDIAN )
#if EE_LITTLE_ENDIAN
#define EE_BIG_ENDIAN (FALSE)
#else
#define EE_BIG_ENDIAN (TRUE)
#endif
#endif

#if EE_BIG_ENDIAN && EE_LITTLE_ENDIAN
#error "Cannot have both Big and Little Endian True"
#endif

#if !EE_BIG_ENDIAN && !EE_LITTLE_ENDIAN
#error "Cannot have both Big and Little Endian False"
#endif
/* for systems that are not 32b */
#if !defined(EE_SIZEOF_PTR)
#define EE_SIZEOF_PTR 4
#define EE_PTR_ALIGN 4
#endif
#if !defined(EE_PTR_ALIGN)
#error "Please define pointer alignment size"
#endif
#if !defined(EE_SIZEOF_LONG)
#define EE_SIZEOF_LONG 4
#define EE_LONG_MOD2 2
#define EE_LONG_ALIGN 4
#endif

#if !defined(EE_LONG_ALIGN)
#error "Please define long alignment size"
#endif
#if !defined(EE_LONG_MOD2)
#error "Please define EE_LONG_MOD2 (log2 of sizeof long)"
#endif
/** Floating point supported in compiler.
 * Set FLOAT_SUPPORT to (TRUE) if the target has floating point, or compiler
 * supports floating point emulation.
 *
 * Set FLOAT_SUPPORT to (FALSE) if not.
 *
 */
#if !defined( FLOAT_SUPPORT )
#define FLOAT_SUPPORT (TRUE)
#endif

/**
 *  HEAP Control Section
 *  @note: See heapport.h for enabling debug on internal heap manager.
 */

/**
 * Set COMPILE_OUT_HEAP to TRUE to completely 'compile out' the test harness
 * memory allocation routines.
 * To use compiler's malloc support, set HAVE_MALLOC to true.
 * @verbatim
 * COMPILE_OUT_HEAP	TRUE,	HAVE_MALLOC TRUE, use compiler's heap manager.
 * COMPILE_OUT_HEAP	FALSE,	HAVE_MALLOC FALSE, use internal heap manager.
 * COMPILE_OUT_HEAP	TRUE,	HAVE_MALLOC FALSE, minimize code size (no malloc).
 * COMPILE_OUT_HEAP	FALSE,	HAVE_MALLOC TRUE, maximize code size (invalid).
 * @endverbatim
 */
#if !defined (COMPILE_OUT_HEAP)
#define COMPILE_OUT_HEAP (TRUE)
#endif
/** Your libc has malloc, calloc, realloc, and free.*/
#if !defined (HAVE_MALLOC)
#define HAVE_MALLOC (TRUE)
#endif

/** Validation of Internal heap manager, and libc heap manager */
#if !COMPILE_OUT_HEAP && HAVE_MALLOC
#error	"COMPILE_OUT_HEAP is false, and HAVE_MALLOC is true. Cannot select both internal and compiler malloc functions."
#endif

/**
 * Turn this on to map malloc() and free() calls to th_malloc()
 * and th_free().  Note: you only need to do this if you use
 * functions in your C library that indirectly call malloc() and free().
 *
 * @warning If malloc is called before C program start (by kernel or crt0)
 * this option CANNOT be used. The harness dectects, and attempts to fail with
 * exit code 8 (THE_OUT_OF_MEMORY). Trap code for this case cannot be 
 * guaranteed to work before C program load and initialization.
 */
#if !defined ( MAP_MALLOC_TO_TH )
#define MAP_MALLOC_TO_TH (FALSE)
#endif

#if COMPILE_OUT_HEAP && MAP_MALLOC_TO_TH
#error "COMPILE_OUT_HEAP && MAP_MALLOC_TO_TH invalid. Set one to FALSE"
#endif

/**
 * CRC Verification Section.
 *
 * Set CRC_CHECK to TRUE to enable Intrusive CRC checking.
 * When CRC_CHECK is enabled, required # of iterations set during compile.
 * Do NOT use when measuring timing for certification.
 */
#if	!defined(CRC_CHECK)
#define CRC_CHECK				(FALSE)
#endif
/** Non-Intrusive CRC check.
 *
 * Set NON_INTRUSIVE_CRC_CHECK to TRUE to enable Non-Intrusive CRC checking.
 * Non Intrusive CRC check is done outside of benchmark timing, and
 * is independent of the number of iterations.
 * You MAY use this when measuring timing for certification.
 */
#if	!defined(NON_INTRUSIVE_CRC_CHECK)
#define	NON_INTRUSIVE_CRC_CHECK	(TRUE)
#endif

#if		CRC_CHECK && NON_INTRUSIVE_CRC_CHECK
#error	"CRC_CHECK and NON_INTRUSIVE_CRC_CHECK are enabled. Set one of them to FALSE"
#endif

/**
 * Display results in th_report_results using integers.
 * VERIFY_INT - v1, v2, v3, v4 as size_t
 */
#if !defined(VERIFY_INT)
#define VERIFY_INT (TRUE)
#endif

/**
 * Display results in th_report_results using floating point.
 * VERIFY_FLOAT - v1,v2 -> double v1v2, and v3,v4 -> double v3v4.
 *
 * This is defined on a PER BENCHMARK basis. The bmark, using a union
 * loads two integer fields with one floating point result.
 *
 * @note VERIFY_FLOAT is used in telecom benchmarks to display 
 * automatically calculated diffmeasure results 
 */
#if !defined(VERIFY_FLOAT)
#define	VERIFY_FLOAT (FALSE)
#endif

/**
 * Set USE_TH_PRINTF to (FALSE) to use the printf engine that comes with
 * your compiler's C Library.
 *
 * Set USE_TH_PRINTF to (TRUE) to use the printf engine that is built into
 * the Test Harness.
 */
#if !defined( USE_TH_PRINTF )
#define USE_TH_PRINTF (FALSE)
#endif

/** Do not Translate CRLF for serial terminal */
#if !defined( NO_CRLF_XLATE )
#define NO_CRLF_XLATE (TRUE)
#endif

/** Use th_harness_poll in BMDEBUG mode. Inactive in th lite */
#if !defined( USE_TH_HARNESS_POLL )
#define	USE_TH_HARNESS_POLL	(FALSE)
#endif

/** Use Test Harness Streams calls (RAM File System).
 *
 * Set USE_TH_FILEIO to (FALSE) to use the File System I/O that comes with
 * your compiler's C Library (stdio.h). Make sure your embedded target has a 
 * block device and drivers that can be used.
 *
 * Set USE_TH_FILEIO to (TRUE) to use the RAM file engine that is built into
 * the Test Harness.
 * 
 * For specific needs (i.e. Read from RAM file, ignore Writes) modifiy thal.c
 */
#if !defined( USE_TH_FILEIO )
#define USE_TH_FILEIO (TRUE)
#endif

/**
 * Set HAVE_FILEIO to (FALSE) if your compiler's C Library does not have support
 * for stdio stream routines: fopen,fclose,fread,fwrite,vfprintf,putc,getc,ungetc, fgets,
 * feof, ferror, and, tmpfile. 
 * These may be individually controlled in thal.c.
 *
 * Set HAVE_FILEIO to (TRUE) if your compiler's C Library has support for file
 * I/O. USE_TH_FILEIO (TRUE), overrides this and the harness RAM file routines
 * are used.
 * 
 * For specific needs modifiy thal.c
 */
#if !defined( HAVE_FILEIO )
#define HAVE_FILEIO (TRUE)
#endif

/** Set this define to 1 if the benchmark is using ee_dirent.
If the benchmark is using a libc defined dirent set this to FALSE
*/
#if	!defined(USE_EE_DIRENT)
#define USE_EE_DIRENT	1
#endif

/** Set this define to 1 if the benchmark is using th_stat.
If the benchmark is using a libc defined stat set this to FALSE
*/
#if	!defined(USE_TH_STAT)
#define USE_TH_STAT	1
#endif

/** Heap alignment specific to Networking benchmarks. */
#if !defined( HEAP_ALIGN_V )
#define HEAP_ALIGN_V	8
#endif

/** Maximum size of Internal Heap.
@note See thal.c to determine if heap memory is allocated as static array, or with libc malloc.
*/
#if !defined(HEAP_SIZE)
#define HEAP_SIZE	(1024*1024*4)	/* 4 Mb */
#endif

/** Command Line Size (TH Regular only).
 *
 * This define is used to set the size of the buffer used to hold the
 * benchmark command line.  E.g. the 'argc' and 'argv' arguments will
 * be in this buffer.
 *
 * @note that two buffers of CMD_LINE_SIZE are allocated.  Normaly, you will not
 * have to change this.  But, if your system is low on memory, you can make
 * CMD_LINE_SIZE smaller.  
 * @warning It is not a good idea to go below 128 bytes, Some benchmarks may fail.
 */
#define CMD_LINE_SIZE         (1024)
/** Maximum number of argc variables passed through to benchmark. */
#define MAX_ARGC              (128)

/** Enable function re-direction defines to harness. */
#ifndef		EE_REDIRECT
#define 	EE_REDIRECT	(FALSE)
#endif

/** 
 * @todo Remove eembc_dt.h defines that use common names.
 * The purpose of this section is to disable eembc_dt extended definitions
 * for applications that have conflicts. 
 * @warning USE CAREFULLY, A TH Library compiled
 * with different definitions than an application may have side effects. In 
 * this case, eembc_dt.h itself will need to be changed to support the application.
 * YOU are responsible for this as part of porting.
 *
 * Control for low level definitions, patterned after autoheader.
 * All are wrapped defines so that benchmarks can override in harness.h, or as needed.
 * Also used inside of benchmarks which may internally define these types
 * for different purposes.
 */

/** Use TH Byte define. Benchmark may have conflicting internal definition */
#if		!defined(USE_TH_BYTE_DEFINE)
#define	USE_TH_BYTE_DEFINE	(TRUE)
#endif
/** Use TH Short define. Benchmark may have conflicting internal definition */
#if		!defined(USE_TH_SHORT_DEFINE)
#define	USE_TH_SHORT_DEFINE	(TRUE)
#endif
/** Use TH Long define. Benchmark may have conflicting internal definition */
#if		!defined(USE_TH_LONG_DEFINE)
#define	USE_TH_LONG_DEFINE	(TRUE)
#endif
/** Use TH Bool define. Benchmark may have conflicting internal definition */
#if		!defined(USE_TH_BOOL_DEFINE)
#define	USE_TH_BOOL_DEFINE	(TRUE)
#endif
/** Use TH SUCCESS define. Benchmark may have conflicting internal definition */
#if		!defined(USE_TH_SUCCESS_DEFINE)
#define	USE_TH_SUCCESS_DEFINE	(TRUE)
#endif
/** Use TH FAILURE define. Benchmark may have conflicting internal definition */
#if		!defined(USE_TH_FAILURE_DEFINE)
#define	USE_TH_FAILURE_DEFINE	(TRUE)
#endif
/** Use TH Enable define. Benchmark may have conflicting internal definition */
#if		!defined(USE_TH_ENABLE_DEFINE)
#define	USE_TH_ENABLE_DEFINE	(TRUE)
#endif

#endif /* THCFG_H file sentinel */

/** @} */
/** @} */
