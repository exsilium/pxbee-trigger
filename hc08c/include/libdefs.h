/******************************************************/
/**
* @file libdefs.h
* Library configuration definitions.
* This file contains all defines to configure the library build.
* Normally they can be set on the compiler command line during library build,
* e.g. the compiler option
*   -DLIBDEF_FAR_HEAP=1
* would enable that the library is build for a 'far' memory used by malloc, free,...
* NOTE: you have to set the define to zero or one, just -DLIBDEF_FAR_HEAP is wrong!
*
* If the following defines are NOT set on the compiler command line, a default is assumed.
* Note that not all configuration defines may be available for a target, e.g. if the
* target does not support the 'far' keyword.
* 
* Please be careful:
* If you build your library using special setting on the command line, use them to build
* your application too, else your application uses not the correct interface to the library!
*/
/*----------------------------------------------------
   Copyright (c) Metrowerks, Basel, Switzerland
               All rights reserved
         Do not modify the Copyright above
 *****************************************************/

#ifndef _H_LIBDEFS_
#define _H_LIBDEFS_

#ifdef __cplusplus
  extern "C" {
#endif

#include <hidef.h>

/*---------------------------------------------------------------------------------
  GENERAL TYPES
  Header Files: stdlib.h
                string.h
                assert.h
                stdio.h
  Functions   : vprintf, sprintf, vsprintf, vsscanf, sscanf
                strtod, strol, strtoul,
                getenv, system
                mblen, mbtowc, mbstowcs,
                strcat, strncat, strcpy, strncpy, strcmp, strncmp,
                strchr, strrchr, strspn, strcspn, strpbrk, strstr,
                strtok, strcoll, strxfrm, strlen,
                _assert
                bsearch, qsort
  Defines     : LIBDEF_FAR_CONST_STRINGS  (0 (default) or 1)
                LIBDEF_FAR_STRINGS        (0 (default) or 1)
                LIBDEF_FAR_CONST_VOID_PTR (0 (default) or 1)
                LIBDEF_FAR_VOID_PTR       (0 (default) or 1)
  Data Segment: none
  Code Segment: none
  ---------------------------------------------------------------------------------*/
/* some processor allocate strings (e.g. "abc") in the far area */
#if defined(__HC05__) || defined(__ST7__) || defined(__HC08__) || defined(__RS08__) || defined(__ST19X__) || defined(__XA__)
  #define LIBDEF_FAR_CONST_STRINGS  1
  /*!< We are using 'far' memory for constant strings. */
  #define LIBDEF_FAR_STRINGS        1
  /*!< We are using strings in far memory area */
  #define LIBDEF_FAR_CONST_VOID_PTR 1
  /*!< Const void pointers (const void *) are far pointers */
  #define LIBDEF_FAR_VOID_PTR       1
  /*!< Void pointers (void *) are handled as far pointers */
  #define LIBDEF_FAR_CONSTANTS      1
  /*!< Contants are in far memory */
#elif defined(__HC16__)
  #ifndef __STDC__
    #if  __OPTION_ACTIVE__("-Ca") /* HC16 with far strings */
      #define LIBDEF_FAR_CONST_STRINGS  1
      /*!< Constant strings are far. */
      #define LIBDEF_FAR_STRINGS        1
      /*!< strings are far. */
    #endif
  #endif
#endif

#if defined(__HCS12X__) && defined(__LARGE__) && defined(__USER_DEF_QUALIS__)
  /*!<  HCS12X with command-line defined pointer qualifiers. The interface with the library will be done via far pointers to assure the correctness of const/non-const pointers.  */
  #define LIBDEF_FAR_CONST_STRINGS     1 
  #define LIBDEF_FAR_STRINGS           1 
  #define LIBDEF_FAR_CONST_VOID_PTR    1 
  #define LIBDEF_FAR_VOID_PTR          1
#endif

#ifndef LIBDEF_FAR_CONST_STRINGS
  #define LIBDEF_FAR_CONST_STRINGS  0
  /*!< Define this to 1 if const strings (const char*) are placed in 'far' heap memory. */
#endif

#ifndef LIBDEF_FAR_STRINGS
  #define LIBDEF_FAR_STRINGS        0
  /*!< Define this to 1 if strings (char *) are placed in 'far' heap memory. */
#endif

#ifndef LIBDEF_FAR_CONST_VOID_PTR
  #define LIBDEF_FAR_CONST_VOID_PTR 0
  /*!< Define this to 1 if const void pointers (const void *) have to point into 'far' heap memory. */
#endif

#ifndef LIBDEF_FAR_VOID_PTR
  #define LIBDEF_FAR_VOID_PTR       0
  /*!< Define this to 1 if void pointers (void *) have to point into 'far' heap memory. */
#endif

#ifndef LIBDEF_FAR_CONSTANTS
  #define LIBDEF_FAR_CONSTANTS      0
  /*!< Define this to 1 if pointers to constants (const *) have to point into 'far' heap memory.  */
#endif

#if LIBDEF_FAR_CONST_STRINGS
  #define LIBDEF_CCHAR_DPTRQ _FAR  /* see hidef.h */
  /*!< We are using _FAR for const char Data PTR qualifier. */
#else /* default */
  #define LIBDEF_CCHAR_DPTRQ  /* empty */
  /*!< No qualifier used for const char Data PTR. */
#endif

#if LIBDEF_FAR_STRINGS
  #define LIBDEF_CHAR_DPTRQ  _FAR
  /*!< char Data PTR Qualifier CHAR_DPTRQ */
#else /* default */
  #define LIBDEF_CHAR_DPTRQ  /* empty */
  /*!< char Data PTR Qualifier CHAR_DPTRQ */
#endif

#if LIBDEF_FAR_CONST_VOID_PTR
  #define LIBDEF_CVOID_DPTRQ  _FAR
  /*!< const void Data PTR Qualifier CVOID_DPTRQ */
#else /* default */
  #define LIBDEF_CVOID_DPTRQ  /* empty */
  /*!< const void Data PTR Qualifier CVOID_DPTRQ */
#endif

#if LIBDEF_FAR_VOID_PTR
  #define LIBDEF_VOID_DPTRQ  _FAR
  /*!< void Data PTR Qualifier VOID_DPTRQ */
#else /* default */
  #define LIBDEF_VOID_DPTRQ  /* empty */
  /*!< void Data PTR Qualifier VOID_DPTRQ */
#endif

#if LIBDEF_FAR_CONSTANTS
  #define LIBDEF_CONST_DPTRQ  _FAR
  /*!< const Data PTR Qualifier CONST_DPTRQ */
#else /* default */
  #define LIBDEF_CONST_DPTRQ  /* empty */
  /*!< const Data PTR Qualifier CONST_DPTRQ. */
#endif

typedef const char *LIBDEF_CCHAR_DPTRQ ConstString;
  /*!< Definition of a constant string. */
typedef const char *LIBDEF_CCHAR_DPTRQ LIBDEF_ConstStringPtr;
  /*!< Definition of a pointer to a constant string. */
typedef       char *LIBDEF_CHAR_DPTRQ  LIBDEF_StringPtr;
  /*!< Definition of a pointer to a string */

typedef const void *LIBDEF_CVOID_DPTRQ    ConstMem;
  /*!< Definition of a generic pointer to constant memory, same as LIBDEF_ConstMemPtr. */
typedef const void *LIBDEF_CVOID_DPTRQ    LIBDEF_ConstMemPtr;
  /*!< Definition of a generic pointer to constant memory */
typedef       void *LIBDEF_VOID_DPTRQ     LIBDEF_MemPtr;
  /*!< Definition of a generic pointer to memory */
typedef       char  LIBDEF_MemByte;
  /*!< Definition of a byte in memory. */
typedef       LIBDEF_MemByte *LIBDEF_VOID_DPTRQ     LIBDEF_MemBytePtr;
  /*!< Pointer to a byte in memory. */
typedef const LIBDEF_MemByte *LIBDEF_VOID_DPTRQ     LIBDEF_ConstMemBytePtr;
  /*!< Pointer to a constant byte in memory. */

/*---------------------------------------------------------------------------------
  MEMORY MANAGEMENT:
  Header Files: stdlib.h
                heap.h
  Functions   : calloc
                free
                malloc
                realloc
                _heapcrash_
  Defines     : LIBDEF_FAR_HEAP_DATA  (0 (default) or 1)
                LIBDEF_HEAPSIZE       (default 2000)
  Data Segment: HEAP_SEGMENT          far if LIBDEF_FAR_HEAP_DATA is 1
  Code Segment: DEFAULT
  ---------------------------------------------------------------------------------*/
#ifndef LIBDEF_FAR_HEAP_DATA
  #define LIBDEF_FAR_HEAP_DATA  0
  /*!< Define this to 1 if you want to use 'far' heap memory. */
#endif

/* Heap Data PTR Qualifier HEAP_DPTRQ */
#if LIBDEF_FAR_HEAP_DATA
  #define LIBDEF_HEAP_DPTRQ  far
    /*!< We are using 'far' as data pointer qualifier to access the heap. */
#else
  #define LIBDEF_HEAP_DPTRQ  /* empty */
    /*!< We are not using any data pointer qualifier to access the heap. */
#endif

#define LIBDEF_HEAPSIZE 2000  
  /*!< Adjust to your requirements, nofBytes = LIBDEF_HEAPSIZE, must be multipe of 4!  */
/*---------------------------------------------------------------------------------
  NUMBER CONVERSION FUNCTIONS:
  Header Files: stdlib.h
  Functions   : 
  Defines     : LIBDEF_FAR_NUMCONV_DATA  (0 (default) or 1)
  Data Segment: none
  Code Segment: DEFAULT
  ---------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------*/
/* stdlib.c */
/*---------------------------------------------------------------------------------*/
/* The following defines are used to tailor the ANSI-C library code overhead.
   To get better code (improved code density and speed), disable them. */
#define LIBDEF_ENABLE_OVERFLOW_CHECK 1
  /*!< ANSI standard overflow checking. Switch off for less code. */
#define LIBDEF_STRTOD_EXTENDED_PREC 1
  /*!< Extended precision for strtod. Disable it for less code. */

/* printf, scanf */
#ifndef LIBDEF_PRINTF_FLOATING
  #ifdef __NO_FLOAT__
    #define LIBDEF_PRINTF_FLOATING      0
   /*!< Set to 1 if %e,%E,%f,%F (floating point) in printf/scanf is needed. */
  #else
    #define LIBDEF_PRINTF_FLOATING      1
   /*!< Set to 1 if %e,%E,%f,%F (floating point) in printf/scanf is needed. */
  #endif
#endif /* LIBDEF_PRINTF_FLOATING */

#ifndef LIBDEF_PRINTF_PTR
  #define LIBDEF_PRINTF_PTR             1 
  /*!< Set to 1 if %p (pointer support) in printf/scanf is needed. */
#endif /* LIBDEF_PRINTF_PTR */

#ifndef LIBDEF_PRINTF_NOF_CHAR
  #define LIBDEF_PRINTF_NOF_CHAR        1
  /*!< Set to 1 if %n (number of char) in printf/scanf is needed. */
#endif /* LIBDEF_PRINTF_NOF_CHAR */

#ifndef LIBDEF_PRINTF_PREC
  #define LIBDEF_PRINTF_PREC            (1 || LIBDEF_PRINTF_FLOATING)
  /*!< Set to 1 if '.' (precision support) in printf/scanf is needed. */
#endif /* LIBDEF_PRINTF_PREC */

#ifndef LIBDEF_PRINTF_CHAR
  #define LIBDEF_PRINTF_CHAR            1
  /*!< Set to 1 if %%c (character support) in printf/scanf is needed. */
#endif /* LIBDEF_PRINTF_CHAR */

#ifndef LIBDEF_PRINTF_LONG
  #define LIBDEF_PRINTF_LONG            (1 || LIBDEF_PRINTF_FLOATING)
  /*!< Set to 1 if %%l,%%L (long decimal) in printf is needed. */
#endif /* LIBDEF_PRINTF_LONG */

#ifndef LIBDEF_PRINTF_ALLOW_OCTINT
  #define LIBDEF_PRINTF_ALLOW_OCTINT    1
  /*!< Set to 1 if %%o (octal printing) in printf is needed. */
#endif /* LIBDEF_PRINTF_ALLOW_OCTINT */

#ifndef LIBDEF_PRINTF_ALLOW_HEXINT
  #define LIBDEF_PRINTF_ALLOW_HEXINT    1
  /*!< Set to 1 if %%x, %%X (hexadecimal printing) in printf is needed. */
#endif  /* LIBDEF_PRINTF_ALLOW_HEXINT */

#ifndef LIBDEF_PRINTF_FAR_PTR
/*!<
* Set to one if far pointers in printf shall be supported:
*  FAR pointer conventions:
*  '%+': FAR qualifier
*  '%P': FAR pointer
*  '%S': FAR string
*  '%N': FAR pointer to the variable where the number of items written is to be stored.
*/
  #define LIBDEF_PRINTF_FAR_PTR         (1 && defined(__HC16__))
#endif /* LIBDEF_PRINTF_FAR_PTR */

#ifndef LIBDEF_SCANF_BUF_SIZE
  #define LIBDEF_SCANF_BUF_SIZE 255
  /*!< Define the buffer size needed in scanf: may be reduced to save RAM. */
#endif  /* LIBDEF_SCANF_BUF_SIZE */

#ifndef LIBDEF_SCANF_DONTCARE_SPACES
  #define LIBDEF_SCANF_DONTCARE_SPACES  0
  /*!< Do not return error if spaces in format are not present in the input string. */
#endif /* LIBDEF_SCANF_DONTCARE_SPACES */

#ifndef LIBDEF_MULTI_CHAR_SELECTION
  #define LIBDEF_MULTI_CHAR_SELECTION   1
  /*!< Set to 1 if the "[" scanf format is needed. */
#endif /* LIBDEF_MULTI_CHAR_SELECTION */

#ifndef LIBDEF_REENTRANT_PRINTF
  #define LIBDEF_REENTRANT_PRINTF       0
  /*!< Set to 1 if a reentrant version of printf and sprintf is needed. */
#endif /* LIBDEF_REENTRANT_PRINTF */
/*---------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------
  C++ library
  Header Files: builtin.h, ccstring.h, cstring.h, streamb.h, stdiostr.h, std.h, regex.h, libiop.h, libio.h, iostream.h, iolibio.h
  Functions   : 
  Defines     : _LIBDEF_FAR_CPP_PTR_CFG  (0 (default) or 1)
  Data Segment: none
  Code Segment: DEFAULT
  ---------------------------------------------------------------------------------*/

#ifndef _LIBDEF_FAR_CPP_PTR_CFG
  #define _LIBDEF_FAR_CPP_PTR_CFG  0
  /*!< Define this to 1 if you want to use 'far' strings with the C++ library. */
#endif

#if _LIBDEF_FAR_CPP_PTR_CFG
  #define _LIBDEF_FAR_CPP_PTR  _FAR
  /*!< _FAR used as qualifier for strings in C++. */
#else
  #define _LIBDEF_FAR_CPP_PTR  /* empty */
  /*!< We are not using far string pointers in C++. */
#endif

/*---------------------------------------------------------------------------------*/
#ifdef __cplusplus
 }
#endif

#endif /* _H_LIBDEFS_ */
/*****************************************************/

