
#include <pthread.h>
#include <stdio.h>
#include <time.h>

#include "shbuf.h"

void* spinlockWrapper(void* args)
{
	int threadNum = *(int*) args;
	
	char message[50];
	
	sprintf(message, "I'm thread #%d", threadNum);
	
	while (1 == 1)
	{
		wBUF(message, clock());
	}
}

/*
 * Spinlock test function
 */
void spinlock_test(int numThreads)
{
	pthread_t threads[4];
	int spinlock_args[4];
	
	initBUF();
	
	wBUF("Before threads\n", clock());
		
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
		spinlock_args[i] = i + 1;
		
		if (pthread_create(&threads[i], NULL, spinlockWrapper, &spinlock_args[i]) != 0)
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
}
