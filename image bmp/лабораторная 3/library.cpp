#include "library.h"

FILE * OpenFILE(char *name_file, char *mode_file)
{
	FILE *file;

	fopen_s(&file, name_file, mode_file);

	return file;
}

void CloseFILE(FILE *file)
{
	fclose(file);
}

bool check_file(INT type)
{
	if (type == 0x4d42 || type == 0x4349 || type == 0x5450)
		return true;
	else
		return false;
}

void check_width_read(BITMAPINFOHEADER &bf)
{
	if (bf.biWidth % 4 != 0)
		bf.biWidth++;
}

void input_name_image(char *name_image)
{
	int step = 0;

	printf("Введите название изображения(haus.bmp, skelet.bmp и т.д.):");

	fgets(name_image, SIZE, stdin);

	for (step = 0; name_image[step] != '\n'; step++);

	name_image[step] = '\0';
}

RGBQUAD ** create_mas(long int biHeight, long int biWidth)
{
	RGBQUAD **RGB = (RGBQUAD**)calloc((biHeight), sizeof(RGBQUAD*));
	if (RGB == nullptr)
		return RGB;

	for (int i = 0; i < biHeight; i++)
	{
		RGB[i] = (RGBQUAD*)calloc(biWidth, sizeof(RGBQUAD));
		if (RGB[i] == nullptr)
		{
			i--;

			for (;i >= 0; i--)
				free(RGB[i]);

			free(RGB);

			break;
		}
	}
	return RGB;
}

RGBQUAD ** read_bmp(BITMAPFILEHEADER &bl, BITMAPINFOHEADER &bf, RGBQUAD **RGB, FILE *image, long int &check_width)
{

	fread(&bl, sizeof(BITMAPFILEHEADER), 1, image);

	fread(&bf, sizeof(BITMAPINFOHEADER), 1, image);

	check_width = bf.biWidth;

	check_width_read(bf);

	RGB = create_mas(bf.biHeight, bf.biWidth);
	if (RGB == nullptr)
		return RGB;

	for (int i = 0; i < bf.biHeight; i++)
	{
		for (int j = 0; j < bf.biWidth; j++)
		{
			fread(&RGB[i][j], sizeof(RGBQUAD), 1, image);
		}
	}

	return RGB;
}

void delete_mas(long int biHeight, RGBQUAD **RGB)
{
	for (int i = 0; i < biHeight; i++)
	{
		free(RGB[i]);
	}
	free(RGB);

}

void fwrite_bmp(BITMAPFILEHEADER bl, BITMAPINFOHEADER bf, RGBQUAD **RGB, FILE *newimage, long int check_width)
{

	fwrite(&bl, sizeof(BITMAPFILEHEADER), 1, newimage);

	if (check_width != bf.biWidth)
		bf.biWidth--;

	fwrite(&bf, sizeof(BITMAPINFOHEADER), 1, newimage);

	check_width_read(bf);

	for (int i = 0; i < bf.biHeight; i++)
	{
		for (int j = 0; j < bf.biWidth; j++)
		{
			fwrite(&RGB[i][j], sizeof(RGBQUAD), 1, newimage);
		}
	}

}

void image_in_negativ(BITMAPINFOHEADER bf, RGBQUAD **RGB) //перeвод изображения в нигатив
{
	for (int i = 0; i < bf.biHeight; i++)
	{
		for (int j = 0; j < bf.biWidth; j++)
		{
			RGB[i][j].rgbRed = 255 - RGB[i][j].rgbRed;
			RGB[i][j].rgbBlue = 255 - RGB[i][j].rgbBlue;
			RGB[i][j].rgbGreen = 255 - RGB[i][j].rgbGreen;
		}
	}
}

void image_in_blackwhite(BITMAPINFOHEADER bf, RGBQUAD **RGB)
{
	unsigned char temp = 0;

	for (int i = 0; i < bf.biHeight; i++)
	{
		for (int j = 0; j < bf.biWidth; j++)
		{
			temp = 0.11*RGB[i][j].rgbBlue + 0.59*RGB[i][j].rgbGreen + 0.3*RGB[i][j].rgbRed;

			RGB[i][j].rgbRed = temp;
			RGB[i][j].rgbBlue = temp;
			RGB[i][j].rgbGreen = temp;
		}
	}
}

void menu_gamma_correction(BITMAPINFOHEADER bf, RGBQUAD **RGB)
{
	system("cls");

	double gamma = 0;

	printf("Введите коэффицент гамма корекции:\n");
	printf("\t\t\t\t\tПри коэффиценте больше 1 изображение станет темнее.\n");
	printf("\t\t\t\t\tПри коэффиценте меньше 1 изображение станет светлее.\n");
	printf("\t\t\t\t\tПри коэффиценте равном 1 изображение останется оригинальным.\n");
	printf("\nВаш ввод:");

	while (scanf_s("%lf", &gamma) != 1 || gamma <= 0)
	{
		rewind(stdin);
		printf("\nПовторите ввод:");
	}

	gamma_correction(bf, RGB, gamma);
}

void gamma_correction(BITMAPINFOHEADER bf, RGBQUAD **RGB, double gamma)
{
	for (int i = 0; i < bf.biHeight; i++)
	{
		for (int j = 0; j < bf.biWidth; j++)
		{
			RGB[i][j].rgbBlue = pow((double)RGB[i][j].rgbBlue / 255, gamma) * 255;
			RGB[i][j].rgbGreen = pow((double)RGB[i][j].rgbGreen / 255, gamma) * 255;
			RGB[i][j].rgbRed = pow((double)RGB[i][j].rgbRed / 255, gamma) * 255;
		}
	}
}

void bouble_sort_up(unsigned char *mas, int size)
{
	unsigned char temp = 0;

	for (int i = 0; i < size; i++)
	{
		for (int j = size - 1; j > 0; j--)
		{
			if (mas[j] < mas[j - 1])
			{
				temp = mas[j];
				mas[j] = mas[j - 1];
				mas[j - 1] = temp;
			}
		}
	}
}

void menu_median_corection(BITMAPINFOHEADER bf, RGBQUAD **RGB)
{
	system("cls");

	int count = 0;

	printf("Введите сколько хотиете провести медианных фильтраций:");

	while (scanf_s("%d", &count) != 1 || count <= 0)
	{
		rewind(stdin);
		printf("\nПовторите ввод:");
	}

	for (int i = 0; i < count;i++)
	{
		median_corection(bf, RGB);
	}
}

void median_corection(BITMAPINFOHEADER bf, RGBQUAD **RGB)
{
	unsigned char masg[CONST_MIND];//массив значений канала rgbGreen
	unsigned char masb[CONST_MIND];//массив значений канала rgbBlue
	unsigned char masr[CONST_MIND];//массив значений канала rgbRed

	int count_pixel = 0;

	for (int i = 0; i < bf.biHeight; i++)
	{
		for (int j = 0; j < bf.biWidth; j++)
		{			
			count_pixel = write_mas(masr, masg, masb, bf, RGB, i, j);

			bouble_sort_up(masr, count_pixel);
			bouble_sort_up(masb, count_pixel);
			bouble_sort_up(masg, count_pixel);

			RGB[i][j].rgbBlue = masb[count_pixel / 2];
			RGB[i][j].rgbGreen = masg[count_pixel / 2];
			RGB[i][j].rgbRed = masr[count_pixel / 2];

		}
	}
}

int write_mas(unsigned char *masr, unsigned char *masg, unsigned char *masb, BITMAPINFOHEADER bf, RGBQUAD **RGB, int x, int y)
{
	int step = 1;
	int count_pixel = 0;

	if (x - step >= 0 && y - step >= 0)
	{
		masr[count_pixel] = RGB[x - step][y - step].rgbRed;
		masg[count_pixel] = RGB[x - step][y - step].rgbGreen;
		masb[count_pixel] = RGB[x - step][y - step].rgbBlue;
		count_pixel++;
	}

	if (x - step >= 0)
	{
		masr[count_pixel] = RGB[x - step][y].rgbRed;
		masg[count_pixel] = RGB[x - step][y].rgbGreen;
		masb[count_pixel] = RGB[x - step][y].rgbBlue;
		count_pixel++;
	}

	if (x - step >= 0 && y + step < bf.biWidth)
	{
		masr[count_pixel] = RGB[x - step][y + step].rgbRed;
		masg[count_pixel] = RGB[x - step][y + step].rgbGreen;
		masb[count_pixel] = RGB[x - step][y + step].rgbBlue;
		count_pixel++;
	}

	if (y + step < bf.biWidth)
	{
		masr[count_pixel] = RGB[x][y + step].rgbRed;
		masg[count_pixel] = RGB[x][y + step].rgbGreen;
		masb[count_pixel] = RGB[x][y + step].rgbBlue;
		count_pixel++;
	}

	if (x + step < bf.biHeight && y + step < bf.biWidth)
	{
		masr[count_pixel] = RGB[x + step][y + step].rgbRed;
		masg[count_pixel] = RGB[x + step][y + step].rgbGreen;
		masb[count_pixel] = RGB[x + step][y + step].rgbBlue;
		count_pixel++;
	}

	if (x + step < bf.biHeight)
	{
		masr[count_pixel] = RGB[x + step][y].rgbRed;
		masg[count_pixel] = RGB[x + step][y].rgbGreen;
		masb[count_pixel] = RGB[x + step][y].rgbBlue;
		count_pixel++;
	}

	if (x + step < bf.biHeight && y - step >= 0)
	{
		masr[count_pixel] = RGB[x + step][y - step].rgbRed;
		masg[count_pixel] = RGB[x + step][y - step].rgbGreen;
		masb[count_pixel] = RGB[x + step][y - step].rgbBlue;
		count_pixel++;
	}

	if (y - step >= 0)
	{
		masr[count_pixel] = RGB[x][y - step].rgbRed;
		masg[count_pixel] = RGB[x][y - step].rgbGreen;
		masb[count_pixel] = RGB[x][y - step].rgbBlue;
		count_pixel++;
	}

	masr[count_pixel] = RGB[x][y].rgbRed;
	masg[count_pixel] = RGB[x][y].rgbGreen;
	masb[count_pixel] = RGB[x][y].rgbBlue;
	count_pixel++;

	return count_pixel;
}