#include "library.h"

int main()
{
	setlocale(LC_ALL, "RUS");

	state *mas = 0;      //������ ��������
	int count_state = 2; //���������� ����������
	int menu = 0;        //���������� ��� ����
	int *state_count;    //��������� �� ���������� ����������

	state_count = &count_state;

	mas = creat_struct(state_count); //��������� ������
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
		printf("���������� ��������� ����������:%d.\n\n", count_state);
		printf("1.�������� ���������� � �����������.\n");
		printf("2.�������� �����������.\n");
		printf("3.������� �����������.\n");
		printf("4.������������� �����������.\n");
		printf("5.������� ���������� � �����������.\n");
		printf("6.�����.\n");
		printf("\n\n\n���� �������:");

		rewind(stdin);
		while (scanf_s("%d", &menu) != 1 || menu>6 || menu<1)
		{
			rewind(stdin);
			printf("��������� ����:");
		}

		switch (menu)
		{
		case 1: 

			system("cls");

			if (*state_count == 0)
			{
				printf("��� ��������� ����������.\n");

				printf("\n\n����� ����� � ������� ����, ������� ����� ������.");

				_getch();
			}
			else
			{
				printf("�������� �����������:\n");

				for (int i = 0; i < *state_count; i++)
					printf("%d.%s\n", i + 1, mas[i].name);

				printf("\n\n\n���� �������:");

				rewind(stdin);
				while (scanf_s("%d", &menu) != 1 || menu<1 || menu > *state_count)
				{
					rewind(stdin);
					printf("��������� ����:");
				}
				menu--;

				input_info(mas[menu]); //��������� ����������
			}

			break;

		case 2:

			system("cls");

			printf("1.�������� �����������.\n");
			printf("2.�����.\n");

			printf("\n\n\n���� �������:");

			rewind(stdin);
			while (scanf_s("%d", &menu) != 1 || menu<1 || menu >2)
			{
				rewind(stdin);
				printf("��������� ����:");
			}

			if (menu == 1)
				mas = creat_new_state(mas, state_count); //�������� ������ �����������

			else if (menu == 2)
				break;

			break;

		case 3:

			system("cls");

			if (*state_count == 0)
			{
				printf("��� ��������� ����������.\n");

				printf("\n\n����� ����� � ������� ����, ������� ����� ������.");

				_getch();
			}
			else
			{	
				mas = del_state(mas, state_count); //�������� ����������a

			}

			break;

		case 4:

			system("cls");

			if (*state_count == 0)
			{
				printf("��� ��������� ����������.\n");

				printf("\n\n����� ����� � ������� ����, ������� ����� ������.");

				_getch();
			}
			else
			{ 
				printf("1.����������� �� ����� ��������������.\n");
				printf("2.����������� �� ���� ���������������.\n");
				printf("3.��������� � ������� ����.\n");
				printf("\n\n\n���� �������:");

				rewind(stdin);
				while (scanf_s("%d", &menu) != 1 || menu<1 || menu >3)
				{
					rewind(stdin);
					printf("��������� ����:");
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
				printf("��� ��������� ����������.\n");

				printf("\n\n����� ����� � ������� ����, ������� ����� ������.");

				_getch();
			}
			else
			{
				printf("�������� �����������:\n");

				for (int i = 0; i < *state_count; i++)
					printf("%d.%s\n", i + 1, mas[i].name);

				printf("\n\n������� %d, ����� ������� ��� �����������", *state_count + 1);

				printf("\n\n\n���� �������:");

				rewind(stdin);
				while (scanf_s("%d", &menu) != 1 || menu<1 || menu > *state_count + 1)
				{
					rewind(stdin);
					printf("��������� ����:");
				}

				if (menu == *state_count + 1)
				{
					system("cls");

					for (int i = 0; i < *state_count; i++)
					{
						output_info(mas[i]);

						printf("\n\n");
					}
				
					printf("\n\n����� ����� � ������� ����, ������� ����� ������.");

					_getch();
				}
				else
				{
					system("cls");

					menu--;

					output_info(mas[menu]);

					printf("\n\n����� ����� � ������� ����, ������� ����� ������.");

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