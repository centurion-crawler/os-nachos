#ifndef DLLIST_H
#define DLLIST_H

class DLLElement{
    public:
        DLLElement(void* itemPtr, int sortKey); // initialize a list element
        DLLElement *next; // next element on the list, NULL if last
        DLLElement *prev; // previous element on the list, NULL if first
        int key; // priority, for a sorted list
        void *item; // pointer to item on the list
};
class DLList{ 
    public:
        DLList(); // initialize a list
        ~DLList(); // destroy or de-allocate a list

        void Prepend(void *item); // add to head of the list 
        void Append(void *item); // add to tail of the list 
        void *Remove(int *keyPtr); // remove from head of the list

        bool IsEmpty(); // check if list is empty return true 
        void SortedInsert(void *item, int sortKey); // insert a item before/after with key==sortkey
        void *SortedRemove(int sortKey); //  remove first item with key==sortKey 
                                         //  return NULL if no such item exist

private:
    DLLElement *first; // head of the list, NULL if empty
    DLLElement *last; // last element of the list, NULL if empty
};
int GenerateInt(int);
bool CreateDLList(DLList*,int,int);
bool RemoveItems(DLList* ,int ,int);
#endif