#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Demonstrates various control structures in C++
int main() {
    cout << "C++ Control Structures Demonstration" << endl;
    cout << "====================================" << endl;
    
    // 1. Selection statements (if, else if, else)
    cout << "\n1. SELECTION STATEMENTS:" << endl;
    
    int score = 85;
    cout << "Score: " << score << endl;
    
    /* > == < <= >= !=
    if (condition) {
        // code to execute if condition is true
    } else if (condition) {
        // code to execute if condition is true
    } else {
        // code to execute if condition is false
    }
    --------------------------------------------------
    if (condition) {
        // code to execute if condition is true
    }
    else {
        // code to execute if condition is false
    }
    */
    if (score >= 90) {
        cout << "Grade: A (Excellent!)" << endl;
    } else if (score >= 80) {
        cout << "Grade: B (Good!)" << endl;
    } else if (score >= 70) {
        cout << "Grade: C (Average)" << endl;
    } else if (score >= 60) {
        cout << "Grade: D (Below Average)" << endl;
    } else {
        cout << "Grade: F (Failed)" << endl;
    }
    
    // 2. Switch statement
    cout << "\n2. SWITCH STATEMENT:" << endl;
    
    char operation = '+';
    int a = 10, b = 5;
    
    cout << a << " " << operation << " " << b << " = ";
    
    switch (operation) {
        case '+':
            cout << (a + b) << endl;
            break;
        case '-':
            cout << (a - b) << endl;
            break;
        case '*':
            cout << (a * b) << endl;
            break;
        case '/':
            if (b != 0) {
                cout << (a / b) << endl;
            } else {
                cout << "Error: Division by zero!" << endl;
            }
            break;
        default:
            cout << "Unknown operation!" << endl;
            break;
    }
    
    // 3. For loop
    cout << "\n3. FOR LOOP:" << endl;
    
    cout << "Counting from 1 to 5:" << endl;
    for (int i = 1; i <= 5; ++i) { // initialization, condition, increment
        cout << "  " << i << endl;
        // ++i;
    }
    
    int x = 10;
    int y = 3;
    int z;

    z = y * ++x;    // z = 3 * 11 = 33, x = 11  (pre-increment)

    int x = 10;
    int y = 3;
    z = y * x++;    // z = 3 * 10 = 30, x = 11  (post-increment)

    // Range-based for loop (C++11)
    cout << "\nRange-based for loop:" << endl;
    vector<int> numbers = {10, 20, 30, 40, 50};
    for (int num : numbers) {
        cout << "  " << num << endl;
    }
    
    // 4. While loop
    cout << "\n4. WHILE LOOP:" << endl;
    
    int count = 0;
    cout << "Countdown from 3:" << endl;
    while (count < 3) {
        cout << "  " << (3 - count) << endl;
        ++count;    // count ++;
    }
    cout << "  Blast off!" << endl;
    
    // 5. Do-while loop
    cout << "\n5. DO-WHILE LOOP:" << endl;
    
    int user_input;
    do {
        cout << "Enter a positive number (0 to quit): ";
        cin >> user_input;
        
        if (user_input > 0) {
            cout << "You entered: " << user_input << endl;
        }
    } while (user_input != 0);
    
    // 6. Nested loops
    cout << "\n6. NESTED LOOPS (Multiplication Table):" << endl;
    
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            cout << i << " x " << j << " = " << (i * j) << "  ";
            // ++j
        }
        cout << endl;
        // ++i;
    }
    
    // 7. Break and continue
    cout << "\n7. BREAK AND CONTINUE:" << endl;
    
    cout << "Numbers 1-10, skipping 5, stopping at 8:" << endl;
    for (int i = 1; i <= 10; ++i) {
        if (i == 5) {
            continue;  // Skip 5
        }
        if (i == 8) {
            break;     // Break out of the loop at 8
        }
        cout << "  " << i << endl;
    }
    
    // 8. Conditional operator (ternary operator)
    cout << "\n8. CONDITIONAL OPERATOR:" << endl;
    
    int x = 15, y = 10;
    string result = (x > y) ? "x is greater" : "y is greater or equal";
    
    if (x > y) {
        result = "x is greater";
    } else {
        result = "y is greater or equal";
    }

    cout << "x = " << x << ", y = " << y << " -> " << result << endl;
    
    return 0;
}
