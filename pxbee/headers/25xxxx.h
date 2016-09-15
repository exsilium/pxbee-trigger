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
 *	@ingroup api_25xxx_eeprom
 *	@defgroup api_25xxx_eeprom
 *	@section api_25xxx_eeprom_macros 25AA/25LC SPI EEPROMs macros
 *	The 25AA/25LC EEPROMs have 11 commands, which may be used along the eeprom_spi_command() function.
 *	Such commands are defined by the following macros:
 *			-SPI EEPROM 25AA/25LC commands:
 *				- \b EEPROM_WREN 		: Set the write enable latch (enable write operations).
 *				- \b EEPROM_WRITE		: Write data to memory array beginning at selected address.
 *				- \b EEPROM_READ		: Read data from memory array beginning at selected address.
 *				- \b EEPROM_WRDI		: Reset the write enable latch (disable write operations).
 *				- \b EEPROM_RDSR		: Read STATUS register.
 *				- \b EEPROM_WRSR		: Write STATUS register.
 *				- \b EEPROM_PE		: Page Erase - erase one page in memory array.
 *				- \b EEPROM_SE		: Sector Erase - erase one sector in memory array.
 *				- \b EEPROM_CE		: Chip Erase - erase all sectors in memory array.
 *				- \b EEPROM_RDID		: Release from Deep power-down and read electronic signature.
 *				- \b EEPROM_DPD		: Deep Power-Down mode.
 *	
 *	Also, the status-register's bits are defined by the following macros:
 *			-SPI EEPROM 25AA/25LC status register bits:
 *				- \b EEPROM_SR_WIP		: Write-In-Progress bit.
 *				- \b EEPROM_SR_WEL		: Write-Enable-Latch bit.
 *				- \b EEPROM_SR_WPEN		: Write-Protect-Enable bit.
 *				- \b EEPROM_SR_BP		: Block-Protecion bit.
*/
#ifndef __EEPROM_25XXX_H_
#define __EEPROM_25XXX_H_

#include <types.h>

typedef enum eeprom_25xxx {
	EEPROM_SPI_0 = 0,
	EEPROM_SPI_1 = 1,
	EEPROM_SPI_2 = 2,
	EEPROM_SPI_3 = 3,
} eeprom_25xxx_t;

/* Determine Num of 25xxx eeproms in use and Maximum Page Size and address 
 * lenght as the bigger of the defined ones */
#ifdef ENABLE_25XXX_EEPROM

#define EEPROM_25XXX_PAGE_SIZE 		0
#define EEPROM_25XXX_ADDRLEN		0

#ifdef EEPROM_25XXX_0
#if (EEPROM_25XXX_PAGE_SIZE_0 > EEPROM_25XXX_PAGE_SIZE)
#undef EEPROM_25XXX_PAGE_SIZE
#define EEPROM_25XXX_PAGE_SIZE 	EEPROM_25XXX_PAGE_SIZE_0
#endif
#if (EEPROM_25XXX_ADDRESS_BYTES_0 > EEPROM_25XXX_ADDRLEN)
#undef EEPROM_25XXX_ADDRLEN
#define EEPROM_25XXX_ADDRLEN	EEPROM_25XXX_ADDRESS_BYTES_0
#endif
#endif

#ifdef EEPROM_25XXX_1
#if (EEPROM_25XXX_PAGE_SIZE_1 > EEPROM_25XXX_PAGE_SIZE)
#undef EEPROM_25XXX_PAGE_SIZE
#define EEPROM_25XXX_PAGE_SIZE EEPROM_25XXX_PAGE_SIZE_1
#endif
#if (EEPROM_25XXX_ADDRESS_BYTES_1 > EEPROM_25XXX_ADDRLEN)
#undef EEPROM_25XXX_ADDRLEN
#define EEPROM_25XXX_ADDRLEN	EEPROM_25XXX_ADDRESS_BYTES_1
#endif
#endif

#ifdef EEPROM_25XXX_2
#if (EEPROM_25XXX_PAGE_SIZE_2 > EEPROM_25XXX_PAGE_SIZE)
#undef EEPROM_25XXX_PAGE_SIZE
#define EEPROM_25XXX_PAGE_SIZE EEPROM_25XXX_PAGE_SIZE_2
#endif
#if (EEPROM_25XXX_ADDRESS_BYTES_2 > EEPROM_25XXX_ADDRLEN)
#undef EEPROM_25XXX_ADDRLEN
#define EEPROM_25XXX_ADDRLEN	EEPROM_25XXX_ADDRESS_BYTES_2
#endif
#endif

#ifdef EEPROM_25XXX_3
#if (EEPROM_25XXX_PAGE_SIZE_3 > EEPROM_25XXX_PAGE_SIZE)
#undef EEPROM_25XXX_PAGE_SIZE
#define EEPROM_25XXX_PAGE_SIZE EEPROM_25XXX_PAGE_SIZE_3
#endif
#if (EEPROM_25XXX_ADDRESS_BYTES_3 > EEPROM_25XXX_ADDRLEN)
#undef EEPROM_25XXX_ADDRLEN
#define EEPROM_25XXX_ADDRLEN	EEPROM_25XXX_ADDRESS_BYTES_3
#endif
#endif

/* Define missing macros */
#ifndef EEPROM_25XXX_0
#define EEPROM_25XXX_PAGE_SIZE_0		0
#define EEPROM_25XXX_SPI_SS_0			0
#define EEPROM_25XXX_ADDRESS_BYTES_0	0
#endif

#ifndef EEPROM_25XXX_1
#define EEPROM_25XXX_PAGE_SIZE_1		0
#define EEPROM_25XXX_SPI_SS_1			0
#define EEPROM_25XXX_ADDRESS_BYTES_1	0
#endif

#ifndef EEPROM_25XXX_2
#define EEPROM_25XXX_PAGE_SIZE_2		0
#define EEPROM_25XXX_SPI_SS_2			0
#define EEPROM_25XXX_ADDRESS_BYTES_2	0
#endif

#ifndef EEPROM_25XXX_3
#define EEPROM_25XXX_PAGE_SIZE_3		0
#define EEPROM_25XXX_SPI_SS_3			0
#define EEPROM_25XXX_ADDRESS_BYTES_3	0
#endif

/* EEPROM 25AAxxxx commands*/
/* Set the write enable latch (enable write operations) */
#define EEPROM_WREN		0x06
/* Write data to memory array beginning at selected address */
#define EEPROM_WRITE	0x02
/* Read data from memory array beginning at selected address */
#define EEPROM_READ		0x03
/* Reset the write enable latch (disable write operations) */
#define	EEPROM_WRDI		0x04
/* Read STATUS register */
#define	EEPROM_RDSR		0x05
/* Write STATUS register */
#define	EEPROM_WRSR		0x01
/* Page Erase - erase one page in memory array */
#define EEPROM_PE		0x42
/* Sector Erase - erase one sector in memory array */
#define EEPROM_SE		0xD8
/* Chip Erase - erase all sectors in memory array */
#define EEPROM_CE		0xC7
/* Release from Deep power-down and read electronic signature */
#define EEPROM_RDID		0xAB
/* Deep Power-Down mode */
#define EEPROM_DPD		0xB9
/*End of EEPROM 25AAxxxx commands*/

/*Status Register Bits*/
#define EEPROM_SR_WIP	0x01
#define EEPROM_SR_WEL	0x02
#define EEPROM_SR_WPEN	0x80
#define	EEPROM_SR_BP	0x0C /*This includes both Block Protection bits */

#define EEPROM_WRITE_CHUNK_TOUT 100
#define TBD						60 /* Max write/erase page cycle = 6 ms */

/* Function prototypes */
ssize_t eeprom_spi_write_enable(eeprom_25xxx_t eeprom);
ssize_t eeprom_spi_command(eeprom_25xxx_t eeprom, uint8_t *cmd, uint8_t len);
ssize_t eeprom_spi_read_status(eeprom_25xxx_t eeprom);
ssize_t eeprom_spi_write(eeprom_25xxx_t eeprom, uint8_t *data, uint32_t addr,
						 size_t len);
ssize_t eeprom_spi_erase(eeprom_25xxx_t eeprom, uint32_t addr, size_t len);
ssize_t eeprom_spi_read(eeprom_25xxx_t eeprom, void *rxbuf, uint32_t addr,
						size_t len);
#endif /* ENABLE_25XXX_EEPROM */
#endif /* EEPROM_25XXX_H_ */
