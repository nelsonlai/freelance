/**
 * Problem: Longest Subsequence Repeated k Times
 * Difficulty: Hard
 * Tags: string, graph, greedy, backtracking
 * 
 * Approach: Generate candidate subsequences, check if they appear k times
 * Time Complexity: O(26^L * n) where L is length of subsequence
 * Space Complexity: O(L)
 */

import java.util.*;

class Solution {
    public String longestSubsequenceRepeatedK(String s, int k) {
        // Count character frequencies
        Map<Character, Integer> count = new HashMap<>();
        for (char c : s.toCharArray()) {
            count.put(c, count.getOrDefault(c, 0) + 1);
        }
        
        // Only consider characters that appear at least k times
        List<Character> candidates = new ArrayList<>();
        for (Map.Entry<Character, Integer> entry : count.entrySet()) {
            if (entry.getValue() >= k) {
                candidates.add(entry.getKey());
            }
        }
        Collections.sort(candidates);
        
        // Try all possible subsequences of increasing length
        StringBuilder result = new StringBuilder();
        
        backtrack(s, k, new StringBuilder(), candidates, result);
        
        return result.toString();
    }
    
    private void backtrack(String s, int k, StringBuilder current, 
                          List<Character> remainingChars, StringBuilder result) {
        if (current.length() > result.length() && isSubsequence(s, current.toString(), k)) {
            result.setLength(0);
            result.append(current);
        }
        
        if (current.length() >= s.length() / k) {
            return;
        }
        
        // Try adding each remaining character
        for (char c : remainingChars) {
            current.append(c);
            backtrack(s, k, current, remainingChars, result);
            current.setLength(current.length() - 1);
        }
    }
    
    private boolean isSubsequence(String s, String subseq, int k) {
        // Check if subseq appears k times in s
        int occurrences = 0;
        int i = 0;
        
        while (i < s.length() && occurrences < k) {
            int j = 0;
            int start = i;
            while (start < s.length() && j < subseq.length()) {
                if (s.charAt(start) == subseq.charAt(j)) {
                    j++;
                }
                start++;
            }
            if (j == subseq.length()) {
                occurrences++;
                i = start;
            } else {
                i++;
            }
        }
        
        return occurrences >= k;
    }
}