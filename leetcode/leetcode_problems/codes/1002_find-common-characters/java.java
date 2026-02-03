/**
 * Problem: Find Common Characters
 * Difficulty: Easy
 * Tags: array, string, hash
 * 
 * Approach: Find minimum count of each character across all words
 * Time Complexity: O(n * m) where n is number of words, m is average length
 * Space Complexity: O(1) for character counts
 */

import java.util.*;

class Solution {
    public List<String> commonChars(String[] words) {
        int[] minCount = new int[26];
        Arrays.fill(minCount, Integer.MAX_VALUE);
        
        for (String word : words) {
            int[] count = new int[26];
            for (char c : word.toCharArray()) {
                count[c - 'a']++;
            }
            for (int i = 0; i < 26; i++) {
                minCount[i] = Math.min(minCount[i], count[i]);
            }
        }
        
        List<String> result = new ArrayList<>();
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < minCount[i]; j++) {
                result.add(String.valueOf((char)('a' + i)));
            }
        }
        
        return result;
    }
}