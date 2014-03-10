%option yylineno
type	int|float
relop	>|<|>=|<=|==|!=
int	0|([1-9][0-9]*)
float	{int}\.([0-9]+)([eE][+-]?{int})?
id	[_A-Za-z][_A-Za-z0-9]*
wrongid	[0-9][_A-Za-z0-9]*
ws	[ \t\n]+
%%
{ws}	{ /*do nothing*/ }
";"	{ printf("SEMI\n"); }
","	{ printf("COMMA\n"); }
"="	{ printf("ASSIGNOP\n"); }
{relop}	{ printf("RELOP\n"); }
"+"	{ printf("PLUS\n"); }
"-"	{ printf("MINUS\n"); }
"*"	{ printf("STAR\n"); }
"/"	{ printf("DIV\n"); }
"&&"	{ printf("AND\n"); }
"||"	{ printf("OR\n"); }
"."	{ printf("DOT\n"); }
"!"	{ printf("NOT\n"); }
{type}	{ printf("TYPE\n"); }
"("	{ printf("LP\n"); }
")"	{ printf("RP\n"); }
"["	{ printf("LB\n"); }
"]"	{ printf("RB\n"); }
"{"	{ printf("LC\n"); }
"}"	{ printf("RC\n"); }
"struct"	{ printf("STRUCT\n"); }
"return"	{ printf("RETURN\n"); }
"if"	{ printf("IF\n"); }
"else"	{ printf("ELSE\n"); }
"while"	{ printf("WHILE\n"); }
{id}	{ printf("ID\n"); }
{int}	{ printf("INT\n"); }
{float}	{ printf("FLOAT\n"); }
{wrongid}	{ printf("Error type A at line %d: You wirte a wrong ID \'%s'\n", yylineno, yytext); }
.	{ printf("Error type A at line %d: Mysterious character \'%s\'\n", yylineno, yytext);}
%%
int main(int argc, char** argv){
	if(argc > 1){
		if(!(yyin = fopen(argv[1],"r"))){
			perror(argv[1]);
			return 1;
		}
	}
	while(yylex() != 0);
	return 0;
}
