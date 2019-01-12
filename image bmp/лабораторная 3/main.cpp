#include "library.h"

int main()
{
	void(*correction_image[])(BITMAPINFOHEADER, RGBQUAD **) = { image_in_negativ, image_in_blackwhite, menu_gamma_correction, menu_median_corection };
	
	setlocale(LC_ALL, ("RUS"));

	int menu = 0;
	
	FILE *image;
	FILE *newimage;
	char name_image[SIZE];
	bool check = false;
	long int check_width;

	BITMAPFILEHEADER bl = { 0 };
	BITMAPINFOHEADER bf = { 0 };
	RGBQUAD **RGB = nullptr;
	
	input_name_image(name_image);

	image = OpenFILE(name_image, "rb");
	if (image == nullptr)
	{
		printf("\n\n����� ����������� �� ��������.\n\n��� ������ ������� ����� �������. ");
		_getch();

		return 1;
	}
	
	newimage = OpenFILE("newimage.bmp", "wb");
	if (newimage == nullptr)
	{
		CloseFILE(image);
		return 2;
	}

	RGB = read_bmp(bl,bf,RGB, image, check_width);
	if (RGB == nullptr)
	{
		CloseFILE(image);
		CloseFILE(newimage);
		return 3;
	}

	if (check_file(bl.bfType) == false)
	{
		CloseFILE(image);
		CloseFILE(newimage);
		delete_mas(bf.biHeight, RGB);
		return 4;
	}

	do
	{
		printf("\n�������� ��������:\n");
		printf("1. �������������� ����������� � �������.\n");
		printf("2. �������������� ����������� � �����-�����.\n");
		printf("3. �������� �����-�������� �����������.\n");
		printf("4. �������� ��������� ���������� ������������.\n");
		printf("5. �����.\n");
		printf("\n���� �������:");

		while (scanf_s("%d", &menu) != 1 || menu < 1 || menu >6)
		{
			rewind(stdin);
			printf("\n��������� ����:");
		}

		if (menu != 5)
			correction_image[menu - 1](bf, RGB);
		else
			break;

		system("cls");
		printf("����������� ����������\n");

	} while (1);
	

	fwrite_bmp(bl, bf, RGB, newimage, check_width);

	delete_mas(bf.biHeight, RGB);

	CloseFILE(image);
	CloseFILE(newimage);

	return 0;
}