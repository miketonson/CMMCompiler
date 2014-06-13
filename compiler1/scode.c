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
 *         Author:  Guang-Zhi Tang, 
 *   Organization:  NJU CS
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "scode.h"

int funcParam;
int funcOffset;

void printSCODE(char *file)
{
	InterCode *IRList = interCodeList;
	if(IRList == NULL)
	{
		printf("IR code null\n");
		return;
	}
	FILE *code;
	code = fopen(file, "w");
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
						fprintf(code, "move $fp, $sp\n");
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

					if(printCode->u.assign.right->kind == CONSTo)
					{
						int num = printCode->u.assign.right->u.const_value;
						fprintf(code, "li $t1, %d\n", num);
					}
					else if(printCode->u.assign.right->kind == ADDRo)
					{
						int num = findVarOff(printCode->u.assign.right->u.addr_of);
						fprintf(code, "li $t1, %d\n", num);
					}
					else if(printCode->u.assign.right->kind == STARo)
					{
						int off = findVarOff(printCode->u.assign.right->u.addr_from);
						fprintf(code, "lw $t2, %d($fp)\n", off);
						fprintf(code, "add $t3, $t2, $fp\n");
						fprintf(code, "lw $t1, 0($t3)\n");
					}
					else
					{
						int rightOff = findVarOff(printCode->u.assign.right);
						fprintf(code, "lw $t1, %d($fp)\n", rightOff);
					}

					if(printCode->u.assign.left->kind == STARo)
					{
						int off = findVarOff(printCode->u.assign.left->u.addr_from);
						fprintf(code, "lw $t2, %d($fp)\n", off);
						fprintf(code, "add $t3, $t2, $fp\n");
						fprintf(code, "sw $t1, 0($t3)\n");
					}
					else
					{
						int leftOff = findVarOff(printCode->u.assign.left);
						fprintf(code, "sw $t1, %d($fp)\n", leftOff);
					}
					break;
				}
			case ADDc:
			case SUBc:
			case MULc:
			case DIVc:
				{
					if(printCode->u.binop.result == NULL)
						break;
				//	int resultOff = findVarOff(printCode->u.binop.result);
					if(printCode->u.binop.op1->kind == CONSTo)
					{
						int num = printCode->u.binop.op1->u.const_value;
						fprintf(code, "li $t1, %d\n", num);
						if(printCode->u.binop.op2->kind == ADDRo)
						{
							int num2 = findVarOff(printCode->u.binop.op2->u.addr_of);
							fprintf(code, "li $t2, %d\n", num2);
						}
						else if(printCode->u.binop.op2->kind == STARo)
						{
							int off = findVarOff(printCode->u.binop.op2->u.addr_from);
							fprintf(code, "lw $t4, %d($fp)\n", off);
							fprintf(code, "add $t5, $t4, $fp\n");
							fprintf(code, "lw $t2, 0($t5)\n");
						}
						else
						{
							int op2Off = findVarOff(printCode->u.binop.op2);
							fprintf(code, "lw $t2, %d($fp)\n", op2Off);
						}
					}
					else if(printCode->u.binop.op2->kind == CONSTo)
					{
						int num = printCode->u.binop.op2->u.const_value;
						fprintf(code, "li $t2, %d\n", num);
						if(printCode->u.binop.op1->kind == ADDRo)
						{
							int num2 = findVarOff(printCode->u.binop.op1->u.addr_of);
							fprintf(code, "li $t1, %d\n", num2);
						}
						else if(printCode->u.binop.op1->kind == STARo)
						{
							int off = findVarOff(printCode->u.binop.op1->u.addr_from);
							fprintf(code, "lw $t4, %d($fp)\n", off);
							fprintf(code, "add $t5, $t4, $fp\n");
							fprintf(code, "lw $t1, 0($t5)\n");
						}
						else
						{
							int op1Off = findVarOff(printCode->u.binop.op1);
							fprintf(code, "lw $t1, %d($fp)\n", op1Off);
						}
					}
					else
					{	
						if(printCode->u.binop.op1->kind == ADDRo)
						{
							int num2 = findVarOff(printCode->u.binop.op1->u.addr_of);
							fprintf(code, "li $t1, %d\n", num2);
						}
						else if(printCode->u.binop.op1->kind == STARo)
						{
							int off = findVarOff(printCode->u.binop.op1->u.addr_from);
							fprintf(code, "lw $t4, %d($fp)\n", off);
							fprintf(code, "add $t5, $t4, $fp\n");
							fprintf(code, "lw $t1, 0($t5)\n");
						}
						else
						{
							int op1Off = findVarOff(printCode->u.binop.op1);
							fprintf(code, "lw $t1, %d($fp)\n", op1Off);
						}

						if(printCode->u.binop.op2->kind == ADDRo)
						{
							int num2 = findVarOff(printCode->u.binop.op2->u.addr_of);
							fprintf(code, "li $t2, %d\n", num2);
						}
						else if(printCode->u.binop.op2->kind == STARo)
						{
							int off = findVarOff(printCode->u.binop.op2->u.addr_from);
							fprintf(code, "lw $t4, %d($fp)\n", off);
							fprintf(code, "add $t5, $t4, $fp\n");
							fprintf(code, "lw $t2, 0($t5)\n");
						}
						else
						{
							int op2Off = findVarOff(printCode->u.binop.op2);
							fprintf(code, "lw $t2, %d($fp)\n", op2Off);
						}
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
					if(printCode->u.binop.result->kind == STARo)
					{
						int off = findVarOff(printCode->u.binop.result->u.addr_from);
						fprintf(code, "lw $t4, %d($fp)\n", off);
						fprintf(code, "add $t5, $t4, $fp\n");
						fprintf(code, "sw $t3, 0($t5)\n");
					}
					else
					{
						int resultOff = findVarOff(printCode->u.binop.result);
						fprintf(code, "sw $t3, %d($fp)\n", resultOff);
					}
					break;
				}
			case LABELc:
				{
					char *label = printOperand(printCode->u.op);
					fprintf(code, "%s:\n", label);
					break;
				}
			case GOTOc:
				{
					char *label = printOperand(printCode->u.op);
					fprintf(code, "j %s\n", label);
					break;
				}
			case IF_GOTOc:
				{
					if(printCode->u.if_goto.left->kind == CONSTo)
					{
						int num = printCode->u.if_goto.left->u.const_value;
						fprintf(code, "li $t1, %d\n", num);
					}
					else if(printCode->u.if_goto.left->kind == STARo)
					{
						int off = findVarOff(printCode->u.if_goto.left->u.addr_from);
						fprintf(code, "lw $t3, %d($fp)\n", off);
						fprintf(code, "add $t4, $t3, $fp\n");
						fprintf(code, "lw $t1, 0($t4)\n");
					}
					else
					{
						int leftOff = findVarOff(printCode->u.if_goto.left);
						fprintf(code, "lw $t1, %d($fp)\n", leftOff);
					}

					if(printCode->u.if_goto.right->kind == CONSTo)
					{
						int num = printCode->u.if_goto.right->u.const_value;
						fprintf(code, "li $t2, %d\n", num);
					}
					else if(printCode->u.if_goto.right->kind == STARo)
					{
						int off = findVarOff(printCode->u.if_goto.right->u.addr_from);
						fprintf(code, "lw $t3, %d($fp)\n",off);
						fprintf(code, "add $t4, $t3, $fp\n");
						fprintf(code, "lw $t2, 0($t4)\n");
					}
					else
					{
						int rightOff = findVarOff(printCode->u.if_goto.right);
						fprintf(code, "lw $t2, %d($fp)\n", rightOff);
					}
					char *label = printOperand(printCode->u.if_goto.label);
					switch(printCode->u.if_goto.relop_value)
					{
						case 1:
							{
								fprintf(code, "bgt $t1, $t2, %s\n", label);
								break;
							}
						case 2:
							{
								fprintf(code, "blt $t1, $t2, %s\n", label);
								break;
							}
						case 3:
							{
								fprintf(code, "bge $t1, $t2, %s\n", label);
								break;
							}
						case 4:
							{
								fprintf(code, "ble $t1, $t2, %s\n", label);
								break;
							}
						case 5:
							{
								fprintf(code, "beq $t1, $t2, %s\n", label);
								break;
							}
						case 6:
							{
								fprintf(code, "bne $t1, $t2, %s\n", label);
								break;
							}
						default:
							break;
					}
					break;
				}
			case RETURNc:
				{
					fprintf(code, "addi $sp, $sp, 2048\n");
					if(printCode->u.op->kind == CONSTo)
					{
						int num = printCode->u.op->u.const_value;
						fprintf(code, "li $t1 %d\n", num);
					}
					else if(printCode->u.op->kind == STARo)
					{
						int off = findVarOff(printCode->u.op->u.addr_from);
						fprintf(code, "lw $t2, %d($fp)\n", off);
						fprintf(code, "add $t3, $t2, $fp\n");
						fprintf(code, "lw $t1, 0($t3)\n");
					}
					else
					{
						int opOff = findVarOff(printCode->u.op);
						fprintf(code, "lw $t1 %d($fp)\n", opOff);
					}
					fprintf(code, "move $v0, $t1\n");
					fprintf(code, "jr $ra\n");
					break;
				}
			case READc:
				{
					fprintf(code, "li $v0, 4\nla $a0, _prompt\nsyscall\nli $v0, 5\nsyscall\n");
					fprintf(code, "move $t1, $v0\n");
					if(printCode->u.op->kind == STARo)
					{
						int off = findVarOff(printCode->u.op->u.addr_from);
						fprintf(code, "lw $t2, %d($fp)\n", off);
						fprintf(code, "add $t3, $t2, $fp\n");
						fprintf(code, "sw $t1, 0($t3)\n");
						break;
					}
					int readOff = findVarOff(printCode->u.op);
					fprintf(code, "sw $t1, %d($fp)\n", readOff);
					break;
				}
			case WRITEc:
				{
					if(printCode->u.op->kind == CONSTo)
					{
						int num = printCode->u.op->u.const_value;
						fprintf(code, "li $a0, %d\n", num);
					}
					else if(printCode->u.op->kind == STARo)
					{
						int off = findVarOff(printCode->u.op->u.addr_from);
						fprintf(code, "lw $t1, %d($fp)\n", off);
						fprintf(code, "add $t2, $t1, $fp\n");
						fprintf(code, "lw $a0, 0($t2)\n");
					}
					else
					{
						int writeOff = findVarOff(printCode->u.op);
						fprintf(code, "lw $a0, %d($fp)\n", writeOff);
					}
					fprintf(code, "li $v0, 1\nsyscall\nli $v0, 4\nla $a0, _ret\nsyscall\n");
					break;
				}
			case ARGc:
				{
					if(printCode->u.op->kind == CONSTo)
					{
						int num = printCode->u.op->u.const_value;
						fprintf(code, "li $t1, %d\n", num);
					}
					else
					{
						int argOff = findVarOff(printCode->u.op);
						fprintf(code, "lw $t1, %d($fp)\n", argOff);
					}
					funcOffset -= 4;
					fprintf(code, "sw $t1, %d($fp)\n", funcOffset);
					break;
				}
			case CALL_FUNCc:
				{
					funcOffset -= 4;
					fprintf(code, "sw $fp, %d($fp)\n", funcOffset);
					funcOffset -= 4;
					fprintf(code, "sw $ra, %d($fp)\n", funcOffset);
					fprintf(code, "addi $fp, $fp, %d\n", funcOffset);
					fprintf(code, "jal %s\n", printCode->u.call_func.func->u.func_name);
					fprintf(code, "lw $ra, 0($fp)\nlw $fp, 4($fp)\n");
					fprintf(code, "move $t1, $v0\n");

					if(printCode->u.call_func.var->kind == STARo)
					{
						int off = findVarOff(printCode->u.call_func.var->u.addr_from);
						fprintf(code, "lw $t2, %d($fp)\n", off);
						fprintf(code, "add $t3, $t2, $fp\n");
						fprintf(code, "sw $t1, 0($t3)\n");
					}
					int varOff = findVarOff(printCode->u.call_func.var);
					fprintf(code, "sw $t1, %d($fp)\n", varOff);
					break;
				}
			case PARAMc:
				{
					fprintf(code, "lw $t1, %d($fp)\n", funcParam);
					funcParam += 4;
					int opOff = findVarOff(printCode->u.op);
					fprintf(code, "sw $t1, %d($fp)\n", opOff);
					break;
				}
			case DECc:
				{
					int size = printCode->u.dec.size;
					funcOffset -= size;
					addrList *array;
					array = malloc(sizeof(addrList));
					array->var = printCode->u.dec.var;
					array->offset = funcOffset;
					array->nextVar = NULL;
					if(nowFunc->varList == NULL)
					{
						nowFunc->varList = array;
						break;
					}
					addrList *tmpVar = nowFunc->varList;
					while(tmpVar->nextVar != NULL)
					{
						tmpVar = tmpVar->nextVar;
					}
					tmpVar->nextVar = array;
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
		case TEMPo:
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
						if(nowVar->kind == TEMPo && nowVar->u.temp_no == var->u.temp_no)
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
				printf("wrong type!%d\n", var->kind);
				break;
			}
	}
	return returnOff;
}
