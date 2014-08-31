#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <scanner.h>

int main(){
    while (yylex()!=NEWLINE){
        printf("%s\n",yytext);
    }
     
    return 0;
}
