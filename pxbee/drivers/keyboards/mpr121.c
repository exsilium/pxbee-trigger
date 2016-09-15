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
 */ 
/** 	
 *	@ingroup mpr121_keyboard
 *
 *	@defgroup mpr121_keyboard
 *	A 12 keys keyboard can be controlled with I2C protocol
 *	@section mpr121 XBee keyboard MPR121 (I2C)
 *	This API contains some functions for control a capacitive display with I2C protocol with a 
 *	XBee programmable module. This display is based on MPR121 driver.
 *	
 *	- For control the Keyboard:
 *		- mpr121_default_config()
 *		- mpr121_read()
 *		- mpr121_write()
 ***************************************************************************/

#include <mpr121.h>


#ifdef ENABLE_MPR121
#define MPR121_ADDRESS		0x5A

/**
 * @ingroup  mpr121_keyboard
 * @{
 * @brief    Init mpr121
 * @return   nothing
 */
void mpr121_default_config(void)
{
	i2c_set_addr(MPR121_ADDRESS);
	
	/* Section A
	 * This group controls filtering when data is > baseline
	 */ 
	(void)mpr121_write(MHD_R, 0x01);
	(void)mpr121_write(NHD_R, 0x01);
	(void)mpr121_write(NCL_R, 0x00);
	(void)mpr121_write(FDL_R, 0x00);

	/* Section B
	 * This group controls filtering when data is < baseline.
	 */
	(void)mpr121_write(MHD_F, 0x01);
	(void)mpr121_write(NHD_F, 0x01);
	(void)mpr121_write(NCL_F, 0xFF);
	(void)mpr121_write(FDL_F, 0x02);
	/* Section C
	 * This group sets touch and release thresholds for each electrode
	 */
	(void)mpr121_write(ELE0_T, TOU_THRESH);
	(void)mpr121_write(ELE0_R, REL_THRESH);
	(void)mpr121_write(ELE1_T, TOU_THRESH);
	(void)mpr121_write(ELE1_R, REL_THRESH);
	(void)mpr121_write(ELE2_T, TOU_THRESH);
	(void)mpr121_write(ELE2_R, REL_THRESH);
	(void)mpr121_write(ELE3_T, TOU_THRESH);
	(void)mpr121_write(ELE3_R, REL_THRESH);
	(void)mpr121_write(ELE4_T, TOU_THRESH);
	(void)mpr121_write(ELE4_R, REL_THRESH);
	(void)mpr121_write(ELE5_T, TOU_THRESH);
	(void)mpr121_write(ELE5_R, REL_THRESH);
	(void)mpr121_write(ELE6_T, TOU_THRESH);
	(void)mpr121_write(ELE6_R, REL_THRESH);
	(void)mpr121_write(ELE7_T, TOU_THRESH);
	(void)mpr121_write(ELE7_R, REL_THRESH);
	(void)mpr121_write(ELE8_T, TOU_THRESH);
	(void)mpr121_write(ELE8_R, REL_THRESH);
	(void)mpr121_write(ELE9_T, TOU_THRESH);
	(void)mpr121_write(ELE9_R, REL_THRESH);
	(void)mpr121_write(ELE10_T, TOU_THRESH);
	(void)mpr121_write(ELE10_R, REL_THRESH);
	(void)mpr121_write(ELE11_T, TOU_THRESH);
	(void)mpr121_write(ELE11_R, REL_THRESH);
	/* 	Section D
	 *	Set the Filter Configuration
	 *	Set ESI2
	 */	
	(void)mpr121_write(FIL_CFG, 0x04);
	/* 	Section E
	 *	Electrode Configuration
	 *	Enable 6 Electrodes and set to run mode
	 *	Set ELE_CFG to 0x00 to return to standby mode
	 *
	 * 	Enables all 12 Electrodes */
	(void)mpr121_write(ELE_CFG, 0x0C);
	/* 	Enable first 6 electrodes
	 *	mpr121_write(ELE_CFG, 0x06);		
	 *	Section F
	 *	Enable Auto Config and auto Reconfig
	 *	mpr121_write(ATO_CFG0, 0x0B);
	 *	mpr121_write(ATO_CFGU, 0xC9);	 USL = (Vdd-0.7)/vdd*256 = 0xC9 @3.3V   mpr121_write(ATO_CFGL, 0x82);	 LSL = 0.65*USL = 0x82 @3.3V
	 *	mpr121_write(ATO_CFGT, 0xB5);	 Target = 0.9*USL = 0xB5 @3.3V 
	 */
}

/**
 * @brief    Write a byte in the selected address
 * @param    regaddr - address to write
 * @param    data - data to write on selected address
 * @return   nothing
 */
ssize_t mpr121_write(uint8_t regaddr, uint8_t data)
{
	uint8_t buf[2];
	buf[0] = regaddr;
	buf[1] = data;

	return i2c_write(buf, 2);
}

/**
 * @brief    Reads a byte from selected address
 * @param    regaddr - direction for read a byte
 * @return   Returns the error code on error or the value read from the 
 *           selected register
 */
ssize_t mpr121_read(uint8_t regaddr)
{
	uint8_t regval;
	ssize_t ret;

	ret = i2c_write_no_stop(&regaddr, 1);
	if (ret < 0)
		return ret;
	
	ret = i2c_read(&regval, 1);
	if (ret < 0)
		return ret;

	return (size_t)regval;
}
#endif

