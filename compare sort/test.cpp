#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<locale>
#include"prot_sort.h"

int main()
{
	setlocale(LC_ALL,("RUS"));
	int *arr;//основной массив
	int *temp_arr;//второй массив 
	int left=0;//левая граница для Хоара
	int right=0;//правая граница для Хоара
	double *zeit=0;//указатель на время сортировки
	double time_sort=0;//время сортировки
	int size=0;//размер массива
	clock_t start;//начало работы сортировки
	clock_t stop;//конец работы сортировки

	zeit=&time_sort;

	printf("Введите размeр массива:");
	while(scanf_s("%d", &size)!=1)
	{
		rewind(stdin);
		printf("\nПовторите ввод:");
	}

	arr = (int*)malloc(size*sizeof(int));
	if(arr==nullptr)
	{
		return 0;
	}

	temp_arr=(int*)malloc(size*sizeof(int));
	if(temp_arr==nullptr)
	{
		free(arr);
		return 0;
	}

	system("cls");
	printf("Создан массив на %d элементов ", size);

	srand((unsigned)time(NULL));
	for(int i=0; i<size; i++)
	{
		arr[i]=-10+rand()%20;
	}
	

	right = size - 1;
	copy_arr(temp_arr, arr, size);
	start = clock();
	my_qsort(temp_arr, left,right);
	stop = clock();
	*zeit=stop-start;
	check_mas(temp_arr, size);
	printf("\nВремя сортировки методом Хоара:%lf секунд.", *zeit/CLK_TCK);
	
	copy_arr(temp_arr, arr, size);
	selection_sort(temp_arr, zeit, size);
	check_mas(temp_arr, size);
	printf("\nВремя сортировки методом выбора:%lf секунд.", *zeit/CLK_TCK);
	
	copy_arr(temp_arr, arr, size);
	sort_sheiker(temp_arr, zeit, size);
	check_mas(temp_arr, size);
	printf("\nВремя сортировки методом Шейкера:%lf секунд.", *zeit/CLK_TCK);

	copy_arr(temp_arr, arr, size);
	sort_Shell(temp_arr, zeit, size);
	check_mas(temp_arr, size);
	printf("\nВремя сортировки методом Шелла:%lf секунд.", *zeit/CLK_TCK);

	copy_arr(temp_arr, arr, size);
	insert_sort(temp_arr, zeit, size);
	check_mas(temp_arr, size);
	printf("\nВремя сортировки методом вставок:%lf секунд.", *zeit / CLK_TCK);

	copy_arr(arr, temp_arr, size);
	Bender_sort_up(temp_arr, size, zeit);
	check_mas(temp_arr, size);
	printf("\nВремя сортировки методом Бендера:%lf секунд.", *zeit / CLK_TCK);

	booble_sort(arr, zeit, size);
	check_mas(arr, size);
	printf("\nВремя сортировки пузырьком:%lf секунд.", *zeit/CLK_TCK);
	
	free(arr);
	free(temp_arr);
	printf("\n\nДля выхода нажмите любую кнопку.");
	_getch();
	return 0;
}