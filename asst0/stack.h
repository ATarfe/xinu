/*
 * Author: Peter Zhang (yz79), Eriya Terada (eterada)
 * CSCI P536 FA14 ASST0
 * Sept 2 2014
 * stack.h file
 */

#ifndef __STACK_H__
#define __STACK_H__

#include "rpn.h"

#define STACK_SIZE 1024

typedef struct{
    Element elem[STACK_SIZE];
    int top_pointer; // Is this current index (top location) of stack? - Eriya
}stack;

Element top(stack * s);
int push(stack * s, void * element_value, int type);
int pop(stack * s); // Shouldn't it return whatever's on the stack?

#endif