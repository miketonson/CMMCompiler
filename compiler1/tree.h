/*
 * =====================================================================================
 *
 *       Filename:  tree.h
 *
 *    Description:  declear the tree structure and add node methods
 *                  for syntax tree
 *        Version:  1.0
 *        Created:  03/22/2014 07:42:38 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Guang-Zhi Tang, 
 *   Organization:  
 *
 * =====================================================================================
 */

typedef struct expnode
{
	int lineno;
	int exp_num;
	int node_sum;
	enum KIND {Program,ExtDefList,ExtDef,Specifier,ExtDecList,FunDec,CompSt,VarDec,StructSpecifier,OptTag,DefList,Tag,VarList,ParamDec,StmtList,Stmt,Exp,Def,DecList,Dec,Args,noExp} kind;
	enum MEAN {ID,INT,FLOAT,TYPE,noMean} mean;
	enum TERM {SEMI,COMMA,ASSIGNOP,RELOP,PLUS,MINUS,STAR,DIV,AND,OR,DOT,NOT,LP,RP,LB,RB,LC,RC,STRUCT,RETURN,IF,ELSE,WHILE,noTerm} terminal;
	struct expnode* son_node[];
}expnode;

