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
void addOptP( char c,  char *  s, void * p);

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
int setO( char c,  int e, void * p);

//
// Get the
// error
// message.
//
char* getErrMsg(void * p);

//
// Get the
// argument
// for the 
// option.
//
char *  getArg( char c, void * p);

//
// Parse the
// command 
// line.
//
sType parse
(
    int                  argc, 
    char *  *  argv, 
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
int optExist( char c, void * p);

//
// Get the 
// parameter
// that follows
// the options.
//
char *  aVI(void * p);


//
// Free
// the memory
//
sType moptFree(void * p);

#endif
