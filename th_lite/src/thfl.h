/**
 * @file
 * @brief  Test Harness routines for benchmarks
 * 
 *$RCSfile: thfl.h,v $
 *
 * @author  ECL, LLC
 *
 *  EEMBC : Technical Advisory Group (TechTAG)
 *
 *    CVS : $Revision: 1.3 $
 *          $Date: 2006/03/09 17:34:18 $
 *          $Author: rick $
 *          $Source: /usr/local/cvs/eembc2/th_lite/src/thfl.h,v $
 *          
 * @note   
 *
 *
 * HISTORY :
 *
 * $Log: thfl.h,v $
 * Revision 1.3  2006/03/09 17:34:18  rick
 * Version 2 Office Release Candidate 5
 *
 * Revision 1.9  2005/12/02 23:53:37  rick
 * Fix mixed EOL format causing ^M's to appear in Unix checkouts.
 *
 * Revision 1.8  2005/09/10 04:02:24  rick
 * eol update, add uu_send_file
 *
 * Revision 1.7  2005/04/27 20:33:15  rick
 * Copyrite update 2005
 *
 * Revision 1.6  2004/12/08 23:27:18  rick
 * New standard header for documentation generation.
 *
 * Revision 1.5  2004/07/09 05:11:21  rick
 * Add gettimeofday
 *
 * Revision 1.4  2004/07/01 17:37:27  rick
 * Add th_crcbuffer, and place all redirection includes inside file sentinel.
 *
 * Revision 1.3  2004/06/23 05:55:05  rick
 * EE_REDIRECT, and Shared Files
 *
 * Revision 1.2  2004/02/11 02:56:08  rick
 * Add macro redefinitions, improve efn and fileio
 *
 * Revision 1.1  2004/01/28 23:08:31  rick
 * Add th_strdup, fileio cwd
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

#ifndef   THFL_H        /* File Sentinal */
#define   THFL_H

#include "thcfg.h"
#include "thstdint.h"
#include "thtime.h"

/** @addtogroup THLFL
@{ */
/** @addtogroup thfl_h Functional layer internal prototypes
@{ */

#ifdef __cplusplus
extern "C" {
#endif

void	*i_malloc( size_t size, const char *fn, int line );
void	*i_calloc( size_t nmemb, size_t size, const char *fn, int line );
void	*i_realloc( void *block, size_t size, const char *fn, int line );
char	*i_strdup( const char *string, const char *fn, int line );
void	i_free( void *block, const char *fn, int line );
void	i_heap_reset( void );

e_u16	t_crcbuffer(const void *inbuf,size_t size,e_u16 inputCRC);

int		t_rand( void );
void	t_srand(unsigned int seed);
void	t_exit( int exit_code, const char *fmt, ... );

char *efn( const char *fn );
char *epn( const char *fn );

/* Time Routines. */

ee_time_t ee_time(ee_time_t *t);
struct ee_tm *ee_localtime(const ee_time_t *t);
int ee_gettimeofday(struct ee_timeval *tp, void *tzp);

#define SOURCE_FILE efn( __FILE__ )

#ifdef __cplusplus
   }
#endif
#endif                /* File Sentinal */
/** @} */
/** @} */
