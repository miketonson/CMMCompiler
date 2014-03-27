%{
#include <stdio.h>
#include "lex.yy.c"
expnode *RootNode;
%}
%locations
%union{
	int type_int;
	float type_float;
	char  *type_id;
	int type_type;
	struct expnode *type_node;
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
%token <type_id> ID RELOP
%token <type_type> TYPE
%token <type_node> SEMI COMMA ASSIGNOP PLUS MINUS STAR DIV AND OR DOT NOT 
%token <type_node> LP RP LB RB LC RC STRUCT RETURN IF ELSE WHILE
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
%nonassoc LOWER_THEN_ERROR
%nonassoc error
%%
Program	:	ExtDefList {	$$ = InsertNode(Program, @$.first_line, 1, 1, $1);
				RootNode = $$;
				}
	;
ExtDefList	:	ExtDef ExtDefList { $$ = InsertNode(ExtDefList, @$.first_line, 1, 2, $1, $2); }
		|	/*empty*/ { $$ = InsertNode(ExtDefList, @$.first_line, 2, 0); }
		;
ExtDef	:	Specifier ExtDecList SEMI { $$ = InsertNode(ExtDef, @$.first_line, 1, 3, $1, $2, $3); }
	|	Specifier SEMI { $$ = InsertNode(ExtDef, @$.first_line, 2, 2, $1, $2); }
	|	Specifier FunDec CompSt { $$ = InsertNode(ExtDef, @$.first_line, 3, 3, $1, $2, $3); }
       	|	error SEMI/*error recovery*/ { $$ = InsertNode(ExtDef, yylineno, -1, 0); }
	;
ExtDecList	:	VarDec { $$ = InsertNode(ExtDecList, @$.first_line, 1, 1, $1); }
		|	VarDec COMMA ExtDecList { $$ = InsertNode(ExtDecList, @$.first_line, 2, 3, $1, $2, $3); }
		;
Specifier	:	TYPE {	expnode *TYPEn = TypeNode(TYPEm, yylineno, $1);
	  			$$ = InsertNode(Specifier, @$.first_line, 1, 1, TYPEn);
				}
		|	StructSpecifier { $$ = InsertNode(Specifier, @$.first_line, 2, 1, $1); }
		;
StructSpecifier	:	STRUCT OptTag LC DefList RC { $$ = InsertNode(StructSpecifier, @$.first_line, 1, 5, $1, $2, $3, $4, $5); }
		|	STRUCT Tag { $$ = InsertNode(StructSpecifier, @$.first_line, 2, 2, $1, $2); }
		;
OptTag	:	ID {	expnode *IDn = IdNode(IDm, yylineno, (char*)$1);
       			$$ = InsertNode(OptTag, @$.first_line, 1, 1, IDn);
			}
	|	/*empty*/ { $$ = InsertNode(OptTag, @$.first_line, 2, 0); }
	;
Tag	:	ID {	expnode *IDn = IdNode(IDm, yylineno, (char*)$1);
    			$$ = InsertNode(Tag, @$.first_line, 1, 1, IDn);
			}
	;
VarDec	:	ID {	expnode *IDn = IdNode(IDm, yylineno, (char*)$1);
       			$$ = InsertNode(VarDec, @$.first_line, 1, 1, IDn);
			}
	|	VarDec LB INT RB {	expnode *INTn = IntNode(INTm, yylineno, $3);
					$$ = InsertNode(VarDec, @$.first_line, 2, 4, $1, $2, INTn, $4);
				}
	;
FunDec	:	ID LP VarList RP {	expnode *IDn = IdNode(IDm, yylineno, (char*)$1);
					$$ = InsertNode(FunDec, @$.first_line, 1, 4, IDn, $2, $3, $4);
					}
	|	ID LP RP {	expnode *IDn = IdNode(IDm, yylineno, (char*)$1);
				$$ = InsertNode(FunDec, @$.first_line, 2, 3, IDn, $2, $3);
				}
       	|	error RP/*error recovery*/ { $$ = InsertNode(FunDec, yylineno, -1, 0); }
	;
VarList	:	ParamDec COMMA VarList { $$ = InsertNode(VarList, @$.first_line, 1, 3, $1, $2, $3); }
	|	ParamDec { $$ = InsertNode(VarList, @$.first_line, 2, 1, $1); }
	;
ParamDec	:	Specifier VarDec { $$ = InsertNode(ParamDec, @$.first_line, 1, 2, $1, $2); }
		;
CompSt	:	LC DefList StmtList RC { $$ = InsertNode(CompSt, @$.first_line, 1, 4, $1, $2, $3, $4); }
       	|	error RC/*error recovery*/{ $$ = InsertNode(CompSt, yylineno, -1, 0); }
	;
StmtList	:	Stmt StmtList { $$ = InsertNode(StmtList, @$.first_line, 1, 2, $1, $2); }
		|	/*empty*/ { $$ = InsertNode(StmtList, @$.first_line, 2, 0); }
		;
Stmt	:	Exp SEMI { $$ = InsertNode(Stmt, @$.first_line, 1, 2, $1, $2); }
	|	CompSt { $$ = InsertNode(Stmt, @$.first_line, 2, 1, $1); }
	|	RETURN Exp SEMI { $$ = InsertNode(Stmt, @$.first_line, 3, 3, $1, $2, $3); }
	|	IF LP Exp RP Stmt %prec LOWER_THEN_ELSE { $$ = InsertNode(Stmt, @$.first_line, 4, 5, $1, $2, $3, $4, $5); }
	|	IF LP Exp RP Stmt ELSE Stmt { $$ = InsertNode(Stmt, @$.first_line, 5, 7, $1, $2, $3, $4, $5, $6, $7); }
	|	WHILE LP Exp RP Stmt { $$ = InsertNode(Stmt, @$.first_line, 6, 5, $1, $2, $3, $4, $5); }
     	|	error SEMI/*error recovery*/{$$ = InsertNode(Stmt, yylineno, -1, 0);}
	;
DefList	:	Def DefList { $$ = InsertNode(DefList, @$.first_line, 1, 2, $1, $2); }
	|	/*empty*/ %prec LOWER_THEN_ERROR { $$ = InsertNode(DefList, @$.first_line, 2, 0); }
	;
Def	:	Specifier DecList SEMI { $$ = InsertNode(Def, @$.first_line, 1, 3, $1, $2, $3); }
	|	error SEMI/*error recovery*/{ $$ = InsertNode(Def, yylineno, -1, 0); }
	;
DecList	:	Dec { $$ = InsertNode(DecList, @$.first_line, 1, 1, $1); }
	|	Dec COMMA DecList { $$ = InsertNode(DecList, @$.first_line, 2, 3, $1, $2, $3); }
	;
Dec	:	VarDec { $$ = InsertNode(Dec, @$.first_line, 1, 1, $1); }
	|	VarDec ASSIGNOP Exp { $$ = InsertNode(Dec, @$.first_line, 2, 3, $1, $2, $3); }
	;
Exp	:	Exp ASSIGNOP Exp { $$ = InsertNode(Exp, @$.first_line, 1, 3, $1, $2, $3); }
	|	Exp AND Exp { $$ =InsertNode(Exp, @$.first_line, 2, 3, $1, $2, $3); }
	|	Exp OR Exp { $$ = InsertNode(Exp, @$.first_line, 3, 3, $1, $2, $3); }
	|	Exp RELOP Exp { expnode *RELOPn = RelopNode(RELOPm, yylineno, (char*)$2);
				$$ = InsertNode(Exp, @$.first_line, 4, 3, $1, RELOPn, $3); 
				}
	|	Exp PLUS Exp { $$ = InsertNode(Exp, @$.first_line, 5, 3, $1, $2, $3); }
	|	Exp MINUS Exp { $$ = InsertNode(Exp, @$.first_line, 6, 3, $1, $2, $3); }
	|	Exp STAR Exp { $$ = InsertNode(Exp, @$.first_line, 7, 3, $1, $2, $3); }
	|	Exp DIV Exp { $$ = InsertNode(Exp, @$.first_line, 8, 3, $1, $2, $3); }
	|	LP Exp RP { $$ = InsertNode(Exp, @$.first_line, 9, 3, $1, $2, $3); }
	|	MINUS Exp { $$ = InsertNode(Exp, @$.first_line, 10, 2, $1, $2); }
	|	NOT Exp { $$ = InsertNode(Exp, @$.first_line, 11, 2, $1, $2); }
	|	ID LP Args RP {	expnode *IDn = IdNode(IDm, yylineno, (char*)$1);
				$$ = InsertNode(Exp, @$.first_line, 12, 4, IDn, $2, $3, $4);
				}
	|	ID LP RP {	expnode *IDn = IdNode(IDm, yylineno, (char*)$1);
				$$ = InsertNode(Exp, @$.first_line, 13, 3, IDn, $2, $3);
				}
	|	Exp LB Exp RB {	$$ = InsertNode(Exp, @$.first_line, 14, 4, $1, $2, $3, $4); }
	|	Exp DOT ID { 	expnode *IDn = IdNode(IDm, yylineno, (char*)$3);
				$$ = InsertNode(Exp, @$.first_line, 15, 3, $1, $2, IDn);
				}
	|	ID {	expnode *IDn = IdNode(IDm, yylineno, (char*)$1);
			$$ = InsertNode(Exp, @$.first_line, 16, 1, IDn);
			}
	|	INT {	expnode *INTn = IntNode(INTm, yylineno, $1);
			$$ = InsertNode(Exp, @$.first_line, 17, 1, INTn);
			}
	|	FLOAT {	expnode *FLOATn = FloatNode(FLOATm, yylineno, $1);
			$$ = InsertNode(Exp, @$.first_line, 18, 1, FLOATn);
			}
	|	LP error RP/*error recovery*/ { $$  = InsertNode(Exp, yylineno, -1, 0); }
	|	Exp LB error RB/*error recovery*/{ $$ = InsertNode(Exp, yylineno, -1, 0); }
	;
Args	:	Exp COMMA Args { $$ = InsertNode(Args, @$.first_line, 1, 3, $1, $2, $3); }
	|	Exp { $$ = InsertNode(Args, @$.first_line, 2, 1, $1); }
	;
%%
yyerror(char* msg)
{
    fprintf(stderr,"Error type B at line %d: %s\n", yylineno, msg);
    have_wrong = 1;
}

void PrintKind(int t_num, KIND kind, int lineno)
{
	int i;
	for(i=0; i<t_num; i++)
	{
		printf("  ");
	}
	switch(kind)
	{
		case ExtDefList:
		{
			printf("ExtDefList (%d)\n", lineno);
			break;
		}
		case ExtDef:
		{
			printf("ExtDef (%d)\n", lineno);
			break;
		}
		case Specifier:
		{
			printf("Specifier (%d)\n", lineno);
			break;
		}
		case ExtDecList:
		{
			printf("ExtDecList (%d)\n", lineno);
			break;
		}
		case FunDec:
		{
			printf("FunDec (%d)\n", lineno);
			break;
		}
		case CompSt:
		{
			printf("CompSt (%d)\n", lineno);
			break;
		}
		case VarDec:
		{
			printf("VarDec (%d)\n", lineno);
			break;
		}
		case StructSpecifier:
		{
			printf("StructSpecifier (%d)\n", lineno);
			break;
		}
		case OptTag:
		{
			printf("OptTag (%d)\n", lineno);
			break;
		}
		case DefList:
		{
			printf("DefList (%d)\n", lineno);
			break;
		}
		case Tag:
		{
			printf("Tag (%d)\n", lineno);
			break;
		}
		case VarList:
		{
			printf("VarList (%d)\n", lineno);
			break;
		}
		case ParamDec:
		{
			printf("ParamDec (%d)\n", lineno);
			break;
		}
		case StmtList:
		{
			printf("StmtList (%d)\n", lineno);
			break;
		}
		case Stmt:
		{
			printf("Stmt (%d)\n", lineno);
			break;
		}
		case Exp:
		{
			printf("Exp (%d)\n", lineno);
			break;
		}
		case Def:
		{
			printf("Def (%d)\n", lineno);
			break;
		}
		case DecList:
		{
			printf("DecList (%d)\n", lineno);
			break;
		}
		case Dec:
		{
			printf("Dec (%d)\n", lineno);
			break;
		}
		case Args:
		{
			printf("Args (%d)\n", lineno);
			break;
		}
		default:
		{
			printf("error in type 1\n");
			break;
		}
	}
}

void PrintTerm(int t_num, TERM term)
{
	int i;
	for(i=0; i<t_num; i++)
	{
		printf("  ");
	}
	switch(term)
	{
		case SEMIm:
		{
			printf("SEMI\n");
			break;
		}
		case COMMAm:
		{
			printf("COMMA\n");
			break;
		}
		case ASSIGNOPm:
		{
			printf("ASSIGNOP\n");
			break;
		}
		case PLUSm:
		{
			printf("PLUS\n");
			break;
		}
		case MINUSm:
		{
			printf("MINUS\n");
			break;
		}
		case STARm:
		{
			printf("STAR\n");
			break;
		}
		case DIVm:
		{
			printf("DIV\n");
			break;
		}
		case ANDm:
		{
			printf("AND\n");
			break;
		}
		case ORm:
		{
			printf("OR\n");
			break;
		}
		case DOTm:
		{
			printf("DOT\n");
			break;
		}
		case NOTm:
		{
			printf("NOT\n");
			break;
		}
		case LPm:
		{
			printf("LP\n");
			break;
		}
		case RPm:
		{
			printf("RP\n");
			break;
		}
		case LBm:
		{
			printf("LB\n");
			break;
		}
		case RBm:
		{
			printf("RB\n");
			break;
		}
		case LCm:
		{
			printf("LC\n");
			break;
		}
		case RCm:
		{
			printf("RC\n");
			break;
		}
		case STRUCTm:
		{
			printf("STRUCT\n");
			break;
		}
		case RETURNm:
		{
			printf("RETURN\n");
			break;
		}
		case IFm:
		{
			printf("IF\n");
			break;
		}
		case ELSEm:
		{
			printf("ELSE\n");
			break;
		}
		case WHILEm:
		{
			printf("WHILE\n");
			break;
		}
		default:
		{
			printf("error at type 2\n");
			break;
		}
	}
}

void PrintMean(int t_num, expnode *mean_node)
{
	int i;
	for(i=0; i<t_num; i++)
	{
		printf("  ");
	}
	switch(mean_node->mean)
	{
		case IDm:
		{
			printf("ID: %s\n", mean_node->id_vaule);
			break;
		}
		case INTm:
		{
			printf("INT: %d\n", mean_node->int_vaule);
			break;
		}
		case FLOATm:
		{
			printf("FLOAT: %f\n", mean_node->float_vaule);
			break;
		}
		case TYPEm:
		{
			if(mean_node->type_vaule == 0)
			{
				printf("TYPE: int\n");
				break;
			}
			else
			{
				printf("TYPE: float\n");
				break;
			}
		}
		case RELOPm:
		{
			printf("RELOP: ");
			switch(mean_node->relop_vaule)
			{
				case 1:
				{
					printf(">\n");
					break;
				}
				case 2:
				{
					printf("<\n");
					break;
				}
				case 3:
				{
					printf(">=\n");
					break;
				}
				case 4:
				{
					printf("<=\n");
					break;
				}
				case 5:
				{
					printf("==\n");
					break;
				}
				case 6:
				{
					printf("!=\n");
					break;
				}
				default:
				{
					printf("relop error\n");
					break;
				}
			}
			break;
		}
		default:
		{
			printf("error print at type 3\n");
		}
	}
}

void PrintTree()
{
	if(have_wrong == 1)
	{
		return;
	}
//	printf("print start\n");
	expnode *NODE = RootNode;
	int tab_num = 0;
	if(NODE->kind == Program)
	{
		printf("Program (%d)\n", NODE->lineno);
		NODE->search_num = 1;
		NODE = NODE->son_node[0];
		tab_num++;
	}
	else
	{
		printf("error\n");
		return;
	}
	while(1)
	{
		if(NODE->kind == Program && NODE->node_type == 1)
		{
//			printf("print end\n");
			break;
		}
		switch(NODE->node_type)
		{
			case 1:
			{
				if(NODE->search_num == 0)
				{
					PrintKind(tab_num, NODE->kind, NODE->lineno);
				}
				if(NODE->search_num < NODE->node_sum)
				{
					int now_num = NODE->search_num;
					NODE->search_num++;
					tab_num++;
					if(NODE->son_node[now_num]->node_sum > 0 || NODE->son_node[now_num]->node_type != 1)
					{
						NODE = NODE->son_node[now_num];
					}
					else
					{
						tab_num--;
					}
				}
				else
				{
					NODE = NODE->father_node;
					tab_num--;
				}
				break;
			}
			case 2:
			{
				PrintTerm(tab_num, NODE->term);
				NODE = NODE->father_node;
				tab_num--;
				break;
			}
			case 3:
			{
				PrintMean(tab_num, NODE);
				NODE = NODE->father_node;
				tab_num--;
				break;
			}
			default:
			{
				printf("error in the null\n");
				break;
			}
		}
	}
}
