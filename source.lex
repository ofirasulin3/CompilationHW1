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
VOID            (void)
BYTE            (byte)
BOOL            (bool)
AND             (and)
TRUE 2           (true)
FALSE           (false)
RETURN          (return)
IF              (if)
ELSE            (else)
WHILE           (while)

%%
{digit}+                    showToken("number");
{letter}+@{letter}+\.com    showToken("email address");
{whitespace}                ;
{VOID}                      showToken("void");
{BOOL}                      showToken("bool");
{BYTE}                      showToken("byte");
.                           printf("Lex doesn't know what that is!\n");
%%


int showToken(char * name){
    printf("Lex found token %s ", name);
    printf("The lexeme is %s ", yytext);
    printf("its length is %d\n", yyleng);
    return 5;
}

int showToken2(char * name){
    /*<line number> <token name> <value>*/
    printf("%d %s %s", yyleng, name, yytext);
    return 5;
}


