#include "tokens.hpp"
#include <stdio.h>
#include <stdlib.h>

void showtoken(char const *);
void parseString(int len);
char numChar(char a, char b, int * err);


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
                printf("Error unclosed string\n");
                exit(0);
                break;

            case -2:
                printf("%s %s\n", "Error:", yytext);
                exit(0);
                break;

            default:
                break;

        }
    }
    return 0;
}

char numChar(char a, char b, int * err)
{
    *err = 0;
    int ascii_code = 0;
    char tmp[2];
    tmp[0] = a;
    tmp[1] = b;
    ascii_code = strtol(tmp, nullptr, 16);
    if(ascii_code > 127 || ascii_code==0)
    {
        *err = -1;
    }
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
    int err;

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
            else if (rep == 'r') {
                rep = '\r';
            }
            else if (rep == 't') {
                rep = '\t';
            }
            else if (rep == '0') {
                rep = '\0';
            }
            else if (rep == '"') {
                rep = '\"';
            }
            else if (rep == '\\') {
                rep = '\\';
            }

            else if(rep == 'x')
            {
                if(tmp[i+2]=='\0')
                {
                    printf("Error undefined escape sequence x\n");
                    exit(0);
                }

                if(tmp[i+3]=='\0')
                {
                    printf("%s%c\n","Error undefined escape sequence x", tmp[i+2]);
                    exit(0);
                }
                final[j] = numChar(tmp[i+2], tmp[i+3], &err);
                ++j;

                if(err == -1)
                {
                    printf("Error undefined escape sequence x");
                    printf("%c%c", tmp[i+2],tmp[i+3]);

                    printf("\n");
                    exit(0);
                    return;
                }
                i = i + 3 ;
                continue;
            }
            else
            {
                printf("%s %c\n", "Error undefined escape sequence", rep);
                exit(0);
                return;
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
    printf("%d %s %s\n",yylineno, "STRING", final);

}

void showtoken(char const * name){

    /*<line number> <token name> <value>*/
    printf("%d %s %s\n", yylineno, name, yytext);
}

