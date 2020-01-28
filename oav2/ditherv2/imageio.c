/*==============================================================================
 *$RCSfile: imageio.c,v $
 *
 *   DESC : This file contains the Test Main and other TH support functions
 *
 * AUTHOR : C Tyron
 *
 *  EEMBC : Office Automation Subcommittee 
 *
 *    CVS : $Revision: 1.6 $
 *          $Date: 2005/04/27 20:37:59 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/office/ditherv2/imageio.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: imageio.c,v $
 * Revision 1.6  2005/04/27 20:37:59  rick
 * Copyrite update 2005
 *
 * Revision 1.5  2004/09/08 05:18:56  rick
 * Add additional office datasets to complete makefile build
 *
 * Revision 1.4  2004/07/07 18:04:41  rick
 * Resolve type definition recursion on Linux GCC
 *
 * Revision 1.3  2004/02/04 01:05:43  rick
 * Add libresource, new cinit features
 *
 * Revision 1.2  2004/01/29 00:34:12  rick
 * Resolve header file cycles
 *
 * Revision 1.1  2004/01/23 00:29:39  rick
 * Initial dither V2
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

/**
@file
@brief
    Binary Image Output (either BMDEBUG mode or normal)
	Uses Portable Gray Map binary format for input and output.
*/


/* --------------------------------------------------------------------- */
/*         I N C L U D E S                                               */
/* --------------------------------------------------------------------- */

/* FILENAME_MAX */
#include <stdio.h>

/* ==== Project Wide Headers */
#include "kernel.h"

/* ==== Algorithm specific headers */
#include "dither.h"
#include "masks.h"
#include "imageio.h"
#include "algo.h"
/* ==== image I/O libraries */
#include <string.h>

/* Prototypes */

/** Initialize Test Harness file system for libtxt, based on DATA_x define. */
void init_libpgm(void);
unsigned long ee_uid=EE_UID;
e_u16 expected_crc=EXPECTED_CRC;
unsigned long ee_uid_all[NUM_DATAS] = {EE_UID_1,EE_UID_2,EE_UID_3,EE_UID_4
	,EE_UID_5,EE_UID_6,EE_UID_7,EE_UID_8,EE_UID_9,EE_UID_10,EE_UID_11};
e_u16 expected_crc_all[NUM_DATAS] = {EXPECTED_CRC_1,EXPECTED_CRC_2,EXPECTED_CRC_3
	,EXPECTED_CRC_4,EXPECTED_CRC_5,EXPECTED_CRC_6,EXPECTED_CRC_7,EXPECTED_CRC_8
	,EXPECTED_CRC_9,EXPECTED_CRC_10,EXPECTED_CRC_11};

char pbm_getc(ee_FILE* file);
int pbm_getint(ee_FILE* file);
ee_FILE *pathfind_file(const char *filename, const char *filemode);

/* --------------------------------------------------------------------- */
/*         D E F I N E S                                                 */
/* --------------------------------------------------------------------- */

#define ONCHAR          '*'
#define OFFCHAR         ' '
#define CHAR_PER_ROW    (15)

/* ===================================================================== */
/*         I N P U T                                                     */
/* ===================================================================== */

/** Defined in libpgm_init.c. */
extern const char *DATANAME;

/** Initialize File System. */
void	init_files(void)
{
	init_libpgm();
}

/** Get character from PBM file header. */
char pbm_getc(ee_FILE* file)
{
   char ch;

   ch = th_getc(file);

   if (ch=='#')
   {
      do
      {
         ch = th_getc(file);
      }
      while (ch!='\n' && ch!='\r');
   }

   return ch;
}
/** Get integer from PBM file header. */
int pbm_getint(ee_FILE* file)
{
	char ch;
	int i;

	do
	{
		ch = pbm_getc(file);
	}
	while (ch==' ' || ch=='\t' || ch=='\n' || ch=='\r' || ch=='\x00A');

	i = 0;

	do
	{
		i = i*10 + ch-'0';
		ch = pbm_getc(file);
	}
	while (ch>='0' && ch<='9');

	/* Added so that trailing CRLF (Windows) LF is removed from end of header */
	while (ch==' ' || ch=='\t' || ch=='\n' || ch=='\r' || ch=='\x00A')
	{
		ch = pbm_getc(file);
	}
	th_ungetc(ch,file);
	return i;
}
/** Find and Open a file */
ee_FILE *pathfind_file(const char *filename, const char *filemode)
{
	char	*path[] = {"","../../","../../libpgm/","libpgm/",NULL};
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

/** Read in a grayscale image in PGM format.
@parm height - Height returned from pgm file.
@parm width - Width returned from pgm file.
@retval e_u8* image buffer, (return parameters, height and width)
*/
e_u8 *readImage( n_int *height, n_int *width )
{
    ee_FILE *      fd;
    e_u8 *      input_image;
	char		magicnumber[2];
	int 		maxcolors;
	int			imgsize;

	/** Open data file. */
	if ((fd = pathfind_file( DATANAME, "rb" ))==NULL)
		th_exit(THE_FAILURE,"Could not open input file: %s\n",DATANAME);
	else
		th_printf(">> Opened data file: %s\n",DATANAME);
	/* The format matches TH info. */
#if (TRAINING==1)
	th_printf(">> Data Set                 : training\n");
#else
	th_printf(">> Data Set                 : %s\n",DATANAME);
#endif
	th_printf(">> UID: %d\n",ee_uid);
	/* Get the PBM header information from the file */

	magicnumber[0] = pbm_getc(fd);	/* magic number (P5) */
	magicnumber[1] = pbm_getc(fd);
	*width = pbm_getint(fd); /* width height maxcolors */
	*height = pbm_getint(fd);
	maxcolors = pbm_getint(fd); /* assume 8 bits/pixel (grayscale) */

	imgsize = *height * *width;

    input_image = (e_u8*)th_malloc( imgsize );
	th_fread(input_image,imgsize,1,fd);
    th_fclose( fd );

    return input_image;
}

/* ===================================================================== */
/*         O U T P U T                                                   */
/* ===================================================================== */

/** Print out image buffer in PGM Binary format */

void outputBinaryImage( e_u8 *image, int height, int width )
{
	ee_FILE	*fd;
	char buf[100];
	const char *oname = "DitherOutput";

	th_sprintf(buf,"P5\n%d\n%d\n255\n",width,height);
	th_fcreate(oname,"wb",NULL,width*height+strlen(buf)+1);
	fd=th_fopen(oname,"wb");
	th_fwrite(buf,strlen(buf)-1,1,fd);
	th_fwrite(image,width*height,1,fd);
	th_fclose(fd);
}

