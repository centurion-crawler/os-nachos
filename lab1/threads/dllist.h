//
// Created by 13411 on 2021/3/18.
//

#ifndef DLLIST_DLLIST_H
#define DLLIST_DLLIST_H

class DLLElement{
public:
    DLLElement( void *itemPtr, int sortKey );  // initialize a list element

    DLLElement *next; // next element on list
                      // NULL if this is the last
    DLLElement *prev; // previous element on list
                      // NULL if this is the first
    int key;          // priority, for a sorted list

    void *item;       // pointer to item on the list
};


class DLList {
public:
    DLList();	// initialize the list
    ~DLList();	// de-allocate the list

    int min_key;
    int max_key;

    void Prepend(void *item);  // add to head of list (set key = min_key-1)
    void Append(void *item);   // add to tail of list (set key = max_key+1)
    void *Remove(int *keyPtr); // remove from head of list
                               // set *keyPtr to key of the removed item
                               // return item (or NULL if list is empty)

    bool IsEmpty();	           // return true if list has elements

    void Display();            //Show all keys in order

    // routines to put/get items on/off list in order (sorted by key)
    void SortedInsert(void *item, int sortKey);
    void *SortedRemove(int sortKey);  // remove first item with key==sortKey
                                      // return NULL if no such item exists

private:
    DLLElement *first;	// head of the list, NULL if empty
    DLLElement *last;	// last element of the list, NULL if empty
};


void InsertN(int N,DLList *dlList,int flag);
void RemoveN(int N,DLList *dlList);

#endif //DLLIST_DLLIST_H
