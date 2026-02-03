/**
 * Problem: Sum of Distances
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public long[] distance(int[] nums) {
        int n = nums.length;
        Map<Integer, List<Integer>> valueToIndices = new HashMap<>();
        for (int i = 0; i < n; i++) {
            valueToIndices.putIfAbsent(nums[i], new ArrayList<>());
            valueToIndices.get(nums[i]).add(i);
        }
        
        long[] result = new long[n];
        
        for (List<Integer> indices : valueToIndices.values()) {
            if (indices.size() == 1) {
                continue;
            }
            
            long[] prefix = new long[indices.size() + 1];
            for (int i = 0; i < indices.size(); i++) {
                prefix[i + 1] = prefix[i] + indices.get(i);
            }
            
            int m = indices.size();
            for (int i = 0; i < indices.size(); i++) {
                int idx = indices.get(i);
                long leftSum = (long)i * idx - prefix[i];
                long rightSum = (prefix[m] - prefix[i + 1]) - (long)(m - i - 1) * idx;
                result[idx] = leftSum + rightSum;
            }
        }
        
        return result;
    }
}