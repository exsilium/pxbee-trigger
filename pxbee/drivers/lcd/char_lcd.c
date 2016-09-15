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
 *	@section char_lcd Character LCD Overview
 *
 *	This API contains the functions to configure and control a character
 *	LCD based on the HD44780, KS0066U or equivalent display controller,
 *	with a programmable XBee device.
 *
 *	- Character LCD configuration functions:
 *		- char_lcd_init()
 *		- char_lcd_cmd_write()
 *		- char_lcd_on_off()
 *		- char_lcd_cursor_on_off()
 *		- char_lcd_cursor_blink_on_off()
 *		- char_lcd_clear()
 *		- char_lcd_goto_xy()
 *
 *	- Functions to read/write the LCD:
 *		- char_lcd_putchar()
 *		- char_lcd_write()
 *		- char_lcd_read_data_xy()
 */

/* Driver for character lcd displays using the HD44780, KS0066U or
 * equivalent display controller */

#include <types.h>
#include <system.h>
#include <xbee_config.h>

#if defined(ENABLE_CHAR_LCD)

#include <gpios.h>
#include <gpio_ports.h>
#include <char_lcd.h>

#define RS_CMD				0
#define RS_DATA				1
#define	TDELAY				1
#define LCD_BUSY			(1 << 7)

#define char_lcd_set_rs(a)	gpio_set(CHAR_LCD_RS_XPIN, a);	\
							sys_udelay(TDELAY)
#define char_lcd_set_rw(a)	gpio_set(CHAR_LCD_RW_XPIN, a);	\
							sys_udelay(TDELAY)
#define char_lcd_set_en(a)	gpio_set(CHAR_LCD_EN_XPIN, a);	\
							sys_udelay(TDELAY)
#define char_lcd_get_rs()	gpio_get(CHAR_LCD_RS_XPIN)

static uint8_t row = 0, col = 0;
static uint8_t char_lcd_cfg;

/* Display initialization commands */
static const uint8_t char_lcd_init_cmds[] = {
	0x33,	/* This seems to be required by the HD4478U */
	0x32,	/* The first 3 is also required by the HD4478U */
	0x2c,	/* 4 bit mode, auto increment */
	0x08, 	/* Display, cursor and blink OFF */
	0x01,	/* Display clear */
	0x06,	/* Auto increment, no shift */
};

static void char_lcd_wr_nybble(uint8_t data)
{
	port_set(CHAR_LCD_DATA_PORT, data);
	sys_udelay(TDELAY);
	char_lcd_set_en(1);
	char_lcd_set_en(0);
}

static uint8_t char_lcd_read(void)
{
	uint8_t data;

	port_config(CHAR_LCD_DATA_PORT, GPIO_CFG_INPUT);

	char_lcd_set_rw(1);
	char_lcd_set_en(1);
	data = port_get(CHAR_LCD_DATA_PORT) << 4;	/* high nibble */
	char_lcd_set_en(0);
	char_lcd_set_en(1);
	data |= port_get(CHAR_LCD_DATA_PORT) & 0x0f; /* low nibble */
	char_lcd_set_en(0);

	port_config(CHAR_LCD_DATA_PORT, GPIO_CFG_OUTPUT);

	return data;
}

static void char_lcd_wr_byte(uint8_t data)
{
	bool_t rsval;

	rsval = (bool_t)char_lcd_get_rs();
	
	char_lcd_set_rs(RS_CMD);
	while (char_lcd_read() & LCD_BUSY)
		;
	if (rsval)
		char_lcd_set_rs(rsval);

	char_lcd_set_rw(0);
	char_lcd_set_en(0);
	char_lcd_wr_nybble(data >> 4);
	char_lcd_wr_nybble(data);
	sys_udelay(43);		/* execution time for "standard" commands */
}

/**
 *	@ingroup api_char_lcd
 *	@brief		Writes a \b command in the display instruction register.
 *	@param[in]	cmd the value (command) to write.
 *	@retval		None
 */
void char_lcd_cmd_write(uint8_t cmd)
{
	/* RS is at low level, so writes are done to the instruction reg */
	char_lcd_wr_byte(cmd);
}

static void char_lcd_config(uint8_t config, uint8_t mask)
{
	char_lcd_cfg &= ~mask;
	
	if (config)
		char_lcd_cfg |= mask;
	char_lcd_cfg |= 0x08;

	char_lcd_wr_byte(char_lcd_cfg);
}

/**
 *	@ingroup api_char_lcd
 *	@brief		Turns ON/OFF the entire display. When turned off, the data
 *	            remains in the display DDRAM.
 *	@param[in]	on		if equal to 1, turns on the display.
 *	@retval		None
 */
void char_lcd_on_off(uint8_t on)
{
	char_lcd_config(on, CHAR_LCD_DISP_ON);
}

/**
 *	@ingroup api_char_lcd
 *	@brief		Turns ON/OFF the display cursor.
 *	@param[in]	on		if equal to 1, turns on the display cursor.
 *	@retval		None
 */
void char_lcd_cursor_on_off(bool_t on)
{
	char_lcd_config(on, CHAR_LCD_CURSOR_ON);
}

/**
 *	@ingroup api_char_lcd
 *	@brief		Enables the cursor blink.
 *	@param[in]	on		if equal to 1, enables the cursor blink
 *	@retval		None
 */
void char_lcd_cursor_blink_on_off(bool_t on)
{
	char_lcd_config(on, CHAR_LCD_CUR_BLINK_ON);
}

/**
 *	@ingroup api_char_lcd
 *	@brief		Clears the LCD display screen and sets the cursor
 *              position to 0,0.
 *	@param[in]	None
 *	@retval		None
 */
void char_lcd_clear(void)
{
	char_lcd_wr_byte(CHAR_LCD_CLR);
	col = 0;
	row = 0;
	delay_ticks(HZ/100);
}

/**
 *	@ingroup api_char_lcd
 *	@brief		Sets the cursor position to the specified coordinates.
 *	@param[in]	x	set the cursor to column \b x
 *	@param[in]	y	set the cursor to row \b y
 *	@retval		int		0 on success
 *	@retval		-EINVAL	on error (invalid coordinates)
 */
int char_lcd_goto_xy(uint8_t x, uint8_t y)
{
	int ret = -EINVAL;
	uint8_t offset;
	
	if ((x < CHAR_LCD_CFG_COLUMNS) && (y < CHAR_LCD_CFG_LINES)) {
		switch (y) {
		case 0:		offset = 0x80;	break;
		case 1:		offset = 0xc0;	break;
#if	CHAR_LCD_CFG_LINES > 2		
		case 2:		offset = 0x94;	break;
		case 3:		offset = 0xd4;	break;
#endif
		}
		offset |= x;
		char_lcd_wr_byte(offset);
		col = x;
		row = y;
		ret = 0;
	}
	return ret;
}

/**
 *	@ingroup api_char_lcd
 *	@brief		Initialices the LCD display.
 *	@param[in]	config	a byte containing the Initial configuration for
 *						display on/off, cursor on/off and blink on/off. See
 *						\ref macros_char_lcd for more information.
 *	@retval		int		0 on success
 *	@retval		int		error code on error
 */
int char_lcd_init(uint8_t config)
{	
	uint8_t i;

	/* set RS, RW and EN to 0 */
	gpio_set(CHAR_LCD_RS_XPIN, 0);
	gpio_set(CHAR_LCD_RW_XPIN, 0);
	gpio_set(CHAR_LCD_EN_XPIN, 0);
	gpio_config(CHAR_LCD_RS_XPIN, GPIO_CFG_OUTPUT);
	gpio_config(CHAR_LCD_RW_XPIN, GPIO_CFG_OUTPUT);
	gpio_config(CHAR_LCD_EN_XPIN, GPIO_CFG_OUTPUT);

	port_set(CHAR_LCD_DATA_PORT, 0);
	port_config(CHAR_LCD_DATA_PORT, GPIO_CFG_OUTPUT);
	
	delay_ticks(HZ/30);

	for (i = 0; i < ARRAY_SIZE(char_lcd_init_cmds); i++) {
		delay_ticks(HZ/100);
		char_lcd_wr_byte(char_lcd_init_cmds[i]);
	}

	/* Save the current config for later use and set it into the display */
	char_lcd_cfg = config & CHAR_LCD_CFG_MASK;
	char_lcd_wr_byte(0x08 | (config & CHAR_LCD_CFG_MASK));
	
	return 0;
}

/**
 *	@ingroup api_char_lcd
 *	@brief		Reads a byte from the display memory, at the specified
 *	            coordinates.
 *	@param[in]	x	column from where will be read the display character 
 *	@param[in]	y	row from where will be read teh display character
 *  @retval		int		the value read from teh display DDRAM
 *  @retval		int		error code on error
 */
int char_lcd_read_data_xy(uint8_t x, uint8_t y)
{
	uint8_t data;
	int ret;

	ret = char_lcd_goto_xy(x, y);
	if (ret)
		return ret;

	char_lcd_set_rs(RS_DATA);	
	data = char_lcd_read();
	char_lcd_set_rs(RS_CMD);	
	
	return data;
}

/**
 *	@ingroup api_char_lcd
 *	@brief		Writes \b data byte in the LCD display.
 *	@param[in]	data	byte that will be written
 *  @retval		None
 */
void char_lcd_putchar(uint8_t data)
{
	if (data == '\n') {
		col = CHAR_LCD_CFG_COLUMNS;
	} else {
		char_lcd_set_rs(RS_DATA);
		char_lcd_wr_byte(data);
		col++;
		char_lcd_set_rs(RS_CMD);
	}

	if (col >= CHAR_LCD_CFG_COLUMNS) {
		col = 0;
		row++;
		if (row >= CHAR_LCD_CFG_LINES)
			row = 0;
		char_lcd_goto_xy(col, row);
	}
}

/**
 *	@ingroup api_char_lcd
 *	@brief		Writes in the display \b len bytes from \b data 
 *	            buffer.
 *	@param[in]	data	buffer that will be written in the display
 *	@param[in]	len		number of bytes that will be written
 *	@retval		ssize_t	number of bytes written on success
 *  @retval		        error code on error
 */
ssize_t char_lcd_write(const uint8_t *data, size_t len)
{
	size_t written = 0;
	
	while (written < len) {
		char_lcd_putchar(*data++);
		written++;
	}

	return (ssize_t)written;
}

#endif /* ENABLE_CHAR_LCD */
