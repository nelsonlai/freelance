/**
 * Problem: Word Pattern II
 * Difficulty: Medium
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public boolean wordPatternMatch(String pattern, String s) {
        return backtrack(pattern, 0, s, 0, new HashMap<>(), new HashMap<>());
    }
    
    private boolean backtrack(String pattern, int patternIdx, String s, int sIdx,
                             Map<Character, String> charToWord, Map<String, Character> wordToChar) {
        if (patternIdx == pattern.length() && sIdx == s.length()) {
            return true;
        }
        if (patternIdx == pattern.length() || sIdx == s.length()) {
            return false;
        }
        
        char c = pattern.charAt(patternIdx);
        
        if (charToWord.containsKey(c)) {
            String word = charToWord.get(c);
            if (sIdx + word.length() > s.length() || !s.substring(sIdx, sIdx + word.length()).equals(word)) {
                return false;
            }
            return backtrack(pattern, patternIdx + 1, s, sIdx + word.length(), charToWord, wordToChar);
        }
        
        for (int end = sIdx + 1; end <= s.length(); end++) {
            String word = s.substring(sIdx, end);
            
            if (wordToChar.containsKey(word)) {
                continue;
            }
            
            charToWord.put(c, word);
            wordToChar.put(word, c);
            
            if (backtrack(pattern, patternIdx + 1, s, end, charToWord, wordToChar)) {
                return true;
            }
            
            charToWord.remove(c);
            wordToChar.remove(word);
        }
        
        return false;
    }
}