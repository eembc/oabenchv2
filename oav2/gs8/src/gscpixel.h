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

/* $Id: gscpixel.h 6651 2006-03-13 16:18:19Z stefan $ */
/* Interface to DevicePixel color space */
/* Requires gscspace.h */

#ifndef gscpixel_INCLUDED
#  define gscpixel_INCLUDED

/* Initialize a DevicePixel color space. */
int gs_cspace_init_DevicePixel(gs_memory_t *mem, gs_color_space * pcs, int depth);

#endif /* gscpixel_INCLUDED */
