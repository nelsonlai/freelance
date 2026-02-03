/**
 * C.java - Data processing class
 * 
 * This class is used by A.java to perform data processing operations
 */

public class C {
    /**
     * Creates a personalized greeting message
     * @param name the name to greet
     * @return greeting message
     */
    public String createGreeting(String name) {
        return "Hello, " + name + "! Welcome to the program.";
    }
    
    /**
     * Finds the maximum value in an array
     * @param numbers array of integers
     * @return maximum value in the array
     */
    public int findMax(int[] numbers) {
        if (numbers == null || numbers.length == 0) {
            throw new IllegalArgumentException("Array cannot be null or empty");
        }
        
        int max = numbers[0];
        for (int i = 1; i < numbers.length; i++) {
            if (numbers[i] > max) {
                max = numbers[i];
            }
        }
        return max;
    }
    
    /**
     * Finds the minimum value in an array
     * @param numbers array of integers
     * @return minimum value in the array
     */
    public int findMin(int[] numbers) {
        if (numbers == null || numbers.length == 0) {
            throw new IllegalArgumentException("Array cannot be null or empty");
        }
        
        int min = numbers[0];
        for (int i = 1; i < numbers.length; i++) {
            if (numbers[i] < min) {
                min = numbers[i];
            }
        }
        return min;
    }
    
    /**
     * Reverses a string
     * @param str the string to reverse
     * @return reversed string
     */
    public String reverseString(String str) {
        if (str == null) {
            return null;
        }
        
        StringBuilder reversed = new StringBuilder();
        for (int i = str.length() - 1; i >= 0; i--) {
            reversed.append(str.charAt(i));
        }
        return reversed.toString();
    }
    
    /**
     * Calculates the average of an array of numbers
     * @param numbers array of integers
     * @return average value
     */
    public double calculateAverage(int[] numbers) {
        if (numbers == null || numbers.length == 0) {
            throw new IllegalArgumentException("Array cannot be null or empty");
        }
        
        int sum = 0;
        for (int num : numbers) {
            sum += num;
        }
        return (double) sum / numbers.length;
    }
}

