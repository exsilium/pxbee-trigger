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

#include <system.h>
#include <types.h>

#if CONFIG_XBEE_FLASH_LEN > 32
#ifdef DISABLE_VECTOR_REDIRECTION
#define SET_VECTOR_ADDR(f)			((uint16_t)(f))
#define SET_RESET_APP_ADDR(f)		SET_VECTOR_ADDR(f)
#define RELOCATED_VECTOR_ADDRESS	@0xFFC0
#else
/** 
 * For those variants with flashes larger than 32KB, the vectors are redirected in 
 * the bootloader to the RELOCATED_VECTOR_ADDRESS and from there, to the proper isr.
 * The vector needs to point to isr address + 1. All routines need to PUSH H at the
 * beginning (otherwise it will not work properly).
 * This initial PUSH is skipped here because the redirection does it. But the POP H
 * at the end must be there in order to restore the register to its previous state.
 * The startup/reset vector (_Startup) uses a #pragma NO_EXIT since it jumps to main
 * instead of returning.  Due to the pragma, it does not include a PUSH H to skip.
 */
#define SET_VECTOR_ADDR(f)			(uint16_t)((uint16_t)(f) + 1)
/* Bellow the + 1 - 1 is to satisfy the compiler and avoid a C3400 error */
#define SET_RESET_APP_ADDR(f)		(uint16_t)((uint16_t)(f) + 1 - 1)

#define RELOCATED_VECTOR_ADDRESS	@0xEFC0
#endif /* DISABLE_VECTOR_REDIRECTION */
#else
#define SET_VECTOR_ADDR(f)			((uint16_t)(f))
#define SET_RESET_APP_ADDR(f)		SET_VECTOR_ADDR(f)
#define RELOCATED_VECTOR_ADDRESS	@0xF1C0
#endif /* CONFIG_XBEE_FLASH_LEN > 32 */

extern void rtc_isr(void);
extern void radio_uart_isr(void);
extern void uart_isr(void);  
extern void gpio_isr(void);
extern void _Startup(void);
extern void lvd_isr(void);
extern void tpm1ch0_isr(void);
extern void tpm1ch1_isr(void);
extern void tpm2ch1_isr(void);
extern void tpm2ch2_isr(void);
extern void tpm3ch0_isr(void);
extern void tpm3ch5_isr(void);
extern void tpm1ov_isr(void);
extern void tpm2ov_isr(void);
extern void tpm3ov_isr(void);

#ifdef CONFIG_XBEE_SMT
extern void tpm2ch0_isr(void);
#elif defined(CONFIG_XBEE_THT)
#define tpm2ch0_isr	die
#endif

#pragma TRAP_PROC 
void die(void)
{
	for (;;) ;
}

#pragma CONST_SEG VECTOR_DATA
/* Interrupt vector table (relocated on variants with more than 32KB of flash) */
const uint16_t vector_table[] RELOCATED_VECTOR_ADDRESS = {
	SET_VECTOR_ADDR(tpm3ov_isr),		/* Int   0 - Vtpm3ovf (at FFC0 or EFC0) */
	SET_VECTOR_ADDR(tpm3ch5_isr),		/* Int   1 - Vtpm3ch5 (at FFC2 or EFC2) */
	SET_VECTOR_ADDR(die),				/* Int   2 - Vtpm3ch4 (at FFC4 or EFC4) */
	SET_VECTOR_ADDR(die),				/* Int   3 - Vtpm3ch3 (at FFC6 or EFC6) */
	SET_VECTOR_ADDR(die),				/* Int   4 - Vtpm3ch2 (at FFC8 or EFC8) */
	SET_VECTOR_ADDR(die),				/* Int   5 - Vtpm3ch1 (at FFCA or EFCA) */
	SET_VECTOR_ADDR(tpm3ch0_isr),		/* Int   6 - Vtpm3ch0 (at FFCC or EFCC) */
	SET_VECTOR_ADDR(rtc_isr),			/* Int   7 - Vrtc     (at FFCE or EFCE) */
	SET_VECTOR_ADDR(die),				/* Int   8 - Vsci2tx  (at FFD0 or EFD0) */
	SET_VECTOR_ADDR(radio_uart_isr),	/* Int   9 - Vsci2rx  (at FFD2 or EFD2) */
	SET_VECTOR_ADDR(die),				/* Int  10 - Vsci2err (at FFD4 or EFD4) */
	SET_VECTOR_ADDR(die),				/* Int  11 - Vacmpx   (at FFD6 or EFD6) */
	SET_VECTOR_ADDR(die),				/* Int  12 - Vadc     (at FFD8 or EFD8) */
	SET_VECTOR_ADDR(gpio_isr),			/* Int  13 - Vkeyboard(at FFDA or EFDA) */
	SET_VECTOR_ADDR(die),				/* Int  14 - Viic     (at FFDC or EFDC) */
	SET_VECTOR_ADDR(die),				/* Int  15 - Vsci1tx  (at FFDE or EFDE) */
	SET_VECTOR_ADDR(uart_isr),			/* Int  16 - Vsci1rx  (at FFE0 or EFE0) */
	SET_VECTOR_ADDR(die),				/* Int  17 - Vsci1err (at FFE2 or EFE2) */
	SET_VECTOR_ADDR(die),				/* Int  18 - Vspi1    (at FFE4 or EFE4) */
	SET_VECTOR_ADDR(die),				/* Int  19 - Vspi2    (at FFE6 or EFE6) */
	SET_VECTOR_ADDR(tpm2ov_isr),		/* Int  20 - Vtpm2ovf (at FFE8 or EFE8) */
	SET_VECTOR_ADDR(tpm2ch2_isr),		/* Int  21 - Vtpm2ch2 (at FFEA or EFEA) */
	SET_VECTOR_ADDR(tpm2ch1_isr),		/* Int  22 - Vtpm2ch1 (at FFEC or EFEC) */
	SET_VECTOR_ADDR(tpm2ch0_isr),		/* Int  23 - Vtpm2ch0 (at FFEE or EFEE) */
	SET_VECTOR_ADDR(tpm1ov_isr),		/* Int  24 - Vtpm1ovf (at FFF0 or EFF0) */
	SET_VECTOR_ADDR(die),				/* Int  25 - Vtpm1ch2 (at FFF2 or EFF2) */
	SET_VECTOR_ADDR(die),				/* Int  26 - Vtpm1ch1 (at FFF4 or EFF4) */
	SET_VECTOR_ADDR(tpm1ch0_isr),		/* Int  27 - Vtpm1ch0 (at FFF6 or EFF6) */
	SET_VECTOR_ADDR(lvd_isr),			/* Int  28 - Vlvd     (at FFF8 or EFF8) */
	SET_VECTOR_ADDR(die),				/* Int  29 - Virq     (at FFFA or EFFA) */
	SET_VECTOR_ADDR(die),				/* Int  30 - Vswi     (at FFFC or EFFC) */
	SET_RESET_APP_ADDR(_Startup),		/* Int  31 - Vreset   (at FFFE) */ 
};

