/**
 * @file            : Structure_ranjith.c
 * @brief           : 
 * @author          : Ranjith Kumar K V (ranjithkumarkv@vvdntech.in)
 * @Copyright(c)    : 2012-2013 , VVDN Technologies Pvt. Ltd. Permission is
 *                    hereby granted to everyone in VVDN Technologies to use
 *                    the Software without restriction, including without
 *                    limitation the rights to use, copy, modify, merge,
 *                    publish, distribute, distribute with modifications.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NEWLINE '\n'
#define SPACE ' '
#define SUCCESS 0
#define FAILURE 0
#define COUNT 3
#define TRUE 1
#define MARK_MIN 0
#define MARK_MAX 100
#define MARK_PASS 33
#define OPTION_MIN 0
#define OPTION_MAX 6
#define ARRAY_SIZE 10
#define NAME_LENGTH 20
#define CHECK_LENGTH 2

struct student {
    char first_name[NAME_LENGTH];
    char last_name[NAME_LENGTH];
    int roll_number;
    int marks;
}details[ARRAY_SIZE];

void input();
int number_validation();
void mark_validation(int iterator);
int option_validation();
void name_assigning(int number);
void highest_mark(int number);
void fail(int number);
void grace_mark(int number);
void student_last_name(int number);

int main()
{
    input();
    return SUCCESS;
}

void input()
{
    int number, option, iterator;

    number = 0;
    option = 0;
    iterator = 0;

    printf("Enter the number of entries.\n");
    number = number_validation();
    for (iterator = 0;iterator < number;iterator++){
        printf("Enter the first name of the student in entry %d : \n", \
                iterator+1);
        scanf("%s",details[iterator].first_name);
        printf("Enter the last name of the student in entry %d : \n", \
                iterator+1);
        scanf("%s", details[iterator].last_name);
        printf("Enter the roll number of the student in entry %d : \n", \
                iterator+1);
        number_validation();
        printf("Enter the marks of the student in entry %d : \n",iterator+1);
        mark_validation(iterator);
    }
    printf("The names will be automatically sorted.\n");
    printf("Choose any option from below.\n");
    printf("1) Highest mark student.\n" \
           "2) Students who are failed.\n3) Students who can pass with" \
           "grace marks.\n4) Display only last name of students.\n");
    option = option_validation();
    name_assigning(number);
    switch(option) {
        case 1:
            highest_mark(number);
            break;
        case 2:
            fail(number);
            break;
        case 3:
            grace_mark(number);
            break;
        case 4:
            student_last_name(number);
            break;
    }
}

int number_validation()
{
    int number, count, check, flag;
    char valid;

    number = 0;
    count = 0;
    check = 0;
    flag = 1;

    do {
        if (count < COUNT) {
            count++;
            check = scanf("%d%c", &number, &valid);
            if ((check != CHECK_LENGTH) && ((valid != NEWLINE) ||
                        (valid != SPACE))) {
                printf("Enter the valid integer for number.\n");
                flag = 0;
            }
            else {
                break;
            }
        }
        else {
            printf("Program is terminated due to repeated false inputs.\n");
            exit(FAILURE);
        }
        while (getchar() != NEWLINE);
    }while (flag == SUCCESS);
    return number;
}

void mark_validation(int iterator)
{
    int number, count, check, flag;
    char valid;

    number = 0;
    count = 0;
    check = 0;
    flag = 1;

    do {
        if (count < COUNT) {
            count++;
            flag = 1;
            check = scanf("%d%c", &number, &valid);
            if ((check != CHECK_LENGTH) && (valid != NEWLINE)) {
                printf("Enter the valid integer to mark.\n");
                flag = 0;
            }
            else if (number < MARK_MIN || number > MARK_MAX) {
                printf("Enter the mark between 0 and 100.\n");
                flag = 0;
            }
            else {
                details[iterator].marks = number;
                break;
            }
        }
        else {
            printf("Program is terminated due to repeated false inputs.\n");
            exit(FAILURE);
        }
        while (getchar() != NEWLINE);
    }while (flag == SUCCESS);
}

int option_validation()
{
    int number, count, check, flag;
    char valid;

    number = 0;
    count = 0;
    check = 0;
    flag = 1;

    do {
        if (count < COUNT) {
            count++;
            flag = 1;
            check = scanf("%d%c", &number, &valid);
            if ((check != CHECK_LENGTH) && (valid != NEWLINE)) {
                printf("Enter the valid integer.\n");
                flag = 0;
            }
            else if (number < OPTION_MIN || number > OPTION_MAX ) {
                printf("Enter valid option from the list.\n");
                flag = 0;
            }
            else {
                break;
            }
        }
        else {
            printf("Program is terminated due to repeated false inputs.\n");
            exit(FAILURE);
        }
        while (getchar() != NEWLINE);
    }while (flag == SUCCESS);
    return number;
}

void highest_mark(int number)
{
    int iterator, maximum, loop;

    iterator = 0;
    loop = 0;
    maximum = 0;

    for (iterator = 0;iterator < number;iterator++) {
        maximum = details[0].marks;
        if (maximum < details[iterator].marks) {
            maximum = details[iterator].marks;
            loop = iterator;
        }
        printf("The details of the highest mark student is as follows.\n");
        printf("The name of the student is : ");
        printf("%s %s\n",details[loop].first_name,
                details[loop].last_name);
        printf("The mark scored by the student is : ");
        printf("%d\n", details[loop].marks);
    }
}

void student_last_name(int number)
{
    int iterator;

    iterator = 0;

    for (iterator = 0;iterator < number;iterator++) {
        printf("The last name of the student %d is %s.\n", \
                iterator+1, details[iterator].last_name);
    }
}

void fail(int number)
{
    int iterator;

    iterator = 0;

    printf("The students who are failed are : \n");
    for (iterator = 0;iterator < number;iterator++) {
        if (details[iterator].marks < MARK_PASS) {
            printf("%s %s\n", details[iterator].first_name, \
                    details[iterator].last_name);
        }
    }
}

void grace_mark(int number)
{
    int iterator, grace;

    iterator = 0;
    grace = 0;

    printf("Enter the grace mark to be added.\n");
    grace = number_validation();
    printf("The following students will be passed after adding" \
            "grace marks : \n");
    for (iterator = 0;iterator < number;iterator++) {
        details[iterator].marks += grace;
        if (details[iterator].marks > MARK_PASS) {
            printf("%s %s\n", details[iterator].first_name,
                    details[iterator].last_name);
        }
    }
}


void name_assigning(int number)
{
    int iterator1, iterator2, roll;
    char temproary[40];

    iterator2 = 0;
    roll = 1;
    iterator1 = 0;

    for (iterator1 = 0;iterator1 < number;iterator1++) {
        strcat(details[iterator1].first_name, details[iterator1].last_name);
    }
    for (iterator1 = 0;iterator1 < number;iterator1++) {
        for (iterator2 = 0;iterator2 < number-iterator1-1;iterator2++) {
            if (strcmp(details[iterator2].first_name,
                        details[iterator2+1].first_name) > 1) {
                strcpy(temproary,details[iterator2].first_name);
                strcpy(details[iterator2].first_name, \
                        details[iterator2+1].first_name);
                strcpy(details[iterator2+1].first_name, temproary);
            }
        }
    }
    for (iterator1 = 0;iterator1 < number;iterator1++) {
        details[iterator1].roll_number = roll;
        roll++;
    }
    printf("The names of the students are as follows\n");
    for (iterator1 = 0;iterator1 < number;iterator1++) {
        printf("%d. %s\n",details[iterator1].roll_number,
                details[iterator1].first_name);
    }
}
