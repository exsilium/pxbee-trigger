/*********************************************************/
/** @file stddef.h  ANSI-C library: standard definitions */
/*-------------------------------------------------------*
   Copyright (c) Metrowerks, Basel, Switzerland
               All rights reserved
                  Do not modify!
 *********************************************************/

#ifndef _H_STDDEF_
#define _H_STDDEF_

#ifdef __cplusplus
extern "C" {
#endif

/** size_t: defines the maximum object size type */
#if defined(__SIZE_T_IS_UCHAR__)
  typedef unsigned char  size_t;
#elif defined(__SIZE_T_IS_USHORT__)
  typedef unsigned short size_t;
#elif defined(__SIZE_T_IS_UINT__)
  typedef unsigned int   size_t;
#elif defined(__SIZE_T_IS_ULONG__)
  typedef unsigned long  size_t;
#else
  typedef unsigned int   size_t;
#endif

/** ptrdiff_t: defines the maximum pointer difference type */
#if defined(__PTRDIFF_T_IS_CHAR__)
  typedef signed char   ptrdiff_t;
#elif defined(__PTRDIFF_T_IS_SHORT__)
  typedef signed short  ptrdiff_t;
#elif defined(__PTRDIFF_T_IS_INT__)
  typedef signed int    ptrdiff_t;
#elif defined(__PTRDIFF_T_IS_LONG__)
  typedef signed long   ptrdiff_t;
#else
  typedef signed int    ptrdiff_t;
#endif

/** wchar_t: defines the type of wide character */
#if defined(__WCHAR_T_IS_UCHAR__)
  typedef unsigned char  wchar_t;
#elif defined(__WCHAR_T_IS_USHORT__)
  typedef unsigned short wchar_t;
#elif defined(__WCHAR_T_IS_UINT__)
  typedef unsigned int   wchar_t;
#elif defined(__WCHAR_T_IS_ULONG__)
  typedef unsigned long  wchar_t;
#else
  typedef unsigned char  wchar_t;
#endif


typedef unsigned long clock_t;
  /*!< Clock type, used as return type for clock() (number of ticks). */
typedef unsigned long time_t;
  /*!< Represents time values in mktime() and time(). */
#define offsetof(type, member) ((size_t) &(((type *) 0)->member))
  /*!< calculates the offset of a struct member to its struct type. */
#define NULL                   ((void *) 0)
  /*!< definition of a NULL pointer. */

#ifdef __cplusplus
 }
#endif

#endif

/*****************************************************/
/* end stddef.h */
