/**
 * Problem: Two Out of Three
 * Difficulty: Easy
 * Tags: array, hash
 * 
 * Approach: Count occurrences in each array, return numbers appearing in at least 2 arrays
 * Time Complexity: O(n) where n is total elements
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public List<Integer> twoOutOfThree(int[] nums1, int[] nums2, int[] nums3) {
        Map<Integer, Set<Integer>> count = new HashMap<>();
        
        for (int num : nums1) {
            count.computeIfAbsent(num, k -> new HashSet<>()).add(1);
        }
        for (int num : nums2) {
            count.computeIfAbsent(num, k -> new HashSet<>()).add(2);
        }
        for (int num : nums3) {
            count.computeIfAbsent(num, k -> new HashSet<>()).add(3);
        }
        
        List<Integer> result = new ArrayList<>();
        for (Map.Entry<Integer, Set<Integer>> entry : count.entrySet()) {
            if (entry.getValue().size() >= 2) {
                result.add(entry.getKey());
            }
        }
        
        return result;
    }
}