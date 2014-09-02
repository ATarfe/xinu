#ifndef __SCANNER_H__
#define __SCANNER_H__

#define PLUS 0
#define MINUS 1
#define MULTIPLY 2 
#define DIVIDE 3 
#define MOD 4 
#define NEWLINE 5 
#define INT_B10 6 
#define INT_B8 7 
#define INT_B16 8 
#define INT_B2 9 
#define FP 10 
#define DEC 11 
#define QUIT 12


int yylex();
extern char *yytext;

#endif
