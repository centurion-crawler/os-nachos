#include "copyright.h"
#include "dllist.h"
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
const int INF=0x3f3f;
int GenerateInt()
{
    srand(time(NULL));
    return rand()%INF;
}
extern bool
CreateDLList(DLList* dptr, int N, int whichthread)
{
    for (int i=0;i<N;i++) 
    {
        int k=GenerateInt();
        dptr->SortedInsert(NULL,k);
        printf("\n Insert key %d to the DLList of Thread %d.\n",k,whichthread);
    }
    return true;
}
extern bool 
RemoveItems(DLList* dptr,int N,int whichthread)
{
    int pi=0;
    while(!dptr->IsEmpty())
    {
        DLLElement *outfirst = dptr->Remove(NULL);
        if (outfirst != NULL)
        {
            pi++;
            printf("\n[%d/%d]Removed key %d (Head of the DLList) of Thread %d.\n",pi,N,outfirst->key,whichthread);
        }
    }
    return true;
}