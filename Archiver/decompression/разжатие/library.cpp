#include "library.h"

bool check_file(FILE *file)//проверка файла на пустоту
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

void swap(spisok *head, char *short_word, char *long_word)
{
	while (head != nullptr)
	{
		if (strcmp(head->word, short_word) == 0)
		{
			strcpy(head->word, long_word);
		}
			
		else if (strcmp(head->word, long_word) == 0)
		{
			strcpy(head->word, short_word);
		}
		head = head->next;
	}
}

void input_spisok(FILE *file, spisok *head)
{
	FILE *temp_file;
	char word[SIZE];
	char simvol;
	int znak = 0;

	temp_file = open_file("TEMP_FILE.txt", "w+");
	if (copy_file == nullptr)
	{
		delete_spisok(&head);
	}
	else
	{
		copy_file(file, temp_file);
		rewind(temp_file);

		while (head != nullptr)
		{
			fscanf_s(temp_file, "%s", &word, SIZE);

			fread(&simvol, sizeof(char), 1, temp_file);

			for (znak = 0; simvol == '\n' || simvol == '\r' || simvol == ' ' || simvol == '\t'; znak++)//запись знаков после запятой
			{
				head->znak[znak] = simvol;
				fread(&simvol, sizeof(char), 1, temp_file);
			}

			head->znak[znak] = '\0';

			fseek(temp_file, -sizeof(char), 1);

			strcpy(head->word, word);

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

void input_file(FILE *file, spisok *head)
{
	while (head != nullptr)
	{
		fprintf(file, "%s", head->word);

		fprintf(file, "%s", head->znak);

		head = head->next;
	}
}