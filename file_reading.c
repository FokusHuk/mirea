/* file_reading.c 
 аргументы передаются через командную строку в main 
 аргументы имеют вид: "X" или X, где X - имя файла 
 ./a.out file     */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


int main(int argc, char *argv[])
{
	FILE *file;
	char file_name[50];
	char *str; /* для считывания длинной строки из файла */
	int size, count;
	size = 0;
	count = 0;
	
	if(argc < 2)
	{
	printf("enter file's name:\n>> ");
	scanf("%s", file_name);
	}
	else
	strcpy(file_name, argv[1]);	
	if((file = fopen(file_name, "r")) == NULL)
	{
		printf("cannot open file\n");
		exit(-1);
	}
	if((str = malloc(100)) == NULL)
	{
		printf("memory error\n");
		exit(-1);
	}
	printf("\n%s\t\t\t\t\t%s\t\t\t\t\t\t%s\n\n", "INTEGER", "STRING", "FLOAT");
	while(!feof(file))
	{
		fscanf(file, "%s", str);
		if(str[0] == ' ' || str[0] == '|')
			{
				size += strlen(str);
				continue;
			}
		if(count == 0)
		{
			size += 4;
			printf("%-30s ", str);
			count++;
		}
		else if(count == 1)
		{
			size += strlen(str);
			printf("%-30s ", str);
			count++;
		}
		else if(count == 2)
		{
			size += strlen(str);
			printf("%30s\n", str);
			count = 0;
		}
	}
	fclose(file);
	printf("\nSize of file = %d byte\n", size);
	return 0;
}