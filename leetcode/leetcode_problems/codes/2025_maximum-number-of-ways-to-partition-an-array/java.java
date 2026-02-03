/**
 * Problem: Maximum Number of Ways to Partition an Array
 * Difficulty: Hard
 * Tags: array, hash, prefix sum
 * 
 * Approach: Use prefix sum and hash map to count partitions before/after changing each element
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public int waysToPartition(int[] nums, int k) {
        int n = nums.length;
        long total = 0;
        for (int num : nums) {
            total += num;
        }
        
        // Calculate prefix sum
        long[] prefix = new long[n];
        prefix[0] = nums[0];
        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] + nums[i];
        }
        
        // Count partitions without changing any element
        int result = 0;
        for (int i = 0; i < n - 1; i++) {
            if (prefix[i] == total - prefix[i]) {
                result++;
            }
        }
        
        // For each position, calculate partitions if we change nums[i] to k
        Map<Long, Integer> leftCount = new HashMap<>();
        Map<Long, Integer> rightCount = new HashMap<>();
        
        // Initialize rightCount with all prefix sums
        for (int i = 0; i < n - 1; i++) {
            rightCount.put(prefix[i], rightCount.getOrDefault(prefix[i], 0) + 1);
        }
        
        for (int i = 0; i < n; i++) {
            // Change nums[i] from original to k
            long diff = k - nums[i];
            long newTotal = total + diff;
            
            // Count partitions
            int count = 0;
            
            // Partitions in left side (before index i)
            if (i > 0) {
                long target = newTotal / 2;
                count += leftCount.getOrDefault(target, 0);
            }
            
            // Partitions in right side (at or after index i)
            if (i < n - 1) {
                long target = (newTotal - 2 * diff) / 2;
                count += rightCount.getOrDefault(target, 0);
            }
            
            result = Math.max(result, count);
            
            // Update counts for next iteration
            if (i < n - 1) {
                rightCount.put(prefix[i], rightCount.get(prefix[i]) - 1);
                if (rightCount.get(prefix[i]) == 0) {
                    rightCount.remove(prefix[i]);
                }
                if (i > 0) {
                    leftCount.put(prefix[i - 1], leftCount.getOrDefault(prefix[i - 1], 0) + 1);
                }
            }
        }
        
        return result;
    }
}