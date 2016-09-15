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
 *	Platform-specific layer provides a consistent Power Management API to 
 *	upper layers of the driver. 
 *
 *	@ingroup cpu_pm 
 *
 *	@defgroup cpu_pm 
 *
 *	@section pm Power Management API Overview 
 *
 *	This API contains the code to configure the operational mode of the
 *	programmable XBee devices. Allows to set the mode of the
 *	CPU and of the radio chip.
 *	
 *	- Power Management configuration functions:
 *		- pm_set_cpu_mode()
 *		- pm_get_cpu_mode()
 *		- pm_set_radio_mode()
 *		- pm_get_radio_mode()
 *		- pm_get_wakeup_source()
 */
#include <system.h>
#include <errno.h>
#include <types.h>
#include <pm.h>
#include <gpios.h>
#include <xbee/atcmd.h>

#define stop()		asm(stop;)
#define	wait()		asm(wait;)

#ifdef ENABLE_POWER_MANAGEMENT

extern xbee_dev_t xdev;
pm_mode_t pm_state = PM_MODE_RUN;

uint32_t seconds_to_wakeup = 0;
uint8_t wakeup_irq = WAKEUP_UNKNOWN;

extern uint8_t rtc_is_slow(void);
extern void rtc_config_slow(void);
extern void rtc_config_fast(void);

#ifdef ENABLE_ON_SLEEP
#if defined(ENABLE_ON_SLEEP_XPIN_13)
void gpio_irq_handler_xpin_13(void)
#elif defined(ENABLE_ON_SLEEP_XPIN_26)
void gpio_irq_handler_xpin_26(void)
#endif
{
	/* Just wakeup the CPU */
}
#endif

/**
 *	@ingroup cpu_pm
 *	@brief		Function that configures the CPU operation mode to \b mode.
 *	@param[in]	mode	        The operating mode. Valid modes are:
 *	                            PM_MODE_RUN to set the CPU in the normal operational
 *	                            mode
 *	                            PM_MODE_WAIT to set the CPU in wait mode (CPU is
 *	                            shutdown but the system clocks are running and the 
 *	                            full regulation is maintained
 *	                            PM_MODE_STOP_2 to set the CPU in Stop2 mode (system
 *	                            clocks are stopped and voltage regulator is in 
 *	                            standby), partial power down of internal ciruits.
 *	                            PM_MODE_STOP_3 to set the CPU in Stop3 mode (system
 *	                            clocks are stopped and voltage regulator is in
 *	                            standby), all internal circuits are powered for fast
 *	                            recovery.
 *	@param[in] sleep_seconds	The number of seconds the device will sleep 
 *                              before waking waking up. Use WAIT_INFINITE (0)
 *                              to wake up only by IRQs.
 *	@retval 	EINVAL  incorrect mode
 *	@retval		0		on success.
 */
int pm_set_cpu_mode(pm_mode_t mode, uint32_t sleep_seconds)
{
	uint8_t mask = 0;
	
	if (mode > PM_MODE_STOP_3)
		return -EINVAL;

	switch (mode) {
	case PM_MODE_RUN:	
		/* Already running and Run LP is not supported, due to the
		 * lack of external clock, so... we do nothing here */
		
		/* Here we should restore the clock ??? 
		 * This means, we force to call pm_set_cpu_mode(PM_MODE_RUN)
		 * on the interrupt handler of the interrupt that woke up the 
		 * CPU */
		break;
		
	case PM_MODE_WAIT:
		/* Wait LP is not supported, so... just wait */
		wait();
		break;

	case PM_MODE_STOP_2:
		mask = 1;
	case PM_MODE_STOP_3:
	case PM_MODE_STOP:
		/* STOPE bit is already set (in SOPT1) by the initialization code */
#if (POWER_MANAGEMENT_ENABLE_LVD == 1)
		SPMSC1_LVDSE = 1; /* Enable Low Voltage Detection on Stop3 mode */
#else
		SPMSC1_LVDSE = 0; /* Disable Low Voltage Detection on Stop3 mode */
#endif

		SPMSC2_PPDE = 1; /* Enable STOP3 MODE */
		pm_state = PM_MODE_STOP_3;
		
#ifdef ENABLE_WAKEUP_FROM_UART
		SCI1BDH_RXEDGIE = 1; /* Enable RxD Interrupt */
#endif
	
#if (POWER_MANAGEMENT_KEEP_UPTIME == 1)
		/* Enable IRCLK in stop3 mode so RTC can wake up the CPU */
		ICSC1_IREFSTEN = 1;
		/* The CPU is going to sleep, but before the system tick frequency is
		 * reconfigured to 2 seconds, to sleep longer and minimize the power 
		 * consumption. Later, its needed to differentiate the system tick
		 * interrupts, from the real wakeup interrupts. This is done in the
		 * RTC interrupt handler.
		 */
		seconds_to_wakeup = sleep_seconds ? uptime + sleep_seconds : WAIT_INFINITE;
		rtc_config_slow();

		/* If the program does not loop on this, it would wake up every time a
		 * RTC IRQ is asserted, configuring the RTC as "slow" this happens every
		 * 2 seconds */
		wakeup_irq = WAKEUP_UNKNOWN;
		do {
			stop();			
		} while(wakeup_irq == WAKEUP_UNKNOWN);
		rtc_config_fast();

#else
		ICSC1_IREFSTEN = 0;
		/* Loop until IRQ asserted... */
		wakeup_irq = WAKEUP_UNKNOWN;
		do {
			stop();
		} while(wakeup_irq == WAKEUP_UNKNOWN);
#endif /* (POWER_MANAGEMENT_KEEP_UPTIME == 1) */
		
#ifdef ENABLE_WAKEUP_FROM_UART
		SCI1BDH_RXEDGIE = 0; /* Disable RxD Interrupt */
#endif

		PTDDD_PTDDD6 = 0; /* Radio_CTS  */
		break;
	}
	return 0;
}

/**
 *	@ingroup cpu_pm
 *	@brief		Function that returns which was the last wake up source for the CPU.
 *	@retval		uint8_t	The current wakeup source. Possible values:
 *	                    - WAKEUP_UNKNOWN
 *						- WAKEUP_UART
 *						- WAKEUP_PERIODIC_TASK
 *						- WAKEUP_TIMEOUT
 *						- WAKEUP_ALARM
 *						- WAKEUP_GPIO
 *						- WAKEUP_RADIO
 */
uint8_t pm_get_wakeup_source(void)
{
	return wakeup_irq;
}

/**
 *	@ingroup cpu_pm
 *	@brief		Function that returns the CPU operational mode.
 *	@retval		pm_mode_t	The current CPU operational mode.
 */
pm_mode_t pm_get_cpu_mode(void)
{
	/* Well, if we are able to answer we must be running... */
	return PM_MODE_RUN;
}

/**
 *	@ingroup cpu_pm
 *	@brief		Function that configures the radio operation mode to \b mode.
 *	@param[in]	mode	The operating mode. Valid modes are:
 *	                    PM_MODE_RUN if the SLEEP_RQ pin is enabled, wakes up
 *	                    the radio using that pin.
 *	                    PM_MODE_STOP sends a Sleep Immediately command to put 
 *	                    the radio in low power mode, entering automatically in
 *	                    cyclic sleep, independently of the ST timer value.
 *	@retval 	nothing.
 */
void pm_set_radio_mode(pm_mode_t mode)
{	
#ifdef ENABLE_SLEEP_RQ
	if (mode == PM_MODE_RUN) {
		if (gpio_get(SLEEP_RQ_XPIN) == 0) /* nothing to do... */
			return;
		(void)gpio_set(SLEEP_RQ_XPIN, 0);	/* high to low on sleep request */
	} else if (mode == PM_MODE_STOP || mode == PM_MODE_STOP_3) {
		if (gpio_get(SLEEP_RQ_XPIN) == 1) /* nothing to do... */
			return;
		(void)gpio_set(SLEEP_RQ_XPIN, 1);
	}
#else
	if (mode == PM_MODE_STOP)
		xbee_cmd_execute(&xdev, "SI", NULL, 0);	/* Sleep Immediately */
#endif

	return;
}

/**
 *	@ingroup cpu_pm
 *	@brief		Function that returns the radio operational mode.
 *              We consider radio operative when On/Sleep pin is high and CTS# is low
 *	@retval		pm_mode_t	The current radio operational mode.
 */
pm_mode_t pm_get_radio_mode(void)
{
#ifdef ENABLE_ON_SLEEP
	/* Intentionally not checking (xbee->flags & XBEE_DEV_FLAG_USE_FLOWCONTROL) */
	return (gpio_get(ON_SLEEP_XPIN) && xbee_ser_get_cts( &xdev.serport) ) ? PM_MODE_RUN : PM_MODE_STOP;
#else
	return xbee_ser_get_cts( &xdev.serport) ? PM_MODE_RUN : PM_MODE_STOP;
#endif
}
#endif /* ENABLE_POWER_MANAGEMENT */
