#ifndef Threads_H
#define Threads_H
#include "q.h"

struct Queue *runQ;


void start_thread(void(*funtion)(void)){
    void *stack = (void*)malloc(8192);
    TCB_t *temp = NewItem();
    init_TCB(temp,function,stack,8192);
    AddItem(runQ, temp);
    return;
}

void run() {
	ucontext_t from, to;
	ucontext_t parent;
	from = parent;
	getcontext(&parent);
	to = (runQ->head->context);
	swapcontext(&parent, &(runQ->head->context));

	return;
}

void run() {
	ucontext_t from, to;
	ucontext_t parent;
	from = parent;
	getcontext(&parent);
	to = (runQ->head->context);
	swapcontext(&parent, &(runQ->head->context));

	return;
}



#endif