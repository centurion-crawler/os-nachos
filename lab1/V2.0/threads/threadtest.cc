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
int testnum = 1; //初始值为1，在main.cc还会改变

DLList *list = new DLList(); //定义链表为全局变量

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

void
DLListOperation1(int which)
{
    int *keyPtr = new int();
    //DLList *list = new DLList();

    // //case 1

    // InsertN(5,list,1);
    // printf("*** thread %d Insert5\n", which);
    // //list->Display();

    // //currentThread->Yield();

    // RemoveN(4,list);
    // printf("*** thread %d Remove4\n", which);
    // list->Display();

    
   // case2

    InsertN(5,list,1);
    printf("*** thread %d Insert 5\n", which);
    //list->Display();

    RemoveN(4,list);
    printf("*** thread %d Remove 4\n", which);
    //list->Display();

    currentThread->Yield();

    InsertN(5,list,2);
    printf("*** thread %d Insert5\n", which);
    list->Display();


    // //case3

    // InsertN(5,list,1);
    // printf("*** thread %d Insert 5\n", which);
    // //list->Display();

    // currentThread->Yield();

    // list->SortedRemove(12);
    // printf("*** thread %d SortedRemove 23\n", which);
    // list->Display();

    // //case4

    // InsertN(5,list,1);
    // printf("*** thread %d Insert 5\n", which);
    // //list->Display();

    // //currentThread->Yield();

    // list->Prepend((void*)0);
    // printf("*** thread %d Prepend\n", which);
    // //list->Display();

    // list->Prepend((void*)0);
    // printf("*** thread %d Prepend\n", which);
    // list->Display();

}


void
DLListOperation2(int which)
{
    int *keyPtr = new int();
    //DLList *list = new DLList();

    // //case 1
    // printf("*** thread %d Insert 5\n", which);
    // InsertN(5,list,2);
    // list->Display();

    //case2

    RemoveN(4,list);
    printf("*** thread %d Remove4\n", which);
    list->Display();

    // //case3

    // list->Remove(keyPtr);
    // printf("*** thread %d Remove\n", which);
    // list->Display();

    // //case4

    // list->Remove(keyPtr);
    // printf("*** thread %d Remove\n", which);
    // list->Display();

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


void
ThreadTest2()
{
    DEBUG('t', "Entering ThreadTest2");

    Thread *t = new Thread("forked thread");

    t->Fork(DLListOperation2, 1);
    DLListOperation1(0);
}

//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest()
{
    printf("testnum:%d\n",testnum);
    switch (testnum) {
    case 1:
	   ThreadTest1();
	   break;
    case 2:
        ThreadTest2();
        break;
    default:
	   printf("No test specified.\n");
	   break;
    }
}

