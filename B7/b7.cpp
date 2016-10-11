

/*
Grammar without left recursion
		 E->TE'
		 E'->+TE|e
		 T->FT'
		 T'->*FT|e
		 F->(E)|i
		 e denotes epsilon.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char *ip=new char[100];
char *op=new char[100];
char *temp=new char[100];
int ip_ptr=0;
int n=0;

void e_prime();
void e();
void t_prime();
void t();
void f();
void advance();

void e()
{
	int n=0;
	for(int i=0;i<=strlen(op);i++)
	{
		if(op[i]!='e')
			temp[n++]=op[i];
	}
	strcpy(op,temp);
	for(n=0;n<strlen(op);n++)
	{
		if(op[n]=='E')
			break;
	}
	for(int i=n+1;i<=strlen(op);i++)
			temp[i+2]=op[i];
	temp[n]='T';
	temp[n+1]='E';
	temp[n+2]='\'';
	strcpy(op,temp);
	printf("E=%-25s",op);
	printf("E->TE'\n");
	t();
	e_prime();
}

void e_prime()
{
	int n=0;
	for(int i=0;i<=strlen(op);i++)
	{
		if(op[i]!='e')
			temp[n++]=op[i];
	}
	strcpy(op,temp);
	for(n=0;n<strlen(op);n++)
	{
		if(op[n]=='E')
			break;
	}

	if(ip[ip_ptr]=='+')
	{
		advance();
		strcpy(temp,op);
		for(int i=n+2;i<=strlen(op);i++)
			temp[i+2]=op[i];
		temp[n]='+';
		temp[n+1]='T';
		temp[n+2]='E';
		temp[n+3]='\'';
		strcpy(op,temp);
		printf("E=%-25s",op);
		printf("E'->+TE'\n");
		t();
		e_prime();
	}
	else
	{
		strcpy(temp,op);
		for(int i=n+2;i<=strlen(op);i++)
					temp[i-1]=op[i];
		temp[n]='e';
		strcpy(op,temp);
		printf("E=%-25s",op);
		printf("E'->e\n");
	}
}

void t()
{
	int n=0;
	for(int i=0;i<=strlen(op);i++)
	{
		if(op[i]!='e')
			temp[n++]=op[i];
	}
	strcpy(op,temp);
	for(n=0;n<strlen(op);n++)
	{
		if(op[n]=='T')
			break;
	}

	for(int i=n+1;i<=strlen(op);i++)
		temp[i+2]=op[i];
	temp[n]='F';
	temp[n+1]='T';
	temp[n+2]='\'';
	strcpy(op,temp);
	printf("E=%-25s",op);
	printf("T->FT'\n");
	f();
	t_prime();
}

void t_prime()
{
	int n=0;
	for(int i=0;i<=strlen(op);i++)
	{
		if(op[i]!='e')
			temp[n++]=op[i];
	}
	strcpy(op,temp);
	for(n=0;n<strlen(op);n++)
	{
		if(op[n]=='T')
			break;
	}

	if(ip[ip_ptr]=='*')
	{
		advance();
		strcpy(temp,op);
		for(int i=n+2;i<=strlen(op);i++)
			temp[i+2]=op[i];
		temp[n]='*';
		temp[n+1]='F';
		temp[n+2]='T';
		temp[n+3]='\'';
		strcpy(op,temp);
		printf("E=%-25s",op);
		printf("T'->*FT'\n");
		f();
		t_prime();
	}
	else
	{
		strcpy(temp,op);
		for(int i=n+2;i<=strlen(op);i++)
					temp[i-1]=op[i];
		temp[n]='e';
		strcpy(op,temp);
		printf("E=%-25s",op);
		printf("T'->e\n");
	}
}

void f()
{
	int n=0;
	for(int i=0;i<=strlen(op);i++)
	{
		if(op[i]!='e')
			temp[n++]=op[i];
	}
	strcpy(op,temp);
	for(n=0;n<strlen(op);n++)
	{
		if(op[n]=='F')
			break;
	}

	if(ip[ip_ptr]=='(')
	{
		advance();
		strcpy(temp,op);
		for(int i=n+1;i<=strlen(op);i++)
			temp[i+2]=op[i];
		temp[n]='(';
		temp[n+1]='E';
		temp[n+2]=')';
		strcpy(op,temp);
		printf("E=%-25s",op);
		printf("F->(E)\n");
		e();
		if(ip[ip_ptr]==')')
		{
			advance();
		}
		else
		{
			printf("\n\t syntax error\n");
			exit(1);
		}
	}
	else if(ip[ip_ptr]=='i' || ip[ip_ptr]=='I')
	{
		advance();
		op[n]='i';
		printf("E=%-25s",op);
		printf("F->i\n");
	}
	else
	{
		printf("\n\t syntax error\n");
		exit(1);
	}
}

void advance()
{
	ip_ptr++;
}

int main()
{
 int i;
 printf("\nGrammar without left recursion");
 printf("\n\t\t E->TE' \n\t\t E'->+TE'|e \n\t\t T->FT' ");
 printf("\n\t\t T'->*FT'|e \n\t\t F->(E)|i");
 printf("\n Enter the input expression:");
 scanf("%s",ip);
 for(i=0;i<strlen(ip);i++)
 {
  if(ip[i]!='+'&&ip[i]!='*'&&ip[i]!='('&&ip[i]!=')'&&ip[i]!='i'&&ip[i]!='I')
  {
   printf("\nSyntax error\n");
   break;
  }
 }
 printf("Expressions");
 printf("\t Sequence of production rules\n");
 e();

 int n=0;
 for(i=0;i<=strlen(op);i++)
 {
	 if(op[i]!='e')
		 temp[n++]=op[i];
 }

 strcpy(op,temp);
 printf("E=%-25s",op);
 return 0;
}
 

