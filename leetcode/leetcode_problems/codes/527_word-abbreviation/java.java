/**
 * Problem: Word Abbreviation
 * Difficulty: Hard
 * Tags: array, string, greedy, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public List<String> wordsAbbreviation(List<String> words) {
        int n = words.size();
        String[] result = new String[n];
        int[] prefixLen = new int[n];
        Arrays.fill(prefixLen, 1);
        
        for (int i = 0; i < n; i++) {
            result[i] = getAbbrev(words.get(i), prefixLen[i]);
        }
        
        for (int i = 0; i < n; i++) {
            while (true) {
                List<Integer> duplicates = new ArrayList<>();
                for (int j = i + 1; j < n; j++) {
                    if (result[i].equals(result[j])) {
                        duplicates.add(j);
                    }
                }
                if (duplicates.isEmpty()) {
                    break;
                }
                duplicates.add(i);
                for (int idx : duplicates) {
                    prefixLen[idx]++;
                    result[idx] = getAbbrev(words.get(idx), prefixLen[idx]);
                }
            }
        }
        
        return Arrays.asList(result);
    }
    
    private String getAbbrev(String word, int prefixLen) {
        if (word.length() <= prefixLen + 2) {
            return word;
        }
        return word.substring(0, prefixLen) + (word.length() - prefixLen - 1) + word.charAt(word.length() - 1);
    }
}