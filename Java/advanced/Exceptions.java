/**
 * ADVANCED LEVEL - Lesson 4: Exception Handling
 * 
 * This lesson covers:
 * - Try-catch-finally blocks
 * - Multiple catch blocks
 * - Checked vs Unchecked exceptions
 * - Custom exceptions
 * - Try-with-resources
 * - Exception propagation
 * - Best practices
 */

import java.io.*;
import java.util.Scanner;

// ========== CUSTOM EXCEPTIONS ==========

class InsufficientFundsException extends Exception {
    private double amount;
    
    public InsufficientFundsException(double amount) {
        super("Insufficient funds. Required: " + amount);
        this.amount = amount;
    }
    
    public double getAmount() {
        return amount;
    }
}

class InvalidAgeException extends RuntimeException {  // Unchecked exception
    public InvalidAgeException(String message) {
        super(message);
    }
}

// ========== CLASS DEMONSTRATING EXCEPTION HANDLING ==========

class BankAccount {
    private double balance;
    
    public BankAccount(double initialBalance) {
        this.balance = initialBalance;
    }
    
    public void withdraw(double amount) throws InsufficientFundsException {
        if (amount > balance) {
            throw new InsufficientFundsException(amount);
        }
        balance -= amount;
        System.out.println("Withdrawn: " + amount + ", Remaining: " + balance);
    }
    
    public double getBalance() {
        return balance;
    }
}

class Person {
    private String name;
    private int age;
    
    public void setAge(int age) {
        if (age < 0 || age > 150) {
            throw new InvalidAgeException("Age must be between 0 and 150");
        }
        this.age = age;
    }
    
    public int getAge() {
        return age;
    }
}

// ========== MAIN CLASS ==========

public class Exceptions {
    public static void main(String[] args) {
        System.out.println("=== BASIC TRY-CATCH ===");
        
        try {
            int result = 10 / 0;  // ArithmeticException
        } catch (ArithmeticException e) {
            System.out.println("Caught exception: " + e.getMessage());
        }
        
        System.out.println("\n=== MULTIPLE CATCH BLOCKS ===");
        
        try {
            int[] arr = {1, 2, 3};
            System.out.println(arr[10]);  // ArrayIndexOutOfBoundsException
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Array index out of bounds: " + e.getMessage());
        } catch (Exception e) {
            System.out.println("General exception: " + e.getMessage());
        }
        
        System.out.println("\n=== FINALLY BLOCK ===");
        
        try {
            int x = 10 / 2;
            System.out.println("Result: " + x);
        } catch (ArithmeticException e) {
            System.out.println("Exception: " + e.getMessage());
        } finally {
            System.out.println("Finally block always executes");
        }
        
        System.out.println("\n=== CHECKED EXCEPTIONS ===");
        
        BankAccount account = new BankAccount(100.0);
        try {
            account.withdraw(50.0);
            account.withdraw(100.0);  // Will throw InsufficientFundsException
        } catch (InsufficientFundsException e) {
            System.out.println("Error: " + e.getMessage());
            System.out.println("Required amount: " + e.getAmount());
        }
        
        System.out.println("\n=== UNCHECKED EXCEPTIONS ===");
        
        Person person = new Person();
        try {
            person.setAge(25);
            System.out.println("Age set to: " + person.getAge());
            person.setAge(-5);  // Will throw InvalidAgeException
        } catch (InvalidAgeException e) {
            System.out.println("Error: " + e.getMessage());
        }
        
        System.out.println("\n=== TRY-WITH-RESOURCES ===");
        
        // Automatically closes resources
        try (FileWriter writer = new FileWriter("test.txt")) {
            writer.write("Hello, World!");
            System.out.println("File written successfully");
        } catch (IOException e) {
            System.out.println("IO Error: " + e.getMessage());
        }
        // File is automatically closed here
        
        // Multiple resources
        try (
            FileReader reader = new FileReader("test.txt");
            Scanner scanner = new Scanner(reader)
        ) {
            while (scanner.hasNextLine()) {
                System.out.println("Read: " + scanner.nextLine());
            }
        } catch (FileNotFoundException e) {
            System.out.println("File not found: " + e.getMessage());
        } catch (IOException e) {
            System.out.println("IO Error: " + e.getMessage());
        }
        
        System.out.println("\n=== EXCEPTION PROPAGATION ===");
        
        try {
            method1();
        } catch (Exception e) {
            System.out.println("Caught in main: " + e.getMessage());
            System.out.println("Stack trace:");
            e.printStackTrace();
        }
        
        System.out.println("\n=== NESTED TRY-CATCH ===");
        
        try {
            try {
                int[] arr = new int[5];
                arr[10] = 100;  // ArrayIndexOutOfBoundsException
            } catch (ArrayIndexOutOfBoundsException e) {
                System.out.println("Inner catch: " + e.getMessage());
                throw e;  // Re-throw
            }
        } catch (Exception e) {
            System.out.println("Outer catch: " + e.getMessage());
        }
        
        System.out.println("\n=== BEST PRACTICES ===");
        demonstrateBestPractices();
    }
    
    // Method that throws exception (propagation)
    public static void method1() throws Exception {
        method2();
    }
    
    public static void method2() throws Exception {
        method3();
    }
    
    public static void method3() throws Exception {
        throw new Exception("Exception from method3");
    }
    
    public static void demonstrateBestPractices() {
        System.out.println("\n--- Best Practices ---");
        System.out.println("1. Use specific exception types");
        System.out.println("2. Don't catch Exception unless necessary");
        System.out.println("3. Always close resources (use try-with-resources)");
        System.out.println("4. Don't swallow exceptions silently");
        System.out.println("5. Provide meaningful error messages");
        System.out.println("6. Use checked exceptions for recoverable conditions");
        System.out.println("7. Use unchecked exceptions for programming errors");
    }
}

