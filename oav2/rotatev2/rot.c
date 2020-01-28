/*==============================================================================
 *$RCSfile: rot.c,v $
 *
 *   DESC : This file contains the Test Main and other TH support functions
 *
 * AUTHOR : C Tyron
 *
 *  EEMBC : Office Automation Subcommittee 
 *
 *    CVS : $Revision: 1.3 $
 *          $Date: 2005/04/27 20:38:09 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/office/rotatev2/rot.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: rot.c,v $
 * Revision 1.3  2005/04/27 20:38:09  rick
 * Copyrite update 2005
 *
 * Revision 1.2  2004/05/13 19:33:29  rick
 * Release cleanup
 *
 * Revision 1.1  2004/05/03 22:27:55  rick
 * Add text, bezier, rotate base for v2
 *
 * Revision 1.4  2002/04/25 23:20:30  rick
 * Cleanup after bug database scrub
 *
 * Revision 1.3  2002/04/22 22:55:02  rick
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

/****************************************************************************

FILE DESCRIPTION
    Rotate a binary image of arbitrary size by 90 degrees.

    At this point, the algorithm makes use of a series of timer
    functions in the timer.c module.  This may change in the future
    as the EEMBC Test Harness API is solidified.

    If the image is to be read in from a data file (as opposed to
    being compiled in), then the main function makes use of a call
    to the test harness malloc to create a buffer of sufficient size
    to hold the image.  This allows for different sizes of input files
***************************************************************************/


/*********************************************************************
    Includes
**********************************************************************/

#include "algo.h"

/* ===================================================================== */
/*         L O C A L   F U N C T I O N S                                 */
/* ===================================================================== */


/************************************************************
FUNCTION NAME: rotateImage

DESCRIPTION:
    Given a BINARY image, rotate it counter-clockwise by 90 degrees

    Note: the memset() call calculates the output buffer size from
    the input buffer by transposing the row and column numbers!

    The "row_offset" is in BITS, rounded up to the next multiple of 8
    (CHAR_BITS)

    Note that the expression:
            *(output+SHIFT(i)) |= setmask[i&MASK];
    is equivalent ot:
            *(output + i/BITS) |= setmask[ i%BITS ];
    The SHIFT and MASK macros are set according to the size of BITS

RETURN:
    none
*************************************************************/

n_void rotateImage( e_u8 *input_buffer, n_int input_height,
                         n_int input_width, e_u8 *output_buffer )
{
    UNIT *      input;
    UNIT        image_in;
    UNIT *      output = (UNIT*)output_buffer;
    n_int       i;
    n_int       row_offset;
#ifndef UNROLLED
    n_int       bit;
#endif
    n_int       first_skip;
    n_int       input_padded_width;
    n_int       input_row, input_col;

    memset( (n_void*)output_buffer, 0, IMAGE_BUFFSZ(input_width,input_height));

    /* ----- number of bits across output row, rounded to next byte */
    row_offset = ((input_height-1) / CHAR_BITS + 1) * CHAR_BITS;
    input_padded_width = ((input_width -1) / CHAR_BITS + 1) * CHAR_BITS;

    DEBUG1( "row offset: %3d\n", row_offset );
    DEBUG1( "padded wid: %3d\n", input_padded_width );

    for (input_row = 0; input_row < input_height; ++input_row)
    {
        input = (UNIT*)input_buffer + (input_row * input_padded_width) / BITS;
        i = input_row + (input_width-1) * row_offset;

        first_skip = (input_row * input_padded_width) % BITS;

        DEBUG1( "%3d [", input_row );

        for (input_col = 0; input_col < input_width; input_col += BITS)
        {
            DEBUG2( " 0x%0*x ", BITS/4, *input );

            if ((image_in = *input++) == 0)
            {   /*  SKIP TRIVIAL CASES! */
                i -= (BITS - first_skip) * row_offset;
            }
            else
            {

#ifdef UNROLLED
/* ----------------------------------- */
#define CheckSet(mask)                                                      \
                if (image_in & mask)                                        \
                {                                                           \
                    *(output+DivideByBITS(i)) |= setmask[ModuloBITS(i)];    \
                }                                                           \
                if ((i -= row_offset) < 0)                                  \
                {                                                           \
                    break;                                                  \
                }
/* ----------------------------------- */

                switch (first_skip)
                {
                case 0:
                    DEBUG0("A");
                    CheckSet(MASK01);
                    CheckSet(MASK02);
                    CheckSet(MASK03);
                    CheckSet(MASK04);
                    CheckSet(MASK05);
                    CheckSet(MASK06);
                    CheckSet(MASK07);
                    CheckSet(MASK08);

#if BITS >= 16
                case CHAR_BITS:
                    DEBUG0("B");
                    CheckSet(MASK09);
                    CheckSet(MASK10);
                    CheckSet(MASK11);
                    CheckSet(MASK12);
                    CheckSet(MASK13);
                    CheckSet(MASK14);
                    CheckSet(MASK15);
                    CheckSet(MASK16);

#if BITS >= 32
                case 2*CHAR_BITS:
                    DEBUG0("C");
                    CheckSet(MASK17);
                    CheckSet(MASK18);
                    CheckSet(MASK19);
                    CheckSet(MASK20);
                    CheckSet(MASK21);
                    CheckSet(MASK22);
                    CheckSet(MASK23);
                    CheckSet(MASK24);

                case 3*CHAR_BITS:
                    DEBUG0("D");
                    CheckSet(MASK25);
                    CheckSet(MASK26);
                    CheckSet(MASK27);
                    CheckSet(MASK28);
                    CheckSet(MASK29);
                    CheckSet(MASK30);
                    CheckSet(MASK31);
                    CheckSet(MASK32);

#endif    /*  BITS >= 32 */
#endif    /*  BITS >= 16 */
                }

#else    /*  not UNROLLED */

                for (bit=first_skip; bit < BITS && i >= 0; ++bit)
                {
                    if (image_in & setmask[bit])
                    {
                        *(output+DivideByBITS(i)) |= setmask[ModuloBITS(i)];
                    }
                    i -= row_offset;
                }

#endif    /*  UNROLLED */
                first_skip = 0;
            }
        }
        DEBUG1("] (i=%d)\n", i);
    }

    return;
}

/* ===================================================================== */
/*         T H E   E N D  -  r o t . c                                   */
/* ===================================================================== */
