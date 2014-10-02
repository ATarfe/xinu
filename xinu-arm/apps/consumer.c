#include <prodcons.h>
void consumer(int count){						
  //Code to consume values of global variable 'n' until the value
  //of n is less than or equal to count
  //print consumed value e.g. consumed : 8
  
  int consumed_value;
  
  while(1){
    signal(sem_producer);
    signal(mutex);

    wait(sem_consumer);
    wait(mutex);
    
    //consume    
    printf("consumed: %d\n",consumed_value);
  }
}

