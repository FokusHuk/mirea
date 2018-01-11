/* turing.c
 программа не принимает аргументов
 считывание инструкций для выполнения программы осуществляется из файла code.txt, находящегося в одной папке с исполняемой программой */


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

struct memory_struct{ /* структура для представления памяти */
	int data;
	struct memory_struct *next;
	struct memory_struct *previous;
};

struct code{ /*структура для хранения кода(1 экземпляр = 1 строка кода) */
	int index; /* номер строки */
	char opr[100]; /* операция */
	struct code *prev;
	struct code *next;
};

typedef struct code Code;
typedef Code * CodePtr;

typedef struct memory_struct Memory;
typedef Memory * MemoryPtr;

void	operation(char *); /* определяет тип операции в данной строке кода и выполняет её */
int 	isoperation(char *); /* возвращает true, если дананя строка является командой */
void	add(MemoryPtr *, int); /* добавляет новую ячейку памяти в начало или конец "ленты памяти" */
void	addc(CodePtr *, char *); /* добавляет новую строку кода в конец списка */
void	move_to(CodePtr *, int); /* перемещает указатель с текущей команды в коде на указанную */

#define ERROR_MESSAGE "ERROR"

MemoryPtr memory = NULL; /* "лента памяти" */
CodePtr cd = NULL; /* указатель на список, содержащий код выполняемой программы */

int memory_stack[10]; /* стек для хранения адресов блоков begin-end для управления вложенными циклами */
int stack_pointer; /* указатель на верхний элемент стека */

int main()
{
	stack_pointer = 0;
	FILE *file;
	char *line, *comment; /* line - считывание очередной команды из файла, comment - считывание комментариев из файла */
	comment = NULL;
	add(&memory, 0);
	if((line = malloc(sizeof(char) * 200)) == NULL)
	{
		printf("%s%s\n", ERROR_MESSAGE, ": memory error");
		exit(-1);
	}
	if((file = fopen("code.txt", "r")) == NULL)
	{
		printf("%s%s\n", ERROR_MESSAGE, ": file cant be opened");
		exit(-1);
	}
	printf("#CODE:\n");
	while(!feof(file))
	{
		fscanf(file, "%s", line);
        if(isoperation(line) == 0 && comment != NULL) /* считывание комментариев */
		{
			strcat(comment, line);
			continue;
		}
		if(comment != NULL) /* добавление комментариев в структуру хранения кода */
		{
			addc(&cd, comment);
			comment = NULL;
			printf("%d\t%s\n", cd->index, cd->opr);
		}
		if(strstr(line, "*"))
		{
		if(comment == NULL)
		comment = malloc(sizeof(char)*100);
		strcpy(comment, line);
		continue;
		}		
	    addc(&cd, line);
		printf("%d\t%s\n", cd->index, cd->opr);
	}
	addc(&cd, "NULL");
	printf("%d\t%s\n\n", cd->index, cd->opr);
	fclose(file);
	free(line);
	free(comment);
	move_to(&cd, 0); /* переместить указатель на начало кода */
	printf("#EXECUTION:\n");
	do
	{
		operation(cd->opr);
		cd = cd->next;
	}while(!strstr(cd->opr, "NULL"));
	return 0;
}


/* FUNCTIONS */


void operation(char * line)
{
	if((strstr(line, "inc")) != NULL)
	{
		memory->data++;
	}
	else if((strstr(line, "dec")) != NULL)
	{
		memory->data--;
	}
	else if((strstr(line, "movl")) != NULL)
	{
		if(memory->previous == NULL)
			add(&memory, -1);
		memory = memory->previous;
	}
	else if((strstr(line, "movr")) != NULL)
	{
		if(memory->next == NULL)
			add(&memory, 1);
		memory = memory->next;
	}
	else if((strstr(line, "get")) != NULL)
	{
	    printf("\n>> ");
		scanf("%d", &(memory->data));
	}
	else if((strstr(line, "printc")) != NULL)
	{
		if((int)memory->data >= 0 && (int)memory->data <= 127)
		printf(":: %c\n", (char)((int)(memory->data)));
		else
		printf(":: %d can not be represented as a symbol\n", (int)memory->data);
	}
	else if((strstr(line, "print")) != NULL)
	{
		printf(":: %d\n", memory->data);
	}
	else if((strstr(line, "begin")) != NULL)
	{
		if(memory->data == 0) /* если в текущей ячейке 0, то переместиться на соответствующий end */
		{
			while(!strstr(cd->opr, "end"))
				cd = cd->next;
		}
		else if(memory_stack[stack_pointer] != cd->index)
		{
			memory_stack[stack_pointer] = cd->index;
			stack_pointer++;
		}
	}
	else if((strstr(line, "end")) != NULL)
	{
		if(memory->data != 0) /* если в текущей ячейке не 0, то переместиться на соответствующий begin */
		{
			move_to(&cd, memory_stack[stack_pointer - 1]);
		}	
		else
		{
			memory_stack[stack_pointer - 1] = 0;
				stack_pointer--;
		}	
	}
	else if((strstr(line, "*")) != NULL)
	{
		printf(":: [comment] %s\n", (line+1));
	}
}

int isoperation(char *line)
{
	if(strstr(line, "inc") || strstr(line, "dec") || strstr(line, "movl") || 
	strstr(line, "movr") || strstr(line, "get") || strstr(line, "printc") || 
	strstr(line, "print") || strstr(line, "begin") || strstr(line, "end") || strstr(line, "*")) 
	return 1;
	else return 0;
}

void add(MemoryPtr * list, int np) /* np - next or previous */
{
	if(*list == NULL)
	{
		if((*list = malloc(sizeof(Memory))) == NULL)
		{
			printf("%s%s in add\n", ERROR_MESSAGE, ": memory error");
			exit(-1);
		}
		(*list)->data = 0;
	}
	else
	{
		MemoryPtr new_m;
		if((new_m = malloc(sizeof(Memory))) == NULL)
		{
			printf("%s%s in add\n", ERROR_MESSAGE, ": memory error");
			exit(-1);
		}
		new_m->data = 0;
		if(np == 1) 
		{
			(*list)->next = new_m;
			new_m->previous = (*list);
			new_m->next = NULL;
		}
		else 
		{
			(*list)->previous = new_m;
			new_m->next = (*list);
			new_m->previous = NULL;
		}
	}
}

void addc(CodePtr *list, char *operator)
{
	if((*list) == NULL)
	{
		if((*list = malloc(sizeof(Code))) == NULL)
		{
			printf("%s%s in addc\n", ERROR_MESSAGE, ": memory error");
			exit(-1);
		}
		(*list)->index = 0;
		strcpy((*list)->opr, operator);
		(*list)->prev = NULL;
	}
	else
	{
		CodePtr new_cd;
		if((new_cd = malloc(sizeof(Code))) == NULL)
		{
			printf("%s%s in addc\n", ERROR_MESSAGE, ": memory error");
			exit(-1);
		}
		new_cd->index = ((*list)->index) + 1;
		strcpy(new_cd->opr, operator);
		(*list)->next = new_cd;
		new_cd->prev = (*list);
		new_cd->next = NULL;
		(*list) = new_cd;
	}
}

void move_to(CodePtr *list, int index)
{
	if((*list)->index > index)
		while((*list)->index > index)
			*list = (*list)->prev;
	else if((*list)->index < index)
		while((*list)->index < index)
			*list = (*list)->next;
	else return;
}
