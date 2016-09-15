/*****************************************************
     ctype.h - ANSI-C library: character handling
 ----------------------------------------------------
   Copyright (c) Metrowerks, Basel, Switzerland
               All rights reserved
                  Do not modify!
 *****************************************************/

#ifndef _H_CTYPE_  
#define _H_CTYPE_

#ifdef __cplusplus
extern "C" {
#endif

extern int isalnum  (int ch);
extern int isalpha  (int ch);
extern int iscntrl  (int ch);
extern int isdigit  (int ch);
extern int isgraph  (int ch);
extern int islower  (int ch);
extern int isprint  (int ch);
extern int ispunct  (int ch);
extern int isspace  (int ch);
extern int isupper  (int ch);
extern int isxdigit (int ch);

extern int tolower  (int ch);
extern int toupper  (int ch);


/**** All those functions (macros, actually) below use the 257byte table _ctype. The
      functions above don't use it and therefore need less RAM.
      In order to use the functions, you have to undefine the corresponding macro
      definition in your application after including the file 'ctype.h' */


extern const unsigned char  _ctype[];

#define  _U  ((unsigned char)((unsigned char)1<<0))  /* Upper case        */
#define  _L  ((unsigned char)((unsigned char)1<<1))  /* Lower case        */
#define  _N  ((unsigned char)((unsigned char)1<<2))  /* Numeral (digit)   */
#define  _S  ((unsigned char)((unsigned char)1<<3))  /* Spacing character */
#define  _P  ((unsigned char)((unsigned char)1<<4))  /* Punctuation       */
#define  _C  ((unsigned char)((unsigned char)1<<5))  /* Control character */
#define  _B  ((unsigned char)((unsigned char)1<<6))  /* Blank             */
#define  _X  ((unsigned char)((unsigned char)1<<7))  /* heXadecimal digit */

#ifdef __OPTIMIZE_FOR_TIME__

#define  isalnum(c)  (_ctype[(unsigned char)(c+1)] & (_U | _L | _N))
#define  isalpha(c)  (_ctype[(unsigned char)(c+1)] & (_U | _L))
#define  iscntrl(c)  (_ctype[(unsigned char)(c+1)] & _C)
#define  isdigit(c)  (_ctype[(unsigned char)(c+1)] & _N)
#define  isgraph(c)  (_ctype[(unsigned char)(c+1)] & (_P | _U | _L | _N))
#define  islower(c)  (_ctype[(unsigned char)(c+1)] & _L)
#define  isprint(c)  (_ctype[(unsigned char)(c+1)] & (_P | _U | _L | _N | _B))
#define  ispunct(c)  (_ctype[(unsigned char)(c+1)] & _P)
#define  isspace(c)  (_ctype[(unsigned char)(c+1)] & _S)
#define  isupper(c)  (_ctype[(unsigned char)(c+1)] & _U)
#define  isxdigit(c) (_ctype[(unsigned char)(c+1)] & _X)

#define  tolower(c)  (isupper(c) ? ((c) - 'A' + 'a') : (c))
#define  toupper(c)  (islower(c) ? ((c) - 'a' + 'A') : (c))

#define  isascii(c)  (!((c) & ~127))
#define  toascii(c)  (c & 127)

#endif /* __OPTIMIZE_FOR_TIME__ */

#ifdef __cplusplus
}
#endif

#endif
/*****************************************************/
/* end ctype.h */
