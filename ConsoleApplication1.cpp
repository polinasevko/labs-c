// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <stdio.h>
#include <math.h>
#include <conio.h>
#define M_PI		3.14159265358979323846

// Exit the program
void Exit(void)
{
	exit(0);
}
// Information about the version and author of the program
void Inf(void)
{
	printf("Author: Sevko Polina Romanovna, gr. 953502.\nVersion: 1.0");
	_getch();
}
// Counting the volume of the cone,
void VolCone(int rad)
{
	double vol = 0;
	vol = M_PI * pow(rad, 3) / 3;
	printf("Volume of the cone is %f", vol);
	_getch();
}
// Counting the length of the side of the square around which the circle is described.
void SideSq(int rad) 
{
	double side = 0;
	side = rad * pow(2, 0.5);
	printf("Side of the square is %f", side);
	_getch();
}
// Circumference calculation.
void Circumference(int rad) 
{
	double circumference = 0;
	circumference = 2 * M_PI * rad;
	printf("Circumference is %f", circumference);
	_getch();
}
// Calculation of the area of the sector of a circle formed by angle A
void SecArea(int rad)
{
	double secArea = 0;
	int A = 0;
	printf("Enter the angle of the sector in degrees ");
	scanf_s("%d", &A);
	secArea = M_PI * pow(rad, 2) * A / 360;
	printf("The area of the sector is %f", secArea);
	_getch();
}
// Circle area calculation
void CirArea(int rad) 
{
	double cirArea = 0;
	cirArea = M_PI * pow(rad, 2);
	printf("The area of the circle is %f", cirArea);
	_getch();
}
// Radius input
void RadInput(int *rad)
{
	printf("Enter the radius of the circle as an integer. ");
	scanf_s("%d", &(*rad));
}

int main(void)
{
	int oper = 0;
	int rad = 0;
	RadInput(&rad);
	while (1)
	{
		printf("Press the number whose number contains the operation you want to carry out.\n");
		printf("1. Radius input\n");
		printf("2. Circle area calculation.\n");
		printf("3. Calculation of the area of the sector of a circle formed by angle A\n");
		printf("4. Circumference calculation.\n");
		printf("5. Counting the length of the side of the square around which the circle is described.\n");
		printf("6. Counting the volume of the cone, the base of which is a circle, and the height is equal to the entered radius.\n");
		printf("7. Information about the version and author of the program.\n");
		printf("8. Exit the program.\n");
		fflush(stdin);
		scanf_s("%d", &oper);
		if (oper == 1)
		{
			RadInput(&rad);
		}
		else if (oper == 2)
		{
			CirArea(rad);
		}
		else if (oper == 3) 
		{
			SecArea(rad);
		}
		else if (oper == 4)
		{
			Circumference(rad);
		}
		else if (oper == 5)
		{
			SideSq(rad);
		}
		else if (oper == 6)
		{
			VolCone(rad);
		}
		else if (oper == 7)
		{
			Inf();
		}
		else if (oper == 8)
		{
			Exit();
		}
		system("cls");
	}
}