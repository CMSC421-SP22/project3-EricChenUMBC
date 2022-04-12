#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include "buffer_mon.h"
void *producer();
void *consumer();

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
    char datain[1024];
    printf("Testing enqueuing the buffer\n");
    for(int j = 0; j < 1024; j++){ //create a data of num of a size of 1024
        datain[j] = '1';
    }
    if(enqueue_buffer_421(datain) == 0){
        printf("Test passed\n");
        printf("Produced: %c\n",datain[1]);
    }else{
        printf("Test failed\n");
    }
    char dataout[1024];
    printf("Testing dequeuing the buffer\n");
    if(dequeue_buffer_421(dataout) == 0){
        printf("Test passed\n");
        printf("Consumed: %s\n",dataout);
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
    printf("Testing deleting a buffer\n");
    if(delete_buffer_421() == 0){
        printf("Test passed\n");
    }else{
        printf("Test failed\n");
    }


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



void *producer(){
    int num = 0; //num in data, goes from 0-9
    for(int i = 0; i < 1000; i++){ //loops 1000 times
        usleep(rand() % 10000); //waits for 0-10 millseconds
        char data[1024];
        for(int j = 0; j < 1024; j++){ //create a data of num of a size of 1024
            data[j] = num + '0';
        }
        printf(":: Enqueueing element into buffer. ::\n");
        enqueue_buffer_421(data); //add data
        num++; //increment number
        if(num >= 10){ //if num is 10, reset to 0
            num = 0;
        }
    }
}


void *consumer(){
    for(int i = 0; i < 1000; i++){ //loops 1000 times
        usleep(rand() % 10000); //waits for 0-10 millseconds
        char data[1024];
        printf(":: Dequeueing element from buffer. ::\n");
        dequeue_buffer_421(data); //gets data from buffer
        printf("Consumed: %s\n",data);
    }
}
