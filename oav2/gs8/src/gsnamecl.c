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
/* $Id: gsnamecl.c 6651 2006-03-13 16:18:19Z stefan $ */
/* Callback mechanism for handling color spaces containing named colors. */

/*
 * This module has been created to provide a callback mechanism for special
 * processing of DeviceN and Separation color spaces.  One possible application
 * of this callback mechanism is to provide a means for special handling of
 * PANTONE or SWOP colors.
 *
 * This implementation consists of four routines.  There are a pair of
 * routines for both Separation and DeviceN color spaces.  Each pair consists
 * of a routine that is called when the color space is installed and a
 * second routine that is called to transform colors in that color space
 * into device colorant values.  The routines named_color_install_Separation
 * and named_color_install_DeviceN are called when a Separation or DeviceN
 * color space is installed.  These routines determine if the given color space
 * meets some criteria decided by the client.  These routines return true if the
 * colors in the color space should be processed via the second routine.
 */

#include "stdpre.h"
#include "math_.h"
#include "memory_.h"
#include "gx.h"
#include "gserrors.h"
#include "gscdefs.h"
#include "gscspace.h"
#include "gxdevice.h"
#include "gzstate.h"

#if ENABLE_NAMED_COLOR_CALLBACK		/* Defined in src/gsnamecl.h */

/*
 * Check if we want to use the callback color processing logic for the given
 * Separation color space.
 */
bool
named_color_callback_install_Separation(gs_color_space * pcs, gs_state * pgs)
{
    gx_device * dev = pgs->device;
    client_named_color_params_t * pcb =
	(client_named_color_params_t *) dev->named_color_callback;

    return (pcb == NULL) ? false
	    		 : pcb->client_procs->install_Separation(pcb, pcs, pgs);
}

/*
 * Check if we want to use the callback color processing logic for the given
 * DeviceN color space.
 */
bool
named_color_callback_install_DeviceN(gs_color_space * pcs, gs_state * pgs)
{
    gx_device * dev = pgs->device;
    client_named_color_params_t * pcb =
	(client_named_color_params_t *) dev->named_color_callback;

    return (pcb == NULL) ? false
	    		 : pcb->client_procs->install_DeviceN(pcb, pcs, pgs);
}

/*
 * Convert a Separation color using the 'named color' callback into device color.
 */
int
gx_remap_concrete_named_color_Separation(const frac * pconc,
	const gs_color_space * pcs, gx_device_color * pdc,
       	const gs_imager_state * pis, gx_device * dev, gs_color_select_t select)
{
    client_named_color_params_t * pcb =
	(client_named_color_params_t *) dev->named_color_callback;

    if (pcb == NULL) {
	dlprintf("ERROR:  Named color callback is NULL\n");
	return_error(gs_error_rangecheck);
    }
    else
	return pcb->client_procs->remap_Separation(pcb, pconc,
					pcs, pdc, pis, dev, select);
}

/*
 * Convert a DeviceN color using the 'named color' callback into device color.
 */
int
gx_remap_concrete_named_color_DeviceN(const frac * pconc,
	const gs_color_space * pcs, gx_device_color * pdc,
       	const gs_imager_state * pis, gx_device * dev, gs_color_select_t select)
{
    client_named_color_params_t * pcb =
	(client_named_color_params_t *) dev->named_color_callback;

    if (pcb == NULL) {
	dlprintf("ERROR:  Named color callback is NULL\n");
	return_error(gs_error_rangecheck);
    }
    else
	return pcb->client_procs->remap_DeviceN(pcb, pconc,
					pcs, pdc, pis, dev, select);
}

/*
 * Get the 'Named color' client callback parameter block pointer.  This value
 * is passed as a string type device paramter.  A string is being used since
 * PostScript does not support pointers as a type.  Note:  An integer type
 * is not being used since PS intergers are nominally 32 bits.  Thus there
 * would be a problem using integers to pass pointer values on 64 bit systems.
 */
int
named_color_callback_get_params(gx_device * dev, gs_param_list * plist)
{
    /* Convert our pointer to a PostScript hex string */
    char buf[64] = "16#";
    int buf_pos = 3;
    gs_param_string named_color_param;
    int idx;
    int val;
    size_t iptr;
   
    idx = ((int)sizeof(size_t)) * 8 - 4;
    iptr = (size_t)(dev->named_color_callback);
    while (idx >= 0) {
	val = (int)(iptr >> idx) & 0xf;
        if (val <= 9)
	    buf[buf_pos++] = '0' + val;
	else
	    buf[buf_pos++] = 'a' - 10 + val;
	idx -= 4;
    }
    buf[buf_pos] = '\0';
     
    param_string_from_transient_string(named_color_param, buf);

    return param_write_string(plist, "NamedColorCallback", &named_color_param);
}

/*
 * Put the 'Named color' client callback parameter block pointer.  This value
 * is passed as a string type device paramter.  A string is being used since
 * PostScript does not support pointers as a type.  Note:  An integer type
 * is not being used since PS integers are nominally 32 bits.  Thus there
 * would be a problem using integers to pass pointer values on 64 bit systems.
 */
int
named_color_callback_put_params(gx_device * dev, gs_param_list * plist)
{
    int code;
    size_t iptr = (size_t)(dev->named_color_callback);
    gs_param_string dh = { 0 };

    switch (code = param_read_string(plist, "NamedColorCallback", &dh)) {
	case 0:
	    {
	        /* 
	         * Convert from a string to a pointer.  
	         * It is assumed that size_t has the same size as a pointer.
	         * Allow formats (1234), (10#1234) or (16#04d2).
	         */
 	        int i;
	        int base = 10;
 	        int val;
	        code = 0;
	        for (i = 0; i < dh.size; i++) {
	            val = dh.data[i];
	            if ((val >= '0') && (val <= '9'))
		        val = val - '0';
	            else if ((val >= 'A') && (val <= 'F'))
		        val = val - 'A' + 10;
	            else if ((val >= 'a') && (val <= 'f'))
		        val = val - 'a' + 10;
	            else if (val == '#' && ((iptr == 10) || (iptr == 16))) {
		        base = (int) iptr;
		        iptr = 0;
		        continue;
	            }
	            else {
		        code = gs_error_rangecheck;
		        break;
	            }
	            iptr = iptr * base + val;
	        }
	    }
	    break;
	default:
	case 1:
	    dh.data = 0;
	    break;
    }
    if (code < 0) {
	param_signal_error(plist, "NamedColorCallback", code);
    }
    else
        dev->named_color_callback = (void *)iptr;

    return 0;
}

#endif 			/* ENABLE_NAMED_COLOR_CALLBACK */
