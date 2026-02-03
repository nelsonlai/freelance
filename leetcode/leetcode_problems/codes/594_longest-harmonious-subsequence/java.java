/**
 * Problem: Longest Harmonious Subsequence
 * Difficulty: Easy
 * Tags: array, hash, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int findLHS(int[] nums) {
        Map<Integer, Integer> count = new HashMap<>();
        for (int num : nums) {
            count.put(num, count.getOrDefault(num, 0) + 1);
        }
        
        int maxLength = 0;
        for (int num : count.keySet()) {
            if (count.containsKey(num + 1)) {
                maxLength = Math.max(maxLength, count.get(num) + count.get(num + 1));
            }
        }
        
        return maxLength;
    }
}