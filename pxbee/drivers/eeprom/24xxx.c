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
/**	Platform-specific layer provides a consistent Virtual EEPROM API to upper 
 *	layers of the driver.
 *	
 *	@ingroup api_24xxx_eeprom
 *	
 * 	@defgroup api_24xxx_eeprom EEPROM
 *	
 *	@section eeprom_section EEPROM API Overview
 *	
 *	This API contains the functions to initialize and control \b 24xxx family 
 *	of EEPROMs (24C08/24C64/24C128) for the Programmable XBee devices.
 *	These EEPROMs are user-modifiable read-only memories (ROM) that are 
 *	connected to the XBee modules trough the I2C interface. They can be 
 *	erased and reprogrammed (written to) repeatedly.
 *	
 *	- 24xxx EEPROM configuration functions:
 *		- eeprom_init()
 *	
 *	- Functions to read/write the 24xxx EEPROMs:
 *		- eeprom_read()
 *		- eeprom_write()
 */

#include <types.h>
#include <errno.h>
#include <i2c.h>
#include <rtc.h>
#include <string.h>

#ifdef ENABLE_24XXX_EEPROM

#define EEPROM_FAMILY_ADDR		0x50

/// \cond
uint8_t g_slaveaddr[EEPROM_24XXX_NUM];
uint8_t g_addrbytes[EEPROM_24XXX_NUM];
uint8_t g_pagesize[EEPROM_24XXX_NUM];
/// \endcond

/**
 *	@ingroup api_24xxx_eeprom
 *	@brief		Configures the EEPROM.
 *	@param[in]	eeprom	 	eeprom index to configure (use the name of the component defined by the config.xml)
 *	@param[in]	subaddr		EEPROM slave subaddress range from 0 (0x50) to 7 (0x57) depending on hardware configuration.
 *	@param[in]	addrbytes	Required address bytes for the eeprom.
 *	@param[in]	pagesize	Device page size for writing operations.
 *	@retval		0  		on success.
 *	@retval 	EINVAL invalid parameter.
 */
int eeprom_24xxx_config(eeprom_24xxx_t eeprom, uint8_t subaddr, uint8_t addrbytes, uint8_t pagesize)
{	
	if (subaddr > 7)
		return -EINVAL;
		
	if (addrbytes < 1 || addrbytes > 3)
		return -EINVAL;
	
	if (!pagesize)
		return -EINVAL;
		
	g_slaveaddr[eeprom] = EEPROM_FAMILY_ADDR + subaddr;
	g_addrbytes[eeprom] = addrbytes;
	g_pagesize[eeprom] = pagesize;
	return 0;
}

/**
 *	@ingroup api_24xxx_eeprom
 *	@brief			Reads the specified number of bytes from the EEPROM.
 *	@param[in]		eeprom	eeprom to handle (use the name of the component defined by the config.xml)
 *	@param[out]		buf		buffer where the read bytes will be stored.
 *	@param[in]		addr	address of the EEPROM to start reading from.
 *	@param[in]		len		number of bytes to read from the EEPROM.
 *	@retval 		ssize_t	the number of bytes read.
 *	@retval			ERANGE	out of range.
 *	@retval 		<0		if there is an error while reading the EEPROM.
 */
ssize_t eeprom_24xxx_read(eeprom_24xxx_t eeprom, void *buf, uint32_t addr, size_t len)
{
	uint8_t address[3];
	ssize_t ret;

	if (!g_addrbytes[eeprom])
		return -ERANGE;
	
	if (g_addrbytes[eeprom] == 1) {
		address[0] = (uint8_t)addr;
	} else if (g_addrbytes[eeprom] == 2) {
		address[0] = (uint8_t)(addr >> 8);
		address[1] = (uint8_t)addr;
	} else {
		address[0] = (uint8_t)(addr >> 16);
		address[1] = (uint8_t)(addr >> 8);
		address[2] = (uint8_t)addr;
	}

	i2c_set_addr(g_slaveaddr[eeprom]);
	
	ret = i2c_write_no_stop(address, g_addrbytes[eeprom]);
	if (ret != g_addrbytes[eeprom])
		return -EIO;

	return i2c_read(buf, len);
}

/**
 *	@ingroup api_24xxx_eeprom
 *	@brief		Writes an array of bytes in the EEPROM.
 *	@param[in]	eeprom	eeprom to handle (use the name of the component defined by the config.xml)
 *	@param[in]	buf		buffer containing the bytes to be written.
 *	@param[in]	addr	address of the EEPROM to start the writing process.
 *	@param[in]	len		number of bytes to write from the buffer.
 *	@retval		ssize_t	number of bytes that where written.
 *	@retval		ERANGE	out of range
 *	@retval		<0		if there is an error while writing in the EEPROM.
 */
ssize_t eeprom_24xxx_write(eeprom_24xxx_t eeprom, void *buf, uint32_t addr, size_t len)
{
	uint8_t pagebuf[EEPROM_24XXX_PAGE_SIZE + 3];	/* data page + address bytes */
	uint8_t chunk, *pbuf;
	size_t ret, written = 0;
	
	if (!g_addrbytes[eeprom])
		return -ERANGE;

	i2c_set_addr(g_slaveaddr[eeprom]);
	
	pbuf = buf;

	while (written < len) {
		if (g_addrbytes[eeprom] == 1) {
			pagebuf[0] = (uint8_t)addr;
		} else if (g_addrbytes[eeprom] == 2) {
			pagebuf[0] = (uint8_t)(addr >> 8);
			pagebuf[1] = (uint8_t)addr;
		} else {
			pagebuf[0] = (uint8_t)(addr >> 16);
			pagebuf[1] = (uint8_t)(addr >> 8);
			pagebuf[2] = (uint8_t)addr;
		}

		chunk = (uint8_t)(((len - written) > g_pagesize[eeprom]) ?
				g_pagesize[eeprom] :
				(len - written));
		memcpy((void *)&pagebuf[g_addrbytes[eeprom]], (const void *)pbuf, (size_t)chunk);
				
		ret = i2c_write(pagebuf, chunk + g_addrbytes[eeprom]);
		if (ret < g_addrbytes[eeprom])
			return ret;
		ret -= g_addrbytes[eeprom];
		written += ret;
		addr += ret;
		pbuf += ret;
		
		delay_ticks(HZ/50);
	}
	return written;
}

#endif /* ENABLE_24XXX_EEPROM */

