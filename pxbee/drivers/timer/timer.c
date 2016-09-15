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
 *  @ingroup api_timer
 *
 *	@defgroup api_timer
 *
 *	@section  api_timer_overview Timer API Overview
 *
 *	This API contains the functions to configure and control the High
 *	Resolution Timer component on programmable XBee devices.
 *
 *	- Timer interrupt request functions:
 *	    - timer_config()
 *		- timer_set_timeout()
 *		- timer_get_timeout()
 *		- timer_set_mode()
 *		- timer_get_mode()
 *		- timer_irq_enable()
 *		- timer_enable()

 */
#include <timer.h>

#ifdef ENABLE_TIMER

#define TIMER1_MODE_MASK		(1 << 0)
#define TIMER2_MODE_MASK		(1 << 1)
#define TIMER3_MODE_MASK		(1 << 2)

uint8_t timers_mode = 0;

/**
 *	@ingroup api_timer
 *	@brief		Function that configures the settings of the timer component.
 *	@param[in]	timer 	timer to configure (use the name of the component 
 *						defined by the config.xml)
 *	@param[in]	enable 	TRUE for enabling, FALSE for disabling the timer.
 *	@param[in]	mode 	desired mode for the timer (use defined macros).
 *	@param[in]	timeout desired time for the timer to timeout
 *	@retval		0			On success.
 *	@retval		-EINVAL		If \b timer is not a valid timer.
 *	@retval		-EOVERFLOW	If \b u_secs is not in supported ranges.
 */
int timer_config(timer_t timer, bool_t enable, timermode_t mode, 
				 uint32_t timeout)
{
	int ret;

	if ( (timer < TPM1) || (timer > TPM3) )
		return -EINVAL;

	timer_set_mode(timer, mode);
	timer_enable(timer, enable);
	ret = timer_set_timeout(timer, timeout);
	if (ret < 0)
		return ret;

	return 0;
}

/**
 *	@ingroup api_timer
 *	@brief		Function that sets the timeout of the timer interrupt if it is
 *				configured as One-Shot timer or the period if it is configured
 *				as a periodic timer.
 *	@param[in]	timer	 	timer to set timeout (use the name of the component
 *							defined by config.xml).
 *	@param[in]	u_secs		Timeout of interrupt in microseconds.
 *	@retval		0			On success.
 *	@retval		-EINVAL		If \b timer is not a valid timer.
 *	@retval		-EOVERFLOW	If \b u_secs is not in supported ranges.
 */
int timer_set_timeout(timer_t timer, uint32_t timeout)
{
	int prescaler;
	uint8_t tpmsc, clk_source;

	if ( (timer < TPM1) || (timer > TPM3) )
		return -EINVAL;

	prescaler = tpm_set_prescaler(timer, timeout);
	if (prescaler < 0)
		return -EOVERFLOW;

	tpmsc = REG_TPMSC(timer);
	clk_source = tpmsc & (TPM_CLKSRC_BUS| TPM_CLKSRC_FIX);
	REG_TPMSC(timer) &= ~(uint8_t)(TPM_CLKSRC_BUS| TPM_CLKSRC_FIX);

	REG_TPMMOD(timer) = tpm_compute_modulo(tpmsc, timeout);

	REG_TPMSC(timer) |= clk_source;

	return 0;
}

/**
 *	@ingroup api_timer
 *	@brief		Function that returns the timeout of the timer interrupt if it
 *				is configured as One-Shot timer or the period if it is
 *				configured as a periodic timer
 *	@param[in]	timer	 	timer to get timeout (use the name of the component
 *							defined by config.xml).
 *	@retval		uint32_t	configured timeout (in microseconds).
 */
uint32_t timer_get_timeout(timer_t timer)
{
	return tpm_modulo_to_usec(REG_TPMSC(timer), REG_TPMMOD(timer));
}

/**
 *	@ingroup api_timer
 *	@brief		Function that enables timer interrupt.
 *	@param[in]	timer	timer to enable IRQ (use the name of the component
 *						defined by config.xml).
 *	@param[in] enable	TRUE to enable, FALSE to disable IRQ.
 *	@retval		0		on success.
 *	@retval		-EINVAL	If \b timer is not a valid timer.
 */
int timer_irq_enable(timer_t timer, bool_t enable)
{
	if ( (timer < TPM1) || (timer > TPM3) )
		return -EINVAL;

	if (enable)
		REG_TPMSC(timer) |= TPM1SC_TOIE_MASK;
	else
		REG_TPMSC(timer) &= ~(uint8_t)TPM1SC_TOIE_MASK;

	return 0;
}

/**
 *	@ingroup api_timer
 *	@brief		Function that sets timer's mode.
 *	@param[in]	timer	timer to set mode (use the name of the component defined
 *						by the config.xml).
 *	@param[in] 	mode	Timer mode: ONE_SHOT or PERIODIC. This determines how
 *						many times the interrupt will be entered.
 *	@retval		-EINVAL	If \b timer is not a valid timer.
 *	@retval		-ERANGE	out of range.
 */
int timer_set_mode(timer_t timer, timermode_t mode)
{
	if ( (timer < TPM1) || (timer > TPM3) )
		return -EINVAL;

	if (mode == ONE_SHOT) {
		if (timer == TPM1)
			timers_mode |= TIMER1_MODE_MASK;
		else if (timer == TPM2)
			timers_mode |= TIMER2_MODE_MASK;
		else
			timers_mode |= TIMER3_MODE_MASK;
	} else if (mode == PERIODIC) {
		if (timer == TPM1)
			timers_mode &= ~TIMER1_MODE_MASK;
		else if (timer == TPM2)
			timers_mode &= ~TIMER2_MODE_MASK;
		else
			timers_mode &= ~TIMER3_MODE_MASK;
	} else {
		return -ERANGE;
	}
	return 0;
}

/**
 *	@ingroup api_timer
 *	@brief		Function that returns timer's mode configuration.
 *	@param[in]	timer			timer to get mode (use the name of the component
 *								defined by config.xml).
 *	@retval 	timermode_t		Timer mode: ONE_SHOT or PERIODIC. This 
 *								determines how many times the interrupt will be
 *								entered.
 *								NO_VALID if bad timer is passed as argument.
 */
timermode_t timer_get_mode(timer_t timer)
{
	switch(timer) {
	case TPM1:
		return (timers_mode & TIMER1_MODE_MASK ? ONE_SHOT : PERIODIC);
	case TPM2:
		return (timers_mode & TIMER2_MODE_MASK ? ONE_SHOT : PERIODIC);
	case TPM3:
		return (timers_mode & TIMER3_MODE_MASK ? ONE_SHOT : PERIODIC);
	}
	return NO_VALID;
}

#pragma INLINE
static void timer_clear_tof(timer_t timer)
{
	REG_TPMSC(timer) &= ~(uint8_t)TPM1SC_TOF_MASK;
}

/**
 *	@ingroup api_timer
 *	@brief		Function that enables/disables the timer module.
 *	@param[in]	timer	 	timer to enable IRQ (use the name of the component
 *							defined by config.xml).
 *	@param[in]	enable		TRUE for enabling, FALSE for disabling module.
 *	@retval		nothing
 */
void timer_enable(timer_t timer, uint8_t enable)
{
	tpm_clock_gating(timer, enable);

	if (enable) {
		REG_TPMCNT(timer) = 0x00;
		timer_clear_tof(timer);
		timer_irq_enable(timer, TRUE);
	}
}

#ifdef TPM1_OVERFLOW_INTERRUPT
#pragma TRAP_PROC
void tpm1ov_isr(void)
{
	if (timers_mode & TIMER1_MODE_MASK) {
		/* One-Shot */
		TPM1SC_TOIE = 0;
		timer_enable(TPM1, FALSE);
	}

	timer_clear_tof(TPM1);
	tpm1ov_irq();
}
#endif /* ENABLE_TPM1_OVERFLOW_INTERRUPT */

#ifdef TPM2_OVERFLOW_INTERRUPT
#pragma TRAP_PROC
void tpm2ov_isr(void)
{
	if (timers_mode & TIMER2_MODE_MASK) {
		/* One-Shot */
		TPM2SC_TOIE = 0;
		timer_enable(TPM2, FALSE);
	}

	timer_clear_tof(TPM2);
	tpm2ov_irq();
}
#endif /* ENABLE_TPM2_OVERFLOW_INTERRUPT */

#ifdef TPM3_OVERFLOW_INTERRUPT
#pragma TRAP_PROC
void tpm3ov_isr(void)
{
	if (timers_mode & TIMER3_MODE_MASK) {
		/* One-Shot */
		TPM3SC_TOIE = 0;
		timer_enable(TPM3, FALSE);
	}

	timer_clear_tof(TPM3);
	tpm3ov_irq();
}
#endif /* ENABLE_TPM3_OVERFLOW_INTERRUPT */
#endif /* ENABLE_TIMER */
