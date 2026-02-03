/**
 * Problem: Camelcase Matching
 * Difficulty: Medium
 * Tags: array, string
 * 
 * Approach: Two pointers - match pattern characters, ensure uppercase letters match
 * Time Complexity: O(n * m) where n is queries, m is average length
 * Space Complexity: O(1) excluding output
 */

import java.util.*;

class Solution {
    public List<Boolean> camelMatch(String[] queries, String pattern) {
        List<Boolean> result = new ArrayList<>();
        for (String query : queries) {
            result.add(match(query, pattern));
        }
        return result;
    }
    
    private boolean match(String query, String pattern) {
        int j = 0;
        for (int i = 0; i < query.length(); i++) {
            char c = query.charAt(i);
            if (j < pattern.length() && c == pattern.charAt(j)) {
                j++;
            } else if (Character.isUpperCase(c)) {
                return false;
            }
        }
        return j == pattern.length();
    }
}