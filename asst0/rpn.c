#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "scanner.h"
#include "stack.h"
#include "rpn.h"

//TODO: put implementation somewhere else
Element new_element(int type, void * value){
  Element e;
  e.type=type;
  e.value=malloc(SIZE);
  memcpy(e.value,value,SIZE); //SIZE was size Sept 3 6:54pm - Eriya
}

void destroy_element(Element e){
  free(e.value);
}



/*
 * calculate(stack* s, int operator) -> int
 *
 * Takes a pointer to a stack, pops off the two numbers on the stack,
 * and performs "operator" on those two numbers.
 * If there is only one number on the stack, performs the identity calculation.
 *
 */

int calculate(stack* s, int operator_type){
  printf("%d\n", operator_type);
 
  return 0;
}
 

int main(){
  stack s;
  calculate(&s, 0);
  
  
  
  int alive=1;
  while(alive){
	  int token_type = 0;
    while (token_type = yylex()!=NEWLINE){
      printf("%s, type %d\n",yytext, token_type);
      //all the cases:
      switch(token_type){
        case(PLUS):
          break;
        case (MINUS):
          break;
        case (MULTIPLY):
          break;
        case (DIVIDE):
          break;
        case (MOD):
          break;
        case (INT_B10):
          break;
        case (INT_B16):
          break;
        case (INT_B2):
          break;
        case (INT_B8):
          break;
        case (FP):
          break;
        case (DEC):
          break;
        case (QUIT):
          alive=0;
          break;
      }
    }
  }
  return 0;
}
