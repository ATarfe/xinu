#include <prodcons.h>
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
	
	//Get value of n
	consumed_value = n;
	while (count > consumed_value){
	  consumed_value--;	
	}
	
	/*
    wait(consumer);
    wait(mutex);
    */
    
    //consume    
    printf("consumed: %d\n",consumed_value);
  }
}

