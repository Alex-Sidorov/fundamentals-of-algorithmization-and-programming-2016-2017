#include "library.h"

int main()
{
	system("chcp 1251");
	system("cls");

	FILE *data;
	Akinator *tree = nullptr;

	data = open_file("data.txt", "r+");
	if (data == nullptr)
		return 1;

	tree = read_data(tree, data);
	if (tree == nullptr)
	{
		close_file(data);
		return 2;
	}

	tree = menu(tree);
	if (tree == nullptr)
	{
		close_file(data);
		return 3;
	}

	write_data(tree, data);

	close_file(data);
	delete_tree(tree);
	return 0;
}