/*
 * =====================================================================================
 *
 *       Filename:  scode.h
 *
 *    Description: final step for the compiler 
 *
 *        Version:  1.0
 *        Created:  06/11/2014 03:07:23 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Guang-Zhi Tang, 
 *   Organization:  NJU CS
 *
 * =====================================================================================
 */
#ifndef _SCODE_H_
#define _SCODE_H_

#include "IR.h"

typedef struct ADDRLIST_ addrList;
typedef struct FUNCLIST_ funcList;

struct ADDRLIST_
{
	Operand *var;
	int offset;
	addrList *nextVar;
};

struct FUNCLIST_
{
	char *funcName;
	addrList *varList;
	funcList *nextFunc;
};

funcList *function;
funcList *nowFunc;

void insertFuncList(char *name);
//void insertVarList(Operand *var, int offset);
int findVarOff(Operand *var);

void printSCODE(char *file);

#endif
