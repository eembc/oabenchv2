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

/* $Id: gscencs.c 6651 2006-03-13 16:18:19Z stefan $ */
/* Compact C representation of built-in encodings */

#include "memory_.h"
#include "gscedata.h"
#include "gscencs.h"
#include "gserror.h"
#include "gserrors.h"

/*
 * The actual encoding data tables in gscedata.c, and the internal
 * interface definitions in gscedata.h, are generated by toolbin/encs2c.ps,
 * q.v.
 *
 * In the encoding tables in gscedata.c, each glyph is represented by a
 * ushort (16-bit) value.  A bias of gs_c_min_std_encoding_glyph is added
 * or subtracted to form a gs_glyph value.
 */

/*
 * gscedata.[hc] defines the following tables:
 *	const char gs_c_known_encoding_chars[NUM_CHARS] --
 *	  the character table.
 *	const int gs_c_known_encoding_offsets[NUM_INDIRECT_LEN] --
 *	  the starting offsets of the names of a given length in the
 *	  character table.
 *	const ushort *const gs_c_known_encodings[] --
 *	  pointers to the encodings per se.
 *	const ushort gs_c_known_encoding_lengths[] --
 *	  lengths of the encodings.
 */

const gs_glyph gs_c_min_std_encoding_glyph = gs_min_cid_glyph - 0x10000;

/*
 * Encode a character in a known encoding.  The only use for glyph numbers
 * returned by this procedure is to pass them to gs_c_glyph_name or gs_c_decode.
 */
gs_glyph
gs_c_known_encode(gs_char ch, int ei)
{
    if (ei < 0 || ei >= gs_c_known_encoding_count ||
	ch >= gs_c_known_encoding_lengths[ei]
	)
	return gs_no_glyph;
    return gs_c_min_std_encoding_glyph + gs_c_known_encodings[ei][ch];
}


/*
 * Decode a gs_c_glyph_name glyph with a known encoding.
 */
gs_char
gs_c_decode(gs_glyph glyph, int ei)
{
    /* Do a binary search for glyph, using gx_c_known_encodings_reverse */
    const ushort *const encoding = gs_c_known_encodings[ei];
    const ushort *const reverse = gs_c_known_encodings_reverse[ei];
    int first_index = 0;
    int last_index = gs_c_known_encoding_reverse_lengths[ei];
    while (first_index < last_index) {
        const int test_index = (first_index + last_index) / 2;
        const gs_glyph test_glyph =
         gs_c_min_std_encoding_glyph + encoding[reverse[test_index]];
        if (glyph < test_glyph)
            last_index = test_index;
        else if (glyph > test_glyph)
            first_index = test_index + 1;
        else
            return reverse[test_index];
    }
    return GS_NO_CHAR;
}


/*
 * Convert a glyph number returned by gs_c_known_encode to a string.
 */
int
gs_c_glyph_name(gs_glyph glyph, gs_const_string *pstr)
{
    uint n = (uint)(glyph - gs_c_min_std_encoding_glyph);
    uint len = N_LEN(n);
    uint off = N_OFFSET(n);

#ifdef DEBUG
    if (len == 0 || len > gs_c_known_encoding_max_length ||
	off >= gs_c_known_encoding_offsets[len + 1] -
	  gs_c_known_encoding_offsets[len] ||
	off % len != 0
	)
	return_error(gs_error_rangecheck);
#endif
    pstr->data = (const byte *)
	&gs_c_known_encoding_chars[gs_c_known_encoding_offsets[len] + off];
    pstr->size = len;
    return 0;
}

/*
 * Test whether a string is one that was returned by gs_c_glyph_name.
 */
bool
gs_is_c_glyph_name(const byte *str, uint len)
{
    return (str >= (const byte *)gs_c_known_encoding_chars &&
	    (str - (const byte *)gs_c_known_encoding_chars) <
	      gs_c_known_encoding_total_chars);
}

/*
 * Return the glyph number corresponding to a string (the inverse of
 * gs_c_glyph_name), or gs_no_glyph if the glyph name is not known.
 */
gs_glyph
gs_c_name_glyph(const byte *str, uint len)
{
    if (len == 0 || len > gs_c_known_encoding_max_length)
	return gs_no_glyph;
    /* Binary search the character table. */
    {
	uint base = gs_c_known_encoding_offsets[len];
	const byte *bot = (const byte *)&gs_c_known_encoding_chars[base];
	uint count = (gs_c_known_encoding_offsets[len + 1] - base) / len;
	uint a = 0, b = count;	/* know b > 0 */
	const byte *probe;

	while (a < b) {		/* know will execute at least once */
	    uint m = (a + b) >> 1;
	    int cmp;

	    probe = bot + m * len;
	    cmp = memcmp(str, probe, len);
	    if (cmp == 0)
		return gs_c_min_std_encoding_glyph + N(len, probe - bot);
	    else if (cmp > 0)
		a = m + 1;
	    else
		b = m;
	}
    }

    return gs_no_glyph;
}

#ifdef TEST

/* NOTE: test values will have to be updated if representation changes. */
#define I_caron N(5,85)
#define I_carriagereturn N(14,154)
#define I_circlemultiply N(14,168)
#define I_numbersign N(10,270)
#define I_copyright N(9,180)
#define I_notdefined N(7, 0)

/* Test */
#include <stdio.h>
main()
{
    gs_glyph g;
	gs_char c;
    gs_const_string str;	

    /* Test with a short name. */
    g = gs_c_known_encode((gs_char)0237, 1); /* caron */
    printf("caron is %u, should be %u\n",
	   g - gs_c_min_std_encoding_glyph, I_caron);
    gs_c_glyph_name(g, &str);
    fwrite(str.data, 1, str.size, stdout);
    printf(" should be caron\n");

    /* Test with a long name. */
    g = gs_c_known_encode((gs_char)0277, 2); /* carriagereturn */
    printf("carriagereturn is %u, should be %u\n",
	   g - gs_c_min_std_encoding_glyph, I_carriagereturn);
    gs_c_glyph_name(g, &str);
    fwrite(str.data, 1, str.size, stdout);
    printf(" should be carriagereturn\n");

    /* Test lookup with 3 kinds of names. */
    g = gs_c_name_glyph((const byte *)"circlemultiply", 14);
    printf("circlemultiply is %u, should be %u\n",
	   g - gs_c_min_std_encoding_glyph, I_circlemultiply);
    g = gs_c_name_glyph((const byte *)"numbersign", 10);
    printf("numbersign is %u, should be %u\n",
	   g - gs_c_min_std_encoding_glyph, I_numbersign);
    g = gs_c_name_glyph((const byte *)"copyright", 9);
    printf("copyright is %u, should be %u\n",
	   g - gs_c_min_std_encoding_glyph, I_copyright);

    /* Test reverse lookup */
    c = gs_c_decode(I_caron + gs_c_min_std_encoding_glyph, 1);
    printf("%u (caron) looked up as %u, should be %u\n",
     I_caron, c, 0237);
    c = gs_c_decode(I_carriagereturn + gs_c_min_std_encoding_glyph, 2);
    printf("%u (carriagereturn) looked up as %u, should be %u\n",
     I_carriagereturn, c, 0277);
    c = gs_c_decode(I_notdefined + gs_c_min_std_encoding_glyph, 1); /* undef'd */
    printf("%u (notdefined) looked up as %d , should be %d\n",
     I_notdefined, c, GS_NO_CHAR);

    exit(0);
}

#endif /* TEST */
