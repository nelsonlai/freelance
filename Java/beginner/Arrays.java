/**
 * BEGINNER LEVEL - Lesson 5: Arrays
 * 
 * This lesson covers:
 * - Array declaration and initialization
 * - Accessing array elements
 * - Array length
 * - Multi-dimensional arrays
 * - Array manipulation
 * - Common array operations
 */

public class Arrays {
    public static void main(String[] args) {
        // ========== ARRAY DECLARATION AND INITIALIZATION ==========
        
        System.out.println("=== Array Declaration ===");
        
        // Method 1: Declare and initialize separately
        int[] numbers1;
        numbers1 = new int[5];  // Array of 5 integers (default value: 0)
        
        // Method 2: Declare and initialize in one line
        int[] numbers2 = new int[5];
        numbers2[0] = 10;
        numbers2[1] = 20;
        numbers2[2] = 30;
        numbers2[3] = 40;
        numbers2[4] = 50;
        numbers2[5] = 15; // Out of bounds access example, raises ArrayIndexOutOfBoundsException
        
        // Method 3: Initialize with values
        int[] numbers3 = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
        
        // Method 4: Initialize with values (alternative syntax)
        int[] numbers4 = new int[]{1, 2, 3, 4, 5};
        
        // ========== ACCESSING ARRAY ELEMENTS ==========
        
        System.out.println("\n=== Accessing Array Elements ===");
        
        int[] arr = {10, 20, 30, 40, 50};
        
        // Access by index (0-based)
        System.out.println("First element: " + arr[0]);   // 10
        System.out.println("Second element: " + arr[1]);  // 20
        System.out.println("Last element: " + arr[4]);    // 50
        
        // Modify array elements
        arr[0] = 100;
        System.out.println("After modification, first element: " + arr[0]);
        
        // ========== ARRAY LENGTH ==========
        
        System.out.println("\n=== Array Length ===");
        System.out.println("Array length: " + arr.length);
        
        // Access last element using length
        System.out.println("Last element: " + arr[arr.length - 1]);
        
        // ========== ITERATING THROUGH ARRAYS ==========
        
        System.out.println("\n=== Iterating Through Arrays ===");
        
        // Using for loop with index
        System.out.print("Using for loop: ");
        for (int i = 0; i < arr.length; i++) {  // initial value; condition; increment
            System.out.print(arr[i] + " ");
        }
        System.out.println();
        
        // Using enhanced for loop (for-each)
        System.out.print("Using for-each: ");
        for (int num : arr) {   // {10, 20, 30, 40, 50} // for int num in arr
            System.out.print(num + " ");
        }
        System.out.println();
        
        // ========== MULTI-DIMENSIONAL ARRAYS ==========
        
        System.out.println("\n=== Multi-dimensional Arrays ===");
        
        // 2D array (matrix)
        int[][] matrix = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };
        
        System.out.println("2D Array (Matrix):");
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[i].length; j++) {
                System.out.print(matrix[i][j] + " ");
            }
            System.out.println();
        }
        
        for (int i = 0; i < matrix.length; i++) {
            for (int j: matrix[i]) {
                System.out.print(j + " ");
            }
            System.out.println();
        }
        

        // Using enhanced for loop for 2D array
        System.out.println("\nUsing enhanced for loop:");
        for (int[] row : matrix) {
            for (int element : row) {
                System.out.print(element + " ");
            }
            System.out.println();
        }
        
        // 3D array
        int[][][] cube = new int[2][3][4];
        System.out.println("\n3D Array dimensions: " + cube.length + "x" + 
                          cube[0].length + "x" + cube[0][0].length);
        
        // ========== COMMON ARRAY OPERATIONS ==========
        
        System.out.println("\n=== Common Array Operations ===");
        
        int[] numbers = {5, 2, 8, 1, 9, 3};
        
        // Find maximum
        int max = numbers[0];
        for (int i = 1; i < numbers.length; i++) {
            if (numbers[i] > max) {
                max = numbers[i];
            }
        }
        System.out.println("Maximum: " + max);
        
        int  max2 = Integer.MIN_VALUE;
        for (int num : numbers) {
            if (num > max2) {
                max2 = num;
            }
        }
        System.out.println("Maximum (using for-each): " + max2);

        // Find minimum
        int min = numbers[0];
        for (int i = 1; i < numbers.length; i++) {  // initial value; condition; increment
            if (numbers[i] < min) {
                min = numbers[i];
            }
        }
        System.out.println("Minimum: " + min);
        
        // Calculate sum
        int sum = 0;
        for (int num : numbers) {
            sum += num;
        }
        System.out.println("Sum: " + sum);
        System.out.println("Average: " + (double) sum / numbers.length);
        
        // Search for an element
        int searchValue = 8;
        boolean found = false;
        int index = -1;
        for (int i = 0; i < numbers.length; i++) {
            if (numbers[i] == searchValue) {
                found = true;
                index = i;
                break;
            }
        }
        System.out.println("Search for " + searchValue + ": " + 
                          (found ? "Found at index " + index : "Not found"));
        
        // ========== ARRAY COPY ==========
        
        System.out.println("\n=== Array Copy ===");
        
        int[] original = {1, 2, 3, 4, 5};
        int[] deep_copy = new int[original.length];
        
        // Shallow copy
        int [] shallowCopy = original;
        shallowCopy[0] = 99;  // Modifying shallowCopy also affects original
        int  value = original[0];  // value is now 99
        System.out.print("Shallow copy: ");
        for (int num : shallowCopy) System.out.print(num + " ");
        System.out.println();

        // deep copy
        for (int i = 0; i < original.length; i++) {
            deep_copy[i] = original[i];
        }
        
        System.out.print("Original: ");
        for (int num : original) System.out.print(num + " ");
        System.out.println();
        
        System.out.print("Copy: ");
        for (int num : deep_copy) System.out.print(num + " ");
        System.out.println();
        
        // Using System.arraycopy()
        int[] copy2 = new int[original.length];
        System.arraycopy(original, 0, copy2, 0, original.length);
        System.out.print("Copy using arraycopy: ");
        for (int num : copy2) System.out.print(num + " ");
        System.out.println();
        
        // ========== ARRAYS OF DIFFERENT TYPES ==========
        
        System.out.println("\n=== Arrays of Different Types ===");
        
        String[] names = {"Alice", "Bob", "Charlie"};
        System.out.print("String array: ");
        for (String name : names) {
            System.out.print(name + " ");
        }
        System.out.println();
        
        boolean[] flags = {true, false, true};
        System.out.print("Boolean array: ");
        for (boolean flag : flags) {
            System.out.print(flag + " ");
        }
        System.out.println();
        
        double[] prices = {19.99, 29.99, 39.99};
        System.out.print("Double array: ");
        for (double price : prices) {
            System.out.print(price + " ");
        }
        System.out.println();
    }
}

