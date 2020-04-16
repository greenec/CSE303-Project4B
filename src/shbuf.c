#include "sem.h"
#include "shbuf.h"
#include <stdio.h>


char v[1024];
enum {SEM = 1};

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
int wBUF(  char *  s )
{
	//also time stamp here
	if(SEM) pSEM(v);
	printf("%s\n",s);
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


