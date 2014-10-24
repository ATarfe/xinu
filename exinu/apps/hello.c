/*
 * @file hello.c
 * @provides printHello function 
 */
 /* For Xinu OS for Assignment 1 of P536
  * Peter Zhang (yz79)
  * Eriya Terada (eterada)
  *
  * Sept 18, 2014
  */

/**
 * prints hello...
 */
#include <stdio.h>
void printHello(char *s){
		printf("Hello %s, Welcome to the world of Xinu!!\n", s);
}
