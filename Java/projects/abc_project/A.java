/**
 * A.java - Main class that uses classes from B.java and C.java
 * 
 * This demonstrates a simple multi-file Java project where:
 * - A.java is the main class that uses B and C
 * - B.java provides utility functions
 * - C.java provides data processing functions
 */

public class A {
    public static void main(String[] args) {
        System.out.println("=== Multi-File Java Project Demo ===\n");
        
        // Create instances of B and C classes
        B utility = new B();
        C processor = new C();
        
        // Use methods from B class
        System.out.println("--- Using B class methods ---");
        int sum = utility.add(10, 20);
        int product = utility.multiply(5, 6);
        System.out.println("Sum of 10 and 20: " + sum);
        System.out.println("Product of 5 and 6: " + product);
        System.out.println("Is 15 even? " + utility.isEven(15));
        System.out.println("Is 16 even? " + utility.isEven(16));
        
        // Use methods from C class
        System.out.println("\n--- Using C class methods ---");
        String greeting = processor.createGreeting("Alice");
        System.out.println(greeting);
        
        int[] numbers = {1, 2, 3, 4, 5};
        int max = processor.findMax(numbers);
        int min = processor.findMin(numbers);
        System.out.println("Array: [1, 2, 3, 4, 5]");
        System.out.println("Maximum value: " + max);
        System.out.println("Minimum value: " + min);
        
        String reversed = processor.reverseString("Hello World");
        System.out.println("Reversed 'Hello World': " + reversed);
        
        // Demonstrate interaction between B and C through A
        System.out.println("\n--- Combining B and C functionality ---");
        int[] testArray = {12, 45, 7, 23, 56};
        int maxValue = processor.findMax(testArray);
        boolean isMaxEven = utility.isEven(maxValue);
        System.out.println("Array: [12, 45, 7, 23, 56]");
        System.out.println("Maximum value: " + maxValue);
        System.out.println("Is maximum value even? " + isMaxEven);
        
        System.out.println("\n=== Project Structure ===");
        System.out.println("abc_project/");
        System.out.println("  ├── A.java  (Main class - uses B and C)");
        System.out.println("  ├── B.java  (Utility class)");
        System.out.println("  └── C.java  (Processor class)");
    }
}

