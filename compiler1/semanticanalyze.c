/*
 * =====================================================================================
 *
 *       Filename:  semanticanalyze.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/19/2014 01:47:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "tree.h"
#include "semanticlist.h"
#include "semanticanalyze.h"
#include "IR.h"

int nowLayerNum = 0;
type *nowReturnType;

// only for test
void printTestError()
{
	printSemError();
}

// first time for hash table insert
void TypeInsert(expnode *NODE)
{
	switch(NODE->kind)
	{
		case ExtDef:
			{
				switch(NODE->exp_num)
				{
					case 1: // for var def
						{
							type *varDefType = SpecifierAnalyzer(NODE->son_node[0]);
							if(varDefType->kind == structure && varDefType->u.stru.structure != NULL && varDefType->u.stru.struct_name !=NULL)
							{
								addStructPoint(varDefType, NODE->lineno);
							}
						
							ExtDecAnalyzer(varDefType, NODE->son_node[1]);
							NODE->search_num = NODE->node_sum;
							NODE = NODE->father_node;
							break;
						}
					case 2: // for struct dec
						{
							type *structDecType = SpecifierAnalyzer(NODE->son_node[0]);
							if(structDecType->kind == structure && structDecType->u.stru.structure != NULL && structDecType->u.stru.struct_name !=NULL)
							{
								addStructPoint(structDecType, NODE->lineno);
							}
							NODE->search_num = NODE->node_sum;
							NODE = NODE->father_node;
							break;
						}
					case 3: // for function def
						{
							type *funcType = SpecifierAnalyzer(NODE->son_node[0]);
							if(funcType->kind == structure && funcType->u.stru.structure != NULL && funcType->u.stru.struct_name !=NULL)
							{
								addStructPoint(funcType, NODE->lineno);
							}
							nowLayerNum++;
							pushLayerStack(nowLayerNum);
							FunDecAnalyzer(funcType, NODE->son_node[1], 1);
							NODE->search_num = 2;
							break;
						}
					case 4: // for function dec
						{
							type *funcType = SpecifierAnalyzer(NODE->son_node[0]);
							if(funcType->kind == structure && funcType->u.stru.structure != NULL && funcType->u.stru.struct_name !=NULL)
							{
								addStructPoint(funcType, NODE->lineno);
							}
							nowLayerNum++;
							pushLayerStack(nowLayerNum);
							FunDecAnalyzer(funcType, NODE->son_node[1], 0);
							pullLayerStack();
							nowLayerNum--;
							NODE->search_num = NODE->node_sum;
							NODE = NODE->father_node;
							break;
						}
					default:
						{
							printf("error exp num for extdef node\n");
							break;
						}
				}
				break;
			}
		case CompSt:
			{
				DefListAnalyzer(NODE->son_node[1]);
				StmtListAnalyzer(NODE->son_node[2]);
				pullLayerStack();
				nowLayerNum--;
				NODE->search_num = NODE->node_sum;
				NODE = NODE->father_node;
			}
		default:
			{
	//			printf("don't mind\n");
				break;
			}
	}
}
// analyze a DefList Node(sub-tree) and insert var def into hash table
void DefListAnalyzer(expnode *defListNode)
{
	type *nouse = NULL;
	while(defListNode->exp_num == 1)
	{
		DefAnalyzer(defListNode->son_node[0], 1, nouse);
		defListNode = defListNode->son_node[1];
	}
	return;
}
// analyze a StmtList Node(sub-tree) and check semantic errors
void StmtListAnalyzer(expnode *stmtListNode)
{
	while(stmtListNode->exp_num == 1)
	{
		StmtAnalyzer(stmtListNode->son_node[0]);
		stmtListNode = stmtListNode->son_node[1];
	}
	return;
}
// analyze a Stmt Node(sub-tree) and check semantic errors
void StmtAnalyzer(expnode *stmtNode)
{
	switch(stmtNode->exp_num)
	{
		case 1: // exp SEMI
			{
				type *expType;
				expType = ExpAnalyzer(stmtNode->son_node[0], 1);
				
				/* code for IR*/
				if(expType != NULL)
				{
					translate_STMT(stmtNode);				
				}
				/* code end*/
				
				break;
			}
		case 2: // compSt
			{
				DefListAnalyzer(stmtNode->son_node[0]->son_node[1]);
				StmtListAnalyzer(stmtNode->son_node[0]->son_node[2]);
				break;
			}
		case 3: // return
			{
				type *expType;
				expType = ExpAnalyzer(stmtNode->son_node[1], 0);
				// here have to compare with the func return type
				if(expType != NULL && isSameType(nowReturnType, expType, nowLayerNum) == 1)
				{
					insertError(8, stmtNode->lineno, NULL);
				}
				
				/* code for IR*/
				if(expType != NULL)
				{
					translate_STMT(stmtNode);				
				}
				/* code end*/

				break;
			}
		case 4: // IF
			{
				type *expType;
				expType = ExpAnalyzer(stmtNode->son_node[2], 2);
				nowLayerNum++;
				pushLayerStack(nowLayerNum);
				
				/* code for IR*/
				Operand *label1;//
				Operand *label2;//
				label1 = new_label();//
				label2 = new_label();//

				translate_COND(stmtNode->son_node[2], label1, label2);//

				InterCode *code1;//
				InterCode *code2;//
				code1 = malloc(sizeof(InterCode));//
				code2 = malloc(sizeof(InterCode));//
				code1->prev = NULL;
				code1->next = NULL;
				
				code2->prev = NULL;
				code2->next = NULL;
				

				code1->kind = LABELc;//
				code2->kind = LABELc;//
				code1->u.op = label1;//
				code2->u.op = label2;//
				insertCodeList(code1);//
				/* code end*/

				StmtAnalyzer(stmtNode->son_node[4]);
				
				/* code for IR*/
				insertCodeList(code2);//
				/* code end*/

				pullLayerStack();
				nowLayerNum--;
				break;
			}
		case 5: // IF ELSE
			{
				type *expType;
				expType = ExpAnalyzer(stmtNode->son_node[2], 2);
				nowLayerNum++;
				pushLayerStack(nowLayerNum);
				
				/* code for IR*/
				Operand *label1;//
				Operand *label2;//
				Operand *label3;//
				label1 = new_label();//
				label2 = new_label();//
				label3 = new_label();//
				
				translate_COND(stmtNode->son_node[2], label1, label2);//

				InterCode *code1;//
				InterCode *code2;//
				InterCode *code3;//
				code1 = malloc(sizeof(InterCode));//
				code2 = malloc(sizeof(InterCode));//
				code3 = malloc(sizeof(InterCode));//
				code1->prev = NULL;
				code1->next = NULL;
				
				code2->prev = NULL;
				code2->next = NULL;
				
				code3->prev = NULL;
				code3->next = NULL;
				

				code1->kind = LABELc;//
				code2->kind = LABELc;//
				code3->kind = LABELc;//
				code1->u.op = label1;//
				code2->u.op = label2;//
				code3->u.op = label3;//
				insertCodeList(code1);//
				/* code end*/

				StmtAnalyzer(stmtNode->son_node[4]);
				
				/* code for IR*/
				InterCode *code4;//
				code4 = malloc(sizeof(InterCode));//
				code4->prev = NULL;
				code4->next = NULL;
				
				code4->kind = GOTOc;//
				code4->u.op = label3;//
				insertCodeList(code4);
				/* code end*/

				pullLayerStack();
				nowLayerNum--;
				nowLayerNum++;
				pushLayerStack(nowLayerNum);

				/* code for IR*/
				insertCodeList(code2);//
				/* code end*/

				StmtAnalyzer(stmtNode->son_node[6]);

				/* code for IR*/
				insertCodeList(code3);//
				/* code end*/

				pullLayerStack();
				nowLayerNum--;
				break;
			}
		case 6: // WHILE
			{
				type *expType;
				expType = ExpAnalyzer(stmtNode->son_node[2], 2);
				nowLayerNum++;
				pushLayerStack(nowLayerNum);
				
				/* code for IR*/
				Operand *label1;//
				Operand *label2;//
				Operand *label3;//
				label1 = new_label();//
				label2 = new_label();//
				label3 = new_label();//
				
				InterCode *code1;//
				code1 = malloc(sizeof(InterCode));//
				code1->prev = NULL;
				code1->next = NULL;
				
				code1->kind = LABELc;//
				code1->u.op = label1;//
				insertCodeList(code1);//
			
				translate_COND(stmtNode->son_node[2], label2, label3);//

				InterCode *code2;//
				InterCode *code3;//
				InterCode *code4;//
				code2 = malloc(sizeof(InterCode));//
				code3 = malloc(sizeof(InterCode));//
				code4 = malloc(sizeof(InterCode));//
				code2->prev = NULL;
				code2->next = NULL;
				
				code3->prev = NULL;
				code3->next = NULL;
				
				code4->prev = NULL;
				code4->next = NULL;
				

				code2->kind = LABELc;//
				code3->kind = LABELc;//
				code4->kind = GOTOc;//
				code2->u.op = label2;//
				code3->u.op = label3;//
				code4->u.op = label1;//
				insertCodeList(code2);//
				/* code end*/
				
				StmtAnalyzer(stmtNode->son_node[4]);
				
				/* code for IR*/
				insertCodeList(code4);//
				insertCodeList(code3);//
				/* code end*/

				pullLayerStack();
				nowLayerNum--;
				break;
			}
	}
}
// analyze a Exp Node(sub-tree) and return something by the etype requested
// etype:
// 0 for finding a real type, from + - * / , or int float struct array
// 1 for analyze =
// 2 for analyze booleans, from AND OR RELOP NOT
// 3 for find if it is a left type
type * ExpAnalyzer(expnode *expNode, int etype)
{
	type *thisType;
	switch(expNode->exp_num)
	{
		case 1: // =
			{
				if(etype == 1 || etype == 2)
				{
					type *leftType = ExpAnalyzer(expNode->son_node[0], 3);
					type *rightType = ExpAnalyzer(expNode->son_node[2], 0);
					if(leftType == NULL || rightType == NULL)
					{
						thisType = NULL;
						return thisType;
					}
					int errorType = isSameType(leftType, rightType, nowLayerNum);
					if(errorType == 1)
					{
						insertError(5, expNode->lineno, NULL);
						thisType = NULL;
						return thisType;
					}
					else
					{
						thisType = leftType;
						return thisType;
					}
				}
				else
				{
					thisType = NULL;
					return thisType;
				}
				break;
			}
		case 2: // AND
		case 3: // OR
		case 4: // RELOP
			{
				if(etype == 2 || etype == 1 || etype == 0)
				{
					type *firType = ExpAnalyzer(expNode->son_node[0], 0);
					type *secType = ExpAnalyzer(expNode->son_node[2], 0);
					if(firType == NULL || secType == NULL)
					{
						thisType = NULL;
						return thisType;
					}
					if((firType->kind == basic && firType->u.basic == 0) && (secType->kind == basic && secType->u.basic == 0))
					{
						thisType = firType;
						return thisType;
					}
					else
					{
						insertError(7, expNode->lineno, NULL);
						thisType = NULL;
						return thisType;
					}
				}
				else if(etype == 3)
				{
					insertError(6, expNode->lineno, NULL);
					thisType = NULL;
					return thisType;
				}
				else
				{
					thisType = NULL;
					return thisType;
				}
				break;
			}
		case 5: // PLUS
		case 6: // MINUS
		case 7: // STAR
		case 8: // DIV
			{
				if(etype == 0 || etype == 1 || etype == 2)
				{
					type *firType = ExpAnalyzer(expNode->son_node[0], 0);
					type *secType = ExpAnalyzer(expNode->son_node[2], 0);
					if(firType == NULL || secType == NULL)
					{
						thisType = NULL;
						return thisType;
					}
					if(isSameType(firType, secType, nowLayerNum) == 1 || firType->kind == array || firType->kind == structure)
					{
						insertError(7, expNode->lineno, NULL);
						thisType = NULL;
						return thisType;
					}
					else
					{
						thisType = firType;
						return thisType;
					}
				}
				else if(etype == 3)
				{
					insertError(6, expNode->lineno, NULL);
					thisType = NULL;
					return thisType;
				}
				else
				{
					thisType = NULL;
					return thisType;
				}
				break;
			}
		case 9: // LP EXP RP
			{
				if(etype == 0 || etype == 2 || etype == 3 || etype == 1)
				{
					thisType = ExpAnalyzer(expNode->son_node[1], etype);
					return thisType;
				}
				else
				{
					thisType = NULL;
					return thisType;
				}
				break;
			}
		case 10: // MINUS EXP
			{
				if(etype == 0 || etype == 1 || etype == 2) 
				{
					thisType = ExpAnalyzer(expNode->son_node[1], 0);
					return thisType;
				}
				else if(etype == 3)
				{
					insertError(6, expNode->lineno, NULL);
					thisType = NULL;
					return thisType;
				}
				else
				{
					thisType = NULL;
					return thisType;
				}
				break;
			}
		case 11: // NOT EXP
			{
				if(etype == 2 || etype == 1)
				{
					thisType = ExpAnalyzer(expNode->son_node[1], 2);
					return thisType;
				}
				else if(etype == 3)
				{
					insertError(6, expNode->lineno, NULL);
					thisType = NULL;
					return thisType;
				}
				else
				{
					thisType = NULL;
					return thisType;
				}
				break;
			}
		case 12: // ID LP ARGS RP
			{
				if(etype == 0 || etype == 1 || etype == 2)
				{
					point *thisFunc = findPoint(expNode->son_node[0]->id_vaule, 1, nowLayerNum);
					if(thisFunc == NULL)
					{
						thisFunc = findPoint(expNode->son_node[0]->id_vaule, 0, nowLayerNum);
						point *isFunc = findPoint(expNode->son_node[0]->id_vaule, 2, nowLayerNum);
						if(thisFunc == NULL && isFunc != NULL)
						{
							insertError(11, expNode->lineno, NULL);
							thisType = NULL;
							return thisType;
						}
						else if(thisFunc == NULL && isFunc == NULL)
						{
							insertError(2, expNode->lineno, NULL);
							thisType = NULL;
							return thisType;
						}
						// check if same with func dec
						thisType = thisFunc->p.func_decPoint->returnType;
						var *funcVarDef = thisFunc->p.func_decPoint->funcVarDef;
						expnode *thisArgNode = expNode->son_node[2];
						while(thisArgNode->exp_num == 1)
						{
							type *argType = ExpAnalyzer(thisArgNode->son_node[0], 0);
							if(funcVarDef == NULL || argType == NULL)
							{
								insertError(9, expNode->lineno, NULL);
								return thisType;
								break;
							}
							else if(isSameType(funcVarDef->var_type, argType, nowLayerNum) == 1)
							{
								insertError(9, expNode->lineno, NULL);
								return thisType;
								break;
							}
							thisArgNode = thisArgNode->son_node[2];
							funcVarDef = funcVarDef->t.funcDef_tail;
						}
						type *argType = ExpAnalyzer(thisArgNode->son_node[0], 0);
						if(funcVarDef == NULL || argType == NULL)
						{
							insertError(9, expNode->lineno, NULL);
							return thisType;
						}
						else if(isSameType(funcVarDef->var_type, argType, nowLayerNum) == 1)
						{
							insertError(9, expNode->lineno, NULL);
							return thisType;
						}
						else
						{
							funcVarDef = funcVarDef->t.funcDef_tail;
							if(funcVarDef != NULL)
							{
								insertError(9, expNode->lineno, NULL);
								return thisType;
							}
						}
						// add this error for later check
						insertError(2, expNode->lineno, thisFunc->p.func_decPoint->name);
						return thisType;
					}
					// check if same with func def
					thisType = thisFunc->p.func_defPoint->returnType;
					var *funcVarDef = thisFunc->p.func_defPoint->funcVarDef;
					expnode *thisArgNode = expNode->son_node[2];
					while(thisArgNode->exp_num == 1)
					{
						type *argType = ExpAnalyzer(thisArgNode->son_node[0], 0);
						if(funcVarDef == NULL || argType == NULL)
						{
							insertError(9, expNode->lineno, NULL);
							return thisType;
							break;
						}
						else if(isSameType(funcVarDef->var_type, argType, nowLayerNum) == 1)
						{
							insertError(9, expNode->lineno, NULL);
							return thisType;
							break;
						}
						thisArgNode = thisArgNode->son_node[2];
						funcVarDef = funcVarDef->t.funcDef_tail;
					}
					type *argType = ExpAnalyzer(thisArgNode->son_node[0], 0);
					if(funcVarDef == NULL || argType == NULL)
					{
						insertError(9, expNode->lineno, NULL);
						return thisType;
					}
					else if(isSameType(funcVarDef->var_type, argType, nowLayerNum) == 1)
					{
						insertError(9, expNode->lineno, NULL);
						return thisType;
					}
					else
					{
						funcVarDef = funcVarDef->t.funcDef_tail;
						if(funcVarDef != NULL)
						{
							insertError(9, expNode->lineno, NULL);
							return thisType;
						}
					}		
					return thisType;
				}
				else if(etype == 3)
				{
					insertError(6, expNode->lineno, NULL);
					thisType = NULL;
					return thisType;
				}
				else
				{
					thisType = NULL;
					return thisType;
				}
				break;
			}
		case 13: // ID LP RP
			{
				if(etype == 0 || etype == 1 || etype == 2)
				{
					point *thisFunc = findPoint(expNode->son_node[0]->id_vaule, 1, nowLayerNum);
					if(thisFunc == NULL)
					{
						thisFunc = findPoint(expNode->son_node[0]->id_vaule, 0, nowLayerNum);
						point *isFunc = findPoint(expNode->son_node[0]->id_vaule, 2, nowLayerNum);
						if(thisFunc == NULL && isFunc != NULL)
						{
							insertError(11, expNode->lineno, NULL);
							thisType = NULL;
							return thisType;
						}
						else if(thisFunc == NULL && isFunc == NULL)
						{
							insertError(2, expNode->lineno, NULL);
							thisType = NULL;
							return thisType;
						}

						thisType = thisFunc->p.func_decPoint->returnType;
						if(thisFunc->p.func_decPoint->funcVarDef != NULL)
						{
							insertError(9, expNode->lineno, NULL);
							return thisType;
						}
						insertError(2, expNode->lineno, thisFunc->p.func_decPoint->name);
						return thisType;
					}
					thisType = thisFunc->p.func_defPoint->returnType;
					if(thisFunc->p.func_defPoint->funcVarDef != NULL)
					{
						insertError(9, expNode->lineno, NULL);
						return thisType;
					}
					return thisType;
				}
				else if(etype == 3)
				{
					insertError(6, expNode->lineno, NULL);
					thisType = NULL;
					return thisType;
				}
				else
				{
					thisType = NULL;
					return thisType;
				}
				break;
			}
		case 14: // EXP LB EXP RB
			{
				if(etype == 0 || etype == 1 || etype == 3 || etype == 2)
				{
					type *arrayType;
					arrayType = ExpAnalyzer(expNode->son_node[0], 0);
					if(arrayType == NULL)
					{
						thisType = NULL;
					}
					if(arrayType->kind == array && arrayType->u.array.elem != NULL)
					{
						thisType = arrayType->u.array.elem;
					}
					else
					{
						insertError(10, expNode->lineno, NULL);
						thisType = NULL;
					}
					type *innerType;
					innerType = ExpAnalyzer(expNode->son_node[2], 0);
					if(innerType != NULL && (innerType->kind != basic || innerType->u.basic != 0))
					{
						insertError(12, expNode->lineno, NULL);
					}
					return thisType;
				}
				else
				{
					thisType = NULL;
					return thisType;
				}
				break;
			}
		case 15: // EXP DOT ID
			{
				if(etype == 0 || etype == 1 || etype == 3 || etype == 2)
				{
					type *structType;
					structType = ExpAnalyzer(expNode->son_node[0], 0);
					if(structType->u.stru.struct_name != NULL && structType->u.stru.structure == NULL)
					{
						point *findStructPoint = findPoint(structType->u.stru.struct_name, 3, nowLayerNum);
						structType = findStructPoint->p.struct_decPoint.struct_decP;
					}
					if(structType == NULL)
					{
						thisType = NULL;
						return thisType;
					}

					if(structType->kind != structure)
					{
						insertError(13, expNode->lineno, NULL);
						thisType = NULL;
						return thisType;
					}
					int have_var = 0;
					var *varTail = structType->u.stru.structure;
					while(varTail != NULL)
					{
						if(strcmp(expNode->son_node[2]->id_vaule,  varTail->name) == 0)
						{
							thisType = varTail->var_type;
							have_var = 1;
							break;
						}
						varTail = varTail->t.struct_tail;
					}
					if(have_var == 0)
					{
						insertError(14, expNode->lineno, NULL);
						thisType = NULL;
						return thisType;
					}
					else
					{
						return thisType;
					}
				}
				else
				{
					thisType = NULL;
					return thisType;
				}
				break;
			}
		case 16: //  ID
			 {
				 if(etype == 0 || etype == 1 || etype == 2 || etype == 3)
				 {
					 point *herePoint;
					herePoint = findPoint(expNode->son_node[0]->id_vaule, 2, nowLayerNum);
					 if(herePoint == NULL)
					 {
						 insertError(1, expNode->lineno, NULL);
						 thisType = NULL;
						 return thisType;
					 }
					 thisType = herePoint->p.var_defPoint.var_defP->var_type;
					 return thisType;
				 }
				 else
				 {
					 thisType = NULL;
					 return thisType;
				 }
				 break;
			 }
		case 17: // INT
			 {
				 if(etype == 0 || etype == 1 || etype == 2)
				 {
					 type *intType;
					 intType = malloc(sizeof(type));
					 intType->kind = basic;
					 intType->u.basic = 0;
					 thisType = intType;
					 return thisType;
				 }
				 else if(etype == 3)
				 {
					 insertError(6, expNode->lineno, NULL);
					 thisType = NULL;
					 return thisType;
				 }
				 else
				 {
					 thisType = NULL;
					 return thisType;
				 }
				 break;
			 }
		case 18: // FLOAT
			 {
				 if(etype == 0 || etype == 1 || etype == 2)
				 {
					 type *floatType;
					 floatType = malloc(sizeof(type));
					 floatType->kind = basic;
					 floatType->u.basic = -1;
					 thisType = floatType;
					 return thisType;
				 }
				 else if(etype == 3)
				 {
					 insertError(6, expNode->lineno, NULL);
					 thisType = NULL;
					 return thisType;
				 }
				 else
				 {
					 thisType = NULL;
					 return thisType;
				 }
				 break;
			 }
	}
}
// analyze a FunDec Node(sub-tree) and insert func_def and func_dec points into hash table
// ftype 0 for dec, 1 for def
void FunDecAnalyzer(type *funcType, expnode *funDecNode, int ftype)
{
	int errorType;
	point *funcPoint;
	funcPoint = malloc(sizeof(point));
	funcDef *funcD;
	funcD = malloc(sizeof(funcDef));
	funcD->returnType = funcType;
	funcD->name = malloc(strlen(funDecNode->son_node[0]->id_vaule) + 1);
	strcpy(funcD->name, funDecNode->son_node[0]->id_vaule);
	switch(ftype)
	{
		case 0:
			{
				funcPoint->point_type = func_dec;
				funcPoint->p.func_decPoint = funcD;
				break;
			}
		case 1:
			{
				nowReturnType = funcType;
				funcPoint->point_type = func_def;
				funcPoint->p.func_defPoint = funcD;
				break;
			}
		default:
			{
				printf("error f type input\n");
				return;
				break;
			}
	}

	if(funDecNode->exp_num == 2)
	{
		funcD->funcVarDef = NULL;
		errorType = addFuncTable(funcPoint);
	}
	else
	{
		expnode *varListNode = funDecNode->son_node[2];
		if(varListNode->exp_num == 1)
		{
			expnode *pDec = varListNode->son_node[0];
			type *funcDefType = SpecifierAnalyzer(pDec->son_node[0]);
			var *funcDef = VarDecAnalyzer(funcDefType, pDec->son_node[1]);
	
			if(funcDefType->kind == structure && funcDefType->u.stru.struct_name != NULL && funcDefType->u.stru.structure != NULL)
			{
				addStructPoint(funcDefType, pDec->lineno);
			}
			addVarPoint(funcDef, pDec->lineno);
			funcD->funcVarDef = funcDef;
			var *nextDef = funcDef;
			varListNode = varListNode->son_node[2];
	
			while(varListNode->exp_num == 1)
			{
				pDec = varListNode->son_node[0];
				funcDefType = SpecifierAnalyzer(pDec->son_node[0]);
				funcDef = VarDecAnalyzer(funcDefType, pDec->son_node[1]);
	
				if(funcDefType->kind == structure && funcDefType->u.stru.struct_name != NULL && funcDefType->u.stru.structure != NULL)
				{
					addStructPoint(funcDefType, pDec->lineno);
				}
				addVarPoint(funcDef, pDec->lineno);
				
				nextDef->t.funcDef_tail = funcDef;
				nextDef = funcDef;
				varListNode = varListNode->son_node[2];
			}
			pDec = varListNode->son_node[0];
			funcDefType = SpecifierAnalyzer(pDec->son_node[0]);
			funcDef = VarDecAnalyzer(funcDefType, pDec->son_node[1]);
			
			if(funcDefType->kind == structure && funcDefType->u.stru.struct_name != NULL && funcDefType->u.stru.structure != NULL)
			{
				addStructPoint(funcDefType, pDec->lineno);
			}
			addVarPoint(funcDef, pDec->lineno);
			
			nextDef->t.funcDef_tail = funcDef;
			funcDef->t.funcDef_tail = NULL;
	
			errorType = addFuncTable(funcPoint);
		}
		else if(varListNode->exp_num == 2)
		{
			expnode *pDec = varListNode->son_node[0];
			type *funcDefType = SpecifierAnalyzer(pDec->son_node[0]);
			var *funcDef = VarDecAnalyzer(funcDefType, pDec->son_node[1]);
	
			if(funcDefType->kind == structure && funcDefType->u.stru.struct_name != NULL && funcDefType->u.stru.structure != NULL)
			{
				addStructPoint(funcDefType, pDec->lineno);
			}
			addVarPoint(funcDef, pDec->lineno);
			funcD->funcVarDef = funcDef;
			funcDef->t.funcDef_tail = NULL;
			errorType = addFuncTable(funcPoint);
		}
	}
	switch(errorType)
	{
		case 0:
			{
				insertError(18, funDecNode->lineno, funcD->name);
				break;
			}
		case 1:
			{
				insertError(4, funDecNode->lineno, NULL);
				break;
			}
		case 2:
			{
				insertError(19, funDecNode->lineno, NULL);
				break;
			}
	}
	return;
}
// analyze a ExtDecList node(sub-tree) and insert the points into the hash table
void ExtDecAnalyzer(type *varDefType, expnode *extDecNode)
{
	var *varDec;
	while(extDecNode->exp_num == 2)
	{
		varDec = VarDecAnalyzer(varDefType, extDecNode->son_node[0]);
		addVarPoint(varDec, extDecNode->lineno);

		/* code for IR*/
		if(varDefType->kind == structure || varDec->var_type->kind == array)
		{
			mem_dec(varDec);
		}
		/* code end*/
		
		extDecNode = extDecNode->son_node[2];
	}
	varDec = VarDecAnalyzer(varDefType, extDecNode->son_node[0]);
	addVarPoint(varDec, extDecNode->lineno);
	
	/* code for IR*/
	if(varDefType->kind == structure || varDec->var_type->kind == array)
	{
		mem_dec(varDec);
	}
	/* code end*/
}

// analyze a VarDec node(sub-tree) and return a var struct, can do array and def
var * VarDecAnalyzer(type *varDefType, expnode *varDecNode)
{
	var *thisVar;
	if(varDecNode->kind != VarDec || varDecNode->node_type != 1)
	{
		printf("vardec analyze wrong! Input is not a vardec\n");
		thisVar = NULL;
		return thisVar;
	}
	thisVar = malloc(sizeof(var));
	if(varDefType->kind == structure && varDefType->u.stru.structure == NULL)
	{
		point *structPoint = findPoint(varDefType->u.stru.struct_name, 3, nowLayerNum);
		if(structPoint == NULL)
		{
			insertError(17, varDecNode->lineno, NULL);
		}
	}
	switch(varDecNode->exp_num)
	{
		case 1:
			{
				expnode *myId = varDecNode->son_node[0];
				thisVar->name = malloc(strlen(myId->id_vaule)+1);
				strcpy(thisVar->name, myId->id_vaule);
				thisVar->var_type = varDefType;
				return thisVar;
				break;
			}
		case 2:
			{
				type *thisArrayType;
				thisArrayType = malloc(sizeof(type));
				thisArrayType->kind = array;
				thisArrayType->u.array.elem = varDefType;
				thisArrayType->u.array.size = varDecNode->son_node[2]->int_vaule;
				varDecNode = varDecNode->son_node[0];
				thisVar = VarDecAnalyzer(thisArrayType, varDecNode);
				return thisVar;
				break;
			}
		default:
			{
				printf("vardec exp num error\n");
				thisVar = NULL;
				return thisVar;
				break;
			}
	}
}

// analyze a specifier node(sub-tree) and return a type
type * SpecifierAnalyzer(expnode *specifier)
{
	type *thisType;
	if(specifier->kind != Specifier || specifier->node_type != 1)
	{
		printf("Specifier analyze wrong! Input is not a specifier\n");
		thisType = NULL;
		return thisType;
	}
	thisType = malloc(sizeof(type));
	if(specifier->exp_num == 1)// means type: int or float
	{
		expnode *myType = specifier->son_node[0];
		thisType->kind = basic;
		thisType->u.basic = myType->type_vaule;
		return thisType;
	}
	else if(specifier->exp_num == 2)// means it is a struct
	{
		expnode *structSpecType = specifier->son_node[0];
		switch(structSpecType->exp_num)
		{
			case 1:
				{
					expnode *OptTagType = structSpecType->son_node[1];
					expnode *DefListType = structSpecType->son_node[3];
					// add def analyze here
					if(OptTagType->exp_num == 1)
					{
						expnode *myId = OptTagType->son_node[0];
						thisType->kind = structure;
						thisType->u.stru.struct_name = malloc(strlen(myId->id_vaule)+1);
						strcpy(thisType->u.stru.struct_name, myId->id_vaule);
					}
					else if(OptTagType->exp_num == 2)
					{
						thisType->kind = structure;
						thisType->u.stru.struct_name = NULL;
					}
					thisType->u.stru.structure = NULL;
					nowLayerNum++;
					pushLayerStack(nowLayerNum);
					while(DefListType->exp_num == 1)
					{
						expnode *DefType = DefListType->son_node[0];
						DefAnalyzer(DefType, 0, thisType);
						DefListType = DefListType->son_node[1];
					}
					pullLayerStack();
					nowLayerNum--;
					return thisType;
					break;
				}
			case 2:
				{
					expnode *tagType = structSpecType->son_node[1];
					expnode *myId = tagType->son_node[0];
					thisType->kind = structure;
					thisType->u.stru.struct_name = malloc(strlen(myId->id_vaule)+1);
					strcpy(thisType->u.stru.struct_name, myId->id_vaule);
					thisType->u.stru.structure = NULL;
					return thisType;
					break;
				}
			default:
				{
					printf("struct specifier error\n");
					thisType = NULL;
					break;
				}
		}
	}
	else
	{
		printf("specifier error\n");
		thisType = NULL;
	}
	return thisType;
}
// analyze a def node(sub-tree) and return a var list, usage 0 for struct, 1 for CompSt
void  DefAnalyzer(expnode *def, int usage, type *structType)
{
	type *defType = SpecifierAnalyzer(def->son_node[0]);
	// if use a struct type to def, check if the struct have been dec
	if(defType->kind == structure && defType->u.stru.structure == NULL)
	{
		point *isDec = findPoint(defType->u.stru.struct_name, 3, nowLayerNum);
		if(isDec == NULL)
		{
			insertError(17, def->lineno, NULL);
			return;
		}
		if(usage == 0)
		{
			defType = isDec->p.struct_decPoint.struct_decP;
		}
	}
	/*
	 * if the specifier is a struct and have a name
	 * and the usage is for Compst but not struct
	 * then the struct dec should put into the hash table*/
	else if(defType->kind == structure && defType->u.stru.struct_name !=NULL && defType->u.stru.structure != NULL)
	{
		addStructPoint(defType, def->son_node[0]->lineno);
	}
	/* *
	 * add hash table finished
	 *
	 * if the specifier is a struct and have a name
	 * and the usage is for Struct
	 * the struct name can't be same with other def or struct dec
	 * */
	if(usage == 0 && (defType->kind == structure && defType->u.stru.struct_name != NULL))
	{
		var *structTail;
		structTail = structType->u.stru.structure;
		while(structTail != NULL)
		{
			if(strcmp(structTail->name, defType->u.stru.struct_name) == 0)
			{
				insertError(15, def->lineno, NULL);
				return;
			}
			structTail = structTail->t.struct_tail;
		}
	}
	expnode *decList;
	decList = def->son_node[1];
	//int nowDec = 0;
	while(decList->exp_num == 2)
	{
		expnode *dec = decList->son_node[0];
		expnode *varDec = dec->son_node[0];
		var *varList;
		varList = malloc(sizeof(var));
		switch(usage)
		{
			case 0:
				{
					if(dec->exp_num == 1)
					{
						varList = VarDecAnalyzer(defType, varDec);
						varList->t.struct_tail = NULL;
						insertStructTail(varList, structType, varDec->lineno);
					}
					else if(dec->exp_num == 2)
					{
						insertError(15, dec->lineno, NULL);
						varList = VarDecAnalyzer(defType, varDec);
						varList->t.struct_tail = NULL;
						insertStructTail(varList, structType, varDec->lineno);
					}
					// dec->exp_num == 2 have = and exp, do it later
					break;
				}
			case 1:
				{
					if(dec->exp_num == 1)
					{
						varList = VarDecAnalyzer(defType, varDec);
						addVarPoint(varList, varDec->lineno);
						
						/* code for IR*/
						if(varList->var_type->kind == structure || varList->var_type->kind == array)
						{
							mem_dec(varList);						
						}	
						/* code end*/
					}
					else if(dec->exp_num == 2)
					{
						varList = VarDecAnalyzer(defType, varDec);
						addVarPoint(varList, varDec->lineno);

						/* code for IR*/
						if(varList->var_type->kind == structure || varList->var_type->kind == array)
						{
							mem_dec(varList);						
						}	
						/* code end*/

						type *expType = ExpAnalyzer(dec->son_node[2], 0);
						if((expType != NULL && varList != NULL) && isSameType(expType, varList->var_type, nowLayerNum) == 1)
						{
							insertError(5, dec->lineno, NULL);
						}
					}
					
					//dec->exp_num == 2 have = and exp, do it later
					break;
				}
			default:
				{
					printf("wrong usage\n");
					return;
					break;
				}
		}
		decList = decList->son_node[2];
	}
	// for the last dec
	expnode *dec = decList->son_node[0];
	expnode *varDec = dec->son_node[0];
	var *varList;
	varList = malloc(sizeof(var));
	switch(usage)
	{
		case 0:
			{
				if(dec->exp_num == 1)
				{
					varList = VarDecAnalyzer(defType, varDec);
					varList->t.struct_tail = NULL;
					insertStructTail(varList, structType, varDec->lineno);
				}
				else if(dec->exp_num == 2)
				{
					insertError(15, dec->lineno, NULL);
					varList = VarDecAnalyzer(defType, varDec);
					varList->t.struct_tail = NULL;
					insertStructTail(varList, structType, varDec->lineno);
				}
				
				// dec->exp_num == 2 is wrong here, do it later	
				break;
			}
		case 1:
			{
				if(dec->exp_num == 1)
				{
					varList = VarDecAnalyzer(defType, varDec);
					addVarPoint(varList, varDec->lineno);
					
					/* code for IR*/
					if(varList->var_type->kind == structure || varList->var_type->kind == array)
					{
						mem_dec(varList);						
					}	
					/* code end*/	
				}
				else if(dec->exp_num == 2)
				{
					varList = VarDecAnalyzer(defType, varDec);
					addVarPoint(varList, varDec->lineno);

					/* code for IR*/
					if(varList->var_type->kind == structure || varList->var_type->kind == array)
					{
						mem_dec(varList);						
					}	
					/* code end*/

					type *expType = ExpAnalyzer(dec->son_node[2], 0);
					if((expType != NULL && varList != NULL) && isSameType(expType, varList->var_type, nowLayerNum) == 1)
					{
						insertError(5, dec->lineno, NULL);
					}
				}
				
				// same
				break;
			}
		default:
			{
				printf("wrong usage\n");
				return;
				break;
			}
	}
	return;
}
// insert tail to struct, and detect error
void insertStructTail(var *varTail, type *structType, int lineno)
{
	var *structTail;
	structTail = structType->u.stru.structure;
	if(structTail == NULL)
	{
		structType->u.stru.structure = varTail;
		return;
	}
	while(structTail->t.struct_tail != NULL)
	{
		if(structTail->var_type->kind == structure && structTail->var_type->u.stru.struct_name != NULL)
		{
			if(strcmp(structTail->var_type->u.stru.struct_name, varTail->name) == 0)
			{
				insertError(15, lineno, NULL);
				return;
			}
		}
		if(strcmp(structTail->name, varTail->name) == 0)
		{
			insertError(15, lineno, NULL);
			return;
		}
		structTail = structTail->t.struct_tail;
	}
	if(structTail->var_type->kind == structure && structTail->var_type->u.stru.struct_name != NULL)
	{
		if(strcmp(structTail->var_type->u.stru.struct_name, varTail->name) == 0)
		{
			insertError(15, lineno, NULL);
			return;
		}
	}
	if(strcmp(structTail->name, varTail->name) == 0)
	{
		insertError(15, lineno, NULL);
		return;
	}
	structTail->t.struct_tail = varTail;
}
// add a var def to hash table, and detect errors
void addVarPoint(var *varDef, int lineno)
{
	point *varPoint;
	varPoint = malloc(sizeof(point));
	varPoint->point_type = var_def;
	varPoint->p.var_defPoint.var_defP = varDef;
	varPoint->p.var_defPoint.next_varPoint = NULL;
	varPoint->p.var_defPoint.layer = nowLayerNum;
	varPoint->next_point = NULL;
	varPoint->former_point = NULL;
	int errorType = addVarTable(varPoint);
	switch(errorType)
	{
		case -1:
			{
				printf("wrong insert type\n");
				break;
			}
		case 0:
			{
				break;
			}
		case 1:
			{
				insertError(3, lineno, NULL);
				break;
			}
		case 2:
			{
				printf("should have a var def here\n");
				break;
			}
		default:
			{
				printf("insert struct error error\n");
				break;
			}
	}
}
// add a struct dec to hash table, and detect errors
void addStructPoint(type *structDec, int lineno)
{
	point *structPoint;
	structPoint = malloc(sizeof(point));
	structPoint->point_type = struct_dec;
	structPoint->p.struct_decPoint.struct_decP = structDec;
	structPoint->p.struct_decPoint.next_varPoint = NULL;
	structPoint->p.struct_decPoint.layer = nowLayerNum;
	structPoint->next_point = NULL;
	structPoint->former_point = NULL;
	int errorType = addVarTable(structPoint);
	switch(errorType)
	{
		case -1:
			{
				printf("wrong insert type\n");
				break;
			}
		case 0:
			{
				break;
			}
		case 1:
			{
				printf("here should insert a struct, error\n");
				break;
			}
		case 2:
			{
				insertError(16, lineno, NULL);
				break;
			}
		default:
			{
				printf("insert struct error error\n");
				break;
			}
	}
}
// insert a error into a error list
void insertError(int errorType, int lineno, char *func_decName)
{
	errorNode *ERROR;
	ERROR = malloc(sizeof(errorNode));
	ERROR->errorType = errorType;
	ERROR->lineno = lineno;
	if(func_decName == NULL)
	{
		ERROR->func_decName = NULL;
	}
	else
	{
		ERROR->func_decName = malloc(strlen(func_decName) + 1);
		strcpy(ERROR->func_decName, func_decName);
	}
	ERROR->nextErrorNode = NULL;
	errorNode *errorNext;
	errorNext = semErrorList;
	if(errorNext == NULL)
	{
		semErrorList = ERROR;
		return;
	}
	while(errorNext->nextErrorNode != NULL)
	{
		errorNext = errorNext->nextErrorNode;
	}
	errorNext->nextErrorNode = ERROR;
	return;
}
void printSemError()
{
	errorNode *errorNext;
	errorNext = semErrorList;
	while(errorNext != NULL)
	{
	 	if(errorNext->func_decName != NULL)
		{
			point *funcDefPoint = findPoint(errorNext->func_decName, 1, 0);
			if(funcDefPoint != NULL)
			{
				errorNext = errorNext->nextErrorNode;
				continue;
			}
		}
		printf("Error type %d at line %d : ", errorNext->errorType, errorNext->lineno);
		switch(errorNext->errorType)
		{
			case 1: printf("Undefined variable\n");break;
			case 2: printf("Undefined function\n");break;
			case 3: printf("Redefined variable\n");break;
			case 4: printf("Redefined function\n");break;
			case 5: printf("Type mismatched\n");break;
			case 6: printf("The left-hand side of an assignment must be a variable\n");break;
			case 7: printf("Operands type mismatched\n");break;
			case 8: printf("The return type mismatched\n");break;
			case 9: printf("The method is not applicable for the arguments\n");break;
			case 10: printf("Variable must be an array\n");break;
			case 11: printf("Variable must be a function\n");break;
			case 12: printf("Operands type mistaken\n");break;
			case 13: printf("Illegal use of “.”\n");break;
			case 14: printf("Un-existed field\n");break;
			case 15: printf("Redefined field\n");break;
			case 16: printf("Duplicated name\n");break;
			case 17: printf("Undefined struct\n");break;
			case 18: printf("Undefined function\n");break;
			case 19: printf("Inconsistent declaration of function\n");break;
		}
		errorNext = errorNext->nextErrorNode;
	}
	return;
}
void SemanticAnalyze()
{
	if(have_wrong == 1)
	{
		return;
	}
	initTable();
	initStack();
	semErrorList = NULL;
	
	/* code for IR */
	interCodeList = NULL;
	/* code end */

	expnode *NODE = RootNode;
	int tab_num = 0;
	if(NODE->kind == Program)
	{
		//printf("Start Semantic Analyze\n");
		nowLayerNum = 0;
		pushLayerStack(nowLayerNum);
		NODE->search_num = 1;
		NODE = NODE->son_node[0];
		tab_num++;
	}
	else
	{
		printf("analyze start error\n");
		return;
	}
	while(1)
	{
		if(NODE->kind == Program && NODE->node_type == 1)
		{
//			printf("123\n");
			break;
		}
		switch(NODE->node_type)
		{
			case 1:
			{
//				printf("345\n");
				if(NODE->search_num == 0)
				{
		//			PrintKind(tab_num, NODE->kind, NODE->lineno);
//					printf("test\n");
					TypeInsert(NODE);
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
		//		PrintTerm(tab_num, NODE->term);
				NODE = NODE->father_node;
				tab_num--;
				break;
			}
			case 3:
			{
		//		PrintMean(tab_num, NODE);
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
