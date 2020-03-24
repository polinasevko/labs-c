// 4.1.18.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

void checkDigit(char str[]) {
	for (int i = 0; str[i] != '\0'; i++) {
		if (isdigit(str[i]) == 0) {
			printf("Invalid input. Try more.");
			exit(0);
		}
	}
}

int func(char str[], int count, int chislo) {
	static int i = 0;
	if (count >= 0) {
		chislo += (int)pow(10, i) * ((int)str[count] - 48);
		i++;
		return func(str, --count, chislo);
	}
	return chislo;
}

int main()
{
	char str[20] = "";
	int count = 0;
	printf("Enter the number: ");
	scanf_s("%s", str, 20);
	checkDigit(str);
	while(str[count] != '\0') {
		count++;
	}
	int chislo = 0;
	chislo = func(str, count - 1, chislo);
	printf("%d", chislo);
	return 0;
}