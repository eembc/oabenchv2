/*==============================================================================
 *$RCSfile: dither.c,v $
 *
 *   DESC : This file contains the Test Main and other TH support functions
 *
 * AUTHOR : C Tyron
 *
 *  EEMBC : Office Automation Subcommittee 
 *
 *    CVS : $Revision: 1.5 $
 *          $Date: 2005/11/03 22:26:25 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/office/ditherv2/dither.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: dither.c,v $
 * Revision 1.5  2005/11/03 22:26:25  rick
 * Bug #141: Restore fix for V2, * Revision 1.2  2002/04/22 22:03:02  rick
 *
 * Revision 1.4  2005/04/27 20:37:58  rick
 * Copyrite update 2005
 *
 * Revision 1.3  2004/07/06 18:25:18  rick
 * Correct string.h include causing makerule warning
 *
 * Revision 1.2  2004/01/29 00:34:12  rick
 * Resolve header file cycles
 *
 * Revision 1.1  2004/01/23 00:29:39  rick
 * Initial dither V2
 *
 * Revision 1.3  2002/05/07 21:18:58  rick
 * Bug #141: Rollback, changed timing
 *
 * Revision 1.2  2002/04/22 22:03:02  rick
 * Bug #141 - FS parm 8->7
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

/***************************************************************************

FILE DESCRIPTION
    Change a grayscale, 8bpp image to a binary image, using a
    Floyd-Steinberg Error Diffusion dithering algorithm

REFERENCES:
    Robert Ulichney (1987); "Digital Halftoning",
        The MIT Press, Cambridge, Massachusetts; pp. 239-242
***************************************************************************/

/*********************************************************************
    Includes
**********************************************************************/

#include <string.h>

/* ==== Project Wide Headers */
#include "kernel.h"

/* ==== Algorithm specific headers */
#include "dither.h"
#include "masks.h"
#include "imageio.h"


/*********************************************************************
    Defines
**********************************************************************/

#define WHITE_PIXEL     (255)        /*  Max pixel value (WHITE) */

/* ----------------------------------------------------- */
/*  Error diffusion elements for a 4 or 12 element array */
/* ----------------------------------------------------- */

#if FILTER == FLOYD_STEIN
#define E0              7
#define E1              3
#define E2              5
#define E3              1
#define DIV(e)          ((e)/16)
#define ERR_BUFFERS     (2)
#define EXTRA_SLOTS     (1)
#endif

#if FILTER == JARVIS
#define E0              7
#define E1              5
#define E2              3
#define E3              5
#define E4              7
#define E5              5
#define E6              3
#define E7              1
#define E8              3
#define E9              5
#define E10             3
#define E11             1
#define DIV(e)          ((e)/48)
#define ERR_BUFFERS     (3)
#define EXTRA_SLOTS     (2)
#endif

/* --------------------------------------------------------------------- */
/*  Define an array of bitmasks for SETTING the output image bits.       */
/*     Using the defines above, this list should cover all Endian cases  */
/*  Note: this is a zero-based list, which assumes the "first" row is    */
/*     row number zero...                                                */
/* --------------------------------------------------------------------- */
e_u8 setmask[] =
{
    MASKBYTE01, MASKBYTE02, MASKBYTE03, MASKBYTE04,
    MASKBYTE05, MASKBYTE06, MASKBYTE07, MASKBYTE08,
};

/* Add in a "random noise" factor to the threashold to reduce artifacts */
n_int threashold[] = { 139,138,122,120,131,135,109,130 };

/*********************************************************************
    M A C R O S
**********************************************************************/

#define IMAGE_BUFFSZ(h,w)       (h * ((w-1)/CHAR_BITS+1))


/* ===================================================================== */
/*         L O C A L   F U N C T I O N S                                 */
/* ===================================================================== */


/************************************************************
FUNCTION NAME: ditherImage

DESCRIPTION:
    Given a GRAYSCALE image, create a BINARY image of the same size,
    using a Floyd-Steinberg error diffusion dithering algorithm.

    Two "error" arrays are used - one for saving the errors from
    the current row (used to dither the next row) and one from the
    previous row, used to diffuse the errors from that row to the
    current pixel.    This array must be zeroed out first thing before
    the first row, to ensure that no spurrious data is left there.

    The error array is created such that there is one extra int
    at either end.    This eliminates special processing at the start
    and end of each row (but requires zeroing the additional columns).

    If using the JARVIS filter, then ERR_BUFFERS is set to 2, since
    the errors from each pixel are diffused over a larger matrix, requiring
    two rows to save the values

RETURN:
    none
*************************************************************/

n_void ditherImage( e_u8 *input_buffer, n_int input_height,
                         n_int input_width, e_u8 *output_buffer )
{
    n_int *       c0;
    n_int *       c1;
#if ERR_BUFFERS > 2
    n_int *       c2;
#endif
    n_int         column;
    n_int         pixel;
    e_u8          byte = 0;
    n_int         error;        /* rolling value for next pixel, same row */
#if ERR_BUFFERS > 2
    n_int         error1;
#endif
    n_int         row;
    n_int         bit = 0;
    n_int *       temp;
    n_int *       err0;
	n_int *		  storage_err0=th_malloc(ERR_BUFFERS * 
					(input_width+2*EXTRA_SLOTS) * sizeof(n_int));

    memset( (n_void*)output_buffer, 0,
                IMAGE_BUFFSZ( input_height,input_width ));

    err0 = storage_err0;
/* Changed for TH_LITE to use global width/height definitions */
    memset( (n_void*)err0, 0,
                ERR_BUFFERS * (input_width+2*EXTRA_SLOTS) * sizeof(n_int));

    c0 = err0 + EXTRA_SLOTS;
    c1 = c0 + input_width + 2*EXTRA_SLOTS;
#if ERR_BUFFERS > 2
    c2 = c1 + input_width + 2*EXTRA_SLOTS;
#endif

    for (row = 0; row < input_height; ++row)
    {
        error = 0;                      /*  no error in first column */

        for (column = 0; column < input_width; ++column)
        {
#if ERR_BUFFERS > 2
            error1 = error;
#endif
            if ((pixel = *(input_buffer++)) == WHITE_PIXEL)
            {
                c0[column] = error = 0; /*  Skip all white pixels */
            }
            else
            {
#if FILTER == FLOYD_STEIN
                pixel += DIV(  error         * E0
                             + c1[column+1]  * E1
                             + c1[column]    * E2
                             + c1[column-1]  * E3 );
#else
                pixel += DIV(  error         * E0
                             + error1        * E1
                             + c1[column+2]  * E2
                             + c1[column+1]  * E3
                             + c1[column]    * E4
                             + c1[column-1]  * E5
                             + c1[column-2]  * E6
                             + c2[column+2]  * E7
                             + c2[column+1]  * E8
                             + c2[column]    * E9
                             + c2[column-1]  * E10
                             + c2[column-2]  * E11 );
#endif

                if (pixel < threashold[bit])
                {  /* -- set to BLACK (0) */
                    byte |= setmask[bit];
                    c0[column] = error = pixel;
                }
                else
                {                          /* -- set to WHITE (255) */
                    c0[column] = error = pixel - WHITE_PIXEL;
                }
            }

            if (++bit >= CHAR_BITS)
            {
                *(output_buffer++) = byte;
                byte = bit = 0;
            }
        }

        /* ------- Check for "leftovers" at end of row */
        if (bit != 0)
        {
            *(output_buffer++) = byte;
            byte = bit = 0;
        }

        /* ------- SWAP ERROR ARRAYS */
        temp = c0;
#if ERR_BUFFERS == 2
        c0 = c1;
#else
        c0 = c2;
        c2 = c1;
#endif
        c1 = temp;
    }

/* Changed for TH_LITE to use global width/height definitions */
/* subroutine overhead similar to malloc/free, so storage not global */
	th_free(storage_err0); 

    return;
}

/* ===================================================================== */
/*         T H E   E N D  -  d i t h e r . c                             */
/* ===================================================================== */
