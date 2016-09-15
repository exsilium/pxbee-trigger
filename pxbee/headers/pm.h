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

#ifndef __PM_H_
#define __PM_H_

#include <types.h>
#include <system.h>

/* @ingroup types */
typedef enum pm_mode {
	PM_MODE_RUN = 0,
	PM_MODE_WAIT,
	PM_MODE_STOP,
	PM_MODE_STOP_2,
	PM_MODE_STOP_3,
	PM_MODE_UNKNOWN,
} pm_mode_t;

#define WAIT_INFINITE	0	/* wake up only by IRQs */

/* Function prototypes */
int pm_set_cpu_mode(pm_mode_t mode, uint32_t sleep_seconds);
void pm_set_radio_mode(pm_mode_t mode);
pm_mode_t pm_get_cpu_mode(void);
uint8_t pm_get_wakeup_source(void);
pm_mode_t pm_get_radio_mode(void);

#endif /* __PM_H_ */
