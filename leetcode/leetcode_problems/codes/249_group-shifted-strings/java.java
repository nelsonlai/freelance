/**
 * Problem: Group Shifted Strings
 * Difficulty: Medium
 * Tags: array, string, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public List<List<String>> groupStrings(String[] strings) {
        Map<String, List<String>> groups = new HashMap<>();
        
        for (String s : strings) {
            String key = getKey(s);
            groups.putIfAbsent(key, new ArrayList<>());
            groups.get(key).add(s);
        }
        
        return new ArrayList<>(groups.values());
    }
    
    private String getKey(String s) {
        if (s.isEmpty()) {
            return "";
        }
        StringBuilder key = new StringBuilder();
        int base = s.charAt(0) - 'a';
        for (char c : s.toCharArray()) {
            int diff = (c - 'a' - base + 26) % 26;
            key.append(diff).append(",");
        }
        return key.toString();
    }
}