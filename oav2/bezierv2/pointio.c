/*==============================================================================
 *$RCSfile: pointio.c,v $
 *
 *   DESC : Bezier Interpolation
 *
 * AUTHOR : C Tryon
 *
 *  EEMBC : Office Automation Subcommittee 
 *
 *    CVS : $Revision: 1.5 $
 *          $Date: 2005/06/14 02:23:58 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/office/bezierv2/pointio.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: pointio.c,v $
 * Revision 1.5  2005/06/14 02:23:58  rick
 * Remove hard coded f_64 declarations from parsedouble for platforms with only 32 bit floats.
 *
 * Revision 1.4  2005/04/27 20:37:52  rick
 * Copyrite update 2005
 *
 * Revision 1.3  2004/09/08 21:03:15  rick
 * Modify CRC algorithms for toolchain differences
 *
 * Revision 1.2  2004/09/08 05:18:53  rick
 * Add additional office datasets to complete makefile build
 *
 * Revision 1.1  2004/05/03 22:27:46  rick
 * Add text, bezier, rotate base for v2
 *
 * Revision 1.3  2002/04/19 19:56:34  rick
 * Bug 137: Compiler Optimization Problem
 *
 * Revision 1.2  2002/03/11 22:11:50  rick
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
    I/O for points in curve definitions
***************************************************************************/

/*********************************************************************
    Includes
**********************************************************************/

/* atoi */
#include <stdlib.h> 
/* strlen, strcpy, etc. */
#include <string.h>
/* isspace */
#include <ctype.h>

/* ==== Project Wide Headers */
#include "kernel.h"

/* ==== Algorithm specific headers */
#include "bez.h"
#include "pointio.h"


/*********************************************************************
    Local Function Prototypes
**********************************************************************/

static Point    setPoint( Scalar X, Scalar Y );
static Point    parseInputLine( n_char *line );
static Scalar   parseDouble( n_char *string );

#ifdef DRAW
/*  --------- DIAGNOSTIC FUNCTIONS */
static n_void   drawPoints( Curve curve, Point array[], n_int count );
static Box      setBoundingBox( Curve curve );
static n_void   addToBoundingBox( Box *bounds, Point p );
static n_int    xIndex( Box b, Point p );
static n_int    yIndex( Box b, Point p );
#endif        /*  DRAW */

/* ===================================================================== */
/*         TH OUTPUT                                                     */
/* ===================================================================== */

#include "thlib.h"
#include "algo.h"
unsigned long ee_uid=EE_UID;
e_u16 expected_crc=EXPECTED_CRC;
unsigned long ee_uid_all[NUM_DATAS] = {EE_UID_1,EE_UID_2,EE_UID_3,EE_UID_4};
e_u16 expected_crc_all[NUM_DATAS] = {EXPECTED_CRC_1,EXPECTED_CRC_2,EXPECTED_CRC_3,EXPECTED_CRC_4};

/*
 *	Prototype
 */

/** Initialize Test Harness file system for libtxt, single file based on DATA_x define. */
void init_libbez(void);

Scalar	parametric(Scalar t, Scalar p0, Scalar p1, Scalar p2, Scalar p3);

/************************************************************
FUNCTION NAME: outputPoints

DESCRIPTION:
    Interpolate a set of points on an array of Bezier curves

    This is the same as the "InterpolatePoints" function, except
    that it includes output of the interpolated data points.

RETURN:
    none
*************************************************************/

n_void outputPoints( Curve *curve, n_int count )
{
    n_int       n;
    n_int       step;           /*  interpolation iterator */
    Point       point;
    Curve       c0;
    Scalar      t;              /*  parametric value */
#ifdef DRAW
    Point        interp[PARM_STEPS];
#endif

#ifdef PRINTOUTPTS
    th_printf( "\n" );
#endif /* PRINTOUTPTS */

    for ( n = 0; n < count; ++n )
    {
        c0 = curve[n];

#ifdef PRINTOUTPTS
        th_printf( "  ---> (%.3f,%.3f) - (%.3f,%.3f)\n",
                 F2D(c0.p1.X),F2D(c0.p1.Y), F2D(c0.p2.X),F2D(c0.p2.Y) );
#endif /* PRINTOUTPTS */

        for ( step = 0; step < PARM_STEPS; ++step )
        {
            /* t = (Scalar)step / PARM_STEPS; */
            t = SCALAR(step) / (Scalar)PARM_STEPS;
            point.X = parametric( t, c0.p1.X, c0.c1.X, c0.c2.X, c0.p2.X );
            point.Y = parametric( t, c0.p1.Y, c0.c1.Y, c0.c2.Y, c0.p2.Y );
#ifdef PRINTOUTPTS
            th_printf( "(%.4lf,%.4lf)\n", F2D(point.X), F2D(point.Y) );
#endif /* PRINTOUTPTS */
#ifdef DRAW
            interp[step] = point;
#endif
        }

#ifdef DRAW
        drawCurvePoints( curve[n], interp, PARM_STEPS );
#endif
    }
}


/* ===================================================================== */
/*         I N P U T                                                     */
/* ===================================================================== */

/** Defined in libbez_single.c. */
extern char *DATANAME;

/** Initialize File System. */
void	init_files(void)
{
	init_libbez();
}
/** Find and Open a file */
ee_FILE *pathfind_file(const char *filename, const char *filemode)
{
	char	*path[] = {"","../../","../../libbez/","libbez/",NULL};
	char	buf[FILENAME_MAX];
	int		i=0;
	ee_FILE	*found_file=NULL;

	if ((strcmp(filename,"stdin")) == 0) return th_fopen(filename,filemode);

while (path[i] != NULL)
{
	strcpy(buf,path[i]);
	strcat(buf,filename);
	if ( (found_file = th_fopen(buf,filemode)) != NULL ) return found_file;
	i++;
}
return NULL;
}


/************************************************************
FUNCTION NAME: readDataPoints

DESCRIPTION:
    read in a series of Curve structures from an external data file

RETURN:
    Curve* points array
*************************************************************/

Curve *readDataPoints( n_int *count, n_int *test_idx, Point **golden_points )
{
    ee_FILE 	*fd;
    n_int       n;
    Point       point;
    n_char      line[1024];
    n_int       point_count;    /*  total number of points READ from file */
    n_int       curve_count;
    Curve		*curve;
	n_int		curve_points=1;
	Point		*golden;
	*test_idx=0;

	/** Open data file. */
	if ((fd = pathfind_file( DATANAME, "rb" ))==NULL)
		th_exit(THE_FAILURE,"Could not open input file: %s\n",DATANAME);
	/* The format matches TH info. */
#if (TRAINING==1)
	th_printf(">> Data Set: training\n");
#else
	th_printf(">> Data Set: %s\n",DATANAME);
#endif
	th_printf(">> UID: %d\n",ee_uid);

	/* Get the number of rules in the file */
	point_count=0;
	while (!th_feof(fd) && curve_points)
	{
		*line=0;
		th_fgets(line,sizeof(line),fd);
		if (line[0]=='!')  /* detect beginning of interpolated point sample */
			curve_points=0;
		else
		if (strlen(line))
			point_count++;
	}
	/** rewind file. */
	th_fseek(fd,0,SEEK_SET);
	curve_points=1;
	
    /*  Create an array of curve elements to hold all the points read in */
    curve = (Curve*)th_malloc( (point_count/4)*sizeof(Curve) );
    golden = (Point *)th_malloc( (point_count/4)*sizeof(Point) );
#if BMDEBUG
	th_printf("Curve data size %d\n",(point_count/4)*sizeof(Curve));
	th_printf("Golden data size %d\n",(point_count/4)*sizeof(Point));
#endif
    /*  Read all points into the curve array once */
    for ( n = 0, curve_count=0; n < point_count; ++n )
    {
        if ( th_fgets( line, sizeof(line), fd ) != NULL )
        {
            point = parseInputLine( line );
            switch ( n%4 )
            {
            case 0: {
                    curve[curve_count].p1 = point;
                    break;
                }
            case 1: {
                    curve[curve_count].c1 = point;
                    break;
                }
            case 2: {
                    curve[curve_count].c2 = point;
                    break;
                }
            case 3: {
                    curve[curve_count].p2 = point;
                    ++curve_count;
                    break;
                }
            default: {
                    th_exit( THE_FAILURE, "Failure: invalid switch case\n" );
                }
            }
        }
        else
        {
            th_exit( THE_FAILURE, "Failure: EOF in point datafile\n" );
        }
    }
	curve_points=1;
    if ( th_fgets( line, sizeof(line), fd ) != NULL ) {
	/* start of interpolated points */
		if (line[0]=='!')
		{
			*test_idx=(line[1]-'0');
			curve_points=0;
		}
	}
	if (curve_points)
	{ /* no interpolated data in file */
		for ( n = 0; n < curve_count; ++n )
		{
			golden[n]=curve[n].p1;
		}
	} else { /* interpolated data exists, read it */
		for ( n = 0; n < curve_count; ++n )
		{
			if ( th_fgets( line, sizeof(line), fd ) != NULL )
			{
				point = parseInputLine( line );
				golden[n]=point;
			} else {
				th_exit( THE_FAILURE, "Failure: EOF in point datafile\n" );
			}
		}
	}

    *count = curve_count;
	*golden_points=golden;

    return curve;
}



/************************************************************
FUNCTION NAME: setPoint

DESCRIPTION:
    Create a Point from two double

RETURN:
    created Point
************************************************************/

static Point setPoint( Scalar X, Scalar Y )
{
    Point       this;

    this.X = X;
    this.Y = Y;

    return this;
}


/* ===================================================================== */
/*         INPUT PARSING                                                 */
/* ===================================================================== */

/************************************************************
FUNCTION NAME: parseInputLine

DESCRIPTION:
    Parse a comma delimited input line into an (X,Y) point
    Note that this function could have been done using scanf(), but given
    the "embedded" nature of the benchmark, it was not known how much of
    the "C" library would be available

RETURN:
    Point p
************************************************************/

static Point parseInputLine( n_char *line )
{
    static n_char tmp_string[80];
    n_char *    s1;
    n_char *    s2;
    n_char      c;
    Scalar      X;
    Scalar      Y;

    s1 = line;
    s2 = tmp_string;
    while ( (*s2++ = *s1++) != ',' )
    {
    }
    *(s2-1) = NULLCHAR;
    X = parseDouble( tmp_string );

    s2 = tmp_string;
    while ( (c = *s2++ = *s1++) != '\n' && c != NULLCHAR )
    {
    }
    *(s2-1) = NULLCHAR;
    Y = parseDouble( tmp_string );

    return setPoint( X,Y );
}


/************************************************************
@brief    Parse a string to extract a single floating point number
@parm p String to parse double precision floating point.
@retval    Scalar num
************************************************************/

static Scalar parseDouble( n_char *p )
{
    n_int       integer = 0;
    n_int       fraction = 0;
    n_int       dec = 1;
    n_int       sign = 1;
    Bool        FoundDec = FALSE;
    Scalar		nn;

    while ( isspace(*p) )
    {
        ++p;
    }

    if ( *p == '-' )
    {
        sign = -1;
        ++p;
    }

    while ( (*p >= '0' && *p <= '9') || *p == '.' )
    {
        if ( *p == '.' )
        {
            FoundDec = TRUE;
        }
        else
        {
            if ( FoundDec )
            {
                fraction = fraction * 10 + (*p - '0');
                dec *= 10;
            }
            else
            {
                integer = integer * 10 + (*p - '0');
            }
        }
        ++p;
    }

    nn = (Scalar)sign * ((Scalar)integer + (Scalar)fraction / (Scalar)dec);

    return D2F(nn);
}


#ifdef DRAW

/* ===================================================================== */
/*         DIAGNOSTIC FUNCTIONS                                          */
/* ===================================================================== */

/************************************************************
FUNCTION NAME: drawPoints

DESCRIPTION:
    Draw a rough graph of the points

RETURN:
    none
************************************************************/

n_void drawCurvePoints( Curve curve, Point array[], n_int count )
{
    Box         bounds;
    n_char        grid[GRIDSIZEY][GRIDSIZEX+1];
    n_int         i;
    n_int         j;

    bounds = setBoundingBox( curve );
    for ( i=0; i<count; )
    {
        addToBoundingBox( &bounds, array[i++] );
    }

    for ( i=0; i<GRIDSIZEY; ++i )
    {
        for ( j=0; j<GRIDSIZEX; ++j )
        {
            grid[i][j] = ' ';
        }
        grid[i][j] = NULLCHAR;
    }

    for ( i=0; i<count; ++i )
    {
        grid[yIndex( bounds, array[i] )][xIndex( bounds, array[i] )] = '.';
    }

    grid[yIndex( bounds, curve.p1 )][xIndex( bounds, curve.p1 )] = '1';
    grid[yIndex( bounds, curve.c1 )][xIndex( bounds, curve.c1 )] = '2';
    grid[yIndex( bounds, curve.c2 )][xIndex( bounds, curve.c2 )] = '3';
    grid[yIndex( bounds, curve.p2 )][xIndex( bounds, curve.p2 )] = '4';
    th_printf( "    ----------\n" );
    for ( i=GRIDSIZEY-1; i>=0; --i )
    {
        th_printf( "   |%s|\n", grid[i] );
    }
    th_printf( "    ----------\n" );
}



/************************************************************
FUNCTION NAME: setBoundingBox

DESCRIPTION:
    Set a bounding box around a set of four points

RETURN:
    Box
************************************************************/

static Box setBoundingBox( Curve curve )
{
    Box         bounds;

    bounds.c1 = bounds.c2 = curve.p1;
    addToBoundingBox( &bounds, curve.c1 );
    addToBoundingBox( &bounds, curve.c2 );
    addToBoundingBox( &bounds, curve.p2 );

    return bounds;
}


/************************************************************
FUNCTION NAME: addToBoundingBox

DESCRIPTION:
    Add a single point into a bounding box

RETURN:
    n_void
************************************************************/

static n_void addToBoundingBox( Box *bounds, Point p )
{
    if ( p.X < bounds->c1.X )
    {
        bounds->c1.X = p.X;
    }
    if ( p.Y < bounds->c1.Y )
    {
        bounds->c1.Y = p.Y;
    }
    if ( p.X > bounds->c2.X )
    {
        bounds->c2.X = p.X;
    }
    if ( p.Y > bounds->c2.Y )
    {
        bounds->c2.Y = p.Y;
    }
}



/************************************************************
FUNCTION NAME: xIndex/yIndex

DESCRIPTION:
    Scale a point relative to the size of the graph
    xIndex Box b - column index
    yIndex Box b - row index
    
RETURN:
    int row/column index
************************************************************/

static n_int xIndex( Box b, Point p )
{
    return 1 + (n_int)( (GRIDSIZEX-2) * (p.X - b.c1.X) / (b.c2.X - b.c1.X));
}

static n_int yIndex( Box b, Point p )
{
    return 1 + (n_int)( (GRIDSIZEY-2) * (p.Y - b.c1.Y) / (b.c2.Y - b.c1.Y));
}

#endif        /*  DRAW */
