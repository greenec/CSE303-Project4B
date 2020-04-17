#if !defined      (SEM___SHBUF)
#define            SEM___SHBUF
#include <time.h>
//
// Initialize.
//
int initBUF();
  
//
// Write to buffer.
//
int wBUF(  char *  s, clock_t);

//
// Clean up.
//
int cuBUF();

#endif

