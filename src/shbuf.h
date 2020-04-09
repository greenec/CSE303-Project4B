#if !defined      (SEM___SHBUF)
#define            SEM___SHBUF

//
// Initialize.
//
int initBUF();
  
//
// Write to buffer.
//
int wBUF( const char * const s);

//
// Clean up.
//
int cuBUF();

#endif

