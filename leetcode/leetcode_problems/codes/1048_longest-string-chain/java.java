/**
 * Problem: Longest String Chain
 * Difficulty: Medium
 * Tags: array, string, dp, hash, sort
 * 
 * Approach: Sort by length, DP - for each word, check if predecessor exists
 * Time Complexity: O(n * m^2) where n is words, m is max length
 * Space Complexity: O(n) for DP
 */

import java.util.*;

class Solution {
    public int longestStrChain(String[] words) {
        Arrays.sort(words, (a, b) -> a.length() - b.length());
        Map<String, Integer> dp = new HashMap<>();
        int maxChain = 1;
        
        for (String word : words) {
            dp.put(word, 1);
            for (int i = 0; i < word.length(); i++) {
                String predecessor = word.substring(0, i) + word.substring(i + 1);
                if (dp.containsKey(predecessor)) {
                    dp.put(word, Math.max(dp.get(word), dp.get(predecessor) + 1));
                }
            }
            maxChain = Math.max(maxChain, dp.get(word));
        }
        
        return maxChain;
    }
}