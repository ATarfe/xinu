#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <stdint.h>
#include "scanner.h"
#include "stack.h"
#include "rpn.h"


//define int and float..some bizzar number...
#define INT 0xfffffff
#define FLOAT 0xffffffe

uint8_t top2_ints[2];

void parse_string(char * input, stack *s){
    yy_scan_string(input);
    int token_type=yylex();
    while(token_type!=NEWLINE){
      //printw("token:%s,type=%d\n",yytext,token_type);
      switch(token_type){
        //parse all int cases:
        case (INT_B10):
          push(s,(float)strtol(yytext,NULL,10));
          top2_ints[0]=top2_ints[1];
          top2_ints[1]=1;
          break;
        case (INT_B16):
          push(s,(float)strtol(yytext,NULL,16));
          top2_ints[0]=top2_ints[1];
          top2_ints[1]=1;
          break;
        case (INT_B2):
          //note: knock out first two chars
          push(s,(float)strtol(yytext+2,NULL,2));
          top2_ints[0]=top2_ints[1];
          top2_ints[1]=1;
          break;
        case (INT_B8):
          push(s,(float)strtol(yytext,NULL,8));
          top2_ints[0]=top2_ints[1];
          top2_ints[1]=1;
          break;
        case (FP):
        case (DEC):
          push(s,(float)strtod(yytext,NULL));
          top2_ints[0]=top2_ints[1];
          top2_ints[1]=0;
          break;
        case (PLUS):
        case (MINUS):
        case (MULTIPLY):
        case (MOD):
        case (DIVIDE):
          calculate(s,token_type);
          break;
        case (0xdeadbeef):
          printw("\n%s is not a valid operator or number. Please check.\n=>",yytext);
      }
      //reset tokentype:
      token_type=yylex();
    }

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

  //get top 2 elements:
  float first=top(s);
  int state=pop(s);
  if(state==-1){
    printw("error. no element on stack\n");
    return -1;
  }
  float second=top(s);
  state=pop(s);
  if(state==-1){
      switch(operator_type){
        case (PLUS):
        case (MULTIPLY):
        case (MOD):
        case (DIVIDE):
          //just incr stack ptr....
          s->top_pointer++;
          break;
        case (MINUS):
          //push negative of first element back:
          push(s,first*-1);
          break;
      }
      printw("\n%g\n=>",top(s));
  }
  else{
    //second element is valid...
    switch(operator_type){
      case (PLUS):
        push(s,second+first);
        break;
      case (MULTIPLY):
        push(s,second*first);
        break;
      case (MOD):
        if(top2_ints[0] && top2_ints[1]){}
        else{
          printw("top two elements on stack are not both integers. casting both elements to integer before applying the mod operation\n");
        }
        push(s,(float)((int)second%(int)first));
        break;
      case (DIVIDE):
        push(s,second/first);
        break;
      case (MINUS):
        push(s,second-first);
        break;
    }
    printw("\n%g\n=>",top(s));
  }
  return 0;
}
 

int main(){
  stack s;
  s.top_pointer = 0;

  //first, initialize curses
  WINDOW * default_win=initscr();
  scrollok(default_win,TRUE);
  
  char buffer[2048];

  printw("=>"); 
  int input=getch(), buffer_ptr=0;

  while (input != 'q'){
    if (input==' '){
      //if input is space, add space to buffer and cont
      buffer[buffer_ptr++]=' '; 
      input=getch();
      continue;
    }
    uint8_t valid_bit=0;
    switch(input){
      //127 is the code for backspace.
      case(127):
        if(buffer_ptr>0){
          delch();
          printw("\b");
          delch();
          printw("\b");
          delch();
          printw("\b");
          delch();
          refresh();
          valid_bit=1;
          buffer_ptr--;
        }
        else{
          delch();
          printw("\b");
          delch();
          printw("\b");
          delch();
          refresh();
          valid_bit=1;
        }
        break;
      case('+'):
      case ('-'):
      case ('*'):
      case ('/'):
      case ('%'):
        //printw("adding to buf\n");
        buffer[buffer_ptr++]=input; 
        buffer[buffer_ptr++]='\n';
        buffer[buffer_ptr]='\0';
        parse_string(buffer,&s);
        valid_bit=1;
        //reset buffer
        buffer_ptr=0;
        break;
      default:
        if(
           (input>='a' && input<='f')
            ||
           (input>='A' && input<='F')
            ||
           (input>='0' && input<='9')
            ||
           (input=='x' || input=='X' || input=='.')
          ){
            buffer[buffer_ptr++]=input; 
            valid_bit=1;
        }
        if(input=='p' || input=='P'){
          //print stack:
          print_stack(s);
          valid_bit=1;
        }
        break;
    }
    if(!valid_bit){
      printw("invalid input \"%c\"\n=>",(char)input);
      refresh();
    }
    //read next input:
    input=getch();

  }
  endwin();
  return 0;
}
