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
 *	@section api_1_wire_ds18b20_macros DS18B20 Macros
 *	The DS18B20 temperature sensor has 6 specific commands that are defined as
 *	the following macros:
 *     - \b DS18B20_TEMP_CONV: 	Performs a temperature conversion and copies it
 *								to scratchpad memory.
 *     - \b DS18B20_SCRPD_CPY: 	Copies scratchpad memory values to device's
 *								EEPROM (only config, TH and TL registers).
 *     - \b DS18B20_SCRPD_WR: 	Allows the master to write the 3 registers of
 *								the scratchpad memory.
 *     - \b DS18B20_SCRPD_RD: 	Allows the master to read the contents of the
 *								scratchpad.
 *     - \b DS18B20_EEPROM_RCL:	Recalls the alarm trigger and configuration
 *								registers from the EEPROM to scratchpad memory.
 *     - \b DS18B20_PWR_RD: 	Reads power supply (externally or 
 *								parasite-powered).
 */

#ifndef __DS18B20_H_
#define __DS18B20_H_

#if defined(ENABLE_DS18B20) && defined(ENABLE_ONE_WIRE)
#include <types.h>

#define DS18B20_TEMP_CONV	0x44
#define DS18B20_SCRPD_CPY	0x48
#define DS18B20_SCRPD_WR	0x4E
#define DS18B20_SCRPD_RD	0xBE
#define DS18B20_EEPROM_RCL	0xB8
#define DS18B20_PWR_RD		0xB4
#define DS18B20_MAX_TRIES	10

ssize_t ds18b20_config(uint8_t *rom, int8_t th, int8_t tl,uint8_t resolution);
ssize_t ds18b20_read_temp(uint8_t *rom, int16_t *temperature);
int16_t ds18b20_temp_conv(uint8_t *temp_regs);
ssize_t ds18b20_parasite_powered(uint8_t *rom);
ssize_t ds18b20_scratchpad_read(uint8_t *rom, uint8_t *scratchpad);
ssize_t ds18b20_eeprom_recall(uint8_t *rom);
ssize_t ds18b20_scratchpad_copy(uint8_t *rom);
ssize_t ds18b20_check_family_code(uint8_t *rom);

#endif /* defined(ENABLE_DS18B20) && defined(ENABLE_ONE_WIRE) */

#endif /* __DS18B20_H_ */
