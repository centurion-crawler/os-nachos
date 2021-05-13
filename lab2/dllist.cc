#include "dllist.h"
#include <stdio.h>

DLLElement :: DLLElement(void *itemPtr, int sortKey){
    item = itemPtr;
    key = sortKey;
    next = NULL;
    prev = NULL;
}

DLList::DLList() {
    first = NULL;
    last = NULL;
    min_key = 0;
    max_key = 100;
    list_lock = new Lock("lock for dllist");
}

DLList::~DLList() {
    while (!IsEmpty()){
        (void) Remove(NULL);
    }// delete all the DLList elements
}

void DLList::Prepend(void *item) {
    list_lock -> Acquire();
    int key;
    key = min_key - 1;
    min_key = min_key -1; //renew min_key
    DLLElement *node = new DLLElement(item,key);
    node->next = first;   // next node is old first node
    node->prev = NULL; // NULL if this is the first
    first->prev = node;
    first = node;         // new first node is current node
    if(last == NULL){  // the first node
        last = node;
    }
    list_lock -> Release();
}

void DLList::Append(void *item) {
    list_lock -> Acquire();
    printf("acquired lock\n");
    int key;
    key = max_key + 1;
    max_key = max_key + 1; //renew max_key
    DLLElement *node = new DLLElement(item,key);
    node->prev = last;    // pre node is old last node
    node->next = NULL; // NULL if this is the last
    last ->next =node;
    last = node;          // new last node is current node
    if(first == NULL){ // the first node
        first = node;
    }
    list_lock -> Release();
}

void *DLList::Remove(int *keyPtr) {
    list_lock -> Acquire();
    void *oldItem;
    if(IsEmpty()){
        list_lock -> Release();
        return NULL;
    }
    else{
        *keyPtr = first->key;
        oldItem = first->item;    //temporarily store the item information of the removed node
        first = first -> next;    //renew first node
        if(first == NULL){     //empty
            last = NULL;
            min_key = 0;
            max_key = 100;
        }
        else{
            min_key = first->key;     //renew min_key
            first -> prev = NULL ; //Disconnect from the previous node
        }
        list_lock -> Release();
        return oldItem;
    }
}

bool DLList::IsEmpty() {
    if(first == last && first == NULL){  //it means empty if the first and last pointers coincide
        return true;
    }
    else{
        return false;
    }
}

void DLList::SortedInsert(void *item, int sortKey) {
    list_lock -> Acquire();
    DLLElement *p;
    if(sortKey > max_key){  //renew max_key
        max_key = sortKey;
    }
    else if (sortKey < min_key){ //renew min_key
        min_key = sortKey;
    }
    DLLElement *node = new DLLElement(item,sortKey);
    p = first;
    if(p == NULL){  //the first node
        first = node;
        last = node;
    }
    else {
        while (p != NULL) {
            if (node->key < p->key) {  //The current node should be inserted before P
                node->prev = p->prev;
                node->next = p;
                p->prev = node;
                if (p == first) {  //The current node is the first node
                    first = node;
                    break;
                }
                node->prev->next = node;
                break;
            }
            p = p->next;
        }
        if (p == NULL) { //Indicates that the current node should be inserted at the end
            node->prev = last;
            last->next = node;
            node->next = NULL;
            last = node;
        }
    }
    list_lock -> Release();
}

void *DLList::SortedRemove(int sortKey) {
    list_lock -> Acquire();
    DLLElement *p;
    void *oldItem;
    if(IsEmpty()){
        return NULL;
    }
    p = first;
    while (p != NULL){
        if(p->key == sortKey){
            oldItem = p->item;
            if(first == last){ //There's only one element left
                last = NULL;
                first = NULL;
                min_key = 0;
                max_key = 100;
                break;
            }
            else if(p == first){ //Delete element at the beginning
                min_key = p->next->key;
                first = p->next;
                first->prev = NULL;
                break;
            }
            else if(p == last){ //Delete element at end
                max_key = p->prev->key;
                last = p->prev;
                last->next = NULL;
                break;
            }
            p->prev->next = p->next;
            p->next->prev = p->prev; //Disconnect two way connection
            break;
        }
        p = p->next;
    }
    if(p == NULL){ //This means that the key of no node is equal to sortKey
        list_lock -> Release();
        return NULL;
    }
    else{
        list_lock -> Release();
        return oldItem;
    }
}

void DLList::Display() {
    DLLElement *p;
    int n = 0;
    p = first;
    printf("\n Current DLList :\n");
    while(p != NULL){
        n++;
        printf("key%d : %d\n",n,p->key);
        p = p->next;
    }
}
