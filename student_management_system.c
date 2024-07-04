#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <postgresql/libpq-fe.h>

struct student_object
{
    int roll;
    char first_name[100];
    char last_name[100];
    char department[100];
    char courses[200];
    char semester[50];
    char section[50];
    char emil[50];
} student;

FILE *fp, *temp_fp;

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void createTables(PGconn *conn);
void connectionBD(PGconn **conn);
void add_student(PGconn *conn);
void student_list(PGconn *conn);
void update_a_student();
void find_by_first_name();
void find_by_roll();
void total_student();
void delete_student();

int main()
{
    int input;
    PGconn *conn = NULL;

    // connecting to Database
    connectionBD(&conn);

    while (1)
    {
        clear_screen();
        printf(" <== Student Management System ==>\n");
        printf(" 1. Add Student\n");
        printf(" 2. Student List\n");
        printf(" 3. Find student By Roll\n");
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
            add_student(conn);
            break;

        case 2:
            student_list(conn);
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
            printf(" 7. Add Teacher Details\n");
            break;

        case 8:
            printf(" 8. Teacher List\n");
            break;

        case 9:
            printf(" 9. Update Teacher\n");
            break;
        case 10:
            printf(" 10. Delete a Teacher\n");
            break;

        case 11:
            printf(" 11. Find teacher by acronym\n");
            break;

        case 12:
            printf(" 12. Find teacher by subject code\n");
            break;

        case 13:
            printf(" 13. Find student list by  teacher acronym\n");
            break;

        case 0:
            // Close the connection to the database
            PQfinish(conn);
            exit(1);
            break;

        default:
            clear_screen();
            printf(" Invalid Choice...\n\n");
            break;
        }
        printf("\n\n Press Any Key To Continue...");
        // Clear newline character from scan
        while ((getchar()) != '\n')
            ;
        getchar();
    }

    return 0;
}

void connectionBD(PGconn **conn)
{
    // Establish connection to the database
    *conn = PQconnectdb("dbname=student_management_system user=postgres password=postgres host=localhost port=5432");

    // Check if the connection was successful
    if (PQstatus(*conn) != CONNECTION_OK)
    {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(*conn));
        PQfinish(*conn);
        exit(1);
    }
    else
    {
        printf("Database connected\n");
    }

    // Create tables
    createTables(*conn);
}

void createTables(PGconn *conn)
{
    PGresult *res;

    // SQL statements to create tables
    const char *createStudentsTable = "CREATE TABLE IF NOT EXISTS students ("
                                      "id SERIAL PRIMARY KEY,"
                                      "first_name VARCHAR(100) NOT NULL,"
                                      "last_name VARCHAR(100) NOT NULL,"
                                      "roll INT UNIQUE NOT NULL,"
                                      "department VARCHAR(100),"
                                      "courses VARCHAR(200),"
                                      "semester VARCHAR(50),"
                                      "section VARCHAR(50),"
                                      "email VARCHAR(50) UNIQUE"
                                      ");";

    const char *createTeachersTable = "CREATE TABLE IF NOT EXISTS teachers ("
                                      "id SERIAL PRIMARY KEY,"
                                      "name VARCHAR(100) NOT NULL,"
                                      "email VARCHAR(100) UNIQUE NOT NULL,"
                                      "acronym VARCHAR(100) UNIQUE NOT NULL,"
                                      "phone_number VARCHAR(100),"
                                      "email VARCHAR(100) UNIQUE NOT NULL,"
                                      "department VARCHAR(100),"
                                      "position VARCHAR(100)"
                                      ");";

    // Execute SQL to create students table
    res = PQexec(conn, createStudentsTable);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "CREATE TABLE students failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }
    PQclear(res);

    // Execute SQL to create teachers table
    res = PQexec(conn, createTeachersTable);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "CREATE TABLE teachers failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }
    PQclear(res);
}

void add_student(PGconn *conn)
{
    clear_screen();
    int roll;
    char first_name[50], last_name[50], email[50], department[50], courses[200], semester[50], section[50];
    PGresult *res;

    printf("\n <== Add Student Details ==>\n");
    printf(" ----------------------------------\n");

    //  take input from the user
    getchar();
    printf(" Enter the first name: ");
    fgets(first_name, sizeof(first_name), stdin);
    // Remove trailing newline character if it exists
    first_name[strcspn(first_name, "\n")] = 0;

    printf(" Enter the last name: ");
    fgets(last_name, sizeof(last_name), stdin);
    last_name[strcspn(last_name, "\n")] = 0;

    printf(" Enter the roll number: ");
    scanf("%d", &roll);
    getchar();

    printf(" Enter your email: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = 0;

    printf(" Enter the department name: ");
    fgets(department, sizeof(department), stdin);
    department[strcspn(department, "\n")] = 0;

    printf(" Enter the semester: ");
    fgets(semester, sizeof(semester), stdin);
    semester[strcspn(semester, "\n")] = 0;

    printf(" Enter the section: ");
    fgets(section, sizeof(section), stdin);
    section[strcspn(section, "\n")] = 0;

    printf(" Enter the course ids (e.g. '123,1234,125'): ");
    fgets(courses, sizeof(courses), stdin);
    courses[strcspn(courses, "\n")] = 0;

    // Construct the SQL INSERT query
    char query[2048]; // Increased buffer size for potential larger queries
    snprintf(query, sizeof(query),
             "INSERT INTO students (first_name, last_name, roll, department, semester, section, email, courses) "
             "VALUES ('%s', '%s', %d, '%s', '%s', '%s', '%s', '%s');",
             first_name, last_name, roll, department, semester, section, email, courses);

    // Execute the SQL query
    res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "INSERT INTO students failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return;
    }

    printf("Student added successfully!\n");
    PQclear(res);

    printf(" %-5s %-10s %-10s %-22s %-10s %-25s %-7s %-6s \n", "Roll", "First Name", "Last Name", "Email", "Department", "Courses", "Semester", "Section");
    printf(" -------------------------------------------------------------------------------------------------------------------\n");
    printf(" %-5d %-10s %-10s %-22s %-10s %-25s %-7s %-6s \n", roll, first_name, last_name, email, department, courses, semester, section);

    printf("\n Student Added Successfully");
}

void student_list(PGconn *conn)
{
    clear_screen();
    printf("\n <== Students List ==>\n");
    printf(" ----------------------------------\n");

    // SQL query to select all students
    const char *query = "SELECT roll, first_name, last_name, department, courses, semester, section FROM students";

    // Execute the query
    PGresult *res = PQexec(conn, query);

    // Check for successful execution
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
        PQclear(res);
        return;
    }

    printf(" %-10s %-15s %-15s %-15s %-15s %-15s %-15s \n", "Roll", "First Name", "Last Name", "Department", "Course", "Semester", "Section");
    printf(" -------------------------------------------------------------------------------------------------------------------\n");

    // Fetch and print each row
    int rows = PQntuples(res);
    for (int i = 0; i < rows; i++)
    {
        printf(" %-10s %-15s %-15s %-15s %-15s %-15s %-15s \n",
               PQgetvalue(res, i, 0), // roll
               PQgetvalue(res, i, 1), // first_name
               PQgetvalue(res, i, 2), // last_name
               PQgetvalue(res, i, 3), // department
               PQgetvalue(res, i, 4), // courses
               PQgetvalue(res, i, 5), // semester
               PQgetvalue(res, i, 6)  // section
        );
    }

    // Clear the result
    PQclear(res);
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
        fgets(updated_student.courses, sizeof(updated_student.courses), stdin);
        updated_student.courses[strcspn(updated_student.courses, "\n")] = 0;

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
        printf(" %-10d %-15s %-15s %-15s %-15s %-15s %-15s \n", updated_student.roll, updated_student.first_name, updated_student.last_name, updated_student.department, updated_student.courses, updated_student.semester, updated_student.section);
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
            printf(" %-10d %-15s %-15s %-15s %-15s %-15s %-15s \n", student.roll, student.first_name, student.last_name, student.department, student.courses, student.semester, student.section);
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
            printf(" %-10d %-15s %-15s %-15s %-15s %-15s %-15s \n", student.roll, student.first_name, student.last_name, student.department, student.courses, student.semester, student.section);
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
