#include<time.h>
#include<stdio.h>

void copy_arr(int *arr_one, int *arr_two, int size)//копирования массива
{
	for(int i=0; i<size; i++)
	{
		*(arr_one + i) = *(arr_two+ i);
	}
}

void check_mas(int *arr, int size)//проверка отсортированого массива 
{
	for(int i=0; i<size - 1; i++)
	{
		if(*(arr+i) > *(arr + i+1))
		{
			printf("\n\nМассив не отсортирован");
			return;
		}
	}
	printf("\n\nМассив отсортирован");
}

void booble_sort(int *arr,double *zeit, int size)//сортировка пузырьком 
{
	int temp=0;
	clock_t start;
	clock_t stop;
	start = clock ();
	for(int i=0; i<size - 1; i++)
	{
		for(int j=0; j<size - 1-i; j++)
		{
			if(*(arr + j) > *(arr + j+1))
			{
				temp = *(arr + j);
				*(arr + j) = *(arr + j+1);
				*(arr + j+1) = temp;
			}
		}
	}
	stop = clock();	
	*zeit=stop-start;
}

void my_qsort(int *arr, int left, int right)//сортировка методом Хоара
{
	int i=left;
	int j=right;
	int temp=0;
	int centr=0;

	centr = arr[(left + right) / 2];
	do
	{
		while (*(arr + i) < centr) i++;
		while (*(arr + j) > centr)j--;

		if (i <= j)
		{
			temp = *(arr + i);
			*(arr + i) = *(arr + j);
			*(arr + j) = temp;
			i++;
			j--;
		}
	}while (i <= j);
	
	if (i < right)
	{
		my_qsort(arr, i, right);
	}
	
	if (j > left)
	{
		my_qsort(arr, left, j);
	}
}
void qsort_down(int *mas, int left, int right)
{
	int i = left;
	int j = right;
	int centr = 0;
	int temp = 0;

	centr = mas[(left + right) / 2];

	do
	{
		while (mas[i] > centr) i++;
		while (mas[j] < centr) j--;

		if (i <= j)
		{
			temp = mas[i];
			mas[i] = mas[j];
			mas[j] = temp;

			i++;
			j--;
		}

	} while (i <= j);
	
	if (i < right)
	{
		qsort_down(mas, i, right);
	}

	if (j > left)
	{
		qsort_down(mas, left, j);
	}
}
void selection_sort(int *arr,double *zeit, int size)// сортировка выбором
{
	int temp=0;
	clock_t start;
	clock_t stop;
	start = clock ();
	for (int i=0; i < size - 1; i++) 
	{
        int min = i;
		for (int j=i+1; j<size; j++) 
		{
			if (*(arr + min) > *(arr + j))
			{
				min = j;
			}
		}
		if(min!=i)
		{
			temp = *(arr + i);
			*(arr + i) = *(arr + min);
			*(arr + min) = temp;
		}
	}
	stop = clock();
	*zeit=stop-start;
}

void sort_sheiker(int *arr,double *zeit, int size)//сортировка шейкером
{
	int	left=0; 
	int	right=0;
	int last=0;
	int temp=0;
	clock_t start;
	clock_t stop;
	
	left=1;
	right = size-1;
	last = size-1;

	start = clock ();
	do
	{
		for(int i = right; i >= left; i--)
		{
			if(*(arr + i-1) > *(arr + i))
			{
				temp = *(arr + i);
				*(arr + i) = *(arr + i-1);
				*(arr + i-1) = temp;
				last = i;
			}
		}

		left = last + 1;

		for(int j = left; j <= right; j++)
		{
			if(*(arr + j-1) > *(arr + j))
			{
				temp = *(arr + j);
				*(arr + j) = *(arr + j-1);
				*(arr + j-1) = temp;
				last = j;
			}
		}
		
		right = last-1;
	
	}while(left <= right);
	stop = clock();
	*zeit=stop-start;
}

void sort_Shell(int *arr,double *zeit, int size)//сортировка методом Шелла
{
	int temp=0;
	int flg=0;
	int step=0;
	int j=0;
	clock_t start;
	clock_t stop;

	start = clock ();
	for(step = size/2; step>0; step/=2)
	{
		do
		{
			flg=0;
			j=step;
			for(int i=0; j<size; i++, j++)
			{
				if(*(arr + i)>*(arr + j))
				{
					temp = *(arr + j);
					*(arr + j) = *(arr + i);
					*(arr + i) = temp;
					flg=1;
				}
			}
		}while(flg==1);
	}
	stop = clock();
	*zeit=stop-start;
}

void insert_sort(int *mas1, double *zeit, int razm)
{
	clock_t start;
	clock_t stop;
	int temp = 0;
	int itemp = 0;

	start = clock();
	for (int i = 1; i < razm; i++)
	{
		temp = *(mas1 + i);
		itemp = i - 1;
		while (itemp >= 0 && *(mas1 + itemp) > temp)
		{
			*(mas1 + itemp + 1) = *(mas1 + itemp);
			*(mas1 + itemp) = temp;
			itemp--;
		}
	}
	stop = clock();
	*zeit = stop - start;
}

void Bender_sort_up(int *mas, int size, double* zeit)
{
	clock_t start;//начало работы сортировки
	clock_t stop;//конец работы сортировки
	int temp = 0;
	int index_min = 0;
	int index_max = 0;
	int j = 0;

	start = clock();

	do
	{
		index_min = j;
		index_max = j;

		for (int i = j + 1; i < size; i++)
		{
			if (*(mas + index_max)<*(mas + i))
			{
				*(mas + index_max) = *(mas + i);
				index_max = i;
			}

			if (*(mas + index_min)>*(mas + i))
			{
				*(mas + index_min) = *(mas + i);
				index_min = i;
			}
		}

		if (index_max != size - 1)
		{
			temp = *(mas + index_max);
			*(mas + index_max) = *(mas + size - 1);
			*(mas + size - 1) = temp;
		}

		if (index_min == size - 1)
			index_min = index_max;

		if (index_min != j)
		{
			temp = *(mas + index_min);
			*(mas + index_min) = *(mas + j);
			*(mas + j) = temp;
		}

		size--;
		j++;


	} while (size > 0 && j<size);

	stop = clock();

	*zeit = stop - start;

}

void Bender_sort_up_rec(int *mas,int origin, int size)
{
	int temp = 0;
	int index_min = origin;
	int index_max = origin;

	for (int i = origin + 1; i < size; i++)
	{
		if (*(mas + index_max)<*(mas + i))
		{
			*(mas + index_max) = *(mas + i);
			index_max = i;
		}

		if (*(mas + index_min)>*(mas + i))
		{
			*(mas + index_min) = *(mas + i);
			index_min = i;
		}
	}

	if (index_max != size - 1)
	{
		temp = *(mas + index_max);
		*(mas + index_max) = *(mas + size - 1);
		*(mas + size - 1) = temp;
	}

	if (index_min == size - 1)
		index_min = index_max;

	if (index_min != origin)
	{
		temp = *(mas + index_min);
		*(mas + index_min) = *(mas + origin);
		*(mas + origin) = temp;
	}

	size--;
	origin++;

	if (origin < size)
		Bender_sort_up_rec(mas, origin, size);
}