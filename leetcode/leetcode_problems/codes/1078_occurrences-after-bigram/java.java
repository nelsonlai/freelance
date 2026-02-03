/**
 * Problem: Occurrences After Bigram
 * Difficulty: Easy
 * Tags: array, string
 * 
 * Approach: Split text, find bigrams, collect following words
 * Time Complexity: O(n) where n is text length
 * Space Complexity: O(n) for words
 */

import java.util.*;

class Solution {
    public String[] findOcurrences(String text, String first, String second) {
        String[] words = text.split(" ");
        List<String> result = new ArrayList<>();
        
        for (int i = 0; i < words.length - 2; i++) {
            if (words[i].equals(first) && words[i + 1].equals(second)) {
                result.add(words[i + 2]);
            }
        }
        
        return result.toArray(new String[0]);
    }
}