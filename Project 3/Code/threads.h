//name : Erick Enriquez
#ifndef threads_h
#define threads_h
#include "q.h"
#include <stdio.h>


/*global queue */
struct Queue* runQ;

void start_thread(void (*function)(void)){
	void * stack = malloc(8192);
	TCB_t * temp = (TCB_t *) malloc(sizeof(TCB_t));
	init_TCB(temp, function, stack, 8192);
	AddItem(runQ, temp);

}



void run(){//run the context
	ucontext_t parent;
	getcontext(&parent);
	swapcontext(&parent, &(runQ->head->context));

}


void yield(){
	ucontext_t *current, *next;
	/* save the current context in the context stuct and rotate the queue to allow the next thread to run */
	current = &runQ->head->context;
	RotateQueue(runQ);

	/* next thread is now at head, because we rotated */
	next = &runQ->head->context;
	swapcontext(current, next);
}

#endif 