#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include "buffer_sem.h"

static bb_buffer_421_t buffer;
static sem_t mutex;
static sem_t fill_count;
static sem_t empty_count;

long init_buffer_421(void){
    if(buffer.read != NULL){ //if buffer is already initalized, init_buffer_421 returns -1 ,fails
        printf("Buffer is already exists\n");
        return -1;
    }else{
        sem_init(&mutex, 0, 1); //initalize the semasphore
        sem_init(&empty_count, 0, SIZE_OF_BUFFER); //initalize empty_count
        sem_init(&fill_count, 0, 0); //initalize fill_count
        bb_node_421_t *curr = NULL; //point to current node
        buffer.length = 0; //initalize buffer length to 0
        for(int i = 0; i < SIZE_OF_BUFFER; i++){ //allocate 20 nodes in circular buffer
            bb_node_421_t *newNode = NULL;
            newNode = malloc(sizeof(bb_node_421_t)); //create node
            if (newNode == NULL) { //if Allocation Failure occurs
                printf("Allocation Failure!! \n");
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


long enqueue_buffer_421(char * data) {
    if(buffer.read == NULL){ //if buffer is not initalized yet, enqueue_buffer_421 returns -1 ,fails
        printf("Buffer does not exist\n");
        return -1;
    }else{
        sem_wait(&empty_count); //if buffer is full, enqueue_buffer_421 is locked and wait for dequeue_buffer_421 to remove nodes
        sem_wait(&mutex);
        strncpy(buffer.write->data,data,DATA_LENGTH); //add data into write node's data
        buffer.length++; //increment length
        buffer.write = buffer.write->next; //move write to next empty node
        printf("%d items in buffer\n",buffer.length);
	    sem_post(&mutex);
        sem_post(&fill_count); //if buffer is no longer full, enqueue_buffer_421 is unlocked and continues function
        return 0;
    }
}

long dequeue_buffer_421(char * data) {
    if (buffer.read == NULL) { //if buffer is not initalized yet, dequeue_buffer_421 returns -1 ,fails
        printf("Buffer does not exist\n");
        return -1;
    }else{
        sem_wait(&fill_count); //if buffer is empty, dequeue_buffer_421 is locked and wait for enqueue_buffer_421 to add nodes
        sem_wait(&mutex);
        strcpy(data,buffer.read->data); //writes pointer write node's data into data
        buffer.length--; //decrements length
        buffer.read = buffer.read->next; //move read to next non-empty node
	    printf("%d items in buffer\n",buffer.length);
	    sem_post(&mutex);
        sem_post(&empty_count); //if buffer is no longerr empty, dequeue_buffer_421 is unlocked and continues function
        return 0;
    }
}


long delete_buffer_421(void){
    if(buffer.read == NULL){ //if buffer is not initalized yet, delete_buffer_421 returns -1 ,fails
        printf("Buffer does not exist\n");
        return -1;
    }else{
        bb_node_421_t *curr = buffer.read; //start at read's node
        for(int i = 0; i < SIZE_OF_BUFFER; i++){ //delete every node in the buffer
            bb_node_421_t *temp;
            if(curr->next != NULL){
                temp = curr->next;
            }else{
                temp = NULL;
            }
            free(curr); //free node
            curr = NULL;
            curr = temp;
        }
        buffer.length = 0; //reset vaules
        buffer.read = NULL; //read and write set to null
        buffer.write = NULL;
        sem_destroy(&empty_count); //destroys semesphores
        sem_destroy(&fill_count);
        sem_destroy(&mutex);
        return 0;
    }
}

void print_semaphores(void) {
	// You can call this method to check the status of the semaphores.
	// Don't forget to initialize them first!
	// YOU DO NOT NEED TO IMPLEMENT THIS FOR KERNEL SPACE.
	int value;
	sem_getvalue(&mutex, &value);
	printf("sem_t mutex = %d\n", value);
	sem_getvalue(&fill_count, &value);
	printf("sem_t fill_count = %d\n", value);
	sem_getvalue(&empty_count, &value);
	printf("sem_t empty_count = %d\n", value);
	return;
}
