%{
	#include "scanner.h"
%}

%option noyywrap

%%
"+" { return PLUS; } 
"-" { return MINUS; }
"*" { return TIMES; }
"/" { return DIVIDES; }
"\n" { return NEWLINE; }
[0-9]+ { return INTEGER; }
[[:blank:]]+ { /* do nothing */ }
%%
