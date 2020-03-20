// 3.1.18.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>


using namespace std;

// ArProgr finds the longest arithmetic progression
void ArProgr(int* array, int n) {
    int ind = 0;
    int countAr = 0;
    int max = 0;
    int startInd = 0;
    int endInd = 0;
    int check = 1;
    for (int i = 1; i < n; i++) {
        if (array[i - 1] + array[i + 1] == 2 * array[i] && i != n - 1) {
            if (check) {
                ind = i - 1;
                countAr = 2;
                check = 0;
            }
            countAr++;
        }
        else {
            if (countAr > max) {
                max = countAr;
                startInd = ind;
                endInd = i + 1;
            }
            countAr = 0;
            check = 1;
        }
    }
    if (max == 0) {
        printf("There are no arithmetic progressions");
    }
    else {
        printf("The longest arithmetic progression:\n");
        for (int i = startInd; i < endInd; i++) {
            printf("%d ", array[i]);
        }
    }
}

// GeomProgr finds the longest geometric progression
void GeomProgr(int* array, int n) {
    int ind = 0;
    int countGeom = 0;
    int max = 0;
    int startInd = 0;
    int endInd = 0;
    int check = 1;
    for (int i = 1; i < n; i++) {
        if (array[i - 1] * array[i + 1] == array[i] * array[i] && i != n - 1) {
            if (check) {
                ind = i - 1;
                countGeom = 2;
                check = 0;
            }
            countGeom++;
        }
        else {
            if (countGeom > max) {
                max = countGeom;
                startInd = ind;
                endInd = i + 1;
            }
            countGeom = 0;
            check = 1;
        }
    }
    if (max == 0) {
        printf("\nThere are no geometric progressions\n");
    }
    else {
        printf("\nThe longest geometric progression:\n");
        for (int i = startInd; i < endInd; i++) {
            printf("%d ", array[i]);
        }
    }
}

int main()
{
    int* array;
    int n = 0;
    printf("Enter the number of elements in array ");
    scanf_s("%d", &n);
    array = (int*)malloc(n * sizeof(int));
    if (!array) {
        printf("Allocation failure.");
        exit(0);
    }
    printf("Enter the array ");
    for (int i = 0; i < n; i++) {
        scanf_s("%d", &array[i]);
    }
    ArProgr(array, n);
    GeomProgr(array, n);
    free(array);
    return 0;
}