#if !defined      (SEM___INCLUDED)
#define            SEM___INCLUDED

//
// Lehigh University
// CSE 303 Spring 2020
// Programming Assignment 4B

//
// Description:
// This is a translation of
// the semaphore class 
// into ANSI C
//


//
// Initialize.
//
void initSEM
(
	void *    v,
	long     k
	);


//
// Return the
// size of the
// internal
// memory needed.
//
int getSSizeSEM(); 

//
// pSEM (Wait)
//
int pSEM
(
	void *    v 
	);

//
// putSEM (set)
//
int setSEM
(
	int      x,
	void *    v 
	);

//
// vSEM (Signal)
//
void vSEM
(
	void *    v 
	);

//
// zSEM (Wait while
//       not 0)
//
void zSEM
(
	void *    v 
	);

//
// dSEM (delete 
//       object) 
void dSEM
(
	void *    v 
	);

#endif

