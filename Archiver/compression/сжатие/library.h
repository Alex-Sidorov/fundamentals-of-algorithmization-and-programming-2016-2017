#pragma once

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define SIZE 50

struct spisok
{
	char word[SIZE];

	bool flag1;

	bool flag2;

	char znak[SIZE];

	int count_word;
	
	spisok *next;
};

struct word
{
	char word1[SIZE];

	int count_word;
};

FILE * open_file(char *, char *);
void close_file(FILE *);
void input_spisok(FILE *, spisok *);
void create_spisok(spisok **);
int word_count(FILE *file, char *word);
int count_all_word(FILE *file);
void copy_file(FILE *, FILE *);
word find_long_word(spisok *, word);
word find_short_word(spisok *, word);
void swap(spisok *, char*, char*);
void input_flag1(spisok *head, char *word);
void input_flag2(spisok *head, char *word);
void output_flag2(spisok *head);
void delete_spisok(spisok **head);
void input_file(FILE *file, spisok *head);
bool check_file(FILE *file);