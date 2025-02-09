
#include <pthread.h>
#include <stdio.h>
#include <time.h>

#include "shbuf.h"

//
// Lehigh University
// CSE 303 Spring 2020
// Programming Assignment 4B
//

struct spinlock_args {
	int threadNum;
	int numMessages;
	int *messageCounter;
};

/*
 * Spinlock wrapper function
 * 
 * Checks to see if all messages are sent
 * and if not sends a message to the buffer (shbuf).
 */
void* spinlockWrapper(void *s)
{
	struct spinlock_args *args = s;
	
	int *messageCounter = args->messageCounter;
	
	char message[50];
	sprintf(message, "I'm thread #%d", args->threadNum);
	
	while (1) //run infinitely
	{
		(*messageCounter)++;
	
		// check if we've exceeded the total number of messages sent
		if ((*messageCounter) > args->numMessages)
		{
			pthread_exit(NULL); // if we have exceeded
		}
		
		// if we haven't exceeded write the message to the synchronized buffer
		wBUF(message, clock());
	}
}

/*
 * Spinlock test function
 * 
 * Arguments:
 * numThreads, the number of threads to use for the spinlock test given via input
 * numMessages, the number of messages to be periodically sent to the shbuf object
 */
void spinlock_test(int numThreads, int numMessages)
{
	// keep track of the threads that we create
	pthread_t threads[4];
	
	// holds the arguments that get passed to the function for each thread
	struct spinlock_args arguments[4];
	
	// each thread gets a reference to this counter so the program can return when it's sent all of its messages
	int messageCounter;
	
	initBUF();
	
	/*
	 * Create the threads
	 */
	for (int i = 0; i < numThreads; i++)
	{
		/*
		 * Set the thread number so the thread can print a message describing itself.
		 * Each argument needs its own space in memory because if a thread isn't ready
		 * until after we've created the the thread before it, they will have duplicate arguments.
		 */
		arguments[i].threadNum = i + 1;
		arguments[i].messageCounter = &messageCounter;
		arguments[i].numMessages = numMessages;
		
		if (pthread_create(&threads[i], NULL, spinlockWrapper, &arguments[i]) != 0)
		{
			fprintf(stderr, "An error occurred while creating thread #%d for the spinlock test.", i);
			return;
		}
	}
	
	/*
	 * Join the threads
	 */
	for (int i = 0; i < numThreads; i++)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			fprintf(stderr, "An error occurred while joining thread #%d for the spinlock test.", i);
			return;
		}
	}
	fprintf(stdout, "While running the spinlock test %d messages were successfully sent to the shbuf object. \n", numMessages);
}
