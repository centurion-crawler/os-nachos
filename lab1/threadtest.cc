// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "dllist.h"


// testnum is set in main.cc
int testnum = 1;
int threadNum;
int itemNum; 
int errorType = 0;
DLList *dlist = new DLList();
int tmpnum;
//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

void
SimpleThread(int which)
{
    int num;
    
    for (num = 0; num < 5; num++) {
	printf("*** thread %d looped %d times\n", which, num);
        currentThread->Yield();
    }
}

//----------------------------------------------------------------------
// ThreadTest1
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------
void
ThreadTest1()
{
    DEBUG('t', "Entering ThreadTest1");

    Thread *t = new Thread("forked thread");

    t->Fork(SimpleThread, 1);
    SimpleThread(0);
}

//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------
void 
DLListThread(int which)
{
    // CreateDLList(dlist,itemNum,which);
    // RemoveItems(dlist,itemNum,which);
    CreateDLList(dlist,itemNum,which);
    printf("*** thread %d Insert %d number\n", which,itemNum);

    dlist->Remove(NULL);
    printf("*** thread %d Remove\n", which);

    currentThread->Yield();
    tmpnum = GenerateInt(which);
    dlist->SortedInsert(NULL,tmpnum);
    printf("*** thread %d SortedInsert %d\n", which,tmpnum);

    dlist->Append(NULL);
    printf("*** thread %d Append\n", which);
    currentThread->Yield();
    dlist->Prepend(NULL);
    printf("*** thread %d Prepend\n", which);

    currentThread->Yield();
    tmpnum = GenerateInt(which);
    dlist->SortedInsert(NULL,tmpnum);
    printf("*** thread %d SortedInsert %d\n", which,tmpnum);
    currentThread->Yield();
    tmpnum = GenerateInt(which);
    dlist->SortedInsert(NULL,tmpnum);
    printf("*** thread %d SortedInsert %d\n", which,tmpnum);

    dlist->Append(NULL);
    printf("*** thread %d Append\n", which);
    
    currentThread->Yield();
    dlist->Prepend(NULL);
    printf("*** thread %d Prepend\n", which);
    currentThread->Yield();
    dlist->Prepend(NULL);
    printf("*** thread %d Prepend\n", which);

    RemoveItems(dlist,itemNum,which);
}

void ThreadTest2()
{
    DEBUG('t', "Entering ThreadTest2");

    for (int i=0;i<threadNum;i++)
    {
        Thread *t = new Thread("fork thread");
        t->Fork(DLListThread,i);
    }

}
void
ThreadTest(int N,int T)
{
    switch (testnum) {
    case 1:
        ThreadTest2();
        break;
    default:
	    printf("No test specified.\n");
	break;
    }
}
