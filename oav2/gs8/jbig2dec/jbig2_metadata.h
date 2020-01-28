/*
    jbig2dec
    
    Copyright (c) 2003 artofcode LLC.
    
    This software is distributed under license and may not
    be copied, modified or distributed except as expressly
    authorized under the terms of the license contained in
    the file LICENSE in this distribution.
                                                                                
    For information on commercial licensing, go to
    http://www.artifex.com/licensing/ or contact
    Artifex Software, Inc.,  101 Lucas Valley Road #110,
    San Rafael, CA  94903, U.S.A., +1(415)492-9861.

    $Id: jbig2_metadata.h 6300 2005-12-28 19:56:24Z giles $
*/


#ifndef _JBIG2_METADATA_H
#define _JBIG2_METADATA_H

/* metadata from extension segments */

/* these bits should be moved to jbig2.h for public access */
typedef enum {
    JBIG2_ENCODING_ASCII,
    JBIG2_ENCODING_UCS16
} Jbig2Encoding;

typedef struct _Jbig2Metadata Jbig2Metadata;

Jbig2Metadata *jbig2_metadata_new(Jbig2Ctx *ctx, Jbig2Encoding encoding);
void jbig2_metadata_free(Jbig2Ctx *ctx, Jbig2Metadata *md);
int jbig2_metadata_add(Jbig2Ctx *ctx, Jbig2Metadata *md,
                        const char *key, const int key_length,
                        const char *value, const int value_length);

struct _Jbig2Metadata {
    Jbig2Encoding encoding;
    char **keys, **values;
    int entries, max_entries;
};

/* these bits can go to jbig2_priv.h */
int jbig2_parse_comment_ascii(Jbig2Ctx *ctx, Jbig2Segment *segment,
                                const uint8_t *segment_data);
int jbig2_parse_comment_unicode(Jbig2Ctx *ctx, Jbig2Segment *segment,
                               const uint8_t *segment_data);

#endif /* _JBIG2_METADATA_H */
