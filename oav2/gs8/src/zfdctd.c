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

/* $Id: zfdctd.c 6651 2006-03-13 16:18:19Z stefan $ */
/* DCTDecode filter creation */
#include "memory_.h"
#include "stdio_.h"		/* for jpeglib.h */
#include "jpeglib_.h"
#include "ghost.h"
#include "oper.h"
#include "gsmemory.h"
#include "strimpl.h"
#include "sdct.h"
#include "sjpeg.h"
#include "ialloc.h"
#include "ifilter.h"
#include "iparam.h"

private_st_jpeg_decompress_data();

/* Import the parameter processing procedure from sddparam.c */
stream_state_proc_put_params(s_DCTD_put_params, stream_DCT_state);

/* <source> <dict> DCTDecode/filter <file> */
/* <source> DCTDecode/filter <file> */
private int
zDCTD(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    gs_memory_t *mem = (gs_memory_t *)(i_ctx_p->memory.current);
    stream_DCT_state state;
    dict_param_list list;
    jpeg_decompress_data *jddp;
    int code;
    const ref *dop;
    uint dspace;

    /* First allocate space for IJG parameters. */
    jddp = gs_alloc_struct_immovable(mem,jpeg_decompress_data,
      &st_jpeg_decompress_data, "zDCTD");
    if (jddp == 0)
	return_error(e_VMerror);
    if (s_DCTD_template.set_defaults)
	(*s_DCTD_template.set_defaults) ((stream_state *) & state);
    state.data.decompress = jddp;
    jddp->memory = state.jpeg_memory = mem;	/* set now for allocation */
    jddp->scanline_buffer = NULL;	/* set this early for safe error exit */
    state.report_error = filter_report_error;	/* in case create fails */
    if ((code = gs_jpeg_create_decompress(&state)) < 0)
	goto fail;		/* correct to do jpeg_destroy here */
    /* Read parameters from dictionary */
    if (r_has_type(op, t_dictionary))
	dop = op, dspace = r_space(op);
    else
	dop = 0, dspace = 0;
    if ((code = dict_param_list_read(&list, dop, NULL, false, iimemory)) < 0)
	goto fail;
    if ((code = s_DCTD_put_params((gs_param_list *) & list, &state)) < 0)
	goto rel;
    /* Create the filter. */
    jddp->template = s_DCTD_template;
    code = filter_read(i_ctx_p, 0, &jddp->template,
		       (stream_state *) & state, dspace);
    if (code >= 0)		/* Success! */
	return code;
    /*
     * We assume that if filter_read fails, the stream has not been
     * registered for closing, so s_DCTD_release will never be called.
     * Therefore we free the allocated memory before failing.
     */
rel:
    iparam_list_release(&list);
fail:
    gs_jpeg_destroy(&state);
    gs_free_object(mem, jddp, "zDCTD fail");
    return code;
}

/* ------ Initialization procedure ------ */

const op_def zfdctd_op_defs[] =
{
    op_def_begin_filter(),
    {"2DCTDecode", zDCTD},
    op_def_end(0)
};
