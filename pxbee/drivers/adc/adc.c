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
 *	Platform-specific layer provides a consistent ADC API to upper layers 
 *	of the driver.
 *
 *	@ingroup api_adc
 *
 *	@defgroup api_adc	
 *
 *	@section adc XBee ADC API Overview
 *	
 *	This API contains the functions to configure and control the ADC channels 
 *	of the programmable XBee modules.
 *  The 12-bit analog to digital converter (ADC12) is a successive 
 *  approximation ADC designer for operation within an integrated 
 *  microcontroller system-on-chip.
 *  
 *	@note	The bandgap channel cannot be converted in low power run mode
 *			or low power wait mode
 *	
 *	- ADC configuration functions:
 *		- adc_config()
 *		- adc_ch_enable()
 *	
 *	- ADC functions to read values:
 *		- adc_ch_read()
 */
#include <system.h>
#include <errno.h>
#include <types.h>
#include <adc.h>

#ifdef ENABLE_ADC
#define ADC_CONV_TOUT		10000

/**
 *	@ingroup api_adc
 *	@brief		Configures the ADC interface settings (all the ADC channels 
 *				will share the same settings.)
 *	@param[in]	config  a byte containing the configuration masks for the 
 *						ADC channels. See the \ref macros_adc for more 
 *						information.
 *	@retval		0 on success
 */
int adc_config(uint8_t config)
{
	uint8_t adccfg = config & ADC_CFG_MODE_BIT_MASK;
	
	SCGC1_ADC = 1;	/* Enable clocks for ADC subsystem */
	ADCSC1 = 0;
	ADCSC2 = 0;
	
	/* Configure ADC optimizing for power or speed */
	if (config & ADC_CFG_OPTIMIZE_FOR_POWER) {
		/**
		 * Configure to optimize for low power, long sample
		 * period, input clock divided by 8 and use bus clock
		 * divided by 2 as input clock 
		 */
		adccfg |= (ADCCFG_ADLPC_MASK | ADCCFG_ADLSMP_MASK | 
				   ADCCFG_ADIV1_MASK | ADCCFG_ADIV0_MASK |
				   ADCCFG_ADICLK0_MASK);
	}
	
	ADCCFG = adccfg;
	return 0;
}

/**
 *	@ingroup api_adc
 *	@brief		Enables or disables the ADC channel running in the specified 
 *				XBee pin.
 * 	@param[in]	pin   	XBee pin configured as ADC channel.
 *	@param[in]	enable	1 to enable the ADC channel, 0 to disable it.
 *	@retval		0		on success
 *	@retval		ERANGE	out of range
 */
int adc_ch_enable(xpin_t pin, bool_t enable)
{
	uint8_t channel;
	
	if (!is_adc_pin(pin))
		return -ERANGE;

	channel = get_adc_ch(pin);
		
	if (channel < 8) {
		if (enable)
			APCTL1 |= (1 << channel);
		else
			APCTL1 &= ~(1 << channel);
	} else if (channel < 10) {
		if (enable)
			APCTL2 |= (1 << (channel - 8));
		else
			APCTL2 &= ~(1 << (channel - 8));
	}
	return 0;
}

/**
 *	@ingroup api_adc
 *	@brief		Reads the value of the ADC channel running in the specified 
 *				XBee pin. 
 *	@param[in]	pin			XBee pin configured as ADC channel to read data 
 *							from.
 *	@retval		uint16_t	the value read from the ADC channel.
 *	@retval 	0xffff		if the XBee pin is not configured as ADC channel 
 *							or there was a timeout error.
 */
uint16_t adc_ch_read(xpin_t pin)
{
	uint16_t timeout = ADC_CONV_TOUT;
	uint8_t channel;

	if (!is_adc_pin(pin))
		return ~0;

	channel = get_adc_ch(pin);

	/* select and enable adc module as one-shot */
	ADCSC1_ADCH = channel;
	
	while (!ADCSC1_COCO && timeout--)
		;

    /* disable adc module */
    ADCSC1_ADCH = 0x1f;
    
	if (!timeout)
		return 0xffff;
  
	return ADCR;
}
#endif /* ENABLE_ADC */
