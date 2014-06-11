analyze:
	bison -d syntax.y
	flex lexical.l
	gcc -g main.c syntax.tab.c tree.c semanticlist.c semanticanalyze.c IR.c scode.c -lfl -ly -o parser
