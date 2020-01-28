/*==============================================================================
 *$RCSfile: parametric.c,v $
 *
 *   DESC : Bezier Algorithm
 *
 *  EEMBC : Office Automation
 *
 * AUTHOR : C Tryon
 *
 *    CVS : $Revision: 1.3 $
 *          $Date: 2005/04/27 20:37:52 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/office/bezierv2/parametric.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: parametric.c,v $
 * Revision 1.3  2005/04/27 20:37:52  rick
 * Copyrite update 2005
 *
 * Revision 1.2  2004/09/08 21:03:15  rick
 * Modify CRC algorithms for toolchain differences
 *
 * Revision 1.1  2004/05/03 22:27:46  rick
 * Add text, bezier, rotate base for v2
 *
 * Revision 1.3  2002/04/19 19:56:34  rick
 * Bug 137: Compiler Optimization Problem
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
    Run the calculations to interpolate a set of points defined by
    the four points of a Bezier curve.

    The curve is defined by two endpoints and two control points.
    The points are in 2D space, and are defined using floating point
    (double precision) variables.

    The actual formula was pulled from a web page created by Paul Thomson:
    http://www.dcs.ed.ac.uk/~pat/dfi/effect_pics/bezier_line.html

    The algorithm makes use of configuration constants in the header
    file "bez.h".  This includes the number of points to interpolate
    for each curve as well as the overall loop count.

    If the points are to be read in from a data file (as opposed to
    being compiled in), then the main function makes use of a call
    to the test harness malloc to create an array of Curve structures.
    This allows for different sizes of input files when the data
    points are read from file.  The first line in the file is the
    number of points following in the rest of the file

***************************************************************************/

/**************************************************************************
    Includes
***************************************************************************/

/* ==== Project Wide Headers ==== */
#include "kernel.h"

/* ==== Algorithm specific headers ==== */
#include "bez.h"
#include "pointio.h"

/************************************************************
FUNCTION NAME: parametric

DESCRIPTION:
    Evaluate parametric function for Bezier curve

            P(t) = p0*(1-t)^3 + 3*p1*t*(1-t)^2 + 3*p2*(t^2)*(1-t) + p3*t^3

    (see: http://www.dcs.ed.ac.uk/~pat/dfi/effect_pics/bezier_line.html)

    The use of the t2, t3, etc. variables is an optimization to reduce
    the number of floating point arithmetic operations required,
    especially for the squares and cubes.

    PORTING NOTE:  It may be that the number of local variables
    here will be too many to push on the stack in some instances.
    In this case, the multiplications could simply be done inline
    with the rest of the formula.

RETURN:
    Scalar P(t)
************************************************************/

Scalar parametric( Scalar t, Scalar p0, Scalar p1,
                          Scalar p2, Scalar p3 )
{
#if USE_FPU
    Scalar      t2 = t * t;
    Scalar      t3 = t2 * t;
    Scalar      t_1 = (Scalar)1.0 - t;
    Scalar      t12 = t_1 * t_1;
    Scalar      t13 = t12 * t_1;

    return (  p0 * t13
                + p1 * (Scalar)3.0 * t * t12
                + p2 * (Scalar)3.0 * t2 * t_1
                + p3 * t3 );

#else
    Scalar      t2 = MULT( t, t );
    Scalar      t3 = MULT( t2, t );
    Scalar      t_1 = SCALAR(1) - t;
    Scalar      t12 = MULT( t_1, t_1 );
    Scalar      t13 = MULT( t12, t_1 );
    Scalar      c3 = SCALAR(3);

    return (  MULT( p0, t13 )
                + MULT( p1, MULT( c3, MULT( t, t12 )))
                + MULT( p2, MULT( c3, MULT( t2, t_1 )))
                + MULT( p3, t3 ) );
#endif
}
