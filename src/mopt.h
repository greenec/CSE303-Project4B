#if !defined      (MOPT___INCLUDED)
#define            MOPT___INCLUDED
//
// Lehigh University
// CSE 303 Spring 2020
// Programming Assignment 4
//
// Description:
//
//

//
// Typedef the
// status values.
//
typedef enum 
{
   MOPT_ERROR = -1, 
   MOPT_CLEAR, 
   MOPT_INIT, 
   MOPT_PARSEOK
} sType;

//
// Register the 
// option and 
// parameter.
// (private)
//
static void addOptP(const char c, const char * const s, void * p);

//
// Initialize the 
// internals.
//
void * initialize();

//
// Register a
// valid option
// and if it 
// has a parameter.
//
const int setO(const char c, const int e, void * p);

//
// Get the
// error
// message.
//
const char * const getErrMsg(void * p);

//
// Get the
// argument
// for the 
// option.
//
const char * const getArg(const char c, void * p);

//
// Parse the
// command 
// line.
//
const sType parse
(
   const int                  argc, 
   const char * const * const argv, 
   void                        * p
);

//
// Was the
// option 
// argument
// on the
// command
// line?
//
const int optExist(const char c, void * p);

//
// Get the 
// parameter
// that follows
// the options.
//
const char * const aVI(void * p);


//
// Free
// the memory
//
const sType moptFree(void * p);

#endif
