/**
 * Problem: Make Two Arrays Equal by Reversing Subarrays
 * Difficulty: Easy
 * Tags: array, hash, sort
 * 
 * Approach: Check if both arrays have same elements (can always rearrange)
 * Time Complexity: O(n) where n is length of arrays
 * Space Complexity: O(n) for counter
 */

import java.util.*;

class Solution {
    public boolean canBeEqual(int[] target, int[] arr) {
        Map<Integer, Integer> count = new HashMap<>();
        for (int num : target) {
            count.put(num, count.getOrDefault(num, 0) + 1);
        }
        for (int num : arr) {
            count.put(num, count.getOrDefault(num, 0) - 1);
        }
        for (int val : count.values()) {
            if (val != 0) {
                return false;
            }
        }
        return true;
    }
}