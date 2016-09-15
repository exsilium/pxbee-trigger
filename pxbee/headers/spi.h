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
/**	Platform-specific layer provides a consistent SPI API to upper layers
 *	of the driver.
 *	
 *	@ingroup api_spi
 *	
 *	@defgroup api_spi
 *	
 *	@section macros_spi SPI Macros
 *	
 *	The spi_config() function needs as fourth parameter a byte containing the 
 *	configuration masks for the SPI module. These masks are defined with 
 *	macros and they are the following:
 *	
 *		- Macros to configure the \b data \b structure:
 * 			- \b SPI_CFG_BIT_MSB 		: Most Significant Bit first.
 *			- \b SPI_CFG_BIT_LSB		: Less Significant Bit first.
 *	
 *	
 *		- Macros to configure the \b clock \b polarity:
 *			- \b SPI_CFG_CPOL_0			: Configures the base value of the 
 *										  clock to 0.
 *			- \b SPI_CFG_CPOL_1			: Configures the base value of the 
 *										  clock to 1.
 *	
 *		- Macros to configure the \b clock \b phase:
 *			- \b SPI_CFG_CPHA_0			: If the clock polarity is 0, the 
 *										  data are captured on the clock's 
 *										  rising edge and data are propagated 
 *										  on a falling edge. If the clock 
 *										  polarity is 1, the data are 
 *										  captured on clock's falling edge 
 *										  and data are propagated on a 
 *										  rising edge.
 *			- \b SPI_CFG_CPHA_1			: If the clock polarity is 0, the 
 *										  data are captured on the clock's 
 *										  falling edge and data are 
 *										  propagated on a rising edge. If the 
 *										  clock polarity is 1, data are 
 *										  captured on clock's rising edge 
 *										  and data are propagated on a 
 *										  falling edge.
 *	
 *
 *	Usage example:
 *	@code spi_config(spi_0, 1, 1, SPI_CFG_BIT_MSB | SPI_CFG_SS_DISABLE  | SPI_CFG_CPOL_0 | SPI_CFG_MODE_SLAVE); 		
 *	@endcode
 *	@warning	It is recommended not to use these macros, they are used by 
 *				the XBee Project Smart Editor of the XBee extensions.
 *
 ***************************************************************************/

#ifndef __SPI_H_
#define __SPI_H_

#include <types.h>
#include <xbee_config.h>

#define SPI_CFG_BIT_MSB					(0 << 0)
#define SPI_CFG_BIT_LSB					(1 << 0)
#define SPI_CFG_SS_DISABLE				(0 << 1)
#define SPI_CFG_SS_ENABLE				(1 << 1)
#define SPI_CFG_CPHA_0					(0 << 2)
#define SPI_CFG_CPHA_1					(1 << 2)
#define SPI_CFG_CPOL_0					(0 << 3)
#define SPI_CFG_CPOL_1					(1 << 3)
#define SPI_CFG_MODE_SLAVE				(0 << 4)
#define SPI_CFG_MODE_MASTER				(1 << 4)
#define SPI_CFG_LOGIC_NEG				(1 << 7)
#define SPI_CFG_LOGIC_POS				(0 << 7)

#define SPI_CFG_BIT_MASK				(1 << 0)
#define SPI_CFG_SS_DISABLE_MASK			(1 << 1)
#define SPI_CFG_CPHA_MASK				(1 << 2)
#define SPI_CFG_CPOL_MASK				(1 << 3)
#define SPI_CFG_MODE_MASK				(1 << 4)
#define SPI_CFG_LOGIC_MASK				(1 << 7)

#ifdef ENABLE_SPI_PORT

#define SPI0				0
#define MAX_SS_SUPPORTED	4

#ifdef ENABLE_SPI0

#define SPI0_CFG			(SPI0_CFG_BIT 	 	 |		\
							 SPI0_CFG_CPHA 		 |		\
							 SPI_CFG_SS_DISABLE  |		\
							 SPI0_CFG_CPOL 		 |		\
							 SPI0_CFG_MODE ) /* doesn't have pin logic */

#ifdef SPI0_SS0_PIN
#define SPI0_SS0_CONFIG		(SPI0_SS0_CFG_BIT   |		\
							 SPI0_SS0_CFG_CPHA  |		\
							 SPI0_SS0_CFG_CPOL  |		\
							 SPI_CFG_SS_DISABLE |		\
							 SPI0_CFG_MODE	    |		\
							 SPI0_SS0_CFG_LOGIC)
#else
#define SPI0_SS0_CONFIG		0
#define SPI0_SS0_PIN		XPIN_UNDEF
#endif /* SPI0_SS0_PIN */

#ifdef SPI0_SS1_PIN
#define SPI0_SS1_CONFIG		(SPI0_SS1_CFG_BIT   |		\
							 SPI0_SS1_CFG_CPHA  |		\
							 SPI0_SS1_CFG_CPOL  |		\
							 SPI_CFG_SS_DISABLE |		\
							 SPI0_CFG_MODE	    |		\
							 SPI0_SS1_CFG_LOGIC)
#else
#define SPI0_SS1_CONFIG		0
#define SPI0_SS1_PIN		XPIN_UNDEF
#endif /* SPI0_SS1_PIN */

#ifdef SPI0_SS2_PIN
#define SPI0_SS2_CONFIG		(SPI0_SS2_CFG_BIT   |		\
							 SPI0_SS2_CFG_CPHA  |		\
							 SPI0_SS2_CFG_CPOL  |		\
							 SPI_CFG_SS_DISABLE |		\
							 SPI0_CFG_MODE	    |		\
							 SPI0_SS2_CFG_LOGIC)
#else
#define SPI0_SS2_CONFIG		0
#define SPI0_SS2_PIN		XPIN_UNDEF
#endif /* SPI0_SS2_PIN */

#ifdef SPI0_SS3_PIN
#define SPI0_SS3_CONFIG		(SPI0_SS3_CFG_BIT   |		\
							 SPI0_SS3_CFG_CPHA  |		\
							 SPI0_SS3_CFG_CPOL  |		\
							 SPI_CFG_SS_DISABLE |		\
							 SPI0_CFG_MODE	    |		\
							 SPI0_SS3_CFG_LOGIC)
#else
#define SPI0_SS3_CONFIG		0
#define SPI0_SS3_PIN		XPIN_UNDEF
#endif /* SPI0_SS3_PIN */

#endif /* ENABLE_SPI0 */

ssize_t spi_config(uint8_t brpree, uint8_t brdiv, uint8_t config);
ssize_t spi_transfer(uint8_t ss_num, const void *txbuf, void *rxbuf, size_t len);

#endif /* ENABLE_SPI_PORT */
#endif /* __SPI_H_ */
