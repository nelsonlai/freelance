/**
 * Problem: Non-negative Integers without Consecutive Ones
 * Difficulty: Hard
 * Tags: dp
 * 
 * Approach: Dynamic programming with memoization or tabulation
 * Time Complexity: O(n * m) where n and m are problem dimensions
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
    public int findIntegers(int n) {
        int[] fib = new int[32];
        fib[0] = 1;
        fib[1] = 2;
        for (int i = 2; i < 32; i++) {
            fib[i] = fib[i-1] + fib[i-2];
        }
        
        int result = 0;
        int prevBit = 0;
        
        for (int i = 30; i >= 0; i--) {
            if ((n >> i & 1) == 1) {
                result += fib[i];
                if (prevBit == 1) {
                    return result;
                }
                prevBit = 1;
            } else {
                prevBit = 0;
            }
        }
        
        return result + 1;
    }
}