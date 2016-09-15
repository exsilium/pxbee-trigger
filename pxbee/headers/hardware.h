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

#ifndef __HARDWARE_H_
#define __HARDWARE_H_

#include <xbee_config.h>
#include <types.h>

/*
 * The xpin_t enumeration encodes the pin capabilities as follows:
 * -Bit 15: determines if the pin is IRQ capable
 * -Bit 14: determines if this pin has an alternative configuration
 * -Bits 13-10: PWM channel (0xf indicates no PWM capable)
 * -Bits 9-6: ADC channel (0xf indicates no ADC capable)
 * -Bits 5-3: Port (A, B, C, D or E)
 * -Bits 2-0: Port Bit (0-7) * 
 */

#define IRQABLE		(1 << 15)
#define HAS_ALT		(1 << 14)
#define PORTBIT_SH	0	/* 3 bits to encode the PORTBIT */
#define PORTBIT_MSK	0x7
#define PORT_SH		3	/* Port shift, 3 bits to encode the PORT */
#define PORT_MSK	0x7
#define ADCCH_SH	6	/* 4 bit to encode the ADC channel */
#define ADCCH_MSK	0xf
#define PWMCH_SH	10	/* 4 bit to encode the ADC channel */
#define PWMCH_MSK	0xf

#define PORT_A		(0 << PORT_SH)
#define PORT_B		(1 << PORT_SH)
#define PORT_C		(2 << PORT_SH)
#define PORT_D		(3 << PORT_SH)
#define PORT_E		(4 << PORT_SH)

#define PORTBIT(a)	((a) << PORTBIT_SH)
#define ADCCH(a)	((a) << ADCCH_SH)
#define NOADC		ADCCH(0xf)
#define PWMCH(a)	((a) << PWMCH_SH)
#define NOPWM		PWMCH(0xf)
#define NOGPIO		(PORT_MSK << PORT_SH)

#ifdef CONFIG_XBEE_THT
/** @ingroup types
 */
/// An enum for manage the pins of the S2B module, this typedef show the possibilities of the pins
typedef enum xpin {
	XPIN_1  = NOPWM | NOADC | NOGPIO,
	XPIN_2  = IRQABLE | NOPWM | ADCCH(5) | PORT_B | PORTBIT(1),
    XPIN_3  = IRQABLE | NOPWM | ADCCH(4) | PORT_B | PORTBIT(0),
    XPIN_4  = PWMCH(4) | NOADC | PORT_B | PORTBIT(4),
    XPIN_5  = NOPWM | NOADC | PORT_A | PORTBIT(5),
    XPIN_6  = PWMCH(11) | NOADC | PORT_C | PORTBIT(5),
    XPIN_7  = IRQABLE | NOPWM | ADCCH(2) | PORT_A | PORTBIT(2),
    XPIN_8  = NOPWM | NOADC | PORT_A | PORTBIT(4),
    XPIN_9  = IRQABLE | NOPWM | NOADC | PORT_D | PORTBIT(5),
    XPIN_10 = NOPWM | NOADC | NOGPIO,
    XPIN_11 = IRQABLE | NOPWM | ADCCH(7) | PORT_B | PORTBIT(3),
    XPIN_12 = PWMCH(6) | NOADC | PORT_C | PORTBIT(0),
    /* ON/SLEEP can not be configured yet with other functionality
     * than IRQ capability for ON/SLEEP support on S2B
     */
#ifndef CONFIG_XBEE_S2B
    XPIN_13 = IRQABLE | PWMCH(3) | ADCCH(1) | PORT_A | PORTBIT(1),
#else
    XPIN_13 = IRQABLE | NOPWM | NOADC | PORT_A | PORTBIT(1),
#endif
    XPIN_14 = NOPWM | NOADC | NOGPIO,
    XPIN_15 = IRQABLE | NOPWM | NOADC | PORT_D | PORTBIT(4),	
    XPIN_16 = IRQABLE | NOPWM | NOADC | PORT_D | PORTBIT(7),		
    XPIN_17 = PWMCH(5) | ADCCH(9) | PORT_B | PORTBIT(5),
    XPIN_18 = IRQABLE | NOPWM | ADCCH(6) | PORT_B | PORTBIT(2),
    XPIN_19 = IRQABLE | NOPWM | ADCCH(3) | PORT_A | PORTBIT(3),		
    XPIN_20 = IRQABLE | PWMCH(0) | ADCCH(0) | PORT_A | PORTBIT(0),		
    XPIN_UNDEF = NOPWM | NOADC | NOGPIO
} xpin_t;
/// \cond 

#define XBEE_MAX_XPIN	20
#define RESET_XPIN		XPIN_5
#define RSSI_XPIN		XPIN_6
#define BKGD_XPIN		XPIN_8
#define SLEEP_RQ_XPIN	XPIN_9
#define ON_SLEEP_XPIN	XPIN_13
#define ASSOC_XPIN		XPIN_15
#define COMMISS_XPIN	XPIN_20

/* Identifiers to enable special pin functionality */
#ifdef ENABLE_RESET_PIN_XPIN_5
#define ENABLE_RESET_PIN
#endif
#ifdef ENABLE_RSSI_PWM_XPIN_6
#define ENABLE_RSSI_PWM
#endif
#ifdef ENABLE_BKGD_PIN_XPIN_8
#define ENABLE_BKGD_PIN
#endif
#ifdef ENABLE_SLEEP_RQ_XPIN_9
#define ENABLE_SLEEP_RQ
#endif
#ifdef ENABLE_ON_SLEEP_XPIN_13
#define ENABLE_ON_SLEEP
#define ENABLE_GPIO_IRQ_XPIN_13
#define GPIO_CFG_IRQ_MODE_13		GPIO_CFG_EDGE_IRQ
#define GPIO_IRQ_LEVEL_EDGE_13		GPIO_IRQ_EDGE_RISE
#define GPIO_IRQ_CFG_PULL_13 		GPIO_IRQ_CFG_PULL_LOW
#endif
#ifdef ENABLE_ASSOCIATION_LED_XPIN_15
#define ENABLE_ASSOCIATION_LED
#endif
#ifdef ENABLE_COMMISSIONING_XPIN_20
#define ENABLE_COMMISSIONING
#endif

#if defined(ENABLE_GPIO_IRQ_XPIN_2) || defined(ENABLE_GPIO_IRQ_XPIN_3) || \
	defined(ENABLE_GPIO_IRQ_XPIN_7) || defined(ENABLE_GPIO_IRQ_XPIN_11) || \
	defined(ENABLE_GPIO_IRQ_XPIN_13) || defined(ENABLE_GPIO_IRQ_XPIN_18) || \
	defined(ENABLE_GPIO_IRQ_XPIN_19) || defined(ENABLE_GPIO_IRQ_XPIN_20)
#define ENABLE_BANK1_GPIO_IRQ
#endif
#if defined(ENABLE_GPIO_IRQ_XPIN_9) || defined(ENABLE_GPIO_IRQ_XPIN_15) || \
	defined(ENABLE_GPIO_IRQ_XPIN_16)
#define ENABLE_BANK2_GPIO_IRQ
#endif
#if defined(ENABLE_GPIO_XPIN_2) || defined(ENABLE_GPIO_XPIN_3) || \
	defined(ENABLE_GPIO_XPIN_4) || defined(ENABLE_GPIO_XPIN_5) || \
	defined(ENABLE_GPIO_XPIN_6) || defined(ENABLE_GPIO_XPIN_7) || \
	defined(ENABLE_GPIO_XPIN_8) || defined(ENABLE_GPIO_XPIN_9) || \
	defined(ENABLE_GPIO_XPIN_11) || defined(ENABLE_GPIO_XPIN_12) || \
	defined(ENABLE_GPIO_XPIN_13) || defined(ENABLE_GPIO_XPIN_15) || \
	defined(ENABLE_GPIO_XPIN_16) || defined(ENABLE_GPIO_XPIN_17) || \
	defined(ENABLE_GPIO_XPIN_18) || defined(ENABLE_GPIO_XPIN_19) || \
	defined(ENABLE_GPIO_XPIN_20) || \
	defined(ENABLE_BANK1_GPIO_IRQ) || defined(ENABLE_BANK2_GPIO_IRQ)
#define ENABLE_GPIO
#endif

#ifdef ENABLE_POWER_MANAGEMENT
/* Keyboard Interrupt pin assignments and call-back functions */
#ifdef ENABLE_GPIO_IRQ_XPIN_2
#define KBI1PE_KBIPE5_XPIN						XPIN_2
#define gpio_irq_handler_KBI1PE_KBIPE5_XPIN()	do{\
													if (wakeup_irq == WAKEUP_UNKNOWN)\
														wakeup_irq = WAKEUP_GPIO;\
													gpio_irq_handler_xpin_2();\
												} while(0)
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_3
#define KBI1PE_KBIPE4_XPIN						XPIN_3
#define gpio_irq_handler_KBI1PE_KBIPE4_XPIN()	do{\
													if (wakeup_irq == WAKEUP_UNKNOWN)\
														wakeup_irq = WAKEUP_GPIO;\
													gpio_irq_handler_xpin_3();\
												} while(0)
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_7
#define KBI1PE_KBIPE2_XPIN						XPIN_7
#define gpio_irq_handler_KBI1PE_KBIPE2_XPIN()	do{\
													if (wakeup_irq == WAKEUP_UNKNOWN)\
														wakeup_irq = WAKEUP_GPIO;\
													gpio_irq_handler_xpin_7();\
												} while(0)
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_11
#define KBI1PE_KBIPE7_XPIN						XPIN_11
#define gpio_irq_handler_KBI1PE_KBIPE7_XPIN()	do{\
													if (wakeup_irq == WAKEUP_UNKNOWN)\
														wakeup_irq = WAKEUP_GPIO;\
													gpio_irq_handler_xpin_11();\
												} while(0)
#endif

#ifdef ENABLE_GPIO_IRQ_XPIN_13
#define KBI1PE_KBIPE1_XPIN						XPIN_13
#if defined ENABLE_ON_SLEEP_XPIN_13
#define gpio_irq_handler_KBI1PE_KBIPE1_XPIN()	do{\
													if (wakeup_irq == WAKEUP_UNKNOWN)\
														wakeup_irq = WAKEUP_RADIO;\
													gpio_irq_handler_xpin_13();\
												} while(0)
#else
#define gpio_irq_handler_KBI1PE_KBIPE1_XPIN()	do{\
													if (wakeup_irq == WAKEUP_UNKNOWN)\
														wakeup_irq = WAKEUP_GPIO;\
													gpio_irq_handler_xpin_13();\
												} while(0)
#endif
#endif

#ifdef ENABLE_GPIO_IRQ_XPIN_18
#define KBI1PE_KBIPE6_XPIN						XPIN_18
#define gpio_irq_handler_KBI1PE_KBIPE6_XPIN()	do{\
													if (wakeup_irq == WAKEUP_UNKNOWN)\
														wakeup_irq = WAKEUP_GPIO;\
													gpio_irq_handler_xpin_18();\
												} while(0)
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_19
#define KBI1PE_KBIPE3_XPIN						XPIN_19
#define gpio_irq_handler_KBI1PE_KBIPE3_XPIN()	do{\
													if (wakeup_irq == WAKEUP_UNKNOWN)\
														wakeup_irq = WAKEUP_GPIO;\
													gpio_irq_handler_xpin_19();\
												} while(0)
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_20
#define KBI1PE_KBIPE0_XPIN						XPIN_20
#define gpio_irq_handler_KBI1PE_KBIPE0_XPIN()	do{\
													if (wakeup_irq == WAKEUP_UNKNOWN)\
														wakeup_irq = WAKEUP_GPIO;\
													gpio_irq_handler_xpin_20();\
												} while(0)
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_9
#define KBI2PE_KBIPE5_XPIN						XPIN_9
#define gpio_irq_handler_KBI2PE_KBIPE5_XPIN()	do{\
													if (wakeup_irq == WAKEUP_UNKNOWN)\
														wakeup_irq = WAKEUP_GPIO;\
													gpio_irq_handler_xpin_9();\
												} while(0)
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_15
#define KBI2PE_KBIPE4_XPIN						XPIN_15
#define gpio_irq_handler_KBI2PE_KBIPE4_XPIN()	do{\
													if (wakeup_irq == WAKEUP_UNKNOWN)\
														wakeup_irq = WAKEUP_GPIO;\
													gpio_irq_handler_xpin_15();\
												} while(0)
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_16
#define KBI2PE_KBIPE7_XPIN						XPIN_16
#define gpio_irq_handler_KBI2PE_KBIPE7_XPIN()	do{\
													if (wakeup_irq == WAKEUP_UNKNOWN)\
														wakeup_irq = WAKEUP_GPIO;\
													gpio_irq_handler_xpin_16();\
												} while(0)
#endif
#else /* ENABLE_POWER_MANAGEMENT */
#ifdef ENABLE_GPIO_IRQ_XPIN_2
#define KBI1PE_KBIPE5_XPIN						XPIN_2
#define gpio_irq_handler_KBI1PE_KBIPE5_XPIN		gpio_irq_handler_xpin_2
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_3
#define KBI1PE_KBIPE4_XPIN						XPIN_3
#define gpio_irq_handler_KBI1PE_KBIPE4_XPIN		gpio_irq_handler_xpin_3
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_7
#define KBI1PE_KBIPE2_XPIN						XPIN_7
#define gpio_irq_handler_KBI1PE_KBIPE2_XPIN		gpio_irq_handler_xpin_7
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_11
#define KBI1PE_KBIPE7_XPIN						XPIN_11
#define gpio_irq_handler_KBI1PE_KBIPE7_XPIN		gpio_irq_handler_xpin_11
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_13
#define KBI1PE_KBIPE1_XPIN						XPIN_13
#define gpio_irq_handler_KBI1PE_KBIPE1_XPIN		gpio_irq_handler_xpin_13
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_18
#define KBI1PE_KBIPE6_XPIN						XPIN_18
#define gpio_irq_handler_KBI1PE_KBIPE6_XPIN		gpio_irq_handler_xpin_18
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_19
#define KBI1PE_KBIPE3_XPIN						XPIN_19
#define gpio_irq_handler_KBI1PE_KBIPE3_XPIN		gpio_irq_handler_xpin_19
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_20
#define KBI1PE_KBIPE0_XPIN						XPIN_20
#define gpio_irq_handler_KBI1PE_KBIPE0_XPIN		gpio_irq_handler_xpin_20
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_9
#define KBI2PE_KBIPE5_XPIN						XPIN_9
#define gpio_irq_handler_KBI2PE_KBIPE5_XPIN		gpio_irq_handler_xpin_9
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_15
#define KBI2PE_KBIPE4_XPIN						XPIN_15
#define gpio_irq_handler_KBI2PE_KBIPE4_XPIN		gpio_irq_handler_xpin_15
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_16
#define KBI2PE_KBIPE7_XPIN						XPIN_16
#define gpio_irq_handler_KBI2PE_KBIPE7_XPIN		gpio_irq_handler_xpin_16
#endif
#endif /* ENABLE_POWER_MANAGEMENT */

#if defined(ENABLE_ICAPTURE_XPIN_4)
#define tpm2_ch1_irq							icapture_irq_xpin4		
#endif
#if defined(ENABLE_ICAPTURE_XPIN_6)
#define tpm3_ch5_irq							icapture_irq_xpin6		
#endif
#if defined(ENABLE_ICAPTURE_XPIN_12)
#define tpm3_ch0_irq							icapture_irq_xpin12		
#endif
#if defined(ENABLE_ICAPTURE_XPIN_17)
#define tpm2_ch2_irq							icapture_irq_xpin17		
#endif
#if defined(ENABLE_ICAPTURE_XPIN_20)
#define tpm1_ch0_irq							icapture_irq_xpin20		
#endif
#if defined(ENABLE_OCOMPARE_XPIN_4)
#define tpm2_ch1_irq							ocompare_irq_xpin4		
#endif
#if defined(ENABLE_OCOMPARE_XPIN_6)
#define tpm3_ch5_irq							ocompare_irq_xpin6		
#endif
#if defined(ENABLE_OCOMPARE_XPIN_12)
#define tpm3_ch0_irq							ocompare_irq_xpin12		
#endif
#if defined(ENABLE_OCOMPARE_XPIN_17)
#define tpm2_ch2_irq							ocompare_irq_xpin17		
#endif
#if defined(ENABLE_OCOMPARE_XPIN_20)
#define tpm1_ch0_irq							ocompare_irq_xpin20		
#endif
#endif /* CONFIG_XBEE_THT */

#ifdef CONFIG_XBEE_SMT
typedef enum xpin {
	XPIN_1  = NOPWM | NOADC | NOGPIO,
	XPIN_2  = NOPWM | NOADC | NOGPIO,
	XPIN_3  = IRQABLE | NOPWM | ADCCH(5) | PORT_B | PORTBIT(1),
	XPIN_4  = IRQABLE | NOPWM | ADCCH(4) | PORT_B | PORTBIT(0),
	XPIN_5  = PWMCH(4) | NOADC | PORT_B | PORTBIT(4),
	XPIN_6  = NOPWM | NOADC | PORT_A | PORTBIT(5),
	XPIN_7  = PWMCH(11) | NOADC | PORT_C | PORTBIT(5),
	XPIN_8  = IRQABLE | NOPWM | ADCCH(2) | PORT_A | PORTBIT(2),
	XPIN_9  = NOPWM | NOADC | PORT_A | PORTBIT(4),
	XPIN_10 = IRQABLE | NOPWM | NOADC | PORT_D | PORTBIT(5),
	XPIN_11 = NOPWM | NOADC | NOGPIO,
    XPIN_12 = IRQABLE | NOPWM | NOADC | PORT_D | PORTBIT(0),
	XPIN_13 = NOPWM | NOADC | NOGPIO,
    XPIN_14 = NOPWM | NOADC | PORT_E | PORTBIT(0),
    /* Disable capabilities of XPIN_15. Must be set to high (input)
     * to avoid asserting the Slave Select line of the SPI interface.
     * This allows to use the SPI pins for other purposes.
     * XPIN_15 = NOPWM | NOADC | PORT_E | PORTBIT(3),
     */
	XPIN_15 = NOPWM | NOADC | NOGPIO,
    XPIN_16 = NOPWM | NOADC | PORT_E | PORTBIT(1),
    XPIN_17 = NOPWM | NOADC | PORT_E | PORTBIT(2),
	XPIN_18 = NOPWM | NOADC | NOGPIO,
    XPIN_19 = NOPWM | NOADC | NOGPIO,
    XPIN_20 = NOPWM | NOADC | NOGPIO,
    XPIN_21 = NOPWM | NOADC | NOGPIO,
    XPIN_22 = NOPWM | NOADC | NOGPIO,
	XPIN_23 = NOPWM | NOADC | NOGPIO,
	XPIN_24 = IRQABLE | NOPWM | ADCCH(7) | PORT_B | PORTBIT(3),
	XPIN_25 = PWMCH(6) | NOADC | PORT_C | PORTBIT(0),
	XPIN_26 = IRQABLE | PWMCH(3) | ADCCH(1) | PORT_A | PORTBIT(1),
	XPIN_27 = NOPWM | NOADC | NOGPIO,
	XPIN_28 = IRQABLE | NOPWM | NOADC | PORT_D | PORTBIT(4),	
	XPIN_29 = IRQABLE | NOPWM | NOADC | PORT_D | PORTBIT(7),	
    XPIN_30 = PWMCH(5) | ADCCH(9) | PORT_B | PORTBIT(5),
    XPIN_31 = IRQABLE | NOPWM | ADCCH(6) | PORT_B | PORTBIT(2),
    XPIN_32 = IRQABLE | NOPWM | ADCCH(3) | PORT_A | PORTBIT(3),		
    XPIN_33 = IRQABLE | PWMCH(0) | ADCCH(0) | PORT_A | PORTBIT(0),		
	XPIN_34 = NOPWM | NOADC | NOGPIO,
	XPIN_35 = NOPWM | NOADC | NOGPIO,
	XPIN_36 = NOPWM | NOADC | NOGPIO,
	XPIN_37 = NOPWM | NOADC | NOGPIO,
	XPIN_UNDEF = NOPWM | NOADC | NOGPIO
} xpin_t;

#define XBEE_MAX_XPIN	37
#define RESET_XPIN		XPIN_6
#define RSSI_XPIN		XPIN_7
#define BKGD_XPIN		XPIN_9
#define SLEEP_RQ_XPIN	XPIN_10
#define ON_SLEEP_XPIN	XPIN_26
#define ASSOC_XPIN		XPIN_28
#define COMMISS_XPIN	XPIN_33

/* Identifiers to enable special pin functionality */
#ifdef ENABLE_RESET_PIN_XPIN_6
#define ENABLE_RESET_PIN
#endif
#ifdef ENABLE_RSSI_PWM_XPIN_7
#define ENABLE_RSSI_PWM
#endif
#ifdef ENABLE_BKGD_PIN_XPIN_9
#define ENABLE_BKGD_PIN
#endif
#ifdef ENABLE_SLEEP_RQ_XPIN_10
#define ENABLE_SLEEP_RQ
#endif
#ifdef ENABLE_ON_SLEEP_XPIN_26
#define ENABLE_ON_SLEEP
#define ENABLE_GPIO_IRQ_XPIN_26
#define GPIO_CFG_IRQ_MODE_26		GPIO_CFG_EDGE_IRQ
#define GPIO_IRQ_LEVEL_EDGE_26		GPIO_IRQ_EDGE_RISE
#define GPIO_IRQ_CFG_PULL_26 		GPIO_IRQ_CFG_PULL_LOW
#endif
#ifdef ENABLE_ASSOCIATION_LED_XPIN_28
#define ENABLE_ASSOCIATION_LED
#endif
#ifdef ENABLE_COMMISSIONING_XPIN_33
#define ENABLE_COMMISSIONING
#endif

#if defined(ENABLE_GPIO_IRQ_XPIN_3) || defined(ENABLE_GPIO_IRQ_XPIN_4) || 	\
	defined(ENABLE_GPIO_IRQ_XPIN_8) || defined(ENABLE_GPIO_IRQ_XPIN_24) || 	\
	defined(ENABLE_GPIO_IRQ_XPIN_19) || defined(ENABLE_GPIO_IRQ_XPIN_26) || \
	defined(ENABLE_GPIO_IRQ_XPIN_31) || defined(ENABLE_GPIO_IRQ_XPIN_32) || \
	defined(ENABLE_GPIO_IRQ_XPIN_33)
#define ENABLE_BANK1_GPIO_IRQ
#endif
#if defined(ENABLE_GPIO_IRQ_XPIN_10) || defined(ENABLE_GPIO_IRQ_XPIN_20) || \
	defined(ENABLE_GPIO_IRQ_XPIN_28) || defined(ENABLE_GPIO_IRQ_XPIN_29)
#define ENABLE_BANK2_GPIO_IRQ
#endif
#if defined(ENABLE_GPIO_XPIN_3) || defined(ENABLE_GPIO_XPIN_4) || 		\
	defined(ENABLE_GPIO_XPIN_5) || defined(ENABLE_GPIO_XPIN_6) || 		\
	defined(ENABLE_GPIO_XPIN_7) || defined(ENABLE_GPIO_XPIN_8) || 		\
	defined(ENABLE_GPIO_XPIN_9) || defined(ENABLE_GPIO_XPIN_10) || 		\
	defined(ENABLE_GPIO_XPIN_12) || defined(ENABLE_GPIO_XPIN_14) || 	\
	defined(ENABLE_GPIO_XPIN_15) || defined(ENABLE_GPIO_XPIN_16) || 	\
	defined(ENABLE_GPIO_XPIN_17) || defined(ENABLE_GPIO_XPIN_19) || 	\
	defined(ENABLE_GPIO_XPIN_20) || defined(ENABLE_GPIO_XPIN_21) || 	\
	defined(ENABLE_GPIO_XPIN_24) || defined(ENABLE_GPIO_XPIN_25) || 	\
	defined(ENABLE_GPIO_XPIN_26) || defined(ENABLE_GPIO_XPIN_28) || 	\
	defined(ENABLE_GPIO_XPIN_29) || defined(ENABLE_GPIO_XPIN_30) || 	\
	defined(ENABLE_GPIO_XPIN_31) || defined(ENABLE_GPIO_XPIN_32) || 	\
	defined(ENABLE_GPIO_XPIN_33) || defined(ENABLE_BANK1_GPIO_IRQ) || 	\
	defined(ENABLE_BANK2_GPIO_IRQ)
#define ENABLE_GPIO
#endif

/* Keyboard Interrupt pin assignments and call-back functions */
#ifdef ENABLE_POWER_MANAGEMENT
#ifdef ENABLE_GPIO_IRQ_XPIN_3
#define KBI1PE_KBIPE5_XPIN						XPIN_3
#define gpio_irq_handler_KBI1PE_KBIPE5_XPIN()	do{\
													if (wakeup_irq == WAKEUP_UNKNOWN)\
														wakeup_irq = WAKEUP_GPIO;\
													gpio_irq_handler_xpin_3();\
												} while(0)
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_4
#define KBI1PE_KBIPE4_XPIN						XPIN_4
#define gpio_irq_handler_KBI1PE_KBIPE4_XPIN()	do{\
													if (wakeup_irq == WAKEUP_UNKNOWN)\
														wakeup_irq = WAKEUP_GPIO;\
													gpio_irq_handler_xpin_4();\
												} while(0)
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_8
#define KBI1PE_KBIPE2_XPIN						XPIN_8
#define gpio_irq_handler_KBI1PE_KBIPE2_XPIN()	do{\
													if (wakeup_irq == WAKEUP_UNKNOWN)\
														wakeup_irq = WAKEUP_GPIO;\
													gpio_irq_handler_xpin_8();\
												} while(0)
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_24
#define KBI1PE_KBIPE7_XPIN						XPIN_24
#define gpio_irq_handler_KBI1PE_KBIPE7_XPIN()	do{\
													if (wakeup_irq == WAKEUP_UNKNOWN)\
														wakeup_irq = WAKEUP_GPIO;\
													gpio_irq_handler_xpin_24();\
												} while(0)
#endif

#ifdef ENABLE_GPIO_IRQ_XPIN_26
#define KBI1PE_KBIPE1_XPIN						XPIN_26
#if defined ENABLE_ON_SLEEP_XPIN_26
#define gpio_irq_handler_KBI1PE_KBIPE1_XPIN()	do{\
													if (wakeup_irq == WAKEUP_UNKNOWN)\
														wakeup_irq = WAKEUP_RADIO;\
													gpio_irq_handler_xpin_26();\
												} while(0)
#else
#define gpio_irq_handler_KBI1PE_KBIPE1_XPIN()	do{\
													if (wakeup_irq == WAKEUP_UNKNOWN)\
														wakeup_irq = WAKEUP_GPIO;\
													gpio_irq_handler_xpin_26();\
												} while(0)
#endif
#endif

#ifdef ENABLE_GPIO_IRQ_XPIN_31
#define KBI1PE_KBIPE6_XPIN						XPIN_31
#define gpio_irq_handler_KBI1PE_KBIPE6_XPIN()	do{\
													if (wakeup_irq == WAKEUP_UNKNOWN)\
														wakeup_irq = WAKEUP_GPIO;\
													gpio_irq_handler_xpin_31();\
												} while(0)
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_32
#define KBI1PE_KBIPE3_XPIN						XPIN_32
#define gpio_irq_handler_KBI1PE_KBIPE3_XPIN()	do{\
													if (wakeup_irq == WAKEUP_UNKNOWN)\
														wakeup_irq = WAKEUP_GPIO;\
													gpio_irq_handler_xpin_32();\
												} while(0)
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_33
#define KBI1PE_KBIPE0_XPIN						XPIN_33
#define gpio_irq_handler_KBI1PE_KBIPE0_XPIN()	do{\
													if (wakeup_irq == WAKEUP_UNKNOWN)\
														wakeup_irq = WAKEUP_GPIO;\
													gpio_irq_handler_xpin_33();\
												} while(0)
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_10
#define KBI2PE_KBIPE5_XPIN						XPIN_10
#define gpio_irq_handler_KBI2PE_KBIPE5_XPIN()	do{\
													if (wakeup_irq == WAKEUP_UNKNOWN)\
														wakeup_irq = WAKEUP_GPIO;\
													gpio_irq_handler_xpin_10();\
												} while(0)
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_20
#define KBI2PE_KBIPE4_XPIN						XPIN_20
#define gpio_irq_handler_KBI2PE_KBIPE4_XPIN()	do{\
													if (wakeup_irq == WAKEUP_UNKNOWN)\
														wakeup_irq = WAKEUP_GPIO;\
													gpio_irq_handler_xpin_20();\
												} while(0)
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_28
#define KBI2PE_KBIPE4_XPIN						XPIN_28
#define gpio_irq_handler_KBI2PE_KBIPE4_XPIN()	do{\
													if (wakeup_irq == WAKEUP_UNKNOWN)\
														wakeup_irq = WAKEUP_GPIO;\
													gpio_irq_handler_xpin_28();\
												} while(0)
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_29
#define KBI2PE_KBIPE7_XPIN						XPIN_29
#define gpio_irq_handler_KBI2PE_KBIPE7_XPIN()	do{\
													if (wakeup_irq == WAKEUP_UNKNOWN)\
														wakeup_irq = WAKEUP_GPIO;\
													gpio_irq_handler_xpin_29();\
												} while(0)
#endif
#else /* ENABLE_POWER_MANAGEMENT */
/* Keyboard Interrupt pin assignments and call-back functions */
#ifdef ENABLE_GPIO_IRQ_XPIN_3
#define KBI1PE_KBIPE5_XPIN						XPIN_3
#define gpio_irq_handler_KBI1PE_KBIPE5_XPIN		gpio_irq_handler_xpin_3
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_4
#define KBI1PE_KBIPE4_XPIN						XPIN_4
#define gpio_irq_handler_KBI1PE_KBIPE4_XPIN		gpio_irq_handler_xpin_4
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_8
#define KBI1PE_KBIPE2_XPIN						XPIN_8
#define gpio_irq_handler_KBI1PE_KBIPE2_XPIN		gpio_irq_handler_xpin_8
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_24
#define KBI1PE_KBIPE7_XPIN						XPIN_24
#define gpio_irq_handler_KBI1PE_KBIPE7_XPIN		gpio_irq_handler_xpin_24
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_26
#define KBI1PE_KBIPE1_XPIN						XPIN_26
#define gpio_irq_handler_KBI1PE_KBIPE1_XPIN		gpio_irq_handler_xpin_26
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_31
#define KBI1PE_KBIPE6_XPIN						XPIN_31
#define gpio_irq_handler_KBI1PE_KBIPE6_XPIN		gpio_irq_handler_xpin_31
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_32
#define KBI1PE_KBIPE3_XPIN						XPIN_32
#define gpio_irq_handler_KBI1PE_KBIPE3_XPIN		gpio_irq_handler_xpin_32
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_33
#define KBI1PE_KBIPE0_XPIN						XPIN_33
#define gpio_irq_handler_KBI1PE_KBIPE0_XPIN		gpio_irq_handler_xpin_33
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_10
#define KBI2PE_KBIPE5_XPIN						XPIN_10
#define gpio_irq_handler_KBI2PE_KBIPE5_XPIN		gpio_irq_handler_xpin_10
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_20
#define KBI2PE_KBIPE4_XPIN						XPIN_20
#define gpio_irq_handler_KBI2PE_KBIPE4_XPIN		gpio_irq_handler_xpin_20
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_28
#define KBI2PE_KBIPE4_XPIN						XPIN_28
#define gpio_irq_handler_KBI2PE_KBIPE4_XPIN		gpio_irq_handler_xpin_28
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_29
#define KBI2PE_KBIPE7_XPIN						XPIN_29
#define gpio_irq_handler_KBI2PE_KBIPE7_XPIN		gpio_irq_handler_xpin_29
#endif
#endif /* ENABLE_POWER_MANAGEMENT */

#ifdef ENABLE_ICAPTURE_XPIN_5
#define tpm2_ch1_irq							icapture_irq_xpin5		
#endif
#ifdef ENABLE_ICAPTURE_XPIN_7
#define tpm3_ch5_irq							icapture_irq_xpin7		
#endif
#ifdef ENABLE_ICAPTURE_XPIN_25
#define tpm3_ch0_irq							icapture_irq_xpin25		
#endif
#ifdef ENABLE_ICAPTURE_XPIN_26
#define tpm2_ch0_irq							icapture_irq_xpin26		
#endif
#ifdef ENABLE_ICAPTURE_XPIN_30
#define tpm1_ch1_irq							icapture_irq_xpin30		
#endif
#ifdef ENABLE_ICAPTURE_XPIN_33
#define tpm1_ch0_irq							icapture_irq_xpin33		
#endif
#ifdef ENABLE_OCOMPARE_XPIN_5
#define tpm2_ch1_irq							ocompare_irq_xpin5		
#endif
#ifdef ENABLE_OCOMPARE_XPIN_7
#define tpm3_ch5_irq							ocompare_irq_xpin7		
#endif
#ifdef ENABLE_OCOMPARE_XPIN_25
#define tpm3_ch0_irq							ocompare_irq_xpin25		
#endif
#ifdef ENABLE_OCOMPARE_XPIN_26
#define tpm2_ch0_irq							ocompare_irq_xpin26		
#endif
#ifdef ENABLE_OCOMPARE_XPIN_30
#define tpm2_ch2_irq							ocompare_irq_xpin30		
#endif
#ifdef ENABLE_OCOMPARE_XPIN_33
#define tpm1_ch0_irq							ocompare_irq_xpin33		
#endif
#endif /* CONFIG_XBEE_SMT */

#if CONFIG_XBEE_FLASH_LEN > 32
/* Constants and addresses for the 128KB variant */
typedef uint32_t maddr_t;
#define APP_VERSION_ADDR	@0x0000EFBC
/* Protect from 0xf000 to 0xffff, the bootloader */
#define NVPROT_INIT_VAL		(0x7b << 1)

/**
 * On the large mem variants, there are 2 I2C interfaces, but only I2C1 is
 * used/supported. This macros keep the code common.
 */
#define IICS_BUSY			IIC1S_BUSY
#define IICS_IICIF			IIC1S_IICIF
#define IICS_RXAK			IIC1S_RXAK
#define IICC				IIC1C
#define IICD				IIC1D
#define IICF				IIC1F
#define IICC_TX				IIC1C_TX
#define IICC_TXAK			IIC1C_TXAK
#define IICC_RSTA			IIC1C_RSTA

#else /* CONFIG_XBEE_FLASH_LEN > 32 */
typedef uint16_t maddr_t;
/* Constants and addresses for the 32KB variant */
#define APP_VERSION_ADDR	@0x0000F1BC
/* Protect from 0xf200 to 0xffff, the bootloader. Must be protected to 
 * enable vector redirection
 */
#define NVPROT_INIT_VAL		(0xf0)
#endif /* CONFIG_XBEE_FLASH_LEN > 32 */

#endif /* __HARDWARE_H_ */
/// \endcond
