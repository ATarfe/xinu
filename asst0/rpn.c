#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <scanner.h>

int main(){
  stack s;
  int alive=1;
  while(alive){
      while (int token_type=yylex()!=NEWLINE){
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
