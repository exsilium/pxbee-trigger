/****************************************************************************
 * Copyright (C) 2011 - 2015 Digi International Inc, All Rights Reserved.
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

#include <types.h>
#include <stdio.h>
#include <uart.h>

/**
 *	@ingroup api_utils
 *	@{
 *	@brief		This function reads a line from the serial console. Can be
 *				invoked in blocking and non blocking mode.
 *	@param[in]	lineptr	pointer to the char array where the string read will
 *              be stored.
 *	@param[in]	limit	max number of characters for the string that will 
 *              be read.
 *	@param[in]	flags   modify the behavior of the function. Supported flags
 *	            are:
 *	             O_NONBLOCK - the function doesn't block (otherwise, blocks)
 *
 *	@retval     The length of the line read
 *	@retval     0       If a line has not been captured and non blocking mode 
 *                      has been selected
 *	@retval 	-EINVAL on error
 */
ssize_t get_line(char **lineptr, size_t limit, uint8_t flags)
{
	static uint8_t lineidx = 0;
	ssize_t retval;
	uint8_t c;
	
	if (lineptr == NULL || limit == 0)
		return -EINVAL;

	do {
		while (uart_read(&c, 1)) {
			switch(c) {
			case '\r':
				putchar('\n');
				goto gotline;
	
			case '\b':
				if (lineidx) {
					printf("\b \b");
					lineidx--;
				}
				break;
				
			/* Cursors are not supported... */
	
			default:
				putchar(c);	/* echo */
				(*lineptr)[lineidx++] = (char)c;
				if (lineidx == (limit - 1))
					goto gotline;
				break;
			}
		}
	}while (!(flags & O_NONBLOCK));
	
	return 0;

gotline:
	(*lineptr)[lineidx++] = '\0';
	retval = lineidx;
	lineidx = 0;
	return retval;
}

