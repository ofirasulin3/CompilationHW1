%{
/* Declarations section */
#include "tokens.hpp"
#include <stdio.h>
int showToken(char *);

%}

%option yylineno
%option noyywrap
digit           ([0-9])
letter          ([a-zA-Z])
whitespace      ([\t\n ])
char            ([a-zA-Z0-9])
num             ([0]|([1-9]+[0-9]*))


%%
b                                       printf("%d %s %s\n", yyleng, "B", yytext); return B;
;                                       printf("%d %s %s\n", yyleng, "SC", yytext); return SC;
void                                    printf("%d %s %s\n", yyleng, "VOID", yytext); return VOID;
=                                       printf("%d %s %s\n", yyleng, "ASSIGN", yytext); return ASSIGN;
\(                                      printf("%d %s %s\n", yyleng, "LPAREN", yytext); return LPAREN;
\)                                      printf("%d %s %s\n", yyleng, "RPAREN", yytext); return RPAREN;
{num}                                   printf("%d %s %s\n", yyleng, "NUM", yytext); return NUM;
{letter}{char}*                         printf("%d %s %s\n", yyleng, "ID", yytext); return ID;
\+|\-|\*|\/	                            return BINOP;
>|<|<=|>=|==|!=                         return RELOP;
\"([^\n\r\"\\]|\\[rnt"\\])+\"           printf("%d %s %s\n", yyleng, "STRING", yytext); return STRING;
\"[^\"]*                                printf("UNCLOSEDERROR\n");
[\r | \x0d | \x0a]+                     ;
\/\/[^\r\n]*[ \r|\n|\r\n]?              ;
{whitespace}                            ;
.                                       printf("Lex doesn't know what that is!\n");
%%


int showToken(char * name){
    printf("Lex found token %s ", name);
    printf("The lexeme is %s ", yytext);
    printf("its length is %d\n", yyleng);
    return 5;
}

int showTokenVoid(char * name){
    /*<line number> <token name> <value>*/
    printf("%d %s %s\n", yyleng, name, yytext);
    return VOID;
}


