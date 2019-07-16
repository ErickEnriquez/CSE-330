#include "threads.h"



int Global_Counter;

void function1();
void function2();
void function3();

int main(int argc , char** argv){

    runQ = (struct Queue*)malloc(sizeof(struct Queue));//allocate the head pointer
    InitQueue(runQ);//initilize the runQ pointer to NULL
    start_thread(function1);
    start_thread(function2);
    start_thread(function3);
    run();
    return 0;

}

void function1(){
    while(1){
        printf("function1\n");
        sleep(1);
        yield();
    }
}

void function2(){
    while(1){
        printf("function2\n");
        sleep(1);
        yield();
    }
}

void function3(){
    while (1){
        printf("function3\n");
        sleep(1);
        yield();
    }
    
}
