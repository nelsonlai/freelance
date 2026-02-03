#include <iostream>
#include <vector>
#include <string>
#include <map>

// Demonstrates all C++ statement types and control flow
int main() {
    std::cout << "C++ Statements Demonstration" << std::endl;
    std::cout << "============================" << std::endl;
    
    // 1. Expression statements
    std::cout << "\n1. EXPRESSION STATEMENTS:" << std::endl;
    
    int x = 42;                    // Declaration statement
    x++;                          // Expression statement
    std::cout << "x = " << x << std::endl;  // Expression statement
    
    // Null statement
    ;  // Null statement (empty)
    
    // 2. Compound statements (blocks)
    std::cout << "\n2. COMPOUND STATEMENTS:" << std::endl;
    
    {
        int local_var = 100;  // Local to this block
        std::cout << "Local variable: " << local_var << std::endl;
    }  // local_var goes out of scope here
    
    // std::cout << local_var << std::endl;  // Error: local_var not in scope
    
    // 3. Selection statements - if
    std::cout << "\n3. SELECTION STATEMENTS - IF:" << std::endl;
    
    int score = 85;
    
    if (score >= 90) {
        std::cout << "Grade: A (Excellent!)" << std::endl;
    } else if (score >= 80) {
        std::cout << "Grade: B (Good!)" << std::endl;
    } else if (score >= 70) {
        std::cout << "Grade: C (Average)" << std::endl;
    } else if (score >= 60) {
        std::cout << "Grade: D (Below Average)" << std::endl;
    } else {
        std::cout << "Grade: F (Failed)" << std::endl;
    }
    
    // 4. Selection statements - switch
    std::cout << "\n4. SELECTION STATEMENTS - SWITCH:" << std::endl;
    
    char operation = '+';
    int a = 10, b = 5;
    
    std::cout << a << " " << operation << " " << b << " = ";
    
    switch (operation) {
        case '+':
            std::cout << (a + b) << std::endl;
            break;
        case '-':
            std::cout << (a - b) << std::endl;
            break;
        case '*':
            std::cout << (a * b) << std::endl;
            break;
        case '/':
            if (b != 0) {
                std::cout << (a / b) << std::endl;
            } else {
                std::cout << "Error: Division by zero!" << std::endl;
            }
            break;
        case '%':
            if (b != 0) {
                std::cout << (a % b) << std::endl;
            } else {
                std::cout << "Error: Modulo by zero!" << std::endl;
            }
            break;
        default:
            std::cout << "Unknown operation!" << std::endl;
            break;
    }
    
    // 5. Iteration statements - for loop
    std::cout << "\n5. ITERATION STATEMENTS - FOR LOOP:" << std::endl;
    
    std::cout << "Counting from 1 to 5: ";
    for (int i = 1; i <= 5; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Counting backwards: ";
    for (int i = 5; i >= 1; --i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Counting by 2s: ";
    for (int i = 0; i <= 10; i += 2) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    // 6. Iteration statements - while loop
    std::cout << "\n6. ITERATION STATEMENTS - WHILE LOOP:" << std::endl;
    
    std::cout << "Countdown: ";
    int count = 5;
    while (count > 0) {
        std::cout << count << " ";
        count--;
    }
    std::cout << "Blast off!" << std::endl;
    
    // 7. Iteration statements - do-while loop
    std::cout << "\n7. ITERATION STATEMENTS - DO-WHILE LOOP:" << std::endl;
    
    std::cout << "Do-while countdown: ";
    int do_count = 3;
    do {
        std::cout << do_count << " ";
        do_count--;
    } while (do_count > 0);
    std::cout << std::endl;
    
    // 8. Range-based for loop
    std::cout << "\n8. RANGE-BASED FOR LOOP:" << std::endl;
    
    std::vector<int> numbers = {10, 20, 30, 40, 50};
    std::cout << "Vector elements: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    std::string text = "Hello";
    std::cout << "String characters: ";
    for (char c : text) {
        std::cout << c << " ";
    }
    std::cout << std::endl;
    
    // 9. Jump statements - break and continue
    std::cout << "\n9. JUMP STATEMENTS - BREAK AND CONTINUE:" << std::endl;
    
    std::cout << "Numbers 1-10, skipping 5, stopping at 8: ";
    for (int i = 1; i <= 10; ++i) {
        if (i == 5) {
            continue;  // Skip 5
        }
        if (i == 8) {
            break;     // Stop at 8
        }
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    // 10. Nested statements
    std::cout << "\n10. NESTED STATEMENTS:" << std::endl;
    
    std::cout << "Nested loops - multiplication table:" << std::endl;
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            std::cout << i << " x " << j << " = " << (i * j) << "  ";
        }
        std::cout << std::endl;
    }
    
    // 11. Complex nested control flow
    std::cout << "\n11. COMPLEX NESTED CONTROL FLOW:" << std::endl;
    
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    std::cout << "Even numbers greater than 3: ";
    for (int num : data) {
        if (num > 3) {
            if (num % 2 == 0) {
                std::cout << num << " ";
            }
        }
    }
    std::cout << std::endl;
    
    // 12. Switch with fall-through
    std::cout << "\n12. SWITCH WITH FALL-THROUGH:" << std::endl;
    
    int day = 3;
    std::cout << "Day " << day << " is ";
    
    switch (day) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            std::cout << "a weekday";
            break;
        case 6:
        case 7:
            std::cout << "a weekend";
            break;
        default:
            std::cout << "invalid";
            break;
    }
    std::cout << std::endl;
    
    // 13. Statement scope and lifetime
    std::cout << "\n13. STATEMENT SCOPE AND LIFETIME:" << std::endl;
    
    {
        int outer_var = 100;
        std::cout << "Outer variable: " << outer_var << std::endl;
        
        {
            int inner_var = 200;
            std::cout << "Inner variable: " << inner_var << std::endl;
            std::cout << "Outer variable from inner scope: " << outer_var << std::endl;
        }  // inner_var goes out of scope
        
        // std::cout << inner_var << std::endl;  // Error: inner_var not in scope
        std::cout << "Outer variable still accessible: " << outer_var << std::endl;
    }  // outer_var goes out of scope
    
    // 14. Loop with multiple variables
    std::cout << "\n14. LOOP WITH MULTIPLE VARIABLES:" << std::endl;
    
    std::cout << "Multiple variables in for loop: ";
    for (int i = 0, j = 10; i < 5; ++i, --j) {
        std::cout << "(" << i << "," << j << ") ";
    }
    std::cout << std::endl;
    
    // 15. Conditional operator (ternary)
    std::cout << "\n15. CONDITIONAL OPERATOR:" << std::endl;
    
    int a_val = 15, b_val = 10;
    std::string result = (a_val > b_val) ? "a is greater" : "b is greater or equal";
    std::cout << "a = " << a_val << ", b = " << b_val << " -> " << result << std::endl;
    
    // 16. Switch with enum
    std::cout << "\n16. SWITCH WITH ENUM:" << std::endl;
    
    enum class Color { RED, GREEN, BLUE };
    Color color = Color::GREEN;
    
    std::cout << "Color is ";
    switch (color) {
        case Color::RED:
            std::cout << "red";
            break;
        case Color::GREEN:
            std::cout << "green";
            break;
        case Color::BLUE:
            std::cout << "blue";
            break;
    }
    std::cout << std::endl;
    
    // 17. Infinite loop with break
    std::cout << "\n17. INFINITE LOOP WITH BREAK:" << std::endl;
    
    std::cout << "Counting until we find 7: ";
    int counter = 1;
    while (true) {
        std::cout << counter << " ";
        if (counter == 7) {
            break;
        }
        counter++;
    }
    std::cout << "Found it!" << std::endl;
    
    // 18. Loop with continue and multiple conditions
    std::cout << "\n18. LOOP WITH CONTINUE AND MULTIPLE CONDITIONS:" << std::endl;
    
    std::cout << "Numbers 1-20, skipping multiples of 3 and 5: ";
    for (int i = 1; i <= 20; ++i) {
        if (i % 3 == 0 || i % 5 == 0) {
            continue;
        }
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    // 19. Nested switch statements
    std::cout << "\n19. NESTED SWITCH STATEMENTS:" << std::endl;
    
    int category = 1;
    int subcategory = 2;
    
    std::cout << "Category " << category << ", Subcategory " << subcategory << ": ";
    switch (category) {
        case 1:
            switch (subcategory) {
                case 1:
                    std::cout << "Category 1, Subcategory 1";
                    break;
                case 2:
                    std::cout << "Category 1, Subcategory 2";
                    break;
                default:
                    std::cout << "Category 1, Unknown subcategory";
                    break;
            }
            break;
        case 2:
            std::cout << "Category 2";
            break;
        default:
            std::cout << "Unknown category";
            break;
    }
    std::cout << std::endl;
    
    // 20. Statement with side effects
    std::cout << "\n20. STATEMENTS WITH SIDE EFFECTS:" << std::endl;
    
    int side_effect_var = 5;
    std::cout << "Original value: " << side_effect_var << std::endl;
    
    // Side effect in condition
    if (++side_effect_var > 5) {
        std::cout << "After increment: " << side_effect_var << std::endl;
    }
    
    // Side effect in loop
    std::cout << "Side effects in loop: ";
    while (side_effect_var > 0) {
        std::cout << side_effect_var-- << " ";
    }
    std::cout << std::endl;
    
    std::cout << "\nStatements demonstration completed!" << std::endl;
    return 0;
}
