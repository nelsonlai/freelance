/**
 * Problem: Maximum Number of Words You Can Type
 * Difficulty: Easy
 * Tags: string, hash
 * 
 * Approach: Check each word if contains any broken letter
 * Time Complexity: O(n * m) where n is words, m is avg word length
 * Space Complexity: O(1) - fixed 26 characters
 */

import java.util.*;

class Solution {
    public int canBeTypedWords(String text, String brokenLetters) {
        Set<Character> broken = new HashSet<>();
        for (char c : brokenLetters.toCharArray()) {
            broken.add(c);
        }
        
        String[] words = text.split(" ");
        int count = 0;
        
        for (String word : words) {
            boolean canType = true;
            for (char c : word.toCharArray()) {
                if (broken.contains(c)) {
                    canType = false;
                    break;
                }
            }
            if (canType) {
                count++;
            }
        }
        
        return count;
    }
}