/**
 * Problem: Count Good Numbers
 * Difficulty: Medium
 * Tags: string, math, fast exponentiation
 * 
 * Approach: Even positions: 5 choices (0,2,4,6,8), odd positions: 4 choices (2,3,5,7)
 * Time Complexity: O(log n) for exponentiation
 * Space Complexity: O(1)
 */

class Solution {
    private static final int MOD = 1000000007;
    
    public int countGoodNumbers(long n) {
        long evenCount = (n + 1) / 2;
        long oddCount = n / 2;
        
        return (int) ((power(5, evenCount) * power(4, oddCount)) % MOD);
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