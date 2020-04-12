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

int main( int argc,  char ** argv)
{

   for(int i = 0 ; i < argc; i++){
      //printf("%s\n", argv[i]);
   }
   int retval = determineMode(argc, argv);
   printf("%d\n", retval);
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

int determineMode(int argc, char** argv){
   /*
   if t == 1 then run merge sort
   if t == 2 then run spin lock
   otherwise return 0 and exit 
   */

   int mode = 0;
   if(argc <= 1){
      return 0;
   }

   int c;
   char* cvalue = NULL;
   while ((c = getopt (argc, argv, "tnfp:")) != -1){
     switch (c) {
      case 't':
         cvalue = optarg;
         //mode = atoi(cvalue);
         fprintf(stderr, "%s\n", cvalue);
         if(mode == 0){
            //printf("Usage: <program name> ( -tx {-ny}| -p ){-f filename} i \n");
            //printf("Goodbye. \n");
            //exit(1);
            //return mode;
         }
         break;
      default:
         printf("Usage: <program name> ( -tx {-ny}| -p ){-f filename} i \n");
         printf("Goodbye. \n");
         exit(1);
      }
   }
   
return mode;



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
