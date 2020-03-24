// 3.2.18.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <malloc.h>

int check(int countI, int countJ, int **array, int n) 
{
    int sum = 0;
    // по вертикали
    for (int i = 0; i < countI; i++) {
        sum += array[i][countJ];
    }
    // по диаг слева-напр
    for (int i = countI - 1, j = countJ - 1; i >= 0 && j >= 0; i--, j--) {
        sum += array[i][j];
    }
    // по диаг справа-нал
    for (int i = countI - 1, j = countJ + 1; i >= 0 && j < n; i--, j++) {
        sum += array[i][j];
    }
    return sum;
}

int main()
{
    int n = 8;
    int** array = (int**)malloc(n * sizeof(int));;
    int* indJ = (int*)malloc(n * sizeof(int));
    if (!indJ) {
        printf("Allocation failure.");
        exit(0);
    }
    if (!array) {
        printf("Allocation failure.");
        exit(0);
    }
    for (int i = 0; i < n; i++) {
        array[i] = (int*)malloc(n * sizeof(int));
        if (!array[i]) {
            printf("Allocation failure.");
            exit(0);
        }
        for (int k = 0; k < n; k++) {
            array[i][k] = 0;
        }
    }
    int ind = 0;
    int j = 0;
    srand(time(NULL));
    ind = rand() % 8;
    array[0][ind] = 1;
    for (int i = 1; i < n; i++) {
        array[i][j] = 1;
        while (check(i, j, array, n)) {
            array[i][j] = 0;
            j++;
            if (j == 8) {
                i -= 2;
                break;
            }
            array[i][j] = 1;
        }
        if (j == 8)
        {
            array[i + 1][indJ[i + 1]] = 0;
            j = indJ[i + 1] + 1;
            if (j == 8) {
                i--;
                array[i + 1][indJ[i + 1]] = 0;
                j = indJ[i + 1] + 1;
            }
        }
        else {
            indJ[i] = j;
            j = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
    free(indJ);
    for (int i = 0; i < n; i++) {
        free(array[i]);
    }
    free(array);
    return 0;
}