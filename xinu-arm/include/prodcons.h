#include	<stddef.h>		
#include	<stdio.h>						
#include  <semaphore.h> //include/semaphore.h
/*Global	vaible	for	producer	consumer*/		
extern int n;

//semaphores:
extern semaphore produced;
extern semaphore consumed;
 
/*function	Prototype*/
void consumer(int count);	
void producer(int count);	
