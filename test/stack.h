/*
 * Author: Peter Zhang (yz79), Eriya Terada (eterada)
 * CSCI P536 FA14 ASST0
 * Sept 2 2014
 * stack.h file
 */

#ifndef __STACK_H__
#define __STACK_H__

#include <rpn.h>

#define STACK_SIZE 1024

typedef struct{
    Element elem[STACK_SIZE];
    Element top;
}stack;

Element top(stack * s);
int push(stack * s);
int pop(stack * s);

#endif
