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
 *	@ingroup api_virtual_eeprom
 *	
 *	@defgroup api_virtual_eeprom EEPROM
 *	
 *	@section virtual_eeprom_section EEPROM API Overview
 *	
 *	This API contains the functions to control a virtual EEPROM 
 *	implementation over the flash memory of the Programmable XBee devices.
 *	The virtual EEPROM is a user-modifiable read-only memory (ROM) that has 
 *	been implemented over the processor flash. It can be erased and 
 *	reprogrammed (written to) repeatedly.
 *	
 *	- Virtual EEPROM configuration functions:
 *		- veeprom_init()
 *	
 *	- Functions to read/write the Virtual EEPROM:
 *		- veeprom_read()
 *		- veeprom_write()
 *	
 *	- Miscellaneous functions:
 *		- veeprom_get_size()
 */

#include <errno.h>
#include <types.h>
#include <string.h>
#include <flash.h>
#include <veeprom.h>

#ifdef ENABLE_VIRTUAL_EEPROM

#include <debug.h>
#ifdef DEBUG
static uint8_t dbgmask = DBG_ERROR | DBG_WARN | DBG_INFO;
#endif

/* TO_DO, this code should be generalized for more than 2 blocks */
#define VEEPROM_BLOCK_SIZE			FLASH_PAGE_SIZE
#define VEEPROM_NUM_BLOCKS			2
#define VEEPROM_BLOCK_MARK			{'V', 'E', 'E', 'P'}
#define VEEPROM_BL_MARK_LEN			4
#define VEEPROM_ACTBL_OFF			VEEPROM_BL_MARK_LEN
#define VEEPROM_CHCKSUM_OFF			5
#define VEEPROM_DATA_OFF			6
#define VEEPROM_BLOCK_DLEN			(VEEPROM_BLOCK_SIZE - VEEPROM_DATA_OFF)
#define VEEPROM_DATA_LEN			VEEPROM_BLOCK_DLEN
#define VEEPROM_ERASED_BLOCK		0xff
#define	VEEPROM_ACTIVE_BLOCK		0x77
#define	VEEPROM_INACTIVE_BLOCK		0x13

#define	VEEPROM_SEC_PER_BLOCK		(VEEPROM_BLOCK_DLEN / VEEPROM_SECTION_LEN)
#define	VEEPROM_LAST_BLOCK_SEC		(VEEPROM_BL_MARK_LEN + VEEPROM_SECTION_LEN * (VEEPROM_SEC_PER_BLOCK - 1))

#if CONFIG_XBEE_FLASH_LEN > 32
#define	VEEPROM_FLASH_BASE_ADDR		0x1f000
#else
#define	VEEPROM_FLASH_BASE_ADDR		0x8000
#endif

#define	VEEPROM_FLASH_BASE_ADDR0	VEEPROM_FLASH_BASE_ADDR
#define	VEEPROM_FLASH_BASE_ADDR1	(VEEPROM_FLASH_BASE_ADDR + VEEPROM_BLOCK_SIZE)

/* 
 * This should be used for multiple blocks
 * #define VEEPROM_BLOCK_ADDR(b)		(VEEPROM_FLASH_BASE_ADDR + VEEPROM_BLOCK_SIZE * b)
 */
#define VEEPROM_BLOCK_ADDR(b)		(b ? VEEPROM_FLASH_BASE_ADDR1 : VEEPROM_FLASH_BASE_ADDR0)

#if VEEPROM_NUM_BLOCKS > 2
#error "The veeprom code is optimized for only 1 data block"
#error "In order to use more blocks (to increase the VEEPROM size),"
#error "the code must be adapted"
#endif

static int veeprom_erase_block(uint8_t block)
{
	char blockmark[] = VEEPROM_BLOCK_MARK;
	maddr_t eepaddr;
	int ret;
	
	if (block >= VEEPROM_NUM_BLOCKS)
		block = 0;

	eepaddr = VEEPROM_BLOCK_ADDR(block);

	ret = flash_erase_page(eepaddr);
	if (!ret) {
		DBG(DBG_INFO, ("VEEPROM erase 0x%04x\n", eepaddr));
		ret = flash_prog(eepaddr, blockmark, VEEPROM_BL_MARK_LEN);
	}
	return ret;
}

static int veeprom_mark_active(uint8_t block, uint8_t mark)
{
	maddr_t eepaddr;
	
	if (block > VEEPROM_NUM_BLOCKS)
		block = 0;

	eepaddr = VEEPROM_BLOCK_ADDR(block) + VEEPROM_ACTBL_OFF;
	DBG(DBG_INFO, ("VEEPROM marking active page 0x%04x\n", eepaddr));
	
	return (int)flash_prog_byte(eepaddr, &mark);
}

static uint8_t veeprom_get_actblock(void)
{
	uint8_t block = 0;
	char blockmark[] = VEEPROM_BLOCK_MARK;
	maddr_t eepaddr;

	while (block < VEEPROM_NUM_BLOCKS) {
		eepaddr = (maddr_t)VEEPROM_BLOCK_ADDR(block);

		if (memcmp((const void *)eepaddr, 
				   (const void *)blockmark,
				   VEEPROM_BL_MARK_LEN)) {
			/* Just in case the system was powered off before
			 * writing the magic string */
			(void)veeprom_erase_block(block);
		}
		if (VEEPROM_ACTIVE_BLOCK == *((uint8_t *)(eepaddr + VEEPROM_ACTBL_OFF)))
			break;
		block++;
	}
	/* If not found, returns out of range */
	return block;
}

/**
 *	@ingroup api_virtual_eeprom
 *	@brief	Returns the size of the virtual EEPROM.
 *	@param	None
 *	@retval	size_t  the size in bytes of the virtual EEPROM.
 */
size_t veeprom_get_size(void)
{
	return VEEPROM_DATA_LEN;
}

/**
 *	@ingroup api_virtual_eeprom
 *	@brief			Reads the content of \b selected virtual EEPROM
 *	@param[out]		buf  	buffer where the read bytes will be stored.
 *	@param[in]		offset	address of the virtual EEPROM to start reading 
 *							from.
 *	@param[in]		len		number of bytes to read.
 *	@retval			ssize_t the number of bytes read.
 *	@retval			EINVAL	invalid offset parameter.
 */
ssize_t veeprom_read(void *buf, maddr_t offset, size_t len)
{
	uint8_t *eepaddr;
	ssize_t toread, read = 0;

	if (offset >= VEEPROM_DATA_LEN)
		return -EINVAL;
    
	toread = (ssize_t)(VEEPROM_DATA_LEN - offset);
	if (toread > len)
		toread = len;
	
	eepaddr = 
		(uint8_t *)VEEPROM_BLOCK_ADDR(veeprom_get_actblock());
	eepaddr += offset + VEEPROM_DATA_OFF;
		
	while (toread--) {
		*((uint8_t *)buf)++ = *eepaddr++;
		read++;
	}
	return read;
}

/**
 *	@ingroup api_virtual_eeprom
 *	@brief		Writes an array of bytes in the virtual EEPROM.
 *	@param[in]	buf  	buffer containing the bytes to be written.
 *	@param[in]	offset	address of the virtual EEPROM to start the writing 
 *						process.
 *	@param[in]	len		number of bytes to write from the buffer.
 *	@retval		ssize_t number of bytes that were written.
 *	@retval		EINVAL	invalid offset parameter.
 */
ssize_t veeprom_write(const void *buf, maddr_t offset, size_t len)
{
	volatile uint8_t *apaddr, *npaddr;
	ssize_t towrite, written = 0, idx, offsethigh;
	uint8_t newactblock = 0, actblock;

	if (offset >= VEEPROM_DATA_LEN)
		return -EINVAL;
    
	towrite = (ssize_t)(VEEPROM_DATA_LEN - offset);
	if (towrite > len)
		towrite = len;

	/* Check if active block can be (re)used... */
	actblock = veeprom_get_actblock();
	apaddr = (uint8_t *)(VEEPROM_BLOCK_ADDR(actblock));
	apaddr += VEEPROM_DATA_OFF + offset;
	idx = towrite;
	npaddr = buf;
	while (idx--) {
		if (*(uint8_t *)npaddr & ~(*apaddr)) {
			newactblock = 1;
			break;
		}
		npaddr++;
		apaddr++;
	}
	
	if (!newactblock) {
		apaddr = (uint8_t *)(VEEPROM_BLOCK_ADDR(actblock));
		apaddr += VEEPROM_DATA_OFF + offset;
		DBG(DBG_INFO, ("VEEPROM writing to 0x%04x, %d bytes\n", apaddr, towrite));		
		while (towrite--) {
			(void)flash_prog_byte((maddr_t)apaddr++, ((uint8_t *)buf)++);
			written++;
		}
		/* Mark active block */
		(void)veeprom_mark_active(actblock, VEEPROM_ACTIVE_BLOCK);
	} else {
		/* Data must be copied from one sector to the new active flash sector */
		apaddr = (uint8_t *)(VEEPROM_BLOCK_ADDR(actblock)) + VEEPROM_DATA_OFF;
		npaddr = (uint8_t *)(VEEPROM_BLOCK_ADDR(!actblock)) + VEEPROM_DATA_OFF;
		offsethigh = (ssize_t)(offset + len);

		DBG(DBG_INFO, ("VEEPROM writing to 0x%04x, %d bytes\n", npaddr, VEEPROM_DATA_LEN));		
		for (idx = 0; idx < VEEPROM_DATA_LEN; idx++) {
			/* TO_DO check value returned */
			if (idx < offset || idx >= offsethigh) {
				(void)flash_prog_byte((maddr_t)npaddr++, (uint8_t *)apaddr++);
			} else {
				(void)flash_prog_byte((maddr_t)npaddr++, ((uint8_t *)buf)++);
				apaddr++;
			}
		}
		written = towrite;

		/* Mark active block and erase the inactive */
		(void)veeprom_mark_active(!actblock, VEEPROM_ACTIVE_BLOCK);
		(void)veeprom_erase_block(actblock);
	}
	
	return written;
}

/**
 *	@ingroup api_virtual_eeprom
 *	@brief	Initializes the virtual EEPROM in the flash of the device. 
 *	@param	None
 *	@retval	0	on success.
 *	@retval <0	if there is an error in the initialization process.
 */
int veeprom_init(void)
{
	uint8_t block = 0;
	char blockmark[] = VEEPROM_BLOCK_MARK;
	int ret=0;
	
	while (block < VEEPROM_NUM_BLOCKS) {
		if (memcmp((const void *)VEEPROM_BLOCK_ADDR(block), 
				    (const void *)blockmark,
				    VEEPROM_BL_MARK_LEN)) {
			ret = veeprom_erase_block(block);
			if (ret < 0)
				break;
		}
		block++;
	}

	return ret;
}
#endif /* ENABLE_VIRTUAL_EEPROM */
