/**
 * Problem: Replace Words
 * Difficulty: Medium
 * Tags: array, string, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public String replaceWords(List<String> dictionary, String sentence) {
        Set<String> dictionarySet = new HashSet<>(dictionary);
        String[] words = sentence.split(" ");
        
        for (int i = 0; i < words.length; i++) {
            for (int j = 1; j <= words[i].length(); j++) {
                String prefix = words[i].substring(0, j);
                if (dictionarySet.contains(prefix)) {
                    words[i] = prefix;
                    break;
                }
            }
        }
        
        return String.join(" ", words);
    }
}