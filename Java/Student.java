/* Homework 1: Class & Object Basics
Task:
Create a Student class with:

Fields: name, age, grade

A constructor to initialize all fields

A method printInfo() to display student information

In main:

Create 2 Student objects

Call printInfo() for each */

class Student {
    private String name;
    private int age;
    private char grade;

    Student(String name, int age, char grade) {
        this.name = name;
        this.age = age;
        this.grade = grade;
    }

    void printInfo() {
        System.out.println("Name: " + name);
        System.out.println("Age: " + age);
        System.out.println("Grade: " + grade);
    }

    public static void main(String[] args) {
        Student student1 = new Student("Alice", 20, 'A');
        Student student2 = new Student("Bob", 22, 'B');

        student1.printInfo();
        System.out.println();
        student2.printInfo();
    }
}