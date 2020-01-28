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

/* $Id: iconf.h 6651 2006-03-13 16:18:19Z stefan $ */
/* Collected imports for interpreter configuration and initialization */

#ifndef iconf_INCLUDED
#define iconf_INCLUDED
/* ------ Imported data ------ */

/* Configuration information imported from iccinit[01].c */
extern const byte gs_init_string[];
extern const uint gs_init_string_sizeof;

/* Configuration information imported from iconf.c */
extern const ref gs_init_file_array[];
extern const ref gs_emulator_name_array[];

#endif /* iconf_INCLUDED */
