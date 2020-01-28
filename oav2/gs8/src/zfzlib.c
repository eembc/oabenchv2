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

/* $Id: zfzlib.c 6651 2006-03-13 16:18:19Z stefan $ */
/* zlib and Flate filter creation */
#include "ghost.h"
#include "oper.h"
#include "idict.h"
#include "strimpl.h"
#include "spdiffx.h"
#include "spngpx.h"
#include "szlibx.h"
#include "idparam.h"
#include "ifilter.h"
#include "ifrpred.h"
#include "ifwpred.h"

/* Common setup for zlib (Flate) filter */
private int
filter_zlib(i_ctx_t *i_ctx_p, stream_zlib_state *pzls)
{
    os_ptr op = osp;
    int code = 0;

    (*s_zlibE_template.set_defaults)((stream_state *)pzls);
    if (r_has_type(op, t_dictionary))
	code = dict_int_param(op, "Effort", -1, 9, -1, &pzls->level);
    return code;
}

/* <source> zlibEncode/filter <file> */
/* <source> <dict> zlibEncode/filter <file> */
private int
zzlibE(i_ctx_t *i_ctx_p)
{
    stream_zlib_state zls;
    int code = filter_zlib(i_ctx_p, &zls);

    if (code < 0)
	return code;
    return filter_write(i_ctx_p, 0, &s_zlibE_template, (stream_state *)&zls, 0);
}

/* <target> zlibDecode/filter <file> */
/* <target> <dict> zlibDecode/filter <file> */
private int
zzlibD(i_ctx_t *i_ctx_p)
{
    stream_zlib_state zls;

    (*s_zlibD_template.set_defaults)((stream_state *)&zls);
    return filter_read(i_ctx_p, 0, &s_zlibD_template, (stream_state *)&zls, 0);
}

/* <source> FlateEncode/filter <file> */
/* <source> <dict> FlateEncode/filter <file> */
private int
zFlateE(i_ctx_t *i_ctx_p)
{
    stream_zlib_state zls;
    int code = filter_zlib(i_ctx_p, &zls);

    if (code < 0)
	return code;
    return filter_write_predictor(i_ctx_p, 0, &s_zlibE_template,
				  (stream_state *)&zls);
}

/* <target> FlateDecode/filter <file> */
/* <target> <dict> FlateDecode/filter <file> */
private int
zFlateD(i_ctx_t *i_ctx_p)
{
    stream_zlib_state zls;

    (*s_zlibD_template.set_defaults)((stream_state *)&zls);
    return filter_read_predictor(i_ctx_p, 0, &s_zlibD_template,
				 (stream_state *)&zls);
}

/* ------ Initialization procedure ------ */

const op_def zfzlib_op_defs[] =
{
    op_def_begin_filter(),
    {"1zlibEncode", zzlibE},
    {"1zlibDecode", zzlibD},
    {"1FlateEncode", zFlateE},
    {"1FlateDecode", zFlateD},
    op_def_end(0)
};
