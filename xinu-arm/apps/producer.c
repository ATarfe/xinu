#include <prodcons.h>
#include <stdlib.h>
#include <stdio.h>

void producer(int count){
  //Code to produce values less than equal to count,
  //produced value should get assigned to global variable 'n'.
  //print produced value e.g. produced : 8

  int produced_value;
  
  while(1){
	//produce value less than or equal to count
	produced_value = 0;
	while (count > produced_value)
	    produced_value++;
    
    /* ----- ENTER CRITICAL SECTION ----- */
    wait(mutex);    

    //Store value back to n
    n = produced_value;    
        

    //Print result
    printf("Produced: %d\n", produced_value);

    signal(mutex);
    /* ----- EXIT CRITICAL SECTION ----- */


    //sleep?
    sleep(500); //sleep. otherwise screen scrolls too fast...
  }
}
