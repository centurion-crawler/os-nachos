#include "synch.h"
class BoundedBuffer {
   public:
     // create a bounded buffer with a limit of 'maxsize' bytes
     BoundedBuffer(int maxsize);
     ~BoundedBuffer();
     // read 'size' bytes from the bounded buffer, storing into 'data'.
     // ('size' may be greater than 'maxsize')
     void Read(void *data, int size);
     
     // write 'size' bytes from 'data' into the bounded buffer.
     // ('size' may be greater than 'maxsize')
     void Write(void *data, int size);
   private:
     Semaphore *not_empty;
	 Semaphore *not_full;
	 Semaphore *mutex;
	 int length;
	 int read;   // index start for Read
	 int write;  // index start for Write
	 int *buffer;
};

