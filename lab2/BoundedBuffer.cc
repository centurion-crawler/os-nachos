#include "BoundedBuffer.h"

BoundedBuffer::BoundedBuffer(int maxsize)
{
	length = maxsize;
	not_empty = new Condition("buffer condition not empty");
	not_full = new Condition("buffer condition not full");
	mutex = new Lock("Buffer Lock");
	buffer = new int[maxsize];
	read = 0;
	write = 0;
        available = length;
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
        mutex -> Acquire();
	if(size > length)
		size = length;
        while(length - available < size)
            not_empty -> Wait(mutex);
	for(int i = 0; i < size; i++){
		*((int *)data + i % length) = *((int *)buffer + (i + read) % length);
	}
        printf("( %d -> %d ) ", read, (read + size) % length);
	read = (read + size) % length;
	available +=  size;
        not_full -> Signal(mutex);
        mutex -> Release();
}

void BoundedBuffer::Write(void *data, int size)
{
        mutex -> Acquire();
	if(size > length)
		size = length;
	while(available < size)
            not_full -> Wait(mutex);
	for(int i = 0; i < size; i++){
		*((int *)buffer + (i + write) % length) = *((int *)data + i % length);
        }
        printf("( %d -> %d ) ", write, (write + size) % length);
        write = (write + size) % length;
        available -= size;
        not_empty -> Signal(mutex);
        mutex -> Release();
}
