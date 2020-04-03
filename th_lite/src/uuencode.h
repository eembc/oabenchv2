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
/** @addtogroup UUENCODE_H Prototypes for uuencode.
@{ */

#ifndef   UUENCODE_H       
#define   UUENCODE_H

#ifdef __cplusplus
extern "C" {
#endif

int uu_send_buf( const char* buf, size_t length, const char* fn  );
int uu_send_file( const char* fn );
void encode (const char *raw_buffer, size_t raw_buf_len);

#ifdef __cplusplus
}
#endif
#endif
/** @} */
