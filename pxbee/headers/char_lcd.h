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
/**	Platform-specific layer provides a consistent API to upper layers
 *	of the driver.
 *
 *	@ingroup api_char_lcd
 *
 *	@defgroup api_char_lcd
 *
 *	@section macros_char_lcd Character LCD Macros
 *
 *  The character LCD API needs to have defined the XBee pins that compose the
 *  data port and which XBee pins are used to control the LCD. For that
 *  purpose you have to define some macros before initialize the character
 *  LCD.
 *
 *		- Macros to configure the data port of the character LCD:
 *			- \b CHAR_LCD_DATA_XPINS	: Indicates which XBee pins are used for
 *										  the data port of the LCD.
 *
 *		- Macros to configure the control lines of the character LCD:
 *			- \b CHAR_LCD_RS_XPIN		: Indicates which XBee pin will be
 *										  configured for the RS line.
 *			- \b CHAR_LCD_RW_XPIN		: Indicates which XBee pin will be
 *										  configured for the RW line.
 *			- \b CHAR_LCD_EN_XPIN		: Indicates which XBee pin will be 
 *										  configured for the EN line.
 *
 *	Usage example:
 *	@code #define CHAR_LCD_DATA_XPINS		{XPIN_4, XPIN_7, XPIN_11, XPIN_12}
 * #define CHAR_LCD_RS_XPIN		XPIN_16
 * #define CHAR_LCD_RW_XPIN		XPIN_17
 * #define CHAR_LCD_EN_XPIN		XPIN_18
 *	@endcode
 *	@warning	It is recommended not to use these macros, they are used by
 *				the XBee Project Smart Editor of the XBee extensions.
 *
 *	There are other macros that configures the number of lines and columns
 *	(characters) of the display. This configuration macro must be also
 *	defined before initializing the LCD.
 *
 *		- Macros to configure the number of lines and columns:
 *			- \b CHAR_LCD_CFG_2x16		: Indicates that the LCD has 2 lines and
 *										  16 characters.
 *			- \b CHAR_LCD_CFG_4x20		: Indicates that the LCD has 4 lines and
 *										  20 characters.
 *
 *	Usage example:
 *	@code #define CHAR_LCD_CFG_2x16
 *	@endcode
 *	@warning	It is recommended not to use these macros, they are used by
 *				the XBee Project Smart Editor of the XBee extensions.
 *
 *  Appart from the previous macros, the char_lcd_init() method of the
 *  character LCD API needs as argument a byte containing the initial
 *  configuration masks for the display. These masks are defined with
 *  macros and they are the following:
 *
 *		- Macros to configure the \b LCD display:
 * 			- \b CHAR_LCD_DISP_ON 		: The LCD display is ON.
 *			- \b CHAR_LCD_DISP_OFF		: The LCD display is OFF.
 *
 *		- Macros to configure (show/hide) the LCD cursor:
 *			- \b CHAR_LCD_CURSOR_ON		: The LCD cursor is displayed.
 *			- \b CHAR_LCD_CURSOR_OFF	: The LCD cursor is hidden.
 *
 *		- Macros to enable or disable the the LCD cursor blinking:
 *			- \b CHAR_LCD_CUR_BLINK_ON	: The LCD cursor blinking is enabled.
 *			- \b CHAR_LCD_CUR_BLINK_OFF	: The LCD cursor blinking is disabled.
 *
 *	Usage example:
 *	@code char_lcd_init(CHAR_LCD_DISP_ON | CHAR_LCD_CURSOR_ON | CHAR_LCD_CUR_BLINK_OFF);
 *	@endcode
 *	@warning	It is recommended not to use these macros, they are used by
 *				the XBee Project Smart Editor of the XBee extensions.
 ***************************************************************************/

#ifndef __CHAR_LCD_H_
#define __CHAR_LCD_H_

/* Configuration masks for the init function */
#define CHAR_LCD_DISP_ON			(1 << 2)
#define CHAR_LCD_DISP_OFF			(0 << 2)
#define CHAR_LCD_CURSOR_ON			(1 << 1)
#define CHAR_LCD_CURSOR_OFF			(0 << 1)
#define CHAR_LCD_CUR_BLINK_ON		(1 << 0)
#define CHAR_LCD_CUR_BLINK_OFF		(0 << 0)

#define CHAR_LCD_CFG_MASK			(CHAR_LCD_DISP_ON | \
									 CHAR_LCD_CURSOR_ON | \
									 CHAR_LCD_CUR_BLINK_ON)

#define CHAR_LCD_CFG				(CHAR_LCD_CFG_DISP_ONOFF |		\
									 CHAR_LCD_CFG_CURSOR_ONOFF |	\
									 CHAR_LCD_CFG_CUR_BLINK_ONOFF)

/* LCD commands for a KS0066U (or equivalent) controller */
#define CHAR_LCD_WR_DATA			0x00		/* Write data */
#define CHAR_LCD_CLR				0x01		/* display clear */
#define CHAR_LCD_HOME				0x02		/* goto home */
#define CHAR_LCD_ENTM_SET			0x06		/* Normal entry mode set */
#define CHAR_LCD_ENTM_SHIFT			0x07		/* With shift */
#define CHAR_LCD_SET_4BIT			0x28		/* 4 Bit mode */
#define CHAR_LCD_SET_8BIT			0x38		/* 8 Bit mode */
#define CHAR_LCD_SET_LINE1			0x80		/* Line 1 position 1 */
#define CHAR_LCD_SET_LINE2			0xC0		/* Line 2 position 1 */

#if defined(CHAR_LCD_CFG_2x16)
#define CHAR_LCD_CFG_COLUMNS		16
#define CHAR_LCD_CFG_LINES			2
#elif defined (CHAR_LCD_CFG_4x20)
#define CHAR_LCD_CFG_COLUMNS		20
#define CHAR_LCD_CFG_LINES			4
#else
#error "One LCD must be selected or the number of columns/rows must be defined"
#endif

/* function prototypes */
int char_lcd_init(uint8_t config);
void char_lcd_clear(void);
void char_lcd_on_off(bool_t on);
void char_lcd_cursor_on_off(bool_t on);
void char_lcd_cursor_blink_on_off(bool_t on);
void char_lcd_cmd_write(uint8_t cmd);
int char_lcd_goto_xy(uint8_t x, uint8_t y);
int char_lcd_read_data_xy(uint8_t x, uint8_t y);
void char_lcd_putchar(uint8_t data);
ssize_t char_lcd_write(const uint8_t *data, size_t len);

#endif /* __CHAR_LCD_H_ */
