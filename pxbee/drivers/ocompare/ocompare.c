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
 *	@ingroup api_output_compare
 *	
 *	@defgroup api_output_compare
 *	
 *	@section  api_output_compare_overview Input Capture API Overview
 *	
 *	This API contains the functions to configure and control the Output Compare 
 *	component on programmable XBee devices.
 *	
 *	- Output Compare functions:
 *		- ocompare_config()
 *		- ocompare_get_mode()
 *		- ocompare_set_mode()
 *		- ocompare_set_timeout()
 *		- ocompare_irq_enable()
 *		- ocompare_enable()
 */

#include <ocompare.h>

#ifdef ENABLE_OUTPUT_COMPARE

#ifdef CONFIG_XBEE_THT
extern void ocompare_irq_xpin4(void);
extern void ocompare_irq_xpin6(void);
extern void ocompare_irq_xpin12(void);
extern void ocompare_irq_xpin17(void);
extern void ocompare_irq_xpin20(void);
#endif /* defined(CONFIG_XBEE_THT) */

#ifdef CONFIG_XBEE_SMT
extern void ocompare_irq_xpin5(void);
extern void ocompare_irq_xpin7(void);
extern void ocompare_irq_xpin25(void);
extern void ocompare_irq_xpin26(void);
extern void ocompare_irq_xpin30(void);
extern void ocompare_irq_xpin33(void);
#endif /* defined(CONFIG_XBEE_SMT) */

/**
 *	@ingroup api_output_compare
 *	@brief		Function that configures the settings of the output-compare
 *              component.
 *	@param[in]	pin pin to be configured.
 *	@param[in]	enable 		TRUE for enabling, FALSE for disabling the Output
 *                          Compare IRQ on pin.
 *	@param[in]	max_timeout	Maximum timeout value (in microseconds) that will be
 *                          used in the followings calls to ocompare_set_timeout
 *                          function.
 *	@param[in]	init_timeout timeout value (in microseconds) for the first 
 *                           interrupt.
 *	@param[in]	behavior	state of the pin when timeout is achieved: set, 
 *                          clear or toggle (use defined macros).
 *	@retval		0			on success
 *	@retval		-EINVAL		if the selected pin is not output-compare capable or
 *                          bad parameters are passed.
 *	@retval		-EOVERFLOW	if the requested timeouts can't be achieved
 */
int ocompare_config(xpin_t pin, bool_t enable, uint32_t max_timeout, 
					uint32_t init_timeout, uint8_t behavior)
{
	tpm_t tpm = xpin_get_tpm(pin);
	uint8_t channel = xpin_get_tpm_ch(pin);

	if (!xpin_has_tpmch(pin))
		return -EINVAL;

	if (init_timeout > max_timeout)
		return -EINVAL;
	
	if (behavior != OCOMPARE_TOGGLE &&
		behavior != OCOMPARE_CLEAR &&
		behavior != OCOMPARE_SET)
		return -EINVAL;

	tpm_clock_gating(tpm, 1);
	REG_TPMSC(tpm) = 0;
	
	/* Prescaler for ocompare won't change in ocompare_set_timeout calls */
	if (tpm_set_prescaler(tpm, max_timeout) < 0)
		return -EOVERFLOW;
	
	REG_TPMCSC(tpm, channel) = TPM1C0SC_MS0A_MASK | (behavior << 2);
	 /* Set timeout */
	REG_TPMCV(tpm, channel) += tpm_compute_modulo(REG_TPMSC(tpm), init_timeout);
	REG_TPMMOD(tpm) = 0; /* free-running counter */
	REG_TPMCNT(tpm) = 0;
	ocompare_irq_enable(pin, enable);
	
	return 0;
}


/**
 *	@ingroup api_output_compare
 *	@brief		Function that returns the programmed behavior of the 
 *              output-compare pin.
 *	@param[in]	pin			Pin to read behavior.
 *	@retval		int			The configured behavior (refer to defined macros).
 *	@retval		-EINVAL		If the selected pin is not output-compare capable.
 */
int ocompare_get_mode(xpin_t pin)
{
	return tpm_get_mode(pin);
}

/**
 *	@ingroup api_output_compare
 *	@brief		Function that sets behavior of the output-compare pin.
 *	@param[in]	pin			pin to set behavior.
 *	@retval		int			the configured behavior.
 *	@retval		-EINVAL		if the selected pin is not output-compare capable. 
 */
int ocompare_set_mode(xpin_t pin, uint8_t behavior)
{
	return tpm_set_mode(pin, behavior);
}

/**
 *	@ingroup api_output_compare
 *	@brief		Function that sets timeout of the output-compare interrupt.
 *	@param[in]	pin			pin to set IRQ timeout
 *	@retval		0			on success
 *	@retval		-EINVAL		if the selected pin is not output-compare capable 
 */
int ocompare_set_timeout(xpin_t pin, uint32_t timeout)
{
	tpm_t tpm = xpin_get_tpm(pin);
	uint8_t channel = xpin_get_tpm_ch(pin);
	
	if (!xpin_has_tpmch(pin))
		return -EINVAL;

	REG_TPMCV(tpm, channel) += tpm_compute_modulo(REG_TPMSC(tpm), timeout);

	return 0;
}

/**
 *	@ingroup api_output_compare
 *	@brief		Function that returns the status of output-compare interrupt.
 *	@param[in]	pin			pin (channel) to read status
 *	@retval		int			the configured status.
 *	@retval		-EINVAL		if the selected pin is not output-compare capable. 
 */
int ocompare_irq_enable(xpin_t pin, bool_t enable)
{
	return tpm_irq_enable(pin, enable);
}

/**
 *	@ingroup api_output_compare
 *	@brief		Function that enables/disables the output-compare module.
 *	@param[in]	pin			pin (channel) to enable/disable.
 *	@param[in]	enable		TRUE for enabling, FALSE for disabling module. 
 *	@retval		0			On success.
 *	@retval		-EINVAL		If the selected pin is not output-compare capable.
 */
int ocompare_enable(xpin_t pin, bool_t enable)
{
	tpm_t tpm = xpin_get_tpm(pin);

	if (!xpin_has_tpmch(pin))
		return -EINVAL;
	tpm_clock_gating(tpm, enable);	
	if (enable) {
		REG_TPMCNT(tpm) = 0;
		tpm_irq_enable(pin, enable);
	}
	
	return 0;
}

#define ocompare_irq_handler(_tpm_, _channel_)			\
	void tpm##_tpm_##ch##_channel_##_isr(void)					\
	{															\
		TPM##_tpm_##C##_channel_##SC_CH##_channel_##F = 0;		\
		/* TPM##_tpm_##CNT = 0;  Counter is cleared */			\
		tpm##_tpm_##_ch##_channel_##_irq();						\
	}

#ifdef CONFIG_XBEE_THT
#ifdef ENABLE_OCOMPARE_XPIN_4
#pragma TRAP_PROC
ocompare_irq_handler(2, 1)
#endif /* ENABLE_OCOMPARE_XPIN_4 */

#ifdef ENABLE_OCOMPARE_XPIN_6
#pragma TRAP_PROC
ocompare_irq_handler(3, 5)
#endif /* ENABLE_OCOMPARE_XPIN_6 */

#if defined(ENABLE_OCOMPARE_XPIN_12)
#pragma TRAP_PROC
ocompare_irq_handler(3, 0)
#endif /* ENABLE_OCOMPARE_XPIN_12 */

#ifdef ENABLE_OCOMPARE_XPIN_17
#pragma TRAP_PROC
ocompare_irq_handler(2, 2)
#endif /* ENABLE_OCOMPARE_XPIN_17 */

#ifdef ENABLE_OCOMPARE_XPIN_20
#pragma TRAP_PROC
ocompare_irq_handler(1, 0)
#endif /* ENABLE_OCOMPARE_XPIN_20*/
#endif /* defined(CONFIG_XBEE_THT) */

#ifdef CONFIG_XBEE_SMT
#ifdef ENABLE_OCOMPARE_XPIN_5 
#pragma TRAP_PROC
ocompare_irq_handler(2, 1)
#endif /* ENABLE_OCOMPARE_XPIN_5 */

#ifdef ENABLE_OCOMPARE_XPIN_7 
#pragma TRAP_PROC
ocompare_irq_handler(3, 5)
#endif /* ENABLE_OCOMPARE_XPIN_7 */

#ifdef ENABLE_OCOMPARE_XPIN_25
#pragma TRAP_PROC
ocompare_irq_handler(3, 0)
#endif /* ENABLE_OCOMPARE_XPIN_25 */

#ifdef ENABLE_OCOMPARE_XPIN_26
#pragma TRAP_PROC
ocompare_irq_handler(2, 0)
#endif /* ENABLE_OCOMPARE_XPIN_26 */

#ifdef ENABLE_OCOMPARE_XPIN_30
#pragma TRAP_PROC
ocompare_irq_handler(2, 2)
#endif /* IRQ_HANDLER_XPIN_30 */

#ifdef ENABLE_OCOMPARE_XPIN_33
#pragma TRAP_PROC
ocompare_irq_handler(1, 0)
#endif /* IRQ_HANDLER_XPIN_33 */
#endif /* defined(CONFIG_XBEE_SMT) */
/* End of Interruption Handler Declarations */
#endif /* ENABLE_OUTPUT_COMPARE */
