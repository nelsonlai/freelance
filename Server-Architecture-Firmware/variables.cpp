#include <iostream>
#include <string>
using namespace std;

int main() {
    // Integer variable
    int age = 25;

    // Floating-point variable
    float height = 1.75;

    // Character variable
    char grade = 'A';

    // Boolean variable
    bool isStudent = true;

    // String variable (C++ string class)
    string name = "Alice";

    cout << "Name: " << name << endl;
    cout << "Age: " << age << " years" << endl;
    cout << "Height: " << height << " meters" << endl;
    cout << "Grade: " << grade << endl;
    cout << "Is a student: " << (isStudent ? "Yes" : "No") << endl;

    return 0;
}