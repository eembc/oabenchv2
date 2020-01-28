/*
    jbig2dec

    Copyright (c) 2001 artofcode LLC.

    This software is distributed under license and may not
    be copied, modified or distributed except as expressly
    authorized under the terms of the license contained in
    the file LICENSE in this distribution.
                                                                                
    For information on commercial licensing, go to
    http://www.artifex.com/licensing/ or contact
    Artifex Software, Inc.,  101 Lucas Valley Road #110,
    San Rafael, CA  94903, U.S.A., +1(415)492-9861.

    $Id: jbig2_mmr.h 6300 2005-12-28 19:56:24Z giles $
*/

int
jbig2_decode_generic_mmr(Jbig2Ctx *ctx,
			 Jbig2Segment *segment,
			 const Jbig2GenericRegionParams *params,
			 const byte *data, size_t size,
			 Jbig2Image *image);

