/* binary_tree.c
  может принимать в качестве аргумента имя файла, из которого будут считаны инструкции
  для управления деревом
  ./a.out commands
  альтернативный вариант работы: запуск без передачи параметров, т.е. ввод команд
  осуществляется вручную во время работы программы
  ./a.out */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct binaryTree {
	int data;
	struct binaryTree *left;
	struct binaryTree *right;	
};

#define ERROR "error "

typedef struct binaryTree BinTree;
typedef BinTree *BinTreePtr;

void insert(BinTreePtr *, int, char *); /* добавление элемента A, как дочернего от элемента B (B может являться корнем дерева) */
void add_sibling(BinTreePtr *, int, char *); /* добавление элемента A, как ровесник элемента B */
void add_root(BinTreePtr *, int); /* добавить главный (корневой) узел */
void printTree(BinTreePtr *); /* вывести дерево */
void auto_exe(char *); /* выполнение команд из файла */
void commands_manager(); /* ручной ввод команд для управления деревом */
void instructions(); /* вывести инструкции (команды управления деревом) */

int find_register; /* флаг, указывающий, идет ли поиск элемента-ровесника в функции add_sibling */

int main(int argc, char *argv[])
{
	if(argc < 2) /* ручное или автоматическое управление */
	{
		printf("execution with the input of commands...\n");
		commands_manager();
		return 0;
	}
	auto_exe(argv[1]);
	return 0;
}

/* FUNCTIONS */

void insert(BinTreePtr * tree, int value, char *root)
{		
	/* Добавление элемента value как дочернего от корневого узла*/
	if(strstr(root, "root"))
	{
		if((*tree)->left == NULL)
		{
			if(((*tree)->left = malloc(sizeof(BinTree))) == NULL)
				{
					printf("%s \n", ERROR);
					exit(-1);
				}
			((*tree)->left)->data = value;
			((*tree)->left)->left = NULL;
			((*tree)->left)->right = NULL;
		}
		else if((*tree)->right == NULL)
		{
			if(((*tree)->right = malloc(sizeof(BinTree))) == NULL)
				{
					printf("%s \n", ERROR);
					exit(-1);
				}
			((*tree)->right)->data = value;
			((*tree)->right)->left = NULL;
			((*tree)->right)->right = NULL;
		}
		else
		{
			printf("both branches of tree are filled\n");
		}
	}

	/* Добавление элемента value как дочернего от некоторого узла root*/
	else
	{
		if((*tree)->data == atoi(root)) 
		{
			if((*tree)->left == NULL)
		 		{
					if(((*tree)->left = malloc(sizeof(BinTree))) == NULL)
						{
							printf("%s \n", ERROR);
							exit(-1);
						}
					((*tree)->left)->data = value;
					((*tree)->left)->left = NULL;
					((*tree)->left)->right = NULL;
				}
			else if((*tree)->right == NULL)
				{
					if(((*tree)->right = malloc(sizeof(BinTree))) == NULL)
						{
							printf("%s \n", ERROR);
							exit(-1);
						}
					((*tree)->right)->data = value;
					((*tree)->right)->left = NULL;
					((*tree)->right)->right = NULL;
				}
			else
				{
					insert(&((*tree)->left), value, root);
					insert(&((*tree)->right), value, root);
				}
		}
		else
		{
		if((*tree)->right != NULL && (*tree)->left != NULL)
		{
			insert(&((*tree)->left), value, root);
			insert(&((*tree)->right), value, root);
		}
		else if((*tree)->right == NULL && (*tree)->left != NULL)
		{
			insert(&((*tree)->left), value, root);
		}
		else if((*tree)->right != NULL && (*tree)->left == NULL)
		{
			insert(&((*tree)->right), value, root);
		}				
		}
	}
	
}

void add_sibling(BinTreePtr * tree, int value, char *root)
{
		if(find_register == 1) /* если регистр поиска равен 1, т.е. искомый элемент найден и добавлен, то прекратить поиск */
		return;
        char *root2;
		if((root2 = malloc(30)) == NULL)
		{
			printf("%s \n", ERROR);
			exit(-1);
		}
		strcpy(root2, root);
		
		char * branch; /* хранит значение элемента, к которому нужно добавить ровесника */
		branch = strtok(root2, " ");
		branch = strtok(NULL, " ");
		
		if((*tree)->left != NULL && (*tree)->right == NULL && ((*tree)->left)->data == atoi(branch))
			{
				if(((*tree)->right = malloc(sizeof(BinTree))) == NULL)
				{
					printf("%s \n", ERROR);
					exit(-1);
				}
				((*tree)->right)->data = value;
				((*tree)->right)->left = NULL;
				((*tree)->right)->right = NULL;
				find_register = 1;
			}
		else if((*tree)->right != NULL && (*tree)->left == NULL && ((*tree)->right)->data == atoi(branch))
			{
				if(((*tree)->left = malloc(sizeof(BinTree))) == NULL)
				{
					printf("%s \n", ERROR);
					exit(-1);
				}
				((*tree)->left)->data = value;
				((*tree)->left)->left = NULL;
				((*tree)->left)->right = NULL;
				find_register = 1;
			}
		else if((*tree)->right == NULL && (*tree)->left == NULL)
		{
			return;
		}
		/* рекурсивный вызов функции add_sibling, если соотвествующие правая и левая ветка не пусты */
		else if((*tree)->right != NULL && (*tree)->left != NULL)
		{
			add_sibling(&((*tree)->left), value, root);
			add_sibling(&((*tree)->right), value, root);
		}
		else if((*tree)->right == NULL && (*tree)->left != NULL)
		{
			add_sibling(&((*tree)->left), value, root);
		}
		else if((*tree)->right != NULL && (*tree)->left == NULL)
		{
			add_sibling(&((*tree)->right), value, root);
		}			 
}

void add_root(BinTreePtr * tree, int value)
{
	/* Если дерево пустое, то создать корневой узел*/
	if((*tree) == NULL)
	{
		printf("Creating new tree...\n");
		if(((*tree) = malloc(sizeof(BinTree))) == NULL)
		{
			printf("%s \n", ERROR);
			exit(-1);
		}
		(*tree)->data = value;
		(*tree)->right = NULL;
		(*tree)->left = NULL;
		return;
	}
	
	/* Добавление нового корневого узла в непустое дерево */
	else
	{
		BinTreePtr new_tree;
		if((new_tree = malloc(sizeof(BinTree))) == NULL)
		{
			printf("%s \n", ERROR);
			exit(-1);
		}
		new_tree->data = value;
		new_tree->right = NULL;
		new_tree->left = *tree;
		(*tree) = new_tree;
	}
}

void printTree(BinTreePtr *tree)
{
	if((*tree) == NULL)
		return;
	printf("%d\t", (*tree)->data);
	printTree(&((*tree)->left));
	printTree(&((*tree)->right));
}

void auto_exe(char *filename)
{	
	/* ARGS */
	
	FILE *file;
	BinTreePtr tree;
	tree = NULL;
	char * command, *root;
	int value;	
	
	/* EXECUTION */
	
	printf("execution with commands from file: \"%s\"...\n", filename);	
	if((file = fopen(filename, "r")) == NULL)
	{
		printf("%s\n", ERROR);
		exit(-1);
	}
	if((command = malloc(200)) == NULL)
	{
		printf("%s\n", ERROR);
		exit(-1);
	}
	if((root = malloc(200)) == NULL)
	{
		printf("%s\n", ERROR);
		exit(-1);
	}
    while(!feof(file)) /* читаем файл с командами */
	{
		find_register = 0; /* регистр поиска в 0 */
		fscanf(file, "%s", command);
		printf("--> %s ", command);
		if(strstr(command, "root")) /* если очередная команда это root, то вызвать add_root */
		{
			fscanf(file, "%s", command);
			printf("%s\n", command);
			value = atoi(command);
			add_root(&tree, value);
		}
		else if(strstr(command, "sibling"))
		{
			fscanf(file, "%s", command);
			printf("%s ", command);
			value = atoi(command);
			fscanf(file, "%s", command);
			printf("%s\n", command);
			strcpy(root, "sibling ");
			strcat(root, command);
			add_sibling(&tree, value, root);
			if(find_register == 0)
			{
				printf("free branch with a value of %s  not founded\n", command);
			}
		}
		else if(strstr(command, "show"))
		{
			fscanf(file, "%s", command);
			printf("%s\n", command);
			printTree(&tree); 
		}
		else
		{
			value = atoi(command);
			fscanf(file, "%s", command);
			printf("%s\n", command);
			insert(&tree, value, command);
		}		
	}
	printf("\n");
	printf("end of program\n");
}

/* работа этой функции аналогична работе функции auto_exe(),
 только команды не читаются из файла, а вводятся вручную */
void commands_manager()
{
 	BinTreePtr tree;
	tree = NULL;
	char command[50] = "";
	char *root;
	if((root = malloc(50)) == NULL)
	{
		printf("%s \n", ERROR);
		exit(-1);		
	}
	int value;
	instructions();
	printf("Enter your commands:\n\n");
    while(1 && 1)
	{
		find_register = 0;
		printf(">>");
		fgets(command, 50, stdin);
		root = strtok(command, " ");
		if(strstr(root, "root"))
		{
			root = strtok(NULL, " ");
			value = atoi(root);
			add_root(&tree, value);
		}
		else if(strstr(root, "sibling"))
		{
			root = strtok(NULL, " ");
			value = atoi(root);
			root = strtok(NULL, " ");
			strcpy(command, "sibling ");
			strcat(command, root);
			add_sibling(&tree, value, command);
			if(find_register == 0)
			{
				printf(" free branch with a value of %s not founded\n", command);
			}
		}
		else if(strstr(root, "show"))
		{
			printTree(&tree); 
			printf("\n");
		}
		else if(isdigit(root[0]))
		{
			value = atoi(command);
			root = strtok(NULL, " ");
			insert(&tree, value, root);
		}
		else if(strstr(command, "end"))
		{
			printf("end of program\n");
			return;
		}
		else
		{
			printf("Incorrect command!\ntry again...\n");
		}
	}
	return;
}

void instructions()
{
	printf("\nCOMMANDS:");
	printf("\n************************************\n");
	printf("root <value>   -   add a root node with a value of <value>\n");
	printf("<value> root  -   add a new node with a value of <value> as a child from the root\n");
	printf("<value1> <value2>   -   add a new node with a value of <value1> as a child from the <value2>\n");
	printf("sibling <value1> <value2>   -   add a new node with value of <value1> as sibling with a node with value of <value2>\n");
	printf("show    -    show the tree's elements\n");
	printf("************************************\n\n");
}