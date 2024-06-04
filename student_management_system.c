#include <stdio.h>

struct student
{
    int roll;
    char first_name[50];
    char last_name[50];
    char department[50];
    char courses[50];
    char semester[50];
    char section[50];
} students[50];

int main()
{
    printf("<== Student Management System ==>\n");
    return 0;
}