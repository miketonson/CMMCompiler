analyze:
	bison -d syntax.y
	flex lexical.l
	gcc -ggdb main.c syntax.tab.c tree.c semanticlist.c semanticanalyze.c IR.c -lfl -ly -o parser
