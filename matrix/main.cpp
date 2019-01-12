#include "library.h"



int main()
{
	setlocale(LC_ALL,("RUS"));

	int **matrix;                
	int size_matrix=0;

	input_size_matrix(size_matrix);
	if (size_matrix == EXIT)
	{
		return 0;
	}

	matrix = create_matrix(size_matrix);
	if (!matrix)
	{
		printf_error();
		_getch();
		return 1;
	}
	
	fill_matrix(matrix, size_matrix);
	printf_matrix(matrix, size_matrix);
	delete_matrix(matrix, size_matrix);
	_getch();
	return 0;
}

	
	