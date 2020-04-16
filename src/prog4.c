#include "mopt.h"
#include "sem.h"
#include "shbuf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include <string.h>
#include <unistd.h>

//
// Lehigh University
// CSE 303 Spring 2020
// Programming Assignment 4
//
// Description:
//
//
void *  getVals( int argc,  char ** argv);
int determineMode(int argc, char** argv);
int getNumberOfThreads(int argc, char** argv);
void printUseage();

int main( int argc,  char ** argv)
{

   for(int i = 0 ; i < argc; i++){
      //printf("%s\n", argv[i]);
   }
   int mode = determineMode(argc, argv);

   if(mode != 1 && mode != 2){
      printUseage();
      return 0;
   }

   if(mode == 2){
      printf("%s\n", "Spin lock test" );
      //call spin lock 
   } else if (mode == 1){
      printf("%s\n", "Threaded merge sort" );
      int threads = getNumberOfThreads(argc, argv);
      printf("Threads: %d \n", threads );
      //parse more args 
   } else{
      //should never be here retval can only ever be 1 or 2
      printf("%s \n", "Error parsing CLI.");
      return 0;
   }




   /*
   void *  v = getVals(argc, argv);
      
   //
   // Output.
   //
   {
      char                         ch;
      for (ch = 'a'; ch <= 'z'; ch++)
         if (optExist(ch,v)+1)
         { 
             char *  pM =
                         getArg(ch,v);
            printf("opt %c found",ch);
            if (pM) printf  
                    (" parm = %s",pM);
            printf             ("\n");
         }
   }


   //
   // Get the ending
   // parameter.
   //
   {
       char *    pm =   aVI(v);
      printf         ("Parm = %s\n", pm);
   }

   //
   // Free the
   // memory
   //

   */
      //moptFree                          (v);
   return 1;
}

int getNumberOfThreads(int argc, char** argv){
   int threads = -1;
   int opt;
   while ((opt = getopt(argc, argv, "n:")) != -1) {
        switch (opt) {
            case 'n':
               threads = atoi(optarg);
               break;
            case 'p':
               return 
            default :  
               continue;
        }
   }
   return threads;
}

/*
char* getFileName(int argc, char** argv){
   char* fileName = NULL;
   return fileName;
}
*/



int determineMode(int argc, char** argv){
   /*
   if t == 1 then run merge sort
   if t == 2 then run spin lock
   otherwise return 0 and exit 
   */
   int mode = 0;
   if(argc <= 1){
      printUseage();
      return 0;
   }

   int opt;
   while ((opt = getopt(argc, argv, "t:")) != -1) {
        switch (opt) {
          case 't': 
            mode = atoi(optarg);
            return mode;
          default : printUseage(); return 0;
        }
   }
   return mode;
}



void printUseage(){
   printf("%s\n", "Usage: <program name> ( -tx {-ny}| -p ){-f filename} i" );
}




void *  getVals( int argc,  char ** argv)
{
   //
   // Initialize.
   //
   void *  v =         initialize();

   //
   // Set expected
   // options and
   // if a parameter
   // is expected.
   //
   setO                      ('a', 0, v);
   setO                      ('b', 0, v);
   setO                      ('g', 0, v);
   setO                      ('r', 1, v);
   setO                      ('s', 1, v);

   {

      //
      // Parse the
      // command line.
      //
     int pI =  parse(argc,argv,v);
     if(pI == -1)
     {
      printf      ("Parse failed!\n");
      exit                        (0);
   }
   return v;
}
}
