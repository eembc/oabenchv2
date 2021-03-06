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
/* $Id: errno_.h 6651 2006-03-13 16:18:19Z stefan $ */
/* Generic substitute for Unix errno.h */

#ifndef errno__INCLUDED
#  define errno__INCLUDED

/* We must include std.h before any file that includes sys/types.h. */
#include "std.h"

/* All environments provide errno.h, but in some of them, errno.h */
/* only defines the error numbers, and doesn't declare errno. */
#if		HAVE_ERRNO_H
#include <errno.h>
#endif
#ifndef errno			/* in case it was #defined (very implausible!) */
extern int errno;

#endif
#include	"therrno.h"
#endif /* errno__INCLUDED */
