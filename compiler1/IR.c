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
int nowLabel = 1;

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
	temp->u.temp_no = nowTemp;

	nowTemp++;

	return temp;
}

Operand * new_label()
{
	Operand *label;
	label = malloc(sizeof(Operand));
	label->kind = LABELo;
	label->u.label_no = nowLabel;

	nowLabel++;

	return label;
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
				con->u.const_value = EXP->son_node[0]->int_vaule;

				InterCode *conCode;
				conCode = malloc(sizeof(InterCode));
				conCode->prev = NULL;
				conCode->next = NULL;
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
				var->u.var_name = malloc(strlen(EXP->son_node[0]->id_vaule) + 1);
				strcpy(var->u.var_name, EXP->son_node[0]->id_vaule);

				InterCode *varCode;
				varCode = malloc(sizeof(InterCode));
				varCode->prev = NULL;
				varCode->next = NULL;
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
							var->u.var_name = malloc(strlen(left->son_node[0]->id_vaule) + 1);
							strcpy(var->u.var_name, left->son_node[0]->id_vaule);
							translate_EXP(EXP->son_node[2], t1);
							InterCode *code1;
							InterCode *code2;
							code1 = malloc(sizeof(InterCode));
							code2 = malloc(sizeof(InterCode));
							code1->prev = NULL;
							code1->next = NULL;
							code2->prev = NULL;
							code2->next = NULL;
							code1->kind = ASSIGNc;
							code2->kind = ASSIGNc;
							code1->u.assign.left = var;
							code1->u.assign.right = t1;
							code2->u.assign.left = place;
							code2->u.assign.right = var;
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
				code3->prev = NULL;
				code3->next = NULL;
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
				code2->prev = NULL;
				code2->next = NULL;
				code2->kind = SUBc;
				Operand *zero;
				zero = malloc(sizeof(Operand));
				zero->kind = CONSTo;
				zero->u.const_value = 0;
				code2->u.binop.result = place;
				code2->u.binop.op1 = zero;
				code2->u.binop.op2 = t1;

				insertCodeList(code2);
				break;
			}
		case 2: /* for AND */
		case 3: /* for OR */
		case 4: /* for RELOP */
		case 11: /* for NOT */
			{
				Operand *label1;
				Operand *label2;
				label1 = new_label();
				label2 = new_label();

				InterCode *code0;
				code0 = malloc(sizeof(InterCode));
				code0->kind = ASSIGNc;
				code0->u.assign.left = place;
				Operand *number0;
				number0 = malloc(sizeof(Operand));
				number0->kind = CONSTo;
				number0->u.const_value = 0;
				code0->u.assign.right = number0;
				insertCodeList(code0);

				translate_COND(EXP, label1, label2);

				InterCode *code1;
				InterCode *code2;
				code1 = malloc(sizeof(InterCode));
				code2 = malloc(sizeof(InterCode));
				code1->kind = LABELc;
				code1->u.op = label1;
				code2->kind = ASSIGNc;
				code2->u.assign.left = place;
				Operand *number1;
				number1 = malloc(sizeof(Operand));
				number1->kind = CONSTo;
				number1->u.const_value = 1;
				code2->u.assign.right = number1;
				insertCodeList(code1);
				insertCodeList(code2);

				InterCode *code3;
				code3 = malloc(sizeof(InterCode));
				code3->kind = LABELc;
				code3->u.op = label2;
				insertCodeList(code3);

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
		case 2:
			{
				break;			
			}
		case 3: /* for RETURN */
			{
				Operand *t1;
				t1 = new_temp();

				translate_EXP(STMT->son_node[1], t1);

				InterCode *code1;
				code1 = malloc(sizeof(InterCode));
				code1->kind = RETURNc;
				code1->u.op = t1;
				insertCodeList(code1);

				break;
			}
		case 4: /* for IF */
		case 5:
		case 6: /* doing in semanticanalyze.c func: StmtAnalyzer()*/
			{
				break;
			}
		default:
			{
				printf("ERROR: wrong stmt type\n");
				break;
			}
	}
}

void translate_COND(expnode *EXP, Operand *label_true, Operand *label_false)
{
	switch(EXP->exp_num)
	{
		case 4: /* for RELOP */
			{
				Operand *t1;
				Operand *t2;
				t1 = new_temp();
				t2 = new_temp();

				translate_EXP(EXP->son_node[0], t1);
				translate_EXP(EXP->son_node[2], t2);

				int relop = EXP->son_node[1]->relop_vaule;
				InterCode *code1;
				InterCode *code2;
				code1 = malloc(sizeof(InterCode));
				code2 = malloc(sizeof(InterCode));

				code1->kind = IF_GOTOc;
				code1->u.if_goto.left = t1;
				code1->u.if_goto.relop_value = relop;
				code1->u.if_goto.right = t2;
				code1->u.if_goto.label = label_true;

				code2->kind = GOTOc;
				code2->u.op = label_false;

				insertCodeList(code1);
				insertCodeList(code2);
				break;
			}
		case 11: /* for NOT */
			{
				translate_COND(EXP->son_node[1], label_false, label_true);
				break;
			}
		case 2: /* for AND */
			{
				Operand *label1;
				label1 = new_label();

				translate_COND(EXP->son_node[0], label1, label_false);

				InterCode *code1;
				code1 = malloc(sizeof(InterCode));
				code1->kind = LABELc;
				code1->u.op = label1;
				insertCodeList(code1);

				translate_COND(EXP->son_node[2], label_true, label_false);

				break;
			}
		case 3: /* for OR */
			{
				Operand *label1;
				label1 = new_label();

				translate_COND(EXP->son_node[0], label_true, label1);

				InterCode *code1;
				code1 = malloc(sizeof(InterCode));
				code1->kind = LABELc;
				code1->u.op = label1;
				insertCodeList(code1);

				translate_COND(EXP->son_node[2], label_true, label_false);

				break;
			}
		default: /* for others */
			{
				Operand *t1;
				t1 = new_temp();

				translate_EXP(EXP, t1);

				InterCode *code1;
				InterCode *code2;
				code1 = malloc(sizeof(InterCode));
				code2 = malloc(sizeof(InterCode));

				code1->kind = IF_GOTOc;
				code1->u.if_goto.left = t1;
				code1->u.if_goto.relop_value = 6;
				Operand *zero;
				zero = malloc(sizeof(Operand));
				zero->kind = CONSTo;
				zero->u.const_value = 0;
				code1->u.if_goto.right = zero;
				code1->u.if_goto.label = label_true;

				code2->kind = GOTOc;
				code2->u.op = label_false;

				insertCodeList(code1);
				insertCodeList(code2);

				break;
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
				print = malloc(strlen(op->u.var_name) + 1);
				strcpy(print, op->u.var_name);
				break;
			}
		case CONSTo:
			{
				char buffer[20] = { 0 };
				sprintf(buffer, "#%d", op->u.const_value);
				print = malloc(strlen(buffer) + 1);
				strcpy(print, buffer);
				break;
			}
		case TEMPo:
			{
				char buffer[20] = { 0 };
				sprintf(buffer, "t%d", op->u.temp_no);
				print = malloc(strlen(buffer) + 1);
				strcpy(print, buffer);
				break;
			}
		case LABELo:
			{
				char buffer[20] = { 0 };
				sprintf(buffer, "label%d", op->u.label_no);
				print = malloc(strlen(buffer) + 1);
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

						printf("%s := %s\n", left, right);
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
					char *result = printOperand(printCode->u.binop.result);
					char *op1 = printOperand(printCode->u.binop.op1);
					char *op2 = printOperand(printCode->u.binop.op2);
					switch(printCode->kind)
					{
						case ADDc:
							{
								printf("%s = %s + %s\n", result, op1, op2);
								break;
							}
						case SUBc:
							{
								printf("%s = %s - %s\n", result, op1, op2);
								break;
							}
						case MULc:
							{
								printf("%s = %s * %s\n", result, op1, op2);
								break;
							}
						case DIVc:
							{
								printf("%s = %s / %s\n", result, op1, op2);
								break;
							}
						default:
							{
								printf("ERROR: kind not right\n");
								break;
							}
					}
					break;
				}
			case LABELc:
				{
					char *op = printOperand(printCode->u.op);
					printf("LABEL %s :\n", op);
					break;
				}
			case GOTOc:
				{
					char *op = printOperand(printCode->u.op);
					printf("GOTO %s\n", op);
					break;
				}
			case IF_GOTOc:
				{
					char *left = printOperand(printCode->u.if_goto.left);
					char *right = printOperand(printCode->u.if_goto.right);
					char *label = printOperand(printCode->u.if_goto.label);

					switch(printCode->u.if_goto.relop_value)
					{
						case 1:
							{
								printf("IF %s > %s GOTO %s\n", left, right, label);
								break;
							}
						case 2:
							{

								printf("IF %s < %s GOTO %s\n", left, right, label);
								break;
							}
						case 3:
							{

								printf("IF %s >= %s GOTO %s\n", left, right, label);
								break;
							}
						case 4:
							{

								printf("IF %s <= %s GOTO %s\n", left, right, label);
								break;
							}
						case 5:
							{
								printf("IF %s == %s GOTO %s\n", left, right, label);
								break;
  
							}
						case 6:
							{
								printf("IF %s != %s GOTO %s\n", left, right, label);
								break;

							}
						default:
							{
								printf("ERROR: wrong relop value\n");
								break;
							}
					}
					break;
				}
			case RETURNc:
				{
					char *op = printOperand(printCode->u.op);
					printf("RETURN %s\n", op);
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
