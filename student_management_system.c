#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fp;
struct student_object
{
    int roll;
    char first_name[50];
    char last_name[50];
    char department[50];
    char course[50];
    char semester[50];
    char section[50];
} student;

void add_student(void);

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
        printf("6.Update Student\n");
        printf("7.Delete Student\n");
        printf("0.Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &input);

        switch (input)
        {
        case 1:
            add_student();
            break;

        case 2:
            printf("Student List");
            break;

        case 3:
            printf("Find By Roll");
            break;

        case 4:
            printf("Find By First Name");
            break;

        case 5:
            printf("Total Students");
            break;

        case 6:
            printf("Update Student");
            break;

        case 7:
            printf("Delete Student");
            break;

        default:
            printf("Invalid Choice...\n\n");
            break;
        }
        printf("\n\nPress Any Key To Continue...");
        getchar();
    }

    return 0;
}

void add_student()
{
    //  opens the file name student in append binary mode
    fp = fopen("student.txt", "ab");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    printf("Add Student Details\n");
    printf("----------------------------------\n");

    //  take input form the user
    getchar();
    printf("Enter the first name: ");
    fgets(student.first_name, sizeof(student.first_name), stdin);
    // Remove trailing newline character if it exists
    student.first_name[strcspn(student.first_name, "\n")] = 0;

    printf("Enter the last name: ");
    fgets(student.last_name, sizeof(student.last_name), stdin);
    student.last_name[strcspn(student.last_name, "\n")] = 0;

    printf("Enter the roll number: ");
    scanf("%d", &student.roll);
    getchar();

    printf("Enter the department name: ");
    fgets(student.department, sizeof(student.department), stdin);
    student.department[strcspn(student.department, "\n")] = 0;

    printf("Enter the course id: ");
    fgets(student.course, sizeof(student.course), stdin);
    student.course[strcspn(student.course, "\n")] = 0;

    printf("Enter the semester: ");
    fgets(student.semester, sizeof(student.semester), stdin);
    student.semester[strcspn(student.semester, "\n")] = 0;

    printf("Enter the section: ");
    fgets(student.section, sizeof(student.section), stdin);
    student.section[strcspn(student.section, "\n")] = 0;

    printf("\nFirst name: %s, last name: %s, roll: %d, department: %s, course: %s, semester: %s, section %s.", student.first_name, student.last_name, student.roll, student.department, student.course, student.semester, student.section);

    printf("\nStudent Added Successfully");

    //  writes the data pointed to by &student to the file referenced by fp
    fwrite(&student, sizeof(student), 1, fp);

    //  closes the file
    fclose(fp);
}