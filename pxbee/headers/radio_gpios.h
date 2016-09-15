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
#ifndef __RADIO_GPIO_H_
#define __RADIO_GPIO_H_

#include <xbee_config.h>

/* Pull-Direction and Pull-Resistor bit shifting for each XPIN according to
 * Datasheet */
#ifdef CONFIG_XBEE_THT

#define shift_xpin_4  (1<<10)
#define shift_xpin_6  (1<<11)
#define shift_xpin_7  (1<<12)
#define shift_xpin_9  (1<<6)
#define shift_xpin_11 (1<<0)
#define shift_xpin_13 (1<<9)
#define shift_xpin_15 (1<<8)
#define shift_xpin_17 (1<<1)
#define shift_xpin_18 (1<<2)
#define shift_xpin_19 (1<<3)
#define shift_xpin_20 (1<<4)

#elif defined (CONFIG_XBEE_SMT)
#define shift_xpin_5  (1<<10)
#define shift_xpin_7  (1<<11)
#define shift_xpin_8  (1<<12)
#define shift_xpin_10 (1<<6)
#define shift_xpin_24 (1<<0)
#define shift_xpin_26 (1<<9)
#define shift_xpin_28 (1<<8)
#define shift_xpin_30 (1<<1)
#define shift_xpin_31 (1<<2)
#define shift_xpin_32 (1<<3)
#define shift_xpin_33 (1<<4)
#endif

/* Pull-Direction and Pull-Resistor null initialization. Will be override by XML
 * configuration */
#ifndef orPD7 
#define orPD7 0 
#endif
#ifndef andPD7
#define andPD7 ~0
#endif
#ifndef orPR7
#define orPR7 0
#endif
#ifndef andPR7
#define andPR7 ~0
#endif

#ifndef orPD8 
#define orPD8 0 
#endif
#ifndef andPD8
#define andPD8 ~0
#endif
#ifndef orPR8
#define orPR8 0
#endif
#ifndef andPR8
#define andPR8 ~0
#endif

#ifndef orPD9 
#define orPD9 0 
#endif
#ifndef andPD9
#define andPD9 ~0
#endif
#ifndef orPR9
#define orPR9 0
#endif
#ifndef andPR9
#define andPR9 ~0
#endif

#ifndef orPD10
#define orPD10 0
#endif
#ifndef andPD10
#define andPD10 ~0
#endif
#ifndef orPR10
#define orPR10 0
#endif
#ifndef andPR10
#define andPR10 ~0
#endif

#ifndef orPD11
#define orPD11 0
#endif
#ifndef andPD11
#define andPD11 ~0
#endif
#ifndef orPR11
#define orPR11 0
#endif
#ifndef andPR11
#define andPR11 ~0
#endif

#ifndef orPD13
#define orPD13 0
#endif
#ifndef andPD13
#define andPD13 ~0
#endif
#ifndef orPR13
#define orPR13 0
#endif
#ifndef andPR13
#define andPR13 ~0
#endif

#ifndef orPD15
#define orPD15 0
#endif
#ifndef andPD15
#define andPD15 ~0
#endif
#ifndef orPR15
#define orPR15 0
#endif
#ifndef andPR15
#define andPR15 ~0
#endif

#ifndef orPD18
#define orPD18 0
#endif
#ifndef andPD18
#define andPD18 ~0
#endif
#ifndef orPR18
#define orPR18 0
#endif
#ifndef andPR18
#define andPR18 ~0
#endif

#ifndef orPD19
#define orPD19 0
#endif
#ifndef andPD19
#define andPD19 ~0
#endif
#ifndef orPR19
#define orPR19 0
#endif
#ifndef andPR19
#define andPR19 ~0
#endif

#ifndef orPD20
#define orPD20 0
#endif
#ifndef andPD20
#define andPD20 ~0
#endif
#ifndef orPR20
#define orPR20 0
#endif
#ifndef andPR20
#define andPR20 ~0
#endif

#ifndef orPD24
#define orPD24 0
#endif
#ifndef andPD24
#define andPD24 ~0
#endif
#ifndef orPR24
#define orPR24 0
#endif
#ifndef andPR24
#define andPR24 ~0
#endif

#ifndef orPD26
#define orPD26 0
#endif
#ifndef andPD26
#define andPD26 ~0
#endif
#ifndef orPR26
#define orPR26 0
#endif
#ifndef andPR26
#define andPR26 ~0
#endif

#ifndef orPD28
#define orPD28 0
#endif
#ifndef andPD28
#define andPD28 ~0
#endif
#ifndef orPR28
#define orPR28 0
#endif
#ifndef andPR28
#define andPR28 ~0
#endif

#ifndef orPD31
#define orPD31 0
#endif
#ifndef andPD31
#define andPD31 ~0
#endif
#ifndef orPR31
#define orPR31 0
#endif
#ifndef andPR31
#define andPR31 ~0
#endif

#ifndef orPD32
#define orPD32 0
#endif
#ifndef andPD32
#define andPD32 ~0
#endif
#ifndef orPR32
#define orPR32 0
#endif
#ifndef andPR32
#define andPR32 ~0
#endif

#ifndef orPD33
#define orPD33 0
#endif
#ifndef andPD33
#define andPD33 ~0
#endif
#ifndef orPR33
#define orPR33 0
#endif
#ifndef andPR33
#define andPR33 ~0
#endif

#endif /* __RADIO_GPIO_H_ */
