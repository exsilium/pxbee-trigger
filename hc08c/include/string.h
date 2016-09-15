/*****************************************************
    string.h - ANSI-C library: string handling
 ----------------------------------------------------
   Copyright (c) Metrowerks, Basel, Switzerland
               All rights reserved
                  Do not modify!
 *****************************************************/

#ifndef _H_STRING_
#define _H_STRING_

#ifdef __cplusplus
extern "C" {
#endif

#include <libdefs.h>
#include <stddef.h>

#if 1
  /* note: the following defines are for compatibility only. There is now an
           easier way to set up the library to deal with far data:
           you can configure this in the libdefs.h, e.g for
           LIBDEF_MemPtr or LIBDEF_ConstMemPtr.
           the following defines may be removed in a future version. */
  #define far_memchr        memchr
  #define far_memcmp        memcmp
  #define far_memcpy        memcpy
  #define far_memcpy2       memcpy2
  #define far_memmove       memmove
  #define far_memset        memset
  #define far_strlen        strlen
  #define far_strset        strset
  #define far_strcat        strcat
  #define far_strncat       strncat
  #define far_strcpy        strcpy
  #define far_strncpy       strncpy
  #define far_strcmp        strcmp
  #define far_strncmp       strncmp
  #define far_strchr        strchr
  #define far_strrchr       strrchr
  #define far_strspn        strspn
  #define far_strcspn       strcspn
  #define far_strpbrk       strpbrk
  #define far_strstr        strstr
  #define far_strtok        strtok
  #define far_strerror      strerror
#endif


extern LIBDEF_MemPtr memchr  (LIBDEF_ConstMemPtr buffer, int chr, size_t count);
extern int           memcmp  (LIBDEF_ConstMemPtr buf1, LIBDEF_ConstMemPtr buf2, size_t count);
extern LIBDEF_MemPtr memcpy  (LIBDEF_MemPtr dest, LIBDEF_ConstMemPtr source, size_t count);

extern void          memcpy2(LIBDEF_MemPtr dest, LIBDEF_ConstMemPtr source, size_t count);
  /* this function does not return the dest and assumes count > 0 */
extern void _memcpy_8bitCount(LIBDEF_MemPtr dest, LIBDEF_ConstMemPtr source, unsigned char count);
  /* this function does not return the dest, and count is in the range 0..0xff */

extern LIBDEF_MemPtr memmove (LIBDEF_MemPtr dest, LIBDEF_ConstMemPtr source, size_t count);
extern LIBDEF_MemPtr memset  (LIBDEF_MemPtr buffer, int chr, size_t count);
extern void _memset_clear_8bitCount(LIBDEF_MemPtr buffer, unsigned char count);
  /* same as memset, but
     - no return value
     - memory is initialized with zero
     - count is a 8bit value and > 0
     ===> this makes it much more efficient!
   */

extern size_t  strlen  (LIBDEF_ConstStringPtr str);
extern LIBDEF_StringPtr strset  (LIBDEF_StringPtr str, int chr);
extern LIBDEF_StringPtr strcat  (LIBDEF_StringPtr str_d, LIBDEF_ConstStringPtr str_s);
extern LIBDEF_StringPtr strncat (LIBDEF_StringPtr str_d, LIBDEF_ConstStringPtr str_s, size_t count);
extern LIBDEF_StringPtr strcpy  (LIBDEF_StringPtr str_d, LIBDEF_ConstStringPtr str_s);
extern LIBDEF_StringPtr strncpy (LIBDEF_StringPtr str_d, LIBDEF_ConstStringPtr str_s, size_t count);
extern int     strcmp  (LIBDEF_ConstStringPtr str1, LIBDEF_ConstStringPtr str2);
extern int     strncmp (LIBDEF_ConstStringPtr str1, LIBDEF_ConstStringPtr str2, size_t count);
extern LIBDEF_StringPtr strchr  (LIBDEF_ConstStringPtr str, int chr);
extern LIBDEF_StringPtr strrchr (LIBDEF_ConstStringPtr str, int chr);
extern size_t  strspn  (LIBDEF_ConstStringPtr str1, LIBDEF_ConstStringPtr str2);
extern size_t  strcspn (LIBDEF_ConstStringPtr str1, LIBDEF_ConstStringPtr str2);
extern LIBDEF_StringPtr strpbrk (LIBDEF_ConstStringPtr str1, LIBDEF_ConstStringPtr str2);
extern LIBDEF_StringPtr strstr  (LIBDEF_ConstStringPtr str1, LIBDEF_ConstStringPtr str2);
extern LIBDEF_StringPtr strtok  (LIBDEF_StringPtr str1, LIBDEF_ConstStringPtr str2);
extern LIBDEF_StringPtr strerror(int errnum);
extern int strcoll(LIBDEF_ConstStringPtr string1, LIBDEF_ConstStringPtr string2);
extern size_t strxfrm(LIBDEF_StringPtr strDest, LIBDEF_ConstStringPtr strSource, size_t count);


#ifdef __cplusplus
 }
#endif

#endif

/*****************************************************/
/* end string.h */
