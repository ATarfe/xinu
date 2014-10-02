#include	<stddef.h>		
#include	<stdio.h>						
#include  <semaphore.h> //include/semaphore.h
/*Global	vaible	for	producer	consumer*/		
extern int n;

//semaphores:
extern semaphore sem_producer;
extern semaphore sem_consumer;
extern semaphore mutex;
 
/*function	Prototype*/
void consumer(int count);	
void producer(int count);	
