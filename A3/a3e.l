%{
	#include<string.h>
	int insert(char str[]);
	FILE *fin;
	char c1[25], c2[25];	
	unsigned int n=1, count=0, i;
	struct st
	{
		char name[25]; 
		int value;
	}*symbol[50];
%}

%%
	
[ \t]+					;
[\n]+					{ n++;}
\/\*[a-zA-Z0-9 \t\n]*\*\/[ \t\n]*	{ n++; }
\/\*.*\*\/[ \t\n]*			{ n++; }
\/\/.*[ \t\n]*				{ n++; }
#					{ printf("\n%d\t#\t\t:Preprocessor", n); }
include					{ printf("\n%d\tinclude\t\t:Including header file", n); }
\<\<					{ printf("\n%d\t<<\t\t:Printing or Left Shift", n); }
\>\>					{ printf("\n%d\t>>\t\t:Accepting input or Right Shift", n); }
\<					{ printf("\n%d\t<\t\t:Left Angular Brackets or less than", n); }
\>					{ printf("\n%d\t>\t\t:Right Angular Brackets or greater than", n); }
[a-zA-Z0-9]+\.h				{ printf("\n%d\t%s\t\t:Header file", n, yytext); }
\(					{ printf("\n%d\t(\t\t:Left bracket", n); }
\)					{ printf("\n%d\t)\t\t:Right bracket", n); }
\{					{ printf("\n%d\t{\t\t:Opening brace", n); }
\}					{ printf("\n%d\t}\t\t:Closing brace", n); }
\,					{ printf("\n%d\t,\t\t:Comma", n); }
\;					{ printf("\n%d\t;\t\t:End of statement", n); }
\+\+					{ printf("\n%d\t%s\t\t:Increment", n, yytext); }
\-\-					{ printf("\n%d\t%s\t\t:Decrement", n, yytext); }
\=|\+|\-|\/|\*|\%			{ printf("\n%d\t%s\t\t:Operator", n, yytext); }
void|short|int|long|float|double|char|struct		{ printf("\n%d\t%s\t\t:Datatype", n, yytext); }
void|main|return			{ printf("\n%d\t%s\t\t:Keyword", n, yytext); }
printf|scanf|cout|cin			{ printf("\n%d\t%s\t\t:Built in function", n, yytext); }
for|while				{ printf("\n%d\t%s\t\t:Loops", n, yytext); }
\"[ _a-zA-Z0-9\%\-\\]*\"		{ printf("\n%d\t%s\t\t:String constant", n, yytext); }
\'[ _a-zA-Z0-9]\'			{ printf("\n%d\t%s\t\t:Character constant", n, yytext); }
[0-9]+					{ printf("\n%d\t%s\t\t:Integer constant", n, yytext); }
[0-9]+\.[0-9]+				{ printf("\n%d\t%s\t\t:Real constant", n, yytext); }
([_a-zA-Z]+[_a-zA-Z0-9]*)		{ printf("\n%d\t%s\t\t:Identifier\t\t%d", n, yytext, insert(yytext)); }
. {printf("\n Error!");}
%%
	
main()
{
	fin=fopen("sample.cpp", "r");
	yyin=fin;
	printf("\n_________________________________________________________");
	printf("\nLINE NO\tLEXEME\t\tTOKEN\t\tATTRIBUTE");
	printf("\n_________________________________________________________");
	yylex();
	printf("\n_________________________________________________________");
	printf("\nSYMBOL TABLE");
	printf("\n_______________________________________");
	printf("\nNAME\t\tVALUE");
	printf("\n_______________________________________");
	for(i=0; i<count; i++)
		printf("\n%s\t\t%d", symbol[i]->name, symbol[i]->value);
	printf("\n_______________________________________");
	fclose(fin);
	printf("\nParsing done!!\n"); 
}

int insert(char str[])
{
	int i;
	for(i=0; i<count; i++)
	{	
		if(strcmp(str, symbol[i]->name)==0)	return i;
	}
	symbol[count]=(struct st*)malloc(sizeof(struct st));
	strcpy(symbol[count]->name, str);
	symbol[count]->value=0;
	return count++;
}

int yywrap()
{
return 1;
}
