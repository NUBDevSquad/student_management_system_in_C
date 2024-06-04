#include <stdio.h>
#include <stdlib.h>
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
    int input;

    while (1)
    {
        system("cls");
        printf("<== Student Management System ==>\n");
        printf("1.Add Student\n");
        printf("2.Student List\n");
        printf("3.Find By Roll\n");
        printf("4.Find By First Name\n");
        printf("5.Total Students\n");
        printf("6.UPdate Student\n");
        printf("7.Delete Student\n");
        printf("0.Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &input);

        switch (input)
        {
        case 1:
            printf("Add student");
            break;

        case 2:
            printf("Add student");
            break;

        case 3:
            printf("Add student");
            break;

        case 4:
            printf("Add student");
            break;

        case 5:
            printf("Add student");
            break;

        case 6:
            printf("Add student");
            break;

        case 7:
            printf("Add student");
            break;

        default:
            printf("Invalid Choice...\n\n");
            break;
        }
        printf("\n\nPress Any Key To Continue...");
    }

    return 0;
}