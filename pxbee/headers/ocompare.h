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
 *	@defgroup api_output_compare
 *	
 *	@section  api_output_compare_macros Output Compare Configuration Macros
 *	The ocompare_ch_config function needs a parameter to state the active edge.
 *	The three different options are defined in the following macros:
 * 		- Input Capture active-edge macros:
 * 			- \b OCOMPARE_TOGGLE: to toggle output at output-compare interrupt.
 * 			- \b OCOMPARE_CLEAR	: to clear output at output-compare interrupt
 * 			- \b OCOMPARE_SET	: to set output at output-compare interrupt
 */
#ifndef __OCOMPARE_H_
#define __OCOMPARE_H_

#include <tpm.h>
#include <hardware.h>

#define	OCOMPARE_TOGGLE				1
#define	OCOMPARE_CLEAR				2
#define	OCOMPARE_SET				3

int ocompare_config(xpin_t pin, bool_t enable, uint32_t max_timeout,
					uint32_t init_timeout, uint8_t behavior);
int ocompare_get_mode(xpin_t pin);
int ocompare_set_mode(xpin_t pin, uint8_t behavior);
int ocompare_set_timeout(xpin_t pin, uint32_t timeout);
int ocompare_irq_enable(xpin_t pin, bool_t enable);
int ocompare_enable(xpin_t pin, bool_t enable);

#endif /* __OCOMPARE_H_ */
