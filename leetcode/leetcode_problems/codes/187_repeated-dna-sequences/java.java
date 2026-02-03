/**
 * Problem: Repeated DNA Sequences
 * Difficulty: Medium
 * Tags: array, string, tree, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

import java.util.*;

class Solution {
    public List<String> findRepeatedDnaSequences(String s) {
        if (s.length() < 10) {
            return new ArrayList<>();
        }
        
        Map<String, Integer> seen = new HashMap<>();
        List<String> result = new ArrayList<>();
        
        for (int i = 0; i <= s.length() - 10; i++) {
            String sequence = s.substring(i, i + 10);
            seen.put(sequence, seen.getOrDefault(sequence, 0) + 1);
            if (seen.get(sequence) == 2) {
                result.add(sequence);
            }
        }
        
        return result;
    }
}