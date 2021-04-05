#include <iostream>
#include "dllist.h"

void InsertN(int N,DLList *dlList,int flag){
    int random;
    int array1[10] = {12,32,32,52,54};
    int array2[10] = {8,30,44,56,94};
    void *item;
    //DLLElement *p;
    //printf("\n");
    if(flag == 0){
        for(int i=0;i<N;i++){
        //Randomly generated numbers from (min_key - 20) to (max_key + 20)
            //random = rand()%(dlList->max_key-dlList->min_key+1 + 20)+(dlList->min_key - 20);
            random = rand()%101;
            printf("insert key: %d\n",random);
            dlList->SortedInsert(item,random);
        }
    }
    else if (flag == 1){
        for(int i=0;i<N;i++){
        //printf("key%d: %d\n",i+1,random);
            dlList->SortedInsert(item,array1[i]);
        }
    }
    else if (flag == 2){
        for(int i=0;i<N;i++){
        //printf("key%d: %d\n",i+1,random);
            dlList->SortedInsert(item,array2[i]);
        }
    }
//    p = dlList->first;
//    while(p!= nullptr){
//        printf("key:%d\n",p->key);
//        p = p->next;
//    }
    //printf("Insert Completed!\n");
}

void RemoveN(int N,DLList *dlList){
    int *keyPtr = new int();
    for(int i=0;i<N;i++){
        dlList->Remove(keyPtr);
        //printf("key%d: %d\n",i+1,*keyPtr);
        //printf("Remove Completed!\n");
    }
}