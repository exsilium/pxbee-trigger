/*****************************************************/
/**
* @file stdtypes.h
*   ANSI-C library: standard type typedefs
*              defines some usefull stuff not in the
*              official ANSI library
*/
/*----------------------------------------------------
 Copyright (c) Metrowerks, Basel, Switzerland
               All rights reserved
                  Do not modify!
 *****************************************************/

#ifndef _H_STDTYPES_
#define _H_STDTYPES_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__HIWARE__)
  #define __CAN_HANDLE_LONG_LONG__
  /*!< We accept 'long long' types. */
#endif

typedef void (*PROC)(void);
/*!< Parameterless function pointer (Procedure variable) */

#if defined(__CHAR_IS_8BIT__)
  typedef  unsigned char      Byte;
  typedef    signed char      sByte;
#elif defined(__SHORT_IS_8BIT__)
  typedef  unsigned short     Byte;
  typedef    signed short     sByte;
#elif defined(__INT_IS_8BIT__)
  typedef  unsigned int       Byte;
  typedef    signed int       sByte;
#elif defined(__LONG_IS_8BIT__)
  typedef  unsigned long      Byte;
  typedef    signed long      sByte;
#elif defined(__LONG_LONG_IS_8BIT__)
  typedef  unsigned long long Byte;
  typedef    signed long long sByte;
#else /* default */
  typedef  unsigned char      Byte;
  typedef    signed char      sByte;
#endif
/*! \typedef Byte 
    Byte is a unsigned integral 8 bit type (typically unsigned char) */
/*! \typedef sByte  
    sByte is a signed integral 8 bit type (typically signed char)  */


#if defined(__CHAR_IS_16BIT__)
  typedef  unsigned char      Word;
  typedef    signed char      sWord;
#elif defined(__SHORT_IS_16BIT__) && !defined(__INT_IS_16BIT__)
  typedef  unsigned short     Word;
  typedef    signed short     sWord;
#elif defined(__INT_IS_16BIT__)
  typedef  unsigned int       Word;
  typedef    signed int       sWord;
#elif defined(__LONG_IS_16BIT__)
  typedef  unsigned long      Word;
  typedef    signed long      sWord;
#elif defined(__LONG_LONG_IS_16BIT__)
  typedef  unsigned long long Word;
  typedef    signed long long sWord;
#else
  typedef  unsigned short     Word;
  typedef    signed short     sWord;
#endif
/*! \typedef Word 
    Word is a unsigned integral 16 bit type (typically unsigned short) */
/*! \typedef sWord  
    sWord is a signed integral 16 bit type (typically signed short)  */

#if defined(__CHAR_IS_32BIT__)
  typedef  unsigned char      LWord;
  typedef    signed char      sLWord;
#elif defined(__SHORT_IS_32BIT__)
  typedef  unsigned short     LWord;
  typedef    signed short     sLWord;
#elif defined(__INT_IS_32BIT__)
  typedef  unsigned int       LWord;
  typedef    signed int       sLWord;
#elif defined(__LONG_IS_32BIT__)
  typedef  unsigned long      LWord;
  typedef    signed long      sLWord;
#elif defined(__LONG_LONG_IS_32BIT__)
  typedef  unsigned long long LWord;
  typedef    signed long long sLWord;
#else /* default */
  typedef  unsigned long LWord;
  typedef    signed long sLWord;
#endif
/*! \typedef LWord 
    LWord is a unsigned integral 32 bit type (typically unsigned int or unsigned long) */
/*! \typedef sLWord  
    sLWord is a signed integral 32 bit type (typically signed int or signed long)  */

typedef  unsigned char      uchar;
  /*!< Definition for an unsigned char. */
typedef  unsigned int       uint;
  /*!< Definition for an unsigned int. */
typedef  unsigned long      ulong;
  /*!< Definition for an unsigned long. */
#ifdef __CAN_HANDLE_LONG_LONG__
typedef  unsigned long long ullong;
  /*!< Definition for an unsigned long long. */
#endif

typedef  signed char        schar;
  /*!< Definition for an signed char. */
typedef  signed int         sint;
  /*!< Definition for an signed int. */
typedef  signed long        slong;
  /*!< Definition for an signed long. */
#ifdef __CAN_HANDLE_LONG_LONG__
typedef  signed long long   sllong;
  /*!< Definition for an signed long long. */
#endif

/** Defines the enum_t type. */
#if defined(__ENUM_IS_8BIT__)
  #if defined(__ENUM_IS_UNSIGNED__)
    typedef Byte   enum_t;
    #elif defined(__ENUM_IS_SIGNED__)
    typedef sByte  enum_t;
    #else
      #error "illegal sign of enum"
    #endif
#elif defined(__ENUM_IS_16BIT__)
  #if defined(__ENUM_IS_UNSIGNED__)
      typedef Word   enum_t;
    #elif defined(__ENUM_IS_SIGNED__)
      typedef sWord  enum_t;
    #else
      #error "illegal sign of enum"
    #endif
#elif defined(__ENUM_IS_32BIT__)
  #if defined(__ENUM_IS_UNSIGNED__)
      typedef LWord   enum_t;
    #elif defined(__ENUM_IS_SIGNED__)
      typedef sLWord  enum_t;
    #else
      #error "illegal sign of enum"
    #endif
#else /* default */
  typedef sWord  enum_t;
#endif

typedef int Bool;
  /*!< Definition for boolean type. */
#ifdef __MISRA__ /* MISRA rule #18 */
  #define TRUE  1u
    /*!< Definitioni for TRUE. */
  #define FALSE 0u
    /*!< Definition for FALSE. */
#else
  #define TRUE  1
    /*!< Definitioni for TRUE. */
  #define FALSE 0
    /*!< Definition for FALSE. */
#endif

#ifdef __cplusplus
 }
#endif

#endif
/*****************************************************/
/* end stdtypes.h */
