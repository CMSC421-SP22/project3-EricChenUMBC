#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"

static ring_buffer_421_t buffer;


long init_buffer_421(void){
    if(buffer.read != NULL){ //if buffer is already initalized, init_buffer_421 returns -1 ,fails
        printf("Buffer already exists\n");
        return -1;
    }else{
        node_421_t *curr = NULL; //point to current node
        buffer.length = 0; //initalize buffer length to 0
        for(int i = 0; i < SIZE_OF_BUFFER; i++){ //allocate 20 nodes in circular buffer
            node_421_t *newNode = NULL;
            newNode = malloc(sizeof(node_421_t)); //create node
            if (newNode == NULL) { //if Allocation Failure occurs
                printf("Allocation Failure!! \n");
                return -1;
            }
            newNode->data = 0; //initalize node's data to 0
            if(buffer.read == NULL) {
                buffer.read = newNode; //if buffer is empty, create head of the linked list
                buffer.write = newNode; //read and write initalized at head
                curr = buffer.read; //current node initalized at head
            }else{
                curr->next = newNode; //current's next initalized at head
                curr->data = 0; //initalize node's data to 0
                curr = curr->next; //increment curr to next node
            }
        }
        curr->next = buffer.read; //link last node's next to the beginning of the list
        return 0;
    }
}

long insert_buffer_421(int i){
    if(buffer.read == NULL){ //if buffer is not initalized yet, insert_buffer_421 returns -1 ,fails
        printf("Buffer does not exist\n");
        return -1;
    }else{
        if(buffer.length == 20){ //if buffer is full, insert_buffer_421 returns -1 ,fails
            printf("Buffer is full\n");
            return -1;
        }else{
            buffer.write->data = i; //add input number i into write node's data
            buffer.length++; //increment length
            buffer.write = buffer.write->next; //move write to next empty node
            return 0;
        }
    }
}

long print_buffer_421(void){
    if(buffer.read == NULL){ //if buffer is not initalized yet, print_buffer_421 returns -1 ,fails
        printf("Buffer does not exist\n");
        return -1;
    }else{
        node_421_t *curr = buffer.read; //start at read's node
        for(int i = 0; i < buffer.length; i++){ //print every node in the buffer
            printf("Current node in buffer: %d\n",curr->data);
            curr = curr->next;
        }
        return 0;
    }
}

long delete_buffer_421(void){
    if(buffer.read == NULL){ //if buffer is not initalized yet, delete_buffer_421 returns -1 ,fails
        printf("Buffer does not exist\n");
        return -1;
    }else{
        node_421_t *curr = buffer.read; //start at read's node
        for(int i = 0; i < SIZE_OF_BUFFER; i++){ //delete every node in the buffer
            node_421_t *temp;
            if(curr->next != NULL){
                temp = curr->next;
            }else{
                temp = NULL;
            }
            curr->data = 0;
            free(curr); //free node
            curr = NULL;
            curr = temp;
        }
        buffer.length = 0; //reset vaules
        buffer.read = NULL; //read and write set to null
        buffer.write = NULL;
        return 0;
    }
}
