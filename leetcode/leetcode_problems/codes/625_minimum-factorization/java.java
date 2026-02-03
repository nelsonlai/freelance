/**
 * Problem: Minimum Factorization
 * Difficulty: Medium
 * Tags: greedy, math
 * 
 * Approach: Greedy algorithm with local optimal choices
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int smallestFactorization(int num) {
        if (num < 2) {
            return num;
        }
        
        long result = 0;
        long base = 1;
        
        for (int i = 9; i >= 2; i--) {
            while (num % i == 0) {
                result += i * base;
                base *= 10;
                num /= i;
            }
        }
        
        return (num == 1 && result <= Integer.MAX_VALUE) ? (int)result : 0;
    }
}