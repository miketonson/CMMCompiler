%{
#include <stdio.h>
#include "lex.yy.c"
#include "tree.c"
expnode *RootNode;
%}
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
%token <type_id> ID
%token <type_type> TYPE
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
Program	:	ExtDefList {	$$ = InsertNode(Program, @$.first_line, 1, 1, $1);
				RootNode = $$;
				}
	;
ExtDefList	:	ExtDef ExtDefList { $$ = InsertNode(ExtDefList, @$.first_line, 1, 2, $1, $2); }
		|	/*empty*/ { $$ = InsertNode(ExtDefList, @$.first_line, 2, 0); }
		;
ExtDef	:	Specifier ExtDecList SEMI {	expnode *SEMIn = TermNode(SEMIm, yylineno);
       						$$ = InsertNode(ExtDef, @$.first_line, 1, 3, $1, $2, SEMIn);
						}
       	|	Specifier error SEMI/*error recovery*/
	|	Specifier SEMI {expnode *SEMIn = TermNode(SEMIm,yylineno);
				$$ = InsertNode(ExtDef, @$.first_line, 2, 2, $1, SEMIn);
				}
	|	Specifier FunDec CompSt { $$ = InsertNode(ExtDef, @$.first_line, 3, 3, $1, $2, $3); }
	;
ExtDecList	:	VarDec { $$ = InsertNode(ExtDecList, @$.first_line, 1, 1, $1); }
		|	VarDec COMMA ExtDecList {expnode *COMMAn = TermNode(COMMAm, yylineno);
						$$ = InsertNode(ExtDecList, @$.first_line, 2, 3, $1, COMMAn, $3);
						}
		;
Specifier	:	TYPE {	expnode *TYPEn = TypeNode(TYPEm, yylineno, $1);
	  			$$ = InsertNode(Specifier, @$.first_line, 1, 1, TYPEn);
				}
		|	StructSpecifier { $$ = InsertNode(Specifier, @$.first_line, 2, 1, $1); }
		;
StructSpecifier	:	STRUCT OptTag LC DefList RC {	expnode *STRUCTn = TermNode(STRUCTm, yylineno);
							expnode *LCn = TermNode(LCm, yylineno);
							expnode *RCn = TermNode(RCm, yylineno);
							$$ = InsertNode(StructSpecifier, @$.first_line, 1, 5, STRUCTn, $2, LCn, $4, RCn);
							}
		|	STRUCT OptTag LC error RC/*error recovery*/
		|	STRUCT Tag {	expnode *STRUCTn = TermNode(STRUCTm, yylineno);
					$$ = InsertNode(StructSpecifier, @$.first_line, 2, 2, STRUCTn, $2);
					}
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
	|	VarDec LB INT RB {	expnode *LBn = TermNode(LBm, yylineno);
					expnode *INTn = IntNode(INTm, yylineno, $3);
					expnode *RBn = TermNode(RBm, yylineno);
					$$ = InsertNode(VarDec, @$.first_line, 2, 4, $1, LBn, INTn, RBn);
				}
	;
FunDec	:	ID LP VarList RP {	expnode *IDn = IdNode(IDm, yylineno, (char*)$1);
       					expnode *LPn = TermNode(LPm, yylineno);
					expnode *RPn = TermNode(RPm, yylineno);
					$$ = InsertNode(FunDec, @$.first_line, 1, 4, IDn, LPn, $3, RPn);
					}
       	|	ID LP error RP/*error recovery*/
	|	ID LP RP {	expnode *IDn = IdNode(IDm, yylineno, (char*)$1);
				expnode *LPn = TermNode(LPm, yylineno);
				expnode *RPn = TermNode(RPm, yylineno);
				$$ = InsertNode(FunDec, @$.first_line, 2, 3, IDn, LPn, RPn);
				}
	;
VarList	:	ParamDec COMMA VarList {expnode *COMMAn = TermNode(COMMAm, yylineno);
					$$ = InsertNode(VarList, @$.first_line, 1, 3, $1, COMMAn, $3);
					}
	|	ParamDec { $$ = InsertNode(VarList, @$.first_line, 2, 1, $1); }
	;
ParamDec	:	Specifier VarDec { $$ = InsertNode(ParamDec, @$.first_line, 1, 2, $1, $2); }
		;
CompSt	:	LC DefList StmtList RC {expnode *LCn = TermNode(LCm, yylineno);
       					expnode *RCn = TermNode(RCm,yylineno);
					$$ = InsertNode(CompSt, @$.first_line, 1, 4, LCn, $2, $3, RCn);
					}
       	|	LC DefList error RC/*error recovery*/
	;
StmtList	:	Stmt StmtList { $$ = InsertNode(StmtList, @$.first_line, 1, 2, $1, $2); }
		|	/*empty*/ { $$ = InsertNode(StmtList, @$.first_line, 2, 0); }
		;
Stmt	:	Exp SEMI {	expnode *SEMIn = TermNode(SEMIm, yylineno);
     				$$ = InsertNode(Stmt, @$.first_line, 1, 2, $1, SEMIn);
				}
     	|	error SEMI/*error recovery*/
	|	CompSt { $$ = InsertNode(Stmt, @$.first_line, 2, 1, $1); }
	|	RETURN Exp SEMI {	expnode *RETURNn = TermNode(RETURNm, yylineno);
					expnode *SEMIn = TermNode(SEMIm, yylineno);
					$$ = InsertNode(Stmt, @$.first_line, 3, 3, RETURNn, $2, SEMIn);
					}
	|	RETURN error SEMI/*error recovery*/
	|	IF LP Exp RP Stmt %prec LOWER_THEN_ELSE {expnode *IFn = TermNode(IFm, yylineno);
							expnode *LPn = TermNode(LPm, yylineno);
							expnode *RPn = TermNode(RPm,yylineno);
							$$ = InsertNode(Stmt, @$.first_line, 4, 5, IFn, LPn, $3, RPn, $5);
							}
	|	IF LP error RP Stmt/*error recovery*/
	|	IF LP Exp RP Stmt ELSE Stmt {	expnode *IFn = TermNode(IFm, yylineno);
						expnode *LPn = TermNode(LPm, yylineno);
						expnode *RPn = TermNode(RPm, yylineno);
						expnode *ELSEn = TermNode(ELSEm, yylineno);
						$$ = InsertNode(Stmt, @$.first_line, 5, 7, IFn, LPn, $3, RPn, $5, ELSEn, $7);
						}
	|	WHILE LP Exp RP Stmt {	expnode *WHILEn = TermNode(WHILEm, yylineno);
					expnode *LPn = TermNode(LPm,yylineno);
					expnode *RPn = TermNode(RPm,yylineno);
					$$ = InsertNode(Stmt, @$.first_line, 6, 5, WHILEn, LPn, $3, RPn, $5);
					}
	|	WHILE LP error RP Stmt/*error recovery*/
	;
DefList	:	Def DefList { $$ = InsertNode(DefList, @$.first_line, 1, 2, $1, $2); }
	|	/*empty*/ { $$ = InsertNode(DefList, @$.first_line, 2, 0); }
	;
Def	:	Specifier DecList SEMI {expnode *SEMIn = TermNode(SEMIm, yylineno);
    					$$ = InsertNode(Def, @$.first_line, 1, 3, $1, $2, SEMIn);
					}
	|	Specifier error SEMI/*error recovery*/
	;
DecList	:	Dec { $$ = InsertNode(DecList, @$.first_line, 1, 1, $1); }
	|	Dec COMMA DecList {	expnode *COMMAn = TermNode(COMMAm, yylineno);
					$$ = InsertNode(DecList, @$.first_line, 2, 3, $1, COMMAn, $3);
					}
	;
Dec	:	VarDec { $$ = InsertNode(Dec, @$.first_line, 1, 1, $1); }
	|	VarDec ASSIGNOP Exp {	expnode *ASSIGNOPn = TermNode(ASSIGNOPm, yylineno);
					$$ = InsertNode(Dec, @$.first_line, 2, 3, $1, ASSIGNOPn, $3);
					}
	;
Exp	:	Exp ASSIGNOP Exp {	expnode *ASSIGNOPn = TermNode(ASSIGNOPm, yylineno);
    					$$ = InsertNode(Exp, @$.first_line, 1, 3, $1, ASSIGNOPn, $3);
					}
	|	Exp AND Exp {	expnode *ANDn = TermNode(ANDm, yylineno);
				$$ =InsertNode(Exp, @$.first_line, 2, 3, $1, ANDn, $3);
				}
	|	Exp OR Exp {	expnode *ORn = TermNode(ORm, yylineno);
				$$ = InsertNode(Exp, @$.first_line, 3, 3, $1, ORn, $3);
				}
	|	Exp RELOP Exp {	expnode *RELOPn = TermNode(RELOPm, yylineno);
				$$ = InsertNode(Exp, @$.first_line, 4, 3, $1, RELOPn, $3);
				}
	|	Exp PLUS Exp {	expnode *PLUSn = TermNode(PLUSm, yylineno);
				$$ = InsertNode(Exp, @$.first_line, 5, 3, $1, PLUSn, $3);
				}
	|	Exp MINUS Exp {	expnode *MINUSn = TermNode(MINUSm, yylineno);
				$$ = InsertNode(Exp, @$.first_line, 6, 3, $1, MINUSn, $3);
				}
	|	Exp STAR Exp {	expnode *STARn = TermNode(STARm, yylineno);
				$$ = InsertNode(Exp, @$.first_line, 7, 3, $1, STARn, $3);
				}
	|	Exp DIV Exp {	expnode *DIVn = TermNode(DIVm, yylineno);
				$$ = InsertNode(Exp, @$.first_line, 8, 3, $1, DIVn, $3);
				}
	|	LP Exp RP {	expnode *LPn = TermNode(LPm,yylineno);
				expnode *RPn = TermNode(RPm,yylineno);
				$$ = InsertNode(Exp, @$.first_line, 9, 3, LPn, $2, RPn );
				}
	|	MINUS Exp {	expnode *MINUSn = TermNode(MINUSm, yylineno);
				$$ = InsertNode(Exp, @$.first_line, 10, 2, MINUSn, $2);
				}
	|	NOT Exp {	expnode *NOTn = TermNode(NOTm, yylineno);
				$$ = InsertNode(Exp, @$.first_line, 11, 2, NOTn, $2);
				}
	|	ID LP Args RP {	expnode *IDn = IdNode(IDm, yylineno, (char*)$1);
				expnode *LPn = TermNode(LPm, yylineno);
				expnode *RPn = TermNode(RPm, yylineno);
				$$ = InsertNode(Exp, @$.first_line, 12, 4, IDn, LPn, $3, RPn);
				}
	|	ID LP error RP/*error recovery*/ 
	|	ID LP RP {	expnode *IDn = IdNode(IDm, yylineno, (char*)$1);
				expnode *LPn = TermNode(LPm, yylineno);
				expnode *RPn = TermNode(RPm, yylineno);
				$$ = InsertNode(Exp, @$.first_line, 13, 3, IDn, LPn, RPn);
				}
	|	Exp LB Exp RB {	expnode *LBn = TermNode(LBm, yylineno);
				expnode *RBn = TermNode(RBm, yylineno);
				$$ = InsertNode(Exp, @$.first_line, 14, 4, $1, LBn, $3, RBn);
				}
	|	Exp LB error RB/*error recovery*/
	|	Exp DOT ID {	expnode *DOTn = TermNode(DOTm, yylineno);
				expnode *IDn = IdNode(IDm, yylineno, (char*)$3);
				$$ = InsertNode(Exp, @$.first_line, 15, 3, $1, DOTn, IDn);
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
	;
Args	:	Exp COMMA Args {expnode *COMMAn = TermNode(COMMAm, yylineno);
     				$$ = InsertNode(Args, @$.first_line, 1, 3, $1, COMMAn, $3);
				}
	|	Exp { $$ = InsertNode(Args, @$.first_line, 2, 1, $1); }
	;
%%
yyerror(char* msg)
{
    fprintf(stderr,"Error type B at line %d: %s\n", yylineno, msg);
}

void PrintKind(int t_num, KIND kind, int lineno)
{
	for(int i=0; i<t_num; i++)
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
	for(int i=0; i<t_num; i++)
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
		case RELOPm:
		{
			printf("RELOP\n");
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
	for(int i=0; i<t_num; i++)
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
	}
}

void PrintTree()
{
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
			printf("end\n");
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
					//printf("num: %d\n", now_num);
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
					//printf("type: %d\n", NODE->node_type);
				}
				else
				{
					//printf("bbb\n");
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
				//printf("aaa\n");
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
	//printf("ccc %d\n", NODE->node_type);
	//PrintMean(tab_num, NODE);
}
