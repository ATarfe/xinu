/*
 * @file xsh_hello.c
 * @provides xsh_hello
 */
 /* For Xinu OS for Assignment 1 of P536
  * Peter Zhang (yz79)
  * Eriya Terada (eterada)
  *
  * Sept 18, 2014
  */
  
#include <stdio.h>
#include <string.h>
#include <hello.h>
  
  
shellcmd xsh_hello(int nargs, char *args[])
{

	if (nargs > 2 || nargs < 2){
		if (nargs >2)
			printf("Too many arguments!\n");
		else
			printf("Too few arguments!\n");
			
		printf("Usage:\n");
		printf("hello <string>\n");
		return SYSERR;
	}
	else{
    printHello(args[1]);
		return OK;
	}
}
