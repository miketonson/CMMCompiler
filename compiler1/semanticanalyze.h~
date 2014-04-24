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
	char *func_decName;
	errorNode *nextErrorNode;
};

errorNode *semErrorList;// semantic error list

void printTestError();

void TypeInsert(expnode *NODE);

// analyze a DefList Node(sub-tree) and insert var def into hash table
void DefListAnalyzer(expnode *defListNode);

// analyze a StmtList Node(sub-tree) and check semantic errors
void StmtListAnalyzer(expnode *stmtListNode);

// analyze a Stmt Node(sub-tree) and check semantic errors
void StmtAnalyzer(expnode *stmtNode);

// analyze a Exp Node(sub-tree) and return something by the etype requested
// etype:
// 0 for finding a real type, from + - * / , or int float struct array
// 1 for analyze =
// 2 for analyze booleans, from AND OR RELOP NOT
// 3 for find if it is a left type
type * ExpAnalyzer(expnode *expNode, int etype);

// analyze a FunDec Node(sub-tree) and insert func_def and func_dec points into hash table
// ftype 0 for dec, 1 for def
void FunDecAnalyzer(type *funcType, expnode *funDecNode, int ftype);

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
void insertError(int errorType, int lineno, char *func_decName);

void printSemError();

void SemanticAnalyze();

#endif
