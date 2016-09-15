/******************************************************/
/**
* @file hidef.h
* Machine/compiler dependent declarations.
*/
/*----------------------------------------------------
   Copyright (c) Metrowerks, Basel, Switzerland
               All rights reserved
                  Do not modify!
 *****************************************************/

#ifndef _H_HIDEF_
#define _H_HIDEF_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdtypes.h>


#ifdef __RS08__

/**** Version for RS08 */

#pragma NO_STRING_CONSTR
  /* allow '#' in HLI (used for HALT_AND_QUIT). */

#pragma CONST_SEG __FAR_SEG .rodata   
  /*!< places constants into flash and accesses them with far accesses by default.
   *    Note that this does imply that non qualified pointers cannot be used to access constants.
   */

#define CONVERT_TO_PAGED(addr) (((addr) != 0) ? ((((addr)>>6)<<8) | ((addr) & 0x3F) | 0xC0) : (0))
  /*!< macro to convert a 14 bit address to its paged address representation 
   *   The low byte of a paged addresses is in the page window area from 0xC0 to 0xFF, the high byte
   *   represents the value to be loaded into PAGESEL.
   *   The input address must be in the 0..0x3FFF range.
   *   Note that this macro is only applicable to compile-time constants, not to link time constants (relocations)
   *   or even to variables.
   */    
   
#define CONVERT_FROM_PAGED(addr) ((((addr)>>8)<<6) | ((addr) & 0x3F)) 
  /*!< macro to convert a paged address to a 14 bit address. Does the reverse of CONVERT_TO_PAGED
   *   The input address must be a legal paged address, so either 0 or in the 0bXXXXXXXX11YYYYYY format.
   *   Note that this macro is only applicable to compile-time constants, not to link time constants (relocations)
   *   or even to variables.
   */       

#define HALT              __asm CLRA; __asm BGND; __asm DC.B 0x40; __asm DC.W 0x4040; /* 0x404040: illegal opcode (to differ from "real" code)  */
  /*!< Allows to halt the simulator. 
   *   (Note: may not be supported by P&E Simulator)
   */

#define HALTX(x)          __asm LDA x; __asm BGND; __asm DC.B 0x40; __asm DC.W 0x4040;
  /*!< Macro to halt the simulator and to let the simulator perform an action (argument \a x), useful for automated testing.
   *   (Note: may not be supported by P&E Simulator)
   */

  /*lint -estring(961, "'#/##' operator used") , not a function-like macro (besides, '#' is used in HLI as an operator - see pragma NO_STRING_CONSTR above) */
#define HALT_AND_QUIT      HALTX(#32)
  /*lint +estring(961, "'#/##' operator used") */
  /*!< Macro to halt the simulator and to close it (exit), useful for automated testing.
   *   (Note: may not be supported by P&E Simulator)
   */

#define EnableInterrupts  /* __asm CLI; */
  /*!< Macro to enable all interrupts. 
   *   As the RS08 does not has direct interrupts it evaluates to nothing. 
   *   Exists to increase HC08 compatibility
   */

#define DisableInterrupts /* __asm SEI; */
  /*!< Macro to disable all interrupts.
   *   As the RS08 does not has direct interrupts it evaluates to nothing.
   *   Exists to increase HC08 compatibility
   */

extern char __SEG_END_SSTACK[];
  /*!< Declaration of a special linker symbol for the stack end, assumes a linker version of at least V5.0.10. Used for INIT_SP_FROM_STARTUP_DESC(). */

#define INIT_SP_FROM_STARTUP_DESC() /* __asm LDHX @__SEG_END_SSTACK; __asm TXS; */
  /*!< Macro to initialize the stack pointer with the end of the stack segment. */

#define _FAR __far
  /*!< _FAR is used instead of \a __far for backward compatibility. */
#define NEAR   __near
  /*!< NEAR is used instead of \a __near for backward compatibility. */
#define _NEAR  __near
  /*!< _NEAR is used instead of \a __near for backward compatibility. */

#define _SRS_ADR     0x200  
  /*!< address of SRS register */
#define __PAGESEL    0x1F
  /*!< PAGESEL register. Used for paging in the 0xC0..0xFF area */

#ifndef _FEED_COP
  /*lint -estring(961, "'#/##' operator used") , '#' used in HLI as an operator (see pragma NO_STRING_CONSTR above) */
#define _FEED_COP { __asm MOV #%HIGH_6_13(_SRS_ADR),__PAGESEL ; __asm  STA %MAP_ADDR_6(_SRS_ADR) ; }
  /*lint +estring(961, "'#/##' operator used") */
#endif


#else /* HC08 */


/**** Version for MC68HC08 */

#pragma NO_STRING_CONSTR
/* allow '#' in HLI (used for HALT_AND_QUIT). */

#define HALT               __asm CLRA; __asm SWI ! {A}, {A+HX+SR};
  /*!< Allows to halt the simulator. */
#define HALTX(x)           __asm LDA x; __asm SWI ! {A}, {A+HX+SR};
  /*!< Macro to halt the simulator and to let the simulator perform an action (argument \a x), useful for automated testing.*/
  /*lint -estring(961, "'#/##' operator used") , not a function-like macro (besides, '#' is used in HLI as an operator - see pragma NO_STRING_CONSTR above) */
#define HALT_AND_QUIT      HALTX(#32)
  /*lint +estring(961, "'#/##' operator used") */
  /*!< Macro to halt the simulator and to close it (exit), useful for automated testing.*/
#define EnableInterrupts   __asm CLI;
  /*!< Macro to enable all interrupts. */
#define DisableInterrupts  __asm SEI;
  /*!< Macro to disable all interrupts. */

extern char __SEG_END_SSTACK[];
  /*!< Declaration of a special linker symbol for the stack end, assumes a linker version of at least V5.0.10. Used for INIT_SP_FROM_STARTUP_DESC(). */

#define INIT_SP_FROM_STARTUP_DESC() __asm LDHX @__SEG_END_SSTACK; __asm TXS;
  /*!< Macro to initialize the stack pointer with the end of the stack segment. */

#if !defined(__TINY__)
  #define FAR
  /*!< For tiny memory model, \a FAR is used as segment modifier */
#endif

#define _FAR __far
  /*!< _FAR is used instead of \a __far for backward compatibility. */
#define NEAR   __near
  /*!< NEAR is used instead of \a __near for backward compatibility. */
#define _NEAR  __near
  /*!< _NEAR is used instead of \a __near for backward compatibility. */

/* COP (Computer Operates Properly) macros */
#if defined(__HCS08__)
/* HCS08 */
#define _SRS_ADR       0x1800
  /*!< address of the SRS HCS08 register */

/*lint -estring(961, "'#/##' operator used") , '#' used in HLI as an operator (see pragma NO_STRING_CONSTR above) */
#define _SRS_ACCESS(_SRS_PATTERN) { __asm LDA #_SRS_PATTERN; __asm STA _SRS_ADR; }
/*lint +estring(961, "'#/##' operator used") */
 /*!< access macro to SRS. */
#define _FEED_COP()     {__asm PSHA; _SRS_ACCESS(0x55); _SRS_ACCESS(0xAA); __asm PULA;} /* Feed the watch-dog */
  /*!< This macro is used in the startup code to feed the COP 
       The DZ series (any maybe other future ones) now needs 2 accesses with a 55/AA pattern to feed the watchdog.
       The previous HCS08 did need any write to SRS to feed the COP.
       So to avoid derivative specifics, we just use the new pattern for all.
    */

#else /* defined(__HCS08__) */
/* HC08 */
#define _COPCTL_ADR 0xFFFF
  /*!< address of the COPCTL register */
#define _FEED_COP()     {__asm sta _COPCTL_ADR;}
  /*!< This macro is used in the startup code to feed the COP */
#endif /* defined(__HCS08__) */

#endif  /* #ifdef __RS08__ */

#ifdef __cplusplus
 }
#endif

#endif

/*****************************************************/
/* end hidef.h */
