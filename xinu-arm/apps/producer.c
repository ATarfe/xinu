#include <prodcons.h>
void producer(int count){
  //Code to produce values less than equal to count,
  //produced value should get assigned to global variable 'n'.
  //print produced value e.g. produced : 8

  int produced_value;
  
  while(1){
    //wait(producer);

    //wait(mutex);
    //CR: access "n"
    //signal(mutex);

    //PRODUCE:
    
    //Get value from n
    produced_value = n;
    
    //Increment it
    produced_value++;
    
    //Store value back to n
    n = produced_value;
    
    //Print result
    printf("produced: %d\n",produced_value);
    //
    //signal(consumer);

    //sleep?
  }
}
