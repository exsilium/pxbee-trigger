/*****************************************************
    stdlib.h - ANSI-C library: various functions
 ----------------------------------------------------
   Copyright (c) Metrowerks, Basel, Switzerland
               All rights reserved
                  Do not modify!
 *****************************************************/

#ifndef _H_STDLIB_
#define _H_STDLIB_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <libdefs.h>

typedef struct _div_t {
  int quot, rem;
} div_t;

typedef struct _ldiv_t {
  long int quot, rem;
} ldiv_t;

#define EXIT_FAILURE    -1
#define EXIT_SUCCESS     0

#define RAND_MAX     32767
#define MB_CUR_MAX       1

/**** Number conversion functions */
#if 1
  /* note: the following defines are for compatibility only. There is now an
           easier way to set up the library to deal with far data:
           you can configure this in the libdefs.h, e.g for
           LIBDEF_MemPtr or LIBDEF_ConstMemPtr.
           the following defines may be removed in a future version. */
  #define far_atof     atof
  #define far_atoi     atoi
  #define far_atol     atol
#endif

/*lint -e683 inhibit warning on standard function being #define'd */
#define atof(nptr)       strtod ((nptr), (LIBDEF_StringPtr*)NULL)
#define atoi(nptr)       (int) strtol ((nptr), (LIBDEF_StringPtr*)NULL, 10)
#define atol(nptr)       strtol ((nptr), (LIBDEF_StringPtr*)NULL, 10)
/*lint +e683 */

LIBDEF_StringPtr _itoa(int val, LIBDEF_StringPtr buf, int radix);
  /* writes an integral value as string into the buffer. Radix is the 
     number base to be used, e.g. 10 (decimal). Returns always buf. */

extern double            strtod  (LIBDEF_ConstStringPtr s, LIBDEF_StringPtr *end);
extern long int          strtol  (LIBDEF_ConstStringPtr s, LIBDEF_StringPtr *end, int base);
extern unsigned long int strtoul (LIBDEF_ConstStringPtr s, LIBDEF_StringPtr *end, int base);

/**** "Random" number generator */
extern int  rand  (void);
extern void srand (unsigned int seed);

/**** Memory management */
extern void *LIBDEF_HEAP_DPTRQ calloc(size_t n, size_t size);
extern void                    free(void *LIBDEF_HEAP_DPTRQ ptr);
extern void *LIBDEF_HEAP_DPTRQ malloc(size_t size);
extern void *LIBDEF_HEAP_DPTRQ realloc(void *LIBDEF_HEAP_DPTRQ ptr, size_t size);

/**** Program termination */
extern void  abort   (void);
extern int   atexit  (void (*func) (void));
extern void  exit    (int status);

/**** Environment */
extern LIBDEF_StringPtr getenv(LIBDEF_ConstStringPtr name);
extern int              system(LIBDEF_ConstStringPtr cmd);

/**** Searching and sorting */
extern LIBDEF_MemPtr bsearch (LIBDEF_ConstMemPtr look_for,
                           LIBDEF_ConstMemPtr base_addr,
                           size_t n, size_t size,
                           int (*cmp) (LIBDEF_ConstMemPtr, LIBDEF_ConstMemPtr)); /*lint !e960 MISRA 16.3 REQ, message reported not for a function, but for a function pointer */
extern void qsort (LIBDEF_ConstMemPtr base,
                   size_t n, size_t size,
                   int (*cmp) (LIBDEF_ConstMemPtr, LIBDEF_ConstMemPtr)); /*lint !e960 MISRA 16.3 REQ, message reported not for a function, but for a function pointer */

/**** Math supplement */
/* macro definitions of abs() and labs() */
#define M_ABS(j)  (((j) >= 0) ? (j) : -(j))

extern int      abs   (int j);
extern long int labs  (long int j);

extern div_t    div   (int dividend, int divisor);
extern ldiv_t   ldiv  (long int dividend, long int divisor);

/**** Wide char support */

extern int mblen(LIBDEF_ConstStringPtr mbs, size_t n);
extern int mbtowc(wchar_t *wc, LIBDEF_ConstStringPtr mb, size_t n);
extern int wctomb(LIBDEF_StringPtr mb, wchar_t wc);
extern size_t mbstowcs(wchar_t *wc, LIBDEF_ConstStringPtr mb, size_t n);
extern size_t wcstombs(LIBDEF_StringPtr mb, const wchar_t *wc, size_t n);

#ifdef __cplusplus
 }
#endif

#endif

/*****************************************************/
/* end stdlib.h */
