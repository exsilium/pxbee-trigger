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
 *	@ingroup api_lvd
 *	
 *	@defgroup api_lvd
 *	
 *	@section  api_lvd_overview Low-Voltage Detection API Overview
 *	
 *	This API contains the functions to configure and use the Low-Voltage Detection 
 *	mechanism of the user application microprocessor on \b programmable XBee devices.
 *	
 *	- Output Compare functions:
 *		- lvd_irq_enable()
 *		- lvd_flag()
 *		- lvd_clear_flag()
 *		- lvd_set_trigger()
 */

#include <lvd.h>

#ifdef ENABLE_LVD
/**
 *	@ingroup api_lvd
 *	@brief		Enables/Disables the Low-Voltage Detection mechanism.
 *	@param[in]	enable \bTrue for enabling and \bFalse for disabling.
 *	@retval		None
 */
void lvd_irq_enable(bool_t enable)
{
	SPMSC1_LVDIE = enable;
	return;
}

/**
 *	@ingroup api_lvd
 *	@brief		Polls the Low-Voltage Detection flag.
 *	@retval		1 if Low-Voltage is detected, 0 if not.
 */
bool_t lvd_flag(void)
{
	return SPMSC3_LVDV;
}

/**
 *	@ingroup api_lvd
 *	@brief		Clears the Low-Voltage Detection flag.
 *	@retval		None.
 */
void lvd_clear_flag(void)
{
	SPMSC1_LVDACK = 1;
}

/**
 *	@ingroup api_lvd
 *	@brief		Sets the voltage at which the LVD flag is set.
 *	@param[in]	low \b 1 (low) for 1.85 V and \0 (high) for 2.4 V.
 *	@retval		None
 */
void lvd_set_trigger(bool_t low)
{
	if (low)
		SPMSC3 &= ~((uint8_t)SPMSC3_LVDV_MASK | (uint8_t)SPMSC3_LVWV_MASK);
	else
		SPMSC3 |= SPMSC3_LVDV_MASK | SPMSC3_LVWV_MASK;
	
	return;
}

#if (LVD_BEHAVIOR == LVD_IRQ_ENABLE)
extern void lvd_irq(void);
#pragma TRAP_PROC
void lvd_isr(void)
{
	SPMSC1_LVDACK = 1; /* Acknowledge the IRQ */

	lvd_irq();
}
#else
#pragma TRAP_PROC
void lvd_isr(void)
{
	for (;;) ; /* Die by watchdog */
}
#endif /* LVD_BEHAVIOR == LVD_IRQ_ENABLE */

#else /* ENABLE_LVD not defined */
#pragma TRAP_PROC
void lvd_isr(void)
{
	for (;;) ; /* Die by watchdog */
}
#endif /* defined(ENABLE_LVD) */
