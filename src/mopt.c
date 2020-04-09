#include "mopt.h"
#include <stdlib.h>
#include "getopt.h"
//
// Lehigh University
// CSE 303 Spring 2020
// Programming Assignment 4
//
// Description:
//
//

enum                   {TABLESIZE = 257};

typedef struct
{
   char           m[TABLESIZE];
   const char   * p[TABLESIZE];
   int                    tLen;
   char        oS[2*TABLESIZE];
   int                    oLen;
   char *                   pC;
} mType;

void * initialize()
{
   const int sL =          sizeof(mType);
   void * mP   =            calloc(sL,1);
   return                             mP;
}

static void addOptP(const char c, const char * const s, void * p) 
{
   if (optExist(c,p) != 1) 
   {
      mType * const mP   = (mType * const)p;
      int            i   =         mP->tLen;
      mP->m[i]           =                c;
      mP->p[i++]         =                s;
      mP->tLen           =                i;
   }
}


const int setO(const char c, const int e, void * p) 
{ 
   mType * const mP   = (mType * const)p;
   int            i   =         mP->oLen;
   mP->oS[i++]        =                c;
   if (e) mP->oS[i++] =              ':';
   mP->oLen           =                i;
   return                              1;
}


const char * const getArg(const char c, void * p) 
{
   const int i =           optExist(c,p);
   if (i>=0)
   {
      mType * const mP =(mType * const)p;
      const char *  pA =        mP->p[i];
      return                          pA;
   }
   return                              0;

}


const sType parse
(
   const int                  argc, 
   const char * const * const argv, 
   void                         *p
) 
{ 
   extern int                     optind;
   extern int                     optopt;
   extern char *                  optarg;
   extern int                     opterr;

   mType * const mP  =  (mType * const)p;
   const char * const optstring = mP->oS; 
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

const char * const aVI(void * p)
{
   mType * const mP   = (mType * const)p;
   const char * const t =         mP->pC;
   return t;
}

const int optExist(const char c, void * p) 
{ 
   if (p)
   {
      const mType * const mP = (mType*)p;

      const char * r =   
                     (const char *)mP->m; 
      int i = 0;
      while(r[i])  
         if (c==r[i])           return i;
         else                        ++i;
   }
   return                             -1;
}


const sType moptFree(void * p)
{
   if (p)                        free(p);
   p                      =            0;
   return                     MOPT_CLEAR;
}
