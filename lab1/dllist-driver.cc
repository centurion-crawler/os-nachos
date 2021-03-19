#include "dllist.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <math.h>
const int INF=0x3ff;

int GenerateInt()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (int)((1+sin((double)tv.tv_usec))*INF);
}
bool 
CreateDLList(DLList* dptr, int N, int whichthread)
{
    
    for (int i=0;i<N;i++) 
    {
        int k=GenerateInt();
        dptr->SortedInsert(NULL,k);
        printf("[%d/%d]Insert key %d to the DLList of Thread %d.\n",i+1,N,k,whichthread);
    }
    return true;
}
bool 
RemoveItems(DLList* dptr,int N,int whichthread)
{
    int pi=0;
    while(!dptr->IsEmpty())
    {
        DLLElement *outfirst = (DLLElement *)dptr->Remove(NULL);
        if (outfirst != NULL)
        {
            pi++;
            printf("[%d/%d]Removed key %d (Head of the DLList) of Thread %d.\n",pi,N,outfirst->key,whichthread);
        }
    }
    return true;
}
