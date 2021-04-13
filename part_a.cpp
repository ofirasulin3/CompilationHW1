#include "tokens.hpp"
#include <stdio.h>
#include <stdlib.h>

void showtoken(char *);
void parseString(int len);
char numChar(char a, char b);


int main()
{



    int token;
    while(token = yylex()) {

        switch(token)
        {
            case VOID:
                showtoken("VOID");
                break;

            case INT:
                showtoken("INT");
                break;

            case BYTE:
                showtoken("BYTE");
                break;

            case B:
                showtoken("B");
                break;

            case BOOL:
                showtoken("BOOL");
                break;

            case AND:
                showtoken("AND");
                break;

            case OR:
                showtoken("OR");
                break;

            case NOT:
                showtoken("NOT");
                break;

            case TRUE:
                showtoken("TRUE");
                break;

            case FALSE:
                showtoken("FALSE");
                break;

            case RETURN:
                showtoken("RETURN");
                break;

            case IF:
                showtoken("IF");
                break;

            case ELSE:
                showtoken("ELSE");
                break;

            case WHILE:
                showtoken("WHILE");
                break;

            case BREAK:
                showtoken("BREAK");
                break;

            case CONTINUE:
                showtoken("CONTINUE");
                break;

            case SWITCH:
                showtoken("SWITCH");
                break;

            case CASE:
                showtoken("CASE");
                break;

            case DEFAULT:
                showtoken("DEFAULT");
                break;

            case COLON:
                showtoken("COLON");
                break;

            case SC:
                showtoken("SC");
                break;

            case COMMA:
                showtoken("COMMA");
                break;

            case LPAREN:
                showtoken("LPAREN");
                break;

            case RPAREN:
                showtoken("RPAREN");
                break;

            case LBRACE:
                showtoken("LBRACE");
                break;

            case RBRACE:
                showtoken("RBRACE");
                break;

            case ASSIGN:
                showtoken("ASSIGN");
                break;

            case RELOP:
                showtoken("RELOP");
                break;

            case BINOP:
                showtoken("BINOP");
                break;

            case COMMENT:
                showtoken("COMMENT");
                break;

            case ID:
                showtoken("ID");
                break;

            case NUM:
                showtoken("NUM");
                break;

            case STRING:
                parseString(yyleng);
                break;

            case -1:
                printf("Error unclosed string \n");
                exit(0);
                break;

            case -2:
                printf("%s %s %s", "Error:", yytext, "\n");
                exit(0);
                break;

            default:
                break;

        }
    }
    return 0;
}

char numChar(char a, char b)
{
    int ascii_code = 0;
    char tmp[2];
    tmp[0] = a;
    tmp[1] = b;
    ascii_code = strtol(tmp, NULL, 16);
    return char(ascii_code);
}


void parseString(int len)
{
    char tmp[1024];
    char final[1024];
    char rep;
    int newlen = len-2;
    int i;
    int j = 0;

    for (i = 0; i + 1 < len - 1; i++)
    {
        tmp[i] = yytext[i + 1];
    }
    tmp[i] = '\0';

    for(i = 0; i<newlen; i++)
    {
        if(tmp[i] == '\\') {
            rep = tmp[i + 1];
            if (rep == 'n') {
                rep = '\n';
            }
            if (rep == 'r') {
                rep == '\r';
            }
            if (rep == 't') {
                rep == '\t';
            }
            if (rep == '0') {
                rep == '\0';
            }
            if (rep == '"') {
                rep == '\"';
            }
            if (rep == '\\') {
                rep == '\\';
            }

            if(rep == 'x')
            {
                final[j] = numChar(tmp[i+2], tmp[i+3]);
                ++j;
                i = i + 3 ;
                continue;
            }

            final[j] = rep;
            ++j;
            i = i + 1;
            continue;
        }
        final[j] = tmp[i];
        j++;
    }
    final[j] = '\0';

    printf("%d %s %s",yylineno, "STRING", final);
    printf("\n");

}

void showtoken(char * name){

    /*<line number> <token name> <value>*/
    printf("%d %s %s\n", yylineno, name, yytext);
}

