/**
 * Problem: Number of Wonderful Substrings
 * Difficulty: Medium
 * Tags: array, string, hash, bit manipulation
 * 
 * Approach: Use prefix XOR to track character parity, count substrings with at most 1 odd count
 * Time Complexity: O(n * 10) where n is length, 10 is possible characters
 * Space Complexity: O(1024) for mask counts
 */

import java.util.*;

class Solution {
    public long wonderfulSubstrings(String word) {
        Map<Integer, Long> count = new HashMap<>();
        count.put(0, 1L);
        int mask = 0;
        long result = 0;
        
        for (char c : word.toCharArray()) {
            int idx = c - 'a';
            mask ^= (1 << idx);
            
            // All even counts
            result += count.getOrDefault(mask, 0L);
            
            // One odd count
            for (int i = 0; i < 10; i++) {
                result += count.getOrDefault(mask ^ (1 << i), 0L);
            }
            
            count.put(mask, count.getOrDefault(mask, 0L) + 1);
        }
        
        return result;
    }
}