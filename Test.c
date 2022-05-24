#include <netinet/in.h> //structure for storing address information
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>
#include "TestStack.h"
int counter = 0;
void *newFunc1(void* txt){
    int curr = *((int*)txt);
    push(curr);
    counter+=curr;
}

void *newFunc2(){
    int poped = pop();
    counter-=poped;
}

int main(int argc, char const* argv[]) {
    initialize();
    int counter = 0;
    for (int i = 1; i <= 100; ++i) {
        pid_t x = fork();
        int *value = (int*)malloc(sizeof (int));
        *value = i;
        if(x==0){
            newFunc1(value);
        }
        else{
            sleep(0.01);
        }
        free(value);
    }
    for (int i = 1; i <= 100; ++i) {
        pid_t x = fork();
        if(x==0){
            newFunc2();
        }
        else{
            sleep(0.01);
        }
    }
    sleep(3);
    if(counter == 0 ){
        printf("Success!\n");
    }
    else{
        printf("Failure...\n");
    }
    return 0;
}