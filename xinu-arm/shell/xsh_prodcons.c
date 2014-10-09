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
#include <stdint.h>
#include <string.h>

int n;
semaphore produced;
semaphore consumed;

shellcmd xsh_prodcons(int argc, char *argv[]) 
{       
  //Argument verifications and validations         

  int count = 2000;  //local varible to hold count
  uint8_t use_future=0;

  //Print nice things if number of arguments provided is wrong
  if (argc > 3){
    fprintf(stderr,"Too many arguments!\n");
    fprintf(stderr,"Usage:\nprodcons <-f> <count: int>\n");
    return SYSERR;
  }

  //Otherwise if we do have an argument...
  else if (argc == 3){
    if(strcmp(argv[2],"-f")==0){
      use_future==1;
    }
    else{
      fprintf(stderr,"Invalid argument %s!\n",argv[2]);
      fprintf(stderr,"Usage:\nprodcons <-f> <count: int>\n");
      return SYSERR;
    }
    count = atoi(argv[3]);
    if (0 == count){
      fprintf(stderr,"Invalid argument %s!\n",argv[3]);
      fprintf(stderr,"You either entered 0 or a non-numerical value.\n");
      return SYSERR;
    }
  }
  else if (argc == 2){
    if(strcmp(argv[1],"-f")==0){
      use_future==1;
    }
    if(!use_future){
      count = atoi(argv[1]);
      if (0 == count){
        fprintf(stderr,"Invalid argument %s!\n",argv[3]);
        fprintf(stderr,"Usage:\nprodcons <-f> <count: int>\n");
        return SYSERR;
      }
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
