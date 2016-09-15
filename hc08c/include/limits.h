/*****************************************************
     limits.h - ANSI-C library: type range limits
 ----------------------------------------------------
   Copyright (c) Metrowerks, Basel, Switzerland
               All rights reserved
                  Do not modify!
 *****************************************************/

#ifndef _H_LIMITS_
#define _H_LIMITS_

#ifdef __cplusplus
extern "C" {
#endif
/* ---------------------- char type ---------------------- */
#if defined(__CHAR_IS_8BIT__)
  #define CHAR_BIT             8     /* number of bits in a char */
  #define SCHAR_MIN      (-127-1)    /* minimum signed char value */
  #define SCHAR_MAX          127     /* maximum signed char value */
  #define UCHAR_MAX         0xff     /* maximum unsigned char value */
  #define MB_LEN_MAX           1     /* max. # bytes in multibyte char */
#elif defined(__CHAR_IS_16BIT__)
  #define CHAR_BIT            16     /* number of bits in a char */
  #define SCHAR_MIN    (-32767-1)    /* minimum signed char value */
  #define SCHAR_MAX        32767     /* maximum signed char value */
  #define UCHAR_MAX       0xffff     /* maximum unsigned char value */
  #define MB_LEN_MAX           2     /* max. # bytes in multibyte char */
#elif defined(__CHAR_IS_32BIT__)
  #define CHAR_BIT            32     /* number of bits in a char */
  #define SCHAR_MIN (-2147483647-1)  /* minimum signed char value */
  #define SCHAR_MAX   2147483647     /* maximum signed char value */
  #define UCHAR_MAX   0xffffffff     /* maximum unsigned char value */
  #define MB_LEN_MAX           4     /* max. # bytes in multibyte char */
#elif defined(__CHAR_IS_64BIT__)
  #define CHAR_BIT            64               /* number of bits in a char */
  #define SCHAR_MIN (-18446744073709551615-1)  /* minimum signed char value */
  #define SCHAR_MAX   18446744073709551615     /* maximum signed char value */
  #define UCHAR_MAX   0xffffffffffffffff       /* maximum unsigned char value */
  #define MB_LEN_MAX           8     /* max. # bytes in multibyte char */
#else /* default */
  #define CHAR_BIT             8     /* number of bits in a char */
  #define SCHAR_MIN      (-127-1)    /* minimum signed char value */
  #define SCHAR_MAX          127     /* maximum signed char value */
  #define UCHAR_MAX         0xff     /* maximum unsigned char value */
  #define MB_LEN_MAX           1     /* max. # bytes in multibyte char */
#endif

#if defined(__CHAR_IS_SIGNED__)
  #define CHAR_MIN     SCHAR_MIN     /* mimimum char value */
  #define CHAR_MAX     SCHAR_MAX     /* maximum char value */
#elif defined(__CHAR_IS_UNSIGNED__)
  #define CHAR_MIN     0             /* mimimum char value */
  #define CHAR_MAX     UCHAR_MAX     /* maximum char value */
#else
  #define CHAR_MIN     SCHAR_MIN     /* mimimum char value */
  #define CHAR_MAX     SCHAR_MAX     /* maximum char value */
#endif
/* ---------------------- short type ---------------------- */
#if defined(__SHORT_IS_8BIT__)
  #define SHORT_BIT            8     /* number of bits in a short */
  #define SHRT_MIN       (-127-1)    /* minimum (signed) short value */
  #define SHRT_MAX           127     /* maximum (signed) short value */
  #define USHRT_MAX         0xff     /* maximum unsigned short value */
#elif defined(__SHORT_IS_16BIT__)
  #define SHORT_BIT           16     /* number of bits in a short */
  #define SHRT_MIN     (-32767-1)    /* minimum (signed) short value */
  #define SHRT_MAX         32767     /* maximum (signed) short value */
  #define USHRT_MAX       0xffff     /* maximum unsigned short value */
#elif defined(__SHORT_IS_32BIT__)
  #define SHORT_BIT           32     /* number of bits in a short */
  #define SHRT_MIN  (-2147483647-1)  /* minimum (signed) short value */
  #define SHRT_MAX    2147483647     /* maximum (signed) short value */
  #define USHRT_MAX   0xffffffff     /* maximum unsigned short value */
#elif defined(__SHORT_IS_64BIT__)
  #define SHORT_BIT            64             /* number of bits in a short */
  #define SHRT_MIN (-18446744073709551615-1)  /* minimum signed short value */
  #define SHRT_MAX   18446744073709551615     /* maximum signed short value */
  #define USHRT_MAX   0xffffffffffffffff      /* maximum unsigned short value */
#else
  #define SHORT_BIT           16     /* number of bits in a short */
  #define SHRT_MIN     (-32767-1)    /* minimum (signed) short value */
  #define SHRT_MAX         32767     /* maximum (signed) short value */
  #define USHRT_MAX       0xffff     /* maximum unsigned short value */
#endif
/* ---------------------- int type ---------------------- */
#if defined(__INT_IS_8BIT__)
  #define INT_BIT             8      /* number of bits in a int */
  #define INT_MIN        (-127-1)    /* minimum (signed) int value */
  #define INT_MAX            127     /* maximum (signed) int value */
  #define UINT_MAX          0xff     /* maximum unsigned int value */
#elif defined(__INT_IS_16BIT__)
  #define INT_BIT            16      /* number of bits in a int */
  #define INT_MIN      (-32767-1)    /* minimum (signed) int value */
  #define INT_MAX          32767     /* maximum (signed) int value */
  #define UINT_MAX        0xffff     /* maximum unsigned int value */
#elif defined(__INT_IS_32BIT__)
  #define INT_BIT            32      /* number of bits in a int */
  #define INT_MIN   (-2147483647-1)  /* minimum (signed) int value */
  #define INT_MAX     2147483647     /* maximum (signed) int value */
  #define UINT_MAX    0xffffffff     /* maximum unsigned int value */
#elif defined(__INT_IS_64BIT__)
  #define INT_BIT            64              /* number of bits in a int */
  #define INT_MIN (-18446744073709551615-1)  /* minimum signed int value */
  #define INT_MAX   18446744073709551615     /* maximum signed int value */
  #define UINT_MAX  0xffffffffffffffff      /* maximum unsigned int value */
#else
  #define INT_BIT            16      /* number of bits in a int */
  #define INT_MIN      (-32767-1)    /* minimum (signed) int value */
  #define INT_MAX          32767     /* maximum (signed) int value */
  #define UINT_MAX        0xffff     /* maximum unsigned int value */
#endif
/* ---------------------- long type ---------------------- */
#if defined(__LONG_IS_8BIT__)
  #define LONG_BIT             8     /* number of bits in a long */
  #define LONG_MIN       (-127-1)    /* minimum (signed) long value */
  #define LONG_MAX           127     /* maximum (signed) long value */
  #define ULONG_MAX         0xff     /* maximum unsigned long value */
#elif defined(__LONG_IS_16BIT__)
  #define LONG_BIT            16     /* number of bits in a long */
  #define LONG_MIN     (-32767-1)    /* minimum (signed) long value */
  #define LONG_MAX         32767     /* maximum (signed) long value */
  #define ULONG_MAX       0xffff     /* maximum unsigned long value */
#elif defined(__LONG_IS_32BIT__)
  #define LONG_BIT            32     /* number of bits in a long */
  #define LONG_MIN  (-2147483647-1)  /* minimum (signed) long value */
  #define LONG_MAX    2147483647     /* maximum (signed) long value */
  #define ULONG_MAX   0xffffffff     /* maximum unsigned long value */
#elif defined(__LONG_IS_64BIT__)
  #define LONG_BIT            64              /* number of bits in a long */
  #define LONG_MIN (-18446744073709551615-1)  /* minimum signed long value */
  #define LONG_MAX   18446744073709551615     /* maximum signed long value */
  #define ULONG_MAX   0xffffffffffffffff      /* maximum unsigned long value */
#else
  #define LONG_BIT            32     /* number of bits in a long */
  #define LONG_MIN  (-2147483647-1)  /* minimum (signed) long value */
  #define LONG_MAX    2147483647     /* maximum (signed) long value */
  #define ULONG_MAX   0xffffffff     /* maximum unsigned long value */
#endif

#ifdef __cplusplus
 }
#endif

#endif

/*****************************************************/
/* end limits.h */
