#include "dllist.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <math.h>
#include "thread.h"
const int INF=0x3ff;
extern Thread *currentThread;
int GenerateInt(int whichthread)
{
    struct timeval tv;
    int out;
    gettimeofday(&tv,NULL);
    out = (int)((1+sin((double)tv.tv_usec))*INF);
    printf("Random %d is generated of Thread %d.\n",out,whichthread);
    return out;
}
bool 
CreateDLList(DLList* dptr, int N, int whichthread)
{
    
    for (int i=0;i<N;i++) 
    {
        int k=GenerateInt(whichthread);
        dptr->SortedInsert(NULL,k);
        printf("[%d/%d]Insert key %d to the DLList of Thread %d.\n",i+1,N,k,whichthread);
    }
    return true;
}
bool 
RemoveItems(DLList* dptr,int N,int whichthread)
{
    int pi=0;
    int all=N;
    while(!dptr->IsEmpty())
    {
        DLLElement *outfirst = (DLLElement *)dptr->Remove(NULL);
        if (outfirst != NULL)
        {
            pi++;
            printf("[%d]Removed key %d (Head of the DLList) of Thread %d.\n",pi,outfirst->key,whichthread);
        }
    }
    return true;
}
