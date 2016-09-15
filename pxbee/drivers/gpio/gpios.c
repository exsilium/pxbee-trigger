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
/**	Platform-specific layer provides a consistent GPIO API to upper layers
 *	of the driver.
 *	
 *	@ingroup api_gpios
 *	
 *	@defgroup api_gpios_gpio
 *	
 *	@section  gpio_section Standard GPIO API Overview
 *	
 *	This API contains the functions to configure and control the standard 
 *	GPIOs of the programmable XBee devices.
 *	
 *	- GPIO configuration functions:
 *		- gpio_config()
 *	
 *	- GPIO functions to read/write the standard GPIOs:
 *		- gpio_get()
 *		- gpio_set()
 *	
 *	
 *	@ingroup api_gpios
 *	
 *	@defgroup api_gpios_irq
 *	
 *	@section  irq_section IRQ API Overview
 *	
 *	This API contains the functions to configure and control the IRQs of the 
 *  the programmable XBee \b devices.
 *	
 *	- IRQ configuration functions:
 *		- gpio_config_irq()
 *		- gpio_irq_enable()
 *	
 *	
 *	@ingroup api_gpios
 *	
 *	@defgroup api_gpios_port
 *	
 *	@section  port_section Port API Overview
 *	
 *	This API contains the functions to configure and control the ports of the 
 *  the programmable XBee devices.
 *  The ports are not the actual ports of the hcs08 chip, so they are not 
 *  read and written atomically. They are groups of GPIOs that have a custom 
 *  read and write implementation in code. 
 *  The ports are defined by an array of xpin_t values and they can go from 2 
 *  pins to 8 pins.
 *  The value written and read in a port is always a byte. 
 *	
 *	- Port configuration functions:
 *		- port_config()
 *	
 *	- Port functions to read/write the ports:
 *		- port_set()
 *		- port_get()
 *	
 */
#include <system.h>
#include <errno.h>
#include <types.h>
#include <gpios.h>
#include <hardware.h>
#include <gpio_ports.h>

#ifdef ENABLE_POWER_MANAGEMENT	
extern uint8_t wakeup_irq;
#endif /* ENABLE_POWER_MANAGEMENT */	
/// \cond 
#ifdef ENABLE_BANK1_GPIO_IRQ
uint8_t kbimod1_reg = 0;
uint8_t kbiedg1_reg = 0;
#endif

#ifdef ENABLE_BANK2_GPIO_IRQ
uint8_t kbimod2_reg = 0;
uint8_t kbiedg2_reg = 0;
#endif

#ifdef ENABLE_PORT_0
const xpin_t __port_0[] = PORT0_XPINS;
#endif
#ifdef ENABLE_PORT_1
const xpin_t  __port_1[] = PORT1_XPINS;
#endif
#ifdef ENABLE_PORT_2
const xpin_t  __port_2[] = PORT2_XPINS;
#endif
#ifdef ENABLE_PORT_3
const xpin_t  __port_3[] = PORT3_XPINS;
#endif
/// \endcond 

/* Helper macros */
#define XPIN_IS_OUTPUT(cfg)			((cfg) & GPIO_CFG_OUTPUT)
#define XPIN_HAS_PULLUP(cfg)		((cfg) & GPIO_CFG_PULL_UP_EN)
#define XPIN_HAS_SLEWR_ON(cfg)		((cfg) & GPIO_CFG_SLEW_RATE_EN)
#define XPIN_HAS_DRVSTR_HIGH(cfg)	((cfg) & GPIO_CFG_DRV_STR_HIGH)
#define XPIN_GET_PORTBIT_MASK(pin)	(0x01 << (((pin) >> PORTBIT_SH) & PORTBIT_MSK))
#define XPIN_GET_PORT(pin)			((pin) & (PORT_MSK << PORT_SH))
#define XPIN_IS_IRQABLE(pin)		(((pin) & IRQABLE) != 0)
#define XPIN_IS_GPIOABLE(pin)		(XPIN_GET_PORT(pin) != NOGPIO)

#define gpio_get_offset_dir_port(pin)	(gpio_get_offset_data_port(pin) + 1)
#define gpio_get_offset_sr_port(pin)	(gpio_get_offset_pull_port(pin) + 1)
#define gpio_get_offset_ds_port(pin)	(gpio_get_offset_pull_port(pin) + 2)

static void gpio_get_port_and_bits(port_t port, const xpin_t **pin, uint8_t *bits)
{
	switch (port)  {
#ifdef ENABLE_PORT_0
	case PORT0:	*bits = ARRAY_SIZE(__port_0);
				*pin = __port_0;
				break;
#endif
#ifdef ENABLE_PORT_1
	case PORT1:	*bits = ARRAY_SIZE(__port_1);
				*pin = __port_1;
				break;
#endif
#ifdef ENABLE_PORT_2
	case PORT2:	*bits = ARRAY_SIZE(__port_2);
				*pin = __port_2;
				break;
#endif
#ifdef ENABLE_PORT_3
	case PORT3:	*bits = ARRAY_SIZE(__port_3);
				*pin = __port_3;
				break;
#endif
	default:	*bits = 0;
				*pin = NULL;
				break;
	}
}

/**
 *	@ingroup api_gpios_port
 *	@brief		Writes a \b byte in the specified \b port.
 *	@param[in]	port the port where the byte will be written.
 *	@param[in]	val  the byte to write in the port.
 *	@retval		None
 */
void port_set(port_t port, uint8_t val)
{
	uint8_t i, portbits, mask;
	xpin_t *ppins;

	gpio_get_port_and_bits(port, &ppins, &portbits);

	for (i = 0, mask = 0x01; i < portbits; i++, mask <<= 1)
		gpio_set(ppins[i], val & mask);
}

/**
 *	@ingroup api_gpios_port
 *	@brief		Writes a \b value in the specified \b bit of
 *	            the selected \b port.
 *	@param[in]	port the port where a bit will be written.
 *	@param[in]	bit  the bit of the port that will be written.
 *	@param[in]	val  the value that will be written.
 *	@retval		0		on success
 *  @retval		-EINVAL on error (invalid port bit)
 */
int port_bit_set(port_t port, uint8_t bit, bool_t val)
{
	uint8_t portbits;
	xpin_t *ppins;

	gpio_get_port_and_bits(port, &ppins, &portbits);

	if (bit >=  portbits)
		return -EINVAL;

	gpio_set(ppins[bit], val);

	return 0;
}

/**
 *	@ingroup api_gpios_port
 *	@brief		Reads a byte of data from the specified \b port.
 *	@param[in]	pin  	the port to read the data from.
 *	@retval		uint8_t the byte read from the port.
 */
uint8_t port_get(port_t port)
{
	uint8_t i, portbits, portval = 0;
	xpin_t *ppins;

	gpio_get_port_and_bits(port, &ppins, &portbits);

	for (i = 0; i < portbits; i++)
		portval |= (gpio_get(ppins[i]) << i) ;
	
	return portval;
}

/**
 *	@ingroup api_gpios_port
 *	@brief		Reads the \b value of the specified \b bit of
 *	            the selected \b port.
 *	@param[in]	port the port where a bit will be read.
 *	@param[in]	bit  the bit of the port that will be read.
 *	@retval		int the value read from the port on success
 *	@retval		-EINVAL on error
 */
int port_bit_get(port_t port, uint8_t bit)
{
	uint8_t portbits;
	xpin_t *ppins;

	gpio_get_port_and_bits(port, &ppins, &portbits);

	if (bit >= portbits)
		return -EINVAL;

	return (int)gpio_get(ppins[bit]);
}

/**
 *	@ingroup api_gpios_port
 *	@brief		Initializes and configures the specified \b port with the 
 *				parameters selected in \b cfg param
 *	@param[in]	port	the port that to initialize. A port is defined by an 
 *						array of standard GPIO capable pins.
 *	@param[in]	cfg		a byte containing the configuration masks for the 
 *						standard GPIO pins of the port. See the 
 *						\ref macros_gpio for more information.
 *	@retval 	0		on successfully
 *	@retval		EINVAL	invalid xpin_t parameter (one or more of the pins 
 *						are not standard GPIO capable pins).
 */
int port_config(port_t port, uint8_t cfg)
{
	int ret;
	uint8_t i, portbits;
	xpin_t *ppins;
	
	gpio_get_port_and_bits(port, &ppins, &portbits);

	for (i = 0; i < portbits; i++) {
		ret = gpio_config(ppins[i], cfg);
		if (ret)
			break;
	}
	return ret;
}

static volatile uint8_t *gpio_get_offset_data_port(xpin_t pin)
{
	uint8_t port;
	  
	/* Mask to get port */
	port = XPIN_GET_PORT(pin);   
	if (port == PORT_A) {
		return &PTAD;
	} else if (port == PORT_B) {
		return &PTBD;
	} else if (port == PORT_C) {
		return &PTCD;
	} else if (port == PORT_D) {
		return &PTDD;
	}  else if (port == PORT_E) {
		return &PTED;
	}
	return NULL;
}

static volatile uint8_t *gpio_get_offset_pull_port(xpin_t pin)
{
	uint8_t port;
	  
	/* Mask to get port */
	port = XPIN_GET_PORT(pin);
	if (port == PORT_A) {
		return &PTAPE;
	} else if (port == PORT_B) {
		return &PTBPE;
	} else if (port == PORT_C) {
		return &PTCPE;
	} else if (port == PORT_D) {
		return &PTDPE;
	} else if (port == PORT_E) {
		return &PTEPE;
	}
	return NULL;
}

/**
 *	@ingroup api_gpios_gpio
 *	@brief		Sets the specified pin in high or low level. Notice the XBee 
 *				pin must be configured as output to be able to set it.
 *	@param[in]	pin	the XBee pin to set.
 *	@param[in]	val	1 to set the pin in high level, 0 to set it in low level.
 *	@retval		None
 */
void gpio_set(xpin_t pin, bool_t val) 
{
	uint8_t portbit = XPIN_GET_PORTBIT_MASK(pin);
	volatile uint8_t *port = gpio_get_offset_data_port(pin);
	  
	if(val)
		*port |= portbit;
	else
		*port &= ~portbit;
}

/**	
 * 	@ingroup api_gpios_gpio
 *	@brief		Gets the value of the specified \b pin.
 *	@param[in]	pin		the XBee pin to get the value from.
 *	@retval		bool_t  1 if the pin is in high level, 0 if it is in low level.
 */
bool_t gpio_get(xpin_t pin)
{
	uint8_t portbit = XPIN_GET_PORTBIT_MASK(pin);
	volatile uint8_t *port = gpio_get_offset_data_port(pin);
	
	return (*port & portbit) ? 1 : 0;
}

/**	
 * 	@ingroup api_gpios_gpio
 *	@brief		Configures \b pin as input or output.
 *	@param[in]	pin		the XBee pin to configure.
 *	@param[in]	dir		\b pin data direction, defined macros may be used.
 */
void gpio_config_dir(xpin_t pin, uint8_t dir)
{
	volatile uint8_t *port;
	uint8_t portbit = XPIN_GET_PORTBIT_MASK(pin);

	/* Here we want to be fast, so we dont check if 
	 * parameter is a valid GPIO. The caller should 
	 * take care of that.
	 */
/*	port = gpio_get_offset_dir_port(pin); */
	
	port = &PTADD + ((pin & (PORT_MSK << PORT_SH)) >> (PORT_SH - 1));
	
	if(dir)
		*port |= portbit;
	else
		*port &= ~portbit;
}

/**	
 *  @ingroup api_gpios_gpio
 *	@brief		Configures the selected \b pin as a standard GPIO.
 *	@param[in]	pin		the XBee pin to configure.
 *	@param[in]  cfg		a byte containing the configuration masks for the 
 *						GPIO. See the \ref macros_gpio for more information.
 *	@retval 	0		on success
 *	@retval 	EINVAL	invalid xpin_t parameter (not standard GPIO capable 
 *						pin).
 */
int gpio_config(xpin_t pin, uint8_t cfg)
{
	volatile uint8_t *port;
	uint8_t portbit = XPIN_GET_PORTBIT_MASK(pin);
   
	if (!XPIN_IS_GPIOABLE(pin))
		return -EINVAL;

	/* Configure pin direction */
	port = gpio_get_offset_dir_port(pin);
	if(XPIN_IS_OUTPUT(cfg))
		*port |= portbit;
	else
		*port &= ~portbit;
  
	/* Configure pin pull-up */
	port = (uint8_t *)gpio_get_offset_pull_port(pin);
	if (XPIN_HAS_PULLUP(cfg))
		*port |= portbit;
	else
		*port &= ~portbit;
  
	/* Configure pin slew rate */
	port = (uint8_t *)gpio_get_offset_sr_port(pin);
 	if (XPIN_HAS_SLEWR_ON(cfg))
		*port |= portbit;
	else
		*port &= ~portbit;
 
	/* Configure pin drive strength */
	port = (uint8_t *)gpio_get_offset_ds_port(pin);
	if (XPIN_HAS_DRVSTR_HIGH(cfg))
		*port |= portbit;
	else
		*port &= ~portbit;
	
	return 0;
}

#if defined(ENABLE_BANK1_GPIO_IRQ) || defined(ENABLE_BANK2_GPIO_IRQ)

/**	
 *  @ingroup api_gpios_irq
 *	@brief		Enables or disables all the IRQs. 
 *	@param[in]	enable	1 to enable the IRQs, 0 to disable them.
 *	@retval	 	None
 */
void gpio_irq_enable(bool_t enable)
{
	/* Enable/Disable gpio interrupts per bank enabled */
#ifdef ENABLE_BANK1_GPIO_IRQ
	KBI1SC_KBIE = enable;
#endif
#ifdef ENABLE_BANK2_GPIO_IRQ
	KBI2SC_KBIE = enable;
#endif
}

static int _gpio_config_irq(xpin_t pin, bool_t enable, bool_t config, 
							bool_t type, bool_t edge)
{
	volatile uint8_t *port;
	uint8_t portbit = XPIN_GET_PORTBIT_MASK(pin);
		
	if (!XPIN_IS_GPIOABLE(pin))
		return -EINVAL;

	/* Configure pin direction to input */
	port = gpio_get_offset_dir_port(pin);
	*port &= ~portbit;

	/* Disable FSL pin pull; radio pin pull will be used instead when possible */
	port = (uint8_t *)gpio_get_offset_pull_port(pin);
	*port &= ~portbit;
				
	switch(pin) {
#ifdef ENABLE_BANK1_GPIO_IRQ
#ifdef KBI1PE_KBIPE5_XPIN
	case KBI1PE_KBIPE5_XPIN:
		if (config) {
			if (type == GPIO_CFG_EDGE_IRQ)
				/* See NOTE 1 */
				KBI1ES_KBEDG5 = gpio_get(KBI1PE_KBIPE5_XPIN) == edge ? 
																!edge : edge;
			else
				KBI1ES_KBEDG5 = edge;
			kbimod1_reg = (kbimod1_reg & ~(1 << 5)) | (type << 5);
			kbiedg1_reg = (kbiedg1_reg & ~(1 << 5)) | (edge << 5);
		}
		KBI1PE_KBIPE5 = enable;
		break;
#endif
#ifdef KBI1PE_KBIPE4_XPIN
	case KBI1PE_KBIPE4_XPIN:
		if (config) {
			if (type == GPIO_CFG_EDGE_IRQ)
				/* See NOTE 1 */
				KBI1ES_KBEDG4 = gpio_get(KBI1PE_KBIPE4_XPIN) == edge ?
																!edge : edge;
			else
				KBI1ES_KBEDG4 = edge;
			kbimod1_reg = (kbimod1_reg & ~(1 << 4)) | (type << 4);
			kbiedg1_reg = (kbiedg1_reg & ~(1 << 4)) | (edge << 4);
		}
		KBI1PE_KBIPE4 = enable;
		break;
#endif
#ifdef KBI1PE_KBIPE2_XPIN
	case KBI1PE_KBIPE2_XPIN:
		if (config) {
			if (type == GPIO_CFG_EDGE_IRQ)
				/* See NOTE 1 */
				KBI1ES_KBEDG2 = gpio_get(KBI1PE_KBIPE2_XPIN) == edge ?
																!edge : edge;
			else
				KBI1ES_KBEDG2 = edge;
			kbimod1_reg = (kbimod1_reg & ~(1 << 2)) | (type << 2);
			kbiedg1_reg = (kbiedg1_reg & ~(1 << 2)) | (edge << 2);
		}
		KBI1PE_KBIPE2 = enable;
		break;
#endif
#ifdef KBI1PE_KBIPE7_XPIN
	case KBI1PE_KBIPE7_XPIN:
		if (config) {
			if (type == GPIO_CFG_EDGE_IRQ)
				/* See NOTE 1 */
				KBI1ES_KBEDG7 = gpio_get(KBI1PE_KBIPE7_XPIN) == edge ?
																!edge : edge;
			else
				KBI1ES_KBEDG7 = edge;
			kbimod1_reg = (kbimod1_reg & ~(1 << 7)) | (type << 7);
			kbiedg1_reg = (kbiedg1_reg & ~(1 << 7)) | (edge << 7);
		}
		KBI1PE_KBIPE7 = enable;
		break;
#endif
#ifdef KBI1PE_KBIPE1_XPIN
	case KBI1PE_KBIPE1_XPIN:
		if (config) {
			if (type == GPIO_CFG_EDGE_IRQ)
				/* See NOTE 1 */
				KBI1ES_KBEDG1 = gpio_get(KBI1PE_KBIPE1_XPIN) == edge ?
																!edge : edge;
			else
				KBI1ES_KBEDG1 = edge;
			kbimod1_reg = (kbimod1_reg & ~(1 << 1)) | (type << 1);
			kbiedg1_reg = (kbiedg1_reg & ~(1 << 1)) | (edge << 1);
		}
		KBI1PE_KBIPE1 = enable;
		break;
#endif
#ifdef KBI1PE_KBIPE6_XPIN
	case KBI1PE_KBIPE6_XPIN:
		if (config) {
			if (type == GPIO_CFG_EDGE_IRQ)
				/* See NOTE 1 */
				KBI1ES_KBEDG6 = gpio_get(KBI1PE_KBIPE6_XPIN) == edge ?
																!edge : edge;
			else
				KBI1ES_KBEDG6 = edge;
			kbimod1_reg = (kbimod1_reg & ~(1 << 6)) | (type << 6);
			kbiedg1_reg = (kbiedg1_reg & ~(1 << 6)) | (edge << 6);
		}
		KBI1PE_KBIPE6 = enable;
		break;
#endif
#ifdef KBI1PE_KBIPE3_XPIN
	case KBI1PE_KBIPE3_XPIN:
		if (config) {
			if (type == GPIO_CFG_EDGE_IRQ)
				/* See NOTE 1 */
				KBI1ES_KBEDG3 = gpio_get(KBI1PE_KBIPE3_XPIN) == edge ?
																!edge : edge;
			else
				KBI1ES_KBEDG3 = edge;
			kbimod1_reg = (kbimod1_reg & ~(1 << 3)) | (type << 3);
			kbiedg1_reg = (kbiedg1_reg & ~(1 << 3)) | (edge << 3);
		}
		KBI1PE_KBIPE3 = enable;
		break;
#endif
#ifdef KBI1PE_KBIPE0_XPIN
	case KBI1PE_KBIPE0_XPIN:
		if (config) {
			if (type == GPIO_CFG_EDGE_IRQ)
				/* See NOTE 1 */
				KBI1ES_KBEDG0 = gpio_get(KBI1PE_KBIPE0_XPIN) == edge ?
																!edge : edge;
			else
				KBI1ES_KBEDG0 = edge;
			kbimod1_reg = (kbimod1_reg & ~(1 << 0)) | (type << 0);
			kbiedg1_reg = (kbiedg1_reg & ~(1 << 0)) | (edge << 0);
		}
		KBI1PE_KBIPE0 = enable;
		break;
#endif
#endif /* ENABLE_BANK1_GPIO_IRQ */
#ifdef ENABLE_BANK2_GPIO_IRQ
#ifdef KBI2PE_KBIPE5_XPIN
	case KBI2PE_KBIPE5_XPIN:
		if (config) {
			if (type == GPIO_CFG_EDGE_IRQ)
				/* See NOTE 1 */
				KBI2ES_KBEDG5 = gpio_get(KBI2PE_KBIPE5_XPIN) == edge ?
																!edge : edge;
			else
				KBI2ES_KBEDG5 = edge;
			kbimod2_reg = (kbimod2_reg & ~(1 << 5)) | (type << 5);
			kbiedg2_reg = (kbiedg2_reg & ~(1 << 5)) | (edge << 5);
		}
		KBI2PE_KBIPE5 = enable;
		break;
#endif
#ifdef KBI2PE_KBIPE4_XPIN
	case KBI2PE_KBIPE4_XPIN:
		if (config) {
			if (type == GPIO_CFG_EDGE_IRQ)
				/* See NOTE 1 */
				KBI2ES_KBEDG4 = gpio_get(KBI2PE_KBIPE4_XPIN) == edge ?
																!edge : edge;
			else
				KBI2ES_KBEDG4 = edge;
			kbimod2_reg = (kbimod2_reg & ~(1 << 4)) | (type << 4);
			kbiedg2_reg = (kbiedg2_reg & ~(1 << 4)) | (edge << 4);
		}
		KBI2PE_KBIPE4 = enable;
		break;
#endif
#ifdef KBI2PE_KBIPE7_XPIN
	case KBI2PE_KBIPE7_XPIN:
		if (config) {
			if (type == GPIO_CFG_EDGE_IRQ)
				/* See NOTE 1 */
				KBI2ES_KBEDG7 = gpio_get(KBI2PE_KBIPE7_XPIN) == edge ?
																!edge : edge;
			else
				KBI2ES_KBEDG7 = edge;
			kbimod2_reg = (kbimod2_reg & ~(1 << 7)) | (type << 7);
			kbiedg2_reg = (kbiedg2_reg & ~(1 << 7)) | (edge << 7);
		}
		KBI2PE_KBIPE7 = enable;
		break;
#endif
#endif /* ENABLE_BANK2_GPIO_IRQ */
	default:		return -EINVAL;
	}

	return 0;
	/* NOTE 1: If current level is active, configure the opposite to avoid
	 * detecting a false edge, see how the edge detection algorithm work in
	 * gpio_isr() function (NOTE 2). */
}

/**	
 *  @ingroup api_gpios_irq
 *	@brief		Configures the specified XBee pin as IRQ.
 *	@param[in]	enable  1 to enable the IRQ, 0 to disable it.
 *	@param[in]	type	the detection mode of the IRQ. 0 to detect the 
 *						interruption with level, 1 to detect it with edge.
 *						See \ref macros_irq for more information.
 *	@param[in]	edge	0 to detect the interruption with a high level or 
 *						a rise edge. 1 to detect it with a low level or a 
 *						fall edge. See \ref macros_irq for more information.
 *	@retval		EINVAL	invalid xpin_t parameter (not IRQ capable pin).
 *	@retval		0		on success.
 */
int gpio_config_irq(xpin_t pin, bool_t type, bool_t edge)
{
	return _gpio_config_irq(pin, 1, 1, type, edge);
}

/**	
 *  @ingroup api_gpios_irq
 *	@brief		Enables or disables a specific IRQ.
 *	@param[in]	pin		the XBee pin containing the IRQ that will be enabled 
 *						or disabled.
 *	@param[in]	enable  0 to disable the IRQ, 1 to enable it.
  *	@retval		EINVAL	invalid xpin_t parameter (not IRQ capable pin).
 *	@retval		0		on success.
 */
int gpio_enable_xpin_irq(xpin_t pin, bool_t enable)
{
	return _gpio_config_irq(pin, enable, 0, 0, 0);
}


#if 0
/* Just for doxygen get the API documentation */
/**
 *	@ingroup api_gpios_gpio
 *	@brief		Inverts the value of a pin.
 *	@param[in]	pin	the XBee pin to toggle.
 *	@retval		None
 */
void gpio_toggle(xpin_t pin)
{}
#endif
/*
 * NOTE 2: All the IRQs are configured as "level" interrupts, the edge detection
 * is emulated by configuring the IRQ as level in the edge's active slope (i.e.:
 * for a rising edge, the IRQ is configured as high-level).
 * Then, every time the ISR detects the pin IRQ is asserted, it toggles the
 * active level, so the first time the level is detected (active slope) it calls
 * the user-function, and next time this ISR will be called because the opposite
 * level is detected (remember it was toggled the first time). So, it becomes 
 * toggled again but the user-function is not called and the IRQ mechanism is 
 * left armed for next active slope. 
 */
#pragma TRAP_PROC
void gpio_isr(void)
{
	uint8_t irqcandidate;
#ifdef ENABLE_BANK1_GPIO_IRQ	
	uint8_t kbi1_val;
#endif	
#ifdef ENABLE_BANK2_GPIO_IRQ	
	uint8_t kbi2_val;
#endif

	gpio_irq_enable(0);
#ifdef ENABLE_BANK1_GPIO_IRQ
	if (KBI1SC_KBF) {
		/* Interrupt in bank1 */
		kbi1_val = (PTBD << 4) | (PTAD & 0x0f);
		irqcandidate = ~(kbi1_val ^ KBI1ES);
		
#ifdef KBI1PE_KBIPE0_XPIN
		if (irqcandidate & 0x01) {
			if (kbimod1_reg & 0x01) {
				KBI1ES_KBEDG0 = !KBI1ES_KBEDG0;
				if (~(kbi1_val ^ kbiedg1_reg) & 0x01)
					/* Edge irq on active slope */
					gpio_irq_handler_KBI1PE_KBIPE0_XPIN();
			} else {
				gpio_irq_handler_KBI1PE_KBIPE0_XPIN();		/* Level irq */
			}
		}
#endif

#ifdef KBI1PE_KBIPE1_XPIN
		if (irqcandidate & 0x02) {
			if (kbimod1_reg & 0x02) {
				KBI1ES_KBEDG1 = !KBI1ES_KBEDG1;
				if (~(kbi1_val ^ kbiedg1_reg) & 0x02)
					/* Edge irq on active slope */
					gpio_irq_handler_KBI1PE_KBIPE1_XPIN();
			} else {
				gpio_irq_handler_KBI1PE_KBIPE1_XPIN();		/* Level irq */
			}
		}
#endif

#ifdef KBI1PE_KBIPE2_XPIN
		if (irqcandidate & 0x04) {
			if (kbimod1_reg & 0x04) {
				KBI1ES_KBEDG2 = !KBI1ES_KBEDG2;
				if (~(kbi1_val ^ kbiedg1_reg) & 0x04)
					/* Edge irq on active slope */
					gpio_irq_handler_KBI1PE_KBIPE2_XPIN();
			} else {
				gpio_irq_handler_KBI1PE_KBIPE2_XPIN();		/* Level irq */
			}
		}
#endif		
		
#ifdef KBI1PE_KBIPE3_XPIN
		if (irqcandidate & 0x08) {
			if (kbimod1_reg & 0x08) {
				KBI1ES_KBEDG3 = !KBI1ES_KBEDG3;
				if (~(kbi1_val ^ kbiedg1_reg) & 0x08)
					/* Edge irq on active slope */
					gpio_irq_handler_KBI1PE_KBIPE3_XPIN();
			} else {
				gpio_irq_handler_KBI1PE_KBIPE3_XPIN();		/* Level irq */
			}
		}
#endif

#ifdef KBI1PE_KBIPE4_XPIN
		if (irqcandidate & 0x10) {
			if (kbimod1_reg & 0x10) {
				KBI1ES_KBEDG4 = !KBI1ES_KBEDG4;
				if (~(kbi1_val ^ kbiedg1_reg) & 0x10)
					/* Edge irq on active slope */
					gpio_irq_handler_KBI1PE_KBIPE4_XPIN();
			} else {
				gpio_irq_handler_KBI1PE_KBIPE4_XPIN();		/* Level irq */
			}
		}
#endif

#ifdef KBI1PE_KBIPE5_XPIN
		if (irqcandidate & 0x20) {
			if (kbimod1_reg & 0x20) {
				KBI1ES_KBEDG5 = !KBI1ES_KBEDG5;
				if (~(kbi1_val ^ kbiedg1_reg) & 0x20)
					/* Edge irq on active slope */
					gpio_irq_handler_KBI1PE_KBIPE5_XPIN();
			} else {
				gpio_irq_handler_KBI1PE_KBIPE5_XPIN();		/* Level irq */
			}
		}
#endif	

#ifdef KBI1PE_KBIPE6_XPIN
		if (irqcandidate & 0x40) {
			if (kbimod1_reg & 0x40) {
				KBI1ES_KBEDG6 = !KBI1ES_KBEDG6;
				if (~(kbi1_val ^ kbiedg1_reg) & 0x40)
					/* Edge irq on active slope */
					gpio_irq_handler_KBI1PE_KBIPE6_XPIN();
			} else {
				gpio_irq_handler_KBI1PE_KBIPE6_XPIN();		/* Level irq */
			}
		}
#endif
		
#ifdef KBI1PE_KBIPE7_XPIN
		if (irqcandidate & 0x80) {
			if (kbimod1_reg & 0x80) {
				KBI1ES_KBEDG7 = !KBI1ES_KBEDG7;
				if (~(kbi1_val ^ kbiedg1_reg) & 0x80)
					/* Edge irq on active slope */
					gpio_irq_handler_KBI1PE_KBIPE7_XPIN();
			} else {
				gpio_irq_handler_KBI1PE_KBIPE7_XPIN();		/* Level irq */
			}
		}
#endif
		
		KBI1SC_KBACK = 1;	/* Ack */
	}		
#endif /* ENABLE_BANK1_GPIO_IRQ */
#ifdef ENABLE_BANK2_GPIO_IRQ	
	if (KBI2SC_KBF) {
		kbi2_val = PTDD;
		irqcandidate = ~(kbi2_val ^ KBI2ES);
		
#ifdef KBI2PE_KBIPE4_XPIN
		if (irqcandidate & 0x10) {
			if (kbimod2_reg & 0x10) {
				KBI2ES_KBEDG4 = !KBI2ES_KBEDG4;
				if (~(kbi2_val ^ kbiedg2_reg) & 0x10)
					/* Edge irq on active slope */
					gpio_irq_handler_KBI2PE_KBIPE4_XPIN();
			} else {
				gpio_irq_handler_KBI2PE_KBIPE4_XPIN();		/* Level irq */
			}
		}
#endif	
		
#ifdef KBI2PE_KBIPE5_XPIN
		if (irqcandidate & 0x20) {
			if (kbimod2_reg & 0x20) {
				KBI2ES_KBEDG5 = !KBI2ES_KBEDG5;
				if (~(kbi2_val ^ kbiedg2_reg) & 0x20)
					/* Edge irq on active slope */
					gpio_irq_handler_KBI2PE_KBIPE5_XPIN();
			} else {
				gpio_irq_handler_KBI2PE_KBIPE5_XPIN();		/* Level irq */
			}
		}
#endif			
	
#ifdef KBI2PE_KBIPE7_XPIN
		if (irqcandidate & 0x80) {
			if (kbimod2_reg & 0x80) {
				KBI2ES_KBEDG7 = !KBI2ES_KBEDG7;
				if (~(kbi2_val ^ kbiedg2_reg) & 0x80)
					/* Edge irq on active slope */
					gpio_irq_handler_KBI2PE_KBIPE7_XPIN();
			} else {
				gpio_irq_handler_KBI2PE_KBIPE7_XPIN();		/* Level irq */
			}
		}
#endif	
		KBI2SC_KBACK = 1;	/* Ack */
	}
#endif /* ENABLE_BANK2_GPIO_IRQ */
	gpio_irq_enable(1);
}
#else
void gpio_isr(void) {}
#endif /* defined(ENABLE_BANK1_GPIO_IRQ) || defined(ENABLE_BANK2_GPIO_IRQ) */
