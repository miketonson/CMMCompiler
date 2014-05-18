/*
 * =====================================================================================
 *
 *       Filename:  semanticlist.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/19/2014 01:06:14 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef _SEMANTICLIST_H_
#define _SEMANTICLIST_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define table_size 16383

typedef struct Var_ var;//define var
typedef struct Type_ type;//type defines, including int float struct array
typedef struct FuncDef_ funcDef;//function define
typedef struct TablePoint point;// point in the hash table
typedef struct LayerVarStack varStack;// a stack for layer variable del
struct Var_
{
	char *name;
	type *var_type;
	union
	{
		var *struct_tail;// define the struct vars
		var *funcDef_tail;// define the function define vars
	} t;
	int isInFuncDef;//0 for no, 1 for yes
};
struct Type_
{
	enum {basic, array, structure} kind;
	union
	{
		int basic;// 0 for int, other for float
		struct
		{
			type *elem;// next layer of the array
			int size;// this layer size
		} array;
		struct
		{
			char *struct_name;//struct type name, NULL means have no name
			var *structure;//area in the struct, NULL means it for a var def, not a struct dec
		} stru;			
	} u;
};
struct FuncDef_
{
	type *returnType;
	char *name;
	var *funcVarDef;
};
struct TablePoint
{
	enum {func_dec,func_def, var_def, struct_dec} point_type;
	union
	{
		funcDef *func_decPoint;// this point have function declaration
		funcDef *func_defPoint;// this point have function define
		struct // this point have a variable define
		{
			var *var_defP;
			point *next_varPoint;// for different layer var del
			int layer;
		} var_defPoint;
		struct // this point have a struct declariation
		{
			type *struct_decP;
			point *next_varPoint;
			int layer;		
		} struct_decPoint;
	} p;
	point *next_point;// it is a stack connect the table
	point *former_point;// its former point in the stack
};
struct LayerVarStack
{
	varStack *upperLayer;
	point *layerPoint;
	int layer;
};
/*
 * basic define ended
 * begin to define the hash table and layer stack
 * */
point *hashTable[table_size];
varStack *nowLayer;
/* 
 * define hash table and the layer stack
 * begin the function for table insertion and find
 * and the function for layer operation
 * */

// hash function
unsigned int hash_pjw(char *name);

// init hash table
void initTable();

// init layer stack
void initStack();

// insert layer stack point
void pushLayerStack(int layer);

// add layer var to the layer point
void addPointLayer(point *addPoint);

// add function point to hash table
int addFuncTable(point *funcPoint);

// if it define a same function
int isSameFunc(point *firPoint, point *secPoint);

// if it is the same type
int isSameType(type *firType, type *secType, int nowLayerNum);

// add variable point to hash table
int addVarTable(point *varPoint);

// delete a layer from the layer stack and hash table
void pullLayerStack();

// find point in hash table, type 0 for fun_dec, 1 for fun_def, 2 for var_def, 3 for struct_dec
point * findPoint(char *name, int type, int layer);

#endif
