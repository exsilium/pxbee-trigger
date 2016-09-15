/****************************************************************************
 * Copyright (C) 2010 - 2015 Digi International Inc, All Rights Reserved.
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
/**	Platform-specific layer provides a consistent UART API to upper layers
 *	of the driver.
 *
 *	@ingroup api_rtc
 *
 *	@defgroup api_rtc
 *
 *	@section macros_rtc RTC Macros
 *
 *	The delay_ticks() function of the RTC module needs as parameter the
 *	number of system ticks for the delay. 1 system tick is 4 milliseconds,
 *	but there is a macro that helps for some operations:
 *
 *		- \b HZ		: This macro represents a value of 250. When used in the
 *					  delay_ticks() function, it will wait for 1 second.
 *
 *	Usage examples:
 *	@code delay_ticks(HZ)
 * delay_ticks(HZ/2)
 * delay_ticks(5*HZ)
 *	@endcode
 *
 ***************************************************************************/

#ifndef __RTC_H_
#define __RTC_H_

#include <types.h>
#include <system.h>

typedef struct {
	uint8_t		sec;
	uint8_t		min;
	uint8_t		hour;
	uint8_t		mday;
	uint8_t		month;
	uint16_t	year;
} tm_t;

#define HZ						250		/* ticks per second (4ms each) */

#ifdef ENABLE_RTC
extern uint32_t wait_for_tout;
extern uint32_t uptime;
extern uint32_t ms_uptime;

#define wait_for(c, to)						\
	do {									\
		wait_for_tout = to;					\
		while (wait_for_tout) {				\
			if (c)	break;					\
			sys_watchdog_reset();			\
		}									\
	} while (0)
#endif

int rtc_set_date(tm_t newdate);
int rtc_get_date(tm_t *now);
int rtc_set_alarm(tm_t newalarm);
uint32_t rtc_get_uptime(void);
uint32_t rtc_get_ms_uptime(void);
int rtc_set_periodic_task_period(uint32_t period);
int rtc_config(void);
void delay_ticks(uint16_t delay);
void rtc_set_timeout(uint16_t timeout);
bool_t rtc_timeout_expired(void);

#endif /* __RTC_H_ */
