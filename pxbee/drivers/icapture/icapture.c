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
 *	@ingroup api_input_capture
 *	
 *	@defgroup api_input_capture
 *	
 *	@section  api_input_capture_overview Input Capture API Overview
 *	
 *	This API contains the functions to configure and control the Input Capture 
 *	component on programmable XBee devices.
 *	
 *	- Input capture functions:
 *		- icapture_config()
 *		- icapture_get_mode()
 *		- icapture_captcount_to_usec()
 *		- icapture_set_mode()
 *		- icapture_get_mode()
 *		- icapture_irq_enable()
 *		- icapture_enable()
 */
#include <icapture.h>

#ifdef ENABLE_INPUT_CAPTURE

#ifdef CONFIG_XBEE_THT
extern void icapture_irq_xpin4(size_t captcount);
extern void icapture_irq_xpin6(size_t captcount);
extern void icapture_irq_xpin12(size_t captcount);
extern void icapture_irq_xpin17(size_t captcount);
extern void icapture_irq_xpin20(size_t captcount);
#endif /* defined(CONFIG_XBEE_THT) */

#ifdef CONFIG_XBEE_SMT
extern void icapture_irq_xpin5(size_t captcount);
extern void icapture_irq_xpin7(size_t captcount);
extern void icapture_irq_xpin25(size_t captcount);
extern void icapture_irq_xpin26(size_t captcount);
extern void icapture_irq_xpin30(size_t captcount);
extern void icapture_irq_xpin33(size_t captcount);
#endif /* defined(CONFIG_XBEE_SMT) */

/**
 *	@ingroup api_input_capture
 *	@brief		Function that configures the settings of the input-capture
 *              component.
 *	@param[in]	pin pin to be configured.
 *	@param[in]	edge 	edge on which interrupt will be triggered (use defined
 *                      macros).
 *	@param[in]	enable 	TRUE for enabling, FALSE for disabling the input-capture
 *                      IRQ on pin.
 *	@param[in]	max_u_secs 	maximum time in uSeconds for sampling. This is used
 *                          for configuring the prescaler and clock source so
 *                          module can have the maximum resolution that allows
 *                          to reach the max count.	 
 */
int icapture_config(xpin_t pin,  uint8_t edge, bool_t enable, uint32_t max_u_secs)
{
	tpm_t tpm = xpin_get_tpm(pin);
	uint8_t channel = xpin_get_tpm_ch(pin);

	if (!xpin_has_tpmch(pin))
		return -EINVAL;
	
	if (edge != ICAPTURE_RISING &&
		edge != ICAPTURE_FALLING &&
		edge != ICAPTURE_BOTH)
		return -EINVAL;

	tpm_clock_gating(tpm, 1);
	REG_TPMSC(tpm) = 0;
	/* The other bits are 0 for icapture */
	REG_TPMCSC(tpm, channel) = edge << 2;
	REG_TPMMOD(tpm) = 0; /* free-running counter */
	REG_TPMCNT(tpm) = 0;
	icapture_irq_enable(pin, enable);
	if (tpm_set_prescaler(tpm, max_u_secs) < 0)
		return -EOVERFLOW;
	return 0;
}

/**
 *	@ingroup api_input_capture
 *	@brief		Function that computes the number of microseconds from value
 *              captured on an input-capture event.
 *	@param[in]	pin	pin which captured value. This is necesary to determine
 *                  prescaler and clock source.
 *	@param[in]	captcount 	value captured by interrupt.
 *	@retval		number of microseconds. 
 */
uint32_t icapture_captcount_to_usec(xpin_t pin, size_t captcount)
{
	tpm_t tpm = xpin_get_tpm(pin);

	return tpm_modulo_to_usec(REG_TPMSC(tpm), captcount);
}

/**
 *	@ingroup api_input_capture
 *	@brief		Function that sets the active edge of the input-capture pin.
 *	@param[in]	pin			Pin to configure active edge.
 *	@retval		0			if success.
 *	@retval		-EINVAL		If the selected pin is not input-capture capable 
 */
int icapture_set_mode(xpin_t pin, uint8_t mode)
{
	return tpm_set_mode(pin, mode);
}

/**
 *	@ingroup api_input_capture
 *	@brief		Function that returns the programmed active edge of the 
 *              input-capture pin.
 *	@param[in]	pin			Pin to read active edge.
 *	@retval		int			The configured active edge.
 *	@retval		-EINVAL		If the selected pin is not input-capture capable. 
 */
int icapture_get_mode(xpin_t pin)
{
	return tpm_get_mode(pin);
}

/**
 *	@ingroup api_input_capture
 *	@brief		Function that enables/disables the input-capture interrupt.
 *	@param[in]	pin			Pin (channel) to set interrupt.
 *	@param[in]	enable		TRUE for enabling, FALSE for disabling IRQ. 
 *	@retval		0			On success.
 *	@retval		-EINVAL		If the selected pin is not input-capture capable.
 */
int icapture_irq_enable(xpin_t pin, uint8_t enable)
{
	return tpm_irq_enable(pin, enable);
}

/**
 *	@ingroup api_input_capture
 *	@brief		Function that enables/disables the input-capture module.
 *	@param[in]	pin			Pin (channel) to enable/disable.
 *	@param[in]	enable		TRUE for enabling, FALSE for disabling module. 
 *	@retval		0			On success.
 *	@retval		-EINVAL		If the selected pin is not input-capture capable.
 */
int icapture_enable(xpin_t pin, uint8_t enable)
{
	tpm_t tpm = xpin_get_tpm(pin);

	if (!xpin_has_tpmch(pin))
		return -EINVAL;
	tpm_clock_gating(tpm, enable);

	tpm_irq_enable(pin, enable);
	
	return 0;
}
#define tpm2channel2_irq icapture_irq_xpin17

#define icapture_irq_handler(_tpm_, _channel_)				\
	void tpm##_tpm_##ch##_channel_##_isr(void)				\
	{														\
		size_t captcount = TPM##_tpm_##C##_channel_##V;		\
		TPM##_tpm_##C##_channel_##SC_CH##_channel_##F = 0;	\
		tpm##_tpm_##_ch##_channel_##_irq(captcount);		\
	}
		
/* Interruption handler declarations */

#ifdef CONFIG_XBEE_THT
#ifdef ENABLE_ICAPTURE_XPIN_4
#pragma TRAP_PROC
icapture_irq_handler(2, 1)
#endif

#ifdef ENABLE_ICAPTURE_XPIN_6
#pragma TRAP_PROC
icapture_irq_handler(3, 5)
#endif

#ifdef ENABLE_ICAPTURE_XPIN_12
#pragma TRAP_PROC
icapture_irq_handler(3, 0)
#endif

#ifdef ENABLE_ICAPTURE_XPIN_17
#pragma TRAP_PROC
icapture_irq_handler(2, 2)
#endif

#ifdef ENABLE_ICAPTURE_XPIN_20
#pragma TRAP_PROC
input_compare_irq_handler(1, 0)
#endif
#endif /* defined(CONFIG_XBEE_THT) */

#ifdef CONFIG_XBEE_SMT
#ifdef ENABLE_ICAPTURE_XPIN_5
#pragma TRAP_PROC
icapture_irq_handler(2, 1)
#endif

#ifdef ENABLE_ICAPTURE_XPIN_7
#pragma TRAP_PROC
icapture_irq_handler(3,5)
#endif

#ifdef ENABLE_ICAPTURE_XPIN_25
#pragma TRAP_PROC
icapture_irq_handler(3, 0)
#endif

#ifdef ENABLE_ICAPTURE_XPIN_26
#pragma TRAP_PROC
icapture_irq_handler(2, 0)
#endif

#ifdef ENABLE_ICAPTURE_XPIN_30
#pragma TRAP_PROC
icapture_irq_handler(2, 2)
#endif

#ifdef ENABLE_ICAPTURE_XPIN_33
#pragma TRAP_PROC
icapture_irq_handler(1, 0)
#endif
#endif /* defined(CONFIG_XBEE_SMT) */
/* End of Interruption Handler Declarations */
#endif /* ENABLE_INPUT_CAPTURE */
