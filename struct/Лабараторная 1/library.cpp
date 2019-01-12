#include "library.h"

void(*sort_name[])(state *, int, int *) = { sort_state_name_up ,sort_state_name_down };//��������� �� ������ ���������� �� ��������
void(*sort_population[])(state *, int, int *) = { sort_state_population_up ,sort_state_population_down };//��������� �� ������ ���������� �� ���������
void(*sort_economy[])(state *, int, int *) = { sort_state_economy_up ,sort_state_economy_down };//��������� �� ������ ���������� �� ������ �������������� ��������
void(*sort_ty_parametr[])(state *, int *) = { sort_name_population ,sort_name_economy , sort_population_economy };//��������� �� ������ ���������� �� ���� �����

state * creat_struct(int *state_count)  //�������� ������� ��������
{	
	state *mas;

	mas = (state *)malloc(*state_count * sizeof(state));

	return mas;
}

void del_struct(state *mas)
{
	free(mas);
}

state * del_state(state *mas, int *state_count) //�������� ��������� �� �������
{
	state temp;
	state *new_mas;
	int state = 0;

	printf("�������� �����������, ������� ������ �������:\n");

	for (int i = 0; i < *state_count; i++)
		printf("%d.%s\n", i + 1, mas[i].name);

	printf("%d.����� � ������� ����.", *state_count + 1);

	printf("\n\n\n���� �������:");

	rewind(stdin);
	while (scanf_s("%d", &state) != 1 || state <= 0 || state > *state_count + 1)
	{
		rewind(stdin);
		printf("��������� ����:");
	}

	if (state == *state_count + 1)//����� � ����
	{
		return mas;
	}
	else
	{
		state--;

		for (int i = state; i < (*state_count) - 1; i++)
		{
			temp = mas[i];
			mas[i] = mas[i + 1];
			mas[i + 1] = temp;
		}
	}
	
	(*state_count)--;

	new_mas = creat_struct(state_count);
	if (new_mas == NULL)
	{
		system("cls");

		printf("������. ������� ����������� �� ��������.");
		printf("\n\n����� ����� � ������� ����, ������� ����� ������.");

		_getch();
		return mas;
	}

	for (int i = 0; i < *state_count; i++)
	{
		new_mas[i] = mas[i];
	}

	del_struct(mas);

	return new_mas;
}

void input_info(state &state) //��������� ���������� � �����������
{
	system("cls");

	int menu = 0;
	int step = 0;//���������� ��� �������� ���������� �����

	for (;;)
	{
		system("cls");

		printf("���������� �����������:%s.\n\n", state.name);
		printf("1.�������� �������� ������.\n");
		printf("2.�������� ������� ���������.\n");
		printf("3.�������� ���������.\n");
		printf("4.� ������� ����.");
		printf("\n\n\n���� �������:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu > 6 || menu < 1)
		{
			rewind(stdin);
			printf("��������� ����:");
		}

		switch (menu)
		{
		case 1:

			system("cls");

			printf("������� �������� �����������(��������� �������� �������):");

			rewind(stdin);
			fgets(state.name, SIZE_NAME, stdin);
			while (state.name[step] != '\n')
			{
				if (state.name[step] < 'A' || state.name[step] > 'Z')
				{
					printf("��������� ����:");

					fgets(state.name, SIZE_NAME, stdin);

					step = 0;
				}
				else
					step++;
			}

			state.name[step] = '\0';
		
			break;

		case 2:

			system("cls");

			printf("1.�������� �� ����������������.\n");
			printf("2.�������� �� ��������������.\n");
			printf("3.�������� �� ������������������.\n");
			printf("4.�����.");
			printf("\n\n\n���� �������:");

			rewind(stdin);
			while (scanf_s("%d", &menu) != 1 || menu > 4 || menu < 1)
			{
				rewind(stdin);
				printf("��������� ����:");
			}

			if (menu == 1)
				state.economy = DO_IND;

			else if (menu == 2)
				state.economy = IND;

			else if (menu == 3)
				state.economy = POST_IND;
			
			break;
		
		case 3:

			system("cls");

			printf("������� ����� ��������:");

			rewind(stdin);
			while (scanf_s("%d", &state.population) != 1 || state.population<0)
			{
				rewind(stdin);
				printf("��������� ����:");
			}

			break;

		case 4: return;

		}
	}
}

void input_new_info(state *mas, int *state_count)
{
	int economy = 0;

	system("cls");

	printf("���������� ������� ���������:\n\n");
	printf("1.����������������.\n");
	printf("2.��������������.\n");
	printf("3.������������������.\n");
	printf("\n\n\n���� �������:");

	rewind(stdin);
	while (scanf_s("%d", &economy) != 1 || economy > 3 || economy < 1)
	{
		rewind(stdin);
		printf("��������� ����:");
	}

	if (economy == 1)
		mas[*state_count - 1].economy = DO_IND;

	else if (economy == 2)
		mas[*state_count - 1].economy = IND;

	else if (economy == 3)
		mas[*state_count - 1].economy = POST_IND;

	system("cls");

	printf("������� ��������� ������:");

	rewind(stdin);
	while (scanf_s("%d", &mas[*state_count - 1].population) != 1 || mas[*state_count - 1].population<0)
	{
		rewind(stdin);
		printf("��������� ����:");
	}
}

state * creat_new_state(state *mas, int *state_count) //�������� ������ �����������
{
	system("cls");

	int economy = 0;
	int step = 0;
	state *new_mas;

	(*state_count)++;

	new_mas = creat_struct(state_count);
	if (new_mas == NULL)
	{
		system("cls");

		printf("������. �������� ����������� �� ��������.");
		printf("\n\n����� ����� � ������� ����, ������� ����� ������.");

		_getch();
		return mas;
	}

	for (int i = 0; i < *state_count; i++)
	{
		new_mas[i] = mas[i];
	}

	del_struct(mas);

	rewind(stdin);

	printf("��e���� �������� �����������(��������� �������� �������):");

	fgets(new_mas[*state_count - 1].name, SIZE_NAME, stdin);
	while (new_mas[*state_count - 1].name[step] != '\n')
	{
		if (new_mas[*state_count - 1].name[step] < 'A' || new_mas[*state_count - 1].name[step] > 'Z')
		{
			printf("��������� ����:");

			fgets(new_mas[*state_count - 1].name, SIZE_NAME, stdin);

			step = 0;
		}
		else
			step++;
	}

	new_mas[*state_count - 1].name[step] = '\0';
	
	input_new_info(new_mas, state_count);

	return new_mas;
}

void output_info(state state) //����� ���������� � �����������
{
	printf("�������� �����������:%s\n", state.name);
	
	if(state.economy == DO_IND)
		printf("������� ���������: ����������������.\n");

	else if(state.economy == IND)
		printf("������� ���������: ��������������.\n");

	else if (state.economy == POST_IND)
		printf("������� ���������: ������������������.\n");
	
	printf("���������:%d\n", state.population);
}

void sort_one_parametr(state *mas, int left, int *right)//������� ��� ������ � ������������ �� ������ ����
{
	int menu = 0;

	system("cls");

	printf("1.����������� �� ��������.\n");
	printf("2.����������� �� ���������.\n");
	printf("3.����������� �� ������� �������������� ��������.\n");
	printf("4.��������� � ������� ����.\n");

	printf("\n\n\n���� �������:");

	rewind(stdin);
	while (scanf_s("%d", &menu) != 1 || menu<1 || menu >4)
	{
		rewind(stdin);
		printf("��������� ����:");
	}

	if (menu == 1)
	{
		system("cls");

		printf("1.����������� �� � �� Z.\n");
		printf("2.����������� �� �� Z �� �.\n");
		printf("3.��������� � ������� ����.\n");

		printf("\n\n\n���� �������:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >3)
		{
			rewind(stdin);
			printf("��������� ����:");
		}

		if (menu == 3)
			return;
		else
		{
			menu--;
			sort_name[menu](mas, 0, right);
		}
	}
	else if (menu == 2)
	{
		system("cls");

		printf("1.����������� �� �o��������� ���������.\n");
		printf("2.����������� �� �������� ���������.\n");
		printf("3.��������� � ������� ����.\n");

		printf("\n\n\n���� �������:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >3)
		{
			rewind(stdin);
			printf("��������� ����:");
		}

		if (menu == 3)
			return;
		else
		{
			menu--;
			sort_population[menu](mas, 0, right);
		}
	}
	else if (menu == 3)
	{
		system("cls");

		printf("1.����������� �� ������� ������ �������������� �������� � ��������.\n");
		printf("2.����������� �� �������� ������ �������������� �������� � �������.\n");
		printf("3.��������� � ������� ����.\n");

		printf("\n\n\n���� �������:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >3)
		{
			rewind(stdin);
			printf("��������� ����:");
		}

		if (menu == 3)
			return;
		else
		{
			menu--;
			sort_economy[menu](mas, 0, right);
		}
	}
	else if (menu == 4)
		return;
}

void sort_tu_parametr(state *mas, int left, int *right)//������� ��� ������ � ����������� �� ���� �����
{
	int menu = 0;

	system("cls");

	printf("1.����������� �� �������� � ���������.\n");
	printf("2.����������� �� �������� � ������ �������������� ��������.\n");
	printf("3.����������� �� ��������� � ������ ������������� ��������.\n");
	printf("4.�������� � ������� ����.\n");

	printf("\n\n\n���� �������:");

	rewind(stdin);
	while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >4)
	{
		rewind(stdin);
		printf("��������� ����:");
	}

	if (menu == 4)
		return;
	else
	{
		menu--;
		sort_ty_parametr[menu](mas, right);
	}
}

void sort_state_name_up(state *mas, int left, int *right)// ���������� �� �������� �� A �� Z
{
	state temp;

	for (int i = left; i < *right; i++)
	{
		for (int j = left; j < *right - 1; j++)
		{
			if (strcmp(mas[j].name, mas[j + 1].name) > 0)
			{
				temp = mas[j];
				mas[j] = mas[j + 1];
				mas[j + 1] = temp;
			}
		}
	}
}

void sort_state_name_down(state *mas, int left, int *right)// ���������� �� �������� �� Z �� A
{
	state temp;

	for (int i = left; i < *right; i++)
	{
		for (int j = left; j < *right - 1; j++)
		{
			if (strcmp(mas[j].name, mas[j + 1].name) < 0)
			{
				temp = mas[j];
				mas[j] = mas[j + 1];
				mas[j + 1] = temp;
			}
		}
	}
}

void sort_state_population_up(state *mas, int left, int *right)// ���������� �� ��������� �� �����������
{
	state temp;

	for (int i = left; i < *right; i++)
	{
		for (int j = left; j < *right - 1; j++)
		{
			if (mas[j].population > mas[j + 1].population)
			{
				temp = mas[j];
				mas[j] = mas[j + 1];
				mas[j + 1] = temp;
			}
		}
	}
}

void sort_state_population_down(state *mas, int left, int *right)// ���������� �� ��������� �� ��������
{
	state temp;

	for (int i = left; i < *right; i++)
	{
		for (int j = left; j < *right - 1; j++)
		{
			if (mas[j].population < mas[j + 1].population)
			{
				temp = mas[j];
				mas[j] = mas[j + 1];
				mas[j + 1] = temp;
			}
		}
	}
}

void sort_state_economy_up(state *mas, int left, int *right)// ���������� �� ������ �������������� �������� �� �����������
{
	state temp;

	for (int i = left; i < *right; i++)
	{
		for (int j = left; j < *right - 1; j++)
		{
			if (mas[j].economy > mas[j + 1].economy)
			{
				temp = mas[j];
				mas[j] = mas[j + 1];
				mas[j + 1] = temp;
			}
		}
	}
}

void sort_state_economy_down(state *mas, int left, int *right)// ���������� �� ������ �������������� �������� �� ��������
{																			
	state temp;

	for (int i = left; i < *right; i++)
	{
		for (int j = left; j < *right - 1; j++)
		{
			if (mas[j].economy < mas[j + 1].economy)
			{
				temp = mas[j];
				mas[j] = mas[j + 1];
				mas[j + 1] = temp;
			}
		}
	}
}

void sort_name_population(state *mas, int *state_count)//���������� �� �������� � ���������
{
	system("cls");

	int left = 0;
	int right = *state_count;
	int menu = 0;
	
	printf("1.����������� ������� �� ��������.\n");
	printf("2.����������� ������� �� ���������.\n");
	printf("3.��������� � ������� ����.\n");

	printf("\n\n\n���� �������:");

	rewind(stdin);
	while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >3)
	{
		rewind(stdin);
		printf("��������� ����:");
	}

	if (menu == 1)
	{
		system("cls");

		printf("1.����������� �� � �� Z.\n");
		printf("2.����������� �� Z �� �.\n");
		printf("3.��������� � ������� ����.\n");

		printf("\n\n\n���� �������:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >3)
		{
			rewind(stdin);
			printf("��������� ����:");
		}

		if (menu == 3)
			return;
		else
		{
			menu--;
			sort_name[menu](mas, left, &right);
		}

		system("cls");

		printf("1.����������� �� �o��������� ���������.\n");
		printf("2.����������� �� �������� ���������.\n");

		printf("\n\n\n���� �������:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >2)
		{
			rewind(stdin);
			printf("��������� ����:");
		}

		right = 0;

		if (menu == 1)
		{
			do
			{
				while (strcmp(mas[right].name, mas[right + 1].name) == 0)
				{
					right++;
				}
				right++;

				sort_state_population_up(mas, left, &right);

				left = right;


			} while (left < *state_count);
		}
		else if (menu == 2)
		{
			do
			{
				while (strcmp(mas[right].name, mas[right + 1].name) == 0)
				{
					right++;
				}
				right++;

				sort_state_population_down(mas, left, &right);

				left = right;


			} while (left < *state_count);
		}
	}
	else if (menu == 2)
	{
		system("cls");

		printf("1.����������� �� �o��������� ���������.\n");
		printf("2.����������� �� �������� ���������.\n");
		printf("3.��������� � ������� ����.\n");

		printf("\n\n\n���� �������:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >3)
		{
			rewind(stdin);
			printf("��������� ����:");
		}

		if (menu == 3)
			return;
		else
		{
			menu--;
			sort_population[menu](mas, left, &right);
		}

		system("cls");

		printf("1.����������� �� � �� Z.\n");
		printf("2.����������� �� Z �� �.\n");

		printf("\n\n\n���� �������:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >2)
		{
			rewind(stdin);
			printf("��������� ����:");
		}

		right = 0;

		if (menu == 1)
		{
			do
			{
				while (mas[right].population == mas[right + 1].population)
				{
					right++;
				}
				right++;

				sort_state_name_up(mas, left, &right);

				left = right;


			} while (left < *state_count);
		}
		else if (menu == 2)
		{
			do
			{
				while (mas[right].population == mas[right + 1].population)
				{
					right++;
				}
				right++;

				sort_state_name_down(mas, left, &right);

				left = right;


			} while (left < *state_count);
		}
	}
	else if (menu == 3)
		return;
}

void sort_name_economy(state *mas, int *state_count)//���������� �� �������� � ������ �������������� ��������
{
	system("cls");

	int left = 0;
	int right = *state_count;
	int menu = 0;

	printf("1.����������� ������� �� ��������.\n");
	printf("2.����������� ������� �� ������ �������������� ��������.\n");
	printf("3.��������� � ������� ����.\n");

	printf("\n\n\n���� �������:");

	rewind(stdin);
	while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >3)
	{
		rewind(stdin);
		printf("��������� ����:");
	}

	if (menu == 1)
	{
		system("cls");

		printf("1.����������� �� � �� Z.\n");
		printf("2.����������� �� Z �� �.\n");
		printf("3.��������� � ������� ����.\n");

		printf("\n\n\n���� �������:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >3)
		{
			rewind(stdin);
			printf("��������� ����:");
		}

		if (menu == 3)
			return;
		else
		{
			menu--;
			sort_name[menu](mas, left, &right);
		}

		system("cls");

		printf("1.����������� �� ������� ������ �������������� �������� � ��������.\n");
		printf("2.����������� �� �������� ������ �������������� �������� � �������.\n");

		printf("\n\n\n���� �������:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >2)
		{
			rewind(stdin);
			printf("��������� ����:");
		}

		right = 0;

		if (menu == 1)
		{
			do
			{
				while (strcmp(mas[right].name, mas[right + 1].name) == 0)
				{
					right++;
				}
				right++;

				sort_state_economy_up(mas, left, &right);

				left = right;


			} while (left < *state_count);
		}
		else if (menu == 2)
		{
			do
			{
				while (strcmp(mas[right].name, mas[right + 1].name) == 0)
				{
					right++;
				}
				right++;

				sort_state_economy_down(mas, left, &right);

				left = right;


			} while (left < *state_count);
		}
	}
	else if (menu == 2)
	{
		system("cls");

		printf("1.����������� �� ������� ������ �������������� �������� � ��������.\n");
		printf("2.����������� �� �������� ������ �������������� �������� � �������.\n");
		printf("3.��������� � ������� ����.\n");

		printf("\n\n\n���� �������:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >3)
		{
			rewind(stdin);
			printf("��������� ����:");
		}

		if (menu == 3)
			return;
		else
		{
			menu--;
			sort_economy[menu](mas, left, &right);
		}

		system("cls");

		printf("1.����������� �� � �� Z.\n");
		printf("2.����������� �� Z �� �.\n");

		printf("\n\n\n���� �������:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >2)
		{
			rewind(stdin);
			printf("��������� ����:");
		}

		right = 0;

		if (menu == 1)
		{
			do
			{
				while (mas[right].economy == mas[right + 1].economy)
				{
					right++;
				}
				right++;

				sort_state_name_up(mas, left, &right);

				left = right;


			} while (left < *state_count);
		}
		else if (menu == 2)
		{
			do
			{
				while (mas[right].economy == mas[right + 1].economy)
				{
					right++;
				}
				right++;

				sort_state_name_down(mas, left, &right);

				left = right;


			} while (left < *state_count);
		}
		else if (menu == 3)
			return;
	}
}

void sort_population_economy(state *mas, int *state_count)//���������� �� ��������� � ������ �������������� ��������
{
	system("cls");

	int left = 0;
	int right = *state_count;
	int menu = 0;

	printf("1.����������� ������� �� ���������.\n");
	printf("2.����������� ������� �� ������ �������������� ��������.\n");
	printf("3.��������� � ������� ����.\n");

	printf("\n\n\n���� �������:");

	rewind(stdin);
	while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >3)
	{
		rewind(stdin);
		printf("��������� ����:");
	}

	if (menu == 1)
	{
		system("cls");

		printf("1.����������� �� �o��������� ���������.\n");
		printf("2.����������� �� �������� ���������.\n");
		printf("3.��������� � ������� ����.\n");

		printf("\n\n\n���� �������:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >3)
		{
			rewind(stdin);
			printf("��������� ����:");
		}

		if (menu == 3)
			return;
		else
		{
			menu--;
			sort_population[menu](mas, left, &right);
		}

		system("cls");

		printf("1.����������� �� ������� ������ �������������� �������� � ��������.\n");
		printf("2.����������� �� �������� ������ �������������� �������� � �������.\n");

		printf("\n\n\n���� �������:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >2)
		{
			rewind(stdin);
			printf("��������� ����:");
		}

		right = 0;

		if (menu == 1)
		{
			do
			{
				while (mas[right].population == mas[right + 1].population)
				{
					right++;
				}
				right++;

				sort_state_economy_up(mas, left, &right);

				left = right;


			} while (left < *state_count);
		}
		else if (menu == 2)
		{
			do
			{
				while (mas[right].population == mas[right + 1].population)
				{
					right++;
				}
				right++;

				sort_state_economy_down(mas, left, &right);

				left = right;


			} while (left < *state_count);
		}
	}
	else if (menu == 2)
	{
		system("cls");

		printf("1.����������� �� ������� ������ �������������� �������� � ��������.\n");
		printf("2.����������� �� �������� ������ �������������� �������� � �������.\n");
		printf("3.��������� � ������� ����.\n");

		printf("\n\n\n���� �������:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >3)
		{
			rewind(stdin);
			printf("��������� ����:");
		}

		if (menu == 3)
			return;
		else
		{
			menu--;
			sort_economy[menu](mas, left, &right);
		}

		system("cls");

		printf("1.����������� �� �o��������� ���������.\n");
		printf("2.����������� �� �������� ���������.\n");

		printf("\n\n\n���� �������:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >2)
		{
			rewind(stdin);
			printf("��������� ����:");
		}

		right = 0;

		if (menu == 1)
		{
			do
			{
				while (mas[right].economy == mas[right + 1].economy)
				{
					right++;
				}
				right++;

				sort_state_population_up(mas, left, &right);

				left = right;


			} while (left < *state_count);
		}
		else if (menu == 2)
		{
			do
			{
				while (mas[right].economy == mas[right + 1].economy)
				{
					right++;
				}
				right++;

				sort_state_population_down(mas, left, &right);

				left = right;


			} while (left < *state_count);
		}
		else if (menu == 3)
			return;
	}
}