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
/**
 *	Platform-specific layer provides a consistent System API to upper layers
 *	of the driver. 
 *
 *	@ingroup cpu_system 
 *
 *	@defgroup cpu_system 
 *
 *	@section system System API Overview 
 *
 *	This API contains the functions to configure and control the system 
 *	module of the programmable XBee devices.
 *	
 *	- System initialization and configuration functions:
 *		- sys_clocks_init()
 *		- sys_init()
 *		- sys_reset()
 * 		- sys_watchdog_reset()
 *		- sys_irqs_disable()
 *		- sys_irqs_enable()
 *		- sys_get_hw_id()
 *		- sys_halt()
 */
#include <stdio.h>
#include <system.h>
#include <types.h>

#ifdef CONFIG_XBEE_DEBUG_BUILD
/* Set flash security to unsecured to allow debugging */
#define NVOPT_INIT_VAL				0x02
#else
/* For release builds, secure the flash to avoid reading the code with the debugger */
#define NVOPT_INIT_VAL				0x00
#endif

#pragma CONST_SEG APPLICATION_VERSION 
static const char app_version[] = APP_VERSION_STRING;
#pragma CONST_SEG DEFAULT
#pragma DATA_SEG SHARED_DATA
volatile app_rst_casuses_t app_rst	@0x200;
/* Reserved 						@0x202 */
volatile bl_rst_casues_t bl_rst		@0x204;
/* App use 6 bytes 					@0x202 */
volatile uint8_t haddr_16[2]		@0x20C;
volatile uint8_t haddr_64[8]		@0x20E;
#pragma DATA_SEG DEFAULT

static const uint32_t app_ver_addr	APP_VERSION_ADDR = (uint32_t)app_version;
static const uint8_t NVPROT_INIT	@0x0000FFBD = NVPROT_INIT_VAL;
static const uint8_t NVOPT_INIT		@0x0000FFBF = NVOPT_INIT_VAL;

static void sys_gpio_init(void)
{
	/* Configure #RESET_RADIO line as output and set it to 1 */
	PTCD_PTCD4 = 1;
	PTCDD_PTCDD4 = 1;

	/* Enable pull-up in the pin that connects cpu-rx and radio-tx.
	 * Required in S2C radio firmwares that support use radio DOUT to detect
	 * SPI boot */
	PTCPE_PTCPE6 = 1;
}

static void sys_radio_reset(void)
{
	uint8_t i = 1;

	/* Pull #RESET_RADIO line to low for 250ns (min) and release it */
	PTCD_PTCD4 = 0;
	while (i++)
		;
	PTCD_PTCD4 = 1;
}

#pragma INLINE
/**
 *	@ingroup cpu_system
 *	@brief	Resets the watchdog timer.
 *	@param	None
 *	@retval	None
 */
void sys_watchdog_reset(void)
{
	__asm sta SRS;
}

#pragma INLINE
/**
 *	@ingroup cpu_system
 *	@brief	Disables the IRQs.
 *	@param	None
 *	@retval	None
 */
void sys_irqs_disable(void)
{
	__asm SEI;
}

#pragma INLINE
/**
 *	@ingroup cpu_system
 *	@brief	Enables the IRQs.
 *	@param	None
 *	@retval	None
 */
void sys_irqs_enable(void)
{
	__asm CLI;
}

/**
 *	@ingroup cpu_system
 *	@brief	Gets the hardware ID of the device.
 *	@param	None.
 *	@retval	uint8_t the hardware ID of the module.
 */
uint8_t sys_get_hw_id(void)
{
	return PTED & XBEE_HW_ID_MASK;
}

/**
 *	@ingroup cpu_system
 *	@brief	Performs a software delay of \b delay micro seconds.
 *	@param	delay	number of microseconds to delay the program
 *                  execution.
 *	@retval	None.
 */
void sys_udelay(uint8_t delay)
{
	/*
	 * Software delay function to perform short (multiples of mirco 
	 * second) delays.
	 * The outer loop has a constant overhead of 10 cycles + 4 cycles 
	 * per loop (per us).
	 * The inner loop has an overhead of 8 cycles per (inner) loop.
	 * To compensate the function call overhead (aprox 1 microsecond),
	 * the delay is decremented by 1.
	 */
	asm {
		ldx		delay		/* 3 cycles */
		cpx		#2			/* 2 cycles */
		blo		udelay_done	/* 3 cycles */
		decx				/* 1 cycle  */
	udelay_1:
#if defined(SYS_CFG_CLK_48_MHz)
		/* (24 - 4 - 4) / 4 rounded up */
		lda		#4			/* 2 cycles */
		ora		#0			/* 2 cycles, dummy */
#elif defined(SYS_CFG_CLK_32_MHz)
		/* (16 - 4 - 4) / 4 rounded up */
		lda		#2			/* 2 cycles */
		ora		#0			/* 2 cycles, dummy */
#elif defined(SYS_CFG_CLK_16_MHz)
		/* (8 - 4 - 4) / 4 rounded up */
		nop					/* 1 cycle */
		bra		udelay_3	/* 3 cycles */
#endif
	udelay_2:
		dbnza	udelay_2	/* 4 cycles */
	udelay_3:
		dbnzx	udelay_1	/* 4 cycles */
	udelay_done:
		nop					/* 1 cycle  */
	} /* asm */
}

/**
 *	@ingroup cpu_system
 *	@brief		Prints out the given string, disables IRQs and stops the 
 *				application execution.
 *	@param[in]	str		the message to print.
 *	@retval		None
 */
void sys_halt(char * str)
{
#if ENABLE_STDIO_PRINTF_SCANF == 1
	printf("%s\n", str);
#endif
	
	sys_irqs_disable();

	for (;;);
}

/**
 *	@ingroup cpu_system
 *	@brief	Initializes all the system clocks.
 *	@param	None
 *	@retval	None	
 */
void sys_clocks_init(void)
{
	/* Disable the clocks on all modules. Will be enabled on demand */
	SCGC1 = 0;
	SCGC2 = SCGC2_IRQ_MASK | SCGC2_DBG_MASK;
	
	/* Internal clock is 31250 Hz (factory calibrated with NVICSTRM and NVFTRIM). */
	if (NVICSTRM != 0xff) {
		/* Initialize ICSTRM register from a non volatile memory */
		ICSTRM = NVICSTRM;
		/* Initialize ICSSC register from a non volatile memory */
		ICSSC = NVFTRIM_FTRIM;
	}
	/* Select FLL as clock source, use the internal reference clock and enable
	 * it as ICSIRCLK source
	 * ICSC1: CLKS=0, RDIV=0, IREFS=1, IRCLKEN=1, IREFSTEN=0 
	 */
	ICSC1 = ICSC1_IRCLKEN_MASK | ICSC1_IREFS_MASK;

	/* ICSC2: BDIV=?, RANGE=0, HGO=0, LP=0, EREFS=0, ERCLKEN=0, EREFSTEN=0 */
	ICSC2 = SYS_CFG_BUSDIV << 6;

	/* Wait until the source of reference clock is internal clock */
	while (!ICSSC_IREFST)
		;
	ICSSC = (ICSSC & 0x1f) | (SYS_CFG_DRS_DMX << 5);

	/* Wait until the FLL switches to the corresponding DCO range */
	while ((ICSSC & 0xc0) != ((SYS_CFG_DRS_DMX << 5) & 0xc0))
		;
}

/**
 *	@ingroup cpu_system
 *	@brief		Restarts the device. 
 *	@param[in]	reason	the reason ID for the reset. See the app_rst_casuses_t 
 *						type value for more information.
 *	@retval		None
 */
void sys_reset(app_rst_casuses_t reason)
{
	/* Don't reset radio while doing firmware update so it keeps PANID and 
	 * other parameters */
	if (reason != APP_CAUSE_FIRMWARE_UPDATE)
		sys_radio_reset();

	sys_irqs_disable();

	/* Write the reason for this reset into the shared mem area */	
	app_rst = reason;

	if (reason == APP_CAUSE_REQUEST_SOPT1_NOT_WRITTEN ||
		reason < 0xfe)
		bl_rst = BL_CAUSE_NOTHING;

	/* if wd not enabled, execute a SW reset with an ILOP */
	if (!SOPT1_COPE)
		__asm DCB 0x8D;

	/* If not, wait for the watchdog timer to expire */
	for (;;);
}

#if defined(ENABLE_WD) && defined(WD_CFG_LONG_TOUT) 
#define WD_CFG					(SOPT1_COPE_MASK | SOPT1_COPT_MASK)
#elif defined(ENABLE_WD) && defined(WD_CFG_SHORT_TOUT)
#define WD_CFG					(SOPT1_COPE_MASK)
#else
#define WD_CFG					0
#endif

#ifdef ENABLE_RESET_PIN
#define RSTPE_CFG				(SOPT1_RSTPE_MASK)
#else
#define RSTPE_CFG				0
#endif /* ENABLE_RESET_PIN */

#ifdef ENABLE_BKGD_PIN
#define BKGDPE_CFG				(SOPT1_BKGDPE_MASK)
#else
#define BKGDPE_CFG				0
#endif /* ENABLE_BKGD_PIN */

#define SOPT1_CFG				(WD_CFG | RSTPE_CFG | BKGDPE_CFG | SOPT1_STOPE_MASK)

/**
 *	@ingroup cpu_system
 *	@brief	Initializes the device. Calls the different module initialization 
			functions.
 *	@param	None
 *	@retval	None
 */
void sys_init(void)
{
	/* Initialize basic system GPIOs... Needed for device reset */
	sys_gpio_init();

	SOPT1 = SOPT1_CFG;

	if ((SOPT1 & 0xe3) != SOPT1_CFG) {
		/* Reset the board after writing in the shared RAM the info
		 * for the BL so it will not initialize the SOPT1 register
		 * so we can program here our specific settings */
		sys_reset(APP_CAUSE_REQUEST_SOPT1_NOT_WRITTEN);
	}

	sys_clocks_init();
	sys_radio_reset();
}

