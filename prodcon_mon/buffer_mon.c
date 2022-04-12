#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include "buffer_mon.h"

static ring_buffer_421_t buffer;
pthread_mutex_t mutex;
pthread_cond_t full;
pthread_cond_t empty;
int emptycount;


long init_buffer_421(void){
    if(buffer.read != NULL){ //if buffer is already initalized, init_buffer_421 returns -1 ,fails
        printf("Buffer is already exists\n");
        return -1;
    }else{
        node_421_t *curr;
        emptycount = 20;
        pthread_mutex_init(&mutex, NULL); //initalize the semasphore
        pthread_cond_init(&empty, NULL); //initalize empty
        pthread_cond_init(&full, NULL); //initalize fill
        curr = NULL; //point to current node
        buffer.length = 0; //initalize buffer length to 0
        for(int i = 0; i < SIZE_OF_BUFFER; i++){ //allocate 20 nodes in circular buffer
            node_421_t *newNode = NULL;
            newNode = malloc(sizeof(node_421_t)); //create node
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
        pthread_mutex_lock(&mutex);
        while(buffer.length == SIZE_OF_BUFFER){ //if buffer is  full, enqueue_buffer_421 is blocked
            pthread_cond_wait(&full,&mutex);
        }
        memcpy(buffer.write->data,data,DATA_LENGTH); //add data into write node's data
        buffer.write->data[DATA_LENGTH - 1] = '\0';
        buffer.length++; //increment length
        emptycount--;
        printf("Enqueue: %c\n",buffer.write->data[1]);
        printf("%d items in buffer\n",buffer.length);
        printf("%d empty spaces in buffer\n",emptycount);
        buffer.write = buffer.write->next; //move write to next empty node
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex); //if buffer is no longer full, enqueue_buffer_421 is unlocked and continues function
        return 0;
    }
}

long dequeue_buffer_421(char * data) {
    if (buffer.read == NULL) { //if buffer is not initalized yet, dequeue_buffer_421 returns -1 ,fails
        printf("Buffer does not exist\n");
        return -1;
    }else{
        pthread_mutex_lock(&mutex);
        while(buffer.length == 0){  //if buffer is empty, dequeue_buffer_421 is locked and wait for enqueue_buffer_421 to add nodes
            pthread_cond_wait(&empty,&mutex);
        }
        memcpy(data,buffer.read->data,DATA_LENGTH); //writes pointer write node's data into data
        buffer.length--; //decrements length
        emptycount++;
        printf("Dequeue: %c\n",data[1]);
        printf("%d items in buffer\n",buffer.length);
        printf("%d empty spaces in buffer\n",emptycount);
        buffer.read = buffer.read->next; //move read to next non-empty node
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
        return 0;
    }
}


long delete_buffer_421(void){
    if(buffer.read == NULL){ //if buffer is not initalized yet, delete_buffer_421 returns -1 ,fails
        printf("Buffer does not exist\n");
        return -1;
    }else{
        node_421_t *curr;
        curr = buffer.read; //start at read's node
        for(int i = 0; i < SIZE_OF_BUFFER; i++){ //delete every node in the buffer
            node_421_t *temp;
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
        pthread_cond_destroy(&empty); //destroys semesphores
        pthread_cond_destroy(&full);
        pthread_mutex_destroy(&mutex);
        return 0;
    }
}
