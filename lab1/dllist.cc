// dllist.cc
#include <stdlib.h>
#include <stdio.h> 
#include "dllist.h"
#include "system.h"

DLLElement::DLLElement(void* itemPtr, int sortKey)
{
    item = itemPtr;
    key = sortKey;
    next = NULL;	// assume we'll put it at the end of the list 
    prev = NULL;
}
DLList::DLList()
{ 
    first = last = NULL; 
}
DLList::~DLList()
{
    while(Remove(NULL)!=NULL);
}
void DLList::Append(void *item)
{
    DLLElement *element = new DLLElement(item,0);

    if (IsEmpty())
    {
        first = element;
        last = element;
    } else {
        last->next = element;
        element->key = last->key+1;
        element->prev=last;
        element->next=NULL;
        last = element;
    } 
}
void DLList::Prepend(void *item)
{
    DLLElement *element = new DLLElement(item,0);
    if (IsEmpty())
    {
        first = element;
        last =  element;
    }else {
        first->prev = element;
        element->key = first->key-1;
        element->next = first;
        element->prev = NULL;
        first = element;
    }
}
void * DLList::Remove(int *keyPtr)
{
    if (!IsEmpty())
    {
        if (keyPtr==NULL)
            return SortedRemove(first->key);
        else 
            return SortedRemove(*keyPtr);
    }
    else return NULL;
}
bool DLList::IsEmpty()
{
    if (first == NULL && last == NULL)
        return true;
    else return false;
}
void 
DLList::SortedInsert(void* item, int sortkey)
{
    DLLElement *element = new DLLElement(item, sortkey);
    DLLElement *ptr; //keep track

    if (IsEmpty()){
        first = element;
        last = element;
    } else if (sortkey < first->key){
        // item goes on front of list
        first->prev = element;
        element->next = first;
        first = element;
    } else {
        for (ptr = first;ptr->next!=NULL;ptr = ptr->next){
            if (sortkey < ptr->next->key){
                element->next = ptr->next;
                element->prev = ptr;
                ptr->next = element;
                element->next->prev=element;
                return;
            }
        }
        last->next = element;
        element->prev=last;
        last = element;
    }
}
void *
DLList::SortedRemove(int sortkey)
{
    DLLElement *ptr;
    DLLElement *item;
    for (ptr = first;ptr->next!=NULL;ptr = ptr->next){
        if (sortkey==ptr->key)
            break;
    }
    if (ptr == NULL)
        return NULL;
    if (ptr == first && ptr == last)
    {
        first = NULL;
        last= NULL;
        return ptr;
    }
    if (ptr == first)
    {
        item=first;
        first = ptr->next;
        first->prev=NULL;
        return item;
    }
    else if (ptr == last) {
        item=last;
        last=ptr->prev;
        last->next=NULL;
        return item;
    }
    else {
        item =ptr;
        ptr->next->prev=ptr->prev;
        ptr->prev->next=ptr->next;
        return item;
    }
    return NULL;
}