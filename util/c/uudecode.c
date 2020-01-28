/* uudecode utility.
   Copyright (C) 1994, 1995 Free Software Foundation, Inc.

   This product is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This product is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this product; see the file COPYING.  If not, write to
   the Free Software Foundation, 59 Temple Place - Suite 330, Boston, MA
   02111-1307, USA.  */

/* Copyright (c) 1983 Regents of the University of California.
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:
   1. Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
   2. Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
   3. All advertising materials mentioning features or use of this software
      must display the following acknowledgement:
	 This product includes software developed by the University of
	 California, Berkeley and its contributors.
   4. Neither the name of the University nor the names of its contributors
      may be used to endorse or promote products derived from this software
      without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
   OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
   OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
   SUCH DAMAGE.  */

/* Reworked to GNU style by Ian Lance Taylor, ian@airs.com, August 93.  */

#include "system.h"
#include <stdarg.h>

/*=====================================================================\
| uudecode [FILE ...]						       |
| 								       |
| Create the specified FILE, decoding as you go.  Used with uuencode.  |
\=====================================================================*/

#if HAVE_PWD_H && !defined(_MSC_VER)
#include <pwd.h>
struct passwd *getpwnam ();
#endif
#include "getopt.h"

static int Verbose=0;

static struct option longopts[] =
{
  { "version", no_argument, NULL, 'v' },
  { "help", no_argument, NULL, 'h' },
  { "output-file", required_argument, NULL, 'o' },
  { NULL, 0, NULL, 0 }
};

static int read_stduu __P ((const char *inname));
static int read_base64 __P ((const char *inname));
static int decode __P ((const char *, const char *));
static void usage __P ((int));

/* The name this program was run with. */
const char *program_name;

/* Single character decode.  */
#define	DEC(Char) (((Char) - ' ') & 077)

/** error routine for libintl removal */
void error(int err1, int err2, const char *format, ...)
{
	int rv;
	va_list args;
	va_start(args,format);
	rv = vprintf(format,args);
	va_end(args);
}

static int
read_stduu (inname)
     const char *inname;
{
  char buf[2 * BUFSIZ];
  int linenum = 0;
  int len;

  while (1)
    {
      int n;
      char *p;

      if (fgets (buf, sizeof(buf), stdin) == NULL)
	{
	  error (0, 0, _("%s: Short file"), inname);
	  return 1;
	}
      p = buf;
      linenum++;

      /* N is used to avoid writing out all the characters at the end of
	 the file.  */

	  if (!strcmp("end\n",buf)) break;

      n = DEC (*p);
	  len = strlen(buf);
	  if (len <= 4)
		  continue;
	  if (n <= 0) {
		  if (Verbose)
			  fprintf(stderr,"Error: (%d) Size less than zero. (%d)\n%s",linenum,len,buf);
		  else
			  fprintf(stderr,"Error: %s Invalid data\n",inname);
		continue;
	  }
	  if (n > 45) {
		  if (Verbose)
			  fprintf(stderr,"Warning: (%d) Size is larger than 45.\n%s",linenum,buf);
		  else
			  fprintf(stderr,"Warning: %s Suspicious data\n",inname);
	  }
	  else if (len > 62) {
		  if (Verbose)
			  fprintf(stderr,"Warning: (%d) Line is too long (%d)\n%s",linenum,len,buf);
		  else
			  fprintf(stderr,"Warning: %s Suspicious data\n",inname);
	  }
      else if ((n*4) > (3*(len-2))) {
		  if (Verbose)
			  fprintf(stderr,"Warning: (%d) N = %d, len = %d\n%s",linenum,n,len,buf);
		  else
			  fprintf(stderr,"Warning: %s Suspicious data\n",inname);
      }
	  else if (((((n+3)*3)/3)*4) < (3*(len-2))) {
		  if (Verbose)
			  fprintf(stderr,"Warning: (%d) len = %d, N = %d\n%s",linenum,len,n,buf);
		  else
			  fprintf(stderr,"Warning: %s Suspicious data\n",inname);
      }
	  else if ((len-2)%4 != 0) {
		  if (Verbose)
			  fprintf(stderr,"Warning: (%d) len = %d\n%s",linenum,len,buf);
		  else
			  fprintf(stderr,"Warning: %s Suspicious data\n",inname);
	  }
      for (++p; n > 0; p += 4, n -= 3)
	{
	  char ch;

	  if (n >= 3)
	    {
	      ch = DEC (p[0]) << 2 | DEC (p[1]) >> 4;
	      putchar (ch);
	      ch = DEC (p[1]) << 4 | DEC (p[2]) >> 2;
	      putchar (ch);
	      ch = DEC (p[2]) << 6 | DEC (p[3]);
	      putchar (ch);
	    }
	  else
	    {
	      if (n >= 1)
		{
		  ch = DEC (p[0]) << 2 | DEC (p[1]) >> 4;
		  putchar (ch);
		}
	      if (n >= 2)
		{
		  ch = DEC (p[1]) << 4 | DEC (p[2]) >> 2;
		  putchar (ch);
		}
	    }
	}
    }

  /*if (fgets (buf, sizeof(buf), stdin) == NULL
      || strcmp (buf, "end\n"))
    {
      error (0, 0, _("%s: No `end' line"), inname);
      return 1;
    } */

  if (Verbose)
    fprintf(stderr,"Decoding complete. %d lines\n\n",linenum);

  return 0;
}

static int
read_base64 (inname)
     const char *inname;
{
  static const char b64_tab[256] =
  {
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*000-007*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*010-017*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*020-027*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*030-037*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*040-047*/
    '\177', '\177', '\177', '\76',  '\177', '\177', '\177', '\77',  /*050-057*/
    '\64',  '\65',  '\66',  '\67',  '\70',  '\71',  '\72',  '\73',  /*060-067*/
    '\74',  '\75',  '\177', '\177', '\177', '\100', '\177', '\177', /*070-077*/
    '\177', '\0',   '\1',   '\2',   '\3',   '\4',   '\5',   '\6',   /*100-107*/
    '\7',   '\10',  '\11',  '\12',  '\13',  '\14',  '\15',  '\16',  /*110-117*/
    '\17',  '\20',  '\21',  '\22',  '\23',  '\24',  '\25',  '\26',  /*120-127*/
    '\27',  '\30',  '\31',  '\177', '\177', '\177', '\177', '\177', /*130-137*/
    '\177', '\32',  '\33',  '\34',  '\35',  '\36',  '\37',  '\40',  /*140-147*/
    '\41',  '\42',  '\43',  '\44',  '\45',  '\46',  '\47',  '\50',  /*150-157*/
    '\51',  '\52',  '\53',  '\54',  '\55',  '\56',  '\57',  '\60',  /*160-167*/
    '\61',  '\62',  '\63',  '\177', '\177', '\177', '\177', '\177', /*170-177*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*200-207*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*210-217*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*220-227*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*230-237*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*240-247*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*250-257*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*260-267*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*270-277*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*300-307*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*310-317*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*320-327*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*330-337*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*340-347*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*350-357*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*360-367*/
    '\177', '\177', '\177', '\177', '\177', '\177', '\177', '\177', /*370-377*/
  };
  unsigned char buf[2 * BUFSIZ];

  while (1)
    {
      int last_data = 0;
      unsigned char *p;

      if (fgets (buf, sizeof(buf), stdin) == NULL)
	{
	  error (0, 0, _("%s: Short file"), inname);
	  return 1;
	}
      p = buf;

      if (memcmp (buf, "====", 4) == 0)
	break;
      if (last_data != 0)
	{
	  error (0, 0, _("%s: data following `=' padding character"), inname);
	  return 1;
	}

      /* The following implementation of the base64 decoding might look
	 a bit clumsy but I only try to follow the POSIX standard:
	 ``All line breaks or other characters not found in the table
	   [with base64 characters] shall be ignored by decoding
	   software.''  */
      while (*p != '\n')
	{
	  char c1, c2, c3;

	  while ((b64_tab[*p] & '\100') != 0)
	    if (*p == '\n' || *p++ == '=')
	      break;
	  if (*p == '\n')
	    /* This leaves the loop.  */
	    continue;
	  c1 = b64_tab[*p++];

	  while ((b64_tab[*p] & '\100') != 0)
	    if (*p == '\n' || *p++ == '=')
	      {
		error (0, 0, _("%s: illegal line"), inname);
		return 1;
	      }
	  c2 = b64_tab[*p++];

	  while (b64_tab[*p] == '\177')
	    if (*p++ == '\n')
	      {
		error (0, 0, _("%s: illegal line"), inname);
		return 1;
	      }
	  if (*p == '=')
	    {
	      putchar (c1 << 2 | c2 >> 4);
	      last_data = 1;
	      break;
	    }
	  c3 = b64_tab[*p++];

	  while (b64_tab[*p] == '\177')
	    if (*p++ == '\n')
	      {
		error (0, 0, _("%s: illegal line"), inname);
		return 1;
	      }
	  putchar (c1 << 2 | c2 >> 4);
	  putchar (c2 << 4 | c3 >> 2);
	  if (*p == '=')
	    {
	      last_data = 1;
	      break;
	    }
	  else
	    putchar (c3 << 6 | b64_tab[*p++]);
	}
    }

  return 0;
}

/** UUdecode a file.
This has been enhanced to extract multiple files from a single file.
It may not work in all cases, but it will try. 
@note alloca is replaced with malloc/free of outname. Too many compiler
problems for a temporary variable. While outname[FILENAME_MAX] should work,
we will just assume someone had a reason for alloca, and make everything malloc.
*/
static int
decode (inname, forced_outname)
     const char *inname;
     const char *forced_outname;
{
  struct passwd *pw;
  register int n;
  register char *p;
  int mode, n1;
  char buf[2 * BUFSIZ];
  char *outname=NULL;
  int do_base64 = 0;
  /** @remarks If one begin was found, do not return error. */
  int onebegin = 0;
  char	*rvfgets = NULL;
  int rvread=0;

  /** Process multiple files within input. */
  while (!feof(stdin))
  {
  /* Search for header line.  */
  while (1)
    {
      if ((rvfgets=fgets (buf, sizeof (buf), stdin)) == NULL)
	{
		  /** If we have already processed files, return normally. */
		  if (!onebegin)
		  {
			  error (0, 0, _("%s: No `begin' line"), inname);
			  return 1;
		  }
		  else
			  break;
	}

      if (strncmp (buf, "begin", 5) == 0)
	{
	  if (sscanf (buf, "begin-base64 %o %s", &mode, buf) == 2)
	    {
	      do_base64 = 1;
	      break;
	    }
	  else if (sscanf (buf, "begin %o %s", &mode, buf) == 2)
	    break;
	}
    }

  /** If we have already processed files, return normally. */
  if (rvfgets)
	  onebegin++;
  else
	  break;

  /* If the output file name is given on the command line this rules.  */
  if (forced_outname != NULL)
  {
	  if (outname) free(outname);
	  outname = (char *) strdup(forced_outname);
  }
  else
    {
      /* Handle ~user/file format.  */

      if (buf[0] != '~')
	  {
		  if (outname) free(outname);
		  outname = strdup(buf);
		  if (Verbose) fprintf(stderr,"\nDecoding file %s\n",outname);
	  }
      else
	{
#if HAVE_PWD_H && !defined(_MSC_VER)
	  p = buf + 1;
	  while (*p != '/')
	    ++p;
	  if (*p == '\0')
	    {
		  if (outname) free(outname);
	      error (0, 0, _("%s: Illegal ~user"), inname);
	      return 1;
	    }
	  *p++ = '\0';
	  pw = getpwnam (buf + 1);
	  if (pw == NULL)
	    {
		  if (outname) free(outname);
	      error (0, 0, _("%s: No user `%s'"), inname, buf + 1);
	      return 1;
	    }
	  n = strlen (pw->pw_dir);
	  n1 = strlen (p);
	  if (outname) free(outname);
	  outname = (char *) /*alloca*/ malloc ((size_t) (n + n1 + 2));
	  memcpy (outname + n + 1, p, (size_t) (n1 + 1));
	  memcpy (outname, pw->pw_dir, (size_t) n);
	  outname[n] = '/';
#else
	  error(0,0, _("%s: ~user not supported"),inname);
	  return 1;
#endif
	}
    }

  /* Create output file and set mode.  */

  if (strcmp (outname, "/dev/stdout") != 0 && strcmp (outname, "-") != 0
      && (freopen (outname, "wb", stdout) == NULL
#if HAVE_FCHMOD
	  || fchmod (fileno (stdout), mode & (S_IRWXU | S_IRWXG | S_IRWXO))
#else
	  || chmod (outname, mode & (S_IRWXU | S_IRWXG | S_IRWXO))
#endif
	  ))
    {
      error (0, errno, "%s: %s", outname, inname);
      return 1;
    }

  /* We differenciate decoding standard UU encoding and base64.  A
     common function would only slow down the program.  */

  /** Do not return to allow multiple uuencoded files. */
  /* For each input line:  */
  if (do_base64)
    rvread = read_base64 (inname);
  else
    rvread = read_stduu (inname);
  if (rvread)
	  return rvread;
  }
  return rvread;
}

static void
usage (status)
     int status;
{
  if (status != 0)
    fprintf (stderr, _("Try `%s --help' for more information.\n"),
	     program_name);
  else
    {
      printf (_("Usage: %s [FILE]...\n"), program_name);
      printf (_("\
Mandatory arguments to long options are mandatory to short options too.\n\
  -h, --help               display this help and exit\n\
  -v, --version            output version information and exit\n\
  -o, --output-file=FILE   direct output to FILE\n"));
    }
  exit (status);
}

int
main (argc, argv)
     int argc;
     char *const *argv;
{
  int opt;
  int exit_status;
  const char *outname;

  program_name = argv[0];
  outname = NULL;
  /** Remove locale and i18n. */
#if 0
  setlocale (LC_ALL, "");

  /* Set the text message domain.  */
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);
#endif
  while (opt = getopt_long (argc, argv, "ho:vV", longopts, (int *) NULL),
	 opt != EOF)
    {
      switch (opt)
	{
	case 'h':
	  usage (EXIT_SUCCESS);

	case 'o':
	  outname = optarg;
	  break;

	case 'v':
	  printf ("%s - GNU %s %s\n", program_name, PACKAGE_NAME, PACKAGE_VERSION);
	  exit (EXIT_SUCCESS);

	case 0:
	  break;

	case 'V':
	  Verbose=1;
	  break;

	default:
	  usage (EXIT_FAILURE);
	}
    }

  if (optind == argc)
    exit_status = decode ("stdin", outname) == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
  else
    {
      exit_status = EXIT_SUCCESS;
      do
	{
	  if (freopen (argv[optind], "r", stdin) != NULL)
	    {
	      if (decode (argv[optind], outname) != 0)
		exit_status = EXIT_FAILURE;
	    }
	  else
	    {
	      error (0, errno, "%s", argv[optind]);
	      exit_status = EXIT_FAILURE;
	    }
	  optind++;
	}
      while (optind < argc);
    }

  exit (exit_status);
}
