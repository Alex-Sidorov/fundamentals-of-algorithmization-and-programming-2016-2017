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

void image_in_negativ(BITMAPINFOHEADER, RGBQUAD **); // перевести изображение в негатив

void image_in_blackwhite(BITMAPINFOHEADER , RGBQUAD **);// перевести изображение в черно-белое

void gamma_correction(BITMAPINFOHEADER, RGBQUAD **, double);//гамма-корекция

void median_corection(BITMAPINFOHEADER, RGBQUAD **);//медианная фильтрация

void bouble_sort_up(unsigned char *, int);//сортировка

FILE * OpenFILE(char *, char *);//открытие файла

void CloseFILE(FILE *);//закрытие файла

RGBQUAD ** create_mas(long int, long int);//создание двумерного массива

RGBQUAD ** read_bmp(BITMAPFILEHEADER &, BITMAPINFOHEADER &, RGBQUAD **, FILE *, long int &);//чтение bmp файла

void fwrite_bmp(BITMAPFILEHEADER, BITMAPINFOHEADER, RGBQUAD **, FILE *, long int);//запись bmp файла

void delete_mas(long int, RGBQUAD **);//удаление двумерного массива

void menu_median_corection(BITMAPINFOHEADER , RGBQUAD **);//меню медианной корекции

int write_mas(unsigned char *, unsigned char *, unsigned char *, BITMAPINFOHEADER , RGBQUAD **, int , int );//запись пикселя и тех пикселей что рядом в массивы

void menu_gamma_correction(BITMAPINFOHEADER , RGBQUAD **);//меню гамма-корекции

void input_name_image(char *);//ввод названия файла
void check_width_read(BITMAPINFOHEADER &);//проверка ширины
bool check_file(INT);//проверка bmp ли это файл