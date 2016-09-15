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

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

#include <hidef.h> /* for EnableInterrupts macro */
#include <xbee_config.h>
#include <types.h>
#include <hardware.h>
#include <lvd.h>

#if (CONFIG_XBEE_FLASH_LEN == 32) 
#include <mc9s08qe32.h>
#elif (CONFIG_XBEE_FLASH_LEN == 128)
#include <mc9s08qe128.h>
#endif

#define XBEE_HW_ID_MASK		0x70
#define INT_REF_FREQ		31250
//#define INT_REF_FREQ		32768

#if INT_REF_FREQ == 31250
#if defined(SYS_CFG_CLK_16_MHz)
#define SYS_CFG_DRS_DMX		0
#define SYS_CFG_FLL_FACTOR	512
#define SYS_CLK_FREQ		16000000
#elif defined(SYS_CFG_CLK_32_MHz)
#define SYS_CFG_DRS_DMX		2
#define SYS_CFG_FLL_FACTOR	1024
#define SYS_CLK_FREQ		32000000
#elif defined(SYS_CFG_CLK_48_MHz)
#define SYS_CFG_DRS_DMX		4
#define SYS_CFG_FLL_FACTOR	1536
#define SYS_CLK_FREQ		48000000
#else
#define SYS_CFG_DRS_DMX		2
#define SYS_CFG_FLL_FACTOR	1024
#define SYS_CLK_FREQ		32000000
#endif
#else	/* 32768 Hz */
#if defined(SYS_CFG_CLK_19_92_MHz)
#define SYS_CFG_DRS_DMX		1
#define SYS_CFG_FLL_FACTOR	608
#define SYS_CLK_FREQ		19920000
#elif defined(SYS_CFG_CLK_39_85_MHz)
#define SYS_CFG_DRS_DMX		3
#define SYS_CFG_FLL_FACTOR	1216
#define SYS_CLK_FREQ		39850000
#elif defined(SYS_CFG_CLK_59_77_MHz)
#define SYS_CFG_DRS_DMX		5
#define SYS_CFG_FLL_FACTOR	1824
#define SYS_CLK_FREQ		59770000
#else
#define SYS_CFG_DRS_DMX		3
#define SYS_CFG_FLL_FACTOR	1216
#define SYS_CLK_FREQ		39850000
#endif
#endif /* INT_REF_FREQ */

/* Bus clock configured by user settings */
/* TO_DO, revisit this... seems that the bus div doesnt work as documented
 * in the DS. The minimum divisor seems to be 2
 */
#if defined(SYS_CFG_BUSCLK_SYSCLK_DIV1)
/* #define SYS_CFG_BUSDIV		0 */
/* #define BUS_CLK_DIV			1 */
#elif defined(SYS_CFG_BUSCLK_SYSCLK_DIV2)
#define SYS_CFG_BUSDIV		0
#define BUS_CLK_DIV			2
#elif defined(SYS_CFG_BUSCLK_SYSCLK_DIV4)
#define SYS_CFG_BUSDIV		1
#define BUS_CLK_DIV			4
#elif defined(SYS_CFG_BUSCLK_SYSCLK_DIV8)
#define SYS_CFG_BUSDIV		2
#define BUS_CLK_DIV			8
#else
#define SYS_CFG_BUSDIV		0
#define BUS_CLK_DIV			2
#endif

#define BUS_CLK_FREQ		(SYS_CLK_FREQ / BUS_CLK_DIV)
#define FLL_CLK_FREQ		(SYS_CLK_FREQ / SYS_CFG_FLL_FACTOR / 2)

/* WARNING C1420: Result of function-call is ignored */
#pragma MESSAGE DISABLE C1420

#ifndef ENABLE_STDIO_PRINTF_SCANF
#define ENABLE_STDIO_PRINTF_SCANF	0
#endif

#if (ENABLE_STDIO_PRINTF_SCANF != 1)
int printf_void(const char * s, ...);
int scanf_void(const char * s, ...);
#define printf		printf_void
#define scanf		scanf_void
#endif

#ifdef ENABLE_POWER_MANAGEMENT
/* These macros are used to let the user know which was the wakeup source */
#define WAKEUP_UNKNOWN			0
#define WAKEUP_UART				(1 << 0)
#define WAKEUP_PERIODIC_TASK	(1 << 1)
#define WAKEUP_TIMEOUT			(1 << 2)
#define WAKEUP_ALARM			(1 << 3)
#define WAKEUP_GPIO				(1 << 4)
#define WAKEUP_RADIO			(1 << 5)
#endif
/* @ingroup types */
typedef enum bl_rst_casues {
	/* reset pin, low voltage, Power On Reset, gotoAPP */
	BL_CAUSE_NOTHING					= 0x0000,
	/* bl_rst_casues incremented each time until Bad App */
	BL_CAUSE_NOTHING_COUNT				= 0x0001,
	BL_CAUSE_BAD_APP					= 0x0010,
} bl_rst_casues_t;

/* @ingroup types */
typedef enum app_rst_causes {
	/* 0x0000 to 0x00FD are considered valid for APP Use */
	APP_CAUSE_NOTHING					= 0x0000,
	APP_CAUSE_COPY_FLASH_SUCCESS		= 0x00FE,
	APP_CAUSE_COPY_FLASH_FAILED			= 0x00FF,
	APP_CAUSE_FIRMWARE_UPDATE			= 0x5981,
	/* APP_CAUSE_FIRMWARE_UPDATE | 0x0002 */
	APP_CAUSE_FIRMWARE_UPDATE_APS		= 0x5983,
	APP_CAUSE_BYPASS_MODE				= 0x4682,
	APP_CAUSE_BOOTLOADER_MENU			= 0x6A18,
	/* (int)0xAB7E */
	APP_CAUSE_COPY_FLASH_TO_RUN_SPACE	= -0x5482,
	APP_CAUSE_REQUEST_SOPT1_NOT_WRITTEN	= 0x7815,
} app_rst_casuses_t;

#include "xbee/device.h"

extern xbee_dev_t xdev;

void sys_udelay(uint8_t delay);
void sys_watchdog_reset(void);
void sys_irqs_disable(void);
void sys_irqs_enable(void);
uint8_t sys_get_hw_id(void);
void sys_halt(char * str);
void sys_hw_init(void);
void sys_clocks_init(void);
void sys_reset(app_rst_casuses_t reason);
void sys_init(void);
void sys_app_banner(void);

#endif /* __SYSTEM_H_ */
