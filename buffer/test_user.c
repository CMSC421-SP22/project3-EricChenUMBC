#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"


int main() { //Test cases
    printf("Testing inserting before initalizing\n");
    if(insert_buffer_421(0) == -1){
        printf("Test passed\n");
    }else{
        printf("Test failed\n");
    }
    printf("Testing printing before initalizing\n");
    if(print_buffer_421() == -1){
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
    printf("Testing initalizing, and adding nodes\n");
    init_buffer_421();
    for(int i = 0; i < SIZE_OF_BUFFER; i++){
        if(insert_buffer_421(i) == -1){
            printf("Test failed\n");
        }
    }
    print_buffer_421();
    printf("Testing adding an extra node to full buffer\n");
    if(insert_buffer_421(20) == -1){
        printf("Test passed\n");
    }else{
        printf("Test failed\n");
    }

    printf("Test deleting buffer\n");
    if(delete_buffer_421() == -1){
        printf("Test failed\n");
    }else{
        printf("Test passed\n");
    }

    printf("Testing adding an extra node to deleted buffer\n");
    if(insert_buffer_421(20) == -1){
        printf("Test passed\n");
    }else{
        printf("Test failed\n");
    }

    printf("Testing printing deleted buffer\n");
    if(print_buffer_421() == -1){
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

    printf("Testing initalizing and initalizing again\n");
    init_buffer_421();
    if(init_buffer_421() == -1){
        printf("Test passed\n");
    }else{
        printf("Test failed\n");
    }

    printf("Testing inserting some nodes, and deleting\n");
    for(int i = 1; i <=5; i++){
        if(insert_buffer_421(i) == -1){
            printf("Test failed\n");
        }
    }
    print_buffer_421();
    if(delete_buffer_421() == -1){
        printf("Test failed\n");
    }else{
        printf("Test passed\n");
    }

    return 0;
}
