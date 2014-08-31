#ifndef __SCANNER_H__
#define __SCANNER_H__

#define UNKNOWN 0
#define AMPERSAND 1
#define LESS 2
#define GRGR 3
#define GREATER 4
#define PIPE 5
#define NEWLINE 6
#define INTEGER 7
#define STRING 8

int yylex();
extern char *yytext;

#endif
