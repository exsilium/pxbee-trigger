/****************************************************************************
 * Copyright (C) 2010 - 2015 Digi International Inc, All Rights Reserved.
 *
 * This software is provided as instructional material without charge 
 * by Digi International for use by its employees and customers
 * subject to the following terms.
 *
 * PERMISSION
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software, to deal with it without restriction, 
 * including without limitation the rights to use, copy,  modify, merge, publish, 
 * distribute, sublicense, and/or sell copies of it, and to permit persons to 
 * whom it is furnished to do so, provided the above copyright notice 
 * and this permission notice are included in all derived works
 * and the use of this software is restricted to Digi products.
 *
 * WARRANTY
 * THIS SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, OR NONINFRINGEMENT.  
 *
 * LIABILITY
 * IN NO EVENT SHALL DIGI INTERNATIONAL BE LIABLE FOR ANY CLAIM, DAMAGES, 
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT, OR OTHERWISE, 
 * ARISING FROM, OUT OF, OR IN CONNECTION WITH THE SOFTWARE, OR THE USE 
 * OR OTHER DEALINGS WITH THE SOFTWARE.
 *
 ****************************************************************************/
/**
 *	@ingroup api_misc
 *	@defgroup api_misc
 *	Platform-specific layer provides a miscellanous functions
 *	@section   Miscellanous API Overview
 *	This API contains some functions for manage the programmable XBee modules
 *			
 */
#include <system.h>
#include <types.h>
#include <debug.h>
#include "xbee/platform.h"

/**
 *	@ingroup api_misc
 *	@brief		Make a dump of a part of memory
 *	@param[in]	data	Pointer to the part of memory
 *	@param[in]	val  	Lenght of data to dump
 *	@retval		Nothing 
 */
void dump(const uint8_t *data, int len)
{
#if ENABLE_STDIO_PRINTF_SCANF == 1
	hex_dump( data, len, HEX_DUMP_FLAG_OFFSET);
#endif
}
