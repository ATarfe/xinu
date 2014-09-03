#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <scanner.h>

int main(){
	printf("=>");
    while(1){
        while (yylex()!=NEWLINE){
            printf("%s\n",yytext);
        }
    }
    return 0;
}
