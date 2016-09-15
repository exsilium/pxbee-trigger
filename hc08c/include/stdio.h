/*****************************************************
    stdio.h - ANSI-C library: standard I/O
 ----------------------------------------------------
   Copyright (c) Metrowerks, Basel, Switzerland
               All rights reserved
                  Do not modify!
 *****************************************************/

#ifndef _H_STDIO_
#define _H_STDIO_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <libdefs.h>
#include <errno.h>

#ifdef __XGATE__ /* XGATE code can be linked with HCS12X code, but then the variable has to be different from the HCS12X one */
  #define channels    _X_channels /* XGATE channel */
#endif /* __XGATE__ */

/* Standalone FILE structure

   NOTE: This is designed for simple I/O in an embedded system.
         You should modify this if actual files or extra stream
         control is required.
   NOTE: "fpos_t position;" is not included in this structure.
 */

typedef struct chnl {
  char *channel_name;        /* Name of I/O channel             */
  char *port_addr;           /* Address of port                 */
  char  flags;               /* STTY style flags                */
  char  lastchar;            /* Last character for ungetc       */
  int   (*open_channel)();   /* routine for port initialization */
  int   (*close_channel)();  /* routine for port shutdown       */
  int   (*read_channel)();   /* routine for port reads          */
  int   (*write_channel)();  /* routine for port writes         */
} FILE;

extern FILE channels[1];

typedef long      fpos_t;

#define  stderr   (&channels[0])
#define  stdin    (&channels[0])
#define  stdout   (&channels[0])

#define _IOEOF    (1<<0)
#define _IOERR    (1<<1)
#define _IOCHR    (1<<2)

#define _IOFBF         0
#define _IOLBF         1
#define _IONBF         2

#define BUFSIZ       255
#define EOF         (-1)
#define FOPEN_MAX      8
#define FILENAME_MAX  16

#define L_tmpnam      17

#ifndef SEEK_SET
  #define SEEK_END       0
  #define SEEK_CUR       1
  #define SEEK_SET       2
#endif
  
#define TMP_MAX        1

/*lint -e683 inhibit warning on standard function being #define'd */
#define getc(s)     fgetc (s)
int fputc(int c, FILE *stream);
#define putc(c,s)   (*((s)->write_channel))(c)
#define getchar()   fgetc (stdin)
#define putchar(c)  fputc ((c), stdout)

#define feof(s)     ((s)->flags & _IOEOF)
#define ferror(s)   ((s)->flags & _IOERR)
#define clearerr(s) ((void) ((s)->flags &= ~(_IOERR | _IOEOF)))

#define far_clearerr   clearerr
#define far_ferror     ferror
#define far_feof       feof
#define far_fputc      fputc
#define far_putc       putc
#define far_getchar()  far_fgetc (stdin)
#define far_putchar(c) far_fputc ((c), stdout)

#define far_perror(s)\
  (far_fputs ((s), stderr),\
   far_fputc (':', stderr), far_fputc (' ', stderr),\
   far_fputs (strerror (errno), stderr))

#define perror(s)\
  (fputs((s),stderr), \
   fputs(": ",stderr), \
   fputs(strerror(errno),stderr))
/*lint +e683 */   

/**** Prototypes for user defined functions: If you need file I/O, implement it! */
#if 1
  /* note: the following defines are for compatibility only. There is now an
           easier way to set up the library to deal with far data:
           you can configure this in the libdefs.h, e.g for
           LIBDEF_MemPtr or LIBDEF_ConstMemPtr.
           the following defines may be removed in a future version. */
    #define far_fopen       fopen
    #define far_fclose      fclose
    #define far_freopen     freopen    
    #define far_remove      remove
    #define far_rename      rename    
    #define far_tmpfile     tmpfile
    #define far_tmpnam      tmpnam
    #define far_fflush      fflush
    #define far_setbuf      setbuf
    #define far_setvbuf     setvbuf
    #define far_fgetpos     fgetpos
    #define far_fseek       fseek
    #define far_fsetpos     fsetpos
    #define far_ftell       ftell
    #define far_rewind      rewind
    #define far_fgetc       fgetc
    #define far_fread       fread
    #define far_fwrite      fwrite
    #define far_fgets       fgets
    #define far_fputs       fputs
    #define far_ungetc      ungetc    
    #define far_gets        gets
    #define far_vsscanf     vsscanf
    #define far_puts        puts
    #define far_vfprintf    vfprintf
    #define far_vsprintf    vsprintf
    #define far_fscanf      fscanf
    #define far_scanf       scanf
    #define far_sscanf      sscanf
    #define far_printf      printf
    #define far_fprintf     fprintf
    #define far_sprintf     sprintf
#endif

extern FILE *   fopen   (LIBDEF_ConstStringPtr name, LIBDEF_ConstStringPtr mode);
extern int      fsetpos (FILE * f, const fpos_t *LIBDEF_CONST_DPTRQ pos);
extern int      scanf(LIBDEF_ConstStringPtr s, ...);                                     /*lint !e960 MISRA 16.1 REQ, standard library function implementation */
extern int      sscanf(LIBDEF_ConstStringPtr s, LIBDEF_ConstStringPtr format, ...);      /*lint !e960 MISRA 16.1 REQ, standard library function implementation */
extern int      vsscanf(LIBDEF_ConstStringPtr s, LIBDEF_ConstStringPtr format, va_list args);
extern int      puts(LIBDEF_ConstStringPtr s);
  /* The puts() function writes string to the standard output stream stdout,
     replacing the string’s terminating null character ('\0') with a newline character ('\n')
     in the output stream.
     returns a nonnegative value if successful. If puts fails it returns EOF */
extern int      printf(LIBDEF_ConstStringPtr s, ...);                                     /*lint !e960 MISRA 16.1 REQ, standard library function implementation */
extern int      fprintf(FILE *f, LIBDEF_ConstStringPtr, ...);                             /*lint !e960 MISRA 16.1 REQ, standard library function implementation */
extern int      vfprintf(FILE *f, LIBDEF_ConstStringPtr s, va_list args);
extern int      sprintf(LIBDEF_StringPtr s, LIBDEF_ConstStringPtr format, ...);           /*lint !e960 MISRA 16.1 REQ, standard library function implementation */
extern int      vsprintf(LIBDEF_StringPtr s, LIBDEF_ConstStringPtr format, va_list args);

extern void set_printf(void (*f)(char)); /*lint !e960 MISRA 16.3 REQ, message reported for a function pointer parameter */
  /* installs a handler function to write to the terminal */
extern int vprintf(LIBDEF_ConstStringPtr format, va_list args);

#if LIBDEF_REENTRANT_PRINTF
  /* reentrant version of printf */
  typedef void (*__printf_callback)(char, struct __print_buf*);

  struct __print_buf {
    __printf_callback outc;
  };

int __vprintf_desc(LIBDEF_ConstStringPtr format, va_list args, struct __print_buf* desc);   /* reentrant version of printf */
/* the outc fields in the desc parameter is called with every character */
/* the second parameter of outc is desc itself */ 

#endif


extern int      fclose  (FILE * f);
extern FILE *   freopen (const char * name, const char * mode, FILE * f);

extern int      remove  (LIBDEF_ConstStringPtr name);
extern int      rename  (const char * old_name, const char * new_name);

#define  fpos_t  long   /* file position variable */

extern FILE *   tmpfile (void);
extern char *   tmpnam  (char * name);
extern int      fflush  (FILE * f);
extern void     setbuf  (FILE * f, char * buf);
extern int      setvbuf (FILE * f, char * buf, int mode, size_t size);
extern int      fgetpos (FILE * f, fpos_t *pos);
extern int      fseek   (FILE * f, long offset, int mode);
extern long int ftell   (FILE * f);
extern void     rewind  (FILE * f);
extern int      fgetc   (FILE * f);
extern size_t   fread   (void * buf, size_t size, size_t n, FILE * f);
extern size_t   fwrite  (const void * buf, size_t size, size_t n, FILE * f);
extern LIBDEF_StringPtr fgets   (LIBDEF_StringPtr s, int n, FILE * f);
extern int      fputs   (LIBDEF_ConstStringPtr s, FILE * f);
extern int      fscanf  (FILE * f, const char * s, ...); /*lint !e960 MISRA 16.1 REQ, standard library function implementation */
extern int      ungetc  (int c, FILE * f);

extern LIBDEF_StringPtr gets(LIBDEF_StringPtr s);
/* The gets() function reads a line from the standard input stream stdin and stores it in buffer s.
   The line consists of all characters up to and including the first newline character ('\n').
   gets() then replaces the newline character with a null character ('\0') before returning
   the line. In contrast, the fgets function retains the newline character. */

#ifdef __cplusplus
}
#endif

#endif

/*****************************************************/
/* end stdio.h */
