#include "library.h"

int find_simple_number(int value)
{
	int count = 0;

	value++;

	for (int i = value;; i++)
	{
		count = 0;
		for (int j = 1; j <= value; j++)
		{
			if (i%j == 0)
			{
				count++;
			}
			if (count > 2)
			{
				value++;
				break;
			}
		}

		if (count == 2)
		{
			return value;
		}
	}
}

void input_size_matrix(int &size_matrix)
{
	printf("Введите размер матрицы(или ноль для выхода):");
	while (scanf_s("%d", &size_matrix) != 1 || size_matrix < 0)
	{
		rewind(stdin);
		printf("Повторите ввод:");
	}
}

int** create_matrix(const int size_matrix)
{
	int **matrix = nullptr;
	matrix = (int**)calloc(size_matrix,sizeof(int*));
	if (!matrix)
	{
		return nullptr;
	}
	for (int index = 0;index < size_matrix; index++)
	{
		matrix[index] = (int*)calloc(size_matrix, sizeof(int));
		if (!matrix[index])
		{
			delete_matrix(matrix, index-1);
			return nullptr;
		}
	}
	return matrix;
}

void delete_matrix(int **matrix, const int size_matrix)
{
	for (int index = 0; index < size_matrix; index++)
	{
		free(matrix[index]);
	}
	free(matrix);
}

void printf_matrix(const int* const* const matrix, const int size_matrix)
{
	for (int index_row = 0; index_row<size_matrix; index_row++)			
	{
		printf("\n\n");
		for (int index_col = 0; index_col<size_matrix; index_col++)
		{
			printf("%5d", matrix[index_row][index_col]);
		}
	}
}

void fill_matrix(int* const* const matrix, const int size_matrix)
{
	int count_number_matrix = 0;     //количество чисел в матрице
	int row = 0;
	int col = 0;
	int direction = 0;           //направление движения
	int simple_number = 1;
	int turnover = 1;            //оборот заполнения матрицы

	count_number_matrix = size_matrix*size_matrix;

	while (count_number_matrix != 0)
	{
		count_number_matrix--;
		switch (direction)
		{
		case RIGHT:
			matrix[row][col] = simple_number = find_simple_number(simple_number);
			col++;
			if (col + turnover == size_matrix)
			{
				direction = DOWN;
			}
			break;

		case DOWN:
			matrix[row][col] = simple_number = find_simple_number(simple_number);
			row++;
			if (row + turnover == size_matrix)
			{
				direction = LEFT;
			}
			break;

		case LEFT:
			matrix[row][col] = simple_number = find_simple_number(simple_number);
			col--;
			if (col == 0 || *(*(matrix + row) + col - 1) != 0)
			{
				direction = UP;
			}
			break;

		case UP:
			matrix[row][col] = simple_number = find_simple_number(simple_number);
			row--;
			if (row - turnover == 0)
			{
				direction = RIGHT;
				turnover++;
			}
			break;
		}
	}
}

void printf_error()
{
	printf("\n\nНедостаточно памяти. Попробуйте позже.");
}
