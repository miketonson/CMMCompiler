%{
#include "syntax.tab.h"
%}
%option yylineno
type	int|float
relop	>|<|>=|<=|==|!=
int	0|([1-9][0-9]*)
float	{int}\.([0-9]+)([eE][+-]?{int})?
id	[_A-Za-z][_A-Za-z0-9]*
wrongid	[0-9][_A-Za-z0-9]*
ws	[ \t\n]+
%%
{ws}	{ /*do nothing*/ }
";"	{ printf("SEMI\n");return SEMI; }
","	{ printf("COMMA\n");return COMMA; }
"="	{ printf("ASSIGNOP\n");return ASSIGNOP; }
{relop}	{ printf("RELOP\n");return RELOP; }
"+"	{ printf("PLUS\n");return PLUS; }
"-"	{ printf("MINUS\n");return MINUS; }
"*"	{ printf("STAR\n");return STAR; }
"/"	{ printf("DIV\n");return DIV; }
"&&"	{ printf("AND\n");return AND; }
"||"	{ printf("OR\n");return OR; }
"."	{ printf("DOT\n");return DOT; }
"!"	{ printf("NOT\n");return NOT; }
{type}	{ printf("TYPE\n");return TYPE; }
"("	{ printf("LP\n");return LP; }
")"	{ printf("RP\n");return RP; }
"["	{ printf("LB\n");return LB; }
"]"	{ printf("RB\n");return RB; }
"{"	{ printf("LC\n");return LC; }
"}"	{ printf("RC\n");return RC; }
"struct"	{ printf("STRUCT\n");return STRUCT; }
"return"	{ printf("RETURN\n");return RETURN; }
"if"	{ printf("IF\n");return IF; }
"else"	{ printf("ELSE\n");return ELSE; }
"while"	{ printf("WHILE\n");return WHILE; }
{id}	{ printf("ID\n");return ID; }
{int}	{ printf("INT\n");return INT; }
{float}	{ printf("FLOAT\n");return FLOAT; }
{wrongid}	{ printf("Error type A at line %d: You wirte a wrong ID \'%s'\n", yylineno, yytext); }
.	{ printf("Error type A at line %d: Mysterious character \'%s\'\n", yylineno, yytext);}
%%
