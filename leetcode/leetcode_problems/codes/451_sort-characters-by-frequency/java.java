/**
 * Problem: Sort Characters By Frequency
 * Difficulty: Medium
 * Tags: string, tree, hash, sort, queue, heap
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

import java.util.*;

class Solution {
    public String frequencySort(String s) {
        Map<Character, Integer> count = new HashMap<>();
        for (char c : s.toCharArray()) {
            count.put(c, count.getOrDefault(c, 0) + 1);
        }
        
        List<Map.Entry<Character, Integer>> list = new ArrayList<>(count.entrySet());
        list.sort((a, b) -> b.getValue().compareTo(a.getValue()));
        
        StringBuilder result = new StringBuilder();
        for (Map.Entry<Character, Integer> entry : list) {
            for (int i = 0; i < entry.getValue(); i++) {
                result.append(entry.getKey());
            }
        }
        
        return result.toString();
    }
}