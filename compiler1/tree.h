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


typedef enum KIND {Program,ExtDefList,ExtDef,Specifier,ExtDecList,FunDec,CompSt,VarDec,StructSpecifier,OptTag,DefList,Tag,VarList,ParamDec,StmtList,Stmt,Exp,Def,DecList,Dec,Args} KIND;
typedef enum TERM {SEMIm,COMMAm,ASSIGNOPm,PLUSm,MINUSm,STARm,DIVm,ANDm,ORm,DOTm,NOTm,LPm,RPm,LBm,RBm,LCm,RCm,STRUCTm,RETURNm,IFm,ELSEm,WHILEm} TERM;
typedef enum MEAN {IDm,INTm,FLOATm,TYPEm,RELOPm} MEAN;

typedef struct expnode
{
	struct expnode *father_node;
	int search_num;

	int lineno;//which line the syntax is in
	int node_type;//type of the node: 1 for non-terminate; 2 for terminate with no meaning; 3 for terminate with meaning
	int exp_num;//the num of exp on the right
	int node_sum;//num of son nodes

	KIND kind;//non-terminate
	TERM term;//terminate with no meaning
	MEAN mean;//terminate with meaning

	int int_vaule;//meaning of INT
	int type_vaule;//meaning of TYPE: 0 for INT, others for FLOAT
	float float_vaule;//mean of FLOAT
	char *id_vaule;//mean of ID
	int relop_vaule;//meaning of RELOP: 1 for >, 2 for <, 3 for >=, 4 for <=, 5 for ==, 6 for !=

	struct expnode *son_node[10];
}expnode;

