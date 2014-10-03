/*
 * @file xsh_prodcons.c
 * @provides prodcons
 */
/* For Xinu OS for Assignment 3 of P536
 * Peter Zhang (yz79)
 * Eriya Terada (eterada)
 *
 * Sept 30, 2014
 */
#include <prodcons.h>

int n;
semaphore produced;
semaphore consumed;

shellcmd xsh_prodcons(int argc, char *argv[]) 
{       
  //Argument verifications and validations         

  int count = 2000;  //local varible to hold count
  
  //Print nice things if number of arguments provided is wrong
  if (argc > 2){
    fprintf(stderr,"Too many arguments!\n");
    fprintf(stderr,"Usage:\nprodcons <count: int>\n");
    return SYSERR;
  }

  //Otherwise if we do have an argument...
  else if (argc == 2){
    count = atoi(argv[1]);
    if (0 == count){
      fprintf(stderr,"You either entered 0 or a non-numerical value.\n");
      return SYSERR;
    }
  }
  
  //create the process producer and consumer and put them in ready queue.
  //Look at the definitions of function create and resume in exinu/system
  //folder for reference.
  
  //initialize semaphores:
  
  consumed=semcreate(0);
  produced=semcreate(1);
  
  resume( create(producer, 1024, 20, "producer", 1, count) );							
  resume( create(consumer, 1024, 20, "consumer", 1, count) );
  return OK;											
}	
