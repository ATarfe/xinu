#include <prodcons.h>
void producer(int count){
  //Code to produce values less than equal to count,
  //produced value should get assigned to global variable 'n'.
  //print produced value e.g. produced : 8

  int produced_value;
  
  while(1){
    wait(sem_producer);

    wait(mutex);
    //CR: access "n"
    signal(mutex);

    //produce
    printf("produced: %d\n",produced_value);
    //
    signal(sem_consumer);

    //sleep?
  }
}
