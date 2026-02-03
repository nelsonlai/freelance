/**
 * Problem: Word Squares
 * Difficulty: Hard
 * Tags: array, string
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public List<List<String>> wordSquares(String[] words) {
        int n = words[0].length();
        Map<String, List<String>> prefixMap = new HashMap<>();
        
        for (String word : words) {
            for (int i = 0; i < n; i++) {
                String prefix = word.substring(0, i + 1);
                prefixMap.putIfAbsent(prefix, new ArrayList<>());
                prefixMap.get(prefix).add(word);
            }
        }
        
        List<List<String>> result = new ArrayList<>();
        List<String> square = new ArrayList<>();
        
        backtrack(square, 0, n, prefixMap, result);
        
        return result;
    }
    
    private void backtrack(List<String> square, int index, int n, 
                           Map<String, List<String>> prefixMap, 
                           List<List<String>> result) {
        if (index == n) {
            result.add(new ArrayList<>(square));
            return;
        }
        
        StringBuilder prefix = new StringBuilder();
        for (String word : square) {
            prefix.append(word.charAt(index));
        }
        
        List<String> candidates = prefixMap.getOrDefault(prefix.toString(), new ArrayList<>());
        for (String word : candidates) {
            square.add(word);
            backtrack(square, index + 1, n, prefixMap, result);
            square.remove(square.size() - 1);
        }
    }
}