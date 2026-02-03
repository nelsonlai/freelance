#include <iostream>
using namespace std;

// Function to calculate the square of a number
int square(int num) {
    return num * num;
}

// Function to check if a number is even
bool isEven(int num) {
    return num % 2 == 0;
}

// Function with default parameter
void greet(string name = "Guest") {
    cout << "Hello, " << name << "!" << endl;
}

int main() {
    int number = 7;

    cout << "Square of " << number << " is: " << square(number) << endl;

    if (isEven(number)) {
        cout << number << " is even." << endl;
    } else {
        cout << number << " is odd." << endl;
    }

    greet();  // Uses default parameter
    greet("Alice");  // Provides a name

    return 0;
}