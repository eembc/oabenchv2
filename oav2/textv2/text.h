/*==============================================================================
 *$RCSfile: text.h,v $
 *
 *   DESC : This file contains the Test Main and other TH support functions
 *
 * AUTHOR : C Tyron
 *
 *  EEMBC : Office Automation Subcommittee 
 *
 *    CVS : $Revision: 1.3 $
 *          $Date: 2005/04/27 20:38:18 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/office/textv2/text.h,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: text.h,v $
 * Revision 1.3  2005/04/27 20:38:18  rick
 * Copyrite update 2005
 *
 * Revision 1.2  2004/09/03 22:32:02  rick
 * New Office Textv2 functions
 *
 * Revision 1.1  2004/05/03 22:27:59  rick
 * Add text, bezier, rotate base for v2
 *
 * Revision 1.4  2004/01/22 20:21:36  rick
 * Copyright update and cleanup
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

#ifndef TEXT_H_DEFINED
#define TEXT_H_DEFINED
/****************************************************************************

FILE DESCRIPTION
    Configuration defines for the Text Processing benchmark
****************************************************************************/

#include "thlib.h"

/**************************************************************************
      Defines
***************************************************************************/


/* ======================================================================= */
/*         O T H E R   C O N S T A N T S                                   */
/* ======================================================================= */

#define MAX_VAR_LENGTH          (64)
#define INPUT_BUFFER_SIZE       (1024)          /*  input line length */
#define NODE_BLOCK_SIZE         (1000)          /*  static btree node list */
#define MAX_VARIABLES           (100)           /*  max number of variables */


#endif        /*  TEXT_H_DEFINED */

/**************************************************************************
      Defines
***************************************************************************/


/****************************************************************************
Boolean operators and values

TABLE OF OPERATOR PRECIDENCE
    The higher the number, the tighter the operator binds (such
    as mult. over add.).  Operators with equal prec. evaluate left to
       right.

    Note that the operator list is maintained both as a linear array,
    AND as a binary tree.  The tree structure allows binary searches
    when comparing terms in the expression against the operator list.

***************************************************************************/

typedef enum
{
    NOOP, AND, OR, THEN, IF, EQUI, NEQU, NAND, NOR, NOT
} OpType;

typedef enum
{
    UNARY, BINARY
} OpMode;


typedef struct Operator_struct
{
    OpType        type;           /*  operation type */
    n_char        symbol;         /*  single char symbol */
    const n_char *name;           /*  long op description */
    OpMode        mode;           /*  one opperand or two */
    n_int         precedence;     /*  operator precedence */
    /* --- btree pointers for comparing terms to find reserved words */
    struct Operator_struct *    higher;
    struct Operator_struct *    lower;
} Operator;


/****************************************************************************
    Character types for parsing lines
***************************************************************************/

typedef enum
{
    C_INVALID, C_VARIABLE, C_CONSTANT, C_OPERATOR, C_UNARY,
    C_OPEN_PAREN, C_CLOSE_PAREN, C_SPACE, C_END
} CharType;


/****************************************************************************
    The following is a binary tree structure used to hold the
    parsed expressions from input line.  Each node on the tree has
    two branches.  Each branch contains:
            (a) a pointer to a variable structure
         or (c) a constant
         or (b) a pointer to another node
***************************************************************************/

typedef struct variable_struct
{
    n_char                      name[MAX_VAR_LENGTH+1];
    Bool                        value;
    struct variable_struct *    higher;
    struct variable_struct *    lower;
} Variable;

typedef struct
{
    enum
    {                            /*  what kind of element is this? */
        IS_EMPTY, IS_VAR, IS_CONSTANT, IS_POINTER
    } type;
    union
    {
        Variable *      variable;               /*  pointer to variable... */
        Bool            constant;               /*    ...or constant T/F */
        struct node_struct * child;             /*    ...or pointer to Node */
    } this;
    OpType        unary;                        /*  unary operator (if any) */
} Expression;


typedef struct node_struct
{
    struct node_struct *parent;     /*  Also used as the "next free" ptr */
    Expression          left;
    Operator *          bin_op;     /*  binary operator structure */
    Expression          right;
} Node;


