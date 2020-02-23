// ConsoleApplication2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <stdio.h>

int main(void)
{
	char x[20] = "";
	printf("Enter the number: ");
	scanf_s("%s", x, 20);
	int sumInt = 0;
	int sumFr = 0;
	int i = 0;

	// Sign Check
	if (x[i] == '-' || x[i] == '+')
		i++;
	// Check for points
	int counter = 0;
	int j = 0;
	for (j = 0; j < 20; j++) 
	{
		if (x[j] == '.') 
		{
			counter++;
			if ((i == 1 && j == 1) || x[j + 1] == '\0' || x[0] == '.') 
			{
				printf("Incorrect dotting. Try again.");
				return 0;
			}
		}
	}
	if (counter > 1) 
	{
		printf("Too many points. Try again.");
		return 0;
	}
	// Check for extra characters
	for (j = i; x[j] != '\0'; j++) 
	{
		if (x[j] != '.' && isdigit(x[j]) == 0)
		{
			printf("Extra characters. Try again.");
			return 0;
		}
	}

	while (x[i] != '.' && x[i]) 
	{
		sumInt += x[i] - 48;
		i++;
	}
	i++;
	if (counter == 0)
	{
		sumFr = 0;
	}
	else 
	{
		while (x[i] != '\0')
		{
			sumFr += x[i] - 48;
			i++;
		}
	}
	printf("The sum of the integer numbers is %d\n\n", sumInt);
	printf("The sum of the fractional numbers is %d\n\n", sumFr);
	if (sumInt > sumFr)
	{
		printf("The largest amount is %d\n", sumInt);
	}
	else if (sumInt < sumFr)
	{
		printf("The largest amount is %d\n", sumFr);
	}
	else
	{
		printf("Amounts = %d, they are equal\n", sumFr);
	}
	return 0;
}
