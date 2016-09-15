/*****************************************************
        errno.h - ANSI-C library: error codes
 ----------------------------------------------------
   Copyright (c) Metrowerks, Basel, Switzerland
               All rights reserved
                  Do not modify!
 *****************************************************/

#ifndef _H_ERRNO_
#define _H_ERRNO_

#ifdef __cplusplus
extern "C" {
#endif

#define ERESET      0
/*!< Reset                      */
#define EDOM        1
/*!< ANSI Required              */
#define ERANGE      2
/*!< ANSI Required, range error */
#define ESIG_ERR    3
/*!< Signal number out of range */
#define EOVERFLOW   4
/*!< Overflow                   */
#define EUNDERFLOW  5
/*!< Underflow                  */

extern int errno;

#ifdef __cplusplus
 }
#endif

#endif

/*****************************************************/
/* end errno.h */
