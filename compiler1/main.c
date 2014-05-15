#include <stdio.h>
#include "syntax.tab.h"
#include "tree.h"
#include "semanticlist.h"
#include "semanticanalyze.h"
#include "IR.h"
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  this is the main method for the complier,
 *                for now it is used for lyntax, and there
 *                may have a tree method under this.
 * =====================================================================================
 */
int main(int argc, char** argv){
	if(argc <= 1)
		return 1;
	FILE* f = fopen(argv[1], "r");
	if (!f){
		perror(argv[1]);
		return 1; 
	}
	yyrestart(f);
	//extern FILE* yydebug; 
	//yydebug = 1; 
	yyparse();
	//PrintTree();
	SemanticAnalyze();
	printTestError();
	
	/* code for IR*/
	printCodeList();
	/* code end */
	return 0;
}
