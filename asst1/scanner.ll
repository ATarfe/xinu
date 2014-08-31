%{
	#include "scanner.h"
	#define yywrap() (1)
%}
%%
"&" { return AMPERSAND; }
"<" { return LESS; }
">>" { return GRGR; }
">" { return GREATER; }
"|" { return PIPE; }
"\n" { return NEWLINE; }
[0-9]+ { return INTEGER; }
[^[:blank:]\n]+ { return STRING; }
[[:blank:]]+ { /* do nothing */ }
%%
