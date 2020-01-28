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
/* $Id: gdevmeds.h 6651 2006-03-13 16:18:19Z stefan $ */
/* Interface for gdevmeds.c */

#ifndef gdevmeds_INCLUDED
#  define gdevmeds_INCLUDED

#include "gdevprn.h"

int select_medium(gx_device_printer *pdev, const char **available,
		  int default_index);

#endif /* gdevmeds_INCLUDED */
