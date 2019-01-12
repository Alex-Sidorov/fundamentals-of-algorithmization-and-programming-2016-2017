#include "library.h"

int main()
{
	FILE *full_file;
	FILE *compact_file;
	FILE *key_file;

	int count_word = 0;

	char short_word[SIZE];
	char long_word[SIZE];

	spisok *head = nullptr;

	full_file = open_file("FULL_FILE.txt", "w+");
	if (full_file == nullptr)
		return 1;
	
	compact_file = open_file("COMPACT_FILE.txt", "r");
	if (compact_file == nullptr)
	{
		close_file(full_file);

		assert(remove("FULL_FILE.txt") == NULL);

		return 2;
	}

	key_file = open_file("KEY_FILE.txt", "r");
	if (key_file == nullptr)
	{
		close_file(full_file);
		close_file(compact_file);

		assert(remove("FULL_FILE.txt") == NULL);

		return 3;
	}

	printf("Decompressing Comes...");

	if (check_file(key_file) == false)
	{
		system("cls");

		printf("File can not be uncompressed.\n");

		system("pause");

		close_file(full_file);
		close_file(compact_file);
		close_file(key_file);

		assert(remove("FULL_FILE.txt") == NULL);

		return 4;
	}

	count_word = count_all_word(compact_file);

	for (int i = 0; i < count_word; i++)
	{
		create_spisok(&head);

		if (head == nullptr)
		{
			close_file(full_file);
			close_file(compact_file);
			close_file(key_file);

			assert(remove("FULL_FILE.txt") == NULL);

			return 5;
		}
	}
	
	input_spisok(compact_file, head);
	if (head == nullptr)
	{
		close_file(full_file);
		close_file(compact_file);
		close_file(key_file);

		assert(remove("FULL_FILE.txt") == NULL);

		return 6;
	}

	rewind(key_file);

	while(1)
	{
		if(fscanf_s(key_file, "%s", &short_word, SIZE) == EOF)
			break;

		fscanf_s(key_file, "%s", &long_word, SIZE);

		swap(head, short_word, long_word);
	}

	input_file(full_file, head);
	delete_spisok(&head);

	system("cls");

	close_file(full_file);
	close_file(compact_file);
	close_file(key_file);


	printf("File compressed.\n");
	system("pause");

	return 0;
}
