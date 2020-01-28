/*==============================================================================
 *$RCSfile: text.c,v $
 *
 *   DESC : This file contains the Test Main and other TH support functions
 *
 * AUTHOR : C Tyron
 *
 *  EEMBC : Office Automation Subcommittee 
 *
 *    CVS : $Revision: 1.5 $
 *          $Date: 2005/04/27 20:38:14 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/office/textv2/text.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: text.c,v $
 * Revision 1.5  2005/04/27 20:38:14  rick
 * Copyrite update 2005
 *
 * Revision 1.4  2004/09/08 05:19:10  rick
 * Add additional office datasets to complete makefile build
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
 * Revision 1.7  2002/04/23 21:15:14  rick
 * Clear printouttext warnings
 *
 * Revision 1.6  2002/04/23 14:29:48  rick
 * Bug #49: Remove showOperators, countFreeNodes undefined prototypes
 *
 * Revision 1.5  2002/04/22 22:55:02  rick
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
    Parse Boolean expressions

    For each line, break the expression into a binary tree structure,
    where each node contains a binary expression with two opperands
    (each with a possible unary operator) and a binary operator.  The
    operands may be variables, constants, or pointers to further nodes
    which themselves represent binary operations, etc...

    NOTE:  Use the BENCHMARK define to activate the main timed loop,
    controled by the test harness.    If this is NOT defined, then
    the program goes into an interactive mode where each "rule"
    (boolean expression) is entered by the user, parsed, and then
    printed out as a truth table

    If in debug mode (i.e., not in benchmark mode), then actually
    evaluate the expression for all possible values of the variable
    list.  This is done with a recursive function to set the
    variables, and then evaluate the expression stored in the binary
    tree.

      NOTE:  Not much error checking is done for valid expressions.  It
      should be hard to crash the program, but ill-formed expressions
      may give bogus results.
	  NOTE: th_lite version does not include th_exit. The prototype is
	  undefined, returning a warning, assuming extern returning int.
	  The modified th_exit in bmark_lite.c is an extern returning int.
	  The prototype was left out to avoid errors in the TH version.
***************************************************************************/

#include <stdlib.h>

#include "algo.h"

#if		!BENCHMARK
#include <stdio.h>
#endif

/** Initialize Test Harness file system for libtxt, single file based on DATA_x define. */
void init_libtxt(void);


/****************************************************************************
      G L O B A L S   A N D   T A B L E S
***************************************************************************/

Operator oplist[] =
{
    AND,    '&',    "and",      BINARY,     8,        NULL,     NULL,
    OR,     '|',    "or",       BINARY,     7,        NULL,     NULL,
    THEN,   '>',    "implies",  BINARY,     1,        NULL,     NULL,
    IF,     '<',    "if",       BINARY,     1,        NULL,     NULL,
    EQUI,   '=',    "eq",       BINARY,     1,        NULL,     NULL,
    NEQU,   '~',    "neq",      BINARY,     1,        NULL,     NULL,
    NAND,   '^',    "nand",     BINARY,     8,        NULL,     NULL,
    NOR,    '-',    "nor",      BINARY,     7,        NULL,     NULL,
    NOT,    '!',    "not",      UNARY,      9,        NULL,     NULL
};

#define OPLIST_LEN      ((n_int)(sizeof(oplist)/sizeof(oplist[0])))


/****************************************************************************
      "Memory Management" blocks - to avoid use of malloc() calls
***************************************************************************/
static Variable         variables[MAX_VARIABLES];   /*  list of variables */
static n_int            variable_count;
static Variable *       VariableTree = NULL;

static Node             NodeBlock[NODE_BLOCK_SIZE];
static Node *           NextFreeNode;
static Node *           FirstFreeNode;

static Operator *       OperatorTree = NULL;


/****************************************************************************
      Local Function Prototypes
***************************************************************************/

n_char *         input(n_void);
#if BENCHMARK
n_void             resetInput(n_void);
#endif

/* ---------- Parser functions */
Node *           parseRule(n_void);
static CharType         getTerm( n_char term[] );
static CharType         identifyTerm( n_char term[], Operator **op );
static Node *           addRight( Node *prev );
static Node *           insertRight( Node *orig );

/* ---------- Initialization functions */
n_void           initFreeNodes(n_void);
n_void           initCharacterTypes(n_void);
n_void           initVariables(n_void);
n_void           initOperatorTree(n_void);

/* ---------- "Memory Management" functions (to avoid malloc calls) */
static Node *           newNode( Node *parent );
n_void           release( Node *p );
static Variable *       saveVariable( n_char *name );

/* ---------- Evaluation functions */
static n_void           doRule( n_int n, Node *ptree );
static Bool             eval( Node *p );
static Bool             value( Expression expression );
static Bool             binOp( Bool p, Bool q, OpType op );
static Bool             unaOp( Bool p, OpType op );

static n_void           printTruthTableHeading(n_void);
n_char           printNodes( Node *p );
#ifdef PRINTOUTTEXT
static n_void           printExpression(n_char c, Expression *this );
static n_char           opSymbol( OpType op );
#endif

/*********************************************************************
    GLOBAL (ugh!) VARIABLES
**********************************************************************/

/** counter for compiled data */
n_int    l_inputIterator;
/** List of datafile strings. */
const char	**g_inputLine=NULL;
/** Current position in buffer. */
static n_char * l_inputBufferPosition;
/* names for intermediate values */
n_char   l_expLetter;
/** Detect tree release errors: NewNode +, Release -, should be 0 when done. */
int nodecnt=0;

/* lookup table for character types */
static CharType l_characterType[256];


/* ===================================================================== */
/*       L O C A L   F U N C T I O N S                                   */
/* ===================================================================== */

/** Defined in libtxt_init.c. */
extern const char *DATANAME;
unsigned long ee_uid=EE_UID;
e_u16 expected_crc=EXPECTED_CRC;
unsigned long ee_uid_all[NUM_DATAS] = {EE_UID_1,EE_UID_2,EE_UID_3,EE_UID_4};
e_u16 expected_crc_all[NUM_DATAS] = {EXPECTED_CRC_1,EXPECTED_CRC_2,EXPECTED_CRC_3,EXPECTED_CRC_4};
/** Number of rules (lines) in data file. */
int		rule_count=0;

/************************************************************
FUNCTION NAME: input

DESCRIPTION:
    print a prompt (if a tty) and input a string.
    On EOF, return a NULL pointer.

RETURN:
    char* input string
*************************************************************/

n_char *input( n_void )
{
    return (l_inputBufferPosition = (n_char*)g_inputLine[l_inputIterator++]);
}


/************************************************************
FUNCTION NAME: resetInput

DESCRIPTION:
    In case we're doing the benchmark (rather than inputing data by
    hand), then reset the counter that goes through the input array.

RETURN:
    none
*************************************************************/

n_void resetInput( n_void )
{
    l_inputIterator = 0;
    return;
}

/** Find and Open a file */
ee_FILE *pathfind_file(const char *filename, const char *filemode)
{
	char	*path[] = {"","../../","../../libtxt/","libtxt/",NULL};
	char	buf[FILENAME_MAX];
	int		i=0;
	ee_FILE	*found_file=NULL;

	if (!filename || !*filename)
		return NULL;

	if ((strcmp(filename,"stdin")) == 0) 
		return th_fopen(filename,filemode);

	while (path[i] != NULL)
	{
		strcpy(buf,path[i]);
		strcat(buf,filename);
		if ( (found_file = th_fopen(buf,filemode)) != NULL )
			return found_file;
		i++;
	}
return NULL;
}
/** @todo replace fgets with th_gets. */
void strip_t_crlf(char *s);

/** Load a rules file into memory.
Load text file into list of strings. Terminate string list with null entry.
@parm numrules - Number of rules in file.
@retval Line buffer of text file.
*/
char **loadRules( int *numrules )
{
	ee_FILE		*fd;
	char		**input_rules,**buf;
	char		line[1024]={0};

	if (!numrules)
		return NULL;

	if ((fd = pathfind_file( DATANAME, "rb" ))==NULL)
		th_exit(THE_FAILURE,"Could not open input file: %s\n",DATANAME);
	/* The format matches TH info. */
#if (TRAINING==1)
	th_printf(">> Data Set                 : training\n");
#else
	th_printf(">> Data Set                 : %s\n",DATANAME);
#endif
	th_printf(">> UID: %d\n",ee_uid);

	/* Get the number of rules in the file */
	*numrules=0;
	while (!th_feof(fd))
	{
		th_fgets(line,sizeof(line),fd);
		if (strlen(line))
			*numrules+=1;
	}
	/** rewind file. */
	th_fseek(fd,0,SEEK_SET);
	
	/** *numrules+1 with calloc NULL terminates the list for input(). */
	input_rules=buf=th_calloc(*numrules+1,sizeof(*input_rules));
	while(!th_feof(fd))
	{
		/* null string in case fgets encounters eof and does nothing. */
		line[0]='\0';
		th_fgets(line,sizeof(line),fd);
		/* some fgets's strip crlf, we strip cr from crlf, 
		others don't do anything. gets does to but deprecated. 
		@todo add th_gets, remove strip_t_crlf.
		*/
		strip_t_crlf(line);
		if (strlen(line))
			*buf=th_strdup(line);
		buf++;
	}

    th_fclose( fd );

    return input_rules;
}

/** Initialize File System. */
void	init_files(void)
{
	init_libtxt();
}

void	load_rules(void)
{
	g_inputLine=loadRules(&rule_count);
}

void free_rules(void) {
	if (g_inputLine) {
		int i;
		for (i=0; i<rule_count; i++) {
			if (g_inputLine[i])
				th_free((void *)g_inputLine[i]);
		}
		th_free((void *)g_inputLine);
	}
	g_inputLine=NULL;
}
/* ====================================================================== */
/*             P A R S E                                                  */
/* ====================================================================== */

/************************************************************
FUNCTION NAME: parseRule

DESCRIPTION:
    Go through rule and create parse tree.  This function may be recursively
    called in the case where a parenthese is encountered.

    This function also fills in the variables table.

RETURN:
    Node* root of parse tree
*************************************************************/

Node *parseRule( n_void )
{
    Operator *          op;
    Node *              pnode = (Node*)NULL;
    Node *              newnode = (Node*)NULL;
    Expression *        expression;
    enum {LEFT, RIGHT}  exp_part;
    CharType            this_term;
    Bool                test_value;
    static n_char       term[MAX_VAR_LENGTH];

    pnode = newNode( NULL );

    exp_part = LEFT;
    expression = &pnode->left;

    while ( (this_term = getTerm( term )) != C_END &&
            this_term != C_CLOSE_PAREN )
    {
        this_term = identifyTerm( term, &op );
        switch (this_term)
        {
        case C_VARIABLE:
            expression->type = IS_VAR;
            expression->this.variable = saveVariable(term);
            break;

        case C_CONSTANT:
            test_value = (term[0] == 'T') ? TRUE : FALSE;
            expression->type = IS_CONSTANT;
            expression->this.constant = test_value;
            break;

        case C_UNARY:
            expression->unary = op->type;
            break;

        case C_OPERATOR:
            switch (exp_part)
            {
            case LEFT:
                pnode->bin_op = op;
                exp_part = RIGHT;
                expression = &pnode->right;
                break;
            case RIGHT:
                if (op->precedence > pnode->bin_op->precedence)
                {
                    /* Do this op first */
                    pnode = addRight(pnode);
                    pnode->bin_op = op;
                }
                else
                {
                    /*     Do other op first */
                    while (pnode->parent != NULL &&
                            ( op->precedence <=
                              pnode->parent->bin_op->precedence) )
                    {
                        pnode = pnode->parent;
                    }
                    newnode = insertRight(pnode);
                    newnode->bin_op = op;
                    pnode = newnode;
                }
                expression = &pnode->right;
                break;
            }
            break;

        case C_OPEN_PAREN:
            newnode = parseRule();
            newnode->parent = pnode;
            expression->type = IS_POINTER;
            expression->this.child = newnode;
            break;

        case C_INVALID:
        default:
            th_exit( 1, "%s:%d - illegal term %c\n",term, __FILE__, __LINE__ );
        }
    }

    /* --- Return the "root" of the tree we've created so far */
    while (pnode->parent != (Node*)NULL)
    {
        pnode = pnode->parent;
    }

    return pnode;
}



/************************************************************
FUNCTION NAME: getTerm

DESCRIPTION:
    Get next term in a string.  Return the "type" of the term,
    which is actually the same as the type of the first character.
    Skip over any whitespace found.

    NOTE:  This function makes use of a static input buffer and
    current position pointer, which is reset by the input function.
    
    n_char term[] - output buffer for extracted term
 
RETURN:
    class of character (or term)
*************************************************************/

static CharType getTerm( n_char term[] )
{

    CharType    term_type = C_INVALID;
    n_char *    p = l_inputBufferPosition;
    n_int       n;

    if (p != NULL)
    {
        while ((term_type = l_characterType[(n_int)*p]) == C_SPACE)
        {
            ++p;
        }

        if (term_type != C_INVALID && term_type != C_END)
        {
            n = 0;
			if (term_type == C_VARIABLE) {
				/*SG: Variables can be multi char, accumulate as long as term type is variable*/
				while ( l_characterType[(n_int)(term[n++] = *(p++))]
							== term_type ) {}
				--p;
				term[n-1] = NULLCHAR;
			} else {
				/*SG: All other terms are single chars only*/
				term[0]=*p++;
				term[1]=NULLCHAR;
			}
        }

        l_inputBufferPosition = p;
    }

    return term_type;
}



/************************************************************
FUNCTION NAME: identifyTerm

DESCRIPTION:
    Look at a term to see what type it is.  If it looks like a name,
    then check against the list of operator names to see if it is a
    reserved word.  For symbols, look up the actual operator and
    return that.

RETURN:
    Character (term) type
*************************************************************/

static CharType identifyTerm( n_char term[], Operator **op )
{
    n_int               i;
    n_int               compare;
    Operator *          this;
    CharType            this_type = l_characterType[(n_int)term[0]];

    switch (this_type)
    {
    case C_VARIABLE:
        /*  Do a binary search through the list of operator names to */
        /*  see if we can identify this term as an operator rather than */
        /*  a variable. */
        this = OperatorTree;
        while (this != NULL)
        {
            if ((compare = strcmp(term, this->name)) == 0)
            {
                *op = this;
                term[0] = this->symbol;
                term[1] = NULLCHAR;
                this_type = (this->mode==BINARY) ? C_OPERATOR : C_UNARY;
                break;
            }
            this = (compare > 0) ? this->higher : this->lower;
        }
        break;

    case C_OPERATOR:
    case C_UNARY:
        /*  If we only have the single character symbol, then we have to */
        /*  do a brute force search through the list... */
        for ( i = 0; oplist[i].symbol != term[0] && i < OPLIST_LEN; ++i)
            ;
        *op = &oplist[i];
        break;

    default:
        break;
    }

    return this_type;
}



/************************************************************
FUNCTION NAME: addRight

DESCRIPTION:
    Replace the expression on the right hand side of a node with
    a pointer to another node.  Copy the original right side to the
    left side of the new node.

RETURN:
    Node* pointer to new node
*************************************************************/

static Node *addRight( Node *prev )
{
    Node *      new = newNode( prev );

    if (prev != (Node *)NULL)
    {
        new->left = prev->right;          /*  copy original expr */
        prev->right.type = IS_POINTER;    /*  this is ptr, not simple var */
        prev->right.this.child = new;     /*  pointer to new Right child */

        /* =================================================== */
        /*  If the right hand expression is a pointer, then    */
        /*  change the child's parent pointer                  */
        /* =================================================== */
        if (new->left.type == IS_POINTER)
        {
            new->left.this.child->parent = new;
        }
    }

    return new;
}



/************************************************************
FUNCTION NAME: insertRight

DESCRIPTION:
    Create a new node, pointing to the original node as the
    left expression.  Return pointer to newly created Node

RETURN:
    Node* pointer to new node
*************************************************************/

static Node *insertRight( Node *old )
{
    Node *      new = newNode( (Node*)NULL );
    Node *      parent;

    if (old != (Node *)NULL)
    {
        new->left.type = IS_POINTER;    /*  this is ptr, not simple var */
        new->left.this.child = old;     /*  point to "old" as its child */
        if ((parent=old->parent) != NULL)
        {
            if (parent->right.this.child == old)
            {
                parent->right.this.child = new;
            }
        }
        new->parent = old->parent;
        old->parent = new;
    }

    return new;
}


/* ====================================================================== */
/*             I N I T I A L I Z E                                        */
/* ====================================================================== */

/************************************************************
FUNCTION NAME: initFreeNodes

DESCRIPTION:
    In order to avoid the use of "malloc" to create new nodes,
    set up a large block of available nodes, using the "parent"
    pointer to keep track of the free list.

RETURN:
    none
*************************************************************/

n_void initFreeNodes( n_void )
{
    n_int    n;

    NodeBlock[0].parent = NULL;

    for (n=1; n < NODE_BLOCK_SIZE; ++n)
    {
        NodeBlock[n].parent = &NodeBlock[n-1];
    }

    NextFreeNode = &NodeBlock[NODE_BLOCK_SIZE-1];
}



/************************************************************
FUNCTION NAME: initCharacterTypes

DESCRIPTION:
    initialize the lookup table for character classes.  This table
    is used when parsing out individual terms off the input line

RETURN:
    none
*************************************************************/

n_void initCharacterTypes( n_void )
{
    n_int i;
    n_int j;


    for (i=0; i < 256; ++i)
    {
        switch (i)
        {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        case 'a': case 'b': case 'c': case 'd': case 'e':
        case 'f': case 'g': case 'h': case 'i': case 'j':
        case 'k': case 'l': case 'm': case 'n': case 'o':
        case 'p': case 'q': case 'r': case 's': case 't':
        case 'u': case 'v': case 'w': case 'x': case 'y':
        case 'z': case '_':
            l_characterType[i] = C_VARIABLE;
            break;

        case 'T': case 'F':
            l_characterType[i] = C_CONSTANT;
            break;

        case '[': case '{': case '(':
            l_characterType[i] = C_OPEN_PAREN;
            break;

        case ']': case '}': case ')':
            l_characterType[i] = C_CLOSE_PAREN;
            break;

        case ' ': case '\t':
            l_characterType[i] = C_SPACE;
            break;

        case '\0': case '\n': case '#':
            l_characterType[i] = C_END;
            break;

        default:
            l_characterType[i] = C_INVALID;
            for (j=0; j < OPLIST_LEN; ++j)
            {
                if (i == oplist[j].symbol)
                {
                    l_characterType[i] = (oplist[j].mode == BINARY)
                                        ? C_OPERATOR : C_UNARY;
                    break;
                }
            }
            break;
        }
    }

    return;
}



/************************************************************
FUNCTION NAME: initVariables

DESCRIPTION:
    initialize the variables array - set the counter to ZERO

RETURN:
    none
*************************************************************/

n_void initVariables( n_void )
{
    variable_count = 0;
    VariableTree = NULL;

    return;
}


/************************************************************
FUNCTION NAME: initOperatorTree

DESCRIPTION:
    initialize the Operator Btree, used to check for
    spelled out operations (e.g., "and", "or" etc.)

RETURN:
    none
*************************************************************/

n_void initOperatorTree( n_void )
{
    n_int         i;
    Operator *    this;
    Operator *    prev;
    n_int         compare = -1;

    OperatorTree = &oplist[0];
    OperatorTree->higher = OperatorTree->lower = NULL;

    for (i = 1; i < OPLIST_LEN; ++i)
    {
        oplist[i].higher = oplist[i].lower = NULL;

        /*  --- Trace down the btree to find where to add the name */
        this = prev = OperatorTree;
        while (this != NULL)
        {
            prev = this;
            compare = strcmp(oplist[i].name, this->name);
            this = (compare > 0) ? this->higher : this->lower;
        }

        /*  --- at the leaf of the tree - add here */
        if (compare > 0)
        {
            prev->higher = &oplist[i];
        }
        else
        {
            prev->lower = &oplist[i];
        }
    }

    return;
}



/* ====================================================================== */
/*             M E M O R Y   M A N A G E M E N T                          */
/* ====================================================================== */

/************************************************************
FUNCTION NAME: newNode

DESCRIPTION:
    Return a pointer to an initialized btree Node

RETURN:
    Node* new node
*************************************************************/

static Node *newNode( Node *parent )
{
    Node *      p = NextFreeNode;

    if (p != (Node *)NULL)
    {
        NextFreeNode = NextFreeNode->parent;  /*  point to next available */

        p->bin_op      = NULL;                /*  nothing here yet */
        p->left.type   = IS_EMPTY;
        p->left.unary  = NOOP;
        p->right.type  = IS_EMPTY;
        p->right.unary = NOOP;
        p->parent      = parent;
    }
    else
    {
        th_exit( THE_FAILURE, "%s:%d - out of memory. Unreleased nodes: %d\n", __FILE__, __LINE__, nodecnt );
    }
	nodecnt++;
    return p;
}



/************************************************************
FUNCTION NAME: release

DESCRIPTION:
    Release memory in parse tree (RECURSIVE)

RETURN:
    none
@bug When a variable occurs just after a paran, release does not discover the node.
The parser allocates a node, then goes to open_paren which recursively calls parser.
The current node is empty, and becomes the top of the tree returned by parser, and 
passed to release (eventually).
*************************************************************/

n_void release( Node *p )
{
    if (p != (Node *)NULL)
    {
        if (p->left.type == IS_POINTER)
        {
            release(p->left.this.child);
        }
        if (p->right.type == IS_POINTER)
        {
            release(p->right.this.child);
        }
        p->bin_op      = NULL;                /*  nothing here yet */
        p->left.type   = IS_EMPTY;
        p->left.unary  = NOOP;
        p->right.type  = IS_EMPTY;
        p->right.unary = NOOP;
        p->parent = NextFreeNode;       /*  Return to free list */
        NextFreeNode = p;
		nodecnt--;
    }

    return;
}



/************************************************************
FUNCTION NAME: saveVariable

DESCRIPTION:
    Check first through the binary tree to see if this name already
    exists, and if found, return a pointer to existing variable.
    Otherwise, add the name to the variable list (and bump the
    counter), and return a pointer to this object.

RETURN:
    pointer to variable just created
*************************************************************/

static Variable *saveVariable( n_char *name )
{
    Variable *    this;
    Variable *    prev;
    n_int         compare = -1;

    this = prev = VariableTree;
    while (this != NULL)
    {
        prev = this;
        if ((compare = strcmp(name, this->name)) == 0)
        {
            return this;
        }
        this = (compare > 0) ? this->higher : this->lower;
    }

    /*  --- Not found - create a new one */
    if (variable_count < MAX_VARIABLES-1)
    {
        this = &variables[variable_count++];
        strncpy(this->name, name, MAX_VAR_LENGTH);
        this->higher = this->lower = NULL;

        if (prev == NULL)
        {
            VariableTree = this;            /*  First name on the list! */
        }
        else
        {
            if (compare > 0)
            {
                prev->higher = this;
            }
            else
            {
                prev->lower = this;
            }
        }
    }
    else
    {
        th_exit( 1, "%s:%d - overflow on variables list",
                  __FILE__, __LINE__ );
    }

    return this;
}



/* ====================================================================== */
/*             E V A L U A T E                                            */
/* ====================================================================== */

/************************************************************
FUNCTION NAME: doRule

DESCRIPTION:
    Fill in values in truth table (RECURSIVE) and evaluate expression

    This function calls itself recursively to fill in the variable
    list with all possible combinations of values.  As each combination
    is filled (i.e., it fills in the last variable), the next call
    causes the line to be printed out, and the rule, now contained
    in the parse tree, to be evaluated.

    n_int     n      - what level we're on
    Node *    ptree  - pointer to parse tree

RETURN:
    none
*************************************************************/

static n_void doRule( n_int n, Node *ptree )
{

    if (n == 0)
    {
        printTruthTableHeading();
    }

    if (n < variable_count)
    {           /*  if this is a valid variable... */
        variables[n].value = FALSE;     /*    then fill in a value, and... */
        doRule(n + 1, ptree);           /*       ...look at the next spot. */
        variables[n].value = TRUE;
        doRule(n + 1, ptree);
    }
    else
    {                              /*  if at end of list */
        eval(ptree);                            /*    ...and evaluate */
    }

    return;
}



/************************************************************
FUNCTION NAME: eval

DESCRIPTION:
    Evaluate an expression at one level (RECURSIVE)

    (Get the values of the two sides of the expression, and then, if
    there is a valid binary operator, evaluate it.)
    
    Node *  p  - pointer to root of tree

RETURN:
    Bool value of expression
*************************************************************/

static Bool eval( Node *p )
{
    Bool        valueL;
    Bool        valueR;
    Bool        Ans;

    /* ---------- Left -------------------- */
    valueL = unaOp(value(p->left), p->left.unary);

    /* ---------- Right ------------------- */
    valueR = unaOp(value(p->right), p->right.unary);

    /* ---------- Evaluate ---------------- */
    Ans = (p->bin_op!=NULL) ? binOp(valueL, valueR, p->bin_op->type) : valueL;

    return Ans;
}



/************************************************************
FUNCTION NAME: value

DESCRIPTION:
    Look at an expression and return its value
    IS_EMPTY, IS_VAR, IS_CONSTANT, IS_POINTER

RETURN:
    Bool value of this expression
*************************************************************/

static Bool value( Expression expression )
{
    Bool l_value = FALSE;

    switch (expression.type)
    {
    case IS_VAR:
        l_value = expression.this.variable->value;
        break;
    case IS_CONSTANT:
        l_value = expression.this.constant;
        break;
    case IS_POINTER:
        l_value = eval(expression.this.child);
        break;
    case IS_EMPTY:
    default:
        break;
    }

    return l_value;
}



/* ------Define "simple" operations on type Bool------ */
#define And(a, b)       ((a) &&  (b))
#define Or(a, b)        ((a) ||  (b))
#define Not(a)          (!(a))
#define Equ(a, b)       ((a) == (b))
/* --------------------------------------------------- */

/************************************************************
FUNCTION NAME: binOp

DESCRIPTION:
    Do Binary op on two values

RETURN:
    Bool value
*************************************************************/

static Bool binOp( Bool p, Bool q, OpType op )
{
    Bool        F;

    switch (op)
    {
    case AND:
        F = And(p, q);
        break;

    case OR:
        F = Or(p, q);
        break;

    case THEN:
        F = Or(Not(p), q);
        break;

    case IF:
        F = Or(p, Not(q));
        break;

    case EQUI:
        F = Equ(p, q);
        break;

    case NEQU:
        F = Not(Equ(p, q));
        break;

    case NAND:
        F = Not(And(p, q));
        break;

    case NOR:
        F = Not(Or(p, q));
        break;

    default:
        F = p;
        break;
    }

    return F;
}



/************************************************************
FUNCTION NAME: unaOp

DESCRIPTION:
    Do Unary op on one value

RETURN:
    Bool
*************************************************************/

static Bool unaOp( Bool p, OpType op )
{
	Bool	F;

	switch (op)
	{
		case NOT:
			F = (p) ? FALSE : TRUE;
			break;

		default:
			F = p;
	}
	return F;
}



/* ====================================================================== */
/*             O U T P U T                                                */
/* ====================================================================== */

/************************************************************
FUNCTION NAME: printTruthTableHeading

DESCRIPTION:
    print the variable names to label the columns in the truth table.
    Include the names (A, B, C...) of the intermediate values
    generated parsing the btree.

    Globals used:
        variable_count - number of variables defined in this expression
        variables - names of these variables
        l_expLetter - highest name of an intermediate calculated value

RETURN:
    none
*************************************************************/

static n_void printTruthTableHeading( n_void )
{
#ifdef PRINTOUTTEXT
    n_int         i;
    n_int         j;
    n_char        c;

    /* ==== Print Names */
    for (i = 0; i < variable_count; ++i)
    {
        th_printf( " %s |", variables[i].name);
    }
    for (c = 'A'; c < l_expLetter - 1; ++c)
    {
        th_printf( " %c |", c);
    }
    th_printf( " Fn\n");

    /* ==== Print the dashes */
    for (i = 0; i < variable_count; ++i)
    {
        for (j = strlen(variables[i].name); j > 0; --j)
        {
            th_printf( "-");
        }
        th_printf( "--+");
    }
    for (c = 'A'; c < l_expLetter - 1; ++c)
    {
        th_printf( "---+");
    }
    th_printf( "---+\n");

#endif /*  PRINTOUTTEXT */

    return;

}


/************************************************************
FUNCTION NAME: printNodes

DESCRIPTION:
    print out tree heirarchy

    The "right_name" and "left_name" variables are automatic names
    created for intermediate values as the evaluation bubbles up the
    tree.

RETURN:
    the automatic name just created
*************************************************************/

n_char printNodes( Node *p )
{

    n_char        left_name;
    n_char        right_name;    /*  names for left and right expressions */
    n_char        this_name = 0;

    if (p != (Node *)NULL)
    {
        /* ---------- Left -------------------- */
        if (p->left.type == IS_POINTER)
        {
            left_name = printNodes(p->left.this.child);
        }
        /* ---------- Right ------------------- */
        if (p->right.type == IS_POINTER)
        {
            right_name = printNodes(p->right.this.child);
        }

#ifdef PRINTOUTTEXT
        /* ---------- Left -------------------- */
        th_printf(  "%c: ", (this_name = l_expLetter++) );
        printExpression(left_name, &p->left);
        if (p->bin_op != NULL)
        {
            th_printf(  " %c ", p->bin_op->symbol );
        }
        printExpression(right_name, &p->right);
        th_printf(  "\n" );
#endif /*  PRINTOUTTEXT */

    }

    return this_name;
}


#ifdef PRINTOUTTEXT
/************************************************************
FUNCTION NAME: printExpression

DESCRIPTION:
    print a single expression name, or a letter for an
    intermediate value if this is a pointer to another node

RETURN:
    none
*************************************************************/

static n_void printExpression( n_char c, Expression *exp )
{
    if (exp->unary != NOOP)
    {
        th_printf(  "%c", opSymbol(exp->unary) );
    }

    switch (exp->type)
    {
    case IS_POINTER:
        th_printf(  "%c", c );
        break;
    case IS_VAR:
        th_printf(  "%s", exp->this.variable->name );
        break;
    case IS_CONSTANT:
        th_printf(  "%c", (exp->this.constant == TRUE) ? 'T' : 'F' );
        break;
    default:
        break;
    }
    return;
}


/************************************************************
FUNCTION NAME: opSymbol

DESCRIPTION:
    Return character representing an operation

RETURN:
    none
*************************************************************/

static n_char opSymbol( OpType op )
{
    n_int        i = 0;

    while (oplist[i].type != op && i < OPLIST_LEN)
    {
        ++i;
    }

    return oplist[i].symbol;
}
#endif /*  PRINTOUTTEXT */
