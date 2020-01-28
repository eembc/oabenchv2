#    Copyright (C) 2004 Artifex Software Inc.
# 
# This software is provided AS-IS with no warranty, either express or
# implied.
# 
# This software is distributed under license and may not be copied,
# modified or distributed except as expressly authorized under the terms
# of the license contained in the file LICENSE in this distribution.
# 
# For more information about licensing, please refer to
# http://www.ghostscript.com/licensing/. For information on
# commercial licensing, go to http://www.artifex.com/licensing/ or
# contact Artifex Software, Inc., 101 Lucas Valley Road #110,
# San Rafael, CA  94903, U.S.A., +1(415)492-9861.

# $Id: gsutil.py 6300 2005-12-28 19:56:24Z giles $

# gsutil.py
#
# this module contains utility routines used by the regression test scripts

import string

def check_extension(fn):
    f = string.lower(fn)
    if f[-3:] == '.ps' or f[-4:] == '.pdf' or f[-4:] == '.eps' \
       or f[-3:] == '.ai':
        return 1
    return 0
