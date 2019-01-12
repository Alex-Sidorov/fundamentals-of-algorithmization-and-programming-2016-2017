#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define SIZE 50

struct spisok
{
	char word[SIZE];

	char znak[SIZE];
	
	spisok *next;
};

FILE * open_file(char *, char *);
void close_file(FILE *);
void input_spisok(FILE *, spisok *);
void create_spisok(spisok **);
void swap(spisok *, char*, char*);
int count_all_word(FILE *file);
void copy_file(FILE *, FILE *);
void delete_spisok(spisok **head);
void input_file(FILE *file, spisok *head);//запись в файл
bool check_file(FILE *file);//проверка файла на пустоту