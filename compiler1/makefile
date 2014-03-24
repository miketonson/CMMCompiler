analyze:
	bison -d syntax.y
	flex lexical.l
	gcc main.c syntax.tab.c -lfl -ly -std=c99 -o parser
