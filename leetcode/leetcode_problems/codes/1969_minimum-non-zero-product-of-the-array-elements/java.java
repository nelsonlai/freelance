/**
 * Problem: Minimum Non-Zero Product of the Array Elements
 * Difficulty: Medium
 * Tags: array, greedy, math, fast exponentiation
 * 
 * Approach: Minimize product by pairing (2^p-2) with 1, leaving (2^p-1) alone
 * Time Complexity: O(p) for exponentiation
 * Space Complexity: O(1)
 */

class Solution {
    private static final int MOD = 1000000007;
    
    public int minNonZeroProduct(int p) {
        long maxNum = (1L << p) - 1;  // 2^p - 1
        long pairs = (maxNum - 1) / 2;
        
        // (maxNum - 1) ^ pairs mod MOD
        long base = (maxNum - 1) % MOD;
        long result = power(base, pairs);
        result = (result * (maxNum % MOD)) % MOD;
        
        return (int) result;
    }
    
    private long power(long base, long exp) {
        long result = 1;
        while (exp > 0) {
            if ((exp & 1) == 1) {
                result = (result * base) % MOD;
            }
            base = (base * base) % MOD;
            exp >>= 1;
        }
        return result;
    }
}