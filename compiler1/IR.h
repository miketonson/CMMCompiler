/*
 * =====================================================================================
 *
 *       Filename:  IR.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/15/2014 06:49:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Guang-Zhi Tang, 
 *   Organization:  NJU CS
 *
 * =====================================================================================
 */
#ifndef _IR_H_
#define _IR_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "semanticlist.h"
#include "semanticanalyze.h"

extern int nowTemp;
extern int nowLabel;

typedef struct Operand_ Operand;
typedef struct InterCode_ InterCode;

struct Operand_
{
	enum { VARo, CONSTo, ADDRo, TEMPo, STARo, LABELo, FUNCo } kind;
	union
	{
		/* for VAR */
		char *var_name;
		/* for CONST */
		int const_value;
		/* for ADDR */
		Operand *addr_of;
		/* for TEMP */
		int temp_no;
		/* for STAR */
		Operand *addr_from;
		/* for LABEL */
		int label_no;
		/* for FUNC */
		char *func_name;
	}u;
};

struct InterCode_
{
	enum { LABELc, FUNCc, ASSIGNc, ADDc, SUBc, MULc, DIVc, GOTOc, IF_GOTOc, RETURNc, DECc, ARGc, CALL_FUNCc, PARAMc, READc, WRITEc } kind;
	union
	{
		/* for LABEL, FUNC, GOTO, RETURN, ARG, PARAM, READ, WRITE */
		Operand *op;
		/* for ASSIGN */
		struct { Operand *left; Operand *right; }assign;
		/* for ADD, SUB, MUL, DIV */
		struct { Operand *result; Operand *op1; Operand *op2; }binop;
		/* for IF_GOTO */
		struct { Operand *left; int relop_value; Operand *right; Operand *label; }if_goto;
		/* for DEC */
		struct { Operand *var; int size; }dec;
		/* for CALL_FUNC */
		struct { Operand *var; Operand *func; }call_func;
	}u;
	InterCode *prev;
	InterCode *next;
};
/* list of the inter code */
InterCode *interCodeList;

void insertCodeList(InterCode *interCode);
Operand * new_temp();
Operand * new_label();
void mem_dec(var *varPoint);
void translate_EXP(expnode *EXP, Operand *place);
void translate_STMT(expnode *STMT);
void translate_COND(expnode *EXP, Operand *label_true, Operand *label_false);
void printCodeList();
#endif
