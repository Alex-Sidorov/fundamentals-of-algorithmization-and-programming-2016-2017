#include "library.h"

int main()
{
	FILE *original_file;
	FILE *compact_file;
	FILE *key_file;

	word long_word = {0};
	word short_word = {0};
	word check_word = {0};

	int count_word  = 0;// колличество всех слов в файле

	spisok *head = nullptr;
	
	original_file = open_file("ORIGINAL_FILE.txt", "r");
	if (original_file == nullptr)
	{
		return 1;
	}
	
	compact_file = open_file("COMPACT_FILE.txt", "w+");
	if (compact_file == nullptr)
	{
		close_file(compact_file);
		return 2;
	}

	key_file = open_file("KEY_FILE.txt", "w+");
	if (key_file == nullptr)
	{
		close_file(original_file);
		close_file(compact_file);
		return 3;
	}

	printf("Compressing Comes...");

	if (check_file(original_file) == false)
	{
		system("cls");

		printf("Empty File.\n");

		system("pause");

		close_file(original_file);
		close_file(compact_file);
		close_file(key_file);

		assert(remove("KEY_FILE.txt") == NULL);
		assert(remove("COMPACT_FILE.txt") == NULL);

		return 4;
	}

	count_word = count_all_word(original_file);

	for (int i = 0; i < count_word; i++)
	{
		create_spisok(&head);

		if (head == nullptr)
		{
			close_file(original_file);
			close_file(compact_file);
			close_file(key_file);

			assert(remove("COMPACT_FILE.txt") == NULL);
			assert(remove("KEY_FILE.txt") == NULL);

			return 5;
		}
	}
		

	input_spisok(original_file, head);
	if (head == nullptr)
	{
		close_file(original_file);
		close_file(compact_file);
		close_file(key_file);

		assert(remove("COMPACT_FILE.txt") == NULL);
		assert(remove("KEY_FILE.txt") == NULL);

		return 6;
	}

	while (1)
	{
		check_word = find_long_word(head, long_word);

		if (strcmp(long_word.word1, check_word.word1) != 0)
			long_word = check_word;//запоминание длинного слова 
		else
			break;

		check_word = find_short_word(head, short_word);

		if (strcmp(short_word.word1, check_word.word1) != 0)
			short_word = check_word;//запоминание длинного слова 
		else
			break;

		if (strcmp(short_word.word1, long_word.word1) == 0 || strlen(long_word.word1) == strlen(short_word.word1))
			break;

		while (1)
		{
			if (long_word.count_word > short_word.count_word)
			{
				swap(head, short_word.word1, long_word.word1);

				fprintf(key_file, "%s %s ", short_word.word1, long_word.word1);

				break;
			}
			else
			{
				input_flag2(head, short_word.word1);

				check_word = find_short_word(head, short_word);

				if (strcmp(short_word.word1, check_word.word1) != 0)
					short_word = check_word;//запоминание длинного слова 
				else
				{
					output_flag2(head);
					input_flag1(head, long_word.word1);
					break;					
				}
				
			}
		}
	}

	input_file(compact_file, head);
	delete_spisok(&head);

	system("cls");

	if (check_file(key_file) == false)
	{
		printf("File can not be uncompressed.\n");

		system("pause");

		close_file(original_file);
		close_file(compact_file);
		close_file(key_file);


		return 7;
	}
	else
	{
		printf("File compressed.\n");
		system("pause");
	}

	close_file(original_file);
	close_file(compact_file);
	close_file(key_file);

	return 0;
}