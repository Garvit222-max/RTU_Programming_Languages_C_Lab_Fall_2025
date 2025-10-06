/*
 * week4_3_struct_database.c
 * Author: Garvit
 * Student ID: 241ADB140
 * Description:
 *   Simple in-memory "database" using an array of structs.
 *   Uses malloc to allocate space for multiple Student records,
 *   then inputs and displays the data.
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
    int n;
    struct Student *students = NULL;
    printf("Enter number of students: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number.\n");
        return 1;
    }
    students = (struct Student *)malloc(n * sizeof(struct Student));
    if (students == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        printf("Enter name, ID, and grade for student %d: ", i + 1);
        scanf("%s %d %f", students[i].name, &students[i].id, &students[i].grade);
    }
    printf("\nID\tName\t\tGrade\n");
    printf("-----------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%-10s\t%.2f\n", students[i].id, students[i].name, students[i].grade);
    }
    free(students);
    return 0;
}
