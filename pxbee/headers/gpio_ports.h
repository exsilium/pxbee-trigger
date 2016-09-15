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

#ifndef __GPIO_PORTS_H_
#define __GPIO_PORTS_H_

/* 
 * The graphic configuration tool doesn't allow to create components that
 * contain other components making impossible, at the moment, the use of 
 * gpio ports inside other drivers.
 * This header file tries to workaround this limitation by making the 
 * assignation of a free IO port to each component that needs one, allowing
 * the use of the port api on those components.
 */

#ifdef ENABLE_CHAR_LCD
#if !defined(ENABLE_PORT_0)
#define ENABLE_PORT_0
#define CHAR_LCD_DATA_PORT		PORT0
#define PORT0_XPINS				CHAR_LCD_DATA_XPINS
#elif !defined(ENABLE_PORT_1)
#define ENABLE_PORT_1
#define CHAR_LCD_DATA_PORT		PORT1
#define PORT1_XPINS				CHAR_LCD_DATA_XPINS
#elif !defined(ENABLE_PORT_2)
#define ENABLE_PORT_2
#define CHAR_LCD_DATA_PORT		PORT2
#define PORT2_XPINS				CHAR_LCD_DATA_XPINS
#elif !defined(ENABLE_PORT_3)
#define ENABLE_PORT_3
#define CHAR_LCD_DATA_PORT		PORT3
#define PORT3_XPINS				CHAR_LCD_DATA_XPINS
#endif
#endif /* ENABLE_CHAR_LCD */

#endif /* __GPIO_PORTS_H_ */
