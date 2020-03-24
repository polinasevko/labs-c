// 4.2.18.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <malloc.h>

struct Medicines {
    char name[20] = "";
    char date[11] = "";
    char num[5] = "";
    char cost[10] = "";
};

int FullCost(Medicines *med, int i) {
    int k = 0;
    int j = 0;
    int num = 0;
    int cost = 0;
    int fullCost = 0;
    int tr = 0;
    while (med[i].cost[k] != '\0') {
        k++;
    }
    while (med[i].num[j] != '\0') {
        j++;
    }
    k--;
    j--;
    for (tr = 0, j; j >= 0; j--, tr++) {
        num += (int)pow(10, tr) * (((int)med[i].num[j]) - 48);
    }
    for (tr = 0, k; k >= 0; k--, tr++) {
        cost += (int)pow(10, tr) * (((int)med[i].cost[k]) - 48);
    }
    fullCost = num * cost;
    return fullCost;
}

int main()
{
    Medicines *med = NULL;
    char name[] = "text.txt";
    char buff[512] = "";
    int i = 0;
    int j = 0;
    int k = 0;
    int count = 0;
    FILE* file = NULL;
    int fullCost = 0;
    int cost = 0;
    int num = 0;
    int tr = 0;
    errno_t err;
    setlocale(LC_ALL, "Rus");
    err = fopen_s(&file, name, "r");
    if (!err && !file)
    {
        fclose(file);
        printf("Ñould not open file.");
        exit(0);
    }
    while (!feof(file)) {
        fgets(buff, BUFSIZ, file);
        count++;
    }
    med = (Medicines*)calloc(count, sizeof(Medicines));
    if (!med) {
        printf("Allocation failure.");
        exit(0);
    }
    fseek(file, 0, 0);
    while (j < count) {
        fgets(buff, BUFSIZ, file);
        for (k = 0, i; buff[i] != ' '; i++, k++) {
            med[j].name[k] = buff[i];
        }
        med[j].name[k] = '\0';
        i++;
        for (k = 0, i; buff[i] != ' '; i++, k++) {
            med[j].date[k] = buff[i];
        }
        med[j].date[k] = '\0';
        i++;
        for (k = 0, i; buff[i] != ' '; i++, k++) {
            med[j].num[k] = buff[i];
        }
        med[j].num[k] = '\0';
        i++;
        for (k = 0, i; buff[i] != ' ' && buff[i] != '\n' && buff[i] != '\0'; i++, k++) {
            med[j].cost[k] = buff[i];
        }
        med[j].cost[k] = '\0' ;
        j++;
        i = 0;
    }
    fclose(file);
    j = 6;
    int date = 0;
    for (i = 0; i < count; i++) {
        date = 0;
        fullCost = 0;
        num = 0; 
        cost = 0;
        for (tr = 0, j = 9; j >= 6; j--, tr++) {
            date += (int)pow(10, tr) * (((int)med[i].date[j]) - 48);
        }
        if (date < 2020) {
            fullCost = FullCost(med, i);
            printf("%s %s %s %s Full cost = %d\n", med[i].name, med[i].date, med[i].num, med[i].cost, fullCost);
        }
        else if (date == 2020) {
            date = 0;
            for (tr = 0, j = 4; j >= 3; j--, tr++) {
                date += (int)pow(10, tr) * (((int)med[i].date[j]) - 48);
            }
            if (date < 3) {
                fullCost = FullCost(med, i);
                printf("%s %s %s %s Full cost = %d\n", med[i].name, med[i].date, med[i].num, med[i].cost, fullCost);

            }
            else if (date == 3) {
                date = 0;
                for (tr = 0, j = 1; j >= 0; j--, tr++) {
                    date += (int)pow(10, tr) * (((int)med[i].date[j]) - 48);
                }
                if (date < 24) {
                    fullCost = FullCost(med, i);
                    printf("%s %s %s %s Full cost = %d\n", med[i].name, med[i].date, med[i].num, med[i].cost, fullCost);
                }
            }
        }
    }
    free(med);
    return 0;
}