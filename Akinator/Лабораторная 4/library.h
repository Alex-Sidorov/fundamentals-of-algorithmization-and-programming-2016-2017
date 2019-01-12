#pragma once

#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>

#define SIZE 1000

struct Akinator
{
	char text[SIZE];

	char *way;

	Akinator *left;
	Akinator *right;
	Akinator *back;
};

FILE * open_file(char *, char *);
void close_file(FILE *);
Akinator * read_data(Akinator *, FILE *);
Akinator * create_node();
void delete_tree(Akinator *);
void write_data(Akinator *, FILE *);
void write_tree(Akinator *, FILE *);
Akinator * step_left(Akinator *);
Akinator * step_right(Akinator *);
int otvet_akinator(Akinator *, Akinator *);
Akinator * input_new_data(Akinator *, char *, char *, char);
Akinator * menu(Akinator *);
int find_size_way(FILE *);

