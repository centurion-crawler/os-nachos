#include "Table.h"

Table::Table(int size)
{
	table_size = size;
	table_lock = new Lock("table lock");
	ind = 0;
	anary = new void*[size];
	for(int i = 0; i < table_size; i++){
		anary[i] = NULL;
	}
}

Table::~Table()
{
	table_size = 0;
	delete (table_lock);
	ind = 0;
	delete (anary);
}

int Table::Alloc(void *object)
{
        table_lock -> Acquire();
	ind = 0;
	while(anary[ind] != NULL && ind < table_size && ind >= 0){
		ind++;
	}
	if(ind >= table_size || ind < 0){
		table_lock -> Release();
                return -1;
	}
	anary[ind] = object;
        printf("( -> %d ) ", ind);
	table_lock -> Release();
	return ind;
}

void *Table::Get(int index)
{
	table_lock -> Acquire();
	if(index < 0 || index >= table_size){
		table_lock -> Release();
		return NULL;
	}
        printf("( [%d] ) ", index);
	table_lock -> Release();
	return anary[index];
}

void Table::Release(int index)
{
	table_lock -> Acquire();
	if(index < 0 || index >= table_size){
		table_lock -> Release();
		return;
	}
        printf(" ( %d ->) ", index);
	anary[index] = NULL;
	table_lock -> Release();
}
