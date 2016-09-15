/*****************************************************
     time.h - ANSI-C library: time function
 ----------------------------------------------------
   Copyright (c) Metrowerks, Basel, Switzerland
               All rights reserved
                  Do not modify!
 *****************************************************/
/*
NOTE:
  This header file is provided for compatibility only,
  the implementation is fully hardware dependend.
*/

#ifndef __time_h
#define __time_h

#ifdef __cplusplus
extern "C" {
#endif

#include <hidef.h> /* #define CLOCKS_PER_SEC defined in hidef */
#include <stddef.h>


#define CLOCKS_PER_SEC 4000000
  /*!< \a CLOCKS_PER_SEC has to be user defined, depending on your timer/target. */


/*
 * Structure returned by gmtime and localtime calls.
 */
struct tm {
  int   tm_sec;
  int   tm_min;
  int   tm_hour;
  int   tm_mday;
  int   tm_mon;
  int   tm_year;
  int   tm_wday;
  int   tm_yday;
  int   tm_isdst;
  long  tm_gmtoff;
};

extern  char *      asctime   (const struct tm *time_rec);
extern  char *      ctime     (const time_t *time_val);
extern  clock_t     clock     (void);
extern  double      difftime  (time_t t1, time_t t2);
extern  struct tm * gmtime    (const time_t *time_val);
extern  struct tm * localtime (const time_t *time_val);
extern  time_t      mktime    (struct tm *time_rec);
extern  size_t      strftime  (char *s, size_t n, const char *format,
                               const struct tm *time_rec);
extern  time_t      time      (time_t *time_val);

#ifdef __cplusplus
 }
#endif

#endif  /* !__time_h */
