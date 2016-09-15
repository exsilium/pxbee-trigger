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
/** Platform-specific layer provides a consistent MACROS API to upper layers
 *	of the driver.
 *	
 *	@ingroup api_gpios
 *	
 *	@defgroup api_gpios_gpio
 *	
 *	@section macros_gpio Standard GPIO Macros
 *	
 *	The gpio_config() function needs as second parameter a byte containing the 
 *	configuration masks for the GPIO. These masks are defined with macros and 
 *	they are the following:
 *	
 *		- Macros to configure the GPIO \b type:
 * 			- \b GPIO_CFG_INPUT 			: Configures the standard GPIO as 
 * 											  input.
 *			- \b GPIO_CFG_OUTPUT			: Configures the standard GPIO as
 *											  output.
 *	
 *		- Macros to configure the \b pullup resistors:
 *			- \b GPIO_CFG_PULL_UP_DIS		: Disables the GPIO Pull-up resistor.
 *			- \b GPIO_CFG_PULL_UP_EN		: Enables the GPIO Pull-up resistor.
 *	
 *		- Macros to configure the \b slew \b rate:
 *			- \b GPIO_CFG_SLEW_RATE_DIS	: Disables the GPIO slew rate.
 *			- \b GPIO_CFG_SLEW_RATE_EN 	: Enables the GPIO slew rate.
 *	
 *		- Macros to configure the \b drive \b strength:
 *			- \b GPIO_CFG_DRV_STR_LOW		: Configures the drive strength to low.
 *			- \b GPIO_CFG_DRV_STR_HIGH 		: Configures the drive strength to high.
 *	
 *	Usage example:
 *	@code gpio_config(XPIN_7, GPIO_CFG_INPUT | GPIO_CFG_PULL_UP_EN | GPIO_CFG_SLEW_RATE_EN | GPIO_CFG_DRV_STR_LOW);
 *	@endcode
 *	@warning	It is recommended not to use these macros, they are used by 
 *				the XBee Project Smart Editor of the XBee extensions.
 *	
 *	@ingroup api_gpios
 *	
 *	@defgroup api_gpios_irq
 *	
 *	@section macros_irq IRQ Macros 
 *	
 *	The gpio_config_irq() function needs as second and third parameters the 
 *	detection and activation modes to configure the IRQ. These parameters 
 *	are defined with macros and they are the following:
 *	
 *		- Macros to configure the \b detection \b mode of the IRQ: 
 *			- \b GPIO_CFG_LEVEL_IRQ 		: Configures the detection mode as
 *											  level - \b 0.
 *			- \b GPIO_CFG_EDGE_IRQ			: Configures the detection mode as
 *											  edge - \b 1.
 *	
 *		- Macros to configure the \b active \b edge (when the detection 
 *		  mode is configured as \b edge):
 *			- \b GPIO_IRQ_EDGE_RISE 		: Select the rise-edge mode - \b 1.
 *			- \b GPIO_IRQ_EDGE_FALL 		: Select the fall-edge mode - \b 0.
 *	
 *		- Macros to configure the \b active \b level (when the detection 
 *		  mode is configured as \b level):
 *			- \b GPIO_IRQ_LEVEL_HIGH 		: Select the high-level mode - \b 1.
 *			- \b GPIO_IRQ_LEVEL_LOW 		: Select the low-level mode - \b 0.
 *	
 *	Usage example:
 *	@code gpio_config_irq(XPIN_7, GPIO_CFG_LEVE_IRQ, GPIO_IRQ_LEVEL_HIGH);
 *	@endcode
 *	@warning	It is recommended not to use these macros, they are used by 
 *				the XBee Project Smart Editor of the XBee extensions.
 *
 ***************************************************************************/

#ifndef __GPIO_H_
#define __GPIO_H_

#include <types.h>
#include <hardware.h>


#define GPIO_CFG_INPUT				(0 << 0)
#define GPIO_CFG_OUTPUT				(1 << 0)
#define GPIO_CFG_PULL_UP_DIS		(0 << 1)
#define GPIO_CFG_PULL_UP_EN			(1 << 1)
#define GPIO_CFG_SLEW_RATE_DIS		(0 << 2)
#define GPIO_CFG_SLEW_RATE_EN		(1 << 2)
#define GPIO_CFG_DRV_STR_LOW		(0 << 3)
#define GPIO_CFG_DRV_STR_HIGH		(1 << 3)

#define GPIO_CFG_LEVEL_IRQ			0
#define GPIO_CFG_EDGE_IRQ			1

#define GPIO_IRQ_EDGE_RISE			(1)
#define GPIO_IRQ_EDGE_FALL			(0)
#define GPIO_IRQ_LEVEL_HIGH			(1)
#define GPIO_IRQ_LEVEL_LOW			(0)
#define GPIO_IRQ_CFG_PULL_NONE		(0)
#define GPIO_IRQ_CFG_PULL_LOW		(1)
#define GPIO_IRQ_CFG_PULL_HIGH		(2)


#ifdef ENABLE_GPIO_XPIN_2
#define GPIO_CFG_XPIN_2		(GPIO_CFG_DIR_2 |			\
							 GPIO_CFG_PULL_UP_EN_2 |	\
							 GPIO_CFG_SLEW_RATE_EN_2 |	\
							 GPIO_CFG_DRV_STR_2)
#endif
#ifdef ENABLE_GPIO_XPIN_3
#define GPIO_CFG_XPIN_3		(GPIO_CFG_DIR_3 |			\
							 GPIO_CFG_PULL_UP_EN_3 |	\
							 GPIO_CFG_SLEW_RATE_EN_3 |	\
							 GPIO_CFG_DRV_STR_3)
#endif
#ifdef ENABLE_GPIO_XPIN_4
#define GPIO_CFG_XPIN_4		(GPIO_CFG_DIR_4 |			\
							 GPIO_CFG_PULL_UP_EN_4 |	\
							 GPIO_CFG_SLEW_RATE_EN_4 |	\
							 GPIO_CFG_DRV_STR_4)
#endif
#ifdef ENABLE_GPIO_XPIN_5
#define GPIO_CFG_XPIN_5		(GPIO_CFG_DIR_5 |			\
							 GPIO_CFG_PULL_UP_EN_5 |	\
							 GPIO_CFG_SLEW_RATE_EN_5 |	\
							 GPIO_CFG_DRV_STR_5)
#endif
#ifdef ENABLE_GPIO_XPIN_6
#define GPIO_CFG_XPIN_6		(GPIO_CFG_DIR_6 |			\
							 GPIO_CFG_PULL_UP_EN_6 |	\
							 GPIO_CFG_SLEW_RATE_EN_6 |	\
							 GPIO_CFG_DRV_STR_6)
#endif
#ifdef ENABLE_GPIO_XPIN_7
#define GPIO_CFG_XPIN_7		(GPIO_CFG_DIR_7 |			\
							 GPIO_CFG_PULL_UP_EN_7 |	\
							 GPIO_CFG_SLEW_RATE_EN_7 |	\
							 GPIO_CFG_DRV_STR_7)
#endif
#ifdef ENABLE_GPIO_XPIN_8
#define GPIO_CFG_XPIN_8		(GPIO_CFG_DIR_8 |			\
							 GPIO_CFG_PULL_UP_EN_8 |	\
							 GPIO_CFG_SLEW_RATE_EN_8 |	\
							 GPIO_CFG_DRV_STR_8)
#endif
#ifdef ENABLE_GPIO_XPIN_9
#define GPIO_CFG_XPIN_9		(GPIO_CFG_DIR_9 |			\
							 GPIO_CFG_PULL_UP_EN_9 |	\
							 GPIO_CFG_SLEW_RATE_EN_9 |	\
							 GPIO_CFG_DRV_STR_9)
#endif
#ifdef ENABLE_GPIO_XPIN_10
#define GPIO_CFG_XPIN_10	 (GPIO_CFG_DIR_10 |			\
							 GPIO_CFG_PULL_UP_EN_10 |	\
							 GPIO_CFG_SLEW_RATE_EN_10 |	\
							 GPIO_CFG_DRV_STR_10)
#endif
#ifdef ENABLE_GPIO_XPIN_11
#define GPIO_CFG_XPIN_11	(GPIO_CFG_DIR_11 |			\
							 GPIO_CFG_PULL_UP_EN_11 |	\
							 GPIO_CFG_SLEW_RATE_EN_11 |	\
							 GPIO_CFG_DRV_STR_11)
#endif
#ifdef ENABLE_GPIO_XPIN_12
#define GPIO_CFG_XPIN_12	(GPIO_CFG_DIR_12 |			\
							 GPIO_CFG_PULL_UP_EN_12 |	\
							 GPIO_CFG_SLEW_RATE_EN_12 |	\
							 GPIO_CFG_DRV_STR_12)
#endif
#ifdef ENABLE_GPIO_XPIN_13
#define GPIO_CFG_XPIN_13	(GPIO_CFG_DIR_13 |			\
							 GPIO_CFG_PULL_UP_EN_13 |	\
							 GPIO_CFG_SLEW_RATE_EN_13 |	\
							 GPIO_CFG_DRV_STR_13)
#endif
#ifdef ENABLE_GPIO_XPIN_14
#define GPIO_CFG_XPIN_14	(GPIO_CFG_DIR_14 |			\
							 GPIO_CFG_PULL_UP_EN_14 |	\
							 GPIO_CFG_SLEW_RATE_EN_14 |	\
							 GPIO_CFG_DRV_STR_14)
#endif
#ifdef ENABLE_GPIO_XPIN_15
#define GPIO_CFG_XPIN_15	(GPIO_CFG_DIR_15 |			\
							 GPIO_CFG_PULL_UP_EN_15 |	\
							 GPIO_CFG_SLEW_RATE_EN_15 |	\
							 GPIO_CFG_DRV_STR_15)
#endif
#ifdef ENABLE_GPIO_XPIN_16
#define GPIO_CFG_XPIN_16	(GPIO_CFG_DIR_16 |			\
							 GPIO_CFG_PULL_UP_EN_16 |	\
							 GPIO_CFG_SLEW_RATE_EN_16 |	\
							 GPIO_CFG_DRV_STR_16)
#endif
#ifdef ENABLE_GPIO_XPIN_17
#define GPIO_CFG_XPIN_17	(GPIO_CFG_DIR_17 |			\
							 GPIO_CFG_PULL_UP_EN_17 |	\
							 GPIO_CFG_SLEW_RATE_EN_17 |	\
							 GPIO_CFG_DRV_STR_17)
#endif
#ifdef ENABLE_GPIO_XPIN_18
#define GPIO_CFG_XPIN_18	(GPIO_CFG_DIR_18 |			\
							 GPIO_CFG_PULL_UP_EN_18 |	\
							 GPIO_CFG_SLEW_RATE_EN_18 |	\
							 GPIO_CFG_DRV_STR_18)
#endif
#ifdef ENABLE_GPIO_XPIN_19
#define GPIO_CFG_XPIN_19	(GPIO_CFG_DIR_19 |			\
							 GPIO_CFG_PULL_UP_EN_19 |	\
							 GPIO_CFG_SLEW_RATE_EN_19 |	\
							 GPIO_CFG_DRV_STR_19)
#endif
#ifdef ENABLE_GPIO_XPIN_20
#define GPIO_CFG_XPIN_20	(GPIO_CFG_DIR_20 |			\
							 GPIO_CFG_PULL_UP_EN_20 |	\
							 GPIO_CFG_SLEW_RATE_EN_20 |	\
							 GPIO_CFG_DRV_STR_20)
#endif
#ifdef ENABLE_GPIO_XPIN_21
#define GPIO_CFG_XPIN_21	(GPIO_CFG_DIR_21 |			\
							 GPIO_CFG_PULL_UP_EN_21 |	\
							 GPIO_CFG_SLEW_RATE_EN_21 |	\
							 GPIO_CFG_DRV_STR_21)
#endif
#ifdef ENABLE_GPIO_XPIN_24
#define GPIO_CFG_XPIN_24	(GPIO_CFG_DIR_24 |			\
							 GPIO_CFG_PULL_UP_EN_24 |	\
							 GPIO_CFG_SLEW_RATE_EN_24 |	\
							 GPIO_CFG_DRV_STR_24)
#endif
#ifdef ENABLE_GPIO_XPIN_25
#define GPIO_CFG_XPIN_25	(GPIO_CFG_DIR_25 |			\
							 GPIO_CFG_PULL_UP_EN_25 |	\
							 GPIO_CFG_SLEW_RATE_EN_25 |	\
							 GPIO_CFG_DRV_STR_25)
#endif
#ifdef ENABLE_GPIO_XPIN_26
#define GPIO_CFG_XPIN_26	(GPIO_CFG_DIR_26 |			\
							 GPIO_CFG_PULL_UP_EN_26 |	\
							 GPIO_CFG_SLEW_RATE_EN_26 |	\
							 GPIO_CFG_DRV_STR_26)
#endif
#ifdef ENABLE_GPIO_XPIN_28
#define GPIO_CFG_XPIN_28	(GPIO_CFG_DIR_28 |			\
							 GPIO_CFG_PULL_UP_EN_28 |	\
							 GPIO_CFG_SLEW_RATE_EN_28 |	\
							 GPIO_CFG_DRV_STR_28)
#endif
#ifdef ENABLE_GPIO_XPIN_29
#define GPIO_CFG_XPIN_29	(GPIO_CFG_DIR_29 |			\
							 GPIO_CFG_PULL_UP_EN_29 |	\
							 GPIO_CFG_SLEW_RATE_EN_29 |	\
							 GPIO_CFG_DRV_STR_29)
#endif
#ifdef ENABLE_GPIO_XPIN_30
#define GPIO_CFG_XPIN_30	(GPIO_CFG_DIR_30 |			\
							 GPIO_CFG_PULL_UP_EN_30 |	\
							 GPIO_CFG_SLEW_RATE_EN_30 |	\
							 GPIO_CFG_DRV_STR_30)
#endif
#ifdef ENABLE_GPIO_XPIN_31
#define GPIO_CFG_XPIN_31	(GPIO_CFG_DIR_31 |			\
							 GPIO_CFG_PULL_UP_EN_31 |	\
							 GPIO_CFG_SLEW_RATE_EN_31 |	\
							 GPIO_CFG_DRV_STR_31)
#endif
#ifdef ENABLE_GPIO_XPIN_32
#define GPIO_CFG_XPIN_32	(GPIO_CFG_DIR_32 |			\
							 GPIO_CFG_PULL_UP_EN_32 |	\
							 GPIO_CFG_SLEW_RATE_EN_32 |	\
							 GPIO_CFG_DRV_STR_32)
#endif
#ifdef ENABLE_GPIO_XPIN_33
#define GPIO_CFG_XPIN_33	(GPIO_CFG_DIR_33 |			\
							 GPIO_CFG_PULL_UP_EN_33 |	\
							 GPIO_CFG_SLEW_RATE_EN_33 |	\
							 GPIO_CFG_DRV_STR_33)
#endif

#if defined(CONFIG_XBEE_THT) && defined(GPIO_CFG_DIR_5)
#if	(GPIO_CFG_DIR_5 == GPIO_CFG_OUTPUT)
#error "Pin 5 (Reset) is only available as input"
#endif /*(GPIO_CFG_DIR_5 == GPIO_CFG_OUTPUT) */
#endif /* defined(CONFIG_XBEE_THT) && defined(GPIO_CFG_DIR_5) */

#if defined(CONFIG_XBEE_SMT) && defined(GPIO_CFG_DIR_6)
#if	(GPIO_CFG_DIR_6 == GPIO_CFG_OUTPUT)
#error "Pin 6 (Reset) is only available as input"
#endif /*(GPIO_CFG_DIR_5 == GPIO_CFG_OUTPUT) */
#endif /* defined(CONFIG_XBEE_SMT) && defined(GPIO_CFG_DIR_6) */

#if defined(CONFIG_XBEE_THT) && defined(GPIO_CFG_DIR_8)
#if	(GPIO_CFG_DIR_8 == GPIO_CFG_INPUT)
#error "Pin 8 (BKGD) is only available as output"
#endif /*(GPIO_CFG_DIR_5 == GPIO_CFG_OUTPUT) */
#endif /* defined(CONFIG_XBEE_THT) && defined(GPIO_CFG_DIR_5) */

#if defined(CONFIG_XBEE_SMT) && defined(GPIO_CFG_DIR_9)
#if	(GPIO_CFG_DIR_9 == GPIO_CFG_INPUT)
#error "Pin 9 (BKGD) is only available as output"
#endif /*(GPIO_CFG_DIR_5 == GPIO_CFG_OUTPUT) */
#endif /* defined(CONFIG_XBEE_SMT) && defined(GPIO_CFG_DIR_6) */
/* Ports configuration */
#ifdef ENABLE_PORT_0
#define PORT0_CFG			(PORT0_CFG_DIR | 			\
							 PORT0_CFG_PULL_UP_EN |		\
							 PORT0_CFG_SLEW_RATE_EN |	\
							 PORT0_CFG_DRV_STR)
#endif
#ifdef ENABLE_PORT_1
#define PORT1_CFG			(PORT1_CFG_DIR | 			\
							 PORT1_CFG_PULL_UP_EN |		\
							 PORT1_CFG_SLEW_RATE_EN |	\
							 PORT1_CFG_DRV_STR)
#endif
#ifdef ENABLE_PORT_2
#define PORT2_CFG			(PORT2_CFG_DIR | 			\
							 PORT2_CFG_PULL_UP_EN |		\
							 PORT2_CFG_SLEW_RATE_EN |	\
							 PORT2_CFG_DRV_STR)
#endif
#ifdef ENABLE_PORT_3
#define PORT3_CFG			(PORT3_CFG_DIR | 			\
							 PORT3_CFG_PULL_UP_EN |		\
							 PORT3_CFG_SLEW_RATE_EN |	\
							 PORT3_CFG_DRV_STR)
#endif

#define gpio_toggle(pin)	gpio_set(pin, !gpio_get(pin))
/* Interrupt handler "call-backs" where customers can code their stuff */
extern void gpio_irq_handler_xpin_2(void);
extern void gpio_irq_handler_xpin_3(void);
extern void gpio_irq_handler_xpin_4(void);
extern void gpio_irq_handler_xpin_7(void);
extern void gpio_irq_handler_xpin_8(void);
extern void gpio_irq_handler_xpin_9(void);
extern void gpio_irq_handler_xpin_11(void);
extern void gpio_irq_handler_xpin_10(void);
extern void gpio_irq_handler_xpin_13(void);
extern void gpio_irq_handler_xpin_15(void);
extern void gpio_irq_handler_xpin_16(void);
extern void gpio_irq_handler_xpin_18(void);
extern void gpio_irq_handler_xpin_19(void);
extern void gpio_irq_handler_xpin_20(void);
extern void gpio_irq_handler_xpin_24(void);
extern void gpio_irq_handler_xpin_26(void);
extern void gpio_irq_handler_xpin_28(void);
extern void gpio_irq_handler_xpin_29(void);
extern void gpio_irq_handler_xpin_31(void);
extern void gpio_irq_handler_xpin_32(void);
extern void gpio_irq_handler_xpin_33(void);

/* Function prototypes */
/* GPIO functions */
void gpio_irq_enable(bool_t enable);
int gpio_enable_xpin_irq(xpin_t pin, bool_t enable);
int gpio_config_irq(xpin_t pin, bool_t type, bool_t edge);
void gpio_set(xpin_t pin, bool_t val);
bool_t gpio_get(xpin_t pin);
int gpio_config(xpin_t pin, uint8_t cfg);
void gpio_config_dir(xpin_t pin, uint8_t cfg);

/* Port functions */
void port_set(port_t port, uint8_t val);
int port_bit_set(port_t port, uint8_t bit, bool_t val);
uint8_t port_get(port_t port);
int port_bit_get(port_t port, uint8_t bit);
int port_config(port_t port, uint8_t cfg);

#endif /* __GPIO_H_ */
