#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include "buffer_sem.h"

static bb_buffer_421_t buffer;
static struct semaphore mutex;
static struct semaphore fill_count;
static struct semaphore empty_count;
int empty; // number of empty spaces in buffer

SYSCALL_DEFINE0(init_buffer_sem_421){
    bb_node_421_t *curr;
    bb_node_421_t *newNode;
    if(buffer.read != NULL){ //if buffer is already initalized, init_buffer_421 returns -1 ,fails
        printk("Buffer is already exists\n");
        return -1;
    }else{
        int i;
	empty = 20; // number of empty spaces in buffer initizlie to 20
        sema_init(&mutex, 1); //initalize the semasphore
        sema_init(&empty_count, SIZE_OF_BUFFER); //initalize empty_count
        sema_init(&fill_count, 0); //initalize fill_count
        buffer.length = 0; //initalize buffer length to 0
	curr = NULL; //point to current node
        for(i = 0; i < SIZE_OF_BUFFER; i++){ //allocate 20 nodes in circular buffer
            newNode = NULL;
            newNode = kmalloc(sizeof(bb_node_421_t), GFP_KERNEL); //create node
            if (newNode == NULL) { //if Allocation Failure occurs
                printk("Allocation Failure!! \n");
                return -1;
            }
            if(buffer.read == NULL) { //if buffer is empty, create head of the linked list
                buffer.read = newNode; //read and write initalized at head
                buffer.write = newNode;
                curr = buffer.read; //current node initalized at head
            }else{
                curr->next = newNode; //current's next initalized at head
                curr = curr->next;  //increment curr to next node
            }
        }
        curr->next = buffer.read; //link last node's next to the beginning of the list
        return 0;
    }
}


SYSCALL_DEFINE1(enqueue_buffer_sem_421, char*, data){
    if(buffer.read == NULL){ //if buffer is not initalized yet, enqueue_buffer_421 returns -1 ,fails
        printk("Buffer does not exist\n");
        return -1;
    }else{
        down(&empty_count); //if buffer is full, enqueue_buffer_421 is locked and wait for dequeue_buffer_421 to remove nodes
        down(&mutex);
        if(copy_from_user(buffer.write->data, data, DATA_LENGTH) != 0){ //copy_from_user
            printk("Enqueue failed.\n");
        }else{
	    buffer.write->data[DATA_LENGTH - 1] = '\0';
	    printk("Produced: %c\n",buffer.write->data[1]);
	}
	empty--; //decrement number of empty spaces in buffer
        buffer.length++; //increment length
        buffer.write = buffer.write->next; //move write to next empty node
        printk("%d items in buffer\n",buffer.length);
	printk("%d empty spaces in buffer\n",empty);
	up(&mutex);
        up(&fill_count); //if buffer is no longer full, enqueue_buffer_421 is unlocked and continues function
        return 0;
    }
}

SYSCALL_DEFINE1(dequeue_buffer_sem_421, char*, data){
    if (buffer.read == NULL) { //if buffer is not initalized yet, dequeue_buffer_421 returns -1 ,fails
        printk("Buffer does not exist\n");
        return -1;
    }else{
        down(&fill_count); //if buffer is empty, dequeue_buffer_421 is locked and wait for enqueue_buffer_421 to add nodes
        down(&mutex);
        if(copy_to_user(data, buffer.read->data, DATA_LENGTH) != 0){ //copy_to_user
            printk("Dequeue failed.\n");
        }else{
	   printk("Consumed: %c\n",data[1]);
	}
	empty++; //increment number of empty spaces in buffer
        buffer.length--; //decrements length
        buffer.read = buffer.read->next; //move read to next non-empty node
        printk("%d items in buffer\n",buffer.length);
	printk("%d empty spaces in buffer\n",empty);
        up(&mutex);
        up(&empty_count); //if buffer is no longerr empty, dequeue_buffer_421 is unlocked and continues function
        return 0;
    }
}


SYSCALL_DEFINE0(delete_buffer_sem_421){
    if(buffer.read == NULL){ //if buffer is not initalized yet, delete_buffer_421 returns -1 ,fails
        printk("Buffer does not exist\n");
        return -1;
    }else{
        int i;
        bb_node_421_t *curr;
        bb_node_421_t *temp;
        curr = buffer.read; //start at read's node
        for(i = 0; i < SIZE_OF_BUFFER; i++){ //delete every node in the buffer
            if(curr->next != NULL){
                temp = curr->next;
            }else{
                temp = NULL;
            }
            kfree(curr); //free node
            curr = NULL;
            curr = temp;
        }
        buffer.length = 0; //reset vaules
        buffer.read = NULL; //read and write set to null
        buffer.write = NULL;
        return 0;
    }
}

/*

void print_semaphores(void) {
	// You can call this method to check the status of the semaphores.
	// Don't forget to initialize them first!
	// YOU DO NOT NEED TO IMPLEMENT THIS FOR KERNEL SPACE.
	int value;
	sem_getvalue(&mutex, &value);
	printk("sem_t mutex = %d\n", value);
	sem_getvalue(&fill_count, &value);
	printk("sem_t fill_count = %d\n", value);
	sem_getvalue(&empty_count, &value);
	printk("sem_t empty_count = %d\n", value);
	return;
}

*/
