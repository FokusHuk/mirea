#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct Stack {
	char data[30];
	struct Stack *next;
};

typedef struct Stack stack_struct;
typedef stack_struct *stack;

int    isOperator(char);
void   operation(int, int, char);

void   push(stack *, char *);
char * pop(stack *);

void itoa(int, char []);
void reverse(char []);

stack st = NULL;

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("No argument for program.\n");
		exit(-1);
	}
    char postfix[256];
	char *str = malloc(sizeof(char)*30);
	strncpy(postfix, argv[1], strlen(argv[1]));
	postfix[strlen(argv[1])] = '\0';
	int j = 0, x, y;
	while(postfix[j] != '\0')
	{
		if(isdigit(postfix[j]))
		{
			x = 0;
			while(isdigit(postfix[j]))
			{
				x++;j++;
			}
			j -= x;
			strncpy(str, postfix+j, x);
			push(&st, str);
			j+=x; j--;
		}
		else if(isOperator(postfix[j]))
		{
				printf("s\n");
				str = (char *)pop(&st);
				printf("h\n");
				x = atoi(str);
				y = atoi((char *)pop(&st));
			    operation(x, y, postfix[j]);
		}
		j++;
	}
	printf("%s\n", pop(&st));
	free(str);
    return 0;
}

void push(stack *st, char *symbol)
{
	stack new_st;
	new_st = malloc(sizeof(stack_struct));
	if(new_st != NULL)
	{
		strcpy(new_st->data, symbol);
		new_st->next = *st;
		*st = new_st;
	}
	else 
	{
	printf("Element not inserted to stack. No memory.\n");
	exit(-1);
	}
}

char *pop(stack *st)
{
	stack delete_st = *st;
	char *ret;
	strcpy(ret, (*st)->data);
	*st = (*st)->next;
	free(delete_st);
	return ret;
}

int isOperator(char symbol)
{
	if(symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '%' || symbol == '^')
		return 1;
	else return 0;
}

void operation(int x, int y, char c)
{
        int result = 0, i = 0;
		char str[30];
	switch(c) {
		case '+': result = y + x; break;
		case '-': result = y - x; break;
		case '*': result = y * x; break;
		case '/': result = y / x; break; }
		printf("%d\n", result);
		itoa(result, str);
		push(&st, str);
}

 void itoa(int n, char s[])
 {  
     int i = 0;
     do { s[i++] = n % 10 + '0'; } while ((n /= 10) > 0);   
     s[i] = '\0';
	 reverse(s);
 }
 
 void reverse(char s[])
 {
     int i, j;
     char c;
 
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }