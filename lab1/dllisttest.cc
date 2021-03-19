#include "dllist.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    int argCount,itemNum;
    DLList *dptr = new DLList();
    for (argc--, argv++; argc > 0; argc -= argCount, argv += argCount) {
		argCount = 1;
		switch (argv[0][1]){
			case 'N':
				itemNum = atoi (argv[1]);
				argCount++;
				break;
            default:
                break;
        }
    }
    CreateDLList(dptr,itemNum,0);
    dptr->Append(NULL);
    dptr->Prepend(NULL);
    printf("IsEmpty? %d\n",dptr->IsEmpty());
    dptr->SortedInsert(NULL, GenerateInt());
    RemoveItems(dptr,itemNum,0);
    printf("IsEmpty? %d\n",dptr->IsEmpty());
    return 0;
}