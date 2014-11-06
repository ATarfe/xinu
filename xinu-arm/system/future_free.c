/*
 * @file future_free.c
 * @provides future_free
 * For Xinu OS for Assignment 5 of P536
  * Peter Zhang (yz79)
  * Eriya Terada (eterada)
  *
  * Oct 9 2014
  */
  
#include <stdio.h>
#include <string.h>
#include <future.h>


/*
 * calls memfree
 *
 * param: future
 * return : syscall
 */
syscall future_free(future* f){
    irqmask im=disable();
    if (f->set_queue!=NULL)
        free(f->set_queue);
    if (f->get_queue!=NULL)
        free(f->get_queue);
    free(f->value);
    int returnval=memfree(f,sizeof(future))!=SYSERR? OK : SYSERR;
    restore(im);
    return returnval;
}
