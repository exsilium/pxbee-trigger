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
 *	@defgroup api_input_capture
 *	
 *	@section  api_input_capture_macros Input Capture Configuration Macros
 *	The icapture_config function needs a parameter to state the active edge. The 
 *	three different options are defined in the following macros:
 * 		- Input Capture active-edge macros:
 * 			- \b ICAPTURE_RISING	: to set rising edges as active edges.
 * 			- \b ICAPTURE_FALLING	: to set falling edges as active edges.
 * 			- \b ICAPTURE_BOTH		: to set both falling and rising edges as 
 * 									  active.
 */

#ifndef __ICAPTURE_H_
#define __ICAPTURE_H_

#include <tpm.h>
#include <hardware.h>

#define	ICAPTURE_RISING			1
#define	ICAPTURE_FALLING		2
#define	ICAPTURE_BOTH			3

int icapture_config(xpin_t pin,  uint8_t edge, bool_t enable,
					uint32_t max_u_secs);
uint32_t icapture_captcount_to_usec(xpin_t pin, size_t captcount);
int icapture_get_mode(xpin_t pin);
int icapture_set_mode(xpin_t pin, uint8_t mode);
int icapture_irq_enable(xpin_t pin, bool_t enable);
int icapture_enable(xpin_t pin, uint8_t enable);

#endif /* __ICAPTURE_H_ */
