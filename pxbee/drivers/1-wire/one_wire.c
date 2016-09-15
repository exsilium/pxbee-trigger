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

/**	Platform-specific layer provides a consistent 1-Wire API to upper layers
 *	of the driver.
 *	
 *	@ingroup api_1_wire
 *	
 *	@defgroup api_1_wire_driver
 *	
 *	@section api_1_wire_driver_overview 1-Wire API Overview
 *	
 *	1-Wire is a device communications bus system designed by Dallas Semiconductor Corp. 
 *	that provides low-speed data, signaling, and power over a single signal.
 *	
 *	This API contains the functions to configure and control a 1 Wire bus
 *	by bit-banging a GPIO of the programmable XBee devices.
 *
 *	- 1-Wire functions:
 *		- one_wire_reset()
 *		- one_wire_write_byte()
 *		- one_wire_read_byte()
 *		- one_wire_write()
 *		- one_wire_read()
 *		- one_wire_read_rom()
 *		- one_wire_skip_rom()
 *		- one_wire_address()
 *		- one_wire_search()
 *		- one_wire_spp_enable()
 *		- crc_check()
 *	
 */

/* WARNING: This function set won't work properly with system clock @16MHz because minimum
 *  'down-time' is >= 15 u_sec */
#include <xbee_config.h>
#include <one_wire.h>

#ifdef ENABLE_ONE_WIRE
#define READ_ROM_ATTEMPTS 10

/* Bit-Banging timing values for different system clock frequencies*/
#ifdef	SYS_CFG_CLK_48_MHz
#define ONE_WIRE_SAMPLE_WR_DELAY		1
#define ONE_WIRE_SAMPLE_RD_DELAY		3
#define ONE_WIRE_WR_CORRECTION			17
#define ONE_WIRE_RD_CORRECTION			17
#endif

#ifdef	SYS_CFG_CLK_32_MHz
#define ONE_WIRE_SAMPLE_WR_DELAY		1
#define ONE_WIRE_SAMPLE_RD_DELAY		3
#define ONE_WIRE_WR_CORRECTION			28
#define ONE_WIRE_RD_CORRECTION			28
#endif

#ifdef	SYS_CFG_CLK_16_MHz
#define ONE_WIRE_SAMPLE_WR_DELAY		0
#define ONE_WIRE_SAMPLE_RD_DELAY		3
#define ONE_WIRE_WR_CORRECTION			50
#define ONE_WIRE_RD_CORRECTION			50
#endif

#define ONE_WIRE_REMAIN_WR_SLOT		(60 - 1 - ONE_WIRE_SAMPLE_WR_DELAY - ONE_WIRE_WR_CORRECTION)
#define ONE_WIRE_REMAIN_RD_SLOT		(60 - 1 - ONE_WIRE_SAMPLE_RD_DELAY - ONE_WIRE_RD_CORRECTION)

/**
 *	@ingroup api_1_wire_driver
 *	@brief		Initializes and configures the 1-Wire interface.
 *	@retval		0 	on success.
 */
int one_wire_config(void)
{
#ifdef ENABLE_ONE_WIRE_STRONG_PULL_UP
	/* Configure Strong-Pull up pin, if used, as output and disable it */
	gpio_config(XPIN_1_WIRE_STRONG_PULL_UP, GPIO_CFG_OUTPUT);
	one_wire_spp_enable(0);
#endif

	return 0;
}

/**
 *	@ingroup api_1_wire_driver
 *	@brief		Performs a reset on the 1-Wire bus.
 *	@retval		0 	on success.
 *	@retval		<0	if there is an error  
 */
ssize_t one_wire_reset(void)
{
	one_wire_spp_enable(0);
	gpio_set(XPIN_1_WIRE_BUS, 0);
	gpio_config(XPIN_1_WIRE_BUS, GPIO_CFG_OUTPUT);
	sys_udelay(240);
	sys_udelay(220); 
	gpio_config(XPIN_1_WIRE_BUS, GPIO_CFG_INPUT);
	sys_udelay(60);
	
	if (gpio_get(XPIN_1_WIRE_BUS))
		return -ENODEV;
	else {
		sys_udelay(200);
		sys_udelay(200);
		if (!gpio_get(XPIN_1_WIRE_BUS))
			return -ETIMEDOUT; 	/* Bus has been too long at low level, probably timed out */
		else 
			return 0; 			/* Handshake made correctly */
	}
}

/**
 *	@ingroup api_1_wire_driver
 *	@brief		Sends 1 bit over the 1-Wire bus.
 *  @param[in]	bit bit to be transferred.
 *	@retval		0 		on success.
 */
uint8_t one_wire_single_bit_tx(uint8_t bit)
{
	sys_irqs_disable();
	
	gpio_set(XPIN_1_WIRE_BUS, 0);
	gpio_config_dir(XPIN_1_WIRE_BUS, GPIO_CFG_OUTPUT);
	sys_udelay(ONE_WIRE_SAMPLE_WR_DELAY);
	
	if (bit)
		gpio_config_dir(XPIN_1_WIRE_BUS, GPIO_CFG_INPUT);
	
	sys_udelay(ONE_WIRE_REMAIN_WR_SLOT);
	gpio_config_dir(XPIN_1_WIRE_BUS, GPIO_CFG_INPUT);

	sys_irqs_enable();
	
	return 0;
}

/**
 *	@ingroup api_1_wire_driver
 *	@brief		Reads 1 bit from the 1-Wire bus.
 *	@retval		bit read.
 */
uint8_t one_wire_single_bit_rx(void)
{
	ssize_t ret;

	sys_irqs_disable();
	
	gpio_set(XPIN_1_WIRE_BUS, 0);
	gpio_config_dir(XPIN_1_WIRE_BUS, GPIO_CFG_OUTPUT);
	gpio_config_dir(XPIN_1_WIRE_BUS, GPIO_CFG_INPUT);
	sys_udelay(ONE_WIRE_SAMPLE_RD_DELAY);
	ret = gpio_get(XPIN_1_WIRE_BUS);
	sys_udelay(ONE_WIRE_REMAIN_RD_SLOT);
	
	sys_irqs_enable();
	
	return (uint8_t)ret;
}

/**
 *	@ingroup api_1_wire_driver
 *	@brief		Sends 1 byte over the 1-Wire bus.
 *  @param[in]	byte	byte to be transferred. This may be \ref api_1_wire_driver_macros or device-specific commands.
 *	@retval	int	0 		on success.
 */
ssize_t one_wire_write_byte(uint8_t byte)
{
	uint8_t i, mask = 0x01;
	
	for(i = 0; i < 8; i++, mask <<= 1) {
		one_wire_single_bit_tx(byte & mask);
	}
	
	return 0;
}

/**
 *	@ingroup api_1_wire_driver
 *	@brief		Reads one byte from the 1-Wire bus.
 *  @param[out]	rxbyte	the buffer where the received byte will be stored.
 *	@retval	int	0 		on success.
 */
ssize_t one_wire_read_byte(uint8_t *rxbyte)
{
	uint8_t i, mask;
	
	*rxbyte = 0;
	
	for (i = 0, mask = 0x01; i < 8; i++, mask <<= 1) {
		if (one_wire_single_bit_rx())
			*rxbyte |= mask;
	}

	return 0;
}

/**
 *	@ingroup api_1_wire_driver
 *	@brief		Sends over the 1-Wire bus a buffer with a determined length.
 *  @param[in]	txbuf	the buffer containing the bytes to be transferred.  Frist byte may be \ref api_1_wire_driver_macros or device-specific commands.
 *	@param[in]	len		the number of bytes to be transferred.
 *	@retval	int	0 		on success.
 *	@retval	int	<0		if there is an error while transferring.
 */
ssize_t one_wire_write(const uint8_t *txbuf, uint8_t len)
{
	uint8_t i; 
	
	for (i = 0; (i < len); i++) {
		one_wire_write_byte(txbuf[i]);
	}
	
	return 0;
}

/**
 *	@ingroup api_1_wire_driver
 *	@brief		Reads from the 1-Wire bus determined number of bytes.
 *  @param[out]	rxbuf	the buffer where the received bytes will be stored.
 *	@param[in]	len		the number of bytes to be read.
 *	@retval	int	0 		on success.
 *	@retval	int	<0		if there is an error while reading.
 */
ssize_t one_wire_read(uint8_t *rxbuf, uint8_t len)
{
	uint8_t i;
	ssize_t error = 0;
	
	for (i = 0; (i < len) && !error; i++) {
		error = one_wire_read_byte(rxbuf + i);
	}
	return error;
}

/**
 *	@ingroup api_1_wire_driver
 *	@brief		If there is only one device connected to the 1-Wire bus, reads its ROM code.
 *				This ROM is CRC8 checked before reporting a success.	
 *  @param[out]	romcode	the buffer where the ROM code will be stored.
 *	@retval	int	0 		on success.
 *	@retval	int	<0		if there is an error while reading.
 */
ssize_t one_wire_read_rom(uint8_t *romcode)
{
	ssize_t ret;
	
	ret = one_wire_reset();
	if (ret < 0)
		return ret;
		
	one_wire_write_byte(ONE_WIRE_READ_ROM);
	one_wire_read(romcode, 8);
	return crc_check(romcode, 8);
}

/**
 *	@ingroup api_1_wire_driver
 *	@brief		Used when only one device is connected to the 1-Wire bus, so sending 32-bit
 *				ROM code is unnecessary. 
 *				Usually used after a one_wire_reset() command.
 *	@retval	ssize_t	0 		on success.
 *	@retval	ssize_t	<0		if there is an error while reading.
 */
ssize_t one_wire_skip_rom(void)
{	
	return one_wire_write_byte(ONE_WIRE_SKIP_ROM);
}

/**
 *	@ingroup api_1_wire_driver
 *	@brief		Used for addressing a specific device connected to the 1-Wire bus. 
 *				Usually used after a one_wire_reset() command.
 *	@param[in] romcode the ROM code of the device to be addressed.
 *	@retval	ssize_t	0 		on success.
 *	@retval	ssize_t	<0		if there is an error.
 */
ssize_t one_wire_address(uint8_t *romcode)
{
	ssize_t ret;

	ret = one_wire_write_byte(ONE_WIRE_MATCH_ROM);
	if (ret < 0)
		return ret;

	ret = one_wire_write(romcode, 8);
	if (ret < 0)
		return ret;

	return 0;
}

/**
 *	@ingroup api_1_wire_driver
 *	@brief		Performs a CRC (Cyclic Redundancy Check) over a buffer.
 *  @param[in]	buffer	the buffer which will be checked.
 *	@param[in]	len		the number of bytes to be considered.
 *	@retval	int			the CRC result.
 */
uint8_t crc_check(uint8_t *buffer, uint8_t len)
{
	uint8_t i = 0, crc = 0, xor = 0, bit, byte;
	
	while (i < len) {
		byte = buffer[i++];
		for (bit = 0; bit < 8; bit++) {
			xor = (byte ^ crc) & 0x01;
			byte >>= 1; 
			crc >>= 1;
			if (xor)
				crc ^= 0b10001100;
		}
	}
	
	return crc;
}

/**
 *	@ingroup api_1_wire_driver
 *	@brief		Performs the 1-Wire search algorithm and store ROM codes found.
 *  @param[in]	rombuf	the buffer where ROM codes will be stored (should be big enough 
 *  					to store maximum number of devices (e.g.: rombuf[8 * len]).
 *	@param[in]	len		the maximum number of device that can be found.
 *	@retval		int		number of devices found.
 *	@retval		<0		if there is any error while looking for devices. 
 */
ssize_t one_wire_search(uint8_t *rombuf, uint8_t len)
{
	/*****************************************************************
	* This function is based on:                                	 *
	* 1-wire ROM Search routine                                 	 *
	* Comment on: http://www.maxim-ic.com/app-notes/index.mvp/id/187 *
	*                                                           	 * 
	* Robert Jensen                                          		 *
	* robertjensen@verizon.net                                  	 *
	* September 14, 2010                                        	 *
	*                                                           	 *
	*****************************************************************/

	uint8_t path = 0, next, pos, roms_found = 0;    /* decision markers */
	uint8_t count;                                  /* bit count */
	uint8_t bit, chk;                               /* bit values */
	uint8_t byte = 0, i = 0, mask = 0x01;
	ssize_t ret;
	
	do {                                         	/* each ROM search pass */
		ret = one_wire_reset();
		if (ret < 0)
			return ret;

		one_wire_write_byte(ONE_WIRE_SEARCH_ROM);
		next = 0;									/* next path to follow */
	    pos = 1;									/* path bit pointer */
	    count = 0;									/* count the bits */
	    do {                                     	/* each bit of the ROM value */
	    	bit = one_wire_single_bit_rx();
	    	chk = one_wire_single_bit_rx();
			if (bit & chk) 
				return -EIO;						/* collision, both are 1 (this shouldn't happen)*/
			
				if(!bit && !chk){					/* collision, both are zero */
					if (pos & path)
						bit = 1;					/* if we've been here before */
					else 
						next = (path & (pos-1)) | pos;   /* else, new branch for next */
					pos <<= 1;
				}

			one_wire_single_bit_tx(bit);
			/* Save bit value */
			if (bit)
				byte |= mask;
			mask <<= 1;
			if (mask == 0x00) {
				rombuf[i++] = byte; 				/*save byte*/
				byte = 0;
				mask = 0x01;
			}
			count++;
	    }while(count < 64);
	/* Check the just-completed ROM value */
	if (!crc_check(rombuf + roms_found * 8, 8))
		roms_found++;
	else
		i -= 8; 									/* if CRC failed, start again*/

	path = next;		
	} while(path && (i < (len * 8)));

	return roms_found;
}
#endif /* ENABLE_ONE_WIRE */
