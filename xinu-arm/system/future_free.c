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
    return memfree(f,sizeof(future))!=SYSERR? OK : SYSERR;
}
