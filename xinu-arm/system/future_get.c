/*
 * @file future_get.c
 * @provides future_get
 * For Xinu OS for Assignment 5 of P536
  * Peter Zhang (yz79)
  * Eriya Terada (eterada)
  *
  * Oct 9 2014
  */
  
#include <stdio.h>
#include <string.h>
#include <future.h>
//necessary??
#include <kernel.h>

/**
 * Get the value of a future set by an operation and change the state of future  
 * fromFUTURE_VALID to FUTURE_EMPTY
 * params: future *f: future on which to wait for and obtain value int *value:
 * variable in which to obtain the value from a future
 *
 * return: syscall: SYSERR or OK 
 */
syscall future_get(future *f, int *value){
    if(f->state==FUTURE_VALID){
        f->state=FUTURE_EMPTY;
        *value=*(f->value);
        return OK;
    }
    else if(f->state==FUTURE_EMPTY){
        //set tid:
        f->tid=gettid();
        //set state:
        f->state=FUTURE_WAITING;
        //block thread:
        wait(f->block_wait);
    }
    else{
        return SYSERR;
    }
}
