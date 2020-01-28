/* Copyright (C) 2001-2006 artofcode LLC.
   All Rights Reserved.
  
   This software is provided AS-IS with no warranty, either express or
   implied.

   This software is distributed under license and may not be copied, modified
   or distributed except as expressly authorized under the terms of that
   license.  Refer to licensing information at http://www.artifex.com/
   or contact Artifex Software, Inc.,  7 Mt. Lassen Drive - Suite A-134,
   San Rafael, CA  94903, U.S.A., +1(415)492-9861, for further information.
*/

/* $Id: istream.h 6651 2006-03-13 16:18:19Z stefan $ */
/* Interpreter support procedures for streams */
/* Requires scommon.h */

#ifndef istream_INCLUDED
#  define istream_INCLUDED

/* Procedures exported by zfproc.c */

	/* for zfilter.c - procedure stream initialization */
int sread_proc(ref *, stream **, gs_ref_memory_t *);
int swrite_proc(ref *, stream **, gs_ref_memory_t *);

	/* for interp.c, zfileio.c, zpaint.c - handle a procedure */
	/* callback or an interrupt */
int s_handle_read_exception(i_ctx_t *, int, const ref *, const ref *,
			    int, op_proc_t);
int s_handle_write_exception(i_ctx_t *, int, const ref *, const ref *,
			     int, op_proc_t);

#endif /* istream_INCLUDED */
