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
/**	Platform-specific layer provides a consistent flash API to upper layers
 *	of the driver. 
 *
 *	@ingroup cpu_flash 
 *
 *	@defgroup cpu_flash 
 *
 *	@section flash Flash API Overview 
 *
 *	This API contains some functions to configure and control the on-chip 
 *	nonvolatile memory of the programmable XBee devices. 
 *	
 *	- Flash configuration functions:
 *		- flash_config()
 *	
 *	- Functions to read/write the flash:
 *		- flash_prog()
 *		- flash_prog_byte()
 *		- flash_byte_read()
 *
 *	- Miscellaneous functions:
 *		- flash_erase_page()
 */
#include <system.h>
#include <errno.h>
#include <types.h>
#include <string.h>
#include <flash.h>

#define RDIV_UP(n, d) (((n) + (d) - 1) / (d))

#define ENABLE_FLASH
#ifdef ENABLE_FLASH

/* The max flash clock is 200KHz. It is computed as:
 * If PRDIV8 = 1
 *   Fclk = Fbus / (8 x (DIV + 1))
 * If PRDIV8 = 0
 *   Fclk = Fbus / (DIV + 1)
 */
#define MAX_FLASH_CLK	200000
#if BUS_CLK_FREQ > 10000000
#define FCDIV_VAL	((RDIV_UP(BUS_CLK_FREQ, 8 * MAX_FLASH_CLK) - 1) | 0x40)
#else
#define FCDIV_VAL	(RDIV_UP(BUS_CLK_FREQ, MAX_FLASH_CLK) - 1)
#endif

#if CONFIG_XBEE_FLASH_LEN > 32
#define FL_PAGE_ADDR_MASK		0x3fff
#define FL_GET_PAGE_OFFSET(a)	((a) & FL_PAGE_ADDR_MASK)
#else
#define FL_GET_PAGE_OFFSET(a)	(a)
#endif

#define FL_CMD_BLANK_CHECK		0x05
#define FL_CMD_BYTE_PROGRAM		0x20
#define FL_CMD_BURST_PROGRAM	0x25
#define FL_CMD_PAGE_ERASE		0x40
#define FL_CMD_MASS_ERASE		0x41


/* Flash functions must run from RAM */
#define flash_run_cmd			((uint8_t (*)(uint16_t, uint8_t))( PGM ))
#define flash_set_cmd(a)		PGM[21] = (a)

#pragma MESSAGE DISABLE C1805

/* Array of opcode instructions of the erase/program function in the HCS08 family */
volatile uint8_t PGM[] = {
	0x87,					/* PSHA */
	0xc6, 0x18, 0x25,		/* LDA 0x1825 	; load FSTAT to A */
	0xa5, 0x10,				/* BIT #0x10	; check FACCERR */
	0x27, 0x08,				/* BEQ 0x08		; branch to ret if no error */
	0xc6, 0x18, 0x25,		/* LDA 0x1825	; load FSTAT to A */
	0xaa, 0x10,				/* ORA #0x10	; A or 0x10 */
	0xc7, 0x18, 0x25,		/* STA 0x1825	; write it back to FSTAT */
							/*cont: */
	0x9e, 0xe6, 0x01,		/* LDA 1,SP */
	0xf7,					/* STA ,X */
	0xa6, 0x20,				/* LDA #0x20	; Load the command (dynamically
							 * updated) */
	0xc7, 0x18,	0x26,		/* STA 0x1826	; Write FCMD  */
	0x45, 0x18, 0x25,		/* LDHX #0x1825 ; load FSTAT to A */
	0xf6,					/* LDA ,X */
	0xaa, 0x80,				/* ORA #0x80    ; set FCBEF to run the command */
	0xf7,					/* STA ,X		; store back to FSTAT */
	0x9d,					/* NOP		; wait for 4 cycles */
	0x9d,					/* NOP */
	0x9d,					/* NOP */
	0x9d,					/* NOP */
	0x45, 0x18, 0x25,		/* LDHX #0x1825	; check FACCERR and FPVIOL */
	0xf6,					/* LDA ,X */
	0xf7,					/* STA ,X		; clean FSTAT flags */
	0xf6,					/* LDA ,X */
	0xa5, 0x30,				/* BIT #0x30 */
	0x27, 0x04,				/* BEQ notyet   ; branch to notyet */
	0xa6, 0xff,				/* LDA #0xff    ; return 0xff on error */
	0x20, 0x09,				/* BRA ret */
							/*notyet: */
	0xc6, 0x18, 0x25,		/* LDA 0x1825	; wait until command is completed */
	0xa5, 0x40,				/* BIT #0x40 */
	0x27, 0xf9,				/* BEQ notyet */
	0xa6, 0x00,				/* LDA #0x00    ; return 0 on success */
	0x8a,					/* PULH */
							/*ret: */
	0x81					/* RTS */
};

/**
 *	@ingroup cpu_flash
 *	@brief		Writes an array of bytes in the flash of the module.
 *	@param[in]	addr	address of the flash to start to writing process.
 *	@param[in]	buf		buffer containing the bytes to write in the flash.
 *	@param[in]	len		number of bytes to write from the buffer.
 *	@retval		EIO		access error.
 *	@retval 	ssize_t	the number of bytes that were written.
 */
ssize_t flash_prog(maddr_t addr, uint8_t *buf, size_t len)
{
	ssize_t written = 0;
	int ret = 0;
	uint16_t offset = FL_GET_PAGE_OFFSET(addr);
#if CONFIG_XBEE_FLASH_LEN > 32
	uint8_t savedpage;
#endif
	
	sys_irqs_disable();

#if CONFIG_XBEE_FLASH_LEN > 32
	savedpage = PPAGE;
	PPAGE = (uint8_t)(addr >> 14);
#endif	
	
	flash_set_cmd(FL_CMD_BYTE_PROGRAM);

	/* TO_DO, check that the boundary of flash pages are not passed */
	
	while (len--) {
		ret = (int)flash_run_cmd(offset++, *buf++);
		sys_watchdog_reset();
		if (ret) {
			written = -EIO;
			break;
		}
		written++;
	}

#if CONFIG_XBEE_FLASH_LEN > 32
	PPAGE = savedpage;
#endif	

	sys_irqs_enable();

	return written;
}

/**
 *	@ingroup cpu_flash
 *	@brief		Writes \b one \b byte in the flash of the device.
 *	@param[in]	addr	the address where the byte will be written.
 *	@param[in]	data	the byte to write.
 *	@retval		EIO		access error.
 *	@retval		1		on success.
 */
int flash_prog_byte(maddr_t addr, uint8_t *data)
{
	return flash_prog(addr, data, 1);
}

/**
 *	@ingroup cpu_flash
 *	@brief		Reads \b one \b byte from the flash of the device.
 *	@param[in]	addr	the address to read the byte from.
 *	@retval		uint8_t	the byte read.
 */
uint8_t flash_byte_read(maddr_t addr)
{
#if CONFIG_XBEE_FLASH_LEN > 32
	uint8_t val, savedpage;
	uint16_t offset = FL_GET_PAGE_OFFSET(addr);

	sys_irqs_disable();
	savedpage = PPAGE;
	PPAGE = (uint8_t)(addr >> 14);
	val = *(uint8_t *)offset;
	PPAGE = savedpage;
	sys_irqs_enable();

	return val;
#else
	return *(uint8_t *)addr;
#endif
}

/**
 *	@ingroup cpu_flash
 *	@brief	Erases a \b page of the flash.
 *	@param	addr	the address to start the erasing process.
 *	@retval EOI		access error.
 *	@retval 0		on success.
 */
int flash_erase_page(maddr_t addr)
{
	int ret = 0;
	uint16_t offset = FL_GET_PAGE_OFFSET(addr);
#if CONFIG_XBEE_FLASH_LEN > 32
	uint8_t savedpage;
#endif

	sys_irqs_disable();

#if CONFIG_XBEE_FLASH_LEN > 32
	savedpage = PPAGE;
	PPAGE = (uint8_t)(addr >> 14);
#endif

	flash_set_cmd(FL_CMD_PAGE_ERASE);
	ret = (int)flash_run_cmd(offset, 0);
	if (ret)
		ret = -EIO;
	sys_watchdog_reset();

#if CONFIG_XBEE_FLASH_LEN > 32
	PPAGE = savedpage;
#endif	

	sys_irqs_enable();

	return ret;
}

/**
 *	@ingroup cpu_flash
 *	@brief	Initializes the flash enabling the clock.
 *	@retval 0	on success.
 */
int flash_config(void)
{
	/* Enable the clock for this (Flash) module */
	SCGC2_FLS = 1;
	FCDIV = FCDIV_VAL & 0x7f;
	
	return 0;
}
#endif /* ENABLE_FLASH */

