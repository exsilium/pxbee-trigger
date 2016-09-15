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
/**	Platform-specific layer provides a consistent I2C API to upper layers
 *	of the driver.
 *	
 * 	@ingroup api_i2c
 * 
 *	@defgroup api_i2c
 *	
 *	@section  XBee I2C API Overview
 *	
 *	This API contains the functions to configure and control the I2C 
 *	communication interface of programmable XBee devices.
 *	The inter-integrated circuit \b (IIC) provides a method of 
 *	communication between a number of devices. The interface is
 *	designed to operate up to 100kbps with maximum bus loading and timing.
 *	
 *	- I2C configuration functions:
 *		- i2c_config()
 *		- i2c_set_addr()
 *		
 *	- Functions to read/write the I2C:
 *		- i2c_write()
 *		- i2c_write_no_stop()
 *		- i2c_read()
 */

#include <system.h>
#include <errno.h>
#include <types.h>
#include <i2c.h>

#ifdef ENABLE_I2C
#define I2C_START_TOUT		60000
#define WRADDR(a)			(a)
#define RDADDR(a)			(a | 0x01)
#define I2C_ACK				0
#define I2C_NACK			1

#define i2c_set_rep_start()	IICC_RSTA = 1
#define i2c_stop()			IICC = 0x80

static uint8_t dev_addr;	/* device physical address */

static int i2c_start(void)
{
	uint16_t timeout = I2C_START_TOUT;

	while (IICS_BUSY && timeout--)
		;
	
	if (!timeout)
		return -EBUSY;
	
	IICC = 0b10110000;   /* + IIC TX and master */
	return 0;
}

static void i2c_restore(void)
{
	/* Disable */
	IICC = 0xc0;
	  
	/* ?? send a few clocks and start/stops*/
	(void)i2c_config(0);
}

static int i2c_wr_byte(const uint8_t val)
{
	uint16_t timeout = I2C_START_TOUT;

	IICD = val;
	
	while (!IICS_IICIF && timeout)
		timeout--;

	if (!timeout)
		return -EBUSY;

	/* Clear the flag and check if we have received an ack */
	IICS_IICIF = 1;
	
	return  IICS_RXAK;
}

static int i2c_r_byte(bool_t ack, bool_t first)
{
	uint16_t timeout = I2C_START_TOUT;
	volatile uint8_t val;

	IICC_TXAK = ack;	/* Enable TX ack ? */
	IICC_TX = 0;		/* Enable TX */

	if (first)
		val = IICD;		/* dummy read */
	
	while (!IICS_IICIF && timeout)
		timeout--;

	if (!timeout)
		return -EBUSY;
  
	if (ack)
		i2c_stop();
  
	val = IICD;
	/* Ack the transfer */
	IICS_IICIF = 1;
	/* TO_DO, Check RXACK? */
	
	return (int)val;
}

#define i2c_rd_firstbyte(ack)	i2c_r_byte(ack, 1)
#define i2c_rd_byte(ack)		i2c_r_byte(ack, 0)

/**
 *	@ingroup api_i2c
 *	@brief		Initializes and configures the I2C interface.
 *	@param[in]	config  a byte containing the configuration masks for the I2C 
 *						interface. At the moment this parameter is not used, 
 *						it is reserved for future use.
 *	@retval		0		on success.
 */
int i2c_config(uint8_t config)
{
	config = !config;	/* just to silent the compiler */
	
	/* Enable clocks for the i2c module */
	SCGC1_IIC = 1;
	
	/* TO_DO, revisit and configure based on the bus clock */
	IICF = 0x8f;
	
	/* IICEN = 1, IICIE = 0, MST = 0... */
	IICC = 0x80;

	return 0;
}

/**
 *	@ingroup api_i2c
 *	@brief		Sets the device (chip) i2c physical \b address  
 *	@param[in]	addr	the slave address to be used by the I2C module 
 *						expressed in 7 bits. This means, not left shifted.
 *	@retval		None.
 */
void i2c_set_addr(uint8_t addr) 
{
	dev_addr = addr << 1;
}

static ssize_t __i2c_write(const void *buf, size_t len, uint8_t stop)
{
	int ret;
	ssize_t written = 0;

	ret = i2c_start();
	if (ret)
		goto error_wr;
	
	ret = i2c_wr_byte(WRADDR(dev_addr));
	if (ret)
		goto error_wr;

	while (written < len && ret == 0) {
		ret = i2c_wr_byte(*((uint8_t *)buf)++);
		if (ret < 0)
			goto error_wr;
		written++;
	}

	if (stop)
		i2c_stop();
	
	return written;
	
error_wr:
	i2c_restore();
	return ret;
}

/**
 *	@ingroup api_i2c
 *	@brief		Writes the specified bytes through the I2C interface without 
 *				sending a stop condition at the end of the transfer.
 *	@param[in]	buf		a buffer containing the bytes that will be written.
 *	@param[in]	len		the number of bytes to write from the buffer.
 *	@retval		ssize_t	the number of bytes written on success or the error code
 *           			on failure.
 */
ssize_t i2c_write_no_stop(const void *buf, size_t len)
{
	return __i2c_write(buf, len, 0);
}

/**
 *	@ingroup api_i2c
 *	@brief		Writes the specified bytes through the I2C interface.
 *	@param[in]	buf		buffer containing the bytes that will be written.
 *	@param[in]	len		the number of bytes to write from the buffer.
 *	@retval		ssize_t	the number of bytes written on success or the error code
 *						on failure.
 */
ssize_t i2c_write(const void *buf, size_t len)
{
	return __i2c_write(buf, len, 1);
}

/**
 *	@ingroup api_i2c
 *	@brief		Reads the specified number of bytes from the I2C interface.
 *	@param[out]	buf		the buffer where the read bytes will be stored.
 *	@param[in]	len		the number of bytes to read.
 *	@retval		ssize_t	the number of bytes read on success or the error code
 *						on failure.
 */
ssize_t i2c_read(void *buf, size_t len)
{
	int ret;
	ssize_t read = 0;
	
	i2c_set_rep_start();

	ret = i2c_wr_byte(RDADDR(dev_addr));
	if (ret)
		goto error_rd;

    ret = i2c_rd_firstbyte(I2C_ACK);
    if (ret < 0)
		goto error_rd;
    *((uint8_t *)buf)++ = (uint8_t)ret;
    read++;
    
    while ( (read < (len - 1) )) {
		ret = i2c_rd_byte(I2C_ACK);
		if (ret < 0)
			goto error_rd;
		*((uint8_t *)buf)++ = (uint8_t)ret;
		read++;
    }

    ret = i2c_rd_byte(I2C_NACK);
	if (ret < 0)
		goto error_rd;

	if (read < len) {
		*((uint8_t *)buf)++ = (uint8_t)ret;
		read++;
	}
	
	i2c_stop();
	return read;
	
error_rd:
	i2c_restore();
	return ret;
}
#endif /* ENABLE_I2C */
