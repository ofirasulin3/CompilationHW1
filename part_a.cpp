#include "tokens.hpp"

int main()
{
	int token;
	while(token = yylex()) {
	// Your code here
	    if(token == VOID){
            printf("Test succedded!");
	    }
	}
	return 0;
}