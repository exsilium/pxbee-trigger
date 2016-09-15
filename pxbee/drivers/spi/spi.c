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
/**	Platform-specific layer provides a consistent SPI API to upper layers
 *	of the driver.
 *	
 *	@ingroup api_spi
 *	
 *	@defgroup api_spi
 *	
 *	@section spi SPI API Overview
 *	
 *	This API contains the functions to configure and control the SPI module 
 *	of the programmable XBee devices. The Serial Peripheral 
 *	Interface Bus is a synchronous serial data link standard named by 
 *	Motorola that operates in full duplex mode. Devices communicate in 
 *	master/slave mode where the master device initiates the data frame. 
 *	Multiple slave devices are allowed with individual slave select (chip 
 *	select) lines.
 *	
 *	- SPI configuration functions:
 *		- spi_config()
 *	
 *	- Functions to read/write the SPI:
*		- spi_transfer()
 */

#include <system.h>
#include <types.h>
#include <spi.h>
#include <gpios.h>
#include <xbee_config.h>

#ifdef ENABLE_SPI_PORT

/* Macros to determine GPIO capability, similar to the ones defined at gpios.c */
#define XPIN_PORT(pin)			((pin) & (PORT_MSK << PORT_SH))
#define XPIN_IS_GPIO(pin)		(XPIN_PORT(pin) != NOGPIO)

static const xpin_t spi0_ss_pins[MAX_SS_SUPPORTED] = {
		SPI0_SS0_PIN,
		SPI0_SS1_PIN,
		SPI0_SS2_PIN,
		SPI0_SS3_PIN
};

static const uint8_t spi0_ss_pin_config[MAX_SS_SUPPORTED] = {
		SPI0_SS0_CONFIG,
		SPI0_SS1_CONFIG,
		SPI0_SS2_CONFIG,
		SPI0_SS3_CONFIG
};

/**
 *	@ingroup api_spi
 *	@brief		Initializes and configures the SPI module of the device.
 *	@param[in]	brpree	baud-rate pre-scaler value. The bus clock of the SPI 
 *						module is divided by (value - 1).
 *	@param[in]	brdiv	baud-rate divider value. The input clock of the SPI 
 *						module is divided by (2 ^ value + 1).
 *	@param[in]	config	a byte containing the configuration masks for the 
 *						SPI interface. See \ref macros_spi for more 
 *						information.
 *	@retval	int	0 		on success.
 */
ssize_t spi_config(uint8_t brpree, uint8_t brdiv, uint8_t config)
{
	uint8_t spic1_reg;
	uint8_t spic2_reg = 0;
	const xpin_t *spi_ss_pins;
	uint8_t i;
	ssize_t ret = -ENODEV;
	
	/* Sanity Check */
	if (brpree <= 8 && brdiv <= 7)
		spi_ss_pins = spi0_ss_pins;
	else
		return -EINVAL; /* Invalid pin */

	/* WARINING: config uses MSB for determine SlaveSelect's logic */
	SCGC2_SPI1 = 1;	/* Enable clocks for SPI1 module */

	spic1_reg = 0x40 | (config & 0x1F);
 
	if (config & SPI_CFG_SS_ENABLE)
		spic2_reg |= 0x10;

	/* Configure and enable SPI interface */
	SPI1BR = (brpree << 4) | (brdiv & 0x0F);
	SPI1C2 = spic2_reg;
	SPI1C1 = spic1_reg;
	ret = 0;

	/* Configure Slave-Select pins as output and de-assert slave-select lines */
	for(i = 0; i < sizeof(spi_ss_pins); i++) {
		if (XPIN_IS_GPIO(spi_ss_pins[i])) {
			gpio_config(spi_ss_pins[i], GPIO_CFG_OUTPUT);
			gpio_set(spi_ss_pins[i], !(config & SPI_CFG_LOGIC_MASK));
		}
	}

	return ret;
}

/**
 *	@ingroup api_spi
 *	@brief		Transfers and receives bytes from the SPI interface. When a 
 *				byte is transferred the function tries to read a byte from 
 *				the SPI interface if the given reception buffer is not NULL.
 *  @param[in]  ss_num  Slave Select number of device. Use 0 if there is no Slave
 *  					Select signal.
 *	@param[in]	txbuf	the buffer containing the bytes to be transferred. If
 *						you only want to receive bytes, configure this parameter 
 *						as NULL.
 *	@param[out]	rxbuf	the buffer where the read bytes will be stored. If you 
 *						only want to transfer an array of bytes, configure 
 *						this parameter as NULL.
 *	@param[in]	len		the number of bytes to be transferred/received
 *	@retval		int		0 on success
 *	@retval		ENODEV	invalid dev_t parameter (the specified device number 
 *						is not correct)
 */
ssize_t spi_transfer(uint8_t ss_num, const void *txbuf, void *rxbuf, size_t len)
{
	size_t transferred = 0;
	uint8_t rxbyte;
	const xpin_t *spi_ss_pins;
	const uint8_t *spi_ss_pin_config;

	if (ss_num < MAX_SS_SUPPORTED) {
		spi_ss_pins = spi0_ss_pins;
		spi_ss_pin_config = spi0_ss_pin_config;
	} else {
		return -EINVAL; /* Invalid pin */
	}
	
	/* Configure the SPI module with device-specific config */
	if (XPIN_IS_GPIO(spi_ss_pins[ss_num])) {
		/* Peripheral config */
		spi_config(SPI0_CFG_PRE_DIV, SPI0_CFG_BAUD_DIV, spi_ss_pin_config[ss_num]); 
		/* Assert the Slave Select */
		gpio_set(spi_ss_pins[ss_num], spi_ss_pin_config[ss_num] & SPI_CFG_LOGIC_MASK);
	} else {
		/* No Slave Select signal. Default SPI config */
		spi_config(SPI0_CFG_PRE_DIV, SPI0_CFG_BAUD_DIV, SPI0_CFG);
	}
	
	while (transferred < len) {
		/* Wait until tx buffer is empty */
		while (!SPI1S_SPTEF)
			;
		/* Transmit real data or dummy (0xff) byte, to just read */
		SPI1D = txbuf ? *((uint8_t *)txbuf)++ : 0xFF;

		/* Wait until rx buffer is full */
		while (!SPI1S_SPRF)
			;
								
		rxbyte = SPI1D;
		if (rxbuf)				
			*((uint8_t *)rxbuf)++ = rxbyte;

		transferred++;
	}

	/* De-assert SlaveSelect if there is Slave Select signal */
	if (XPIN_IS_GPIO(spi_ss_pins[ss_num])) {
		gpio_set(spi_ss_pins[ss_num], ! (spi_ss_pin_config[ss_num] &
										 SPI_CFG_LOGIC_MASK));
	}
	if (!transferred)
		transferred = -ENODEV;	/* Most likely, a wrong dev number */

	return (ssize_t)transferred;
}
#endif /* ENABLE_SPI_PORT */
