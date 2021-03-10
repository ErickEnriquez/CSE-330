
//name : Erick Enriquez
#include "sem.h"
#include "threads.h"


/////////////////////
// Function prototypes
////////////////////
void func_1();
void func_2();
void func_3();

struct Semaphore* sem;
int Variable = 0;

int main(int argc , char** argv){
	printf("Starting Program\n\n");
	runQ = (struct Queue*)malloc(sizeof(struct Queue));//allocate the head pointer
	InitQueue(runQ);//initialize queue
	sem = (struct Semaphore*)malloc(sizeof(struct Semaphore));//allocate the semaphore pointer
	InitSem(sem ,1);//initialize queue
	start_thread(func_1);
	start_thread(func_2);
	start_thread(func_3);
	run();

	return 0;
}


void func_1(){
	int x = 1;
	for(;;){
		printf("Entering critical section\n");
		P(sem);//start critical section
		Variable++;
		x = x*3;
		printf("Global Variable at function 1 is %d Local Variable is %d\n\n", Variable,x );
		sleep(1);
		printf("Exiting critical section\n\n");
		V(sem);//end critical section
		}
}


void func_2(){
	int x = 0;
	for(;;){
		printf("Entering critical section\n");
		P(sem);
		x = x+2;
		x= x%5;//modulo of x
		Variable = Variable+ 2;
		printf("Global Variable at function 2 is %d Local Variable is %d\n\n", Variable,x);
		sleep(1);
		printf("Exiting critical section\n\n");
		V(sem);//end critical section
	}
}

void func_3(){
	int x= 0;
	for(;;){
		printf("Entering critical section\n");
		P(sem);//start critical section
		Variable = Variable * 2;//double the global Variable
		x--;
		printf("Global Variable at function 3 is %d Local Variable is %d\n\n", Variable,x);
		sleep(1);
		printf("Exiting critical section\n\n ");
		V(sem);//end critical section
	}
}




