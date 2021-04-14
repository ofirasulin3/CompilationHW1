%{
/* Declarations section */
#include "tokens.hpp"

%}

%option yylineno
%option noyywrap
digit           ([0-9])
positive		([1-9])
letter          ([a-zA-Z])
char            ([a-zA-Z0-9])
validString 	([^\r\n\"\\]|\\[tn0rx"\\])
string			([^\r\n\"\\]|\\[tn0rx"\\]|\\[^tn0rx"\\])
ignore 			[\n | \r | \t | \x0a | \x0d]+
printable 		[\x20-\x21\x23-\x7E]


%%
void								return VOID;
int									return INT;
byte	   							return BYTE;
b									return B;
bool								return BOOL;
and									return AND;
or									return OR;
not									return NOT;
true								return TRUE;
false								return FALSE;
return								return RETURN;
if									return IF;
else								return ELSE;
while								return WHILE;
break								return BREAK;
continue							return CONTINUE;
switch								return SWITCH;
case								return CASE;
default							    return DEFAULT;
\:									return COLON;
\;     			        		    return SC;
\,     	        				    return COMMA;
\(									return LPAREN;
\)									return RPAREN;
\{									return LBRACE;
\}									return RBRACE;
\=									return ASSIGN;
==|<|>|!=|>=|<=					    return RELOP;
\+|-|\*|\/					return BINOP;
{letter}{char}*						return ID;
{positive}{digit}*					return NUM;
{digit}								return NUM;
\"{string}*\"      					return STRING;
\"({printable})*                    return -1;
{ignore}							{};
(\/\/)([^\n\r\r\n])*				return COMMENT;
.               					return -2;
%%


