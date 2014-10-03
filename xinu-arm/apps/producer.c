#include <prodcons.h>
#include <stdlib.h>
#include <stdio.h>

void producer(int count){
  //Code to produce values less than equal to count,
  //produced value should get assigned to global variable 'n'.
  //print produced value e.g. produced : 8

  int produced_value = 0;
  int upperbound=count;
  while(count>0){
    //produce value less than or equal to count
	produced_value = upperbound - count;

    //Store value back to n
    n = produced_value;

    wait(produced);
    /* ----- EXIT CRITICAL SECTION ----- */


    //Print result
    printf("Produced: %d\n", produced_value);

	/* ----- ENTER CRITICAL SECTION ----- */
	signal(consumed);

    count--;
    //sleep?
    sleep(500); //sleep. otherwise screen scrolls too fast...
  }
}