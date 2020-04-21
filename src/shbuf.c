#include "sem.h"
#include "shbuf.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//
// Lehigh University
// CSE 303 Spring 2020
// Programming Assignment 4B
//

char v[1024];
enum {SEM = 1};
double mS_PER_SEC1   = 1000000.0;
int initBUF() {
	//if sem == 0 then its disabled
	if(SEM){
		initSEM(v, 11212);
		setSEM(1,v);
		return 0;	
	}

}

//
// Write to buffer.
//
int wBUF(  char *  s ,clock_t t1 )
{
	double mS_PER_CLOCK = mS_PER_SEC1/CLOCKS_PER_SEC;

	if(SEM) pSEM(v);
	time_t ltime = clock();
  	char* time = ctime(&ltime);

  	clock_t t2 = clock();
	printf("%s ",s);
	printf("Wait Time: %f \n", 
           (double)(t2-t1) * mS_PER_CLOCK);



	if(SEM) vSEM(v);
	return  0;
}

//
// Clean up.
//
int cuBUF() {
	if(SEM) dSEM(v);
	return 0;
}


