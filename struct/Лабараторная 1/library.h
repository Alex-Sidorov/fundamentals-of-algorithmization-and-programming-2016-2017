#pragma once

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale>

#define SIZE_NAME 50 //максимальная длина названия государства

enum econm           //переменная для характеристики уровня экономического развития
{
	DO_IND,
	IND,
	POST_IND
};

struct state
{
	char name[SIZE_NAME]; //название государства

	econm economy;  //экономическое развитие государства

	int population; //численность население
};

void sort_one_parametr(state *, int, int *);//функция для работы с сортироками по одному полю
void sort_tu_parametr(state *, int, int *);//функция для работы с сортироками по двум полям
void input_new_info(state *, int *);//ввод информации
void input_info(state &);//изменение информации о государстве
void output_info(state);//вывов информации о государстве
state * creat_struct(int *);//создание массива структур
state * creat_new_state(state *, int *);//создание новой структуры
state * del_state(state *, int *);//удаление структуры
void sort_state_population_up(state *, int, int *);//сортировка по населению по возрастанию
void sort_state_population_down(state *, int, int *);//сортировка по населению по убыванию
void sort_state_economy_up(state *, int, int *);//сортировка по уровню экономического развития по возрастанию
void sort_state_economy_down(state *, int, int *);//сортировка по уровню экономического развития по убыванию
void sort_state_name_up(state *, int, int *);//сортировка по алфавиту от A до Z
void sort_state_name_down(state *, int, int *);//сортировка по алфавиту от A до Z
void del_struct(state *);//удаление массива структур
void sort_name_population(state *, int *);//сортировка по названию и населению
void sort_name_economy(state *, int *);//сортировка по названию и уровню экономического развития
void sort_population_economy(state *, int *);//сортировка по населению и уровню экономического развития