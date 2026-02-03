/**
 * Problem: Longest Common Subsequence Between Sorted Arrays
 * Difficulty: Medium
 * Tags: array, hash, sort, two pointers
 * 
 * Approach: Count frequency, return elements appearing in all arrays
 * Time Complexity: O(n * m) where n is arrays, m is avg length
 * Space Complexity: O(m)
 */

import java.util.*;

class Solution {
    public List<Integer> longestCommonSubsequence(int[][] arrays) {
        Map<Integer, Integer> count = new HashMap<>();
        for (int[] arr : arrays) {
            Set<Integer> seen = new HashSet<>();
            for (int num : arr) {
                if (seen.add(num)) {
                    count.put(num, count.getOrDefault(num, 0) + 1);
                }
            }
        }
        
        int n = arrays.length;
        List<Integer> result = new ArrayList<>();
        for (Map.Entry<Integer, Integer> entry : count.entrySet()) {
            if (entry.getValue() == n) {
                result.add(entry.getKey());
            }
        }
        Collections.sort(result);
        return result;
    }
}