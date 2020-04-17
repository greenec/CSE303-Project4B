/*
** Program 4 -- W Phillips 04705804
** CSE 7343 Summer 2006
**
** This program was compiled and run on neo.engr.smu.edu
** and on fermi.engr.smu.edu.
**
**
** To compile and run:
**     cc -pthread -o prog4 prog4.c 
**     ./prog4 <parm>  Any parm provided results in quicksort
**                     being used. Otherwise shellsort is used.
**                     The value you are prompted for is n --
**                     the size of the small array.  
*/
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "sem.h"
#include "shbuf.h"

//#include "shbuf.c"

/*
** On most Linux machines you can go up
** to ten million.
*/
enum  { MAXARRAYSIZE  =        30000000 };
enum  { MAX2ARRAYSIZE = MAXARRAYSIZE*2 };
enum  { MAXLINE       =             20 };
enum  { PROMPTSIZE    =             80 };

/*
** Change this to 0 to dump the contents
** of the sorted arrays. I would
** recommend keeping n small if you do
** this.
*/
enum  { DUMPINHIBIT   =              1 };

/*
** Instead of mallocing I decided to just make
** the arrays the max size which is what we'd
** have to do in the max case anyway.  For
** multiple runs I figured this would work out
** better instead of doing all the dynamic
** allocations and frees.  It could make for
** a fairer test.  
*/
      int    smallArray1[MAXARRAYSIZE];
      int    smallArray2[MAXARRAYSIZE];
      int    smallArray3[MAXARRAYSIZE];
      int    smallArray4[MAXARRAYSIZE];
      int    largeArray1[MAX2ARRAYSIZE];
      int    largeArray2[MAX2ARRAYSIZE];
      int    largeArray3[MAX2ARRAYSIZE];

      /*
      ** This parameter gets set to 1 if the user 
      ** enters any parameter when this program is
      ** run.  If that is the case, quicksort is
      ** used instead of shell sort.
      */
      int    useQsort     = 0; 
    
 double mS_PER_SEC   = 1000000.0;

/*
** This is the quicksort algorithm. Since all intermediate
** variables are defined locally (on the stack) it is thread-
** safe.
** 
*/
int partition(int *  a,  int l,  int r,  char * s) 
{
     int pivot = a[l];
          int     i = l; 
          int     j = r+1;
          int     t;

    while(1)
    {
    	double mS_PER_CLOCK = mS_PER_SEC/CLOCKS_PER_SEC;
		clock_t   t1 = clock();
        char message[5000] = "Thread: ";
        strcat(message, s);


        //strcat(message, total);
       // printf("%s\n" , message);

        wBUF(message, t1);
        //wBUF(s);
        //wBUF((char*)total);
       // wBUF("\n");
        do ++i; while((a[i]<=pivot) && (i<=r));
        do --j; while(a[j]>pivot );
        if(i>=j) break;
        t    = a[i]; 
        a[i] = a[j]; 
        a[j] = t;
    }
    t    = a[l]; 
    a[l] = a[j]; 
    a[j] = t;
    return j;
}

void qSortArray(int *  a,  int l,  int r,  char * s)
{
    if( l < r ) 
    {
         int j = partition( a, l, r, s );
        qSortArray(a,l,  j-1, s );
        qSortArray(a,j+1,r  , s );
    }
}
/*
** END QUICKSORT ALOGORITHM
*/


/*
** This is the shellsort algorithm.
*/
void shellSortPhase(int *  a,  int length,  int gap) 
{
    int i;
    for (i=gap; i<length; ++i) 
    {
        //wBUF("An S message\n");
         int value = a[i];
              int j;
        for (j = i - gap; j >= 0 && a[j] > value; j -= gap) 
            a[j + gap] = a[j];
        a[j + gap] = value;
    }
}
    
void sSortArray(int *  a,  size_t length,  char * s) 
{
    /*
     * gaps[] should approximate a geometric progression.
     * The following sequence is the best known in terms of
     * the average number of key comparisons made [2]
     */
    static  int gaps[] = { 1, 4, 10, 23, 57, 132, 301, 701 };
    int sizeIndex;
    
    for 
    (
        sizeIndex = sizeof(gaps)/sizeof(gaps[0]) - 1;
        sizeIndex >= 0;
        --sizeIndex
    )
    shellSortPhase(a,length,gaps[sizeIndex]);
}
/*
** END SHELL SORT ALGORITHM
*/


/*
** This structure is passed between the thread 
** invocation and the sort algorithm.
*/
typedef struct
{
           int *  a;
      int         s;
      char    tc[2];
} sortParmType;

/*
** Single exit point.
*/
void cleanExit()
{
    pthread_exit(NULL);
}

/*
** This is a wrapper that translates the void *
** parameter we are allowed into meaningful values.
** Those values (array and array size) are passed
** to the selected sort function.
*/
void * sortWrapper(void * x)
{
    sortParmType *  S = (sortParmType * )x;
    if (S->a != 0) 
        /*
        ** Perform shell or quicksort.
        */
        if (useQsort) qSortArray (S->a,0,  (S->s)-1, S->tc);
        else          sSortArray (S->a,S->s        , S->tc);
    cleanExit();
    return (void *)0; /* never executes -- eliminates */
                      /* compiler warnings            */
}

/*
** This function gets the array size from the 
** user.
*/
 long getArraySize( char *  p)
{
          char         line[MAXLINE];
     int          j = fputs(p, stdout);
     char *  c = fgets(line, MAXLINE, stdin);
     long         s = (long) atof(line);
    if ((s<=0) || (s>MAXARRAYSIZE)) 
    {
        if (useQsort) printf("Quicksort Used\n");
        else          printf("Shellsort Used\n");
        cleanExit();
    }
    return s;
}

/*
** This function copies one array to another. 
*/
void copyArray
    (int *  a,  int *  b,  int arrSize)
{
    int i;
    for (i=0; i<arrSize; ++i) a[i] = b[i];
}

/*
** This function merges two equal sized arrays (aTargSize/2) into
** an array double the size (aTargSize).
*/
void mergeArrays
(
           int *  aTarg, 
      int *  a1, 
      int *  a2, 
      int         aTargSize)
{
    int iTarg = 0;
    int i1    = 0;
    int i2    = 0;

     int aInSize = aTargSize/2;
    
    do
    {
        if      (i1 == aInSize)
            aTarg[iTarg++] = a2[i2++];
        else if (i2 == aInSize)
            aTarg[iTarg++] = a1[i1++];
        else if (a1[i1] < a2[i2])
            aTarg[iTarg++] = a1[i1++];
        else
            aTarg[iTarg++] = a2[i2++];
    } while (iTarg<aTargSize);
}

/*
** Error in spawning thread?  Exit.
*/
void sThreadError( int t)
{
    if(t) printf("Error spawning Thread 1\n");
    else  printf("Error spawning Thread 2\n");
    cleanExit();
}

/*
** Error in joining thread?  Exit.
*/
void jThreadError( int t)
{
    if(t) printf("Error joining Thread 1\n");
    else  printf("Error joining Thread 2\n");
    cleanExit();
}

/*
** This function joins the threads.
*/
void joinThreads
( 
     pthread_t t1, 
     pthread_t t2
)
{
    int *s;
    if (t1 != 0) 
        if (pthread_join(t1,(void **)&s)) jThreadError(0);
    if (t2 != 0)
        if (pthread_join(t2,(void **)&s)) jThreadError(1);
}

/*
** This function performs the sequential sort by 
** direct invocation.
*/
void sequentialSort(int *  a,  int arrSize)
{
    if (useQsort) qSortArray (a,0,     arrSize-1,"0");
    else          sSortArray (a,arrSize         ,"0");
}

/*
** If either of the array pointers are = 0, that array won't be
** sorted. However, in this program 2 arrays are always sorted
** but I did test the other option.
*/
void threadedSort
(
          int *  a1in, 
          int *  a2in, 
     int         arrSize
)
{
     sortParmType S1 = {a1in,arrSize,"1"};
     sortParmType S2 = {a2in,arrSize,"2"};
          pthread_t    t1 = 0;
          pthread_t    t2 = 0;

    /*
    ** Set thread detatched attribute.
    */
//    pthread_attr_t attr;
//    pthread_attr_init(&attr);
//    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

    if (a1in != 0)
    {
         int rc = 
            pthread_create(&t1,NULL,sortWrapper,(void *)(&S1));
        if (rc) sThreadError(0);
    }
    if (a2in != 0)
    {
         int rc = 
            pthread_create(&t2,NULL,sortWrapper,(void *)(&S2));
        if (rc) sThreadError(1);
    }

    joinThreads(t1,t2);

//    pthread_attr_destroy(&attr);
}

/*
** This function verifies that two arrays are equal and
** in ascending sorted order. Returns 1 if OK, otherwise 0.
*/
int verifyArrays
(
     int *  a1in, 
     int *  a2in, 
     int         arrSize
)
{
          int i;
     int u = arrSize-1;
    for (i=0; i<arrSize; ++i)
    {
        if (a1in[i] != a2in[i])             return 0;
        if ((i<u) && (a1in[i] > a1in[i+1])) return 0;
    }
    return 1;
}

/*
** This function outputs an array to stdout as long
** as DUMPINHIBIT is not equal to zero. 
*/
void dumpArray
(
      char *  t, 
      int  *  a, 
      int          arrSize
)
{
    if (DUMPINHIBIT) return;
    int i;
    printf("\n"); printf("%s\n",t); printf("\n");
    for (i=0; i<arrSize; printf("    %d\n", a[i++]));

}

/*
** This function fills an array with values
** ranging from 0 to RAND_MAX. 
*/
void fillArray(int *  a,  int arrSize)
{
    int i;
    for (i=0; i<arrSize; ++i) a[i] = rand();
}

int threadedMergeSort( int argc, char *  argv[])
{

    /*
    ** Build the prompt so it will adjust if MAXARRAYSIZE
    ** is changed.
    */
    char prompt[PROMPTSIZE];
    sprintf
        (
            prompt,
            "\nEnter array size: 1 -- %d or anything else to quit >> ",
            MAXARRAYSIZE
        );

    /*
    ** ant used in time computation
    */
     double mS_PER_CLOCK = mS_PER_SEC/CLOCKS_PER_SEC;

    /*
    ** If the user supplies any argument, use quicksort.
    */
    useQsort = 1;

    while(1)
    {
         int as  = getArraySize(prompt);
         int as2 = as*2;
        clock_t   t1,t2;


        /*
        ** Populate the test arrays. Steps 1,2, and 3
        */
        fillArray(smallArray1,as);
        fillArray(smallArray2,as);
        copyArray(smallArray3,smallArray1,as);
        copyArray(smallArray4,smallArray2,as);
        copyArray(largeArray3,smallArray1,as);
        copyArray(&largeArray3[as],smallArray2,as);

        /*
        ** Run the first test case (2 sorts and a merge) Step 4
        */
	initBUF();
        t1 = clock();
        threadedSort(smallArray1,smallArray2,as);
        mergeArrays(largeArray1,smallArray1,smallArray2,as2);
        t2 = clock();
	cuBUF();
        dumpArray("largeArray1:",largeArray1,as2);
        printf("Time to do 2 thread sorts and a merge            = %f", 
           (double)(t2-t1) * mS_PER_CLOCK);
        printf(" microseconds\n");
return 1;
        /*
        ** Run the second test case (2 sorts, copy &merge) Step 5
        */
        t1 = clock();
        sequentialSort(smallArray3,as);
        sequentialSort(smallArray4,as);
        mergeArrays(largeArray2,smallArray3,smallArray4,as2);
        t2 = clock();
        dumpArray("largeArray2:",largeArray2,as2);
        printf("Time to do 2 sequential sorts and a merge        = %f", 
           (double)(t2-t1) * mS_PER_CLOCK);
        printf(" microseconds\n");

        /*
        ** Run the third test case (single sort) Step 6
        */
        t1 = clock();
        sequentialSort(largeArray3,as2);
        t2 = clock();
        dumpArray("largeArray3:",largeArray3,as2);
        printf("Time to do a sequential sort on a combined array = %f", 
           (double)(t2-t1) * mS_PER_CLOCK);
        printf(" microseconds\n");

        /*
        ** As a sanity check, ensure the arrays are
        ** equal and in sorted order.
        */
        if((verifyArrays(largeArray1,largeArray2,as2) == 0) ||
           (verifyArrays(largeArray1,largeArray3,as2) == 0))  
            printf("Error in sort algorithm!!!!\n");
    }
    cleanExit();    
    return 0;
}

