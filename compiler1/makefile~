analyze:
	bison -d syntax.y
	flex lexical.l
	gcc main.c syntax.tab.c tree.c semanticlist.c semanticanalyze.c -lfl -ly -o parser
