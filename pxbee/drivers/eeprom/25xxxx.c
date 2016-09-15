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
 *	@ingroup api_25xxx_eeprom
 *	
 *	@defgroup api_25xxx_eeprom EEPROM
 *	
 *	@section eeprom_section EEPROM API Overview
 *	
 *	This API contains the functions to initialize and control \b 25AAxxxx/25LCxxxx family 
 *	of EEPROMs (25xx010/25xx020/25xx040/25xx080/25xx160/25xx320/25xx640/25xx128/25xx256/25xx512/25xx1024)
 *	of  for the Programmable XBee devices.
 *	These EEPROMs are user-modifiable read-only memories (ROM) that are 
 *	connected to the XBee modules trough the SPI interface. They can be 
 *	erased and reprogrammed (written to) repeatedly.
 *
 *	- Functions to read/write/erase the 25xxx EEPROMs:
 *		- eeprom_spi_write()
 *		- eeprom_spi_erase()
 *		- eeprom_spi_read()
 *		- eeprom_spi_write_enable()
 *		- eeprom_spi_command()
 *		- eeprom_spi_read_status()
 */
#include <types.h>
#include <spi.h>
#include <string.h>
#include <xbee_config.h>
#include <25xxxx.h>

#ifdef ENABLE_25XXX_EEPROM

#define EEPROM_PAYLOAD_OVERHEAD		(eeprom25_addrbytes[eeprom] + 1) /* Address bytes + command */
#define MAX_EEPROM_PAYLOAD_OVERHEAD	(EEPROM_25XXX_ADDRLEN + 1)
#define MAX_EEPROM_SPI_NUM			4

/* Statically defined, existence of SPI_SS_3 doesn't imply existence of 0, 1 and 2 due 
 * to SmartEditor's algorithms */
const uint8_t eeprom25_ss_index[MAX_EEPROM_SPI_NUM] = {
		EEPROM_25XXX_SPI_SS_0,
		EEPROM_25XXX_SPI_SS_1,
		EEPROM_25XXX_SPI_SS_2,
		EEPROM_25XXX_SPI_SS_3
};
const uint8_t eeprom25_addrbytes[MAX_EEPROM_SPI_NUM] = {
		EEPROM_25XXX_ADDRESS_BYTES_0,
		EEPROM_25XXX_ADDRESS_BYTES_1,
		EEPROM_25XXX_ADDRESS_BYTES_2,
		EEPROM_25XXX_ADDRESS_BYTES_3
};
const uint16_t eeprom25_pagesize[MAX_EEPROM_SPI_NUM] = {
		EEPROM_25XXX_PAGE_SIZE_0,
		EEPROM_25XXX_PAGE_SIZE_1,
		EEPROM_25XXX_PAGE_SIZE_2,
		EEPROM_25XXX_PAGE_SIZE_3
};

/**
 *	@ingroup api_25xxx_eeprom
 *	@brief		Sets the Write-Enable Latch in the memory.
 *	@param[in]	eeprom	 	eeprom index to configure (use the name of the component defined by the config.xml)
 *	@retval		<0		if there is an error while writing in the EEPROM.
 */
ssize_t eeprom_spi_write_enable(eeprom_25xxx_t eeprom)
{
	uint8_t cmd = EEPROM_WREN;

	return spi_transfer(eeprom25_ss_index[eeprom], &cmd, NULL, 1);
}

/**
 *	@ingroup api_25xxx_eeprom
 *	@brief		Sends a generic command to the SPI memory.
 *	@param[in]	eeprom	 	eeprom index to configure (use the name of the component defined by the config.xml)
 *	@param[in]	cmd		buffer containing the bytes to be written. This may be one of the \ref api_25xxx_eeprom_macros defined. 
 *	@param[in]	len		number of bytes to write from the buffer.
 *	@retval		<0		if there is an error while writing in the EEPROM.
 */
ssize_t eeprom_spi_command(eeprom_25xxx_t eeprom, uint8_t *cmd, uint8_t len)
{	
	return spi_transfer(eeprom25_ss_index[eeprom], cmd, NULL, len);
}

/**
 *	@ingroup api_25xxx_eeprom
 *	@brief		Reads the status register of the memory.
 *	@param[in]	eeprom	 	eeprom index to configure (use the name of the component defined by the config.xml)
 *	@param[in]	cmd		buffer containing the bytes to be written.
 *	@param[in]	len		number of bytes to write from the buffer.
 *	@retval				Returns the status register.
 *	@retval		<0		if there is an error while writing in the EEPROM.
 */
ssize_t eeprom_spi_read_status(eeprom_25xxx_t eeprom)
{
	/* Reads Status Register from EEPROM memory
	 * returns SR value: WPEN-X-X-X-BP1-BP0-WEL-WIP */
	uint8_t buf[2], cmd[2];
	ssize_t ret;
	
	cmd[0]= EEPROM_RDSR;
	cmd[1]= 0xFF;

	ret = spi_transfer(eeprom25_ss_index[eeprom], cmd, buf, 2);
	if (ret != 2)
		return ret;
	
	return (ssize_t)buf[1];	/* Status register */
}

/**
 *	@ingroup api_25xxx_eeprom
 *	@brief		Writes an array of bytes in the EEPROM.
 *	@param[in]	eeprom	 	eeprom index to configure (use the name of the component defined by the config.xml)
 *	@param[in]	data	buffer containing the bytes to be written.
 *	@param[in]	addr	address of the EEPROM to start the writing process.
 *	@param[in]	len		number of bytes to write from the buffer.
 *	@retval		ssize_t	number of bytes that where written.
 *	@retval		ERANGE	out of range
 *	@retval		<0		if there is an error while writing in the EEPROM.
 */
ssize_t eeprom_spi_write(eeprom_25xxx_t eeprom, uint8_t *data, uint32_t addr, size_t len)
{
	/* Writes 'data' to 'addr' once, Write-In-Process bit from the Status Register
	 * is checked 'attempts' times after writing to ensure the memory is ready for
	 * any other instruction.
	 * If WIP bit is not automatically cleared, returns -1. 
	 * This could mean either the writing cycle is still in progress or there was an error.
	 * Also, Write-Enable-Latch is checked, if  WRITE instruction is successfully executed
	 * this bit is reset automatically. If not cleared, function returns -2 */
	uint8_t timeout = 0;
	ssize_t ret, cur_page_size, chunk, written = 0;
	uint8_t *pdata = data;
	uint8_t eepbuf[EEPROM_25XXX_PAGE_SIZE + MAX_EEPROM_PAYLOAD_OVERHEAD];	/* cmd + addr + data */
	
	while (written < len) {
		eepbuf[0] = EEPROM_WRITE;
		if (eeprom25_addrbytes[eeprom] == 1) {
			eepbuf[1] = (uint8_t)addr;
		} else if (eeprom25_addrbytes[eeprom] == 2) {
			eepbuf[1] = (uint8_t)(addr >> 8);
			eepbuf[2] = (uint8_t)addr;
		} else if (eeprom25_addrbytes[eeprom] == 3) {
			eepbuf[1] = (uint8_t)(addr >> 16);
			eepbuf[2] = (uint8_t)(addr >> 8);
			eepbuf[3] = (uint8_t)addr;
		}

		cur_page_size = eeprom25_pagesize[eeprom];
		cur_page_size -= (int)(addr % eeprom25_pagesize[eeprom]);	/* Adjust page boundary on first loop */
		chunk = len - written;
		if (chunk > cur_page_size)
			chunk = cur_page_size;
		
		memcpy(&eepbuf[eeprom25_addrbytes[eeprom] + 1], pdata, chunk);
		
		ret = eeprom_spi_write_enable(eeprom);
		if (ret < 0)
			return ret;
		
		ret = eeprom_spi_read_status(eeprom);
		if ((ret & EEPROM_SR_WEL) != EEPROM_SR_WEL)
			return -EIO;
		
		ret = spi_transfer(eeprom25_ss_index[eeprom], eepbuf, NULL, chunk + EEPROM_PAYLOAD_OVERHEAD);
		if (ret < 0)
			return ret;

		while (timeout++ < EEPROM_WRITE_CHUNK_TOUT) {
			ret = eeprom_spi_read_status(eeprom);
			if (ret < 0)
				return ret;
			if (!(ret & EEPROM_SR_WIP))
				break;
			sys_udelay(TBD);
		}

		if (timeout >= EEPROM_WRITE_CHUNK_TOUT)
			return -EIO;
		
		timeout = 0;
		written += chunk;
		pdata += chunk;
		addr += chunk;
	}

	ret = eeprom_spi_read_status(eeprom);
	if (ret < 0)
		return ret;
	if (ret & EEPROM_SR_WEL)
		return -EIO;

	return written;
}

/**
 *	@ingroup api_25xxx_eeprom
 *	@brief		Erases an array of bytes in the EEPROM. Erase Page command is used
 *	@param[in]	eeprom	 	eeprom index to configure (use the name of the component defined by the config.xml)
 *	@param[in]	addr	address of the EEPROM to start the erasing process.
 *	@param[in]	len		number of bytes to write from the buffer.
 *	@retval		ssize_t	number of bytes that were erased.
 *	@retval		ERANGE	out of range
 *	@retval		<0		if there is an error while erasing in the EEPROM.
 */
ssize_t eeprom_spi_erase(eeprom_25xxx_t eeprom, uint32_t addr, size_t len)
{
	uint8_t timeout = 0;
	ssize_t ret, cur_page_size, chunk, erased = 0;
	uint8_t eepbuf[MAX_EEPROM_PAYLOAD_OVERHEAD];	/* cmd + addr (maximum overhead)*/
	
	while (erased < len) {
		eepbuf[0] = EEPROM_PE;
		if (eeprom25_addrbytes[eeprom] == 1) {
			eepbuf[1] = (uint8_t)addr;
		} else if (eeprom25_addrbytes[eeprom] == 2) {
			eepbuf[1] = (uint8_t)(addr >> 8);
			eepbuf[2] = (uint8_t)addr;
		} else if (eeprom25_addrbytes[eeprom] == 3) {
			eepbuf[1] = (uint8_t)(addr >> 16);
			eepbuf[2] = (uint8_t)(addr >> 8);
			eepbuf[3] = (uint8_t)addr;
		}

		cur_page_size = eeprom25_pagesize[eeprom];
		cur_page_size -= (int)(addr % eeprom25_pagesize[eeprom]);	// Adjust page boundary on first loop
		chunk = len - erased;
		if (chunk > cur_page_size)
			chunk = cur_page_size;
				
		ret = eeprom_spi_write_enable(eeprom);
		if (ret < 0)
			return ret;
		
		ret = eeprom_spi_read_status(eeprom);
		if ((ret & EEPROM_SR_WEL) != EEPROM_SR_WEL)
			return -EIO;
		
		ret = spi_transfer(eeprom25_ss_index[eeprom], eepbuf, NULL, EEPROM_PAYLOAD_OVERHEAD);
		if (ret < 0)
			return ret;

		while (timeout++ < EEPROM_WRITE_CHUNK_TOUT) {
			ret = eeprom_spi_read_status(eeprom);
			if (ret < 0)
				return ret;
			if (!(ret & EEPROM_SR_WIP))
				break;
			sys_udelay(TBD);
		}

		if (timeout >= EEPROM_WRITE_CHUNK_TOUT)
			return -EIO;
		
		timeout = 0;
		erased += chunk;
		addr += chunk;
	}

	ret = eeprom_spi_read_status(eeprom);
	if (ret < 0)
		return ret;
	if (ret & EEPROM_SR_WEL)
		return -EIO;

	return erased;
}

/**
 *	@ingroup api_25xxx_eeprom
 *	@brief			Reads the specified number of bytes from the EEPROM.
 *	@param[in]		eeprom	eeprom index to configure (use the name of the component defined by the config.xml)
 *	@param[out]		rxbuf	buffer where the read bytes will be stored.
 *	@param[in]		addr	address of the EEPROM to start reading from.
 *	@param[in]		len		number of bytes to read from the EEPROM.
 *	@retval 		ssize_t	the number of bytes read.
 *	@retval			ERANGE	out of range.
 *	@retval 		<0		if there is an error while reading the EEPROM.
 */
ssize_t eeprom_spi_read(eeprom_25xxx_t eeprom, void *rxbuf, uint32_t addr, size_t len)
{
	/* Copies from EEPROM 'len' bytes starting from 'addr'.
	 * Tries to read memory up to 'attempts' times. If successful returns number of bytes read.
	 * Else, returns -1. This would mean that either memory is at a Writing Cycle or is not present. 
	 */
	
	uint8_t timeout = 0, *pdata = rxbuf;
	ssize_t chunk, read = 0, counter = 0, ret;
	uint8_t eepbuf[EEPROM_25XXX_PAGE_SIZE + MAX_EEPROM_PAYLOAD_OVERHEAD]; /* cmd + addr + data */
	
	while (read < len) {
		eepbuf[0] = EEPROM_READ;
		if (eeprom25_addrbytes[eeprom] == 1) {
			eepbuf[1] = (uint8_t)addr;
		} else if (eeprom25_addrbytes[eeprom] == 2) {
			eepbuf[1] = (uint8_t)(addr >> 8);
			eepbuf[2] = (uint8_t)addr;
		} else if (eeprom25_addrbytes[eeprom] == 3) {
			eepbuf[1] = (uint8_t)(addr >> 16);
			eepbuf[2] = (uint8_t)(addr >> 8);
			eepbuf[3] = (uint8_t)addr;
		}
				
		chunk = len - read;
		if (chunk > eeprom25_pagesize[eeprom])
			chunk = eeprom25_pagesize[eeprom];
				
		while (timeout++ < EEPROM_WRITE_CHUNK_TOUT) {
					ret = eeprom_spi_read_status(eeprom);
					if (ret < 0)
						return ret;
					if (!(ret & EEPROM_SR_WIP))
						break;
					sys_udelay(TBD);
				}

		if (timeout >= EEPROM_WRITE_CHUNK_TOUT)
			return -EIO;
		timeout = 0;
		
		ret = spi_transfer(eeprom25_ss_index[eeprom], eepbuf, eepbuf, chunk + EEPROM_PAYLOAD_OVERHEAD);
		
		if (ret < 0)
				return ret;
		
		memcpy(pdata, &eepbuf[eeprom25_addrbytes[eeprom] + 1], chunk);
				
		read  += chunk;
		pdata += chunk;
		addr  += chunk;
	}

	return read;
}
#endif /* ENABLE_25XXX_EEPROM */
