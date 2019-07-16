#include "q.h"
#include <stdio.h>
#define STACK_SIZE 8192

/*global queue */
struct Queue* runQ;

void start_thread(void (*function)(void)){
	void * stack = malloc(STACK_SIZE);
	TCB_t * tcb = (TCB_t *) malloc(sizeof(TCB_t));
	init_TCB(tcb, function, stack, STACK_SIZE);
	
	/* Add the TCB to the thread Q */
	AddItem(runQ, tcb);

}



void run(){
	ucontext_t parent;
	getcontext(&parent);
	swapcontext(&parent, &(runQ->head->context));

}


void yield(){
	ucontext_t *current, *next;
	/* save the current context in the context struct
		of the currently executing thread
		(ie. the thread at the front of the runQ when yield is called == the tail after rotating)
		and activate the context of the next thread
		(ie. the thread at the front of th runQ after rotating) */
	current = &runQ->head->context;
	RotateQueue(runQ);

	/* next thread is now at head, because we rotated */
	next = &runQ->head->context;
	swapcontext(current, next);
}