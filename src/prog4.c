
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "mopt.h"
#include "sem.h"
#include "shbuf.h"
#include "spinlock.h"

#include "threadedMergeSort.c"

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
   int stdout;
} Commands;



void determineMode(int argc, char** argv, struct Commands*);
int validateArguments(struct Commands*);
void printUseage();



int main(int argc, char** argv)
{
	for (int i = 0 ; i < argc; i++)
	{
		// printf("%s\n", argv[i]);
	}

	struct Commands* command = (struct Commands*) malloc (sizeof(Commands));
	determineMode(argc, argv, command);
	printf(" Mode: %d \n", command->mode  );
	printf(" Threads: %d \n", command->threads  );
	printf(" Messages: %d \n", command->messages  );
	printf(" Mode: %d \n", command->messages  );
	printf(" Filename: %s \n", command->filename  );

	int valid = validateArguments(command);
	if (!valid)
	{
		printUseage();
		return 0;
	}


	if(command->mode == 1)
	{
		int ret = threadedMergeSort(argc, argv);
	}
	else if (command->mode == 2)
	{
		spinlock_test(command->threads);
	}

	free(command);
	
	return 1;
}


int validateArguments(struct Commands* command){
   if(command->mode == 1){
      if(command->userEntry != 0){
         return 0;
      }
      if(command->threads != 0){
         return 0;
      }
      return 1;
   } else if(command->mode == 2){
      if(command->threads < 1 || command->threads > 4){
         return 0;
      } else{
         return 1;
      }
   } else{
      if(command->userEntry == 1){
         printf("Enter mode: "); 
         scanf("%d", &command->mode);
         if(command->mode == 2){
            printf("Enter number of threads: "); 
            scanf("%d", &command->threads);
            if(command->threads > 1 && command->threads < 5){
               return 1;
            }
         }  else if(command->mode == 1 ){
            return 1;
         }
         else{
            return 0;
         }
      } else{
         return 0;
      }
   }
   if(command->messages <= 0){
      return 0;
   }
   return 1;
}




void determineMode(int argc, char** argv, struct Commands* command){
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
            case 'p':
               command->userEntry = 1;
               return;
            case 'i':
               command->messages = atoi(optarg);
               break;
            case 'f':
               command->filename = optarg;
               command->stdout = 1;
               break;
            default : printUseage(); return;
        }
   }

}



void printUseage(){
   printf("%s\n", "Usage: <program name> ( -tx {-ny}| -p ){-f filename} i" );
}



