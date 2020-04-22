
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
// Programming Assignment 4B
//

/*
 * Members:
 *    Chris Doms
 *    Connor Greene
 *    Gabe Siegel
 *    Kareem Eleskandarani
 * 
 * Description:
 *    The program should accept a command line: <program name> (-tx -ny | -p) {-f filename} i
 *    Where x = 1 or 2.
 * 
 *    If x=1 run a threaded merge sort algorithm. 
 *    If x=2 run a spinlock test, where n = the number of threads, 1-4. 
 *    i is the number of messages each thread will output.
 * 
 *    If -p is given, the program will prompt the user for test 1 or 2, and the number of threads if 2 is selected.
 *    If -f filename is given a file, named filename, is opened and the report is written to filename. 
 *    If -f filename is not given the report should be written to stdout.
 *    If anything else is input (including if a -n value is given when x = 1), the following usage statement is output:
 *    Usage: <program name> ( -tx {-ny}| -p ){-f filename} i
 *    And exit the program. 
 * 
 *    If the -p option is given and the user enters anything besides a 1 or a 2, output an error message and exit. 
 *    If 2 is selected, prompt for the number of threads, 1-4. Again, exit if anything is entered besides 1, 2, 3 or 4.
 *    The spinlock test will run 1-4 pthreads, which will be while(1) loops testing a value, which never changes. 
 *    Periodically, each thread will send a string to the wBUF(.) function in shmem, which will timestamp and store the messages. 
 *    When cuBuf(.) is called, an informative report is output to stdout or to a file. 
 *    At the very least the program should output each time-stamped message in the order sent to the shbuf object 
 *    with at least one summary line at the end, providing some useful information about the test run.
 *    At this point, the program should exit.
 *    In order to prevent thread conflict only one thread may enter the shmem object’ functions at a time. 
 *    Access to shmem’s functions is protected via a semaphore (sem.h and sem.c supplied)
 */ 

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
	printf(" Filename: %s \n", command->filename  );

   if(command->filename != NULL){
      //redirect standard out to the new file
      freopen(command->filename, "a+", stdout); 
   }
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
		spinlock_test(command->threads, command->messages);
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
   while ((opt = getopt(argc, argv, "pt:n:f:i:")) != -1) {
        switch (opt) {
            case 't': // t2 value represents spinlock test and t1 the threaded mergesort
               command->mode = atoi(optarg);
               break;
            case 'n': // n represents the number of threads from 1 to 4 in the spinlock test, n3 is 3 threads
               command->threads = atoi(optarg);
               break;
            case 'p': // p represents a prompt to ask whether t1 or t2
               command->userEntry = 1;
               return;
            case 'i': // i is the number of messages each thread will output
               command->messages = atoi(optarg);
               break;
            case 'f': // f is a filename which is opened and the report is written to filename.
               command->filename = optarg;
               command->stdout = 1;
               break;
            default : printUseage(); return;
        }
   }

}


// The command line the program should accept
void printUseage(){
   printf("%s\n", "Usage: <program name> ( -tx {-ny}| -p ){-f filename} i" );
}



