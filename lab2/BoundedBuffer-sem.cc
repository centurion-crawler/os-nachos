#include "BoundedBuffer.h"

BoundedBuffer::BoundedBuffer(int maxsize)
{
	length = maxsize;
	not_empty = new Semaphore("buffer sem not empty", 0);
	not_full = new Semaphore("buffer sem not full", maxsize);
	mutex = new Semaphore("buffer sem mutex", 1);
	buffer = new int[maxsize];
	read = 0;
	write = 0;
}

BoundedBuffer::~BoundedBuffer()
{
	delete (not_empty);
	delete (not_full);
	delete (mutex);
	delete (buffer);
	length = 0;
}

void BoundedBuffer::Read(void *data, int size)
{
	if(size > length)
		size = length;
        printf("stuck begins %d\n", size);
        for(int i = 0; i < size; i++){
		not_empty -> P();
	}
        printf("finished stuck\n");
	mutex -> P();
	for(int i = 0; i < size; i++){
		*((int *)data + i % length) = *((int *)buffer + (i + read) % length);
	}
	read = (read + size) % length;
	mutex -> V();
	for(int i = 0; i < size; i++){
		not_full -> V();
	}
}

void BoundedBuffer::Write(void *data, int size)
{
	if(size > length)
		size = length;
	for(int i = 0; i < size; i++){
		not_full -> P();
	}
	mutex -> P();
	for(int i = 0; i < size; i++){
		*((int *)buffer + (i + write) % length) = *((int *)data + i % length);
	}
	write = (write + size) % length;
	mutex -> V();
	for(int i = 0; i < size; i++){
		not_empty -> V();
	}
}
