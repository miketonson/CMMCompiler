/*
 * =====================================================================================
 *
 *       Filename:  IR.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/15/2014 06:50:16 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Guang-Zhi Tang, 
 *   Organization:  NJU CS
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "IR.h"

void insertCodeList(InterCode *interCode)
{
	if(interCodeList == NULL)
	{
		interCodeList = interCode;
	}
	else
	{
		InterCode *exCodes;
		exCodes = interCodeList;
		while(exCodes->next != NULL)
		{
			exCodes = exCodes->next;
		}
		exCodes->next = interCode;
		interCode->prev = exCodes;
	}
	return;
}

void mem_dec(var *varPoint)
{
	InterCode *decCode;
	decCode = malloc(sizeof(InterCode));
	decCode->prev = NULL;
	decCode->next = NULL;

	decCode->kind = DECc;
	decCode->u.dec.var = malloc(sizeof(Operand));
	decCode->u.dec.var->kind = VARo;
	decCode->u.dec.var->u.var_name = malloc(strlen(varPoint->name) + 1);
	strcpy(decCode->u.dec.var->u.var_name, varPoint->name);

	int size_all;
	size_all = dec_sizeCal(varPoint->var_type);
	decCode->u.dec.size = size_all;

	insertCodeList(decCode);
	return;
}

int dec_sizeCal(type *varType)
{
	int size = 0;
	switch(varType->kind)
	{
		case basic:
			{
				size = 4;
				break;
			}
		case array:
			{
				size = dec_sizeCal(varType->u.array.elem);
				size = size * varType->u.array.size;
				break;
			}
		case structure:
			{
				if(varType->u.stru.struct_name != NULL && varType->u.stru.structure == NULL)
				{
					point *structPoint;
					structPoint = findPoint(varType->u.stru.struct_name, 3, nowLayerNum);
					size = dec_sizeCal(structPoint->p.struct_decPoint.struct_decP);
				}
				else
				{
					var *structTail = varType->u.stru.structure;
					while(structTail != NULL)
					{
						size += dec_sizeCal(structTail->var_type);
						structTail = structTail->t.struct_tail;
					}
				}
				break;
			}
		default:
			{
				printf("ERROR: wrong type kind\n");
				break;
			}
	}
	return size;
}

void printCodeList()
{
	if(interCodeList == NULL)
	{
		return;
	}
	InterCode *printCode;
	printCode = interCodeList;
	while(printCode != NULL)
	{
		switch(printCode->kind)
		{
			case DECc:
				{
					printf("DEC %s [%d]\n", printCode->u.dec.var->u.var_name, printCode->u.dec.size);
					break;
				}
			default:
				{
					printf("ERROR: wrong code node kind\n");
					break;
				}
		}
		printCode = printCode->next;
	}
}
