/**
 * Problem: Vowels of All Substrings
 * Difficulty: Medium
 * Tags: string, math, combinatorics
 * 
 * Approach: For each vowel at index i, count how many substrings contain it
 * Time Complexity: O(n) where n is string length
 * Space Complexity: O(1)
 */

import java.util.*;

class Solution {
    public long countVowels(String word) {
        Set<Character> vowels = new HashSet<>(Arrays.asList('a', 'e', 'i', 'o', 'u'));
        int n = word.length();
        long result = 0;
        
        for (int i = 0; i < n; i++) {
            char c = word.charAt(i);
            if (vowels.contains(c)) {
                // Number of substrings containing this vowel
                // Left choices: i + 1, Right choices: n - i
                result += (long)(i + 1) * (n - i);
            }
        }
        
        return result;
    }
}