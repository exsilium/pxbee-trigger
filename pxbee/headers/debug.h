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

#ifndef __DEBUG_H_
#define __DEBUG_H_

/* Some debugging macros and constants */
/* Bits 0..3 are reserved for specific use on each module/file */
#define DBG_ERROR		(1 << 7)
#define DBG_WARN		(1 << 6)
#define DBG_NOTICE		(1 << 5)
#define DBG_INFO		(1 << 4)

#undef DBG
#ifdef DEBUG
#define DBG(lvl,x)		do {					\
							if (lvl & dbgmask)	\
								printf x;		\
						} while(0)
#else
#define DBG(lvl,x)
#endif

/*
 * Led debug macros. Used for low level debugging operations.
 * Note that the pin connected to the XBIB leds may vary with the
 * different revisions of the board
 */
#define DBG_LED_0(a)		PTBD_PTBD3 = !(a);			\
							PTBDD_PTBDD3 = 1

#define DBG_LED_1(a)		PTBD_PTBD4 = !(a);			\
							PTBDD_PTBDD4 = 1

#define DBG_LED_2(a)		PTAD_PTAD2 = !(a);			\
							PTADD_PTADD2 = 1

#define DBG_LEDs(a)			DBG_LED_0(a & 1);			\
							DBG_LED_1((a >> 1) & 1);	\
							DBG_LED_2((a >> 2) & 1)

void dump(const uint8_t *data, int len);

#endif /* __DEBUG_H_ */
