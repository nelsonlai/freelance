/**
 * Problem: Complex Number Multiplication
 * Difficulty: Medium
 * Tags: string, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public String complexNumberMultiply(String num1, String num2) {
        int[] a = parseComplex(num1);
        int[] b = parseComplex(num2);
        
        int real = a[0] * b[0] - a[1] * b[1];
        int imag = a[0] * b[1] + a[1] * b[0];
        
        return real + "+" + imag + "i";
    }
    
    private int[] parseComplex(String num) {
        String[] parts = num.substring(0, num.length() - 1).split("\\+");
        return new int[]{Integer.parseInt(parts[0]), Integer.parseInt(parts[1])};
    }
}