%{
/* Declarations section */
#include "tokens.hpp"
#include <stdio.h>
int showToken(char *);

/*
letterORdigit   ([a-zA-Z0-9]*)
  ID              ([a-zA-Z]+[a-zA-Z0-9]*)
  IDD             ([a-zA-Z][a-zA-Z0-9]*)
  letters         ([a-zA-Z]+)
  */
%}

%option yylineno
%option noyywrap
digit           ([0-9])
letter          ([a-zA-Z])
whitespace      ([\t\n ])
assign          (=)
lparen          (\()
rparen          (\))
char            ([a-zA-Z0-9])

%%
(void)                      showToken("number");
{digit}+                    showToken("number");
{letter}{char}*             printf("%d %s %s", yyleng, name, yytext); return ID;
{whitespace}                ;
.                           printf("Lex doesn't know what that is!\n");
%%


int showToken(char * name){
    printf("Lex found token %s ", name);
    printf("The lexeme is %s ", yytext);
    printf("its length is %d\n", yyleng);
    return 5;
}

int showTokenVoid(char * name){
    /*<line number> <token name> <value>*/
    printf("%d %s %s", yyleng, name, yytext);
    return VOID;
}


