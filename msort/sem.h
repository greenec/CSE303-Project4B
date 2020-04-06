#if !defined      (SEM___INCLUDED)
#define            SEM___INCLUDED

//
// Fairleigh Dickinson University
// CSCIxxxx    <semester><year>
// Programming Assignment x

//
// Description:
//

// This is a translation of
// the semaphore class 
// into ANSI C
//


//
// Initialize.
//
void initSEM
(
   void * const   v,
   const long     k
);
  

//
// Return the
// size of the
// internal
// memory needed.
//
const int getSSizeSEM(); 

//
// pSEM (Wait)
//
const int pSEM
(
   void * const   v 
);

//
// putSEM (set)
//
const int setSEM
(
   const int      x,
   void * const   v 
);

//
// vSEM (Signal)
//
void vSEM
(
   void * const   v 
);

//
// zSEM (Wait while
//       not 0)
//
void zSEM
(
   void * const   v 
);

//
// dSEM (delete 
//       object) 
void dSEM
(
   void * const   v 
);

#endif

