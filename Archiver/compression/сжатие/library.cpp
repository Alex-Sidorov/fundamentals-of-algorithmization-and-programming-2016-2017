#include "library.h"

bool check_file(FILE *file)
{
	char word[SIZE];

	if (fscanf_s(file, "%s", &word, SIZE) != EOF)
		return true;
	else
		return false;
}

FILE * open_file(char *name_file, char *mode_file)
{
	FILE *file;

	fopen_s(&file, name_file, mode_file);

	return file;
}

void close_file(FILE *file)
{
	fclose(file);
}

int word_count(FILE *file, char *check_word)//подсчет слов
{
	char word[SIZE];

	int count_word = 0;

	rewind(file);

	while (fscanf_s(file, "%s", &word, SIZE) != EOF)
	{
		if (strcmp(word, check_word) == 0)
			count_word++;
	}

	return count_word;
}

int count_all_word(FILE *file)
{
	int count_all_word = 0;
	char word[SIZE];

	rewind(file);

	while (fscanf_s(file, "%s", &word, SIZE) != EOF)
	{
		count_all_word++;
	}

	return count_all_word;
}

void input_spisok(FILE *file, spisok *head)
{
	char word[SIZE];

	char simvol;

	int znak = 0;

	FILE *temp_file;

	temp_file = open_file("TEMP_FILE.txt", "w+");
	if (copy_file == nullptr)
	{
		delete_spisok(&head);
	}
	else
	{
		copy_file(file, temp_file);

		rewind(file);

		while (head != nullptr)
		{
			fscanf_s(file, "%s", &word, SIZE);

			fread(&simvol, sizeof(char), 1, file);

			for (znak = 0; simvol == '\n' || simvol == '\r' || simvol == ' ' || simvol == '\t'; znak++)
			{
				head->znak[znak] = simvol;
				fread(&simvol, sizeof(char), 1, file);
			}

			head->znak[znak] = '\0';

			fseek(file, -sizeof(char), 1);

			strcpy(head->word, word);

			head->count_word = word_count(temp_file, word);

			head->flag1 = true;
			head->flag2 = true;

			head = head->next;

		}

		close_file(temp_file);

		assert(remove("TEMP_FILE.txt") == NULL);
	}
	
}

void copy_file(FILE *original_file, FILE *copy_file)
{
	char simvol;

	rewind(original_file);
	rewind(copy_file);

	fread(&simvol, sizeof(char), 1, original_file);

	if (!feof(original_file))
	{
		while (1)
		{
			if (!feof(original_file))
				fwrite(&simvol, sizeof(char), 1, copy_file);
			else
				break;

			fread(&simvol, sizeof(char), 1, original_file);
		}
	}
}

void create_spisok(spisok **head)
{
	spisok *temp;
	
	temp=(spisok *)malloc(sizeof(spisok));
		
	if (temp == nullptr)
		delete_spisok(head);
	else
	{
		temp->next = (*head);
		(*head) = temp;
	}
	
}

word find_short_word(spisok *head, word short_word)
{
	word new_short_word = short_word;

	while (1)
	{
		while (head != nullptr)
		{
			if (head->flag1 == true && head->flag2 == true)
			{
				strcpy(new_short_word.word1, head->word);

				new_short_word.count_word = head->count_word;

				break;
			}

			head = head->next;
		}

		break;
	}

	if (strcmp(new_short_word.word1, short_word.word1) == 0)
		return short_word;

	while (head != nullptr)
	{
		if (head->flag1 == true && head->flag2 == true && strlen(new_short_word.word1) > strlen(head->word))
		{
			strcpy(new_short_word.word1, head->word);
			new_short_word.count_word = head->count_word;
		}


		head = head->next;
	}

	return new_short_word;
}

word find_long_word(spisok *head, word long_word)
{
	word new_long_word = long_word;
	
	while (1)
	{
		while (head != nullptr)
		{
			if (head->flag1 == true && head->flag2 == true)
			{
				strcpy(new_long_word.word1, head->word);

				new_long_word.count_word = head->count_word;

				break;
			}

			head = head->next;
		}
		break;
	}

	if(strcmp(new_long_word.word1, long_word.word1) == 0)
		return long_word;

	while (head != nullptr)
	{
		if (head->flag1 == true && head->flag2 == true && strlen(new_long_word.word1) < strlen(head->word))
		{
			strcpy(new_long_word.word1, head->word);
			new_long_word.count_word = head->count_word;
		}


		head = head->next;
	}

	return new_long_word;
}

void swap(spisok *head, char *short_word, char *long_word)
{
	while (head != nullptr)
	{
		if (strcmp(head->word, short_word) == 0)
		{
			strcpy(head->word, long_word);
			head->flag1 = false;
		}
			
		else if (strcmp(head->word, long_word) == 0)
		{
			strcpy(head->word, short_word);
			head->flag1 = false;
		}
			
		head = head->next;
	}

}

void input_flag2(spisok *head, char *word)
{
	while (head != nullptr)
	{
		if (strcmp(head->word, word) == 0)
		{
			head->flag2 = false;
		}

		head = head->next;
	}
}

void input_flag1(spisok *head, char *word)
{
	while (head != nullptr)
	{
		if (strcmp(head->word, word) == 0)
		{
			head->flag1 = false;
		}

		head = head->next;
	}
}

void output_flag2(spisok *head)
{
	while (head != nullptr)
	{
		if (head->flag2 == false)
		{
			head->flag2 = true;
		}

		head = head->next;
	}
}

void input_file(FILE *file, spisok *head)
{
	while (head != nullptr)
	{
		fprintf(file, "%s", head->word);

		fprintf(file, "%s", head->znak);
		
		head = head->next;
	}
}

void delete_spisok(spisok **head)
{
	spisok *temp;

	while ((*head) != nullptr)
	{
		temp = *head;

		(*head) = (*head)->next;

		free(temp);
	}
}