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
/**
 *	@ingroup api_1_wire_components
 *	
 *	@defgroup api_1_wire_ds18b20
 *	
 *	@section api_1_wire_ds18b20_overview DS18B20 API Overview
 *	
 *	This API contains the functions to configure and control a DS18B20 temperature sensor
 *	over a 1-Wire bus.
 *	
 *	- DS18B20 functions:
 *		- ds18b20_config()
 *		- ds18b20_read_temp()
 *		- ds18b20_temp_conv()
 *		- ds18b20_parasite_powered()
 *		- ds18b20_scratchpad_read()
 *		- ds18b20_eeprom_recall()
 *		- ds18b20_scratchpad_copy()
 */
#include <xbee_config.h>
#if defined(ENABLE_DS18B20) && defined(ENABLE_ONE_WIRE)

#include <ds18b20.h>
#include <one_wire.h>

#define DS18B20_RES_9BITS	0b00011111
#define DS18B20_RES_10BITS	0b00111111
#define DS18B20_RES_11BITS	0b01011111
#define DS18B20_RES_12BITS	0b01111111
#define DS18B20_FAMILYCODE	0x28
/**
 *	@ingroup api_1_wire_ds18b20
 *	@brief		Configures resolution and alarm registers of a specific DS18B20.
 *  @param[in]	rom address where ROM of device is stored. NULL if only one device is connected to the 1-Wire bus.
 *  @param[in]	th alarm High Register.
 *  @param[in]	tl alarm Low Register.
 *  @param[in]	resolution resolution to be configured (9, 10, 11 or 12 bits).
 *	@retval		0 	on success.
 *	@retval		<0	if there is any error. 
 */
ssize_t ds18b20_config(uint8_t *rom, int8_t th, int8_t tl, uint8_t resolution)
{
	ssize_t ret;
	uint8_t txbuf[4], config_reg;
			
	switch(resolution) {
	case 9: 	config_reg = DS18B20_RES_9BITS;
				break;
	case 10: 	config_reg = DS18B20_RES_10BITS;
				break;
	case 11:	config_reg = DS18B20_RES_11BITS;
				break;
	case 12:	config_reg = DS18B20_RES_12BITS;
				break;
	default:	config_reg = DS18B20_RES_12BITS; /* Default resolution: 12 bits*/
				break;
	}
	txbuf[0] = DS18B20_SCRPD_WR;
	txbuf[1] = th;
	txbuf[2] = tl;
	txbuf[3] = config_reg;
	
	ret = one_wire_reset();
	if (ret < 0)
		return ret;
	
	if (rom == NULL)
		ret = one_wire_skip_rom();
	else
		ret = one_wire_address(rom);
	if (ret < 0)
		return ret;
	
	ret = one_wire_write(txbuf, sizeof(txbuf));
	if (ret < 0)
		return ret;
	else
		return 0;
}

/**
 *	@ingroup api_1_wire_ds18b20
 *	@brief		Reads temperature registers from DS18B20.
				If device is parasite-powered a strong pull-up is necessary.
 *  @param[in]	rom  address where ROM of device is stored. 
 *              NULL if only one device is connected to the 1-Wire bus.
 *  @param[in]	temperature buffer where read register will be stored.
 *	@retval		0 	on success.
 *	@retval		<0	if there is any error. 
 */
ssize_t ds18b20_read_temp(uint8_t *rom, int16_t *temperature)
{
	uint8_t rbuf[9], i = 0;
	ssize_t ret, parasite;
	
	parasite = (uint8_t)ds18b20_parasite_powered(rom);
	if (parasite < 0)
		return parasite;
	
	ret = one_wire_reset();
	if (ret < 0)
		return ret;
	
	if (rom == NULL)
		ret = one_wire_skip_rom();
	else
		ret = one_wire_address(rom);
	if (ret < 0)
		return ret;
	
	one_wire_write_byte(DS18B20_TEMP_CONV);
	
	if (parasite) {
		one_wire_spp_enable(1); /*Activate strong pullup */
		delay_ticks(HZ);
		one_wire_spp_enable(0);
	} else {
		while(!one_wire_single_bit_rx() && (i++ <= 250))
			delay_ticks(2); /* Wait for temperature conversion to finish*/
		if (i >= 250)
			return -ETIMEDOUT;
	}
	
	ret = ds18b20_scratchpad_read(rom, rbuf);
	if (ret < 0)
		return ret;

	*temperature = ds18b20_temp_conv(rbuf);
	
	return 0;
}

/**
 *	@ingroup api_1_wire_ds18b20
 *	@brief		Performs a conversion of the temperature read from DS18B20.
 *  @param[in]	temp_regs temperature registers (LSB and MSB).
 *	@retval		signed value of temperature multiplied by 100 (2 less significative digits are decimals).
 */
int16_t ds18b20_temp_conv(uint8_t *temp_regs)
{	
	int16_t temperature = 0, tmp;
	bool_t negative;
	
	negative = temp_regs[1] & 0x80;
	tmp = temp_regs[1] * 0x100 + temp_regs[0];
	
	if (negative) 
		tmp = -tmp;
	
	temperature = (tmp >> 4) * 100;
	
	/* Decimal digits */
	if (tmp & 0x08)
		temperature += 50;
	if (tmp & 0x04)
		temperature += 25;
	if (tmp & 0x02)
		temperature += 12;
	if (tmp & 0x01)
		temperature += 6;

	return (negative ? -temperature : temperature);
}

/**
 *	@ingroup api_1_wire_ds18b20
 *	@brief		Checks wether the DS18B20 is parasite powered.
 *  @param[in]	uint8_t	*rom address where ROM of device is stored. NULL if only one device is connected to the 1-Wire bus.
 *	@retval		0 	if device is externally powered.
 *	@retval		1	if device is parasite powered.
 *	@retval		<0	if there is any error. 
 */
ssize_t ds18b20_parasite_powered(uint8_t *rom)
{
	uint8_t byte = 0;
	ssize_t ret;
		
	ret = one_wire_reset();
	if (ret < 0)
		return ret;
		
	if (rom == NULL)
		ret = one_wire_skip_rom();
	else
		ret = one_wire_address(rom);
	if (ret < 0)
		return ret;
	
	one_wire_write_byte(DS18B20_PWR_RD);
	one_wire_read_byte(&byte);
	
	return (byte ? FALSE : TRUE);
}

/**
 *	@ingroup api_1_wire_ds18b20
 *	@brief		Copies data from scratchpad memory (TH, TL and configuration registers) to permanent EEPROM.
 *				If device is parasite-powered a strong pull-up is necessary.
 *  @param[in]	rom address where ROM of device is stored. NULL if only one device is connected to the 1-Wire bus.
 *	@retval		0 	on success.
 *	@retval		<0	if there is any error. 
 */
ssize_t ds18b20_scratchpad_copy(uint8_t *rom)
{
	uint8_t i = 0, parasite;
	ssize_t ret;
		
	parasite = (uint8_t)ds18b20_parasite_powered(rom);
	
	ret = one_wire_reset();
	if (ret < 0)
		return ret;
	
	if (rom == NULL)
		ret = one_wire_skip_rom();
	else
		ret = one_wire_address(rom);
	if (ret < 0)
		return ret;
	
	one_wire_write_byte(DS18B20_SCRPD_CPY);
	
	if (parasite) {
		one_wire_spp_enable(1); /*Activate strong pullup */
		delay_ticks(HZ/8); /* 10 ms max */
		one_wire_spp_enable(0);
	}
	
	return 0;	
}
/**
 *	@ingroup api_1_wire_ds18b20
 *	@brief		Restores data from permanent EEPROM (TH, TL and configuration registers) to scratchpad memory.
 *  @param[in]	rom address where ROM of device is stored. NULL if only one device is connected to the 1-Wire bus.
 *	@retval		0 	on success.
 *	@retval		<0	if there is any error. 
 */
ssize_t ds18b20_eeprom_recall(uint8_t *rom)
{
	uint8_t i;
	ssize_t ret;
		
	ret = one_wire_reset();
	if (ret < 0)
		return ret;
	
	if (rom == NULL)
		ret = one_wire_skip_rom();
	else
		ret = one_wire_address(rom);
	if (ret < 0)
		return ret;
	
	one_wire_write_byte(DS18B20_EEPROM_RCL);
	
	while(!one_wire_single_bit_rx() && i++ < 255)
		sys_udelay(10); /* Wait for recalling process finish */
	
	if (i >= 255)
		return -ETIMEDOUT;
	else
		return 0;
}

/**
 *	@ingroup api_1_wire_ds18b20
 *	@brief		Reads the content of scratchpad memory (temperature, triggers and configuration registers) from DS18B20.
				Data read is CRC8 checked before a success is reported.
 *  @param[in]	rom address where ROM of device is stored. NULL if only one device is connected to the 1-Wire bus.
 *  @param[in]	scratchpad address where content of memory will be stored.
 *	@retval		0 	on success.
 *	@retval		<0	if there is any error. 
 */
ssize_t ds18b20_scratchpad_read(uint8_t *rom, uint8_t *scratchpad)
{
	uint8_t i = 0;
	ssize_t ret;
	
	do {
		ret = one_wire_reset();
		if (ret < 0)
			return ret;
		
		if (rom == NULL)
			ret = one_wire_skip_rom();
		else
			ret = one_wire_address(rom);
		if (ret < 0)
			return ret;
		
		one_wire_write_byte(DS18B20_SCRPD_RD);
		ret = one_wire_read(scratchpad, 9);
		if (ret < 0)
				return ret;
			
	} while (crc_check(scratchpad, 9) && (i++ < DS18B20_MAX_TRIES));
	
	return ( i >= DS18B20_MAX_TRIES ? -ETIMEDOUT : 0);
}

/**
 *	@ingroup api_1_wire_ds18b20
 *	@brief		Verifies that the family code stored in rom first byte belongs to the driver supported device.
				Data read is CRC8 checked before a success is reported.
 *  @param[in]	rom address where ROM of device is stored.
  *	@retval		0 	on success.
 *	@retval		<0	if there is any error. 
 */
ssize_t ds18b20_check_family_code(uint8_t *rom)
{
	if (rom[0] != DS18B20_FAMILYCODE)
		return -ENODEV;

	/* crc is already checked in search and read_rom functions, but do it again anyway */
	if (crc_check(rom, 8))
		return -EILSEQ; /* Invalid ROM */

	return 0;
}

#endif /* defined(ENABLE_DS18B20) && defined(ENABLE_ONE_WIRE) */
	
