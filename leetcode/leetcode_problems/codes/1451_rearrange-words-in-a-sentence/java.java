/**
 * Problem: Rearrange Words in a Sentence
 * Difficulty: Medium
 * Tags: string, sort
 * 
 * Approach: Split, sort by length, capitalize first word, lowercase rest
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n) for words list
 */

import java.util.*;

class Solution {
    public String arrangeWords(String text) {
        String[] words = text.split(" ");
        Arrays.sort(words, (a, b) -> a.length() - b.length());
        
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < words.length; i++) {
            if (i == 0) {
                result.append(Character.toUpperCase(words[i].charAt(0)));
                result.append(words[i].substring(1).toLowerCase());
            } else {
                result.append(" ");
                result.append(words[i].toLowerCase());
            }
        }
        
        return result.toString();
    }
}