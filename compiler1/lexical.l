%{
#include <stdlib.h>
#include <string.h>
#include "syntax.tab.h"
#include "tree.h"
int yycolumn = 1;
#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;\
	yylloc.first_column = yycolumn; yylloc.last_column = yycolumn + yyleng - 1;\
	yycolumn += yyleng;
%}
%option yylineno
octal	0[1-7]+[0-7]*
wrongO	0(0+[0-9]*|[0-9]*[89]+[0-9]*)
hex	0[xX]([0-9A-Fa-f]*)
wrongH	0[xX]([0-9A-Za-z]*[G-Zg-z]+[0-9A-Za-z]*)
type	int|float
relop	>|<|>=|<=|==|!=
int	0|([1-9][0-9]*)
float	(((\.[0-9]+)|([0-9]+\.)|([0-9]+\.[0-9]+))([eE][+-]?[0-9]+)?)|([0-9]+[eE][+-]?[0-9]+)
wrongF	\.?([eE][+-]?([0-9]+)?)|[0-9]*\.[0-9]*([eE][+-]?)
id	[_A-Za-z][_A-Za-z0-9]*
wrongid	[0-9][_A-Za-z0-9]*
ws	[ \t]+
cline	\n
com_1	"//".*\n
com_2	"/*"(.|\n)*"*/"
wrongC	("/*"(.|\n)*"/*"(.|\n)*"*/"(.|\n)*"*/")|("/*"[^("*/")]*)|([^("/*")]*"*/")
%%
{com_2}	{ printf("COM_2, %d\n", yylineno); }
{wrongC}	{printf("Error type A at line %d: Illegal comments usage\n", yylineno); have_wrong = 1;}
{com_1}	{/* printf("COM_1\n");*/ }
\n	{ yycolumn = 1; }
{ws}	{ /*do nothing*/ }
";"	{/* printf("SEMI\n");*/ yylval.type_node = TermNode(SEMIm,yylineno); return SEMI; }
","	{/* printf("COMMA\n");*/ yylval.type_node = TermNode(COMMAm,yylineno); return COMMA; }
"="	{/* printf("ASSIGNOP\n");*/ yylval.type_node = TermNode(ASSIGNOPm,yylineno); return ASSIGNOP; }
{relop}	{/* printf("RELOP\n");*/ yylval.type_id = malloc(strlen(yytext)+1); strcpy(yylval.type_id, yytext); return RELOP; }
"+"	{/* printf("PLUS\n");*/ yylval.type_node = TermNode(PLUSm, yylineno); return PLUS; }
"-"	{/* printf("MINUS\n");*/ yylval.type_node = TermNode(MINUSm,yylineno); return MINUS; }
"*"	{/* printf("STAR\n");*/ yylval.type_node = TermNode(STARm, yylineno); return STAR; }
"/"	{/* printf("DIV\n");*/ yylval.type_node = TermNode(DIVm,yylineno); return DIV; }
"&&"	{/* printf("AND\n");*/ yylval.type_node = TermNode(ANDm,yylineno); return AND; }
"||"	{/* printf("OR\n");*/ yylval.type_node = TermNode(ORm, yylineno); return OR; }
"."	{/* printf("DOT\n");*/ yylval.type_node = TermNode(DOTm,yylineno); return DOT; }
"!"	{/* printf("NOT\n");*/ yylval.type_node = TermNode(NOTm, yylineno); return NOT; }
{type}	{/* printf("TYPE\n");*/ yylval.type_type = strcmp(yytext, "int"); return TYPE;}
"("	{/* printf("LP\n");*/ yylval.type_node = TermNode(LPm, yylineno); return LP; }
")"	{/* printf("RP\n");*/ yylval.type_node = TermNode(RPm, yylineno); return RP; }
"["	{/* printf("LB\n");*/ yylval.type_node = TermNode(LBm, yylineno); return LB; }
"]"	{/* printf("RB\n");*/ yylval.type_node = TermNode(RBm, yylineno); return RB; }
"{"	{/* printf("LC\n");*/ yylval.type_node = TermNode(LCm, yylineno); return LC; }
"}"	{/* printf("RC\n");*/ yylval.type_node = TermNode(RCm, yylineno); return RC; }
"struct"	{/* printf("STRUCT\n");*/ yylval.type_node = TermNode(STRUCTm, yylineno); return STRUCT; }
"return"	{/* printf("RETURN\n");*/ yylval.type_node = TermNode(RETURNm, yylineno); return RETURN; }
"if"	{/* printf("IF\n");*/ yylval.type_node = TermNode(IFm, yylineno); return IF; }
"else"	{/* printf("ELSE\n");*/ yylval.type_node = TermNode(ELSEm, yylineno); return ELSE; }
"while"	{/* printf("WHILE\n");*/ yylval.type_node = TermNode(WHILEm, yylineno); return WHILE; }
{id}	{/* printf("ID\n");*/ yylval.type_id = malloc(strlen(yytext)+1); strcpy(yylval.type_id, yytext); return ID; }
{int}	{/* printf("INT\n");*/ yylval.type_int = atoi(yytext); return INT; }
{float}	{/* printf("FLOAT\n");*/ yylval.type_float = strtof(yytext,NULL); return FLOAT; }
{hex}	{/* printf("HEX\n");*/ yylval.type_int = (int)strtol(yytext,NULL,16); return INT; }
{octal}	{/* printf("OCTAL\n");*/ yylval.type_int = (int)strtol(yytext,NULL,8); return INT; }
{wrongF}	{ printf("Error type A at line %d: Illegal floating point number \'%s\'\n", yylineno, yytext);have_wrong = 1; }
{wrongO}	{ printf("Error type A at line %d: Illegal octal number \'%s\'\n", yylineno, yytext);have_wrong = 1; }
{wrongH}	{ printf("Error type A at line %d: Illegal hexadecimal number \'%s\'\n", yylineno, yytext);have_wrong = 1; }	
{wrongid}	{ printf("Error type A at line %d: Illegal ID \'%s\'\n", yylineno, yytext);have_wrong = 1; }
.	{ printf("Error type A at line %d: Mysterious character \'%s\'\n", yylineno, yytext);have_wrong = 1;}
%%
