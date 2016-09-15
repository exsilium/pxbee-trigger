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

#include <system.h>

#include <gpios.h>
#include <radio_gpios.h>
#include <uart.h>
#include <spi.h>
#include <i2c.h>
#include <adc.h>
#include <rtc.h>
#include <veeprom.h>
#include <flash.h>
#include <string.h>

#include <xbee/device.h>
#include <xbee/atcmd.h>		/* for XBEE_FRAME_HANDLE_LOCAL_AT */
#include <xbee/device.h>	/* for XBEE_FRAME_HANDLE_TX_STATUS */
#include <xbee/wpan.h>		/* for XBEE_FRAME_HANDLE_RX_EXPLICIT */

xbee_dev_t xdev;
#define RADIO_RATE_IDX 	1	/* Selects rates[1] = 115200 as radio rate*/
const uint32_t rates[] = {9600, 115200, 57600, 38400, 19200, 4800, 2400, 1200};
const uint8_t modem_status_resp[] = {0x7e, 0x00, 0x02, 0x8a, 0x00, 0x75};
const uint8_t ATAC_cmd[] = {0x7e, 0x00, 0x04, 0x08, 0x0f, 0x41, 0x43, 0x64};
const uint8_t ATBD7_cmd[] = {0x7e, 0x00, 0x05, 0x08, 0x0f, 0x42, 0x44, 0x07, 0x5b};
const uint8_t ATBD7_resp[] = {0x7e, 0x00, 0x05, 0x88, 0x0f, 0x42, 0x44, 0x00, 0xe2};
const uint8_t ATWR_cmd[] = {0x7e, 0x00, 0x04, 0x08, 0x0f, 0x57, 0x52, 0x3f};

const uint8_t ATBPD_cmd[] = {0x7e, 0x00, 0x04, 0x09, 0x01, 0x50, 0x44, 0x61};
const uint8_t ATBPR_cmd[] = {0x7e, 0x00, 0x04, 0x09, 0x01, 0x50, 0x52, 0x53};
/* 	S2B:     PR = 16bit	PD = don't exist
	S2C:     PR = 16bit	PD = 16bits
	S8:      PR = 32bit	PD = 32bits
	S3B:     PR = 16bit	PD = 16bits (not documented)
	S2CTH:   PR = 16bit	PD = 16bits
 */
#ifndef CONFIG_XBEE_S8		
const uint8_t ATBPD_resp_fix[] = {0x7e, 0x00, 0x07, 0x88, 0x01, 0x50, 0x44, 0x00};
const uint8_t ATBPR_resp_fix[] = {0x7e, 0x00, 0x07, 0x88, 0x01, 0x50, 0x52, 0x00};
#else
const uint8_t ATBPD_resp_fix[] = {0x7e, 0x00, 0x09, 0x88, 0x01, 0x50, 0x44, 0x00};
const uint8_t ATBPR_resp_fix[] = {0x7e, 0x00, 0x09, 0x88, 0x01, 0x50, 0x52, 0x00};
#endif

const uint8_t MS_resp[] = {0x7e, 0x00, 0x02, 0x8a, 0x00, 0x75};
/* const uint8_t ATAC_resp[] = {0x7e, 0x00, 0x05, 0x88, 0x0f, 0x41, 0x43, 0x00, 0xe4}; */

#ifndef CONFIG_XBEE_S8	/* S8 has 32-bit registers */
void radio_gpio_init(uint16_t *pull_direction, uint16_t *pullup_resistor)
#else
void radio_gpio_init(uint32_t *pull_direction, uint32_t *pullup_resistor)
#endif
{
/* Following section configure as mode1 = "peripheral control" those XPINs that
 * are using radio functionality 
 */ 
#ifdef ENABLE_ASSOCIATION_LED
	(void)xbee_cmd_simple(&xdev, "D5", 1);
#endif
#ifdef ENABLE_COMMISSIONING
	(void)xbee_cmd_simple(&xdev, "D0", 1);
#endif
	
#ifndef CONFIG_XBEE_S2B
	/* These commands are not supported on S2B Modules */
#ifdef ENABLE_SLEEP_RQ
	(void)xbee_cmd_simple(&xdev, "D8", 1);
#endif
#ifdef ENABLE_ON_SLEEP
	(void)xbee_cmd_simple(&xdev, "D9", 1);
	/* Set ON_SLEEP as irq input to allow waking up through this pin */
/*	(void)gpio_config_irq(ON_SLEEP_XPIN, GPIO_CFG_EDGE_IRQ, GPIO_IRQ_EDGE_RISE); */
#endif
#endif /* ! defined CONFIG_XBEE_S2B */
#ifdef ENABLE_RSSI_PWM
	(void)xbee_cmd_simple(&xdev, "P0", 1);
#endif
 
/* Following section configure radio pins as mode0 = "disabled" for those XPINs 
 * that are using cpu functionality. 
 * An exception are XPINS configured as irq gpios in this case radio pins are 
 * configured as digital input to make use of the radio pulls when possible. 
 */
#ifdef CONFIG_XBEE_THT
	
/* XPIN_1: Vcc */
/* XPIN_2: Not shared */
#if defined(ENABLE_GPIO_IRQ_XPIN_2)
#if (GPIO_IRQ_CFG_PULL_2 == GPIO_IRQ_CFG_PULL_HIGH) 
#warning "Pull-up for IRQ GPIO on XPIN 2 not available. Change to none and use"
		 "external pull."
#endif
#endif
/* XPIN_3: Not shared */
#if defined(ENABLE_GPIO_IRQ_XPIN_3)
#if (GPIO_IRQ_CFG_PULL_3 == GPIO_IRQ_CFG_PULL_HIGH) 
#warning "Pull-up for IRQ GPIO on XPIN 3 not available. Change to none and use"
		 "external pull."
#endif
#endif
/* XPIN_4: */
#ifdef XPIN_4_USED
	*pullup_resistor &= ~shift_xpin_4;
	(void)xbee_cmd_simple(&xdev, "P2", 0);		/* Disable PWM2/DIO12 */
#endif
/* XPIN_5: Not shared */
/* XPIN_6: */
#ifdef XPIN_6_USED
#ifndef ENABLE_RSSI_PWM
	*pullup_resistor &= ~shift_xpin_6;
	(void)xbee_cmd_simple(&xdev, "P0", 0);		/* Disable PWM0/RSSIM/DIO10 */
#endif
#endif
/* XPIN_7: */
#ifdef XPIN_7_USED
#if defined(ENABLE_GPIO_IRQ_XPIN_7)
	(void)xbee_cmd_simple(&xdev, "P1", 3);		/* PWM1/DIO11 = Digital input */	
#else
	/* S2B/S2C don't really remove pulls when in mode 0 so disable pulls here */
	*pullup_resistor &= ~shift_xpin_7;
	(void)xbee_cmd_simple(&xdev, "P1", 0);		/* Disable PWM1/DIO11 */
#endif
#endif
/* XPIN_8: Not shared */
/* XPIN_9: */
#ifdef XPIN_9_USED
#if defined(ENABLE_GPIO_IRQ_XPIN_9)
#if defined (CONFIG_XBEE_S2B)
	/* Command not implemented according to datasheet */
	/* SLEEP_RQ#/DIO8 = Digital input */
	/*(void)xbee_cmd_simple(&xdev, "D8", 3); */
#elif defined (CONFIG_XBEE_S3B) || defined (CONFIG_XBEE_S2CTH)
	(void)xbee_cmd_simple(&xdev, "D8", 3);		/* SLEEP_RQ#/DIO8 = Digital input */	
#endif
#else
#ifndef ENABLE_SLEEP_RQ
	/* S2B/S2C don't really remove pulls when in mode 0 so disable pulls here */
	*pullup_resistor &= ~shift_xpin_9;
#if defined (CONFIG_XBEE_S2B)
	/* Command not implemented according to datasheet */
	/* Disable SLEEP_RQ#/DIO8 */
	/* (void)xbee_cmd_simple(&xdev, "D8", 0); */
#elif defined (CONFIG_XBEE_S3B) || defined (CONFIG_XBEE_S2CTH)
	(void)xbee_cmd_simple(&xdev, "D8", 0);		/* Disable SLEEP_RQ#/DIO8 */
#endif
#endif
#endif
#endif	
/* XPIN_10: Gnd */
/* XPIN_11: */
#ifdef XPIN_11_USED
#if defined(ENABLE_GPIO_IRQ_XPIN_11)
	(void)xbee_cmd_simple(&xdev, "D4", 3);		/* AD4/DIO4 = Digital input */	
#else
	/* S2B/S2C don't really remove pulls when in mode 0 so disable pulls here */
	*pullup_resistor &= ~shift_xpin_11;
	(void)xbee_cmd_simple(&xdev, "D4", 0);		/* Disable AD4/DIO4 */
#endif
#endif
/* XPIN_12: Not shared */
/* XPIN_13: */
#ifdef XPIN_13_USED
#ifndef ENABLE_ON_SLEEP
#ifdef CONFIG_XBEE_S2B
	/* Command not implemented according to datasheet */
	/* Disable ON_SLEEP#/DIO7 */
	/* (void)xbee_cmd_simple(&xdev, "D9", 0);	*/
#elif defined (CONFIG_XBEE_S3B) || defined (CONFIG_XBEE_S2CTH)
#ifndef ENABLE_GPIO_IRQ_XPIN_13
	/* S2B/S2C don't really remove pulls when in mode 0 so disable pulls here */
	*pullup_resistor &= ~shift_xpin_13;
#endif /* ifndef ENABLE_GPIO_IRQ_XPIN_13 */
	(void)xbee_cmd_simple(&xdev, "D9", 0);		/* Disable ON_SLEEP#/DIO7 */
#endif
#endif /* ENABLE_ON_SLEEP */
#endif /* XPIN_13_USED */
/* XPIN_14: Not shared */
/* XPIN_15: */
#ifdef XPIN_15_USED
#if defined(ENABLE_GPIO_IRQ_XPIN_15)
	(void)xbee_cmd_simple(&xdev, "D5", 3);		/* ASSOC/DIO5 = Digital input */	
#else
	/* S2B/S2C don't really remove pulls when in mode 0 so disable pulls here */
	*pullup_resistor &= ~shift_xpin_15;
#ifndef ENABLE_ASSOCIATION_LED
	(void)xbee_cmd_simple(&xdev, "D5", 0);		/* Disable ASSOC/DIO5 */
#endif
#endif
#endif
/* XPIN_16: Not shared */
#if defined(ENABLE_GPIO_IRQ_XPIN_16)
#if (GPIO_IRQ_CFG_PULL_16 == GPIO_IRQ_CFG_PULL_HIGH) 
#warning "Pull-up for IRQ GPIO on XPIN 16 not available. Change to none and use"
		 "external pull."
#endif
#endif
/* XPIN_17: */
#ifdef XPIN_17_USED
	*pullup_resistor &= ~shift_xpin_17;	
	(void)xbee_cmd_simple(&xdev, "D3", 0);		/* Disable AD3/DIO3 */
#endif
/* XPIN_18: */
#ifdef XPIN_18_USED
#if defined(ENABLE_GPIO_IRQ_XPIN_18)
	(void)xbee_cmd_simple(&xdev, "D2", 3);		/* AD2/DIO2 = Digital input */	
#else
	/* S2B/S2C don't really remove pulls when in mode 0 so disable pulls here */
	*pullup_resistor &= ~shift_xpin_18;	
	(void)xbee_cmd_simple(&xdev, "D2", 0);		/* Disable AD2/DIO2 */
#endif
#endif
// XPIN_19:
#ifdef XPIN_19_USED
#if defined(ENABLE_GPIO_IRQ_XPIN_19)
	(void)xbee_cmd_simple(&xdev, "D1", 3);		/* AD1/DIO1 = Digital input */	
#else
	/* S2B/S2C don't really remove pulls when in mode 0 so disable pulls here */
	*pullup_resistor &= ~shift_xpin_19;	
	(void)xbee_cmd_simple(&xdev, "D1", 0);		/* Disable AD1/DIO1 */
#endif
#endif
// XPIN_20:
#ifdef XPIN_20_USED
#if defined(ENABLE_GPIO_IRQ_XPIN_20)
	(void)xbee_cmd_simple(&xdev, "D0", 3);		/* AD0/DIO0 = Digital input */	
#else
#ifndef ENABLE_COMMISSIONING
	/* S2B/S2C don't really remove pulls when in mode 0 so disable pulls here */
	*pullup_resistor &= ~shift_xpin_20;	
	(void)xbee_cmd_simple(&xdev, "D0", 0);		/* Disable AD0/DIO0 */
#endif
#endif
#endif
	
#pragma MESSAGE DISABLE C5917	/* Removed dead assignment */
	/* Collect pull information from gpio interrupt xml component */
	*pull_direction |= orPD7 | orPD9 | orPD11 | orPD13 | orPD15 | orPD18 | 
					   orPD19 | orPD20;
	*pull_direction &= andPD7 & andPD9 & andPD11 & andPD13 & andPD15 & 
			           andPD18 & andPD19 & andPD20;
	*pullup_resistor |= orPR7 | orPR9 | orPR11 | orPR13 | orPR15 | orPR18 | 
						orPR19 | orPR20;
	*pullup_resistor &= andPR7 & andPR9 & andPR11 & andPR13 & andPR15 & 
						andPR18 & andPR19 & andPR20;

    /* remove RTS_RADIO# pull as we tend to leave it configured as disabled in the radio 
     * (pulls still work in this mode) and the CPU is driving this pin mostly to 0 */
	*pullup_resistor &= ~(1<<5); 
	
	/* Apply Pull configuration */
#ifndef CONFIG_XBEE_S2B
	(void)xbee_cmd_simple(&xdev, "PD", *pull_direction);
#endif
	(void)xbee_cmd_simple(&xdev, "PR", *pullup_resistor);
#elif defined (CONFIG_XBEE_SMT)
	
/* XPIN_1: Gnd */
/* XPIN_2: Vcc */
/* XPIN_3: Not shared */
#if defined(ENABLE_GPIO_IRQ_XPIN_3)
#if (GPIO_IRQ_CFG_PULL_3 == GPIO_IRQ_CFG_PULL_HIGH) 
#warning "Pull-up for IRQ GPIO on XPIN 3 not available. Change to none and use"
		 "external pull."
#endif
#endif
/* XPIN_4: Not shared */
#if defined(ENABLE_GPIO_IRQ_XPIN_4)
#if (GPIO_IRQ_CFG_PULL_4 == GPIO_IRQ_CFG_PULL_HIGH) 
#warning "Pull-up for IRQ GPIO on XPIN 4 not available. Change to none and use"
		 "external pull."
#endif
#endif
/* XPIN_5: */
#ifdef XPIN_5_USED
	*pullup_resistor &= ~shift_xpin_5;
	(void)xbee_cmd_simple(&xdev, "P2", 0);		/* Disable DIO12 */
#endif
/* XPIN_6: Not shared */
/* XPIN_7: */
#ifdef XPIN_7_USED
#ifndef ENABLE_RSSI_PWM
	*pullup_resistor &= ~shift_xpin_7;
	(void)xbee_cmd_simple(&xdev, "P0", 0);		/* Disable PWM RSSI/DIO10 */
#endif
#endif

/* XPIN_8: */
#ifdef XPIN_8_USED
#if defined(ENABLE_GPIO_IRQ_XPIN_8)
	(void)xbee_cmd_simple(&xdev, "P1", 3);		/* PWM1/DIO11 = Digital input */	
#else
	/* S2B/S2C don't really remove pulls when in mode 0 so disable pulls here */
	*pullup_resistor &= ~shift_xpin_8;	
	(void)xbee_cmd_simple(&xdev, "P1", 0);		/* Disable PWM1/DIO11 */
#endif
#endif
		
/* XPIN_9: Not shared */
/* XPIN_10: */
#ifdef XPIN_10_USED
#if defined(ENABLE_GPIO_IRQ_XPIN_10)
	(void)xbee_cmd_simple(&xdev, "D8", 3);		/* SLEEP_RQ#/DIO8 = Digital input */	
#else
#ifndef ENABLE_SLEEP_RQ
	/* S2B/S2C don't really remove pulls when in mode 0 so disable pulls here */
	*pullup_resistor &= ~shift_xpin_10;
	(void)xbee_cmd_simple(&xdev, "D8", 0);		/* Disable SLEEP_RQ#/DIO8 */
#endif
#endif
#endif
/* XPIN_11: GND */
/* XPIN_12: */
#ifdef XPIN_12_USED
	(void)xbee_cmd_simple(&xdev, "P9", 0);		/* Disable SPI_Atn#/DIO19 */
#endif
/* XPIN_13: Gnd */
/* XPIN_14: */
#ifdef XPIN_14_USED
	(void)xbee_cmd_simple(&xdev, "P8", 0);		/* Disable SPI_CLK/DIO18 */
#endif
/* XPIN_15: */
#ifdef XPIN_15_USED
	(void)xbee_cmd_simple(&xdev, "P7", 0);		/* Disable SPI_SEL/DIO17 */
#endif
/* XPIN_16: */
#ifdef XPIN_16_USED
	(void)xbee_cmd_simple(&xdev, "P6", 0);		/* Disable SPI_MOSI/DIO16 */
#endif
/* XPIN_17: */
#ifdef XPIN_17_USED
	(void)xbee_cmd_simple(&xdev, "P5", 0);		/* Disable SPI_MISO/DIO15 */
#endif
/* XPIN_18: JTAG */
/* XPIN_19: JTAG */
/* XPIN_20: JTAG */
/* XPIN_21: JTAG */
/* XPIN_22: GND */
/* XPIN_23: Not connected */
/* XPIN_24: */
#ifdef XPIN_24_USED
#if defined(ENABLE_GPIO_IRQ_XPIN_24)
	(void)xbee_cmd_simple(&xdev, "D4", 3);		/* JTRst/DIO4 = Digital input */
#else
	/* S2B/S2C don't really remove pulls when in mode 0 so disable pulls here */
	*pullup_resistor &= ~shift_xpin_24;
	(void)xbee_cmd_simple(&xdev, "D4", 0);		/* Disable JTRst/DIO4 */
#endif
#endif
/* XPIN_25: */
#ifdef XPIN_25_USED
	/* Disable CTS#/DIO7 WARNING: Seems that it is not correct.*/
	/*(void)xbee_cmd_simple(&xdev, "D7", 0); */
#endif
/* XPIN_26: */
#ifdef XPIN_26_USED
#if defined(ENABLE_GPIO_IRQ_XPIN_26)
#ifndef ENABLE_ON_SLEEP
	(void)xbee_cmd_simple(&xdev, "D9", 3);		/* On_SLP#/DIO9 = Digital input */	
#endif
#else
#ifndef ENABLE_ON_SLEEP
	/* S2B/S2C don't really remove pulls when in mode 0 so disable pulls here */
	*pullup_resistor &= ~shift_xpin_26;	
	(void)xbee_cmd_simple(&xdev, "D9", 0);		/* Disable On_SLP#/DIO9 */
#endif
#endif
#endif
/* XPIN_27: Not shared */
/* XPIN_28: */
#ifdef XPIN_28_USED
#if defined(ENABLE_GPIO_IRQ_XPIN_28)
	(void)xbee_cmd_simple(&xdev, "D5", 3);		/* Assoc/DIO5 = Digital input */	
#else
#ifndef ENABLE_ASSOCIATION_LED
	/* S2B/S2C don't really remove pulls when in mode 0 so disable pulls here */
	*pullup_resistor &= ~shift_xpin_28;	
	(void)xbee_cmd_simple(&xdev, "D5", 0);		/* Disable Assoc/DIO5 */
#endif
#endif
#endif
/* XPIN_29: Not shared */
#if defined(ENABLE_GPIO_IRQ_XPIN_29)
#if (GPIO_IRQ_CFG_PULL_29 == GPIO_IRQ_CFG_PULL_HIGH) 
#warning "Pull-up for IRQ GPIO on XPIN 29 not available. Change to none and use"
		 "external pull."
#endif
#endif
/* XPIN_30: */
#ifdef XPIN_30_USED
	*pullup_resistor &= ~shift_xpin_30;	
	(void)xbee_cmd_simple(&xdev, "D3", 0);		/* Disable AD3/DIO3 */
#endif
/* XPIN_31: */
#ifdef XPIN_31_USED
#if defined(ENABLE_GPIO_IRQ_XPIN_31)
	(void)xbee_cmd_simple(&xdev, "D2", 3);		/* AD2/DIO2 = Digital input */	
#else
	/* S2B/S2C don't really remove pulls when in mode 0 so disable pulls here */
	*pullup_resistor &= ~shift_xpin_31;	
	(void)xbee_cmd_simple(&xdev, "D2", 0);		/* Disable AD2/DIO2 */
#endif
#endif	
/* XPIN_32: */
#ifdef XPIN_32_USED
#if defined(ENABLE_GPIO_IRQ_XPIN_32)
	(void)xbee_cmd_simple(&xdev, "D1", 3);		/* AD1/DIO1 = Digital input */	
#else
	/* S2B/S2C don't really remove pulls when in mode 0 so disable pulls here */
	*pullup_resistor &= ~shift_xpin_32;
	(void)xbee_cmd_simple(&xdev, "D1", 0);		/* Disable AD1/DIO1 */
#endif
#endif
/* XPIN_33: */
#ifdef XPIN_33_USED
#if defined(ENABLE_GPIO_IRQ_XPIN_33)
	(void)xbee_cmd_simple(&xdev, "D0", 3);		/* AD0/DIO0 = Digital input */	
#else
#ifndef ENABLE_COMMISSIONING
	/* S2B/S2C don't really remove pulls when in mode 0 so disable pulls here */
	*pullup_resistor &= ~shift_xpin_33;	
	(void)xbee_cmd_simple(&xdev, "D0", 0);		/* Disable AD0/DIO0 */
#endif
#endif
#endif	
/* XPIN_34: Not connected */
/* XPIN_35: GND */
/* XPIN_36: Not shared */
/* XPIN_37: Not connected */

#pragma MESSAGE DISABLE C5917	/* Removed dead assignment */
	/* Collect pull information from gpio interrupt xml component */
	*pull_direction |= orPD8 | orPD10 | orPD24 | orPD26 | orPD28 | orPD31 |
					   orPD32 | orPD33;
	*pull_direction &= andPD8 & andPD10 & andPD24 & andPD26 & andPD28 & 
					   andPD31 & andPD32 & andPD33;
	*pullup_resistor |= orPR8 | orPR10 | orPR24 | orPR26 | orPR28 | orPR31 | 
						orPR32 | orPR33;
	*pullup_resistor &= andPR8 & andPR10 & andPR24 & andPR26 & andPR28 & 
						andPR31 & andPR32 & andPR33;

    /* remove RTS_RADIO# pull as we tend to leave it configured as disabled in the radio 
     * (pulls still work in this mode) and the CPU is driving this pin mostly to 0 */
	*pullup_resistor &= ~(1<<5); 

	/* Apply Pull configuration */
	(void)xbee_cmd_simple(&xdev, "PD", *pull_direction);
	(void)xbee_cmd_simple(&xdev, "PR", *pullup_resistor);
#endif	
}

void gpio_init(void)
{
	/* Configure unused internal pins as outputs to reduce power consumption */
#ifdef CONFIG_XBEE_THT
	PTADD |= 0x40;
#if !defined(CONFIG_XBEE_S2CTH)
	PTBDD |= 0xC0;
#else
	PTBDD |= 0x40;
#endif
	PTCDD |= 0x0C;
	PTDDD |= 0x0F;
	
	PTAD |= 0x40;
	PTBD |= 0xC0;
	PTCD |= 0x0C;
	PTDD |= 0x0F;
#ifdef CONFIG_XBEE_S2B
	PTEDD |= 0x8F;
	PTED |= 0x8F;
#endif /* CONFIG_XBEE_S2B */
#ifdef CONFIG_XBEE_S3B
	PTEDD |= 0xBF;
	PTED |= 0xBF;
#endif /* CONFIG_XBEE_S3B */
#ifdef CONFIG_XBEE_S2CTH
	PTEDD |= 0xCF;
	PTED |= 0xCF;
#endif /* CONFIG_XBEE_S3B */
#endif /* CONFIG_XBEE_THT */
#ifdef CONFIG_XBEE_SMT
	PTADD |= 0x40;
	PTBDD |= 0x40;
	PTCDD |= 0x0C;

	PTAD |= 0x40;
	PTBD |= 0x40;
	PTCD |= 0x0C;
#ifdef CONFIG_XBEE_S2C
	PTDDD |= 0x0E;
	PTEDD |= 0x90;
	PTDD |= 0x0E;
	PTED |= 0x90;
#endif /* CONFIG_XBEE_S2C */
#ifdef CONFIG_XBEE_S8
	PTDDD |= 0x0E;
	PTEDD |= 0xA8;
	PTDD |= 0x0E;
	PTED |= 0xA8;
#endif /* CONFIG_XBEE_S8 */
#endif /* CONFIG_XBEE_SMT */

#if defined(ENABLE_BANK1_GPIO_IRQ) || defined(ENABLE_BANK2_GPIO_IRQ)
	SCGC2_KBI = 1;	/* Enable clocks for this module */
#endif
#ifdef ENABLE_GPIO_XPIN_1
	(void)gpio_config(XPIN_1, GPIO_CFG_XPIN_1);
#endif
#ifdef ENABLE_GPIO_XPIN_2
	(void)gpio_config(XPIN_2, GPIO_CFG_XPIN_2);
#endif
#ifdef ENABLE_GPIO_XPIN_3
	(void)gpio_config(XPIN_3, GPIO_CFG_XPIN_3);
#endif
#ifdef ENABLE_GPIO_XPIN_4
	(void)gpio_config(XPIN_4, GPIO_CFG_XPIN_4);
#endif
#ifdef ENABLE_GPIO_XPIN_5
	(void)gpio_config(XPIN_5, GPIO_CFG_XPIN_5);
#endif
#ifdef ENABLE_GPIO_XPIN_6
	(void)gpio_config(XPIN_6, GPIO_CFG_XPIN_6);
#endif
#ifdef ENABLE_GPIO_XPIN_7
	(void)gpio_config(XPIN_7, GPIO_CFG_XPIN_7);
#endif
#ifdef ENABLE_GPIO_XPIN_8
	(void)gpio_config(XPIN_8, GPIO_CFG_XPIN_8);
#endif
#ifdef ENABLE_GPIO_XPIN_9
	(void)gpio_config(XPIN_9, GPIO_CFG_XPIN_9);
#endif
#ifdef ENABLE_GPIO_XPIN_10
	(void)gpio_config(XPIN_10, GPIO_CFG_XPIN_10);
#endif
#ifdef ENABLE_GPIO_XPIN_11
	(void)gpio_config(XPIN_11, GPIO_CFG_XPIN_11);
#endif
#ifdef ENABLE_GPIO_XPIN_12
	(void)gpio_config(XPIN_12, GPIO_CFG_XPIN_12);
#endif
#ifdef ENABLE_GPIO_XPIN_13
	(void)gpio_config(XPIN_13, GPIO_CFG_XPIN_13);
#endif
#ifdef ENABLE_GPIO_XPIN_14
	(void)gpio_config(XPIN_14, GPIO_CFG_XPIN_14);
#endif
#ifdef ENABLE_GPIO_XPIN_15
	(void)gpio_config(XPIN_15, GPIO_CFG_XPIN_15);
#endif
#ifdef ENABLE_GPIO_XPIN_16
	(void)gpio_config(XPIN_16, GPIO_CFG_XPIN_16);
#endif
#ifdef ENABLE_GPIO_XPIN_17
	(void)gpio_config(XPIN_17, GPIO_CFG_XPIN_17);
#endif
#ifdef ENABLE_GPIO_XPIN_18
	(void)gpio_config(XPIN_18, GPIO_CFG_XPIN_18);
#endif
#ifdef ENABLE_GPIO_XPIN_19
	(void)gpio_config(XPIN_19, GPIO_CFG_XPIN_19);
#endif
#ifdef ENABLE_GPIO_XPIN_20
	(void)gpio_config(XPIN_20, GPIO_CFG_XPIN_20);
#endif
#ifdef CONFIG_XBEE_SMT
	/* SMT extended GPIO pins */
#ifdef ENABLE_GPIO_XPIN_21
	(void)gpio_config(XPIN_21, GPIO_CFG_XPIN_21);
#endif
#ifdef ENABLE_GPIO_XPIN_24
	(void)gpio_config(XPIN_24, GPIO_CFG_XPIN_24);
#endif
#ifdef ENABLE_GPIO_XPIN_25
	(void)gpio_config(XPIN_25, GPIO_CFG_XPIN_25);
#endif
#ifdef ENABLE_GPIO_XPIN_26
	(void)gpio_config(XPIN_26, GPIO_CFG_XPIN_26);
#endif
#ifdef ENABLE_GPIO_XPIN_28
	(void)gpio_config(XPIN_28, GPIO_CFG_XPIN_28);
#endif
#ifdef ENABLE_GPIO_XPIN_29
	(void)gpio_config(XPIN_29, GPIO_CFG_XPIN_29);
#endif
#ifdef ENABLE_GPIO_XPIN_30
	(void)gpio_config(XPIN_30, GPIO_CFG_XPIN_30);
#endif
#ifdef ENABLE_GPIO_XPIN_31
	(void)gpio_config(XPIN_31, GPIO_CFG_XPIN_31);
#endif
#ifdef ENABLE_GPIO_XPIN_32
	(void)gpio_config(XPIN_32, GPIO_CFG_XPIN_32);
#endif
#ifdef ENABLE_GPIO_XPIN_33
	(void)gpio_config(XPIN_33, GPIO_CFG_XPIN_33);
#endif
#endif /* CONFIG_XBEE_SMT */
	
#ifdef ENABLE_GPIO_IRQ_XPIN_2
	(void)gpio_config_irq(XPIN_2, GPIO_CFG_IRQ_MODE_2, GPIO_IRQ_LEVEL_EDGE_2);
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_3
	(void)gpio_config_irq(XPIN_3, GPIO_CFG_IRQ_MODE_3, GPIO_IRQ_LEVEL_EDGE_3);
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_4
	(void)gpio_config_irq(XPIN_4, GPIO_CFG_IRQ_MODE_4, GPIO_IRQ_LEVEL_EDGE_4);
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_7
	(void)gpio_config_irq(XPIN_7, GPIO_CFG_IRQ_MODE_7, GPIO_IRQ_LEVEL_EDGE_7);
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_8
	(void)gpio_config_irq(XPIN_8, GPIO_CFG_IRQ_MODE_8, GPIO_IRQ_LEVEL_EDGE_8);
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_9
	(void)gpio_config_irq(XPIN_9, GPIO_CFG_IRQ_MODE_9, GPIO_IRQ_LEVEL_EDGE_9);
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_10
	(void)gpio_config_irq(XPIN_10, GPIO_CFG_IRQ_MODE_10, GPIO_IRQ_LEVEL_EDGE_10);
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_11
	(void)gpio_config_irq(XPIN_11, GPIO_CFG_IRQ_MODE_11, GPIO_IRQ_LEVEL_EDGE_11);
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_13
	(void)gpio_config_irq(XPIN_13, GPIO_CFG_IRQ_MODE_13, GPIO_IRQ_LEVEL_EDGE_13);
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_15
	(void)gpio_config_irq(XPIN_15, GPIO_CFG_IRQ_MODE_15, GPIO_IRQ_LEVEL_EDGE_15);
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_16
	(void)gpio_config_irq(XPIN_16, GPIO_CFG_IRQ_MODE_16, GPIO_IRQ_LEVEL_EDGE_16);
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_18
	(void)gpio_config_irq(XPIN_18, GPIO_CFG_IRQ_MODE_18, GPIO_IRQ_LEVEL_EDGE_18);
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_19
	(void)gpio_config_irq(XPIN_19, GPIO_CFG_IRQ_MODE_19, GPIO_IRQ_LEVEL_EDGE_19);
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_20
	(void)gpio_config_irq(XPIN_20, GPIO_CFG_IRQ_MODE_20, GPIO_IRQ_LEVEL_EDGE_20);
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_24
	(void)gpio_config_irq(XPIN_24, GPIO_CFG_IRQ_MODE_24, GPIO_IRQ_LEVEL_EDGE_24);
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_26
	(void)gpio_config_irq(XPIN_26, GPIO_CFG_IRQ_MODE_26, GPIO_IRQ_LEVEL_EDGE_26);
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_28
	(void)gpio_config_irq(XPIN_28, GPIO_CFG_IRQ_MODE_28, GPIO_IRQ_LEVEL_EDGE_28);
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_29
	(void)gpio_config_irq(XPIN_29, GPIO_CFG_IRQ_MODE_29, GPIO_IRQ_LEVEL_EDGE_29);
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_31
	(void)gpio_config_irq(XPIN_31, GPIO_CFG_IRQ_MODE_31, GPIO_IRQ_LEVEL_EDGE_31);
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_32
	(void)gpio_config_irq(XPIN_32, GPIO_CFG_IRQ_MODE_32, GPIO_IRQ_LEVEL_EDGE_32);
#endif
#ifdef ENABLE_GPIO_IRQ_XPIN_33
	(void)gpio_config_irq(XPIN_33, GPIO_CFG_IRQ_MODE_33, GPIO_IRQ_LEVEL_EDGE_33);
#endif
	
	/**
	 * Configure both banks for level irqs.
	 * Edge irqs are simulated by the software
	 */
#ifdef ENABLE_BANK1_GPIO_IRQ	
	KBI1SC_KBIMOD = 1;
#endif
#ifdef ENABLE_BANK2_GPIO_IRQ	
	KBI2SC_KBIMOD = 1;
#endif
#if defined(ENABLE_BANK1_GPIO_IRQ) || defined(ENABLE_BANK2_GPIO_IRQ)
	gpio_irq_enable(1);
#endif


#ifdef ENABLE_PORT_0
	port_config(PORT0, PORT0_CFG);
#endif
#ifdef ENABLE_PORT_1
	port_config(PORT1, PORT1_CFG);
#endif
#ifdef ENABLE_PORT_2
	port_config(PORT2, PORT2_CFG);
#endif
#ifdef ENABLE_PORT_3
	port_config(PORT3, PORT3_CFG);
#endif
}

#ifdef ENABLE_ADC
void adc_init(void)
{
	(void)adc_config(ADC_CFG);
#ifdef ENABLE_ADC_XPIN_2
	(void)adc_ch_enable(XPIN_2, 1);
#endif
#ifdef ENABLE_ADC_XPIN_3
	(void)adc_ch_enable(XPIN_3, 1);
#endif
#ifdef ENABLE_ADC_XPIN_7
	(void)adc_ch_enable(XPIN_7, 1);
#endif
#ifdef ENABLE_ADC_XPIN_11
	(void)adc_ch_enable(XPIN_11, 1);
#endif
#ifdef ENABLE_ADC_XPIN_13
	(void)adc_ch_enable(XPIN_13, 1);
#endif
#ifdef ENABLE_ADC_XPIN_17
	(void)adc_ch_enable(XPIN_17, 1);
#endif
#ifdef ENABLE_ADC_XPIN_18
	(void)adc_ch_enable(XPIN_18, 1);
#endif
#ifdef ENABLE_ADC_XPIN_19
	(void)adc_ch_enable(XPIN_19, 1);
#endif
#ifdef ENABLE_ADC_XPIN_20
	(void)adc_ch_enable(XPIN_20, 1);
#endif
}
#endif

/* #define DBG_RADIO_INITIAL_STATE */

#ifdef DBG_RADIO_INITIAL_STATE
#define RADIO_FLAG_DETECTED 0x80
#define RADIO_FLAG_API 		0x40
#define RADIO_FLAG_FAST 	0x20
#define RADIO_BAUD_MASK		0x0F
uint8_t org_cfg = 0;
#endif

static int xbee_check_answer(const uint8_t *expected, uint8_t bytes,
							 uint16_t timeout)
{
	uint8_t read, rxb;
	const uint8_t *pbuf;

	rtc_set_timeout(timeout);
	do {
		sys_watchdog_reset();
		if (rtc_timeout_expired())
			return -ETIMEDOUT;
		read = (uint8_t)xbee_ser_rx_used(&EMBER_SERIAL_PORT);
	} while (read < bytes);

	pbuf = expected;
	for (read = 0; read < bytes; read++, pbuf++) {
		xbee_ser_read(&EMBER_SERIAL_PORT, &rxb, 1);
		if (rxb != *pbuf)
			break;
	}

	return read == bytes ? 1 : 0;
}

static int xbee_get_answer(const uint8_t *expected, uint8_t bytes_fix, 
						   uint8_t bytes_data, uint8_t* pdata, uint16_t timeout)
{
	uint8_t read, rxb;
	const uint8_t *pbuf;

	rtc_set_timeout(timeout);
	do {
		sys_watchdog_reset();
		if (rtc_timeout_expired())
			return -ETIMEDOUT;
		read = (uint8_t)xbee_ser_rx_used(&EMBER_SERIAL_PORT);
	} while (read < (bytes_fix+bytes_data+1));	/* fix + variable + checksum */

	pbuf = expected;

	for (read = 0; read < bytes_fix; read++, pbuf++) {
		xbee_ser_read(&EMBER_SERIAL_PORT, &rxb, 1);
		if (rxb != *pbuf)
			break;
	}
	if (read != bytes_fix)
		return 0;
	
	for (read = 0; read < bytes_data; read++, pdata++) {
		xbee_ser_read(&EMBER_SERIAL_PORT, &rxb, 1);
		*pdata = rxb;
	}

	/* Flush checksum */
	/* TO_DO: Compute checksum */
	xbee_ser_read(&EMBER_SERIAL_PORT, &rxb, 1);

	return 1;
}

static uint32_t radio_switch_to_api_mode_and_autorate(void)
{
	uint8_t i;
	int ret = 0;
	
	/* Test on the preferred radio configuration (rates[RADIO_RATE_IDX]-API). 
	 * If radio is at that speed there should arrive a modem status report
	 */
	(void)radio_uart_config(rates[RADIO_RATE_IDX], 0);
	ret = xbee_check_answer(modem_status_resp, ARRAY_SIZE(modem_status_resp),
							3 * HZ);
	if (ret == 1) {
#ifdef DBG_RADIO_INITIAL_STATE
		/* Report rates[RADIO_RATE_IDX]-API-FAST */
		org_cfg = RADIO_FLAG_DETECTED | RADIO_FLAG_API | RADIO_FLAG_FAST | 
				  RADIO_RATE_IDX;
#endif
		return rates[RADIO_RATE_IDX];
	}
		
	for (i = 0; i < ARRAY_SIZE(rates); i++) {
		(void)radio_uart_config(rates[i], 0);
		
#ifndef CONFIG_RADIO_UART_BAUDRATE		
		delay_ticks(HZ / 4);	/* guard time */
		/* A modem status may arrive in between !! */
		xbee_ser_rx_flush(&EMBER_SERIAL_PORT);
		xbee_ser_write(&EMBER_SERIAL_PORT, ATBD7_cmd, ARRAY_SIZE(ATBD7_cmd));
		ret = xbee_check_answer(ATBD7_resp, ARRAY_SIZE(ATBD7_resp), 3 * HZ);
		if (ret == 1) {
#ifdef DBG_RADIO_INITIAL_STATE
			org_cfg = RADIO_FLAG_DETECTED | RADIO_FLAG_API | i;
#endif
			if (rates[i] != rates[RADIO_RATE_IDX]) {
				/* First AC, then WR */
				xbee_ser_write(&EMBER_SERIAL_PORT, ATAC_cmd, ARRAY_SIZE(ATAC_cmd));
				(void)radio_uart_config(rates[RADIO_RATE_IDX], 0);
				delay_ticks(HZ / 4);	/* guard time */
				/* Make API, rates[RADIO_RATE_IDX] persistent */
				xbee_ser_write(&EMBER_SERIAL_PORT, ATWR_cmd, ARRAY_SIZE(ATWR_cmd));			
			}
			delay_ticks(HZ/4);
			
			return rates[RADIO_RATE_IDX];
		}
#endif
		
#ifndef CONFIG_XBEE_S2B /* Enabled for all modules supporting 'atAP' command: S2C, S8, S3B, S2CTH */
		
		delay_ticks(HZ / 4);	/* guard time */
				
		/* Switch to command mode, assuming we are in transparent mode */
		/* A modem status may arrive in between !! */
		xbee_ser_rx_flush(&EMBER_SERIAL_PORT);
		xbee_ser_write(&EMBER_SERIAL_PORT, "+++", 3);
		ret = xbee_check_answer("OK\r", 3, 3 * HZ);
		if (ret == 1) {
			/* A modem status may arrive in between !! */
			xbee_ser_rx_flush(&EMBER_SERIAL_PORT);	
			xbee_ser_write(&EMBER_SERIAL_PORT, "ATAP1\r", 6);
			ret = xbee_check_answer("OK\r", 3, HZ);
			if (ret == 1) {
				/* A modem status may arrive in between !! */
				xbee_ser_rx_flush(&EMBER_SERIAL_PORT);
				xbee_ser_write(&EMBER_SERIAL_PORT, "ATBD7\r", 6);
				ret = xbee_check_answer("OK\r", 3, HZ);
				if (ret == 1) {
					/* Make API, rates[RADIO_RATE_IDX] persistent */
					/* A modem status may arrive in between !! */
					xbee_ser_rx_flush(&EMBER_SERIAL_PORT);
					xbee_ser_write(&EMBER_SERIAL_PORT, "ATWR\r", 5);
					ret = xbee_check_answer("OK\r", 3, 5 * HZ);
					if (ret == 1) {
						xbee_ser_write(&EMBER_SERIAL_PORT, "ATCN\r", 5);
						/* Change baudrate and wait for the modem status ? */
						delay_ticks(HZ / 4);
#ifdef DBG_RADIO_INITIAL_STATE
						org_cfg = RADIO_FLAG_DETECTED | i;
#endif
						return rates[RADIO_RATE_IDX];
					}
				}
			}
		}
#endif		
	}
	
#ifdef CONFIG_RADIO_UART_BAUDRATE
	return CONFIG_RADIO_UART_BAUDRATE;
#else
	return 0;
#endif
}

void sys_hw_init(void)
{
#ifndef CONFIG_XBEE_S8	/* S8 has 32bit registers */
	uint16_t				pull_direction = 0;
	uint16_t				pullup_resistor = 0;
#else
	uint32_t				pull_direction = 0;
	uint32_t				pullup_resistor = 0;
#endif
	
	sys_init();

#ifdef ENABLE_LVD
#if (LVD_BEHAVIOR == LVD_IRQ_ENABLE)
	SPMSC1_LVDRE = 0; /* Disable LVD Reset*/
	lvd_irq_enable(TRUE);	
#endif
	SPMSC1_LVDE = 1;
	lvd_set_trigger(LVD_TRIGGER);
#endif /* ENABLE_LVD */
	
#ifdef ENABLE_RTC
	/* Early initialization of the system tick, used for timing and delays
	 * during the initialization of rest of the peripherals 
	 */
	(void)rtc_config();
#endif

	sys_irqs_enable();
	
#ifdef ENABLE_UART
	(void)uart_config(UART_CFG_BAUDRATE, UART_CFG);
#endif
	
#ifdef ENABLE_SLEEP_RQ
	(void)gpio_set(SLEEP_RQ_XPIN, 0);
	(void)gpio_config(SLEEP_RQ_XPIN, GPIO_CFG_OUTPUT);
	/* This ensures that the radio will be awake */
#endif
	EMBER_SERIAL_PORT.baudrate = radio_switch_to_api_mode_and_autorate();
	(void)radio_uart_config(EMBER_SERIAL_PORT.baudrate, 0);		/* Apply new baudrate */

#ifndef CONFIG_XBEE_S2B
	xbee_ser_write(&EMBER_SERIAL_PORT, ATBPD_cmd, ARRAY_SIZE(ATBPD_cmd));
	xbee_get_answer(ATBPD_resp_fix, ARRAY_SIZE(ATBPD_resp_fix), sizeof(pull_direction), (uint8_t*)&pull_direction, 2 * HZ);
#endif
	xbee_ser_write(&EMBER_SERIAL_PORT, ATBPR_cmd, ARRAY_SIZE(ATBPR_cmd));
	xbee_get_answer(ATBPR_resp_fix, ARRAY_SIZE(ATBPR_resp_fix), sizeof(pullup_resistor), (uint8_t*)&pullup_resistor, 2 * HZ);
	
	/* Initialize the AT Command layer for this XBee device to reconfigure
	 * the GPIOs of the Ember chip accordingly to the user configuration.
	 */
	xbee_dev_init(&xdev, &EMBER_SERIAL_PORT, NULL, NULL);
	
	/* Tell the library we are not using CTS# so xbee_frame_write never fails 
	 * checking it. We can afford that since the xbee_ser_write function will 
	 * always check CTS# regardless the flow-control configured below. 
	 */
	xbee_dev_flowcontrol(&xdev, FALSE);

#ifndef ENABLE_POWER_MANAGEMENT
	/* Disable radio sleep mode if power management is not selected. Some 
	 * End-Device firmwares will not accept the request.
	 */
	(void)xbee_cmd_simple(&xdev, "SM", 0);	
#endif
	radio_gpio_init(&pull_direction, &pullup_resistor);

	sys_irqs_disable();
	gpio_init();
	
#ifdef ENABLE_SPI_PORT
#ifdef _MC9S08QE32_H
#if (SPI_PINOUT_MUX == 2)
	/* SPI through secondary pin multiplexing (Pins: 14, 16 & 17)*/
	SOPT2_SPIPS = 1;
#else
	/* SPI through primary pin multiplexing (Pins: 5, 24 & 31)*/
	SOPT2_SPIPS = 0;
#endif
#endif
	(void)spi_config(SPI0_CFG_PRE_DIV, SPI0_CFG_BAUD_DIV, SPI0_CFG);
#endif


#ifdef ENABLE_ADC
	adc_init();
#endif
	
#ifdef ENABLE_FLASH
	(void)flash_config();
#ifdef ENABLE_VIRTUAL_EEPROM
	(void)veeprom_init();
#endif
#endif

#ifdef RTC_ENABLE_PERIODIC_TASK
	(void)rtc_set_periodic_task_period(RTC_CFG_PERIODIC_TASK_PERIOD);
#endif

#ifdef ENABLE_I2C
	(void)i2c_config(0);
#endif

#ifdef ENABLE_ONE_WIRE
	(void)one_wire_config();
#endif

#ifdef ENABLE_24XXX_EEPROM
#ifdef EEPROM_24XXX_0
	(void)eeprom_24xxx_config(EEPROM_24XXX_0, EEPROM_24XXX_SLAVE_SUBADDRESS_0, 
						EEPROM_24XXX_ADDRESS_BYTES_0, EEPROM_24XXX_PAGE_SIZE_0);
#endif
#ifdef EEPROM_24XXX_1
	(void)eeprom_24xxx_config(EEPROM_24XXX_1, EEPROM_24XXX_SLAVE_SUBADDRESS_1,
						EEPROM_24XXX_ADDRESS_BYTES_1, EEPROM_24XXX_PAGE_SIZE_1);
#endif
#ifdef EEPROM_24XXX_2
	(void)eeprom_24xxx_config(EEPROM_24XXX_2, EEPROM_24XXX_SLAVE_SUBADDRESS_2,
						EEPROM_24XXX_ADDRESS_BYTES_2, EEPROM_24XXX_PAGE_SIZE_2);
#endif
#ifdef EEPROM_24XXX_3
	(void)eeprom_24xxx_config(EEPROM_24XXX_3, EEPROM_24XXX_SLAVE_SUBADDRESS_3,
						EEPROM_24XXX_ADDRESS_BYTES_3, EEPROM_24XXX_PAGE_SIZE_3);
#endif
#ifdef EEPROM_24XXX_4
	(void)eeprom_24xxx_config(EEPROM_24XXX_4, EEPROM_24XXX_SLAVE_SUBADDRESS_4,
						EEPROM_24XXX_ADDRESS_BYTES_4, EEPROM_24XXX_PAGE_SIZE_4);
#endif
#ifdef EEPROM_24XXX_5
	(void)eeprom_24xxx_config(EEPROM_24XXX_5, EEPROM_24XXX_SLAVE_SUBADDRESS_5,
						EEPROM_24XXX_ADDRESS_BYTES_5, EEPROM_24XXX_PAGE_SIZE_5);
#endif
#ifdef EEPROM_24XXX_6
	(void)eeprom_24xxx_config(EEPROM_24XXX_6, EEPROM_24XXX_SLAVE_SUBADDRESS_6,
						EEPROM_24XXX_ADDRESS_BYTES_6, EEPROM_24XXX_PAGE_SIZE_6);
#endif
#ifdef EEPROM_24XXX_7
	(void)eeprom_24xxx_config(EEPROM_24XXX_7, EEPROM_24XXX_SLAVE_SUBADDRESS_7,
						EEPROM_24XXX_ADDRESS_BYTES_7, EEPROM_24XXX_PAGE_SIZE_7);
#endif
#endif /* ENABLE_24XXX_EEPROM */

	KBI1SC_KBACK = 1;
	sys_irqs_enable();
}

void sys_app_banner(void)
{
#if (ENABLE_STDIO_PRINTF_SCANF == 1)
#ifdef CONFIG_XBEE_S2B
#define	XBEE_VERSION	"S2B"
#elif defined(CONFIG_XBEE_S2C)
#define	XBEE_VERSION	"S2C"
#elif defined(CONFIG_XBEE_S8)
#define	XBEE_VERSION	"S8"
#elif defined(CONFIG_XBEE_S3B)
#define	XBEE_VERSION	"S3B"
#elif defined(CONFIG_XBEE_S2CTH)
#define	XBEE_VERSION	"S2CTH"
#endif
	
	char addr[ADDR64_STRING_LENGTH];

    sys_watchdog_reset();

	printf("\n\n---------------------------------------------\n");
	printf("  o Application: %s\n", APP_VERSION_STRING);
	printf("  o XBee module: %s %dkB flash\n", XBEE_VERSION, CONFIG_XBEE_FLASH_LEN);
	printf("  o HW address : %s\n", addr64_format(addr, &xdev.wpan_dev.address.ieee));
	printf("  o HW version : 0x%x\n", xdev.hardware_version);
	printf("  o FW version : 0x%lx", xdev.firmware_version);

    sys_watchdog_reset();

	switch ((unsigned) (xdev.firmware_version & XBEE_NODETYPE_MASK)) {
		case XBEE_NODETYPE_COORD:	
			printf(" (coordinator)\n");
			break;
		case XBEE_NODETYPE_ROUTER:
			printf(" (router)\n");
			break;
		case XBEE_NODETYPE_ENDDEV:
			printf(" (end-device)\n");
			break;
		default:
			printf("\n");
			break;
	}
#ifdef XBEE_ATCMD_PARAM_ID
#ifdef CONFIG_XBEE_ZB
	printf("  o PAN ID     : %s\n", XBEE_ATCMD_PARAM_ID);
#elif defined(CONFIG_XBEE_DIGI_MESH)
	printf("  o Network ID : %s\n", XBEE_ATCMD_PARAM_ID);
#endif
#endif
#ifdef DBG_RADIO_INITIAL_STATE
	if (org_cfg != (RADIO_FLAG_DETECTED | RADIO_FLAG_FAST | 
		RADIO_FLAG_API | RADIO_RATE_IDX)) {
		if (!(org_cfg & RADIO_FLAG_DETECTED)) {
			printf("Radio NOT detected !!!!!!!!\n");
		} else {
			printf("  o radio start: %ld-%c-", rates[org_cfg & RADIO_BAUD_MASK],
					(org_cfg & RADIO_FLAG_FAST)?'F':'S' );
			if (org_cfg & RADIO_FLAG_API)
				printf("API\n");
			else
				printf("AT\n");
					
		}
	}
#endif
	printf("---------------------------------------------\n\n");

    sys_watchdog_reset();
#undef XBEE_VERSION
#endif /* (ENABLE_STDIO_PRINTF_SCANF == 1) */
}
