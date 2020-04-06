#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "sem.h"

 

typedef struct sem_ds  sDType;
typedef struct seminfo sIType;
typedef struct sembuf  sBType;


typedef union 
{
   int             val;
   sDType         *buf;
   const unsigned 
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
   sBType * const    s,
   const int        sN,
   const int        sO,
   const int        sF 
)
{
   s->sem_num =     sN;
   s->sem_op  =     sO;
   s->sem_flg =     sF;
}

void initSEM
(
   void * const      v,
   const long        k
)
{
   const long kY =   k;
   iNType *const iP =
      (iNType* const)v;  
   sBType *const sZ =
             &iP->zero;
   sBType *const sL =
             &iP->lock;
   sBType *const sU =
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
  
const int getSSizeSEM() 
{ 
   const int s = 
        sizeof(iNType);
   return            s;
}

const int pSEM           
(
   void * const      v 
)
{
   iNType *const iP =
       (iNType* const)v;  
   const int sid =
                iP->sID;
   sBType *const sL =
              &iP->lock;
   const int eC =
      semop(sid, sL, 1);
   return            eC;
}


const int setSEM
(
   const int         x,
   void * const      v 
)
{
   iNType *const iP =
       (iNType* const)v;  
   const int sid =
                iP->sID;
   semctl
      (sid,0,SETVAL, x);
   
}

void vSEM
(
   void * const      v 
)
{
   iNType *const iP =
       (iNType* const)v;  
   const int sid =
                iP->sID;
   sBType *const sU =
            &iP->unlock;
   semop   (sid, sU, 1);
}

void zSEM
(
   void * const      v 
)
{
   iNType *const iP =
       (iNType* const)v;  
   const int sid =
                iP->sID;
   sBType *const sZ =
              &iP->zero;
   semop   (sid, sZ, 1);
}


void dSEM
(
   void * const      v 
)
{
   iNType *const iP =
       (iNType* const)v;  
   const int p1     = 
               getpid();
   const int p2     =  
                iP->pID;
   const long p3     =  
                iP->sID;
   if(p1==p2)
     semctl(p3,0,
            IPC_RMID,0);
}
