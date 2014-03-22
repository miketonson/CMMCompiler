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
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "tree.h"
expnode InsertNode(KIND kind,int lineno, int exp_num, int node_num, ...)
{
	va_list ap;
	expnode* EXP;
	EXP = malloc(sizeof(expnode)+node_num*sizeof(expnode));
	va_start (ap,node_num);
	for(int i=0; i<node_num; i++)
	{
		EXP->son_node[i] = va_arg(ap,expnode*);
	}
	EXP->lineno = lineno;
	EXP->exp_num = exp_num;
	EXP->node_num = node_num;
	EXP->kind = kind;
	EXP->mean = noMean;
	EXP->terminal = noTerm;
	return EXP;
}

expnode TermNode(TERM terminal)
{
	expnode* EXP;
	EXP = malloc(sizeof(expnode));
	EXP->terminal = terminal;
	EXP->kind = noExp;
	EXP->mean = noMean;
	return EXP;
}
