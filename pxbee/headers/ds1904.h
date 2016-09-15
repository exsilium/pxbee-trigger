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
/** Platform-specific layer provides a consistent MACROS API to upper layers
 *	of the driver.
 *
 *	@ingroup api_1_wire_components
 *
 *	@defgroup api_1_wire_ds1904
 *
 *	@section api_1_wire_ds1904_macros DS1904 RTC Macros
 *	The DS1904 has 2 specific commands that are defined as the following macros:
 *        - \b DS1904_READ_CLOCK 		: Allows master to read the current time
 *										  value and configuration resgister.
 *        - \b DS1904_WRITE_CLOCK		: Allows master to write time and
 *										  configuration resgiers.
 *  Also there are defined the two combinations of configuration register to
 *  enable or disable internal oscillator:
 *        - \b DS1904_OSC_ENABLE		: Enables RTC oscillator.
 *        - \b DS1904_OSC_DISABLE		: Disables.
*/
#ifndef __DS1904_H_
#define __DS1904_H_
#include <xbee_config.h>
#if defined(ENABLE_DS1904) && defined(ENABLE_ONE_WIRE)
#include <types.h>
#include <xbee_config.h>

#define DS1904_READ_CLOCK	0x66
#define DS1904_WRITE_CLOCK	0x99
#define DS1904_OSC_ENABLE	0x0C
#define DS1904_OSC_DISABLE	0x00

#define JANUARY			31
#define FEBRUARY 		(JANUARY + (28 + is_leap)) /* is_leap is local */
#define MARCH			(FEBRUARY + 31)
#define	APRIL			(MARCH + 30)
#define	MAY				(APRIL + 31)
#define JUNE			(MAY + 30)
#define	JULY			(JUNE + 31)
#define AUGUST			(JULY + 31)
#define	SEPTEMBER		(AUGUST + 30)
#define OCTOBER			(SEPTEMBER + 31)
#define NOVEMBER		(OCTOBER + 30)
#define DECEMBER		(NOVEMBER + 31)
#define IS_LEAP(year)	(((year % 4 == 0) && (year % 100 != 0) || \
						 (year % 400 == 0))? 1 : 0)	

typedef struct {
	uint8_t		sec;
	uint8_t		min;
	uint8_t		hour;
	uint8_t		mday;
	uint8_t		month;
	uint16_t	year;
} tm_rtc_t;

ssize_t ds1904_read(uint8_t *rom, uint8_t *config, uint32_t *time);
ssize_t ds1904_write(uint8_t *rom, uint8_t config, uint32_t time);
ssize_t ds1904_set(uint8_t *rom, bool_t enable);
uint32_t ds1904_date_convert(tm_rtc_t date);
ssize_t ds1904_date_update(uint8_t *rom);
void ds1904_get_date(tm_rtc_t *date);
ssize_t ds1904_check_family_code(uint8_t *rom);

#endif /* defined(ENABLE_DS1904) && defined(ENABLE_ONE_WIRE) */
#endif /* __DS1904_H_ */
