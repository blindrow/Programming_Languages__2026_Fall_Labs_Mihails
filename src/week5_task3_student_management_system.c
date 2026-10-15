
// week5_task3_student_management_system.c
// Name: Mihails  Surname: Semjonovs  Student ID: 251ADB194
//
// Task 3: Mini-project – Student management system with file persistence
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task3_student_management_system

#include <stdio.h>
#include <stdlib.h>
#include <string.h>




#include <errno.h>
#include <limits.h>

#include <ctype.h>
#include <math.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define LINE_LEN 256
#define DATA_FILE "students.txt"

typedef struct Student {
    char name[NAME_LEN];
    int id;
    float gpa;
} Student;


int  load_students(Student arr[], int max);

int  save_students(const Student arr[], int count)
;
void add_student(Student arr[], int *count);





void list_students(const Student arr[], int count);
int  read_line(const char *prompt, char *buf, size_t size);

int main(void) {
    Student students[MAX_STUDENTS];
    int count = 0;

    char input[LINE_LEN];
    int running = 1;



    count = load_students(students, MAX_STUDENTS);
    printf("Loaded %d student(s) from %s\n", count, DATA_FILE);

    while (running) {
        printf("\n=== Student Management System ===\n");
        printf("1. List students\n");
        printf("2. Add student\n");

        printf("3. Save and Exit\n");


        int choice;


        if (read_line("Select an option: ", input, sizeof input) != 0) {

            choice = 3;

        } else {
            char *end;

            long value = strtol(input, &end, 10);
            choice = (end != input && *end == '\0') ? (int)value : 0;
        }

        switch (choice) {
            case 1:
                list_students(students, count);
                break;

            case 2:
                add_student(students, &count);
                break;


            case 3:
                if (save_students(students, count) != 0) {
                    fprintf(stderr, "Error saving students.\n");

                    return EXIT_FAILURE;
                }

                printf("Data saved. Goodbye!\n");
                running = 0;
                break;

            default:
                printf("Invalid option. Try again.\n");
        }
    }

    return EXIT_SUCCESS;
}


int read_line(const char *prompt, char *buf, size_t size) {
    printf("%s", prompt);

    fflush(stdout);





    if (fgets(buf, (int)size, stdin) == NULL) {
        return -1;
    }

    size_t len = strcspn(buf, "\r\n");

    if (buf[len] == '\0' && len == size - 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }

    buf[len] = '\0';
    return 0;
}

int load_students(Student arr[], int max) {

    FILE *fp = fopen(DATA_FILE, "r");




    if (fp == NULL) {
        return 0;
    }

    char line[LINE_LEN];
    int count = 0;

    while (count < max && fgets(line, sizeof line, fp) != NULL) {
        if (strchr(line, '\n') == NULL &&
            strlen(line) == sizeof line - 1) {
            int ch;

            while ((ch = fgetc(fp)) != '\n' && ch != EOF) { }
            continue;
        }


        Student s = {0};

        char extra;

        if (sscanf(line, "%49[^,],%d,%f %c",
                   s.name, &s.id, &s.gpa, &extra) == 3 &&
            s.name[0] != '\0' &&
            strspn(s.name, " \t") != strlen(s.name) &&
            isfinite(s.gpa)) {
            arr[count++] = s;
        }
    }

    fclose(fp);
    return count;
}

int save_students(const Student arr[], int count) {
    if (count < 0 || count > MAX_STUDENTS ||
        (count > 0 && arr == NULL)) {
        return -1;
    }

    FILE *fp = fopen(DATA_FILE, "w");

    if (fp == NULL) {
        return -1;
    }

    int write_ok = 1;

    for (int i = 0; i < count; i++) {
        if (fprintf(fp, "%s,%d,%.2f\n",
                    arr[i].name, arr[i].id, arr[i].gpa) < 0) {
            write_ok = 0;
            break;
        }
    }

    int close_ok = fclose(fp) == 0;

    return (write_ok && close_ok) ? 0 : -1;
}

// Check that the student ID is a valid integer.
static int parse_id(const char *text, int *value) {
    char *end;
    errno = 0;

    long number = strtol(text, &end, 10);

    while (isspace((unsigned char)*end)) {
        end++;


    }

    if (end == text || *end != '\0' ||
        errno == ERANGE ||
        number < INT_MIN || number > INT_MAX) {
        return -1;
    }

    *value = (int)number;
    return 0;
}

static int parse_gpa(const char *text, float *value) {
    char *end;



    errno = 0;

    float number = strtof(text, &end);

    while (isspace((unsigned char)*end)) {
        end++;
    }

    if (end == text || *end != '\0' ||
        errno == ERANGE ||
        !isfinite(number) ||
        number < 0.0f || number > 4.0f) {
        return -1;
    }

    
    *value = number;
    return 0;
}

void add_student(Student arr[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Cannot add more students (limit reached).\n");
        return;
    }

    char name[LINE_LEN];
    char id_text[LINE_LEN];
    char gpa_text[LINE_LEN];

    if (read_line("Enter name: ", name, sizeof name) != 0 ||
        read_line("Enter ID: ", id_text, sizeof id_text) != 0 ||
        read_line("Enter GPA: ", gpa_text, sizeof gpa_text) != 0) {
        return;
    }

    int id;
    float gpa;

    if (name[0] == '\0' ||
        strlen(name) >= NAME_LEN ||
        strchr(name, ',') != NULL ||
        strspn(name, " \t") == strlen(name) ||
        parse_id(id_text, &id) != 0 ||
        parse_gpa(gpa_text, &gpa) != 0) {
        printf("Invalid input. Student not added.\n");
        return;
    }

    Student *s = &arr[*count];

    strcpy(s->name, name);
    s->id = id;
    s->gpa = gpa;

    (*count)++;

    printf("Student added successfully!\n");
}

void list_students(const Student arr[], int count) {
    if (count == 0) {
        printf("No students found.\n");
        return;
    }

    printf("%-5s %-20s %s\n", "ID", "Name", "GPA");

    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %.2f\n",
               arr[i].id, arr[i].name, arr[i].gpa);
    }
}
