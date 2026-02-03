/**
 * Problem: Partition Array Into Two Arrays to Minimize Sum Difference
 * Difficulty: Hard
 * Tags: array, dp, search, meet-in-middle
 * 
 * Approach: Meet-in-middle - split array in half, find all possible sums for each half
 * Time Complexity: O(n * 2^(n/2))
 * Space Complexity: O(2^(n/2))
 */

import java.util.*;

class Solution {
    public int minimumDifference(int[] nums) {
        int n = nums.length;
        int total = 0;
        for (int num : nums) {
            total += num;
        }
        int target = total / 2;
        
        // Split array in half
        int[] left = Arrays.copyOfRange(nums, 0, n / 2);
        int[] right = Arrays.copyOfRange(nums, n / 2, n);
        
        // Generate all possible sums for left half with different sizes
        Map<Integer, List<Integer>> leftSums = new HashMap<>();
        for (int mask = 0; mask < (1 << left.length); mask++) {
            int sum = 0;
            for (int i = 0; i < left.length; i++) {
                if ((mask & (1 << i)) != 0) {
                    sum += left[i];
                }
            }
            int count = Integer.bitCount(mask);
            leftSums.computeIfAbsent(count, k -> new ArrayList<>()).add(sum);
        }
        
        // Sort for binary search
        for (int count : leftSums.keySet()) {
            Collections.sort(leftSums.get(count));
        }
        
        // Generate all possible sums for right half
        int result = Integer.MAX_VALUE;
        for (int mask = 0; mask < (1 << right.length); mask++) {
            int sum = 0;
            for (int i = 0; i < right.length; i++) {
                if ((mask & (1 << i)) != 0) {
                    sum += right[i];
                }
            }
            int count = Integer.bitCount(mask);
            int neededCount = n / 2 - count;
            
            if (leftSums.containsKey(neededCount)) {
                List<Integer> arr = leftSums.get(neededCount);
                // Binary search for closest sum to target - sum
                int idx = Collections.binarySearch(arr, target - sum);
                if (idx < 0) {
                    idx = -(idx + 1);
                }
                
                // Check closest values
                for (int i = Math.max(0, idx - 1); i <= Math.min(arr.size() - 1, idx + 1); i++) {
                    int sum1 = sum + arr.get(i);
                    int sum2 = total - sum1;
                    result = Math.min(result, Math.abs(sum1 - sum2));
                }
            }
        }
        
        return result;
    }
}