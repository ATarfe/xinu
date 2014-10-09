/*
 * @file future_set.c
 * @provides future_set  
 * */
 /* For Xinu OS for Assignment 5 of P536
  * Peter Zhang (yz79)
  * Eriya Terada (eterada)
  *
  * Oct 9 2014
  */
  
#include <stdio.h>
#include <string.h>
#include <future.h>
#include <kernel.h>

/**
 * Set a value in a future and changes state from FUTURE_EMPTY or FUTURE_WAITING
 * to FUTURE_VALID.  
 * params: future *f: future in which to set the value int
 *          *value: result of an operation to be set as value in a future 
 * return:
 * syscall: SYSERR or OK
 */
syscall future_set(future *f, int *value){
    if(f->state==FUTURE_WAITING || f->state=FUTURE_EMPTY){
        *(f->value)=*value;
        f->state=FUTURE_VALID;
        signal(f->block_wait);
        return OK;
    }
    else{
        return SYSERR;
    }

}
