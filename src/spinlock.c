
#include <pthread.h>
#include <stdio.h>

void* spinlockWrapper(void* args)
{
	printf("I'm a thread!\n");
}

/*
 * Spinlock test function
 */
void spinlock_test(int numThreads)
{
	pthread_t t1 = 0;
	
	printf("Before threads\n");
	
	pthread_create(&t1, NULL, spinlockWrapper, NULL);
	
	pthread_join(t1, NULL);
}
