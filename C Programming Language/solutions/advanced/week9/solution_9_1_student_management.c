/**
 * Solution 9.1: Student Management System
 * Week 9 - Structures and User-Defined Types
 * 
 * Description: Student management system using structures
 */

#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

struct Student {
    int id;
    char name[50];
    int age;
    float gpa;
};

struct Student students[MAX_STUDENTS];
int studentCount = 0;

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Cannot add more students. Database full!\n");
        return;
    }
    
    struct Student *s = &students[studentCount];
    
    printf("Enter student ID: ");
    scanf("%d", &s->id);
    
    printf("Enter student name: ");
    scanf("%s", s->name);
    
    printf("Enter student age: ");
    scanf("%d", &s->age);
    
    printf("Enter student GPA: ");
    scanf("%f", &s->gpa);
    
    studentCount++;
    printf("Student added successfully!\n");
}

void displayStudents() {
    if (studentCount == 0) {
        printf("No students in database.\n");
        return;
    }
    
    printf("\n--- Student Database ---\n");
    printf("ID\tName\t\tAge\tGPA\n");
    printf("--------------------------------\n");
    
    for (int i = 0; i < studentCount; i++) {
        printf("%d\t%-15s\t%d\t%.2f\n", 
               students[i].id, students[i].name, 
               students[i].age, students[i].gpa);
    }
}

void searchStudent() {
    int id;
    printf("Enter student ID to search: ");
    scanf("%d", &id);
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("Student found:\n");
            printf("ID: %d\n", students[i].id);
            printf("Name: %s\n", students[i].name);
            printf("Age: %d\n", students[i].age);
            printf("GPA: %.2f\n", students[i].gpa);
            return;
        }
    }
    
    printf("Student with ID %d not found.\n", id);
}

int main() {
    int choice;
    
    while (1) {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}
