/*==============================================================================
 *$RCSfile: imageio.h,v $
 *
 *   DESC : This file contains the Test Main and other TH support functions
 *
 * AUTHOR : C Tyron
 *
 *  EEMBC : Office Automation Subcommittee 
 *
 *    CVS : $Revision: 1.3 $
 *          $Date: 2005/04/27 20:37:59 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/office/ditherv2/imageio.h,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: imageio.h,v $
 * Revision 1.3  2005/04/27 20:37:59  rick
 * Copyrite update 2005
 *
 * Revision 1.2  2004/01/29 00:34:12  rick
 * Resolve header file cycles
 *
 * Revision 1.1  2004/01/23 00:29:39  rick
 * Initial dither V2
 *
 * Revision 1.2  2002/04/22 22:55:01  rick
 * Standard Comment blocks
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

#ifndef IMAGEOUT_H_DEFINED
#define IMAGEOUT_H_DEFINED
/**************************************************************************

FILE DESCRIPTION
    Function prototypes for binary image output functions

**************************************************************************/

/*********************************************************************
        F U N C T I O N   P R O T O T Y P E S
**********************************************************************/

n_void  outputBinaryImage( e_u8 *image, n_int height, n_int width );
e_u8 *  readImage( n_int *height, n_int *width );
void init_files(void);

#endif        /*  IMAGEOUT_H_DEFINED */
