#ifndef q_h
#define q_h

struct Queue{
    struct Node* head;
};

struct Node{
    struct Node* next;
    struct Node*  previous;
    int payload;
};




#endif