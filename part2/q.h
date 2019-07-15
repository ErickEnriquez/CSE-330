#ifndef q_h
#define q_h
#include <stdio.h>
#include <stdlib.h>
#include "tcb.h"



struct Queue{
    struct TCB_t*  head;
};

//-----------
//--NEW ITEM
//-----------

//Creates a new TCB_t pointer and initializes the variables
struct TCB_t* NewItem(){
    struct TCB_t* temp = (struct TCB_t*)malloc(sizeof(struct TCB_t));
    temp->next = NULL;
    temp->prev = NULL;
    return temp;

}
 
//-----------
// INIT QUEUE
//------------

//creates an empty queue pointed to by the head variable
void InitQueue(struct Queue* head){
    head->head = NULL;//set the head to be null initially
    return;
}

//----------
// ADD ITEM
//----------

void AddItem(struct Queue* head, struct TCB_t* item){
    if(head->head == NULL){//if queue is empty then add the item at the head
        head->head = item;
        return;
    }
    //if the head is not null
    else if(head->head != NULL){
        struct TCB_t* temp  = head->head;
        while(temp->next != NULL){//move until we get to last element 
            temp = temp->next;
        }
        temp->next = item;//set item at end of list
        item->prev = temp;//make item point to the previous tail
        return;
    }
}

//-----------
// DEL QUEUE
//-----------

struct TCB_t* DelQueue(struct Queue* head){
    if(head->head == NULL)
        return NULL;
    else{
        struct TCB_t* temp = head->head;
        head->head = head->head->next;//unlink previous head from the queue
        return temp;//return unlinked element
    }
}

//this function moves the head pointer to the next element in the queue and places the previous head at the end of the queue
void RotateQueue(struct Queue* head){
    if(head->head == NULL){
        return ;
    }
    else{
        struct TCB_t* item = head->head;//move the head to the back of the queue
        head->head = head->head->next;
        struct TCB_t* temp = head->head;
        item->next = NULL;
        item->prev = NULL;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = item;
        item->prev = temp;
        return;
    }
    
}



#endif