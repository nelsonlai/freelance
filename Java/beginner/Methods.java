/**
 * BEGINNER LEVEL - Lesson 4: Methods
 * 
 * This lesson covers:
 * - Method declaration and definition
 * - Method parameters and arguments
 * - Return types and return statements
 * - Method overloading
 * - Static vs instance methods
 * - Pass by value vs pass by reference
 */

public class Methods {
    
    // ========== BASIC METHOD ==========
    
    // Method with no parameters and no return value
    public static void greet() {
        System.out.println("Hello, World!");
        // No data returned
    }
    
    // Method with parameters and no return value
    public static void greetPerson(String name) {
        System.out.println("Hello, " + name + "!");
        // No data returned
    }
    
    // Method with parameters and return value
    public static int add(int a, int b) {
        return a + b;
    }
    
    // Method with multiple parameters
    public static double calculateAverage(double num1, double num2, double num3) {
        return (num1 + num2 + num3) / 3.0;
    }
    
    // ========== METHOD OVERLOADING ==========
    
    // Same method name, different parameters
    public static int multiply(int a, int b) {
        return a * b;
    }
    
    public static double multiply(double a, double b) {
        return a * b;
    }
    
    public static int multiply(int a, int b, int c) {
        return a * b * c;
    }
    
    // ========== METHODS WITH DIFFERENT RETURN TYPES ==========
    
    public static boolean isEven(int number) {
        return number % 2 == 0;
    }
    
    public static String getGrade(int score) {
        if (score >= 90) return "A";
        if (score >= 80) return "B";
        if (score >= 70) return "C";
        if (score >= 60) return "D";
        return "F";
    }
    
    public static int[] getFirstAndLast(int[] array) {
        if (array.length == 0) {
            return new int[0];
        }
        return new int[]{array[0], array[array.length - 1]};
    }
    
    // ========== RECURSIVE METHOD ==========
    
    public static int factorial(int n) { // n! = n * (n-1) * (n-2) * ... * 1
        if (n <= 1) {
            return 1;  // Base case
        }
        return n * factorial(n - 1);
        // Recursive case 
        // 5! = 5 * 4!
        // 4! = 4 * 3!
        // 3! = 3 * 2!
        // 2! = 2 * 1!
        // 1! = 1
    }
    
    // ========== METHOD WITH VARARGS (Variable Arguments) ==========
    
    public static int sum(int... numbers) {
        int total = 0;
        for (int num : numbers) {
            total += num;
        }
        return total;
    }
    
    // ========== MAIN METHOD ==========
    
    public static void main(String[] args) {
        System.out.println("=== Basic Methods ===");
        
        // Calling methods
        greet();
        greetPerson("Alice");
        greetPerson("Bob");
        
        int result = add(5, 3);
        System.out.println("5 + 3 = " + result);
        
        double avg = calculateAverage(10, 20, 30);
        System.out.println("Average of 10, 20, 30: " + avg);
        
        System.out.println("\n=== Method Overloading ===");
        System.out.println("multiply(5, 3) = " + multiply(5, 3));
        System.out.println("multiply(5.5, 3.2) = " + multiply(5.5, 3.2));
        System.out.println("multiply(2, 3, 4) = " + multiply(2, 3, 4));
        
        System.out.println("\n=== Methods with Different Return Types ===");
        System.out.println("Is 8 even? " + isEven(8));
        System.out.println("Is 7 even? " + isEven(7));
        System.out.println("Score 85 gets grade: " + getGrade(85));
        
        int[] numbers = {10, 20, 30, 40, 50};
        int[] firstLast = getFirstAndLast(numbers);
        System.out.println("First: " + firstLast[0] + ", Last: " + firstLast[1]);
        
        System.out.println("\n=== Recursive Method ===");
        System.out.println("Factorial of 5: " + factorial(5));
        System.out.println("Factorial of 0: " + factorial(0));
        
        System.out.println("\n=== Varargs Method ===");
        System.out.println("sum(1, 2, 3) = " + sum(1, 2, 3));
        System.out.println("sum(10, 20, 30, 40, 50) = " + sum(10, 20, 30, 40, 50));
        System.out.println("sum() = " + sum(10, 7));  // Can call with no arguments
    }
}

