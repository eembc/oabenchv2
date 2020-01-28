/**
 * @file
 * @brief  Test Harness Cyclical Redundancy Check Routines
 *
 *$RCSfile: crc.c,v $
 *
 *  EEMBC : EEMBC Technical Advisory Group (TechTAG)
 *
 * @author  ARM Ltd., ECL, LLC
 *
 *    CVS : $Revision: 1.24 $
 *          $Date: 2005/12/02 23:53:33 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/techtag/th_lite/src/crc.c,v $
 *          
 * @note   
 *
 *
 * HISTORY :
 *
 * $Log: crc.c,v $
 * Revision 1.24  2005/12/02 23:53:33  rick
 * Fix mixed EOL format causing ^M's to appear in Unix checkouts.
 *
 * Revision 1.23  2005/09/10 04:02:23  rick
 * eol update, add uu_send_file
 *
 * Revision 1.22  2005/04/27 20:33:13  rick
 * Copyrite update 2005
 *
 * Revision 1.21  2004/12/08 23:27:17  rick
 * New standard header for documentation generation.
 *
 * Revision 1.9  2004/07/07 01:03:22  rick
 * Remove exit from harness, print Failure message instead.
 *
 * Revision 1.8  2004/07/02 18:00:04  rick
 * Return without th_exec if user requests Null buffer of size 0.
 *
 * Revision 1.7  2004/07/01 17:34:16  rick
 * Add th_crcbuffer
 *
 * Revision 1.6  2004/06/29 19:36:22  rick
 * EE_REDIRECT, and Shared file for Regular and Lite
 *
 * Revision 1.5  2004/06/23 05:55:23  rick
 * EE_REDIRECT, and Shared Files
 *
 * Revision 1.4  2004/03/15 21:29:05  rick
 * Add documentation tags, and cleanup comments
 *
 * Revision 1.3  2004/01/22 00:56:51  rick
 * Release cleanup, copyright year corrections
 *
 * Revision 1.2  2002/09/12 19:02:25  rick
 * Fix dbpf and | definitions
 *
 * Revision 1.1  2002/08/06 21:57:16  rick
 * Add NI CRC to TH Regular
 *
 * Revision 1.11  2002/05/10 23:39:24  rick
 * Fix missing shifts in 16, and 32 bit CRC calculations
 *
 * Revision 1.10  2002/03/18 21:15:08  rick
 * Add al_report, cyclecount, crc fix in iirflt, and pktflow.
 *
 *
 * @verbatim
 *------------------------------------------------------------------------------
 * Copyright (c) 1998-2005 by the EDN Embedded Microprocessor 
 * Benchmark Consortium (EEMBC), Inc. 
 * 
 * All Rights Reserved. This is licensed program product and 
 * is owned by EEMBC. The Licensee understands and agrees that the 
 * Benchmarks licensed by EEMBC hereunder (including methods or concepts 
 * utilized therein) contain certain information that is confidential 
 * and proprietary which the Licensee expressly agrees to retain in the 
 * strictest confidence and to use only in conjunction with the Benchmarks 
 * pursuant to the terms of this Agreement. The Licensee further agrees 
 * to keep the source code and all related documentation confidential and 
 * not to disclose such source code and/or related documentation to any 
 * third party. The Licensee and any READER of this code is subject to 
 * either the EEMBC Member License Agreement and/or the EEMBC Licensee 
 * Agreement. 
 * TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, EEMBC DISCLAIMS ALL 
 * WARRANTIES, EITHER EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, 
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR 
 * PURPOSE, WITH REGARD TO THE BENCHMARKS AND THE ACCOMPANYING 
 * DOCUMENTATION. LICENSEE ACKNOWLEDGES AND AGREES THAT THERE ARE NO 
 * WARRANTIES, GUARANTIES, CONDITIONS, COVENANTS, OR REPRESENTATIONS BY 
 * EEMBC AS TO MARKETABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR OTHER 
 * ATTRIBUTES, WHETHER EXPRESS OR IMPLIED (IN LAW OR IN FACT), ORAL OR 
 * WRITTEN. 
 * 
 * Licensee hereby agrees by accessing this source code that all benchmark 
 * scores related to this code must be certified by ECL prior to publication 
 * in any media, form, distribution, or other means of conveyance of 
 * information subject to the terms of the EEMBC Member License Agreement 
 * and/or EEMBC Licensee Agreement. 
 * 
 * Other Copyright Notice (if any): 
 * 
 * For conditions of distribution and use, see the accompanying README file.
 *------------------------------------------------------------------------------
 * @endverbatim
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
