/*
 * @file future_prod.c
 * @provides future_prod
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

uint future_prod(future *fut) {
		int i, j;
		j = (int)fut;
		for (i=0; i<1000; i++) {
				j += i;
		}
    printf("producer produced:%d\n\r",j);
		future_set(fut, &j);
		return OK;
}
