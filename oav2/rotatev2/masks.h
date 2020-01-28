/*==============================================================================
 *$RCSfile: masks.h,v $
 *
 *   DESC : This file contains the Test Main and other TH support functions
 *
 * AUTHOR : C Tyron
 *
 *  EEMBC : Office Automation Subcommittee 
 *
 *    CVS : $Revision: 1.2 $
 *          $Date: 2005/04/27 20:38:09 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/office/rotatev2/masks.h,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: masks.h,v $
 * Revision 1.2  2005/04/27 20:38:09  rick
 * Copyrite update 2005
 *
 * Revision 1.1  2004/05/03 22:27:55  rick
 * Add text, bezier, rotate base for v2
 *
 * Revision 1.2  2002/04/22 22:55:02  rick
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

#ifndef MASKS_H_DEFINED
#define MASKS_H_DEFINED
/**************************************************************************

FILE DESCRIPTION
    Mask byte defines, depending on hardware architecture
**************************************************************************/


/*********************************************************************
        C O N F I G U R A T I O N    D E F I N E S
**********************************************************************/

/* ------------------------------------------------- */
/*     Check MSBit high or low                       */
/* ------------------------------------------------- */
#ifdef BIT1_LOW
/*  first pixel in image is least significant bit */
#define MASKBYTE01      0x01
#define MASKBYTE02      0x02
#define MASKBYTE03      0x04
#define MASKBYTE04      0x08
#define MASKBYTE05      0x10
#define MASKBYTE06      0x20
#define MASKBYTE07      0x40
#define MASKBYTE08      0x80
#else
/*  first pixel in image is most significant bit */
#define MASKBYTE01      0x80
#define MASKBYTE02      0x40
#define MASKBYTE03      0x20
#define MASKBYTE04      0x10
#define MASKBYTE05      0x08
#define MASKBYTE06      0x04
#define MASKBYTE07      0x02
#define MASKBYTE08      0x01
#endif


#endif        /*  MASKS_H_DEFINED */
