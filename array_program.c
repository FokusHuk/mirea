// array_program.c
// не принимает аргументов
// ./a.out


#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX_NUMBER 20 // максимальное значение элемента матрицы
#define MIN_NUMBER MAX_NUMBER/2 // модуль минимального значения элемента матрицы
#define MAX_M 1000 // максимальное кол-во строк матрицы
#define MAX_N 1500 // максимальное кол-во столбцов матрицы

int M , N, C; // M - кол-во строк, N - кол-во столбцов первой матрицы; С - кол-во столбцов второй матрицы

void reverse_first_last(int [][N]); // меняет местами первую и последнюю строки первой матрицы, затем меняет порядок элементов в ней на противоположный
void print_array(int [][N]); // выводит элементы первой матрицы
void delete_minlc(int [][N], int[][N-1]); // находит наименьший элемент в первой матрице, и удаляет строку и столбец на пересечении которых он находится
void print_del_array(int [][N - 1]); // выводит получившуюся матрицу
void create_new_array(int[][C]); // создает новую матрицу (элементы вводит пользователь) и выводит ее
void multiplication_of_arrays(int [][N-1], int [][C]); // перемножает первую и вторую матрицы

int main()
{
	srand(time(0));
	int i, j;
	while(M < 4 || N < 5 || M > MAX_M || N > MAX_N)
	{
		printf("enter m and n:\n");
		scanf("%d%d", &M, &N);
	}
	int array[M][N]; // ПЕРВАЯ МАТРИЦА (с произвольными элементами)
	printf("\nARRAY:\n");
	for(i = 0; i < M; i ++)
		for(j = 0; j < N; j++)
			{
				array[i][j] = rand() % MAX_NUMBER - MIN_NUMBER;
				printf("%3d\t", array[i][j]);
				if(j == N - 1) printf("\n");
			}
	printf("\nREVERSE ARRAY:\n");
	reverse_first_last(array);
	print_array(array);
	
	int del_array[M-1][N-1]; // матрица, на порядок меньше первой
	delete_minlc(array, del_array);
	print_del_array(del_array);
	
	printf("NEW ARRAY CREATE\n-> enter number of columns for new array: ");
	scanf("%d", &C);
	int new_array[N-1][C]; // ВТОРАЯ МАТРИЦА
	create_new_array(new_array);
	
	multiplication_of_arrays(del_array, new_array);
	printf("end of program\n");
	return 0;
}


//FUNCTIONS


void reverse_first_last(int array[][N])
{
	int i, j;
	for(i = 0; i < N; i ++)
	{
		array[0][i] += array[M - 1][i];
		array[M - 1][i] = array[0][i] - array[M - 1][i];
		array[0][i] -= array[M - 1][i];
	}
	
	for(i = 0, j = N - 1; i < N/2; i ++, j--)
	{
		array[0][i] += array[0][j];
		array[0][j] = array[0][i] - array[0][j];
		array[0][i] -= array[0][j];
		
		array[M - 1][i] += array[M - 1][j];
		array[M - 1][j] = array[M - 1][i] - array[M - 1][j];
		array[M - 1][i] -= array[M - 1][j];
	}
}

void print_array(int array[][N])
{
	int i, j;
	for(i = 0; i < M; i ++)
		for(j = 0; j < N; j++)
			{
				printf("%3d\t", array[i][j]);
				if(j == N - 1) printf("\n");
			}
	printf("\n");
}

void delete_minlc(int array[][N], int del_array[][N-1])
{
	int line, column, minimal, i, j;
	minimal = MAX_NUMBER+1;
	
	for(i = 0; i < M; i ++)
		for(j = 0; j < N; j++)
			{
				if(array[i][j] < minimal)
				{
					minimal = array[i][j];
					line = i;
					column = j;
				}
			}
	printf("minimal element = array[%d][%d]\nline %d and column %d will be deleted\n\n", line, column, line, column);
	
	for(i = 0; i < M - 1; i ++)
		for(j = 0; j < N - 1; j ++)
		{
			if(i < line)
			{
				if(j < column) 
					del_array[i][j] = array[i][j];
				else 
					del_array[i][j] = array[i][j+1];
			}
			else
			{
				if(j < column) 
					del_array[i][j] = array[i+1][j];
				else 
					del_array[i][j] = array[i+1][j+1];
			}
		}
}

void print_del_array(int del_array[][N - 1])
{
    int i, j;
	printf("ARRAY AFTER DELETE:\n");
	for(i = 0; i < M - 1; i ++)
		for(j = 0; j < N - 1; j++)
			{
				printf("%3d\t", del_array[i][j]);
				if(j == N - 2) printf("\n");
			}
	printf("\n");
}

void create_new_array(int new_array[][C])
{
	printf("-> fill in new array:\n");
	int inpt, i, j;
	for(i = 0;  i < N - 1; i ++)
		for(j = 0; j < C; j ++)
			{
				printf("new_array[%d][%d] = ", i, j);
				scanf("%d", &inpt);
				while(inpt > MAX_NUMBER || inpt < -MIN_NUMBER)
				{
					printf("incorrect!(array[i][j] -> [%d;%d]\nnew_array[%d][%d] = ", -MIN_NUMBER, MAX_NUMBER, i, j);
				    scanf("%d", &inpt);
				}
				new_array[i][j] = inpt;
			}
	printf("\nNEW ARRAY:\n");		
    for(i = 0;  i < N - 1; i ++)
		for(j = 0; j < C; j ++)
			{
				printf("%3d\t", new_array[i][j]);
				if(j == C - 1) printf("\n");
			}
	printf("\n");
}

void multiplication_of_arrays(int del_array[][N-1], int new_array[][C])
{
	int finally_array[M-1][C]; // МАТРИЦА, ПОЛУЧИВШАЯСЯ В РЕЗУЛЬТАТЕ УМНОЖЕНИЯ ПЕРВОЙ И ВТОРОЙ МАТРИЦ
	int i, j, k;
	for(i = 0; i < M - 1; i ++)
		for(j = 0; j < C; j++)
			finally_array[i][j] = 0;
	for(i = 0; i < M - 1; i ++)
		for(j = 0; j < C; j ++)
			for(k = 0; k < N - 1; k ++)
			{
				finally_array[i][j] += del_array[i][k] * new_array[k][j];
			}
	printf("FINALLY ARRAY:\n");
	for(i = 0; i < M - 1; i ++)
		for(j = 0; j < C; j++)
			{
				printf("%6d\t", finally_array[i][j]);
				if(j == C - 1) printf("\n");
			}
	printf("\n");
}
