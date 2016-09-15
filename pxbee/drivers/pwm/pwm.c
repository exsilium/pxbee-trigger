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
/**
 *	@ingroup api_pwm
 *	
 *	@defgroup api_pwm
 *	
 *	@section  api_pwm_overview Pulse-Width-Modulation component API Overview
 *	
 *	This API contains the functions to configure and control the
 *	Pulse-Width-Modulation component on programmable XBee devices.
 *	
 *	- Output Compare functions:
 *		- pwm_config()
 *		- pwm_enable()
 *		- pwm_get_period()
 */

#include <pwm.h>

#ifdef ENABLE_PWM
/**
 *	@ingroup api_pwm
 *	@brief		Function that configures the settings of the Pulse-Width-Modulation
 *              module.
 *	@param[in]	pin 	pin to be configured.
 *	@param[in]	enable 	TRUE for enabling, FALSE for disabling the PWM on pin.
 *	@param[in]	ton		time (in microseconds) that the pulse will stay at positive
 *						state.
 *	@param[in]	period	period (in microseconds) of the waveform.
 */
int pwm_config(xpin_t pin, bool_t enable, uint32_t ton, uint32_t period)
{
	tpm_t tpm = xpin_get_tpm(pin);
	uint8_t channel = xpin_get_tpm_ch(pin);

	if (!xpin_has_tpmch(pin))
		return -EINVAL;
	
	REG_TPMSC(tpm) = 0;
	tpm_clock_gating(tpm, enable);

	if (ton > period)
		return -EINVAL;
	
	/* Config as PWM */
	REG_TPMCSC(tpm, channel) = TPM1C0SC_MS0B_MASK | TPM1C0SC_ELS0B_MASK;
	if (tpm_set_prescaler(tpm, period) < 0)
		return -EOVERFLOW;
	REG_TPMMOD(tpm) = tpm_compute_modulo(REG_TPMSC(tpm), period);
	REG_TPMCV(tpm, channel) = tpm_compute_modulo(REG_TPMSC(tpm), ton);
	
	return 0;
}

/**
 *	@ingroup api_pwm
 *	@brief		Function that changes the positive pulse-width of the
 *				Pulse-Width-Modulation component.
 *	@param[in]	pin 		pin from which the period will be read.
 *	@param[in]	uint32_t	The configured ton (in microseconds)
 *	@retval		-EINVAL		If the pin is not pwm capable. 
 */
uint32_t pwm_set_ton(xpin_t pin, uint32_t ton)
{
	tpm_t tpm = xpin_get_tpm(pin);
	uint8_t channel = xpin_get_tpm_ch(pin);

	if (!xpin_has_tpmch(pin))
		return -EINVAL;
	
	REG_TPMCV(tpm, channel) = tpm_compute_modulo(REG_TPMSC(tpm), ton);

	return 0;
}

/**
 *	@ingroup api_pwm
 *	@brief		Function that returns the current period for the 
 *				Pulse-Width-Modulation component.
 *	@param[in]	pin 		pin from which the period will be read.
 *	@retval		uint32_t	The configured period (in microseconds)
 *	@retval		-EINVAL		If the pin is not pwm capable. 
 */
uint32_t pwm_get_period(xpin_t pin)
{
	tpm_t tpm;
	tpm = xpin_get_tpm(pin);

	if (!xpin_has_tpmch(pin))
		return -EINVAL;

	return tpm_modulo_to_usec(REG_TPMSC(tpm), REG_TPMMOD(tpm));
}

/**
 *	@ingroup api_pwm
 *	@brief		Function that enables/disables the Pulse-Width-Modulation.
 *	@param[in]	pin			Pin (channel) to set PWM status.
 *	@param[in]	enable		TRUE for enabling, FALSE for disabling PWM. 
 *	@retval		0			On success.
 *	@retval		-EINVAL		If the selected pin is not PWM capable.
 */
int pwm_enable(xpin_t pin, bool_t enable)
{
	tpm_t tpm = xpin_get_tpm(pin);
	
	if (!xpin_has_tpmch(pin))
		return -EINVAL;
	tpm_clock_gating(tpm, enable);
	return 0;
}

/**
 *	@ingroup api_pwm
 *	@brief		Function that returns the current positive semiperiod for the 
 *				Pulse-Width-Modulation component.
 *	@param[in]	pin 		pin from which the period will be read.
 *	@retval		uint32_t	The configured period (in microseconds)
 *	@retval		-EINVAL		If the pin is not pwm capable. 
 */
uint32_t pwm_get_ton(xpin_t pin)
{
	tpm_t tpm = xpin_get_tpm(pin);
	uint8_t channel = xpin_get_tpm_ch(pin);

	if (!xpin_has_tpmch(pin))
		return -EINVAL;
	
	return tpm_modulo_to_usec(REG_TPMSC(tpm), REG_TPMCV(tpm, channel));
}
#endif	/* ENABLE_PWM */
