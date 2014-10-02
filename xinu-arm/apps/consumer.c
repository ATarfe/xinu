#include <prodcons.h>
#include <stdio.h>

void consumer(int count){						
  //Code to consume values of global variable 'n' until the value
  //of n is less than or equal to count
  //print consumed value e.g. consumed : 8
  
  int consumed_value;
  
  while(1){
    /*
    signal(producer);
    signal(mutex);
	*/
	
	/* ----- ENTER CRITICAL SECTION ----- */
	wait(mutex);
	//Get value of n
	consumed_value = n;
	
	//TO-DO: ILL-DEFINED ASSIGNMENT. PROCEED WITH INTERPRETATION.
	//while (consumed_value > count){
	while (count > consumed_value){
	  count--;
	}
    printf("Consumed: %d\n",consumed_value);
    
	signal(mutex);
	/* ----- EXIT CRITICAL SECTION ----- */
	
	/*
    wait(consumer);
    wait(mutex);
    */
    sleep(450); // Intentionally out of sync with producer to demonstrate mutual exclusion
  }
}

