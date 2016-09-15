/****************************************************************************
 * Copyright (C) 2012 - 2015 Digi International Inc, All Rights Reserved.
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
 *	@ingroup api_1_wire
 *
 *	@defgroup api_1_wire_driver
 *
 *	@section api_1_wire_driver_macros 1-Wire ROM-Commands
 *	The 1-Wire protocol has 5 generic ROM-Commands that may be used with
 *	one_wire_write() and one_wire_write_byte() functions:
 *        - \b ONE_WIRE_READ_ROM 	: Read rom of device (only works when 
 *									  there is a unique device conected to the bus).
 *        - \b ONE_WIRE_MATCH_ROM	: Master will transfer the ROM of desired 
 *									  device, devices with different ROM will
 *									  stay idle.
 *        - \b ONE_WIRE_SEARCH_ROM	: Starts a ROM search over the 1-Wire bus.
 *        - \b ONE_WIRE_SKIP_ROM	: All devices will listen to command
 *									  regardless their ROM, use with care.
 *        - \b ONE_WIRE_AlARM_SEARCH: Similar to search ROM algorithm but only
 *									  devices with a triggered alarm will answer.
 */

#ifndef __ONE_WIRE_2_H_
#define __ONE_WIRE_2_H_

#include <types.h>
#include <hardware.h> 
#include <xbee_config.h>
#ifdef ENABLE_ONE_WIRE

/* 1-Wire ROM Commands */
#define ONE_WIRE_READ_ROM		0x33
#define	ONE_WIRE_MATCH_ROM		0x55
#define	ONE_WIRE_SEARCH_ROM		0xF0
#define	ONE_WIRE_SKIP_ROM		0xCC
#define	ONE_WIRE_AlARM_SEARCH	0xEC

/* Function prototypes */
int one_wire_config(void);
ssize_t one_wire_reset(void);
ssize_t one_wire_write_byte(uint8_t byte);
ssize_t one_wire_read_byte(uint8_t *rxbyte);
ssize_t one_wire_write(const uint8_t *txbuf, uint8_t len);
ssize_t one_wire_read(uint8_t *rxbuf, uint8_t len);
ssize_t one_wire_read_rom(uint8_t *romcode);
ssize_t one_wire_address(uint8_t *romcode);
ssize_t one_wire_skip_rom(void);
uint8_t crc_check(uint8_t *buffer, uint8_t len);
ssize_t one_wire_search(uint8_t *rombuf, uint8_t len);
uint8_t one_wire_single_bit_tx(uint8_t bit);
uint8_t one_wire_single_bit_rx(void);
uint8_t one_wire_strong_pullup(uint8_t enabled);

#ifdef ENABLE_ONE_WIRE_STRONG_PULL_UP
/**
 *	@ingroup api_1_wire_driver
 *	@brief		Activates or deactivates the strong pull-up (if enabled) on the
 *				1-Wire bus.
 *  @param[in]	val 1 for enabling, 0 for disabling.
 *	@retval	none
 */
#if 0
/* This won't compile, is put here so doxygen will index this as a function 
 * (notice it's just a macro definition) 
 */
void one_wire_spp_enable(bool_t val) {} 
#endif
/* Strong-Pull up is a PNP or a P-MOS, so it is enabled by asserting a low-level 
 * and disabled by a high level
 */
#define one_wire_spp_enable(val)	gpio_set(XPIN_1_WIRE_STRONG_PULL_UP, !val)
#else
#define one_wire_spp_enable(val)
#endif

#endif /*ENABLE_ONE_WIRE*/

#endif /* __ONE_WIRE_2_H_ */

