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
 *	@defgroup api_timer
 *	
 *	@section  api_timer_macros Timer API Configuration Macros
 *	The timer_config function needs a parameter to state the timer type. The 
 *	two different options are defined in the following macros:
 * 		- Input Capture active-edge macros:
 * 			- \b ONE_SHOT	: to set the timer as one shot.
 * 			- \b PERIODIC	: to set timer as periodic.
 */

#ifndef __TIMER_H_
#define __TIMER_H_

#include <tpm.h>

extern void tpm1ov_irq(void);
extern void tpm2ov_irq(void);
extern void tpm3ov_irq(void);

typedef enum tpm_t timer_t;

typedef enum {
	ONE_SHOT = 0,
	PERIODIC = 1,
	NO_VALID
} timermode_t;

int timer_set_timeout(timer_t timer, uint32_t timeout);
int timer_set_mode(timer_t timer, timermode_t mode);
timermode_t timer_get_mode(timer_t timer);
int timer_irq_enable(timer_t timer, bool_t enable);
void timer_enable(timer_t timer, uint8_t enable);
uint32_t timer_get_timeout(timer_t timer);
int timer_config(timer_t timer, bool_t enable, timermode_t mode,
				 uint32_t timeout);

#endif /* __TIMER_H_ */
