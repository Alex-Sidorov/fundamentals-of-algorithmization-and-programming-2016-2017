#include "library.h"

void(*sort_name[])(state *, int, int *) = { sort_state_name_up ,sort_state_name_down };//указатель на массив сортировок по названию
void(*sort_population[])(state *, int, int *) = { sort_state_population_up ,sort_state_population_down };//указатель на массив сортировок по населению
void(*sort_economy[])(state *, int, int *) = { sort_state_economy_up ,sort_state_economy_down };//указатель на массив сортировок по уровню экономического развития
void(*sort_ty_parametr[])(state *, int *) = { sort_name_population ,sort_name_economy , sort_population_economy };//указатель на массив сортировок по двум полям

state * creat_struct(int *state_count)  //создания массива структур
{	
	state *mas;

	mas = (state *)malloc(*state_count * sizeof(state));

	return mas;
}

void del_struct(state *mas)
{
	free(mas);
}

state * del_state(state *mas, int *state_count) //удаление структуры из массива
{
	state temp;
	state *new_mas;
	int state = 0;

	printf("Выберите государство, которое хотите удалить:\n");

	for (int i = 0; i < *state_count; i++)
		printf("%d.%s\n", i + 1, mas[i].name);

	printf("%d.Выход в главное меню.", *state_count + 1);

	printf("\n\n\nВаша команда:");

	rewind(stdin);
	while (scanf_s("%d", &state) != 1 || state <= 0 || state > *state_count + 1)
	{
		rewind(stdin);
		printf("Повторите ввод:");
	}

	if (state == *state_count + 1)//выход в меню
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

		printf("Ошибка. Удалить государство не возможно.");
		printf("\n\nЧтобы выйти в главное меню, нажмите любую кнопку.");

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

void input_info(state &state) //изменение информации о государстве
{
	system("cls");

	int menu = 0;
	int step = 0;//переменная для проверки введенного слова

	for (;;)
	{
		system("cls");

		printf("Изменяемое государство:%s.\n\n", state.name);
		printf("1.Изменить название страны.\n");
		printf("2.Изменить уровень экономики.\n");
		printf("3.Изменить население.\n");
		printf("4.В главное меню.");
		printf("\n\n\nВаша команда:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu > 6 || menu < 1)
		{
			rewind(stdin);
			printf("Повторите ввод:");
		}

		switch (menu)
		{
		case 1:

			system("cls");

			printf("Вводите название государства(латиницей большими буквами):");

			rewind(stdin);
			fgets(state.name, SIZE_NAME, stdin);
			while (state.name[step] != '\n')
			{
				if (state.name[step] < 'A' || state.name[step] > 'Z')
				{
					printf("Повторите ввод:");

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

			printf("1.Изменить на доиндустриальный.\n");
			printf("2.Изменить на индустриальный.\n");
			printf("3.Изменить на постиндустриальный.\n");
			printf("4.Назад.");
			printf("\n\n\nВаша команда:");

			rewind(stdin);
			while (scanf_s("%d", &menu) != 1 || menu > 4 || menu < 1)
			{
				rewind(stdin);
				printf("Повторите ввод:");
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

			printf("Вводите новое значение:");

			rewind(stdin);
			while (scanf_s("%d", &state.population) != 1 || state.population<0)
			{
				rewind(stdin);
				printf("Повторите ввод:");
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

	printf("Определите уровень экономики:\n\n");
	printf("1.Доиндустриальный.\n");
	printf("2.Индустриальный.\n");
	printf("3.Постиндустриальный.\n");
	printf("\n\n\nВаша команда:");

	rewind(stdin);
	while (scanf_s("%d", &economy) != 1 || economy > 3 || economy < 1)
	{
		rewind(stdin);
		printf("Повторите ввод:");
	}

	if (economy == 1)
		mas[*state_count - 1].economy = DO_IND;

	else if (economy == 2)
		mas[*state_count - 1].economy = IND;

	else if (economy == 3)
		mas[*state_count - 1].economy = POST_IND;

	system("cls");

	printf("Введите население страны:");

	rewind(stdin);
	while (scanf_s("%d", &mas[*state_count - 1].population) != 1 || mas[*state_count - 1].population<0)
	{
		rewind(stdin);
		printf("Повторите ввод:");
	}
}

state * creat_new_state(state *mas, int *state_count) //создание нового государства
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

		printf("Ошибка. Добавить государство не возможно.");
		printf("\n\nЧтобы выйти в главное меню, нажмите любую кнопку.");

		_getch();
		return mas;
	}

	for (int i = 0; i < *state_count; i++)
	{
		new_mas[i] = mas[i];
	}

	del_struct(mas);

	rewind(stdin);

	printf("Ввeдите название государства(латиницей большими буквами):");

	fgets(new_mas[*state_count - 1].name, SIZE_NAME, stdin);
	while (new_mas[*state_count - 1].name[step] != '\n')
	{
		if (new_mas[*state_count - 1].name[step] < 'A' || new_mas[*state_count - 1].name[step] > 'Z')
		{
			printf("Повторите ввод:");

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

void output_info(state state) //вывод информации о государстве
{
	printf("Название государства:%s\n", state.name);
	
	if(state.economy == DO_IND)
		printf("Уровень экономики: Доиндустриальный.\n");

	else if(state.economy == IND)
		printf("Уровень экономики: Индустриальный.\n");

	else if (state.economy == POST_IND)
		printf("Уровень экономики: Постиндустриальный.\n");
	
	printf("Население:%d\n", state.population);
}

void sort_one_parametr(state *mas, int left, int *right)//функция для работы с сортировками по одному полю
{
	int menu = 0;

	system("cls");

	printf("1.Сортировать по алфавиту.\n");
	printf("2.Сортировать по населению.\n");
	printf("3.Сортировать по уровнию экономического развития.\n");
	printf("4.Вернуться в главное меню.\n");

	printf("\n\n\nВаша команда:");

	rewind(stdin);
	while (scanf_s("%d", &menu) != 1 || menu<1 || menu >4)
	{
		rewind(stdin);
		printf("Повторите ввод:");
	}

	if (menu == 1)
	{
		system("cls");

		printf("1.Сортировать от А до Z.\n");
		printf("2.Сортировать по от Z до А.\n");
		printf("3.Вернуться в главное меню.\n");

		printf("\n\n\nВаша команда:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >3)
		{
			rewind(stdin);
			printf("Повторите ввод:");
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

		printf("1.Сортировать по вoзрастанию населения.\n");
		printf("2.Сортировать по убыванию населения.\n");
		printf("3.Вернуться в главное меню.\n");

		printf("\n\n\nВаша команда:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >3)
		{
			rewind(stdin);
			printf("Повторите ввод:");
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

		printf("1.Сортировать от низкого уровня экономического развития к высокому.\n");
		printf("2.Сортировать от высокого уровня экономического развития к низкому.\n");
		printf("3.Вернуться в главное меню.\n");

		printf("\n\n\nВаша команда:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >3)
		{
			rewind(stdin);
			printf("Повторите ввод:");
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

void sort_tu_parametr(state *mas, int left, int *right)//функция для работы с сортирвками по двум полям
{
	int menu = 0;

	system("cls");

	printf("1.Сортировать по названию и населению.\n");
	printf("2.Сортировать по названию и уровню экономического развития.\n");
	printf("3.Сортировать по населению и уровню экономичского развития.\n");
	printf("4.Вернутся в главное меню.\n");

	printf("\n\n\nВаша команда:");

	rewind(stdin);
	while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >4)
	{
		rewind(stdin);
		printf("Повторите ввод:");
	}

	if (menu == 4)
		return;
	else
	{
		menu--;
		sort_ty_parametr[menu](mas, right);
	}
}

void sort_state_name_up(state *mas, int left, int *right)// сортировка по алфавиту от A до Z
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

void sort_state_name_down(state *mas, int left, int *right)// сортировка по алфавиту от Z до A
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

void sort_state_population_up(state *mas, int left, int *right)// сортировка по населению по возрастанию
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

void sort_state_population_down(state *mas, int left, int *right)// сортировка по населению по убыванию
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

void sort_state_economy_up(state *mas, int left, int *right)// сортировка по уровню экономического развития по возрастанию
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

void sort_state_economy_down(state *mas, int left, int *right)// сортировка по уровню экономического развития по убыванию
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

void sort_name_population(state *mas, int *state_count)//сортировка по названию и населению
{
	system("cls");

	int left = 0;
	int right = *state_count;
	int menu = 0;
	
	printf("1.Сортировать сначало по названию.\n");
	printf("2.Сортировать сначало по населению.\n");
	printf("3.Вернуться в главное меню.\n");

	printf("\n\n\nВаша команда:");

	rewind(stdin);
	while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >3)
	{
		rewind(stdin);
		printf("Повторите ввод:");
	}

	if (menu == 1)
	{
		system("cls");

		printf("1.Сортировать от А до Z.\n");
		printf("2.Сортировать от Z до А.\n");
		printf("3.Вернуться в главное меню.\n");

		printf("\n\n\nВаша команда:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >3)
		{
			rewind(stdin);
			printf("Повторите ввод:");
		}

		if (menu == 3)
			return;
		else
		{
			menu--;
			sort_name[menu](mas, left, &right);
		}

		system("cls");

		printf("1.Сортировать по вoзрастанию населения.\n");
		printf("2.Сортировать по убыванию населения.\n");

		printf("\n\n\nВаша команда:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >2)
		{
			rewind(stdin);
			printf("Повторите ввод:");
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

		printf("1.Сортировать по вoзрастанию населения.\n");
		printf("2.Сортировать по убыванию населения.\n");
		printf("3.Вернуться в главное меню.\n");

		printf("\n\n\nВаша команда:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >3)
		{
			rewind(stdin);
			printf("Повторите ввод:");
		}

		if (menu == 3)
			return;
		else
		{
			menu--;
			sort_population[menu](mas, left, &right);
		}

		system("cls");

		printf("1.Сортировать от А до Z.\n");
		printf("2.Сортировать от Z до А.\n");

		printf("\n\n\nВаша команда:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >2)
		{
			rewind(stdin);
			printf("Повторите ввод:");
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

void sort_name_economy(state *mas, int *state_count)//сортировка по названию и уровню экономического развития
{
	system("cls");

	int left = 0;
	int right = *state_count;
	int menu = 0;

	printf("1.Сортировать сначала по названию.\n");
	printf("2.Сортировать сначала по уровню экономического развития.\n");
	printf("3.Вернуться в главное меню.\n");

	printf("\n\n\nВаша команда:");

	rewind(stdin);
	while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >3)
	{
		rewind(stdin);
		printf("Повторите ввод:");
	}

	if (menu == 1)
	{
		system("cls");

		printf("1.Сортировать от А до Z.\n");
		printf("2.Сортировать от Z до А.\n");
		printf("3.Вернуться в главное меню.\n");

		printf("\n\n\nВаша команда:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >3)
		{
			rewind(stdin);
			printf("Повторите ввод:");
		}

		if (menu == 3)
			return;
		else
		{
			menu--;
			sort_name[menu](mas, left, &right);
		}

		system("cls");

		printf("1.Сортировать от низкого уровня экономического развития к высокому.\n");
		printf("2.Сортировать от высокого уровня экономического развития к низкому.\n");

		printf("\n\n\nВаша команда:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >2)
		{
			rewind(stdin);
			printf("Повторите ввод:");
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

		printf("1.Сортировать от низкого уровня экономического развития к высокому.\n");
		printf("2.Сортировать от высокого уровня экономического развития к низкому.\n");
		printf("3.Вернуться в главное меню.\n");

		printf("\n\n\nВаша команда:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >3)
		{
			rewind(stdin);
			printf("Повторите ввод:");
		}

		if (menu == 3)
			return;
		else
		{
			menu--;
			sort_economy[menu](mas, left, &right);
		}

		system("cls");

		printf("1.Сортировать от А до Z.\n");
		printf("2.Сортировать от Z до А.\n");

		printf("\n\n\nВаша команда:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >2)
		{
			rewind(stdin);
			printf("Повторите ввод:");
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

void sort_population_economy(state *mas, int *state_count)//сортировка по населению и уровню экономического развития
{
	system("cls");

	int left = 0;
	int right = *state_count;
	int menu = 0;

	printf("1.Сортировать сначала по населению.\n");
	printf("2.Сортировать сначала па уровню экономического развития.\n");
	printf("3.Вернуться в главное меню.\n");

	printf("\n\n\nВаша команда:");

	rewind(stdin);
	while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >3)
	{
		rewind(stdin);
		printf("Повторите ввод:");
	}

	if (menu == 1)
	{
		system("cls");

		printf("1.Сортировать по вoзрастанию населения.\n");
		printf("2.Сортировать по убыванию населения.\n");
		printf("3.Вернуться в главное меню.\n");

		printf("\n\n\nВаша команда:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >3)
		{
			rewind(stdin);
			printf("Повторите ввод:");
		}

		if (menu == 3)
			return;
		else
		{
			menu--;
			sort_population[menu](mas, left, &right);
		}

		system("cls");

		printf("1.Сортировать от низкого уровня экономического развития к высокому.\n");
		printf("2.Сортировать от высокого уровня экономического развития к низкому.\n");

		printf("\n\n\nВаша команда:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >2)
		{
			rewind(stdin);
			printf("Повторите ввод:");
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

		printf("1.Сортировать от низкого уровня экономического развития к высокому.\n");
		printf("2.Сортировать от высокого уровня экономического развития к низкому.\n");
		printf("3.Вернуться в главное меню.\n");

		printf("\n\n\nВаша команда:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >3)
		{
			rewind(stdin);
			printf("Повторите ввод:");
		}

		if (menu == 3)
			return;
		else
		{
			menu--;
			sort_economy[menu](mas, left, &right);
		}

		system("cls");

		printf("1.Сортировать по вoзрастанию населения.\n");
		printf("2.Сортировать по убыванию населения.\n");

		printf("\n\n\nВаша команда:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >2)
		{
			rewind(stdin);
			printf("Повторите ввод:");
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