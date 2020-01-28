/*==============================================================================
 *$RCSfile: bez.c,v $
 *
 *   DESC : Bezier Interpolation
 *
 * AUTHOR : C Tyron
 *
 *  EEMBC : Office Automation Subcommittee 
 *
 *    CVS : $Revision: 1.4 $
 *          $Date: 2005/04/27 20:37:51 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/office/bezierv2/bez.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: bez.c,v $
 * Revision 1.4  2005/04/27 20:37:51  rick
 * Copyrite update 2005
 *
 * Revision 1.3  2004/09/08 21:03:14  rick
 * Modify CRC algorithms for toolchain differences
 *
 * Revision 1.2  2004/07/02 18:19:25  rick
 * Remove uninitialized variable warning.
 *
 * Revision 1.1  2004/05/03 22:27:46  rick
 * Add text, bezier, rotate base for v2
 *
 * Revision 1.3  2002/07/31 22:42:20  rick
 * Fix Results iterations to report actual iterations
 *
 * Revision 1.2  2002/04/19 19:56:33  rick
 * Bug 137: Compiler Optimization Problem
 *
 * Revision 1.4  2002/04/09 21:27:20  rick
 * Set ITERATIONS to 1000 to fix Reg/Lite differences
 *
 * Revision 1.3  2002/03/11 22:11:50  rick
 * ITERATIONS, CRC_CHECK, NON_INTRUSIVE TCDef Usage
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

/*
 *	Includes
 */

/* ==== Project Wide Headers ==== */
#include "kernel.h"

/* ==== Algorithm specific headers ==== */
#include "bez.h"
#include "pointio.h"

volatile Scalar	strongoptimization=0;

/*
 *	Prototypes
 */

Scalar	parametric(Scalar t, Scalar p0, Scalar p1, Scalar p2, Scalar p3);

/************************************************************
FUNCTION NAME: interpolatePoints

DESCRIPTION:
    Interpolate a set of points on an array of Bezier curves

    The number of passes through the loop is determinied by the
    PARM_STEPS define.  Conceptually, the parametric value "t"
    goes from 0.0 to 1.0.


RETURN:
    none
*************************************************************/
/* Bug #137:
With strong C compiler optimization, C  compiler can completely remove out  "while" 
statement in  interpolatePoints() because it can find  "while" statement has no effect 
to the  results of the program. 
Actually C  compiler finds;
	- interpolatePoints() is defined as  void type.
	- the caller for interpolatePoints(),  t_run_test, doesn't use return-value of 
	  interpolatePoints().
	- parametric(), called by  interpolatePoints(), returns its  return-value only to 
	  local variables in  interpolatePoints(), which can't affect  beyond interpolatePoints().
*/

n_void interpolatePoints( Curve *curve, n_int count, Point *interpolate_test, n_int test_idx)
{
    n_int       n;
    n_int       step;           /*  interpolation iterator */
    Point       point={0,0};
    Curve       c0;
    Scalar      t;              /*  parametric value */

    for ( n = 0; n < count; ++n )
    {
        c0 = curve[n];
		interpolate_test[n].X=(Scalar)0; 
		interpolate_test[n].Y=(Scalar)0; 
        for ( step = 0; step < PARM_STEPS; ++step )
        {
            t = SCALAR(step) / (Scalar)PARM_STEPS;
            point.X = parametric( t, c0.p1.X, c0.c1.X, c0.c2.X, c0.p2.X );
            point.Y = parametric( t, c0.p1.Y, c0.c1.Y, c0.c2.Y, c0.p2.Y );
#if BMDEBUG
			/* SG: to aid in porting/optimization, when BMDEBUG is on, print all interpolated points */
			th_printf("[n=%d step=%d] %f,%f\n",n,step,point.X,point.Y);
#endif
			/* SG: for verification, we are saving sum of values of interpolated points. */
			/* incidentally, this will also mean the compiler cannot optimize the computation away */
			interpolate_test[n].X+=point.X; 
			interpolate_test[n].Y+=point.Y; 
        }
    }
}
