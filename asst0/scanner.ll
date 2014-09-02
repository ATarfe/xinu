%{
	#include "scanner.h"
%}

%option noyywrap

%%
"+" { return PLUS; } 
"-" { return MINUS; }
"*" { return MULTIPLY; }
"/" { return DIVIDE; }
"%" { return MOD; }
"\n" { return NEWLINE; }
("+"|"-")*[0-9]+ { return INT_B10; }
0[0-7]+ { return INT_B8; }
0("x"|"X")[0-9A-Fa-f]+ {return INT_B16;}
0("b"|"B")(0|1)+ {return INT_B2;}
("+"|"-")*[0-9]+.[0-9]+E[0-9]+ { return FP; }
("+"|"-")*[0-9]*.[0-9]+ { return DEC;}
[[:blank:]]+ { /* do nothing */ }
"q" {return QUIT;}
%%
