#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct Stack {
	int data;
	struct Stack *next;
};

typedef struct Stack stack_struct;
typedef stack_struct *stack;

int    isOperator(char);
void   operation(int, int, char);

void   push(stack *, int);
int    pop(stack *);

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
			str[x] = '\0';
			push(&st, atoi(str));
			j+=x; j--;
		}
		else if(isOperator(postfix[j]))
		{
				x = pop(&st);
				y = pop(&st);
			    operation(x, y, postfix[j]);
		}
		j++;
	}
	printf("%d\n", pop(&st));
	free(str);
    return 0;
}

void push(stack *st, int input)
{
	stack new_st;
	new_st = malloc(sizeof(stack_struct));
	if(new_st != NULL)
	{
		new_st->data = input;
		new_st->next = *st;
		*st = new_st;
	}
	else 
	{
	printf("Element not inserted to stack. No memory.\n");
	exit(-1);
	}
}

int pop(stack *st)
{
	stack delete_st = *st;
    int ret = (*st)->data;
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
	switch(c) {
		case '+': result = y + x; break;
		case '-': result = y - x; break;
		case '*': result = y * x; break;
		case '/': result = y / x; break; }
		push(&st, result);
}