#include "library.h"

FILE *open_file(char *name_file, char *mode_file)
{
	FILE *file;

	fopen_s(&file, name_file, mode_file);

	return file;
}

void close_file(FILE *file)
{
	fclose(file);
}

Akinator *create_node()
{
	Akinator *node = nullptr;

	node = (Akinator*)calloc(1, sizeof(Akinator));
	
	return node;
}

char *create_way(int size)
{
	char *way;

	way = (char*)calloc(size, sizeof(char));

	return way;
}

Akinator *read_data(Akinator *tree, FILE *data)
{
	Akinator *temp;//переменная для хранения корня дерева
	char simvol;
	char *temp_way;//временный путь
	int step = 0;
	int size = 0;

	size = find_size_way(data);

	if (tree == nullptr)
	{
		tree = create_node();
		if (tree == nullptr)
			return tree;
	}

	temp_way = create_way(size);

	if (temp_way == nullptr)
	{
		delete_tree(tree);
		return nullptr;
	}

	rewind(data);

	temp = tree;

	simvol = fgetc(data);

	while (1)
	{
		if (simvol == 'l')
		{
			if (tree->left == nullptr)
			{
				tree->left = create_node();
				if (tree->left == nullptr)
				{
					delete_tree(temp);
					return nullptr;
				}
			}

			tree->left->back = tree;
			tree = tree->left;

			temp_way[step] = 'l';
			step++;

			simvol = fgetc(data);
		}
		else if (simvol == 'r')
		{
			if (tree->right == nullptr)
			{
				tree->right = create_node();
				if (tree->right == nullptr)
				{
					delete_tree(temp);
					return nullptr;
				}
			}

			tree->right->back = tree;
			tree = tree->right;

			temp_way[step] = 'r';
			step++;

			simvol = fgetc(data);
		}
		else if(simvol == ' ')
		{
			for (int i = 0;;i++)
			{
				tree->text[i] = fgetc(data);

				if (tree->text[i] == '\n')
				{
					tree->text[i] = '\0';
					break;
				}
			}

			if(temp_way[0]!=' ')
				temp_way[step] = '\0';

			if (tree->way == nullptr)
				tree->way = create_way(strlen(temp_way) + 1);

			if (tree->way == nullptr)
			{
				delete_tree(temp);
				return nullptr;
			}

			strcpy(tree->way, temp_way);

			tree = temp;

			step = 0;
			temp_way[step] = ' ';
			temp_way[step+1] = '\0';

			simvol = fgetc(data);
		}
		else if (simvol == '/')
			break;
	}
	return tree;
}

void write_tree(Akinator *tree, FILE *data)
{
	if (tree->left != nullptr)
		write_tree(tree->left, data);

	if (tree->right != nullptr)
		write_tree(tree->right, data);

	if (tree->way[0] != ' ')
		fprintf(data, "%s %s\n", tree->way, tree->text);
	else
		fprintf(data, "%s%s\n", tree->way, tree->text);
}

void write_data(Akinator *tree, FILE *data)
{
	rewind(data);
	write_tree(tree, data);
	fputc('/', data);
}

void delete_tree(Akinator *tree)
{
	if (tree->left != nullptr)
		delete_tree(tree->left);

	if (tree->right != nullptr)
		delete_tree(tree->right);

	free(tree->way);
	free(tree);
}

Akinator *step_right(Akinator *tree)
{
	return tree->right;
}

Akinator *step_left(Akinator *tree)
{
	return tree->left;
}

Akinator *step_back(Akinator *tree)
{
	if (tree->back == nullptr)
		return tree;
	else
		return tree->back;
}

void input_text(char *text)
{
	rewind(stdin);

	fgets(text, SIZE, stdin);

	for (int i = 0;;i++)
	{
		if (text[i] == '\n')
		{
			text[i] = '\0';
			break;
		}
	}
}

void input_question(char *question)
{
	rewind(stdin);
	
	fgets(question, SIZE, stdin);

	for (int i = 0;;i++)
	{
		if (question[i] == '\n')
		{
			question[i] = '?';
			question[i + 1] = '\0';
			break;
		}
	}
}

int otvet_akinator(Akinator *tree, Akinator *temp)
{
	int otvet = 0;
	char new_otvet[SIZE];
	char new_vopros[SIZE];

	system("cls");

	rewind(stdin);
	printf("\nВы загадали %s.\n", tree->text);
	printf("\nЭто верно ?\n");
	printf("\n1. Да.");
	printf("\n2. Нет.");
	printf("\nВаша команда:");

	while (scanf_s("%d", &otvet) != 1 || otvet > 2 || otvet < 1)
	{
		rewind(stdin);
		printf("\n\nПовторите ввод:");
	}

	if (otvet != 1)
	{
		printf("\nКого вы загадали:");
		
		input_text(new_otvet);

		printf("\nЧто его отличает от %s:", tree->text);
	
		input_question(new_vopros);

		printf("\n%s %s\n", new_otvet, new_vopros);

		printf("\n1. Да.");
		printf("\n2. Нет.");
		printf("\n\nВаша команда:");

		rewind(stdin);
		while (scanf_s("%d", &otvet) != 1 || otvet > 2 || otvet < 1)
		{
			rewind(stdin);
			printf("\n\nПовторите ввод:");
		}

		if(otvet==1)
			tree = input_new_data(tree,new_otvet,new_vopros, 'r');
		else
			tree = input_new_data(tree, new_otvet, new_vopros, 'l');

		if (tree == nullptr)
			return 3;

		system("cls");

		printf("\n\nНовые данные внесены.");
	}

	printf("\nЖелаете продолжить ?\n");

	printf("\n1. Да.");
	printf("\n2. Нет.");
	printf("\n\nВаша команда:");

	rewind(stdin);

	while (scanf_s("%d", &otvet) != 1 || otvet > 2 || otvet < 1)
	{
		rewind(stdin);
		printf("\n\nПовторите ввод:");
	}

	system("cls");

	return otvet;
}

Akinator * input_new_data(Akinator *tree,char *new_otvet, char *new_vopros, char position)
{
	tree->left = create_node();
	if (tree->left == nullptr)
	{
		return nullptr;
	}

	tree->left->way = create_way(strlen(tree->way) + 2);
	if (tree->left->way == nullptr)
		return nullptr;

	tree->right = create_node();
	if (tree->right == nullptr)
	{
		return nullptr;
	}

	tree->right->way = create_way(strlen(tree->way) + 2);
	if (tree->right->way == nullptr)
		return nullptr;

	tree->right->back = tree->left->back = tree;

	if (position == 'l')
	{		
		strcpy(tree->left->text, new_otvet);
		strcpy(tree->left->way, tree->way);

		for (int i = 0;;i++)
		{
			if (tree->left->way[i] == '\0')
			{
				tree->left->way[i] = 'l';
				tree->left->way[i + 1] = '\0';
				break;
			}
		}
		
		strcpy(tree->right->text, tree->text);
		strcpy(tree->right->way, tree->way);

		for (int i = 0;;i++)
		{
			if (tree->right->way[i] == '\0')
			{
				tree->right->way[i] = 'r';
				tree->right->way[i + 1] = '\0';
				break;
			}
		}

		strcpy(tree->text, new_vopros);

	}
	else
	{
		strcpy(tree->right->text, new_otvet);
		strcpy(tree->right->way, tree->way);

		for (int i = 0;;i++)
		{
			if (tree->right->way[i] == '\0')
			{
				tree->right->way[i] = 'r';
				tree->right->way[i + 1] = '\0';
				break;
			}
		}

		strcpy(tree->left->text, tree->text);
		strcpy(tree->left->way, tree->way);

		for (int i = 0;;i++)
		{
			if (tree->left->way[i] == '\0')
			{
				tree->left->way[i] = 'l';
				tree->left->way[i + 1] = '\0';
				break;
			}
		}

		strcpy(tree->text, new_vopros);
	}

	return tree;
}

Akinator *menu(Akinator *tree)
{
	Akinator * (*menu[])(Akinator *tree) = { step_right, step_left, step_back };

	Akinator *temp = tree;
	int answer = 0;

	while (1)
	{
		if (tree->left == nullptr && tree->right == nullptr)
		{
			answer = otvet_akinator(tree,temp);

			if (answer == 2)
				return temp;
			else if (answer == 3)
			{
				delete_tree(temp);
				return nullptr;
			}
			else
				tree = temp;
		}
		
		printf("\n%s\n", tree->text);

		printf("\n1. Да.");
		printf("\n2. Нет.");
		printf("\n3. Изменить предыдущее решение.");
		printf("\n4. Закончить.\n");
		printf("\nВаша команда:");

		rewind(stdin);

		while (scanf_s("%d", &answer) != 1 || answer > 4 || answer < 1)
		{
			rewind(stdin);
			printf("\n\nПовторите ввод:");
		}

		if (answer == 4)
			return temp;
		else
		{
			if (tree == menu[answer - 1](tree))
			{
				system("cls");
				printf("\nИзменить предыдущее решение не возможно.");
			}
			else
			{
				tree = menu[answer - 1](tree);
				system("cls");
			}
		}
	}
}

int find_size_way(FILE *data)
{
	int max_size = 0;
	int size = 0;
	char simvol = 0;;

	simvol = fgetc(data);

	while (simvol != '/')
	{
		if (simvol == ' ')
		{
			while (simvol != '\n')
				simvol = fgetc(data);

			simvol = fgetc(data);
		}
		else
		{
			while (simvol != ' ')
			{
				size++;
				simvol = fgetc(data);
			}

			if (size > max_size)
				max_size = size;

			size = 0;
		}
	}

	return max_size + 1;
}
