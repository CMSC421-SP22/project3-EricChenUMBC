Eric Chen LD19338 echen5@umbc.edu CMSC 421 Section 2 Tompkins

How to compile user space:

gcc -pthread buffer_mon.c test_mon.c -o test

 Run with ./test



The way I tackled part 1 is first initializing the buffer like using a for loop to allocate an empty node 20 times. I set buffer length to 0 and linked the last node to the first node to create the circular linked list. I set read and write to point to the first node allocated. Of course, before I do this stuff, I check to see if the buffer is already initialized by the checking of read is NULL or not.

The way I did enqueuing the buffer is first by checking to see if read is NULL or not to see if buffer is initialized yet. Then I copy char  *data passed in the function to write node's data. I then increment the buffer length and I move the pointer write to the next node. I use the POSIX pthread API to lock the critical section so that no other parts of the code can execute its critical section. I used conditional variables empty and full to block the function if the buffer is full.

The way I did dequeuing the buffer is first by checking to see if read is NULL or not to see if buffer is initialized yet. Then I copy read node's data to char  *data passed into function. I then decrement the buffer length and I move the pointer read to the next node. I use the POSIX pthread API to lock the critical section so that no other parts of the code can execute its critical section. I used conditional variables empty and full to block the function if the buffer is full.

The way I deleted the buffer is simply using a for loop from 0 to 20 and deallocating each node and set read and write to NULL and buffer length to 0. I of course first check to see if the read pointer is NULL or not to see if the buffer is initialized yet.

For the producer and consumer problem, I use pthreads. I created and joined these two threads, producer and consumer. For these two, I for loop 1000 to enqueue the buffer in producer and dequeue from buffer in consumer. Each enqueue or dequeue, I print out the data I’m using and show the number of items in the buffer and how many empty spaces are left.

For testing, I checked every edge case I can think of, then ran the producer/consumer thread.
I print out the buffer length and the number of empty spaces to see the status of the buffer after each enqueue and dequeue.
