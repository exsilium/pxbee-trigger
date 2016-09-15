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
 *	@defgroup api_1_wire_ds1904
 *	
 *	@section api_1_wire_ds1904_overview DS1904 API Overview
 *	
 *	This API contains the functions to configure and control a DS1904 Real-Time-Clock
 *	over a 1-Wire bus.
 *	
 *	- DS1904 functions:
 *		- ds1904_read()
 *		- ds1904_write()
 *		- ds1904_set()
 *		- ds1904_date_convert()
 *		- ds1904_date_update()
 *		- ds1904_get_date()
 */
#include <ds1904.h>
#include <types.h>

#if defined(ENABLE_DS1904) && defined(ENABLE_ONE_WIRE)

#define DS1904_FAMILY_CODE	0x24

static tm_rtc_t ds1904_rtc_now;
/**
 *	@ingroup api_1_wire_ds1904
 *	@brief		Reads configuration and time registers.
 *  @param[in]	rom address where ROM of device is stored. NULL if only one device is connected to the 1-Wire bus.
 *  @param[out]	config address where configuration register will be stored.
 *  @param[out]	time address where time-count register will be stored.
  *	@retval		0 	on success.
 *	@retval		<0	if there is any error. 
 */
ssize_t ds1904_read(uint8_t *rom, uint8_t *config, uint32_t *time)
{
	ssize_t ret;
	uint8_t rxbuf[5], i; 
		
	ret = one_wire_reset();
	if (ret < 0)
		return ret;
	
	if (rom == NULL)
		ret = one_wire_skip_rom();
	else
		ret = one_wire_address(rom);
	if (ret < 0)
		return ret;
	
	ret = one_wire_write_byte(DS1904_READ_CLOCK);
	if (ret < 0)
		return ret;

	ret = one_wire_read(rxbuf, 5);
	if (ret < 0)
		return ret;

	ret = one_wire_reset();
	if (ret < 0)
		return ret;
	
	*config = rxbuf[0];
	*time = 0;

	for (i = 1; i < 5; i++)
		*time |=  (uint32_t)rxbuf[i] << (uint8_t)((i-1) * 8); 
		/* First receive configurationregister, next LSB and last MSB */

	return 0;
}

/**
 *	@ingroup api_1_wire_ds1904
 *	@brief		Writes configuration and time registers.
 *  @param[in]	rom address where ROM of device is stored.  NULL if only one device is connected to the 1-Wire bus.
 *  @param[in]	config configuration register to be written.
 *  @param[in]	time time-count register to be written.
 *	@retval		0 	on success.
 *	@retval		<0	if there is any error. 
 */
ssize_t ds1904_write(uint8_t *rom, uint8_t config, uint32_t time)
{
	ssize_t ret;
	uint8_t txbuf[5], i;
		
	txbuf[0] = config;
	for (i = 1; i < 5; i++)
		txbuf[i] = (uint8_t)(time >> (uint8_t)(8 * (i-1)));
		/* First transfer configuration register, next LSB and last MSB */
	
	ret = one_wire_reset();
	if (ret < 0)
		return ret;
	
	if (rom == NULL)
		ret = one_wire_skip_rom();
	else
		ret = one_wire_address(rom);
	if (ret < 0)
		return ret;
	
	ret = one_wire_write_byte(DS1904_WRITE_CLOCK);
	if (ret < 0)
		return ret;
	
	ret = one_wire_write(txbuf, 5);
	if (ret < 0)
		return ret;
	
	ret = one_wire_reset();
	if (ret < 0)
		return ret;

	return 0;
}

/**
 *	@ingroup api_1_wire_ds1904
 *	@brief		Enables or disables RTC's oscillator maintaining current time value.
 *  @param[in]	rom address where ROM of device is stored. NULL if only one device is connected to the 1-Wire bus.
 *  @param[in]	enable TRUE for enabling and FALSE for disabling.
 *	@retval		0 	on success.
 *	@retval		<0	if there is any error. 
 */
ssize_t ds1904_set(uint8_t *rom, bool_t enable)
{
	uint8_t config;
	uint32_t time;
	ssize_t ret;
	
	ret = ds1904_read(rom, &config, &time);
	if (ret < 0)
		return ret;
	
	if (enable)
		config = 0x0C;
	else
		config = 0x00;
	
	ret = ds1904_write(rom, config, time);
	if (ret < 0)
		return ret;
	
	return 0;
}

/**
 *	@ingroup api_1_wire_ds1904
 *	@brief		Converts a date to epoch time.
 *  @param[in]	date address where ROM of device is stored.
 *	@retval		date in epoch time (0 for 0:00 of 1/1/1970).
 */
uint32_t ds1904_date_convert(tm_rtc_t date)
{
	uint32_t days = 0;
	uint16_t i;
	uint8_t is_leap = IS_LEAP(date.year); /* This is for february macro to work */
	
	if (date.year < 1970)
		return -EINVAL;
	
	switch(date.month) {
	case 1:
		days = date.mday;
		break;
	case 2:
		days = JANUARY + date.mday;
		break;
	case 3:
		days = FEBRUARY + date.mday;
		break;
	case 4:
		days = MARCH + date.mday;
		break;
	case 5:
		days = APRIL + date.mday;
		break;
	case 6:
		days = MAY + date.mday;
		break;
	case 7:
		days = JUNE + date.mday;
		break;
	case 8:
		days = JULY + date.mday;
		break;
	case 9:
		days = AUGUST + date.mday;
		break;
	case 10:
		days = SEPTEMBER + date.mday;
		break;
	case 11:
		days = OCTOBER + date.mday;
		break;
	case 12:
		days = NOVEMBER + date.mday;
		break;
	default:
		return -EINVAL;
	}
	
	for (i = 1970; i < date.year; i++) {
		if (IS_LEAP(i))
			days++; 
	} /* Add extra days due to leap-years from 1970 to desired year */
	
	days += (date.year - 1970) * 365 - 1;
	return date.sec + date.min * 60 + (date.hour + days * 24) * 3600;
}

/**
 *	@ingroup api_1_wire_ds1904
 *	@brief		Reads the RTC time-register and updates global time.
 *  @param[in]	rom address where ROM of device is stored. NULL if only one device is connected to the 1-Wire bus.
 *	@retval		0 	on success.
 *	@retval		<0	if there is any error. 
 */
ssize_t ds1904_date_update(uint8_t *rom)
{
	/* Epoch time is 0:00 on 1-1-1970 */
	uint32_t days, time;
	uint8_t leap_count = 0, is_leap;
	uint16_t i;
	ssize_t ret;

	ret = ds1904_read(rom, NULL, &time);
	if (ret < 0)
		return ret;
	
	ds1904_rtc_now.sec = time % 60;
	ds1904_rtc_now.min = (time / 60) % 60;
	ds1904_rtc_now.hour = (time / 3600) % 24;
	ds1904_rtc_now.year = (uint16_t)(1970 + (time / 3600 / 24 / 365));
	
	is_leap = IS_LEAP(ds1904_rtc_now.year); /* This is for february macro to work */
	
	for (i = 1970; i < ds1904_rtc_now.year; i++) {
		if (IS_LEAP(i))	
			leap_count++;
	}

	days = (time / 3600 / 24) % 365 - leap_count + 1; /* Days from 1st january */

	if (days <= JANUARY) {
		ds1904_rtc_now.month = 1;
		ds1904_rtc_now.mday = (uint8_t)days;
	} else if (days <= FEBRUARY) {
		ds1904_rtc_now.month = 2;
		ds1904_rtc_now.mday = days - JANUARY;
	} else if ( days <= MARCH) {
		ds1904_rtc_now.month = 3;
		ds1904_rtc_now.mday = days - FEBRUARY;
	} else if ( days <= APRIL) {
		ds1904_rtc_now.month = 4;
		ds1904_rtc_now.mday = days - MARCH;
	} else if ( days <= MAY) {
		ds1904_rtc_now.month = 5;
		ds1904_rtc_now.mday = days - APRIL;
	} else if ( days <= JUNE) {
		ds1904_rtc_now.month = 6;
		ds1904_rtc_now.mday = days - MAY;
	} else if ( days <= JULY){
		ds1904_rtc_now.month = 7;
		ds1904_rtc_now.mday = days - JUNE;
	} else if ( days <= AUGUST){
		ds1904_rtc_now.month = 8;
		ds1904_rtc_now.mday = days - JULY;
	} else if ( days <= SEPTEMBER){
		ds1904_rtc_now.month = 9;
		ds1904_rtc_now.mday = days - AUGUST;
	} else if ( days <= OCTOBER){
		ds1904_rtc_now.month = 10;
		ds1904_rtc_now.mday = days - SEPTEMBER;
	} else if ( days <= NOVEMBER){
		ds1904_rtc_now.month = 11;
		ds1904_rtc_now.mday = days - OCTOBER;
	} else if ( days <= DECEMBER){
		ds1904_rtc_now.month = 12;
		ds1904_rtc_now.mday = days - NOVEMBER;
	}

	return 0;
}

/**
 *	@ingroup api_1_wire_ds1904
 *	@brief		Returns current date and time from RTC.
 *  @param[out]	date address where current date will be written.
 *	@retval		void 
 */
void ds1904_get_date(tm_rtc_t *date)
{
	memcpy(date, &ds1904_rtc_now, sizeof(tm_rtc_t));
}

/**
 *	@ingroup api_1_wire_ds18b20
 *	@brief		Verifies that the family code stored in rom first byte belongs to the driver supported device.
 *				Data read is CRC8 checked before a success is reported.
 *  @param[in]	rom address where ROM of device is stored.
 *	@retval		0 	on success.
 *	@retval		<0	if there is any error. 
 */
ssize_t ds1904_check_family_code(uint8_t *rom)
{
	if (rom[0] != DS1904_FAMILY_CODE)
		return -ENODEV;

	/* crc is already checked in search and read_rom functions, but do it again anyway */
	if (crc_check(rom, 8))
		return -EILSEQ; /* Invalid ROM */
	
	return 0;
}
#endif /* defined(ENABLE_DS1904) && defined(ENABLE_ONE_WIRE) */
