/**
 * @file
 * @brief  Functional Layer UUEncoding Routines
 *
 * $RCSfile: uuencode.c,v $
 *
 *  EEMBC : EEMBC Technical Advisory Group (TechTAG)
 *
 * @author  Sergei Larin, ECL, LLC
 *
 *    CVS : $Revision: 1.3 $
 *          $Date: 2006/03/09 17:34:18 $
 *          $Author: rick $
 *          $Source: /usr/local/cvs/eembc2/th_lite/src/uuencode.c,v $
 *          
 * @note   Simplified interface using UUENCODING (as specified in GNU) Writes it's
 *         output to stdout 
 *
 *
 * HISTORY :
 *
 * $Log: uuencode.c,v $
 * Revision 1.3  2006/03/09 17:34:18  rick
 * Version 2 Office Release Candidate 5
 *
 * Revision 1.17  2005/12/02 23:53:39  rick
 * Fix mixed EOL format causing ^M's to appear in Unix checkouts.
 *
 * Revision 1.16  2005/09/10 04:02:24  rick
 * eol update, add uu_send_file
 *
 * Revision 1.21  2005/04/27 20:32:56  rick
 * Copyrite update 2005
 *
 * Revision 1.20  2004/12/08 23:27:48  rick
 * New standard header for documentation generation.
 *
 * Revision 1.19  2004/06/23 05:55:25  rick
 * EE_REDIRECT, and Shared Files
 *
 * Revision 1.18  2004/06/14 18:02:20  rick
 * Bug 274: Precision in log files is not large enough for reporting results on simulators.
 *
 * Revision 1.17  2004/04/17 00:32:55  rick
 * Restore HAVE_STAT, Fix size_t
 *
 * Revision 1.16  2004/03/19 21:16:04  rick
 * Fix uuencode table
 *
 * Revision 1.15  2004/03/15 21:29:07  rick
 * Add documentation tags, and cleanup comments
 *
 * Revision 1.14  2004/02/26 08:42:09  rick
 * psnr/uudecode enhancements
 *
 * Revision 1.13  2004/01/22 00:56:53  rick
 * Release cleanup, copyright year corrections
 *
 * Revision 1.12  2003/01/22 00:00:57  rick
 * Add File I/O to Regular
 *
 * Revision 1.3  2003/01/17 22:44:37  rick
 * Add File I/O to harness
 *
 * Revision 1.2  2002/12/31 16:21:02  rick
 * Add harness stubs for memmgr
 *
 * Revision 1.1  2002/10/11 22:02:32  rick
 * Port uuencode to th_lite for mpeg
 *
 * Revision 1.10  2002/06/12 21:20:33  rick
 * Allow encode to be called from Bmark
 *
 * Revision 1.9  2002/05/23 16:31:52  rick
 * Bug #169, #170, #172, #173: Char/assert fixes
 *
 * Revision 1.8  2002/04/30 15:08:49  rick
 * Add extra newline to end so uudecode will recognize it
 *
 * Revision 1.7  2002/04/25 18:32:17  rick
 * Bug #115: Wrong printf format for a double-word variable
 *
 * Revision 1.6  2002/04/23 22:04:34  rick
 * Bug #88: Remove unused dump_buffer_as_binary, fputc is portability problem
 *
 * Revision 1.5  2002/04/10 19:37:00  rick
 * Fixes to reduce Lite vs. Regular variances in timing
 *
 * Revision 1.4  2002/04/02 17:06:28  administrator
 * Remove whitespace before # directives
 *
 *
 * @verbatim
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
 *------------------------------------------------------------------------------
 * @endverbatim
 */

#include <stdio.h>
#include "thlib.h"
#include "uuencode.h" 

/** @addtogroup SHFL
@{ */
/** @addtogroup uuencode_c Test Harness UUEncoding Routines.
@{ */

/** Standard encoding table. Base64 is not used
@note Some versions include a '`'  termination character.
*/
const Char uu_std[64] =
{
	'`', '!', '"', '#', '$', '%', '&', '\'',
	'(', ')', '*', '+', ',', '-', '.', '/',
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', ':', ';', '<', '=', '>', '?',
	'@', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
	'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
	'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
	'X', 'Y', 'Z', '[', '\\', ']', '^', '_'
};

/** Pointer to the translation table we currently use.  */
const Char *trans_ptr = uu_std;

/** ENC is the basic 1 character encoding function to make a char printing.  */
#define ENC(Char) (trans_ptr[(Char) & 077])

/** Gnu style uuencoding routine.
 *
 *  encodes buffer raw_buffer of size raw_buf_len
 *
 */ 
void encode (const char *raw_buffer, size_t raw_buf_len)
{
  size_t			ch, n	= 0;
  size_t		    buf_cnt = 0;
  Char			    buf[80];
  register Char     *p		= buf;
  

  if(raw_buf_len <= 0 || !raw_buffer)
  {
	  th_printf("Uuencode buffer parameters error.\n");
	  return;
  } 

  trans_ptr = uu_std;	/* used by ENC macro */

  while (1)
  {
	  for(n = 0; n<45;n++)
	  {
		  if(n+buf_cnt >= raw_buf_len) break; 
		  buf[n]	= raw_buffer[n+buf_cnt]; 
	  }
	  buf_cnt += 45; 

      if (n == 0)					break;
	  if (th_printf ("%c",ENC (n)) == EOF)	break;

	  for (p = buf; n > 2; n -= 3, p += 3)
	  {
			ch = *p >> 2;
			ch = ENC (ch);
			if (th_printf("%c",ch) == EOF)	break;
			ch = ((*p << 4) & 060) | ((p[1] >> 4) & 017);
			ch = ENC (ch);
			if (th_printf("%c",ch) == EOF)	break;
			ch = ((p[1] << 2) & 074) | ((p[2] >> 6) & 03);
			ch = ENC (ch);
			if (th_printf("%c",ch) == EOF)	break;
			ch = p[2] & 077;
			ch = ENC (ch);
			if (th_printf("%c",ch) == EOF)	break;
		}

		if (n != 0)						break;
		if (th_printf("\n") == EOF)		break;
    }

    while (n != 0)
	{
		Char c1 = *p;
		Char c2 = (Char) (n == 1 ?  0 :  p[1]);

		ch = c1 >> 2;
		ch = ENC (ch);
		if (th_printf("%c",ch) == EOF)		break;

		ch = ((c1 << 4) & 060) | ((c2 >> 4) & 017);
		ch = ENC (ch);
		if (th_printf("%c",ch) == EOF)		break;

		if (n == 1)
			ch = ENC ('\0');
		else{
			ch = (c2 << 2) & 074;
			ch = ENC (ch);
		}
		if (th_printf("%c",ch) == EOF)		break;
		ch = ENC ('\0');
		if (th_printf("%c",ch) == EOF)		break;
		th_printf("\n");
		break;
    }

	th_printf("\0\n");
}

/** Send buffer that uudecode will extract as a file.
@note Add spaces after file data to avoid short file warnings from uudecode.
@param buf data to encode.
@param length length of data
@param fn file name for uudecode.
@retval 0 Success (No user fail modes).
*/
int uu_send_buf( const char* buf, size_t length, const char* fn  )
{

   /* tell uudecode file mode (owner read/write), and file name. */ 
   th_printf ("begin 600 %s\n",fn);
   encode(buf,length);
   /* tell uudecode the file is done. */
   th_printf ("   \nend\n\n");
   return 0; /* Success; */ 
}
/** uuencode file buffer size, multiple of 80 from encode. */
#define	UU_FILE_BUFSIZ	4*80

/** Send uuencoded file.

Send a file as uuencoded data to minimize mallocs on large files. The
encode routine uses 80 char buffers, so this routine will malloc a
buffer that is a multiple of 80. The file will be sent to stdout.

@note Add spaces after file data to avoid short file warnings from uudecode.
@param buf data to encode.
@param length length of data
@param fn file name for uudecode.
@retval 0 Success.
@retval 1 Malloc failed.
@retval 2 File open failed.
*/
int uu_send_file( const char* fn )
{
	ee_FILE	*in_fp;
	char	*buf;
	int 	bufsize;

	if ((in_fp=th_fopen(fn,"rb"))==NULL)
		return 1;
	/* open file, return errors. */
	if ((buf=th_malloc(UU_FILE_BUFSIZ))==NULL)
		return 2;
	/* tell uudecode file mode (owner read/write), and file name. */ 
	th_printf ("begin 600 %s\n",fn);
	/* Encode blocks of data. use size 1 count bufsiz so we can get number
	of bytes. */
	while (!th_feof(in_fp))
		if ((bufsize=th_fread(buf, 1, UU_FILE_BUFSIZ, in_fp)))
			encode(buf,bufsize);
	/* tell uudecode the file is done. */
	th_printf ("   \nend\n\n");
	/* Release resources. */
	th_free(buf);
	th_fclose(in_fp);
	return 0; /* Success; */ 
}

/** @} */
