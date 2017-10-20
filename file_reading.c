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
	int num_int; /* целое число из пакета данных */
	char string[256]; /* стркоа из пакета данных */
	float num_fl; /* вещественное число из пакета данных */
	char readstr[25]; /* для считывания длинной строки из файла */
	int size;
	size = 0;
	
	if(argc < 2)
	{
	printf("enter file's name:\n>> ");
	scanf("%s", file_name);
	}
	strcpy(file_name, argv[1]);	
	if((file = fopen(file_name, "r")) == NULL)
	{
		printf("cannot open file\n");
		exit(-1);
	}
	printf("\n%s\t\t\t\t\t%s\t\t\t\t\t\t%s\n\n", "INTEGER", "STRING", "FLOAT");
	while(!feof(file))
	{
		fscanf(file, "%d%s", &num_int, string);
		size += strlen(string);
		fscanf(file, "%s", readstr);
		while(!isdigit(readstr[0]) && !isdigit(readstr[strlen(readstr)-1]))
		{
			strcat(string, " ");
			strcat(string, readstr);
			size += strlen(readstr) + 1;
			fscanf(file, "%s", readstr);
		}
		num_fl = atof(readstr);
		printf("%-10d\t%-70s %-10.4f\n", num_int, string, num_fl);
		size += 10;
	}
	fclose(file);
	printf("\nSize of file = %d byte\n", size);
	return 0;
}
