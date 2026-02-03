/*
Declare a structure named 'Student' with the following members:
- 'name': a string to hold the student's name
- 'age': an integer to hold the student's age
- 'grade': a character to hold the student's grade
- 'is_enrolled': a boolean to indicate if the student is currently enrolled
- 'gpa': a float to hold the student's GPA
*/
#include <stdio.h>
#include <stdbool.h>

struct Student {
    char name[30];
    int age;
    char grade;
    bool is_enrolled;
    float gpa;
};

int main() {
    struct Student student1;

    // Assign values to the members of student1
    snprintf(student1.name, sizeof(student1.name), "Louis");
    student1.age = 20;
    student1.grade = 'A';
    student1.is_enrolled = true;
    student1.gpa = 3.8f;

    // Print the details of student1
    printf("Name: %s\n", student1.name);
    printf("Age: %d\n", student1.age);
    printf("Grade: %c\n", student1.grade);
    printf("Enrolled: %s\n", student1.is_enrolled ? "Yes" : "No");
    printf("GPA: %.2f\n", student1.gpa);

    return 0;
}