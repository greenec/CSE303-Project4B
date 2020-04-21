#include "mopt.h"
#include <stdlib.h>
#include "getopt.h"

//
// Lehigh University
// CSE 303 Spring 2020
// Programming Assignment 4B
//


enum                   {TABLESIZE = 257};

typedef struct
{
   char           m[TABLESIZE];
    char   * p[TABLESIZE];
   int                    tLen;
   char        oS[2*TABLESIZE];
   int                    oLen;
   char *                   pC;
} mType;

void * initialize()
{
    int sL =          sizeof(mType);
   void * mP   =            calloc(sL,1);
   return                             mP;
}

void addOptP( char c,  char *  s, void * p) 
{
   if (optExist(c,p) != 1) 
   {
      mType *  mP   = (mType * )p;
      int            i   =         mP->tLen;
      mP->m[i]           =                c;
      mP->p[i++]         =                s;
      mP->tLen           =                i;
   }
}


 int setO( char c,  int e, void * p) 
{ 
   mType *  mP   = (mType * )p;
   int            i   =         mP->oLen;
   mP->oS[i++]        =                c;
   if (e) mP->oS[i++] =              ':';
   mP->oLen           =                i;
   return                              1;
}


 char *  getArg( char c, void * p) 
{
    int i =           optExist(c,p);
   if (i>=0)
   {
      mType *  mP =(mType * )p;
       char *  pA =        mP->p[i];
      return                          pA;
   }
   return                              0;

}


 sType parse
(
    int                  argc, 
    char *  *  argv, 
   void                         *p
) 
{ 
   extern int                     optind;
   extern int                     optopt;
   extern char *                  optarg;
   extern int                     opterr;

   mType *  mP  =  (mType * )p;
    char *  optstring = mP->oS; 
   char                                c;

   //
   // Set opterr
   // to 0 to prevent
   // getopt from 
   // printing
   // messages.
   //
   opterr  =                           0;
   c       = getopt(argc,argv,optstring);
   do
   {
      if (c=='?')      return MOPT_ERROR;
      if (optExist(c,p) != -1)
                       return MOPT_ERROR;
      addOptP              (c,optarg,mP);
      c =  getopt(argc, argv, optstring);
   }                         while (c+1);

   mP->pC =         (char *)argv[optind];

   return                   MOPT_PARSEOK; 
}

 char *  aVI(void * p)
{
   mType *  mP   = (mType * )p;
    char *  t =         mP->pC;
   return t;
}

 int optExist( char c, void * p) 
{ 
   if (p)
   {
       mType *  mP = (mType*)p;

       char * r =   
                     ( char *)mP->m; 
      int i = 0;
      while(r[i])  
         if (c==r[i])           return i;
         else                        ++i;
   }
   return                             -1;
}


 sType moptFree(void * p)
{
   if (p)                        free(p);
   p                      =            0;
   return                     MOPT_CLEAR;
}
