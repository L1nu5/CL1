%{
	#include<stdio.h>
	extern FILE *yyin;
	int flag = 1;
%}

%start s
%token ID MAIN OP CONDITIONAL IF FOR WHILE RELATIONAL INC DEC NUMBER DT ELSE
%left '+''-'
%left '/''*'

%%

s:	MAIN'('')' '{' prog '}' { if(flag) printf("PROGRAM IS VALID\n"); else printf("INVALID PROGRAM\n");  }
	;

prog:	stmtlist prog
	|
	;

stmtlist:stmtlist stmt|;

stmt:	ID '=' expr ';'	{ printf("Valid Statement\n"); }
	| expr ';'	{ printf("Valid Statement\n"); }
	| forstmt	{ printf("for statement is a Valid Statement\n"); }
	| whilestmt 	{ printf("while statement is a Valid Statement\n"); }
	| ifstmt	{ printf("if statement is a Valid Statement\n"); }
	| vardeclare    { printf("Incorrect declaration statement\n"); flag = 0;}
	| vardeclare ';'{ printf("variable declaration statment is a Valid Statement\n"); }
	;
vardeclist: vardeclist vardeclare|;

vardeclare:	DT ID	{}
		| DT ID '=' NUMBER	{}
		| ID '=' NUMBER	{}
		| DT ID '=' NUMBER ',' vardeclist	{}
		| ID '=' NUMBER  ',' vardeclist	{}
		;

expr:	expr OP expr	{}
	| ID '=' expr OP NUMBER	{}
	| ID		{}
	;

ifstmt:	IF'(' condition ')' '{' stmtlist '}'	{}
	| IF'(' condition ')' '{' stmtlist '}' ELSE'{' stmtlist '}'	{}
	| IF'(' condition ')'  stmtlist  ELSE stmtlist	{}
	;

forstmt:	FOR '(' assigning ';' condition ';' incdec ')' '{' stmtlist '}'	{}
		;
			
condition:	expr RELATIONAL expr		{}
		| expr RELATIONAL NUMBER	{}
		;

incdec:	ID INC	{}
	| ID DEC	{}
	;

assigning:	ID '=' expr	{}
		| ID '=' NUMBER	{}
		;

whilestmt:	WHILE'(' condition ')' '{' stmtlist '}'	{}
		;

%%

main()
{
	FILE *fin;
	fin=fopen("expressions.txt", "r");
	yyin=fin;
	yyparse();
}

int yywrap()
{
	return 1;
}

int yyerror()
{
	printf("**Syntax Error**");
	return 1;
}
