/**
 * Problem: Index Pairs of a String
 * Difficulty: Easy
 * Tags: array, string, tree, sort
 * 
 * Approach: For each word, find all occurrences in text
 * Time Complexity: O(n * m * k) where n is text length, m is words, k is word length
 * Space Complexity: O(1) excluding output
 */

import java.util.*;

class Solution {
    public int[][] indexPairs(String text, String[] words) {
        List<int[]> result = new ArrayList<>();
        
        for (String word : words) {
            int start = 0;
            while (true) {
                int idx = text.indexOf(word, start);
                if (idx == -1) {
                    break;
                }
                result.add(new int[]{idx, idx + word.length() - 1});
                start = idx + 1;
            }
        }
        
        result.sort((a, b) -> {
            if (a[0] != b[0]) return a[0] - b[0];
            return a[1] - b[1];
        });
        
        return result.toArray(new int[result.size()][]);
    }
}