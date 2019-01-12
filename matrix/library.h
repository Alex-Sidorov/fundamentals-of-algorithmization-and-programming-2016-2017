#pragma once

#include<stdio.h>
#include<conio.h>
#include<locale>
#include<stdlib.h>

const int EXIT = 0;
const int RIGHT = 0;
const int DOWN = 1;
const int LEFT = 2;
const int UP = 3;

int** create_matrix(const int size);
void delete_matrix(int **matrix, const int size);
int find_simple_number(int value);
void input_size_matrix(int &size_matrix);
void printf_matrix(const int* const* const matrix, const int size_matrix);
void fill_matrix(int*const* const matrix, const int size_matrix);
void printf_error();