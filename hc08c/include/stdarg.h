#ifndef _H_STDARG_
#define _H_STDARG_


#ifdef __HIWARE__
  /*****************************************************
      stdarg.h - ANSI-C library: standard arguments
   ----------------------------------------------------
     Copyright (c) Metrowerks, Basel, Switzerland
                 All rights reserved
                    Do not modify!
   *****************************************************/

  #ifdef __cplusplus
  extern "C" {
  #endif
  
  #if defined(__PPC__)
    typedef struct {
	    char gpr;
	    char fpr;
	    char reserved[2];
	    char *input_arg_area;
	    char *reg_save_area;
    } va_list[1];
  #else
  /* va_list: defines the type of the pointer which will point each unnamed argument. */
  typedef char *va_list;
  #endif

  /* va_start: makes 'ap' pointing the first unnamed argument. */
  #if defined(__MCORE__)
    #define __va_rounded_size(type) (((sizeof(type) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))
    #define va_start(ap,v)          ((ap) = (char *)((long)& v & ~3) + __va_rounded_size(v))
  #elif defined(__M68K__)
    /* for M68k, if a char is passed as first argument for an open argument list, 2 bytes are on the stack! */
    #define va_start(ap,v) ((sizeof(v) == 1) ? ((ap) = (char *)&v + 2) : ((ap) = (char *)&v + sizeof(v)))
  #elif defined(__PPC__)
    extern void __va_start__(va_list);
    #define va_start(ap,v)          ((void)v, __va_start__(ap))  /* __va_start__ is a built in function */
  #elif defined(__RS08__) || defined(__ST7__) || defined(__HC05__) || defined(__ST19X__)
    #define va_start_stack(ap,v)      ((ap) = (char *)&v + sizeof(v))
    #define va_start_overlap(ap,v)    ((ap) = *((char **)((char *)(&v)+sizeof(v))) )

    #if defined(__RS08__) || !defined(__SICG__) || defined(__SHORT_OVERLAP__) || defined(__LONG_OVERLAP__)
      #define va_start va_start_overlap
    #else
      #define va_start va_start_stack
    #endif
  #else
    #define va_start(ap,v)          ((ap) = (char *)&v + sizeof(v))
  #endif
  /* NOTE: 

      look at the following example:
    
      char f(int n, ...) {
        char c=0;
        va_list l;
        va_start(l, n);
        if (n > 0) {
          c= va_arg(l, int);    // (*)
        } 
        return c; 
      }
    
      void main(void) {
        char c=2;
        if (f(c) != 2) Error();
      }
    
     In the line (*) va_arg must be called with int, not with char.
     Because of the default argument promotion rules of C,
     for integral types at least an int is passed and
     for floating types at least a double is passed.
  */      

  /* va_arg: updates 'ap' pointer according to 'type'.
             returns value of previous element. */
  #if defined (__HC16__)
    /**** If sizeof (type) == 1, it must be a 1-byte-struct (chars always are
          passed as integers). These are in the LSB of the word, i.e. we first
          gotta skip one byte. */
   
    #define __va(ap, type)     (((type *)((ap) += sizeof (type)))[-1])
  
    #define va_arg(ap, type)   ((sizeof (type) & 1) ?       \
                                ((ap)++, __va (ap, type)) : \
                                __va (ap, type))
  #elif defined (__MCORE__)
      /* since the ABI 1.0:
              - we have to pass parameters with, at least, 8 bytes alignment in EVEN registers.
              - we have to garanty that stack pointer is always multiple of eight. 
              - We use Big Endian (a char is at highest address (least significant) byte of a word).
         ==> this means we just have to: - make the 'ap' address multiple of eight for 8byte aligned objects
                                         - update the 'ap' pointer
                                         - return value of the previous element */
    #define va_arg(ap,type)    (((__alignof__(type)>=8) ? ((ap) = (char *)(((int)(ap) + __alignof__(type) - 1) & (~(__alignof__(type) - 1)))) : 0),\
                                ((ap) += __va_rounded_size(type)),\
                                (((type *) (ap))[-1]))
  #elif defined(__M68K__)
    #define va_arg(ap, type)   ((__va_sizeof__ (type) == 1) ?       \
                                ((ap)++, (((type *)((ap) += __va_sizeof__ (type)))[-2])) : \
                                (((type *)((ap) += __va_sizeof__ (type)))[-1]))
  #elif defined(__PPC__)
    extern void* __va_arg(void*, int);  /* defined in rtsppc.c */
    #define va_arg(ap, type)	(sizeof(type) < 4 ? (*((type *)((char *)&(*((int*)__va_arg(ap, __va_arg_type__(type)))) + (4 - sizeof(type))))) : (*((type*)__va_arg(ap, __va_arg_type__(type)))))
  #elif defined(__XGATE__) 
    /* 1 byte large types are pushed with a 16 bit push instruction */
    #define va_arg(ap, type)   ((sizeof(type) < 2U) ? ((type *)((ap) += 2U))[-1] : ((type *)((ap) += __va_sizeof__(type)))[-1])
  #elif defined(__S12LISA__)
    #define va_arg(ap, type)   (((type *)((ap) += sizeof(type)))[-1])
  #else
    #define va_arg(ap, type)   (((type *)((ap) += __va_sizeof__(type)))[-1])
  #endif


  #if defined(__PPC__)
    #define va_end(ap)
  #elif defined(__HC08__) || defined(__RS08__) || defined(__HC12__) || defined(__XGATE__)
    /* va_end: sets the 'ap' pointer to NULL. */
    /*lint -e773 va_end is never used as an expression operand*/
    #define va_end(ap) ap = (va_list)0
    /*lint +e773 */
  #else
    #define va_end(ap) 0      
  #endif

  #ifdef __cplusplus
  }
  #endif

  /*****************************************************/
  /* end stdarg.h */
#elif !defined(__HIWARE__) && defined(__MWERKS__) && defined(__MCORE__) /* Metrowerks M-CORE */

    #include <cstdarg>

    #if defined(__cplusplus) && defined(_MSL_USING_NAMESPACE)
	    using namespace std;
    #endif

#elif !defined(__HIWARE__) && defined(__MWERKS__) && defined(__PPC__) /* Metrowerks PPC */

    #include <cstdarg>

    #if defined(__cplusplus) && defined(_MSL_USING_NAMESPACE)
	    using namespace std;
    #endif

#else
  #error
#endif

#endif

