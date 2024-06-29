#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fp, *temp_fp;
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

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void add_student(void);
void student_list();
void update_a_student();
void find_by_first_name();
void find_by_roll();
void total_student();
void delete_student();

int main()
{
    int input;

    while (1)
    {
        clear_screen();
        printf(" <== Student Management System ==>\n");
        printf(" 1. Add Student\n");
        printf(" 2. Student List\n");
        printf(" 3. Find By Roll\n");
        printf(" 4. Find By First Name\n");
        printf(" 5. Total Students\n");
        printf(" 6. Update Student\n");
        printf(" 7. Delete Student\n");
        printf(" 0. Exit\n\n");
        printf(" Enter your choice: ");
        scanf("%d", &input);

        switch (input)
        {
        case 1:
            add_student();
            break;

        case 2:
            student_list();
            break;

        case 3:
            find_by_roll();
            break;

        case 4:
            find_by_first_name();
            break;

        case 5:
            total_student();
            break;

        case 6:
            update_a_student();
            break;

        case 7:
            delete_student();
            break;

        case 0:
            exit(1);
            break;

        default:
            clear_screen();
            printf(" Invalid Choice...\n\n");
            break;
        }
        printf("\n\n Press Any Key To Continue... \n");
        // Clear newline character from scan
        while ((getchar()) != '\n')
            ;
        getchar();
    }

    return 0;
}

void add_student()
{
    clear_screen();
    //  opens the file name student in append binary mode
    fp = fopen("student.txt", "ab");
    if (fp == NULL)
    {
        printf(" Error opening file\n");
        exit(1);
    }

    printf("\n <== Add Student Details ==>\n");
    printf(" ----------------------------------\n");

    //  take input from the user
    getchar();
    printf(" Enter the first name: ");
    fgets(student.first_name, sizeof(student.first_name), stdin);
    // Remove trailing newline character if it exists
    student.first_name[strcspn(student.first_name, "\n")] = 0;

    printf(" Enter the last name: ");
    fgets(student.last_name, sizeof(student.last_name), stdin);
    student.last_name[strcspn(student.last_name, "\n")] = 0;

    printf(" Enter the roll number: ");
    scanf("%d", &student.roll);
    getchar();

    printf(" Enter the department name: ");
    fgets(student.department, sizeof(student.department), stdin);
    student.department[strcspn(student.department, "\n")] = 0;

    printf(" Enter the course id: ");
    fgets(student.course, sizeof(student.course), stdin);
    student.course[strcspn(student.course, "\n")] = 0;

    printf(" Enter the semester: ");
    fgets(student.semester, sizeof(student.semester), stdin);
    student.semester[strcspn(student.semester, "\n")] = 0;

    printf(" Enter the section: ");
    fgets(student.section, sizeof(student.section), stdin);
    student.section[strcspn(student.section, "\n")] = 0;

    printf(" %-10s %-15s %-15s %-15s %-15s %-15s %-15s \n", "Roll", "First Name", "Last Name", "Department", "Course", "Semester", "Section");
    printf(" -------------------------------------------------------------------------------------------------------------------\n");
    printf(" %-10d %-15s %-15s %-15s %-15s %-15s %-15s \n", student.roll, student.first_name, student.last_name, student.department, student.course, student.semester, student.section);

    printf("\n Student Added Successfully");

    //  writes the data pointed to by &student to the file referenced by fp
    fwrite(&student, sizeof(student), 1, fp);

    //  closes the file
    fclose(fp);
}

void student_list()
{
    clear_screen();
    printf("\n <== Students List ==>\n");
    printf(" ----------------------------------\n");

    // Open the file in read and write binary mode
    fp = fopen("student.txt", "rb+");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    printf(" %-10s %-15s %-15s %-15s %-15s %-15s %-15s \n", "Roll", "First Name", "Last Name", "Department", "Course", "Semester", "Section");
    printf(" -------------------------------------------------------------------------------------------------------------------\n");
    // iterate student.txt to find all student
    while (fread(&student, sizeof(student), 1, fp))
    {

        printf(" %-10d %-15s %-15s %-15s %-15s %-15s %-15s \n", student.roll, student.first_name, student.last_name, student.department, student.course, student.semester, student.section);
    }

    // Close the file
    fclose(fp);
}

void update_a_student()
{
    clear_screen();
    printf("\n <== Update Student Details ==>\n");
    printf(" ----------------------------------\n\n");

    int found = 0;
    int student_roll;
    printf("\n Enter student roll number: ");
    scanf("%d", &student_roll);

    // Open the file in read and write binary mode
    fp = fopen("student.txt", "rb+");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    // find student roll from student.txt
    while (fread(&student, sizeof(student), 1, fp))
    {
        if (student.roll == student_roll)
        {
            found = 1;
            break;
        }
    }

    // if student found then update student details
    if (found)
    {
        struct student_object updated_student;

        printf("\n Enter updated student details\n");
        printf(" ----------------------------------\n");

        // take input from the user
        getchar();
        printf(" Enter the first name: ");
        fgets(updated_student.first_name, sizeof(updated_student.first_name), stdin);
        updated_student.first_name[strcspn(updated_student.first_name, "\n")] = 0;

        printf(" Enter the last name: ");
        fgets(updated_student.last_name, sizeof(updated_student.last_name), stdin);
        updated_student.last_name[strcspn(updated_student.last_name, "\n")] = 0;

        printf(" Enter the roll number: ");
        scanf("%d", &updated_student.roll);
        getchar();

        printf(" Enter the department name: ");
        fgets(updated_student.department, sizeof(updated_student.department), stdin);
        updated_student.department[strcspn(updated_student.department, "\n")] = 0;

        printf(" Enter the course id: ");
        fgets(updated_student.course, sizeof(updated_student.course), stdin);
        updated_student.course[strcspn(updated_student.course, "\n")] = 0;

        printf(" Enter the semester: ");
        fgets(updated_student.semester, sizeof(updated_student.semester), stdin);
        updated_student.semester[strcspn(updated_student.semester, "\n")] = 0;

        printf(" Enter the section: ");
        fgets(updated_student.section, sizeof(updated_student.section), stdin);
        updated_student.section[strcspn(updated_student.section, "\n")] = 0;

        // remove current student from student.txt
        fseek(fp, -sizeof(student), SEEK_CUR);
        // updated student data
        fwrite(&updated_student, sizeof(updated_student), 1, fp);
        printf("\n Student details updated successfully.\n\n");

        // showing update result data
        printf(" %-10s %-15s %-15s %-15s %-15s %-15s %-15s \n", "Roll", "First Name", "Last Name", "Department", "Course", "Semester", "Section");
        printf(" -------------------------------------------------------------------------------------------------------------------\n");
        printf(" %-10d %-15s %-15s %-15s %-15s %-15s %-15s \n", updated_student.roll, updated_student.first_name, updated_student.last_name, updated_student.department, updated_student.course, updated_student.semester, updated_student.section);
    }
    else
    {
        printf("\n Student with roll number %d not found. \n", student_roll);
    }

    // Close the file
    fclose(fp);
}

void find_by_first_name()
{
    clear_screen();
    printf("\n <== Find Student Details By First Name ==>\n");
    printf(" ----------------------------------\n\n");

    int found = 0;
    char first_name[50];

    // takeing input from user
    getchar();
    printf(" Enter the first name: ");
    fgets(first_name, sizeof(first_name), stdin);
    first_name[strcspn(first_name, "\n")] = 0;

    // Open the file in read and write binary mode
    fp = fopen("student.txt", "rb+");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    // find student from student.txt using first_name
    while (fread(&student, sizeof(student), 1, fp))
    {
        if (strcmp(student.first_name, first_name) == 0)
        {
            found = 1;
            // showing student details
            printf(" %-10s %-15s %-15s %-15s %-15s %-15s %-15s \n", "Roll", "First Name", "Last Name", "Department", "Course", "Semester", "Section");
            printf(" -------------------------------------------------------------------------------------------------------------------\n");
            printf(" %-10d %-15s %-15s %-15s %-15s %-15s %-15s \n", student.roll, student.first_name, student.last_name, student.department, student.course, student.semester, student.section);
        }
    }

    // if student is not found then  showing not found message
    if (!found)
    {
        printf("\n Student with this first name '%s' not found. \n", first_name);
    }

    // Close the file
    fclose(fp);
};

void find_by_roll()
{
    clear_screen();
    printf("\n <== Find Student Details By Roll ==>\n");
    printf(" ----------------------------------\n\n");

    int found = 0;
    int student_roll;
    printf("\n Enter student roll number: ");
    scanf("%d", &student_roll);

    // Open the file in read and write binary mode
    fp = fopen("student.txt", "rb+");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    // find student roll from student.txt
    while (fread(&student, sizeof(student), 1, fp))
    {
        if (student.roll == student_roll)
        {
            found = 1;
            // showing student details
            printf(" %-10s %-15s %-15s %-15s %-15s %-15s %-15s \n", "Roll", "First Name", "Last Name", "Department", "Course", "Semester", "Section");
            printf(" -------------------------------------------------------------------------------------------------------------------\n");
            printf(" %-10d %-15s %-15s %-15s %-15s %-15s %-15s \n", student.roll, student.first_name, student.last_name, student.department, student.course, student.semester, student.section);
        }
    }

    // if student is not found then  showing not found message
    if (!found)
    {
        printf("\n Student with roll number %d not found. \n", student_roll);
    }

    // Close the file
    fclose(fp);
};

void total_student()
{
    clear_screen();
    printf("\n <== Total Student Count ==>\n");
    printf(" ----------------------------------\n\n");

    int count = 0;

    // Open the file in read binary mode
    fp = fopen("student.txt", "rb");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    // Count the number of students in student.txt
    while (fread(&student, sizeof(student), 1, fp))
    {
        count++;
    }

    printf("\n We Have a Total of %d Students. \n", count);

    // Close the file
    fclose(fp);
}

void delete_student()
{
    clear_screen();
    printf("\n <== Delete Student Using Roll ==>\n");
    printf(" ----------------------------------\n\n");

    int found = 0;
    int student_roll;
    printf("\n Enter student roll number: ");
    scanf("%d", &student_roll);

    // Open the original file in read binary mode
    fp = fopen("student.txt", "rb");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    // Open a temporary file in write binary mode
    temp_fp = fopen("temp.txt", "wb");
    if (temp_fp == NULL)
    {
        printf("Error opening temporary file\n");
        fclose(fp);
        exit(1);
    }

    // Copy data from original file to temporary file, skipping the record to delete
    while (fread(&student, sizeof(student), 1, fp))
    {
        if (student.roll == student_roll)
        {
            found = 1;
        }
        else
        {
            fwrite(&student, sizeof(student), 1, temp_fp);
        }
    }

    // Close the files
    fclose(fp);
    fclose(temp_fp);

    // Replace original file with temporary file
    remove("student.txt");
    rename("temp.txt", "student.txt");

    // If student was found and deleted
    if (found)
    {
        printf("\n Student Deleted successfully.\n\n");
    }
    else
    {
        printf("\n Student with roll number %d not found. \n", student_roll);
    }
}