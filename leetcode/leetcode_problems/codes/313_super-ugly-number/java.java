/**
 * Problem: Super Ugly Number
 * Difficulty: Medium
 * Tags: array, dp, math, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
    public int nthSuperUglyNumber(int n, int[] primes) {
        int[] ugly = new int[n];
        int[] indices = new int[primes.length];
        ugly[0] = 1;
        
        for (int i = 1; i < n; i++) {
            int nextUgly = Integer.MAX_VALUE;
            for (int j = 0; j < primes.length; j++) {
                nextUgly = Math.min(nextUgly, ugly[indices[j]] * primes[j]);
            }
            ugly[i] = nextUgly;
            
            for (int j = 0; j < primes.length; j++) {
                if (ugly[indices[j]] * primes[j] == nextUgly) {
                    indices[j]++;
                }
            }
        }
        
        return ugly[n - 1];
    }
}