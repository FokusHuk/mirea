/*ffile.c
аргументы передаются через командную строку в main
аргументы имеют вид: "X" "Y", где X - имя файла, в котором осуществляется
поиск, Y - строка (или символ), которую необходимо найти
./a.out file_for_reading.c "some string"
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char * argv[])
{
	FILE *file;
	int line, position, isword, index, ff;
	char symbol;
	/*
	line, position - текущая позиция в  файле
	isword - счетчик для поиска длинных строк
	index - счетчик для строки, которую мы ищем
	ff - счетчик показывающий, что строка найдена в файле
	*/
	line = 1;
	position = 1;
	
	ff = 0;
	isword = 0;
	index = 0;
	if((file = fopen(argv[1]	, "r")) == NULL)
		{
			printf("error :: file could not be opened\n");
			exit(-1);
		}
	while(!feof(file))
	{
		symbol = getc(file);	
		if(isword == 1)
		{
			index++;
			if((int)strlen(argv[2]) == index)
			{
				index = 0;
				isword = 0;
				printf("%d:%d %s\n", line, position - (int)strlen(argv[2]), argv[2]);
				ff = 1;
			}
			else if(symbol != argv[2][index])
			{
				index = 0;
				isword = 0;
			}
		}
		else {
		if(symbol == argv[2][0])
			isword = 1;
		}
		
		if(symbol == '\n')
		{
			line++;
			position = 1;
		}
		else position++;
	}
	fclose(file);
	if(ff == 0)
		printf("%s could not be found in %s\n", argv[2], argv[1]);
	return 0;
}