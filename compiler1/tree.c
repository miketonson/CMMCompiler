/*
 * =====================================================================================
 *
 *       Filename:  tree.c
 *
 *    Description:  method for tree insert
 *
 *        Version:  1.0
 *        Created:  03/22/2014 09:32:19 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Guang-Zhi Tang, 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "tree.h"
#define MEANNODE expnode *EXP;\
		EXP = malloc(sizeof(expnode));\
		EXP->node_type = 3;\
		EXP->lineno = lineno;\
		EXP->mean = mean

expnode * InsertNode(KIND kind,int lineno, int exp_num, int node_num, ...)
{
	va_list ap;
	expnode *EXP;
	EXP = malloc(sizeof(expnode));
	va_start (ap,node_num);
	int i;
	for(i=0; i<node_num; i++)
	{
		EXP->son_node[i] = va_arg(ap,expnode *);
		EXP->son_node[i]->father_node = EXP;
		EXP->son_node[i]->search_num = 0;
	}
	EXP->lineno = lineno;
	EXP->exp_num = exp_num;
	EXP->node_sum = node_num;
	EXP->kind = kind;
	EXP->node_type = 1;
	return EXP;
}

expnode * TermNode(TERM term, int lineno)
{
	expnode *EXP;
	EXP = malloc(sizeof(expnode));
	EXP->term = term;
	EXP->lineno = lineno;
	EXP->node_type = 2;
	return EXP;
}
expnode * IntNode(MEAN mean, int lineno, int int_vaule)
{
	MEANNODE;
	EXP->int_vaule = int_vaule;
	return EXP;
}
expnode * FloatNode(MEAN mean, int lineno, float float_vaule)
{
	MEANNODE;
	EXP->float_vaule = float_vaule;
	return EXP;
}
expnode * TypeNode(MEAN mean, int lineno, int type_vaule)
{
	MEANNODE;
	EXP->type_vaule = type_vaule;
	return EXP;
}
expnode * IdNode(MEAN mean, int lineno, char* id_vaule)
{
	MEANNODE;
	EXP->id_vaule = id_vaule;
	return EXP;
}
expnode * RelopNode(MEAN mean, int lineno, char* relop_char)
{
	MEANNODE;
	if(strcmp(relop_char,">") == 0)
	{
		EXP->relop_vaule = 1;
	}
	else if(strcmp(relop_char, "<") == 0)
	{
		EXP->relop_vaule = 2;
	}
	else if(strcmp(relop_char, ">=") == 0)
	{
		EXP->relop_vaule = 3;
	}
	else if(strcmp(relop_char, "<=") == 0)
	{
		EXP->relop_vaule = 4;
	}
	else if(strcmp(relop_char, "==") == 0)
	{
		EXP->relop_vaule = 5;
	}
	else
	{
		EXP->relop_vaule = 6;
	}
	return EXP;
}
