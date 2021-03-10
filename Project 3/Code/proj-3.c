
// Name : Erick Enriquez

#include "sem.h"

//thread functions 
void w1();
void w2();
void r1();
void r2();
void r3();

int shared_int;// this int will be what the readers read and what the writers write, i.e critical section

struct Semaphore *rsem, *wsem, *mutex;
int wwc, rwc, wc, rc = 0;//these are the read wait counter , the write wait counter , the read counter , and the write counter


int main(){
	runQ = (struct Queue*) malloc(sizeof(struct Queue));//allocate the Queue for the running proccesses
	InitQueue(runQ);//initialize it to be null

	//allocate memory for the 3 semaphores
	rsem = (struct Semaphore*) malloc(sizeof(struct Semaphore));
	wsem = (struct Semaphore*) malloc(sizeof(struct Semaphore));
	mutex = (struct Semaphore*) malloc(sizeof(struct Semaphore));

	InitSem(rsem, 0);
	InitSem(wsem, 1);//initialize to 1 or we end up with deadlock
	InitSem(mutex, 1);

	start_thread(w1);
	start_thread(r1);
	start_thread(w2);
	start_thread(r2);
	start_thread(r3);


	run();//run the threads

}



void w1(){
	int num = 1;//number of the writer
	for(;;){//infinite loop
		 shared_int = rand();//set our shared value to a random number
		P(mutex);//lock down the mutex
		if(rc > 0 || wc > 0){//if there are readers or writers ready wait 
			printf("Writer %d blocked, as read count=%d, write count=%d\n", num, rc, wc);
			wwc++;
			V(mutex);//unlock the the mutex semaphore
			P(wsem);//lock the write semaphore so only 1 can be writing at once
			wwc--;//remove it to the write wait count
		}
		wc++;//add 1 to the writer count
		printf("Writer %d enters critical section\n", num);
		V(mutex);//unlock the mutex sem
		printf("Writer %d writes %d in the variable\n", num, shared_int);
		P(mutex);
		wc--;//its done writing do remove it from the count
		printf("Writer %d exiting critical section\n", num);
		if(rwc > 0)//if there are readers waiting unlock the reader
			V(rsem);
		else if(wwc > 0)//if there are no readers waiting and no writers waiting 
			V(wsem);//unlock the writer to go again
		else
			V(mutex);//unlock the mutex
		sleep(2);
	}

}

void w2(){
	int num = 2;
	for(;;){
		 shared_int = rand();//generate random number
		P(mutex);//lock down the mutex
		if(rc > 0 || wc > 0){//if there are readers or writers ready wait
			printf("Writer %d blocked, as read count=%d, write count=%d\n", num, rc, wc);
			wwc++;
			V(mutex);//unlock the the mutex semaphore
			P(wsem);//lock the write semaphore so only 1 can be writing at once
			wwc--;//remove it to the write wait count
		}
		wc++;//add 1 to the writer count
		printf("Writer %d enters critical section \n", num);
		V(mutex);//unlock the mutex sem
		printf("Writer %d writes %d in the variable\n", num, shared_int);
		P(mutex);
		wc--;//its done writing do remove it from the count
		printf("Writer %d exiting critical section\n", num);
		if(rwc > 0)//if there are readers waiting unlock the reader
			V(rsem);
		else if(wwc > 0)//if there are no readers waiting and no writers waiting 
			V(wsem);//unlock the writer to go again
		else
			V(mutex);//unlock the mutex
		sleep(2);
	}

}


void r1(){
	int num = 1;
	for(;;){
		P(mutex);
		if(wwc > 0 || wc > 0){//if there are writers ready and waiting defer to them
			printf("Reader %d blocked, as write wait count=%d, write count=%d\n", num, wwc, wc);
			rwc++;
			V(mutex);//unlock the mutex
			P(rsem);//lock the read semaphore
			rwc--;
		}
		rc++;
		if(rwc > 0)//if there are readers waiting unlock the read semaphore
			V(rsem);
		else
			V(mutex);//unlock the mutex
		printf("Reader %d reads %d from the variable\n", num, shared_int);
		P(mutex);
		rc--;
		printf("Reader %d exiting critical section\n", num);
		if(rc == 0 && wwc > 0)// if there no readers and there are writers waiting
			V(wsem);//unlock the writer
		else
			V(mutex);
		sleep(2);
	}

}

void r2(){
	int num = 2;
	for(;;){
		P(mutex);
		if(wwc > 0 || wc > 0){//if there are writers ready and waiting defer to them
			printf("Reader %d blocked, as write wait count = %d, write count =%d\n", num, wwc, wc);
			rwc++;
			V(mutex);//unlock the mutex
			P(rsem);//lock the read semaphore
			rwc--;
		}
		rc++;
		if(rwc > 0)//if there are readers waiting unlock the read semaphore
			V(rsem);
		else
			V(mutex);//unlock the mutex
		printf("Reader %d reads %d from the variable\n", num, shared_int);
		P(mutex);
		rc--;
		printf("Reader %d exiting critical section\n", num);
		if(rc == 0 && wwc > 0)// if there no readers and there are writers waiting
			V(wsem);//unlock the writer
		else
			V(mutex);
		sleep(2);
	}
}

void r3() {
	int num = 3;
	for(;;){
		P(mutex);
		if(wwc > 0 || wc > 0){//if there are writers ready and waiting defer to them
			printf("Reader %d blocked, as write wait count=%d, write count =%d\n", num, wwc, wc);
			rwc++;
			V(mutex);//unlock the mutex
			P(rsem);//lock the read semaphore
			rwc--;
		}
		rc++;
		if(rwc > 0)//if there are readers waiting unlock the read semaphore
			V(rsem);
		else
			V(mutex);//unlock the mutex
		printf("Reader %d reads %d from the variable\n", num, shared_int);
		P(mutex);
		rc--;
		printf("Reader %d exiting critical section\n", num);
		if(rc == 0 && wwc > 0)// if there no readers and there are writers waiting
			V(wsem);//unlock the writer
		else
			V(mutex);
		sleep(2);
	}
}
