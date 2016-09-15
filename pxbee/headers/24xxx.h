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

#ifndef __EEPROM_24XXX_H_
#define __EEPROM_24XXX_H_

#include <types.h>

typedef enum eeprom_24xxx {
	EEPROM_0,
	EEPROM_1,
	EEPROM_2,
	EEPROM_3,
	EEPROM_4,
	EEPROM_5,
	EEPROM_6,
	EEPROM_7
} eeprom_24xxx_t;

#if defined(EEPROM_24XXX_0) || defined(EEPROM_24XXX_1) ||	\
	defined(EEPROM_24XXX_2) || defined(EEPROM_24XXX_3) ||	\
	defined(EEPROM_24XXX_4) || defined(EEPROM_24XXX_5) ||	\
	defined(EEPROM_24XXX_6) || defined(EEPROM_24XXX_7)
#define ENABLE_24XXX_EEPROM
#endif

/* Determine Num of 24xxx eeproms in use and Maximum Page Size allocation as the
 * bigger of the defined ones */
#define EEPROM_24XXX_NUM		0
#define EEPROM_24XXX_PAGE_SIZE 	0

#if defined(EEPROM_24XXX_0)
#undef EEPROM_24XXX_NUM
#define EEPROM_24XXX_NUM (0 + 1)
#if (EEPROM_24XXX_PAGE_SIZE_0 > EEPROM_24XXX_PAGE_SIZE)
#undef EEPROM_24XXX_PAGE_SIZE
#define EEPROM_24XXX_PAGE_SIZE EEPROM_24XXX_PAGE_SIZE_0
#endif
#endif
#if defined(EEPROM_24XXX_1)
#undef EEPROM_24XXX_NUM
#define EEPROM_24XXX_NUM (1 + 1)
#if (EEPROM_24XXX_PAGE_SIZE_1 > EEPROM_24XXX_PAGE_SIZE)
#undef EEPROM_24XXX_PAGE_SIZE
#define EEPROM_24XXX_PAGE_SIZE EEPROM_24XXX_PAGE_SIZE_1
#endif
#endif
#if defined(EEPROM_24XXX_2)
#undef EEPROM_24XXX_NUM
#define EEPROM_24XXX_NUM (2 + 1)
#if (EEPROM_24XXX_PAGE_SIZE_2 > EEPROM_24XXX_PAGE_SIZE)
#undef EEPROM_24XXX_PAGE_SIZE
#define EEPROM_24XXX_PAGE_SIZE EEPROM_24XXX_PAGE_SIZE_2
#endif
#endif
#if defined(EEPROM_24XXX_3)
#undef EEPROM_24XXX_NUM
#define EEPROM_24XXX_NUM (3 + 1)
#if (EEPROM_24XXX_PAGE_SIZE_3 > EEPROM_24XXX_PAGE_SIZE)
#undef EEPROM_24XXX_PAGE_SIZE
#define EEPROM_24XXX_PAGE_SIZE EEPROM_24XXX_PAGE_SIZE_3
#endif
#endif
#if defined(EEPROM_24XXX_4)
#undef EEPROM_24XXX_NUM
#define EEPROM_24XXX_NUM (4 + 1)
#if (EEPROM_24XXX_PAGE_SIZE_4 > EEPROM_24XXX_PAGE_SIZE)
#undef EEPROM_24XXX_PAGE_SIZE
#define EEPROM_24XXX_PAGE_SIZE EEPROM_24XXX_PAGE_SIZE_4
#endif
#endif
#if defined(EEPROM_24XXX_5)
#undef EEPROM_24XXX_NUM
#define EEPROM_24XXX_NUM (5 + 1)
#if (EEPROM_24XXX_PAGE_SIZE_5 > EEPROM_24XXX_PAGE_SIZE)
#undef EEPROM_24XXX_PAGE_SIZE
#define EEPROM_24XXX_PAGE_SIZE EEPROM_24XXX_PAGE_SIZE_5
#endif
#endif
#if defined(EEPROM_24XXX_6)
#undef EEPROM_24XXX_NUM
#define EEPROM_24XXX_NUM (6 + 1)
#if (EEPROM_24XXX_PAGE_SIZE_6 > EEPROM_24XXX_PAGE_SIZE)
#undef EEPROM_24XXX_PAGE_SIZE
#define EEPROM_24XXX_PAGE_SIZE EEPROM_24XXX_PAGE_SIZE_6
#endif
#endif
#if defined(EEPROM_24XXX_7)
#undef EEPROM_24XXX_NUM
#define EEPROM_24XXX_NUM (7 + 1)
#if (EEPROM_24XXX_PAGE_SIZE_7 > EEPROM_24XXX_PAGE_SIZE)
#undef EEPROM_24XXX_PAGE_SIZE
#define EEPROM_24XXX_PAGE_SIZE EEPROM_24XXX_PAGE_SIZE_7
#endif
#endif




/* Function prototypes */
int eeprom_24xxx_config(eeprom_24xxx_t eeprom, uint8_t subaddr, 
						uint8_t addrbytes, uint8_t pagesize);
ssize_t eeprom_24xxx_read(eeprom_24xxx_t eeprom, void *buf, uint32_t addr,
						size_t len);
ssize_t eeprom_24xxx_write(eeprom_24xxx_t eeprom, void *buf, uint32_t addr,
						size_t len);
#endif /* __EEPROM_24XXX_H_ */
