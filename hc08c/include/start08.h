/******************************************************************************
  FILE    : start08.h
  PURPOSE : datastructures for startup
  LANGUAGE: ANSI-C
*/
/********************************************************************************/

#ifndef START08_H
#define START08_H

#ifdef __cplusplus
extern "C" {
#endif

#include <hidef.h>

/*
  the following data structures contain the data needed to
  initialize the processor and memory 
*/

typedef struct{
  unsigned char *_FAR beg;
  int size;      /* [beg..beg+size] */
} _Range;

typedef struct _Copy{
  int size;
  unsigned char *_FAR dest;
} _Copy;

typedef void (*_PFunc)(void);

typedef struct _LibInit{
  _PFunc  *startup;      /* address of startup desc */
} _LibInit;

typedef struct _Cpp{
  _PFunc  initFunc;      /* address of init function */
} _Cpp;

#define STARTUP_FLAGS_NONE          0
#define STARTUP_FLAGS_ROM_LIB       (1<<0)  /* if module is a ROM library */
#define STARTUP_FLAGS_NOT_INIT_SP   (1<<1)  /* if stack pointer has not to be initialized */


#pragma DATA_SEG FAR _STARTUP

#ifdef __ELF_OBJECT_FILE_FORMAT__

/* ELF/DWARF object file format */

/* attention: the linker scans the debug information for these structures */
/* to obtain the available fields and their sizes. */
/* So don't change the names in this file. */

extern struct _tagStartup {
#ifndef __NO_FLAGS_OFFSET
     unsigned char   flags;                  /* STARTUP_FLAGS_xxx */
#endif
#ifndef __NO_MAIN_OFFSET
     _PFunc          main;                   /* top level procedure of user program */
#endif
     unsigned short  nofZeroOuts;            /* number of zero out ranges */
     _Range          *_FAR pZeroOut;         /* vector of ranges with nofZeroOuts elements */
     _Copy           *_FAR toCopyDownBeg;    /* ROM-address where copy down-data begins */
#if 0  /* switch on to implement ROM libraries */
     unsigned short  nofLibInits;            /* number of library startup descriptors */
     _LibInit        *_FAR libInits;         /* vector of pointers to library startup descriptors */
#endif
#if defined(__cplusplus)
     unsigned short  nofInitBodies;          /* number of init functions for C++ constructors */
     _Cpp            *_FAR initBodies;       /* vector of function pointers to init functions for C++ constructors */
#endif
} _startupData;

#else

extern struct _tagStartup{
     unsigned   flags;
    _PFunc      main;            /* top procedure of user program */
     unsigned   dataPage;        /* page where data allocation begins */
     long       stackOffset;
     int        nofZeroOuts;
    _Range      *_FAR pZeroOut;  /* pZeroOut is a vector of ranges with nofZeroOuts elements */
     long       toCopyDownBeg;   /* ROM-address where copy down-data begins */
    _PFunc      *_FAR mInits;    /* mInits is a vector of function pointers, terminated by 0 */
    _PFunc      *_FAR libInits;  /* libInits is a vector of function pointers, terminated by 0x0000FFFF */
} _startupData;  

#endif  

#pragma DATA_SEG DEFAULT

#pragma push
#include "non_bank.sgm" /* _Startup is referred by the reset vector -> must be non banked. */

extern void _Startup(void);    /* execution begins in this procedure */
/*-------------------------------------------------------------------*/

#pragma pop

#ifdef __cplusplus
 }
#endif

#endif
