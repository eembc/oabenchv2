/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

/** @addtogroup SHFL
@{ */
/** @addtogroup THVINFO_H Test Harness Version Information
@{ */

/** File Sentinel */
#ifndef THVINFO_H
#define THVINFO_H

#ifdef __cplusplus
extern "C" {
#endif

/** Version Text displayed to the user.

This is a human readable form of the version number. It is manually kept
in sync with major, minor, step, and revision numbers.
The revision minor, step, and revision are related to CVS tags.
*/
#define EEMBC_TH_ID "EEMBC Portable Test Harness V4.3B16"

/** Major Release of Test Harness. */
#define EEMBC_TH_MAJOR         4
/** Minor Release of Test Harness. */
#define EEMBC_TH_MINOR         3
/** Step Version in Release. Describes Beta and Release. */
#define EEMBC_TH_STEP          'B'
/** Sub version within Step. */
#define EEMBC_TH_REVISION      16

#ifdef __cplusplus
}
#endif
#endif /* THVINFO_H */
/** @} */
/** @} */
