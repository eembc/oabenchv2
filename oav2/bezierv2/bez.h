/*==============================================================================
 *$RCSfile: bez.h,v $
 *
 *   DESC : Bezier Interpolation
 *
 * AUTHOR : C Tyron
 *
 *  EEMBC : Office Automation Subcommittee 
 *
 *    CVS : $Revision: 1.3 $
 *          $Date: 2005/04/27 20:37:51 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/office/bezierv2/bez.h,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: bez.h,v $
 * Revision 1.3  2005/04/27 20:37:51  rick
 * Copyrite update 2005
 *
 * Revision 1.2  2004/09/08 21:03:14  rick
 * Modify CRC algorithms for toolchain differences
 *
 * Revision 1.1  2004/05/03 22:27:46  rick
 * Add text, bezier, rotate base for v2
 *
 * Revision 1.4  2002/08/09 17:47:06  rick
 * Add NI CRC to th regular benchmarks
 *
 * Revision 1.3  2002/07/31 22:42:20  rick
 * Fix Results iterations to report actual iterations
 *
 * Revision 1.2  2002/04/19 19:56:33  rick
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

#ifndef BEZ_H_DEFINED
#define BEZ_H_DEFINED

/****************************************************************************

FILE DESCRIPTION
    Configuration defines and structure typedefs for the Bezier
    Curve interpolation algorithm

    Structures need to be defined here because the curve structure
    is needed for the compiled in version of the dataset.

    NOTE: Using, 32bit ints for the fixed point math, it is possible
    to push the SHIFT constant up to 14 bits before running into
    overflow problems with the provided dataset.  With input values in
    the 0 to 10 range though, a shift constant of 12 is more
    realistic.
****************************************************************************/

#include "thlib.h"

/****************************************************************************
                C O N F I G U R A T I O N    D E F I N E S
****************************************************************************/

#ifndef DRAW
/* #define        DRAW */
#endif
#ifndef USE_FPU
#define USE_FPU         (0)
#endif

/* Trap for Floating point support */
#if		USE_FPU && !FLOAT_SUPPORT
#undef	USE_FPU
#define	USE_FPU			(0)
#endif

#define PARM_STEPS      (10)

#if                USE_FPU
/* ======== DO CALCULATIONS IN FLOATING POINT MATH ================ */
#define FIXED_SHIFT     (0)
#define D2F(n)          (n)
#define F2D(n)          (n)
/*  convert int value to scalar */
#define SCALAR(n)       ((Scalar)(n))

#define MULT(a,b)       ((a)*(b))
#define DIVD(a,b)       ((a)/(b))

#else
/* ======== DO CALCULATIONS IN FIXED POINT (int) MATH ============= */
#define FIXED_SHIFT     (12)
#define D2F(n)          ((e_s32)((n)*(1<<FIXED_SHIFT)))
#define F2D(n)          ((e_f32)(n)/(1<<FIXED_SHIFT))
#define SCALAR(n)       ((Scalar)((n)<<FIXED_SHIFT))

#define MULT(a,b)       (((a)*(b))>>FIXED_SHIFT)
#define DIVD(a,b)       (((a)<<FIXED_SHIFT)/(b))

#endif /*  USE_FPU */


/* ======== DIAGNOSTIC - ASCII Graph Output ======== */
#define GRIDSIZEX       (22)
#define GRIDSIZEY       (12)


/****************************************************************************
        Structure Definitions
****************************************************************************/

#if USE_FPU
typedef e_f32           Scalar;
#else
typedef e_s32           Scalar;
#endif

typedef struct
{
    Scalar X, Y;
} Point;

typedef struct
{
    Point p1;           /*  endpoint 1 */
    Point c1;           /*  control point 1 */
    Point c2;           /*  control point 2 */
    Point p2;           /*  endpoint 2 */
} Curve;

typedef struct
{
    Point c1;           /*  lower left corner (minimum values) */
    Point c2;           /*  upper right corner (maximum values) */
} Box;

/****************************************************************************
    Function Prototypes
****************************************************************************/
n_void interpolatePoints( Curve *curve, n_int count, Point *interpolate_test, n_int test_idx);
n_void	outputPoints( Curve* curve, n_int count );

#endif /*  BEZ_H_DEFINED */
