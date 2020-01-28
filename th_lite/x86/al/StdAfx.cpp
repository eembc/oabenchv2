/**
 * @file
 * @brief WinCE wrapper for console applications.
 *
 * $RCSfile: StdAfx.cpp,v $
 *
 * @author  Rick Foos, ECL, LLC
 *
 *  EEMBC : Technical Advisory Group (TechTAG)
 *
 *    CVS : $Revision: 1.1 $
 *          $Date: 2006/03/09 17:34:19 $
 *          $Author: rick $
 *          $Source: /usr/local/cvs/eembc2/th_lite/x86/al/StdAfx.cpp,v $
 *          
 * @note   
 *
 *
 * HISTORY :
 *
 * $Log: StdAfx.cpp,v $
 * Revision 1.1  2006/03/09 17:34:19  rick
 * Version 2 Office Release Candidate 5
 *
 * Revision 1.8  2005/07/16 03:08:31  rick
 * Merge updates for DSP environments
 *
 * Revision 1.7  2005/04/27 20:33:16  rick
 * Copyrite update 2005
 *
 * Revision 1.6  2004/12/08 23:27:25  rick
 * New standard header for documentation generation.
 *
 * Revision 1.2  2004/06/29 19:36:26  rick
 * EE_REDIRECT, and Shared file for Regular and Lite
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

#include "StdAfx.h"

/** @addtogroup SHAL
@{ */
/** @addtogroup stdafx_cpp Wrapper for C program under WinCE console.
@{ */

/** The C program to invoke. */
extern "C" {
int	main(int argc,char *argv[]);
/** clock CRT routine, defined but missing from WinCE libc. */
clock_t __cdecl clock(void)
{
	return GetTickCount();
}
}

/** Arbitrary number of arguments. You could pre-calculate the number of strtok hits. */
#define MAX_ARGC	256

/** Wrapper for STDC Program. */
int WINAPI WinMain(	HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPTSTR    lpCmdLine,
					int       nCmdShow)
{
	int	argc=0;
	char *argv[MAX_ARGC];
	/** @note lpCmdLine input is Unicode, argv is char. */
	int 	wlen=wcslen((const wchar_t *)lpCmdLine);
	char	*buf=(char *)malloc(wlen+1);
	int		len=wcstombs(buf,lpCmdLine,wlen);
	char	*freebuf=buf;

	/* If wlen != len we should do something, or let the C program deal with it. */

	/* Practically perfect, enhance strtok delimiters later. for quoted strings */
	argv[0]=_strdup("Program");
	for (buf=strtok(freebuf," "),argc=1;
		buf && argc < MAX_ARGC;
		buf=strtok(NULL," "),argc++)
		argv[argc]=_strdup(buf);
	free(freebuf);
	/** @todo Wait for window close option. To do this we need to know
	whether the cmd window was launched by us, or whether we were invoked from
	the command line. */
	len=main(argc, argv);
	/* Clear our local strdups. */
	for (wlen=argc;wlen && argv[wlen];free(argv[wlen--]));
	return len;
}
/** @} */
/** @} */
