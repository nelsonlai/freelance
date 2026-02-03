/**
 * Problem: Sorting the Sentence
 * Difficulty: Easy
 * Tags: string, sort
 * 
 * Approach: Split words, extract position numbers, sort and reconstruct
 * Time Complexity: O(n log n) where n is words
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public String sortSentence(String s) {
        String[] words = s.split(" ");
        Arrays.sort(words, (a, b) -> {
            int posA = Character.getNumericValue(a.charAt(a.length() - 1));
            int posB = Character.getNumericValue(b.charAt(b.length() - 1));
            return Integer.compare(posA, posB);
        });
        
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < words.length; i++) {
            if (i > 0) result.append(" ");
            result.append(words[i].substring(0, words[i].length() - 1));
        }
        
        return result.toString();
    }
}