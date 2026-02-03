/**
 * Problem: Keyboard Row
 * Difficulty: Easy
 * Tags: array, string, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public String[] findWords(String[] words) {
        Set<Character> row1 = new HashSet<>(Arrays.asList('q','w','e','r','t','y','u','i','o','p'));
        Set<Character> row2 = new HashSet<>(Arrays.asList('a','s','d','f','g','h','j','k','l'));
        Set<Character> row3 = new HashSet<>(Arrays.asList('z','x','c','v','b','n','m'));
        List<Set<Character>> rows = Arrays.asList(row1, row2, row3);
        
        List<String> result = new ArrayList<>();
        for (String word : words) {
            String wordLower = word.toLowerCase();
            for (Set<Character> row : rows) {
                boolean valid = true;
                for (char c : wordLower.toCharArray()) {
                    if (!row.contains(c)) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    result.add(word);
                    break;
                }
            }
        }
        
        return result.toArray(new String[0]);
    }
}