#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <locale>

#define CONST_MIND 9
#define SIZE 100

typedef unsigned __int16 INT;


#pragma pack(push, 1)

struct BITMAPFILEHEADER
{
	INT					bfType;

	unsigned long int   bfSize;

	INT					bfReserved1;

	INT					bfReserved2;

	unsigned long int   bfOffBits;
};

#pragma pack(pop)

struct BITMAPINFOHEADER 
{
	unsigned long int   biSize;

	long int			biWidth;

	long int			biHeight;

	INT					biPlanes;

	INT					biBitCount;

	unsigned long int   biCompression;

	unsigned long int   biSizeImage;

	long int			biXPelsPerMeter;

	long int			biYPelsPerMeter;

	unsigned long int   biClrUsed;

	unsigned long int   biClrImportant;

};

#pragma pack(push, 1)

struct RGBQUAD 
{
	unsigned char    rgbBlue;
	unsigned char    rgbGreen;
	unsigned char    rgbRed;
};

#pragma pack(pop)

void image_in_negativ(BITMAPINFOHEADER, RGBQUAD **); // ��������� ����������� � �������

void image_in_blackwhite(BITMAPINFOHEADER , RGBQUAD **);// ��������� ����������� � �����-�����

void gamma_correction(BITMAPINFOHEADER, RGBQUAD **, double);//�����-��������

void median_corection(BITMAPINFOHEADER, RGBQUAD **);//��������� ����������

void bouble_sort_up(unsigned char *, int);//����������

FILE * OpenFILE(char *, char *);//�������� �����

void CloseFILE(FILE *);//�������� �����

RGBQUAD ** create_mas(long int, long int);//�������� ���������� �������

RGBQUAD ** read_bmp(BITMAPFILEHEADER &, BITMAPINFOHEADER &, RGBQUAD **, FILE *, long int &);//������ bmp �����

void fwrite_bmp(BITMAPFILEHEADER, BITMAPINFOHEADER, RGBQUAD **, FILE *, long int);//������ bmp �����

void delete_mas(long int, RGBQUAD **);//�������� ���������� �������

void menu_median_corection(BITMAPINFOHEADER , RGBQUAD **);//���� ��������� ��������

int write_mas(unsigned char *, unsigned char *, unsigned char *, BITMAPINFOHEADER , RGBQUAD **, int , int );//������ ������� � ��� �������� ��� ����� � �������

void menu_gamma_correction(BITMAPINFOHEADER , RGBQUAD **);//���� �����-��������

void input_name_image(char *);//���� �������� �����
void check_width_read(BITMAPINFOHEADER &);//�������� ������
bool check_file(INT);//�������� bmp �� ��� ����