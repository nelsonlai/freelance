/**
 * BEGINNER LEVEL - Lesson 2: Operators
 * 
 * This lesson covers:
 * - Arithmetic operators (+, -, *, /, %)
 * - Comparison operators (==, !=, <, >, <=, >=)
 * - Logical operators (&&, ||, !)
 * - Assignment operators (=, +=, -=, *=, /=, %=)
 * - Increment/Decrement operators (++, --)
 * - Ternary operator (? :)
 * - Operator precedence
 */

public class Operators {
    public static void main(String[] args) {
        // ========== ARITHMETIC OPERATORS ==========
        
        int a = 10, b = 3;
        
        System.out.println("=== Arithmetic Operators ===");
        System.out.println("a + b = " + (a + b));  // Addition: 13
        System.out.println("a - b = " + (a - b));  // Subtraction: 7
        System.out.println("a * b = " + (a * b));  // Multiplication: 30
        System.out.println("a / b = " + (a / b));  // Division: 3 (integer division)
        System.out.println("a % b = " + (a % b));  // Modulus (remainder): 1
        
        double x = 10.0, y = 3.0;
        System.out.println("x / y = " + (x / y));  // Floating point division: 3.333...
        
        // ========== COMPARISON OPERATORS ==========
        
        System.out.println("\n=== Comparison Operators ===");
        System.out.println("a == b: " + (a == b));  // Equal to: false
        System.out.println("a != b: " + (a != b));  // Not equal to: true
        System.out.println("a < b: " + (a < b));    // Less than: false
        System.out.println("a > b: " + (a > b));    // Greater than: true
        System.out.println("a <= b: " + (a <= b));  // Less than or equal: false
        System.out.println("a >= b: " + (a >= b));  // Greater than or equal: true
        
        // ========== LOGICAL OPERATORS ==========
        
        boolean p = true, q = false;
        
        System.out.println("\n=== Logical Operators ===");
        System.out.println("p && q: " + (p && q));  // AND: false
        System.out.println("p || q: " + (p || q));  // OR: true
        System.out.println("!p: " + (!p));          // NOT: false
        
        // Short-circuit evaluation
        int num = 5;
        if (num > 0 && num < 10) {  // Both conditions checked
            System.out.println("Number is between 0 and 10");
        }
        
        // ========== ASSIGNMENT OPERATORS ==========
        
        System.out.println("\n=== Assignment Operators ===");
        int value = 10;
        System.out.println("Initial value: " + value);
        
        value += 5;  // Same as: value = value + 5
        System.out.println("After += 5: " + value);  // 15
        
        value -= 3;  // Same as: value = value - 3
        System.out.println("After -= 3: " + value);  // 12
        
        value *= 2;  // Same as: value = value * 2
        System.out.println("After *= 2: " + value);  // 24
        
        value /= 4;  // Same as: value = value / 4
        System.out.println("After /= 4: " + value);  // 6
        
        value %= 4;  // Same as: value = value % 4
        System.out.println("After %= 4: " + value);  // 2
        
        // ========== INCREMENT/DECREMENT OPERATORS ==========
        
        System.out.println("\n=== Increment/Decrement Operators ===");
        int count = 5;
        
        System.out.println("Initial count: " + count);
        System.out.println("count++: " + count++);  // Post-increment: prints 5, then becomes 6
        System.out.println("After post-increment: " + count);  // 6
        
        System.out.println("++count: " + ++count);  // Pre-increment: becomes 7, then prints 7
        System.out.println("After pre-increment: " + count);  // 7
        
        System.out.println("count--: " + count--);  // Post-decrement: prints 7, then becomes 6
        System.out.println("--count: " + --count);  // Pre-decrement: becomes 5, then prints 5
        
        // ========== TERNARY OPERATOR ==========
        
        System.out.println("\n=== Ternary Operator ===");
        int score = 85;
        String result = (score >= 60) ? "Pass" : "Fail";
        System.out.println("Score: " + score + ", Result: " + result);
        
        // Nested ternary
        String grade = (score >= 90) ? "A" : (score >= 80) ? "B" : (score >= 70) ? "C" : "D";
        System.out.println("Grade: " + grade);
        
        // ========== OPERATOR PRECEDENCE ==========
        
        System.out.println("\n=== Operator Precedence ===");
        int result1 = 2 + 3 * 4;        // Multiplication first: 2 + 12 = 14
        int result2 = (2 + 3) * 4;      // Parentheses first: 5 * 4 = 20
        
        System.out.println("2 + 3 * 4 = " + result1);
        System.out.println("(2 + 3) * 4 = " + result2);
        
        // Precedence order (highest to lowest):
        // 1. Parentheses: ()
        // 2. Unary: ++, --, !, +, -
        // 3. Multiplicative: *, /, %
        // 4. Additive: +, -
        // 5. Relational: <, >, <=, >=
        // 6. Equality: ==, !=
        // 7. Logical AND: &&
        // 8. Logical OR: ||
        // 9. Ternary: ? :
        // 10. Assignment: =, +=, -=, etc.
    }
}

