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
/**	Platform-specific layer provides a consistent UART API to upper layers
 *	of the driver.
 *	
 *	@ingroup api_uart
 *	
 *	@defgroup api_uart
 *	
 *	@section macros_uart UART Macros 
 *	
 *	The uart_config() function needs as second parameter a byte containing the 
 *	configuration masks for the UART. These masks are defined with macros and 
 *	they are the following:
 *	
 *		- Macros to configure the \b parity \b enable:
 *			- \b UART_CFG_PARITY_DIS	: Disables the parity configuration.
 *			- \b UART_CFG_PARITY_EN		: Enables the parity configuration.
 *	
 *		- Macros to configure the \b parity \b value:
 *			- \b UART_CFG_PARITY_EVEN	: Configures the parity to even.
 *			- \b UART_CFG_PARITY_ODD 	: Configures the parity to odd.
 *	
 *		- Macros to configure the number \b data \b bits:
 *			- \b UART_CFG_BITS_8		: Configures the data bits to 8.
 *			- \b UART_CFG_BITS_9 		: Configures the data bits to 9.
 *	
 **		- Macros to configure the \b parity \b mask:
 *			- \b UART_CFG_PARITY_MASK 	: Enables the UART parity mask.
 *	
 *	Usage example:
 *	@code uart_config(9600, UART_CFG_PARITY_EN | UART_CFG_PARITY_ODD | UART_CFG_BITS_8);
 *	@endcode
 *	@warning	It is recommended not to use these macros, they are used by 
 *				the XBee Project Smart Editor of the XBee extensions.
 *	
 *	Apart from the configuration macros, there are other macros that configures 
 *	the number of wires of the UART. These macros should be defined before 
 *	calling the uart_config() function.
 *	
 *		- Macros to configure the number of wires for the UART:
 *			- \b UART_CFG_MODE_2W		: Configures the UART to use 2 wires (RX and TX)
 *			- \b UART_CFG_MODE_3W		: Configures the UART to use 3 wires (RX, TX and RTS)
 *			- \b UART_CFG_MODE_4W		: Configures the UART to use 3 wires (RX, TX, RTS and CTS)
 *	
 *	Usage example:
 *	@code #define UART_CFG_MODE_4W
 *	@endcode
 *	
 *	If none wire macro is defined, the UART will be configured to use 2 wires.
 *	
 *	If you define the UART_CFG_MODE_3W or the UART_CFG_MODE_4W macros, you 
 *	must also define the XBee pins for the RTS, the CTS or both pins:
 *	
 *		- If you define the \b UART_CFG_MODE_3W macro you must define the macro 
 *		  to configure the RTS pin:
 *			- \b UART_CFG_RTS_XPIN		: Defines the XBee pin corresponding to
 *										  the RTS pin.
 *	
 *		- If you define the \b UART_CFG_MODE_4W macro you must define the macro 
 *		  to configure the \b RTS and the \b CTS pins:
 *			- \b UART_CFG_RTS_XPIN		: Defines the XBee pin corresponding to
 *										  the RTS pin.
 *			- \b UART_CFG_CTS_XPIN		: Defines the XBee pin corresponding to
 *										  the CTS pin.
 *	Usage examples:
 *	@code #define UART_CFG_RTS_XPIN		XPIN_4
 *  #define UART_CFG_CTS_XPIN			XPIN_7
 *	@endcode
 *	
 ***************************************************************************/

#ifndef __UART_H_
#define __UART_H_

#include <types.h>
#include <system.h>

#if (ENABLE_STDIO_PRINTF_SCANF == 1)
#include <stdio.h>
#endif

#define UART_BAUD_1200			(((BUS_CLK_FREQ / 16) + 600) / 1200)
#define UART_BAUD_2400			(((BUS_CLK_FREQ / 16) + 1200) / 2400)
#define UART_BAUD_4800			(((BUS_CLK_FREQ / 16) + 2400) / 4800)
#define UART_BAUD_9600			(((BUS_CLK_FREQ / 16) + 4800) / 9600)
#define UART_BAUD_19200			(((BUS_CLK_FREQ / 16) + 9600) / 19200)
#define UART_BAUD_38400			(((BUS_CLK_FREQ / 16) + 19200) / 38400)
#define UART_BAUD_57600			(((BUS_CLK_FREQ / 16) + 28800) / 57600)
#define UART_BAUD_115200		(((BUS_CLK_FREQ / 16) + 57600) / 115200)

#define UART_CFG_PARITY_EVEN	(0 << 0)
#define UART_CFG_PARITY_ODD		(1 << 0)
#define UART_CFG_PARITY_DIS		(0 << 1)
#define UART_CFG_PARITY_EN		(1 << 1)
#define UART_CFG_PARITY_MASK	(3 << 0)
#define UART_CFG_BITS_8			(0 << 2)
#define UART_CFG_BITS_9			(1 << 2)

#define radio_uart_set_rts(v)	PTCD_PTCD1 = (v)
#define radio_uart_get_cts()	PTDD_PTDD6

#define uart_set_rts(v)			PTCD_PTCD7 = (v)
#define uart_get_cts()			PTDD_PTDD7

#define	uart_get_rx_byte()		SCI1D

#ifdef ENABLE_UART
#ifndef UART_CFG_RX_BUF_LEN
#define UART_CFG_RX_BUF_LEN		64
#endif

#define UART_CFG				(UART_CFG_PAR_EN |		\
								 UART_CFG_PAR_VAL |		\
								 UART_CFG_BITS)
#endif

int uart_config(uint32_t baudrate, uint8_t config);
size_t uart_bytes_in_rx_buffer(void);
size_t uart_write(const void *buf, size_t len);
size_t uart_read(void *buf, size_t len);
int radio_uart_config(uint32_t baudrate, uint8_t config);
void radio_uart_write_byte(const uint8_t data);
uint8_t radio_uart_write(const uint8_t *buffer, uint8_t len);
size_t radio_uart_read(void *buf, size_t len);

#endif /* __UART_H_ */
