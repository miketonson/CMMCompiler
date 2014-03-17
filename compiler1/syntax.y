%{
#include <stdio.h>
	#include "lex.yy.c"
%}
%token	INT
%token	FLOAT
%token	ID
%token	SEMI COMMA ASSIGNOP RELOP PLUS MINUS STAR DIV AND OR DOT NOT TYPE
%token	LP RP LB RB LC RC STRUCT RETURN IF ELSE WHILE
%right	ASSIGNOP
%left	OR
%left	AND
%left	RELOP
%left	PLUS MINUS
%left	STAR DIV
%right	NOT
%left	LP RP LB RB DOT
%%
Program	:	ExtDefList
	;
ExtDefList	:	ExtDef ExtDefList
		|	/*empty*/
		;
ExtDef	:	Specifier ExtDecList SEMI
	|	Specifier SEMI
	|	Specifier FunDec CompSt
	;
ExtDecList	:	VarDec
		|	VarDec COMMA ExtDecList
		;
Specifier	:	TYPE
		|	StructSpecifier
		;
StructSpecifier	:	STRUCT OptTag LC DefList RC
		|	STRUCT Tag
		;
OptTag	:	ID
	|	/*empty*/
	;
Tag	:	ID
	;
VarDec	:	ID
	|	VarDec LB INT RB
	;
FunDec	:	ID LP VarList RP
	|	ID LP RP
	;
VarList	:	ParamDec COMMA VarList
	|	ParamDec
	;
ParamDec	:	Specifier VarDec
		;
CompSt	:	LC DefList StmtList RC
	;
StmtList	:	Stmt StmtList
		|	/*empty*/
		;
Stmt	:	Exp SEMI
     	|	error SEMI/*error recovery*/
	|	CompSt
	|	RETURN Exp SEMI
	|	IF LP Exp RP Stmt
	|	IF LP Exp RP Stmt ELSE Stmt
	|	WHILE LP Exp RP Stmt
	;
DefList	:	Def DefList
	|	/*empty*/
	;
Def	:	Specifier DecList SEMI
	|	Specifier error SEMI/*error recovery*/
	;
DecList	:	Dec
	|	Dec COMMA DecList
	;
Dec	:	VarDec
	|	VarDec ASSIGNOP Exp
	;
Exp	:	Exp ASSIGNOP Exp
	|	Exp AND Exp
	|	Exp OR Exp
	|	Exp RELOP Exp
	|	Exp PLUS Exp
	|	Exp MINUS Exp
	|	Exp STAR Exp
	|	Exp DIV Exp
	|	LP Exp RP
	|	LP error RP/*error recovery*/
	|	MINUS Exp
	|	NOT Exp
	|	ID LP Args RP
	|	ID LP error RP/*error recovery*/ 
	|	ID LP RP
	|	Exp LB Exp RB
	|	Exp LB error RB/*error recovery*/
	|	Exp DOT ID
/*	|	error DOT ID/*error recovery*/
	|	ID
	|	INT
	|	FLOAT
	;
Args	:	Exp COMMA Args
	|	Exp
	;
%%
yyerror(char* msg)
{
    fprintf(stderr,"Error type B at line %d: %s\n", yylineno, msg);
}
