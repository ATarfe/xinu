/*
 * Author: Peter Zhang (yz79), Eriya Terada (eterada)
 * CSCI P536 FA14 ASST0
 * Sept 2 2014
 * stack.c file
 */
#include "scanner.h"
#include "rpn.h"
#include "stack.h"
#include <stdio.h>

Element top(stack * s){
  return s->elem[s->top_pointer];
}
int push(stack * s, void * element_value, int type){
  if(s->top_pointer<STACK_SIZE){
    s->elem[s->top_pointer++]=new_element(type,element_value);
    return 0;
  }
  else{
    fprintf(stderr,"stack overflow\n");
    return -1;
  }
}
int pop(stack * s){
  if(s->top_pointer>0){
    // TO-DO: Get top of stack
    destroy_element(s->elem[s->top_pointer--]);
    // TO-DO: Return top of stack
  }
  else{
    fprintf(stderr,"stack size is 0, cannot pop.\n");
    return -1;
  }
}