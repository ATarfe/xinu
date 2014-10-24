#include <prodcons.h>
#include <stdio.h>

void consumer(int count){						
  //Code to consume values of global variable 'n' until the value
  //of n is less than or equal to count
  //print consumed value e.g. consumed : 8
  
  int consumed_value;
  while(count>0){
	
    /* ----- ENTER CRITICAL SECTION ----- */
    wait(consumed);
    
    //Get value of n
    consumed_value = n;
    
    sleep(510); // To simulate race condition if no mutex is set.

    printf("Consumed: %d\n",consumed_value);
      
    signal(produced);
    /* ----- EXIT CRITICAL SECTION ----- */
    
    count--;
  }
}
