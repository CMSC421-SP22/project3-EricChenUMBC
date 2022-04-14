Eric Chen LD19338 echen5@umbc.edu CMSC 421 Section 2 Tompkins

How to compile user space:

gcc buffer_user.c test_user.c -o test_user

 Run with ./test_user

How to compile kernel space:

gcc test.c -o test

Run with ./test

The way I tackled part 1 at the beginning for initializing the buffer is by using a for loop to allocate an empty node with initial value of 0 20 times. I set buffer length to 0 and linked the last node to the first node to create the circular linked list. I set read and write to point to the first node allocated. Of course, before I do this stuff, I check to see if the buffer is already initialized by the checking of read is NULL or not.

The way I did inserting the buffer is first by checking to see if read is NULL or not to see if buffer is initialized yet. Then I set int i passed in this function to equal data from the node pointed by write. I then increment buffer length and move write to point to the next node.

The way I done print buffer is first by checking to see if read is NULL or not to see if buffer is initialized yet. Then I used a for loop to print each node’s data starting from the node pointed by read to the last or 20th node. This is done by looping from 0 to 20.

The way I deleted the buffer is by simply using a for loop from 0 to 20 and deallocating each node and set read and write to NULL and buffer length to 0. I of course first check to see if the read pointer is NULL or not to see if the buffer is initialized yet.

For testing, I check every edge case I can think of and then test each function in general and use print_buffer to see the buffer.
