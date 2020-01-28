/**
 * @file
 * @brief Prototypes for uuencode
 *
 * $RCSfile: uuencode.h,v $
 *
 *  EEMBC : EEMBC Technical Advisory Group (TechTAG)
 *
 * @author  Sergei Larin
 *
 *    CVS : $Revision: 1.3 $
 *          $Date: 2006/03/09 17:34:18 $
 *          $Author: rick $
 *          $Source: /usr/local/cvs/eembc2/th_lite/src/uuencode.h,v $
 *          
 * @note   
 *
 *
 * HISTORY :
 *
 * $Log: uuencode.h,v $
 * Revision 1.3  2006/03/09 17:34:18  rick
 * Version 2 Office Release Candidate 5
 *
 * Revision 1.13  2005/12/02 23:53:39  rick
 * Fix mixed EOL format causing ^M's to appear in Unix checkouts.
 *
 * Revision 1.12  2005/09/10 04:02:24  rick
 * eol update, add uu_send_file
 *
 * Revision 1.11  2005/04/27 20:32:56  rick
 * Copyrite update 2005
 *
 * Revision 1.10  2004/12/08 23:27:48  rick
 * New standard header for documentation generation.
 *
 * Revision 1.9  2004/06/23 05:55:25  rick
 * EE_REDIRECT, and Shared Files
 *
 * Revision 1.8  2004/04/17 00:32:55  rick
 * Restore HAVE_STAT, Fix size_t
 *
 * Revision 1.7  2004/03/19 21:16:04  rick
 * Fix uuencode table
 *
 * Revision 1.6  2004/01/22 00:56:53  rick
 * Release cleanup, copyright year corrections
 *
 * Revision 1.5  2002/06/12 21:20:33  rick
 * Allow encode to be called from Bmark
 *
 * Revision 1.4  2002/04/02 17:06:28  administrator
 * Remove whitespace before # directives
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

/** @addtogroup SHFL
@{ */
/** @addtogroup UUENCODE_H Prototypes for uuencode.
@{ */

#ifndef   UUENCODE_H       
#define   UUENCODE_H

#ifdef __cplusplus
extern "C" {
#endif

int uu_send_buf( const char* buf, size_t length, const char* fn  );
int uu_send_file( const char* fn );
void encode (const char *raw_buffer, size_t raw_buf_len);

#ifdef __cplusplus
}
#endif
#endif
/** @} */
