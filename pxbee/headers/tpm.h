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

#ifndef __TPM_H_
#define __TPM_H_

#include <types.h>
#include <system.h>
#include <hardware.h>

/* TPM register offsets */
#define	TPM_CNT_OFFSET			1
#define TPM_MOD_OFFSET			3
#define TPM_CH_OFFSET			5

/* TPM register access macros */
#define REG_TPMSC(tpm) 			(*(tpm_get_baseaddr(tpm)))
#define REG_TPMCNT(tpm) 		(*((uint16_t *)(tpm_get_baseaddr(tpm) + \
								 TPM_CNT_OFFSET)))
#define REG_TPMMOD(tpm)			(*((uint16_t *)(tpm_get_baseaddr(tpm) + \
								 TPM_MOD_OFFSET)))
#define REG_TPMCSC(tpm, ch)		(*(tpm_get_baseaddr(tpm) + TPM_CH_OFFSET + \
								 3 * ch))	/* 3 registers per ch */
#define REG_TPMCV(tpm, ch)		(*(uint16_t *)((tpm_get_baseaddr(tpm) + \
								 TPM_CH_OFFSET + 3 * ch) + 1))

/* TPM_MAX_USEC_INITVAL represents how many microseconds can measure the TPM 
 * with prescaler set to 0. It's calculated with the formula:
 *            TPM_MAX_USEC_INITVAL = (0xFFFF / (BUS_CLK_FREQ / 1000000))	
 * However, it's hard-coded because C-preprocessor do not handle float 
 * operations very well.
 * As prescaler is always a 2 multiple, it can be easily determined which 
 * prescaler is needed.
 * TPM_MIN_USEC represents the minimum microseconds that the TPM can measure 
 * with selected prescaler. With prescaler values smaller than 3 it's able to 
 * measure 1 microsecond, but with bigger values the minimum increases in 
 * multiples of 2 (2 for prescaler = 4; 4 for prescaler = 8, etc...).
 * TPM_MIN_TICKS calculates the register value which correspond with the minimum
 * calculated by TPM_MIN_USEC.
 */

#if defined(SYS_CFG_CLK_48_MHz)

#if defined(SYS_CFG_BUSCLK_SYSCLK_DIV2)
#define TPM_MAX_USEC_INITVAL	2731 
#define TPM_MIN_USEC(pre)		(((pre) <= 3) ? 1 : (1 << (uint8_t)(pre - 3)))
#define TPM_MIN_TICKS(pre)		(((pre) <= 3) ? (24 / (uint8_t)(1 << pre)) : 3)
#elif defined(SYS_CFG_BUSCLK_SYSCLK_DIV4)
#define TPM_MAX_USEC_INITVAL	5461
#define TPM_MIN_USEC(pre)		(((pre) <= 4) ? 1 : (uint8_t)(1 << (pre - 4)))
#define TPM_MIN_TICKS(pre)		(((pre) <= 1) ? (12 / (uint8_t)(1 << pre)) : 3)
#elif defined(SYS_CFG_BUSCLK_SYSCLK_DIV8)
#define TPM_MAX_USEC_INITVAL	10923
#define TPM_MIN_USEC(pre)		(((pre) <= 1) ? 1 : (uint8_t)(1 << (pre - 1)))
#define TPM_MIN_TICKS(pre)		(((pre) == 0) ? 6 : 3)
#endif

#elif defined(SYS_CFG_CLK_32_MHz)

#if defined(SYS_CFG_BUSCLK_SYSCLK_DIV2)
#define TPM_MAX_USEC_INITVAL	4096
#define TPM_MIN_USEC(pre)		(((pre) <= 4) ? 1 : (uint8_t)(1 << (pre - 4)))
#define TPM_MIN_TICKS(pre)		(((pre) <= 3) ? (16 / (uint8_t)(1 << pre)) : 1)
#elif defined(SYS_CFG_BUSCLK_SYSCLK_DIV4)
#define TPM_MAX_USEC_INITVAL	8192
#define TPM_MIN_USEC(pre)		(((pre) <= 3) ? 1 : (uint8_t)(1 << (pre - 3)))
#define TPM_MIN_TICKS(pre)		(((pre) <= 2) ? (8 / (uint8_t)(1 << pre)) : 1)
#elif defined(SYS_CFG_BUSCLK_SYSCLK_DIV8)
#define TPM_MAX_USEC_INITVAL	16384
#define TPM_MIN_USEC(pre)		(((pre) <= 2) ? 1 : (uint8_t)(1 << (pre - 2)))
#define TPM_MIN_TICKS(pre)		(((pre) <= 1) ? (4 / (uint8_t)(1 << pre)) : 1)
#endif

#elif defined(SYS_CFG_CLK_16_MHz)

#if defined(SYS_CFG_BUSCLK_SYSCLK_DIV2)
#define TPM_MAX_USEC_INITVAL	8192
#define TPM_MIN_USEC(pre)		(((pre) <= 3) ? 1 : (uint8_t)(1 << (pre - 3)))
#define TPM_MIN_TICKS(pre)		(((pre) <= 2) ? (8 / (uint8_t)(1 << pre)) : 1)
#elif defined(SYS_CFG_BUSCLK_SYSCLK_DIV4)
#define TPM_MAX_USEC_INITVAL	16384
#define TPM_MIN_USEC(pre)		(((pre) <= 2) ? 1 : (uint8_t)(1 << (pre - 2)))
#define TPM_MIN_TICKS(pre)		(((pre) <= 1) ? (4 / (uint8_t)(1 << pre)) : 1)
#elif defined(SYS_CFG_BUSCLK_SYSCLK_DIV8)
#define TPM_MAX_USEC_INITVAL	32768
#define TPM_MIN_USEC(pre)		(((pre) <= 1) ? 1 : (uint8_t)(1 << (pre - 1)))
#define TPM_MIN_TICKS(pre)		(((pre) <= 1) ? (4 / (uint8_t)(1 << pre)) : 1)
#endif

#else

#error "Invalid SYS_CFG_CLK frequency"

#endif


#define TPM_MAX_USEC_INITVAL_FX_CLK		4194304
#define TPM_MIN_USEC_FX_CLK(pre)		(64U << (pre))
#define TPM_MIN_TICKS_FX_CLK			1

#define XPIN_GET_TPM_INFO(pin)		(((pin) >> PWMCH_SH) & 0x0f)
											/* PWMCH_SH is defined at hardware.h */
#define TPM_CLKSRC_BUS	TPM1SC_CLKSA_MASK
#define TPM_CLKSRC_FIX	TPM1SC_CLKSB_MASK

typedef enum {
	TPM1,
	TPM2,
	TPM3
} tpm_t;

uint8_t *tpm_get_baseaddr(tpm_t tpm);
int tpm_set_prescaler(tpm_t tpm, uint32_t u_secs);
uint16_t tpm_compute_modulo(uint8_t tpmsc, uint32_t u_secs);
uint32_t tpm_modulo_to_usec(uint8_t tpmsc, uint16_t modulo);
void tpm_clock_gating(tpm_t tpm, uint8_t enable);
int tpm_irq_enable(xpin_t pin, bool_t enable);
int tpm_set_mode(xpin_t pin, uint8_t mode);
int tpm_get_mode(xpin_t pin);
bool_t xpin_has_tpmch(xpin_t pin);
tpm_t xpin_get_tpm(xpin_t pin);
uint8_t xpin_get_tpm_ch(xpin_t pin);
#endif /* __TPM_H_ */
