/*
 * =====================================================================================
 *
 *       Filename:  scode.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/11/2014 03:08:07 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "scode.h"

int funcParam;
int funcOffset;

void printSCODE()
{
	InterCode *IRList = interCodeList;
	if(IRList == NULL)
	{
		printf("IR code null\n");
		return;
	}
	FILE *code;
	code = fopen("code.s", "w");
	fprintf(code, ".data\n_prompt: .asciiz \"Enter an integer:\"\n_ret: .asciiz \"\\n\"\n.globl main\n.text\n");
	
	InterCode *printCode;
	printCode = IRList;

	function = NULL;
	nowFunc = function;

	while(printCode != NULL)
	{
		switch(printCode->kind)
		{
			case FUNCc:
				{
					insertFuncList(printCode->u.op->u.func_name);
					fprintf(code, "%s:\n", nowFunc->funcName);
					if(strcmp(nowFunc->funcName, "main") == 0)
					{
						fprintf(code, "move $fp $sp\n");
					}
					fprintf(code, "addi $sp, $sp, -2048\n");
					funcOffset = 0;
					funcParam = 8;
					break;
				}
			case ASSIGNc:
				{
					if(printCode->u.assign.left == NULL)
						break;

					int leftOff = findVarOff(printCode->u.assign.left);
					if(printCode->u.assign.right->kind == CONSTo)
					{
						int num = printCode->u.assign.right->u.const_value;
						fprintf(code, "li $t1 %d\n", num);
					}
					else
					{
						int rightOff = findVarOff(printCode->u.assign.right);
						fprintf(code, "lw $t1 %d($fp)\n", rightOff);
					}
					fprintf(code, "sw $t1 %d($fp)\n", leftOff);
					break;
				}
			case ADDc:
			case SUBc:
			case MULc:
			case DIVc:
				{
					if(printCode->u.binop.result == NULL)
						break;
					int resultOff = findVarOff(printCode->u.binop.result);
					if(printCode->u.binop.op1->kind == CONSTo)
					{
						int num = printCode->u.binop.op1->u.const_value;
						fprintf(code, "li $t1 %d\n", num);
						int op2Off = findVarOff(printCode->u.binop.op2);
						fprintf(code, "lw $t2 %d($fp)\n", op2Off);
					}
					else if(printCode->u.binop.op2->kind == CONSTo)
					{
						int num = printCode->u.binop.op2->u.const_value;
						fprintf(code, "li $t2 %d\n", num);
						int op1Off = findVarOff(printCode->u.binop.op1);
						fprintf(code, "lw $t1 %d($fp)\n", op1Off);
					}
					else
					{
						int op1Off = findVarOff(printCode->u.binop.op1);
						int op2Off = findVarOff(printCode->u.binop.op2);
						fprintf(code, "lw $t1 %d($fp)\n", op1Off);
						fprintf(code, "lw $t2 %d($fp)\n", op2Off);
					}
					switch(printCode->kind)
					{
						case ADDc:
							{
								fprintf(code, "add $t3, $t1, $t2\n");
								break;
							}
						case SUBc:
							{
								fprintf(code, "sub $t3, $t1, $t2\n");
								break;
							}
						case MULc:
							{
								fprintf(code, "mul $t3, $t1, $t2\n");
								break;
							}
						case DIVc:
							{
								fprintf(code, "div $t1, $t2\n");
								fprintf(code, "mflo $t3\n");
								break;
							}
						default:
							break;
					}
					fprintf(code, "sw $t3 %d($fp)\n", resultOff);
					break;
				}
			default:
				{
					break;
				}
		}
		printCode = printCode->next;
	}
}
void insertFuncList(char *name)
{
	funcList *func;
	func = malloc(sizeof(funcList));
	func->funcName = malloc(strlen(name) + 1);
	strcpy(func->funcName, name);
	func->varList = NULL;
	func->nextFunc = NULL;

	if(function == NULL)
	{
		function = func;
		nowFunc = function;
	}
	else
	{
		funcList *tmpFunc;
		tmpFunc = function;
		while(tmpFunc->nextFunc != NULL)
		{
			tmpFunc = tmpFunc->nextFunc;
		}
		tmpFunc->nextFunc = func;
		nowFunc = func;
	}
	return;
}
int findVarOff(Operand *var)
{
	int returnOff;
	switch(var->kind)
	{
		case VARo:
			{
				if(nowFunc->varList == NULL)
				{
					funcOffset -= 4;
					returnOff = funcOffset;
					addrList *varList;
					varList = malloc(sizeof(addrList));
					varList->var = var;
					varList->offset = returnOff;
					varList->nextVar = NULL;
					nowFunc->varList = varList;
					break;
				}
				else
				{
					addrList *tmpVar;
					addrList *conVar;
					tmpVar = nowFunc->varList;
					conVar = tmpVar;
					while(tmpVar != NULL)
					{
						Operand *nowVar;
						nowVar = tmpVar->var;
						if(nowVar->kind == VARo && strcmp(nowVar->u.var_name, var->u.var_name) == 0)
						{
							returnOff = tmpVar->offset;
							break;
						}
						conVar = tmpVar;
						tmpVar = tmpVar->nextVar;
					}
					if(tmpVar == NULL)
					{
						funcOffset -= 4;			
						returnOff = funcOffset;
						addrList *varList;
						varList = malloc(sizeof(addrList));
						varList->var = var;
						varList->offset = returnOff;
						varList->nextVar = NULL;
						conVar->nextVar = varList;
					}
					break;
				}
			}
		default:
			{
				break;
			}
	}
	return returnOff;
}
