/*==============================================================================
 *$RCSfile: algo.c,v $
 *
 *   DESC : Test Harness benchmark routines
 *
 *  EEMBC : Office Automation
 *
 * AUTHOR : Rick Foos, ECL, LLC
 *
 *    CVS : $Revision: 1.4 $
 *          $Date: 2005/04/27 20:38:03 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/oav2/gs8/algo.c,v $
 *          
 * NOTE   :
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: algo.c,v $
 * Revision 1.4  2005/04/27 20:38:03  rick
 * Copyrite update 2005
 *
 * Revision 1.3  2004/11/10 23:19:12  rick
 * Add automated output generation
 *
 * Revision 1.2  2004/07/03 03:29:47  rick
 * Add thtime.h, and link/time harness interfaces.
 *
 * Revision 1.1  2004/07/02 17:56:11  rick
 * Add utilities for CRC, UUENCODE, and Ghostscript command line processing.
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

#include "algo.h"
#include "thtypes.h"

/** Check for option on command line. If requested, clear option.
@note Caller should free non-null returns to avoid valgrind errors.
@param argc Number of options in argv.
@param argv Array of command line options.
@param option Option to scan for.
@param remove 0 do not remove, ~0 remove option.
@retval Value of found option (malloc'ed), or NULL.
*/
char *getOption(int *argc,char *argv[],const char *option,int remove)
{
	int		i;
	size_t 	len;
	char	*buf=NULL;

	if (!option || !*option)
		return NULL;

	/*
	 * Allow caller to determine 
	 * if there is a value and what to do with it
	 * i.e. option=xxx
	 */
	len=strlen(option);
	/* Look for option, if found set variable and remove from argv */
	for (i=1;i<*argc;i++)
	{
		if ((strncmp(argv[i],option,len)) == 0)
		{
			buf=th_strdup(argv[i]);
			/** single arg remover. */
			if (remove)
			{
				int	j;
				/* We know that this is previously malloced. */
				th_free(argv[i]);
				/* Reduce number of arguments. */
				*argc=*argc-1;
				/* Slide remaining arguments back one. */
				for (j=i; j<*argc; j++)
					argv[j]=argv[j+1];

			}
			break;
		}
	}

	return buf;
}

/** Set do_uuencode option based on compiler default, and user arguments. */
int setDouuencode(int *argc,char *argv[])
{
	int		do_uuencode;
	const char *option="-do_uuencode";
	char	*buf;

	/** Set initial value based on thcfg. */
#if		defined(DO_UUENCODE)
	do_uuencode=1;
#else
	do_uuencode=0;
#endif
	/* Check for option, if found remove */
	if ((buf=getOption(argc,argv,option,1))!=NULL)
		do_uuencode=1;
	if (buf) th_free(buf);
	return do_uuencode;
}
static int numscan(char *p)
{
	unsigned char digit;
	int num=0,d;
	while (digit=*p++) {
		d=digit-'0';
		if (d>9 || d<0)
			break;
		num*=10;
		num+=d;
	}
	return num;
}

/** Set uid based on user arguments. */
int setUID(int *argc,char *argv[])
{
	int		uid=-1;
	const char *option="-uid";
	char	*buf,*pscanner;

	/* Check for option, if found remove */
	if ((buf=getOption(argc,argv,option,1))!=NULL)
	{
		if ((pscanner=strchr(buf,'='))!=NULL) {
			pscanner++;
			uid=numscan(pscanner);
		}
		th_free(buf);
	}
	return uid;
}

/** Set Ghostscript output file name based on default, and user option. */
char *setOutname(int *argc,char *argv[])
{
	char *outname;
	char *buf=NULL;
	const char *defaultname="ghostscript.out";
	const char *option="-sOutputFile";

	/* Check for option, do not remove */
	if ((outname=getOption(argc,argv,option,0))!=NULL)
	{
		if ((buf=strchr(outname,'='))==NULL)
			buf=th_strdup(defaultname);
		else
			buf=th_strdup(++buf);
		th_free(outname);
	}
	return buf;
}

/** Set Ghostscript device name, and user option. */
char *setDevice(int *argc,char *argv[])
{
	char *outname;
	char *buf=NULL;
	const char *option="-sDEVICE";

	/* Check for option, do not remove */
	if ((outname=getOption(argc,argv,option,0))!=NULL)
	{
		if ((buf=strchr(outname,'='))!=NULL)
			buf=th_strdup(++buf);
		th_free(outname);
	}
	return buf;
}

/** Set example postscript file. */
char *setExample(int argc,const char *argv[])
{
	/* get last argument assumption. */
	char *buf=(char *)argv[argc-1];
	if (*buf)
		buf=efn(argv[argc-1]);
	else
		buf=NULL;
	return buf;
}

/** Set example postscript file. */
char *setDevParams(int argc,const char *argv[])
{
	char *outname;
	char res[256]="";
	char *options[]={"-r","-dGrayValues=",NULL};
	char *option;
	int i=0,cur=0;

	while ((option=options[i])!=NULL) {
	/* Check for option, do not remove */
		if ((outname=getOption(&argc,argv,option,0))!=NULL)
		{
			int j=0;
			while (option[j]) j++; /* go to end of option */
			res[cur++]=':';
			while (outname[j]) res[cur++]=outname[j++];
			th_free(outname);
		}
		i++;
	}
	res[cur]=0;
	return th_strdup(res);
}
/** Get expected CRC based on device driver and example postscript file.
@todo If we use CRC, build an e_u16 associative array of [example][device]
containing CRC values.
@param device Ghostscript device driver
@param example Ghostscript example file name.
@retval Expected CRC, invalid arguments return 0.
*/
e_u16 getExpectedcrc(char *device,char *example)
{
	e_u16 expected_crc=0;
	if (!device || !*device || !example || !*example)
		return 0;
	return expected_crc;
}

/** Create fresh argv array. */
char **loadMyargv(int *argc,const char *argv[])
{
	int i,j,myargc=*argc;
	char **myargv;
	char *p;
	int n;
	int add=0;

	if ((myargc==0) || (argv==NULL))
		return NULL;
	/* scan for arguments that need duplication */
	for (i=0;i<*argc;i++) {
		p=strchr(argv[i],':');
		if (p != NULL) {
			n=numscan(++p);
			if (n>0) /* only arguments of the type <X>:<N> will be duplicated */
				myargc+=n-1;
		}
	}
	myargv=th_malloc(myargc*sizeof(*myargv));
	for (i=0;i<*argc;i++) {
		p=strchr(argv[i],':');
		if (p == NULL) {
			myargv[i+add]=th_strdup(argv[i]);
		} else {
			n=numscan(++p);
			if (n==0)
				myargv[i+add]=th_strdup(argv[i]);
			else {
				*--p=0;
				for (j=0; j<n; j++) {
					myargv[i+add]=th_strdup(argv[i]);
					add++;
				}
			}
		}
	}
	*argc=myargc;
	return myargv;
}

/** Free argv array. */
void freeMyargv(int argc,char *myargv[])
{
	int i;

	if (!argc || !myargv)
		return;
	for (i=0;i<argc;i++)
		th_free(myargv[i]);
	th_free(myargv);
}
