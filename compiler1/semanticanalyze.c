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

void TypeInsert(expnode *NODE)
{
	printf("insert:%d\n", NODE->kind);
	switch(NODE->kind)
	{
		case Def:
			{
				printf("def TEst\n");
				expnode *specifier = NODE->son_node[0];
				expnode *declist = NODE->son_node[1];
				expnode *dec = declist->son_node[0];
				expnode *vardec = dec->son_node[0];
				expnode *mytype = specifier->son_node[0];
				expnode *myid = vardec->son_node[0];
				type *thistype;
				thistype = malloc(sizeof(type));
				thistype->kind = basic;
				thistype->u.basic = mytype->type_vaule;
				var *thisvar;
				thisvar = malloc(sizeof(var));
				thisvar->name = malloc(strlen(myid->id_vaule)+1);
				strcpy(thisvar->name, myid->id_vaule);
				thisvar->var_type = thistype;
				point *thispoint;
				thispoint = malloc(sizeof(point));
				thispoint->point_type = variable;
				thispoint->p.var_point.var_def = thisvar;
				thispoint->p.var_point.next_varPoint = NULL;
				thispoint->p.var_point.layer = 1;
				thispoint->next_point = NULL;
				thispoint->former_point = NULL;
				pushLayerStack(1, thispoint);
				int suc;
				suc = addVarTable(thispoint);
				printf("%d\n", suc);
				// print it out for test
				point *test;
				test = findPoint("a", 0, 1);
				printf("name:%s, type:%d\n", test->p.var_point.var_def->name, test->p.var_point.var_def->var_type->u.basic);
				break;
			}
		default:
			{
				printf("don't mind\n");
				break;
			}
	}
}
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
		
	}
}
void SemanticAnalyze()
{
	if(have_wrong == 1)
	{
		return;
	}
	initTable();
	initStack();
	expnode *NODE = RootNode;
	int tab_num = 0;
	if(NODE->kind == Program)
	{
		printf("Start Semantic Analyze\n");
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
					printf("test\n");
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
