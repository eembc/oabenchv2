/*==============================================================================
 *$RCSfile: crc_lite.c,v $
 *
 *   DESC : crc routines to check output tree
 *
 *  EEMBC : Office Automation
 *
 * AUTHOR : ARM Ltd., ECL, LLC
 *
 *    CVS : $Revision: 1.4 $
 *          $Date: 2005/04/27 20:38:13 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/office/textv2/crc_lite.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: crc_lite.c,v $
 * Revision 1.4  2005/04/27 20:38:13  rick
 * Copyrite update 2005
 *
 * Revision 1.3  2004/09/03 22:32:02  rick
 * New Office Textv2 functions
 *
 * Revision 1.2  2004/07/06 18:25:32  rick
 * Correct string.h include causing makerule warning
 *
 * Revision 1.1  2004/05/03 22:27:59  rick
 * Add text, bezier, rotate base for v2
 *
 * Revision 1.8  2004/01/22 20:21:35  rick
 * Copyright update and cleanup
 *
 * Revision 1.7  2002/12/07 00:45:59  rick
 * MPEG 4 data files
 *
 * Revision 1.6  2002/08/09 17:47:18  rick
 * Add NI CRC to th regular benchmarks
 *
 * Revision 1.5  2002/03/11 22:11:50  rick
 * ITERATIONS, CRC_CHECK, NON_INTRUSIVE TCDef Usage
 *
 * Revision 1.4  2002/02/27 17:40:50  rick
 * Update Documentation and API comments for 0.3
 *
 * Revision 1.3  2002/02/21 19:52:12  administrator
 * Build TH_Lite makefile for cygwin
 *
 * Revision 1.5  2002/02/19 20:12:09  rick
 * Add long copyright message per Alan.
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



#include <string.h>

/* ==== Project Wide Headers */
#include "thlib.h"
#include "kernel.h"

/* ==== Algorithm specific headers */
#include "text.h"

extern TCDef the_tcdef;

#if NON_INTRUSIVE_CRC_CHECK

n_char        CRCNodes( Node *p, e_u16 *crc );
static n_void CRCVoid (e_u8 *stuff, int stufflen, e_u16 *crc);
static n_void CRCExpression(n_char c, Expression *this, e_u16 *crc);


/************************************************************
FUNCTION NAME: CRCNodes

DESCRIPTION:
    CRC the tree heirarchy

    The "right_name" and "left_name" variables are automatic names
    created for intermediate values as the evaluation bubbles up the
    tree.

RETURN:
    the automatic name just created
NOTE:
    Derived from printNodes
*************************************************************/
n_char CRCNodes( Node *p, e_u16 *crc )
{

    /*  names for left and right expressions */
    n_char        left_name = 0;
    n_char        right_name = 0;
    n_char        this_name = 0;

    if (p != (Node *)NULL)
    {
        /* ---------- Left -------------------- */
        if (p->left.type == IS_POINTER)
        {
            left_name = CRCNodes(p->left.this.child,crc);
        }
        /* ---------- Right ------------------- */
        if (p->right.type == IS_POINTER)
        {
            right_name = CRCNodes(p->right.this.child,crc);
        }

        CRCExpression(left_name, &p->left,crc);
        CRCExpression(right_name, &p->right,crc);
    }

    return this_name;
}

/************************************************************
FUNCTION NAME: CRCExpression

DESCRIPTION:
    CRC a single expression name, or a letter for an
    intermediate value if this is a pointer to another node
	Avoid all endian problems.

RETURN:
    none
NOTE:
    Derived from printExpression
	constant a Bool is always 16 Bits (signed). Calc_crc16 to avoid
	Endian problems because it is internally generated data.
*************************************************************/
static n_void CRCExpression( n_char c, Expression *exp, e_u16 *crc )
{
    if (exp->unary != NOOP) 
	{
	crc[0] = Calc_crc8((e_u8)exp->unary,crc[0]);
	}

    switch (exp->type)
    {
    case IS_POINTER:
        CRCVoid((e_u8*)&c,1,crc);
        break;
    case IS_VAR:
        CRCVoid((e_u8*)exp->this.variable->name,strlen(exp->this.variable->name),crc);
        break;
    case IS_CONSTANT:
	crc[0] = Calc_crc16(exp->this.constant,crc[0]);
        break;
    default:
        break;
    }
    return;
}

/************************************************************
FUNCTION NAME: CRCVoid

DESCRIPTION:
    CRC data as a string of bytes

RETURN:
    none
NOTE:
    Derived from printExpression
*************************************************************/
static n_void CRCVoid (e_u8 *stuff, int stufflen, e_u16 *crc)
{
int	loop_cnt;
for(loop_cnt=0;loop_cnt<stufflen;loop_cnt++) 
	crc[0] = Calc_crc8(stuff[loop_cnt], crc[0] );
}

#endif /* NON_INTRUSIVE_CRC_CHECK */

