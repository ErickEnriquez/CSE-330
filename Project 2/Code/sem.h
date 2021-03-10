//Name : Erick Enriquez
#ifndef sem_h
#define sem_h

#include "threads.h"

////////////////
//DATA STRUCTURE
////////////////
struct Semaphore{

    int value;//value of the semaphore for P() and V()
    struct Queue * myQueue;//queue of processes

};


///////////
//INITSEM
///////////
void InitSem(struct Semaphore* sem , int number){
    
    sem->myQueue = (struct Queue*)malloc(sizeof(struct Queue));//initialize queue

    InitQueue(sem->myQueue);//intialize the head of queue;

    sem->value = number;//set the value to be the number
}

//////////
//  P
//////////
void P(struct Semaphore* sem){

    struct TCB_t* temp;//make a temp tcb 
    sem->value--;
    // Check if the semaphore value is less than 1
	if (sem->value < 0) {
		temp = DelQueue(runQ);//grab thread from runQ
		AddItem(sem->myQueue, temp);// Block the thread
		swapcontext(&(temp->context), &(runQ->head->context));// Swap processes 
	}
}

////////////////
// V
////////////////
void V(struct Semaphore *sem) {
	
	struct TCB_t *temp; //make a temp tcb
	sem->value++;
	if (sem->value <= 0) {//check if the semaphore is positive
		temp = DelQueue(sem->myQueue);//hold the tcb in the queue of the semaphore
		AddItem(runQ, temp);//put proccess in run queue
	}
	// swap thread
	yield();
}


#endif