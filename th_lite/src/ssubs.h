/**
 * @file
 * @brief  Test Harness routines for benchmarks
 *
 * $RCSfile: ssubs.h,v $
 *
 * @author  ECL, LLC
 *
 *  EEMBC : Technical Advisory Group (TechTAG)
 *
 *    CVS : $Revision: 1.2 $
 *          $Date: 2006/03/09 17:34:18 $
 *          $Author: rick $
 *          $Source: /usr/local/cvs/eembc2/th_lite/src/ssubs.h,v $
 *          
 * @note   
 *
 *
 * HISTORY :
 *
 * $Log: ssubs.h,v $
 * Revision 1.2  2006/03/09 17:34:18  rick
 * Version 2 Office Release Candidate 5
 *
 * Revision 1.11  2005/12/02 23:53:35  rick
 * Fix mixed EOL format causing ^M's to appear in Unix checkouts.
 *
 * Revision 1.10  2005/09/10 04:02:24  rick
 * eol update, add uu_send_file
 *
 * Revision 1.9  2005/04/27 20:33:14  rick
 * Copyrite update 2005
 *
 * Revision 1.8  2004/12/08 23:27:18  rick
 * New standard header for documentation generation.
 *
 * Revision 1.6  2004/09/03 22:29:25  rick
 * New Office Textv2 functions
 *
 * Revision 1.5  2004/06/23 05:55:23  rick
 * EE_REDIRECT, and Shared Files
 *
 * Revision 1.4  2004/01/22 00:56:52  rick
 * Release cleanup, copyright year corrections
 *
 * Revision 1.3  2002/04/23 18:33:56  rick
 * Match eembc_dt with Lite, remove stdinc.h
 *
 * Revision 1.2  2002/03/21 22:31:09  rick
 * Network Harness, and empty benchmark fixes
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

#include "eembc_dt.h"

/** @addtogroup SHFL
@{ */
/** @addtogroup ssubs_c Functional Layer String Maniupulation
@{ */

#ifndef   SSUBS_H
#define   SSUBS_H
#ifdef __cplusplus
extern "C" {
#endif

/*- Function Prototypes ------------------------------------------------------*/

char  last_char( char *s );

void  char_remove( char *s, int i );
void  char_remove_n( char *s, int i, int n );

void  strip_l_spaces( char *s );    /* Leading */
void  strip_lt_spaces( char *s );   /* Trailing */
void  strip_t_spaces( char *s );    /* Leading & Trailing */
void  strip_t_crlf( char *s );		/* Trailing CRLF */
void  strip_all_spaces( char *s );  /* All */

void  make_simple_nl( char *str );

int   is_all_white_space( const char *s );

int   cpystr( char *dest, const char *src, int len );
int   cpypaddstr( char *dest, const char *src, int len );

void  paddstr( char *s, int len );

int   tabs_to_spaces( char *line, int tab );

unsigned int conv_to_ui( const char *str );
unsigned long conv_to_ul( const char *str );

int str_cmp( const char *s1, const char *s2 );
int str_icmp( const char *s1, const char *s2 );

int xlate_nl_inplace( char *str );
int xlate_nl( const char *str, char *dest_buf );

#ifdef __cplusplus
   }
#endif
#endif /* File Sentinel */
/** @} */
/** @} */
