/*
 * @file future_alloc.c
 * @provides future_alloc 
 */
 /* For Xinu OS for Assignment 5 of P536
  * Peter Zhang (yz79)
  * Eriya Terada (eterada)
  *
  * Oct 9 2014
  */
  
#include <stdio.h>
#include <string.h>
#include <future.h>
#include <memory.h>


/**
 * Allocates a new future (in the FUTURE_EMPTY state) in given mode. We will 
 * use memget() call to allocate space to new future.
 *
 * Parameters:
 * int future_flag: flag to be set for this future
 *
 * Return:
 * future: NULL or a valid future reference
 */
future* future_alloc(int future_flag){
    //first allocate the struct future:
    future *f=memget(sizeof(future));
    if ((int*)f==-1){
        //failed
        return NULL; 
    }
    //second, set future flag:
    f->flag=future_flag;
    f->state=FUTURE_EMPTY;
    f->tid=NULL;
    (f->set_queue)=NULL;
    (f->get_queue)=NULL;
    printf("future is allocated with flag=%d\n\r",f->flag);
    return f;
}

