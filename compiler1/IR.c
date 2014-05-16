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

int nowTemp = 1;

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

Operand * new_temp()
{
	Operand *temp;
	temp = malloc(sizeof(Operand));
	temp->kind = TEMPo;
	temp->temp_no = nowTemp;

	nowTemp++;

	return temp;
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

void translate_EXP(expnode *EXP, Operand *place)
{
	switch(EXP->exp_num)
	{
		case 17: /* for INT */
			{
				Operand *con;
				con = malloc(sizeof(Operand));
				con->kind = CONSTo;
				con->u.const_value = EXP->int_vaule;

				InterCode *conCode;
				conCode = malloc(sizeof(InterCode));
				conCode->kind = ASSIGNc;
				conCode->u.assign.left = place;
				conCode->u.assign.right = con;

				insertCodeList(conCode);
				break;
			}
		case 16: /* for ID */
			{
				Operand *var;
				var = malloc(sizeof(Operand));
				var->kind = VARo;
				strcpy(var->u.var_name, EXP->id_vaule);

				InterCode *varCode;
				varCode = malloc(sizeof(InterCode));
				varCode->kind = ASSIGNc;
				varCode->u.assign.left = place;
				varCode->u.assign.right = var;

				insertCodeList(varCode);
				break;
			}
		case 1: /* for ASSIGN */
			{
				expnode *left = EXP->son_node[0];
				switch(left->exp_num)
				{
					case 16: /* for ID */
						{
							Operand *t1;
							t1 = new_temp();

							Operand *var;
							var = malloc(sizeof(Operand));
							var->kind = VARo;
							strcpy(var->u.var_name, left->id_vaule);

							tanslate_EXP(EXP->son_node[2], t1);

							InterCode *code1;
							InterCode *code2;
							code1 = malloc(sizeof(InterCode));
							code2 = malloc(sizeof(InterCode));
							code1->kind = ASSIGNc;
							code2->kind = ASSIGNc;
							code1->u.assign.left = var;
							code1->u.assign.right = t1;
							code2->u.assign.left = place;
							code2->u.assigh.right = var;

							insertCodeList(code1);
							insertCodeList(code2);
							break;
						}
					default:
						{
							printf("ERROR: not a assign left side type\n");
							break;
						}
				}
				break;
			}
		case 5: /* for ADD */
		case 6: /* for SUB */
		case 7: /* for MUL */
		case 8: /* for DIV */
			{
				Operand *t1;
				Operand *t2;
				t1 = new_temp();
				t2 = new_temp();

				translate_EXP(EXP->son_node[0], t1);
				translate_EXP(EXP->son_node[2], t2);

				InterCode *code3;
				code3 = malloc(sizeof(InterCode));
				switch(EXP->exp_num)
				{
					case 5:
						code3->kind = ADDc; break;
					case 6:
						code3->kind = SUBc; break;
					case 7:
						code3->kind = MULc; break;
					case 8:
						code3->kind = DIVc; break;
					default:
						break;
				}
				code3->u.binop.result = place;
				code3->u.binop.op1 = t1;
				code3->u.binop.op2 = t2;

				insertCodeList(code3);
				break;
			}
		case 10: /* for MINUS EXP */
			{
				Operand *t1;
				t1 = new_temp();

				translate_EXP(EXP->son_node[1], t1);

				InterCode *code2;
				code2 = malloc(sizeof(InterCode));
				code2->kind = SUBc;
				Operand *zero;
				zero = malloc(sizeof(Operand));
				zero->kind = CONSTo;
				zero->u.const_value = 0;
				code2->u.binop.result = place;
				code2->u.op1 = zero;
				code2->u.op2 = t1;

				insertCodeList(code2);
				break;
			}
	}
}

void translate_STMT(expnode *STMT)
{
	switch(STMT->exp_num)
	{
		case 1: /* for EXP SEMI */
			{
				translate_EXP(STMT->son_node[0], NULL);
				break;
			}
		default:
			{
				printf("ERROR: wrong stmt type\n");
			}
	}
}

char * printOperand(Operand *op)
{
	char *print;
	switch(op->kind)
	{
		case VARo:
			{
				strcpy(print, op->u.var_name);
				break;
			}
		case CONSTo:
			{
				char buffer[20] = { 0 };
				sprintf(buffer, "#%d", op->u.const_value);
				strcpy(print, buffer);
				break;
			}
		case TEMPo:
			{
				char buffer[20] = { 0 };
				sprintf(buffer, "t%d", op->u.temp_no);
				strcpy(print, buffer);
				break;
			}
		default:
			{
				printf("ERROR: wrong operand kind\n");
				break;
			}
	}
	return print;
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
			case ASSIGNc:
				{
					if(printCode->u.assign.left != NULL)
					{
						char *left = printOperand(printCode->u.assign.left);
						char *right = printOperand(printCode->u.assign.right);

						printf("%s := %s", left, right);
					}
					break;
				}
			case ADDc:
			case SUBc:
			case MULc:
			case DIVc:
				{
					if(printCode->u.binop.result == NULL)
					{
						break;
					}

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
