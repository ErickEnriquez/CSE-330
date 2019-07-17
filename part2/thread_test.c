//name : Erick Enriquez
#include "threads.h"

int Global_Counter;

void function1();
void function2();
void function3();

int main(int argc , char** argv){

    Global_Counter = 0;
    runQ = (struct Queue*)malloc(sizeof(struct Queue));//allocate the head pointer
    InitQueue(runQ);//initilize the runQ pointer to NULL
    start_thread(function1);
    start_thread(function2);
    start_thread(function3);
    run();
    return 0;

}

//-----------------
// INFINITE COUNTER
//-----------------
void function1(){
    int localCounter = 1;
    while(1){
        
        printf("Global Counter %d",Global_Counter);
        printf("\nLocal Counter %d\n",localCounter);
        localCounter++;
        Global_Counter++;
        sleep(1);//sleep so that you can see it in action and not have it going crazy fast
        yield();
    }
}

//-----------------
// INFINITE TEXT
//-----------------
void function2(){
    while(1){
        printf("time for thread 2\n");
        sleep(1);
        yield();
    }
}

//-------------- 
// Reset Global Counter
//-------------
void function3(){
    while (1){
        printf("Reset Global Counter to  %d \n",Global_Counter);
        Global_Counter--;
        sleep(1);
        yield();
    }
    
}
