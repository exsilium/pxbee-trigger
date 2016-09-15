/****************************************************************************
 * Copyright (C) 2010 - 2015 Digi International Inc, All Rights Reserved.
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
 *	@ingroup api_adc
 *	
 *	@defgroup api_adc
 *	
 *	@section macros_adc ADC Macros
 *
 *	The adc_config() function needs as parameter a byte containing the 
 *	configuration masks for the ADC channels. These masks are defined with 
 *	macros and they are the following:
 *	
 *		- Macros to configure the \b optimization of the ADC channels:
 * 			- \b ADC_CFG_OPTIMIZE_FOR_SPEED 	: Optimizes the ADC channels for
 * 												  speed.
 *			- \b ADC_CFG_OPTIMIZE_FOR_POWER		: Optimizes the ADC channels for
 *												  power saving.
 *	
 *		- Macros to select the \b mode of the ADC channels:
 *			- \b ADC_CFG_MODE_8BIT				: Enables the 8-bits conversion.
 *			- \b ADC_CFG_MODE_10BIT				: Enables the 10-bits conversion.
 *			- \b ADC_CFG_MODE_12BIT 			: Enables the 12-bits conversion.
 *	
 *		- Macros to enable the \b mode \b bit-mask:
 *			- \b ADC_CFG_MODE_BIT_MASK			: Enables the bit mask mode.
 * 
 *	Usage example:
 *	@code adc_config(ADC_CFG_OPTIMIZE_FOR_SPEED | ADC_CFG_MODE_8BIT); 
 *	@endcode
 *	@warning	It is recommended not to use these macros, they are used by 
 *				the XBee Project Smart Editor of the XBee extensions.
 *
 ***************************************************************************/

#ifndef __ADC_H_
#define __ADC_H_

#include <types.h>
#include <hardware.h>

#define ADC_CFG_OPTIMIZE_FOR_SPEED	(0 << 0)
#define ADC_CFG_OPTIMIZE_FOR_POWER	(1 << 0)

#define ADC_CFG_MODE_8BIT			(0 << 2)
#define ADC_CFG_MODE_12BIT			(1 << 2)
#define ADC_CFG_MODE_10BIT			(2 << 2)
#define ADC_CFG_MODE_BIT_MASK		(3 << 2)

#define get_adc_ch(pin)				(((pin) >> ADCCH_SH) & ADCCH_MSK)
#define is_adc_pin(pin)				(get_adc_ch(pin) != 0xf)

#if defined(ENABLE_ADC_XPIN_2) || defined(ENABLE_ADC_XPIN_3) ||		\
	defined(ENABLE_ADC_XPIN_7) || defined(ENABLE_ADC_XPIN_11) ||	\
	defined(ENABLE_ADC_XPIN_13) || defined(ENABLE_ADC_XPIN_17) ||	\
	defined(ENABLE_ADC_XPIN_18) || defined(ENABLE_ADC_XPIN_19) ||	\
	defined(ENABLE_ADC_XPIN_20)
#define ENABLE_ADC
#endif		

#define ADC_CFG						(ADC_CFG_OPTIMIZE | ADC_CFG_MODE_BITS)

/* Function prototypes */
int adc_config(uint8_t config);
int adc_ch_enable(xpin_t pin, bool_t enable);
uint16_t adc_ch_read(xpin_t pin);

#endif /* __ADC_H_ */
