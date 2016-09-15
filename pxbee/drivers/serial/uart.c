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
 *	@section uart UART API Overview
 *	
 *	This API contains the functions to configure and control the UART 
 *	interface of the programmable XBee devices.
 *	The device has two universal asynchronous receiver/transmitters, but one 
 *	of them is directly connected to the UART of the radio chip, so only the 
 *	first of the UART modules can be externally accessed.
 *	
 *	- UART configuration functions:
 *		- uart_config()
 *		- radio_uart_config()
 *	
 *	- Functions to read/write the UART:
 *		- uart_bytes_in_rx_buffer()
 *		- uart_read()
 *		- uart_write()
 *	
 *	- Miscellaneous functions:
 *		- uart_isr()
 */
#include <system.h>
#include <types.h>
#include <errno.h>
#include <uart.h>
#include <cbuffer.h>
#include <gpios.h>

#include "xbee/device.h"

#define ENABLE_RADIO_UART

#define UART_STAT_ERROR_MASK	(SCI1S1_PF_MASK | SCI1S1_FE_MASK | \
								 SCI1S1_NF_MASK | SCI1S1_OR_MASK)

#if defined(ENABLE_RADIO_UART) || defined(ENABLE_UART)
static uint16_t uart_get_scibd(uint32_t baudrate)
{
	/** 
	 * Avoid floating point calculation for baud rate divider,
	 * use compile-time calculations.
	 * Freescale 32-bit compares require lots of code. Cheat and
	 * just use lower 16 bits of baud rate. Saves 33 code bytes.
	 */
	if ((uint16_t)baudrate == 1200)
		return UART_BAUD_1200;
	else if ((uint16_t)baudrate == 2400)
		return UART_BAUD_2400;
	else if ((uint16_t)baudrate == 4800)
		return UART_BAUD_4800;
	else if ((uint16_t)baudrate == 9600)
		return UART_BAUD_9600;
	else if ((uint16_t)baudrate == 19200)
		return UART_BAUD_19200;
	else if ((uint16_t)baudrate == 38400)
		return UART_BAUD_38400;
	else if ((uint16_t)baudrate == 57600)
		return UART_BAUD_57600;
	else if ((uint16_t)baudrate == (115200 & 0xffff))
		return UART_BAUD_115200;
	return 0xffff;
}
#endif /* defined(ENABLE_RADIO_UART) || defined(ENABLE_UART) */

#ifdef ENABLE_UART

#if UART_CFG_RX_WATERMARK > 0
extern void uart_rx_data(void);
#endif

static struct cbuf rxcb;
static uint8_t rxbuf[UART_CFG_RX_BUF_LEN];

/**
 *	@ingroup api_uart
 *	@brief		Initializes and configures the UART module.
 *	@param[in]	baudrate	the baud rate of the UART, i.e.: 9600, 115200, etc.
 *	@param[in]	config  	a byte containing the configuration masks for the 
 *						  	UART. See the \ref macros_uart for more information.
 *	@retval		0			on success.
 *	@retval 	EDOM		invalid uint32_t parameter (the baud rate value is
 *							out of range)
 */
int uart_config(uint32_t baudrate, uint8_t config)
{
	uint8_t reg = 0;
	uint16_t baud_reg;

	SCGC1_SCI1 = 1;		/* Enable clocks for SCI1 module */
	
	baud_reg = uart_get_scibd(baudrate);
	if (baud_reg == 0xffff)
		return -EDOM;
	SCI1BD = baud_reg;

	if (config & UART_CFG_PARITY_EN)
		reg |= (config & UART_CFG_PARITY_MASK) >> 0;
	if (config & UART_CFG_BITS_9)
		reg |= SCI1C1_M_MASK;
	
	SCI1C1 = reg;
	SCI1C3 = 0;
	SCI1S2 = 0;
	SCI1C2 = SCI1C2_RE_MASK | SCI1C2_TE_MASK | SCI1C2_RIE_MASK;

	/* Configure GPIOs, accordingly to the selected mode*/
#ifdef UART_CFG_RTS_XPIN
	gpio_config(UART_CFG_RTS_XPIN, GPIO_CFG_OUTPUT);
	gpio_set(UART_CFG_RTS_XPIN, 0);
#endif
#ifdef UART_CFG_CTS_XPIN
	gpio_config(UART_CFG_CTS_XPIN, GPIO_CFG_INPUT);
#endif

	/* Setup the RX circular buffer */
	cbuf_init(&rxcb, rxbuf, UART_CFG_RX_BUF_LEN);
	
	return 0;
}

/**
 *  @ingroup api_uart
 *	@brief		Writes an array of bytes to the UART.
 *	@param[in]	buf  	buffer containing the bytes to be written.
 *	@param[in]	len		number of bytes to write from the buffer.
 *	@retval		size_t	number of bytes that where written.
 */
size_t uart_write(const void *buf, size_t len)
{
	size_t sent = len;

#if defined(UART_CFG_MODE_3W)
	gpio_set(UART_CFG_RTS_XPIN, 1);
#endif		
	
	while (len--) {
		/**
		 * TO_DO exit after a timeout? 
		 * TO_DO reset the watchdog? 
		 */
#if defined(UART_CFG_MODE_4W)
		while (gpio_get(UART_CFG_CTS_XPIN))
			sys_watchdog_reset();
#endif
		while (!SCI1S1_TDRE)
			;
		if (SCI1C1_M) {
			/* 9 bits */
			SCI1C3_T8 = *((uint8_t *)buf)++ & 0x01;
			len--;
		}
		SCI1D = *((uint8_t *)buf)++;
	}
	
#if defined(UART_CFG_MODE_3W)
	while (!SCI1S1_TC)
		;
	gpio_set(UART_CFG_RTS_XPIN, 0);
#endif
	return sent;
}

/**
 *	@ingroup api_uart
 *	@brief		Returns the number of bytes that are available to
  *				be read from the RX buffer of the UART.
 *	@retval		size_t		the number of bytes contained in the RX buffer.
 */
size_t uart_bytes_in_rx_buffer(void)
{
	return (size_t)cbuf_data_in_buf(&rxcb);
}

/**
 *	@ingroup api_uart
 *	@brief		Reads the specified number of bytes from the RX buffer of the 
 *				UART.
 *	@param[out]	buf  		buffer where the read bytes will be stored.
 *	@param[in]	len			number of bytes to read from the RX buffer of the 
 *							UART.
 *	@retval		size_t		the number of bytes read.
 */
size_t uart_read(void *buf, size_t len)
{
	size_t read = 0, available;
	
	available = cbuf_data_in_buf(&rxcb);
	if (available > len)
		available = len;

	while (read < available) {
		*((uint8_t *)buf)++ = cbuf_get_nocheck(&rxcb);
		read++;
	}
	return read;
}

#pragma TRAP_PROC
/**
 *	@ingroup api_uart
 *	@brief	On reception interrupt service routine of the UART module. Called 
 *			when any data or error is received by the UART.
 *	@param	None.
 *	@retval	None.
 */
void uart_isr(void)
{
	uint8_t status, rdata;
#if defined ENABLE_WAKEUP_FROM_UART
	extern uint8_t wakeup_irq;
	
	if (SCI1S2_RXEDGIF) {
		SCI1S2_RXEDGIF = 1;
		if (wakeup_irq == WAKEUP_UNKNOWN)
			wakeup_irq = WAKEUP_UART;
		return;
	}
#endif
	/* Read status info and the data register to ack the interrupt */
	status = SCI1S1;
	rdata = uart_get_rx_byte();
	if (status & UART_STAT_ERROR_MASK) {
		/* TO_DO update uart stats */
		return;
	}
	
	cbuf_append(&rxcb, rdata);

#if (UART_CFG_RX_WATERMARK > 0) && (ENABLE_STDIO_PRINTF_SCANF == 0) 
	/* Call the callback when we have enough data */
	if (cbuf_data_in_buf(&rxcb) >= UART_CFG_RX_WATERMARK)
		uart_rx_data();
#endif	
}

#if (ENABLE_STDIO_PRINTF_SCANF == 1)

void TERMIO_PutChar(char c)
{
	if (c == '\n') {
		(void)uart_write("\r\n", 2);
	} else {
		(void)uart_write(&c, 1);
	}
}
 
char TERMIO_GetChar(void)
{
	char rdata;
	
	while (!uart_read(&rdata, 1))
		;
	return rdata;
}

#endif /* ENABLE_STDIO_PRINTF_SCANF */
#else
void uart_isr(void) {}
#endif /* ENABLE_UART */

#ifdef ENABLE_RADIO_UART

#include "xbee/serial.h"
#include "xbee/cbuf.h"

#define RADIO_UART_CFG_RX_WATERMARK		1
/* RX BUF LEN must be a power of 2, minus 1; and at least 15
 * valid settings: 15, 31 63, 127, 255 
 */
#define RADIO_UART_CFG_RX_BUF_LEN		63
#define UART_RADIO_CFG_MODE_4W			1

extern void radio_uart_rx_data(void);

union {
	xbee_cbuf_t		cbuf;
	uint8_t			raw[RADIO_UART_CFG_RX_BUF_LEN + XBEE_CBUF_OVERHEAD];
} ember_rxbuf;

/**
 *	@ingroup api_uart
 *	@brief		Initializes and configures the UART module for the radio chip.
 *	@param[in]	baudrate	the baud rate of the UART, i.e.: 9600, 115200, etc.
 *	@param[in]	config  	a byte containing the configuration masks for the 
 *						  	UART. See the \ref macros_uart for more information.
 *	@retval		0			on success.
 *	@retval 	EDOM		invalid uint32_t parameter (the baud rate value is
 *							out of range)
 */
int radio_uart_config(uint32_t baudrate, uint8_t config)
{
	uint8_t reg = 0;
	uint16_t baud_reg;

	SCGC1_SCI2 = 1;		/* Enable clocks for SCI2 module */
	
	baud_reg = uart_get_scibd(baudrate);
	if (baud_reg == 0xffff)
		return -EDOM;
	SCI2BD = baud_reg;

	/* Parity is determined by ATNB parameter, no parity by default */
	if (config & UART_CFG_PARITY_EN)
		reg |= (config & UART_CFG_PARITY_MASK) >> 0;

	SCI2C1 = reg;
	SCI2C3 = 0;
	SCI2S2 = 0;
	SCI2C2 = SCI2C2_RE_MASK | SCI2C2_TE_MASK | SCI1C2_RIE_MASK;
	
#if defined(UART_RADIO_CFG_MODE_4W)
	PTDDD_PTDDD6 = 0;	/* Configure CTS as input */
	PTCDD_PTCDD1 = 1;	/* Configure RTS as output */
	PTCD_PTCD1 = 0;		/* Set initially to low */
#endif
	
	/* Setup the RX circular buffer */
	xbee_cbuf_init( &ember_rxbuf.cbuf, RADIO_UART_CFG_RX_BUF_LEN);
	EMBER_SERIAL_PORT.rxbuf = &ember_rxbuf.cbuf;
	xbee_ser_open( &EMBER_SERIAL_PORT, baudrate);

	return 0;
}

#if (ENABLE_STDIO_PRINTF_SCANF == 0)
int printf_void(const char * s, ...) {return 0;}
int scanf_void(const char * s, ...) {return 0;}
#endif
#endif