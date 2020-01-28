/**
 * @file
 * @brief  vfscanf formatted input variables.
 *
 * $RCSfile: doscan.c,v $
 *
 *  EEMBC : TechTag
 *
 * @author  Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.4 $
 *          $Date: 2006/03/28 04:44:43 $
 *          $Author: Shay $
 *          $Source: /usr/local/cvs/eembc2/th_lite/src/doscan.c,v $
 *          
 * @note   
 *	This file is not 64b safe.
 *
 * HISTORY :
 *
 * $Log: doscan.c,v $
 * Revision 1.4  2006/03/28 04:44:43  Shay
 * enable VS8
 *
 * Revision 1.3  2006/03/09 17:34:18  rick
 * Version 2 Office Release Candidate 5
 *
 * Revision 1.24  2005/12/02 23:53:34  rick
 * Fix mixed EOL format causing ^M's to appear in Unix checkouts.
 *
 * Revision 1.23  2005/09/10 04:02:23  rick
 * eol update, add uu_send_file
 *
 * Revision 1.22  2005/04/27 20:33:13  rick
 * Copyrite update 2005
 *
 * Revision 1.21  2005/04/27 16:05:06  rick
 * Add HAVE_CTYPE_H, re-order headers in doscan.c, and correct type sign in fileio.c to remove warnings.
 *
 * Revision 1.16  2004/12/08 23:27:43  rick
 * New standard header for documentation generation.
 *
 * Revision 1.15  2004/08/09 20:22:37  rick
 * Add th_open, clear warnings from stdio/threent
 *
 * Revision 1.14  2004/08/09 18:29:49  rick
 * Porting enhancements for wchar_t, FILE typedefs, and missing stdio definitions.
 *
 * Revision 1.13  2004/06/23 05:55:23  rick
 * EE_REDIRECT, and Shared Files
 *
 * Revision 1.12  2004/05/20 18:43:52  rick
 * Add definition for missing or incomplete MB_CUR_MAX
 *
 * Revision 1.11  2004/04/01 22:38:46  rick
 * Add ee_exec_ls, add config flags for doscan, fix msvc dirent flags
 *
 * Revision 1.10  2004/03/15 21:29:05  rick
 * Add documentation tags, and cleanup comments
 *
 * Revision 1.9  2004/03/10 23:57:16  rick
 * fix dirent calls
 *
 * Revision 1.8  2004/03/10 00:18:00  rick
 * Add scanf family, vfprintf, and new doscan
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
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * For conditions of distribution and use, see the accompanying README file.
 *------------------------------------------------------------------------------
 * @endverbatim
 */

/** Get autoconf definitions. */
#include "thconfig.h"

#if 	HAVE_CTYPE_H
#include <ctype.h>
#endif

#include <stdio.h>

/** MB_CUR_MAX, strtoll, strtoull. */
#if 	HAVE_STDLIB_H
#include <stdlib.h>
#endif

/** CHAR_BIT usually 8 */
#if 	HAVE_LIMITS_H
#include <limits.h>
#endif
#if 	HAVE_STRING_H
#include <string.h>
#endif
#if		HAVE_STDARG_H
#include <stdarg.h>
#endif

/** th_getc */
#include "thlib.h"
/** Get ee_putc for runtime option. */
#include "fileio.h"

/** Some stdio.h do not define wchar_t. */
#if 	NEED_WCHAR_T
typedef unsigned short wchar_t;
#endif

/** @addtogroup SHFL
@{ */
/** @addtogroup doscan_c Functional Layer Scan Engine
@{ */

#if	!defined(MB_CUR_MAX) || defined(UNDER_CE)
/** Usually defined in libc locale/locale.h, and extern via stdlib.h. */
static int __mb_cur_max = 1;
/*extern __IMPORT int __mb_cur_max;*/

#define MB_CUR_MAX __mb_cur_max
#endif

/*#include "local.h"*/

/** Internal FLOATING_POINT define controlled by Harness FLOAT_SUPPORT. */
#if		FLOAT_SUPPORT
#define FLOATING_POINT
#endif

/** @remark Selected definitions for generic code generation */

#define BUF 40
#define _NO_LONGDBL 1
#define _NO_LONG_DOUBLE 1
#undef	MB_CAPABLE
#define __SINGLE_THREAD__ 1
#undef  __SCLE 
#undef	__USE_INTERNAL_STAT64

/** An upper bound for how long a long prints in decimal.  4 / 13 approximates
   log (2).  Add one char for roundoff compensation and one for the sign.  */
#define MAX_LONG_LEN ((CHAR_BIT * sizeof (long)  - 1) * 4 / 13 + 2)

/*
 * Flags used during conversion.
 */
/** l: long or double */
#define	LONG		0x01
/** L/ll: long double or long long */
#define	LONGDBL		0x02
/** h: short */
#define	SHORT		0x04
/** hh: 8 bit integer */
#define CHAR		0x08
/** suppress assignment */
#define	SUPPRESS	0x10
/** weird %p pointer (`fake hex') */
#define	POINTER		0x20
/** do not skip blanks */
#define	NOSKIP		0x40

/** @note
 * The following are used in numeric conversions only:
 * SIGNOK, NDIGITS, DPTOK, and EXPOK are for floating point;
 * SIGNOK, NDIGITS, PFXOK, and NZDIGITS are for integral.
 */

/** +/- is (still) legal */
#define	SIGNOK		0x80
/** no digits detected */
#define	NDIGITS		0x100

/** (float) decimal point is still legal */
#define	DPTOK		0x200
/** (float) exponent (e+3, etc) still legal */
#define	EXPOK		0x400

/** 0x prefix is (still) legal */
#define	PFXOK		0x200
/** no zero digits detected */
#define	NZDIGITS	0x400

/*
 * Conversion types.
 */

/** %c conversion */
#define	CT_CHAR		0
/** %[...] conversion */
#define	CT_CCL		1
/** %s conversion */
#define	CT_STRING	2
/** integer, i.e., strtol or strtoul */
#define	CT_INT		3
/** floating, i.e., strtod */
#define	CT_FLOAT	4

#define u_char char
#define u_long unsigned long

#if		HAVE_64
#undef	_NO_LONGLONG
#else
#define	_NO_LONGLONG
#endif


#ifndef _NO_LONGLONG
typedef e_u64	u_long_long;
#endif

static u_char *__sccl(register char *tab,register u_char *fmt);

/*
 * vfscanf
 */

/** Re-defined to reflect th_getc() calls */
#define BufferEmpty (fp_p == EOF)

/** from newlib/libc/stdio/mbtowc.c, !MB_CAPABLE code path. */
#if !defined(_MSC_VER) || (_MSC_VER<=8)
int mbtowc(wchar_t *pwc,const char *s,size_t n)
{
  /* !MB_CAPABLE */
  if (s == NULL)
    return 0;
  if (n == 0)
    return -1;
  if (pwc)
    *pwc = (wchar_t) *s;
  return (*s != '\0');
}
#endif

/** Set in fileio.c by create/destroy strfile. */
extern int ee_use_internal_fileio;
/** Redirector to force internal fileio on internal strfile. */
#define TH_GETC(x) (ee_use_internal_fileio ? ee_getc(x):th_getc(x))

/** from newlib/libc/stdio/vfscanf.c */
int  ee_svfscanf (register ee_FILE *fp,const char *fmt0,va_list ap)
/*     struct _reent *rptr, removed */
{
  register u_char *fmt = (u_char *) fmt0;
  register int c;		/* character from format, or conversion */
  register size_t width;	/* field width, or 0 */
  register char *p;		/* points into all kinds of strings */
  register int n;		/* handy integer */
  register int flags;		/* flags as defined above */
  register char *p0;		/* saves original value of p when necessary */
  int nassigned;		/* number of fields assigned */
  int nread;			/* number of characters consumed from fp */
  int base = 0;			/* base argument to strtol/strtoul */
  int nbytes = 1;               /* number of bytes read from fmt string */
  wchar_t wc;                   /* wchar to use to read format string */
  wchar_t *wcp;                 /* handy wide character pointer */
  size_t mbslen;                /* length of converted multibyte sequence */
  /*mbstate_t state;*/              /* value to keep track of multibyte state */

  u_long (*ccfn)(const char *, char **, int ) = 0;	/* conversion function (strtol/strtoul) */
  char ccltab[256];		/* character class table for %[...] */
  char buf[BUF];		/* buffer for numeric conversions */
  char *lptr;                   /* literal pointer */

  char *cp;
  short *sp;
  int *ip;
  float *flp;
#if 	!defined(_NO_LONG_DOUBLE) || !defined(_NO_LONG_DBL)
  /*_LONG_DOUBLE*/ long double *ldp;
#endif
  double *dp;
  long *lp;
#ifndef _NO_LONGLONG
  /*long long*/ e_u64 *llp;
#endif

  /* `basefix' is used to avoid `if' tests in the integer scanner */
  static /*_CONST*/ const short basefix[17] =
    {10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
/* remap direct FILE access with th_getc */
	int fp_p=TH_GETC(fp);
	unsigned int i;

  nassigned = 0;
  nread = 0;
  for (;;)
    {
#ifndef MB_CAPABLE
      wc = *fmt;
#else
      memset (&state, '\0', sizeof (state));
      nbytes = _mbtowc_r (rptr, &wc, fmt, MB_CUR_MAX, &state);
#endif
      fmt += nbytes;
      if (wc == 0)
	return nassigned;
      if (nbytes == 1 && isspace (wc))
	{
	  for (;;)
	    {
	      if (BufferEmpty || !isspace (fp_p))
		break;
	      nread++, fp_p=TH_GETC(fp) /*fp->_r--, fp->_p++*/;
	    }
	  continue;
	}
      if (wc != '%')
	goto literal;
      width = 0;
      flags = 0;

      /*
       * switch on the format.  continue if done; break once format
       * type is derived.
       */

    again:
      c = *fmt++;

      switch (c)
	{
	case '%':
	literal:
          lptr = fmt - nbytes;
          for (n = 0; n < nbytes; ++n)
            {
	      if (BufferEmpty)
	        goto input_failure;
	      if (fp_p != *lptr)
	        goto match_failure;
	      fp_p=TH_GETC(fp) /*fp->_r--, fp->_p++*/;
	      nread++;
              ++lptr;
            }
	  continue;

	case '*':
	  flags |= SUPPRESS;
	  goto again;
	case 'l':
	  if (*fmt == 'l')	/* Check for 'll' = long long (SUSv3) */
	    {
	      ++fmt;
	      flags |= LONGDBL;
	    }
	  else
	    flags |= LONG;
	  goto again;
	case 'L':
	  flags |= LONGDBL;
	  goto again;
	case 'h':
	  if (*fmt == 'h')	/* Check for 'hh' = char int (SUSv3) */
	    {
	      ++fmt;
	      flags |= CHAR;
	    }
	  else
	    flags |= SHORT;
	  goto again;

	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	  width = width * 10 + c - '0';
	  goto again;

	  /*
	   * Conversions. Those marked `compat' are for
	   * 4.[123]BSD compatibility.
	   *
	   * (According to ANSI, E and X formats are supposed to
	   * the same as e and x.  Sorry about that.)
	   */

	case 'D':		/* compat */
	  flags |= LONG;
	  /* FALLTHROUGH */
	case 'd':
	  c = CT_INT;
	  ccfn = (u_long (*)(const char *,char**,int))strtol;
	  base = 10;
	  break;

	case 'i':
	  c = CT_INT;
	  ccfn = (u_long (*)(const char *,char**,int))strtol;
	  base = 0;
	  break;

	case 'O':		/* compat */
	  flags |= LONG;
	  /* FALLTHROUGH */
	case 'o':
	  c = CT_INT;
	  ccfn = (u_long (*)(const char *,char**,int))strtoul;
	  base = 8;
	  break;

	case 'u':
	  c = CT_INT;
	  ccfn = (u_long (*)(const char *,char**,int))strtoul;
	  base = 10;
	  break;

	case 'X':		/* compat   XXX */
	case 'x':
	  flags |= PFXOK;	/* enable 0x prefixing */
	  c = CT_INT;
	  ccfn = (u_long (*)(const char *,char**,int))strtoul;
	  base = 16;
	  break;

#ifdef FLOATING_POINT
	case 'E':		/* compat   XXX */
	case 'G':		/* compat   XXX */
/* ANSI says that E,G and X behave the same way as e,g,x */
	  /* FALLTHROUGH */
	case 'e':
	case 'f':
	case 'g':
	  c = CT_FLOAT;
	  break;
#endif
        case 'S':
          flags |= LONG;
          /* FALLTHROUGH */

	case 's':
	  c = CT_STRING;
	  break;

	case '[':
	  fmt = __sccl (ccltab, fmt);
	  flags |= NOSKIP;
	  c = CT_CCL;
	  break;

        case 'C':
          flags |= LONG;
          /* FALLTHROUGH */

	case 'c':
	  flags |= NOSKIP;
	  c = CT_CHAR;
	  break;

	case 'p':		/* pointer format is like hex */
	  flags |= POINTER | PFXOK;
	  c = CT_INT;
	  ccfn = (u_long (*)(const char *,char**,int))strtoul;
	  base = 16;
	  break;

	case 'n':
	  if (flags & SUPPRESS)	/* ??? */
	    continue;
	  if (flags & CHAR)
	    {
	      cp = va_arg (ap, char *);
	      *cp = (char)nread;
	    }
	  else if (flags & SHORT)
	    {
	      sp = va_arg (ap, short *);
	      *sp = (short)nread;
	    }
	  else if (flags & LONG)
	    {
	      lp = va_arg (ap, long *);
	      *lp = (long)nread;
	    }
#ifndef _NO_LONGLONG
	  else if (flags & LONGDBL)
	    {
	      llp = va_arg (ap, /*long long*/ e_u64 *);
	      *llp = nread;
	    }
#endif
	  else
	    {
	      ip = va_arg (ap, int *);
	      *ip = nread;
	    }
	  continue;

	  /*
	   * Disgusting backwards compatibility hacks.	XXX
	   */
	case '\0':		/* compat */
	  return EOF;

	default:		/* compat */
	  if (isupper (c))
	    flags |= LONG;
	  c = CT_INT;
	  ccfn = (u_long (*)(const char *,char**,int))strtol;
	  base = 10;
	  break;
	}

      /*
       * We have a conversion that requires input.
       */
      if (BufferEmpty)
	goto input_failure;

      /*
       * Consume leading white space, except for formats that
       * suppress this.
       */
      if ((flags & NOSKIP) == 0)
	{
	  while (isspace (fp_p))
	    {
	      nread++;
	      fp_p=TH_GETC(fp);
#if 0
	      if (--fp->_r > 0)
		fp->_p++;
	      else
	      if (__srefill (fp))
#else
          if (BufferEmpty)
#endif

		goto input_failure;
	    }
	  /*
	   * Note that there is at least one character in the
	   * buffer, so conversions that do not set NOSKIP ca
	   * no longer result in an input failure.
	   */
	}

      /*
       * Do the conversion.
       */
      switch (c)
	{

	case CT_CHAR:
	  /* scan arbitrary characters (sets NOSKIP) */
	  if (width == 0)
	    width = 1;
          if (flags & LONG) 
            {
              if ((flags & SUPPRESS) == 0)
                wcp = va_arg(ap, wchar_t *);
              else
                wcp = NULL;
              n = 0;
              while (width != 0) 
                {
                  if (n == MB_CUR_MAX)
                    goto input_failure;
				  fp_p = TH_GETC(fp);
                  buf[n++] = (char)fp_p;
#if 0
                  fp->_r -= 1;
                  fp->_p += 1;
                  memset((void *)&state, '\0', sizeof(mbstate_t));
#endif
                  if ((mbslen = mbtowc(/*rptr,*/ wcp, buf, n)) 
                                                         == (size_t)-1)
                    goto input_failure; /* Invalid sequence */
                  if (mbslen == 0 && !(flags & SUPPRESS))
                    *wcp = L'\0';
                  if (mbslen != (size_t)-2) /* Incomplete sequence */
                    {
                      nread += n;
                      width -= 1;
                      if (!(flags & SUPPRESS))
                        wcp += 1;
                      n = 0;
                    }
                  if (BufferEmpty) 
	                {
                      if (n != 0) 
                        goto input_failure;
                      break;
                    }
                }
              if (!(flags & SUPPRESS))
                nassigned++;
            } 
          else if (flags & SUPPRESS) 
	        {
	      size_t sum = 0;
	      for (;;)
		  {
#if 0
		  if ((n = fp->_r) < (int)width)
		    {
		      sum += n;
		      width -= n;
		      fp->_p += n;
		      if (__srefill (fp))
			  {
			  if (sum == 0)
			    goto input_failure;
			  break;
			  }
		    }
		  else
#endif
		    {
		      for (i=0;i<width;i++)
		      	fp_p=TH_GETC(fp);
		      sum += width;
#if 0
		      fp->_r -= width;
		      fp->_p += width;
#endif
		      break;
		    }
		}
	      nread += sum;
	    }
	  else
	    {
	      size_t r = th_fread ((/*_PTR*/ void *) va_arg (ap, char *), 1, width, fp);

	      if (r == 0)
		goto input_failure;
	      nread += r;
	      nassigned++;
	    }
	  break;

	case CT_CCL:
	  /* scan a (nonempty) character class (sets NOSKIP) */
	  if (width == 0)
	    width = (unsigned int)~0;		/* `infinity' */
	  /* take only those things in the class */
	  if (flags & SUPPRESS)
	  {
		  n = 0;
		  while (ccltab[fp_p])
		  {
			  n++;fp_p=TH_GETC(fp); /*, fp->_r--, fp->_p++*/
			  if (--width == 0)
				  break;
			  if (BufferEmpty)
			  {
				  if (n == 0)
					  goto input_failure;
				  break;
			  }
		  }
		  if (n == 0)
			  goto match_failure;
	  }
	  else
	  {
	      p0 = p = va_arg (ap, char *);
	      while (ccltab[fp_p])
		  {
			/*fp->_r--;*/
			fp_p = TH_GETC(fp); /* *fp->_p++*/
			*p++ = (char) fp_p;
			if (--width == 0)
				break;
			if (BufferEmpty)
			{
				if (p == p0)
					goto input_failure;
				break;
			}
	  }
		  n = p - p0;
		  if (n == 0)
			  goto match_failure;
	      *p = 0;
	      nassigned++;
	    }
	  nread += n;
	  break;

	case CT_STRING:
	  /* like CCL, but zero-length string OK, & no NOSKIP */
	  if (width == 0)
            width = (size_t)~0;		/* `infinity' */
          if (flags & LONG) 
            {
              /* Process %S and %ls placeholders */
              if ((flags & SUPPRESS) == 0)
                wcp = va_arg(ap, wchar_t *);
              else
                wcp = &wc;
              n = 0;
              while (!isspace(fp_p) && width != 0) 
                {
                  if (n == MB_CUR_MAX)
                    goto input_failure;
                  buf[n++] = (char)fp_p;
                  fp_p=TH_GETC(fp);
#if 0
                  fp->_r -= 1;
                  fp->_p += 1;
                  memset((void *)&state, '\0', sizeof(mbstate_t));
#endif
                  if ((mbslen = mbtowc(/*rptr,*/ wcp, buf, n)) 
                                                        == (size_t)-1)
                    goto input_failure;
                  if (mbslen == 0)
                    *wcp = L'\0';
                  if (mbslen != (size_t)-2) /* Incomplete sequence */
                    {
#ifdef MB_CAPABLE
                      if (iswspace(*wcp)) 
                        {
                          while (n != 0)
                            th_ungetc(buf[--n], fp);
                          break;
                        }
#endif
                      nread += n;
                      width -= 1;
                      if ((flags & SUPPRESS) == 0)
                        wcp += 1;
                      n = 0;
                    }
                  if (BufferEmpty) 
                    {
                      if (n != 0)
                        goto input_failure;
                      break;
                    }
                }
              if (!(flags & SUPPRESS)) 
                {
                  *wcp = L'\0';
                  nassigned++;
                }
            }
          else if (flags & SUPPRESS) 
	    {
	      n = 0;
	      while (!isspace (fp_p))
		{
		  n++;
		  fp_p=TH_GETC(fp) /*fp->_r--, fp->_p++*/;
		  if (--width == 0)
		    break;
		  if (BufferEmpty)
		    break;
		}
	      nread += n;
	    }
	  else
	    {
	      p0 = p = va_arg (ap, char *);
	      while (!isspace (fp_p))
		{
		  /*fp->_r--;*/
		  *p++ = (char)fp_p;
		  fp_p = TH_GETC(fp); /**fp->_p++;*/
		  if (--width == 0)
		    break;
		  if (BufferEmpty)
		    break;
		}
	      *p = 0;
	      nread += p - p0;
	      nassigned++;
	    }
	  continue;

	case CT_INT:
	  /* scan an integer as if by strtol/strtoul */
#ifdef hardway
	  if (width == 0 || width > sizeof (buf) - 1)
	    width = sizeof (buf) - 1;
#else
	  /* size_t is unsigned, hence this optimisation */
	  if (--width > sizeof (buf) - 2)
	    width = sizeof (buf) - 2;
	  width++;
#endif
	  flags |= SIGNOK | NDIGITS | NZDIGITS;
	  for (p = buf; width; width--)
	    {
	      c = fp_p;
	      /*
	       * Switch on the character; `goto ok' if we
	       * accept it as a part of number.
	       */
	      switch (c)
		{
		  /*
		   * The digit 0 is always legal, but is special.
		   * For %i conversions, if no digits (zero or nonzero)
		   * have been scanned (only signs), we will have base==0.
		   * In that case, we should set it to 8 and enable 0x
		   * prefixing. Also, if we have not scanned zero digits
		   * before this, do not turn off prefixing (someone else
		   * will turn it off if we have scanned any nonzero digits).
		   */
		case '0':
		  if (base == 0)
		    {
		      base = 8;
		      flags |= PFXOK;
		    }
		  if (flags & NZDIGITS)
		    flags &= ~(SIGNOK | NZDIGITS | NDIGITS);
		  else
		    flags &= ~(SIGNOK | PFXOK | NDIGITS);
		  goto ok;

		  /* 1 through 7 always legal */
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		  base = basefix[base];
		  flags &= ~(SIGNOK | PFXOK | NDIGITS);
		  goto ok;

		  /* digits 8 and 9 ok iff decimal or hex */
		case '8':
		case '9':
		  base = basefix[base];
		  if (base <= 8)
		    break;	/* not legal here */
		  flags &= ~(SIGNOK | PFXOK | NDIGITS);
		  goto ok;

		  /* letters ok iff hex */
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		  /* no need to fix base here */
		  if (base <= 10)
		    break;	/* not legal here */
		  flags &= ~(SIGNOK | PFXOK | NDIGITS);
		  goto ok;

		  /* sign ok only as first character */
		case '+':
		case '-':
		  if (flags & SIGNOK)
		    {
		      flags &= ~SIGNOK;
		      goto ok;
		    }
		  break;

		  /* x ok iff flag still set & 2nd char */
		case 'x':
		case 'X':
		  if (flags & PFXOK && p == buf + 1)
		    {
		      base = 16;/* if %i */
		      flags &= ~PFXOK;
		      goto ok;
		    }
		  break;
		}

	      /*
	       * If we got here, c is not a legal character
	       * for a number.  Stop accumulating digits.
	       */
	      break;
	    ok:
	      /*
	       * c is legal: store it and look at the next.
	       */
	      *p++ = (char)c;
#if 0
	      if (--fp->_r > 0)
		fp->_p++;
	      else
	      if (__srefill (fp))
#else
		  fp_p=TH_GETC(fp);
		  if (BufferEmpty)
#endif
		break;		/* EOF */
	    }
	  /*
	   * If we had only a sign, it is no good; push back the sign.
	   * If the number ends in `x', it was [sign] '0' 'x', so push back
	   * the x and treat it as [sign] '0'.
	   */
	  if (flags & NDIGITS)
	    {
	      if (p > buf)
		/*_CAST_VOID*/ (void) th_ungetc (*(u_char *)-- p, fp);
	      goto match_failure;
	    }
	  c = ((u_char *) p)[-1];
	  if (c == 'x' || c == 'X')
	    {
	      --p;
	      /*(void)*/ th_ungetc (c, fp);
	    }
	  if ((flags & SUPPRESS) == 0)
	    {
	      u_long res;

	      *p = 0;
	      res = (*ccfn) (/*rptr,*/ buf, (char **) NULL, base);
	      if (flags & POINTER)
		*(va_arg (ap, /*_PTR*/ void * *)) = (/*_PTR*/ void *) (unsigned /*_POINTER_INT*/ int *) res;
	      else if (flags & CHAR)
		{
		  cp = va_arg (ap, char *);
		  *cp = (char) res;
		}
	      else if (flags & SHORT)
		{
		  sp = va_arg (ap, short *);
		  *sp = (short) res;
		}
	      else if (flags & LONG)
		{
		  lp = va_arg (ap, long *);
		  *lp = res;
		}
#ifndef _NO_LONGLONG
	      else if (flags & LONGDBL)
		{
		  u_long_long resll;
#if		HAVE_STRTOLL
		  if (ccfn == strtoul)
		    resll = strtoull (/*rptr,*/ buf, (char **) NULL, base);
		  else
		    resll = strtoll (/*rptr,*/ buf, (char **) NULL, base);
#else
		  if (ccfn == (u_long (*)(const char *,char**,int))strtoul)
		    resll = strtoul (/*rptr,*/ buf, (char **) NULL, base);
		  else
		    resll = strtol (/*rptr,*/ buf, (char **) NULL, base);
#endif
		  llp = va_arg (ap, /*long long*/ e_u64 *);
		  *llp = (long) resll;
		}
#endif
	      else
		{
		  ip = va_arg (ap, int *);
		  *ip = res;
		}
	      nassigned++;
	    }
	  nread += p - buf;
	  break;

#ifdef FLOATING_POINT
	case CT_FLOAT:
	{
	  /* scan a floating point number as if by strtod */
	  /* This code used to assume that the number of digits is reasonable.
	     However, ANSI / ISO C makes no such stipulation; we have to get
	     exact results even when there is an unreasonable amount of
	     leading zeroes.  */
	  long leading_zeroes = 0;
	  long zeroes, exp_adjust;
	  char *exp_start = NULL;
#ifdef hardway
	  if (width == 0 || width > sizeof (buf) - 1)
	    width = sizeof (buf) - 1;
#else
	  /* size_t is unsigned, hence this optimisation */
	  if (--width > sizeof (buf) - 2)
	    width = sizeof (buf) - 2;
	  width++;
#endif
	  flags |= SIGNOK | NDIGITS | DPTOK | EXPOK;
	  zeroes = 0;
	  exp_adjust = 0;
	  for (p = buf; width; )
	    {
	      c = fp_p;
	      /*
	       * This code mimicks the integer conversion
	       * code, but is much simpler.
	       */
	      switch (c)
		{

		case '0':
		  if (flags & NDIGITS)
		    {
		      flags &= ~SIGNOK;
		      zeroes++;
		      goto fskip;
		    }
		  /* Fall through.  */
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		  flags &= ~(SIGNOK | NDIGITS);
		  goto fok;

		case '+':
		case '-':
		  if (flags & SIGNOK)
		    {
		      flags &= ~SIGNOK;
		      goto fok;
		    }
		  break;
		case '.':
		  if (flags & DPTOK)
		    {
		      flags &= ~(SIGNOK | DPTOK);
		      leading_zeroes = zeroes;
		      goto fok;
		    }
		  break;
		case 'e':
		case 'E':
		  /* no exponent without some digits */
		  if ((flags & (NDIGITS | EXPOK)) == EXPOK
		      || ((flags & EXPOK) && zeroes))
		    {
		      if (! (flags & DPTOK))
			{
			  exp_adjust = zeroes - leading_zeroes;
			  exp_start = p;
			}
		      flags =
			(flags & ~(EXPOK | DPTOK)) |
			SIGNOK | NDIGITS;
		      zeroes = 0;
		      goto fok;
		    }
		  break;
		}
	      break;
	    fok:
	      *p++ = (char)c;
	    fskip:
	      width--;
              ++nread;
#if 0
	      if (--fp->_r > 0)
		fp->_p++;
	      else
	      if (__srefill (fp))
#else
		fp_p = TH_GETC(fp);
		if (BufferEmpty)
#endif
		break;		/* EOF */
	    }
	  if (zeroes)
	    flags &= ~NDIGITS;
	  /*
	   * If no digits, might be missing exponent digits
	   * (just give back the exponent) or might be missing
	   * regular digits, but had sign and/or decimal point.
	   */
	  if (flags & NDIGITS)
	    {
	      if (flags & EXPOK)
		{
		  /* no digits at all */
		  while (p > buf)
                    {
		      th_ungetc (*(u_char *)-- p, fp);
                      --nread;
                    }
		  goto match_failure;
		}
	      /* just a bad exponent (e and maybe sign) */
	      c = *(u_char *)-- p;
              --nread;
	      if (c != 'e' && c != 'E')
		{
		  /*_CAST_VOID*/ (void) th_ungetc (c, fp);	/* sign */
		  c = *(u_char *)-- p;
                  --nread;
		}
	      /*_CAST_VOID*/ (void) th_ungetc (c, fp);
	    }
	  if ((flags & SUPPRESS) == 0)
	    {
	      double res = 0;
#ifdef _NO_LONGDBL
#define QUAD_RES res;
#else  /* !_NO_LONG_DBL */
	      long double qres = 0;
#define QUAD_RES qres;
#endif /* !_NO_LONG_DBL */
	      long new_exp = 0;

	      *p = 0;
	      if ((flags & (DPTOK | EXPOK)) == EXPOK)
		{
		  exp_adjust = zeroes - leading_zeroes;
		  new_exp = -exp_adjust;
		  exp_start = p;
		}
	      else if (exp_adjust)
                new_exp = strtol (/*rptr,*/ (exp_start + 1), NULL, 10) - exp_adjust;
	      if (exp_adjust)
		{

		  /* If there might not be enough space for the new exponent,
		     truncate some trailing digits to make room.  */
		  if (exp_start >= buf + sizeof (buf) - MAX_LONG_LEN)
		    exp_start = buf + sizeof (buf) - MAX_LONG_LEN - 1;
                 sprintf (exp_start, "e%ld", new_exp);
		}

	      /* Current _strtold routine is markedly slower than 
	         _strtod_r.  Only use it if we have a long double
	         result.  */
#ifndef _NO_LONGDBL /* !_NO_LONGDBL */
	      if (flags & LONGDBL)
	      	qres = strtold (buf, NULL);
	      else
#endif
/** @todo Convert CT_FLOAT section to a dummy strtod if needed by bmarks. */
#if 	HAVE_STRTOD
	        res = strtod (/*rptr,*/ buf, NULL);
#else
			th_exit("%s : %s Failure: Need to implement strtod for this benchmark.\n",
				__FILE__,__LINE__);
#endif

	      if (flags & LONG)
		{
		  dp = va_arg (ap, double *);
		  *dp = res;
		}
#ifndef _NO_LONG_DBL
	      else if (flags & LONGDBL)
		{
		  ldp = va_arg (ap, /*_LONG_DOUBLE*/ long double  *);
		  *ldp = QUAD_RES;
		}
#endif
	      else
		{
		  flp = va_arg (ap, float *);
		  *flp = (float)res;
		}
	      nassigned++;
	    }
	  break;
	}
#endif /* FLOATING_POINT */
	}
    }
input_failure:
  return nassigned ? nassigned : -1;
match_failure:
  return nassigned;
}

/**
 * Fill in the given table from the scanset at the given format
 * (just after `[').  Return a pointer to the character past the
 * closing `]'.  The table has a 1 wherever characters should be
 * considered part of the scanset.
 */
static u_char *__sccl(register char *tab,register u_char *fmt)
{
  register int c, n, v;

  /* first `clear' the whole table */
  c = *fmt++;			/* first char hat => negated scanset */
  if (c == '^')
    {
      v = 1;			/* default => accept */
      c = *fmt++;		/* get new first char */
    }
  else
    v = 0;			/* default => reject */
  /* should probably use memset here */
  for (n = 0; n < 256; n++)
    tab[n] = (char)v;
  if (c == 0)
    return fmt - 1;		/* format ended before closing ] */

  /*
   * Now set the entries corresponding to the actual scanset to the
   * opposite of the above.
   *
   * The first character may be ']' (or '-') without being special; the
   * last character may be '-'.
   */

  v = 1 - v;
  for (;;)
    {
      tab[c] = (char)v;		/* take character c */
    doswitch:
      n = *fmt++;		/* and examine the next */
      switch (n)
	{

	case 0:		/* format ended too soon */
	  return fmt - 1;

	case '-':
	  /*
	   * A scanset of the form [01+-] is defined as `the digit 0, the
	   * digit 1, the character +, the character -', but the effect of a
	   * scanset such as [a-zA-Z0-9] is implementation defined.  The V7
	   * Unix scanf treats `a-z' as `the letters a through z', but treats
	   * `a-a' as `the letter a, the character -, and the letter a'.
	   *
	   * For compatibility, the `-' is not considerd to define a range if
	   * the character following it is either a close bracket (required by
	   * ANSI) or is not numerically greater than the character we just
	   * stored in the table (c).
	   */
	  n = *fmt;
	  if (n == ']' || n < c)
	    {
	      c = '-';
	      break;		/* resume the for(;;) */
	    }
	  fmt++;
	  do
	    {			/* fill in the range */
	      tab[++c] = (char)v;
	    }
	  while (c < n);
#if 1			/* XXX another disgusting compatibility hack */
	  /*
	   * Alas, the V7 Unix scanf also treats formats such
	   * as [a-c-e] as `the letters a through e'. This too
	   * is permitted by the standard....
	   */
	  goto doswitch;
#else
	  c = *fmt++;
	  if (c == 0)
	    return fmt - 1;
	  if (c == ']')
	    return fmt;
	  break;
#endif

	case ']':		/* end of scanset */
	  return fmt;

	default:		/* just another character */
	  c = n;
	  break;
	}
    }
  /* NOTREACHED */
}
/** @} */
/** @} */
