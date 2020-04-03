/**
 *
 * Copyright (C) EEMBC(R) All Rights Reserved
 *
 * This software is licensed with an Acceptable Use Agreement under Apache 2.0.
 * Please refer to the license file (LICENSE.md) included with this code.
 *
 */

/** Prototypes and eembc types. */
#include "thlib.h"
/** t_exit definition. */
#include "thfl.h"

/** @addtogroup SHFL
@{ */
/** @addtogroup crc_c Functional Layer Cyclical Redundancy Check Routines
@{ */

/** Compute crc16 a byte at a time */
e_u16 Calc_crc8(e_u8 data, e_u16 crc )
{
	e_u8 i=0,x16=0,carry=0; /* SG initialization to avoid optimization bug */

	for (i = 0; i < 8; i++)
    {
		x16 = (e_u8)((data & 1) ^ ((e_u8)crc & 1));
		data >>= 1;
		if (x16 == 1)
		{
		   crc ^= 0x4002;
		   carry = 1;
		}
		else carry = 0;
		crc >>= 1;
		if (carry)
		   crc |= 0x8000;
		else
		   crc &= 0x7fff;
    }
	return crc;
}

/** Compute crc16 of a buffer. 

A CRC is calculated of an input buffer. 
Multiple buffer CRC checking is also supported for streaming 
output data. 

For a single buffer the input CRC MUST be 0, and the final 
CRC result is returned.

In the muliple buffer case, the input CRC is used as an intermediate
value for calculating the final CRC result.
The first buffer is passed with a inputCRC 
of 0 as in the single buffer case. The subsequent buffers are
passed with the CRC result of the previous buffer calculation. 

The caller must save the CRC result value and pass it 
back in inputCRC for the additional buffers.

The original usage is that this routine is called 
after a th_fsize and th_fread of a file into a buffer. The size and
buffer parameters are compatible with th_fsize and th_fread types.

@note Addressability is not assumed, but the data is assumed 
to be unpacked. Packing can be 
handled by using crc16, or crc32 routines. A Local fix is allowed.
However, it is likely that other dependencies have already caused
the buffer to be unpacked. When porting, You must ensure that the buffer
is packed before applying a local fix. When calculating
CRC's on packed data, you may also 
have endian issues.
@param inbuf Input buffer, usually e_u8* of data to CRC check.
@param size  Number of e_u8's to CRC.
@param inputCRC Initial CRC value for inbuf. 0 for the first buffer.
For multiple buffers, the CRC of the previous call must be used. The
caller is responsible for saving this value.
@retval CRC of inbuf based on inputCRC.
*/
e_u16	t_crcbuffer(const void *inbuf, size_t size, e_u16 inputCRC)
{
	e_u16		CRC=inputCRC;
	e_u8		*buf=(void *)inbuf;
	size_t		i;

	/* 
	 * Allow the AND case if found to be necessary.
	 * Allow AND case being a NULL inbuf, and 0 size buffer where the inputCRC is returned.
	 */
	if (!buf && !size)
		return 0;
	else if (!buf || !size)
	{
		th_printf("\nFailure: Attempt to CRC an empty buffer, inbuf:%x size:%d.\n",(size_t)buf,size);
		return 0;
	}

	for (i=0;i<size;i++)
	{
		CRC=Calc_crc8(*buf,CRC);
		buf++;
	}
	return CRC;
}
/** Compute crc16 a 16 bits at a time */
e_u16 Calc_crc16( e_u16 data, e_u16 crc )
{

	crc = Calc_crc8( (e_u8)(data & 0x00FF ), crc );
	crc = Calc_crc8( (e_u8)((data & 0xFF00)>>8), crc );
	return crc;
}

/** Compute crc16 a 32 bits at a time */
e_u16 Calc_crc32( e_u32 data, e_u16 crc )
{

	crc = Calc_crc8( (e_u8)(data & 0x000000FF), crc );
	crc = Calc_crc8( (e_u8)((data & 0x0000FF00)>>8), crc );
	crc = Calc_crc8( (e_u8)((data & 0x00FF0000)>>16), crc );
	crc = Calc_crc8( (e_u8)((data & 0xFF000000)>>24), crc );

	return crc;
}
/** @} */
/** @} */
