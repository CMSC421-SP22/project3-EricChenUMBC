#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include "buffer_sem.h"

void *producer(void*);
void *consumer(void*);

#define NR_init_buffer_sem_421 446
#define NR_enqueue_buffer_sem_421 447
#define NR_dequeue_buffer_sem_421 448
#define NR_delete_buffer_sem_421 449

long init_buffer_421(void) {
    return syscall(NR_init_buffer_sem_421);
}

long enqueue_buffer_421(char* data) {
    return syscall(NR_enqueue_buffer_sem_421, data);
}

long dequeue_buffer_421(char* data) {
    return syscall(NR_dequeue_buffer_sem_421, data);
}

long delete_buffer_421(void) {
    return syscall(NR_delete_buffer_sem_421);
}
int main() {
    printf("Testing enqueuing before initalizing\n");
    if(enqueue_buffer_421("DATA") == -1){
        printf("Test passed\n");
    }else{
        printf("Test failed\n");
    }
    
    printf("Testing dequeuing before initalizing\n");
    if(dequeue_buffer_421("DATA") == -1){
        printf("Test passed\n");
    }else{
        printf("Test failed\n");
    }
    
    printf("Testing deleting before initalizing\n");
    if(delete_buffer_421() == -1){
        printf("Test passed\n");
    }else{
        printf("Test failed\n");
    }
    
    printf("Testing initalizing and initalizing again\n");
    init_buffer_421();
    if(init_buffer_421() == -1){
        printf("Test passed\n");
    }else{
        printf("Test failed\n");
    }
    delete_buffer_421();
    
    init_buffer_421();
    pthread_t producerthread;
    pthread_t consumberthread;
    pthread_create(&producerthread, NULL, &producer, NULL);
    pthread_create(&consumberthread, NULL, &consumer, NULL);
    pthread_join(producerthread, NULL);
    pthread_join(consumberthread, NULL);
    delete_buffer_421();
    
    printf("Testing enqueuing an extra node to deleted buffer\n");
    if(enqueue_buffer_421("DATA") == -1){
        printf("Test passed\n");
    }else{
        printf("Test failed\n");
    }
    
    printf("Testing dequeuing an extra node to deleted buffer\n");
    if(dequeue_buffer_421("DATA") == -1){
        printf("Test passed\n");
    }else{
        printf("Test failed\n");
    }
    
    printf("Testing deleting an already deleted buffer\n");
    if(delete_buffer_421() == -1){
        printf("Test passed\n");
    }else{
        printf("Test failed\n");
    }
    
    return 0;
}


void *producer(void*){
    int num = 0; //num in data, goes from 0-9
    for(int i = 0; i < 1000; i++){ //loops 1000 times
        usleep(rand() % 10000); //waits for 0-10 millseconds
        char data[1024];
        for(int j = 0; j < DATA_LENGTH; j++){ //create a data of num of a size of 1024
            data[j] = num + '0';
        }
        data[DATA_LENGTH - 1] = '\0'; //null termaintor
        printf(":: Enqueueing element into buffer. ::\n");
        enqueue_buffer_421(data); //add data
        printf("%s\n",data);
        num++; //increment number
        if(num >= 10){ //if num is 10, reset to 0
            num = 0;
        }
    }
}


void *consumer(void*){
    for(int i = 0; i < 1000; i++){ //loops 1000 times
        usleep(rand() % 10000); //waits for 0-10 millseconds
        char data[1024];
        printf(":: Dequeueing element from buffer. ::\n");
        if(dequeue_buffer_421(data) == 0){ //gets data from buffer
            printf("%s\n",data);
        }
    }
}


