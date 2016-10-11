%{
	#include"y.tab.h"
%}

%%

[ \t\n]+			;
\+|\-|\/|\*		{ return OP; }
main			{ return MAIN; }

if			{ return IF; }
else			{ return ELSE; }
for			{ return FOR; }
while			{ return WHILE; }
int|float|double|short|long|void	{return DT; }

\>|\<|\>\=|\<\=|\=\=	{ return RELATIONAL; }

\+\+			{ return INC; }
\-\-			{ return DEC; }

[0-9]+			{ return NUMBER; }
[a-zA-Z][a-zA-Z0-9]*	{ return ID; }
.			{ return yytext[0]; }

%%
