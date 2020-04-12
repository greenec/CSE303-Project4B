#include "mopt.h"
#include "sem.h"
#include "shbuf.h"
#include <stdio.h>
#include <stdlib.h>
//
// Lehigh University
// CSE 303 Spring 2020
// Programming Assignment 4
//
// Description:
//
//
void *  getVals( int argc,  char ** argv);


int main( int argc,  char ** argv)
{
 
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
   moptFree                          (v);
   return 1;
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
