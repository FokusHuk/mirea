// infix_to_postfix.c
// аргументы передаются через командную строку в main
// аргументы имеют вид: "X", где X - выражение, которое необходимо перевести в постфиксную форму
// ./a.out "(2 + 2) / 2"
// ДЛЯ КОРРЕКТНОЙ РАБОТЫ! => необходимо справа и слева от знаков операций (+, -, *, /, %, ^) ставить пробелы, как в примере выше


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct Stack {
	char data;
	struct Stack *next;
};

typedef struct Stack stack_struct;
typedef stack_struct *stack;

int    isOperator(char);
int    cmp(char, char); // сравнение приоритетов двух операций

void   push(stack *, char);
char   pop(stack *);

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("No argument for program.\n");
		exit(-1);
	}
    char infix[256], postfix[256]; // два массива, для инфиксной и постфиксной записи данного выражения
	int i, j;
	i = 0;
	j = 0;
	strncpy(infix, argv[1], strlen(argv[1]));
	stack st = NULL;
	push(&st, '(');
	strncat(infix, ")", 1);
	while(st != NULL)
		{
			if(isdigit(infix[i]))
				{
					postfix[j] = infix[i];
					j++;
				}
			else if(infix[i] == '(')
				push(&st, '(');
			else if(isOperator(infix[i]))
				{
				    postfix[j] = ' ';
					j++;
					if(isOperator(st->data))
						while(cmp(infix[i], st->data)) // пока верхний элемент стека содержит операцию и
							{							// ее приоритет меньше приоритета текущей операции из infix[i]
								postfix[j] = pop(&st);  // извлекать операции из стека в postfix
								j++;
								if(!isOperator(st->data))
									break;
							}
					if(postfix[j-1] != ' ') 
					{
						postfix[j] = ' ';
						j++;
					}
					push(&st, infix[i]);
				}
			if(infix[i] == ')')
				{
					postfix[j] = ' ';
					j++;
					while(st->data != '(')
						{
							if(isOperator(st->data))
								{
									postfix[j] = st->data;
									j++;
									pop(&st);
								}
							else pop(&st);
						}
					pop(&st);
				}
			i++;
		}
	postfix[j] = '\0';
	printf("%s\n", postfix);
    return 0;
}

void push(stack *st, char symbol)
{
	stack new_st;
	new_st = malloc(sizeof(stack_struct));
	if(new_st != NULL)
	{
		new_st->data = symbol;
		new_st->next = *st;
		*st = new_st;
	}
	else 
	{
	printf("Element not inserted to stack. No memory.\n");
	exit(-1);
	}
}

char pop(stack *st)
{
	stack delete_st;
	char ret;
	delete_st = *st;
	ret = (*st)->data;
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

int cmp(char sym_1, char sym_2)
{
	switch(sym_1)
		{
			case '+': sym_1 = '2'; break;
			case '-': sym_1 = '1'; break;
			case '*': sym_1 = '5'; break;
			case '/': sym_1 = '4'; break;
			case '%': sym_1 = '3'; break;
			case '^': sym_1 = '6'; break;
		}
	switch(sym_2)
		{
			case '+': sym_2 = '2'; break;
			case '-': sym_2 = '1'; break;
			case '*': sym_2 = '5'; break;
			case '/': sym_2 = '4'; break;
			case '%': sym_2 = '3'; break;
			case '^': sym_2 = '6'; break;
		}
	if((int)sym_1 <= (int)sym_2) return 1;
	return 0;
}
