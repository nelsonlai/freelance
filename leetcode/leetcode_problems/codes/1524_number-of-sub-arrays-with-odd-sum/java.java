/**
 * Problem: Number of Sub-arrays With Odd Sum
 * Difficulty: Medium
 * Tags: array, dp, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
    public int numOfSubarrays(int[] arr) {
        int MOD = 1000000007;
        int oddCount = 0;
        int evenCount = 1;
        int prefixSum = 0;
        long result = 0;
        
        for (int num : arr) {
            prefixSum += num;
            if (prefixSum % 2 == 1) {
                result = (result + evenCount) % MOD;
                oddCount++;
            } else {
                result = (result + oddCount) % MOD;
                evenCount++;
            }
        }
        
        return (int) result;
    }
}