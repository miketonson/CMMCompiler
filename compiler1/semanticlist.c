/*
 * =====================================================================================
 *
 *       Filename:  semanticlist.c
 *
 *    Description: type structure defines and hash table defines, hash table oprations for sematic analyze 
 *
 *        Version:  1.0
 *        Created:  04/17/2014 07:40:23 PM
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
}
struct Type_
{
	enum {basic, array, structure} kind;
	union
	{
		int basic;
		struct
		{
			type *elem;// next layer of the array
			int size;// this layer size
		} array;
		var *structure;
	} u;
};
struct FuncDef_
{
	enum {int_num, float_num, struct_num} returnType;
	char *name;
	var *funcVarDef;
};
struct TablePoint
{
	enum {function, variable} point_type;
	union
	{
		funcDef *func_point;// this point have function define
		struct // this point have a variable define
		{
			var *var_def;
			point *next_varPoint;// for different layer var del
			int layer;
		} var_point;
	} p;
	point *next_point;// it is a stack connect the table
	point *fomer_point;// its former point in the stack
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
unsigned int hash_pjw(char *name)
{
	unsigned int val = 0, i;
	for(; *name; ++name)
	{
		val = (val<<2) + *name;
		if(i = val & ~0x3fff)
			val = (val^(i>>12)) & 0x3fff;
	}
	return val;
}
// init hash table
void initTable()
{
	int i;
	for(i=0; i<table_size; i++)
		hashTable[i] = NULL;
}
// init layer stack
void initStack()
{
	nowLayer = NULL;
}
// insert layer stack point
void pushLayerStack(int layer, point *startPoint)
{
	varStack *thisLayer;
	thisLayer = malloc(sizeof(varStack));
	thisLayer->upperLayer = nowLayer;
	thisLayer->layerPoint = startPoint;
	thisLayer->layer = layer;
	nowLayer = thisLayer;
}
// add layer var to the layer point
void addPointLayer(point *addPoint)
{
	point *tempPoint;
	tempPoint = nowLayer->layerPoint;
	while(tempPoint->p.var_point.next_varPoint != NULL)
	{
		tempPoint = tempPoint->p.var_point.next_varPoint;
	}
	tempPoint->p.var_point.next_varPoint = addPoint;

}
// add function point to hash table
int addFuncTable(point *funcPoint)
{
	unsigned int value = hash_pjw(funcPoint->p.func_point->name);
	if(hashTable[value] == NULL)
	{
		hashTable[value] = funcPoint;
		return 1; // return means success
	}
	point *nextPoint;
	nextPoint = hashTable[value];
	do
	{
		if(nextPoint->point_type == function)
		{
			if(strcmp(funcPoint->p.func_point->name, nextPoint->p.func_point->name) == 0)
				return 0;// multi def
		}
		nextPoint = nextPoint->next_point;
	}while(nextPoint != NULL);
	hashTable[value]->former_point = funcPoint;
	funcPoint->next_point = hashTable[value];
	hashTable[value] = funcPoint;
	return 1; // return means success
}
// add variable point to hash table
int addVarTable(point *varPoint)
{
	unsigned int value = hash_pjw(varPoint->p.var_point.var_def->name);
	if(hashTable[value] == NULL)
	{
		hashTable[value] = varPoint;
		addPointLayer(varPoint);
		return 1; // return means success
	}
	point *nextPoint;
	nextPoint = hashTable[value];
	while(nextPoint != NULL)
	{
		if(nextPoint->point_type == variable)
		{
			if(nextPoint->p.var_point.layer < varPoint->p.var_point.layer)
				break;
			if(strcmp(varPoint->p.var_point.var_def->name, nextPoint->p.var_point.var_def->name) == 0 && varPoint->p.var_point.layer == nextPoint->p.var_point.layer)
				return 0; // multi def
		}
		nextPoint = nextPoint->next_point;
	}
	hashTalbe[value]->former_point = varPoint;
	varPoint->next_point = hashTable[value];
	hashTable[value] = varPoint;
	addPointLayer(varPoint);
	return 1; // return means success
}
// delete a layer from the layer stack and hash table
void pullLayerStack()
{
	// pull from layer stack
	varStack *firLayer;
	firLayer = nowLayer;
	nowLayer = firLayer->upperLayer;
	// delete from hash table
	point *tempPoint;
	tempPoint = firLayer->layerPoint;
	while(tempPoint != NULL)
	{
		if(tempPoint->next_point == NULL && tempPoint->former_point == NULL)
		{
			unsigned int num = hash_pjw(tempPoint->p.var_point.var_def->name);
			hashTable[num] = NULL;
			point *tempNew;
			tempNew = tempPoint->p.var_point.next_varPoint;
			free(tempPoint);
			tempPoint = tempNew;
		}
		else if(tempPoint->next_point == NULL && tempPoint->former_point != NULL)
		{
			point *tempNew;
			point *tempNextNew;
			tempNew = tempPoint->former_point;
			tempNew->next_point = NULL;
			tempNextNew = tempPoint->p.var_point.next_varPoint;
			free(tempPoint);
			tempPoint = tempNextNew;
		}
		else if(tempPoint->next_point != NULL && tempPoint->former_point == NULL)
		{
			unsigned int num = hash_pjw(tempPoint->p.var_point.var_def->name);
			hashTable[num] = tempPoint->next_point;
			point *tempNew;
			tempNew = tempPoint->p.var_point.next_varPoint;
			free(tempPoint);
			tempPoint = tempNew;
		}
		else
		{
			point *formerPoint;
			point *nextPoint;
			point *tempNew;
			formerPoint = tempPoint->former_point;
			nextPoint = tempPoint->next_point;
			formerPoint->next_point = nextPoint;
			nextPoint->former_point = formerPoint;
			tempNew = tempPoint->p.var_point.next_varPoint;
			free(tempPoint);
			tempPoint = tempNew;
		}
	}
	free(firLayer);
}
// find point in hash table, type 0 for var, 1 for func
point * findPoint(char *name, int type, int layer)
{
	point *returnPoint;
	unsigned int num = hash_pjw(name);
	returnPoint = hashTable[num];
	while(returnPoint != NULL)
	{
		if(type == 0)
		{
			if(returnPoint->point_type == variable)
			{
				if(stdcmp(returnPoint->p.var_point.var_def->name, name) == 0 && returnPoint->p.var_point.layer <= layer)
					return returnPoint;
			}
		}
		else
		{
			if(returnPoint->point_type == function)
			{
				if(stdcmp(returnPoint->p.func_point->name, name) == 0)
				{
					return returnPoint;
				}
			}
		}
		returnPoint = returnPoint->next_point;
	}
	return returnPoint;
}
