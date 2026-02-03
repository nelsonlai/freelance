/**
 * BEGINNER LEVEL - Lesson 3: Control Flow
 * 
 * This lesson covers:
 * - if, else if, else statements
 * - switch statements
 * - for loops
 * - while loops
 * - do-while loops
 * - break and continue statements
 * - Nested loops
 */

public class ControlFlow {
    public static void main(String[] args) {
        // ========== IF-ELSE STATEMENTS ==========
        
        System.out.println("=== If-Else Statements ===");
        
        int age = 20;
        
        if (age >= 18) {
            System.out.println("You are an adult");
        } else {
            System.out.println("You are a minor");
        }
        
        // Multiple conditions with else-if
        int score = 85;
        if (score >= 90) {
            System.out.println("Grade: A");
        } else if (score >= 80) {
            System.out.println("Grade: B");
        } else if (score >= 70) {
            System.out.println("Grade: C");
        } else if (score >= 60) {
            System.out.println("Grade: D");
        } else {
            System.out.println("Grade: F");
        }
        
        // ========== SWITCH STATEMENTS ==========
        
        System.out.println("\n=== Switch Statements ===");
        
        int day = 3;
        String dayName;
        
        switch (day) {
            case 1:
                dayName = "Monday";
                break;
            case 2:
                dayName = "Tuesday";
                break;
            case 3:
                dayName = "Wednesday";
                break;
            case 4:
                dayName = "Thursday";
                break;
            case 5:
                dayName = "Friday";
                break;
            case 6:
                dayName = "Saturday";
                break;
            case 7:
                dayName = "Sunday";
                break;
            default:
                dayName = "Invalid day";
        }
        System.out.println("Day " + day + " is " + dayName);
        
        // Switch with multiple cases (Java 14+ switch expressions)
        String season = switch (day) {
            case 12, 1, 2 -> "Winter";
            case 3, 4, 5 -> "Spring";
            case 6, 7, 8 -> "Summer";
            case 9, 10, 11 -> "Fall";
            default -> "Invalid month";
        };
        System.out.println("Season: " + season);
        
        // ========== FOR LOOPS ==========
        
        System.out.println("\n=== For Loops ===");
        
        // Basic for loop
        System.out.print("Counting 1 to 5: ");
        for (int i = 1; i <= 5; i++) {
            System.out.print(i + " ");
        }
        System.out.println();
        
        // For loop with step
        System.out.print("Even numbers 0 to 10: ");
        for (int i = 0; i <= 10; i += 2) {
            System.out.print(i + " ");
        }
        System.out.println();
        
        // Reverse loop
        System.out.print("Counting down 5 to 1: ");
        for (int i = 5; i >= 1; i--) {
            System.out.print(i + " ");
        }
        System.out.println();
        
        // Enhanced for loop (for-each) - works with arrays and collections
        int[] numbers = {10, 20, 30, 40, 50};
        System.out.print("Array elements: ");
        for (int num : numbers) {
            System.out.print(num + " ");
        }
        System.out.println();
        
        // ========== WHILE LOOPS ==========
        
        System.out.println("\n=== While Loops ===");
        
        int count = 1;
        System.out.print("While loop 1 to 5: ");
        while (count <= 5) {
            System.out.print(count + " ");
            count++;
        }
        System.out.println();
        
        // While loop with condition check
        int number = 10;
        System.out.print("Counting down from 10: ");
        while (number > 0) {
            System.out.print(number + " ");
            number -= 2;
        }
        System.out.println();
        
        // ========== DO-WHILE LOOPS ==========
        
        System.out.println("\n=== Do-While Loops ===");
        
        // Do-while executes at least once
        int value = 1;
        System.out.print("Do-while 1 to 3: ");
        do {
            System.out.print(value + " ");
            value++;
        } while (value <= 3);
        System.out.println();
        
        // Even if condition is false, executes once
        int x = 10;
        do {
            System.out.println("This executes once even though x > 10");
            x++;
        } while (x < 5);
        
        // ========== BREAK STATEMENT ==========
        
        System.out.println("\n=== Break Statement ===");
        System.out.print("Loop breaks at 5: ");
        for (int i = 1; i <= 10; i++) {
            if (i == 5) {
                break;  // Exit the loop immediately
            }
            System.out.print(i + " ");
        }
        System.out.println();
        
        // ========== CONTINUE STATEMENT ==========
        
        System.out.println("\n=== Continue Statement ===");
        System.out.print("Skip even numbers (print only odds): ");
        for (int i = 1; i <= 10; i++) {
            if (i % 2 == 0) {
                continue;  // Skip to next iteration
            }
            System.out.print(i + " ");
        }
        System.out.println();
        
        // ========== NESTED LOOPS ==========
        
        System.out.println("\n=== Nested Loops ===");
        System.out.println("Multiplication table (1-3):");
        for (int i = 1; i <= 3; i++) {
            for (int j = 1; j <= 3; j++) {
                System.out.print(i + "x" + j + "=" + (i * j) + "\t");
            }
            System.out.println();
        }
        
        // ========== LABELED BREAK AND CONTINUE ==========
        
        System.out.println("\n=== Labeled Break ===");
        outer: for (int i = 1; i <= 3; i++) {
            inner: for (int j = 1; j <= 3; j++) {
                if (i == 2 && j == 2) {
                    break outer;  // Breaks out of outer loop
                }
                System.out.print("(" + i + "," + j + ") ");
            }
        }
        System.out.println();
    }
}

