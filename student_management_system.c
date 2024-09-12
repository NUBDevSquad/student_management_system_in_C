#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fp, *temp_fp, *fpt, *temp_fpt;
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

struct teacher_object
{
    char name[50];
    char phone[50];
    char department[50];
    char acronym[50];
    char subject_code[50];
} teacher;

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
void find_by_roll();
void total_student();
void delete_student();
void add_teacher();
void teacher_list();
void update_teacher();
void delete_teacher();
void find_teacher_by_arc();
void find_teacher_by_subject_code();
void find_student_by_teacher_arc();

int main()
{
    int input;

    while (1)
    {
        clear_screen();
        printf(" <== School Management System ==>\n");
        printf(" 1. Add Student\n");
        printf(" 2. Student List\n");
        printf(" 3. Find By Roll\n");
        printf(" 4. Total Students\n");
        printf(" 5. Update Student\n");
        printf(" 6. Delete Student\n");
        printf(" 7. Add Teacher Details\n");
        printf(" 8. Teacher List\n");
        printf(" 9. Update Teacher\n");
        printf(" 10. Delete a Teacher\n");
        printf(" 11. Find teacher by acronym\n");
        printf(" 12. Find teacher by subject code\n");
        printf(" 13. Find student list by  teacher acronym\n");
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
            total_student();
            break;

        case 5:
            update_a_student();
            break;

        case 6:
            delete_student();
            break;

        case 7:
            add_teacher();
            break;

        case 8:
            teacher_list();
            break;

        case 9:
            update_teacher();
            break;
        case 10:
            delete_teacher();
            break;

        case 11:
            find_teacher_by_arc();
            break;

        case 12:
            find_teacher_by_subject_code();
            break;

        case 13:
            find_student_by_teacher_arc();
            break;

        case 0:
            // Close the connection to the database
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
        printf(" Error opening file. you don't have any data. \n");
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

    // Open the file in read and write binary mode
    fp = fopen("student.txt", "rb+");
    if (fp == NULL)
    {
        printf(" Error opening file. you don't have any data. \n");
        exit(1);
    }

    int found = 0;
    int student_roll;
    printf("\n Enter student roll number: ");
    scanf("%d", &student_roll);

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

void find_by_roll()
{
    // Open the file in read and write binary mode
    fp = fopen("student.txt", "rb+");
    if (fp == NULL)
    {
        printf(" Error opening file. you don't have any data. \n");
        exit(1);
    }

    clear_screen();
    printf("\n <== Find Student Details By Roll ==>\n");
    printf(" ----------------------------------\n\n");

    int found = 0;
    int student_roll;
    printf("\n Enter student roll number: ");
    scanf("%d", &student_roll);

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

    // Open the file in read binary mode
    fp = fopen("student.txt", "rb");
    if (fp == NULL)
    {
        printf(" Error opening file. you don't have any data. \n");
        exit(1);
    }

    int count = 0;

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

    // Open the original file in read binary mode
    fp = fopen("student.txt", "rb");
    if (fp == NULL)
    {
        printf(" Error opening file. you don't have any data. \n");
        exit(1);
    }

    int found = 0;
    int student_roll;
    printf("\n Enter student roll number: ");
    scanf("%d", &student_roll);

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

void add_teacher()
{
    clear_screen();
    //  opens the file name teacher in append binary mode
    fpt = fopen("teacher.txt", "ab");

    printf("\n <== Add Teacher Details ==>\n");
    printf(" ----------------------------------\n");

    //  take input from the user
    getchar();
    printf(" Enter name: ");
    fgets(teacher.name, sizeof(teacher.name), stdin);
    // Remove trailing newline character if it exists
    teacher.name[strcspn(teacher.name, "\n")] = 0;

    printf(" Enter phone number: ");
    fgets(teacher.phone, sizeof(teacher.phone), stdin);
    teacher.phone[strcspn(teacher.phone, "\n")] = 0;

    printf(" Enter department name: ");
    fgets(teacher.department, sizeof(teacher.department), stdin);
    teacher.department[strcspn(teacher.department, "\n")] = 0;

    printf(" Enter teacher acronym: ");
    fgets(teacher.acronym, sizeof(teacher.acronym), stdin);
    teacher.acronym[strcspn(teacher.acronym, "\n")] = 0;

    printf(" Enter subject code: ");
    fgets(teacher.subject_code, sizeof(teacher.subject_code), stdin);
    teacher.subject_code[strcspn(teacher.subject_code, "\n")] = 0;

    printf(" %-30s %-20s %-20s %-15s %-15s \n", "Name", "Phone Number", "Department", "Acronym", "Subject Code");
    printf(" -------------------------------------------------------------------------------------------------------------------\n");
    printf(" %-30s %-20s %-20s %-15s %-15s \n", teacher.name, teacher.phone, teacher.department, teacher.acronym, teacher.subject_code);

    printf("\n Teacher Added Successfully");

    //  writes the data pointed to by &teacher to the file referenced by fpt
    fwrite(&teacher, sizeof(teacher), 1, fpt);

    //  closes the file
    fclose(fpt);
}

void teacher_list()
{
    clear_screen();
    printf("\n <== Teacher List ==>\n");
    printf(" ----------------------------------\n");

    // Open the file in read and write binary mode
    fpt = fopen("teacher.txt", "rb+");
    if (fpt == NULL)
    {
        printf(" Error opening file. you don't have any data. \n");
        exit(1);
    }

    printf(" %-30s %-20s %-20s %-15s %-15s \n", "Name", "Phone Number", "Department", "Acronym", "Subject Code");
    printf(" -------------------------------------------------------------------------------------------------------------------\n");
    // iterate teacher.txt to find all teacher
    while (fread(&teacher, sizeof(teacher), 1, fpt))
    {

        printf(" %-30s %-20s %-20s %-15s %-15s \n", teacher.name, teacher.phone, teacher.department, teacher.acronym, teacher.subject_code);
    }

    // Close the file
    fclose(fpt);
};

void update_teacher()
{
    clear_screen();
    printf("\n <== Update Teacher Details ==>\n");
    printf(" ----------------------------------\n\n");

    // Open the file in read and write binary mode
    fpt = fopen("teacher.txt", "rb+");
    if (fpt == NULL)
    {
        printf(" Error opening file. you don't have any data. \n");
        exit(1);
    }

    int found = 0;
    char teacher_acronym[10];

    printf("\n Enter teacher acronym: ");
    scanf("%s", teacher_acronym);

    // Find teacher by acronym in teacher.txt
    while (fread(&teacher, sizeof(teacher), 1, fpt))
    {
        if (strcmp(teacher.acronym, teacher_acronym) == 0)
        {
            found = 1;
            break;
        }
    }

    // If teacher is found, update their details
    if (found)
    {
        struct teacher_object updated_teacher; // Use the correct struct

        printf("\n Enter updated teacher details\n");
        printf(" ----------------------------------\n");

        // Take input from the user
        getchar(); // Clear the newline from the buffer
        printf(" Enter name: ");
        fgets(updated_teacher.name, sizeof(updated_teacher.name), stdin);
        updated_teacher.name[strcspn(updated_teacher.name, "\n")] = 0; // Remove trailing newline

        printf(" Enter phone number: ");
        fgets(updated_teacher.phone, sizeof(updated_teacher.phone), stdin);
        updated_teacher.phone[strcspn(updated_teacher.phone, "\n")] = 0;

        printf(" Enter department name: ");
        fgets(updated_teacher.department, sizeof(updated_teacher.department), stdin);
        updated_teacher.department[strcspn(updated_teacher.department, "\n")] = 0;

        printf(" Enter teacher acronym: ");
        fgets(updated_teacher.acronym, sizeof(updated_teacher.acronym), stdin);
        updated_teacher.acronym[strcspn(updated_teacher.acronym, "\n")] = 0;

        printf(" Enter subject code: ");
        fgets(updated_teacher.subject_code, sizeof(updated_teacher.subject_code), stdin);
        updated_teacher.subject_code[strcspn(updated_teacher.subject_code, "\n")] = 0;

        // Seek back to overwrite the current teacher entry
        fseek(fpt, -sizeof(teacher), SEEK_CUR);
        fwrite(&updated_teacher, sizeof(updated_teacher), 1, fpt);

        printf("\n Teacher details updated successfully.\n\n");

        // Display updated data
        printf(" %-30s %-20s %-20s %-15s %-15s \n", "Name", "Phone Number", "Department", "Acronym", "Subject Code");
        printf(" -------------------------------------------------------------------------------------------------------------------\n");
        printf(" %-30s %-20s %-20s %-15s %-15s \n", updated_teacher.name, updated_teacher.phone, updated_teacher.department, updated_teacher.acronym, updated_teacher.subject_code);
    }
    else
    {
        printf("\n Teacher with acronym %s not found.\n", teacher_acronym);
    }

    // Close the file
    fclose(fpt);
}

void delete_teacher()
{
    clear_screen();
    printf("\n <== Delete Teacher Using acronym ==>\n");
    printf(" ----------------------------------\n\n");

    // Open the file in read and write binary mode
    fpt = fopen("teacher.txt", "rb+");
    if (fpt == NULL)
    {
        printf(" Error opening file. you don't have any data. \n");
        exit(1);
    }

    // Open a temporary file in write binary mode
    temp_fpt = fopen("temp_teacher.txt", "wb");

    int found = 0;
    char teacher_acronym[10];

    printf("\n Enter teacher acronym: ");
    scanf("%s", teacher_acronym);

    // Copy data from original file to temporary file, skipping the record to delete
    while (fread(&teacher, sizeof(teacher), 1, fpt))
    {
        if (strcmp(teacher.acronym, teacher_acronym) == 0)
        {
            found = 1;
            break;
        }
        else
        {
            fwrite(&teacher, sizeof(teacher), 1, temp_fpt);
        }
    }

    // Close the files
    fclose(fpt);
    fclose(temp_fpt);

    // Replace original file with temporary file
    remove("teacher.txt");
    rename("temp_teacher.txt", "teacher.txt");

    // If teacher was found and deleted
    if (found)
    {
        printf("\n Teacher Deleted successfully.\n\n");
    }
    else
    {
        printf("\n Teacher with this acronym %s not found. \n", teacher_acronym);
    }
};

void find_teacher_by_arc()
{
    clear_screen();
    printf("\n <== Find Teacher Details By Acronym ==>\n");
    printf(" ----------------------------------\n\n");

    // Open the file in read and write binary mode
    fpt = fopen("teacher.txt", "rb+");
    if (fpt == NULL)
    {
        printf(" Error opening file. you don't have any data. \n");
        exit(1);
    }

    int found = 0;
    char teacher_acronym[10];

    printf("\n Enter teacher acronym: ");
    scanf("%s", teacher_acronym);

    // Find teacher by acronym in teacher.txt
    while (fread(&teacher, sizeof(teacher), 1, fpt))
    {
        if (strcmp(teacher.acronym, teacher_acronym) == 0)
        {
            found = 1;
            printf(" %-30s %-20s %-20s %-15s %-15s \n", "Name", "Phone Number", "Department", "Acronym", "Subject Code");
            printf(" -------------------------------------------------------------------------------------------------------------------\n");
            printf(" %-30s %-20s %-20s %-15s %-15s \n", teacher.name, teacher.phone, teacher.department, teacher.acronym, teacher.subject_code);

            break;
        }
    }

    if (found == 0)
    {
        printf("\n Teacher with acronym %s not found.\n", teacher_acronym);
    }

    // Close the file
    fclose(fpt);
};

void find_teacher_by_subject_code()
{
    clear_screen();
    printf("\n <== Find Teacher Details By Subject Code ==>\n");
    printf(" ----------------------------------\n\n");

    // Open the file in read and write binary mode
    fpt = fopen("teacher.txt", "rb+");
    if (fpt == NULL)
    {
        printf(" Error opening file. you don't have any data. \n");
        exit(1);
    }

    int found = 0;
    char subject_code[10];

    printf("\n Enter teacher acronym: ");
    scanf("%s", subject_code);

    // Find teacher by acronym in teacher.txt
    while (fread(&teacher, sizeof(teacher), 1, fpt))
    {
        if (strcmp(teacher.subject_code, subject_code) == 0)
        {
            found = 1;
            printf(" %-30s %-20s %-20s %-15s %-15s \n", "Name", "Phone Number", "Department", "Acronym", "Subject Code");
            printf(" -------------------------------------------------------------------------------------------------------------------\n");
            printf(" %-30s %-20s %-20s %-15s %-15s \n", teacher.name, teacher.phone, teacher.department, teacher.acronym, teacher.subject_code);

            break;
        }
    }

    if (found == 0)
    {
        printf("\n Teacher with acronym %s not found.\n", subject_code);
    }

    // Close the file
    fclose(fpt);
};

void find_student_by_teacher_arc()
{
    clear_screen();
    printf("\n <== Find Students Details By Teacher Acronym ==>\n");
    printf(" ----------------------------------\n\n");

    // Open the teacher file in read and write binary mode
    fpt = fopen("teacher.txt", "rb+");
    if (fpt == NULL)
    {
        printf(" Error opening teacher file.  you don't have any data. \n");
        exit(1);
    }

    // Open the student file in read and write binary mode
    fp = fopen("student.txt", "rb+");
    if (fp == NULL)
    {
        printf(" Error opening student file.  you don't have any data.\n");
        fclose(fpt);
        exit(1);
    }

    int found = 0;
    int found_student = 0;
    char acronym[10];
    char subject_code[10];

    printf("\n Enter teacher acronym: ");
    scanf("%s", acronym);

    // Find teacher by acronym in teacher.txt
    while (fread(&teacher, sizeof(teacher), 1, fpt))
    {
        if (strcmp(teacher.acronym, acronym) == 0)
        {
            found = 1;
            strcpy(subject_code, teacher.subject_code);
            break;
        }
    }

    if (found)
    {
        printf(" %-10s %-15s %-15s %-15s %-15s %-15s %-15s \n", "Roll", "First Name", "Last Name", "Department", "Course", "Semester", "Section");
        printf(" -------------------------------------------------------------------------------------------------------------------\n");

        while (fread(&student, sizeof(student), 1, fp))
        {
            if (strcmp(student.course, subject_code) == 0)
            {
                found_student = 1;
                printf(" %-10d %-15s %-15s %-15s %-15s %-15s %-15s \n", student.roll, student.first_name, student.last_name, student.department, student.course, student.semester, student.section);
            }
        }

        if (!found_student)
        {
            printf("\n No students found!\n");
        }
    }
    else
    {
        printf("\n Teacher with acronym %s not found.\n", acronym);
    }

    // Close the files
    fclose(fp);
    fclose(fpt);
}
