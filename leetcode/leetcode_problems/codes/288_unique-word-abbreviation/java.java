/**
 * Problem: Unique Word Abbreviation
 * Difficulty: Medium
 * Tags: array, string, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class ValidWordAbbr {
    private Map<String, Set<String>> abbrMap;

    public ValidWordAbbr(String[] dictionary) {
        abbrMap = new HashMap<>();
        for (String word : dictionary) {
            String abbr = getAbbr(word);
            abbrMap.putIfAbsent(abbr, new HashSet<>());
            abbrMap.get(abbr).add(word);
        }
    }
    
    private String getAbbr(String word) {
        if (word.length() <= 2) {
            return word;
        }
        return word.charAt(0) + String.valueOf(word.length() - 2) + word.charAt(word.length() - 1);
    }
    
    public boolean isUnique(String word) {
        String abbr = getAbbr(word);
        Set<String> words = abbrMap.get(abbr);
        return words == null || (words.size() == 1 && words.contains(word));
    }
}

/**
 * Your ValidWordAbbr object will be instantiated and called as such:
 * ValidWordAbbr obj = new ValidWordAbbr(dictionary);
 * boolean param_1 = obj.isUnique(word);
 */