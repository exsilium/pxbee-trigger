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
 *	@ingroup api_display_graphic
 *
 *	@defgroup api_display_graphic
 *
 *	@section macros_display_graphic Graphic Display Macros
 *
 *  The character LCD API needs to have defined which XBee pin is used for
 *  the data select functionality. For that purpose you have to define
 *  a macro before initialize the graphic display.
 *
 *		- Macros to configure the data select pin:
 *			- \b DATA_SELECT0			: Indicates which XBee pin is used
 *										  for the data select line of the
 *										  display. Depending on the number of
 *										  displays you are going to use, you
 *										  will declare the macro with a 0 at
 *										  the end or with a 1.
 *
 *	Usage example:
 *	@code #define DATA_SELECT0		XPIN_7
 *	@endcode
 *	@warning	It is recommended not to use these macros, they are used by
 *				the XBee Project Smart Editor of the XBee extensions.
 *
 *	Apart from the previous macro, there are other macros that configures
 *	different settings of the display.
 *
 *		- Macro to configure the display contrast:
 *			- \b LCD_DISPLAY_CONTRAST	: Hexadecimal value for the contrast.
 *
 *	Usage example:
 *	@code #define LCD_DISPLAY_CONTRAST		0x1f
 *	@endcode
 *	@warning	It is recommended not to use these macros, they are used by
 *				the XBee Project Smart Editor of the XBee extensions.
 *
 *		- Macro to enable/disable the text library:
 *			- \b ENABLE_TEXT_LIBRARY0	: 1 to enable, 0 to disable it.
 *										  Depending on the number of displays
 *										  you are going to use, you will
 *										  declare the macro with a 0 at the
 *										  end or with a 1.
 *
 *	Usage example:
 *	@code #define ENABLE_TEXT_LIBRARY0		1
 *	@endcode
 *	@warning	It is recommended not to use these macros, they are used by
 *				the XBee Project Smart Editor of the XBee extensions.
 *
 *	Remember that the display uses the SPI port for the data transfer and a
 *	GPIO for the data select line, so you will need to initialize those
 *	components before initializing the display itself. The their
 *	documentation for more information about the macros and how to initialize
 *	them.
 ***************************************************************************/

#ifndef __GRAPHIC_DISPLAY_H_
#define __GRAPHIC_DISPLAY_H_
#include <xbee_config.h>
#include <types.h>


#define NUM_PIXELS_X		128	
#define NUM_PIXELS_Y		64
#define NUM_PAGES			8
#define VERT_PXS_PER_PAGE	(NUM_PIXELS_Y / NUM_PAGES)
#define NUM_ROWS			(NUM_PIXELS_Y / VERT_PXS_PER_PAGE)

	/*Display commands*/
#define	CMD_ON_OFF			0xae
#define	CMD_RES_RATIO		0x20
#define CMD_POWER_CTRL		0x28
#define	CMD_ELECT_VOL		0x81
#define	CMD_SCAN_DIR		0xc0
#define	CMD_ADC_SELECT		0xa0
#define	CMD_LINE_START		0x40
#define	CMD_PAGE_ADDR_SET	0xb0
#define	CMD_STATIC_IND		0xac
#define	CMD_SET_ALL			0xa4
#define	CMD_COL_ADDR_SET	0x10
#define	STATIC_IND_ON		0x03
#define ON					1
#define OFF					(!ON)

/* LCD Power controller masks */
#define	LCD_PW_BOOSTER		0x04
#define	LCD_PW_VREG			0x02
#define	LCD_PW_VFOLLOW		0x01

#define cmd_data_select(a)			gpio_set(DATA_SELECT0,a)
#define lcd_page_addr_set(a)		lcd_graphic_cmd_write(CMD_PAGE_ADDR_SET | ((a) & 0x0f))
#define lcd_col_addr_set(a)			lcd_graphic_cmd_write(CMD_COL_ADDR_SET | ((a) >> 4));	\
									lcd_graphic_cmd_write((a) & 0x0f)
#define lcd_set_elect_vol(a)		lcd_graphic_cmd_write(CMD_ELECT_VOL); \
									lcd_graphic_cmd_write((a) & 0x3f)
#define lcd_scan_dir(a)				lcd_graphic_cmd_write(CMD_SCAN_DIR | ((a) ? 0x08 : 0))
#define lcd_adc_select(a)			lcd_graphic_cmd_write(CMD_ADC_SELECT | ((a) & 0x01))
#define lcd_set_line_start(a)		lcd_graphic_cmd_write(CMD_LINE_START | ((a) & 0x3f))
#define	lcd_on_off(a)				lcd_graphic_cmd_write(CMD_ON_OFF | ((a) & 0x01))
#define lcd_static_ind(a)			lcd_graphic_cmd_write(CMD_STATIC_IND | ((a) & 0x01)) 
#define lcd_exit_sleep()			lcd_on_off(1); \
									lcd_set_all(0); \
									lcd_static_ind(1); \
									lcd_graphic_cmd_write(STATIC_IND_ON)
#define lcd_set_all(a)				lcd_graphic_cmd_write(CMD_SET_ALL | ((a) & 0x01)) 
#define lcd_set_reverse(a)			lcd_graphic_cmd_write(0xA6 | a)
#define lcd_internal_reset()		lcd_graphic_cmd_write(0xE2)
#define check_bit(a, b)				a & (1 << b)


void lcd_graphic_goto_xy(uint8_t x, uint8_t y);
void lcd_graphic_data_write(uint8_t data);
void lcd_graphic_cmd_write(uint8_t cmd);
void lcd_graphic_write_text(uint8_t x0,uint8_t y0, uint8_t* textplot,
							bool_t color);
void lcd_graphic_write_tile(uint8_t x, uint8_t y,uint8_t *buf);
void lcd_graphic_write_pixel(uint8_t x,uint8_t y,bool_t color);
void lcd_graphic_write_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1,
							bool_t color);
void lcd_graphic_write_rectangle(uint8_t x0 , uint8_t y0 , uint8_t x1 , 
								 uint8_t y1, bool_t color );
void lcd_graphic_write_circle(uint8_t x0, uint8_t y0, uint8_t r, bool_t color);
void lcd_graphic_write_box(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1,
						   bool_t color);
void lcd_graphic_init(void);
void lcd_graphic_set_clear_screen(uint8_t);

#endif /* __GRAPHIC_DISPLAY_H_ */
