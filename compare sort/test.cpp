#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<locale>
#include"prot_sort.h"

int main()
{
	setlocale(LC_ALL,("RUS"));
	int *arr;//�������� ������
	int *temp_arr;//������ ������ 
	int left=0;//����� ������� ��� �����
	int right=0;//������ ������� ��� �����
	double *zeit=0;//��������� �� ����� ����������
	double time_sort=0;//����� ����������
	int size=0;//������ �������
	clock_t start;//������ ������ ����������
	clock_t stop;//����� ������ ����������

	zeit=&time_sort;

	printf("������� ����e� �������:");
	while(scanf_s("%d", &size)!=1)
	{
		rewind(stdin);
		printf("\n��������� ����:");
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
	printf("������ ������ �� %d ��������� ", size);

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
	printf("\n����� ���������� ������� �����:%lf ������.", *zeit/CLK_TCK);
	
	copy_arr(temp_arr, arr, size);
	selection_sort(temp_arr, zeit, size);
	check_mas(temp_arr, size);
	printf("\n����� ���������� ������� ������:%lf ������.", *zeit/CLK_TCK);
	
	copy_arr(temp_arr, arr, size);
	sort_sheiker(temp_arr, zeit, size);
	check_mas(temp_arr, size);
	printf("\n����� ���������� ������� �������:%lf ������.", *zeit/CLK_TCK);

	copy_arr(temp_arr, arr, size);
	sort_Shell(temp_arr, zeit, size);
	check_mas(temp_arr, size);
	printf("\n����� ���������� ������� �����:%lf ������.", *zeit/CLK_TCK);

	copy_arr(temp_arr, arr, size);
	insert_sort(temp_arr, zeit, size);
	check_mas(temp_arr, size);
	printf("\n����� ���������� ������� �������:%lf ������.", *zeit / CLK_TCK);

	copy_arr(arr, temp_arr, size);
	Bender_sort_up(temp_arr, size, zeit);
	check_mas(temp_arr, size);
	printf("\n����� ���������� ������� �������:%lf ������.", *zeit / CLK_TCK);

	booble_sort(arr, zeit, size);
	check_mas(arr, size);
	printf("\n����� ���������� ���������:%lf ������.", *zeit/CLK_TCK);
	
	free(arr);
	free(temp_arr);
	printf("\n\n��� ������ ������� ����� ������.");
	_getch();
	return 0;
}