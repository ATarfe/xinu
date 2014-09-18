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
  
  
shellcmd xsh_hello(int nargs, char *args[])
{

	if (nargs > 2){
		printf("Too many arguments!\n");
		printf("Usage:\n");
		printf("hello <string>\n");
		return SYSERR;
	}
	else if (nargs < 2){
		printf("Too few arguments!\n");
		printf("Usage:\n");
		printf("hello <string>\n");		
		return SYSERR;
	}
	else{
		printf("Hello %s, Welcome to the world of Xinu!!\n", args[1]);
		return OK;
	}
}