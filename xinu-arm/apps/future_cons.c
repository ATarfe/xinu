/*
 * @file future_cons.c
 * @provides future_cons
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

uint future_cons(future *fut) {
  int i, status;
  status = future_get(fut, &i);
  if (status < 1) {
    printf("future_get failed\n");
      return -1;
  }
  printf("consumer consumed: %d\n", i);
  return OK;
}

