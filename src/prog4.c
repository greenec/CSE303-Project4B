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

typedef struct Commands {
   int mode;
   int threads;
   char* filename;
   int userEntry;
   int messages;
} Commands;

//
void *  getVals( int argc,  char ** argv);
void determineMode(int argc, char** argv, struct Commands*);
int getNumberOfThreads(int argc, char** argv);
void printUseage();




int main( int argc,  char ** argv)
{

   for(int i = 0 ; i < argc; i++){
      //printf("%s\n", argv[i]);
   }

   struct Commands* command = (struct Commands*) malloc (sizeof(Commands));
   determineMode(argc, argv, command);
   printf(" Mode: %d \n", command->mode  );
   printf(" Threads: %d \n", command->threads  );
   printf(" Mode: %d \n", command->userEntry  );
   printf(" Mode: %d \n", command->messages  );








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




void determineMode(int argc, char** argv, struct Commands* command){
   /*
   if t == 1 then run merge sort
   if t == 2 then run spin lock
   otherwise return 0 and exit 
   */

   if(argc <= 1){
      printUseage();
      return;
   }

   int opt;
   while ((opt = getopt(argc, argv, "pt:n:f:i")) != -1) {
        switch (opt) {
            case 't': 
               command->mode = atoi(optarg);
               break;
            case 'n':
               command->threads = atoi(optarg);
               break;
            case 'f':
               command->filename = optarg;
               break;
            case 'p':
               command->userEntry = 1;
               return;
            case 'i':
               command->messages = atoi(optarg);
               break;
            default : printUseage(); return;
        }
   }

   if(command->mode ==3 ){

   }

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
