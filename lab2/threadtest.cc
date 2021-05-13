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

#include "Table.h"
#include "BoundedBuffer.h"
#include "synch.h"
#include "synchdllist.h"

int threadNum;
int itemNum;
int errorType = 0;

SynchDLList *sdlist;
Table *t1 = new Table(2);


 
Lock *list_lock =  new Lock("threadtest list lock");

BoundedBuffer *buffer;
int buffer_size;
int reader_num;
int writer_num;

Table *tables;
int table_length;
int allocer_num;
int releaser_num;

DLList *dlist;
int remover_num;
int inserter_num;

// testnum is set in main.c
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

void DlListThread(int which)
{
   // CreateDLList(sdlist,itemNum,which);
   // RemoveItems(sdlist,itemNum,which);
    printf("dllist sem test\n"); // zzf
}
	
void ThreadTest11()   // zzf dllist test. test no.11
{
    sdlist = new SynchDLList();

    for (int i=1;i< threadNum;i++)
    {
        Thread *t = new Thread("fork Thread");
        t->Fork(DlListThread,i);
    }
    DlListThread(0);
}

void 
TableOperation1(int which) 
{
    char data[3][4] = {"123", "456", "abc"};
    for(int i=0; i<3; i++) {
        int index = t1->Alloc(data[i]);
        printf("Thread %d: Alloc %s to table[%d]\n", which, data[i], index);
    }
}

void 
TableOperation2(int which)  
{
    for(int i=0; i<2; i++) {
        void *item;
        item = t1->Get(i);
        printf("Thread %d: Get %s to table[%d]\n", which, item, i);

        t1->Release(i);
        printf("Thread %d: Release table[%d]\n", which, i);
    }
}

void
ThreadTest33()    // wzj table test. test no.33
{
    DEBUG('t', "Entering ThreadTest3");
    Thread *t = new Thread("forked thread");
    t->Fork(TableOperation2, 1);
    TableOperation1(0);
}

void ThreadTest44()
{
    printf("Bounded Buffer Test\n");
}

void Buffer_Reader(int which)
{
	while(1){
                printf("--- Buffer Reader Thread %d Now ---\n", which);
		int size = Random() % 50 + 1;
		int *data = new int[size];
               // printf("Thread buffer reader %d\n", which);
		buffer -> Read(data, size);
		printf("Thread %d read %d entries from buffer.\n", which, size);
	        currentThread -> Yield();
        }
}

void Buffer_Writer(int which)
{
	while(1){
                printf("--- Buffer Writer Thread %d Now ---\n", which);
		int size = Random() % 50 + 1;
		int *data = new int[size];
		for(int i = 0; i < size; i++){
			*((int *)data + i) = i;
		}
               // printf("Thread buffer writer %d\n", which);
		buffer -> Write(data, size);
		printf("Thread %d wrote %d entries to buffer.\n", which, size);
                currentThread -> Yield();
	}
}

void BufferTest()
{
	DEBUG('t', "Entering BufferTest");
	buffer_size = 100;
	buffer = new BoundedBuffer(buffer_size);
	reader_num = 3;
	writer_num = 2;
	for(int i = 0; i < reader_num; i++){
		Thread *t = new Thread("reader forked thread");
		t -> Fork(Buffer_Reader, i + 10);
	}
	for(int i = 0; i < writer_num; i++){
		Thread *t = new Thread("writer forked thread");
		t -> Fork(Buffer_Writer, i + 20);
	}
        if(reader_num > writer_num){
            Buffer_Reader(0);
        }
        else{
            Buffer_Writer(0);
        }
}

void Table_Allocer(int which)
{
	while(1){
                printf("--- Table Allocer Thread %d Now ---\n", which);
		int *object = new int[1];
		object[0] = Random() % 97 + 1;
		int index = tables -> Alloc(object);
                if(index != -1){
      		    printf("Thread %d allocced entry %d to table.\n", which, index);
                }
                currentThread -> Yield();
	}
}

void Table_Releaser(int which)
{
	while(1){
                printf("--- Table Releaser Thread %d Now ---\n", which);
		int index = Random() % table_length + 1;
		void *reciever = tables -> Get(index);
		while(reciever == NULL){
			index = Random() % table_length + 1;
			reciever = tables -> Get(index);
		}
		tables -> Release(index);
		printf("Thread %d got and released entry %d from table.\n", which, index);
                currentThread -> Yield();
	}
}

void TableTest()
{
	DEBUG('t', "Entering Table Test");
	table_length = 70;
	tables = new Table(table_length);
	allocer_num = 4;
	releaser_num = 3;
	for(int i = 0; i < allocer_num; i++){
		Thread *t = new Thread("allocer forked thread");
		t -> Fork(Table_Allocer, i + 100);
	}
	for(int i = 0; i < releaser_num; i++){
		Thread *t = new Thread("releaser forked thread");
		t -> Fork(Table_Releaser, i + 200);
	}
	if(allocer_num > releaser_num){
            Table_Allocer(0);
        }
        else{
            Table_Releaser(0);
        }
	
}

void DLList_Inserter(int which)
{
	while(1){
                printf("--- DLList Inserter Thread %d Now ---\n", which);
               // printf("Thread is %d\n", which);
		int insert_key = Random() % 15 + 1;
		int *insert_term = new int[1];
		insert_term[0] = Random() % 100 + 1;
		dlist -> SortedInsert(insert_term, insert_key);
		printf("Thread %d inserted %d into dllist.\n", which, insert_key);
		currentThread -> Yield();
	}
	
}


void DLList_Remover(int which)
{
        while(1){
                printf("--- DLList Remover Thread %d Now ---\n", which);
               // printf("Thread is %d\n", which);
	        int remove_key = 0;
               // printf("ineted\n");
                void * remove_result = dlist -> Remove(&remove_key);
	       // printf("Removed\n");     
          	if(remove_result != NULL)
			printf("Thread %d removed %d from dllist.\n", which, remove_key);            
                else
                        printf("Result is null\n");
		currentThread -> Yield();
	}
	
}

void DLListTest()
{
	DEBUG('t', "Entering DLList Test");
	dlist = new DLList();
	inserter_num = 5;
	remover_num = 3;
	for(int i = 0; i < inserter_num; i++){
		Thread *t = new Thread("inserter forked thread");
		t -> Fork(DLList_Inserter, i + 50);
	}
	for(int i = 0; i < remover_num; i++){
		Thread *t = new Thread("remover forked thread");
		t -> Fork(DLList_Remover, i + 90);
	}
	
}

void
DLListOperation1(int which) //0
{
	list_lock -> Acquire();
    printf("DLListoperation 1 acquired the lock\n");
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

    
    //case2

    //InsertN(5,list,1);
    //printf("*** thread %d Insert5\n", which);
    //list->Display();

    //RemoveN(4,list);
    //printf("*** thread %d Remove4\n", which);
    //list->Display();

    //currentThread->Yield();

    //InsertN(5,list,2);
    //printf("*** thread %d Insert5\n", which);
    //list->Display();


    //case3

    //InsertN(5,list,1);
   // printf("*** thread %d Insert5\n", which);
    //list->Display();

    //currentThread->Yield();

    //list->SortedRemove(12);
    //printf("*** thread %d SortedRemove23\n", which);
    //list->Display();

    //case4

    InsertN(5,list,1);
    printf("\nThread %d Inserted 5 number\n", which);
    list->Display();
    printf("thread yielding ...\n");
    currentThread->Yield();
    printf("thread yielded ...\n");
    list->Prepend((void*)0);
    printf("\nThread %d Prepend an element\n", which);
    list->Display();

    list->Prepend((void*)0);
    printf("\nThread %d Prepend an element\n", which);
    list->Display();
    list_lock -> Release();
    printf("DLListoperation 1 released the lock\n");
}


void
DLListOperation2(int which) // 1
{
    list_lock -> Acquire();
    printf("DLListoperation 2 acquired the lock\n");
    int *keyPtr = new int();
    //DLList *list = new DLList();

    // //case 1

    // InsertN(5,list,2);
    // list->Display();

    // //case2

    // RemoveN(4,list);
    // printf("*** thread %d Remove4\n", which);
    // list->Display();

    //case3

   // list->Remove(keyPtr);
   // printf("*** thread %d Remove\n", which);
    //list->Display();

    //case4

    list->Remove(keyPtr);
    printf("\nThread %d Removed an element %d\n", which, *keyPtr);
    list->Display();
    list_lock -> Release();
    printf("DLListoperation 2 released the lock\n");
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
    printf("Test %d successfully started.\n", testnum);
    switch (testnum) {
    case 1:
	   ThreadTest1();
	   break;
    case 2:
        printf("       === Test for DLList ===\n");
        DLListTest();  // dllisttest
        break;
	case 3:
                printf("       === Test fot Table ===\n");      
         	TableTest();
		break;
	case 4:
                printf("       === Test for BoundedBuffer ===\n");
		BufferTest();
		break;
        case 5:
                printf("       === Evaluate for DLList===\n");
                ThreadTest2();
                break;
        case 11:
                printf("thread num is %d   item num is %d\n", threadNum, itemNum);
                ThreadTest11();  // zzf dllist semaphore test. test no.11
                break;
        case 22:
                ThreadTest2();   // hgw dllist sleep test. test no.22
                break;
        case 33:
                ThreadTest33();  // wzj table test. test no.33
                break;
        case 44:
                ThreadTest44();  // lzh bounded buffer test. test no.44
                break;
    default:
	   printf("Wrong Test No. Quitting ...\n");
	   break;
    }
}

