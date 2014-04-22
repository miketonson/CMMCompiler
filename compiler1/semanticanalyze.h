/*
 * =====================================================================================
 *
 *       Filename:  semanticanalyze.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/21/2014 02:54:56 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef _SEMANTICANALYZE_H_
#define _SEMANTICANALYZE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "semanticlist.h"

extern int nowLayerNum;

typedef struct ErrorNode_ errorNode;// a semantic error node type

struct ErrorNode_
{
	int errorType;
	int lineno;
	errorNode *nextErrorNode;
};

errorNode *semErrorList;// semantic error list

void printTestError();

void TypeInsert(expnode *NODE);

// analyze a ExtDecList node(sub-tree) and insert the points into the hash table
void ExtDecAnalyzer(type *varDefType, expnode *extDecNode);

// analyze a VarDec node(sub-tree) and return a var struct, can do array and def
var * VarDecAnalyzer(type *varDefType, expnode *varDecNode);

// analyze a specifier node(sub-tree) and return a type
type * SpecifierAnalyzer(expnode *specifier);

// analyze a def node(sub-tree) and return a var list, usage 0 for struct, 1 for CompSt
void  DefAnalyzer(expnode *def, int usage, type *structType);

// insert tail to struct, and detect error
void insertStructTail(var *varTail, type *structType, int lineno);

// add a var def to hash table, and detect errors
void addVarPoint(var *varDef, int lineno);

// add a struct dec to hash table, and detect errors
void addStructPoint(type *structDec, int lineno);

// insert a error into a error list
void insertError(int errorType, int lineno);

void printSemError();

void SemanticAnalyze();

#endif
