/**
 * Problem: Clumsy Factorial
 * Difficulty: Medium
 * Tags: math, stack
 * 
 * Approach: Process operations in groups: * / + - pattern, handle first group specially
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

class Solution {
    public int clumsy(int n) {
        if (n <= 2) return n;
        if (n == 3) return 6;
        
        int result = n * (n - 1) / (n - 2) + (n - 3);
        n -= 4;
        
        while (n >= 4) {
            result -= n * (n - 1) / (n - 2);
            result += (n - 3);
            n -= 4;
        }
        
        if (n == 3) {
            result -= 6;
        } else if (n == 2) {
            result -= 2;
        } else if (n == 1) {
            result -= 1;
        }
        
        return result;
    }
}