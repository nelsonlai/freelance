/**
 * Problem: Super Pow
 * Difficulty: Medium
 * Tags: array, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    private static final int MOD = 1337;
    
    public int superPow(int a, int[] b) {
        int result = 1;
        for (int digit : b) {
            result = powMod(result, 10) * powMod(a, digit) % MOD;
        }
        return result;
    }
    
    private int powMod(int base, int exp) {
        int result = 1;
        base %= MOD;
        while (exp > 0) {
            if (exp % 2 == 1) {
                result = (result * base) % MOD;
            }
            base = (base * base) % MOD;
            exp /= 2;
        }
        return result;
    }
}