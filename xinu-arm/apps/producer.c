#include <prodcons.h>
#include <stdlib.h>
void producer(int count){
  //Code to produce values less than equal to count,
  //produced value should get assigned to global variable 'n'.
  //print produced value e.g. produced : 8

  int produced_value;
  
  while(1){
    //wait(producer);

	//produce value less than or equal to count
    srand(10);
    produced_value = rand()%(count+1)+1;
    
    //wait(mutex);
    //CR: access "n"

    //Store value back to n
    n = produced_value;    
        
    //signal(mutex);
    
    //Print result
    printf("produced: %d\n",produced_value);

    //signal(consumer);

    //sleep?
  }
}
