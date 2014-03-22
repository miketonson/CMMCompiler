analyze:
	bison -d -t syntax.y
	flex lexical.l
	gcc main.c syntax.tab.c -lfl -ly -o parser
