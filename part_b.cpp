#include "tokens.hpp"
#include <stdio.h>
//#include <stdlib.h>

void showErrorToken(char const * name){
    printf("%s %s\n", "Error:", name);
    exit(0);
}

void badExpressionError(){
    printf("Error: Bad Expression\n");
    exit(0);
}

void printParenthesis(char parenthesis, int tabs_factor){
    for(int i=0;i<tabs_factor;i++) printf("\t");
    printf("%c\n", parenthesis);
}

int main()
{
    int token;

    int maxEven = 2;
    int maxOdd = 3;
    int balanceEven = 0;
    int balanceOdd = 0;
    char last_token = 0;
    int tabs_factor = -1;

    while(token = yylex()) {
//        int last_line_number = yylineno;

        switch(token)
        {
            case VOID:
                showErrorToken("VOID");
                break;

            case INT:
                showErrorToken("INT");
                break;

            case BYTE:
                showErrorToken("BYTE");
                break;

            case B:
                showErrorToken("B");
                break;

            case BOOL:
                showErrorToken("BOOL");
                break;

            case AND:
                showErrorToken("AND");
                break;

            case OR:
                showErrorToken("OR");
                break;

            case NOT:
                showErrorToken("NOT");
                break;

            case TRUE:
                showErrorToken("TRUE");
                break;

            case FALSE:
                showErrorToken("FALSE");
                break;

            case RETURN:
                showErrorToken("RETURN");
                break;

            case IF:
                showErrorToken("IF");
                break;

            case ELSE:
                showErrorToken("ELSE");
                break;

            case WHILE:
                showErrorToken("WHILE");
                break;

            case BREAK:
                showErrorToken("BREAK");
                break;

            case CONTINUE:
                showErrorToken("CONTINUE");
                break;

            case SWITCH:
                showErrorToken("SWITCH");
                break;

            case CASE:
                showErrorToken("CASE");
                break;

            case DEFAULT:
                showErrorToken("DEFAULT");
                break;

            case COLON:
                showErrorToken("COLON");
                break;

            case SC:
                showErrorToken("SC");
                break;

            case COMMA:
                showErrorToken("COMMA");
                break;

            case ASSIGN:
                showErrorToken("ASSIGN");
                break;

            case RELOP:
                showErrorToken("RELOP");
                break;

            case BINOP:
                showErrorToken("BINOP");
                break;

            case COMMENT:
                showErrorToken("COMMENT");
                break;

            case ID:
                showErrorToken("ID");
                break;

            case NUM:
                showErrorToken("NUM");
                break;

            case STRING:
                showErrorToken("STRING");
                break;

            case -2:
                printf("%s %s\n", "Error:", yytext);
                exit(0);
                break;



            case LPAREN:
                tabs_factor+=1;
                maxEven+=2;
                balanceEven+=maxEven;
                printParenthesis('(', tabs_factor);
                break;

            case RPAREN:
                if(last_token==LBRACE) {
                    //{)
                    badExpressionError();
                    exit(0);
                }
                balanceEven-=maxEven;
                maxEven-=2;
                if(balanceEven<0){
                    badExpressionError();
                    exit(0);
                }
                printParenthesis(')', tabs_factor);
                tabs_factor-=1;
                break;

            case LBRACE:
                maxOdd+=2;
                balanceOdd+=maxOdd;

                tabs_factor+=1;
                printParenthesis('{', tabs_factor);
                break;

            case RBRACE:
                if(last_token==LPAREN) {
                    //(}
                    badExpressionError();
                    exit(0);
                }
                balanceOdd-=maxOdd;
                maxOdd-=2;
                if(balanceOdd<0){
                    badExpressionError();
                    exit(0);
                }
                printParenthesis('}', tabs_factor);
                tabs_factor-=1;
                break;

            default:
                break;

        }
        last_token = token;
    }
    if(balanceOdd!=0 || balanceEven!=0){
        badExpressionError();
        exit(0);
    }
    return 0;
}
