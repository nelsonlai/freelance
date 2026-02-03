/**
 * Problem: Number of Good Pairs
 * Difficulty: Easy
 * Tags: array, math, hash
 * 
 * Approach: Count frequency of each number, for n occurrences, there are n*(n-1)/2 pairs
 * Time Complexity: O(n) where n is length of nums
 * Space Complexity: O(n) for frequency map
 */

import java.util.*;

class Solution {
    public int numIdenticalPairs(int[] nums) {
        Map<Integer, Integer> freq = new HashMap<>();
        for (int num : nums) {
            freq.put(num, freq.getOrDefault(num, 0) + 1);
        }
        
        int result = 0;
        for (int count : freq.values()) {
            result += count * (count - 1) / 2;
        }
        
        return result;
    }
}