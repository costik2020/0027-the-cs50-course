/**
 * structs-1.c
 *
 * David J. Malan
 * malan@harvard.edu
 *
 * Demonstrates use of file I/O.
 */
#include"myLibrary.h"       

#include "structs.h"

// number of students
#define STUDENTS 3

int main(void)
{
    // declare students
    student students[STUDENTS];

    // populate students with user's input
    for (int i = 0; i < STUDENTS; i++)
    {
        printf("Student's name: ");
        students[i].name = GetString();

        printf("Student's dorm: ");
        students[i].dorm = GetString();
    }

    // save students to disk
    FILE* file = fopen("students.csv", "w");
    if (file != NULL)
    {
        for (int i = 0; i < STUDENTS; i++)
        {
            fprintf(file, "%s,%s\n", students[i].name, students[i].dorm);
        }
        fclose(file);
    }

    // free memory
    for (int i = 0; i < STUDENTS; i++)
    {
        free(students[i].name);
        free(students[i].dorm);
    }
}
