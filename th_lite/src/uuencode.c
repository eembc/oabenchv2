/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
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
