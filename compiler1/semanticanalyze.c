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

int nowLayerNum = 0;

// only for test
void printTestError()
{
	printSemError();
// point 1 array
	point *point1 = findPoint("a", 2, 0);
	printf("name: %s, type: %d, inner_type: %d\n", point1->p.var_defPoint.var_defP->name, point1->point_type, point1->p.var_defPoint.var_defP->var_type->kind);
	type *thisType = point1->p.var_defPoint.var_defP->var_type;
	while(thisType->kind == array)
	{
		printf("array: %d ", thisType->u.array.size);
		thisType = thisType->u.array.elem;
	}
	printf("array_type: %d\n", thisType->kind);
// point 2 int
	point *point2 = findPoint("b", 2, 0);
	printf("name: %s, type: %d, inner_type: %d\n", point2->p.var_defPoint.var_defP->name, point2->point_type, point2->p.var_defPoint.var_defP->var_type->kind);
// point 3 struct
	point *point3 = findPoint("test", 3, 0);
	printf("name: %s, type: %d\n", point3->p.struct_decPoint.struct_decP->u.stru.struct_name, point3->point_type);
	var *thisVar = point3->p.struct_decPoint.struct_decP->u.stru.structure;
	while(thisVar != NULL)
	{
		printf("   name: %s, type : %d\n", thisVar->name, thisVar->var_type->kind);
		if(thisVar->var_type->kind == array)
		{
			type *atype = thisVar->var_type;
			while(atype->kind == array)
			{
				printf("   array: %d ", atype->u.array.size);
				atype = atype->u.array.elem;
			}
			printf("array_type: %d\n", atype->kind);
		}
		thisVar = thisVar->t.struct_tail;
	}
}

// first time for hash table insert
void TypeInsert(expnode *NODE)
{
	printf("insert:%d\n", NODE->kind);
	switch(NODE->kind)
	{
		case ExtDef:
			{
				if(NODE->exp_num == 1)
				{
					type *varDefType = SpecifierAnalyzer(NODE->son_node[0]);
					ExtDecAnalyzer(varDefType, NODE->son_node[1]);
					NODE->search_num = NODE->node_sum;
					NODE = NODE->father_node;
				}
				if(NODE->exp_num == 2)
				{
					type *structDecType = SpecifierAnalyzer(NODE->son_node[0]);
					addStructPoint(structDecType, NODE->lineno);
					NODE->search_num = NODE->node_sum;
					NODE = NODE->father_node;
				}
				break;
			}
		default:
			{
	//			printf("don't mind\n");
				break;
			}
	}
}

// analyze a ExtDecList node(sub-tree) and insert the points into the hash table
void ExtDecAnalyzer(type *varDefType, expnode *extDecNode)
{
	while(extDecNode->exp_num == 2)
	{
		addVarPoint(VarDecAnalyzer(varDefType, extDecNode->son_node[0]), extDecNode->lineno);
		extDecNode = extDecNode->son_node[2];
	}
	addVarPoint(VarDecAnalyzer(varDefType, extDecNode->son_node[0]), extDecNode->lineno);
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
//	printf("here 2\n");
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
//		printf("here 3\n");
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
			//		printf("%s\n", thisType->u.stru.struct_name);
					while(DefListType->exp_num == 1)
					{
						expnode *DefType = DefListType->son_node[0];
						DefAnalyzer(DefType, 0, thisType);
						DefListType = DefListType->son_node[1];
					}
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
			insertError(17, def->lineno);
			return;
		}
	}
	/*
	 * if the specifier is a struct and have a name
	 * and the usage is for Compst but not struct
	 * then the struct dec should put into the hash table*/
	if(usage == 1 && (defType->kind == structure && defType->u.stru.struct_name !=NULL && defType->u.stru.structure != NULL))
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
		while(structTail != NULL && structTail->t.struct_tail != NULL)
		{
			if(strcmp(structTail->name, defType->u.stru.struct_name) == 0)
			{
				insertError(15, def->lineno);
				return;
			}
			structTail = structTail->t.struct_tail;
		}
		if(strcmp(structTail->name, defType->u.stru.struct_name) == 0)
		{
			insertError(15, def->lineno);
			return;
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
					varList = VarDecAnalyzer(defType, varDec);
					varList->t.struct_tail = NULL;
					insertStructTail(varList, structType, varDec->lineno);
					
					// dec->exp_num == 2 have = and exp, do it later
					break;
				}
			case 1:
				{
					varList = VarDecAnalyzer(defType, varDec);
					addVarPoint(varList, varDec->lineno);
					
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
				varList = VarDecAnalyzer(defType, varDec);
				varList->t.struct_tail = NULL;
				insertStructTail(varList, structType, varDec->lineno);
				
				// dec->exp_num == 2 is wrong here, do it later	
				break;
			}
		case 1:
			{
				varList = VarDecAnalyzer(defType, varDec);
				addVarPoint(varList, varDec->lineno);
				
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
				insertError(15, lineno);
				return;
			}
		}
		if(strcmp(structTail->name, varTail->name) == 0)
		{
			insertError(15, lineno);
			return;
		}
		structTail = structTail->t.struct_tail;
	}
	if(structTail->var_type->kind == structure && structTail->var_type->u.stru.struct_name != NULL)
	{
		if(strcmp(structTail->var_type->u.stru.struct_name, varTail->name) == 0)
		{
			insertError(15, lineno);
			return;
		}
	}
	if(strcmp(structTail->name, varTail->name) == 0)
	{
		insertError(15, lineno);
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
				insertError(3, lineno);
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
				insertError(16, lineno);
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
void insertError(int errorType, int lineno)
{
	errorNode *ERROR;
	ERROR = malloc(sizeof(errorNode));
	ERROR->errorType = errorType;
	ERROR->lineno = lineno;
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
		printf("Error type %d at line %d\n", errorNext->errorType, errorNext->lineno);
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
	expnode *NODE = RootNode;
	int tab_num = 0;
	if(NODE->kind == Program)
	{
		printf("Start Semantic Analyze\n");
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
