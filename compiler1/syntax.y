%{
#include <stdio.h>
#include "lex.yy.c"

%}
%union{
	int type_int;
	float type_float;
	char* type_id;
	enum {I,F} type_bool;
	expnode* type_node;
}
%type <type_node> Program
%type <type_node> ExtDefList
%type <type_node> ExtDef
%type <type_node> Specifier
%type <type_node> ExtDecList
%type <type_node> FunDec
%type <type_node> CompSt
%type <type_node> VarDec
%type <type_node> StructSpecifier
%type <type_node> OptTag
%type <type_node> DefList
%type <type_node> Tag
%type <type_node> VarList
%type <type_node> ParamDec
%type <type_node> StmtList
%type <type_node> Stmt
%type <type_node> Exp
%type <type_node> Def
%type <type_node> DecList
%type <type_node> Dec
%type <type_node> Args
%token <type_int> INT
%token <type_float> FLOAT
%token <type_id> ID
%token <type_bool> TYPE
%token	SEMI COMMA ASSIGNOP RELOP PLUS MINUS STAR DIV AND OR DOT NOT 
%token	LP RP LB RB LC RC STRUCT RETURN IF ELSE WHILE
%right	ASSIGNOP
%left	OR
%left	AND
%left	RELOP
%left	PLUS MINUS
%left	STAR DIV
%right	NOT
%left	LP RP LB RB DOT
%nonassoc LOWER_THEN_ELSE
%nonassoc ELSE
%%
Program	:	ExtDefList
	;
ExtDefList	:	ExtDef ExtDefList
		|	/*empty*/
		;
ExtDef	:	Specifier ExtDecList SEMI
       	|	Specifier error SEMI/*error recovery*/
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
		|	STRUCT OptTag LC error RC/*error recovery*/
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
       	|	ID LP error RP/*error recovery*/
	|	ID LP RP
	;
VarList	:	ParamDec COMMA VarList
	|	ParamDec
	;
ParamDec	:	Specifier VarDec
		;
CompSt	:	LC DefList StmtList RC
       	|	LC DefList error RC/*error recovery*/
	;
StmtList	:	Stmt StmtList
		|	/*empty*/
		;
Stmt	:	Exp SEMI
     	|	error SEMI/*error recovery*/
	|	CompSt
	|	RETURN Exp SEMI
	|	RETURN error SEMI/*error recovery*/
	|	IF LP Exp RP Stmt	%prec LOWER_THEN_ELSE
	|	IF LP error RP Stmt/*error recovery*/
	|	IF LP Exp RP Stmt ELSE Stmt
	|	WHILE LP Exp RP Stmt
	|	WHILE LP error RP Stmt
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
	|	MINUS Exp
	|	NOT Exp
	|	ID LP Args RP
	|	ID LP error RP/*error recovery*/ 
	|	ID LP RP
	|	Exp LB Exp RB
	|	Exp LB error RB/*error recovery*/
	|	Exp DOT ID
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
