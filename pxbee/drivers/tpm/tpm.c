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

#include <xbee_config.h>
#include <tpm.h>

#if defined(ENABLE_PWM) || defined(ENABLE_INPUT_CAPTURE) || \
	defined(ENABLE_OUTPUT_COMPARE) || defined(ENABLE_TIMER)

/*
 * Return base address of TPM
 */
uint8_t *tpm_get_baseaddr(tpm_t tpm)
{
	if (tpm == TPM1)
		return &TPM1SC;
	else if (tpm == TPM2)
		return &TPM2SC;
	else if (tpm == TPM3)
			return &TPM3SC;
	else
		return NULL;
}

bool_t xpin_has_tpmch(xpin_t pin)
{
	return XPIN_GET_TPM_INFO(pin) != 0xf;
}

tpm_t xpin_get_tpm(xpin_t pin)
{
	uint8_t pin_info = XPIN_GET_TPM_INFO(pin);
	return (pin_info == 0 ? TPM1 :((pin_info <= 5) ? TPM2 : TPM3));
}

uint8_t xpin_get_tpm_ch(xpin_t pin)
{
	switch(XPIN_GET_TPM_INFO(pin)) {
	case 0:
	case 3:
	case 6:
		return 0;
	case 4:
		return 1;
	case 5:
		return 2;
	case 11:
		return 5;
	default:
		return 0xFF;
	}
}

/*
 * This function selects an appropriate prescaler and
 * clock source to meet the requirements imposed by
 * u_secs
 */
int tpm_set_prescaler(tpm_t tpm, uint32_t u_secs)
{
	uint8_t prescaler, i;
	uint32_t max[2] = {TPM_MAX_USEC_INITVAL, TPM_MAX_USEC_INITVAL_FX_CLK};

	for (i = 0; i < 2; i++){
		for (prescaler = 0; prescaler < 8; prescaler++) {
			if (u_secs <= max[i]) {
				/* Clean the Clock Source and prescaler bytes */
				REG_TPMSC(tpm) &= ~(uint8_t)(TPM_CLKSRC_BUS |
									TPM_CLKSRC_FIX | TPM1SC_PS_MASK);
				/* Set new values */
				REG_TPMSC(tpm) |= (i ? TPM_CLKSRC_FIX: TPM_CLKSRC_BUS) |
										(prescaler & TPM1SC_PS_MASK);
	
				return (int)prescaler;
			}
			max[i] <<= 1;
		}
	}	
	return -EINVAL;
}

/*
 * This functions "translates" microseconds to Modulo value considering
 * TPM's clock source and prescaler
 */
uint16_t tpm_compute_modulo(uint8_t tpmsc, uint32_t u_secs)
{
	uint8_t prescaler = tpmsc & TPM1SC_PS_MASK;
	
	if (tpmsc & TPM_CLKSRC_BUS)
		return ((uint16_t) (u_secs * TPM_MIN_TICKS(prescaler) / 
									 TPM_MIN_USEC(prescaler)));
	else
		/* always TPM_MIN_TICKS = 1 @FixedFreq*/
		return ((uint16_t) (u_secs / TPM_MIN_USEC_FX_CLK(prescaler)));
}

/* 
 * This function calculates and returns the microseconds value of the TPM's 
 * modulo register, considering clock source and prescaler.
 */
uint32_t tpm_modulo_to_usec(uint8_t tpmsc, uint16_t modulo)
{
	uint8_t prescaler = tpmsc & TPM1SC_PS_MASK;
	
	if (tpmsc & TPM_CLKSRC_BUS)
		return (uint32_t)modulo * TPM_MIN_USEC(prescaler) / 
								  TPM_MIN_TICKS(prescaler);
	else
		return (uint32_t)modulo * TPM_MIN_USEC_FX_CLK(prescaler);
}

/* Enable/Disable clock gating for TPM module. */
void tpm_clock_gating(tpm_t tpm, uint8_t enable)
{
	switch(tpm) {
	case TPM1:
		SCGC1_TPM1 = enable;
		break;
	case TPM2:
		SCGC1_TPM2 = enable;
		break;
	case TPM3:
		SCGC1_TPM3 = enable;
		break;
	}
}

/*
 * Returns mode of TPM (Input Captura, Output Compare,
 * Pulse-Width-Modulator) to compare with defined macros.
 */
#pragma INLINE
int tpm_get_mode(xpin_t pin)
{
	tpm_t tpm;
	int	  channel;
	
	if (!xpin_has_tpmch(pin))
		return -EINVAL;
		
	tpm = xpin_get_tpm(pin);
	channel = xpin_get_tpm_ch(pin);
	
	return ((REG_TPMCSC(tpm, channel) & TPM1C1SC_ELS1x_MASK) >> 2);
}

/*
 * Sets mode of TPM (Input Captura, Output Compare,
 * Pulse-Width-Modulator) using defined macros.
 */
#pragma INLINE
int tpm_set_mode(xpin_t pin, uint8_t mode)
{
	tpm_t tpm = xpin_get_tpm(pin);
	int	channel = xpin_get_tpm_ch(pin);

	
	if (!xpin_has_tpmch(pin))
			return -EINVAL;
		
	REG_TPMCSC(tpm, channel) = (uint8_t)(REG_TPMCSC(tpm, channel) &
								~TPM1C1SC_ELS1x_MASK) | (mode << 2);
	return 0;
}

/*
 * Enable/Disable pin-associated interrupts (TPM Channels)
 */
#pragma INLINE
int tpm_irq_enable(xpin_t pin, bool_t enable)
{
	tpm_t tpm = xpin_get_tpm(pin);
	int channel = xpin_get_tpm_ch(pin);
	
	if (!xpin_has_tpmch(pin))
			return -EINVAL;
	
	if (enable)
	{
		/* Clear flag */
		REG_TPMCSC(tpm, channel) &= ~(uint8_t)TPM1C0SC_CH0F_MASK;	
		REG_TPMCSC(tpm, channel) |= TPM1C0SC_CH0IE_MASK;
	}
	else
		REG_TPMCSC(tpm, channel) &= ~(uint8_t)TPM1C0SC_CH0IE_MASK;
	
	return 0;
}
#endif /* ENABLE_PWM || ENABLE_INPUT_CAPTURE || ENABLE_OUTPUT_COMPARE || 
		  ENABLE_TIMER */
/* IRQ handlers for unused modules */
#define tpm_irq_handler_off(_tpm_, _channel_) \
		void tpm##_tpm_##ch##_channel_##_isr(void) {}

#ifdef CONFIG_XBEE_THT
#if !(defined (ENABLE_OCOMPARE_XPIN_4) || defined(ENABLE_ICAPTURE_XPIN_4) || \
	  defined(TPM_TESTING))
#pragma TRAP_PROC
tpm_irq_handler_off(2, 1)
#endif /* IRQ_HANDLER_XPIN_4 */

#if !(defined (ENABLE_OCOMPARE_XPIN_6) || defined(ENABLE_ICAPTURE_XPIN_6) || \
	  defined(TPM_TESTING))
#pragma TRAP_PROC
tpm_irq_handler_off(3, 5)
#endif /* IRQ_HANDLER_XPIN_6 */

#if !(defined (ENABLE_OCOMPARE_XPIN_12) || defined(ENABLE_ICAPTURE_XPIN_12) || \
	  defined(TPM_TESTING))
#pragma TRAP_PROC
tpm_irq_handler_off(3, 0)
#endif /* IRQ_HANDLER_XPIN_12 */

#if !(defined (ENABLE_OCOMPARE_XPIN_17) || defined(ENABLE_ICAPTURE_XPIN_17) || \
	  defined(TPM_TESTING))
#pragma TRAP_PROC
tpm_irq_handler_off(2, 2)
#endif /* IRQ_HANDLER_XPIN_17 */

#if !(defined (ENABLE_OCOMPARE_XPIN_20) || defined(ENABLE_ICAPTURE_XPIN_20) || \
	  defined(TPM_TESTING))
#pragma TRAP_PROC
tpm_irq_handler_off(1, 0)
#endif /* IRQ_HANDLER_XPIN_20 */
#endif /* defined(CONFIG_XBEE_THT) */

#ifdef CONFIG_XBEE_SMT
#if !(defined (ENABLE_OCOMPARE_XPIN_5) || defined(ENABLE_ICAPTURE_XPIN_5) || \
	  defined(TPM_TESTING))
#pragma TRAP_PROC
tpm_irq_handler_off(2,1)
#endif /* IRQ_HANDLER_XPIN_5 */

#if !(defined (ENABLE_OCOMPARE_XPIN_7) || defined(ENABLE_ICAPTURE_XPIN_7) || \
	  defined(TPM_TESTING))
#pragma TRAP_PROC
tpm_irq_handler_off(3, 5)
#endif /* IRQ_HANDLER_XPIN_7 */

#if !(defined (ENABLE_OCOMPARE_XPIN_25) || defined(ENABLE_ICAPTURE_XPIN_25) || \
	  defined(TPM_TESTING))
#pragma TRAP_PROC
tpm_irq_handler_off(3, 0)
#endif /* IRQ_HANDLER_XPIN_25 */

#if !(defined (ENABLE_OCOMPARE_XPIN_26) || defined(ENABLE_ICAPTURE_XPIN_26) || \
	  defined(TPM_TESTING))
#pragma TRAP_PROC
tpm_irq_handler_off(2, 0)
#endif /* IRQ_HANDLER_XPIN_25 */

#if !(defined (ENABLE_OCOMPARE_XPIN_30) || defined(ENABLE_ICAPTURE_XPIN_30) || \
	  defined(TPM_TESTING))
#pragma TRAP_PROC
tpm_irq_handler_off(2, 2)
#endif /* IRQ_HANDLER_XPIN_30 */

#if !(defined (ENABLE_OCOMPARE_XPIN_33) || defined(ENABLE_ICAPTURE_XPIN_33) || \
	  defined(TPM_TESTING))
#pragma TRAP_PROC
tpm_irq_handler_off(1, 0)
#endif /* IRQ_HANDLER_XPIN_33 */
#endif /* defined(CONFIG_XBEE_SMT) */

#if !(defined(TPM1_OVERFLOW_INTERRUPT) || defined(TPM_TESTING))
#pragma TRAP_PROC
void tpm1ov_isr(void) {}
#endif /* ENABLE_TPM1_OVERFLOW_INTERRUPT */

#if !(defined(TPM2_OVERFLOW_INTERRUPT) || defined(TPM_TESTING))
#pragma TRAP_PROC
void tpm2ov_isr(void) {}
#endif /* ENABLE_TPM2_OVERFLOW_INTERRUPT */

#if !(defined(TPM3_OVERFLOW_INTERRUPT) || defined(TPM_TESTING))
#pragma TRAP_PROC
void tpm3ov_isr(void) {}
#endif /* ENABLE_TPM3_OVERFLOW_INTERRUPT */
/* End of Interruption Handler Declarations */
