Eric Chen LD19338 echen5@umbc.edu CMSC 421 Section 2 Tompkins

How to compile user space:

gcc -pthread buffer_user_sem.c test_user_sem.c -o test_user

 Run with ./test_user

How to compile kernel space:

gcc -pthread test_sem.c -o test

Run with ./test


The way I tackled part 1 is first initializing the buffer by using a for loop to allocate an empty node 20 times. I set buffer length to 0 and linked the last node to the first node to create the circular linked list. I set read and write to point to the first node allocated. Of course, before I do this stuff, I check to see if the buffer is already initialized by the checking of read is NULL or not.

The way I did enqueuing the buffer is first by checking to see if read is NULL or not to see if buffer is initialized yet. Then I copy char *data passed in the function to write node's data. I then increment the buffer length and I move the pointer write to the next node. I use semaphores to lock the critical section so that no other parts of the code can execute its critical section and I increment the fill count and decrement empty count. If the buffer is full or fill count is 20 or the empty count is 0, the enqueue function is blocked and it waits for dequeue to remove data so that there will be empty spaces again.

The way I did dequeuing the buffer is first by checking to see if read is NULL or not to see if buffer is initialized yet. Then I copy read node's data to char *data passed into function. I then decrement the buffer length and I move the pointer read to the next node. I use semaphores to lock the critical section so that no other parts of the code can execute its critical section and I decrement the fill count and increment empty count. If the buffer is empty or fill count is 0 or the empty count is 20, the dequeue function is blocked and it waits for enqueue to insert data so that there will be available data to read again.

The way I deleted the buffer is simply using a for loop from 0 to 20 and deallocating each node and set read and write to NULL and buffer length to 0. I of course first check to see if the read pointer is NULL or not to see if the buffer is initialized yet.

For the producer and consumer problem, I use pthreads. I created and joined these two threads, producer and consumer. For these two, I for loop 1000 to enqueue the buffer in producer and dequeue from buffer in consumer. Each enqueue or dequeue, I print out the data I’m using and print semaphores to show the number of items in the buffer and how many empty spaces are left.

For testing, I checked every edge case I can think of, then ran the producer/consumer thread.
I print out the buffer length and the number of empty spaces to see the status of the buffer after each enqueue and dequeue.
