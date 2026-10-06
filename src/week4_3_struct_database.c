/*
 * week4_3_struct_database.c
 * Author: [Mihails Semjonovs]
 * Student ID: [251ADB194]
 * Description:
 *   Simple in-memory "database" using an array of structs.
 *   Use malloc to allocate space for n Student records,
 *   read each record from the user, print them as a table,
 *   and then free the memory.
 *
 *   Output must match the format in the Week 4 instructions exactly
 *   (it is checked by the autograder).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char name[50];
    int id;
    float grade;
};

int main(void) {
    int student_count;
    struct Student *student_records = NULL;

    printf("Enter number of students: ");

    if (scanf("%d", &student_count) != 1 || student_count <= 0) {
        printf("Invalid number.\n");
        return 1;
    }

    // Reserve memory for all student records
    student_records = malloc(student_count * sizeof(struct Student));

    if (student_records == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Read information for every student
    for (int index = 0; index < student_count; index++) {
        printf("Enter data for student %d: ", index + 1);

        if (scanf("%49s %d %f",
                  student_records[index].name,
                  &student_records[index].id,
                  &student_records[index].grade) != 3) {
            printf("Invalid input.\n");
            free(student_records);
            return 1;
        }
    }

    printf("\n");
    printf("%-6s %-11s %s\n", "ID", "Name", "Grade");

    // Print all records in the same order as they were entered
    for (int index = 0; index < student_count; index++) {
        printf("%-6d %-11s %.1f\n",
               student_records[index].id,
               student_records[index].name,
               student_records[index].grade);
    }

    free(student_records);

    return 0;
}