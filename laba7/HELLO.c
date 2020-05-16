//6.2.28 Flight Schedule for May!!!

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <string.h>
#include <conio.h>

#define mySize 25

typedef enum 
{
    Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday
} Days;

/* Структура, описывающая обобщенный элемент */
struct Plain {
    char num[mySize]; //номер рейса
    char type[mySize]; //тип самолета
    int spaces; //кол-во своб мест
    char departure[mySize];//место отправления
    char destination[mySize];//место прибытия
    char** interm;//массив промежуточных пунктов
    char depTime[mySize];//время вылета
    Days* day;//дни полета
    char** nameSurname;// имя пассажира
    int countOfDays;
    int countOfInterm;
};

/* Структура, описывающая полеты списка */
typedef struct FlightDay {
    struct Plain* plain;
    char date[mySize];//дата полета
    Days day;//день недели
    int countOfPlains;

    struct FlightDay* next;
    struct FlightDay* prev;
} FlightDay;

/* Структура, описывающая список полетов*/
struct List {
    FlightDay* head;
    FlightDay* tail;
};

char* settime(struct tm* u, char format[]);
void nearFlight(struct List* list);
struct Plain readFile(struct Plain plains, char name[]);
void clearScreen();
int checkSign(int sign, int max);
void delLastChar(char* str);
void createList(struct Plain* plains, struct List* list, int n, char date[mySize], int day);
int checkDayOfWeek(struct Plain plains, int day);
void searchFlight(struct Plain* plain, int n);
int compare(struct Plain plains, char plain[mySize], char str[mySize]);
void print(struct Plain plains);
void landingSheet(struct List* list);
int checkDate(char* date);
int compareInterm(struct Plain plains, char** plain, char str[mySize]);
void sortingPlains(struct Plain* plains, int n);
void orderingTickets(struct List* list);
void ticketPrinting(struct Plain plains, char* date);
void ticketReturn(struct List* list);
FlightDay* toCertainDay(struct List* list);


int main(void)
{
    struct List list;
    list.head = list.tail = NULL;
    int n = 6;
    int i = 0;
    int countDay = 0;
    char name[] = "plain1.TXT";
    char date[] = "01.05";
    int day = 4;
    int nextDate = 0;
    int sign = 0;
    struct Plain* plains = (struct Plain*)malloc(n * sizeof(struct Plain));
    if (plains == NULL) {
        printf("Allocation failure.");
        exit(0);
    }
    for (i = 0; i < n; i++) {
        plains[i] = readFile(plains[i], name);
        name[5] = name[5] + 1;
    }
    sortingPlains(plains, n);
    for (countDay; countDay < 31; countDay++) {
        createList(plains, &list, n, date, day);
        day++;
        nextDate = (date[0] - '0') * 10 + date[1] - '0' + 1;
        date[0] = nextDate / 10 + '0';
        date[1] = nextDate % 10 + '0';
        if (day == 7) {
            day = 0;
        }
    }

    while (1) {
        puts("Press the desired number");
        puts("1. Search the flight");
        puts("2. Selecting the closest flight to your destination");
        puts("3. Ordering tickets");
        puts("4. Ticket return");
        puts("5. Registration of the landing sheet.");
        puts("6. Exit");
        rewind(stdin);
        sign = getchar() - '0';
        if (checkSign(sign, 6) == 0) {
            puts("Wrong input. Try more.");
            continue;
        }
        switch (sign) {
        case 1: searchFlight(plains, n);  break;
        case 2: nearFlight(&list); break;
        case 3: orderingTickets(&list); break;
        case 4: ticketReturn(&list); break;
        case 5: landingSheet(&list); break;
        default: exit(0);
        }
        _getch();
        clearScreen();
    }
    free(plains);
    return 0;
}

int countOfSimDest(FlightDay* p, char* dest) {
    int count = 0;
    int i = 0;
    for (i = 0; i < p->countOfPlains; i++) {
        if (strcmp(p->plain[i].destination, dest) == 0) {
            count++;
        }
    }
    return count;
}

void ticketReturn(struct List* list) {
    int i = 0;
    int j = 0;
    int count = 0;
    char* name = (char*)malloc(mySize * sizeof(char));
    char* num = (char*)malloc(mySize * sizeof(char));
    FlightDay* p = toCertainDay(list);
    if (p == NULL) return;
    char* dest = (char*)malloc(mySize * sizeof(char));
    if (dest == NULL || name == NULL || num == NULL) {
        printf("Allocation failure.");
        exit(0);
    }
    puts("Enter destination ");
    rewind(stdin);
    gets_s(dest, mySize - 1);
    count = countOfSimDest(p, dest);
    if (count == 0) {
        puts("Flights with this direction are currently not carried out.");
        return;
    }
    else if (count > 1) {
        puts("Enter the flight number");
        rewind(stdin);
        gets_s(num, mySize - 1);
    }
    puts("Enter your name and surname: ");
    rewind(stdin);
    gets_s(name, mySize - 1);
    for (i = 0; i < p->countOfPlains; i++) {
        if (strcmp(p->plain[i].destination, dest) == 0 && (count == 1 || strcmp(p->plain[i].num, num) == 0)) {
            while (strcmp(p->plain[i].nameSurname[j], name) != 0 && j < p->plain[i].spaces - 1) {
                j++;
            }
            if (strcmp(p->plain[i].nameSurname[j], name) == 0) {
                p->plain[i].spaces++;
                p->plain[i].nameSurname[j][0] = '\0';
                puts("Ticket refund made successfully.");
                return;
            }
        }
    }
    puts("Ticket refund made unsuccessfully.");
    free(dest);
    free(name);
    free(num);
}

void ticketPrinting(struct Plain plains, char* date) {
    int i = 0;
    char* name = (char*)malloc(mySize * sizeof(char));
    if (name == NULL) {
        printf("Allocation failure.");
        exit(0);
    }
    puts("Enter your name and surname: ");
    rewind(stdin);
    gets_s(name, mySize - 1);
    while (plains.nameSurname[i][0] != '\0') {
        if (strcmp(plains.nameSurname[i], name) == 0) {
            puts("A ticket for this name has already been ordered. Try more.");
            puts("Enter your name and surname: ");
            rewind(stdin);
            gets_s(name, mySize - 1);
            i = 0;
            continue;
        }
        i++;
    }
    strcpy_s(plains.nameSurname[i], mySize, name);
    clearScreen();
    printf("YOUR TICKET\nName: %s\nDate: %s\n", name, date);
    print(plains);
    free(name);
}

void orderingTickets(struct List* list) {
    int i = 0;
    int count = 0;
    FlightDay* p = toCertainDay(list);
    if (p == NULL) return;
    char* dest = (char*)malloc(mySize * sizeof(char));
    char* num = (char*)malloc(mySize * sizeof(char));
    if (dest == NULL || num == NULL) {
        printf("Allocation failure.");
        exit(0);
    }
    puts("Enter destination ");
    rewind(stdin);
    gets_s(dest, mySize - 1);
    count = countOfSimDest(p, dest);
    if (count == 0) {
        puts("Flights with this direction are currently not carried out.");
        return;
    }
    else if (count > 1) {
        puts("Enter the flight number");
        rewind(stdin);
        gets_s(num, mySize - 1);
    }
    for (i = 0; i < p->countOfPlains; i++) {
        if (strcmp(p->plain[i].destination, dest) == 0 && (count == 1 || strcmp(p->plain[i].num, num) == 0)) {
            if (p->plain[i].spaces > 0) {
                p->plain[i].spaces--;
                ticketPrinting(p->plain[i], p->date);
            }
            else {
                puts("All tickets sold.");
            }
            return;
        }
    }
}

void sortingPlains(struct Plain* plains, int n) {
    int i = 0;
    int j = 0;
    struct Plain temp;
    for (i = 0; i < n - 1; i++)
    {
        for (int j = (n - 1); j > i; j--)
        {
            if (strcmp(plains[j - 1].depTime, plains[j].depTime) == 1)
            {
                temp = plains[j - 1];
                plains[j - 1] = plains[j];
                plains[j] = temp;
            }
        }
    }
}

char* settime(struct tm* u, char format[])
{
    char s[40];
    char* tmp;
    int length = strftime(s, 40, format, u);
    tmp = (char*)malloc(sizeof(s));
    strcpy_s(tmp, 40, s);
    return(tmp);
}

void nearFlight(struct List* list)
{
    struct tm u;
    int i = 0;
    char* today;
    char* date;
    char* hourMin;
    char* dest = (char*)malloc(mySize * sizeof(char));
    if (dest == NULL) {
        printf("Allocation failure.");
        exit(0);
    }
    puts("Enter destination ");
    rewind(stdin);
    gets_s(dest, mySize - 1);
    const time_t timer = time(NULL);
    localtime_s(&u, &timer);
    today = settime(&u, "%d.%m.%Y %H:%M, %A");

    date = settime(&u, "%d.%m");
    hourMin = settime(&u, "%H:%M");

    printf("Time: %s\n", today);
    FlightDay* p = list->head;
    while (strcmp(p->date, date) != 0) {
        p = p->next;
    }
    while (p->next != NULL) {
        for (i = 0; i < p->countOfPlains; i++) {
            if (strcmp(p->plain[i].destination, dest) == 0) {
                if ((strcmp(p->plain[i].depTime, hourMin) == 1 && strcmp(date, p->date) == 0) || strcmp(date, p->date) == -1) {
                    printf("The nearest flight: %s.2020\n", p->date);
                    print(p->plain[i]);
                    return;
                }
            }
        }
        p = p->next;
    }
    puts("Flights with this direction are currently not carried out.");
    free(dest);
}

int checkDate(char* date) {
    int day = 0;
    day = (date[0] - '0') * 10 + date[1] - '0';
    if (day > 31 || day <= 0) {
        return 0;
    }
    if (date[2] != '.' || date[3] != '0' || date[4] != '5') {
        return 0;
    }
    return 1;
}

FlightDay* toCertainDay(struct List* list) {
    char* date = (char*)malloc(6 * sizeof(char));
    int i = 0;
    int j = 0;
    if (date == NULL) {
        printf("Allocation failure.");
        exit(0);
    }
    puts("Enter the date in the format ($$.$$).");
    rewind(stdin);
    gets_s(date, 6);
    if (checkDate(date) == 0) {
        puts("Wrong input. Try more.");
        return NULL;
    }
    FlightDay* p = list->head;
    while (strcmp(p->date, date) != 0) {
        p = p->next;
    }
    free(date);
    return p;
}

void landingSheet(struct List* list) {
    int i = 0;
    int j = 0;
    FlightDay* p = toCertainDay(list);
    if (p == NULL) return;
    for (i = 0; i < p->countOfPlains; i++) {
        print(p->plain[i]);
        for (j = 0; j < p->plain[i].spaces; j++) {
            if (p->plain[i].nameSurname[j][0] == '\0') {
                continue;
            }
            printf("\n%s", p->plain[i].nameSurname[j]);
        }
    }
}

void print(struct Plain plains) {
    int i = 0;
    printf("\n\n\nFlight number: %s, Type of aircraft: %s,\nRoute: %s", plains.num, plains.type, plains.departure);
    if (plains.interm[0][0] != '0') {
        for (i = 0; i < plains.countOfInterm; i++) {
            printf(" - %s", plains.interm[i]);
        }
    }
    printf(" - %s\nDeparture time: %s, Number of free places: %d", plains.destination, plains.depTime, plains.spaces);
}

int compare(struct Plain plains, char plain[mySize], char str[mySize]) {
    if (strcmp(str, plain) == 0) {
        print(plains);
        return 1;
    }
    return 0;
}

int compareInterm(struct Plain plains, char** plain, char str[mySize]) {
    int i = 0;
    for (i = 0; i < plains.countOfInterm; i++) {
        if (strcmp(str, plain[i]) == 0) {
            print(plains);
            return 1;
        }
    }
    return 0;
}

void searchFlight(struct Plain* plains, int n) {
    int i = 0;
    int sign = 0;
    int check = 0;
    char* item = (char*)malloc(mySize * sizeof(char));
    if (item == NULL) {
        printf("Allocation failure.");
        exit(0);
    }
    puts("Search by (press the desired number)");
    puts("1. Flight number");
    puts("2. Type of aircraft");
    puts("3. Place of departure");
    puts("4. Destination");
    puts("5. Departure time");
    puts("6. Intermidiate point");
    rewind(stdin);
    sign = getchar() - '0';
    if (checkSign(sign, 6) == 0) {
        puts("Wrong input. Try more.");
        return;
    }
    puts("Enter the item ");
    rewind(stdin);
    gets_s(item, mySize - 1);
    for (i = 0; i < n; i++) {
        switch (sign) {
        case 1: check += compare(plains[i], plains[i].num, item); break;
        case 2: check += compare(plains[i], plains[i].type, item); break;
        case 3: check += compare(plains[i], plains[i].departure, item); break;
        case 4: check += compare(plains[i], plains[i].destination, item); break;
        case 5: check += compare(plains[i], plains[i].depTime, item); break;
        default: check += compareInterm(plains[i], plains[i].interm, item);
        }
    }
    if (check == 0) {
        puts("Flights with such data do not exist.");
    }
    free(item);
}

int checkDayOfWeek(struct Plain plains, int day) {
    int i = 0;
    while (i < plains.countOfDays) {
        if (plains.day[i] == day) return 1;
        i++;
    }
    return 0;
}

void createList(struct Plain* plains, struct List* list, int n, char date[mySize], int day) {
    FlightDay* p = (FlightDay*)malloc(sizeof(FlightDay));
    int* checkDay = (int*)malloc(n * sizeof(int));
    if (p == NULL || checkDay == NULL) {
        printf("Allocation failure.");
        exit(0);
    }
    int i = 0;
    int j = 0;
    int count = 0;
    strcpy_s(p->date, mySize, date);
    p->day = day;
    for (i = 0; i < n; i++) {
        if (checkDayOfWeek(plains[i], day) == 1) {
            count++;
            checkDay[i] = 1;
        }
        else {
            checkDay[i] = 0;
        }
    }
    p->countOfPlains = count;
    p->plain = (struct Plain*)malloc(count * sizeof(struct Plain));
    if (p->plain == NULL) {
        printf("Allocation failure.");
        exit(0);
    }
    for (i = 0; i < count; i++, j++) {
        for (j; j < n; j++) {
            if (checkDay[j] == 1) break;
        }
        p->plain[i] = plains[j];
    }
    p->next = p->prev = NULL;

    if (list->head == NULL)
        list->head = list->tail = p;
    else {
        list->tail->next = p;
        p->prev = list->tail;
        list->tail = p;
    }
    free(checkDay);
}

int checkSign(int sign, int max) 
{
    int check = 0;
    if (sign < 1 || sign > max) {
        return 0;
    }
    return 1;
}

struct Plain readFile(struct Plain plains, char name[])
{
    FILE* file = NULL;
    errno_t err;
    char buff[512] = "";
    int i = 0;
    int k = 0;
    int j = 0;
    int count = 1;
    err = fopen_s(&file, name, "r");
    if (err == NULL && file == NULL)
    {
        fclose(file);
        printf("Could not open file.");
        exit(0);
    }
    fgets(plains.num, mySize, file);
    fgets(plains.type, mySize, file);
    fgets(buff, BUFSIZ, file);
    plains.spaces = atoi(buff);

    plains.nameSurname = (char**)malloc(plains.spaces * sizeof(char*));
    if (plains.nameSurname == NULL) {
        printf("Allocation failure.");
        exit(0);
    }
    for (i = 0; i < plains.spaces; i++) {
        plains.nameSurname[i] = (char*)malloc(mySize * sizeof(char));
        if (plains.nameSurname[i] == NULL) {
            printf("Allocation failure.");
            exit(0);
        }
        plains.nameSurname[i][0] = '\0';
    }

    fgets(plains.departure, mySize, file);
    fgets(plains.destination, mySize, file);

    fgets(buff, BUFSIZ, file);
    if (buff[0] == '0') {
        plains.interm = (char**)malloc(sizeof(char*));
        if (plains.interm == NULL) {
            printf("Allocation failure.");
            exit(0);
        }
        plains.interm[0] = (char*)malloc(sizeof(char));
        if (plains.interm[0] == NULL) {
            printf("Allocation failure.");
            exit(0);
        }
        strcpy_s(plains.interm[0], 2, "0");
    }
    else {
        for (i = 0; buff[i] != '\0'; i++) {
            if (buff[i] == ',') {
                count++;
            }
        }
        plains.countOfInterm = count;
        plains.interm = (char**)malloc(count * sizeof(char*));
        if (plains.interm == NULL) {
            printf("Allocation failure.");
            exit(0);
        }
        for (i = 0, j = 0; i < count; i++) {
            plains.interm[i] = (char*)malloc(mySize * sizeof(char));
            if (plains.interm[i] == NULL) {
                printf("Allocation failure.");
                exit(0);
            }
            for (j, k = 0; buff[j] != ',' && buff[j] != '\n'; j++, k++) {
                plains.interm[i][k] = buff[j];
            }
            plains.interm[i][k] = '\0';
            j++;
        }
    }

    fgets(plains.depTime, mySize, file);

    fgets(buff, BUFSIZ, file);
    count = 1;
    for (i = 0; buff[i] != '\0'; i++) {
        if (buff[i] == ',') {
            count++;
        }
    }
    plains.countOfDays = count;
    plains.day = (Days*)malloc(count * sizeof(Days));
    if (plains.day == NULL) {
        printf("Allocation failure.");
        exit(0);
    }
    for (i = 0, j = 0; i < count; i++, j += 2) {
        plains.day[i] = buff[j] - '0';
    }
    fclose(file);
    delLastChar(plains.num);
    delLastChar(plains.type);
    delLastChar(plains.departure);
    delLastChar(plains.destination);
    delLastChar(plains.depTime);
    return plains;
}

void delLastChar(char *str) {
    int ind = 0;
    ind = strnlen_s(str, mySize);
    str[ind - 1] = '\0';
}

void clearScreen()
{
    int n;
    for (n = 0; n < 10; n++)
        printf("\n\n\n\n\n\n\n\n\n\n");
}
