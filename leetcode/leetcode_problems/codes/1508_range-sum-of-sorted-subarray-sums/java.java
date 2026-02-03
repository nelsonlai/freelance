/**
 * Problem: Range Sum of Sorted Subarray Sums
 * Difficulty: Medium
 * Tags: array, sort, search
 * 
 * Approach: Generate all subarray sums, sort, sum elements from left to right
 * Time Complexity: O(n^2 log n) for generating and sorting
 * Space Complexity: O(n^2) for subarray sums
 */

import java.util.*;

class Solution {
    public int rangeSum(int[] nums, int n, int left, int right) {
        int MOD = 1000000007;
        List<Long> subarraySums = new ArrayList<>();
        
        for (int i = 0; i < n; i++) {
            long currentSum = 0;
            for (int j = i; j < n; j++) {
                currentSum += nums[j];
                subarraySums.add(currentSum);
            }
        }
        
        Collections.sort(subarraySums);
        long result = 0;
        for (int i = left - 1; i < right; i++) {
            result = (result + subarraySums.get(i)) % MOD;
        }
        
        return (int) result;
    }
}