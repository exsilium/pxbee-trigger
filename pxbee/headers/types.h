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
 * 	@ingroup types	
 *	@defgroup types
 *	Types.h is the document with the variables types that we use
 *	in the API.
 */
#ifndef __TYPES_H_
#define __TYPES_H_

#include <stddef.h>
/** @ingroup types
 */
typedef char bool_t;
///  A unsigned char variable 8 bits
typedef unsigned char uint8_t;
//typedef unsigned short uint16_t;
/// An unsigned integer variable 16 bits
typedef unsigned int uint16_t;
/// An unsigned long variable 32 bit 
typedef unsigned long uint32_t;
//typedef char int8_t;
/// A signed char variable 8 bits
typedef signed char int8_t;
//typedef short int16_t;
/// A signed integer variable 16 bits
typedef int int16_t;
/// A signed long variable 32 bits
typedef long int32_t;
/// A integer variable for return data lenght
/** @ingroup types
 */
typedef int ssize_t;
/// An unsigned char variable for select devices. Used in SPI for select SPI0 SPI1
/** @ingroup types
 */
typedef unsigned char dev_t;
/** @ingroup types
 */
/// Variable for manage the port component.
typedef enum {
	PORT0,
	PORT1,
	PORT2, 
	PORT3,
}port_t;

/* Some definitions that maybe not found in errno.h */
#ifndef EPERM
#define EPERM 			1
#endif
#ifndef ENOENT
#define ENOENT			2		/* No such file or directory */
#endif
#ifndef EIO
#define EIO				5		/* I/O error */
#endif
#ifndef ENODEV
#define ENODEV			19		/* No such device */
#endif
#ifndef EINVAL
#define EINVAL          22		/* Invalid argument */
#endif
#ifndef EAGAIN
#define EAGAIN			35		/* Try again */
#endif
#ifndef ENXIO
#define ENXIO			41      /* No such device or address TO_DO review */
#endif
#ifndef EILSEQ
#define	EILSEQ			42		/* Illegal byte sequence */
#endif
#ifndef EBUSY
#define EBUSY			203		/* Device or resource busy */
#endif
#ifndef ETIMEDOUT
#define ETIMEDOUT		212		/* Timeout */
#endif

/* Additional flags */
#ifndef O_NONBLOCK
#define O_NONBLOCK		(1 << 0)
#endif

#define ARRAY_SIZE(a)	(sizeof(a) / sizeof(a[0]))

#endif /* __TYPES_H_ */

