//Erick Enriquez
#include "q.h"

int main(){
    printf("running\n");
    struct Queue* list = (struct Queue*)malloc(sizeof(struct Queue));
    InitQueue(list);
    int i = 0 ; 
    while(i <5){
        struct Node* temp = NewItem();
        temp->data = i;
        i++;
        AddItem(list,temp);
    }
    while (i >0){
        printf("%d \n", list->head->data);
        RotateQueue(list);
        i--;
    }
   return 0 ;
    
}