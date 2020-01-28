/*==============================================================================
 *$RCSfile: harness.h,v $
 *
 *   DESC : Application Specific TH definitions
 *
 * AUTHOR : Rick Foos, ECL, LLC
 *
 *  EEMBC : Office
 *
 *    CVS : $Revision: 1.5 $
 *          $Date: 2005/04/27 20:37:46 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/office/harness.h,v $
 *          
 * NOTE   : These can override thcfg.h ONLY if wrapped in #ifndefs. Wrap
 *          defines with #ifndef here as well so compiler line override 
 *          is possible.
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: harness.h,v $
 * Revision 1.5  2005/04/27 20:37:46  rick
 * Copyrite update 2005
 *
 * Revision 1.4  2004/01/29 00:33:28  rick
 * Resolve header file cycles
 *
 * Revision 1.3  2004/01/22 20:20:50  rick
 * Copyright update and cleanup
 *
 * Revision 1.2  2002/10/10 17:59:49  rick
 * Resolve timevar,timezone compilation with GS_TIMEVAL
 *
 * Revision 1.1  2002/07/26 20:56:26  rick
 * Add harness.h for Application overrides
 *
 *
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
 * ===========================================================================*/

#if	!defined(HARNESS_H)
#define	HARNESS_H

#if	VER==v2
/*
 * If Ghostscript compilatation fails because timeval and timezone
 * change undef to define.
 * (Solaris gcc requires this)
 */
#undef	GS_TIMEVAL
#endif

/** Code has Byte define, do not re-define */
#if		!defined(HAVE_BYTE_DEFINE)
#define	HAVE_BYTE_DEFINE	(TRUE)
#endif

#define _CRT_SECURE_NO_DEPRECATE 1
#undef UNICODE

#endif /* File Sentinal */

