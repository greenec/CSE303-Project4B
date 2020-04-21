#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "sem.h"

//
// Lehigh University
// CSE 303 Spring 2020
// Programming Assignment 4B
//

typedef struct sem_ds  sDType;
typedef struct seminfo sIType;
typedef struct sembuf  sBType;


typedef union 
{
 int             val;
 sDType         *buf;
 unsigned 
 short int *array;
 sIType       *__buf;
} sUType;

typedef struct
{
 sUType          arg;
 sBType         zero;
 sBType         lock;
 sBType       unlock;
 long            sID; 
 pid_t           pID;
} iNType; 

static void setSB
(
 sBType *     s,
 int        sN,
 int        sO,
 int        sF 
 )
{
 s->sem_num =     sN;
 s->sem_op  =     sO;
 s->sem_flg =     sF;
}

void initSEM
(
 void *       v,
 long        k
 )
{
  long kY =   k;
  iNType * iP =
  (iNType* )v;  
  sBType * sZ =
  &iP->zero;
  sBType * sL =
  &iP->lock;
  sBType * sU =
  &iP->unlock;
  setSB
  (sZ,0,0,SEM_UNDO);
  setSB
  (sL,0,-1,SEM_UNDO);
  setSB
  (sU,0,1,SEM_UNDO);
  iP->pID =  getpid();
  iP->sID = 
  semget(kY,1,
    IPC_CREAT|
    IPC_EXCL|
    0666);
  if(iP->sID == -1)
    iP->sID = 
  semget (kY,1,0); 
  setSEM        (0,v);
}

int getSSizeSEM() 
{ 
  int s = 
  sizeof(iNType);
  return            s;
}

int pSEM           
(
 void *       v 
 )
{
 iNType * iP =
 (iNType* )v;  
 int sid =
 iP->sID;
 sBType * sL =
 &iP->lock;
 int eC =
 semop(sid, sL, 1);
 return            eC;
}


int setSEM
(
  int         x,
  void *       v 
  )
{
 iNType * iP =
 (iNType* )v;  
 int sid =
 iP->sID;
 semctl
 (sid,0,SETVAL, x);
      //this function oroginally did not have any return value specified so I just had it return SID
      //because I wasn't sure of its use at the time -Chris
 return sid;
 
}

void vSEM
(
 void *       v 
 )
{
 iNType * iP =
 (iNType* )v;  
 int sid =
 iP->sID;
 sBType * sU =
 &iP->unlock;
 semop   (sid, sU, 1);
}

void zSEM
(
 void *       v 
 )
{
 iNType * iP =
 (iNType* )v;  
 int sid =
 iP->sID;
 sBType * sZ =
 &iP->zero;
 semop   (sid, sZ, 1);
}


void dSEM
(
 void *       v 
 )
{
 iNType * iP =
 (iNType* )v;  
 int p1     = 
 getpid();
 int p2     =  
 iP->pID;
 long p3     =  
 iP->sID;
 if(p1==p2)
   semctl(p3,0,
    IPC_RMID,0);
}
