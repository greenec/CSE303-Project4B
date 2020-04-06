#include "mopt.h"
#include <stdio.h>
#include <stdlib.h>
//
// Fairleigh Dickinson University
// CSCIxxxx    <semester><year>
// Programming Assignment x
//
// Description:
//
//
void * const getVals(const int argc, const char ** argv);


main(const int argc, const char ** argv)
{
 
   void * const v = getVals(argc, argv);
      
   //
   // Output.
   //
   {
      char                         ch;
      for (ch = 'a'; ch <= 'z'; ch++)
         if (optExist(ch,v)+1)
         { 
            const char * const pM =
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
      const char * const   pm =   aVI(v);
      printf         ("Parm = %s\n", pm);
   }

   //
   // Free the
   // memory
   //
   moptFree                          (v);
}


void * const getVals(const int argc, const char ** argv)
{
   //
   // Initialize.
   //
   void * const v =         initialize();

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
      const int pI =  parse(argc,argv,v);
      if(pI == -1)
      {
         printf      ("Parse failed!\n");
         exit                        (0);
      }
      return v;
   }
}
