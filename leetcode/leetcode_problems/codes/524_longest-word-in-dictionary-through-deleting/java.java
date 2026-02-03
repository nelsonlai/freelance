/**
 * Problem: Longest Word in Dictionary through Deleting
 * Difficulty: Medium
 * Tags: array, string, graph, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public String findLongestWord(String s, List<String> dictionary) {
        Collections.sort(dictionary, (a, b) -> {
            if (a.length() != b.length()) {
                return Integer.compare(b.length(), a.length());
            }
            return a.compareTo(b);
        });
        
        for (String word : dictionary) {
            if (isSubsequence(word, s)) {
                return word;
            }
        }
        
        return "";
    }
    
    private boolean isSubsequence(String word, String s) {
        int i = 0;
        for (char c : s.toCharArray()) {
            if (i < word.length() && word.charAt(i) == c) {
                i++;
            }
        }
        return i == word.length();
    }
}