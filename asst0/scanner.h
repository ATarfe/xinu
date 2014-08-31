#ifndef __SCANNER_H__
#define __SCANNER_H__

#define PLUS 0
#define MINUS 1
#define TIMES 2 
#define DIVIDES 3 
#define INTEGER 4 
#define NEWLINE 5 

int yylex();
extern char *yytext;

#endif
