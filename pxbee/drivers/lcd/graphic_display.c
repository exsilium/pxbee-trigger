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
 */ 	
/**	Platform-specific layer provides a consistent API to upper layers
 *	of the driver.
 *	
 * 	@ingroup api_display_graphic
 *
 *	@defgroup api_display_graphic
 *	
 *	@section display_lcd Graphic display (SPI) Overview
 *	
 *	This API contains some functions to configure and control a graphic
 *	display based on the ST7565R controller, with a programmable XBee
 *	programmable device.
 *	
 *	- Graphic Display configuration functions:
 *		- lcd_graphic_init()
  *		- lcd_graphic_goto_xy()
 *
 *	- Functions to write the display:
 *		- lcd_graphic_cmd_write()
 *		- lcd_graphic_write_tile()
 *		- lcd_graphic_write_pixel()
 *		- lcd_graphic_write_line()	
 *		- lcd_graphic_write_rectangle()
 *		- lcd_graphic_write_circle()
 *		- lcd_graphic_write_box()
 *		- lcd_graphic_write_text()	
 ***************************************************************************/

#include <graphic_display.h>
#include <spi.h>
#include <stdlib.h>
#include <string.h>

#if defined(ENABLE_GRAPHIC_DISPLAY_0) || defined(ENABLE_GRAPHIC_DISPLAY_1)
/// \cond 

#ifdef ENABLE_GRAPHIC_DISPLAY_0
uint8_t display0_contrast = LCD_DISPLAY_CONTRAST;
uint8_t row0 = 0, col0 = 0;
#if CONFIG_XBEE_FLASH_LEN > 32
uint8_t state0[128][8];
#endif /* CONFIG_XBEE_FLASH_LEN > 32 */

#endif
#ifdef ENABLE_GRAPHIC_DISPLAY_1

uint8_t display1_contrast = LCD_DISPLAY_CONTRAST1;
uint8_t row1 = 0, col1 = 0;
uint8_t state1[128][8];
#endif

#if defined(ENABLE_TEXT_LIBRARY0) || defined(ENABLE_TEXT_LIBRARY1)
const uint8_t TEXT35[95][5]={
   0b00000000,   0b00000000,   0b00000000,   0b00000000,   0b00000000, //SPACE
   0b01000100,   0b01000100,   0b01000100,   0b00000000,   0b01000100, //!
   0b10101010,   0b10101010,   0b00000000,   0b00000000,   0b00000000, //"
   0b10101010,   0b11101110,   0b10101010,   0b11101110,   0b10101010, //#
   0b01100110,   0b11001100,   0b11001100,   0b01100110,   0b11101110, //$
   0b10101010,   0b00100010,   0b01000100,   0b10001000,   0b10101010, //%
   0b01000100,   0b10101010,   0b01000100,   0b10101010,   0b01100110, //&
   0b01000100,   0b01000100,   0b00000000,   0b00000000,   0b00000000, //'
   0b01000100,   0b10001000,   0b10001000,   0b10001000,   0b01000100, //(
   0b01000100,   0b00100010,   0b00100010,   0b00100010,   0b01000100, //)
   0b00000000,   0b10101010,   0b01000100,   0b10101010,   0b00000000, //*
   0b00000000,   0b01000100,   0b11101110,   0b01000100,   0b00000000, //+
   0b00000000,   0b00000000,   0b00000000,   0b01000100,   0b10001000, //,
   0b00000000,   0b00000000,   0b11101110,   0b00000000,   0b00000000, //-
   0b00000000,   0b00000000,   0b00000000,   0b00000000,   0b01000100, //.
   0b00100010,   0b00100010,   0b01000100,   0b10001000,   0b10001000, ///
   0b11101110,   0b10101010,   0b10101010,   0b10101010,   0b11101110, //0
   0b01000100,   0b11001100,   0b01000100,   0b01000100,   0b11101110, //1
   0b11101110,   0b00100010,   0b11101110,   0b10001000,   0b11101110, //2
   0b11101110,   0b00100010,   0b11101110,   0b00100010,   0b11101110, //3
   0b10101010,   0b10101010,   0b11101110,   0b00100010,   0b00100010, //4
   0b11101110,   0b10001000,   0b11101110,   0b00100010,   0b11101110, //5
   0b11001100,   0b10001000,   0b11101110,   0b10101010,   0b11101110, //6
   0b11101110,   0b00100010,   0b01000100,   0b10001000,   0b10001000, //7
   0b11101110,   0b10101010,   0b11101110,   0b10101010,   0b11101110, //8
   0b11101110,   0b10101010,   0b11101110,   0b00100010,   0b01100110, //9
   0b00000000,   0b01000100,   0b00000000,   0b01000100,   0b00000000, //:
   0b00000000,   0b01000100,   0b00000000,   0b01000100,   0b10001000, //;
   0b00100010,   0b01000100,   0b10001000,   0b01000100,   0b00100010, //<
   0b00000000,   0b11101110,   0b00000000,   0b11101110,   0b00000000, //=
   0b10001000,   0b01000100,   0b00100010,   0b01000100,   0b10001000, //>
   0b11001100,   0b00100010,   0b01100110,   0b00000000,   0b01000100, //?
   0b01000100,   0b10101010,   0b11101110,   0b10001000,   0b01100110, //@
   0b11101110,   0b10101010,   0b11101110,   0b10101010,   0b10101010, //A
   0b11001100,   0b10101010,   0b11101110,   0b10101010,   0b11001100, //B
   0b11101110,   0b10001000,   0b10001000,   0b10001000,   0b11101110, //C
   0b11001100,   0b10101010,   0b10101010,   0b10101010,   0b11001100, //D
   0b11101110,   0b10001000,   0b11101110,   0b10001000,   0b11101110, //E
   0b11101110,   0b10001000,   0b11101110,   0b10001000,   0b10001000, //F
   0b11101110,   0b10001000,   0b10001000,   0b10101010,   0b11101110, //G
   0b10101010,   0b10101010,   0b11101110,   0b10101010,   0b10101010, //H
   0b11101110,   0b01000100,   0b01000100,   0b01000100,   0b11101110, //I
   0b00100010,   0b00100010,   0b00100010,   0b10101010,   0b11101110, //J
   0b10001000,   0b10101010,   0b11001100,   0b11001100,   0b10101010, //K
   0b10001000,   0b10001000,   0b10001000,   0b10001000,   0b11101110, //L
   0b10101010,   0b11101110,   0b11101110,   0b10101010,   0b10101010, //M
   0b00000000,   0b11001100,   0b10101010,   0b10101010,   0b10101010, //N
   0b01000100,   0b10101010,   0b10101010,   0b10101010,   0b01000100, //O
   0b11101110,   0b10101010,   0b11101110,   0b10001000,   0b10001000, //P
   0b01000100,   0b10101010,   0b10101010,   0b11101110,   0b01100110, //Q
   0b11101110,   0b10101010,   0b11001100,   0b11101110,   0b10101010, //R
   0b11101110,   0b10001000,   0b11101110,   0b00100010,   0b11101110, //S
   0b11101110,   0b01000100,   0b01000100,   0b01000100,   0b01000100, //T
   0b10101010,   0b10101010,   0b10101010,   0b10101010,   0b11101110, //U
   0b10101010,   0b10101010,   0b10101010,   0b10101010,   0b01000100, //V
   0b10101010,   0b10101010,   0b11101110,   0b11101110,   0b10101010, //W
   0b00000000,   0b10101010,   0b01000100,   0b01000100,   0b10101010, //X
   0b10101010,   0b10101010,   0b01000100,   0b01000100,   0b01000100, //Y
   0b11101110,   0b00100010,   0b01000100,   0b10001000,   0b11101110, //Z
   0b11101110,   0b10001000,   0b10001000,   0b10001000,   0b11101110, //[
   0b10001000,   0b10001000,   0b01000100,   0b00100010,   0b00100010, /* * */
   0b11101110,   0b00100010,   0b00100010,   0b00100010,   0b11101110, //]
   0b01000100,   0b10101010,   0b00000000,   0b00000000,   0b00000000, //^
   0b00000000,   0b00000000,   0b00000000,   0b00000000,   0b11101110, //_
   0b10001000,   0b01000100,   0b00000000,   0b00000000,   0b00000000, //`
   0b00000000,   0b01000100,   0b10101010,   0b10101010,   0b01100110, //a
   0b10001000,   0b11001100,   0b10101010,   0b10101010,   0b11001100, //b
   0b00000000,   0b01100110,   0b10001000,   0b10001000,   0b01100110, //c
   0b00100010,   0b01100110,   0b10101010,   0b10101010,   0b01100110, //d
   0b00000000,   0b01000100,   0b10101010,   0b11001100,   0b01100110, //e
   0b01100110,   0b01000100,   0b11101110,   0b01000100,   0b01000100, //f
   0b00000000,   0b01000100,   0b10101010,   0b01100110,   0b11001100, //g
   0b10001000,   0b11001100,   0b10101010,   0b10101010,   0b10101010, //h
   0b01000100,   0b00000000,   0b01000100,   0b01000100,   0b01000100, //i
   0b01000100,   0b00000000,   0b01000100,   0b01000100,   0b10001000, //j
   0b10001000,   0b10001000,   0b10101010,   0b11001100,   0b10101010, //k
   0b01000100,   0b01000100,   0b01000100,   0b01000100,   0b01000100, //l
   0b00000000,   0b11101110,   0b11101110,   0b10101010,   0b10101010, //m
   0b00000000,   0b11001100,   0b10101010,   0b10101010,   0b10101010, //n
   0b00000000,   0b01000100,   0b10101010,   0b10101010,   0b01000100, //o
   0b00000000,   0b11001100,   0b10101010,   0b11001100,   0b10001000, //p
   0b00000000,   0b01100110,   0b10101010,   0b01100110,   0b00100010, //q
   0b00000000,   0b10001000,   0b11101110,   0b10001000,   0b10001000, //r
   0b00000000,   0b01100110,   0b11001100,   0b00100010,   0b11001100, //s
   0b01000100,   0b11101110,   0b01000100,   0b01000100,   0b01000100, //t
   0b00000000,   0b10101010,   0b10101010,   0b10101010,   0b01000100, //u
   0b00000000,   0b10101010,   0b10101010,   0b01000100,   0b01000100, //v
   0b00000000,   0b10101010,   0b10101010,   0b11101110,   0b10101010, //w
   0b00000000,   0b10101010,   0b01000100,   0b01000100,   0b10101010, //x
   0b00000000,   0b10101010,   0b10101010,   0b01100110,   0b11001100, //y
   0b00000000,   0b11101110,   0b01100110,   0b11001100,   0b11101110, //z
   0b00100010,   0b01000100,   0b11001100,   0b01000100,   0b00100010, //{
   0b01000100,   0b01000100,   0b01000100,   0b01000100,   0b01000100, //|
   0b10001000,   0b01000100,   0b01100110,   0b01000100,   0b10001000, //}
   0b00000000,   0b11001100,   0b10101010,   0b00000000,   0b00000000  //~
   };
#endif
/// \endcond 

/**
 *	@ingroup api_display_graphic
 *	@brief	Initializes graphic display with default params.
 *	@retval		None.
 *	@note		Some functions of graphic display cannot be used until the
 *				the LCD is initialized.
 */
void lcd_graphic_init(void)
{
	lcd_exit_sleep();	/* just in case we are a lazy devdice... */
	lcd_graphic_cmd_write(CMD_RES_RATIO | 0x04);
	lcd_graphic_cmd_write(CMD_POWER_CTRL | LCD_PW_BOOSTER | LCD_PW_VREG | LCD_PW_VFOLLOW);
	
#ifdef ENABLE_GRAPHIC_DISPLAY_0
	lcd_set_elect_vol(display0_contrast);
#endif
	
#ifdef ENABLE_GRAPHIC_DISPLAY_1
	lcd_set_elect_vol(display1_contrast);
#endif
	lcd_scan_dir(1);
	lcd_adc_select(0);
	lcd_set_line_start(0);
	lcd_graphic_goto_xy(0, 0);
	lcd_graphic_set_clear_screen(0);
	lcd_on_off(ON);
	lcd_set_all(0);
}

/**
 *	@ingroup api_display_graphic
 *	@brief		Fills all the display with the specified byte mask.
 *	@param[in]	data  	The data to be written into the display.
 *	@retval		Nothing 
 *	@warning	This function can not be used until the LCD is initialized
 */
void lcd_graphic_set_clear_screen(uint8_t data)
{
	uint8_t i, j;
	lcd_graphic_goto_xy(0, 0);
	for (j = 0; j < NUM_ROWS; j++) {
		for (i = 0; i < NUM_PIXELS_X; i++) 
			lcd_graphic_data_write(data);
		}	
}

/**
 *	@ingroup api_display_graphic
 *	@brief		Sets the pointer of the LCD at the specified coordinates.
 *	@param[in]	x  		x coordinate of the pointer.
 *	@param[in]	y  		y coordinate of the pointer.
 *	@retval		None
 *	@warning	This function can not be used until the LCD is initialized.
 */
void lcd_graphic_goto_xy(uint8_t x, uint8_t y)
{
	if ((x < NUM_PIXELS_X) && (y < NUM_ROWS)) {
 		lcd_page_addr_set(y);
 		lcd_col_addr_set(x);
 	}
	col0 = x;
	row0 = y & 0x07;
}

/**
 *	@ingroup api_display_graphic
 *	@brief		Sends a byte of data to be written in the LCD.
 *	@param[in]	data	The data (byte) to draw in the display.
 *	@retval		Nothing 
 *	@warning	This function can not be used until the LCD is initialized.
 */
void lcd_graphic_data_write(uint8_t data)
{
	spi_transfer(DISPLAY_SPI_SS, &data, NULL,1); /* Dummy buffer to wait the reception */
#ifdef ENABLE_GRAPHIC_DISPLAY_0
	if  (++col0 >= NUM_PIXELS_X){
		col0 = 0;
		row0 = (++row0) & 0x07;
		lcd_page_addr_set(row0);
		lcd_col_addr_set(col0);
	}
#endif
#ifdef ENABLE_GRAPHIC_DISPLAY_1
	if  (++col1 >= NUM_PIXELS_X){
		col1 = 0;
		row1 = (++row1) & 0x07;
		lcd_page_addr_set(row1);
		lcd_col_addr_set(col1);
	}
#endif
	
}

/**
 *	@ingroup api_display_graphic
 *	@brief		Sends the given command to the LCD.
 *	@param[in]	cmd		the command to send to the LCD.
 *	@retval		None
 */
void lcd_graphic_cmd_write(uint8_t cmd)
{
	cmd_data_select(0);
    spi_transfer(DISPLAY_SPI_SS, &cmd, &cmd, 1); /* Dummy buffer to wait the reception */
    cmd_data_select(1);
}

/**
 *	@ingroup api_display_graphic
 *	@brief		Writes a tile (square of 8x8 pixels/bits) at the given point.
 *	@param[in]	x		x position of the tile. 0 <= x < 16.
 *	@param[in]	y		y position of the tile. 0 <= y < 8.
 *	@param[in]	buf		buffer with the data of the tile (8 bytes).
 *	@retval		None
 *	@warning	This function can not be used until the LCD is initialized.
 */
void lcd_graphic_write_tile(uint8_t x, uint8_t y, uint8_t *buf)
{
	uint8_t i;
	
	if ((x < 16) & (y < 8)) {
		lcd_graphic_goto_xy(8 * x, y);
		for (i = 0; i < 8 ;i++) {
			lcd_graphic_data_write(*((uint8_t *)buf)++);
		}
	}
}
#if CONFIG_XBEE_FLASH_LEN > 32
/**
 *	@ingroup api_display_graphic
 *	@brief		Draws a pixel in the LCD given position (point).
 *	@param[in]	x		x value of the pixel. 0 <= x < 128.
 *	@param[in]	y		y value of the pixel. 0 <= y < 64.
 *	@param[in]	color	1 for black / 0 for white.
 *	@retval		None
 *	@warning	This function can not be used until the LCD is initialized.
 */
void lcd_graphic_write_pixel(uint8_t x, uint8_t y, bool_t color)
{
	if ((x < 128)&(y < 64)){
		lcd_graphic_goto_xy(x, y / 8);
#ifdef ENABLE_GRAPHIC_DISPLAY_0
		if (color){
			state0[x][y/8] |= (1 << y % 8);
		}
		else{
			state0[x][y/8] &= ~(1 << y % 8);
		}
		lcd_graphic_data_write(state0[x][y/8]);
#endif
#ifdef ENABLE_GRAPHIC_DISPLAY_1
		if (color){
			state1[x][y/8] |= (1 << y % 8);
		}
		else{
			state1[x][y/8] &= ~(1 << y % 8);
		}
		lcd_graphic_data_write(state1[x][y/8]);
#endif
	}
}
#else
void lcd_graphic_write_pixel(uint8_t x, uint8_t y, bool_t color) {}
#endif /* CONFIG_XBEE_FLASH_LEN > 32 */
/**
 *	@ingroup api_display_graphic
 *	@brief		Draws a line in the LCD defined by two points.
 *	@param[in]	x0		x value of the starting point. 0 <= x < 128.
 *	@param[in]	y0		y value of the starting point. 0 <= y < 64.
 *	@param[in]	x1		x value of the end point. 0 <= x < 128.
 *	@param[in]	y1		y value of the end point. 0 <= y < 64.
 *	@param[in]	color	1 for black / 0 for white.
 *	@retval		None
 *	@warning	This function can not be used until the LCD is initialized.
 */
void lcd_graphic_write_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool_t color)
{
	int16_t inc_x, inc_y, far_x, far_y, i, P;
	uint8_t x, y;
	
	far_x = abs((x1 - x0));
	far_y = abs((y1 - y0));
	x = x0;
	y = y0;
	if(x0 > x1) 
		inc_x = -1; 
	else 
		inc_x = 1;
	if(y0 > y1) 
		inc_y = -1; 
	else 
		inc_y = 1;
	if(far_x >= far_y){ 
		P = 2 * far_y - far_x;
		for(i = 0; i <= far_x; ++i){
			lcd_graphic_write_pixel(x, y, color);
			if(P < 0){ 
				P += 2 * far_y;
				x += inc_x; 
			}
			else{ 
				P += 2*far_y - 2*far_x;
				x += inc_x;
				y += inc_y;
			}
	      }
	}
	else{ 
		P = 2 * far_x - far_y;
		for(i = 0; i <= far_y; ++i){ 
			lcd_graphic_write_pixel(x, y, color);
			if(P < 0){  
				P += 2 * far_x;
				y += inc_y; 
			}
			else{  
				P += 2 * far_x - 2 * far_y;
				x += inc_x;
				y += inc_y; 
			}
		}
	}
}

/**
 *	@ingroup api_display_graphic
 *	@brief		Draws a rectangle in the LCD defined by two points.
 *	@param[in]	x0		x value of the starting point. 0 <= x < 128.
 *	@param[in]	y0		y value of the starting point. 0 <= y < 64.
 *	@param[in]	x1		x value of the end point. 0 <= x < 128.
 *	@param[in]	y1		y value of the end point. 0 <= y < 64.
 *	@param[in]	color	1 for black / 0 for white.
 *	@retval		None
 *	@warning	This function can not be used until the LCD is initialized.
 */
void lcd_graphic_write_rectangle(uint8_t x0 , uint8_t y0 , uint8_t x1 , uint8_t y1, bool_t color )
{
	lcd_graphic_write_line(x0, y0, x1, y0, color);
	lcd_graphic_write_line(x0, y0, x0, y1, color);
	lcd_graphic_write_line(x0, y1, x1, y1, color);
	lcd_graphic_write_line(x1, y0, x1, y1, color);
}

/**
 *	@ingroup api_display_graphic
 *	@brief		Draws a circle in the LCD defined by its center point and
 *				the radius.
 *	@param[in]	x0		x value of the center point. 0 <= x < 128.
 *	@param[in]	y0		y value of the center point. 0 <= y < 64.
 *	@param[in]	r		radius value (in pixels) of the circle.
 *	@param[in]	color	1 for black / 0 for white.
 *	@retval		None
 *	@warning	This function can not be used until the LCD is initialized.
 */
void lcd_graphic_write_circle(uint8_t x0, uint8_t y0, uint8_t r, bool_t color)
{
	int8_t d = 1 - r ,x = 0,y = r ;
	
	lcd_graphic_write_pixel(x0, y0 + r, color);
	lcd_graphic_write_pixel(x0, y0 - r, color);
	lcd_graphic_write_pixel(x0 + r, y0, color);
	lcd_graphic_write_pixel(x0 - r, y0, color);
	while (x < y){
		if(d < 0) 
			d += 2 * x + 3;
		else{
			d += 2 * (x - y) + 5;
		    y--;
		}
		x++;
		lcd_graphic_write_pixel(x0 + x , y0 + y, color);
		lcd_graphic_write_pixel(x0 - x , y0 + y, color);
		lcd_graphic_write_pixel(x0 + x , y0 - y, color);
		lcd_graphic_write_pixel(x0 - x , y0 - y, color);
		lcd_graphic_write_pixel(x0 + y , y0 + x, color);
		lcd_graphic_write_pixel(x0 - y , y0 + x, color);
		lcd_graphic_write_pixel(x0 + y , y0 - x, color);
		lcd_graphic_write_pixel(x0 - y , y0 - x, color);
	}
}

/**
 *	@ingroup api_display_graphic
 *	@brief		Draws a filled rectangle in the LCD defined by two points.
 *	@param[in]	x0		x value of the starting point. 0 <= x < 128.
 *	@param[in]	y0		y value of the starting point. 0 <= y < 64.
 *	@param[in]	x1		x value of the end point. 0 <= x < 128.
 *	@param[in]	y1		y value of the end point. 0 <= y < 64.
 *	@param[in]	color	1 for black / 0 for white 
 *	@retval		None
 *	@warning	This function can not be used until the LCD is initialized.
 */
void lcd_graphic_write_box(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool_t color)
{
	uint8_t i;
	for (i = y0; i < y1; i++)
		lcd_graphic_write_line(x0, i, x1, i, color);
}

/**
 *	@ingroup api_display_graphic
 *	@brief		Writes the given text in the graphic display.
 *	@param[in]	x0			x value of the point where the text will start
 *							to be written. 0 <= x < 128.
 *	@param[in]	y0			y value of the point where the text will start
 *							to be written. 0 <= y < 64.
 *	@param[in]	textplot	buffer containing the text to write.
 *	@param[in]	color		1 for black / 0 for white.
 *	@retval		None
 *	@warning	This function cannot be used until the LCD is initialized.
 */	
#if defined(ENABLE_TEXT_LIBRARY0) || defined(ENABLE_TEXT_LIBRARY1)
#if CONFIG_XBEE_FLASH_LEN > 32
void lcd_graphic_write_text(uint8_t x0, uint8_t y0, uint8_t* textplot, bool_t color)
{
	uint8_t i,j,k;
	uint8_t pixeldata[5];
	
	for(i = 0; textplot[i] != '\0'; ++i, ++x0) {
		if((textplot[i] >= ' ') && (textplot[i] <= '~'))
			memcpy(pixeldata, TEXT35[textplot[i]-' '], 5);
		else
		    memcpy(pixeldata, TEXT35[0], 5); // Default to space
		
		 if(x0 + 3 >= NUM_PIXELS_X) {         // Performs character wrapping
		      x0 = 0;                         // Set x at far left position
		      y0 += 5 + 1;                    // Set y at next position down
		 }
		 for(j = 3; j > 0; j--, x0++) {       // Loop through character byte data
		    for(k=0; k<5; k++) {              // Loop through the vertical pixels
		    	if(check_bit(pixeldata[k],j))
		    		lcd_graphic_write_pixel(x0, y0+k, color); // Draws the pixel
		    	else
		    		lcd_graphic_write_pixel(x0, y0+k, !color);
		    }
		 }
	}
}
#else /* Basic text for 32kb */
void lcd_graphic_write_text(uint8_t x0, uint8_t y0, uint8_t* textplot, bool_t color)
{
	uint8_t i,j;
	uint8_t pixeldata[8] = {0};
	
	lcd_graphic_goto_xy(x0, y0);
	for(i = 0; textplot[i] != '\0'; ++i) {
		if((textplot[i] >= ' ') && (textplot[i] <= '~'))
			memcpy(pixeldata, TEXT35[textplot[i]-' '], 5);
		else
		    memcpy(pixeldata, TEXT35[0], 5); // Default to space
		
		for(j = 0; j < ARRAY_SIZE(pixeldata); j++)
			lcd_graphic_data_write(pixeldata[j]);
		
	}	
	
}
#endif /* CONFIG_XBEE_FLASH_LEN > 32 */
#endif /* defined(ENABLE_TEXT_LIBRARY0) || defined(ENABLE_TEXT_LIBRARY1) */
#endif
