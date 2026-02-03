/**
 * BEGINNER LEVEL - Lesson 1: Variables and Data Types
 * 
 * This lesson covers:
 * - Primitive data types (int, double, boolean, char, etc.)
 * - Variable declaration and initialization
 * - Type conversion (casting)
 * - Constants (final keyword)
 */

public class VariablesAndDataTypes {
    public static void main(String[] args) {
        // ========== PRIMITIVE DATA TYPES ==========
        
        // Integer types
        byte byteValue = 127;           // 8-bit: -128 to 127
        short shortValue = 32767;       // 16-bit: -32,768 to 32,767
        int intValue = 2147483647;      // 32-bit: -2^31 to 2^31-1
        long longValue = 9223372036854775807L; // 64-bit: -2^63 to 2^63-1 (note the 'L')
        
        // Floating point types
        float floatValue = 3.14f;       // 32-bit (note the 'f')
        double doubleValue = 3.141592653589793; // 64-bit (default for decimals)
        
        // Character type
        char charValue = 'A';           // 16-bit Unicode character
        char unicodeChar = '\u0041';    // Unicode representation
        
        // Boolean type
        boolean boolValue = true;       // true or false only
        
        // ========== VARIABLE DECLARATION ==========
        
        // Declaration and initialization in one line
        int age = 25;
        
        // Declaration first, initialization later
        int count;
        count = 10;
        
        // Multiple variables of same type
        int x = 1, y = 2, z = 3;
        
        // ========== TYPE CONVERSION (CASTING) ==========
        
        // Implicit conversion (widening - automatic)
        int smallInt = 100;
        long largeLong = smallInt;      // int to long (automatic)
        double largeDouble = smallInt;  // int to double (automatic)
        
        // Explicit conversion (narrowing - requires casting)
        double pi = 3.14159;
        int intPi = (int) pi;           // double to int (loses decimal part)
        System.out.println("pi as int: " + intPi); // Output: 3
        
        // ========== CONSTANTS (final keyword) ==========
        
        final int MAX_SIZE = 100;       // Constant - cannot be changed
        final double PI = 3.14159;
        // MAX_SIZE = 200;              // This would cause a compile error
        
        // ========== STRING (Reference Type) ==========
        
        String name = "Java Learner";
        String greeting = "Hello, " + name; // String concatenation
        
        // ========== OUTPUT EXAMPLES ==========
        
        System.out.println("=== Variables and Data Types ===");
        System.out.println("Integer: " + intValue);
        System.out.println("Double: " + doubleValue);
        System.out.println("Character: " + charValue);
        System.out.println("Boolean: " + boolValue);
        System.out.println("String: " + greeting);
        System.out.println("Constant PI: " + PI);
    }
}

