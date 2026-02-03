/**
 * Problem: K-diff Pairs in an Array
 * Difficulty: Medium
 * Tags: array, hash, sort, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int findPairs(int[] nums, int k) {
        Map<Integer, Integer> count = new HashMap<>();
        for (int num : nums) {
            count.put(num, count.getOrDefault(num, 0) + 1);
        }
        
        int result = 0;
        if (k == 0) {
            for (int cnt : count.values()) {
                if (cnt > 1) {
                    result++;
                }
            }
        } else {
            for (int num : count.keySet()) {
                if (count.containsKey(num + k)) {
                    result++;
                }
            }
        }
        
        return result;
    }
}