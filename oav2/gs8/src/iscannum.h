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

/* $Id: iscannum.h 6651 2006-03-13 16:18:19Z stefan $ */
/* Interface to Ghostscript number scanner */

#ifndef iscannum_INCLUDED
#  define iscannum_INCLUDED

/*
 * Scan a number.  If the number consumes the entire string, return 0;
 * if not, set *psp to the first character beyond the number and return 1.
 * Note that scan_number does not mark the result ref as "new".
 */
int scan_number(const byte * sp, const byte * end, int sign, ref * pref,
		const byte ** psp, const bool PDFScanRules);

#endif /* iscannum_INCLUDED */
