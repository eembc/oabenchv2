/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
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
