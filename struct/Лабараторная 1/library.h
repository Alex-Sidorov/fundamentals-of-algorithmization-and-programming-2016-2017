#pragma once

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale>

#define SIZE_NAME 50 //������������ ����� �������� �����������

enum econm           //���������� ��� �������������� ������ �������������� ��������
{
	DO_IND,
	IND,
	POST_IND
};

struct state
{
	char name[SIZE_NAME]; //�������� �����������

	econm economy;  //������������� �������� �����������

	int population; //����������� ���������
};

void sort_one_parametr(state *, int, int *);//������� ��� ������ � ����������� �� ������ ����
void sort_tu_parametr(state *, int, int *);//������� ��� ������ � ����������� �� ���� �����
void input_new_info(state *, int *);//���� ����������
void input_info(state &);//��������� ���������� � �����������
void output_info(state);//����� ���������� � �����������
state * creat_struct(int *);//�������� ������� ��������
state * creat_new_state(state *, int *);//�������� ����� ���������
state * del_state(state *, int *);//�������� ���������
void sort_state_population_up(state *, int, int *);//���������� �� ��������� �� �����������
void sort_state_population_down(state *, int, int *);//���������� �� ��������� �� ��������
void sort_state_economy_up(state *, int, int *);//���������� �� ������ �������������� �������� �� �����������
void sort_state_economy_down(state *, int, int *);//���������� �� ������ �������������� �������� �� ��������
void sort_state_name_up(state *, int, int *);//���������� �� �������� �� A �� Z
void sort_state_name_down(state *, int, int *);//���������� �� �������� �� A �� Z
void del_struct(state *);//�������� ������� ��������
void sort_name_population(state *, int *);//���������� �� �������� � ���������
void sort_name_economy(state *, int *);//���������� �� �������� � ������ �������������� ��������
void sort_population_economy(state *, int *);//���������� �� ��������� � ������ �������������� ��������