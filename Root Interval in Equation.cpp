#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
double power(double,double);
void push(char *,char);
void push2(double *,double);
double pop2(double *);
char pop(char *);
char peep(char *);
int precedence(char);
int isoperator(char);
int isoperand(char);
double evalpostfix(char *,int);
int top=-1;
int top2=-1;
int main()
{
	char str[100],stack[100],post[100],x,ch2;
	int n,i=0,k=0,j,num,temp=-1;
	double value;
	printf("Enter the Infix Expression :");
	scanf("%s",str);
	n=strlen(str);
	str[n]=')';
	str[++n]='\0';
	push(stack,'(');
	while(str[i]!='\0')
	{
		char ch;
		ch=str[i];
		if(isoperand(ch))
			post[k++]=ch;
		else
		{
			if(ch=='(') //if the new sym is left preanthesis
			{
				push(stack,ch);
			}
			if(ch==')') //if the sym is right preanthesis then pop from stack till left preanthesis
			{
				x=pop(stack);
				while(x!='(')  //
				{
					post[k++]=x;
					x=pop(stack);
				}
			}
			if(isoperator(ch))
			{
				ch2=peep(stack);

					while(precedence(ch)<=precedence(ch2))
					{
						ch2=pop(stack);
						post[k++]=ch2;
						ch2=peep(stack);
					}
				push(stack,ch);
			}
		}
	i++;
	}
	post[k]='\0';
	printf("Postfix Notation : %s \n",post);
	for(j=-20;j<=20;j++)
	{
		value=evalpostfix(post,j);
		//printf("Value of Expression at %d = %lf \n",j,value);
		if(evalpostfix(post,j)*evalpostfix(post,temp)<0)
		{
			printf("Your Interval is : %d & %d",temp,j);
			exit (0);
		}
		temp=j;
	}
}
void push(char *s,char ch)
{
	if(top==99)
	{
		printf("!!ERROR!! stack is full");
		exit(0);
	}
	else
		s[++top]=ch;
}
void push2(double *s,double ch)
{
	if(top2==99)
	{
		printf("!!ERROR!! stack is full");
		exit(0);
	}
	else
		s[++top2]=ch;
}
char pop(char *s)
{
	if(top==-1)
	{
		printf("!!Error!! stack is empty");
		exit(0);
	}
	return s[top--];
}
double pop2(double *s)
{
	if(top2==-1)
	{
		printf("!!Error!! stack is empty");
		exit(0);
	}
	return s[top2--];
}
char peep(char *s)
{
	return (s[top]);
}
int precedence(char ch)
{
	switch(ch)
	{
		case '+':
		case '-':return 1;
		case '*':
		case '/':return 2;
		case '^':return 3;
		default: return 0;
	}
}
int isoperator(char ch)
{
	if(ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='^')
		return 1;
	else
        return 0;
}

int isoperand(char ch)
{
	if(ch>='a' && ch<='z' || ch>='A' && ch<='Z' || ch>='0' && ch<='9')
		return 1;
	else
		return 0;
}
double evalpostfix(char post[],int j)
{
	int i=0;
	double stack[100];
	while(post[i]!='\0')
	{
		char ch3=post[i];
		if(isoperand(ch3))
		{
			//if(isdigit(ch3))
			if(ch3>='0'&&ch3<='9')
			{
				int a='0';
				push2(stack,ch3-a);
			}
			else
				push2(stack,j);
		}
		if(isoperator(ch3))
		{
			double A,B;
			A=pop2(stack);
			B=pop2(stack);
			switch(ch3)
			{
				case '+':push2(stack,B+A);
					 break;
				case '-':push2(stack,B-A);
					 break;
				case '*':push2(stack,B*A);
					 break;
				case '/':push2(stack,B/A);
					 break;
				case '^':push2(stack,power(B,A));
					 break;
			}

		}
	i++;
	}
	return pop2(stack);
}
double power(double a,double b)
{
	if(b==0)
		return 1;
	else
		return a*power(a,b-1);
}
