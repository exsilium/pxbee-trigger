/****************************************************************************
 * Copyright (C) 2010, 2011 Digi International Inc, All Rights Reserved.
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
/**	Platform-specific layer provides a consistent RTC API to upper layers
 *	of the driver.
 *
 *	@ingroup api_rtc
 *
 *	@defgroup api_rtc
 *
 *	@section rtc XBee RTC API Overview
 *
 *	This API contains the functions to configure and control the RTC module of
 *  the Programmable XBee devices.
 *  The RTC provides the system time through second an millisecond counters,
 *  support to trigger a periodic task, calendar (date/time), one programmable
 *  alarm (with alarm function) and several functions to perform delays.
 *
 *	- RTC configuration functions:
 *		- rtc_config()
 *		- rtc_set_alarm()
 *		- rtc_set_periodic_task_period()
 *		- rtc_set_timeout()
 *		- rtc_set_date()
 *
 *	- RTC functions to read/get status and RTC values:
 *		- rtc_get_date()
 *		- rtc_get_uptime()
 *		- rtc_get_ms_uptime()
 *		- rtc_timeout_expired()
 *
 *	- Miscellaneous RTC functions:
 *		- delay_ticks()
 */

#include <system.h>
#include <errno.h>
#include <types.h>
#include <rtc.h>
#include <string.h>

#ifdef ENABLE_RTC

#define month_has_30_days(m)	((m) == 4 || (m) == 6 || (m) == 9 || (m) == 11)
#define leap_year(y)			((((y) % 4 == 0) && (((y) % 100 != 0) || ((y) % 400 == 0))) ? 1 : 0)
#define trigger_alarm()			(!memcmp(&date, &alarm, sizeof(tm_t)))

#define RTCPS					0x08	/* divide by 1 */
#define RTCPS_SLOW				0x0e
#define RTCMOD_VAL				((INT_REF_FREQ / HZ) - 1)
#define RTC_SLOW_MSEC_INC		2000
#define RTC_SLOW_SEC_INC		2
#define RTC_FAST_MSEC_INC		4
#define RTC_SLOW_TICKS_INC		500 /* 2 seconds = 500 * 4 milliseconds / tick */


/// \cond
static uint16_t ticks = 0;
uint32_t uptime = 0;
uint32_t ms_uptime = 0;
uint16_t wait_for_tout1 = 0;
uint16_t wait_for_tout2 = 0;
#ifdef ENABLE_POWER_MANAGEMENT	
extern uint32_t seconds_to_wakeup;
extern uint8_t wakeup_irq;
#endif /* ENABLE_POWER_MANAGEMENT */	
/// \endcond
#ifdef RTC_ENABLE_CALENDAR
extern void rtc_alarm_task(void);
static tm_t date;
static tm_t alarm;

/**
 *	@ingroup    api_rtc
 *	@brief      Sets \b date as RTC date
 *	@param[in] 	newdate		Date to program in the RTC
 *	@retval	    0 on success, error code otherwise
 */
int rtc_set_date(tm_t newdate)
{
	(void)memcpy(&date, &newdate, sizeof(tm_t));
	return 0;
}

/**
 *	@ingroup    api_rtc
 *	@brief		Reads the RTC time/date and saves it in \b now
 *	@param[out] now		struct where the time/date is saved
 *	@retval		0		on success
 *	@retval 	EINVAL	invalid parameter
 */
int rtc_get_date(tm_t *now)
{
	if (!now)
		return -EINVAL;

	(void)memcpy(now, &date, sizeof(tm_t));
	return 0;
}

#ifdef RTC_ENABLE_ALARM
/**
 *	@ingroup    api_rtc
 *	@brief		Programs the \b alarm with newalarm time values
 *	@param[in] 	newalarm  time/date value when the alarm will be
 *	            triggered
 *	@retval		0 on success
 */
int rtc_set_alarm(tm_t newalarm)
{
	if (date.year > newalarm.year)
		return -EINVAL;
	else if (date.year == newalarm.year) {
		/* Check month */
		if (date.month > newalarm.month)
			return -EINVAL;
		else if (date.month == newalarm.month) {
			/* Check month day */
			if (date.mday > newalarm.mday)
				return -EINVAL;
			else if (date.mday == newalarm.mday) {
				/* Check hour */
				if (date.hour > newalarm.hour)
					return -EINVAL;
				if (date.hour == newalarm.hour) {
					/* Check mins */
					if (date.min > newalarm.min)
						return -EINVAL;
					else if (date.min == newalarm.min) {
						/* Check secs */
						if (date.sec >= newalarm.sec)
							return -EINVAL;
					}
				}
			}
		}
	}
	(void)memcpy(&alarm, &newalarm, sizeof(tm_t));
	return 0;
}
#endif /* RTC_ENABLE_ALARM */
#endif /* RTC_ENABLE_CALENDAR */

#ifdef RTC_ENABLE_PERIODIC_TASK
/**
 *	@ingroup    api_rtc
 *	@brief		Function called when the periodic timer expires.
 *	            The periodic timer is rearmed automatically by the
 *	            firmware
 *	@param 		None
 *	@retval		None
 */
extern void rtc_periodic_task(void);
/// \cond
uint32_t ticks_ptask_tout = 0;
uint32_t ticks_ptask_cnt;
/// \endcond

/**
 *	@ingroup    api_rtc
 *	@brief		Configures the \p period (expressed as number of system
 *              ticks) of execution of the periodic task. A call to this
 *              function resets/restarts the periodic task timer
 *	@param[in] 	period	in system ticks, for the periodic task
 *	@retval		0 on success
 */
int rtc_set_periodic_task_period(uint32_t period)
{
	ticks_ptask_tout = period;
	ticks_ptask_cnt = 0;
	return 0;
}

/**
 *	@ingroup    api_rtc
 *	@brief		Cancels the execution of the periodic task setting to
 *	            0 the periodic task timer.
 *	@param[in] 	None
 *	@retval		None
 */
void rtc_cancel_periodic_task(void)
{
	ticks_ptask_tout = 0;
}
#endif /* RTC_ENABLE_PERIODIC_TASK */

#pragma INLINE
/**
 *	@ingroup    api_rtc
 *	@brief 	    Returns the second counter, number of seconds the system has
 *	            been running without interruption (downtime)
 *	@param      None
 *	@retval     Number of seconds the system has been up and running
 */
uint32_t rtc_get_uptime(void)
{
	return uptime;
}

#pragma INLINE
/**
 *	@ingroup    api_rtc
 *	@brief 	    Returns the miliseconds counter, number of ms the system has
 *	            been running without interruption (downtime)
 * 	@param	    None
 *	@retval     Number of miliseconds the system has been up and running
 */
uint32_t rtc_get_ms_uptime(void)
{
	uint32_t ms_uptime_adj;
	uint8_t ms1, ms2;

	/* With a 4ms tick, RTCCNT varies from 0 to 124. Divide by 32 to
	 * get the number of ms and improve the resolution of ms_uptime.
	 * It is not exact, but a good enough approximation. */
	do {
		ms1 = RTCCNT >> 5;
		ms_uptime_adj = ms_uptime + ms1;
		ms2 = RTCCNT >> 5;
	} while (ms1 != ms2);

	return ms_uptime_adj;
}

/**
 *	@ingroup    api_rtc
 *	@brief      Configures and initializes the RTC module, with the defualt
 *	            settings. Its automatically called by sys_hw_init()
 *	@param      None
 *	@retval     0 on success
 */
int rtc_config(void)
{
	/* Enable the clock for this (RTC) module */
	SCGC2_RTC = 1;

#ifdef RTC_ENABLE_CALENDAR
	/* Just to avoid triggering the alarm before programming it */
	(void)memset(&date, 0, sizeof(tm_t));
	alarm.year = 0xffff;
#endif

	/**
	 * Configure IRCLK as RTC clock source, enable the RTC
	 * interrupt and configure the system tick to 4ms.
	 */
	RTCSC = RTCSC_RTIE_MASK | RTCSC_RTCLKS1_MASK | RTCPS;
	RTCMOD = RTCMOD_VAL;

	return 0;
}
#ifdef ENABLE_POWER_MANAGEMENT
uint8_t rtc_is_slow(void)
{
	/**
	 * Configure IRCLK as RTC clock source, enable the RTC
	 * interrupt and configure the system tick to 4ms.
	 */
	return ((RTCSC & 0x0f) == RTCPS_SLOW) ? 1 : 0;
}

void rtc_config_slow(void)
{
	/**
	 * Configure IRCLK as RTC clock source, enable the RTC
	 * interrupt and configure the system tick to 4ms.
	 */
	RTCSC &= 0xf0;
	RTCSC |= RTCPS_SLOW;
	
	/* Now the system tick is 500 times slower than in fast mode*/
}

void rtc_config_fast(void)
{
	/**
	 * Configure IRCLK as RTC clock source, enable the RTC
	 * interrupt and configure the system tick to 4ms.
	 */
	if (rtc_is_slow())
	{
		/**
		 * We are changing from slow to fast. We may have been interrupted
		 * before the slow period (2 second) elapsed.
		 * Read current remaining count to not lose it.
		 */
		
		/** 
		 * Here we adjust ms_uptime, ticks and ticks_ptask_cnt global variables
		 * according to re-schedule in next 4mS rtc_isr will be called and it 
		 * will update uptime global variable and call update_date() and 
		 * rtc_periodic_task() if necessary  
		 */
		
		/* Each count in RTCCNT while in slow mode is 16mS */
		ms_uptime += RTCCNT * 16;
		ticks += RTCCNT * 16 / 4;

#ifdef RTC_ENABLE_PERIODIC_TASK
		if (ticks_ptask_tout) 
			ticks_ptask_cnt += RTCCNT * 16 / 4;		
#endif /* RTC_ENABLE_PERIODIC_TASK */		
	}
	
	RTCSC &= 0xf0;
	RTCSC |= RTCPS;
}
#endif /* ENABLE_POWER_MANAGEMENT */
/**
 *	@ingroup    api_rtc
 *	@brief		Performs a busy loop delay of \b delay system ticks.
 *              The watchdog is continuously refreshed during the delay.
 *	@param[in]	delay	the number of system ticks of the delay, 1 tick is
 *						4ms. You can also use the HZ macro. See the
 *						\ref macros_rtc for more information.
 *	@retval		None
 */
void delay_ticks(uint16_t delay)
{
	wait_for_tout1 = delay;

	while (wait_for_tout1)
		sys_watchdog_reset();
}

/**
 *	@ingroup    api_rtc
 *	@brief		Programs the \b timeout variable, decremented each
 *	            system tick
 *	@param[in]	timeout expressed as number of system ticks.
 *	@retval		Nothing
 */
void rtc_set_timeout(uint16_t timeout)
{
	wait_for_tout2 = timeout;
}

/**
 *	@ingroup    api_rtc
 *	@brief		Returns a 1 if the programmed timeout expired. The timeout
 *	            is programmed with rtc_set_timeout()
 *	@param[in]	None
 *	@retval		1 if the timeout expired, 0 otherwise
 */
bool_t rtc_timeout_expired(void)
{
	return (wait_for_tout2 == 0) ? 1 : 0;
}

#ifdef RTC_ENABLE_CALENDAR
void update_date(void)
{		
	date.sec++;
	
	if (date.sec > 59) {
		date.sec -= 60;
		date.min++;

		if (date.min > 59) {
			date.min = 0;
			date.hour++;

			if (date.hour > 23) {
				date.hour = 0;
				date.mday++;

				if ((date.mday > 31) ||
					(date.mday == 31 && month_has_30_days(date.month)) ||
					(date.mday == 30 && date.month == 2) ||
					(date.mday == 29 && date.month == 2 && !leap_year(date.year))) {

					date.month++;
					date.mday = 1;
				}

				if (date.month > 12) {
					date.month = 1;
					date.year++;
				}
			}
		}
	}
#ifdef RTC_ENABLE_ALARM
	if (trigger_alarm()) {
#ifdef ENABLE_POWER_MANAGEMENT
		if (wakeup_irq == WAKEUP_UNKNOWN)
			wakeup_irq = WAKEUP_ALARM;
#endif /* ENABLE_POWER_MANAGEMENT */	
		rtc_alarm_task();
	}
#endif /* RTC_ENABLE_ALARM */
}
#endif /* RTC_ENABLE_CALENDAR */

#ifdef ENABLE_POWER_MANAGEMENT
#pragma INLINE
void check_clock_and_update(void)
{
	if (rtc_is_slow()) {
		ms_uptime += RTC_SLOW_MSEC_INC;
		uptime += RTC_SLOW_SEC_INC;
		
#ifdef RTC_ENABLE_CALENDAR
		update_date();
		/* Called twice because 2 seconds were incremented and alarm
		 * trigger is checked inside */
		update_date();
#endif /* RTC_ENABLE_CALENDAR */
	} else {
		ms_uptime += RTC_FAST_MSEC_INC;
		if (++ticks >= HZ) {
			uptime += ticks / HZ;
#ifdef RTC_ENABLE_CALENDAR
			if ((ticks / HZ) > 1)
				/* More than one second may have been increased during
				 * slow to fast transition. */
				update_date();
			update_date();
#endif /* RTC_ENABLE_CALENDAR */
			ticks %= HZ;
		}
	}
	 
	if (wakeup_irq == WAKEUP_UNKNOWN && seconds_to_wakeup && (uptime >= seconds_to_wakeup)) {
			wakeup_irq = WAKEUP_TIMEOUT;
	}
}

#pragma INLINE
void check_periodic_task(void)
{
#ifdef RTC_ENABLE_PERIODIC_TASK
	if (ticks_ptask_tout) {
		if (rtc_is_slow())
			ticks_ptask_cnt += RTC_SLOW_TICKS_INC;
		else
			ticks_ptask_cnt++;
		
		if (ticks_ptask_cnt >= ticks_ptask_tout) {
			ticks_ptask_cnt = 0;
			if (wakeup_irq == WAKEUP_UNKNOWN)
				wakeup_irq = WAKEUP_PERIODIC_TASK;
			rtc_periodic_task();
		}
	}
#endif /* RTC_ENABLE_PERIODIC_TASK */
}
#else
#pragma INLINE
void check_clock_and_update(void)
{
	ms_uptime += RTC_FAST_MSEC_INC;
	
	if (++ticks >= HZ) {
		uptime += ticks / HZ;
#ifdef RTC_ENABLE_CALENDAR
		update_date();
#endif /* RTC_ENABLE_CALENDAR */
		ticks %= HZ;
	}
}

#pragma INLINE
void check_periodic_task(void)
{
#ifdef RTC_ENABLE_PERIODIC_TASK
	if (ticks_ptask_tout) {
		ticks_ptask_cnt++;
		if (ticks_ptask_cnt >= ticks_ptask_tout) {
			ticks_ptask_cnt = 0;
			rtc_periodic_task();
		}
	}
#endif /* RTC_ENABLE_PERIODIC_TASK */
}

#endif /* ENABLE_POWER_MANAGEMENT */

#pragma TRAP_PROC
/**
 *	@ingroup    api_rtc
 *	@brief      RTC interrupt service routine
 *	@param      None
 *	@retval     None
 */
void rtc_isr(void)
{
	if (wait_for_tout1)
		wait_for_tout1--;
	if (wait_for_tout2)
		wait_for_tout2--;
	
	check_clock_and_update();
	check_periodic_task();

	/* Ack the interrupt */
	RTCSC_RTIF = 1;
	
}
#else
void rtc_isr(void) {}
#endif /* ENABLE_RTC */
