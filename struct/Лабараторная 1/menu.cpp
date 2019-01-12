#include "library.h"

int main()
{
	setlocale(LC_ALL, "RUS");

	state *mas = 0;      //массив структур
	int count_state = 2; //количество государств
	int menu = 0;        //переменная для меню
	int *state_count;    //указатель на количество государств

	state_count = &count_state;

	mas = creat_struct(state_count); //выделение памяти
	if (mas == NULL)
		return 1;

	strcpy_s(mas[0].name, "RUSSIA");
	mas[0].economy = IND;
	mas[0].population = 146'804'372;

	strcpy_s(mas[1].name, "USA");
	mas[1].economy = POST_IND;
	mas[1].population = 324'227'000;

	for (;;)
	{
		system("cls");
		printf("Количество известных государств:%d.\n\n", count_state);
		printf("1.Изменить информацию о государстве.\n");
		printf("2.Добавить государство.\n");
		printf("3.Удалить государство.\n");
		printf("4.Отсортировать государства.\n");
		printf("5.Вывести информацию о государстве.\n");
		printf("6.Выйти.\n");
		printf("\n\n\nВаша команда:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu>6 || menu<1)
		{
			rewind(stdin);
			printf("Повторите ввод:");
		}

		switch (menu)
		{
		case 1: 

			system("cls");

			if (*state_count == 0)
			{
				printf("Нет известных государств.\n");

				printf("\n\nЧтобы выйти в главное меню, нажмите любую кнопку.");

				_getch();
			}
			else
			{
				printf("Выберите государство:\n");

				for (int i = 0; i < *state_count; i++)
					printf("%d.%s\n", i + 1, mas[i].name);

				printf("\n\n\nВаша команда:");

				rewind(stdin);
				while (scanf_s("%d", &menu) != 1 || menu<1 || menu > *state_count)
				{
					rewind(stdin);
					printf("Повторите ввод:");
				}
				menu--;

				input_info(mas[menu]); //изменение информации
			}

			break;

		case 2:

			system("cls");

			printf("1.Добавить государство.\n");
			printf("2.Назад.\n");

			printf("\n\n\nВаша команда:");

			rewind(stdin);
			while (scanf_s("%d", &menu) != 1 || menu<1 || menu >2)
			{
				rewind(stdin);
				printf("Повторите ввод:");
			}

			if (menu == 1)
				mas = creat_new_state(mas, state_count); //создание нового государства

			else if (menu == 2)
				break;

			break;

		case 3:

			system("cls");

			if (*state_count == 0)
			{
				printf("Нет известных государств.\n");

				printf("\n\nЧтобы выйти в главное меню, нажмите любую кнопку.");

				_getch();
			}
			else
			{	
				mas = del_state(mas, state_count); //удаление государствa

			}

			break;

		case 4:

			system("cls");

			if (*state_count == 0)
			{
				printf("Нет известных государств.\n");

				printf("\n\nЧтобы выйти в главное меню, нажмите любую кнопку.");

				_getch();
			}
			else
			{ 
				printf("1.Сортировать по одной характеристики.\n");
				printf("2.Сортировать по двум характеристикам.\n");
				printf("3.Вернуться в главное меню.\n");
				printf("\n\n\nВаша команда:");

				rewind(stdin);
				while (scanf_s("%d", &menu) != 1 || menu<1 || menu >3)
				{
					rewind(stdin);
					printf("Повторите ввод:");
				}

				if (menu == 1)
				{
					sort_one_parametr(mas, 0, state_count);
					break;
				}

				else if (menu == 2)
				{
					sort_tu_parametr(mas, 0, state_count);//TWO
					break;
				}

				else if (menu == 3)
					break;
			}

		case 5: 

			system("cls");

			if (*state_count == 0)
			{
				printf("Нет известных государств.\n");

				printf("\n\nЧтобы выйти в главное меню, нажмите любую кнопку.");

				_getch();
			}
			else
			{
				printf("Выберите государство:\n");

				for (int i = 0; i < *state_count; i++)
					printf("%d.%s\n", i + 1, mas[i].name);

				printf("\n\nВведите %d, чтобы вывести все государства", *state_count + 1);

				printf("\n\n\nВаша команда:");

				rewind(stdin);
				while (scanf_s("%d", &menu) != 1 || menu<1 || menu > *state_count + 1)
				{
					rewind(stdin);
					printf("Повторите ввод:");
				}

				if (menu == *state_count + 1)
				{
					system("cls");

					for (int i = 0; i < *state_count; i++)
					{
						output_info(mas[i]);

						printf("\n\n");
					}
				
					printf("\n\nЧтобы выйти в главное меню, нажмите любую кнопку.");

					_getch();
				}
				else
				{
					system("cls");

					menu--;

					output_info(mas[menu]);

					printf("\n\nЧтобы выйти в главное меню, нажмите любую кнопку.");

					_getch();
				}		
			}

			break;

		case 6:
			del_struct(mas);
			return 0;
		}
	}
}