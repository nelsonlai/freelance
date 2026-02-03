/**
 * Problem: Count Vowel Substrings of a String
 * Difficulty: Easy
 * Tags: string, hash, sliding window
 * 
 * Approach: Count substrings containing all 5 vowels exactly once each
 * Time Complexity: O(n^2) where n is string length
 * Space Complexity: O(1)
 */

import java.util.*;

class Solution {
    public int countVowelSubstrings(String word) {
        Set<Character> vowels = new HashSet<>(Arrays.asList('a', 'e', 'i', 'o', 'u'));
        int result = 0;
        int n = word.length();
        
        for (int i = 0; i < n; i++) {
            Map<Character, Integer> count = new HashMap<>();
            for (int j = i; j < n; j++) {
                char c = word.charAt(j);
                if (!vowels.contains(c)) {
                    break;
                }
                count.put(c, count.getOrDefault(c, 0) + 1);
                if (count.size() == 5) {
                    boolean allOne = true;
                    for (char v : vowels) {
                        if (count.getOrDefault(v, 0) != 1) {
                            allOne = false;
                            break;
                        }
                    }
                    if (allOne) {
                        result++;
                    }
                }
            }
        }
        
        return result;
    }
}