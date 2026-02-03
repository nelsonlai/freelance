/**
 * Problem: Redistribute Characters to Make All Strings Equal
 * Difficulty: Easy
 * Tags: array, string, hash
 * 
 * Approach: Count all characters, check if divisible by number of words
 * Time Complexity: O(n * m) where n is words, m is avg length
 * Space Complexity: O(1) - fixed 26 characters
 */

import java.util.*;

class Solution {
    public boolean makeEqual(String[] words) {
        int[] count = new int[26];
        for (String word : words) {
            for (char c : word.toCharArray()) {
                count[c - 'a']++;
            }
        }
        
        int n = words.length;
        for (int c : count) {
            if (c % n != 0) {
                return false;
            }
        }
        
        return true;
    }
}