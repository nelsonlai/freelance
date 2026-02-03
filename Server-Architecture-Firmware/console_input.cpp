#include <iostream>
#include <iomanip>  // For setprecision
#include <string>   // For string operations
using namespace std;

int main() {
    string name;
    int age;
    double height;

    // Input operations
    cout << "Enter your name: ";
    getline(cin, name);  // Reads a full line, including spaces

    cout << "Enter your age: ";
    cin >> age;

    cout << "Enter your height in meters: ";
    cin >> height;

    // Output operations
    cout << "\n--- Your Information ---\n";
    cout << "Name: " << name << endl;
    cout << "Age: " << age << " years" << endl;

    // Setting precision for floating-point output
    cout << fixed << setprecision(2);
    cout << "Height: " << height << " meters" << endl;

    // Using width and fill for formatted output
    cout << "\nFormatted Age Display:\n";
    cout << setw(10) << setfill('.') << left << "Age" << setw(5) << right << age << endl;

    return 0;
}