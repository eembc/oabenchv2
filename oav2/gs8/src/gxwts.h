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
/*$Id: gxwts.h 6673 2006-03-22 08:43:11Z leonardo $ */
#ifndef gxwts_INCLUDED
#  define gxwts_INCLUDED

typedef bits16 wts_screen_sample_t;

#ifndef wts_screen_t_DEFINED
#  define wts_screen_t_DEFINED
typedef struct wts_screen_s wts_screen_t;
#endif

typedef enum {
    WTS_SCREEN_RAT,
    WTS_SCREEN_J,
    WTS_SCREEN_H
} wts_screen_type;

struct wts_screen_s {
    wts_screen_type type;
    int cell_width;
    int cell_height;
    int cell_shift;
    wts_screen_sample_t *samples;
};

typedef struct {
    wts_screen_t base;

    /* Probabilities of "jumps". A and B jumps can happen when moving
       one pixel to the right. C and D can happen when moving one pixel
       down. */
    int pa; /* change to double? */
    int pb;
    int pc;
    int pd;

    int XA;
    int YA;
    int XB;
    int YB;
    int XC;
    int YC;
    int XD;
    int YD;
} wts_screen_j_t;

typedef struct {
    wts_screen_t base;

    /* This is the exact value that x1 and (width-x1) approximates. */
    double px;
    /* Ditto y1 and (height-y1). */
    double py;

    int x1;
    int y1;
} wts_screen_h_t;

int wts_get_samples(const wts_screen_t *ws, int x, int y,
		wts_screen_sample_t **samples, int *p_nsamples);

#endif
