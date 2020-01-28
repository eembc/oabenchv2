/*==============================================================================
 *$RCSfile: rot.h,v $
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
 *          $Source: /cvs/eembc2/office/rotatev2/rot.h,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: rot.h,v $
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

#ifndef ROT_H_DEFINED
#define ROT_H_DEFINED
/****************************************************************************
FILE DESCRIPTION
    Configuration defines and structure typedefs for the Binary Image
    Rotation algorithm

    NOTE: This header defines the UNIT type, depending on the number of bits
    selected for the minimum processing unit (byte, half word or word).
    Depending on the hardware configuration and compiler, these defines may
    need to be changed.
****************************************************************************/

#include "thlib.h"

/*********************************************************************
        C O N F I G U R A T I O N    D E F I N E S
**********************************************************************/

#define BIT1_LOW
#define UNROLLED

/* ---------------------------------- */
/*     Select ONE of the following... */
/* ---------------------------------- */
#ifndef BITS
/* #define BITS    (8) */
/* #define BITS    (16) */
#define BITS    (32)
#endif

#if BITS == 32
typedef n_uint          UNIT;
#define DivideByBITS(n) ((n)>>5)
#define ModuloBITS(n)   ((n) & 0x0000001F)
#endif

#if BITS == 16
typedef n_ushort        UNIT;
#define DivideByBITS(n) ((n)>>4)
#define ModuloBITS(n)   ((n) & 0x0000000F)
#endif

#if BITS == 8
typedef n_uchar         UNIT;
#define DivideByBITS(n) ((n)>>3)
#define ModuloBITS(n)   ((n) & 0x00000007)
#endif

#define WORD_CHAR       (BITS/CHAR_BITS)        /*  how many chars per UNIT */

#if BITS != 8 && BITS != 16 && BITS != 32
    #error "DEFINE ERROR FOR Bits!!"
#endif

#endif        /*  ROT_H_DEFINED */
