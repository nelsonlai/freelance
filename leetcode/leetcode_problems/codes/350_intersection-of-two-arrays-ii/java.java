/**
 * Problem: Intersection of Two Arrays II
 * Difficulty: Easy
 * Tags: array, hash, sort, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int[] intersect(int[] nums1, int[] nums2) {
        Map<Integer, Integer> count = new HashMap<>();
        for (int num : nums1) {
            count.put(num, count.getOrDefault(num, 0) + 1);
        }
        
        List<Integer> result = new ArrayList<>();
        for (int num : nums2) {
            if (count.getOrDefault(num, 0) > 0) {
                result.add(num);
                count.put(num, count.get(num) - 1);
            }
        }
        
        return result.stream().mapToInt(i -> i).toArray();
    }
}